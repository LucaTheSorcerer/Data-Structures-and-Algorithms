#include "DLL_Iterator.h"
#include <stdexcept>

DLLIterator::DLLIterator(const DLL &d) : dll(d){
    current = dll.head;
}

void DLLIterator::first() {
    if(dll.isEmpty()){
        throw std::invalid_argument("List is empty");
    }
    current = dll.head;
}

void DLLIterator::next() {
    if(!valid())
        throw std::invalid_argument("Invalid iterator");
    current = current->next;
}

bool DLLIterator::valid() {
    return current != nullptr;
}

TComp DLLIterator::getCurrent() {
    if(!valid())
        throw std::invalid_argument("Invalid iterator");

    return current->info;
}