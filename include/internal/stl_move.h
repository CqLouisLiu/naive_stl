//
// Created by Shuai on 2017/8/28.
//

#ifndef NAIVE_STL_STL_UTILITY_H
#define NAIVE_STL_STL_UTILITY_H

#include "../type_traits.h"

namespace naive {

	/*
	 * 1.the naive::move(T&& t) just cast something to rvalue type, not move something to other;
	 * 2.naive::move(T&& t) can both accept rvalue and lvalue;
	 *   For example, int i=1024, i is a left value, when we invoke the
	 *   naive::move(i), the T can be deduced as int&, so the type of parameter t can be
	 *   supposed as int& &&, finally, the compiler can fold it to int&. As a result, the function can
	 *   be decided as:
	 *   int&& move(int& t){ return static_cast<int&&>(t);}
	 *
	 */

	template<class T>
	typename naive::remove_reference<T>::type &&move(T &&t) noexcept {

		return static_cast<typename naive::remove_reference<T>::type &&>(t);
	}

	/* Forwards lvalues as either lvalues or as rvalues, depending on T;
	 * As detail please see: http://en.cppreference.com/w/cpp/utility/forward
	 */
	template<class T>
	T &&forward(typename naive::remove_reference<T>::type &t) noexcept {

		// if std::string& is the invoked parameter, this function like this:
		// std::string& forward(std::string& t){ return static_cast<std::string&>t;}
		// because of reference fold rules;
		return static_cast<T &&>(t);//reference will be folded as T&;
	}

	template<class T>
	T &&forward(typename naive::remove_reference<T>::type &&t) noexcept {
		return static_cast<T&&>(t);
	}
}
#endif //NAIVE_STL_STL_UTILITY_H
