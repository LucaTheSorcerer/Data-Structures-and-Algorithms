#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

#include <iostream>

using namespace std;


struct Node {
    int line{-1};
    int column{-1};
    TElem value{NULL_TELEM};
    int nextLine{-1};
    int nextColumn{-1};


    void print() const {
        cout << line << ' ' << column << ' ' << value << ' ' << nextLine << ' ' << nextColumn << endl;
    }
};

class Matrix {
private:
    int lines;
    int columns;
    int capacity;
    int size;
    Node *nodes;
    int head;
    int firstEmpty;

    void createHeaderNodes();

    // Returns the indexes of previous Nodes and current Node with (i, j)

public:
    //constructor
    Matrix(int nrLines, int nrCols);

    //returns the number of lines
    int nrLines() const;

    //returns the number of columns
    int nrColumns() const;

    //returns the element from line i and column j (indexing starts from 0)
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem element(int i, int j) const;

    //modifies the value from line i and column j
    //returns the previous value from the position
    //throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);


    void automaticResize();

    void resize(int newCapacity);

    void print() const;


    // destructor
    ~Matrix();

};
