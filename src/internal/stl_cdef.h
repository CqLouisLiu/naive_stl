//
// Created by Shuai on 2018/1/14.
//

#ifndef NAIVE_STL_STL_CDEF_H
#define NAIVE_STL_STL_CDEF_H

#if !defined __GNUC__ || __GNUC__ < 2
# define __attribute__(xyz)
#endif


#ifdef NAIVE_STL_DYNAMIC_STR_H

#define MAX_DYSTRING_SIZE 1024*1024

#ifdef __cplusplus
extern "C" {
#endif
//必要头文件;
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __cplusplus
}
#endif

#endif //NAIVE_STL_DYNAMIC_STR_H




#endif //NAIVE_STL_STL_CDEF_H
