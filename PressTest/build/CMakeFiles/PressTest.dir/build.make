# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ServerTest/PressTest/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ServerTest/PressTest/build

# Include any dependencies generated for this target.
include CMakeFiles/PressTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PressTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PressTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PressTest.dir/flags.make

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o: CMakeFiles/PressTest.dir/flags.make
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o: /root/ServerTest/PressTest/src/main.cpp
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o: CMakeFiles/PressTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ServerTest/PressTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o -MF CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o.d -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o -c /root/ServerTest/PressTest/src/main.cpp

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ServerTest/PressTest/src/main.cpp > CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.i

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ServerTest/PressTest/src/main.cpp -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.s

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o: CMakeFiles/PressTest.dir/flags.make
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o: /root/ServerTest/PressTest/src/threadpool.cpp
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o: CMakeFiles/PressTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ServerTest/PressTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o -MF CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o.d -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o -c /root/ServerTest/PressTest/src/threadpool.cpp

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ServerTest/PressTest/src/threadpool.cpp > CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.i

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ServerTest/PressTest/src/threadpool.cpp -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.s

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o: CMakeFiles/PressTest.dir/flags.make
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o: /root/ServerTest/PressTest/src/tool.cpp
CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o: CMakeFiles/PressTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ServerTest/PressTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o -MF CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o.d -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o -c /root/ServerTest/PressTest/src/tool.cpp

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ServerTest/PressTest/src/tool.cpp > CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.i

CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ServerTest/PressTest/src/tool.cpp -o CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.s

# Object files for target PressTest
PressTest_OBJECTS = \
"CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o" \
"CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o" \
"CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o"

# External object files for target PressTest
PressTest_EXTERNAL_OBJECTS =

PressTest: CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/main.cpp.o
PressTest: CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/threadpool.cpp.o
PressTest: CMakeFiles/PressTest.dir/root/ServerTest/PressTest/src/tool.cpp.o
PressTest: CMakeFiles/PressTest.dir/build.make
PressTest: CMakeFiles/PressTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ServerTest/PressTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PressTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PressTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PressTest.dir/build: PressTest
.PHONY : CMakeFiles/PressTest.dir/build

CMakeFiles/PressTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PressTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PressTest.dir/clean

CMakeFiles/PressTest.dir/depend:
	cd /root/ServerTest/PressTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ServerTest/PressTest/build /root/ServerTest/PressTest/build /root/ServerTest/PressTest/build /root/ServerTest/PressTest/build /root/ServerTest/PressTest/build/CMakeFiles/PressTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PressTest.dir/depend

