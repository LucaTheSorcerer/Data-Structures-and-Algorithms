#pragma once

#include <string>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM -11111

struct SNode {
    int info;
    SNode* previous;
    SNode* next;
};

class Stack {
private:
    SNode* head;
    SNode* tail;


public:
    Stack();

    //pushes an element to the end of the stack
    void push(TElem e);

    //returns the element from the top of the stack
    //throws exception if the stack is empty
    [[nodiscard]] TElem top() const;

    //removes and returns the element from the top of the stack
    //throws exception if the stack is empty
    TElem pop();

    //checks if the stack is empty
    [[nodiscard]] bool isEmpty() const;

    // destructor
    ~Stack();


    [[nodiscard]] SNode* getTail() const;
};

