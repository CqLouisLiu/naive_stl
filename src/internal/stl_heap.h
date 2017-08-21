
/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 *
*/

#ifndef NAIVE_STL_STL_HEAP_H
#define NAIVE_STL_STL_HEAP_H

#include "../iterator.h"
/*
 * A heap is a kind of complete binary tree.
 *
 */


namespace naive{


	template <typename _RandomIt, typename _Distance, typename _T>
	inline void _push_heap(_RandomIt _first, _RandomIt _last,_Distance*, _T*){


	}

	template <typename _RandomIt, typename _Distance, typename _T>
	inline void _push_heap_aux(_RandomIt _first, _RandomIt _last,_Distance*, _T*){


	}


	template<typename RandomIt >
	void push_heap( RandomIt first, RandomIt last ){

		_push_heap_aux(first,last,naive::Distance_type(first),naive::Value_type(first));
	}

	template<typename RandomIt, typename Compare >
	void push_heap( RandomIt first, RandomIt last, Compare comp ){

	}


}






#endif //NAIVE_STL_STL_HEAP_H
