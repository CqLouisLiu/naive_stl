//
// Created by Shuai on 2017/9/12.
//

#ifndef NAIVE_STL_ALLOC_TRAITS_H
#define NAIVE_STL_ALLOC_TRAITS_H

namespace naive{

	template <typename Alloc>
	struct allocator_traits{

		typedef Alloc allocator_type;
	};

}



#endif //NAIVE_STL_STL_ALLOC_TRAITS_H
