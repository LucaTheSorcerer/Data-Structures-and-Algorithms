#include "Queue.h"
#include <iostream>

using namespace std;

/**
 * This it the constructor of the queue. It sets the head and the tail to nullptr
 * @param head: this is the head of the queue
 * @param tail: this is the tail of the queue
 * @return
 * @timeComplexity-BestCase θ(1)
 * @timeComplexity-MediumCase θ(1)
 * @timeComplexity-WorstCase θ(1)
 */
Queue::Queue(): head(nullptr), tail(nullptr) {}

/**
 * @brief: This is the push function of the queue. We create a new node and we have two cases. If the queue is empty,
 * we set the head and the tail to the new node. If the queue is not empty, we set the next pointer of the tail
 * to the new node and we update the tail pointer to the new node.
 * The element will be pushed into the queue and the tail pointer will be updated
 * @param elem: this is the element that we wish to push into the queue
 * @return: nothing
 * @timeComplexity-BestCase θ(1)
 * @timeComplexity-MediumCase θ(1)
 * @timeComplexity-Worst θ(1)
 */
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

/**
 * @brief: This is the top function of the queue. This function returns the first element at the top of the queue,
 * without removing it.
 * @param: none
 * @return: the first element at the top of the queue
 * @timeComplexity-BestCase θ(1)
 * @timeComplexity-MediumCase θ(1)
 * @timeComplexity-WorstCase θ(1)
 */
TElem Queue::top() const {
    if(isEmpty()) {
        throw std::invalid_argument("The queue is empty");
    }
    return head -> info;
}

/**
 * @brief: This is the pop function of the queue. This function removes the first element of the queue and returns it.
 * It also updates the head pointer to the next element in the queue.
 * @param: none
 * @return the first element of the queue
 * @timeComplexity-BestCase θ(1)
 * @timeComplexity-MediumCase θ(1)
 * @timeComplexity-WorstCase θ(1)
 * @throw: if the queue is empty, the function throws and invalid_argument exception
 */
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

/**
 * @brief: This is the isEmpty function of the queue. The function checks whether the queue is empty or not.
 * @param: none
 * @return true if the queue is empty, and false otherwise
 * @timeComplexity-BestCase θ(1)
 * @timeComplexity-MediumCase θ(1)
 * @timeComplexity-WorstCase θ(1)
 */
bool Queue::isEmpty() const {
    //Checks if the queue is empty
    return head == nullptr;
}

/**
 * @brief: This is the destructor of the queue. It deletes all nodes in the queue
 * @param: none
 * @return: nothing
 * @timeComplexity-BestCase θ(n)
 * @timeComplexity-MediumCase θ(n)
 * @timeComplexity-WorstCase θ(n)
 * @n = the number of nodes in the queue
 *
 */
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