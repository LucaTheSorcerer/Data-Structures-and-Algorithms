cmake_minimum_required(VERSION 3.25)
project(L4_test)

set(CMAKE_CXX_STANDARD 23)

add_executable(L4_test App.cpp Map.cpp MapIterator.cpp ShortTest.cpp ExtendedTest.cpp)
