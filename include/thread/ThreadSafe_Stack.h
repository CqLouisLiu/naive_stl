//
// Created by shuai on 2017/9/26.
//

#ifndef NAIVE_STL_THREADSAFE_STACK_H
#define NAIVE_STL_THREADSAFE_STACK_H

#include <mutex>
#include <memory>
#include "../util/Stack.h"
#include "../internal/stl_move.h"
#include "../exception/exception.h"

namespace naive{


    template <typename T>
    class ThreadSafe_Stack{

    private:
        naive::Stack<T> _M_stk;
        mutable std::mutex _M_mutex;

    public:
        typedef ThreadSafe_Stack<T> _Self_type;
        typedef T value_type;
        typedef std::shared_ptr<value_type> pointer;
        typedef const std::shared_ptr<value_type> const_pointer;

        ThreadSafe_Stack():_M_stk(naive::Stack<T>()){}

        ThreadSafe_Stack(ThreadSafe_Stack& other){

            std::lock_guard<std::mutex> _t_lock(other._M_mutex);
            _M_stk=other._M_stk;
        }

        ThreadSafe_Stack(ThreadSafe_Stack&& other) noexcept {

            std::lock_guard<std::mutex> _t_lock(other._M_mutex);
            _M_stk=naive::move(other._M_stk);
        }

        _Self_type& operator=(ThreadSafe_Stack& other)=delete;

    public:
        void push(value_type value){

            std::lock_guard<std::mutex> _t_lock(_M_mutex);
            _M_stk.push(value);
        }

        pointer pop(){

            std::lock_guard<std::mutex> _t_lock(_M_mutex);

            if(_M_stk.empty())
                throw naive::Empty_stack();

            const_pointer ret(std::make_shared<T>(_M_stk.top()));
            _M_stk.pop();

            return ret;
        }

        bool empty() const {

            std::lock_guard<std::mutex> lock(_M_mutex);
            return _M_stk.empty();
        }
    };
}

#endif //NAIVE_STL_THREADSAFE_STACK_H
