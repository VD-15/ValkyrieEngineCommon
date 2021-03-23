/*!
 * \file VMath.hpp
 * \brief Provides constexpr overloads of normal cmath functions.
 *
 *	Constexpr-compatible functions incur a significant performance penalty at
 *	runtime compared to cmath functions and use outside of purely-constexpr
 *	environments is stringly discouraged. Constexpr overloads may be accessed
 *	by wrapping each argument in a vlk::ConstexprWrapper<T> with use of
 *	vlk::ForceCXPR<T>(T).
 *
 *	Constexpr-compatible overloads attempt to emulate their cmath equivelants as
 *	closely as possible, but some are known to suffer from accuracy issues in
 *	certain scenarios and others may not work at all. These conditions, will be
 *	highlighted as a warning in the documentation of functions that suffer from
 *	them.
 */

#ifndef VLK_VMATH_HPP
#define VLK_VMATH_HPP

//TODO: use Morwenn/static_math for better precision on some functions?

#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "ValkyrieEngineCommon/ConstexprWrapper.hpp"
#include "gcem.hpp"
#include <type_traits>
#include <cmath>

namespace vlk
{
	template <typename T>
	VLK_CXX14_CONSTEXPR inline T GetPi()
	{
		return static_cast<T>(3.14159265358979323846);
	}

	template <typename T>
	VLK_CXX14_CONSTEXPR inline T GetTwoPi()
	{
		return static_cast<T>(GetPi<long double>() * 2.0);
	}

	template <typename T>
	VLK_CXX14_CONSTEXPR inline T GetHalfPi()
	{
		return static_cast<T>(GetPi<long double>() / 2.0);
	}

	VLK_CXX14_CONSTEXPR Float Pi = GetPi<Float>();
	VLK_CXX14_CONSTEXPR Float TwoPi = GetTwoPi<Float>();
	VLK_CXX14_CONSTEXPR Float HalfPi = GetHalfPi<Float>();

	/*!
	 * \brief Gets the sign of value <tt>t</tt>
	 *
	 * \returns
	 * -1 if <tt>t</tt> is lower than 0<br>
	 *  0 if <tt>t</tt> is equal to 0<br>
	 *  1 if <tt>t</tt> is greater than 0
	 */
	template <typename T>
	VLK_CXX14_CONSTEXPR T Sign(T t)
	{
		return (T(0) < t) - (t < T(0));
	}

	/*!
	 * \brief Returns the sine of an angle.
	 *
	 * \param f An angle, measured in radians.
	 *
	 * \returns The sine of f.
	 */
	template <typename F>
	inline F Sin(F f)
	{
		return std::sin(f);
	}

	/*!
	 * \copydoc vlk::Sin()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Sin(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::sin(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the cosine of an angle.
	 *
	 * \param f An angle, measured in radians.
	 *
	 * \returns The cosine of f.
	 */
	template <typename F>
	inline F Cos(F f)
	{
		return std::cos(f);
	}

	/*!
	 * \copydoc vlk::Cos()
	 *
	 * \remark Constexpr-compatible overload. No not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Cos(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::cos(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the tangent of an angle.
	 *
	 * \param f An angle, measured in radians.
	 *
	 * \returns The tangent of f.
	 */
	template <typename F>
	inline F Tan(F f)
	{
		return std::tan(f);
	}

	//TODO: this gets inaccurate with larger values
	/*!
	 * \copydoc vlk::Tan()
	 *
	 * \warning This overload gets increasingly inaccurate as values of <tt>f</tt>
	 * approach the asymtote of the tan graph.
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Tan(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::tan(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the arc sine of a value.
	 *
	 * \param f An value in the range of [-1.0, 1.0].
	 *
	 * \returns An angle, given in radians.
	 */
	template <typename F>
	inline F ASin(F f)
	{
		return std::asin(f);
	}

	/*!
	 * \copydoc ASin()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> ASin(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::asin(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the arc cosine of a value.
	 *
	 * \param f An value in the range of [-1.0, 1.0].
	 *
	 * \returns An angle, given in radians.
	 */
	template <typename F>
	inline F ACos(F f)
	{
		return std::acos(f);
	}

	/*!
	 * \copydoc vlk::ACos()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> ACos(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::acos(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the arc tangent of a value
	 * \param f An value in the range of [-1.0, 1.0]
	 * \returns An angle, given in radians
	 */
	template <typename F>
	inline F ATan(F f)
	{
		return std::atan(f);
	}

	/*!
	 * \copydoc vlk::ATan()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> ATan(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::atan(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the arc tangent of a coordinate measured from the origin.
	 *
	 * Often used to calculate the angle between a vector and the x-axis, measured from the origin.
	 *
	 * \param y the y-coordinate of the point
	 * \param x The x-coordinate of the point
	 * \returns An angle, given in radians
	 */
	template <typename F>
	inline F ATan2(F y, F x)
	{
		return std::atan2(y, x);
	}

	/*!
	 * \copydoc vlk::ATan2()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> ATan2(ConstexprWrapper<F> y, ConstexprWrapper<F> x)
	{
		return ForceCXPR(gcem::atan2(static_cast<F>(y), static_cast<F>(x)));
	}
	
	/*!
	 * \brief Returns the square root of a number.
	 *
	 * \param f a positive number
	 */
	template <typename F>
	inline F Sqrt(F f)
	{
		return std::sqrt(f);
	}

	/*!
	 * \copydoc vlk::Sqrt()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Sqrt(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::sqrt(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the value of f raised to the power of e.
	 *
	 * \param f A base floating point value
	 * \param e An exponent value
	 */
	template <typename F>
	inline F Pow(F f, F e)
	{
		return std::pow(f, e);
	}

	//TODO: This doesn't work properly with negative values.
	/*!
	 * \copydoc vlk::Pow()
	 *
	 * \warning This overload does not currently work correctly with negative values for <tt>f</tt> or <tt>e</tt>.
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Pow(ConstexprWrapper<F> f, ConstexprWrapper<F> e)
	{
		return ForceCXPR(gcem::pow(static_cast<F>(f), static_cast<F>(e)));
	}

	/*!
	 * \brief Returns the modulo of two floating point numbers.
	 *
	 * Equivelant of 'a % b' for integers.
	 */
	template <typename F>
	inline F FMod(F a, F b)
	{
		return std::fmod(a, b);
	}

	//TODO: This gets inaccurate with small values of b
	/*!
	 * \copydoc vlk::FMod()
	 *
	 * \warning This overload gets increasingly inaccurate as <tt>b</tt>
	 * approaches zero.
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> FMod(ConstexprWrapper<F> a, ConstexprWrapper<F> b)
	{
		return ForceCXPR(gcem::fmod(static_cast<F>(a), static_cast<F>(b)));
	}

	/*!
	 * \brief Returns the ceiling of a floating point number.
	 *
	 * Rounds up to the nearest whole number.
	 */
	template <typename F>
	inline F Ceil(F f)
	{
		return std::ceil(f);
	}

	/*!
	 * \copydoc vlk::Ceil()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Ceil(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::ceil(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the floor of a floating point number.
	 *
	 * Rounds down to the nearest whole number.
	 */
	template <typename F>
	inline F Floor(F f)
	{
		return std::floor(f);
	}

	/*!
	 * \copydoc vlk::Floor()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Floor(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::floor(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the truncation of a floating point number.
	 * Rounds towards zero to the nearest whole number.
	 */
	template <typename F>
	inline F Trunc(F f)
	{
		return std::trunc(f);
	}

	/*!
	 * \copydoc vlk::Trunc()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Trunc(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::trunc(static_cast<F>(f)));
	}

	/*!
	 * \brief Rounds a floating point to the nearest whole number.
	 */	
	template <typename F>
	inline F Round(F f)
	{
		return std::round(f);
	}

	/*!
	 * \copydoc vlk::Round()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Round(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::round(static_cast<F>(f)));
	}

	/*!
	 * \brief Returns the magnitude of a floating point number.
	 */
	template <typename F>
	inline F Abs(F f)
	{
		return std::abs(f);
	}

	/*!
	 * \copydoc vlk::Abs()
	 *
	 * \remark Constexpr-compatible overload. Do not use in runtime code.
	 */
	template <typename F>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<F> Abs(ConstexprWrapper<F> f)
	{
		return ForceCXPR(gcem::abs(static_cast<F>(f)));
	}
}

#endif
