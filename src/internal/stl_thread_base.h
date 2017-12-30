//
// Created by shuai on 2017/12/30.
//

#ifndef NAIVE_STL_STL_THREAD_BASE_H
#define NAIVE_STL_STL_THREAD_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

#ifdef __cplusplus
}

typedef pthread_t thread_id;        //线程ID类型;
typedef pthread_attr_t thread_attr; //线程属性类型;

#endif
#endif //NAIVE_STL_STL_THREAD_BASE_H
