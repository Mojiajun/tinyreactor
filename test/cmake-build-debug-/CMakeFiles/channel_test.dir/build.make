# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mojiajun/CLionProjects/reactor_cpp/test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug-

# Include any dependencies generated for this target.
include CMakeFiles/channel_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/channel_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/channel_test.dir/flags.make

CMakeFiles/channel_test.dir/Channel_test.cpp.o: CMakeFiles/channel_test.dir/flags.make
CMakeFiles/channel_test.dir/Channel_test.cpp.o: ../Channel_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/channel_test.dir/Channel_test.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/channel_test.dir/Channel_test.cpp.o -c /Users/mojiajun/CLionProjects/reactor_cpp/test/Channel_test.cpp

CMakeFiles/channel_test.dir/Channel_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/channel_test.dir/Channel_test.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mojiajun/CLionProjects/reactor_cpp/test/Channel_test.cpp > CMakeFiles/channel_test.dir/Channel_test.cpp.i

CMakeFiles/channel_test.dir/Channel_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/channel_test.dir/Channel_test.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mojiajun/CLionProjects/reactor_cpp/test/Channel_test.cpp -o CMakeFiles/channel_test.dir/Channel_test.cpp.s

# Object files for target channel_test
channel_test_OBJECTS = \
"CMakeFiles/channel_test.dir/Channel_test.cpp.o"

# External object files for target channel_test
channel_test_EXTERNAL_OBJECTS =

channel_test: CMakeFiles/channel_test.dir/Channel_test.cpp.o
channel_test: CMakeFiles/channel_test.dir/build.make
channel_test: CMakeFiles/channel_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable channel_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/channel_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/channel_test.dir/build: channel_test

.PHONY : CMakeFiles/channel_test.dir/build

CMakeFiles/channel_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/channel_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/channel_test.dir/clean

CMakeFiles/channel_test.dir/depend:
	cd /Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug- && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mojiajun/CLionProjects/reactor_cpp/test /Users/mojiajun/CLionProjects/reactor_cpp/test /Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug- /Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug- /Users/mojiajun/CLionProjects/reactor_cpp/test/cmake-build-debug-/CMakeFiles/channel_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/channel_test.dir/depend
