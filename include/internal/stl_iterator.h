#ifndef _NAIVE_STL_ITERATOR_H
#define _NAIVE_STL_ITERATOR_H

#include "stl_type_traits.h"

namespace naive
{

	// Input&Output->Forward->Bidirectional->Random;
	struct input_iterator_tag{};

	struct output_iterator_tag{};

	struct forward_iterator_tag : public input_iterator_tag{};

	struct bidirectional_iterator_tag: public forward_iterator_tag{};

	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template <typename _Category, typename _T, typename _Distance = ptrdiff_t, typename _Pointer = _T *, typename _Reference = _T &>
	struct iterator
	{
		typedef _Category iterator_category;
		typedef _T value_type;
		typedef _Distance difference_type;
		typedef _Pointer pointer;
		typedef _Reference reference;
	};


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
		typedef naive::random_access_iterator_tag iterator_category;
		typedef _T value_type;
		typedef ptrdiff_t difference_type;
		typedef _T *pointer;
		typedef _T &reference;
	};

	template <typename _T>
	struct iterator_traits<const _T *>
	{
		typedef naive::random_access_iterator_tag iterator_category;
		typedef _T value_type;
		typedef ptrdiff_t difference_type;
		typedef _T *pointer;
		typedef _T &reference;
	};


	template<typename It>
	inline typename iterator_traits<It>::iterator_category Iterator_category(const It& _it) {

		typedef typename iterator_traits<It>::iterator_category _Category;
		return _Category();
	}

	// return as a pointer can avoid copy a object;
	template<typename It>
	inline typename iterator_traits<It>::value_type* Value_type(const It& _it) {

		//typedef typename iterator_traits<It>::value_type _Value_type;
		return static_cast<typename iterator_traits<It>::value_type*>(0);
	}

	template<typename It>
	inline typename iterator_traits<It>::difference_type* Distance_type(const It &_it) {
		return static_cast<typename iterator_traits<It>::difference_type*>(0);
	}

	template <typename _InputIterator, typename _Distance>
	inline void _advance(_InputIterator &iter, _Distance _n, naive::input_iterator_tag){
		while (_n--)
			++iter;
	}

	template <typename _BidiectionalIterator, typename _Distance>
	inline void _advance(_BidiectionalIterator &iter, _Distance _n, naive::bidirectional_iterator_tag){
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
	inline void _advance(_RandomAccessIterator &iter, _Distance _n, naive::random_access_iterator_tag){
		iter += _n;
	}

	template <typename InputIterator, typename Distance>
	inline void advance(InputIterator &iter, Distance n){

		_advance(iter, n, typename iterator_traits<InputIterator>::iterator_category());
	}


	template <typename _InputIt, typename _Distance>
	inline void _distance(_InputIt _first, _InputIt _last,
						   _Distance& _n, input_iterator_tag) {

		while (_first != _last) {
			++_first; ++_n;
		}
	}

	template <typename _RandomAccessIt, typename _Distance>
	inline void _distance(_RandomAccessIt _first,
						  _RandomAccessIt _last,
						   _Distance& _n, random_access_iterator_tag) {
		_n += _last - _first;
	}

	template <typename InputIt, typename _Distance>
	inline void distance(InputIt first,
						 InputIt last, _Distance& n) {

		typedef typename naive::iterator_traits<InputIt>::iterator_category _iterator_category;
		_distance(first, last, n, _iterator_category());
	}


	template< typename InputIt >
	typename naive::iterator_traits<InputIt>::difference_type
		_distance(InputIt first, InputIt last,naive::input_iterator_tag) {
		
		typename naive::iterator_traits<InputIt>::difference_type _t_size= 0;
		
		while (first != last) {
			first++;
			++_t_size;
		}

		return _t_size;
	}



	template< typename RandomAccessIt >
	typename naive::iterator_traits<RandomAccessIt>::difference_type
		_distance(RandomAccessIt first, RandomAccessIt last,naive::random_access_iterator_tag) {
		return (last - first);
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
		
		typedef typename naive::iterator_traits<InputIt>::iterator_category _iterator_category;
		return _distance(first,last,_iterator_category());
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