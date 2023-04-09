#pragma once

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct StackNode {
    TElem info;
    StackNode* previous;
    StackNode* next;
};

class Stack {
private:
    StackNode* head;

public:
    Stack();

    //pushes an element to the end of the stack
    void push(TElem e);

    //returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem top() const;

    //removes and returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem pop();

    //checks if the stack is empty
    bool isEmpty() const;

    // destructor
    ~Stack();
};

