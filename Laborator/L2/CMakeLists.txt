cmake_minimum_required(VERSION 3.25)
project(L2)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_HEADER Queue/src/Queue.h Stack/src/Stack.h ShortTestQueue.h ExtendedTestQueue.h)

add_executable(L2 App.cpp Queue/src/Queue.cpp Stack/src/Stack.cpp Queue/test/ShortTestQueue.cpp Queue/test/ExtendedTestQueue.cpp Stack/test/ExtendedStackTest.cpp Stack/test/ShortStackTest.cpp Stack/test/ExtendedStackTest.h Stack/test/ShortStackTest.h)