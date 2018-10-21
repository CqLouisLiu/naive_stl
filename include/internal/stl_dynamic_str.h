//
// Created by Shuai on 2017/8/19.
//

#ifndef NAIVE_STL_DYNAMIC_STR_H
#define NAIVE_STL_DYNAMIC_STR_H

#include "stl_cdef.h"



    typedef char* _dstr;

    struct _dystr_struct{

        unsigned int _size;//动态字符串的大小(不包含空字符串);

        unsigned int _capacity;//buff中所有字节数(不包含空字符串);

        char _buff[];//字符串空间，不完整类型不占据内存空间;
    };

    static inline size_t dstr_len(const _dstr s){


        // sizeof(struct _dystr_struct))的长度是8(默认编译器对齐)，而s指向dstr_struct中的_buf字符数组,
        // 所以 s-8 的结果就是dstr_struct结构体的地址(sizeof uint =4 in 32 bits machine)，
        // 通过_sh->_size就可以获得字符串的长度;
        struct _dystr_struct* _sh=(struct _dystr_struct*)((s)-sizeof(struct _dystr_struct));

        return _sh->_size;

    }

    static inline size_t dstr_free(const _dstr s) {

        // sizeof(struct _dystr_struct))的长度是8(默认编译器对齐)，而s指向dstr_struct中的_buf字符数组,
        // 所以 s-8 的结果就是dstr_struct结构体的地址(sizeof uint =4 in 32 bits machine)，
        // 通过_sh->_size就可以获得字符串的长度;
        struct _dystr_struct* _sh=(struct _dystr_struct*)((s)-sizeof(struct _dystr_struct));

        return (_sh->_capacity-_sh->_size);
    }

    _dstr dstr_new(const char* str);//根据char*初始化_dystr_struct对象;
    size_t sdslen(const _dstr s);





#endif //NAIVE_STL_DYNAMIC_STRING_H
