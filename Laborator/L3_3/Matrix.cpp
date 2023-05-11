#include "Matrix.h"
#include <exception>

#include "Matrix.h"
#include <exception>

Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0)
        throw std::out_of_range("Invalid dimensions");

    lines = nrLines;
    columns = nrCols;
    capacity = 5;
    size = 0;

    nodes = new Node[capacity];

    head = 0;
    nodes[head].line = -1;
    nodes[head].column = -1;
    nodes[head].nextLine = head;
    nodes[head].nextColumn = head;

    firstEmpty = 1;

    for (int i = 1; i < capacity - 1; ++i) {
        nodes[i].nextLine = i + 1;
        nodes[i].nextColumn = i + 1;
    }

    nodes[capacity - 1].nextLine = head;
    nodes[capacity - 1].nextColumn = head;


    // create a circular connection between the last and the first element in each line and column
    for (int i = 0; i < lines; i++) {
        int lastLine = i * columns + columns - 1;
        nodes[lastLine].nextLine = nodes[head].nextLine;
        nodes[head].nextLine = i * columns;
    }
    for (int i = 0; i < columns; i++) {
        int lastColumn = (lines - 1) * columns + i;
        nodes[lastColumn].nextColumn = nodes[head].nextColumn;
        nodes[head].nextColumn = i;
    }
}

int Matrix::nrLines() const {
    return lines;
}

int Matrix::nrColumns() const {
    return columns;
}


TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();


    int index = nodes[0].nextLine;

    while (index != 0) {
        if (nodes[index].line == i && nodes[index].column == j)
            return nodes[index].value;
        if (nodes[index].line > i)
            return NULL_TELEM;
        index = nodes[index].nextLine;
    }

    return NULL_TELEM;

}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();

    int prevValue = NULL_TELEM;
    int index = nodes[0].nextLine;
    int prevIndex = head;

    // find the node at (i, j) and its predecessor in the linked list
    while (index != 0) {
        if (nodes[index].line == i && nodes[index].column == j) {
            prevValue = nodes[index].value;
            break;
        }
        if (nodes[index].line > i)
            break;
        prevIndex = index;
        index = nodes[index].nextLine;
    }

    // case 1: non-zero -> zero
    if (e == NULL_TELEM) {
        if (prevValue != NULL_TELEM) { // node exists
            nodes[index].value = NULL_TELEM;

            // remove the node from the linked list
            nodes[prevIndex].nextLine = nodes[index].nextLine;
            nodes[nodes[index].nextColumn].nextColumn = nodes[index].nextColumn;
            nodes[index].nextLine = firstEmpty;
            firstEmpty = index;

            size--;

            automaticResize();
        }
    }
        // case 2: zero -> non-zero
    else if (prevValue == NULL_TELEM) { // node does not exist
        // add a new node to the linked list
        int newIndex = firstEmpty;
        firstEmpty = nodes[firstEmpty].nextLine;
        nodes[newIndex].line = i;
        nodes[newIndex].column = j;
        nodes[newIndex].value = e;
        nodes[newIndex].nextLine = nodes[prevIndex].nextLine;
        nodes[newIndex].nextColumn = nodes[j].nextColumn;
        nodes[prevIndex].nextLine = newIndex;
        nodes[nodes[j].nextColumn].nextColumn = newIndex;

        size++;

        automaticResize();
    }
        // case 3: non-zero -> non-zero
    else {
        nodes[index].value = e;
    }

    return prevValue;
}

//TElem Matrix::modify(int i, int j, TElem e) {
//    if (i < 0 || i >= lines || j < 0 || j >= columns)
//        throw std::exception();
//
//    int prevValue = NULL_TELEM;
//    int index = nodes[0].nextLine;
//    int prevIndex = head;
//
//    // find the node at (i, j) and its predecessor in the linked list
//    while (index != 0) {
//        if (nodes[index].line == i && nodes[index].column == j) {
//            prevValue = nodes[index].value;
//            break;
//        }
//        if (nodes[index].line > i)
//            break;
//        prevIndex = index;
//        index = nodes[index].nextLine;
//    }
//
//    // case 1: non-zero -> zero
//    if (e == NULL_TELEM) {
//        if (prevValue != NULL_TELEM) {
//            // remove the node at (i, j)
//            nodes[prevIndex].nextLine = nodes[index].nextLine;
//            nodes[prevIndex].nextColumn = nodes[index].nextColumn;
//            nodes[index].nextLine = firstEmpty;
//            firstEmpty = index;
//            size--;
//        }
//    }
//        // case 2: zero -> non-zero or non-zero -> non-zero
//    else {
//        if (prevValue == NULL_TELEM) {
//            // create a new node at (i, j)
//            if (firstEmpty == capacity)
//                automaticResize();
//            int newIndex = firstEmpty;
//            firstEmpty = nodes[firstEmpty].nextLine;
//            nodes[newIndex].line = i;
//            nodes[newIndex].column = j;
//            nodes[newIndex].value = e;
//            nodes[newIndex].nextLine = nodes[prevIndex].nextLine;
//            nodes[newIndex].nextColumn = nodes[prevIndex].nextColumn;
//            nodes[prevIndex].nextLine = newIndex;
//            nodes[prevIndex].nextColumn = newIndex;
//            size++;
//        }
//        else {
//            // update the value at (i, j)
//            nodes[index].value = e;
//        }
//    }
//
//    return prevValue;
//}

//TElem Matrix::modify(int i, int j, TElem e) {
//    if (i < 0 || i >= lines || j < 0 || j >= columns)
//        throw std::out_of_range("Invalid position");
//
//    int prev = head;
//    int current = nodes[head].nextLine;
//
//    // search for the node with the given coordinates
//    while (current != head && (nodes[current].line < i || (nodes[current].line == i && nodes[current].column < j))) {
//        prev = current;
//        current = nodes[current].nextLine;
//    }
//
//    // if the node exists, update its value
//    if (current != head && nodes[current].line == i && nodes[current].column == j) {
//        TElem prevValue = nodes[current].value;
//        nodes[current].value = e;
//        return prevValue;
//    }
//
//    // if the node does not exist, add a new one
//    int newNode = firstEmpty;
//    firstEmpty = nodes[firstEmpty].nextLine;
//
//    nodes[newNode].line = i;
//    nodes[newNode].column = j;
//    nodes[newNode].value = e;
//
//    nodes[newNode].nextLine = current;
//    nodes[prev].nextLine = newNode;
//
//    // update the circular connections for the column
//    prev = head;
//    current = nodes[head].nextColumn;
//
//    while (current != head && (nodes[current].column < j || (nodes[current].column == j && nodes[current].line < i))) {
//        prev = current;
//        current = nodes[current].nextColumn;
//    }
//
//    nodes[newNode].nextColumn = current;
//    nodes[prev].nextColumn = newNode;
//
//    size++;
//    automaticResize();
//
//    return NULL_TELEM;
//}


Matrix::~Matrix() {
    delete[] nodes;
}

void Matrix::automaticResize() {
    if (firstEmpty == -1)
        resize(capacity * 2);
    else if (size <= capacity / 4 && capacity >= 10)
        resize(capacity / 2);
}

void Matrix::resize(int newCapacity) {
    if (newCapacity < size)
        throw std::invalid_argument("New capacity cannot be smaller than the actual size");

    Node *newNodes = new Node[newCapacity];

    for (int i = 0; i < newCapacity; ++i) {
        newNodes[i] = nodes[i];
    }

    for (int i = capacity; i < newCapacity; ++i) {
        newNodes[i].nextLine = i + 1;
        newNodes[i].nextColumn = i + 1;
    }

    newNodes[newCapacity - 1].nextLine = -1;
    newNodes[newCapacity - 1].nextColumn = -1;

    firstEmpty = capacity;

    capacity = newCapacity;

    delete[] nodes;

    nodes = newNodes;
}

void Matrix::print() const {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            cout << element(i, j) << " ";
        }
        cout << endl;
    }
}



