
/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 * This file is from sgi_stl_312;
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

				while (_M_node->_M_left != nullptr)
					_M_node = _M_node->_M_left;
			}
			else {
				_Base_node_ptr _t_arent = _M_node->_M_parent;

				while (_M_node == _t_arent->_M_right) {
					_M_node = _t_arent;
					_t_arent = _t_arent->_M_parent;
				}

				if (_M_node->_M_right != _t_arent) {
					_M_node = _t_arent;
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
		typedef std::size_t size_type;
		typedef _Ptr pointer;
		typedef _RBTree_iterator<_Value, _Value&, _Value*> iterator;
		typedef _RBTree_iterator<_Value, const _Value&, const _Value*> const_iterator;
		typedef _RBTree_iterator<_Value, _Ref, _Ptr> _Self_type;
		typedef _RBTree_node<_Value>* _Link_type;

		_RBTree_iterator() {}

		 _RBTree_iterator(_Link_type _lt) {
			_M_node = _lt;
		}

		_RBTree_iterator(const iterator& _it) {
			_M_node = _it._M_node;
		}

		reference operator*() const {
			return _Link_type(_M_node)->_M_node_value;
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

	/*
	* @param _node: the rotated node;
	*
	* */
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


	//////////////////////////////////////////////////
	//// The memory allocate base class of RB-Tree
	/////////////////////////////////////////////////
	template<typename _T, typename _Alloc>
	class _RBTree_alloc_base {

	private:
		const std::size_t _ALLOC_SINGLE_NODE = 1;

	public:
		using allocator_type = typename _Alloc::template rebind<_RBTree_node<_T>>::other;

		allocator_type get_allocator() const {
			return _M_node_allocator;
		}

		 _RBTree_alloc_base() :
				_M_node_allocator(get_allocator()), _M_header(nullptr) {}

		explicit _RBTree_alloc_base(const allocator_type& _alloc) :
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

		_RBTree_base(const allocator_type& _alloc) :_Base(_alloc) {
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


	//////////////////////////////////////////////////
	//// The RB-Tree class
	/////////////////////////////////////////////////
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
		typedef _RBTree_node_base::_Base_node_ptr _Base_node_ptr;
		typedef _RBTree_iterator<value_type, reference, pointer> iterator;
		typedef _RBTree_iterator<value_type, const_reference, const_pointer> const_iterator;
		typedef naive::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef naive::reverse_iterator<iterator> reverse_iterator;

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
				::construct(&(_temp->_M_node_value), _value);
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

		void destroy_node(_Link_type _node) {

			::destroy(&(_node->_M_node_value));

			_M_deallocate_node(_node);
		}

	protected:

		_Link_type& _M_get_root() const {
			return (_Link_type&)(_M_header->_M_parent);
		}

		_Link_type& _M_get_leftmost() const {
			return (_Link_type&)(_M_header->_M_left);
		}

		_Link_type& _M_get_rightmost() const {
			return (_Link_type&)(_M_header->_M_right);
		}

		static _Link_type& _M_get_left(_Link_type _node) {
			return (_Link_type&)(_node->_M_left);
		}

		static _Link_type& _M_get_right(_Link_type _node) {
			return (_Link_type&)(_node->_M_right);
		}

		static _Link_type& _M_get_parent(_Link_type _node) {
			return (_Link_type&)(_node->_M_parent);
		}

		static reference _M_get_value(_Link_type _node) {
			return _node->_M_node_value;
		}

		static const _Key& _M_get_key(_Link_type _node) {
			return _KeyOfValue()(_M_get_value(_node));
		}

		static _Node_color_type& _M_get_color(_Link_type _node) {
			return (_Node_color_type&)(_node->_M_color);
		}

		static _Link_type _M_get_minimum(_Link_type _node) {

			return static_cast<_Link_type&>(_RBTree_node_base::_M_minimum(_node));
		}

		static _Link_type _M_get_maxmum(_Link_type _node) {

			return static_cast<_Link_type&>(_RBTree_node_base::_M_maximum(_node));
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
			return _KeyOfValue()(_M_get_value((_Link_type)_node));
		}

		static _Node_color_type& _M_get_color(_Base_node_ptr _node) {
			return (_Node_color_type&)(((_Link_type)_node)->_M_color);
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
			return iterator(_M_get_leftmost());
		}

		const_iterator begin() const {
			return const_iterator(_M_get_leftmost());
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

		naive::Pair<iterator, bool> insert_unique(const value_type& _value);

		iterator insert_equal(const value_type& _value);


	private:
		void _M_empty_initialize() {

			_M_get_color(_M_header) = _M_color_red;// because the root must be black, so the _M_header should be red;
			_M_get_root() = nullptr;
			_M_get_leftmost() = _M_header;
			_M_get_rightmost() = _M_header;
		}

		iterator _M_insert(_RBTree_node_base* x, _RBTree_node_base* y, const value_type& _value);
	};


	/*
	* Insert the element into the red-black tree, if the element is unique, then insert success.
	* Otherwise, the insert is failure;
	*
	* @return: a naive::pair, the first element is a iterator point to the new element; the second element indicates
	* 			the insert if success;
	* */
	template<typename _Key, typename _Value, typename _KeyOfValue, typename _Compare, typename _Alloc>
	inline naive::Pair<typename RBTree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>::iterator, bool> RBTree<_Key, _Value,
			_KeyOfValue, _Compare, _Alloc>::insert_unique(const value_type & _value) {

		_Link_type _t_node = _M_header;
		_Link_type _t_parent = _M_get_root();

		bool _t_cmp = true;

		while (_t_parent != nullptr) {

			_t_node = _t_parent;
			_t_cmp = _M_key_compare(_KeyOfValue()(_value), _M_get_key(_t_parent));
			_t_parent = _t_cmp ? _M_get_left(_t_parent) : _M_get_right(_t_parent);
		}

		iterator _it = iterator(_t_node);

		if (_t_cmp) {

			if (_it == begin()) {

				return naive::Pair<iterator, bool>(_M_insert(_t_parent, _t_node, _value), true);
			} else {

				--_it;
			}
		}

		if (_M_key_compare(_M_get_key(_it._M_node), _KeyOfValue()(_value))) {

			return naive::Pair<iterator, bool>(_M_insert(_t_parent, _t_node, _value), true);
		}

		return naive::Pair<iterator, bool>(_it, false);
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


	inline bool operator==(const _RBTree_iterator_base& x, const _RBTree_iterator_base& y) {
		return x._M_node == y._M_node;
	}

	inline bool operator!=(const _RBTree_iterator_base& x, const _RBTree_iterator_base& y) {
		return x._M_node != y._M_node;
	}
}
#endif //NAIVE_STL_STL_RB_TREE_H
