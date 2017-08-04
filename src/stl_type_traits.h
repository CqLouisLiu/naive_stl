#ifndef _NAIVE_STL_TYPE_TRAITS_H
#define _NAIVE_STL_TYPE_TRAITS_H
#include <type_traits>

namespace naive {

	struct false_type {};
	struct true_type {};

	template<bool T>
	struct is_integral_type;

	template<>
	struct is_integral_type<false> :public false_type {
		typedef false_type is_integral;
	};

	template<>
	struct is_integral_type<true> :public true_type {
		typedef true_type is_integral;
	};


	template<bool T>
	struct is_pod_type;


	template<>
	struct is_pod_type<false> :public false_type {
		typedef false_type is_pod;
	};

	template<>
	struct is_pod_type<true> :public true_type {
		typedef true_type is_pod;
	};


	template<bool T>
	struct has_trivial_destructor;

	template<>
	struct has_trivial_destructor<false> :public false_type {
		typedef false_type is_trivial_destructor;
	};

	template<>
	struct has_trivial_destructor<true> :public true_type {
		typedef true_type is_trivial_destructor;
	};


	template<bool B, class T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

}

#endif
