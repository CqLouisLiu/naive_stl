//
// Created by Shuai on 2017/8/18.
//

#ifndef NAIVE_STL_FILE_H
#define NAIVE_STL_FILE_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class File{

	File() noexcept:_M_fd(-1){}

	File(const char* name,int flags,mode_t mode);

private:
	int _M_fd;
};




#endif //NAIVE_STL_FILE_H
