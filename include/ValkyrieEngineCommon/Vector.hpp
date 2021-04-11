#ifndef VLK_VECTOR_HPP
#define VLK_VECTOR_HPP

#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "ValkyrieEngineCommon/VMath.hpp"
#include <type_traits>

namespace vlk
{
	template <Size N, typename Val>
	class VectorBase
	{
		public:
		typedef VectorBase<N, Val> SelfType;
		typedef Val ValueType;
		typedef Val ArrayType[N];

		ArrayType data;

		VLK_CXX14_CONSTEXPR inline VectorBase<N, Val>() :
			data {}
		{
			for (Size i = 0; i < N; i++)
			{
				data[i] = 0.0f;
			}
		}
		
		VLK_CXX14_CONSTEXPR inline VectorBase<N, Val>(const ArrayType& arr) :
			data {}
		{
		   for (Size i = 0; i < N; i++)
		   {
			   data[i] = arr[i];
		   }
		}

		/*
		template <typename... V>
		VLK_CXX14_CONSTEXPR inline VectorBase<N, Val>(Val vals...) :
			data{vals} { }
		*/

		VLK_CXX14_CONSTEXPR inline VectorBase<N, Val>(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline VectorBase<N, Val>(SelfType&&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(SelfType&&) = default;
		VLK_CXX20_CONSTEXPR inline ~VectorBase<N, Val>() = default;

		VLK_CXX14_CONSTEXPR inline SelfType operator+(const SelfType& rhs) const
		{
			ArrayType tmp;
			for (Size i = 0; i < N; i++) tmp[i] = data[i] + rhs[i];
			return VectorBase<N, Val>(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator-(const SelfType& rhs) const
		{
			ArrayType tmp;
			for (Size i = 0; i < N; i++) tmp[i] = data[i] - rhs[i];
			return VectorBase<N, Val>(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator*(const Val v) const
		{
			ArrayType tmp;
			for (Size i = 0; i < N; i++) tmp[i] = data[i] * v;
			return VectorBase<N, Val>(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType operator/(const Val v) const
		{
			ArrayType tmp;
			for (Size i = 0; i < N; i++) tmp[i] = data[i] / v;
			return VectorBase<N, Val>(tmp);
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator+=(const SelfType& rhs)
		{
			for (Size i = 0; i < N; i++) data[i] += rhs[i];
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator-=(const SelfType& rhs)
		{
			for (Size i = 0; i < N; i++) data[i] -= rhs[i];
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator*=(const Val v)
		{
			for (Size i = 0; i < N; i++) data[i] *= v;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline SelfType& operator/=(const Val v)
		{
			for (Size i = 0; i < N; i++) data[i] /= v;
			return *this;
		}

		VLK_CXX14_CONSTEXPR inline bool operator==(const SelfType& rhs) const
		{
			for (Size i = 0; i < N; i++)
			{
				if (data[i] != rhs[i]) return false;
			}

			return true;
		}

		VLK_CXX14_CONSTEXPR inline bool operator!=(const SelfType& rhs) const
		{
			for (Size i = 0; i < N; i++)
			{
				if (data[i] != rhs[i]) return true;
			}

			return false;
		}

		VLK_CXX14_CONSTEXPR inline Val* Data() { return data; }
		VLK_CXX14_CONSTEXPR inline const Val* Data() const { return data; }

		VLK_CXX14_CONSTEXPR inline Val& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Val& operator[](Size i) const { return data[i]; }
	};

	template <typename Val = Int>
	class Point
	{
		public:
		typedef VectorBase<2, Val> DataType;
		typedef Point<Val> SelfType;
		typedef Val ValueType;

		private:
		VectorBase<2, Val> data;
		public:

		VLK_STATIC_ASSERT_MSG(std::is_integral<Val>::value & std::is_signed<Val>::value, "Val mist be a signed integer type.");

		VLK_CXX14_CONSTEXPR inline Val& X() { return data[0]; }
		VLK_CXX14_CONSTEXPR inline Val& Y() { return data[1]; }

		VLK_CXX14_CONSTEXPR inline const Val& X() const { return data[0]; }
		VLK_CXX14_CONSTEXPR inline const Val& Y() const { return data[1]; }

		VLK_CXX14_CONSTEXPR inline Point() : data({0, 0}) { }
		VLK_CXX14_CONSTEXPR inline Point(Val x, Val y) : data({x, y}) { }
		VLK_CXX14_CONSTEXPR inline Point(const DataType& d) : data(d) { }

		VLK_CXX14_CONSTEXPR inline Point(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline Point(SelfType&&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(const SelfType&) = default;
		VLK_CXX14_CONSTEXPR inline SelfType& operator=(SelfType&&) = default;
		VLK_CXX20_CONSTEXPR inline ~Point() = default;

		VLK_CXX14_CONSTEXPR inline Val& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Val& operator[](Size i) const { return data[i]; }

		VLK_CXX14_CONSTEXPR inline Val* Data() { return data.Data(); }
		VLK_CXX14_CONSTEXPR inline const Val* Data() const { return data.Data(); }

		VLK_CXX14_CONSTEXPR inline SelfType operator-() const { return SelfType(-this->X(), -this->Y()); }
		VLK_CXX14_CONSTEXPR inline bool operator==(const SelfType& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const SelfType& rhs) const { return data != rhs.data; }

		VLK_CXX14_CONSTEXPR inline SelfType operator+(const SelfType& rhs) const { return SelfType(data + rhs.data); }
		VLK_CXX14_CONSTEXPR inline SelfType operator-(const SelfType& rhs) const { return SelfType(data - rhs.data); }
		VLK_CXX14_CONSTEXPR inline SelfType operator*(const Val factor) const { return SelfType(data * factor); }
		VLK_CXX14_CONSTEXPR inline SelfType operator/(const Val factor) const { return SelfType(data / factor); }

		VLK_CXX14_CONSTEXPR inline SelfType& operator +=(const SelfType& rhs) { data += rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline SelfType& operator -=(const SelfType& rhs) { data -= rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline SelfType& operator *=(const Val factor) { data *= factor; return *this; }
		VLK_CXX14_CONSTEXPR inline SelfType& operator /=(const Val factor) { data /= factor; return *this; }
	};

	/*!
	 * \brief 2-dimensional vector class
	 */
	class Vector2
	{
		VectorBase<2, Float> data;
		public:

		VLK_CXX14_CONSTEXPR inline Float& X() { return data[0]; }
		VLK_CXX14_CONSTEXPR inline Float& Y() { return data[1]; }

		VLK_CXX14_CONSTEXPR inline const Float& X() const { return data[0]; }
		VLK_CXX14_CONSTEXPR inline const Float& Y() const { return data[1]; }

		VLK_CXX14_CONSTEXPR inline Vector2() : data({0.0f, 0.0f}) { };
		VLK_CXX14_CONSTEXPR inline Vector2(Float x, Float y): data({x, y}) { }
		VLK_CXX14_CONSTEXPR inline Vector2(const VectorBase<2, Float>& d) : data(d) { }

		VLK_CXX14_CONSTEXPR inline Vector2(const Vector2& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector2(Vector2&& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector2& operator=(const Vector2& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector2& operator=(Vector2&& v) = default;
		VLK_CXX20_CONSTEXPR inline ~Vector2() = default;

		VLK_CXX14_CONSTEXPR inline Float& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Float& operator[](Size i) const { return data[i]; }

		VLK_CXX14_CONSTEXPR inline Float* Data() { return data.Data(); }
		VLK_CXX14_CONSTEXPR inline const Float* Data() const { return data.Data(); }

		VLK_CXX14_CONSTEXPR inline Vector2 operator-() const { return Vector2(-this->X(), -this->Y()); }
		VLK_CXX14_CONSTEXPR inline bool operator==(const Vector2& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Vector2& rhs) const { return data != rhs.data; }

		VLK_CXX14_CONSTEXPR inline Vector2 operator+(const Vector2& rhs) const { return Vector2(data + rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector2 operator-(const Vector2& rhs) const { return Vector2(data - rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector2 operator*(const Float factor) const { return Vector2(data * factor); }
		VLK_CXX14_CONSTEXPR inline Vector2 operator/(const Float factor) const { return Vector2(data / factor); }

		VLK_CXX14_CONSTEXPR inline Vector2& operator +=(const Vector2& rhs) { data += rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector2& operator -=(const Vector2& rhs) { data -= rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector2& operator *=(const Float factor) { data *= factor; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector2& operator /=(const Float factor) { data /= factor; return *this; }

		//TODO: Make members like Length non-static with ConstexprWrapper<void>

		/*!
		 * \brief Returns the length (magnitude) of a vector.
		 * \sa #SquareLength
		 */
		static inline Float Length(const Vector2& v)
		{
			return Sqrt(Dot(v, v));
		}

		/*!
		 * \copydoc Vector2::Length(const Vector2&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> Length(ConstexprWrapper<Vector2> v)
		{
			return Sqrt(Dot(v, v));
		}

		/*!
		 * \brief Returns the square length of this vector. Can be faster than calculating #Length.
		 * If you're just comparing the relative length of vectors and don't need the actual magnitude, use this.
		 *
		 * \sa #Length
		 */
		static inline Float SquareLength(const Vector2& v)
		{
			return Dot(v, v);
		}

		/*!
		 * \copydoc vlk::Vector2::SquareLength(const Vector2& v)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> SquareLength(ConstexprWrapper<Vector2> v)
		{
			return Dot(v, v);
		}

		/*!
		 * \brief Returns a unit vector with the same direction as \c v
		 *
		 * \warning If the provided vector has a length of zero, both components
		 * of the returned vector will be <tt>NaN</tt>
		 */
		static inline Vector2 Normalized(const Vector2& v)
		{
			return v / Vector2::Length(v);
		}

		/*!
		 * \copydoc vlk::Vector2::Normalized
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector2> Normalized(ConstexprWrapper<Vector2> v)
		{
			return ForceCXPR(static_cast<Vector2>(v) / Vector2::Length(v));
		}

		/*!
		 * \brief Returns the distance between two vectors
		 */
		static inline Float Distance(const Vector2& lhs, const Vector2& rhs)
		{
			return Vector2::Length(lhs - rhs);
		}

		/*!
		 * \copydoc vlk::Vector2::Distance(const Vector2&, const Vector2&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> Distance(ConstexprWrapper<Vector2> lhs, ConstexprWrapper<Vector2> rhs)
		{
			return Vector2::Length(ForceCXPR(static_cast<Vector2>(lhs) - static_cast<Vector2>(rhs)));
		}

		/*!
		 * \brief Returns the dot product of two vectors
		 */
		static inline Float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return (rhs[0] * lhs[0]) + (rhs[1] * lhs[1]);
		}

		/*!
		 * \copydoc vlk::Vector2::Dot(const Vector2&, const Vector2&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR ConstexprWrapper<Float> Dot(ConstexprWrapper<Vector2> lhs, ConstexprWrapper<Vector2> rhs)
		{
			return ForceCXPR((rhs.value[0] * lhs.value[0]) + (rhs.value[1] * lhs.value[1]));
		}

		/*!
		 * \brief Returns the angle in radians between two vectors
		 */
		static inline Float AngleBetween(const Vector2& lhs, const Vector2& rhs)
		{
			return ACos(Vector2::Dot(lhs, rhs) / Vector2::Length(lhs) * Vector2::Length(rhs));
		}

		/*!
		 * \copydoc vlk::Vector2::AngleBetween(const Vector2&, const Vector2&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> AngleBetween(
			ConstexprWrapper<Vector2> lhs,
			ConstexprWrapper<Vector2> rhs)
		{
			return ACos(ForceCXPR(Vector2::Dot(lhs, rhs).value / Vector2::Length(lhs).value * Vector2::Length(rhs).value));
		}

		/*!
		 * \brief Linearly interpolates between two vectors
		 */
		static VLK_CXX14_CONSTEXPR inline Vector2 Lerp(const Vector2& start, const Vector2& end, const Float t)
		{
			return Vector2(start[0] + t * (end[0] - start[0]), start[1] + t * (end[1] - start[1]));
		}
		
		/*!
		 * \copydoc vlk::Vector2::Lerp(const Vector2&, const Vector2&, const Float)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector2> Lerp(
			ConstexprWrapper<Vector2> start,
			ConstexprWrapper<Vector2> end,
			ConstexprWrapper<Float> t)
		{
			return ForceCXPR(Vector2::Lerp(*start, *end, *t));
		}

		/*!
		 * \brief Returns a vector perpendicular to \c v
		 */
		static VLK_CXX14_CONSTEXPR inline Vector2 Perpendicular(const Vector2& v)
		{
			return Vector2(v[1], -v[0]);
		}

		/*!
		 * \copydoc vlk::Vector2::Perpendicular(const Vector2&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector2> Perpendicular(ConstexprWrapper<Vector2> v)
		{
			return ForceCXPR(Vector2::Perpendicular(*v));
		}

		static VLK_CXX14_CONSTEXPR inline Vector2 Up()    { return Vector2( 0.0f,  1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector2 Down()  { return Vector2( 0.0f, -1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector2 Left()  { return Vector2(-1.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector2 Right() { return Vector2( 1.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector2 One()   { return Vector2( 1.0f,  1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector2 Zero()  { return Vector2( 0.0f,  0.0f); }
	};

	class Vector3
	{
		VectorBase<3, Float> data;
		public:

		VLK_CXX14_CONSTEXPR inline Float& X() { return data[0]; }
		VLK_CXX14_CONSTEXPR inline Float& Y() { return data[1]; }
		VLK_CXX14_CONSTEXPR inline Float& Z() { return data[2]; }

		VLK_CXX14_CONSTEXPR inline const Float& X() const { return data[0]; }
		VLK_CXX14_CONSTEXPR inline const Float& Y() const { return data[1]; }
		VLK_CXX14_CONSTEXPR inline const Float& Z() const { return data[2]; }

		VLK_CXX14_CONSTEXPR inline Vector3(): data({0.0f, 0.0f, 0.0f}) { }
		VLK_CXX14_CONSTEXPR inline Vector3(Float x, Float y, Float z): data({x, y, z}) { }
		VLK_CXX14_CONSTEXPR inline Vector3(const VectorBase<3, Float>& d) : data(d) { }
		VLK_CXX14_CONSTEXPR inline explicit Vector3(const Vector2& v, Float z): data({v[0], v[1], z}) { }

		VLK_CXX14_CONSTEXPR inline Vector3(const Vector3& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector3(Vector3&& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector3& operator=(const Vector3& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector3& operator=(Vector3&& v) = default;
		VLK_CXX20_CONSTEXPR inline ~Vector3() = default;

		VLK_CXX14_CONSTEXPR inline operator Vector2() const { return Vector2(data[0], data[1]); }

		VLK_CXX14_CONSTEXPR inline Float& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Float& operator[](Size i) const { return data[i]; }

		VLK_CXX14_CONSTEXPR inline Float* Data() { return data.Data(); }
		VLK_CXX14_CONSTEXPR inline const Float* Data() const { return data.Data(); }

		VLK_CXX14_CONSTEXPR inline Vector3 operator-() const { return Vector3(-data[0], -data[1], -data[2]); }
		VLK_CXX14_CONSTEXPR inline bool operator==(const Vector3& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Vector3& rhs) const { return data != rhs.data; }

		VLK_CXX14_CONSTEXPR inline Vector3 operator+(const Vector3& rhs) const { return Vector3(data + rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector3 operator-(const Vector3& rhs) const { return Vector3(data - rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector3 operator*(const Float factor) const { return Vector3(data * factor); }
		VLK_CXX14_CONSTEXPR inline Vector3 operator/(const Float factor) const { return Vector3(data / factor); }

		VLK_CXX14_CONSTEXPR inline Vector3& operator +=(const Vector3& rhs) { data += rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector3& operator -=(const Vector3& rhs) { data -= rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector3& operator *=(const Float factor) { data *= factor; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector3& operator /=(const Float factor) { data /= factor; return *this; }

		static VLK_CXX14_CONSTEXPR inline Vector3 Up()			{ return Vector3( 0.0f,  1.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Down()		{ return Vector3( 0.0f, -1.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Left()		{ return Vector3(-1.0f,  0.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Right()		{ return Vector3( 1.0f,  0.0f,  0.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Forward()		{ return Vector3( 0.0f,  0.0f, -1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Backward()	{ return Vector3( 0.0f,  0.0f,  1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 One()			{ return Vector3( 1.0f,  1.0f,  1.0f); }
		static VLK_CXX14_CONSTEXPR inline Vector3 Zero()		{ return Vector3( 0.0f,  0.0f,  0.0f); }
	
		/*!
		 * \brief Returns the length (magnitude) of this vector
		 * \sa SquareLength
		 */	
		static inline Float Length(const Vector3& v)
		{
			return Sqrt(Dot(v, v));
		}

		/*!
		 * \copydoc vlk::Vector3::Length(const Vector3&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> Length(ConstexprWrapper<Vector3> v)
		{
			return Sqrt(Dot(v, v));
		}

		/*!
		 * \brief Returns the square of the length of this vector. Can be faster than calculating #Length
		 * If you're just comparing the relative length of vectors and don't need the actual magnitude, use this.
		 * \sa Length
		 */
		static inline Float SquareLength(const Vector3& v)
		{
			return Dot(v, v);
		}

		/*!
		 * \copydoc vlk::Vector3::SquareLength(const Vector3&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> SquareLength(ConstexprWrapper<Vector3> v)
		{
			return Dot(v, v);	
		}

		/*!
		 * \brief Returns the distance between two vectors
		 */
		static inline Float Distance(const Vector3& lhs, const Vector3& rhs)
		{
			return Length(lhs - rhs);
		}

		/*!
		 * \copydoc vlk::Vector3::Distance(const Vector3&, const Vector3&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> Distance(ConstexprWrapper<Vector3> lhs, ConstexprWrapper<Vector3> rhs)
		{
			return Length(ForceCXPR(lhs.value - rhs.value));
		}

		/*!
		 * \brief Returns the dot product of two vectors
		 */
		static VLK_CXX14_CONSTEXPR inline Float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]) + (lhs[2] * rhs[2]);
		}

		/*!
		 * \copydoc vlk::Vector3::Dot(const Vector3&, const Vector3&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Float> Dot(ConstexprWrapper<Vector3> lhs, ConstexprWrapper<Vector3> rhs)
		{
			return ForceCXPR(Dot(*lhs, *rhs));
		}

		/*!
		 * \brief Returns a unit vector with the same direction as \c v
		 *
		 * \warning If the provided vector has a length of zero, both components
		 * of the returned vector will be <tt>NaN</tt>
		 */
		static inline Vector3 Normalized(const Vector3& v)
		{
			return v / Length(v);
		}

		/*!
		 * \copydoc vlk::Vector3::Normalized(const Vector3& v)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector3> Normalized(ConstexprWrapper<Vector3> v)
		{
			return ForceCXPR(v.value / Length(v).value);
		}

		/*!
		 * \brief Linearly interpolates between two vectors
		 */
		static VLK_CXX14_CONSTEXPR inline Vector3 Lerp(const Vector3& start, const Vector3& end, const Float t)
		{
			return Vector3(
				start[0] + t * (end[0] - start[0]),
				start[1] + t * (end[1] - start[1]),
				start[2] + t * (end[2] - start[2]));
		}

		/*!
		 * \copydoc vlk::Vector3::Lerp(const Vector3&, const Vector3&, const Float)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector3> Lerp(ConstexprWrapper<Vector3> start, ConstexprWrapper<Vector3> end, ConstexprWrapper<Float> t)
		{
			return ForceCXPR(Vector3::Lerp(
				*start,
				*end,
				*t));
		}

		/*!
		 * \brief Returns the cross product of two vectors
		 */
		static VLK_CXX14_CONSTEXPR inline Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs[1] * rhs[2] - lhs[2] * rhs[1],
				lhs[2] * rhs[0] - lhs[0] * rhs[2],
				lhs[0] * rhs[1] - lhs[1] * rhs[0]);
		}

		/*!
		 * \copydoc vlk::Vector3::Cross(const Vector3&, const Vector3&)
		 *
		 * \cxpr
		 */
		static VLK_CXX14_CONSTEXPR inline ConstexprWrapper<Vector3> Cross(ConstexprWrapper<Vector3> lhs, ConstexprWrapper<Vector3> rhs)
		{
			return ForceCXPR(Vector3::Cross(*lhs, *rhs));
		}
	};

	class Vector4
	{
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

		VLK_CXX14_CONSTEXPR inline Vector4() : data({0.0f, 0.0f, 0.0f, 0.0f}) { }
		VLK_CXX14_CONSTEXPR inline Vector4(const Vector3& xyz, Float w) : data({xyz[0], xyz[1], xyz[2], w}) { }
		VLK_CXX14_CONSTEXPR inline Vector4(Float x, Float y, Float z, Float w) : data({x, y, z, w}) { }
		VLK_CXX14_CONSTEXPR inline Vector4(const VectorBase<4, Float>& d) : data(d) { }

		VLK_CXX14_CONSTEXPR inline Vector4(const Vector4& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector4(Vector4&& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector4& operator=(const Vector4& v) = default;
		VLK_CXX14_CONSTEXPR inline Vector4& operator=(Vector4&& v) = default;
		VLK_CXX20_CONSTEXPR inline ~Vector4() = default;

		VLK_CXX14_CONSTEXPR inline operator Vector3() const { return Vector3(data[0], data[1], data[2]); }

		VLK_CXX14_CONSTEXPR inline Float& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Float& operator[](Size i) const { return data[i]; }

		VLK_CXX14_CONSTEXPR inline Float* Data() { return data.Data(); }
		VLK_CXX14_CONSTEXPR inline const Float* Data() const { return data.Data(); }

		VLK_CXX14_CONSTEXPR inline Vector4 operator-() const { return Vector4(-data[0], -data[1], -data[2], -data[3]); }
		VLK_CXX14_CONSTEXPR inline bool operator==(const Vector4& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Vector4& rhs) const { return data != rhs.data; }

		VLK_CXX14_CONSTEXPR inline Vector4 operator+(const Vector4& rhs) const { return Vector4(data + rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector4 operator-(const Vector4& rhs) const { return Vector4(data - rhs.data); }
		VLK_CXX14_CONSTEXPR inline Vector4 operator*(const Float factor) const { return Vector4(data * factor); }
		VLK_CXX14_CONSTEXPR inline Vector4 operator/(const Float factor) const { return Vector4(data / factor); }

		VLK_CXX14_CONSTEXPR inline Vector4& operator +=(const Vector4& rhs) { data += rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector4& operator -=(const Vector4& rhs) { data -= rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector4& operator *=(const Float factor) { data *= factor; return *this; }
		VLK_CXX14_CONSTEXPR inline Vector4& operator /=(const Float factor) { data /= factor; return *this; }
	};
}

#endif
