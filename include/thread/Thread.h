//
// Created by shuai on 2017/12/30.
//

#ifndef NAIVE_STL_THREAD_H
#define NAIVE_STL_THREAD_H


/*
 namespace std {
    class thread;

    void swap(thread& x, thread& y) noexcept;

    bool operator==(thread::id x, thread::id y) noexcept;
    bool operator!=(thread::id x, thread::id y) noexcept;

    bool operator<(thread::id x, thread::id y) noexcept;
    bool operator<=(thread::id x, thread::id y) noexcept;
    bool operator>(thread::id x, thread::id y) noexcept;
    bool operator>=(thread::id x, thread::id y) noexcept;

    template<class CharT, class Traits>
    basic_ostream<CharT, Traits>& operator<<(basic_ostream<CharT, Traits>& out,
                                            thread::id id);

    template <class T> struct hash;
    template <> struct hash<thread::id>;

    namespace this_thread {

        thread::id get_id() noexcept;
        void yield() noexcept;
        template <class Clock, class Duration>
            void sleep_until(const chrono::time_point<Clock, Duration>& abs_time);
        template <class Rep, class Period>
            void sleep_for(const chrono::duration<Rep, Period>& rel_time);

    }
}*/

/*
 class thread {
 public:
    // types:
    class id;
    typedef implementation-defined native_handle_type;

    thread() noexcept;
    template <class F, class ...Args> explicit thread(F&& f, Args&&... args);
    ~thread();
    thread(const thread&) = delete;
    thread(thread&&) noexcept;
    thread& operator=(const thread&) = delete;
    thread& operator=(thread&&) noexcept;

    void swap(thread&) noexcept;
    bool joinable() const noexcept;
    void join();
    void detach();
    id get_id() const noexcept;
    native_handle_type native_handle();

    // static members:
    static unsigned hardware_concurrency() noexcept;
};
 */

/*
class thread::id {
 public:
    id() noexcept;
};*/

/*
#include "./Thread_base.h"


namespace naive {

    class _thread_id {
    private:
        thread_id _myId;

        friend class Thread;

        _thread_id(thread_id _id) : _myId(_id) {}

    public:
        _thread_id() noexcept : _myId(0) {}

        bool operator==(_thread_id _id1, _thread_id _id2) noexcept {
            if (Thread_equal(_id1._myId, _id2._myId) == 1)
                return true;
            return false;
        }


    };

    class Thread {

    private:
        _thread_id _myId;

    public:
        Thread() noexcept;

        Thread(Thread &&other) noexcept;

        template<class F, class ...Args>
        explicit Thread(F &&f, Args &&... args);

        Thread(const Thread &) = delete;

        void swap(Thread &thread);

        bool joinable();

        void join();

        void detach();

    };
}

*/
#endif //NAIVE_STL_THREAD_H
