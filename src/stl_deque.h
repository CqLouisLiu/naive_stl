#ifndef _NAIVE_STL_DEQUE_H
#define _NAIVE_STL_DEQUE_H
#include "stl_alloc.h"
#include "stl_uninitialized.h"
#include <iostream>

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

		_T* _M_cur;//point to the current elememt in a buffer;
		_T* _M_first;//point to the first element in a buffer;
		_T* _M_last;//point to the position after the last elements in a buffer;

		/*Note: the map is a continuous memory with type T**, so every elemnt so called node in the map is T*
		* type so that the node can point to a buffer; There use T** to define _M_node because it can use
		* +/- to select in the map and *_M_node can get a address of a buffer that current iterator point;
		*/
		_Map_pointer _M_node;

		//For a instance, if T=int, the default buffer size=(512/4)=128;
		static size_type _M_buffer_size() {
			return _deque_buf_size(_M_BUFF_SIZE, sizeof(_T));
		}

		//Constructor;
		_Deque_iterator() :_M_cur(nullptr), _M_first(nullptr), _M_last(nullptr), _M_node(nullptr) {}

		_Deque_iterator(_T* _cur, _Map_pointer _node) :_M_cur(_cur), _M_first(*_node), _M_last(*_node + _M_buffer_size()), _M_node(_node) {}

		_Deque_iterator(const iterator& _it) :_M_cur(_it._M_cur), _M_first(_it._M_first), _M_last(_it._M_last), _M_node(_it._M_node) {}

		void _M_set_node(_Map_pointer _new_node) {
			_M_node = _new_node;
			_M_first = *_new_node;
			_M_last = _M_first + static_cast<difference_type>(_M_buffer_size());
		}


		reference operator*() const {
			return *_M_cur;
		}

		pointer operator->() const {
			return _M_cur;
		}

		_Self& operator++() {
			++_M_cur;
			if (_M_cur == _M_last) {
				_M_set_node(_M_node + 1);//the next node;
				_M_cur = _M_first;
			}
			return *this;
		}

		_Self operator++(int) {

			_Self _Tmp = *this;
			++(*this);
			return _Tmp;
		}

		_Self& operator--() {
			if (_M_cur == _M_first) {
				_M_set_node(_M_node - 1);
				_M_cur = _M_last;
			}
			--_M_cur;
			return *this;
		}

		_Self operator--(int) {
			_Self _Tmp = *this;
			--(*this);
			return _Tmp;
		}

		// expression it += n;
		_Self& operator+=(difference_type _n) {

			//(_M_cur-_M_first) means has used memory in current buffer;
			//Because _n>0 or _n<o both is  ok;
			difference_type _Offset = _n + (_M_cur - _M_first);
			if (_Offset >= 0 && _Offset < static_cast<difference_type>(_M_buffer_size())) {
				_M_cur += _n;//_Offset in [_M_first,_M_last);
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
		difference_type operator-(const _Self& _it) const{
			return static_cast<difference_type>(_M_buffer_size())*(_M_node - _it._M_node - 1) + (_M_cur - _M_first) + (_it._M_last-_it._M_cur);
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
		typedef std::size_t size_type;
		typedef _Alloc allocator_type;

		//Use rebind to transform _T to _T*;
		using map_alloctor_type = typename _Alloc:: template rebind<_T*>::other;

		allocator_type get_allocator() const {
			return _M_node_allocator;
		}

		_Deque_alloc_base(const allocator_type& _a) :_M_node_allocator(_a), _M_map_allocator(_a),
													 _M_map(nullptr), _M_map_size(0) {
		}

	protected:
		allocator_type _M_node_allocator;//allocator for nodes in map(return T* stands a real memory point to a buffer);
		map_alloctor_type _M_map_allocator;//allocator for map;

		_T** _M_map;// the map is a continuous memory;
		size_type _M_map_size;//the size of map;

		_T* _M_allocate_node() {
			return _M_node_allocator.allocate(_deque_buf_size(_BUFF_SIZE, sizeof(_T)));//512/sizeof(T)kb;
		}

		void _M_deallocate_node(_T* _p) {
			_M_node_allocator.deallocate(_p, _deque_buf_size(_BUFF_SIZE, sizeof(_T)));
		}

		_T** _M_allocate_map(size_type _n) {
			return _M_map_allocator.allocate(_n);
		}

		void _M_deallocate_map(_T** _p, size_type _n){
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

		allocator_type get_allocator() const {
			return _MyBase::get_allocator();
		}

		_Deque_base(const allocator_type& _alloc):_MyBase(_alloc),_M_start(),_M_finish(){}

		_Deque_base(const allocator_type& _alloc, std::size_t _num_elems) :_MyBase(_alloc), _M_start(), _M_finish() {
			_M_init_map(_num_elems);//init the map in the base class of deque;
		}

		~_Deque_base(){
			_M_destroy_nodes(_M_start._M_node,_M_finish._M_node+1);
			_M_deallocate_map(_M_map,_M_map_size);
		}

	protected:
		using _MyBase::_M_map_size;
		using _MyBase::_M_map;
		using _MyBase::_M_allocate_node;
		using _MyBase::_M_deallocate_node;
		using _MyBase::_M_allocate_map;
		using _MyBase::_M_deallocate_map;


		void _M_init_map(std::size_t _num_elements);
		void _M_create_nodes(_T** _nstart, _T** _nfinish);
		void _M_destroy_nodes(_T** _nstart, _T** _nfinish);

	protected:
		iterator _M_start;//point to the first node in the map;
		iterator _M_finish;//point to the last node in the map;
	};

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_init_map(std::size_t _num_elements){

		std::size_t _Num_nodes = (_num_elements / _deque_buf_size(_BUFF_SIZE, sizeof(_T)))+1;

		//if num_node< 8 then default size=8;
		//otherwise, size=num_node_2;
		_M_map_size = naive::max(MINIMUM_SIZE_OF_MAP, _Num_nodes + 2);

		// allocate the _M_map_size memory as map;
		_M_map = _M_allocate_map(_M_map_size);

		//Set the _N_start and _N_finish to the middle of map;
		//Don't use expreesion (_M_map + _M_map_size / 2),because we need there are the
		//same free nodes in both previous and backward position of _N_start and _N_finish;
		_T** _N_start = _M_map + (_M_map_size - _Num_nodes) / 2;
		_T** _N_finish = _N_start + _Num_nodes;

		try {
			_M_create_nodes(_N_start, _N_finish);
		}
		catch (...) {
			//commit or rollback;
			_M_deallocate_map(_M_map, _M_map_size);
		}

		//set iterator _M_start and _M_finish;
		_M_start._M_set_node(_N_start);
		_M_finish._M_set_node(_N_finish-1);
		_M_start._M_cur = _M_start._M_first;
		_M_finish._M_cur = _M_finish._M_first + _num_elements%_deque_buf_size(_BUFF_SIZE, sizeof(_T));
	}

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_create_nodes(_T ** _nstart, _T ** _nfinish) {

		_T** _curr = nullptr;

		try {
			for (_curr = _nstart; _curr < _nfinish; ++_curr) {
				*_curr = _M_allocate_node();//make the node point to the buffer, every node point to a 64kb size of buffer;
			}
		}
		catch (...) {
			//commit or rollback;
			_M_destroy_nodes(_nstart, _curr);
		}

	}

	template<class _T, class _Alloc, std::size_t _BUFF_SIZE>
	inline void _Deque_base<_T, _Alloc, _BUFF_SIZE>::_M_destroy_nodes(_T ** _nstart, _T ** _nfinish) {

		_T** _node = nullptr;

		for (_node = _nstart; _node < _nfinish; ++_node)
			_M_deallocate_node(*_node);
	}



	//Double-ended queue;
	template <typename T, typename Alloc = naive::allocator<T>, std::size_t _BUFF_SIZE = 512 >
	class deque :public _Deque_base<T,Alloc, _BUFF_SIZE> {
	private:
		typedef _Deque_base<T, Alloc,_BUFF_SIZE> _Base;
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
		static std::size_t _M_buffer_size(){
			return _deque_buf_size(_BUFF_SIZE, sizeof(T));
		}
		void _M_fill_initialize(const value_type& value);

	protected:
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
		explicit deque(const allocator_type& alloc = allocator_type())
				: _Base(alloc, 0) {}

		deque(size_type n, const value_type& value, const allocator_type alloc = allocator_type()) :_Base(alloc, n) {
			//naive::un
			_M_fill_initialize(value);
		}

		iterator begin() {
			return _M_start;
		}

		iterator begin() const{
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
			return _M_finish - _M_start;
		}

		size_type max_size() const noexcept {
			return static_cast<size_type>(-1);
		}

	};

	template<typename T, typename Alloc, std::size_t _BUFF_SIZE>
	inline void deque<T, Alloc, _BUFF_SIZE>::_M_fill_initialize(const value_type & value){
		_Map_pointer _cur = nullptr;

		try {
			// init nodes, the globel function just need iterator type, so *_curr is ok;
			for (_cur = _M_start._M_node; _cur < _M_finish._M_node; ++_cur) {
				naive::uninitialized_fill(*_cur,*_cur+ _M_buffer_size(),value);
			}
			naive::uninitialized_fill(_M_finish._M_first, _M_finish._M_cur, value);
		}
		catch (...) {
			::destroy(_M_start,iterator(*_cur,_cur));
		}

	}
}

#endif