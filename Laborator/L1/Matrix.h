#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	//TODO - Representation
    /*
     * rows = number of rows, columns = number of columns, size = size of values
     *
     */
    int rows, columns, size;
    TElem* elements;
    int* rowIndexes;
    int* columnPointers;
//    Array line_vec, column_vec;
//    Arraytelem elements_vec;

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	[[nodiscard]] int nrLines();

	//returns the number of columns
	[[nodiscard]] int nrColumns();

	//returns the element from line_vec i and column_vec j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	[[nodiscard]] TElem element(int i, int j);

	//modifies the value from line_vec i and column_vec j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);
	
	// destructor
	~Matrix();

};
