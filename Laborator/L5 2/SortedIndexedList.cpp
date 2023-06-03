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

//void SortedIndexedList::add(TComp e) {
//
//    Node *currentNode = this->root;
//    Node *parentNode = nullptr;
//    Node *newNode = new Node;
//    newNode->info = e;
//    newNode->left = nullptr;
//    newNode->right = nullptr;
//    newNode->nrLeftElements = 0;
//
////    if(this->root == nullptr) {
////        this->root = newNode;
////        this->sizeTree++;
////        return;
////    }
//
//    //Case 1: Empty tree
//    if(this->root == nullptr) {
//        this->root = newNode;
//        this->sizeTree++;
//        return;
//    }
//
//    //Case 2: element is smaller than the root and the element is not equal to the root or is equal to the root
//
//    if(this->r(e, this->root->info) && root->right == nullptr) {
//        newNode->nrLeftElements = this->root->nrLeftElements + 1;
//        this->root->nrLeftElements = 0;
//        newNode->left = this->root;
//        this->root->parent = newNode;
//        this->root = newNode;
//        this->sizeTree++;
//        return;
//    }
//
//    while(currentNode != nullptr) {
//        parentNode = currentNode;
//        if(this->r(e, currentNode->info)) {
//            currentNode->nrLeftElements++;
//            currentNode = currentNode->left;
//        }
//        else {
//            currentNode = currentNode->right;
//        }
//    }
//    newNode -> parent = parentNode;
//
//    if(parentNode == nullptr) {
//        this->root = newNode;
//    }
//    else {
//        if(this -> r(e, parentNode->info)) {
//            parentNode -> left = newNode;
//        } else {
//            parentNode -> right = newNode;
//        }
//    }
//
//    this->sizeTree++;
//}

void SortedIndexedList::add(TComp e) {
    Node* newNode = new Node{e, nullptr, nullptr, nullptr, 0};
    sizeTree++;

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;
    bool isLeftChild = false;

    while (current != nullptr) {
        parent = current;

        if (r(e, current->info) && e != current->info) {
            current->nrLeftElements++;
            current = current->left;
            isLeftChild = true;
        } else {
            current = current->right;
            isLeftChild = false;
        }
    }

    newNode->parent = parent;

    if (isLeftChild) {
        parent->left = newNode;
    } else if (e == parent->info && parent->right == nullptr) {
        parent->right = newNode;
    } else {
        parent->right = newNode;
    }
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




void SortedIndexedList::updateNrLeftElementsSubtree(Node* node) {
    if (node == nullptr) {
        return;
    }

    int leftSize = 0;
    if (node->left != nullptr) {
        leftSize = node->left->nrLeftElements + 1;
    }

    node->nrLeftElements = leftSize;
    updateNrLeftElementsSubtree(node->left);
    updateNrLeftElementsSubtree(node->right);
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



void SortedIndexedList::printSortedList() const {
    Node* currentNode = findMin(this->root);
    while(currentNode != nullptr) {
        cout << currentNode->info << "(" << currentNode->nrLeftElements << ")" << " ";
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





//TComp SortedIndexedList::remove(int i) {
//
//}



Node* SortedIndexedList::getPredecessor(Node* node) const {
    if(node == nullptr) {
        return nullptr;
    }

    if(node->left != nullptr) {
        return findMax(node->left);
    }

    Node* parentNode = node->parent;
    while(parentNode != nullptr && node == parentNode->left) {
        node = parentNode;
        parentNode = parentNode->parent;
    }

    return parentNode;
}


Node *SortedIndexedList::findMax(Node *node) {
    Node *currentNode = node;
    while(currentNode->right != nullptr) {
        currentNode = currentNode->right;
    }
    return currentNode;
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




//TComp SortedIndexedList::remove(int i) {
//    if (i < 0 || i >= this->sizeTree) {
//        throw std::invalid_argument("Invalid position in the list!");
//    }
//
//    Node* prev = nullptr;
//    Node* current = this->root;
//    int position = 0;
//    while (current) {
//        if (i == position + current->nrLeftElements) {
//            break;
//        } else if (i < position + current->nrLeftElements) {
//            prev = current;
//            current = current->left;
//        } else {
//            prev = current;
//            position = position + current->nrLeftElements + 1;
//            current = current->right;
//        }
//    }
//
//    TComp removedElement = current->info;
//
//    if (current->left == nullptr && current->right == nullptr) {
//        decrease(i);
//        if (prev == nullptr) {
//            this->root = nullptr;
//        } else {
//            if (this->r(current->info, prev->info)) {
//                prev->left = nullptr;
//            } else {
//                prev->right = nullptr;
//            }
//            delete current;
//        }
//        this->sizeTree--;
//    } else if (current->left == nullptr || current->right == nullptr) {
//        decrease(i);
//
//        Node* descendant;
//        if (current->left == nullptr) {
//            descendant = current->right;
//        } else {
//            descendant = current->left;
//        }
//
//        if (prev == nullptr) {
//            // root
//            this->root = descendant;
//        } else {
//            // not root
//            if (this->r(current->info, prev->info)) {
//                // on left
//                prev->left = descendant;
//            } else {
//                // on right
//                prev->right = descendant;
//            }
//            delete current;
//        }
//        this->sizeTree--;
//    } else {
//        TComp successor = this->successor(current->info);
//        int index = this->search(successor);
//
//        this->remove(index);
//
//        current->info = successor;
//    }
//
//    return removedElement;
//}
//
//void SortedIndexedList::decrease(int i) const {
//    if (i >= this->sizeTree || i < 0) {
//        throw std::exception();
//    }
//
//    Node* current = this->root;
//    int position = 0;
//    while (current) {
//        if (i == position + current->nrLeftElements) {
//            return;
//        } else if (i < position + current->nrLeftElements) {
//            // left
//            current->nrLeftElements--;
//            current = current->left;
//        } else {
//            // right
//            position = position + current->nrLeftElements + 1;
//            current = current->right;
//        }
//    }
//}
//
//TComp SortedIndexedList::successor(TComp e) {
//    Node* current = this->root;
//    while (current->info != e) {
//        if (this->r(e, current->info)) {
//            current = current->left;
//        } else {
//            current = current->right;
//        }
//    }
//    if (current->right) {
//        current = current->right;
//        while (current->left) {
//            current = current->left;
//        }
//        return current->info;
//    } else {
//        TComp p = this->parentOfNode(current->info);
//        Node* parent = this->root;
//
//        while (parent->info != p) {
//            if (this->r(p, current->info)) {
//                current = current->left;
//            } else {
//                current = current->right;
//            }
//        }
//
//        while (parent && parent->left != current) {
//            current = parent;
//            TComp p = this->parentOfNode(current->info);
//            Node* parent = this->root;
//
//            while (parent->info != p) {
//                if (this->r(p, current->info)) {
//                    current = current->left;
//                } else {
//                    current = current->right;
//                }
//            }
//        }
//        return p;
//    }
//}
//
//TComp SortedIndexedList::parentOfNode(TComp e)
//{
//    if (this->root->info == e)
//        return -1;
//    Node* current = this->root;
//
//    while (current && current->left->info != e && current->right->info != e)
//    {
//        if (!this->r(current->info, e))
//            current = current->left;
//        else
//            current = current->right;
//    }
//
//    return current->info;
//
//}



