#ifndef _NAIVE_ALGORITHM_H
#define _NAIVE_ALGORITHM_H

#include "internal/stl_algo.h"
#include "internal/stl_heap.h"

namespace naive {

	template<typename InputIt1, typename InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {

		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template<typename InputIt1, class InputIt2, typename BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!p(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////
	//// Checks if the first range [first1, last1) is lexicographically
	///  less than the second range [first2, last2).
	/////////////////////////////////////////////////////////////////////////////////
	template< typename InputIt1, typename InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ){

		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//// Returns an iterator pointing to the first element in the range [first, last) that is not less than
	/// (i.e. greater or equal to) value, or last if no such element is found.
	/// The range [first, last) must be partitioned with respect to the expression element < value or
	/// comp(element, value). A fully-sorted range meets this criterion.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename ForwardIt, typename T>
	ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value){

		ForwardIt it;
		typename naive::iterator_traits<ForwardIt>::difference_type count=naive::distance(first,last);
		typename naive::iterator_traits<ForwardIt>::difference_type step;

		while(count>0){

			it=first;
			step=count/2;
			naive::advance(it,step);

			if(*it<value){
				first=++it;
				count -= step+1;
			}else{
				count=step;
			}
		}

		return first;
	}

}
#endif