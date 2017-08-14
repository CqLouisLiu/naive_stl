#ifndef _NAIVE_STL_VECTOR_H
#define _NAIVE_STL_VECTOR_H
#include <utility>
#include "memory.h"
#include <iostream>
#include <cassert>
namespace naive {

	/*Suppose not use static interfaces to implemnt.
	*All memory operations are in _Vector_base;
	*/
	template<typename _T, typename _Alloc>
	class _Vector_base {

	public:

		typedef _Alloc allocator_type;//naive::allocator<_T>;
		allocator_type get_allocator() const {
			return _data_allocator;
		}

		_Vector_base(const allocator_type& _alloc) :_start(nullptr), _finish(nullptr),
			_end_of_storage(nullptr) {}

		_Vector_base(size_t n, const allocator_type& _alloc) :_data_allocator(_alloc), _start(nullptr), _finish(nullptr),
			_end_of_storage(nullptr) {
			_start = _data_allocator.allocate(n);
			_finish = _start;//just allocate n size of memory, not init the memory;
			_end_of_storage = _start + n;
		}

		~_Vector_base() noexcept {
			_data_allocator.deallocate(_start, static_cast<size_t>(_end_of_storage - _start));
		}

	protected:
		allocator_type _data_allocator;
		_T* _start;
		_T* _finish;
		_T* _end_of_storage;

		_T* _allocate(size_t _n) {
			return _data_allocator.allocate(_n);
		}

		void _deallocate(_T* _p, size_t n) {
			if (_p != nullptr)
				_data_allocator.deallocate(_p, n);
		}
	};

	template<typename _T, typename _Alloc = naive::allocator<_T>>
	class Vector :protected _Vector_base<_T, _Alloc> {

	private:
		typedef _Vector_base<_T, _Alloc> _MyBase;
	public:
		typedef _T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type* iterator;//Vector using a continous memory,so the pointer can work well;
		typedef const value_type* const_iterator;
		typedef naive::random_access_iterator_tag iterator_category;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef typename _MyBase::allocator_type allocator_type;

		allocator_type get_allocator() const {
			return _MyBase::get_allocator();
		}

	protected:
		using _MyBase::_start;
		using _MyBase::_finish;
		using _MyBase::_end_of_storage;
		using _MyBase::_allocate;
		using _MyBase::_deallocate;
		using _MyBase::_data_allocator;

		void _insert_aux(iterator _position, const _T& _value);

		iterator _allocate_and_copy(size_type n, const_iterator _first, const_iterator _last) {

			iterator _result = _allocate(n);

			//commit or rollback;
			try {
				naive::uninitialized_copy(_first, _last, _result);
				return _result;
			}
			catch (...) {
				_deallocate(_result, n);
				throw;
			}
		}

	public:


		//The construtors of Vector;
		explicit Vector(const allocator_type& __a = allocator_type()) noexcept
			: _MyBase(__a) {}

		explicit Vector(size_type n) noexcept : _MyBase(n, allocator_type()) {
			_finish = naive::uninitialized_fill_n(_start, n, value_type());
		}

		Vector(size_type n, const _T& value) noexcept : _MyBase(n, allocator_type()) {
			_finish = naive::uninitialized_fill_n(_start, n, value);
		}

		Vector(std::initializer_list<_T> init,
			const allocator_type& alloc = allocator_type()) :_MyBase(init.size(), alloc) {
			_finish = naive::uninitialized_copy(init.begin(), init.end(), _start);
		}

		template<typename InputIt>
		void __initialize_aux(InputIt first, InputIt last, naive::false_type) {

		}

		template<typename InputIt>
		void __initialize_aux(InputIt first, InputIt last, naive::true_type) {

		}

		template <typename InputIt>
		Vector(InputIt first, InputIt last, const allocator_type& __a = allocator_type()) :_MyBase(__a) {
			//typedef typename naive::is_integral_type<std::is_integral_type<InputIt>::value>::is_integral_type is_integral_type;
			//接下来根据是不是int具体处理;

		}

		/*
		* Becasue we set allcate memory functions in _Vector_base, so copy constructor should as following;
		* 1)get base alloctor from rhs;
		* 2)get size from rhs;
		* 3)use alloctor and size to init current Vector;
		*/
		Vector(Vector& rhs) noexcept:_MyBase(rhs.size(), rhs.get_allocator()) {
			_finish = naive::uninitialized_copy(rhs.begin(), rhs.end(), _start);
		}

		//move-constructor;
		Vector(Vector&& rhs) noexcept : _MyBase(rhs.get_allocator()) {

			std::swap(_start, rhs._start);
			std::swap(_finish, rhs._finish);
			std::swap(_end_of_storage, rhs._end_of_storage);
			_data_allocator = rhs.get_allocator();
			rhs._start = rhs._finish = rhs._end_of_storage = nullptr;
		}

		//copy-swap, it determine by the object if it has move-constructor;
		Vector& operator= (const Vector rhs) noexcept {
			std::swap(*this, rhs);
			return *this;
		}

		Vector& operator= (const Vector&& rhs) noexcept {
			std::swap(_start, rhs._start);
			std::swap(_finish, rhs._finish);
			std::swap(_end_of_storage, rhs._end_of_storage);
			_data_allocator = rhs.get_allocator();

			return *this;
		}
		
		~Vector() {
			::destroy(_start, _finish);
		}

		iterator begin() noexcept {
			return _start;
		}

		const_iterator begin() const noexcept {
			return _start;
		}

		const_iterator cbegin() const noexcept {
			return _start;
		}

		iterator end() noexcept {
			return _finish;
		}

		const_iterator end() const noexcept {
			return _finish;
		}

		const_iterator cend() const noexcept {
			return _finish;
		}

		size_type size() const {
			return static_cast<size_type>(_finish - _start);
		}

		size_type capacity() const {
			return static_cast<size_type>(_end_of_storage - _start);
		}

		bool empty() const {
			return _start == _finish;
		}

		reference operator[](size_type n) {
			return *(_start + n);
		}
		const_reference operator[](size_type n) const {
			return *(_start + n);
		}

		reference front() {
			return *begin();
		}

		reference back() {
			return *(end() - 1);
		}

		reference& at(size_type pos) {

			if (pos >= size()) {
				throw std::out_of_range("out of range at function Vector<T,Alloc>::at(size_type pos)");
			}
			else
				return *(_start + pos);
		}

		_T* data() noexcept {
			return &(front());
		}


		void push_back(const _T& x) {

			if (_finish != _end_of_storage) {
				::construct(_finish, x);
				_finish++;
			}
			else {
				_insert_aux(end(), x);//_finish==_end_of_storage;
			}
		}

		void pop_back() {
			--_finish;
			::destroy(_finish);
		}

		void reserve(size_type n) {

			if (capacity() > n)
				return;
			const size_type _old_size = size();
			iterator _temp = _allocate_and_copy(n, _start, _finish);
			::destroy(_start, _finish);
			_deallocate(_start, _end_of_storage - _start);

			_start = _temp;
			_finish = _temp + _old_size;
			_end_of_storage = _start + n;
		}

		void insert(iterator pos, size_type count, const _T& value);

		iterator insert(const_iterator pos, const _T& value) {

			size_type elems_before = pos - begin();

			if (_finish != _end_of_storage&& pos == end())
				push_back(value);
			else {
				_insert_aux(_finish, value);
			}

			return begin() + elems_before;
		}

		template< class InputIt >
		void insert(iterator pos, InputIt first, InputIt last);


		iterator erase(iterator pos) {

			if ((pos + 1) != end()) {
				naive::copy(pos + 1, _finish, pos);
			}
			else {
				throw std::out_of_range("the end() iterator cannot be used as a value for pos.");
			}

			_finish--;
			::destroy(_finish);

			return pos;

		}


		//Invalidates iterators and references at or after the point of the erase;
		iterator erase(iterator first, iterator last) {

			iterator _temp = naive::copy(last, _finish, first);

			::destroy(_temp, _finish);

			_finish = _finish - (last - first);

			return first;
		}

		void clear() {
			erase(begin(), end());
		}


	};

	template<typename _T, typename _Alloc>
	inline void Vector<_T, _Alloc>::_insert_aux(iterator _position, const _T & _value) {

		
		if (_finish == _end_of_storage) {//No enough allocated memory.

			const size_type _Old_size = size();//Now, the capacity()==size();

			const size_type _New_size = (_Old_size == 0 ? 1 : 2 * _Old_size);

			iterator _new_start = _allocate(_New_size);

			iterator _new_finish = _new_start;

			try {
				_new_finish = naive::uninitialized_copy(_start, _position, _new_start);
				::construct(_new_finish, _value);
				++_new_finish;
				_new_finish = naive::uninitialized_copy(_position, _finish, _new_finish);
			}
			catch (...) {
				//or rollback;
				::destroy(_new_start, _new_finish);
				_deallocate(_new_start, _New_size);
			}

			destroy(begin(), end());
			_deallocate(begin(), _end_of_storage - _start);

			_start = _new_start;
			_finish = _new_finish;
			_end_of_storage = _new_start + _New_size;
		}
		else {//deal with insert: has enough momory;

			::construct(_finish, _T());
			iterator _Old_finish = _finish;
			++_finish;

			_T _Value_copy = std::move(_value);

			naive::copy_backward(_position, _Old_finish, _finish);
			*_position = _Value_copy;

		}
	}

	template<typename _T, typename _Alloc>
	inline void Vector<_T, _Alloc>::insert(iterator pos, size_type count, const _T & value) {

		if (count != 0) {

			const size_type _free_elems = static_cast<size_type>(_end_of_storage - _finish);

			//There are enough free memory to storage the count size value;
			if (_free_elems >= count) {

				_T _value = std::move(value);

				iterator _old_finish = _finish;

				naive::uninitialized_fill_n(_finish, count,_T());

				_finish += count;

				iterator _d_last = naive::copy_backward(pos, _old_finish, _finish);
				naive::fill(pos, _d_last, _value);
															
			}
			else { //There are no enough free memory to storage the number of count objects;
				const size_type _old_size = size();
				const size_type _new_size = 2 * _old_size;

				iterator _new_start = _allocate(_new_size);
				iterator _new_finish = _new_start;

				try {
					_new_finish = naive::uninitialized_copy(_start, pos, _new_start);
					_new_finish = naive::uninitialized_fill_n(_new_finish, count, value);
					_new_finish = naive::uninitialized_copy(pos, _finish, _new_finish);

				}
				catch (...) {
					::destroy(_new_start, _new_finish);
					_deallocate(_new_start, _new_size);
				}

				_start = _new_start;
				_finish = _new_finish;
				_end_of_storage = _new_start + _new_size;
			}

		}

	}

	template<typename _T, typename _Alloc>
	template<class InputIt>
	inline void Vector<_T, _Alloc>::insert(iterator pos, InputIt first, InputIt last){

	}

}


#endif