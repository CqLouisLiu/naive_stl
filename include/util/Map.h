
#ifndef NAIVE_STL_MAP_H
#define NAIVE_STL_MAP_H

#include "../internal/stl_rb_tree.h"

template<typename Key,typename Value,typename Compare=naive::less<Key>,
		typename Alloc=naive::allocator<Value>>
class Map{

public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef naive::pair<const Key,Value> value_type;
	typedef Compare key_compare;
	typedef Alloc allocator_type;


	typedef Map<Key,Value,Compare,Alloc> _Self_type;
};


#endif //NAIVE_STL_MAP_H
