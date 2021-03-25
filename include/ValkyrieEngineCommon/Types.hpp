#ifndef VLK_TYPES_HPP
#define VLK_TYPES_HPP

#include "Vector.hpp"

namespace vlk
{
	template <typename T = Int>
	class Area
	{
		public:
		Point<T> size;
		Point<T> location;
	};

	class Color
	{
		VectorBase<4, Float> data;
		public:
		
		VLK_CXX14_CONSTEXPR inline Float& R() { return data[0]; }
		VLK_CXX14_CONSTEXPR inline Float& G() { return data[1]; }
		VLK_CXX14_CONSTEXPR inline Float& B() { return data[2]; }
		VLK_CXX14_CONSTEXPR inline Float& A() { return data[3]; }

		VLK_CXX14_CONSTEXPR inline const Float& R() const { return data[0]; }
		VLK_CXX14_CONSTEXPR inline const Float& G() const { return data[1]; }
		VLK_CXX14_CONSTEXPR inline const Float& B() const { return data[2]; }
		VLK_CXX14_CONSTEXPR inline const Float& A() const { return data[3]; }

		VLK_CXX14_CONSTEXPR inline Color() : data({0.0f, 0.0f, 0.0f, 0.0f}) { }
		VLK_CXX14_CONSTEXPR inline Color(Float r, Float g, Float b) : data({r, g, b, 1.f}) { }
		VLK_CXX14_CONSTEXPR inline Color(Float r, Float g, Float b, Float a) : data({r, g, b, a}) { }
		VLK_CXX14_CONSTEXPR inline Color(const VectorBase<4, Float>& d) : data(d) { }

		VLK_CXX14_CONSTEXPR inline Color(const Color& v) = default;
		VLK_CXX14_CONSTEXPR inline Color(Color&& v) = default;
		VLK_CXX14_CONSTEXPR inline Color& operator=(const Color& v) = default;
		VLK_CXX14_CONSTEXPR inline Color& operator=(Color&& v) = default;
		VLK_CXX20_CONSTEXPR inline ~Color() = default;

		VLK_CXX14_CONSTEXPR inline Float& operator[](Size i) { return data[i]; }
		VLK_CXX14_CONSTEXPR inline const Float& operator[](Size i) const { return data[i]; }

		VLK_CXX14_CONSTEXPR inline Float* Data() { return data.Data(); }
		VLK_CXX14_CONSTEXPR inline const Float* Data() const { return data.Data(); }

		VLK_CXX14_CONSTEXPR inline Color operator-() const { return Color(1.f - data[0], 1.f - data[1], 1.f - data[2], data[3]); }
		VLK_CXX14_CONSTEXPR inline bool operator==(const Color& rhs) const { return data == rhs.data; }
		VLK_CXX14_CONSTEXPR inline bool operator!=(const Color& rhs) const { return data != rhs.data; }

		VLK_CXX14_CONSTEXPR inline Color operator+(const Color& rhs) const { return Color(data + rhs.data); }
		VLK_CXX14_CONSTEXPR inline Color operator-(const Color& rhs) const { return Color(data - rhs.data); }
		VLK_CXX14_CONSTEXPR inline Color operator*(const Float factor) const { return Color(data * factor); }
		VLK_CXX14_CONSTEXPR inline Color operator/(const Float factor) const { return Color(data / factor); }

		VLK_CXX14_CONSTEXPR inline Color& operator +=(const Color& rhs) { data += rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Color& operator -=(const Color& rhs) { data -= rhs.data; return *this; }
		VLK_CXX14_CONSTEXPR inline Color& operator *=(const Float factor) { data *= factor; return *this; }
		VLK_CXX14_CONSTEXPR inline Color& operator /=(const Float factor) { data /= factor; return *this; }

		VLK_CXX14_CONSTEXPR inline Color Mix(const Color& lhs, const Color& rhs, Float t)
		{
			return Color(
				lhs[0] + t * (rhs[0] - lhs[0]),
				lhs[1] + t * (rhs[1] - lhs[1]),
				lhs[2] + t * (rhs[2] - lhs[2]),
				lhs[3] + t * (rhs[3] - lhs[3])
			);
		}

		//TODO: To/from HSV & HSL
	};
}

#endif
