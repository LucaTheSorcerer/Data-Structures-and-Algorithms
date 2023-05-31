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
    if(i < 0 || i >= this->sizeTree)
        throw invalid_argument("Invalid position in the list!");

	Node *currentNode = this->root;
    while(currentNode != nullptr) {
        int leftSize = currentNode->nrLeftElements;
        if(i == leftSize) {
            return currentNode -> info;
        }
        else if (i < leftSize) {
            currentNode = currentNode -> left;
        }
        else {
            i = i - leftSize - 1;
            currentNode = currentNode -> right;
        }
    }

    return NULL_TCOMP;
}

TComp SortedIndexedList::remove(int i) {
    if(i < 0 || i >= this->sizeTree) {
        throw invalid_argument("Invalid position in the list!");
    }

    Node *currentNode = this->root;
    while(currentNode != nullptr) {
        int leftSize = currentNode->nrLeftElements;
        if(i == leftSize) {
            break;
        }
        else if(i < leftSize) {
            currentNode = currentNode->left;
        }
        else {
            i = i - leftSize - 1;
            currentNode = currentNode->right;
        }
    }

    TComp removedElement = currentNode->info;

    if(currentNode->left == nullptr && currentNode->right == nullptr) {
        if(currentNode == this->root) {
            this->root = nullptr;
        }
        else {
            Node *parentNode = currentNode->parent;
            if(parentNode->left == currentNode) {
                parentNode->left = nullptr;
            }
            else {
                parentNode->right = nullptr;
            }
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    }
    else if(currentNode->left == nullptr) {
        if(currentNode == this->root) {
            this->root = currentNode->right;
            this->root->parent = nullptr;
        }
        else {
            Node *parentNode = currentNode->parent;
            if(parentNode->left == currentNode) {
                parentNode->left = currentNode->right;
            }
            else {
                parentNode->right = currentNode->right;
            }
            currentNode->right->parent = parentNode;
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    }
    else if(currentNode->right == nullptr) {
        if(currentNode == this->root) {
            this->root = currentNode->left;
            this->root->parent = nullptr;
        }
        else {
            Node *parentNode = currentNode->parent;
            if(parentNode->left == currentNode) {
                parentNode->left = currentNode->left;
            }
            else {
                parentNode->right = currentNode->left;
            }
            currentNode->left->parent = parentNode;
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    }
    else {
        Node *successorNode = currentNode->right;
        while(successorNode->left != nullptr) {
            successorNode = successorNode->left;
        }
        currentNode->info = successorNode->info;
        if(successorNode->right != nullptr) {
            successorNode->right->parent = successorNode->parent;
        }
        if(successorNode->parent->left == successorNode) {
            successorNode->parent->left = successorNode->right;
        }
        else {
            successorNode->parent->right = successorNode->right;
        }
        this->updateNrLeftElements(successorNode->parent);
        delete successorNode;
    }

    this->sizeTree--;
    return removedElement;
}

void SortedIndexedList::updateNrLeftElements(Node *node) {
    if(node == nullptr) {
        return;
    }

    int nrLeftElements = 0;
    if(node->left != nullptr) {
        nrLeftElements = node->left->nrLeftElements + 1;
    }
    node->nrLeftElements = nrLeftElements;
    this->updateNrLeftElements(node->parent);
}

int SortedIndexedList::search(TComp e) const {
    Node *currentNode = this->root;
    int position = 0;

    while(currentNode != nullptr && currentNode->info != e)  {
        if(this->r(e, currentNode->info)) {
            currentNode = currentNode->left;
        }
        else {
            position = currentNode->nrLeftElements + 1;
            currentNode = currentNode->right;
        }
    }

    if(currentNode == nullptr)
        return -1;
    else
        return position + currentNode->nrLeftElements;
}

void SortedIndexedList::add(TComp e) {

    Node *currentNode = this->root;
    Node *parentNode = nullptr;
    Node *newNode = new Node;
    newNode->info = e;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->nrLeftElements = 0;

    while(currentNode != nullptr) {
        parentNode = currentNode;
        if(this->r(e, currentNode->info)) {
            currentNode->nrLeftElements++;
            currentNode = currentNode->left;
        }
        else {
            currentNode = currentNode->right;
        }
    }

    if(parentNode == nullptr) {
        this->root = newNode;
    }
    else {
        if(this -> r(e, parentNode->info)) {
            parentNode -> left = newNode;
        } else {
            parentNode -> right = newNode;
        }
    }

    newNode -> parent = parentNode;
    this->sizeTree++;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    this->destroyTree(this->root);
}

Node *SortedIndexedList::findMin(Node *node) const {
    Node *currentNode = node;
    while(currentNode->left != nullptr) {
        currentNode = currentNode->left;
    }
    return currentNode;
}

void SortedIndexedList::destroyTree(Node *node) {
    if(node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
