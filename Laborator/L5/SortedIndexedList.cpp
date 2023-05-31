#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {

    this->root = nullptr;
    this->sizeTree = 0;
    this->r = r;
}

int SortedIndexedList::size() const {

    if(root == nullptr)
        return 0;
    else
        return this->sizeTree;
}

bool SortedIndexedList::isEmpty() const {
    return(this->sizeTree == 0);
}

TComp SortedIndexedList::getElement(int i) const{
	//TODO - Implementation
	return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
	//TODO - Implementation
	return NULL_TCOMP;
}

int SortedIndexedList::search(TComp e) const {
	//TODO - Implementation
	return 0;
}

void SortedIndexedList::add(TComp e) {
	//TODO - Implementation
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
}
