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
    Node* newNode = new Node;
    newNode->info = e;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent = nullptr;
    newNode->nrLeftElements = 0;

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





TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= sizeTree)
        throw exception();

    Node* current = root;
    int currentPosition = root->nrLeftElements;

    while (currentPosition != i) {
        if (i < currentPosition) {
            current = current->left;
            currentPosition--;
            currentPosition -= (current->parent->nrLeftElements - current->nrLeftElements - 1);
            current->parent->nrLeftElements--;
        } else {
            current = current->right;
            currentPosition++;
            currentPosition += current->nrLeftElements;
        }
    }

    TComp deletedValue = current->info;
    Node* parent = current->parent;

    if (current == root) {
        if (root->left == nullptr && root->right == nullptr) {
            delete current;
            root = nullptr;
        } else if (root->left == nullptr && root->right != nullptr) {
            root = root->right;
            delete current;
            root->parent = nullptr;
        } else if (root->left != nullptr && root->right == nullptr) {
            root = root->left;
            delete current;
            root->parent = nullptr;
        } else {
            Node* nextNode = root->right;

            while (nextNode->left != nullptr) {
                nextNode->nrLeftElements--;
                nextNode = nextNode->left;
            }

            root->info = nextNode->info;

            if (nextNode->parent->left == nextNode)
                nextNode->parent->left = nextNode->right;
            else
                nextNode->parent->right = nextNode->right;

            if (nextNode->right != nullptr)
                nextNode->right->parent = nextNode->parent;

            delete nextNode;
        }
    } else {
        if (current->left == nullptr && current->right == nullptr) {
            if (parent->left == current)
                parent->left = nullptr;
            else
                parent->right = nullptr;
            delete current;
        } else if (current->left == nullptr && current->right != nullptr) {
            if (parent->left == current)
                parent->left = current->right;
            else
                parent->right = current->right;
            current->right->parent = parent;
            delete current;
        } else if (current->left != nullptr && current->right == nullptr) {
            if (parent->left == current)
                parent->left = current->left;
            else
                parent->right = current->left;
            current->left->parent = parent;
            delete current;
        } else {
            Node* nextNode = current->right;

            while (nextNode->left != nullptr) {
                nextNode->nrLeftElements--;
                nextNode = nextNode->left;
            }

            current->info = nextNode->info;

            if (nextNode->parent->left == nextNode)
                nextNode->parent->left = nextNode->right;
            else
                nextNode->parent->right = nextNode->right;

            if (nextNode->right != nullptr)
                nextNode->right->parent = nextNode->parent;

            delete nextNode;
        }
    }

    sizeTree--;
    return deletedValue;
}


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