#include <stdexcept>
#include "DynamicArrayIterator.h"
#include "DynamicArray.h"

DynamicArrayIterator::DynamicArrayIterator(const DynamicArray &a) : array(a) {
    this->current = 0;
}

void DynamicArrayIterator::first() {
    current = 0;
}

void DynamicArrayIterator::next() {
    if(!valid())
        throw std::invalid_argument("Iterator is invalid");
    this->current++;
}

bool DynamicArrayIterator::valid() {
    if(this->array.isEmpty()) return false;
    if(this->current < 0 || this->current >= this->array.size) return false;
    return true;
}

TComp DynamicArrayIterator::getCurrent() {
    if(!valid())
        throw std::invalid_argument("Iterator is invalid");
    return this->array.array[current];
}
