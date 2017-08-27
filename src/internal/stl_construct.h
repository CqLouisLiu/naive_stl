#ifndef _NAIVE_STL_CONSTRUCT_H
#define _NAIVE_STL_CONSTRUCT_H



#include <new>
#include "stl_iterator.h"
#include "../type_traits.h"
#include <iostream>
#include <string>

//According to C++ Standard, some functions related to Allocator should define in global namespace;
template <typename T1, typename T2>
inline void construct(T1 *p, T2 value)
{
	new (p) T2(value);
}

template<typename T>
inline void destroy(T* p) {
	p->~T();
}

inline void destroy(std::string* p) {
	p->std::string::~basic_string();
}


template<typename InputIterator>
inline void _destroy_aux(InputIterator first, InputIterator last,naive::_false_type) {

	for (; first < last; ++first) {
		::destroy(&(*first));
	}

}

template<typename InputIterator>
inline void _destroy_aux(InputIterator first, InputIterator last,naive::_true_type) {
	return;
}

template<typename InputIterator, typename _T>
inline void _destroy(InputIterator first, InputIterator last, _T) {
	
	typedef typename naive::has_trivial_destructor<std::is_trivially_destructible<_T>::value>::is_trivial_destructor _is_trivial_destructor;

	_destroy_aux(first, last, _is_trivial_destructor());
	
}

// Destory the range [first,lats) in C++ 17;
template<typename InputIterator>
inline void destroy(InputIterator first, InputIterator last) {
	_destroy(first, last, typename naive::iterator_traits<InputIterator>::value_type());
}

inline void destroy(char*, char*) {}

inline void destroy(wchar_t*, wchar_t*) {};

#endif