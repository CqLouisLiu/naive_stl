# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/Shuai/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Shuai/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/f/workspaces/naive_stl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/f/workspaces/naive_stl/cmake-build-debug

# Include any dependencies generated for this target.
include bin/CMakeFiles/naive_stl.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/naive_stl.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/naive_stl.dir/flags.make

bin/CMakeFiles/naive_stl.dir/main.cpp.o: bin/CMakeFiles/naive_stl.dir/flags.make
bin/CMakeFiles/naive_stl.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/f/workspaces/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/naive_stl.dir/main.cpp.o"
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin && /usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_stl.dir/main.cpp.o -c /cygdrive/f/workspaces/naive_stl/src/main.cpp

bin/CMakeFiles/naive_stl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_stl.dir/main.cpp.i"
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/f/workspaces/naive_stl/src/main.cpp > CMakeFiles/naive_stl.dir/main.cpp.i

bin/CMakeFiles/naive_stl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_stl.dir/main.cpp.s"
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin && /usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/f/workspaces/naive_stl/src/main.cpp -o CMakeFiles/naive_stl.dir/main.cpp.s

bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires:

.PHONY : bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires

bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides: bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/naive_stl.dir/build.make bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides.build
.PHONY : bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides

bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides.build: bin/CMakeFiles/naive_stl.dir/main.cpp.o


# Object files for target naive_stl
naive_stl_OBJECTS = \
"CMakeFiles/naive_stl.dir/main.cpp.o"

# External object files for target naive_stl
naive_stl_EXTERNAL_OBJECTS =

bin/naive_stl.exe: bin/CMakeFiles/naive_stl.dir/main.cpp.o
bin/naive_stl.exe: bin/CMakeFiles/naive_stl.dir/build.make
bin/naive_stl.exe: bin/CMakeFiles/naive_stl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/f/workspaces/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable naive_stl.exe"
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/naive_stl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/naive_stl.dir/build: bin/naive_stl.exe

.PHONY : bin/CMakeFiles/naive_stl.dir/build

bin/CMakeFiles/naive_stl.dir/requires: bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires

.PHONY : bin/CMakeFiles/naive_stl.dir/requires

bin/CMakeFiles/naive_stl.dir/clean:
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin && $(CMAKE_COMMAND) -P CMakeFiles/naive_stl.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/naive_stl.dir/clean

bin/CMakeFiles/naive_stl.dir/depend:
	cd /cygdrive/f/workspaces/naive_stl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/f/workspaces/naive_stl /cygdrive/f/workspaces/naive_stl/src /cygdrive/f/workspaces/naive_stl/cmake-build-debug /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin /cygdrive/f/workspaces/naive_stl/cmake-build-debug/bin/CMakeFiles/naive_stl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/naive_stl.dir/depend

