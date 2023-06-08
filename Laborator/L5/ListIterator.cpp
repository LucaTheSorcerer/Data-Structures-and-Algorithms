#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

/**
 * @brief Construct a new List Iterator:: List Iterator object
 * @details This calls the first() method to set the current node to the first node in the list
 * @param list
 * @TimeComplexity-BestCase: θ(1) -> the tree is empty and the function insert the new element as the root of the tree
 * @TimeComplexity-AverageCase: θ(log(n)) -> each iteration reduces the search space by half on average
 * @TimeComplexity-WorstCase: θ(n) -> the binary tree is entirely to left or to the right and the function needs to
 * traverse the entire height of the tree to find the correct position for insertion
 */
ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    first();
}

/**
 * @brief Sets the current node to the first node in the list
 * @details this method is responsible for setting the iterator to the first node in the list. If starts from the root of
 * the tree and moves down the most left side until there are no more children left.
 * @TimeComplexity-BestCase: θ(1) -> the tree is empty and the function insert the new element as the root of the tree
 * @TimeComplexity-AverageCase: θ(log(n)) -> each iteration reduces the search space by half on average
 * @TimeComplexity-WorstCase: θ(n) -> the binary tree is entirely to left or to the right and the function needs to
 * traverse the entire height of the tree to find the correct position for insertion
 */
void ListIterator::first(){
    this->currentNode = this->list.root;
    while(this->currentNode != nullptr && this->currentNode->left != nullptr) {
        this->currentNode = this->currentNode->left;
    }
}

/**
 * @brief Moves the iterator to the next node in the list
 * @details This method is responsible for moving the iterator to the next node in the list. If the current node has a
 * right child, update the current node to its right child, then while the current node has a left child, update the
 * current node to its left childs. This ensures that the iterator moves to the leftmost child of the right subtree
 * If the current node does not have a right child, find the first ancestor of the current node for which the current node
 * is in the left subtree. The function traverses the tree through parent nodes until either reaching to the root or
 * finding a parent node for which the current node is in the left subtree. Finally the current node is updated to the
 * ancestor node.
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 *
 */
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

/**
 * @brief Checks if the iterator is valid
 * @return true if the iterator is valid, false otherwise
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
bool ListIterator::valid() const{
    return(this->currentNode != nullptr);

}

/**
 * @brief Returns the current element from the iterator
 * @details This method returns the current element from the iterator. If the iterator is not valid, an exception is
 * thrown
 * @return
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
TComp ListIterator::getCurrent() const{
    if(!this->valid()) {
        throw invalid_argument("Invalid position in the list!");
    }

    return this->currentNode->info;
}


