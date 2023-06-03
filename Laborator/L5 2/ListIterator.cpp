#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    first();
}

void ListIterator::first(){
    this->currentNode = this->list.root;
    while(this->currentNode != nullptr && this->currentNode->left != nullptr) {
        this->currentNode = this->currentNode->left;
    }
}

void ListIterator::next(){
    if(!this->valid()) {
        throw invalid_argument("Invalid position in the list!");
    }

    if(this->currentNode->right != nullptr) {
        this->currentNode = this->currentNode->right;
        while(this->currentNode->left != nullptr) {
            this->currentNode = this->currentNode->left;
        }
    }

    else {
        Node *parent = this->currentNode->parent;
        while(parent != nullptr && this->currentNode == parent->right) {
            this->currentNode = parent;
            parent = parent->parent;
        }
        this->currentNode = parent;
    }
}

bool ListIterator::valid() const{
    return(this->currentNode != nullptr);

}

TComp ListIterator::getCurrent() const{
    if(!this->valid()) {
        throw invalid_argument("Invalid position in the list!");
    }

    return this->currentNode->info;
}


