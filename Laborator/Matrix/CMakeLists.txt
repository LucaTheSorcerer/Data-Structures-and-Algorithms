cmake_minimum_required(VERSION 3.24)
project(Matrix)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_HEADERS Matrix.h Vector.h ShortTest.h ExtendedTest.h)
add_executable(Matrix App.cpp Matrix.cpp Matrix.h Vector.cpp ShortTest.cpp ExtendedTest.cpp)
