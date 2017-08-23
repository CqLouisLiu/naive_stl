#ifndef _NAIVE_STL_UNINITIALIZED_H
#define _NAIVE_STL_UNINITIALIZED_H
#include "stl_iterator.h"
#include "stl_construct.h"
#include "stl_algo.h"
#include "stl_type_traits.h"

namespace naive {

	template<typename InputIt, typename ForwardIt>
	inline ForwardIt _uninitialized_copy_aux(InputIt __first, InputIt __last, ForwardIt __d_first,naive::_true_type) {

		return naive::copy(__first, __last, __d_first);
	}

	template<typename InputIt, typename ForwardIt>
	inline ForwardIt _uninitialized_copy_aux(InputIt __first, InputIt __last, ForwardIt __d_first,naive::_false_type) {

		//commit or rollback rule;
		ForwardIt __current = __d_first;

		try {
			for (; __first != __last; ++__first, ++__current)
				::construct(&(*__current), *__first);
			return __current;//Iterator to the element past the last element copied, but don't change __d_first;

		}
		catch (...) {

			::destroy(__d_first, __current);
			throw;
		}

	}

	template<typename InputIt, typename ForwardIt, typename _T>
	ForwardIt _uninitialized_copy(InputIt _first, InputIt _last, ForwardIt _d_first, _T) {

		typedef typename naive::is_pod_type<std::is_pod<_T>::value>::is_pod _Is_pod;
		return _uninitialized_copy_aux(_first, _last, _d_first, _Is_pod());

	}

	template<typename InputIt, typename ForwardIt>
	ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first) {

		return _uninitialized_copy(first, last, d_first, typename naive::iterator_traits<ForwardIt>::value_type());
	}

	inline char* uninitialized_copy(const char* __first, const char* __last, char* __d_first) {
		naive::memmove(__d_first, __first, __last - __first);
		return __d_first + (__last - __first);
	}

	inline wchar_t* uninitialized_copy(const wchar_t* __first, const wchar_t* __last, wchar_t* __d_first) {
		naive::memmove(__d_first, __first, sizeof(wchar_t)*(__last - __first));
		return __d_first + (__last - __first);
	}


	template<typename ForwardIt, typename T1>
	void _uninitialized_fill_aux(ForwardIt __first, ForwardIt __last, const T1& __value,naive::_false_type) {

		//commit of rollback;
		ForwardIt _current = __first;

		try {
			for (; _current != __last; ++_current) {
				::construct(&(*_current), __value);
			}

		}
		catch (...) {
			::destroy(__first, _current);
			throw;
		}

	}

	template<typename ForwardIt, typename T1>
	void _uninitialized_fill_aux(ForwardIt __first, ForwardIt __last, const T1& __value,naive::_true_type) {

		naive::fill(__first, __last, __value);
	}

	template<typename ForwardIt, typename T1, typename T2>
	void _uninitialized_fill(ForwardIt _first, ForwardIt _last, const T1& _value, T2) {

		typedef typename naive::is_pod_type<std::is_pod<T2>::value>::is_pod _Is_pod;
		_uninitialized_fill_aux(_first, _last, _value, _Is_pod());

	}

	template<typename ForwardIt, typename _T>
	void uninitialized_fill(ForwardIt first, ForwardIt last, const _T& value) {
		_uninitialized_fill(first, last, value, typename naive::iterator_traits<ForwardIt>::value_type());
	}

	template< typename ForwardIt, typename Size, typename _T>
	ForwardIt _uninitialized_fill_n_aux(ForwardIt __first, Size __count, const _T& __value, naive::_true_type) {

		return naive::fill_n(__first, __count, __value);
	}

	template< typename ForwardIt, typename Size, typename _T>
	ForwardIt _uninitialized_fill_n_aux(ForwardIt __first, Size __count, const _T& __value, naive::_false_type) {

		ForwardIt _current = __first;

		try {
			for (; __count > 0; --__count, ++_current) {
				construct(&(*_current), __value);
			}
			return _current;
		}
		catch (...) {

			for (; __first != _current; ++__first)
				::destroy(&(*__first));
			throw;
		}

	}

	template< typename ForwardIt, typename Size, typename T1, typename T2 >
	ForwardIt _uninitialized_fill_n(ForwardIt _first, Size _count, const T1& _value, T2) {

		typedef typename naive::is_pod_type<std::is_pod<T2>::value>::is_pod _Is_pod;
		return _uninitialized_fill_n_aux(_first, _count, _value, _Is_pod());

	}

	template< typename ForwardIt, typename Size, typename _T >
	ForwardIt uninitialized_fill_n(ForwardIt first, Size count, const _T& value) {
		return _uninitialized_fill_n(first, count, value, typename naive::iterator_traits<ForwardIt>::value_type());
	}


}

#endif