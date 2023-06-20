cmake_minimum_required(VERSION 3.25)
project(DataStructures)

set(CMAKE_CXX_STANDARD 23)

add_executable(DataStructures main.cpp DynamicArray/DynamicArray.cpp DynamicArray/DynamicArrayIterator.cpp Heap/BinaryHeap.cpp LinkedList/SLL/SLL.h LinkedList/SLL/SLL.cpp LinkedList/SLL/SLL_Iterator.cpp LinkedList/DLL/DLL.cpp LinkedList/DLL/DLL_Iterator.cpp LinkedListOnArrays/SLLA/SLLA.h LinkedListOnArrays/SLLA/SLLAIterator.h LinkedListOnArrays/SLLA/SLLA.cpp LinkedListOnArrays/SLLA/SLLAIterator.cpp LinkedListOnArrays/DLLA/DLLA.h LinkedListOnArrays/DLLA/DLLAIterator.h LinkedListOnArrays/DLLA/DLLA.cpp LinkedListOnArrays/DLLA/DLLAIterator.cpp)
