#pragma once
#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "static_math/static_math.h"
#include <math.h>
#include <type_traits>

//static_math is used to provide constexpr equivelants of the standard cmath header
//so that all vector expressions can be calculated at compile-time. However, Since
//cmath is considerably faster, we elect to use that at runtime instead, using
//std::is_constant_evaluated to discriminate between compile-time and runtime.
//
//This std::is_constant_evaluated call has a small overhead that leads to slower
//dynamic times when compared to just using cmath, however I believe the much 
//faster times achieved in a static scenario are worth it.
//
//Tests were run to calculate the square root of a float 1,000,000,000 times,
//this float was declared either constexpr or volatile. Here are the results:
//
//  Compiled with G++ 10.1.0:
//  mixed approach	(dynamic number):   6817ms
//  mixed approach	(static number)	:   1753ms
//  pure cmath		(dynamic number):   5828ms
//  pure cmath		(static number)	:   4905ms
//  pure smath		(dynamic number): 150555ms
//  pure smath		(static number)	:   1747ms

namespace vlk
{
	/*!
	 * \brief 2-dimensional vector class
	 */
	class Vector2 final
	{
		public:
		Float x;
		Float y;

		constexpr Vector2() :
			x(0.0f),
			y(0.0f)
		{ }

		constexpr Vector2(Float xy) :
			x(xy),
			y(xy)
		{ }

		constexpr Vector2(Float x, Float y) :
			x(x),
			y(y)
		{ }

		constexpr Vector2(const Vector2& v) = default;
		constexpr Vector2(Vector2&& v) = default;
		constexpr Vector2& operator=(const Vector2& v) = default;
		constexpr Vector2& operator=(Vector2&& v) = default;
		constexpr ~Vector2() = default;

		constexpr Vector2 operator-() const { return Vector2(-this->x, -this->y); }
		constexpr bool operator==(const Vector2& rhs) const { return x == rhs.x && y == rhs.y; }
		constexpr bool operator!=(const Vector2& rhs) const { return x != rhs.x || y != rhs.y; }

		constexpr Vector2 operator+(const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
		constexpr Vector2 operator-(const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
		constexpr Vector2 operator*(const Float factor) const { return Vector2(x * factor, y * factor); }
		constexpr Vector2 operator/(const Float factor) const { return Vector2(x / factor, y / factor); }

		constexpr Vector2& operator +=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
		constexpr Vector2& operator -=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		constexpr Vector2& operator *=(const Float factor) { x *= factor; y *= factor; return *this; }
		constexpr Vector2& operator /=(const Float factor) { x /= factor; y /= factor; return *this; }

		/*!
		 * \brief Returns the length (magnitude) of this vector.
		 * \sa #SquareLength
		 */
		constexpr Float Length() const
		{
			if (std::is_constant_evaluated())
			{
				//Use constexpr variant at compile time
				return smath::sqrt(Dot(*this, *this));
			}
			else
			{
				//Use std variant at runtime
				return std::sqrt(Dot(*this, *this));
			}
		}

		/*!
		 * \brief Returns the square length of this vector. Can be faster than calculating #Length.
		 * If you're just comparing the relative length of vectors and don't need the actual magnitude, use this.
		 * \sa #Length
		 */
		constexpr Float SquareLength() const
		{
			return Dot(*this, *this);
		}

		/*!
		 * \brief Normalize this vector so it has a length of 1.0
		 */
		constexpr void Normalize()
		{
			if (std::is_constant_evaluated())
			{
				*this *= (1.0f / smath::sqrt(Dot(*this, *this)));
			}
			else
			{
				*this *= (1.0f / std::sqrt(Dot(*this, *this)));
			}
		}

		/*!
		 * \brief Returns the distance between two vectors
		 */
		static constexpr Float Distance(const Vector2& lhs, const Vector2& rhs)
		{
			return (lhs - rhs).Length();
		}

		/*!
		 * \brief Returns the dot product of two vectors
		 */
		static constexpr Float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return (rhs.x * lhs.x) + (rhs.y * lhs.y);
		}

		/*!
		 * \brief Returns a unit vector with the same direction as \c v
		 */
		static constexpr Vector2 Normalized(const Vector2& v)
		{
			if (std::is_constant_evaluated())
			{
				return v * (1.0f / smath::sqrt(Dot(v, v)));
			}
			else
			{
				return v * (1.0f / std::sqrt(Dot(v, v)));
			}
		}

		/*!
		 * \brief Linearly interpolates between two vectors
		 */
		static constexpr Vector2 Lerp(const Vector2& start, const Vector2& end, const Float t)
		{
			return Vector2(start.x + t * (end.x - start.x), start.y + t * (end.y - start.y));
		}

		/*!
		 * \brief Returns a vector perpendicular to \c v
		 */
		static constexpr Vector2 Perpendicular(const Vector2& v)
		{
			return Vector2(v.y, -v.x);
		}

		/*!
		 * \brief Unit vector facing up
		 */
		static constexpr Vector2 Up() { return Vector2(0.0f, 1.0f); }

		/*!
		 * \brief Unit vector facing down
		 */
		static constexpr Vector2 Down() { return Vector2(0.0f, -1.0f); }

		/*!
		 * \brief Unit vector facing left
		 */
		static constexpr Vector2 Left() { return Vector2(-1.0f, 0.0f); }

		/*!
		 * \brief Unit vector facing right
		 */
		static constexpr Vector2 Right() { return Vector2(1.0f, 0.0f); }

		/*!
		 * \brief vector with a x and y component of 1.0
		 */
		static constexpr Vector2 One() { return Vector2(1.0f, 1.0f); }

		/*!
		 * \brief vector with a x and y component of 0.0
		 */
		static constexpr Vector2 Zero() { return Vector2(0.0f, 0.0f); }
	};

	class Vector3 final
	{
		public:

		Float x;
		Float y;
		Float z;

		constexpr Vector3() :
			x(0.0f),
			y(0.0f),
			z(0.0f)
		{

		}

		constexpr Vector3(Float xyz) :
			x(xyz),
			y(xyz),
			z(xyz)
		{ }

		constexpr Vector3(Float x, Float y, Float z) :
			x(x),
			y(y),
			z(z)
		{ }

		constexpr Vector3(const Vector2 xy, Float z) :
			x(xy.x),
			y(xy.y),
			z(z)
		{}

		constexpr Vector3(const Vector3& v) = default;
		constexpr Vector3(Vector3&& v) = default;
		constexpr Vector3& operator=(const Vector3& v) = default;
		constexpr Vector3& operator=(Vector3&& v) = default;
		constexpr ~Vector3() = default;

		constexpr operator Vector2() { return Vector2(this->x, this->y); }

		constexpr Vector3 operator-() const { return Vector3(-this->x, -this->y, -this->z); }
		constexpr bool operator==(const Vector3& rhs) const { return x == rhs.x && y == rhs.y && z == rhs.z; }
		constexpr bool operator!=(const Vector3& rhs) const { return x != rhs.x || y != rhs.y || z != rhs.z; }

		constexpr Vector3 operator+(const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
		constexpr Vector3 operator-(const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
		constexpr Vector3 operator*(const Float factor) const { return Vector3(x * factor, y * factor, z * factor); }
		constexpr Vector3 operator/(const Float factor) const { return Vector3(x / factor, y / factor, z / factor); }

		constexpr Vector3& operator +=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
		constexpr Vector3& operator -=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
		constexpr Vector3& operator *=(const Float factor) { x *= factor; y *= factor; z *= factor; return *this; }
		constexpr Vector3& operator /=(const Float factor) { x /= factor; y /= factor; z /= factor; return *this; }

		static constexpr Vector3 Up()		{ return Vector3( 0.0f,  1.0f,  0.0f); }
		static constexpr Vector3 Down()		{ return Vector3( 0.0f, -1.0f,  0.0f); }
		static constexpr Vector3 Left()		{ return Vector3(-1.0f,  0.0f,  0.0f); }
		static constexpr Vector3 Right()	{ return Vector3( 1.0f,  0.0f,  0.0f); }
		static constexpr Vector3 Forward()	{ return Vector3( 0.0f,  0.0f, -1.0f); }
		static constexpr Vector3 Backward()	{ return Vector3( 0.0f,  0.0f,  1.0f); }
		static constexpr Vector3 One()		{ return Vector3( 1.0f,  1.0f,  1.0f); }
		static constexpr Vector3 Zero()		{ return Vector3( 0.0f,  0.0f,  0.0f); }
	
		/*!
		 * \brief Returns the length (magnitude) of this vector
		 * \sa SquareLength
		 */	
		constexpr Float Length() const
		{
			if (std::is_constant_evaluated())
			{
				return smath::sqrt(Dot(*this, *this));
			}
			else
			{
				return std::sqrt(Dot(*this, *this));
			}
		}

		/*!
		 * \brief Returns the square of the length of this vector. Can be faster than calculating #Length
		 * If you're just comparing the relative length of vectors and don't need the actual magnitude, use this.
		 * \sa Length
		 */
		constexpr Float SquareLength() const
		{
			return Dot(*this, *this);
		}

		/*!
		 * \brief Normalize this vector so it has a length of 1.0
		 */
		constexpr void Normalize()
		{
			if (std::is_constant_evaluated())
			{
				*this *= (1.0f / smath::sqrt(Dot(*this, *this)));
			}
			else
			{
				*this *= (1.0f / std::sqrt(Dot(*this, *this)));
			}
		}

		/*!
		 * \brief Returns the distance between two vectors
		 */
		static constexpr Float Distance(const Vector3& lhs, const Vector3& rhs)
		{
			return (lhs - rhs).Length();
		}

		/*!
		 * \brief Returns the dot product of two vectors
		 */
		static constexpr Float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
		}

		/*!
		 * \brief Returns a unit vector with the same direction as \c v
		 */
		static constexpr Vector3 Normalized(const Vector3& v)
		{
			if (std::is_constant_evaluated())
			{
				return v * (1.0f / smath::sqrt(Dot(v, v)));
			}
			else
			{
				return v * (1.0f / std::sqrt(Dot(v, v)));
			}
		}

		/*!
		 * \brief Linearly interpolates between two vectors
		 */
		static constexpr Vector3 Lerp(const Vector3& start, const Vector3& end, const Float t)
		{
			return Vector3(
					start.x + t * (end.x - start.x),
					start.y + t * (end.y - start.y),
					start.z + t * (end.z - start.z));
		}

		/*!
		 * \brief Returns the cross product of two vectors
		 */
		static constexpr Vector3 Cross(const Vector3& lhs, const Vector3& rhs)
		{
			return Vector3(
				lhs.y * rhs.z - lhs.z * rhs.y,
				lhs.z * rhs.x - lhs.x * rhs.z,
				lhs.x * rhs.y - lhs.y * rhs.x
			);
		}
	};
}
