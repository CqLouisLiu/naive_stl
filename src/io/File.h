//
// Created by 刘帅 on 2017/8/12.
//

#ifndef NAIVE_STL_FILE_H
#define NAIVE_STL_FILE_H

namespace navie{

    class File{

    public:
        File();

        ~File();
    private:
        int _M_fd;
    };
}


#endif //NAIVE_STL_FILE_H
