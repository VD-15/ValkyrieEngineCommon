#ifndef VLK_TRANSFORM_HPP
#define VLK_TRANSFORM_HPP

#include "ValkyrieEngineCommon/Matrix.hpp"
#include <algorithm>
#include <shared_mutex>
#include <stdexcept>
#include <unordered_map>

namespace vlk
{
	/*!
	 * \brief 2D geometric transform.
	 *
	 * Combines a scale, rotation and translation into a single operation.
	 */
	class Transform2D
	{
		/*!
		 * \brief The parent of this transform. May be <tt>nullptr</tt>.
		 *
		 * If present, this transform function will be performed relative to the coordinate space of the parent.
		 */
		const Transform2D* parent;

		public:

		Vector2 translation;
		Float rotation;
		Vector2 scale;

		VLK_CXX14_CONSTEXPR inline Transform2D() :
			parent(nullptr),
			translation(),
			rotation(0.f),
			scale(1.f, 1.f)
		{ }

		VLK_CXX14_CONSTEXPR inline Transform2D(const Transform2D&) = default;
		VLK_CXX14_CONSTEXPR inline Transform2D(Transform2D&&) = default;
		VLK_CXX14_CONSTEXPR inline Transform2D& operator=(const Transform2D&) = default;
		VLK_CXX14_CONSTEXPR inline Transform2D& operator=(Transform2D&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Transform2D() = default;

		VLK_CXX14_CONSTEXPR inline bool operator==(const Transform2D& rhs) const
		{
			return
				parent == rhs.parent &&
				translation == rhs.translation &&
				rotation == rhs.rotation &&
				scale == rhs.scale;
		};

		VLK_CXX14_CONSTEXPR inline bool operator!=(const Transform2D& rhs) const
		{
			return
				parent != rhs.parent || 
				translation != rhs.translation ||
				rotation != rhs.rotation ||
				scale != rhs.scale;
		}

		//! brief Gets a transformation matrix representing this transform of this object in local space.
		inline Matrix3 GetMatrix() const
		{
			return 
				Matrix3::CreateTranslation(translation) *
				Matrix3::CreateRotation(rotation) *
				Matrix3::CreateScale(scale);
		}

		/*!
		 * \copydoc vlk::Transform2D::GetMatrix() const
		 * \cxpr
		 */
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix3> GetMatrix(ConstexprWrapper<void>) const
		{
			return ForceCXPR(
				Matrix3::CreateTranslation(translation) *
				Matrix3::CreateRotation(ForceCXPR(rotation)).value *
				Matrix3::CreateScale(scale));
		}

		/*!
		 * \brief Gets a transformation matrix representing the transform of this object and all it's parent transforms in world space.
		 */
		inline Matrix3 GetWorldMatrix() const
		{
			if (parent == nullptr) return GetMatrix();
			return parent->GetWorldMatrix() * GetMatrix();
		}

		/*!
		 * \copydoc vlk::Transform2D::GetWorldMatrix() const
		 * \cxpr
		 */
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Matrix3> GetWorldMatrix(ConstexprWrapper<void>) const
		{
			if (parent == nullptr) return ForceCXPR(GetMatrix(ForceCXPR()).value);
			return ForceCXPR(parent->GetWorldMatrix(ForceCXPR()).value * GetMatrix(ForceCXPR()));
		}

		/*!
		 * \brief Gets the current parent of this transform object, may be <tt>nullptr</tt>.
		 */
		VLK_CXX14_CONSTEXPR inline const Transform2D* GetParent() const
		{
			return parent;
		}

		/*!
		 * \brief Sets the parent of this transform.
		 *
		 * \param tr The new parent of this transform or <tt>nullptr</tt> to remove the current parent.
		 * Additionally, <tt>this</tt> must not be equal to <tt>tr</tt> or any parent of <tt>tr</tt>.
		 *
		 * \throws std::runtime_error If <tt>this</tt> is already a parent of <tt>tr</tt>.
		 */
		VLK_CXX14_CONSTEXPR inline void SetParent(const Transform2D* tr)
		{
			for (const Transform2D* tt = tr; tt != nullptr; tt = tt->parent)
			{
				if (tt == this)
				{
					throw std::runtime_error("Circular transform hierarchy formed; A transform cannot be parented to itself.");
					return;
				}
			}

			parent = tr;
		}

		/*!
		 * \brief Gets the translation of this transform in world space.
		 */
		inline Vector2 GetWorldTranslation() const
		{
			return GetWorldMatrix() * Vector3(0.f, 0.f, 1.f);
		}

		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector2> GetWorldTranslation(ConstexprWrapper<void>) const
		{
			return ForceCXPR<Vector2>(GetWorldMatrix(ForceCXPR()).value * Vector3(0.f, 0.f, 1.f));
		}

		/*!
		 * \brief Gets the rotation of this transform in world space.
		 */
		inline Float GetWorldRotation() const
		{
			Matrix3 world(GetWorldMatrix());
			Vector2 leftDirection = (world * Vector3(1.f, 0.f, 1.f)) - (world * Vector3(0.f, 0.f, 1.f));
			return ATan2(leftDirection[1], leftDirection[2]);
		}
		
		/*!
		 * \copydoc vlk::Transform2D::GetWorldRotation() const
		 * \cxpr
		 */
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> GetWorldRotation(ConstexprWrapper<void>) const
		{
			Matrix3 world(GetWorldMatrix(ForceCXPR()));
			Vector2 leftDirection = (world * Vector3(1.f, 0.f, 1.f)) - (world * Vector3(0.f, 0.f, 1.f));
			return ATan2(ForceCXPR(leftDirection[1]), ForceCXPR(leftDirection[2]));
		}

		/*! 
		 * \brief Gets the approximate scale of this transform in world space.
		 */
		inline Vector2 GetWorldScale() const
		{
			Matrix3 world(GetWorldMatrix());
			return (world * Vector3(1.f, 1.f, 1.f)) - (world * Vector3(0.f, 0.f, 1.f));
		}
		
		/*!
		 * \copydoc vlk::Transform2D::GetWorldScale() const
		 * \cxpr
		 */
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector2> GetWorldScale(ConstexprWrapper<void>) const
		{
			Matrix3 world(GetWorldMatrix(ForceCXPR()));
			return ForceCXPR<Vector2>((world * Vector3(1.f, 1.f, 1.f)) - (world * Vector3(0.f, 0.f, 1.f)));
		}
	};
	
	/*!
	 * \brief 3D geometric transform.
	 *
	 * Combines a scale, rotation and translation into a single operation.
	 */
	class Transform3D
	{
		/*!
		 * \brief The parent of this transform. May be <tt>nullptr</tt>.
		 *
		 * If present, this transform function will be performed relative to the coordinate space of the parent.
		 */
		const Transform3D* parent;

		public:

		Vector3 translation;
		Quaternion rotation;
		Vector3 scale;

		VLK_CXX14_CONSTEXPR inline Transform3D() :
			parent(nullptr),
			translation(),
			rotation(),
			scale(1.f, 1.f, 1.f)
		{ }

		VLK_CXX14_CONSTEXPR inline Transform3D(const Transform3D&) = default;
		VLK_CXX14_CONSTEXPR inline Transform3D(Transform3D&&) = default;
		VLK_CXX14_CONSTEXPR inline Transform3D& operator=(const Transform3D&) = default;
		VLK_CXX14_CONSTEXPR inline Transform3D& operator=(Transform3D&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Transform3D() = default;

		VLK_CXX14_CONSTEXPR inline bool operator==(const Transform3D& rhs) const
		{
			return
				parent == rhs.parent &&
				translation == rhs.translation &&
				rotation == rhs.rotation &&
				scale == rhs.scale;
		};

		VLK_CXX14_CONSTEXPR inline bool operator!=(const Transform3D& rhs) const
		{
			return
				parent != rhs.parent || 
				translation != rhs.translation ||
				rotation != rhs.rotation ||
				scale != rhs.scale;
		}

		//! brief Gets a transformation matrix representing this transform of this object in local space.
		VLK_CXX14_CONSTEXPR inline Matrix4 GetMatrix() const
		{
			return
				Matrix4::CreateTranslation(translation) *
				Matrix4::CreateRotation(rotation) *
				Matrix4::CreateScale(scale);
		}

		/*!
		 * \brief Gets a transformation matrix representing the transform of this object and all it's parent transforms in world space.
		 */
		VLK_CXX14_CONSTEXPR inline Matrix4 GetWorldMatrix() const
		{
			if (parent == nullptr) return GetMatrix();
			return parent->GetWorldMatrix() * GetMatrix();
		}

		/*!
		 * \brief Gets the current parent of this transform object, may be <tt>nullptr</tt>.
		 */
		VLK_CXX14_CONSTEXPR inline const Transform3D* GetParent() const
		{
			return parent;
		}

		/*!
		 * \brief Sets the parent of this transform.
		 *
		 * \param tr The new parent of this transform or <tt>nullptr</tt> to remove the current parent.
		 * Additionally, <tt>this</tt> must not be equal to <tt>tr</tt> or any parent of <tt>tr</tt>.
		 *
		 * \throws std::runtime_error If <tt>this</tt> is already a parent of <tt>tr</tt>.
		 */
		VLK_CXX14_CONSTEXPR inline void SetParent(const Transform3D* tr)
		{
			for (const Transform3D* tt = tr; tt != nullptr; tt++)
			{
				if (tt == this)
				{
					throw std::runtime_error("Circular transform hierarchy formed; A transform cannot be parented to itself.");
					return;
				}
			}

			parent = tr;
		}

		/*!
		 * \brief Gets the translation of this transform in world space.
		 */
		VLK_CXX14_CONSTEXPR inline Vector3 GetWorldTranslation() const
		{
			return GetWorldMatrix() * Vector4(0.f, 0.f, 0.f, 1.f);
		}

		/*!
		 * \brief Gets the rotation of this transform in world space.
		 */
		inline Quaternion GetWorldRotation() const
		{
			Matrix4 world(GetWorldMatrix());
			Vector3 point (world * Vector4(1.f, 0.f, 0.f, 1.f));
			Vector3 axis = point - (world * Vector4(0.f, 0.f, 0.f, 1.f));
			Float angle = Vector3::Dot(Vector4(1.f, 0.f, 0.f, 1.f), point);
			return Quaternion::AngleAxis(angle, axis);
		}

		VLK_CXX14_CONSTEXPR inline Quaternion GetWorldRotation(ConstexprWrapper<void>) const
		{
			Matrix4 world(GetWorldMatrix());
			Vector3 point (world * Vector4(1.f, 0.f, 0.f, 1.f));
			Vector3 axis = point - (world * Vector4(0.f, 0.f, 0.f, 1.f));
			Float angle = Vector3::Dot(ForceCXPR(Vector3(1.f, 0.f, 0.f)), ForceCXPR(point));
			return Quaternion::AngleAxis(ForceCXPR(angle), ForceCXPR(axis));
		}

		/*! 
		 * \brief Gets the approximate scale of this transform in world space.
		 */
		inline Vector3 GetWorldScale() const
		{
			Matrix4 world(GetWorldMatrix());
			return (world * Vector4(1.f, 1.f, 1.f, 1.f)) - (world * Vector4(0.f, 0.f, 0.f, 1.f));
		}
	};
}

#endif
