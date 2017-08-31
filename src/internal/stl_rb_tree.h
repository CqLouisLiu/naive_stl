
/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 * This file is modified from sgi_stl_312;
 *
*/

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
#include "../utility.h"
#include "../algorithm.h"

namespace naive {


	typedef bool _Node_color_type;
	const _Node_color_type _M_color_red = false;//red is false and black is true;
	const _Node_color_type _M_color_black = true;

	struct _RBTree_node_base {

		typedef _RBTree_node_base _Base_node_type;
		typedef _Base_node_type* _Base_node_ptr;

		_Base_node_ptr _M_parent;
		_Base_node_ptr _M_left;
		_Base_node_ptr _M_right;
		_Node_color_type _M_color;

		static _Base_node_ptr _M_minimum(_Base_node_ptr _node) {

			while (_node->_M_left != nullptr) {
				_node = _node->_M_left;
			}

			return _node;
		}

		static _Base_node_ptr _M_maximum(_Base_node_ptr _node) {

			while (_node->_M_right != nullptr){
				_node = _node->_M_right;
			}

			return _node;
		}
	};

	////////////////////////////////////////////////////////////////
	//// The node of RB-Tree
	////////////////////////////////////////////////////////////////
	template <typename _T>
	struct _RBTree_node :public _RBTree_node_base {

		typedef _T _Node_value_type;
		typedef _RBTree_node<_T>* _Link_type;

		_Node_value_type _M_node_value;
	};


	struct _RBTree_iterator_base {

		typedef ptrdiff_t difference_type;
		typedef naive::bidirectional_iterator_tag iterator_category;
		typedef _RBTree_node_base::_Base_node_ptr _Base_node_ptr;
		_Base_node_ptr _M_node;

		void _M_Tree_increment() {

			/*
			* The current node have a right child node means that the node just bigger than
			* the current node in red-black tree is the most-left node in its right child tree;
			* Otherwise, we need to percolate up to find the next element;
			*/
			if (_M_node->_M_right != nullptr) {

				_M_node = _M_node->_M_right;

				while (_M_node->_M_left != nullptr){
					_M_node = _M_node->_M_left;
				}
			}
			else {

				_Base_node_ptr _t_parent = _M_node->_M_parent;

				while (_M_node == _t_parent->_M_right) {

					_M_node = _t_parent;
					_t_parent = _t_parent->_M_parent;
				}

				if (_M_node->_M_right != _t_parent) {
					_M_node = _t_parent;
				}
			}
		}

		void _M_Tree_decrement() {

			if (_M_node->_M_color == _M_color_red && _M_node->_M_parent->_M_parent == _M_node){
				_M_node = _M_node->_M_right;
			}
			else if (_M_node->_M_left != nullptr) {

				_Base_node_ptr _t_parent = _M_node->_M_left;

				while (_t_parent->_M_right != nullptr){
					_t_parent = _t_parent->_M_right;
				}

				_M_node = _t_parent;
			}
			else {

				_Base_node_ptr _t_parent = _M_node->_M_parent;

				while (_M_node == _t_parent->_M_left) {

					_M_node = _t_parent;
					_t_parent = _t_parent->_M_parent;
				}

				_M_node = _t_parent;
			}
		}
	};

	/////////////////////////////////////////////////////////////
	//// The iterator of RB-tree
	///////////////////////////////////////////////////////////
	template <typename _Value, typename _Ref, typename _Ptr>
	struct _RBTree_iterator :public _RBTree_iterator_base {

		typedef _Value value_type;
		typedef _Ref reference;
		typedef _Ptr pointer;
		typedef _RBTree_iterator<_Value, _Value&, _Value*> iterator;
		typedef _RBTree_iterator<_Value, const _Value&, const _Value*> const_iterator;
		typedef _RBTree_iterator<_Value, _Ref, _Ptr> _Self_type;

		typedef _RBTree_node<_Value>* _Link_type;

		_RBTree_iterator()= default;

		 _RBTree_iterator(_Link_type _node) {
			_M_node = _node;
		}

		_RBTree_iterator(const iterator& rhs) {
			_M_node = rhs._M_node;
		}

		_RBTree_iterator& operator=(const iterator& rhs){
			_M_node=rhs._M_node;
		}

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
		* @return the next element in sequence;
		*
		*/
		_Self_type& operator++() {

			_M_Tree_increment();
			return *this;
		}

		// expression (it++);
		_Self_type operator++(int) {

			_Self_type _temp = *this;
			_M_Tree_increment();
			return _temp;
		}

		// expression (--it)
		_Self_type& operator--() {

			_M_Tree_decrement();
			return *this;
		}

		_Self_type operator--(int) {

			_Self_type _temp = *this;
			_M_Tree_decrement();
			return _temp;
		}
	};

	inline bool operator==(const _RBTree_iterator_base& x, const _RBTree_iterator_base& y) {
		return x._M_node == y._M_node;
	}

	inline bool operator!=(const _RBTree_iterator_base& x, const _RBTree_iterator_base& y) {
		return x._M_node != y._M_node;
	}

	inline void _RBTree_rotate_left(_RBTree_node_base* _rt_node, _RBTree_node_base*& _root) {

		_RBTree_node_base* _temp = _rt_node->_M_right;

		_rt_node->_M_right = _temp->_M_left;

		if (_temp->_M_left !=nullptr) {
			_temp->_M_left->_M_parent = _rt_node;
		}
		_temp->_M_parent = _rt_node->_M_parent;

		if (_rt_node == _root) {
			_root = _temp;
		}
		else if (_rt_node == _rt_node->_M_parent->_M_left){
			_rt_node->_M_parent->_M_left = _temp;
		}
		else {
			_rt_node->_M_parent->_M_right = _temp;
		}

		_temp->_M_left = _rt_node;
		_rt_node->_M_parent = _temp;
	}

	//////////////////////////////////////////////////////////////////////
	///// global function
	//// Red-black tree node rotate right
	//// @param _node: the rotated node;
	/////////////////////////////////////////////////////////////////////
	inline void _RBTree_rotate_right(_RBTree_node_base* _rt_node, _RBTree_node_base*& _root) {

		_RBTree_node_base* _temp = _rt_node->_M_left;

		_rt_node->_M_left = _temp->_M_right;

		if (_temp->_M_right != 0) {
			_temp->_M_right->_M_parent = _rt_node;
		}

		_temp->_M_parent = _rt_node->_M_parent;

		if (_rt_node == _root) {
			_root = _temp;
		}
		else if (_rt_node == _rt_node->_M_parent->_M_right) {
			_rt_node->_M_parent->_M_right = _temp;
		}
		else {
			_rt_node->_M_parent->_M_left = _temp;
		}
		_temp->_M_right = _rt_node;
		_rt_node->_M_parent = _temp;

	}

	///////////////////////////////////////////////////////////////////////////
	//// the global function to balance the red-black tree
	//////////////////////////////////////////////////////////////////////////
	inline void _RBTree_rebalance(_RBTree_node_base* _node, _RBTree_node_base*& _root){

		_node->_M_color = _M_color_red;// the new element must be red node;


		// the new node and its parent node are both red;
		while (_node != _root && _node->_M_parent->_M_color == _M_color_red) {

			if (_node->_M_parent == _node->_M_parent->_M_parent->_M_left) {

				//get new node's uncle node;
				_RBTree_node_base* _uncle_node = _node->_M_parent->_M_parent->_M_right;

				// this mean the uncle node and parent node are both red node;
				// use top-down procedure;
				if (_uncle_node && _uncle_node->_M_color == _M_color_red) {

					_node->_M_parent->_M_color = _M_color_black;
					_uncle_node->_M_color = _M_color_black;
					_node->_M_parent->_M_parent->_M_color = _M_color_red;
					_node = _node->_M_parent->_M_parent;
				}
				else {

					//Note: the null nodes are considered as black node;
					// "inside" means that the parent node of new node is the left child of of grandparent node;
					// And the new node is the right child of its parent node;
					// we need rotate left firstly;
					if (_node == _node->_M_parent->_M_right) {

						_node = _node->_M_parent;
						_RBTree_rotate_left(_node, _root);
					}

					_node->_M_parent->_M_color = _M_color_black;
					_node->_M_parent->_M_parent->_M_color = _M_color_red;
					_RBTree_rotate_right(_node->_M_parent->_M_parent, _root);
				}
			}
			else {

				_RBTree_node_base* _uncle_node = _node->_M_parent->_M_parent->_M_left;

				if (_uncle_node && _uncle_node->_M_color == _M_color_red) {

					_node->_M_parent->_M_color = _M_color_black;
					_uncle_node->_M_color = _M_color_black;
					_node->_M_parent->_M_parent->_M_color = _M_color_red;
					_node = _node->_M_parent->_M_parent;
				}
				else {

					if (_node == _node->_M_parent->_M_left) {

						_node = _node->_M_parent;
						_RBTree_rotate_right(_node, _root);
					}

					_node->_M_parent->_M_color = _M_color_black;
					_node->_M_parent->_M_parent->_M_color = _M_color_red;
					_RBTree_rotate_left(_node->_M_parent->_M_parent, _root);
				}
			}
		}
		_root->_M_color = _M_color_black;
	}

	inline _RBTree_node_base* _RBTree_rebalance_for_erase(_RBTree_node_base* _x,
														  _RBTree_node_base*& _root, _RBTree_node_base*& _leftmost,
														  _RBTree_node_base*& _rightmost) {
		_RBTree_node_base* _rt_node = _x;
		_RBTree_node_base* _t_node = nullptr;
		_RBTree_node_base* t_parent = nullptr;

		if (_rt_node->_M_left == nullptr) {

			_t_node = _rt_node->_M_right;
		}
		else {

			if (_rt_node->_M_right == nullptr) {

				_t_node = _rt_node->_M_left;
			}
			else {

				_rt_node = _rt_node->_M_right;

				while (_rt_node->_M_left != nullptr) {
					_rt_node = _rt_node->_M_left;
				}

				_t_node = _rt_node->_M_right;
			}
		}
		if(_rt_node != _x) {

			_x->_M_left->_M_parent = _rt_node;

			_rt_node->_M_left = _x->_M_left;

			if (_rt_node != _x->_M_right) {

				t_parent = _rt_node->_M_parent;

				if(_t_node) {
					_t_node->_M_parent = _rt_node->_M_parent;
				}

				_rt_node->_M_parent->_M_left = _t_node;
				_rt_node->_M_right = _x->_M_right;
				_x->_M_right->_M_parent = _rt_node;
			}
			else {

				t_parent = _rt_node;
			}

			if (_root == _x) {

				_root = _rt_node;
			}
			else if(_x->_M_parent->_M_left == _x) {
				_x->_M_parent->_M_left = _rt_node;
			}

			else {
				_x->_M_parent->_M_right = _rt_node;
			}
			_rt_node->_M_parent = _x->_M_parent;
			std::swap(_rt_node->_M_color, _x->_M_color);
			_rt_node = _x;
		}

		else {

			t_parent = _rt_node->_M_parent;

			if(_t_node) {

				_t_node->_M_parent = _rt_node->_M_parent;
			}
			if(_root == _x) {
				_root = _t_node;
			}
			else {
				if (_x->_M_parent->_M_left == _x)
					_x->_M_parent->_M_left = _t_node;
				else
					_x->_M_parent->_M_right = _t_node;
			}
			if (_leftmost == _x) {

				if (_x->_M_right == nullptr) {
					_leftmost = _x->_M_parent;
				}
				else{
					_leftmost = _RBTree_node_base::_M_minimum(_t_node);
				}
			}

			if (_rightmost == _x){

				if (_x->_M_left == 0) {
					_rightmost = _x->_M_parent;
				}
				else{
					_rightmost = _RBTree_node_base::_M_minimum(_t_node);
				}
			}
		}
		if (_rt_node->_M_color != _M_color_red) {

			while (_t_node != _root && (_t_node == 0 || _t_node->_M_color == _M_color_black)) {

				if (_t_node == t_parent->_M_left) {

					_RBTree_node_base *_w = t_parent->_M_right;

					if (_w->_M_color == _M_color_red) {

						_w->_M_color = _M_color_black;
						t_parent->_M_color = _M_color_red;
						_RBTree_rotate_left(t_parent, _root);
						_w = t_parent->_M_right;
					}
					if ((_w->_M_left == 0 || _w->_M_left->_M_color == _M_color_black) &&
							(_w->_M_right == 0 || _w->_M_right->_M_color == _M_color_black)) {

						_w->_M_color = _M_color_red;
						_t_node = t_parent;
						t_parent = t_parent->_M_parent;
					} else {
						if (_w->_M_right == 0 || _w->_M_right->_M_color == _M_color_black) {

							if (_w->_M_left){
								_w->_M_left->_M_color = _M_color_black;
							}

							_w->_M_color = _M_color_red;
							_RBTree_rotate_right(_w, _root);
							_w = t_parent->_M_right;
						}

						_w->_M_color = t_parent->_M_color;
						t_parent->_M_color = _M_color_black;

						if (_w->_M_right) {

							_w->_M_right->_M_color = _M_color_black;
						}

						_RBTree_rotate_left(t_parent, _root);
						break;
					}
				} else {

					_RBTree_node_base *__w = t_parent->_M_left;

					if (__w->_M_color == _M_color_red) {

						__w->_M_color = _M_color_black;
						t_parent->_M_color = _M_color_red;
						_RBTree_rotate_right(t_parent, _root);
						__w = t_parent->_M_left;
					}
					if ((__w->_M_right == 0 || __w->_M_right->_M_color == _M_color_black) &&
							(__w->_M_left == 0 || __w->_M_left->_M_color == _M_color_black)) {

						__w->_M_color = _M_color_red;
						_t_node = t_parent;
						t_parent = t_parent->_M_parent;

					} else {
						if (__w->_M_left == 0 || __w->_M_left->_M_color == _M_color_black) {

							if (__w->_M_right) {
								__w->_M_right->_M_color = _M_color_black;
							}
							__w->_M_color = _M_color_red;

							_RBTree_rotate_left(__w, _root);

							__w = t_parent->_M_left;
						}
						__w->_M_color = t_parent->_M_color;

						t_parent->_M_color = _M_color_black;

						if (__w->_M_left){
							__w->_M_left->_M_color = _M_color_black;
						}
						_RBTree_rotate_right(t_parent, _root);
						break;
					}
				}
			}

			if (_t_node){
				_t_node->_M_color = _M_color_black;
			}
		}
		return _rt_node;
	}



	//////////////////////////////////////////////////
	//// The memory allocate base class of RB-Tree
	/////////////////////////////////////////////////
	template<typename _T, typename _Alloc>
	class _RBTree_alloc_base {

	protected:
		const std::size_t _ALLOC_SINGLE_NODE = 1;

	public:
		using allocator_type = typename _Alloc::template rebind<_RBTree_node<_T>>::other;

		allocator_type get_allocator() const {
			return _M_node_allocator;
		}

		explicit _RBTree_alloc_base(const allocator_type& _alloc):
				_M_node_allocator(_alloc), _M_header(nullptr) {}

	protected:

		allocator_type _M_node_allocator;

		_RBTree_node<_T>* _M_header;//the _M_header is a trick;

		_RBTree_node<_T>* _M_node_allocate() {

			return _M_node_allocator.allocate(_ALLOC_SINGLE_NODE);
		}

		void _M_deallocate_node(_RBTree_node<_T>* _p) {

			_M_node_allocator.deallocate(_p, _ALLOC_SINGLE_NODE);
		}
	};


	//////////////////////////////////////////////////
	//// The base class of RB-Tree
	/////////////////////////////////////////////////
	template<typename _T, typename _Alloc>
	class _RBTree_base :public _RBTree_alloc_base<_T, _Alloc> {

	public:
		typedef _RBTree_alloc_base<_T, _Alloc> _Base;
		typedef typename _Base::allocator_type allocator_type;

		explicit _RBTree_base(const allocator_type& _alloc) :_Base(_alloc) {
			_M_header = _M_node_allocate();
		}

		//_RBTree_base(_RBTree_node_base&& rhs)= default;
		//_RBTree_base &operator=(_RBTree_base&& rhs)= default;

		~_RBTree_base() {
			_M_deallocate_node(_M_header);
		}

	protected:
		using _Base::_M_node_allocate;
		using _Base::_M_deallocate_node;
		using _Base::_M_header;
		using _Base::get_allocator;
	};


	//////////////////////////////////////////////////////////////////////
	//// The RB-Tree class
	////////////////////////////////////////////////////////////////////
	template <typename _Key, typename _Value, typename _KeyOfValue, typename _Compare = naive::less<_Value>,
			typename _Alloc = naive::allocator<_Value>>
	class RBTree :protected _RBTree_base<_Value, _Alloc> {

	private:
		typedef _RBTree_base<_Value, _Alloc> _MyBase;

	protected:
		typedef _RBTree_node_base::_Base_node_ptr _Base_node_ptr;
		typedef _RBTree_node<_Value> _RBTree_node_type;
		typedef _RBTree_node_type _Tree_node;
		typedef _Node_color_type _Color_type;

	public:
		typedef _Value value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef _Key key_type;
		typedef typename _MyBase::allocator_type allocator_type;
		typedef _RBTree_iterator<value_type, reference, pointer> iterator;
		typedef _RBTree_iterator<value_type, const_reference, const_pointer> const_iterator;
		typedef naive::reverse_iterator<iterator> reverse_iterator;
		typedef naive::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef _RBTree_node_type* _Link_type;

	protected:
		using _MyBase::get_allocator;
		using _MyBase::_M_node_allocate;
		using _MyBase::_M_deallocate_node;
		size_type _M_node_count;
		_Compare _M_key_compare;//A function object;

		////////////////////////////////////////////////////////
		//// The parent node of root and the child of root
		//// (root.parent<->_M_header.parent);
		//// _M_header allocate in _RBTree_alloc_base class;
		////////////////////////////////////////////////////////
		using _MyBase::_M_header;

	protected:
		_Link_type _M_create_node(const value_type& _value) {

			_Link_type _temp = _M_node_allocate();

			try {
				::construct(&_temp->_M_node_value, _value);
			}// commit or rollback;
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

		void destroy_node(_Link_type _node) {

			::destroy(&_node->_M_node_value);
			_M_deallocate_node(_node);
		}

	protected:

		_Link_type& _M_get_root() const {

			return (_Link_type&)_M_header->_M_parent;
		}

		_Link_type& _M_get_leftmost() const {

			return (_Link_type&)_M_header->_M_left;
		}

		_Link_type& _M_get_rightmost() const {

			return (_Link_type&)_M_header->_M_right;
		}

		static _Link_type& _M_get_left(_Link_type _node) {

			return (_Link_type&)_node->_M_left;
		}

		static _Link_type& _M_get_right(_Link_type _node) {

			return (_Link_type&)_node->_M_right;
		}

		static _Link_type& _M_get_parent(_Link_type _node) {

			return (_Link_type&)_node->_M_parent;
		}

		static reference _M_get_value(_Link_type _node) {

			return _node->_M_node_value;
		}

		static const _Key& _M_get_key(_Link_type _node) {

			return _KeyOfValue()(_M_get_value(_node));
		}

		static _Color_type& _M_get_color(_Link_type _node) {

			return (_Color_type&)(_node->_M_color);
		}

		static _Link_type _M_get_minimum(_Link_type _node) {

			return static_cast<_Link_type>(_RBTree_node_base::_M_minimum(_node));
		}

		static _Link_type _M_get_maxmum(_Link_type _node) {

			return static_cast<_Link_type>(_RBTree_node_base::_M_maximum(_node));
		}


	protected:

		static _Link_type& _M_get_left(_Base_node_ptr _node) {

			return (_Link_type&)(_node->_M_left);
		}

		static _Link_type& _M_get_right(_Base_node_ptr _node) {

			return (_Link_type&)(_node->_M_right);
		}

		static _Link_type& _M_get_parent(_Base_node_ptr _node) {

			return (_Link_type&)(_node->_M_parent);
		}

		static reference _M_get_value(_Base_node_ptr _node) {
			return ((_Link_type)_node)->_M_node_value;
		}

		static const _Key& _M_get_key(_Base_node_ptr _node) {

			return _KeyOfValue()(_M_get_value(_Link_type(_node)));
		}

		static _Color_type& _M_get_color(_Base_node_ptr _node) {
			return (_Color_type&)(_Link_type(_node)->_M_color);
		}


	public:

		RBTree() :_MyBase(allocator_type()), _M_node_count(0), _M_key_compare() {
			_M_empty_initialize();
		}

		RBTree(const _Compare& _cmp, const allocator_type& __a) : _MyBase(__a), _M_node_count(0), _M_key_compare(_cmp) {
			_M_empty_initialize();
		}

		RBTree& operator=(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs){

			if (this != &rhs) {

				clear();
				_M_node_count = 0;
				_M_key_compare = rhs._M_key_compare;

				if (rhs._M_get_root() == nullptr) {

					_M_get_root() = nullptr;
					_M_get_leftmost() = _M_header;
					_M_get_rightmost() = _M_header;
				}
				else {
					_M_get_root() = _M_copy(rhs._M_get_root(), _M_header);
					_M_get_leftmost() = _M_get_minimum(_M_get_root());
					_M_get_rightmost() = _M_get_maxmum(_M_get_root());
					_M_node_count = rhs._M_node_count;
				}
			}
			return *this;
		}

		~RBTree(){
			clear();
		}

		// Return the function object;
		_Compare key_compare() const {
			return _M_key_compare;
		}

		iterator begin() {
			return iterator(_M_get_leftmost());
		}

		const_iterator begin() const {
			return _M_get_leftmost();
		}

		iterator end() {
			return iterator(_M_header);
		}

		const_iterator end() const {
			return _M_header;
		}

		reverse_iterator rbegin() {

			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const {

			return const_reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const {

			return const_reverse_iterator(begin());
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

		void swap(RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

			std::swap(_M_header, rhs._M_header);
			std::swap(_M_node_count, rhs._M_node_count);
			std::swap(_M_key_compare, rhs._M_key_compare);
		}


	public:

		void clear() {
			if (_M_node_count != 0) {
				_M_erase(_M_get_root());
				_M_get_leftmost() = _M_header;
				_M_get_root() = nullptr;
				_M_get_rightmost() = _M_header;
				_M_node_count = 0;
			}
		}

		naive::pair<iterator, bool> insert_unique(const value_type& value);
		iterator insert_unique(iterator pos, const value_type& value);
		void insert_unique(const_iterator first, const_iterator last);
		template <typename InputIt>
		void insert_unique(InputIt first, InputIt last);

		iterator insert_equal(const value_type& _value);
		iterator insert_equal(iterator pos, const value_type& value);
		template <typename InputIt>
		void insert_equal(InputIt first, InputIt last);


		iterator find(const key_type& key);
		const_iterator find(const key_type& __x) const;


		void erase(iterator pos);
		size_type erase(const key_type& key);

		void erase(iterator first, iterator last){

			if (first == begin() && last == end()) {
				clear();
			}
			else{
				while (first != last) {
					erase(first++);
				}
			}
		}

		void erase(const key_type* first, const key_type* last){

			while (first != last){
				erase(*first++);
			}
		}

		iterator lower_bound(const key_type& key){

			_Link_type _t_curr = _M_get_root();
			_Link_type _t_last = _M_header;

			while (_t_curr != 0)
				if (!_M_key_compare(_M_get_key(_t_curr), key)){

					_t_last = _t_curr;
					_t_curr = _M_get_left(_t_curr);

				}
				else {
					_t_curr = _M_get_right(_t_curr);
				}

			return iterator(_t_last);
		}

		const_iterator lower_bound(const key_type& key) const{

			_Link_type _t_curr = _M_get_root();
			_Link_type _t_last = _M_header;

			while (_t_curr != 0)
				if (!_M_key_compare(_M_get_key(_t_curr), key)){

					_t_last = _t_curr;
					_t_curr = _M_get_left(_t_curr);

				}
				else {
					_t_curr = _M_get_right(_t_curr);
				}

			return const_iterator(_t_last);
		}

		iterator upper_bound(const key_type& key){

			_Link_type _t_curr = _M_get_root();
			_Link_type _t_last = _M_header;

			while (_t_curr != 0)
				if (_M_key_compare(key, _M_get_key(_t_curr))){

					_t_last = _t_curr;
					_t_curr = _M_get_left(_t_curr);
				}
				else {
					_t_curr = _M_get_right(_t_curr);
				}
			return iterator(_t_last);
		}

		const_iterator upper_bound(const key_type& key) const{

			_Link_type _t_curr = _M_get_root();
			_Link_type _t_last = _M_header;

			while (_t_curr != 0)
				if (_M_key_compare(key, _M_get_key(_t_curr))){

					_t_last = _t_curr;
					_t_curr = _M_get_left(_t_curr);
				}
				else {
					_t_curr = _M_get_right(_t_curr);
				}
			return const_iterator(_t_last);
		}

		naive::pair<iterator,iterator> equal_range(const key_type& key){

			return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		}

		naive::pair<const_iterator, const_iterator> equal_range(const key_type& key) const{

			return pair<const_iterator,const_iterator>(lower_bound(key), upper_bound(key));
		}


	private:
		void _M_empty_initialize() {

			_M_get_color(_M_header) = _M_color_red;// because the root must be black, so the _M_header should be red;
			_M_get_root() = nullptr;
			_M_get_leftmost() = _M_header;
			_M_get_rightmost() = _M_header;
		}

		iterator _M_insert(_RBTree_node_base* x, _RBTree_node_base* y, const value_type& _value);

		void _M_erase(_Link_type _node){

			while (_node != nullptr) {
				_M_erase(_M_get_right(_node));

				_Link_type _temp = _M_get_left(_node);
				destroy_node(_node);
				_node = _temp;
			}
		}

		_Link_type _M_copy(_Link_type _t_node, _Link_type _t_parent){

			_Link_type __top = _M_clone_node(_t_node);
			__top->_M_parent = _t_parent;

			try {
				if (_t_node->_M_right) {
					__top->_M_right = _M_copy(_M_get_right(_t_node), __top);
				}
				_t_parent = __top;
				_t_node = _M_get_left(_t_node);

					while (_t_node != nullptr) {

						_Link_type _temp = _M_clone_node(_t_node);

						_t_parent->_M_left = _temp;

						_temp->_M_parent = _t_parent;

						if (_t_node->_M_right)
							_temp->_M_right = _M_copy(_M_get_right(_t_node), _temp);
						_t_parent = _temp;
						_t_node = _M_get_left(_t_node);
					}
			}
			catch (...){
				_M_erase(__top);
			};

			return __top;
		}

	};




	/*
	* Insert the element into the red-black tree, if the element is unique, then insert success.
	* Otherwise, the insert is failure;
	*
	* @return: a naive::pair, the first element is a iterator point to the new element; the second element indicates
	* 			the insert if success;
	* */
	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline naive::pair<typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator, bool> RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(const value_type& value) {

		_Link_type _t_node = _M_header;
		_Link_type _t_parent = _M_get_root();

		bool _t_cmp = true;

		while (_t_parent != nullptr) {

			_t_node = _t_parent;
			_t_cmp = _M_key_compare(_KeyOfValue()(value), _M_get_key(_t_parent));
			_t_parent = _t_cmp ? _M_get_left(_t_parent) : _M_get_right(_t_parent);
		}

		iterator _it = iterator(_t_node);

		if (_t_cmp) {

			if (_it == begin()) {

				return naive::pair<iterator, bool>(_M_insert(_t_parent, _t_node, value), true);
			} else {

				--_it;
			}
		}

		if (_M_key_compare(_M_get_key(_it._M_node), _KeyOfValue()(value))) {

			return naive::pair<iterator, bool>(_M_insert(_t_parent, _t_node, value), true);
		}

		return naive::pair<iterator, bool>(_it, false);
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator RBTree<_Key, _Value,
			_KeyOfValue, _Compare, _Alloc>::insert_unique(iterator pos, const value_type & value) {

		if (pos._M_node == _M_header->_M_left) {
			if (size() > 0 && _M_key_compare(_KeyOfValue()(value), _M_get_key(pos._M_node))) {
				return _M_insert(pos._M_node, pos._M_node, value);
			}
			else {
				return insert_unique(value).first;
			}
		} else if (pos._M_node == _M_header) {

			if (_M_key_compare(_M_get_key(_M_get_rightmost()), _KeyOfValue()(value))){
				return _M_insert(0, _M_get_rightmost(), value);
			}
			else{
				return insert_unique(value).first;
			}

		} else {

			iterator _t_before = pos;
			--_t_before;

			if (_M_key_compare(_M_get_key(_t_before._M_node), _KeyOfValue()(value)) &&
					_M_key_compare(_KeyOfValue()(value), _M_get_key(pos._M_node))) {

				if (_M_get_right(_t_before._M_node) == 0) {
					return _M_insert(0, _t_before._M_node, value);
				}
				else {
					return _M_insert(pos._M_node, pos._M_node, value);
				}
			} else {
				return insert_unique(value).first;
			}
		}
	}


	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline void RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(const_iterator first, const_iterator last) {

		for ( ; first != last; ++first){
			insert_unique(*first);
		}
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	template<typename InputIt>
	inline void RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_unique(InputIt first, InputIt last) {

		for ( ; first != last; ++first){
			insert_equal(*first);
		}
	}


	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline void RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::erase(iterator pos){

		_Link_type _temp = (_Link_type) _RBTree_rebalance_for_erase(pos._M_node, _M_header->_M_parent,
																	_M_header->_M_left, _M_header->_M_right);
		destroy_node(_temp);
		--_M_node_count;
	}


	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::size_type RBTree<_Key, _Value,
			_KeyOfValue, _Compare, _Alloc>::erase(const key_type & key) {

		naive::pair<iterator,iterator> _t_pair = equal_range(key);

		size_type _n = 0;

		distance(_t_pair.first, _t_pair.second, _n);

		erase(_t_pair.first, _t_pair.second);

		return _n;

	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator RBTree<_Key, _Value, _KeyOfValue,
			_Compare, _Alloc>::insert_equal(const value_type & _value) {

		_Link_type _t_node = _M_get_root();
		_Link_type _t_parent = _M_header;

		while (_t_node != nullptr) {

			_t_parent = _t_node;
			_t_node = _M_key_compare(_KeyOfValue()(_value), _M_get_key(_t_node)) ? _M_get_left(_t_node) : _M_get_right(_t_node);

		}

		return _M_insert(_t_node, _t_parent, _value);
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator RBTree<_Key, _Value,
			_KeyOfValue, _Compare, _Alloc>::insert_equal(iterator pos, const value_type & value) {

		if (pos._M_node == _M_header->_M_left) {
			if (size() > 0 && _M_key_compare(_KeyOfValue()(value), _M_get_key(pos._M_node))){
				return _M_insert(pos._M_node, pos._M_node, value);

			}
			else {
				return insert_equal(value);
			}
		}
		else if (pos._M_node == _M_header) {
			if (!_M_key_compare(_KeyOfValue()(value), _M_get_key(_M_get_rightmost()))) {
				return _M_insert(0, _M_get_rightmost(), value);
			}
			else {
				return insert_equal(value);
			}
		}
		else {

			iterator _t_before = pos;
			--_t_before;
			if (!_M_key_compare(_KeyOfValue()(value), _M_get_key(_t_before._M_node)) &&
					!_M_key_compare(_M_get_key(pos._M_node), _KeyOfValue()(value))) {

				if (_M_get_right(_t_before._M_node) == nullptr) {
					return _M_insert(0, _t_before._M_node, value);
				}
				else {
					return _M_insert(pos._M_node, pos._M_node, value);
				}
			}
			else {
				return insert_equal(value);
			}
		}
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	template<typename InputIt>
	inline void RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::insert_equal(InputIt first, InputIt last) {

		for (; first != last; ++first)
			insert_equal(*first);
	}


	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator RBTree<_Key, _Value, _KeyOfValue,
			_Compare, _Alloc>::_M_insert(_RBTree_node_base* x, _RBTree_node_base* y, const value_type & _value) {

		_Link_type _t_node = (_Link_type) x;
		_Link_type _t_parent = (_Link_type) y;
		_Link_type _temp=nullptr;

		if (_t_parent == _M_header || _t_node != nullptr || _M_key_compare(_KeyOfValue()(_value), _M_get_key(_t_parent))) {

			_temp = _M_create_node(_value);
			_M_get_left(_t_parent) = _temp;

			if (_t_parent == _M_header) {

				_M_get_root() = _temp;
				_M_get_rightmost() = _temp;

			}
			else if (_t_parent == _M_get_leftmost())
				_M_get_leftmost() = _temp;
		}
		else {
			_temp = _M_create_node(_value);
			_M_get_right(_t_parent) = _temp;
			if (_t_parent == _M_get_rightmost())
				_M_get_rightmost() = _temp;
		}

		_M_get_parent(_temp) = _t_parent;

		_M_get_left(_temp) = nullptr;
		_M_get_right(_temp) = nullptr;
		_RBTree_rebalance(_temp, _M_header->_M_parent);
		++_M_node_count;
		return iterator(_temp);
	}

	/*
	 * Search in the tree if there is a element with key value x;
	 * @ key: the key of search value;
	 * @return: if success returen a iterator point to the element;
	 * */
	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator RBTree<_Key, _Value, _KeyOfValue,
			_Compare, _Alloc>::find(const key_type & key) {

		_Link_type _t_curr=_M_get_root();
		_Link_type _t_last=_M_header;

		while(_t_curr!=nullptr){

			if(!_M_key_compare(_M_get_key(_t_curr),key)){//_t_curr>=key;

				_t_last=_t_curr;
				_t_curr=_M_get_left(_t_curr);
				//_t_curr=(_Link_type)_t_curr->_M_left;

			}else{//t_node<key;
				_t_curr=_M_get_right(_t_curr);
			}
		}

		iterator _it=iterator(_t_last);

		if(_it==end()||_M_key_compare(key,_M_get_key(_it._M_node))){

			return end();
		}

		return _it;
	}

	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::const_iterator RBTree<_Key, _Value, _KeyOfValue,
			_Compare, _Alloc>::find(const key_type & key) const{

		_Link_type _t_curr=_M_get_root();
		_Link_type _t_last=_M_header;

		while(_t_curr!=nullptr){

			if(!_M_key_compare(_M_get_key(_t_curr),key)){//_t_curr>=key;

				_t_last=_t_curr;
				_t_curr=_M_get_left(_t_curr);
				//_t_curr=(_Link_type)_t_curr->_M_left;

			}else{//t_node<key;
				_t_curr=_M_get_right(_t_curr);
			}
		}

		const_iterator _it=const_iterator(_t_last);

		if(_it==end()||_M_key_compare(key,_M_get_key(_it._M_node))){

			return end();
		}

		return _it;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator==(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
			   const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return lhs.size() == rhs.size() && naive::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator!=(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
						   const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return !(lhs==rhs);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator<(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
						   const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return naive::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator>(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
						  const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return rhs<lhs;
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator>=(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
						  const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return !(lhs<rhs);
	}

	template <typename _Key, typename _Value, typename _KeyOfValue,
			typename _Compare, typename _Alloc>
	inline bool operator<=(const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& lhs,
						   const RBTree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& rhs) {

		return !(rhs<lhs);
	}
}
#endif //NAIVE_STL_STL_RB_TREE_H
