#include <iostream>
#include "util/Set.h"
#include <cmath>
#include <vector>
using namespace std;

int main(){

	// (1) Default constructor
	naive::Set<std::string> a;
	a.insert("cat");
	a.insert("dog");
	a.insert("horse");
	for(auto& str: a) std::cout << str << ' ';
	std::cout << '\n';

	// (2) Iterator constructor
	naive::Set<std::string> b(a.find("dog"), a.end());
	for(auto& str: b) std::cout << str << ' ';
	std::cout << '\n';

	// (3) Copy constructor
	naive::Set<std::string> c(a);
	c.insert("another horse");
	for(auto& str: c) std::cout << str << ' ';
	std::cout << '\n';

	// (4) Move constructor
	naive::Set<std::string> d(std::move(a));
	for(auto& str: d) std::cout << str << ' ';
	std::cout << '\n';
	std::cout << "moved-from set is ";
	for(auto& str: a) std::cout << str << ' ';
	std::cout << '\n';

	// (5) Initializer list constructor
	naive::Set<std::string> e {"one", "two", "three", "five", "eight"};
	for(auto& str: e) std::cout << str << ' ';
	std::cout << '\n';



	naive::Set<int> set;

	auto result_1 = set.insert(3);
	assert(result_1.first != set.end()); // it's a valid iterator
	assert(*result_1.first == 3);
	if (result_1.second)
		std::cout << "insert done\n";

	auto result_2 = set.insert(3);
	assert(result_2.first == result_1.first); // same iterator
	assert(*result_2.first == 3);
	if (!result_2.second)
		std::cout << "no insertion\n";


	vector<int> ivec;
	int ia[]={1,2,3,4,5,6,7,8,9};
	naive::Set<int> f(ia,ia+9);

	for(int i=10;i<20;++i)
		ivec.push_back(i);

	f.insert(ivec.begin(),ivec.end());

	for(int n : f)
		std::cout << n << ' ';
	cout<<endl;

	// erase all odd numbers from c
	for(auto it = f.begin(); it != f.end(); )
		if(*it % 2 == 1)
			it = f.erase(it);
		else
			++it;
	for(int n : f)
		std::cout << n << ' ';
	cout<<endl;

	//unsigned

	return 0;
}