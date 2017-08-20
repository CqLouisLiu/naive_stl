//
// Created by Shuai on 2017/8/16.
//

#ifndef NAIVE_STL_RB_TREE_H
#define NAIVE_STL_RB_TREE_H


/*
* RB-Tree(Red-black tree)
* Different from Binary tree, Red-black tree keep the average
* height in range [logN,2*long(N+1)] always;
*
* 1: Every node is colored either red or black;
* 2: The root of RB-Tree is black;
* 3: The parent and children node can't be red meanwhile;
* 4: Every path from a node to a null pointer must contain the same
*    number of black nodes.
* 5: When insert node into RB-Tree, the new node must be red and only if its
*    parent is black, the insert operation is done. Otherwise, adjust the RB-Tree;
*/
#include "../iterator.h"
#include <cstddef>
#include "../memory.h"
#include "../functional.h"

namespace naive {

	typedef bool _Node_color_type;
	const _Node_color_type _M_color_red = false;//read is false and black is true;
	const _Node_color_type _M_color_black = true;

	template <typename _T>
	struct _RBTree_node {

		typedef _RBTree_node<_T> _Self_type;
		typedef _Self_type* _Link_type;

		_Node_color_type _M_color;
		_Link_type _M_parent;
		_Link_type _M_left;
		_Link_type _M_right;
		_T _M_node_value;

		_RBTree_node() :_M_color(), _M_parent(nullptr), _M_left(nullptr), _M_right(nullptr),
						_M_node_value(nullptr) {}

		_RBTree_node(const _RBTree_node& _node) :_M_color(_node._M_color), _M_parent(_node._M_parent), _M_left(_node._M_left), _M_right(_node._M_right),
												 _M_node_value(_node._M_node_value) {}

		_RBTree_node(const _RBTree_node&& _node) noexcept : _M_color(_node._M_color), _M_parent(_node._M_parent), _M_left(_node._M_left),
															_M_right(_node._M_right), _M_node_value(std::move(_node._M_node_value)) {
			_M_left = _M_right = _M_parent = nullptr;
		}

		_RBTree_node& operator=(const _RBTree_node& _node) {
			_M_color = _node._M_color;
			_M_parent = _node._M_parent;
			_M_left = _node._M_left;
			_M_right = _node._M_right;
			_M_node_value = _node._M_node_value;
		}

		_RBTree_node& operator=(_RBTree_node&& _node) noexcept {
			_M_color = _node._M_color;
			_M_parent = _node._M_parent;
			_M_left = _node._M_left;
			_M_right = _node._M_right;
			_M_node_value = std::move(_node._M_node_value);

			_M_left = _M_right = _M_parent = nullptr;
		}

		~_RBTree_node() = default;

	};

	template <typename _Value, typename _Ref, typename _Ptr>
	class _RBTree_iterator {

	public:
		typedef _Value value_type;
		typedef _Ref reference;
		typedef std::size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef _Ptr pointer;
		typedef naive::bidirectional_iterator_tag iterator_category;
		typedef _RBTree_iterator<_Value, _Value&, _Value*> iterator;
		typedef _RBTree_iterator<_Value, const _Value&, const _Value*> const_iterator;
		typedef _RBTree_iterator<_Value, _Ref, _Ptr> _Self;
		typedef typename _RBTree_node<value_type>::_Link_type _Link_type;

		_RBTree_iterator() = default;

		explicit _RBTree_iterator(_Link_type _lt) :_M_node(_lt) {}

		explicit _RBTree_iterator(const iterator& _it) :_M_node(_M_node = _it._M_node) {}


		reference operator*() const {
			return static_cast<_Link_type>(_M_node)->_M_node_value;
		}

		pointer operator->() const {
			return &(operator*());
		}

		/* expression (++it);
		* The Red-black tree is a sorted tree, so the first elements is the most-left node;
		* On the other hand the last node is the most-right node;
		* The sequence is defined according to right-root-left recursively;
		*/
		_Self& operator++() {

			/*
			* The current node have a right child node means that the node just bigger than
			* the current node in red-black tree is the most-left node in its right child tree;
			*/
			if (_M_node->_M_right != nullptr) {

				_M_node = _M_node->_M_right;//get the right child tree;
				while (_M_node->_M_left != nullptr) {
					_M_node = _M_node->_M_left;//go to the left-most node;
				}
			}
			else {

				/* If the current node not have a right child tree, according to properties of
				* red-black tree, we need go back to the first node that is not a right child,
				* then it is the node just bigger than the current node;
				*/
				_Link_type _t_parent = _M_node->_M_parent;

				while (_M_node == _t_parent->_M_right) {
					_M_node = _t_parent;
					_t_parent = _t_parent->_M_parent;
				}

				// A special case that the iterator point to the root;
				if (_M_node->_M_right != _t_parent) {
					_M_node = _t_parent;
				}
			}

			return *this;
		}

		// expression (it++);
		_Self operator++(int) {
			_Self _temp = *this;
			++(*this);
			return _temp;
		}

		// expression (--it)
		_Self& operator--() {

		}

		_Self operator--(int);

		//bool operator==(const _RBTree_iterator& l_rf,const_iterator& r_rf);

	protected:
		_Link_type _M_node;// Point to _RBTree_node_base;
	};

	//template <typename _T>
	template<typename _T, typename _Alloc>
	class _RBTree_alloc_base {

	public:
		//typedef _RBTree_node<_T>* _ptr_tree_node;
		using allocator_type = typename _Alloc::template rebind<_RBTree_node<_T>>::other;
		//std::allocator_traits<_Alloc>::rebind_alloc ;

		allocator_type get_allocator() const {
			return _M_node_allocator;
		}

		explicit _RBTree_alloc_base() :
				_M_node_allocator(get_allocator()), _M_header(nullptr) {}

		explicit _RBTree_alloc_base(const allocator_type& _alloc) :
				_M_node_allocator(_alloc), _M_header(nullptr) {}

	protected:
		allocator_type _M_node_allocator;
		_RBTree_node<_T>* _M_header;

		_RBTree_node<_T>* _M_node_allocate() {
			return _M_node_allocator.allocate(_NUM_ALLOC_NODE);
		}

		void _M_deallocate_node(_RBTree_node<_T>* _p) {
			_M_node_allocator.deallocate(_p, _NUM_ALLOC_NODE);
		}

	private:
		const std::size_t _NUM_ALLOC_NODE = 1;
	};

	template<typename _T, typename _Alloc>
	class _RBTree_base :public _RBTree_alloc_base<_T, _Alloc> {

	public:
		typedef _RBTree_alloc_base<_T, _Alloc> _Base;
		typedef typename _Base::allocator_type allocator_type;

		explicit _RBTree_base(const allocator_type& _alloc = allocator_type()) :_Base(_alloc) {
			_M_header = _M_node_allocate();
		}

		~_RBTree_base() {
			_M_deallocate_node(_M_header);
		}

	protected:
		using _Base::_M_node_allocate;
		using _Base::_M_deallocate_node;
		using _Base::_M_header;
	};

	template <typename _Key, typename _Value, typename _KeyOfValue, typename _Compare = naive::less<_Value>,
			typename _Alloc = naive::allocator<_Value>>
	class RBTree :protected _RBTree_base<_Value, _Alloc> {

	private:
		typedef _RBTree_base<_Value, _Alloc> _MyBase;

	protected:
		typedef _RBTree_node<_Value> _RBTree_node_type;
		typedef _RBTree_node_type _Tree_node;

	public:
		typedef _Key key_type;
		typedef _Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef _RBTree_node_type* _Link_type;
		typedef _RBTree_iterator<value_type, reference, pointer > iterator;
		typedef _RBTree_iterator<value_type, const_reference, const_pointer > const_iterator;

	protected:
		typedef typename _MyBase::allocator_type allocator_type;
		using _MyBase::get_allocator;
		using _MyBase::_M_node_allocate;
		using _MyBase::_M_deallocate_node;

		// the parent node of root and the child of root
		// (root.parent<->_M_header.parent);
		// _M_header allocate in _RBTree_alloc_base class;
		using _MyBase::_M_header;


	protected:
		size_type _M_node_count;
		_Compare _M_key_compare;//A function object;

		_Link_type _M_create_node(const value_type& _value) {

			_Link_type _temp = _M_node_allocate();
			try {
				::construct(&_temp->_M_node_value, _value);
			}
			catch (...) {
				_M_deallocate_node(_temp);
			}

			return _temp;
		}

		_Link_type _M_clone_node(_Link_type _node)
		{
			_Link_type _tmp = _M_create_node(_node->_M_node_value);
			_tmp->_M_color = _node->_M_color;
			_tmp->_M_left = nullptr;
			_tmp->_M_right = nullptr;
			return _tmp;
		}

		void destroy_node(_Link_type _node)
		{
			::destroy(&_node->_M_node_value);
			_M_deallocate_node(_node);
		}

		_Link_type& _M_root() const {
			return _M_header->_M_parent;
		}

		_Link_type& _M_leftmost() const {
			return _M_header->_M_left;
		}

		_Link_type& _M_rightmost() const {
			return _M_header->_M_right;
		}

		static _Link_type& _S_left(_Link_type _node) {
			return (_node->_M_left);
		}

		static _Link_type& _S_right(_Link_type _node) {
			return (_node->_M_right);
		}

		static _Link_type& _S_parent(_Link_type _node) {
			return (_node->_M_parent);
		}

		static reference _S_value(_Link_type _node) {
			return _node->_M_node_value;
		}

		static const _Key& _S_key(_Link_type _node) {
			return _KeyOfValue()(_S_value(_node));
		}

		static _Node_color_type& _S_color(_Link_type _node) {
			return (_node->_M_color);
		}

		static _Link_type _M_minimum(_Link_type _node) {

			while (_node->_M_left != nullptr) {
				_node = _node->_M_left;
			}

			return _node;
		}

		static _Link_type _M_maxmum(_Link_type _node) {

			while (_node->_M_right != nullptr) {
				_node = _node->_M_right;
			}

			return _node;
		}


	public:

		RBTree() :_MyBase(allocator_type()), _M_node_count(0), _M_key_compare() {
			_M_empty_initialize();
		}

		// Return the function object;
		_Compare key_compare() const {
			return _M_key_compare;
		}

		iterator begin() {
			return iterator(_M_leftmost());
		}

		const_iterator begin() const {
			return const_iterator(_M_leftmost());
		}

		iterator end() {
			return iterator(_M_header);
		}

		const_iterator end() const {
			return const_iterator(_M_header);
		}

		bool empty() const {
			return _M_node_count == 0;
		}

		size_type size() const {
			return _M_node_count;
		}

		size_type max_size() const {
			return size_type(-1);
		}

		iterator insert_unique(iterator _position, const value_type& _value);

		iterator insert_equal(iterator _position, const value_type& _value);




	private:
		void _M_empty_initialize() {
			_S_color(_M_header) = _M_color_red;// because the root must be black, so the _M_header should be red;
			_M_root() = nullptr;
			_M_leftmost() = _M_header;
			_M_rightmost() = _M_header;
		}
	};



	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline iterator RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(iterator _position, const value_type & _value){

		return iterator();
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline iterator RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_equal(iterator _position, const value_type & _value){


		return iterator();
	}

}
#endif //NAIVE_STL_STL_RB_TREE_H
