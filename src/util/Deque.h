//
// Created by 刘帅 on 2017/8/12.
//

#ifndef NAIVE_STL_DEQUE_H
#define NAIVE_STL_DEQUE_H


#include "../stl_alloc.h"
#include "../stl_uninitialized.h"
#include "../stl_alloc.h"

namespace naive {

	// Define the buffer's size;
	inline std::size_t _deque_buf_size(std::size_t _buf_size, std::size_t _elem_size) {

		return _elem_size > _buf_size ? 1 : static_cast<std::size_t>(_buf_size / _elem_size);
	}

	template <typename _T, typename _Ref, typename _Ptr>
	class _Deque_iterator {
	private:
		static constexpr std::size_t _M_BUFF_SIZE = 512;// use const expression in order to init static memnber in-ner class;
	public:
		typedef _T value_type;
		typedef _Ptr pointer;
		typedef _Ref reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef naive::random_access_iterator_tag iterator_category;
		typedef _Deque_iterator<_T, _T&, _T*> iterator;
		typedef _Deque_iterator<_T, const _T&, const _T*> const_iterator;
		typedef _T** _Map_pointer;

		typedef _Deque_iterator _Self;

		_T* _M_cur;//point to the current element in a buffer;
		_T* _M_first;//point to the first element in a buffer;
		_T* _M_last;//point to the position after the last elements in a buffer;

		/*Note: the map is a continuous memory with type T**, so every element so called node in the map is T*
		* type so that the node can point to a buffer; There use T** to define _M_node because it can use
		* +/- to select in the map and *_M_node can get a address of a buffer that current iterator point;
		*/
		_Map_pointer _M_node;

		//For a instance, if T=int, the default buffer size=(512/4)=128 in 32bit machine;
		static size_type _M_buffer_size() {
			return _deque_buf_size(_M_BUFF_SIZE, sizeof(_T));
		}

		//Constructors;
		_Deque_iterator() :_M_cur(nullptr), _M_first(nullptr), _M_last(nullptr), _M_node(nullptr) {}

		_Deque_iterator(_T* _cur, _Map_pointer _node) :_M_cur(_cur), _M_first(*_node), _M_last(*_node + _M_buffer_size()), _M_node(_node) {}

		_Deque_iterator(const iterator& _it) :_M_cur(_it._M_cur), _M_first(_it._M_first), _M_last(_it._M_last), _M_node(_it._M_node) {}

		void _M_set_node(_Map_pointer _new_node) {
			_M_node = _new_node;
			_M_first = *_new_node;
			_M_last = _M_first + static_cast<difference_type>(_M_buffer_size());
		}

		/*
		 * Note: the iterator of Deque need to simulate all the behaviours of primitive pointer;
		 *
		 */
		reference operator*() const {
			return *_M_cur;
		}

		pointer operator->() const {
			return _M_cur;
		}

		//expression ++it;
		_Self& operator++() {
			++_M_cur;
			if (_M_cur == _M_last) {// if equal to the position after the last one, then go to the next node;
				_M_set_node(_M_node + 1);
				_M_cur = _M_first;
			}
			return *this;
		}

		//expression it++;
		_Self operator++(int) {

			_Self _Tmp = *this;
			++(*this);
			return _Tmp;
		}

		//expression --it;
		_Self& operator--() {
			if (_M_cur == _M_first) {
				_M_set_node(_M_node - 1);
				_M_cur = _M_last;
			}
			--_M_cur;
			return *this;
		}

		//expression it--;
		_Self operator--(int) {
			_Self _Tmp = *this;
			--(*this);
			return _Tmp;
		}

		// expression it += n;
		_Self& operator+=(difference_type _n) {

			//(_M_cur-_M_first) means the memory has been used in current buffer because _n>0 or _n<o both is possible;
			difference_type _Offset = _n + (_M_cur - _M_first);
			if (_Offset >= 0 && _Offset < static_cast<difference_type>(_M_buffer_size())) {
				_M_cur += _n;//_Offset in range [_M_first,_M_last);
			}
			else {

				difference_type _Node_offset = 0;

				if (_Offset > 0) {
					_Node_offset = _Offset / static_cast<difference_type>(_M_buffer_size());
				}
				else {
					_Node_offset = (-(static_cast<difference_type>((-_Offset - 1)) / _M_buffer_size())) - 1;
				}

				_M_set_node(_M_node + _Node_offset);
				_M_cur = _M_first + (_Offset - _Node_offset*static_cast<difference_type>(_M_buffer_size()));

			}
			return *this;
		}

		// expression (it+n);
		_Self operator+(difference_type _n) const {
			_Self _Tmp = *this;
			return _Tmp += _n;
		}

		// expression it -= n;
		_Self& operator-=(difference_type _n) {
			return *this += -_n;
		}

		// expression (it-n);
		_Self operator-(difference_type _n) const {
			_Self _Tmp = *this;
			return _Tmp -= _n;
		}

		// expression it1-it2;
		difference_type operator-(const _Self& _it) const {
			return static_cast<difference_type>(_M_buffer_size())*(_M_node - _it._M_node - 1) +
					(_M_cur - _M_first) + (_it._M_last - _it._M_cur);
		}

		reference operator[](difference_type _n) const {
			return *(*this + _n);
		}

		bool operator==(const _Self& _x) const {
			return _M_cur == _x._M_cur;
		}

		bool operator!=(const _Self& _x) const {
			return !(*this == _x);
		}

		bool operator<(const _Self& _x) const {
			return (_M_node == _x._M_node) ?
				   (_M_cur < _x._M_cur) : (_M_node < _x._M_node);
		}

		bool operator>(const _Self& _x) const {
			return _x < *this;
		}

		bool operator<=(const _Self& _x) const {
			return !(_x < *this);
		}

		bool operator>=(const _Self& _x) const {
			return !(*this < _x);
		}
	};


	template<typename _T, typename _Alloc, std::size_t _BUFF_SIZE>
	class _Deque_alloc_base {

	public:
		//typedef std::size_t size_type;
		typedef _Alloc allocator_type;

		//Use rebind to transform _T to _T*;
		using map_alloctor_type = typename _Alloc:: template rebind<_T*>::other;

		allocator_type get_allocator() const {
			return _M_node_allocator;
		}

		explicit _Deque_alloc_base(const allocator_type& _a) :_M_node_allocator(_a),
													 _M_map_allocator(_a),_M_map(nullptr), _M_map_size(0) {
		}

	protected:
		allocator_type _M_node_allocator;//allocator for nodes in map(return T* stands a real memory point to a buffer);
		map_alloctor_type _M_map_allocator;//allocator for map;

		_T** _M_map;// the map is a continuous memory;
		std::size_t _M_map_size;//the size of map;

		// A node in the map point a buffer that size of 512/sizeof(T) ;
		_T* _M_allocate_node() {
			return _M_node_allocator.allocate(_deque_buf_size(_BUFF_SIZE, sizeof(_T)));
		}

		void _M_deallocate_node(_T* _p) {
			_M_node_allocator.deallocate(_p, _deque_buf_size(_BUFF_SIZE, sizeof(_T)));
		}

		// Allocate a map with n size;
		_T** _M_allocate_map(std::size_t _n) {
			return _M_map_allocator.allocate(_n);
		}

		void _M_deallocate_map(_T** _p, std::size_t _n) {
			_M_map_allocator.deallocate(_p, _n);
		}

	};


	template <class _T, class _Alloc, std::size_t _BUFF_SIZE>
	class _Deque_base : protected _Deque_alloc_base<_T, _Alloc, _BUFF_SIZE> {

	private:
		const std::size_t MINIMUM_SIZE_OF_MAP = 8;

	public:
		typedef _Deque_alloc_base<_T, _Alloc, _BUFF_SIZE> _MyBase;
		typedef typename _MyBase::allocator_type allocator_type;
		typedef _Deque_iterator<_T, _T&, _T*> iterator;
		typedef _Deque_iterator<_T, const _T&, const _T*> const_iterator;

		explicit _Deque_base(const allocator_type& _alloc) :_MyBase(_alloc), _M_start(), _M_finish() {}

		_Deque_base(const allocator_type& _alloc, std::size_t _num_of_elements) :_MyBase(_alloc), _M_start(), _M_finish() {
			_M_init_map(_num_of_elements);//init the map in the base class of Deque.h;
		}

		_Deque_base(const _Deque_base&) = delete;

		_Deque_base(const _Deque_base&&) = delete;

		_Deque_base& operator=(const _Deque_base&) = delete;

		_Deque_base& operator=(const _Deque_base&&) = delete;

		~_Deque_base() {
			_M_destroy_nodes(_M_start._M_node, _M_finish._M_node + 1);
			_M_deallocate_map(_M_map, _M_map_size);
		}

	protected:
		using _MyBase::_M_map_size;
		using _MyBase::_M_map;
		using _MyBase::_M_allocate_node;
		using _MyBase::_M_deallocate_node;
		using _MyBase::_M_allocate_map;
		using _MyBase::_M_deallocate_map;


		void _M_init_map(std::size_t _num_of_elements);
		void _M_create_nodes(_T** _t_start, _T** _t_finish);
		void _M_destroy_nodes(_T** _t_start, _T** _t_curr);

	protected:
		iterator _M_start;//point to the first node in the map;
		iterator _M_finish;//point to the last node in the map;
	};

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_init_map(std::size_t _num_of_elements) {

		// According to the number of elements passed by constructor to create the number of node in the map;
		// The minimum number of node is 1;
		std::size_t _Num_nodes = (_num_of_elements / _deque_buf_size(_BUFF_SIZE, sizeof(_T))) + 1;

		// If num_node< 8 then the default size of map is 8;
		// Otherwise, the size of map is the number of node plus 2;
		_M_map_size = naive::max(MINIMUM_SIZE_OF_MAP, _Num_nodes + 2);

		// Allocate the memory of map;
		_M_map = _M_allocate_map(_M_map_size);

		// Set the _N_start and _N_finish to the middle of map;
		// Don't use expression (_M_map + _M_map_size / 2),because we need keep the
		// same free nodes in both previous and backward position of _t_start and _t_finish;
		_T** _t_start = _M_map + (_M_map_size - _Num_nodes) / 2;
		_T** _t_finish = _t_start + _Num_nodes;

		try {
			_M_create_nodes(_t_start, _t_finish);
		}
		catch (...) {
			//commit or rollback;
			_M_deallocate_map(_M_map, _M_map_size);
			_M_map=nullptr;
			_M_map_size=0;
		}

		//set iterator _M_start and _M_finish;
		_M_start._M_set_node(_t_start);
		_M_finish._M_set_node(_t_finish - 1);

		_M_start._M_cur = _M_start._M_first;
		_M_finish._M_cur = _M_finish._M_first + _num_of_elements % _deque_buf_size(_BUFF_SIZE, sizeof(_T));
	}

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_create_nodes(_T ** _t_start, _T ** _t_finish) {

		_T** _t_curr = _t_start;

		try {
			for (; _t_curr < _t_finish; ++_t_curr) {
				*_t_curr = _M_allocate_node();//make the node point to the buffer, every node point to the same size of buffer;
			}
		}
		catch (...) {
			//commit or rollback;
			_M_destroy_nodes(_t_start, _t_curr);
		}

	}

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_destroy_nodes(_T ** _t_start, _T ** _t_curr) {

		_T** _t_begin= _t_start;

		for (; _t_begin < _t_curr; ++_t_begin) {
			_M_deallocate_node(*_t_begin);
		}
	}

	//class Double-ended queue;
	template <typename T, typename Alloc = naive::allocator<T>, std::size_t _BUFF_SIZE = 512 >
	class Deque :public _Deque_base<T, Alloc, _BUFF_SIZE> {
	private:
		typedef _Deque_base<T, Alloc, _BUFF_SIZE> _Base;
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename _Base::iterator       iterator;
		typedef typename _Base::const_iterator const_iterator;

		typedef typename _Base::allocator_type allocator_type;

		allocator_type get_allocator() const {
			return _Base::get_allocator();
		}

	protected:
		typedef pointer* _Map_pointer;
		static std::size_t _M_buffer_size() {
			return _deque_buf_size(_BUFF_SIZE, sizeof(T));
		}
		void _M_fill_initialize(const value_type& value);

	public:
		using _Base::_M_init_map;
		using _Base::_M_create_nodes;
		using _Base::_M_destroy_nodes;
		using _Base::_M_allocate_node;
		using _Base::_M_allocate_map;
		using _Base::_M_deallocate_node;
		using _Base::_M_deallocate_map;

		using _Base::_M_map_size;
		using _Base::_M_map;
		using _Base::_M_start;
		using _Base::_M_finish;

	public:

		explicit Deque(const allocator_type& alloc = allocator_type())
				: _Base(alloc, 0) {}

		//Deque(const allocator_type& alloc = allocator_type(),const Deque& _dqe): _Base(alloc){}

		Deque(size_type n, const value_type& value, const allocator_type alloc = allocator_type()) :_Base(alloc, n) {
			//naive::un
			_M_fill_initialize(value);
		}

		iterator begin() {
			return _M_start;
		}

		iterator begin() const {
			return _M_start;
		}

		const_iterator cbegin() const {
			return _M_start;
		}

		iterator end() {
			return _M_finish;
		}

		iterator end() const {
			return _M_finish;
		}

		const_iterator cend() const {
			return _M_finish;
		}

		size_type size() const noexcept {
			return static_cast<size_type >(_M_finish - _M_start);
		}

		static size_type max_size() noexcept {
			return static_cast<size_type>(-1);
		}

		reference operator[](std::size_t n){
			return _M_start[static_cast<difference_type>(n)];
		}

		const_reference operator[](std::size_t n) const{
			return _M_start[static_cast<difference_type>(n)];
		}

		reference front(){
			return *_M_start;
		}

		const_reference front() const{
			return *_M_start;
		}

		reference back(){
			return *(_M_finish._M_cur-1);
		}

		const_reference back() const{
			return *(_M_finish._M_cur-1);
		}

		bool empty() const{
			return _M_finish==_M_start;
		}

		void push_back(const value_type& value) {
			/*
			* Note: while the push_back operation finished, the _M_cur point
			* to the position after the new element;
			*/
			if (_M_finish._M_cur != _M_finish._M_last - 1) {
				::construct(_M_finish._M_cur, value);// the iterator point a free position in buffer;
				++_M_finish._M_cur;
			}
			else {//_M_finish._M_cur == _M_finish._M_last -1;
				_push_back_aux(value);
			}
		}

		void push_back(value_type&& value){
			push_back(std::move(value));
		}

		void pop_back(){

			// There at least have one element in the buffer;
			if(_M_finish._M_cur!=_M_finish._M_first){
				// The inner buffer iterator _M_cur point to a free position in buffer;
				// So need to decrease the _M_cur firstly;
				--_M_finish._M_cur;
				::destroy(_M_finish._M_cur);
			}else{
				_pop_back_aux();//No elements in the buffer;
			}
		}

		void push_front(const value_type& value){

			/*
			* Note: while the push_front operation finished, the _M_cur point
			* to the new element in the buffer;
			*/
			if(_M_start._M_cur!=_M_start._M_first){
				::construct(_M_start._M_cur-1,value);
				--_M_start._M_cur;
			}else{
				_push_front_aux(value);
			}
		}

		void push_front(value_type&& value) {
				push_front(std::move(value));
		}

		void pop_front(){

			if(_M_start._M_cur!=_M_start._M_last-1){
				::destroy(_M_start._M_cur);
				++_M_start._M_cur;
			} else{// there has only a element in the buffer;
				_pop_front_aux();
			}
		}

		void clear();

		void erase(iterator pos);

		iterator erase(iterator first,iterator last);

		iterator insert(iterator pos, const value_type& value);

	protected:
		void _push_back_aux(const value_type& _value);

		void _pop_back_aux();

		void _push_front_aux(const value_type& _value);

		void _pop_front_aux();

		void _M_reallocate_map(std::size_t _nodes_to_add,bool _add_at_front);

		void _M_reserve_map_at_back(size_type _nodes_to_add = 1){

			//the value of_M_map_size-(_M_finish._M_node-_M_map) equal 1 stands there is no free node in the back of map;
			if((_nodes_to_add+1)>_M_map_size-(_M_finish._M_node-_M_map)){
				_M_reallocate_map(_nodes_to_add,false);
			}
		}

		void _M_reserve_map_at_front(std::size_t _nodes_to_add = 1){

			// If no free node in the previous of _M_start;
			if(_nodes_to_add> static_cast<std::size_t >(_M_start._M_node-_M_map)){
				_M_reallocate_map(_nodes_to_add,true);
			}
		}
	};

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_M_fill_initialize(const value_type & value) {

		_Map_pointer _cur = _M_start._M_node;

		try {
			// init nodes, the global function just need iterator type, so *_curr is ok;
			for (; _cur < _M_finish._M_node; ++_cur) {
				naive::uninitialized_fill(*_cur, *_cur + _M_buffer_size(), value);
			}
			naive::uninitialized_fill(_M_finish._M_first, _M_finish._M_cur, value);
		}
		catch (...) {
			::destroy(_M_start, iterator(*_cur, _cur));
		}

	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_M_reallocate_map(std::size_t _nodes_to_add, bool _add_at_front){

		std::size_t _used_num_of_node=_M_finish._M_node-_M_start._M_node+1;//the number of used nodes in the map;
		std::size_t _new_num_of_node=_used_num_of_node+_nodes_to_add;

		_Map_pointer _new_t_start=nullptr;

		if(_M_map_size>2*_new_num_of_node){

			_new_t_start=(_M_map+(_M_map_size - _new_num_of_node)/2)+(_add_at_front? _nodes_to_add:0);

			if(_new_t_start<_M_start._M_node) {
				naive::copy(_M_start._M_node, _M_finish._M_node + 1, _new_t_start);
			}else {
				naive::copy_backward(_M_start._M_node, _M_finish._M_node + 1, _new_t_start + _used_num_of_node);
			}
		}else{

			//allocate a new memory for map;
			std::size_t _new_t_map_size=_M_map_size+::naive::max(_M_map_size,_nodes_to_add)+2;
			_Map_pointer _new_t_map=_M_allocate_map(_new_t_map_size);

			_new_t_start=_new_t_map+(_new_t_map_size-_new_num_of_node)/2 +(_add_at_front? _nodes_to_add:0);
			naive::copy(_M_start._M_node,_M_finish._M_node,_new_t_start);

			_M_deallocate_map(_M_start._M_node,_M_map_size);//deallocate the old map;

			_M_map=_new_t_map;
			_M_map_size=_new_t_map_size;
		}

		_M_start._M_set_node(_new_t_start);
		_M_finish._M_set_node(_new_t_start+_used_num_of_node-1);

	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_push_back_aux(const value_type & _value){

		value_type _t_value = _value;

		// Check if there has free node in the map;
		_M_reserve_map_at_back();

		*(_M_finish._M_node+1)=_M_allocate_node();//allocate a new node in the map;

		try {

			::construct(_M_finish._M_cur,_t_value);
			_M_finish._M_set_node(_M_finish._M_node+1);//point to the next node;
			_M_finish._M_cur=_M_finish._M_first;

		}catch (...){
			_M_deallocate_node(*(_M_finish._M_node+1));
		}
	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_pop_back_aux(){
		//
		_M_deallocate_node(_M_finish._M_first);
		_M_finish._M_set_node(_M_finish._M_node-1);
		_M_finish._M_cur=_M_finish._M_last-1;
		::destroy(_M_finish._M_cur);//destroy a element in the buffer point by the previous node;
	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_push_front_aux(const value_type & _value){

		value_type _t_value=_value;
		_M_reserve_map_at_front();
		*(_M_start._M_node-1)=_M_allocate_node();
		try{

			_M_start._M_set_node(_M_start._M_node-1);
			_M_start._M_cur=_M_start._M_last-1;
			::construct(_M_start._M_cur,_t_value);

		}catch (...){
			++_M_start;
			_M_deallocate_node(*(_M_start._M_node-1));
		}
	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::_pop_front_aux(){

		::destroy(_M_start._M_cur);

		_M_deallocate_node(_M_start._M_first);
		_M_start._M_set_node(_M_start._M_node+1);
		_M_start._M_cur=_M_start._M_first;
	}

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void Deque<T, Alloc, _BUFF_SIZE>::clear(){

		difference_type _t_num_nodes=_M_finish._M_node-_M_start._M_node+1;

		/*
		 * Note: In the buffers point by _M_start and _M_finish may has free some positions;
		 * The buffers in the range (_M_start,_M_finish) there has the same number of elements with
		 * buffer size(512/sizeof(T));
		 *
		 */
		if(_t_num_nodes>=3) {

			for (_Map_pointer _t_node=_M_start._M_node+1; _t_node < _M_finish._M_node; ++_t_node) {
				::destroy(*_t_node, *_t_node + _M_buffer_size());
				_M_deallocate_node(*_t_node);
			}

		}else{

			if(_t_num_nodes==2){

				::destroy(_M_start._M_cur,_M_start._M_last);
				::destroy(_M_finish._M_first,_M_finish._M_cur);
				_M_deallocate_node(_M_finish._M_first);
			}

			if(_t_num_nodes==1){

				::destroy(_M_start._M_cur,_M_finish._M_cur);
			}
		}

		//_M_finish._M_set_node(_M_start._M_node);
		_M_finish=_M_start;
	}

}

#endif //NAIVE_STL_DEQUE_H
