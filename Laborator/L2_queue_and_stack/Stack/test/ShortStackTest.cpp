//
// Created by Luca Tudor on 10.04.2023.
//
#include "ShortStackTest.h"
#include "../src/Stack.h"
#include <cassert>
#include <iostream>

using namespace std;

void testAllStack() {
    cout << "Test all stack" << endl;
    Stack s;
    assert(s.isEmpty());
    s.push(5);
    assert(s.top() == 5);
    s.push(1);
    assert(s.top() == 1);
    s.push(10);
    assert(s.top() == 10);
    assert(s.pop() == 10);
    assert(s.top() == 1);
    assert(s.pop() == 1);
    assert(s.top() == 5);
}