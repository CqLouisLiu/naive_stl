/*
 * NOTE: This is an internal header file, included by other C++ headers.
 * You should not attempt to use it directly.
 *
*/

#ifndef NAIVE_STL_STL_SORT_H
#define NAIVE_STL_STL_SORT_H

#include "stl_move.h"
#include "../functional.h"

namespace naive{


    template <typename Iterator,typename Compare>
    void insert_sort(const Iterator& begin,const Iterator& end,Compare cmp){

        if(begin==end)
            return;

        Iterator j;

        for(Iterator p=begin+1;p!=end;++p){

            auto tmp=naive::move(*p);

            for(j=p;j!=begin&&cmp(tmp,*(j-1));--j){
                *j=naive::move(*(j-1));
            }

            *j=naive::move(tmp);
        }
    }

    template <typename Iterator>
    void insert_sort(const Iterator& begin,const Iterator& end) {
        insert_sort(begin,end,naive::less<decltype(*begin)>());
    }
}


#endif //NAIVE_STL_STL_SORT_H
