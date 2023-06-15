# Install script for directory: /home/erfenjiao/project/muduo/muduo/base

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/erfenjiao/project/muduo/muduo/build/lib/libmuduo_base.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muduo/base" TYPE FILE FILES
    "/home/erfenjiao/project/muduo/muduo/base/Atomic.h"
    "/home/erfenjiao/project/muduo/muduo/base/Condition.h"
    "/home/erfenjiao/project/muduo/muduo/base/CountDownLatch.h"
    "/home/erfenjiao/project/muduo/muduo/base/CurrentThread.h"
    "/home/erfenjiao/project/muduo/muduo/base/Date.h"
    "/home/erfenjiao/project/muduo/muduo/base/Exception.h"
    "/home/erfenjiao/project/muduo/muduo/base/LogStream.h"
    "/home/erfenjiao/project/muduo/muduo/base/Logging.h"
    "/home/erfenjiao/project/muduo/muduo/base/Mutex.h"
    "/home/erfenjiao/project/muduo/muduo/base/StringPiece.h"
    "/home/erfenjiao/project/muduo/muduo/base/Thread.h"
    "/home/erfenjiao/project/muduo/muduo/base/TimeStamp.h"
    "/home/erfenjiao/project/muduo/muduo/base/TimeZone.h"
    "/home/erfenjiao/project/muduo/muduo/base/Types.h"
    "/home/erfenjiao/project/muduo/muduo/base/copyable.h"
    "/home/erfenjiao/project/muduo/muduo/base/noncopyable.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/erfenjiao/project/muduo/muduo/build/base/tests/cmake_install.cmake")
endif()

