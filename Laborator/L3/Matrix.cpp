#include "Matrix.h"
#include <exception>

Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0)
        throw std::exception();

    lines = nrLines;
    columns = nrCols;
    capacity = 4 * (nrLines + nrCols);
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

    for (int i = 0; i < capacity - 1; ++i) {
        nodes[i].nextLine = i + 1;
        nodes[i].nextColumn = i + 1;
    }

    nodes[capacity - 1].nextLine = -1;
    nodes[capacity - 1].nextColumn = -1;
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

//TElem Matrix::modify(int i, int j, TElem e) {
//    if (i < 0 || i >= lines || j < 0 || j >= columns)
//        throw std::exception();
//
//    int index = lineHead[i];
//    int prevIndex = -1;
//
//    while (index != -1) {
//        if (nodes[index].column == j) {
//            TElem oldValue = nodes[index].value;
//            nodes[index].value = e;
//            return oldValue;
//        }
//        prevIndex = index;
//        index = nodes[index].nextLine;
//    }
//
//    if (e == NULL_TELEM)
//        return NULL_TELEM;
//
//    if (firstEmpty == -1) {
//        automaticResize();
//    }
//
//    int newNodeIndex = firstEmpty;
//    firstEmpty = nodes[firstEmpty].nextLine;
//
//    nodes[newNodeIndex].line = i;
//    nodes[newNodeIndex].column = j;
//    nodes[newNodeIndex].value = e;
//
//    if (lineHead[i] == -1 || nodes[lineHead[i]].column > j) {
//        nodes[newNodeIndex].nextLine = lineHead[i];
//        lineHead[i] = newNodeIndex;
//    } else {
//        nodes[newNodeIndex].nextLine = nodes[prevIndex].nextLine;
//        nodes[prevIndex].nextLine = newNodeIndex;
//    }
//
//    int colIndex = columnHead[j];
//    int prevColIndex = -1;
//
//    while (colIndex != -1 && nodes[colIndex].line < i) {
//        prevColIndex = colIndex;
//        colIndex = nodes[colIndex].nextColumn;
//    }
//
//    if (prevColIndex == -1) {
//        nodes[newNodeIndex].nextColumn = columnHead[j];
//        columnHead[j] = newNodeIndex;
//    } else {
//        nodes[newNodeIndex].nextColumn = nodes[prevColIndex].nextColumn;
//        nodes[prevColIndex].nextColumn = newNodeIndex;
//    }
//
//    size++;
//
//    return NULL_TELEM;
//}


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();

    int index = lineHead[i];
    int prevIndex = -1;

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

    for (int i = 0; i < capacity; ++i) {
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
