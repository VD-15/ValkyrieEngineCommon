/*!
 * \file ConstexprWrapper.hpp
 * \brief Provides a wrapper type to enable <tt>constexpr</tt> overloading.
 */

//TODO: ConstexprWrapper could be made either safer or completely obsolete in C++20 with proper use of consteval?

#ifndef VLK_CONSTEXPR_WRAPPER_HPP
#define VLK_CONSTEXPR_WRAPPER_HPP

#include "ValkyrieEngine/ValkyrieDefs.hpp"
#include "ValkyrieEngine/Util.hpp"

namespace vlk
{
	template <typename T>
	class ConstexprWrapper;

	template <typename T>
	class ConstexprWrapper
	{
		public:
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T>() = delete;
		VLK_CXX14_CONSTEXPR inline explicit ConstexprWrapper<T>(const T& t) : value(t)
		{
			VLK_STATIC_ASSERT_MSG(std::is_copy_constructible<T>::value, "T must be copy constructible for ConstexprWrapper to work.");

			VLK_STATIC_ASSERT_MSG((!IsSpecialization<T, ConstexprWrapper>::value), "Nested constexpr wrapping occuring. Remove template specialization of ConstexprWrapper<ConstexprWrapper<T>>.");
		}

		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T>(const ConstexprWrapper<T>&) = default;
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T>(ConstexprWrapper<T>&&) = default;
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T>& operator=(const ConstexprWrapper<T>&) = default;
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T>& operator=(ConstexprWrapper<T>&&) = default;

		const typename std::remove_reference<T>::type value;

		VLK_CXX14_CONSTEXPR inline operator const T&() const { return value; }
		VLK_CXX14_CONSTEXPR inline const T* operator->() const { return &value; }
		VLK_CXX14_CONSTEXPR inline const T& operator*() const { return value; }
	};

	template <>
	class ConstexprWrapper<void> 
	{
		public:
		VLK_CXX14_CONSTEXPR inline ConstexprWrapper<void>() = default;	
	};


	template <typename T>
	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<T> ForceCXPR(T t)
	{
		return ConstexprWrapper<T>(t);
	}

	VLK_CXX14_CONSTEXPR inline ConstexprWrapper<void> ForceCXPR()
	{
		return ConstexprWrapper<void>();
	}
}

#endif
