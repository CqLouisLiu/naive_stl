#ifndef _NAIVE_STL_ALGO_H
#define _NAIVE_STL_ALGO_H

#include "stl_config.h"

namespace naive {

	/*
	* Copies count characters from the object pointed to by src to the object pointed to by dest.
	* If the objects are not TriviallyCopyable, the behavior of memmove is not specified and may be undefined.
	*@param dest	-	pointer to the memory location to copy to.
	*@param src	-	pointer to the memory location to copy from.
	*@param count	-	number of bytes to copy.
	*@return dest.
	*/
	inline void* memmove(void* dest, const void* src, std::size_t count) {

		//assert(dest==nullptr||src==nullptr);
		if (dest == nullptr || src == nullptr)
			return nullptr;

		char* _dest = static_cast<char*>(dest);
		const char* _src = static_cast<const char*>(src);

		// Firstly to deal with the overlap areas;
		if (_src < _dest) {
			_src = _src + count - 1;//to the end of src;
			_dest = _dest + count - 1;//to the end of dest;

			while (count--)
				*_dest-- = *_src--;

		}
		else if (_src > _dest) {//src>dest;
			while (count--)
				*_dest++ = *_src++;
		}


		return dest;


	}

	/*
	* Copies count characters from the object pointed to by src to the object pointed to by dest.
	*(1) If the objects overlap, the behavior is undefined.
	*(2) If either dest or src is a null pointer, the behavior is undefined, even if count is zero.
	*(3) If the objects are not TriviallyCopyable, the behavior of memcpy is not specified and may be undefined.
	*@param dest	-	pointer to the memory location to copy to.
	*@param src	-	pointer to the memory location to copy from.
	*@param count	-	number of bytes to copy.
	*@return dest.
	*/
	inline void* memcpy(void* dest, const void* src, std::size_t count) {
		if (dest == nullptr || src == nullptr)
			return nullptr;

		char* _dest = static_cast<char*>(dest);
		const char* _src = static_cast<const char*>(src);

		while (count--)
			*_dest++ = *_src++;

		return dest;
	}

	/*
	*Copies the elements in the range, defined by [first, last), to another range beginning at d_first.
	*Copies all elements in the range [first, last). The behavior is undefined if d_first is within the range [first, last).
	*@param first, last	-	the range of elements to copy
	*@param d_first	-	the beginning of the destination range.
	@return Output iterator to the element in the destination range, one past the last element copied.
	*/
	template<typename InputIt, typename OutputIt>
	OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
		//assert(first == last);

		while (first != last)
			*d_first++ = *first++;

		return d_first;
	}

	/*
	* Assigns the given value to the elements in the range [first, last).
	*@param first, last	-	the range of elements to modify.
	*@param value	-	the value to be assigned.
	*@return none.
	*/
	template< typename ForwardIt, typename _T >
	void fill(ForwardIt first, ForwardIt last, const _T& value) {

		while (first != last) {
			*first++ = value;
			//first++;
		}
	}


	/*
	* Assigns the given value to the elements in the range [first, last).
	*@param first, last	-	the range of elements to modify.
	*@param value	-	the value to be assigned.
	*@return none.
	*/
	template< typename OutputIt, typename Size, typename _T >
	OutputIt fill_n(OutputIt first, Size count, const _T& value) {

		for (Size i = 0; i < count; ++i)
			*first++ = value;
		return first;

	}

	//Copies the elements from the range, defined by [first, last), to another range ending at d_last;
	//The elements are copied in reverse order (the last element is copied first), but their relative order is preserved.
	template< class BidirIt1, class BidirIt2 >
	BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
		while (first != last) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}

	template<class T>
	const T& max(const T& a, const T& b) {
		return (a < b) ? b : a;
	}
}



#endif

