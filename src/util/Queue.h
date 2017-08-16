//
// Created by Shuai on 2017/8/16.
//

#ifndef NAIVE_STL_QUEUE_H
#define NAIVE_STL_QUEUE_H

#include "Deque.h"
//#include <exception>
namespace naive{

	template <typename T,typename _CONTAINER=naive::Deque<T>>
	class Queue{

	public:
		typedef typename _CONTAINER::value_type value_type;
		typedef typename _CONTAINER::size_type size_type;
		typedef typename _CONTAINER::reference reference;
		typedef typename _CONTAINER::const_reference const_reference;

	protected:
		_CONTAINER _container;

	public:

		Queue() noexcept:_container() {}

		//copy-constructor;
		Queue(const Queue& _que):_container(_que._container){}

		//move-constructor;
		Queue(Queue&& _que) noexcept :_container(std::move(_que._container)){}

		explicit Queue(const _CONTAINER& _c):_container(_c){}

		explicit Queue(_CONTAINER&& _c) noexcept :_container(std::move(_c)){}

		Queue& operator=(const Queue& _que){
			_container=_que._container;
			return *this;
		}

		Queue& operator=(Queue&& _que) noexcept {
			_container=std::move(_que._container);
			return *this;
		}

		bool empty(){
			return _container.empty();
		}

		size_type size() const{
			return _container.size();
		}

		reference front(){
			return _container.front();
		}

		const_reference front() const{
			return _container.front();
		}

		reference back(){
			return _container.back();
		}

		const_reference back() const{
			return _container.back();
		}

		void push(const value_type& value){
			_container.push_back(value);
		}

		void pop(){
			_container.pop_front();
		}
	};
}


#endif //NAIVE_STL_QUEUE_H
