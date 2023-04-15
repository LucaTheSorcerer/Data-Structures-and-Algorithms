//
// Created by Luca Tudor on 07.04.2023.
//
#include "Stack.h"


Stack::Stack() {
    //This is the constructor of the stack
    this -> head = nullptr;
    this -> tail = nullptr;
}


void Stack::push(TElem e) {

    //This is the push function of the stack that pushes the operators for postfix conversion
    //using the shunting yard algorithm
    //First check if the stack is empty
    if(isEmpty()) {
        head = new SNode;
        head -> info = e;
        head -> previous = head;
        head -> next = tail;
        this->tail = head;
    }
    else {

        auto *newNode = new SNode;
        newNode -> info = e;
        newNode -> next = nullptr;
        newNode -> previous = tail;
        tail -> next = newNode;
        tail = newNode;
    }
}

TElem Stack::top() const  {
    //This is the top or peek function of the stack

    //First we check if the stack is empty and if it is we throw an exception
    if(isEmpty()) {
        throw std::exception();
    }

    //If the stack is not empty we return the value of the top element
    return tail -> info;
}


TElem Stack::pop() {
    //This is the pop function of the stack
    // First we check if the stack is empty
    if(isEmpty()) {
        throw std::invalid_argument("The stack is empty");
    }

    //Get the top element in the stack, pop it and return its value
    TElem top = tail->info;

    //Update the tail pointer if this is the last element in the stack
    if (head == tail) {
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
    else {
        SNode *newTail = tail -> previous;
        newTail -> next = nullptr;
        delete tail;
        tail = newTail;
    }

    return top;
}


bool Stack::isEmpty() const {
    //Checks if the stack is empty
    return this -> head == nullptr;
}

Stack::~Stack() {
    //This is the destructor of the stack

    SNode *current = head;
    while(current != nullptr) {
        SNode *next = current -> next;
        delete current;
        current = next;
    }

    this->head = nullptr;
    this->tail = nullptr;
}

SNode *Stack::getTail() const {
    SNode* current = head;
    while (current != nullptr && current->next != nullptr) {
        current = current->next;
    }
    return current;
}