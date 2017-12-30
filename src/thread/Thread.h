//
// Created by shuai on 2017/12/30.
//

#ifndef NAIVE_STL_THREAD_H
#define NAIVE_STL_THREAD_H

#include "./Thread_base.h"

namespace naive {

    class Thread {

    private:
        thread_id id;

    public:
        Thread() noexcept;

        Thread(Thread &&other) noexcept;

        Thread(const Thread &) = delete;
    };
}


#endif //NAIVE_STL_THREAD_H
