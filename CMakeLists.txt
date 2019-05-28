cmake_minimum_required (VERSION 3.5)
project (KGTrading)

include_directories ("${PROJECT_SOURCE_DIR}/include")

#set (Tutorial_VERSION_MAJOR 1)
#set (Tutorial_VERSION_MINOR 0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused --std=c++14")

add_executable (utest ${PROJECT_SOURCE_DIR}/test/test.cpp)

#install (TARGET utest DESTINATION bin)
