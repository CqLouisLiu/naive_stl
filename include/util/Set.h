
#ifndef NAIVE_STL_SET_H
#define NAIVE_STL_SET_H

#include "../internal/stl_rb_tree.h"

namespace naive{


	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//// naive::Set is an associative container that contains a sorted set of unique objects of type Key.
	/// Sorting is done using the key comparison function Compare. Search, removal, and insertion
	/// operations have logarithmic complexity. Sets are usually implemented as red-black trees.
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename Key, typename Compare = std::less<Key>, typename Allocator=naive::allocator<Key>>
	class Set{

	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Allocator allocator_type;


	private:
		typedef RBTree<key_type ,value_type,naive::identity<value_type >,key_compare,Allocator> _TreeContainer;
		_TreeContainer _M_tree_container;

	public:
		typedef typename _TreeContainer::size_type size_type;
		typedef typename _TreeContainer::difference_type difference_type;
		typedef typename _TreeContainer::pointer pointer;
		typedef typename _TreeContainer::const_pointer const_pointer;
		typedef typename _TreeContainer::const_iterator iterator;
		typedef typename _TreeContainer::const_iterator const_iterator;
		typedef typename _TreeContainer::const_reference reference;
		typedef typename _TreeContainer::const_reference const_reference;
		typedef typename _TreeContainer::const_reverse_iterator reverse_iterator;
		typedef typename _TreeContainer::const_reverse_iterator const_reverse_iterator;

		allocator_type get_allocator() const{

			return _M_tree_container.get_allocator();
		}

	public:
		Set():_M_tree_container(Compare(),allocator_type()){}

		explicit Set(const Compare& cmp,const allocator_type& alloc=allocator_type()):_M_tree_container(cmp,alloc){}


		Set(const value_type* first, const value_type* last): _M_tree_container(Compare(), allocator_type()) {
			_M_tree_container.insert_unique(first, last);
		}

		Set( std::initializer_list<value_type> init, const Compare& cmp = Compare(),
			 const Allocator& alloc = Allocator()):_M_tree_container(cmp,alloc){

			_M_tree_container.insert_unique(init.begin(),init.end());
		}

		template <class InputIt>
		Set(InputIt first, InputIt last):_M_tree_container(Compare(),allocator_type()){

			_M_tree_container.insert_unique(first,last);
		}

		template <class InputIt>
		Set(InputIt first, InputIt last, const Compare& cmp, const allocator_type& alloc = allocator_type()):
				_M_tree_container(cmp,alloc){

			_M_tree_container.insert_unique(first,last);
		}

	public:

		key_compare key_comp() const{

			return _M_tree_container.key_compare();
		}

		value_compare value_comp() const{

			return _M_tree_container.key_compare();
		}

		iterator begin() const{

			return _M_tree_container.begin();
		}

		const_iterator cbegin() const{

			return _M_tree_container.cbegin();
		}

		iterator end() const{

			return _M_tree_container.end();
		}

		const_iterator cend() const{

			return _M_tree_container.cend();
		}

		reverse_iterator rbegin() const{

			return _M_tree_container.rbegin();
		}

		const_reverse_iterator crbegin() const{

			return _M_tree_container.crbegin();
		}

		reverse_iterator rend() const{

			return _M_tree_container.rend();
		}

		const_reverse_iterator crend() const{

			return _M_tree_container.crend();
		}

		bool empty() const{

			return _M_tree_container.empty();
		}

		size_type size() const{

			return _M_tree_container.size();
		}

		size_type max_size() const{

			return _M_tree_container.max_size();
		}

		void clear() noexcept{

			_M_tree_container.clear();
		}

		iterator find(const key_type& key) const{

			return _M_tree_container.find(key);
		}

		iterator lower_bound(const key_type& key) const{

			return _M_tree_container.lower_bound(key);
		}

		iterator upper_bound(const key_type& key) const{

			return _M_tree_container.upper_bound(key);
		}

		naive::pair<iterator,iterator> equal_range(const key_type& key) const {

			return _M_tree_container.equal_range(key);
		}

		naive::pair<iterator,bool> insert( const value_type& value ){

			naive::pair<typename _TreeContainer::iterator,bool> _t_pair=_M_tree_container.insert_unique(value);

			return naive::pair<iterator,bool>(_t_pair.first,_t_pair.second);
		}

		naive::pair<iterator,bool> insert( value_type&& value ){

			naive::pair<typename _TreeContainer::iterator,bool> _t_pair=_M_tree_container.insert_unique(naive::move(value));

			return naive::pair<iterator,bool>(_t_pair.first,_t_pair.second);
		}

		iterator insert(const_iterator hint,const value_type& value){

			return _M_tree_container.insert_unique(hint,value);
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last) {
			_M_tree_container.insert_unique(first, last);
		}

		void insert(const_iterator first, const_iterator last) {
			_M_tree_container.insert_unique(first, last);
		}
		void insert(const value_type* first, const value_type* last) {
			_M_tree_container.insert_unique(first, last);
		}

		void insert( std::initializer_list<value_type> ilist ){

			insert(ilist.begin(),ilist.end());
		}

		iterator erase(const_iterator pos ){

			return _M_tree_container.erase(pos);
		}

		size_type erase( const key_type& key ){

			_M_tree_container.erase(key);
		}

		iterator erase(iterator first, iterator last) {

			return _M_tree_container.erase(first,last);
		}
	};


	template <class _Key, class _Compare, class _Alloc>
	inline bool operator==(const Set<_Key,_Compare,_Alloc>& lhs,
						   const Set<_Key,_Compare,_Alloc>& rhs) {

		return lhs._M_tree_container == rhs._M_tree_container;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator<(const Set<_Key,_Compare,_Alloc>& lhs,
						  const Set<_Key,_Compare,_Alloc>& rhs) {
		return lhs._M_tree_container < rhs._M_tree_container;
	}


	template <class _Key, class _Compare, class _Alloc>
	inline bool operator!=(const Set<_Key,_Compare,_Alloc>& lhs,
                       const Set<_Key,_Compare,_Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator>(const Set<_Key,_Compare,_Alloc>& lhs,
                      const Set<_Key,_Compare,_Alloc>& rhs) {
		return rhs < lhs;
	}

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator<=(const Set<_Key,_Compare,_Alloc>& lhs,
                       const Set<_Key,_Compare,_Alloc>& rhs) {
		return !(rhs < lhs);
	}

	template <class _Key, class _Compare, class _Alloc>
	inline bool operator>=(const Set<_Key,_Compare,_Alloc>& lhs,
                       const Set<_Key,_Compare,_Alloc>& rhs) {
		return !(lhs < rhs);
	}

	/*
	template <class _Key, class _Compare, class _Alloc>
	inline void swap(Set<_Key,_Compare,_Alloc>& lhs,
                 Set<_Key,_Compare,_Alloc>& rhs) {
		lhs.swap(rhs);
	}*/
}




#endif //NAIVE_STL_SET_H
