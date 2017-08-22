
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
	void _push_heap(_RandomIt _first,_Distance _holeIndex, _Distance _topIndex, _T _value){

		_Distance _t_parent=(_holeIndex-1)/2;//get the parent;

		// if the value is smaller than its parent, the processing is done;
		// then make the hole percolate up;
		while((_holeIndex>_topIndex)&& (*(_first+_t_parent)<_value)){//percolate up util satisfy the order-required;

			*(_first+_holeIndex)=*(_first+_t_parent);
			_holeIndex=_t_parent;
			_t_parent=(_holeIndex-1)/2;
		}

		*(_first+_holeIndex)=_value;
	}

	template <typename _RandomIt, typename _Distance, typename _T>
	inline void _push_heap_aux(_RandomIt _first, _RandomIt _last,_Distance*, _T*){

		// 1.if difference_type is ptrdiff_t, then _Distance is deduced as int;
		_push_heap(_first,_Distance((_last-_first)-1),_Distance(0),_T(*(_last-1)));
	}


	template<typename RandomIt >
	void push_heap( RandomIt first, RandomIt last ){

		_push_heap_aux(first,last,naive::Distance_type(first),naive::Value_type(first));
	}

	/*
	template<typename RandomIt, typename Compare >
	void push_heap( RandomIt first, RandomIt last, Compare comp ){

	}*/


	template <typename _RandomIt, typename _Distance, typename _T>
	void _adjust_heap(_RandomIt _first, _Distance _holeIndex, _Distance _len, _T _value){


		// at the first time, the holeIndex=0 stand for root position;
		// the first iterator point to the start position of basic container;
		_Distance _topIndex=_holeIndex;

		_Distance _rightChild = 2 * _holeIndex + 2;//get the right child of root;

		while(_rightChild<_len){

			// if the right child is smaller than left child, then secondChild is change to the left child;
			if(*(_first+_rightChild)<*(_first+(_rightChild-1))){

				_rightChild--;
			}

			// let the bigger value between right and left child to the hole position;
			*(_first+_holeIndex)=*(_first+_rightChild);

			_holeIndex=_rightChild;

			_rightChild=2*_rightChild+2;// percolate down the hole;
		}

		// at now, deal with the last elements in basic container;
		if(_rightChild==_len){

			*(_first+_holeIndex)=*(_first+(_rightChild-1));
			_holeIndex=_rightChild-1;
		}

		_push_heap(_first,_holeIndex,_topIndex,_value);

	}


	template <typename _RandomIt, typename _T, typename _Distance>
	inline void _pop_heap(_RandomIt _first, _RandomIt _last, _RandomIt _result, _T _value, _Distance*){

		*_result=*_first;
		_adjust_heap(_first,_Distance(0),_Distance(_last-_first),_value);
	}

	template <typename _RandomIt,typename _T>
	inline void _pop_heap_aux(_RandomIt _first,_RandomIt _last,_T*){

		_pop_heap(_first,_last-1,_last-1,_T(*(_last-1)),naive::Distance_type(_first));

	}

	template <typename RandomIt>
	inline void pop_heap(RandomIt first, RandomIt last){

		_pop_heap_aux(first,last,naive::Value_type(first));
	}



	template <typename RandomIt>
	void sort_heap(RandomIt first, RandomIt last){

		while ((last-first)>1){
			pop_heap(first,last--);
		}
	}

	template <typename RandomIt, typename _T, typename _Distance>
	void _make_heap(RandomIt _first,RandomIt _last, _T*, _Distance*) {

		// just 0 or 1 element;
		if (_last - _first < 2)
			return;

		_Distance _len = _last - _first;

		_Distance _holeIndex = (_len - 2)/2;//get position of its parent;

		while (true) {

			_adjust_heap(_first, _holeIndex, _len, _T(*(_first + _holeIndex)));

			if (_holeIndex == 0)
				return;

			_holeIndex--;
		}
	}


	/*
	 * Input a range [first,last), this function convert it to a heap;
	 */
	template <typename RandomIt>
	inline void make_heap(RandomIt first, RandomIt last) {



		_make_heap(first, last, naive::Value_type(first), naive::Distance_type(first));
	}




}






#endif //NAIVE_STL_STL_HEAP_H
