
#include "./include/util/Vector.h"
#include <iostream>

int main(int argc,char* argv[]){

    naive::Vector<int> vec(10,0);

    for(auto v:vec)
        std::cout<<v<<std::endl;
    return 0;
}
