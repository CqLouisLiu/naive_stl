//
// Created by Shuai on 2017/8/20.
//

#ifndef NAIVE_STL_FUNCTIONAL_H
#define NAIVE_STL_FUNCTIONAL_H

#include <functional>

namespace naive{

	///////////////////////////////////////////////////////////////////
	//// unary_function is a base class for creating function objects
	/// with one argument.
	///////////////////////////////////////////////////////////////
	template <typename ArgumentType, typename ResultType>
	struct unary_function{
		typedef ArgumentType argument_type;
		typedef ResultType result_type;
	};

	///////////////////////////////////////////////////
	//// binary_function is a base class for creating
	/// function objects with two arguments.
	//////////////////////////////////////////////////
	template <class _Value1, class _Value2, class _Result>
	struct binary_function{
		//In C++ 17;
		typedef _Value1   first_argument_type;
		typedef _Value2   second_argument_type;
		typedef _Result   result_type;
	};


	template<typename T>
	struct _Identity:public unary_function<T,T>{

		const T& operator()(const T& _value) const{
			return _value;
		}
	};

	////////////////////////////////////////////////////////////////////////
	//// Identity is a Unary Function that represents the
	/// identity function: it takes a single argument x, and returns x.
	////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct identity:public _Identity<T>{};

	/////////////////////////////////////////////////////////////////////////////////////////////////
 	//// Function object for performing comparisons. Unless specialized, invokes operator< on type T.
 	/////////////////////////////////////////////////////////////////////////////////////////////////
	template< class T >
	struct less:public binary_function<T,T,bool>{

		//expression ();
		bool operator()(const T& _value1,const T& _value2) const{
			return _value1<_value2;
		}
	};


	template<>
	struct less<void>{};



}

#endif //NAIVE_STL_FUNCTIONAL_H
