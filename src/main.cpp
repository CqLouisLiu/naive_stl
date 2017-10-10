#include<iostream>
#include"internal/stl_sort.h"
#include "util/Vector.h"


using namespace std;

int main() {

    naive::Vector<int> vec{9,8,7,6,5,4,3,2,1};

    naive::insert_sort(vec.begin(),vec.end());

    for(auto v:vec)
        cout<<v<<",";
    cout<<endl;



	return 0;
}