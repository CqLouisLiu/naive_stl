#ifndef _NAIVE_ITERATOR_H
#define _NAIVE_ITERATOR_H

#include "internal/stl_iterator.h"

namespace naive{


/*
 * struct reverse_iterator is an iterator adaptor that reverses the direction of a given iterator. In other words, when provided
 * with a bidirectional iterator, std::reverse_iterator produces a new iterator that moves from the end to the beginning
 * of the sequence defined by the underlying bidirectional iterator.The key relationship in reverse_iterator and the given
 * iterator is &*(reverse_iterator(i))==&(*(i-1)). In other words, because the position begin()-1 is a illegal position in the given
 * iterator, then rbegin() in reverse_iterator equal to the end() in the given iterator actually, but point to the last element logically, so
 * that make the reverse_iterator point to the range with open-and-close range;
 *
 */
	template<class Iterator>
	class reverse_iterator : public naive::iterator<
			typename naive::iterator_traits<Iterator>::iterator_category,
			typename naive::iterator_traits<Iterator>::value_type,
			typename naive::iterator_traits<Iterator>::difference_type,
			typename naive::iterator_traits<Iterator>::pointer,
			typename naive::iterator_traits<Iterator>::reference> {

	public:

		typedef typename naive::iterator_traits<Iterator>::value_type value_type;
		typedef typename naive::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename naive::iterator_traits<Iterator>::pointer pointer;
		typedef typename naive::iterator_traits<Iterator>::reference reference;
		typedef typename naive::iterator_traits<Iterator>::iterator_category iterator_category;

		typedef Iterator iterator_type;

	protected:
		iterator_type _M_iterator;

	public:
		reverse_iterator() : _M_iterator() {}

		explicit reverse_iterator(iterator_type _it) : _M_iterator(_it) {}

		reverse_iterator(const reverse_iterator &_rit) : _M_iterator(_rit._M_iterator) {}

		template<typename U>
		reverse_iterator(const reverse_iterator<U> &other):_M_iterator(other.base()) {}

		template<typename U>
		reverse_iterator<Iterator> &operator=(const reverse_iterator<U> &other) {

			_M_iterator = other.base();
			return *this;
		}


	public:
		iterator_type base() const {
			return _M_iterator;
		}

		// Returns a reference or pointer to the element previous to current.
		// Because of relationship &*(reverse_iterator(i))==&(*(i-1))
		reference operator*() const {

			iterator_type _temp(_M_iterator);
			return *--_temp;
		}

		pointer operator->() const {
			return &(operator*());
		}

		reverse_iterator &operator++() {
			--_M_iterator;
			return *this;
		}

		reverse_iterator operator++(int) {

			reverse_iterator _temp(*this);
			--_M_iterator;
			return _temp;
		}

		reverse_iterator &operator--() {
			++_M_iterator;
			return *this;
		}

		reverse_iterator operator--(int) {

			reverse_iterator _temp(*this);
			++_M_iterator;
			return _temp;
		}

		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(_M_iterator - n);
		}

		reverse_iterator &operator+=(difference_type n) {
			_M_iterator -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(_M_iterator + n);
		}

		reverse_iterator &operator-=(difference_type n) {
			_M_iterator += n;
			return *this;
		}

		reference operator[](difference_type n) const {
			return *(*this + n);
		}

	};

	template <typename Iterator1, typename Iterator2>
	inline bool operator==(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() == it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool operator<(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() > it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool operator!=(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() != it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool operator>(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() < it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool operator<=(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() >= it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline bool operator>=(const reverse_iterator<Iterator1>& it1, const reverse_iterator<Iterator2>& it2) {
		return it1.base() <= it2.base();
	}

	template <typename Iterator1, typename Iterator2>
	inline typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& it1,
																		   const reverse_iterator<Iterator2>& it2) {
		return it2.base() - it1.base();
	}

	template <typename Iterator>
	inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
												const reverse_iterator<Iterator>& it) {
		return reverse_iterator<Iterator>(it.base() - n);
	}





}

#endif
