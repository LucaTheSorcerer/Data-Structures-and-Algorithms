#include <stdexcept>
#include "DLL.h"
#include "DLL_Iterator.h"

DLL::DLL() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

DLL::~DLL() {
    DLLNode *current = head;
    while (current != nullptr){
        DLLNode *deletedNode = current;
        current = current->next;
        delete deletedNode;
    }
}

void DLL::addToEnd(TComp element) {
    auto newNode = new DLLNode{element, nullptr, tail};
    if(size == 0){
        head = newNode;
        tail = newNode;
        size = 1;
        return;
    }

    tail->next = newNode;
    tail = newNode;
    size++;
}

void DLL::addToPosition(int position, TComp elem) {
    if (position < 0 || position > size)
        throw std::invalid_argument("Invalid position!");

    DLLNode* current = head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    auto *newNode = new DLLNode;
    newNode->info = elem;
    newNode->next = current->next;
    newNode->previous = current;
    if (current->next != nullptr) {
        current->next->previous = newNode;
    }
    current->next = newNode;

    size++;
}

void DLL::addToStart(TComp elem) {
    auto *newNode = new DLLNode{elem, head, nullptr};
    if(isEmpty()){
        head = newNode;
        tail = newNode;
        size = 1;
        return;
    }

    head->previous = newNode;
    head = newNode;
    size++;
}

TComp DLL::removeStart() {
    if (size == 0)
        throw std::invalid_argument("List is empty!");

    DLLNode* deletedNode = head;
    auto deletedValue = head->info;

    if (size == 1) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = head->next;
        head->previous = nullptr;
    }

    delete deletedNode;
    size--;

    return deletedValue;
}

TComp DLL::removeElement(TComp element) {
    if(isEmpty())
        return NULL_TELEM;

    if(element == head->info) {
        TComp deletedValue = head->info;
        DLLNode* deletedNode = head;
        head = head->next;
        head->previous = nullptr;
        delete deletedNode;
        size--;

        if(size == 0) {
            head = nullptr;
            tail = nullptr;
        }

        return deletedValue;
    }

    DLLNode* current = head;

    while(current != nullptr) {
        if(current->info == element) {
            if(current->previous == nullptr) {
                if(current->next == nullptr) {
                    head = nullptr;
                    tail = nullptr;
                }
                else {
                    head = head->next;
                    head->previous = nullptr;
                }
            }
            else if(current->next == nullptr) {
                tail = tail->previous;
                tail->next = nullptr;
            }
            else {
                current->next->previous = current->previous;
                current->previous->next = current->next;
            }
            auto deletedValue = current->info;
            delete current;
            size--;
            return deletedValue;
        }
        current = current->next;
    }
    return NULL_TELEM;
}

bool DLL::isEmpty() const {
    return size == 0;
}

int DLL::getSize() const {
    return size;
}

DLLIterator DLL::getIterator() {
    return DLLIterator(*this);
}