# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/erfenjiao/project/muduo/muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erfenjiao/project/muduo/muduo/build

# Include any dependencies generated for this target.
include base/CMakeFiles/muduo_base.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include base/CMakeFiles/muduo_base.dir/compiler_depend.make

# Include the progress variables for this target.
include base/CMakeFiles/muduo_base.dir/progress.make

# Include the compile flags for this target's objects.
include base/CMakeFiles/muduo_base.dir/flags.make

base/CMakeFiles/muduo_base.dir/Condition.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/Condition.cc.o: ../base/Condition.cc
base/CMakeFiles/muduo_base.dir/Condition.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object base/CMakeFiles/muduo_base.dir/Condition.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/Condition.cc.o -MF CMakeFiles/muduo_base.dir/Condition.cc.o.d -o CMakeFiles/muduo_base.dir/Condition.cc.o -c /home/erfenjiao/project/muduo/muduo/base/Condition.cc

base/CMakeFiles/muduo_base.dir/Condition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Condition.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/Condition.cc > CMakeFiles/muduo_base.dir/Condition.cc.i

base/CMakeFiles/muduo_base.dir/Condition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Condition.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/Condition.cc -o CMakeFiles/muduo_base.dir/Condition.cc.s

base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o: ../base/CountDownLatch.cc
base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o -MF CMakeFiles/muduo_base.dir/CountDownLatch.cc.o.d -o CMakeFiles/muduo_base.dir/CountDownLatch.cc.o -c /home/erfenjiao/project/muduo/muduo/base/CountDownLatch.cc

base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/CountDownLatch.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/CountDownLatch.cc > CMakeFiles/muduo_base.dir/CountDownLatch.cc.i

base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/CountDownLatch.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/CountDownLatch.cc -o CMakeFiles/muduo_base.dir/CountDownLatch.cc.s

base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o: ../base/CurrentThread.cc
base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o -MF CMakeFiles/muduo_base.dir/CurrentThread.cc.o.d -o CMakeFiles/muduo_base.dir/CurrentThread.cc.o -c /home/erfenjiao/project/muduo/muduo/base/CurrentThread.cc

base/CMakeFiles/muduo_base.dir/CurrentThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/CurrentThread.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/CurrentThread.cc > CMakeFiles/muduo_base.dir/CurrentThread.cc.i

base/CMakeFiles/muduo_base.dir/CurrentThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/CurrentThread.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/CurrentThread.cc -o CMakeFiles/muduo_base.dir/CurrentThread.cc.s

base/CMakeFiles/muduo_base.dir/Logging.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/Logging.cc.o: ../base/Logging.cc
base/CMakeFiles/muduo_base.dir/Logging.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object base/CMakeFiles/muduo_base.dir/Logging.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/Logging.cc.o -MF CMakeFiles/muduo_base.dir/Logging.cc.o.d -o CMakeFiles/muduo_base.dir/Logging.cc.o -c /home/erfenjiao/project/muduo/muduo/base/Logging.cc

base/CMakeFiles/muduo_base.dir/Logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Logging.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/Logging.cc > CMakeFiles/muduo_base.dir/Logging.cc.i

base/CMakeFiles/muduo_base.dir/Logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Logging.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/Logging.cc -o CMakeFiles/muduo_base.dir/Logging.cc.s

base/CMakeFiles/muduo_base.dir/LogStream.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/LogStream.cc.o: ../base/LogStream.cc
base/CMakeFiles/muduo_base.dir/LogStream.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object base/CMakeFiles/muduo_base.dir/LogStream.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/LogStream.cc.o -MF CMakeFiles/muduo_base.dir/LogStream.cc.o.d -o CMakeFiles/muduo_base.dir/LogStream.cc.o -c /home/erfenjiao/project/muduo/muduo/base/LogStream.cc

base/CMakeFiles/muduo_base.dir/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/LogStream.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/LogStream.cc > CMakeFiles/muduo_base.dir/LogStream.cc.i

base/CMakeFiles/muduo_base.dir/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/LogStream.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/LogStream.cc -o CMakeFiles/muduo_base.dir/LogStream.cc.s

base/CMakeFiles/muduo_base.dir/Thread.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/Thread.cc.o: ../base/Thread.cc
base/CMakeFiles/muduo_base.dir/Thread.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object base/CMakeFiles/muduo_base.dir/Thread.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/Thread.cc.o -MF CMakeFiles/muduo_base.dir/Thread.cc.o.d -o CMakeFiles/muduo_base.dir/Thread.cc.o -c /home/erfenjiao/project/muduo/muduo/base/Thread.cc

base/CMakeFiles/muduo_base.dir/Thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/Thread.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/Thread.cc > CMakeFiles/muduo_base.dir/Thread.cc.i

base/CMakeFiles/muduo_base.dir/Thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/Thread.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/Thread.cc -o CMakeFiles/muduo_base.dir/Thread.cc.s

base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o: base/CMakeFiles/muduo_base.dir/flags.make
base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o: ../base/TimeStamp.cc
base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o: base/CMakeFiles/muduo_base.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o -MF CMakeFiles/muduo_base.dir/TimeStamp.cc.o.d -o CMakeFiles/muduo_base.dir/TimeStamp.cc.o -c /home/erfenjiao/project/muduo/muduo/base/TimeStamp.cc

base/CMakeFiles/muduo_base.dir/TimeStamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/muduo_base.dir/TimeStamp.cc.i"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/base/TimeStamp.cc > CMakeFiles/muduo_base.dir/TimeStamp.cc.i

base/CMakeFiles/muduo_base.dir/TimeStamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/muduo_base.dir/TimeStamp.cc.s"
	cd /home/erfenjiao/project/muduo/muduo/build/base && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/base/TimeStamp.cc -o CMakeFiles/muduo_base.dir/TimeStamp.cc.s

# Object files for target muduo_base
muduo_base_OBJECTS = \
"CMakeFiles/muduo_base.dir/Condition.cc.o" \
"CMakeFiles/muduo_base.dir/CountDownLatch.cc.o" \
"CMakeFiles/muduo_base.dir/CurrentThread.cc.o" \
"CMakeFiles/muduo_base.dir/Logging.cc.o" \
"CMakeFiles/muduo_base.dir/LogStream.cc.o" \
"CMakeFiles/muduo_base.dir/Thread.cc.o" \
"CMakeFiles/muduo_base.dir/TimeStamp.cc.o"

# External object files for target muduo_base
muduo_base_EXTERNAL_OBJECTS =

lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/Condition.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/CountDownLatch.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/CurrentThread.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/Logging.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/LogStream.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/Thread.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/TimeStamp.cc.o
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/build.make
lib/libmuduo_base.a: base/CMakeFiles/muduo_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library ../lib/libmuduo_base.a"
	cd /home/erfenjiao/project/muduo/muduo/build/base && $(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean_target.cmake
	cd /home/erfenjiao/project/muduo/muduo/build/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/muduo_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
base/CMakeFiles/muduo_base.dir/build: lib/libmuduo_base.a
.PHONY : base/CMakeFiles/muduo_base.dir/build

base/CMakeFiles/muduo_base.dir/clean:
	cd /home/erfenjiao/project/muduo/muduo/build/base && $(CMAKE_COMMAND) -P CMakeFiles/muduo_base.dir/cmake_clean.cmake
.PHONY : base/CMakeFiles/muduo_base.dir/clean

base/CMakeFiles/muduo_base.dir/depend:
	cd /home/erfenjiao/project/muduo/muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erfenjiao/project/muduo/muduo /home/erfenjiao/project/muduo/muduo/base /home/erfenjiao/project/muduo/muduo/build /home/erfenjiao/project/muduo/muduo/build/base /home/erfenjiao/project/muduo/muduo/build/base/CMakeFiles/muduo_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : base/CMakeFiles/muduo_base.dir/depend

