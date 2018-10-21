//
// Created by Shuai on 2017/9/12.
//

#ifndef NAIVE_STL_POINT_TRAITS_H
#define NAIVE_STL_POINT_TRAITS_H

namespace naive{

	template<typename P>
	struct pointer_traits {

		typedef P pointer;
	};

	template<typename P>
	struct pointer_traits<P*> {

		typedef P* pointer;
		typedef P element_type;
		typedef ptrdiff_t difference_type;

		template<typename U>
		using rebind = U*;

		//Constructs a dereferenceable pointer or pointer-like object ("fancy pointer") to its argument;
		static pointer pointer_to(element_type& x) noexcept {
			return std::addressof(x);
		}
	};
}
#endif //NAIVE_STL_POINT_TRAITS_H
