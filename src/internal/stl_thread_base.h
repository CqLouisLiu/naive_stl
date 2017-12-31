//
// Created by shuai on 2017/12/30.
//

#ifndef NAIVE_STL_STL_THREAD_BASE_H
#define NAIVE_STL_STL_THREAD_BASE_H

#include "../config.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

#ifdef __cplusplus
}
#endif


#ifdef __linux__
typedef unsigned long thread_id;//linux中线程ID是无符号长整形;
#else
typedef pthread_t thread_id;        //线程ID类型;

#endif

typedef pthread_attr_t thread_attr; //线程属性类型;
typedef void *native_handle_type; //线程入口函数返回类型;

#endif //NAIVE_STL_STL_THREAD_BASE_H
