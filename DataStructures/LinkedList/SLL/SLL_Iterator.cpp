#include "SLL_Iterator.h"
#include "SLL.h"
#include <stdexcept>

SLLIterator::SLLIterator(const SLL &s) : sll(s) {
    this->node = sll.head;
}

void SLLIterator::first() {
    this->node = sll.head;
}

void SLLIterator::next() {
    if(!valid())
        throw std::invalid_argument("Iterator is invalid");
    node = node->next;
}

bool SLLIterator::valid() const {
    return node != nullptr;
}

TComp SLLIterator::getCurrent() const {
    if(!valid())
        throw std::invalid_argument("Iterator is invalid");

    return node->info;
}