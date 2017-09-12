//
// Created by Shuai on 2017/8/9.
//

#ifndef NAIVE_STL_HASTABLE_H
#define NAIVE_STL_HASTABLE_H

#include "stl_hash_base.h"
#include "../memory.h"

template <typename Value, typename Key, typename HashFun,
		typename ExtractKey, typename EqualKey, typename Alloc =naive::allocator<Value>>
class _hash_table;

template <typename Value>
struct _hash_table_node{

	typedef _hash_table_node* _Self_ptr;
	_Self_ptr _M_next;
	Value _M_value;
};

template <typename Value, typename Key, typename HashFnc,
		typename ExtractKey, typename EqualKey, typename Alloc =naive::allocator<Value>>
class _hash_table_const_iterator;


template <typename Value, typename Key, typename HashFnc,
		typename ExtractKey, typename EqualKey, typename Alloc =naive::allocator<Value>>
class _hash_table_iterator{

public:
	typedef _hash_table<Value,Key,HashFnc,ExtractKey,EqualKey,Alloc> _HashTable_type;
	typedef _hash_table_iterator<Value,Key,ExtractKey,EqualKey,Alloc> iterator;
	typedef _hash_table_const_iterator<Value,Key,ExtractKey,EqualKey,Alloc> const_iterator;
	typedef _hash_table_node<Value> _Node_type;

	typedef naive::forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef std::size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

public:
	_Node_type* _M_curr;
	_HashTable_type* _M_hash_table;

public:
	_hash_table_iterator():_M_curr(nullptr),_M_hash_table(nullptr){}
	_hash_table_iterator(_Node_type* _node,_HashTable_type* _hash_table):_M_curr(_node),_M_hash_table(_hash_table){}

	reference operator*() const{

		return _M_curr->_M_value;
	}

	pointer operator->() const{
		return &(operator*());
	}

	iterator& operator++(){

		_Node_type* _old=_M_curr;

		_M_curr=_M_curr->_M_next;

		if(_M_curr==nullptr){


		}
	}

	iterator operator++(int){

		iterator _tmp=*this;

		++(*this);

		return _tmp;
	}

};


template <typename Value, typename Key, typename HashFun,
		typename ExtractKey, typename EqualKey, typename Alloc =naive::allocator<Value>>
class _hash_table{

public:
	typedef Key key_type;
	typedef Value value_type;
	typedef HashFun hasher;
	typedef EqualKey key_equal;
	typedef std::size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef naive::allocator_traits<Alloc> allocator_type;

	allocator_type get_allocator() const{

		return allocator_type();
	}

private:
	typedef _hash_table_node<Value> _Linked_node;



};






#endif //NAIVE_STL_HASTABLE_H
