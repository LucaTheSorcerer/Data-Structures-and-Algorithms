#pragma once

#include <string>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef char TChar;
#define NULL_TELEM -11111

struct Node {
    basic_string<char, char_traits<char>, allocator<char>> info;
    Node* previous;
    Node* next;
};

class Stack {
private:
    Node* head;
    Node* tail;

public:
    Stack();

    //pushes an element to the end of the stack
    void push(TChar c);

    //returns the element from the top of the stack
    //throws exception if the stack is empty
    top() const;

    //removes and returns the element from the top of the stack
    //throws exception if the stack is empty
    basic_string<char, char_traits<char>, allocator<char>> pop();

    //checks if the stack is empty
    bool isEmpty() const;

    // destructor
    ~Stack();
};

