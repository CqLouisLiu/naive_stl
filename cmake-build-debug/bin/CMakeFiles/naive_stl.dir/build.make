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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liushuai/Workspace/naive_stl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liushuai/Workspace/naive_stl/cmake-build-debug

# Include any dependencies generated for this target.
include bin/CMakeFiles/naive_stl.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/naive_stl.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/naive_stl.dir/flags.make

bin/CMakeFiles/naive_stl.dir/main.cpp.o: bin/CMakeFiles/naive_stl.dir/flags.make
bin/CMakeFiles/naive_stl.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liushuai/Workspace/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/naive_stl.dir/main.cpp.o"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_stl.dir/main.cpp.o -c /Users/liushuai/Workspace/naive_stl/src/main.cpp

bin/CMakeFiles/naive_stl.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_stl.dir/main.cpp.i"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liushuai/Workspace/naive_stl/src/main.cpp > CMakeFiles/naive_stl.dir/main.cpp.i

bin/CMakeFiles/naive_stl.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_stl.dir/main.cpp.s"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liushuai/Workspace/naive_stl/src/main.cpp -o CMakeFiles/naive_stl.dir/main.cpp.s

bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires:

.PHONY : bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires

bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides: bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/naive_stl.dir/build.make bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides.build
.PHONY : bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides

bin/CMakeFiles/naive_stl.dir/main.cpp.o.provides.build: bin/CMakeFiles/naive_stl.dir/main.cpp.o


bin/CMakeFiles/naive_stl.dir/io/File.cpp.o: bin/CMakeFiles/naive_stl.dir/flags.make
bin/CMakeFiles/naive_stl.dir/io/File.cpp.o: ../src/io/File.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liushuai/Workspace/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bin/CMakeFiles/naive_stl.dir/io/File.cpp.o"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_stl.dir/io/File.cpp.o -c /Users/liushuai/Workspace/naive_stl/src/io/File.cpp

bin/CMakeFiles/naive_stl.dir/io/File.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_stl.dir/io/File.cpp.i"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liushuai/Workspace/naive_stl/src/io/File.cpp > CMakeFiles/naive_stl.dir/io/File.cpp.i

bin/CMakeFiles/naive_stl.dir/io/File.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_stl.dir/io/File.cpp.s"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liushuai/Workspace/naive_stl/src/io/File.cpp -o CMakeFiles/naive_stl.dir/io/File.cpp.s

bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.requires:

.PHONY : bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.requires

bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.provides: bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/naive_stl.dir/build.make bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.provides.build
.PHONY : bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.provides

bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.provides.build: bin/CMakeFiles/naive_stl.dir/io/File.cpp.o


bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o: bin/CMakeFiles/naive_stl.dir/flags.make
bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o: ../src/thread/ThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liushuai/Workspace/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o -c /Users/liushuai/Workspace/naive_stl/src/thread/ThreadPool.cpp

bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.i"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liushuai/Workspace/naive_stl/src/thread/ThreadPool.cpp > CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.i

bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.s"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liushuai/Workspace/naive_stl/src/thread/ThreadPool.cpp -o CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.s

bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.requires:

.PHONY : bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.requires

bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.provides: bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.requires
	$(MAKE) -f bin/CMakeFiles/naive_stl.dir/build.make bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.provides.build
.PHONY : bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.provides

bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.provides.build: bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o


# Object files for target naive_stl
naive_stl_OBJECTS = \
"CMakeFiles/naive_stl.dir/main.cpp.o" \
"CMakeFiles/naive_stl.dir/io/File.cpp.o" \
"CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o"

# External object files for target naive_stl
naive_stl_EXTERNAL_OBJECTS =

bin/naive_stl: bin/CMakeFiles/naive_stl.dir/main.cpp.o
bin/naive_stl: bin/CMakeFiles/naive_stl.dir/io/File.cpp.o
bin/naive_stl: bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o
bin/naive_stl: bin/CMakeFiles/naive_stl.dir/build.make
bin/naive_stl: bin/CMakeFiles/naive_stl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liushuai/Workspace/naive_stl/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable naive_stl"
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/naive_stl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/naive_stl.dir/build: bin/naive_stl

.PHONY : bin/CMakeFiles/naive_stl.dir/build

bin/CMakeFiles/naive_stl.dir/requires: bin/CMakeFiles/naive_stl.dir/main.cpp.o.requires
bin/CMakeFiles/naive_stl.dir/requires: bin/CMakeFiles/naive_stl.dir/io/File.cpp.o.requires
bin/CMakeFiles/naive_stl.dir/requires: bin/CMakeFiles/naive_stl.dir/thread/ThreadPool.cpp.o.requires

.PHONY : bin/CMakeFiles/naive_stl.dir/requires

bin/CMakeFiles/naive_stl.dir/clean:
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin && $(CMAKE_COMMAND) -P CMakeFiles/naive_stl.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/naive_stl.dir/clean

bin/CMakeFiles/naive_stl.dir/depend:
	cd /Users/liushuai/Workspace/naive_stl/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liushuai/Workspace/naive_stl /Users/liushuai/Workspace/naive_stl/src /Users/liushuai/Workspace/naive_stl/cmake-build-debug /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin /Users/liushuai/Workspace/naive_stl/cmake-build-debug/bin/CMakeFiles/naive_stl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/naive_stl.dir/depend

