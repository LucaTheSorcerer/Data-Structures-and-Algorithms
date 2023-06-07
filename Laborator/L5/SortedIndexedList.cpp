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
 * @brief function used to return an element
 * @details function used to retrieve the element at a specific position in the list. The function first checks if the index
 * 'i' is valid. If it is not, an exception is thrown. If the index is valid, the function initializes a current node
 * pointer to the root of the binary search tree and a position variable to 0. The position variable is used to keep
 * track of the current position within the sorted indexed list while traversing the binary search tree. Then the
 * function enters a loop that continues until the current node pointer is null, indicating the end of the binary search
 * tree or the element at the given position has been successfully found. In the loop the function first computes the
 * number of elements in the left subtree. This value represents the number of elements in the sorted indexed list that
 * are smaller that the current node's value. The function compares the sum of the current position and left size with
 * the target index i to determine the relative position of the target index withing the current subtree.
 * If the target index marches the sum of the current position and leftSize, it means that the current node's value
 * is the element at the desired index i. In this case the function returns the current node's value.
 * If the target index is less than the sum of the current position and leftSize, it means that desired element within
 * the left subtree of the current node. The function updates the current node pointer to its left child and continues
 * the search in that subtree.
 * If the target index is greater than the sum of the current position and leftSize, it means the desired element lies
 * within the right subtree of the current node. The function updates the position variable to the sum of the current
 * position, leftSize and 1 to account for the current node, and updates the current node pointer to its right child
 * If the loop ends without finding the element at the target index, if means the index is invalid or the element does
 * not exist in the list and the function returns NULL_TCOMP
 * @param i - the position of the element
 * @return the element from the given position
 * @throws exception if the position is not valid
 * @TimeComplexity-BestCase: θ(1) -> when the element is located at the root of the binary search tree
 * @TimeComplexity-AverageCase: θ(log(n)) -> each iteration reduces the search space by half
 * @TimeComplexity-WorstCase: θ(n) -> when the binary search tree is skewed, either entirely to the lift or to the right
 *                                    this result in a linear search traversing each level
 * @note n is number of elements in the binary search tree
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

/**
 * @brief function used to find the index of a given element e within the sorted indexed list
 * @details It starts by initializing a current node pointer to the root of the binary search tree and a position
 * variable to 0.
 * The function enters a loop that continues until the current node pointer becomes nullptr, indicating that the end of
 * the tree has been reached or the element has been found.
 * Withing the loop, the function compares the value of the current node with the target e and if they are equal it
 * means that the target element has been found. In this case, the function returns the sum of the current position and
 * the number of elements in the the left subtree of the current node. This sum represents the index of the target
 * element withing the sorted indexed list.
 * If the current node's value is greater than the target element 'e', it means that our desired element lies within
 * the left subtree of the current node. the function then updates the current node pointer to its left child and
 * continues the search in that subtree
 * If the current pointer is less than the target element 'e', it means that the desired element lies within the right
 * subtree of the current node. The position variable is updated to the sum of the current position, the number of
 * elements in the left subtree of the current node, and 1 to keep account of the current node, and updates the current
 * node pointer to its right child. The search continues in the right subtree.
 * If the loop ends without finding the target element, it means that the element is not present in the list, and it
 * returns -1
 * @param e given element
 * @TimeComplexity-BestCase: θ(1) -> when the element is located at the root of the binary search tree
 * @TimeComplexity-AverageCase: θ(log(n)) -> each iteration reduces the search space by half
 * @TimeComplexity-WorstCase: θ(n) -> when the binary search tree is skewed, either entirely to the lift or to the right
 *                                    this result in a linear search traversing each level
 * @note n is number of elements in the binary search tree
 */

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


/**
 * @brief function used to add a new element to the sorted indexed list
 * @details It starts by creating a new node with the given element e and initializing its left, right and parent, and
 * the nrLeftElements is set to 0
 * The sizeTree variable, which keeps track of the number of elements in the tree, is incremented by 1 to indicate that
 * a new element has been added. If the root of the binary tree is nullptr, it means that the tree is empty and the
 * newly created node is set as the root of the tree, because the tree is empty.
 * If the tree is not empty, the function enters a loop to find the correct position to insert the newly created node.
 * The loop continues until the current node pointer becomes nullptr, indicating that the end of the tree has been.
 * In the loop, the function updates the parent pointer to keep track of the current node's parent. If the given element
 * e is less than the current node's value, the function increments the nrLeftElements count of the current node and
 * moves to the left child by updating the current pointer. It also sets the isLeftChilds flag to true to keep track
 * of the fact that the new node will be inserted as the left child.
 * If the given element e is greater than or equal to the current node's value the function moves to the right child by
 * updating the current pointer. It sets the isLeftChild flag to false to indicate that the new node will be inserted as
 * the right child.
 * After finding the appropriate position, the parent pointer is assigned as the parent of the new node.
 * If the given element is equal to the paren node's value and the right child of the parent node is nullptr, the new
 * node is inserted as the right child.
 * @param e given element to be added
 * @TimeComplexity-BestCase: θ(1) -> the tree is empty and the function insert the new element as the root of the tree
 * @TimeComplexity-AverageCase: θ(log(n)) -> each iteration reduces the search space by half on average
 * @TimeComplexity-WorstCase: θ(n) -> the binary tree is entirely to left or to the right and the function needs to
 * traverse the entire height of the tree to find the correct position for insertion
 * @note n is number of elements in the binary search tree
 */
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
 * @brief Function that recursively destroys the tree
 * @details First it checks if the given node is not null ptr indicating that the tree is not empty. If the node is not
 * empty, the function recursively calls itself to destroy the left and right subtrees. After destroying the subtrees,
 * the function deletes the current node.
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




/**
 * @brief Function that deletes an element from the sorted indexed list at a specific position
 * @details The function first checks if the given position is valid. If it is, it initializes a pointer current to the
 * root of the tree and an integer currentPosition to keep track of the number of elements in the left subtree of the
 * root. The function enters a loop until the current position matches the given index. Inside the loop, the function
 * checks whether the given index is smaller than the current position. If it is, it moves to the left subtree of the
 * current node, updates the current position and the number of left element accordingly, and decrements the number of
 * of elements of the parent node.
 * If the given index is bigger than the current position, it moves to the right subtree of the current node. updates
 * the current position by adding the number of elements in the left subtree of the current node, and continues the loop
 * until the current position matches the given index.
 * The function handles different cases:
 * @Case1-Node to be deleted is the root with no children: If the root has no children, it means that the tree contains
 * only one node. In this case, the root is deleted and set to nullptr.
 * @Case2-Node to be deleted is the root with a right child: If the root has no left child but a right child, the right
 * child becomes the new root and the root pointer is then updated to point to the right child. The parent of the new
 * root is set ti nullptr.
 * @Case3-Node to be deleted is the root with a left child: If the root has no right child but a left child, the left
 * child becomes the new root and the root pointer is updated to point to the left child. The parent of the new root is
 * set to nullptr.
 * @Case4-Node to be deleted is the root with both left and right child: If the root has both a left and a right child,
 * a replacement node needs to be found. The replacement node is found by traversing to the right subtree of the root
 * and then going as far to the left. The replacement node will have the next smallest value compared to the current
 * root, and this ensures that the sorted order is maintained. The value of the replacement node is copied to the
 * current node. If the replacement node has a right child, it takes the places of the replacement node and if the
 * node doesn't have a right child, its parent's left child is updated to nullptr. Then the replacement is deleted.
 * @Case5-Node to be deleted is not the root and also has not children: If the node to be deleted is a leaf, its
 * parent's reference to the node is updated to nullptr.
 * @Case6-Node to be deleted is not the root and has a right child: If the node to be deleted has a right child, the
 * right child takes its place. The parent's reference to the node is updated to point to the right child, and then the
 * right child's parent is updated to the parent.
 * @Case7-Node to be deleted is not the root and has a left child: If the node to be deleted has a left child but no
 * right child, the left child takes its place. The parent's reference to the node is updated to point to the left and
 * the left child's parent is updated to the parent.
 * @Case8-Node to be deleted is not the root and has both left and right child: If the node to be deleted has both a
 * left and a right child, a replacement node needs to be found by following the same process as in Case4.
 * @param i - the position of the element to be deleted
 * @return the deleted element
 * @throws exception if the given position is invalid
 * @TimeComplexity-BestCase: θ(1) -> when the node to be deleted is the root
 * @TimeComplexity-AverageCase: θ(log(n))
 * @TimeComplexity-WorstCase: θ(n) -> when the node to be deleted is a leaf so at the deepest level of the tree
 */
TComp SortedIndexedList::remove(int i) {
    if (i < 0 || i >= sizeTree)
        throw invalid_argument("Invalid position in the list!");

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


//TComp SortedIndexedList::remove(int i) {
//    if (i < 0 || i >= sizeTree)
//        throw exception();
//
//    Node* current = root;
//    int currentPosition = root->nrLeftElements;
//
//    while (currentPosition != i) {
//        if (i < currentPosition) {
//            current = current->left;
//            currentPosition--;
//            currentPosition -= (current->parent->nrLeftElements - current->nrLeftElements - 1);
//            current->parent->nrLeftElements--;
//        } else {
//            current = current->right;
//            currentPosition++;
//            currentPosition += current->nrLeftElements;
//        }
//    }
//
//    TComp deletedValue = current->info;
//    Node* parent = current->parent;
//
//    if (current == root) {
//        if (root->left == nullptr) {
//            root = root->right;
//            if (root != nullptr)
//                root->parent = nullptr;
//        } else if (root->right == nullptr) {
//            root = root->left;
//            if (root != nullptr)
//                root->parent = nullptr;
//        } else {
//            Node* nextNode = root->right;
//
//            while (nextNode->left != nullptr) {
//                nextNode->nrLeftElements--;
//                nextNode = nextNode->left;
//            }
//
//            root->info = nextNode->info;
//            if (nextNode->parent->left == nextNode)
//                nextNode->parent->left = nextNode->right;
//            else
//                nextNode->parent->right = nextNode->right;
//
//            if (nextNode->right != nullptr)
//                nextNode->right->parent = nextNode->parent;
//
//            delete nextNode;
//        }
//    } else {
//        if (current->left == nullptr && current->right == nullptr) {
//            if (parent->left == current)
//                parent->left = nullptr;
//            else
//                parent->right = nullptr;
//            delete current;
//        } else if (current->left == nullptr) {
//            if (parent->left == current)
//                parent->left = current->right;
//            else
//                parent->right = current->right;
//            current->right->parent = parent;
//            delete current;
//        } else if (current->right == nullptr) {
//            if (parent->left == current)
//                parent->left = current->left;
//            else
//                parent->right = current->left;
//            current->left->parent = parent;
//            delete current;
//        } else {
//            Node* nextNode = current->right;
//
//            while (nextNode->left != nullptr) {
//                nextNode->nrLeftElements--;
//                nextNode = nextNode->left;
//            }
//
//            current->info = nextNode->info;
//            if (nextNode->parent->left == nextNode)
//                nextNode->parent->left = nextNode->right;
//            else
//                nextNode->parent->right = nextNode->right;
//
//            if (nextNode->right != nullptr)
//                nextNode->right->parent = nextNode->parent;
//
//            delete nextNode;
//        }
//    }
//
//    sizeTree--;
//    return deletedValue;
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