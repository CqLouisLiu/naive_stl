//
// Created by shuai on 2017/12/30.
//

#ifndef NAIVE_STL_STL_THREAD_BASE_H_H
#define NAIVE_STL_STL_THREAD_BASE_H_H




#include "../internal/stl_thread_base.h"


/*
 * DESCRIPTION: 比较两个线程标识符;
 * PARAMETERS: 两个线程ID,tid1和tid2;
 * RETURN VALUE: 相等返回1，否则0;
*/
int Thread_equal(thread_id t1, thread_id t2);

/*
 * DESCRIPTION: 返回调用线程ID;
 * PARAMETERS: void;
 * RETURN VALUE: 调用线程ID;
 * ERRORS: 总是成功，不返回错误;
*/
thread_id Thread_get_id(void);


/*
 * DESCRIPTION: 返回调用线程ID;
 * PARAMETERS:
 *   thread:一个thread_id类型指针，表示线程传出参数;
 *   attr:代表线程属性，默认为NULL;
 *   start_routine: 一个类型为void*的函数指针，且有一个类型为void*的参数extra，代表线程调用入口;
 *   extra:线程调用入口的参数，如果需要不止一个参数，可以封装成符合类型然后转换为void*传入;
 * RETURN VALUE: 成功返回0，错误返回错误代码;
 * ERRORS: 返回错误代码;
 * NOTES: 在Linux中fork()和pthread_create()都是使用clone()系统调用完成的;
*/
int Thread_create(thread_id *thread, const thread_attr *attr, void *(*start_routine)(void *), void *extra);


/*
 * DESCRIPTION: 终止调用线程，并且通过指针retval传出线程退出码;
 * PARAMETERS: void*类型传出参数retval;
 * RETURN VALUE: 不需要向调用者返回;
 * ERRORS: 总是成功，不返回错误;
 * NOTES: 线程可以通过三种方式退出
 *   1) 简单通过return返回;
 *   2) 被其他进程取消;
 *   3) 调用系统调用pthread_exit();
*/
void Thread_exit(void *retval);


/*
* DESCRIPTION: 等待指定thread线程退出;
* PARAMETERS:
*   thread: 等待指定线程ID
*   retval: void**类型传出参数retval;
* RETURN VALUE: 成功返回0,错误返回对应错误代码;
* NOTES: 关于join的意思不是"加入"，而是"汇聚"在一起的意思，即调用线程和指定线程在指定点汇合(可能阻塞，但不是阻塞的意思，不是大学老师讲的那个意思！)；
*/
int Thread_join(thread_id thread, void **retval);


int Tread_cancel(thread_id thread);


#endif //NAIVE_STL_STL_THREAD_BASE_H_H
