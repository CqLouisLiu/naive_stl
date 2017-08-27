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


}
#endif