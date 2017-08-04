#include <iostream>
#include "deque.h"
#include "list.h"

int main(){
	
	naive::deque<int> idq(20,200);
	std::cout<<idq.size()<<std::endl;

	return 0;
}