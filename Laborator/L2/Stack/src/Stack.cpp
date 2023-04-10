//
// Created by Luca Tudor on 07.04.2023.
//
#include "Stack.h"

#include <utility>

Stack::Stack() {
    //This is the constructor of the stack
    this -> head = nullptr;
    this -> tail = nullptr;
}

void Stack::push(TChar c) {

    //This is the push function of the stack that pushes the operators for postfix conversion
    //using the shunting yard algorithm
    //First check if the stack is empty
    if(isEmpty()) {
        Node *newNode = new Node;
        newNode -> info = std::move(c);
        newNode -> previous = head;
        newNode -> next = tail;
        tail = head;
    }
    else {
        Node *newNode = new Node;
        newNode -> info = std::move(c);
        newNode -> previous = tail;
        newNode -> next = nullptr;
        tail -> next = newNode;
        tail = newNode;
    }
}

basic_string<char, char_traits<char>, allocator<char>> Stack::top() const {
    //This is the top or peek function of the stack

    //First we check if the stack is empty and if it is we throw an exception
    if(isEmpty()) {
        throw std::invalid_argument("The stack is empty");
    }

    //If the stack is not empty we return the value of the top element
    return head -> info;
}

basic_string<char, char_traits<char>, allocator<char>> Stack::pop() {
    //This is the pop function of the stack
    // First we check if the stack is empty
    if(isEmpty()) {
        throw std::invalid_argument("The stack is empty");
    }

    //We create a new node that will be the new head of our stack
    //Get the top first element in the stack, pop it and return its value

    TChar top = tail->info;

    if(isEmpty()) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    else {
        Node *newNode = tail;
        tail = tail -> previous;
        delete newNode;
    }

    return top;
}

bool Stack::isEmpty() const {
    //Checks if the stack is empty
    return this -> head == nullptr;
}

Stack::~Stack() {
    //This is the destructor of the stack

    Node *current = head;
    while(current != nullptr) {
        Node *next = current -> next;
        delete current;
        current = next;
    }

    this->head = nullptr;
    this->tail = nullptr;
}
