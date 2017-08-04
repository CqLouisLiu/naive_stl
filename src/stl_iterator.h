#ifndef _NAIVE_STL_ITERATOR_H
#define _NAIVE_STL_ITERATOR_H
#include <cstddef>
#include "stl_type_traits.h"

namespace naive
{

	// 迭代器类型标记;
	// Input&Output->Forward->Bidirectional->Random;
	struct input_iterator_tag{};

	struct output_iterator_tag{};

	struct forward_iterator_tag : public input_iterator_tag{};

	struct bidirectional_iterator_tag: public forward_iterator_tag{};

	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	//自行开发的迭代器需要继承这个类;
	template <typename _Category, typename _T, typename _Distance = ptrdiff_t, typename _Pointer = _T *, typename _Reference = _T &>
	struct iterator
	{
		typedef _Category iterator_category;			 //迭代器种类;
		typedef _T value_type;               //迭代器所指类型;
		typedef _Distance difference_type;   //迭代器距离;
		typedef _Pointer pointer;            //所指元素的指针类型;
		typedef _Reference reference;        //引用;
	};

	
	//获取迭代器相关类型的trait;
	template <typename _Iterator>
	struct iterator_traits
	{
		typedef typename _Iterator::iterator_category iterator_category;
		typedef typename _Iterator::value_type value_type;
		typedef typename _Iterator::difference_type difference_type;
		typedef typename _Iterator::pointer pointer;
		typedef typename _Iterator::reference reference;
	};

	template <typename _T>
	struct iterator_traits<_T *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _T value_type;
		typedef ptrdiff_t difference_type;
		typedef _T *pointer;
		typedef _T &reference;
	};

	template <typename _T>
	struct iterator_traits<const _T *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef _T value_type;
		typedef ptrdiff_t difference_type;
		typedef _T *pointer;
		typedef _T &reference;
	};

	template <typename _InputIterator, typename _Distance>
	inline void __advance(_InputIterator &iter, _Distance _n, naive::input_iterator_tag){
		while (_n--)
			++iter;
	}

	template <typename _BidiectionalIterator, typename _Distance>
	inline void __advance(_BidiectionalIterator &iter, _Distance _n, naive::bidirectional_iterator_tag){
		if (_n >= 0)
		{
			while (_n--)
				++iter;
		}
		else
		{
			while (_n++)
				--iter;
		}
	}

	template <typename _RandomAccessIterator, typename _Distance>
	inline void __advance(_RandomAccessIterator &iter, _Distance _n, naive::random_access_iterator_tag){
		iter += _n;
	}

	template <typename InputIterator, typename Distance>
	inline void advance(InputIterator &iter, Distance n){
		//获得迭代器类型后向下调用;
		__advance(iter, n, typename iterator_traits<InputIterator>::iterator_category());
	}


	template< typename InputIt >
	typename naive::iterator_traits<InputIt>::difference_type
		__distance(InputIt first, InputIt last,naive::input_iterator_tag) {
		
		typename naive::iterator_traits<InputIt>::difference_type _n= 0;
		
		while (first != last) {
			first++;
			_n++;
		}

		return _n;
	}



	template< typename RandomAccessIt >
	typename naive::iterator_traits<RandomAccessIt>::difference_type
		__distance(RandomAccessIt first, RandomAccessIt last,naive::random_access_iterator_tag) {
		return (first - last);
	}

	/*
	*Returns the number of hops from first to last.
	*@param first	-	iterator pointing to the first element
	*@param last	-	iterator pointing to the end of the range
	*@return The number of increments needed to go from first to last.
	*/
	template< typename InputIt >
	typename naive::iterator_traits<InputIt>::difference_type
		distance(InputIt first, InputIt last) {
		
		using category = typename naive::iterator_traits<InputIt>::iterator_category;
		return __distance(first,last,category());
	}

#ifdef _NAIVA_STL_LIST_H
	/*
	template <typename InputIt, typename Distance>
	inline void __distance(InputIt _first, InputIt _last, Distance& _n,naive::input_iterator_tag) {
		while (_first != _last) {
			_first++;
			_n++;
		}
	}

	template <typename RandomAccess, typename Distance>
	inline void __distance(RandomAccess _first, RandomAccess _last, Distance& _n,naive::random_access_iterator_tag) {
		_n += (first - last);
	}

	template <typename InputIt,typename Distance>
	inline void distance(InputIt first, InputIt last, Distance& n) {
		using category = typename naive::iterator_traits<InputIt>::iterator_category;
		 __distance(first, last, n, category());
	}*/
#endif // _NAIVA_STL_LIST_H


};

#endif