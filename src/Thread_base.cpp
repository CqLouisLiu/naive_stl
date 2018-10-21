//
// Created by shuai on 2017/12/30.
//

#include "../include/thread/Thread_base.h"

int Thread_equal(thread_id t1, thread_id t2) {

    if (pthread_equal(t1, t2) == 0)
        return 0;
    else
        return 1;
}

thread_id Thread_get_id(void) {

    return pthread_self();
}

int Thread_create(thread_id *thread, const thread_attr *attr, void *(*start_routine)(void *), void *extra) {

    return pthread_create(thread, attr, start_routine, extra);

}

void Thread_exit(void *retval) {

    pthread_exit(retval);
}

int Thread_join(thread_id thread, void **retval) {

    return pthread_join(thread, retval);
}

int Thread_cancle(thread_id thread){

    return pthread_cancel(thread);

}

