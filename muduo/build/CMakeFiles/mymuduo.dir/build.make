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
include CMakeFiles/mymuduo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mymuduo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mymuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mymuduo.dir/flags.make

CMakeFiles/mymuduo.dir/Channel.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Channel.o: ../Channel.cc
CMakeFiles/mymuduo.dir/Channel.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mymuduo.dir/Channel.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Channel.o -MF CMakeFiles/mymuduo.dir/Channel.o.d -o CMakeFiles/mymuduo.dir/Channel.o -c /home/erfenjiao/project/muduo/muduo/Channel.cc

CMakeFiles/mymuduo.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Channel.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/Channel.cc > CMakeFiles/mymuduo.dir/Channel.i

CMakeFiles/mymuduo.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Channel.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/Channel.cc -o CMakeFiles/mymuduo.dir/Channel.s

CMakeFiles/mymuduo.dir/DefaultPoller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/DefaultPoller.o: ../DefaultPoller.cc
CMakeFiles/mymuduo.dir/DefaultPoller.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mymuduo.dir/DefaultPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/DefaultPoller.o -MF CMakeFiles/mymuduo.dir/DefaultPoller.o.d -o CMakeFiles/mymuduo.dir/DefaultPoller.o -c /home/erfenjiao/project/muduo/muduo/DefaultPoller.cc

CMakeFiles/mymuduo.dir/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/DefaultPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/DefaultPoller.cc > CMakeFiles/mymuduo.dir/DefaultPoller.i

CMakeFiles/mymuduo.dir/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/DefaultPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/DefaultPoller.cc -o CMakeFiles/mymuduo.dir/DefaultPoller.s

CMakeFiles/mymuduo.dir/EPollPoller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EPollPoller.o: ../EPollPoller.cc
CMakeFiles/mymuduo.dir/EPollPoller.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mymuduo.dir/EPollPoller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EPollPoller.o -MF CMakeFiles/mymuduo.dir/EPollPoller.o.d -o CMakeFiles/mymuduo.dir/EPollPoller.o -c /home/erfenjiao/project/muduo/muduo/EPollPoller.cc

CMakeFiles/mymuduo.dir/EPollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EPollPoller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/EPollPoller.cc > CMakeFiles/mymuduo.dir/EPollPoller.i

CMakeFiles/mymuduo.dir/EPollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EPollPoller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/EPollPoller.cc -o CMakeFiles/mymuduo.dir/EPollPoller.s

CMakeFiles/mymuduo.dir/EventLoop.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EventLoop.o: ../EventLoop.cc
CMakeFiles/mymuduo.dir/EventLoop.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mymuduo.dir/EventLoop.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EventLoop.o -MF CMakeFiles/mymuduo.dir/EventLoop.o.d -o CMakeFiles/mymuduo.dir/EventLoop.o -c /home/erfenjiao/project/muduo/muduo/EventLoop.cc

CMakeFiles/mymuduo.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoop.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/EventLoop.cc > CMakeFiles/mymuduo.dir/EventLoop.i

CMakeFiles/mymuduo.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoop.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/EventLoop.cc -o CMakeFiles/mymuduo.dir/EventLoop.s

CMakeFiles/mymuduo.dir/InetAddress.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/InetAddress.o: ../InetAddress.cc
CMakeFiles/mymuduo.dir/InetAddress.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mymuduo.dir/InetAddress.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/InetAddress.o -MF CMakeFiles/mymuduo.dir/InetAddress.o.d -o CMakeFiles/mymuduo.dir/InetAddress.o -c /home/erfenjiao/project/muduo/muduo/InetAddress.cc

CMakeFiles/mymuduo.dir/InetAddress.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/InetAddress.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/InetAddress.cc > CMakeFiles/mymuduo.dir/InetAddress.i

CMakeFiles/mymuduo.dir/InetAddress.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/InetAddress.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/InetAddress.cc -o CMakeFiles/mymuduo.dir/InetAddress.s

CMakeFiles/mymuduo.dir/Logger.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Logger.o: ../Logger.cc
CMakeFiles/mymuduo.dir/Logger.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mymuduo.dir/Logger.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Logger.o -MF CMakeFiles/mymuduo.dir/Logger.o.d -o CMakeFiles/mymuduo.dir/Logger.o -c /home/erfenjiao/project/muduo/muduo/Logger.cc

CMakeFiles/mymuduo.dir/Logger.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Logger.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/Logger.cc > CMakeFiles/mymuduo.dir/Logger.i

CMakeFiles/mymuduo.dir/Logger.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Logger.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/Logger.cc -o CMakeFiles/mymuduo.dir/Logger.s

CMakeFiles/mymuduo.dir/Poller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Poller.o: ../Poller.cc
CMakeFiles/mymuduo.dir/Poller.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mymuduo.dir/Poller.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Poller.o -MF CMakeFiles/mymuduo.dir/Poller.o.d -o CMakeFiles/mymuduo.dir/Poller.o -c /home/erfenjiao/project/muduo/muduo/Poller.cc

CMakeFiles/mymuduo.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Poller.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/Poller.cc > CMakeFiles/mymuduo.dir/Poller.i

CMakeFiles/mymuduo.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Poller.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/Poller.cc -o CMakeFiles/mymuduo.dir/Poller.s

CMakeFiles/mymuduo.dir/TcpServer.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/TcpServer.o: ../TcpServer.cc
CMakeFiles/mymuduo.dir/TcpServer.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mymuduo.dir/TcpServer.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/TcpServer.o -MF CMakeFiles/mymuduo.dir/TcpServer.o.d -o CMakeFiles/mymuduo.dir/TcpServer.o -c /home/erfenjiao/project/muduo/muduo/TcpServer.cc

CMakeFiles/mymuduo.dir/TcpServer.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/TcpServer.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/TcpServer.cc > CMakeFiles/mymuduo.dir/TcpServer.i

CMakeFiles/mymuduo.dir/TcpServer.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/TcpServer.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/TcpServer.cc -o CMakeFiles/mymuduo.dir/TcpServer.s

CMakeFiles/mymuduo.dir/Timestamp.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Timestamp.o: ../Timestamp.cc
CMakeFiles/mymuduo.dir/Timestamp.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/mymuduo.dir/Timestamp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Timestamp.o -MF CMakeFiles/mymuduo.dir/Timestamp.o.d -o CMakeFiles/mymuduo.dir/Timestamp.o -c /home/erfenjiao/project/muduo/muduo/Timestamp.cc

CMakeFiles/mymuduo.dir/Timestamp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Timestamp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erfenjiao/project/muduo/muduo/Timestamp.cc > CMakeFiles/mymuduo.dir/Timestamp.i

CMakeFiles/mymuduo.dir/Timestamp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Timestamp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erfenjiao/project/muduo/muduo/Timestamp.cc -o CMakeFiles/mymuduo.dir/Timestamp.s

# Object files for target mymuduo
mymuduo_OBJECTS = \
"CMakeFiles/mymuduo.dir/Channel.o" \
"CMakeFiles/mymuduo.dir/DefaultPoller.o" \
"CMakeFiles/mymuduo.dir/EPollPoller.o" \
"CMakeFiles/mymuduo.dir/EventLoop.o" \
"CMakeFiles/mymuduo.dir/InetAddress.o" \
"CMakeFiles/mymuduo.dir/Logger.o" \
"CMakeFiles/mymuduo.dir/Poller.o" \
"CMakeFiles/mymuduo.dir/TcpServer.o" \
"CMakeFiles/mymuduo.dir/Timestamp.o"

# External object files for target mymuduo
mymuduo_EXTERNAL_OBJECTS =

../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Channel.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/DefaultPoller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EPollPoller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EventLoop.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/InetAddress.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Logger.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Poller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/TcpServer.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Timestamp.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/build.make
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erfenjiao/project/muduo/muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX shared library ../lib/libmymuduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mymuduo.dir/build: ../lib/libmymuduo.so
.PHONY : CMakeFiles/mymuduo.dir/build

CMakeFiles/mymuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mymuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mymuduo.dir/clean

CMakeFiles/mymuduo.dir/depend:
	cd /home/erfenjiao/project/muduo/muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erfenjiao/project/muduo/muduo /home/erfenjiao/project/muduo/muduo /home/erfenjiao/project/muduo/muduo/build /home/erfenjiao/project/muduo/muduo/build /home/erfenjiao/project/muduo/muduo/build/CMakeFiles/mymuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mymuduo.dir/depend

