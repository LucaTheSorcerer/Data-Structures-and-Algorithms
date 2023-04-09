#include "Matrix.h"
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;


/**
 * @brief This is the class contractor
 * @param nrLines - the number of lines
 * @param nrCols - the number of columns of the matrix
 * @Best_case  θ(1)
 * @Medium_case  θ(1)
 * @Worst_case θ(1)
 */
Matrix::Matrix(int nrLines, int nrCols) {

    /**
 * @details We implement the constructor so that it can initialize the private members
 * values and rowIndexes arrays can be allocated with the initial capacity of
 * columns and the columnPointers can be initialized with the size of columns+1.
 * Also, the first element of columnPointers is set to 0 and the rest are set to size
 * We initialize three dynamic arrays that hold the elements, row indexes and column_vec pointers so we can represent
 * the ccs sparse matrix format. it initializes the matrix with empty elements and column pointers
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
 * @brief returns the number of rows in the matrix
 * @params  -
 * @Best_case  θ(1)
 * @Medium_case  θ(1)
 * @Worst_case θ(1)
 */
int Matrix::nrLines() const {
    return this->rows;
}

/**
 * @brief returns the number of columns in the matrix
 * @params -
 * @Best_case θ(1)
 * @Medium_case θ(1)
 * @Worst_case θ(1)
 */
int Matrix::nrColumns() const {
    return this->columns;
}


/**
 * @brief returns the element from position i and j
 * @param i  index for line
 * @param j  index for column
 * @details this function returns the element in the matrix from position i and j. If the element does not exist in the
 * matrix it will return NULL_TELEM
 * @throws out_of_range - It will throw and exception if the position in the matrix is not valid so when the indexes are out of range/bounds
 * @Best_case - θ(1)
 * @Average_case - θ(n) where n is the number of elements on the column j
 * @Worst_case - θ(n)
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
 * @brief the function modifies the element on the line i and column j.
 * This function modifies the element at position (i,j) in the matrix.
 * If the element exists, it replaces the element with a new value e. If e is NULL_TELEM it deletes the existing element.
 * @param: i - index for row
 * @param: j - index for column
 * @param: TElem e - the element to be modified
 * @details: First check if the indices are valid. We iterate through the range of rows that have non-zero elements
 * and check if it is the row 'i' that we want to modify. If it is and the element is not NULL_TELEM, then we replace the element
 * otherwise, we delete the element and return the old value
 * If it is not the row 'i' the row that we want to modify, we check if there is a row that comes after 'i'
 * If it is then we insert the new element at position 'i' and return the old value
 * If none of the rows in the column have an index equal or greater than 'i' then we have to add the new element at the end
 * of the columns, so we add it with the function addToPosition

 * @throws out_of_range if the indices (i,j) are out of range
 * @Best_case - θ(1)
 * @Average_case - θ(n) where n is the number lines
 * @Worst_case - θ(n)
 */
//TElem Matrix::modify(int i, int j, TElem e) {
//    if (i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns()) {
//        throw std::out_of_range("Invalid Position for your element");
//    }
//
//    int start = columnPointers[j];
//    int end = columnPointers[j + 1];
//
//    for (int k = start; k < end; k++) {
//        if (rowIndexes[k] == i) {
//            if (e != NULL_TELEM) {
//                elements[k] = e;
//            } else {
//                deleteFromPosition(k, j);
//            }
//            return elements[k];
//        }
//        if (rowIndexes[k] > i) {
//            addToPosition(k, i, j, e);
//            return e;
//        }
//    }
//    addToPosition(end, i, j, e);
//    return e;
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

        // if it is not the row i that we are looking for, we check if there is next row and if it is
        // we add the desired element to the position idx
        if (this->rowIndexes[idx] > i) {
            old = this->elements[idx];
            this->addToPosition(idx, i, j, e);
            return old;
        }
    }

    //if none of the rows have an index equal or greater to i, we add the element to the end of the column
    this->addToPosition(end, i, j, e);
    return NULL_TELEM;
}


/**
 * @brief function used to resize the row array indexes
 * @details the function resizes the indexes of the elements array when needed with a newCapacity that is given by the
 * function automaticResizeRowIndexes. First the function check whether the new capacity is smaller than the current one
 * and if it is it throws an exception. Otherwise it creates a new integer array with the new size
 * then the function loops over each element of rowIndexes starting from 0 and ending at rowSize-1 and then it copies the
 * elements from the old array to the new one. Then it deletes the old array and sets the pointer to the new one
 * Then the capacity is updated to the new capacity
 * @param newCapacity: the new capacity of the rowIndexes array
 * @Best_case - θ(n)
 * @Average_case - θ(n)
 * @Worst_case - θ(n)
 */

void Matrix::resizeRowIndexes(int newCapacity) {
    if (newCapacity < rowSize)
        throw std::out_of_range("Index out of range");

    int *newArray = new int[newCapacity];
    for (int i = 0; i < rowSize; i++)
        newArray[i] = this->rowIndexes[i];

    delete[] this->rowIndexes;
    this->rowIndexes = newArray;
    this->rowCapacity = newCapacity;
}

/**
 * @brief function used to resize the elements array
 * @details the function resizes the capacity of the elements array when needed with a newCapacity that is given by the
 * function automaticElementsIndexes. It check whether the new capacity is smaller than the current one and if it is
 * it throws an exception
 * a new dynamic array is created of type Telem with the new capacity
 * a for loop is used to copy the elements from the old array to the new one
 * then the old array gets deleted
 * the pointer to the old array is set to the new array
 * the capacity of the elements is modified to the new capacity
 * @param newCapacity: represents the new capacity of the elements dynamic array
 * @Best_case - θ(n)
 * @Average_case - θ(n)
 * @Worst_case - θ(n)
 */

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


/**
 * @brief function used to automatically resize the row array indexes
 * @details the function calls the function resizeRowIndexes with a new capacity determined by the fullness of the array.
 * takes the time complexity of the resizeRowIndexes function
 * @Best_case - θ(1)
 * @Average_case - θ(1)
 * @Worst_case - θ(n)
 */
void Matrix::automaticResizeRowIndexes() {
    if (rowSize == rowCapacity)
        resizeRowIndexes(rowCapacity * 2);
    else if (rowSize <= rowCapacity / 4 && rowCapacity >= 10)
        resizeRowIndexes(rowCapacity / 2);
}
/**
 * @brief function used to automatically resize the elements array
 * @details the function calls the function resizeElements with a new capacity determined by the fullness of the array.
 * takes the time complexity of the resizeElements function
 * @Best_case - θ(1)
 * @Average_case - θ(1)
 * @Worst_case - θ(n)
 */
void Matrix::automaticElementsIndexes() {
    if (elementsSize == elementsCapacity)
        resizeElements(elementsCapacity * 2);
    if (elementsSize == elementsCapacity / 4 && elementsCapacity >= 10)
        resizeElements(this->elementsCapacity / 2);
}

/**
 * @brief The destructor function for the Matrix class
 * @details it frees the memory allocated for the arrays elements, rowIndex and columnPointers
 * @Best_case  θ(1)
 * @Medium_case  θ(1)
 * @Worst_case θ(1)
 */
Matrix::~Matrix() {
    delete[] this->elements;
    delete[] this->rowIndexes;
    delete[] this->columnPointers;
}




/**
 * @brief function to adds an element to a certain position, used for the modify function
 * @details if the number of rows is equal to the capacity, it calls the resize function to increase
 * the capacity of the matrix. It then shifts the elements to the right of position 'position' by one index
 * and increments their column pointer values by one.
 * It then updates the rowIndexes and elements arrays at the specified new position
 * @param position - the position where the element e should be added
 * @param i - index for row i
 * @param j - index for column j
 * @param e - element to be added to the array
 * @Best_case - θ(1)
 * @Average_case - θ(n) where n is the number lines
 * @Worst_case - θ(n)
 */
void Matrix::addToPosition(int position, int i, int j, TElem e) {
    //if row indexes array reached max capacity, resize it
    if (this->rowSize == this->rowCapacity) {
        this->automaticResizeRowIndexes();
        this->automaticElementsIndexes();

    }

    //we increment the number of rows by one because we are adding a new elem
    this->rowSize++;

    //we initiate a loop that starts from the end of the array and goes at the desired position
    for(int index = this->rowSize - 1; index > position; index--){
        //we shift the elements to the right by one index
        this->rowIndexes[index] = this->rowIndexes[index - 1];
        //we shift the elements to the right by one index
        this->elements[index] = this->elements[index-1];
    }

    //the column pointers array will be incremented by one for all the elements
    //that are from j+1 to columns+1 because a new element has been added
    for(int index = j + 1; index < this->columns + 1; index++)
        this->columnPointers[index]++;

    //we update the row indexes array and the element array at the specified position
    this->rowIndexes[position] = i;
    this->elements[position] = e;

}

/**
 * @brief function to delete an element at a certain position, used for the modify function
 * @details The function begins by iterating over the elements that come after the element that we want to remove
 * using a for loop that begins from position and ends at rowSize - 1.
 * In the for loop, the function replaces each element at index 'index' with the element at 'index + 1'
 * This way it shifts all element after the desired element one position to the left
 * After the loop ends, the function decrements the rowSize by one because one element has been removed
 * Then it calls the automaticResizeRowIndexes and automaticElementsIndexes functions to resize the arrays
 * so that no extra space is being used.
 * At the end, the function updates the columnPointer array for columns that come after the column 'j'.
 * This step is done using another for loop that starts from j + 1 and ends at columns + 1.
 * The column pointers are decremented by 1 for every column, because one element has been removed.
 * @param position - basically the index of the element to be removed
 * @param j - index for column j where the element in located
 * @Best_case - θ(1)
 * @Medium_case - θ(n) where n is the number lines
 * @Worst_case - θ(n)
 */
void Matrix::deleteFromPosition(int position, int j) {
    for(int index = position; index < this->rowSize - 1; index++) {
        this->rowIndexes[index] = this->rowIndexes[index + 1];
        this->elements[index] = this->elements[index + 1];
    }
    this->rowSize--;
    automaticResizeRowIndexes();
    automaticElementsIndexes();

    for(int index = j + 1; index < this->columns + 1; index++) {
        this->columnPointers[index]--;
    }
}

/**
 * @brief function used to print the matrix, purely used for debugging and testing purposes
 */
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




/**
 *
 * @param nrLines new number of lines from the new matrix that we are giving as parameter
 * @param nrCols  new number of columns from the new matrix that we aregiving as a parameter
 * @pre: the nr of lines and nr of columns have to be initialized correctly, the matrix has to be a valid one
 * @post: it should return the resized matrix with the new resize, where the capacity is based on the resized one
 * best_case theta(n)
 * medium_case theta(n)
 * worst_case theta(n)
 */

//pseudocode
/**
 * if (dimensions bigger)
 *      simply resize
 *      rows = nrLines
 *      cols = nrCols
 * else
 *     new capacity = rowCapacity
 *     new rowIndex = 0
 *     newElementIndex = 0
 *     newColumnPointers = new int[nrCols + 1]{0};
 *       newRowIndexes = new int[newCapacity]{0};
 *      newElements = new TElem[newCapacity]{0};
 *
 *      for(index in current column)
 *          start = columnPointer[j]
 *          end = columnPointer[j+1]
 *
 *      for(from start to  < end)
 *          if(index i <NrLines && index j < NrColumns)
 *              newRowIndex[newElementIndex] = i --> keep the element
 *              newElement[newElementsIndex] = elements[k]
 *              newElementsIndex++;
 */
/**
 *
 * elements = new elements of size newline * new columns
 * if the new dimensions are smaller than the function has to eliminate the other elements
 * the function then creates new arrays for column pointer, row indexes, new elements
 * new cap = new cap
 * it iterates through the current column of the matrix and for each column the function finds the start and end index
 * of the non-zero elements in that column using the columnPointers array
 * then it loops over the non zero elements in the column using the rowIndexes array and for each element it
 * then checks if the row indices and column indices are withing the new given dimension
 * If it is withing the range, then the element is added to the new arrays, if not then the element is basically skipped
 * because it won't fit in the new array
 * After the column piinters are updated to the new numbe rof elements in the newElements array
 * This represents the fact that the index in at the end
 * Then the funciton deletes the old arrays and the rows and columns are set to the new dimensions
 *
 */


void Matrix::resize(int nrLines, int nrCols) {
    if (nrLines > this->rows || nrCols > this->columns) {
        // if the new dimensions are larger, simply resize the matrix
        this->rows = nrLines;
        this->columns = nrCols;
    } else {
        // if the new dimensions are smaller, eliminate elements outside the new dimensions
        int newCapacity = this->rowCapacity;
        int newRowIndex = 0;
        int newElementIndex = 0;
        int* newColumnPointers = new int[nrCols + 1]{0};
        int* newRowIndexes = new int[newCapacity]{0};
        TElem* newElements = new TElem[newCapacity]{0};

        for (int j = 0; j < this->columns; j++) {
            int start = this->columnPointers[j];
            int end = this->columnPointers[j + 1];
            for (int k = start; k < end; k++) {
                int i = this->rowIndexes[k];
                if (i < nrLines && j < nrCols) {
                    // the element is within the new dimensions, keep it
                    newRowIndexes[newElementIndex] = i;
                    newElements[newElementIndex] = this->elements[k];
                    newElementIndex++;
                }
            }
            // update the column pointer to the new number of elements
            newColumnPointers[j + 1] = newElementIndex;
        }
        // update the private members of the matrix
        delete[] this->columnPointers;
        delete[] this->rowIndexes;
        delete[] this->elements;
        this->columnPointers = newColumnPointers;
        this->rowIndexes = newRowIndexes;
        this->elements = newElements;
        this->rowCapacity = newCapacity;
        this->rowSize = newRowIndex;
        this->rows = nrLines;
        this->columns = nrCols;
    }
}

