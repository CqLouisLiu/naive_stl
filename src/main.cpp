#include "type_traits.h"
#include <iostream>
#include <typeinfo>

using namespace std;
int main() {
	using nonref = int;
	using lref = typename naive::add_lvalue_reference<nonref>::type;
	using rref = typename naive::add_rvalue_reference<nonref>::type;

	std::cout << std::boolalpha;
	std::cout << naive::is_lvalue_reference<nonref>::value << '\n';
	std::cout << naive::is_lvalue_reference<lref>::value << '\n';
	std::cout << naive::is_rvalue_reference<rref>::value << '\n';
}