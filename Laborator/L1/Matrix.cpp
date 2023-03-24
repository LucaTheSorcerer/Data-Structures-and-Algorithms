#include "Matrix.h"
#include <exception>
#include <stdexcept>

using namespace std;

/**
 * This is the class contractor
 * parameters: nrLines and nrCols are the number of lines, respectively the number of columns of the matrix
 */
Matrix::Matrix(int nrLines, int nrCols) {

    /**
     * We implement the constructor so that it can initialize the private members
     * values and rowIndexes arrays can be allocated with the initial capacity of
     * columns and the columnPointers can be initialized with the size of columns+1.
     * Also, the first element of columnPointers is set to 0 and the rest are set to size
     * We initialize three dynamic arrays that hold the elements, row indexes and column_vec pointers so we can represent
     * the ccs sparse matrix format
     */
     if(nrLines <= 0 || nrCols <= 0)
     {
         throw invalid_argument("The matrix cannot be null");
     }
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

/**
 * @brief return the number of rows in the matrix
 * params - nothing
 * Time complexity: θ(1)
 */
int Matrix::nrLines()  {
	//TODO - Implementation
	return this->rows;
}

/**
 * @brief return the number of columns in the matrix
 * parameters - nothing
 * Time complexity: θ(1)
 */
int Matrix::nrColumns()  {
    return this->columns;
}

/**
 * @brief returns the element from position i and j
 * parameters: i = line_vec, j = column_vec
 * @details this function returns the element in the matrix from position i and j.
 * It will throw and exception if the position in the matrix is not valid so when the indexes are out of range/bounds
 * Time complexity: best case - θ(1), worst case - O(n)
 */
TElem Matrix::element(int i, int j)  {
    if(i < 0 || j < 0 || i >= this->nrLines() || j >= this->nrColumns()) {
        throw std::out_of_range("Invalid Position for your element");
    }

    int start = columnPointers[j];
    int end = columnPointers[j + 1];

    //start = 1
    //end = 4 - 1 = 3

    for(int k = start; k < end; k++)
    {
        if(rowIndexes[k] == i)
            return elements[k];
    }
	return NULL_TELEM;
}

/**
 * @brief the function modifies the element on the line_vec i and column_vec j
 * parameters: i - index for row, j - index for column_vec, TElem e - the element to be modified
 * @detail
 * Time complexity: idk yet bro gotta think this one through
 */
//TElem Matrix::modify(int i, int j, TElem e) {
//	//TODO - Implementation
//
//    if(i < 0 || j < 0 || i >= rows || j >= columns)
//        throw std::out_of_range("Invalid position");
//
//    int start = columnPointers[j];
//    int end = columnPointers[j + 1];
//
//    int k, l;
//
//    for(k = start; k < end; k++)
//    {
//        if(rowIndexes[k] == i)
//        {
//            TElem old_value = elements[k];
//            elements[k] = e;
//            return old_value;
//        }
//
//        if(rowIndexes[k] > i)
//        {
//            if(e != NULL_TELEM) {
//                for(l = end; l > k; l--){
//                    elements[l] = elements[l-1];
//                    rowIndexes[l] = rowIndexes[l - 1];
//                }
//                elements[k] = e;
//                rowIndexes[k] = i;
//                columnPointers[j+1]++;
//                return NULL_TELEM;
//            }
//            for(l = k; l < end - 1; l++)
//            {
//                elements[l] = elements[l + 1];
//                rowIndexes[l] = rowIndexes[l + 1];
//            }
//            columnPointers[j + 1]--;
//            return NULL_TELEM;
//        }
//    }
//    if (e == NULL_TELEM) {
//        return NULL_TELEM;
//    }
//
//    elements[end] = e;
//    rowIndexes[end] = i;
//    columnPointers[j + 1]++;
//	return NULL_TELEM;
//}

//TElem Matrix::modify(int i, int j, TElem e) {
//
//    if(i < 0 || j < 0 || i >= rows || j >= columns)
//    throw std::out_of_range("Invalid position");
//    int start = columnPointers[j];
//    int end = columnPointers[j+1];
//    int k = start;
//
//    while(k < end && rowIndexes[k] < i) {
//        k++;
//    }
//
//    if(k < end && rowIndexes[k] == i) {
//        TElem old_value = elements[k];
//        elements[k] = e;
//        return old_value;
//    }
//
//    if(e != NULL_TELEM) {
//        if(size == end) {
//            int new_size = size * 2;
//            TElem* new_elements = new TElem[new_size];
//            int* new_rowIndexes = new int[new_size];
//
//            for(int l = 0; l < size; l++) {
//                new_elements[l] = elements[l];
//                new_rowIndexes[l] = rowIndexes[l];
//            }
//
//            delete[] elements;
//            delete[] rowIndexes;
//
//            elements = new_elements;
//            rowIndexes = new_rowIndexes;
//            size = new_size;
//        }
//
//        for(int l = end; l > k; l--) {
//            elements[l] = elements[l-1];
//            rowIndexes[l] = rowIndexes[l-1];
//        }
//
//        elements[k] = e;
//        rowIndexes[k] = i;
//        columnPointers[j+1]++;
//    }
//    else {
//        for(int l = k; l < end-1; l++) {
//            elements[l] = elements[l+1];
//            rowIndexes[l] = rowIndexes[l+1];
//        }
//        columnPointers[j+1]--;
//    }
//    return NULL_TELEM;
//
//}

TElem Matrix::modify(int i, int j, TElem e) {
    // Check if (i, j) is a valid position in the matrix
    if (i < 0 || i >= rows || j < 0 || j >= columns) {
        throw std::out_of_range("Invalid position!");
    }

    // Find the starting and ending positions of the column_vec j in the columnPointers array
    int start = columnPointers[j];
    int end = columnPointers[j+1];

    // Find the index of the row i in the rowIndexes array, if it exists
    int index = -1;
    for (int k = start; k < end; k++) {
        if (rowIndexes[k] == i) {
            index = k;
            break;
        }
    }

    // If the element (i, j) exists, update its value
    if (index != -1) {
        TElem old_value = elements[index];
        elements[index] = e;
        return old_value;
    }

    // If the element (i, j) does not exist, insert it
    int new_size = size + 1;
    TElem* new_elements = new TElem[new_size];
    int* new_rowIndexes = new int[new_size];
    for (int k = 0; k < start; k++) {
        new_elements[k] = elements[k];
        new_rowIndexes[k] = rowIndexes[k];
    }

    new_elements[start] = e;
    new_rowIndexes[start] = i;
    for (int k = end; k < new_size; k++) {
        new_elements[k] = elements[k-1];
        new_rowIndexes[k] = rowIndexes[k-1];
    }
    delete[] elements;
    delete[] rowIndexes;
    elements = new_elements;
    rowIndexes = new_rowIndexes;
    size = new_size;

    // Insert the new element
    //elements[start] = e;
    //rowIndexes[start] = i;

    // Update the columnPointers array to reflect the new element
    for (int k = j+1; k <= columns; k++) {
        columnPointers[k]++;
    }

    return NULL_TELEM;
}

//TElem Matrix::modify(int i, int j, TElem e) {
//    /*
//    ! se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
//
//    Cautam elementul e de pe linia i , coloana j in vectorii nostri daca exitsa
//    il modificam si ii returnam vechea valoare
//    Alftel
//    Adaugam cate un element nou la finalul fiecaruia dintre cei 3 vectori
//    apoi ii cautam pozitia corecta ,, mutam toate elementele la dreapta pentru a
//    ii face loc.
//
//    */
//    if (i < 0 || j < 0 || j >= this->nrColumns() || i >= this->nrLines())
//    {
//        throw exception();
//        return NULL_TELEM;
//    }
//
//    for (int k = 0; k < this->line_vec.getLen(); k++)
//        if (this->line_vec.vec[k] == i && this->column_vec.vec[k] == j)
//        {
//            TElem aux = this->elements_vec.vec[k];
//            this->elements_vec.vec[k] = e;
//            return aux;
//        }
//
//    /// adaugam la final
//    this->line_vec.Adauga(i);
//    this->column_vec.Adauga(j);
//    this->elements_vec.Adauga(e);
//
//    int k;
//    for (k = this->line_vec.getLen() - 1; k >= 0; k--)
//    {
//        if (this->line_vec.vec[k] < i)
//            break;
//        else if(this->line_vec.vec[k] == i && this->column_vec.vec[k] < i)
//            break;
//    }
//    k++;
//
//    /// facem loc
//    for (int c = this->line_vec.getLen() - 1; c > k; c--)
//    {
//        this->line_vec.vec[c] = this->line_vec.vec[c - 1];
//        this->column_vec.vec[c] = this->column_vec.vec[c - 1];
//        this->elements_vec.vec[c] = this->elements_vec.vec[c - 1];
//    }
//
//    /// mutam elementul
//    this->line_vec.vec[k] = i;
//    this->column_vec.vec[k] = j;
//    this->elements_vec.vec[k] = e;
//
//    return NULL_TELEM;
//}
//


/*
 * This is the class destructor
 * It frees app the dynamic allocated memory
 */
Matrix::~Matrix() {
    delete[] rowIndexes;
    delete[] columnPointers;
    delete[] elements;
}


