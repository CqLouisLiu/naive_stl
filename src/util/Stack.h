//
// Created by 刘帅 on 2017/8/12.
//

#ifndef NAIVE_STL_STACK_H
#define NAIVE_STL_STACK_H

#include "Deque.h"

namespace naive {

	template<typename T, typename _CONTAINER=naive::Deque<T>>
	class Stack {

	protected:
		_CONTAINER _container;

	public:
		typedef typename _CONTAINER::value_type value_type;
		typedef typename _CONTAINER::size_type size_type;
		typedef typename _CONTAINER::reference reference;
		typedef typename _CONTAINER::const_reference const_reference;



	public:

		Stack() noexcept: _container() {}

		//copy-constructor;
		Stack(const Stack& _stk):_container(_stk._container){}

		//move-constructor;
		Stack(Stack&& _stk) noexcept :_container(std::move(_stk._container)){}

		explicit Stack(const _CONTAINER &_c): _container(_c) {}

		explicit Stack(_CONTAINER&& _c) noexcept :_container(std::move(_c)){}

		Stack& operator=(const Stack& _stk){
			_container=_stk._container;
			return *this;
		}

		Stack& operator=(Stack&& _stk) noexcept {
			_container=std::move(_stk._container);
			return *this;
		}

		bool empty() const {
			return _container.empty();
		}

		size_type size() const {
			return _container.size();
		}

		reference top() {
			return _container.back();
		}

		const_reference top() const {
			return _container.back();
		}

		void push(const value_type &value) {
			_container.push_back(value);
		}

		void pop() {
			_container.pop_back();
		}

	};
}

#endif //NAIVE_STL_STACK_H
