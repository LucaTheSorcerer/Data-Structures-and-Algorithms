#include "DLLA.h"
#include "DLLAIterator.h"
#include <stdexcept>

DLLA::DLLA() {
    capacity = 10;
    size = 0;
    firstEmpty = 0;
    head = -1;
    tail = -1;
    array = new DLLANode[capacity];

    for (int i = 0; i < capacity; i++) {
        array[i].next = i + 1;
    }

    array[capacity - 1].next = -1;
}

DLLA::~DLLA() {
    delete[] array;
}

void DLLA::addToStart(TComp elem) {
    if (size == 0) {
        array[firstEmpty].info = elem;
        head = firstEmpty;
        tail = firstEmpty;
        firstEmpty = array[firstEmpty].next;
        array[head].next = -1;
    } else {
        int newIndex = firstEmpty;
        firstEmpty = array[firstEmpty].next;

        array[newIndex].info = elem;
        array[newIndex].next = head;
        array[newIndex].previous = -1;

        array[head].previous = newIndex;
        head = newIndex;
    }
    size++;
}

DLLAIterator DLLA::getIterator() {
    return DLLAIterator(*this);
}

TComp DLLA::removeFromStart() {
    if (size == 0) {
        throw std::invalid_argument("List is empty");
    }

    TComp removedElem = array[head].info;  // Store the element value to be removed

    if (size == 1) {
        firstEmpty = head;  // Mark the current head node as the first empty node
        head = -1;
        tail = -1;
    } else {
        int nextIndex = array[head].next;

        array[nextIndex].previous = -1;  // Update the previous field of the next node
        array[head].next = firstEmpty;   // Set the next field of the removed node as the new first empty node
        array[head].previous = -1;       // Clear the previous field of the removed node
        firstEmpty = head;               // Mark the removed node as the first empty node
        head = nextIndex;                // Update the head to the next node
    }

    size--;
    return removedElem;
}
