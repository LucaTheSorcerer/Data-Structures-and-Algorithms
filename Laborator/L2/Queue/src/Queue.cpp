#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue(): head(nullptr), tail(nullptr) {}


void Queue::push(TElem elem) {
    //This is the push function of the queue
    auto *newNode = new QNode;
    newNode -> info = elem;
    newNode -> next = nullptr;
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail -> next = newNode;
        tail = newNode;
    }
}


TElem Queue::top() const {
    if(isEmpty()) {
        throw std::invalid_argument("The queue is empty");
    }
    return head -> info;
}

TElem Queue::pop() {
    //First we check if the queue is empty
    if(isEmpty()) {
        throw std::invalid_argument("The queue is empty");
    }

    //We create a node that will be the new head of our queue
    //Get the top first element in the queue, pop it and return the value
    TElem top = head -> info;
    QNode *newHead = head;
    head = head -> next;
    //If the queue is empty, we set the tail to nullptr

    if(isEmpty()) {
        tail = nullptr;
    }

    //We delete the old head and return the value of the top element
    delete newHead;
    return top;

}

bool Queue::isEmpty() const {
    //Checks if the queue is empty
    return head == nullptr;
}


Queue::~Queue() {
    //This is the destructor of the queue
    QNode *current = head;
    while(current != nullptr) {
        QNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}