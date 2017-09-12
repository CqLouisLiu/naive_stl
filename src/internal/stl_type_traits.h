#ifndef _NAIVE_STL_TYPE_TRAITS_H
#define _NAIVE_STL_TYPE_TRAITS_H
#include <type_traits>

namespace naive {

	struct _false_type_tag {};
	struct _true_type_tag {};



	template<bool T>
	struct is_pod_type;


	template<>
	struct is_pod_type<false> :public _false_type_tag {
		typedef _false_type_tag is_pod;
	};

	template<>
	struct is_pod_type<true> :public _true_type_tag {
		typedef _true_type_tag is_pod;
	};


	template<bool T>
	struct has_trivial_destructor;

	template<>
	struct has_trivial_destructor<false> :public _false_type_tag {
		typedef _false_type_tag is_trivial_destructor;
	};

	template<>
	struct has_trivial_destructor<true> :public _true_type_tag {
		typedef _true_type_tag is_trivial_destructor;
	};

}

#endif
