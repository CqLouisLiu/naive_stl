//
// Created by 刘帅 on 2017/9/22.
//

#ifndef NAIVE_STL_EXCEPTION_H
#define NAIVE_STL_EXCEPTION_H

#include <exception>

namespace naive{

    struct Empty_stack: std::exception{

        const char* what() const throw();
    };
}


#endif //NAIVE_STL_EXCEPTION_H
