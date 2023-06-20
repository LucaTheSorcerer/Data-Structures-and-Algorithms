#include <stdexcept>
#include "SLLA.h"
#include "SLLAIterator.h"

SingleLinkedListOnArrays::SingleLinkedListOnArrays() {
    size = 0;
    capacity = 10;
    array = new SLLANode[capacity];
    for (int i = 0; i < capacity; i++) {
        array[i].next = i + 1;
    }
    array[capacity - 1].next = -1;
    head = -1;
    firstEmpty = 0;
}

SingleLinkedListOnArrays::~SingleLinkedListOnArrays() {
    delete[] array;
}

void SingleLinkedListOnArrays::addToStart(TComp element) {
    int current = firstEmpty;
    firstEmpty = array[firstEmpty].next;
    array[current] = SLLANode{element, head};
    head = current;
    size++;
//    automaticResize();
}

void SingleLinkedListOnArrays::addToPosition(int position, TComp elem) {
    if(position == 0)
        addToStart(elem);

    if(position < 0 || position >= size){
        throw std::invalid_argument("Invalid size");
    }

    array[firstEmpty] = SLLANode{elem};

    int current = head;
    for(int i = 0; i < position; i++){
        current = array[current].next;
    }

    array[firstEmpty].next = array[current].next;
    array[current].next = firstEmpty;
    firstEmpty = array[firstEmpty].next;
    size++;
//    automaticResize();
}

SLLAIterator SingleLinkedListOnArrays::getIterator() const {
    return SLLAIterator(*this);
}

TComp SingleLinkedListOnArrays::removeFromStart() {
    int oldIndex = head;
    head = array[head].next;
    array[oldIndex].next = firstEmpty;
    firstEmpty = oldIndex;
    return array[oldIndex].info;
}

TComp SingleLinkedListOnArrays::removeElement(TComp element) {
    int current = head;
    int previous = -1;  // Initialize previous as -1 (invalid index)

    while (current != -1) {
        if (array[current].info == element) {
            if (previous == -1) {
                // Case: Removing the head node
                head = array[current].next;
            } else {
                // Case: Removing a node in the middle or at the end
                array[previous].next = array[current].next;
            }
            size--;
            return array[current].info;
        } else {
            previous = current;  // Update previous after checking the current node
            current = array[current].next;
        }
    }
    return NULL_TELEM;
}

TComp SingleLinkedListOnArrays::removeFromPosition(int position) {
    if (position < 0 || position >= size) {
        throw std::out_of_range("Invalid position");
    }

    int current = head;
    int previous = -1;

    for (int i = 0; i < position; i++) {
        previous = current;
        current = array[current].next;
    }

    if (previous == -1) {
        // Case: Removing the head node
        head = array[current].next;
    } else {
        // Case: Removing a node in the middle or at the end
        array[previous].next = array[current].next;
    }

    TComp removedElement = array[current].info;
    array[current].info = NULL_TELEM; // Optional: Clear the info of the removed node
    array[current].next = firstEmpty;
    firstEmpty = current;
    size--;

    return removedElement;
}