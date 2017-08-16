#include <iostream>
#include "util/Stack.h"
#include "util/Queue.h"
//#include <util/Queue.h>


using namespace std;

int main(){

	naive::Queue<int>   s;

	s.push( 2 );
	s.push( 6 );
	s.push( 51 );

	std::cout << s.size() << " elements on stack\n";
	std::cout << "Top element: "
			  << s.front()         // Leaves element on stack
			  << "\n";
	std::cout << s.size() << " elements on stack\n";
	s.pop();
	std::cout << s.size() << " elements on stack\n";
	std::cout << "Top element: " << s.front() << "\n";


	return 0;
}