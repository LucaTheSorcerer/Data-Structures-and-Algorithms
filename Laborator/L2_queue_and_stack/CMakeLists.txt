cmake_minimum_required(VERSION 3.25)
project(L2_queue_and_stack)

set(CMAKE_CXX_STANDARD 23)

add_executable(L2_queue_and_stack Main/App.cpp Queue/src/Queue.h Queue/src/Queue.cpp Stack/src/Stack.h Stack/src/Stack.cpp Queue/test/ExtendedTestQueue.cpp Queue/test/ShortTestQueue.cpp Stack/test/ExtendedStackTest.cpp Stack/test/ShortStackTest.cpp Shunting_Yard/src/shunting_yard.cpp Shunting_Yard/src/shunting_yard.h Shunting_Yard/test/shunting_yard_test.cpp Shunting_Yard_With_Both/src/shunting_yard_with_both.h Shunting_Yard_With_Both/src/shunting_yard_with_both.cpp Shunting_Yard_With_Both/test/shunting_yard_with_both_test.h Shunting_Yard_With_Both/test/shunting_yard_with_both_test.cpp)
