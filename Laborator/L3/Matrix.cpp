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

    lineHead = new int[nrLines];
    columnHead = new int[nrCols];

    lastLine = new int[nrLines];
    lastColumn = new int[nrCols];

    firstEmpty = 0;

    for (int i = 0; i < nrLines; ++i)
        lineHead[i] = lastLine[i] = -1;

    for (int i = 0; i < nrCols; ++i)
        columnHead[i] = lastColumn[i] = -1;

    lastLine[nrLines - 1] = (nrLines - 1) * columns;
    nodes[lastLine[nrLines - 1]].nextLine = lineHead[0];

    lastColumn[columns - 1] = columns - 1;
    nodes[lastColumn[columns - 1]].nextColumn = columnHead[0];



    for (int i = 0; i < capacity - 1; ++i) {
        nodes[i].nextLine = i + 1;
        nodes[i].nextColumn = i + 1;
    }

    nodes[capacity - 1].nextLine = -1;
    nodes[capacity - 1].nextColumn = -1;


    // create a circular connection between the last and the first element in each line and column
    for (int i = 0; i < lines; i++) {
        if (lastLine[i] != -1) {
            nodes[lastLine[i]].nextLine = lineHead[i];
        }
    }
//    for (int i = 0; i < columns; i++) {
//        if (lastColumn[i] != -1) {
//            nodes[lastColumn[i]].nextColumn = columnHead[i];
//        }
//    }
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

    int index = lineHead[i];

    while (index != -1) {
        if (nodes[index].column == j)
            return nodes[index].value;
        index = nodes[index].nextLine;
    }

    return NULL_TELEM;
}

/**
 * @brief This is the modify function of the matrix
 * @details The function first checks if the given position is valid. If it is, it searches for the element in the
 * matrix. It does this by traversing the linked list of nodes corresponding to the row index i. The variable
 * index is initialized with the index of the first node in the list. The variable prevIndex is used to keep track of
 * the node that comes before the current node being searched. PrevIndex is initialized with -1. A while loop is used to
 * traverse the linked list until the node containing the column index j is found or the end of the linked list is
 * reached. If the node containing the column index j is found, the function updates the value of the node with the new
 * value e and returns the old value of the node. If the new value e is equal to NULL_TELEM, then the function removes
 * the node from both row and column linked lists. If the node is the head of the row linked list, then the head is
 * updated to point to the next node in the list. Otherwise, the nextLine pointer of the node before the current node
 * is updated to point to the next node in the list. the same is done for the column linked list. After the node is
 * removed from the linked lists, it is added to the list of empty nodes to be reused later. The var size is decremented
 * by 1. If the new value e is not equal to NULL_TELEM and the node was not found in the linked list, then a new node is
 * created and it is inserted into the linked list. IF there are no empty nodes available, then the function
 * automatically resizes the matrix to create more nodes. The new node is assigned the row index i, col j and val e. The
 * function then finds the correct position to insert the node in both the row and column linked lists, It does this by
 * traversing the linked list for the column index j. A while loop is used to loop through the linked list until the
 * correct position is found. The same is done for the row linked list. Once the position is found, the node is inserted
 * into the linked list by updating the nextLine and nextColumn pointers. The function returns NULL_TELEM to indicate
 * that no old value was replaced if the node was not found in the linked list.
 *
 * @param i
 * @param j
 * @param e
 * @return
 */
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();

    int index = lineHead[i];
//    int prevIndex = -1;
// initialize prevIndex to the last node of the line
    int prevIndex = lastLine[i];


    while (index != -1) {
        if (nodes[index].column == j) {
            TElem oldValue = nodes[index].value;
            nodes[index].value = e;
            if (e == NULL_TELEM) {
                if (prevIndex == -1) {
                    lineHead[i] = nodes[index].nextLine;
                } else {
                    nodes[prevIndex].nextLine = nodes[index].nextLine;
                }
                int colIndex = columnHead[j];
                int prevColIndex = -1;
                while (colIndex != -1 && colIndex != index) {
                    prevColIndex = colIndex;
                    colIndex = nodes[colIndex].nextColumn;
                }
                if (prevColIndex == -1) {
                    columnHead[j] = nodes[index].nextColumn;
                } else {
                    nodes[prevColIndex].nextColumn = nodes[index].nextColumn;
                }
                nodes[index].nextLine = firstEmpty;
                firstEmpty = index;
                size--;
                automaticResize();
            }
            return oldValue;
        }
        prevIndex = index;
        index = nodes[index].nextLine;
    }


    if (e == NULL_TELEM)
        return NULL_TELEM;
    if (firstEmpty == -1) {
        automaticResize();
    }

    int newNodeIndex = firstEmpty;
    firstEmpty = nodes[firstEmpty].nextLine;

    nodes[newNodeIndex].line = i;
    nodes[newNodeIndex].column = j;
    nodes[newNodeIndex].value = e;

    if (lineHead[i] == -1 || nodes[lineHead[i]].column > j) {
        nodes[newNodeIndex].nextLine = lineHead[i];
        lineHead[i] = newNodeIndex;
    } else {
        nodes[newNodeIndex].nextLine = nodes[prevIndex].nextLine;
        nodes[prevIndex].nextLine = newNodeIndex;
    }

    int colIndex = columnHead[j];
    int prevColIndex = -1;

    while (colIndex != -1 && nodes[colIndex].line < i) {
        prevColIndex = colIndex;
        colIndex = nodes[colIndex].nextColumn;
    }

    if (prevColIndex == -1) {
        nodes[newNodeIndex].nextColumn = columnHead[j];
        columnHead[j] = newNodeIndex;
    } else {
        nodes[newNodeIndex].nextColumn = nodes[prevColIndex].nextColumn;
        nodes[prevColIndex].nextColumn = newNodeIndex;
    }

    size++;

//    lastLine[i] = index;
//    lastColumn[j] = colIndex;

    return NULL_TELEM;

}


Matrix::~Matrix() {
    delete[] nodes;
    delete[] lineHead;
    delete[] columnHead;
    delete[] lastLine;
    delete[] lastColumn;
}



void Matrix::automaticResize() {
    if(firstEmpty == -1)
        resize(capacity * 2);
    else if(size <= capacity / 4 && capacity >= 10)
        resize(capacity / 2);
}

void Matrix::resize(int newCapacity) {
    if(newCapacity < size)
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