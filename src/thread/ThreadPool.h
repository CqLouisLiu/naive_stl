//
// Created by 刘帅 on 2017/9/18.
//

#ifndef NAIVE_STL_THREADPOOL_H
#define NAIVE_STL_THREADPOOL_H

#include "../util/Vector.h"
#include <thread>

class ThreadPool{

private:
    naive::Vector<std::thread> _M_threads;
};

#endif //NAIVE_STL_THREADPOOL_H
