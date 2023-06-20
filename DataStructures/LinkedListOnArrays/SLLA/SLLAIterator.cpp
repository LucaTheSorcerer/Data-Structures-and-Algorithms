#include <stdexcept>
#include "SLLAIterator.h"

SLLAIterator::SLLAIterator(const SingleLinkedListOnArrays &slla) : singleLinkedListOnArrays(slla){
    current = singleLinkedListOnArrays.head;
}

void SLLAIterator::first() {
    current = singleLinkedListOnArrays.head;
}

void SLLAIterator::next() {
    if(!valid())
        throw std::invalid_argument("Invalid position in slla");
    current = singleLinkedListOnArrays.array[current].next;
}

bool SLLAIterator::valid() const {
    return current != -1;
}

TComp SLLAIterator::getCurrent() {
    if(!valid())
        throw std::invalid_argument("Invalid position in slla");
    return singleLinkedListOnArrays.array[current].info;
}