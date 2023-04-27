//
// Created by Luca Tudor on 07.04.2023.
//
#include "Stack.h"

/**
 * @brief: This is the constructor of the stack. It sets the head and the tail to nullptr
 * @param head: this is the head of the stack so the first element of the stack
 * @param tail: this is the tail of the stack so the last element of the stack meaning the top of the stack
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
Stack::Stack() {
    //This is the constructor of the stack
    this -> head = nullptr;
    this -> tail = nullptr;
}

/**
 * @brief: This is the push function of the stack.
 * @details: This function adds a new element  to the top of the stack. There are two cases regarding the stack.
 * On one hand, if the stack is empty, the function creates a new node and set the head and the tail to the new node.
 * We set the info to the element that we want to push and then we set the previous and next pointers to head and tail
 * that represent the first and the last element of the stack. Previous is set to to head to indicate that the head is
 * the first node in the stack and has no previous node. Next is set to tail in order to indicate that the first node in
 * the stack has no next node. The tail is also set to head to indicate that the tail is the last node.
 * On the other hand, if the stack is not empty, the function creates a new node and set the previous pointer of the new
 * node to the tail and the next pointer to the new node. The tail pointer is then updated to the new node. We set the
 * info to the element e that we want to push. Its next pointer is set to nullptr because it indicates that it will be
 * the last node in the list and its previous pointer is set to the current tail node, which will become its predecessor
 * Then, the next pointer of the curent tail node is updated to point to the new node, to link the current tail node
 * with the new node as its successor. Then the tail pointer is updated in order to point to the new node, because the
 * new node is now the last node in the list. This simplifies the implementation of the pop and top functions, which can
 * simply access the info field of the last node in the list.
 * @param e This is the element that we push to the stack
 * @return: nothing
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 * @throws: none
 */
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

//void Stack::push(TElem e) {
//
//    //This is the push function of the stack that pushes the operators for postfix conversion
//    //using the shunting yard algorithm
//    //First check if the stack is empty
//    if(!isEmpty()) {
//        auto *newNode = new SNode;
//        newNode -> info = e;
//        newNode -> next = nullptr;
//        newNode -> previous = tail;
//        tail -> next = newNode;
//        tail = newNode;
//    }
//    else {
//        head = new SNode;
//        head -> info = e;
//        head -> previous = head;
//        head -> next = tail;
//        this->tail = head;
//    }
//}

/**
 * @brief: This is the top function of the stack. This function returns the element from the top of the stack without
 * deleting it.
 * @details: First the function checks if the stack is empty and if it is then it will throw an exception.
 * If the stack is not empty, the function will return the value of the info field of the node pointed by tail
 * @return return the value of the info field of the node pointed by tail.
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 * @throws: std::exception
 * @param: none
 */
TElem Stack::top() const  {
    //This is the top or peek function of the stack

    //First we check if the stack is empty and if it is we throw an exception
    if(isEmpty()) {
        throw std::exception();
    }

    //If the stack is not empty we return the value of the top element
    return tail -> info;
}

/**
 * @brief: This is the pop function of the stack.
 * @details: This function removes the element from the top of the stack and returns it.
 * There are three cases regarding the pop function. First, if the stack is empty, the function will throw an exception.
 * Second, if the stack has only one element or the element in the last, the function will delete the element and set
 * the head and the tail to nullptr. The head and tail pointers are set to nullptr and the memory allocated for the
 * node is deallocated using the delete operator.
 * Third, if the stack has more than one element, the function will delete the element pointed by tail and update the
 * tail to point to the previous node in the list. The newTail pointer is first set to point to the previous node in the
 * list so the node that is currently pointed by the previous pointer of the current tail node
 * The next pointer of the new tail node is set to nullptr because it is
 * now the last element in the list.
 * @return the value of the info field of the node pointed by tail
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
TElem Stack::pop() {
    //This is the pop function of the stack
    // First we check if the stack is empty
    if(isEmpty()) {
        throw std::invalid_argument("The stack is empty");
    }

    //We get the element at the top of the stack, we pop it and return the value
    TElem top = tail->info;

    //We update the tail pointer if it is the last element in the stack.
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

/**
 * @brief: This is the isEmpty function of the stack.
 * @details: This function returns a boolean value indicating whether the stack is empty or not.
 * @return true if the stack is empty, and false otherwise
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
bool Stack::isEmpty() const {
    //Checks if the stack is empty
    return this -> head == nullptr;
}

/**
 * @brief: This is the destructor of the stack. It deallocates all the memory used by the double linked list.
 * @details: each node is deleted using a while loop and the head and tail are both set to nullptr.
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 * @n: the number of elements in the stack
 * @param: none
 * @throws: none
 */
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

/**
 * @brief: This is the getTail() function of the stack.
 * @details: The implementation sets a current pointer to head and then it iterates through the list until the end.
 * It returns the current pointer representing the tail of the list.
 * @return: the node pointed by tail
 * @TimeComplexity-BestCase θ(n)
 * @TimeComplexity-MediumCase θ(n)
 * @TimeComplexity-WorstCase θ(n)
 * @n: the number of elements in the stack
 */
//SNode *Stack::getTail() const {
//    SNode* current = head;
//    while (current != nullptr && current->next != nullptr) {
//        current = current->next;
//    }
//    return current;
//}

/**
 * @brief: This is the getTail() function of the stack.
 * @return returns the tail pointer
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-MediumCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 * @note regarding the time complexity, it is more efficient that the above implementation
 */
SNode* Stack::getTail() const {
    return tail;
}
