/*!
 * \file Quaternion.hpp
 * \brief Quaternion class file.
 */

#ifndef VLK_QUATERNION_HPP
#define VLK_QUATERNION_HPP

#include "ValkyrieEngineCommon/Vector.hpp"
#include <type_traits>

namespace vlk
{
	class Quaternion
	{
		// Ordered XYZW
		VectorBase<4, Float> data;
		public:

		VLK_CXX14_CONSTEXPR inline Float& X() { return data[0]; }
		VLK_CXX14_CONSTEXPR inline Float& Y() { return data[1]; }
		VLK_CXX14_CONSTEXPR inline Float& Z() { return data[2]; }
		VLK_CXX14_CONSTEXPR inline Float& W() { return data[3]; }

		VLK_CXX14_CONSTEXPR inline const Float& X() const { return data[0]; }
		VLK_CXX14_CONSTEXPR inline const Float& Y() const { return data[1]; }
		VLK_CXX14_CONSTEXPR inline const Float& Z() const { return data[2]; }
		VLK_CXX14_CONSTEXPR inline const Float& W() const { return data[3]; }

		VLK_CXX14_CONSTEXPR inline Quaternion() : data({0.0f, 0.0f, 0.0f, 1.0f}) {}
		VLK_CXX14_CONSTEXPR inline Quaternion(Float x, Float y, Float z, Float w) :	data({x, y, z, w}) { }
		VLK_CXX14_CONSTEXPR inline Quaternion(const Quaternion&) = default;
		VLK_CXX14_CONSTEXPR inline Quaternion(Quaternion&&) = default;
		VLK_CXX14_CONSTEXPR inline Quaternion& operator=(const Quaternion&) = default;
		VLK_CXX14_CONSTEXPR inline Quaternion& operator=(Quaternion&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Quaternion() = default;

		VLK_CXX14_CONSTEXPR inline Float& operator[](Size s) { return data[s]; }
		VLK_CXX14_CONSTEXPR inline const Float& operator[](Size s) const { return data[s]; }

		VLK_CXX14_CONSTEXPR inline bool operator==(const Quaternion& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Quaternion& rhs) const { return data != rhs.data; }

		//! Multiplies two quaternions.
		VLK_CXX14_CONSTEXPR inline Quaternion operator*(const Quaternion& rhs) const
		{
			return Quaternion(
				W() * rhs.X() + X() * rhs.W() + Y() * rhs.Z() - Z() * rhs.Y(),
				W() * rhs.Y() + Y() * rhs.W() + Z() * rhs.X() - X() * rhs.Z(),
				W() * rhs.Z() + Z() * rhs.W() + X() * rhs.Y() - Y() * rhs.X(),
				W() * rhs.W() - X() * rhs.X() - Y() * rhs.Y() - Z() * rhs.Z());
		}

		/*!
		 * \brief Constructs a quaternion representing a rotation of <tt>angle</tt> radians around an arbitrary axis <tt>axis</tt>.
		 *
		 * \param axis A normalized unit vector representing the axis of rotation.
		 * \param angle An angle measured in radians.
		 */
		static inline Quaternion AngleAxis(const Float angle, const Vector3& axis)
		{
			Float a = angle / 2.0f;
			Float sinA = Sin(a);
			Float cosA = Cos(a);

			return Quaternion(
				axis[0] * sinA,
				axis[1] * sinA,
				axis[2] * sinA,
				cosA
				);
		}

		/*!
		 * \copydoc vlk::Quaternion::AngleAxis(const Float, const Vector3&)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline Quaternion AngleAxis(ConstexprWrapper<Float> angle, ConstexprWrapper<Vector3> axis)
		{
			Float a = angle / 2.0f;
			Float sinA = Sin(ForceCXPR(a));
			Float cosA = Cos(ForceCXPR(a));

			return Quaternion(
				axis.value[0] * sinA,
				axis.value[1] * sinA,
				axis.value[2] * sinA,
				cosA
				);
		}

		/*!
		 * \brief Constructs a quaternion representing a rotation of <tt>angle</tt> radians around the X-axis.
		 */
		static inline Quaternion RotationX(const Float angle)
		{
			Float a = angle / 2.0f;

			return Quaternion(
				Sin(a),
				0.0f,
				0.0f,
				Cos(a));
		}

		/*!
		 * \copydoc vlk::Quaternion::RotationX(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Quaternion> RotationX(ConstexprWrapper<Float> angle)
		{
			Float a = angle / 2.0f;

			return ForceCXPR(Quaternion(
				Sin(ForceCXPR(a)),
				0.0f,
				0.0f,
				Cos(ForceCXPR(a))));
		}
		
		/*!
		 * \brief Constructs a quaternion representing a rotation of <tt>angle</tt> radians around the Y-axis.
		 */
		static inline Quaternion RotationY(const Float angle)
		{
			Float a = angle / 2.0f;

			return Quaternion(
				0.0f,
				Sin(a),
				0.0f,
				Cos(a));
		}

		/*!
		 * \copydoc vlk::Quaternion::RotationZ(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Quaternion> RotationY(ConstexprWrapper<Float> angle)
		{
			Float a = angle / 2.0f;

			return ForceCXPR(Quaternion(
				0.0f,
				Sin(ForceCXPR(a)),
				0.0f,
				Cos(ForceCXPR(a))));
		}

		/*!
		 * \brief Constructs a quaternion representing a rotation of <tt>angle</tt> radians around the Z-axis.
		 */
		static inline Quaternion RotationZ(const Float angle)
		{
			Float a = angle / 2.0f;

			return Quaternion(
				0.0f,
				0.0f,
				Sin(a),
				Cos(a));
		}

		/*!
		 * \copydoc vlk::Quaternion::RotationZ(const Float)
		 *
		 * \remark Constexpr-compatible overload. Do not use in runtime code.
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Quaternion> RotationZ(ConstexprWrapper<Float> angle)
		{
			Float a = angle / 2.0f;

			return ForceCXPR(Quaternion(
				0.0f,
				0.0f,
				Sin(ForceCXPR(a)),
				Cos(ForceCXPR(a))));
		}
	};
}

#endif
