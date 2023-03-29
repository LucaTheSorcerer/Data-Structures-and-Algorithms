#include "Matrix.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;


/**
 * @brief This is the class contractor
 * @param nrLines - the number of lines
 * @param nrCols - the number of columns of the matrix
 */
Matrix::Matrix(int nrLines, int nrCols) {

    /**
 * @details We implement the constructor so that it can initialize the private members
 * values and rowIndexes arrays can be allocated with the initial capacity of
 * columns and the columnPointers can be initialized with the size of columns+1.
 * Also, the first element of columnPointers is set to 0 and the rest are set to size
 * We initialize three dynamic arrays that hold the elements, row indexes and column_vec pointers so we can represent
 * the ccs sparse matrix format
 */
    this->rows = nrLines; //nr_lines
    this->columns = nrCols; //nr_cols

    this->rowSize = 0; //line_size
    this->rowCapacity = 5; //line_capacity

    //elementsCapacity = 10;
    this->elements = new TElem[this->rowCapacity]{NULL_TELEM};
    this->columnPointers = new int[this->columns + 1]{NULL_TELEM};
    this->rowIndexes = new int[this->rowCapacity]{NULL_TELEM};

}

/**
 * @brief return the number of rows in the matrix
 * @params  -
 * @Best_case  θ(1)
 * @Medium_case  θ(1)
 * @Amortized_case  θ(1)
 * @Worst_case θ(1)
 */
int Matrix::nrLines() const {
    return this->rows;
}

/**
 * @brief return the number of columns in the matrix
 * @params -
 * @Best_case θ(1)
 * @Medium_case θ(1)
 * @Amortized_case θ(1)
 * @Worst_case θ(1)
 */
int Matrix::nrColumns() const {
    return this->columns;
}


/**
 * @brief returns the element from position i and j
 * @param i  index for line
 * @param j  index for column
 * @details this function returns the element in the matrix from position i and j.
 * It will throw and exception if the position in the matrix is not valid so when the indexes are out of range/bounds
 * @Time_complexity: best case - θ(1), worst case - O(n)
 */
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

/**
 * @brief the function modifies the element on the line_vec i and column_vec j
 * @params: i - index for row, j - index for column_vec, TElem e - the element to be modified
 * @detail
 * Time complexity: idk yet bro gotta think this one through
 */

//
//TElem Matrix::modify(int i, int j, TElem e) {
//    if (i < 0 || j < 0 || i > this->nrLines() || j > this->nrColumns()) {
//        throw std::out_of_range("Invalid Position for your element");
//    }
//
//    int start = this->columnPointers[j];
//    int end = this->columnPointers[j + 1];
//    TElem old = NULL_TELEM;
//
//    while(start < end) {
//        if(this->rowIndexes[start] == i) {
//            old = this->elements[start];
//            if(e != NULL_TELEM) {
//                this->elements[start] = e;
//            }
//            else {
//                this->deleteFromPosition(start, j);
//            }
//            return old;
//        }
//
//        if(this->rowIndexes[start] > i) {
//            old = this->elements[start];
//
//            this->addToPosition(start, i, j, e);
//
//            return old;
//        }
//
//        start++;
//    }
//
//    this->addToPosition(start, i, j, e);
//    return NULL_TELEM;
//
//}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i > this->nrLines() || j > this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }


    int start = this->columnPointers[j];
    int end = this->columnPointers[j + 1];
    TElem old = NULL_TELEM;

    for (int idx = start; idx < end; idx++) {
        if (this->rowIndexes[idx] == i) {
            old = this->elements[idx];
            if (e != NULL_TELEM) {
                this->elements[idx] = e;
            } else {
                this->deleteFromPosition(idx, j);
            }
            return old;
        }

        if (this->rowIndexes[idx] > i) {
            old = this->elements[idx];
            this->addToPosition(idx, i, j, e);
            return old;
        }
    }

    this->addToPosition(end, i, j, e);
    return NULL_TELEM;
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
    if (rowSize == rowCapacity)
        resizeRowIndexes(rowCapacity * 2);
    else if (rowSize <= rowCapacity / 4 && rowCapacity >= 10)
        resizeRowIndexes(rowCapacity / 2);
}

void Matrix::automaticElementsIndexes() {
    if (elementsSize == elementsCapacity)
        resizeElements(elementsCapacity * 2);
    if (elementsSize == elementsCapacity / 4 && elementsCapacity >= 10)
        resizeElements(this->elementsCapacity / 2);
}

Matrix::~Matrix() {
    delete[] this->elements;
    delete[] this->rowIndexes;
    delete[] this->columnPointers;
}

void Matrix::resize() {

    auto newRowIndexes = new TElem[2 * this->rowCapacity];
    auto new_elements = new TElem[2 * this->rowCapacity];

    for(int i = 0; i < this->rowSize; i++) {
        newRowIndexes[i] = this->rowIndexes[i];
        new_elements[i] = this->elements[i];
    }
    delete[] this->elements;
    delete[] this->rowIndexes;

    this->rowCapacity *= 2;
    this->elements = new_elements;
    this->rowIndexes = newRowIndexes;
}

void Matrix::addToPosition(int position, int i, int j, TElem e) {
    if(this->rowSize == this->rowCapacity)
        this->resize();
    this->rowSize++;

    for(int index = this->rowSize - 1; index > position; index--){
        this->rowIndexes[index] = this->rowIndexes[index - 1];
        this->elements[index] = this->elements[index-1];
    }

    for(int index = j + 1; index < this->columns + 1; index++)
        this->columnPointers[index]++;

    this->rowIndexes[position] = i;
    this->elements[position] = e;

}

void Matrix::deleteFromPosition(int position, int j) {
    for(int index = position; index < this->rowSize - 1; index++) {
        this->rowIndexes[index] = this->rowIndexes[index + 1];
        this->elements[index] = this->elements[index + 1];
    }
    this->rowSize--;

    for(int index = j + 1; index < this->columns + 1; index++) {
        this->columnPointers[index]--;
    }


}


