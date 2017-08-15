#include <iostream>
#include "util/Deque.h"
#include "util/List.h"

using namespace std;

int main(){
	
	naive::Deque<int> idq(20,200);
	cout<<"size of Deque="<<idq.size()<<endl;
    idq.push_back(100);

	auto it1=idq.begin();

	cout<<"it1="<<*it1<<endl;
	//cout<<"size of Deque="<<idq.size()<<endl;

	idq.push_front(101);
	auto it2=idq.begin();

	cout<<"it2="<<*it2<<endl;
	cout<<"size of Deque="<<idq.size()<<endl;

	return 0;
}