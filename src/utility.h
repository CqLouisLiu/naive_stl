
#ifndef NAIVE_STL_UTILITY_H
#define NAIVE_STL_UTILITY_H

#include "internal/stl_pair.h"
#include "internal/stl_move.h"
#include "internal/stl_type_traits.h"

namespace naive{



	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	////Converts any type T to a reference type, making it possible to use member functions in decltype
	/// expressions without the need to go through constructors.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	typename naive::add_rvalue_reference<T>::type declval() noexcept;
}



#endif //NAIVE_STL_UTILITY_H
