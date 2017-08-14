#include <iostream>
#include "util/Deque.h"
#include "util/List.h"

using namespace std;

int main(){
	
	naive::Deque<int> idq(20,200);
	std::cout<<idq.size()<<std::endl;

    idq.push_back(100);

    cout<<idq.size()<<endl;
    cout<<*idq.begin()<<endl;
    //count<<*(idq.end()._M_cur)<<endl;
	//naive::List<int> lst1;
	//std::cout<<lst1.size()<<std::endl;
	return 0;
}