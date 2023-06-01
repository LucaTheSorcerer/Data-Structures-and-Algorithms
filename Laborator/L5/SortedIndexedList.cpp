#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

/**
 * @brief Constructor of the SortedIndexedList class
 * @param r - the relation used for sorting the list
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
SortedIndexedList::SortedIndexedList(Relation r) {

    this->root = nullptr;
    this->sizeTree = 0;
    this->r = r;
}

/**
 * @brief Returns the size of the binary search tree or the number of elements in the list
 * @return the size of the binary search tree or the number of elements in the list
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
int SortedIndexedList::size() const {

    if(root == nullptr)
        return 0;
    else
        return this->sizeTree;
}

/**
 * @brief Check whether the list is empty or not
 * @return true if the list is empty, false otherwise
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
bool SortedIndexedList::isEmpty() const {
    return(this->sizeTree == 0);
}

/**
 * @brief Gets an element from a given position from the list
 * @param i - the position of the element
 * @return the element from the given position
 * @throws exception if the position is not valid
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(log(n))
 * @TimeComplexity-WorstCase: θ(log(n))
 */
TComp SortedIndexedList::getElement(int i) const {
    if (i < 0 || i >= this->sizeTree) {
        throw std::out_of_range("Invalid position in the list!");
    }

    Node* current = this->root;
    int position = 0;

    while (current != nullptr) {
        int leftSize = current->nrLeftElements;

        if (i == (position + leftSize)) {
            return current->info;
        }

        if (i < (position + leftSize)) {
            current = current->left;
        } else {
            position = position + leftSize + 1;
            current = current->right;
        }
    }

    return NULL_TCOMP;
}



/**
 * @brief Finds the minimum element in the binary search tree
 * @brief this function is used to find the minimum element in the binary search tree.
 * @param node - the current node of the binary search tree
 * @return the minimum element in the binary search tree
 * @TimeComplexity-BestCase: θ(n)
 * @TimeComplexity-AverageCase: θ(n)
 * @TimeComplexity-WorstCase: θ(n)
 */
Node *SortedIndexedList::findMin(Node *node) const {
    Node *currentNode = node;

    //check if empty
    if(currentNode == nullptr) {
        return nullptr;
    }

    while(currentNode->left != nullptr) {
        currentNode = currentNode->left;
    }
    return currentNode;
}


int SortedIndexedList::search(TComp e) const {
    Node *current = this->root;
    int position = 0;
    while (current != nullptr) {
        if (current->info == e) {
            return (position + current->nrLeftElements);
        }
        if (this->r(e, current->info)) {
            current = current->left;
        } else {
            position = position + current->nrLeftElements + 1;
            current = current->right;
        }
    }
    return -1;
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

/**
 * @brief Destructor of the SortedIndexedList class
 * @details Function that destroys the tree by calling the destroyTree function
 * @TimeComplexity-BestCase: θ(n)
 * @TimeComplexity-AverageCase: θ(n)
 * @TimeComplexity-WorstCase: θ(n)
 */
SortedIndexedList::~SortedIndexedList() {
    this->destroyTree(this->root);
}

/**
 * @brief Function that destroys the tree
 * @param node - the root of the tree
 * @TimeComplexity-BestCase: θ(n)
 * @TimeComplexity-AverageCase: θ(n)
 * @TimeComplexity-WorstCase: θ(n)
 */
void SortedIndexedList::destroyTree(Node *node) {
    if(node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
void SortedIndexedList::updateNrLeftElements(Node* node) {
    if(node == nullptr) {
        return;
    }

    int leftSize = 0;
    if(node->left != nullptr) {
        leftSize = node->left->nrLeftElements + 1;
    }

    node->nrLeftElements = leftSize;
    updateNrLeftElements(node->parent);
}

void SortedIndexedList::printTree(Node* node, int level) const {
    if(node == nullptr) {
        return;
    }

    printTree(node->right, level + 1);
    for(int i = 0; i < level; i++) {
        cout << "   ";
    }
    cout << node->info << "(" << node->nrLeftElements << ")" << endl;
    printTree(node->left, level + 1);
}

//void SortedIndexedList::printTree(Node* node, int level) const {
//    if(node == nullptr) {
//        return;
//    }
//
//    printTree(node->right, level + 1);
//
//    for(int i = 0; i < level; i++) {
//        cout << "    ";
//    }
//
//    if(node->parent != nullptr) {
//        if(node == node->parent->left) {
//            cout << "L-->";
//        }
//        else {
//            cout << "R-->";
//        }
//    }
//
//    cout << node->info << "(" << node->nrLeftElements << ")" << endl;
//
//    printTree(node->left, level + 1);
//}

void SortedIndexedList::printSortedList() const {
    Node* currentNode = findMin(this->root);
    while(currentNode != nullptr) {
        cout << currentNode->info << " ";
        currentNode = getSuccessor(currentNode);
    }
    cout << endl;
}

void SortedIndexedList::printDebugInfo() const {
    cout << "Tree:" << endl;
    printTree(this->root, 0);

    cout << "List:" << endl;
    printSortedList();
}

/**
 * @brief Function that returns the successor of a node
 * @param node - the node whose successor we want to find
 * @return the successor of the node
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(logn)
 * @TimeComplexity-WorstCase: θ(n)
 *
 */
Node* SortedIndexedList::getSuccessor(Node* node) const {
    if(node == nullptr) {
        return nullptr;
    }

    if(node->right != nullptr) {
        return findMin(node->right);
    }

    Node* parentNode = node->parent;
    while(parentNode != nullptr && node == parentNode->right) {
        node = parentNode;
        parentNode = parentNode->parent;
    }

    return parentNode;
}

//TComp SortedIndexedList::remove(int pos) {
//    if (pos < 0 || pos >= this->sizeTree) {
//        throw invalid_argument("Invalid position in the list!");
//    }
//
//    Node* currentNode = this->root;
//    while (currentNode != nullptr) {
//        int leftSize = currentNode->nrLeftElements;
//        if (pos == leftSize) {
//            break;
//        } else if (pos < leftSize) {
//            currentNode = currentNode->left;
//        } else {
//            pos = pos - leftSize - 1;
//            currentNode = currentNode->right;
//        }
//    }
//
//    TComp removedElement = currentNode->info;
//
//    // Update the condition to check if the element's value matches the position
//    if (removedElement == pos) {
//        if (currentNode->left == nullptr && currentNode->right == nullptr) {
//            // Handle the case when the node has no children
//            if (currentNode == this->root) {
//                this->root = nullptr;
//            } else {
//                Node* parentNode = currentNode->parent;
//                if (parentNode->left == currentNode) {
//                    parentNode->left = nullptr;
//                } else {
//                    parentNode->right = nullptr;
//                }
//                this->updateNrLeftElements(parentNode);
//            }
//            delete currentNode;
//        } else {
//            // Handle the case when the node has one child
//            Node* childNode;
//            if (currentNode->left != nullptr) {
//                childNode = currentNode->left;
//            } else {
//                childNode = currentNode->right;
//            }
//
//            if (currentNode == this->root) {
//                this->root = childNode;
//                this->root->parent = nullptr;
//            } else {
//                Node* parentNode = currentNode->parent;
//                if (parentNode->left == currentNode) {
//                    parentNode->left = childNode;
//                } else {
//                    parentNode->right = childNode;
//                }
//                childNode->parent = parentNode;
//                this->updateNrLeftElements(parentNode);
//            }
//            delete currentNode;
//        }
//    }
//
//    this->sizeTree--;
//    return removedElement;
//}

TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= this->sizeTree) {
        throw std::invalid_argument("Invalid position in the list!");
    }

    Node* currentNode = this->root;
    while (currentNode != nullptr) {
        int leftSize = currentNode->nrLeftElements;
        if (i == leftSize) {
            break;
        } else if (i < leftSize) {
            currentNode = currentNode->left;
        } else {
            i = i - leftSize - 1;
            currentNode = currentNode->right;
        }
    }

    TComp removedElement = currentNode->info;

    if (currentNode->left == nullptr && currentNode->right == nullptr) {
        if (currentNode == this->root) {
            this->root = nullptr;
        } else {
            Node* parentNode = currentNode->parent;
            if (parentNode->left == currentNode) {
                parentNode->left = nullptr;
            } else {
                parentNode->right = nullptr;
            }
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    } else if (currentNode->left == nullptr) {
        if (currentNode == this->root) {
            this->root = currentNode->right;
            this->root->parent = nullptr;
        } else {
            Node* parentNode = currentNode->parent;
            if (parentNode->left == currentNode) {
                parentNode->left = currentNode->right;
            } else {
                parentNode->right = currentNode->right;
            }
            currentNode->right->parent = parentNode;
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    } else if (currentNode->right == nullptr) {
        if (currentNode == this->root) {
            this->root = currentNode->left;
            this->root->parent = nullptr;
        } else {
            Node* parentNode = currentNode->parent;
            if (parentNode->left == currentNode) {
                parentNode->left = currentNode->left;
            } else {
                parentNode->right = currentNode->left;
            }
            currentNode->left->parent = parentNode;
            this->updateNrLeftElements(parentNode);
        }
        delete currentNode;
    } else {
        Node* successorNode = currentNode->right;
        while (successorNode->left != nullptr) {
            successorNode = successorNode->left;
        }
        currentNode->info = successorNode->info;
        if (successorNode->right != nullptr) {
            successorNode->right->parent = successorNode->parent;
        }
        if (successorNode->parent->left == successorNode) {
            successorNode->parent->left = successorNode->right;
        } else {
            successorNode->parent->right = successorNode->right;
        }
        this->updateNrLeftElements(successorNode->parent);
        delete successorNode;
    }

    this->sizeTree--;
    return removedElement;
}


/**
 * @brief Function that returns the parent of a node
 * @param node
 * @return parent of the node
 */
Node* SortedIndexedList::getParent(Node* node) const {
    if(node == nullptr) {
        return nullptr;
    }

    return node->parent;
}

