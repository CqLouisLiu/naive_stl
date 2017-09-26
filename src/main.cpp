#include "type_traits.h"
#include <iostream>
#include <typeinfo>
#include "./thread/ThreadSafe_Stack.h"

using namespace naive;

int main() {

	ThreadSafe_Stack<int> threadSafe_stack;

	for(auto i=0;i<10;++i)
		threadSafe_stack.push(i);



	return 0;
}