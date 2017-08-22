#include <iostream>
#include "util/Vector.h"
#include "internal/stl_heap.h"

using namespace std;

int main(){

	naive::Vector<int> ivec(10);

	for(auto i=0;i<10;++i)
		ivec[i]=i;

	naive::make_heap(ivec.begin(),ivec.end());

	for(auto i=0;i<ivec.size();++i)
		cout<<ivec[i]<<" ";
	cout<<endl;

	return 0;
}