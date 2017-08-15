#include <iostream>
#include "util/Deque.h"
#include "util/List.h"

using namespace std;

int main(){
	
	naive::Deque<int> idq;
	//cout<<"size of Deque="<<idq.size()<<endl;

	for(int i=0;i<20;++i)
		idq.push_back(0);

	for(int i=0;i<20;++i)
		idq.push_front(1);

	for(auto it=idq.begin();it<idq.end();++it){
		cout<<*it<<" ";
	}
	cout<<endl;

	idq.push_front(11);
	idq.push_back(99);

	cout<<"back="<<idq.back()<<endl;
	cout<<"front="<<idq.front()<<endl;
	cout<<"size of Deque="<<idq.size()<<endl;

	idq.clear();
	cout<<"size of Deque="<<idq.size()<<endl;


	return 0;
}