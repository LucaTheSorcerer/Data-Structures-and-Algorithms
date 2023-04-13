//
// Created by Luca Tudor on 10.04.2023.
//
#include "../src/Stack.h"
#include "ExtendedStackTest.h"
#include <cassert>

void test_push_pop() {
    Stack s;
    for (int i = 1; i <= 10; i++) {
        s.push(i);
        assert(!s.isEmpty());
        assert(s.top() == i);
    }
    for (int i = 10; i >= 1; i--) {
        assert(s.top() == i);
        s.pop();
        assert(!s.isEmpty());
    }
}

void testAllExtendedStack() {
    test_push_pop();
}
