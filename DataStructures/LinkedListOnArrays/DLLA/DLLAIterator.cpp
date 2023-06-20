#include "DLLAIterator.h"
#include <stdexcept>

DLLAIterator::DLLAIterator(const DLLA &d) : dlla(d) {
    current = dlla.head;
}

void DLLAIterator::first() {
    current = dlla.head;
}

void DLLAIterator::next() {
    if(!valid())
        throw std::invalid_argument("Invalid position in dlla");
    current = dlla.array[current].next;
}

bool DLLAIterator::valid() const {
    return current != -1;
}

TComp DLLAIterator::getCurrent() {
    if(!valid())
        throw std::invalid_argument("Invalid position in dlla");
    return dlla.array[current].info;
}