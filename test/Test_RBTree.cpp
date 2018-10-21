#include <iostream>
#include "../internal/stl_rb_tree.h"
using namespace std;

int main(){


	naive::RBTree<int,int,naive::identity<int>> rbtree;

	cout<<"size="<<rbtree.size()<<endl;

	rbtree.insert_unique(10);
	rbtree.insert_unique(7);
	rbtree.insert_unique(8);
	rbtree.insert_unique(15);
	rbtree.insert_unique(5);
	rbtree.insert_unique(6);
	rbtree.insert_unique(11);
	rbtree.insert_unique(13);
	rbtree.insert_unique(12);

	cout<<"size="<<rbtree.size()<<endl;

	auto  it1=rbtree.begin();
	auto  it2=rbtree.end();

	naive::_RBTree_iterator_base rbit;

	for(auto c:rbtree) {

		rbit = naive::_RBTree_iterator_base(it1);

		if (it1 != it2) {
			cout << c << '(' << rbit._M_node->_M_color << ") ";
			++it1;
		}
	}
	cout<<endl;

	auto it=rbtree.find(5);
	cout<<*it<<endl;

	rbtree.erase(11);
	for(auto c:rbtree) {
		cout << c <<" ";
	}
	cout<<endl;

	int ia[]={1,2,3,12,9,7,4,5};
	naive::RBTree<int,int,naive::identity<int>> rbtree2;
	rbtree2.insert_unique(ia,ia+8);
	for(auto c:rbtree2) {
		cout << c <<" ";
	}
	cout<<endl;

	rbtree2.clear();
	cout<<rbtree2.size()<<endl;


	return 0;
}