//
// Created by Shuai on 2017/9/12.
//

#ifndef NAIVE_STL_MEMORY_BASE_H
#define NAIVE_STL_MEMORY_BASE_H

namespace naive{

	template <typename T>
	struct has_element_type{
	private:
		template <typename U>
		static auto check(int)-> decltype();
	};



}



#endif //NAIVE_STL_STL_MEMORY_BASE_H
