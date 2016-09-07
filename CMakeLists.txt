cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(qieda)

#Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    set( CMAKE_C_FLAGS   "-Wall ${CMAKE_C_FLAGS}" )
    set( CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}" )
endif()

find_package(OpenGL REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
  )

add_subdirectory(src)