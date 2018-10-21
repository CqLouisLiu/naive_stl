#ifndef _NAIVE_LIST_H
#define _NAIVE_LIST_H

#include "../iterator.h"
#include "../memory.h"
#include "../algorithm.h"
#include <initializer_list>

namespace naive {

	//The node of List;
	template<typename _T>
	struct _List_node {

		_List_node<_T> * _prev;
		_List_node<_T> * _next;
		_T _data;

		_List_node() = default;
		_List_node(_T&& x) :_data(std::move(x)), _prev(nullptr), _next(nullptr) {}
	};

	template<typename _T, typename _Ref, typename _Ptr>
	struct _List_iterator {

		typedef _T value_type;
		typedef _Ptr pointer;
		typedef _Ref reference;
		typedef _List_iterator<_T, _T&, _T*>             iterator;
		typedef _List_iterator<_T, const _T&, const _T*> const_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef naive::bidirectional_iterator_tag iterator_category;

		typedef _List_iterator<_T, _Ref, _Ptr>             _Self;

		_List_node<_T>* _M_node;//For pointing current node;

		_List_iterator() = default;
		//conversion constructor;
		_List_iterator(_List_node<_T>* _nd) :_M_node(_nd) {}
		//Copy-constructor;
		_List_iterator(const iterator& it) :_M_node(it._M_node) {}

		//Some overload functions make this class behaviour like really iterator;
		bool operator==(const _Self& lt) const {
			return _M_node == lt._M_node;
		}

		bool operator!=(const _Self& lt) const {
			return _M_node != lt._M_node;
		}

		reference operator*() const {
			return _M_node->_data;
		}

		//pointer operator->() const {}

		//++it;
		_Self& operator++() {
			_M_node = _M_node->_next;
			return *this;
		}

		//it++;
		_Self operator++(int) {
			_Self _old = *this;
			++(*this);
			return _old;
		}

		//--it;
		_Self& operator--() {
			_M_node = _M_node->_prev;
			return *this;
		}

		//it--;
		_Self operator--(int) {
			_Self _old = *this;
			--(*this);
			return _old;
		}
	};

	template <class _T, typename _Alloc>
	class _List_base {
	private:
		static constexpr std::size_t SIZE_OF_SINGLE_NODE = 1;
	public:
		typedef _Alloc allocator_type;

		//Use rebind to transform T to _List_node;
		using _List_allocator = typename _Alloc::template rebind<_List_node<_T>>::other;

		allocator_type get_allocator() const {
			return allocator_type();
		}

	protected:
		//This idea is from sgi_stl ,this node is both empty head and tail node becasue this is a circle double-linked List;
		_List_node<_T>* _M_node;

		_List_allocator _list_node_allocator;

		_List_node<_T>* _new_node() {
			//return std::allocator_traits<_Alloc_type>::allocate(_Alloc_type, 1);
			return _list_node_allocator.allocate(SIZE_OF_SINGLE_NODE);
		}
		void _release_node(_List_node<_T>* _p) {
			_list_node_allocator.deallocate(_p, SIZE_OF_SINGLE_NODE);
		}

	public:
		// Create a mark node;
		_List_base(const allocator_type& alloc) {
			_M_node = _new_node();//get a node;
			_M_node->_next = _M_node;
			_M_node->_prev = _M_node;
		}

		~_List_base() {
			clear();
			_release_node(_M_node);
		}

		void clear();//clear all the List;

	};

	template<class _T, typename _Alloc>
	inline void _List_base<_T, _Alloc>::clear() {
		_List_node<_T>* _curr = _M_node->_next;//beginning of the List;
		while (_curr != _M_node) {
			_List_node<_T>* _temp = _curr;
			_curr = _curr->_next;

			::destroy(&(_temp->_data));
			_release_node(_temp);
		}

		_M_node->_next = _M_node;
		_M_node->_prev = _M_node;
	}

	template<typename _T, typename _Alloc = naive::allocator<_T>>
	class List :protected _List_base<_T, _Alloc> {

	private:
		typedef _List_base<_T, _Alloc> _Base;
	public:
		typedef _T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _List_iterator<_T, _T&, _T*> iterator;
		typedef _List_iterator<_T, const _T&, const _T*> const_iterator;
		typedef naive::reverse_iterator<iterator>       reverse_iterator
		typedef naive::reverse_iterator<const_iterator> const_reverse_iterator;

		typedef typename _Base::allocator_type allocator_type;
		typedef _List_node<_T> _Node;
		//using _Node_pointer = _Node*;

		allocator_type get_allocator() {
			return _Base::get_allocator();
		}


	protected:
		using _Base::_M_node;
		using _Base::_release_node;
		using _Base::_new_node;
	protected:

		_List_node<_T>* _create_node(const _T& _x) {
			_List_node<_T>* _p = _new_node();
			try {
				::construct(&(_p->_data), _x);
			}
			catch (...) {
				_Base::_release_node(_p);
				throw;
			}

			return _p;
		}

		_List_node<_T>* _create_node() {
			_List_node<_T>* _p = _new_node();
			try {
				::construct(&(_p->_data), _T());
			}
			catch (...) {
				_Base::_release_node(_p);
				throw;
			}

			return _p;
		}

		void transfer(const_iterator pos, iterator first, iterator last);

	public:
		explicit List(const allocator_type& _alloc = allocator_type()) :_Base(_alloc) {}
		explicit List(size_type n) :_Base(allocator_type()) {
			insert(begin(), n, _T());
		}
		List(std::initializer_list<_T> init, const allocator_type& _alloc = allocator_type()) :_Base(_alloc) {
			insert(begin(), init.begin(), init.begin() + init.size());
		}

		iterator begin() noexcept {
			return _M_node->_next;
		}

		const_iterator begin() const noexcept {
			return _M_node->_next;
		}


		const_iterator cbegin() const noexcept {
			return _M_node->_next;
		}

		iterator end() noexcept {
			return _M_node;
		}

		const_iterator end() const noexcept {
			return _M_node;
		}


		const_iterator cend() const noexcept {
			return _M_node;
		}

		bool empty() const {
			return _M_node->_next == _M_node;
		}

		size_type max_size() const {
			return size_type(-1);
		}

		reference front() {
			return *begin();
		}

		const_reference front() const {
			return *cbegin();
		}

		reference back() {
			return *((--end()));
		}

		size_type size() const {

			size_type n = static_cast<size_type>(naive::distance(begin(), end()));
			return n;
		}

		void clear() {
			_Base::clear();
		}

		void push_front(const _T& value) {
			insert(begin(), value);
		}

		void push_front(const _T&& value) {
			insert(begin(), std::move(value));
		}


		void push_back(const _T& value) {
			insert(end(), value);
		}

		void push_back(const _T&& value) {
			insert(end(), std::move(value));
		}
		void pop_front() {
			erase(begin());
		}

		void pop_back() {
			//erase(end());
			iterator __tmp = end();
			erase(--__tmp);
		}

		iterator insert(const_iterator position, const _T& x) {
			_Node* _temp = _create_node(x);
			_temp->_next = position._M_node;//The next pointer of new Node is pointered to position;
			_temp->_prev = position._M_node->_prev;
			(position._M_node->_prev)->_next = _temp;
			position._M_node->_prev = _temp;
			return _temp;//use conversion constructor;
		}

		void insert(iterator position, size_type count, const _T&);

		template< typename InputIt >
		void insert(iterator pos, InputIt first, InputIt last);

		iterator insert(const_iterator position, const _T&& x) {
			_Node* _temp = _create_node(std::move(x));
			_temp->_next = position._M_node;
			_temp->_prev = position._M_node->_prev;
			(position._M_node->_prev)->_next = _temp;
			position._M_node->_prev = _temp;
			return _temp;//use conversion constructor;
		}

		iterator erase(const_iterator position) {
			_Node* _next_node = position._M_node->_next;
			_Node* _prev_node = position._M_node->_prev;

			_prev_node->_next = _next_node;
			_next_node->_prev = _prev_node;

			::destroy(&(position._M_node->_data));
			_release_node(position._M_node);

			return iterator(_next_node);

		}

		void unique();

		void remove(const _T& value);

		void splice(iterator pos, List& other) {
			if (get_allocator() != other.get_allocator())
				return;

			if (!other.empty())
				transfer(pos, other.begin(), other.end());

		}

		void splice(const_iterator pos, List&& other) {
			if (get_allocator() != other.get_allocator())
				return;

			if (!other.empty())
				transfer(pos, other.begin(), other.end());
		}

		void splice(const_iterator pos, List& other, iterator it) {
			iterator _it = it;
			++_it;
			if (pos == it || pos == _it)
				return;

			transfer(pos, it, _it);
		}

		void splice(const_iterator pos, List&& other, iterator it) {
			iterator _it = it;
			++_it;
			if (pos == it || pos == _it)
				return;

			transfer(pos, it, _it);
		}

		void splice(const_iterator pos, List& other,
					iterator first, iterator last) {
			if (get_allocator() != other.get_allocator())
				return;

			if (first != last)
				transfer(pos, first, last);

		}

		void splice(const_iterator pos, List&& other,
					iterator first, iterator last) {
			if (get_allocator() != other.get_allocator())
				return;

			if (first != last)
				transfer(pos, first, last);
		}

		void swap(List& rhs){

			std::swap(_M_node,rhs._M_node);
		}
	};


	template<typename _T, typename _Alloc>
	inline void List<_T, _Alloc>::transfer(const_iterator pos, iterator first, iterator last) {
		if (first == last)
			return;
		_Node* temp = (pos._M_node)->_prev;

		((last._M_node)->_prev)->_next = pos._M_node;
		(pos._M_node)->_prev = (last._M_node)->_prev;

		((first._M_node)->_prev)->_next = last._M_node;
		(last._M_node)->_prev = (first._M_node)->_prev;


		(first._M_node)->_prev = temp;
		temp->_next = first._M_node;

	}

	template<typename _T, typename _Alloc>

	inline void List<_T, _Alloc>::insert(iterator position, size_type count, const _T & x) {
		//if(conut<0)
		while (count > 0) {
			insert(position, x);
			--count;
		}
	}

	template<typename _T, typename _Alloc>
	template<typename InputIt>
	inline void List<_T, _Alloc>::insert(iterator pos, InputIt first, InputIt last) {
		while (first != last) {
			insert(pos, *first);
			++first;
		}
	}

	template<typename _T, typename _Alloc>
	inline void naive::List<_T, _Alloc>::unique() {
		iterator it = begin();
		iterator last = end();
		if (empty())
			return;
		iterator _curr = it;
		++_curr;
		while (_curr != last) {
			if (*it == *_curr) {
				_curr = erase(_curr);
			}
			else {
				it = _curr;
				++_curr;
			}
		}
	}

	template<typename _T, typename _Alloc>
	inline void naive::List<_T, _Alloc>::remove(const _T & value) {
		iterator it = begin();
		while (it != end()) {
			if (*it == value) {
				it = erase(it);
			}
			else {
				++it;
			}
		}
	}

	template< class T, class Alloc >
	bool operator==( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		typename List<T,Alloc>::iterator _t_lhs_bg=lhs.begin();
		typename List<T,Alloc>::iterator _t_lhs_ed=lhs.end();
		typename List<T,Alloc>::iterator _t_rhs_bg=lhs.begin();
		typename List<T,Alloc>::iterator _t_rhs_ed=lhs.end();

		while((_t_lhs_bg!=_t_lhs_ed) && (_t_rhs_bg!=_t_rhs_ed) && (*_t_lhs_bg==*_t_rhs_bg)){

			++_t_lhs_bg;
			++_t_rhs_bg;
		}

		return (_t_lhs_bg==_t_lhs_ed)&&(_t_rhs_bg==_t_rhs_ed);
	}

	template< class T, class Alloc >
	bool operator!=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		return !(lhs==rhs);
	}

	template< class T, class Alloc >
	bool operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		return naive::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
	}

	template< class T, class Alloc >
	bool operator>( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		return rhs<lhs;
	}

	template< class T, class Alloc >
	bool operator<=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		return !(rhs<lhs);
	}

	template< class T, class Alloc >
	bool operator>=( const List<T,Alloc>& lhs, const List<T,Alloc>& rhs ){

		return !(lhs<rhs);
	}

	template< class T, class Alloc >
	void swap( List<T,Alloc>& lhs, List<T,Alloc>& rhs){
		lhs.swap(rhs);
	}
}

#endif
