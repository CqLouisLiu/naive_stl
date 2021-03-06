//
// Created by Shuai on 2017/8/18.
//

#ifndef NAIVE_STL_FILE_H
#define NAIVE_STL_FILE_H


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef __cplusplus
}
#endif


namespace naive {

	class File {

		File() noexcept: _M_fd(-1) {}

		File(const char *name, int flags, mode_t mode);

		~File();

	private:
		int _M_fd;
	};

}




#endif //NAIVE_STL_FILE_H
