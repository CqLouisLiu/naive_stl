#ifndef _NAIVE_TYPE_TRAITS_H
#define _NAIVE_TYPE_TRAITS_H

#include "internal/stl_type_traits.h"

namespace naive{

	/////////////////////////////////////////////////////////////////////////
	// If the type T is a reference type, provides the member
	// typedef type which is the type referred to by T. Otherwise type is T.
	//////////////////////////////////////////////////////////////////////////
	template <typename T>
	struct remove_reference{

		typedef T type;
	};

	template <typename T>
	struct remove_reference<T&>{

		typedef T type;
	};

	template <typename T>
	struct remove_reference<T&&>{
		typedef T type;
	};

	///////////////////////////////////////////
	//// removes the topmost volatile
	//////////////////////////////////////////
	template<typename T>
	struct remove_volatile{

		typedef T type;
	};

	template<typename T>
	struct remove_volatile<volatile T>{
		typedef T type;
	};

	////////////////////////////////////////////
	//// removes the topmost const
	////////////////////////////////////////////
	template<typename T>
	struct remove_const{

		typedef T type;
	};

	template<typename T>
	struct remove_const<const T>{

		typedef T type;
	};

	////////////////////////////////////////////////////////////////////////////
	//// removes the topmost const, the topmost volatile, or both, if present.
	///////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct remove_cv{

		typedef typename naive::remove_volatile<typename remove_const<T>::type>::type type;
	};

	/////////////////////////////////////////////////////////////////////////////
	//// naive::integral_constant wraps a static constant of specified type.
	//// It is the base class for the C++ type traits.
	//// Checks whether T is an integral type. Provides the member constant value which is equal to true,
	/// if T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long, or any
	/// implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants.
	/// Otherwise, value is equal to false.
	/////////////////////////////////////////////////////////////////////////////
	template< typename T, T _value >
	struct integral_constant{

		static constexpr T value=_value;

		//using value_type=T;
		//using type =integral_constant<T,_value>;

		typedef T value_type;
		typedef integral_constant<T,_value> type;

		constexpr operator value_type() const noexcept {
			return value;
		}

		constexpr value_type operator()()const noexcept {
			return value;
		}
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T>
	struct _Is_integral_type : public false_type{};

	template<>
	struct _Is_integral_type<bool>: public true_type{};

	template<>
	struct _Is_integral_type<char>: public true_type{};

	template<>
	struct _Is_integral_type<unsigned char>: public true_type{};

	template<>
	struct _Is_integral_type<unsigned short>: public true_type{};

	template<>
	struct _Is_integral_type<unsigned int>: public true_type{};

	template<>
	struct _Is_integral_type<unsigned long>: public true_type{};

	template<>
	struct _Is_integral_type<unsigned long long>: public true_type{};

	template<>
	struct _Is_integral_type<signed char>: public true_type{};

	template<>
	struct _Is_integral_type<signed short>: public true_type{};

	template<>
	struct _Is_integral_type<signed int>: public true_type{};

	template<>
	struct _Is_integral_type<signed long>: public true_type{};

	template<>
	struct _Is_integral_type<signed long long>: public true_type{};

	template<>
	struct _Is_integral_type<char16_t >: public true_type{};

	template<>
	struct _Is_integral_type<char32_t >: public true_type{};

	template<>
	struct _Is_integral_type<wchar_t>: public true_type{};

	template<typename T>
	struct is_integral:public _Is_integral_type<typename naive::remove_cv<T>::type>{};

	///////////////////////////////////////////////////////////////////////////////////
	//// If B is true, std::enable_if has a public member typedef type, equal to T;
	/// otherwise, there is no member typedef.
	///////////////////////////////////////////////////////////////////////////////////
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};


}


#endif
