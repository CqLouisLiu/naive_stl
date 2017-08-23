//
// Created by Shuai on 2017/8/22.
//

#ifndef NAIVE_STL_PRIORITYQUEUE_H
#define NAIVE_STL_PRIORITYQUEUE_H

#include "Vector.h"
#include "../internal/stl_heap.h"
#include "../functional.h"


namespace naive{

	template <typename T,typename Container=naive::Vector<T>,typename Compare=naive::less<typename Container::value_type>>
	class PriorityQueue{

	public:
		typedef typename Container::value_type value_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;
		typedef typename Container::size_type size_type;
		typedef typename Container::difference_type difference_type;
		typedef Container _Container_type;
		typedef Compare _Compare_type;
		typedef PriorityQueue<T,Container,Compare> _Self_type;

	public:
		_Container_type _M_container;
		_Compare_type _M_compare;

	public:
		PriorityQueue():_M_container(),_M_compare(){}

		explicit PriorityQueue(const _Compare_type& _cmp):_M_container(),_M_compare(_cmp){}

		/*
		template<typename Allocator>
		explicit PriorityQueue(const Allocator& _alloc):_M_container(_alloc),_M_compare(){}
		*/

		template<typename InputIt>
		explicit PriorityQueue(InputIt first,InputIt last,const _Compare_type& cmp):_M_container(first,last) {

			naive::make_heap(_M_container.begin(),_M_container.end(),cmp);
		}

		bool empty() const{

			return _M_container.empty();
		}

		size_type size() const{
			return _M_container.size();
		}

		const_reference top() const{

			return _M_container.front();
		}

		void push(const value_type& value){

			try{

				_M_container.push_back(value);
				naive::push_heap(_M_container.begin(),_M_container.end(),_M_compare);
			}catch (...){
				_M_container.clear();
			}
		}

		void pop(){

			try{

				naive::pop_heap(_M_container.begin(),_M_container.end(),_M_compare);
				_M_container.pop_back();

			}catch (...){

				_M_container.clear();
			}
		}

		_Container_type & get_container(){
			return _M_container;
		}

		const _Container_type & get_container() const{
			return _M_container;
		}
	};

	template <typename T,typename Container,typename Compare>
	bool operator==(const PriorityQueue<T,Container,Compare>& p1,const PriorityQueue<T,Container,Compare>& p2){

		return p1._M_container==p2._M_container;
	}

	template <typename T, typename Container, typename Compare>
	bool operator<(const PriorityQueue<T, Container, Compare>& p1, const PriorityQueue<T, Container, Compare>& p2){
		return (p1._M_container < p2._M_container);
	}

	template <typename T, typename Container, typename Compare>
	inline bool operator!=(const PriorityQueue<T, Container, Compare>& p1, const PriorityQueue<T, Container, Compare>& p2){
		return !(p1._M_container == p2._M_container);
	}

	template <typename T, typename Container, typename Compare>
	inline bool operator>(const PriorityQueue<T, Container, Compare>& p1, const PriorityQueue<T, Container, Compare>& p2){
		return (p2._M_container < p1._M_container);
	}

	template <typename T, typename Container, typename Compare>
	inline bool operator<=(const PriorityQueue<T, Container, Compare>& p1, const PriorityQueue<T, Container, Compare>& p2){
		return !(p2._M_container < p1._M_container);
	}

	template <typename T, typename Container, typename Compare>
	inline bool operator>=(const PriorityQueue<T, Container, Compare>& p1, const PriorityQueue<T, Container, Compare>& p2){
		return !(p1._M_container < p2._M_container);
	}

}


#endif //NAIVE_STL_PRIORITYQUEUE_H
