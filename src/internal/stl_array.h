
/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 *
*/



#ifndef _NAIVE_STL_ARRAY_H
#define _NAIVE_STL_ARRAY_H
#include "../memory.h"
#include "../algorithm.h"

namespace naive {

	template<typename T,std::size_t N>
	struct Array  {
		
		typedef T value_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef naive::random_access_iterator_tag iterator_category;

		T _elems[N>0?N:1];
		
		void fill(const T& u) {
			naive::fill_n(_elems,N,u);
		}

		iterator begin() noexcept {
			return iterator(std::addressof(_elems[0]));
		}

		const_iterator begin() const noexcept {
			return const_iterator(std::addressof(_elems[0]));
		}

		const_iterator cbegin() const noexcept {
			return const_iterator(std::addressof(_elems[0]));
		}

		iterator end() noexcept {
			return iterator(std::addressof(_elems[N]));
		}

		const_iterator end() const noexcept {
			return const_iterator(std::addressof(_elems[N]));
		}

		const_iterator cend() const noexcept {
			return const_iterator(std::addressof(_elems[N]));
		}
	};



}


#endif // !_NAIVA_STL_ARRAY_H
