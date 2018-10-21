//
// Created by Shuai on 2018/1/14.
//

#include "stl_dynamic_str.h"
#include "stl_alloc.h"

_dstr dstr_new(const char* init_str){

    struct _dystr_struct* sh=nullptr;
    naive::allocator<char> alloc;

    if(init_str== nullptr){
       alloc.allocate(sizeof(struct _dystr_struct)+1);
    }


    size_t _len=strlen(init_str);

}