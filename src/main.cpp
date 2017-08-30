#include <iostream>
#include <string>
#include "internal/stl_rb_tree.h"
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

	//naive::_RBTree_iterator_base rbit;

	for(;it1!=it2;++it1){
		//rbit=naive::_RBTree_iterator_base(it1);
		//cout<<*it2<<'('<<rbit._M_node->_M_color<<") ";
		cout<<*it2<<" ";
	}
	cout<<endl;

	return 0;
}