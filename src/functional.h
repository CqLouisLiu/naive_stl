//
// Created by Shuai on 2017/8/20.
//

#ifndef NAIVE_STL_FUNCTIONAL_H
#define NAIVE_STL_FUNCTIONAL_H

#include <functional>

namespace naive{


	template <class _Value1, class _Value2, class _Result>
	struct binary_function{
		//In C++ 17;
		typedef _Value1   first_argument_type;
		typedef _Value2   second_argument_type;
		typedef _Result   result_type;
	};

	/*
 	* Function object for performing comparisons. Unless specialized, invokes operator< on type T.
 	*/
	template< class T >
	struct less:public binary_function<T,T,bool>{

		//expression ();
		bool operator()(const T& _value1,const T& _value2) const{
			return _value1<_value2;
		}
	};


	template<>
	struct less<void>{

	};

}

#endif //NAIVE_STL_FUNCTIONAL_H
