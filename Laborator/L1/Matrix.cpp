#include "Matrix.h"
#include <exception>
#include <stdexcept>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {

    /*
     * We implement the constructor so that it can initialize the private members
     * values and rowIndexes arrays can be allocated with the initial capacity of
     * columns and the columnPointers can be initialized with the size of columns+1.
     * Also, the first element of columnPointers is set to 0 and the rest are set to size
     */
	//TODO - Implementation
    rows = nrLines;
    columns = nrCols;
    size = columns;
    elements = new TElem[size];
    rowIndexes = new int[size];
    columnPointers = new int[columns+1];

    columnPointers[0] = 0;
    int i;
    for(i = 1; i <= columns; i++)
        columnPointers[i] = size;
}


int Matrix::nrLines() const {
	//TODO - Implementation
	return rows;
}


int Matrix::nrColumns() const {
	//TODO - Implementation
    return columns;
}


TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
    if(i >= rows || j >= columns)
        throw std::out_of_range("Invalid Position");

    int start = columnPointers[j];
    int end = columnPointers[j + 1];

    int k;
    for(k = start; k < end; k++)
    {
        if(rowIndexes[k] == i)
            return elements[k];
        if(rowIndexes[k] > i)
            break;
    }
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation

    if(i >= rows || j >= columns)
        throw std::out_of_range("Invalid position");

    int start = columnPointers[j];
    int end = columnPointers[j + 1];

    int k, l;

    for(k = start; k < end; k++)
    {
        if(rowIndexes[k] == i)
        {
            TElem old_value = elements[k];
            elements[k] = e;
            return old_value;
        }

        if(rowIndexes[k] > i)
        {
            if(e != NULL_TELEM) {
                for(l = end; l > k; l--){
                    elements[l] = elements[l-1];
                    rowIndexes[l] = rowIndexes[l - 1];
                }
                elements[k] = e;
                rowIndexes[k] = i;
                columnPointers[j+1]++;
                return NULL_TELEM;
            }
            for(l = k; l < end - 1; l++)
            {
                elements[l] = elements[l + 1];
                rowIndexes[l] = rowIndexes[l + 1];
            }
            columnPointers[j + 1]--;
            return NULL_TELEM;
        }
    }
    if (e == NULL_TELEM) {
        return NULL_TELEM;
    }

    elements[end] = e;
    rowIndexes[end] = i;
    columnPointers[j + 1]++;
	return NULL_TELEM;
}

Matrix::~Matrix() {
	//TODO - Implementation
    delete[] rowIndexes;
    delete[] columnPointers;
    delete[] elements;
}


