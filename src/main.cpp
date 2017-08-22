#include <iostream>
#include <vector>
#include "util/Vector.h"
#include "internal/stl_heap.h"

using namespace std;

int main(){

	int ia[] = {0,1,2,3,4,8,9,5};
	std::vector<int> ivec(ia,ia+8);


	naive::make_heap(ivec.begin(), ivec.end());

	for (auto i = 0; i<ivec.size(); ++i)
		cout << ivec[i] << " ";
	cout << endl;

	/*
	ivec.push_back(7);

	naive::push_heap(ivec.begin(),ivec.end());
	for (auto i = 0; i<ivec.size(); ++i)
		cout << ivec[i] << " ";
	cout << endl;
	*/


	naive::pop_heap(ivec.begin(),ivec.end());

	for (auto i = 0; i<ivec.size(); ++i)
		cout << ivec[i] << " ";
	cout << endl;

	ivec.pop_back();

	for (auto i = 0; i<ivec.size(); ++i)
		cout << ivec[i] << " ";
	cout << endl;

	return 0;

	return 0;
}