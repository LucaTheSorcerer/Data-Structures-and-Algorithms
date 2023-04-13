#pragma once

#include <string>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct Node {
    int info;
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
    void push(TElem e);

    //returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem top();

    //removes and returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem pop();

    //checks if the stack is empty
    [[nodiscard]] bool isEmpty() const;

    // destructor
    ~Stack();
};

