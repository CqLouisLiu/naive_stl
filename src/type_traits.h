#ifndef _NAIVE_TYPE_TRAITS_H
#define _NAIVE_TYPE_TRAITS_H

#include "internal/stl_type_traits.h"

namespace naive{

	/*
	 * If the type T is a reference type, provides the member
	 * typedef type which is the type referred to by T. Otherwise type is T.
	 *
	 */
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



}


#endif
