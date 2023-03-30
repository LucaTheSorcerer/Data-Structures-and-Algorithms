#include "SetIterator.h"
#include "Set.h"
#include <exception>
using namespace std;

SetIterator::SetIterator(const Set& m) : set(m)
{
    first();
}

void SetIterator::first() {
    this->index = 0;
    while(valid() && !this->set.elements[this->index])
        this->index++;
}


void SetIterator::next() {
    if (!valid())
        throw exception();
    else {
        this->index++;
        while(!this->set.elements[this->index] && valid())
            this->index++;
    }
}


void SetIterator::previous(){
    this->index--;
    while(!this->set.elements[this->index] && valid())
        this->index--;
    if(!valid())
        throw exception();
}


TElem SetIterator::getCurrent() const
{
    if(!valid())
        throw exception();
    else
        return this->index + this->set.left;
}

bool SetIterator::valid() const {
    if(index >= 0 && this->index <= this->set.right - this->set.left)
        return true;
    return false;
}



