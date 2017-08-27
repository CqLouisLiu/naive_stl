#include <iostream>
#include "util/PriorityQueue.h"


using namespace std;

int main(){

	int ia[9]={0,1,2,3,4,8,9,3,5};
	naive::PriorityQueue<int> ipq(ia,ia+9);

	cout<<"size="<<ipq.size()<<endl;

	for(auto i=0;i<ipq.size();++i)
		cout<<ipq.top()<<' ';
	cout<<endl;

	while(!ipq.empty()){
		cout<<ipq.top()<<' ';
		ipq.pop();
	}
	cout<<endl;


	return 0;
}