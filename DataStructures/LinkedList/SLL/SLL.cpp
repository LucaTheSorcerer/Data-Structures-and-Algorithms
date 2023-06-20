#include "SLL.h"
#include "SLL_Iterator.h"
#include <stdexcept>

SLL::SLL() {
    head = nullptr;
    size = 0;
}

SLL::~SLL() {
    SLLNode *deletedNode;
    SLLNode *current = head;
    while (current != nullptr) {
        deletedNode = current;
        current = current->next;
        delete deletedNode;
    }
}

int SLL::getSize() const {
    return size;
}

bool SLL::isEmpty() const {
    if (size == 0)
        return true;
    return false;
}

TComp SLL::deleteElement(TComp element) {
    if (isEmpty())
        return NULL_TELEM;

    if (element == head->info) {
        TComp deletedValue = head->info;
        SLLNode* deletedNode = head;
        head = head->next;
        delete deletedNode;
        size--;
        return deletedValue;
    }

    SLLNode* current = head;
    SLLNode* previous = nullptr;

    while (current != nullptr) {
        if (current->info == element) {
            if (previous == nullptr) {
                // If previous is nullptr, it means the element to delete is at the head
                head = current->next;
            } else {
                previous->next = current->next;
            }

            auto deletedValue = current->info;
            delete current;
            size--;
            return deletedValue;
        }

        previous = current;
        current = current->next;
    }

    return NULL_TELEM;
}

void SLL::addFirst(TComp element) {
    auto *newNode = new SLLNode;
    newNode->info = element;
    newNode->next = head;
    this->head = newNode;
    size++;
}

void SLL::AddBeforeNode(SLLNode *currentNode, TComp element) {
    SLLNode *previous = head;
    while (previous != nullptr && previous->next != currentNode) {
        previous = previous->next;
    }

    if (previous == nullptr) {
        throw std::invalid_argument("Node does not exist");
    }

    auto *newNode = new SLLNode{element, currentNode};
    previous->next = newNode;
}

void SLL::addAfterNode(SLLNode *currentNode, TComp element) {
    auto *newNode = new SLLNode;
    newNode->info = element;
    newNode->next = currentNode->next;
    currentNode->next = newNode;
}

void SLL::insertPosition(int position, TComp element) {
    if (position < 0 || position >= size)
        throw std::invalid_argument("Invalid position");

    SLLNode *current = head;
    for (int i = 0; i <= position; i++) {
        current = current->next;
    }
    auto *newNode = new SLLNode{element, current->next};
    current->next = newNode;
}

TComp SLL::deleteFirst() {
    if (size == 0) {
        throw std::invalid_argument("List is empty");
    }

    SLLNode *deletedNode = head;
    auto deletedValue = head->info;
    head = head->next;
    delete deletedNode;
    size--;
    return deletedValue;
}

SLLIterator SLL::getIterator() {
    return SLLIterator(*this);
}