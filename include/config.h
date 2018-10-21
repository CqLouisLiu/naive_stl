//
// Created by Shuai on 2017/12/31.
//

#ifndef NAIVE_STL_CONFIG_H
#define NAIVE_STL_CONFIG_H

#ifdef _WIN32
#ifdef _WIN64
#define _WINDOWS_64_BIT
#else
#define _WINDOWS_32_BIT
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#define  _MAC_OS_X
#endif
#elif __linux__
#define  _LINUX_OS
#elif __unix__
#define  _UNIX_OS
#elif defined(_POSIX_VERSION)
#define  _POSIX_STANDARD
#endif

#endif //NAIVE_STL_CONFIG_H
