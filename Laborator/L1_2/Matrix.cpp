#include "Matrix.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols) {
    rows = nrLines;
    columns = nrCols;
    columnCapacity = nrCols;
    rowIndexes = new int[nrLines];
    columnPointers = new int[columnCapacity];
    elementsCapacity = 10;
    elements = new TElem[10];

    for (int i = 0; i < columns; i++)
        columnPointers[i] = NULL_TELEM;
}

int Matrix::nrLines() const {
    return rows;
}

int Matrix::nrColumns() const {
    return columns;
}

TElem Matrix::element(int i, int j) {
    if (i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }
    int start = columnPointers[j];
    int end = columnPointers[j + 1];

    //start = 1
    //end = 4 - 1 = 3

    for (int k = start; k < end; k++) {
        if (rowIndexes[k] == i)
            return elements[k];
    }

    return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }

    // Find the start and end indices for the j-th column
    int start = columnPointers[j];
    int end = columnPointers[j + 1];

    // Search for the i-th row index in the j-th column
    int k = start;
    while (k < end && rowIndexes[k] < i)
        k++;

    // If the element already exists, update its value and return the previous value
    if (k < end && rowIndexes[k] == i) {
        TElem previousValue = elements[k];
        elements[k] = e;
        return previousValue;
    }

        // If the element doesn't exist, insert it and shift the remaining elements
    else {
        // Resize the row indexes and elements arrays if necessary
        elementsSize++;
        rows++;
        automaticResizeRowIndexes();
        automaticElementsIndexes();

        // Shift the remaining elements in the column
        for (int l = end - 1; l >= k; l--) {
            elements[l + 1] = elements[l];
            rowIndexes[l + 1] = rowIndexes[l];
        }

        // Insert the new element
        elements[k] = e;
        rowIndexes[k] = i;

        // Update the column pointers for subsequent columns
        for (int l = j + 1; l <= columns; l++) {
            columnPointers[l]++;
        }

        // Return the default value for a newly inserted element
        return NULL_TELEM;
    }
}

void Matrix::print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int start = columnPointers[j];
            int end = columnPointers[j + 1];

            bool found = false;
            for (int k = start; k < end; k++) {
                if (rowIndexes[k] == i) {
                    std::cout << elements[k] << " ";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }
}

void Matrix::resizeRowIndexes(int newCapacity) {
    if (newCapacity < rows)
        throw std::out_of_range("Index out of range");

    int *newArray = new int[newCapacity];
    for (int i = 0; i < rows; i++)
        newArray[i] = rowIndexes[i];

    delete[] rowIndexes;
    rowIndexes = newArray;
    rowCapacity = newCapacity;
}

void Matrix::resizeElements(int newCapacity) {
    if (newCapacity < elementsSize)
        throw std::out_of_range("Index out of range");

    auto *newArray = new TElem[newCapacity];
    for (int i = 0; i < elementsSize; i++)
        newArray[i] = elements[i];

    delete[] elements;
    elements = newArray;
    elementsCapacity = newCapacity;
}

void Matrix::automaticResizeRowIndexes() {
    if (rows == rowCapacity)
        resizeRowIndexes(rowCapacity * 2);
    else if (rows <= rowCapacity / 4 && rowCapacity >= 10)
        resizeRowIndexes(rowCapacity / 2);
}

void Matrix::automaticElementsIndexes() {
    if (elementsSize == elementsCapacity)
        resizeElements(elementsCapacity * 2);
    if (elementsSize == elementsCapacity / 4 && elementsCapacity >= 10)
        resizeElements(this->elementsCapacity / 2);
}

Matrix::~Matrix() {
    delete[] elements;
    delete[] rowIndexes;
    delete[] columnPointers;
}
