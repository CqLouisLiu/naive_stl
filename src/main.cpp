
#include "util/Vector.h"
#include <iostream>
int main(){

    naive::Vector<int> vec(10,0);

    for(auto v:vec)
        std::cout<<v<<std::endl;
    return 0;
}
