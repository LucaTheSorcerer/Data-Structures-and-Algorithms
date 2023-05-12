#include "Matrix.h"
#include <exception>

/**
 * @brief constructor for the Matrix class
 * @details: the constructor receives the number of lines and columns of the matrix as parameters and initializes
 * the matrix with the given dimensions.
 * @param nrLines number of lines of the matrix
 * @param nrCols number of columns of the matrix
 * @throws exception if the dimensions are invalid
 * @TimeComplexity-BestCase: θ(n + m)
 * @TimeComplexity-AverageCase: θ(n + m)
 * @TimeComplexity-WorstCase: θ(n + m)
 * @note n = nrLines, m = nrCols, the time complexity is dominated by the createHeaderNodes() function
 *
 */
Matrix::Matrix(int nrLines, int nrCols) {
    if (nrLines <= 0 || nrCols <= 0)
        throw std::out_of_range("Invalid dimensions");

    lines = nrLines;
    columns = nrCols;
    // 1 = head, nrLines+nrCols = head Nodes, 10 matrix elements
    capacity = 1 + nrLines + nrCols + 10;
    size = 0;
    head = 0; // Index of head node (-1, -1) in nodes array
    firstEmpty = -1;

    nodes = new Node[capacity];

    createHeaderNodes();

}

/**
 * @brief function that creates the necessary header nodes for a circular sparse matrix.
 * @details: the head is initialized with the index position (-1,-1). The head node is the top-left corner of the matrix
 * It does not store any element value but acts as a sentinel node to simplify the algorithms that manipulate the matrix
 * The initialization of the header node distinguishes is from the regular matrix columns and lines nodes
 * Then there are header nodes for lines created. The first loop iterates over the lines of the matrix and for each line
 * it creates a header node with the index arrIdx, which stores the line index, the index of the next line header and
 * the index of the first non-zero element of the line. The arrIdx is incremented after each iteration to keep track of
 * the next available index for a header node.
 * With the second for loop we iterate over the columns of the matrix. For each column, it creates a header node with
 * index arrIdx which stores the column index, the index of the next column header and the index of the first non-zero
 * element of the column. The arrIdx is incremented after each iteration to keep track of the next available index for
 * a header node.
 * @TimeComplexity-BestCase θ(n + m)
 * @TimeComplexity-AverageCase θ(n + m)
 * @TimeComplexity-WorstCase θ(n + m)
 * @note n = number of lines, m = number of columns
 */
void Matrix::createHeaderNodes() {
    nodes[head].line = -1;
    nodes[head].column = -1;
    nodes[head].nextLine = 1; // first line header (0, -1)
    nodes[head].nextColumn = 1 + lines; // first column header (-1, 0)

    // Create header nodes for lines
    int arrIdx = 1;
    for (int line = 0; line < lines; line++) {
        nodes[arrIdx].line = line;
        nodes[arrIdx].nextLine = arrIdx + 1;
        nodes[arrIdx].nextColumn = arrIdx;
        arrIdx++;
    }

    // Last row head points to head(-1,-1)
    nodes[arrIdx - 1].nextLine = head;

    // Create header nodes for columns
    for (int col = 0; col < columns; col++) {
        nodes[arrIdx].column = col;
        nodes[arrIdx].nextColumn = arrIdx + 1;
        nodes[arrIdx].nextLine = arrIdx;
        arrIdx++;
    }

    // Last column head points to head(-1,-1)
    nodes[arrIdx - 1].nextColumn = head;

    size = arrIdx;
}

/**
 * @brief function that returns the number of lines of the matrix
 * @return line - number of lines
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
int Matrix::nrLines() const {
    return lines;
}

/**
 * @brief function that returns the number of columns of the matrix
 * @return column - number of columns
 * @TimeComplexity-BestCase θ(1)
 * @TimeComplexity-AverageCase θ(1)
 * @TimeComplexity-WorstCase θ(1)
 */
int Matrix::nrColumns() const {
    return columns;
}


/**
 * @brief function that returns the element from the given position (i,j) of the matrix
 * @details the function first checks if the specified position is valid. If it is not, it throws an exception. This is
 * to ensure that the indices are valid and that the function does not try to access elements outside the matrix.
 * Next the function initializes a variable curr to the index of the first node in the matrix.
 * The first while loop iterates over the nodes until it find the node with line equal to 'i'.
 * The next while loop iterates over the nodes starting at the node with line equal to 'i' until it finds the node with
 * column equal to 'j'. If the node with column j is found, the function returns the value of the node, because it means
 * that the element (i,j) exists in the matrix. If the node with column j is not found, it means that the element (i,j)
 * does not exist in the matrix, so the function returns NULL_TELEM.
 * @param i - line index
 * @param j - column index
 * @return value of the element (i,j) if it exists in the matrix, NULL_TELEM otherwise
 * @throws exception if the indexes are invalid
 * @TimeComplexity-BestCase θ(1) - the element is the first element in the matrix
 * @TimeComplexity-AverageCase θ(n) - the element is in the middle of the matrix
 * @TimeComplexity-WorstCase θ(n) - the element is the last element in the matrix
 * @note n = number of elements in the matrix
 */

TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::invalid_argument("Invalid indexes!");

    int curr = nodes[head].nextLine;

    // curr = index of the first node in line i
    while (nodes[curr].line != i) {
        curr = nodes[curr].nextLine;
    }

    // curr = index of node(i, j) || head
    while (nodes[nodes[curr].nextColumn].column != -1) {
        if (nodes[curr].nextColumn >= capacity) {
            throw std::out_of_range("Index out of range");
        }
        curr = nodes[curr].nextColumn;
        if (nodes[curr].column == j)
            return nodes[curr].value;
    }

    return NULL_TELEM;
}



/**
 * @brief function that is used to modify the element at the given position (i,j) in the matrix and returns
 * the previous value from that.
 * @details the function first checks if the specified position is valid. If the indexes are out of bounds, the function
 * throws an exception. This is to ensure that the indices are valid and that the function does not try to access
 * elements outside the matrix. If the indexes are valid, the function proceeds to find the node in the sparse matrix
 * corresponding to the (i, j) position. Each node is stored in an array, which defined the slla idea, and each node
 * has three fields: the line index, the column index, and the value. The function starts by finding the line and column
 * header nodes. Next, the function searched for the node with (i,j) in the matrix, by iterating through the linked list
 * starting from the node next to the line header for the i-th row. If the node is found, its value is updated to the
 * new value e. If e is NULL_TELEM, meaning that node is being deleted from the matrix. To delete the node, the function
 * sets the nextColumn field of the previous node to point to the next next, and update nextColumn pointer of the node
 * to be deleted to point to the first empty slot. Then firstEmpty is updated to point to the deleted node, so that it
 * can be used for future insertions. If the new value e is not a null element, we simply update the value of the
 * existing node with the new value e, as a non null element is either modified to another non null element, or a null
 * element is being changed to a non null element. If the node does not exist in the matrix and the new value e is not
 * a null element, the function creates a new nodes with (i,j) and the new value is inserted into the matrix in the
 * correct position based on the line and column indexes.
 * @param i - line index
 * @param j - column index
 * @param e - new value of the element (i,j) in the matrix
 * @return the previous value of the element (i,j) in the matrix
 * @throws invalid_argument if the indexes are invalid
 * @TimeComplexity-BestCase θ(1) - the element is the first element in the matrix || the e = NULL_TELEM and the node
 * does not exist in the matrix, then the function does not have to perform any actions.
 * @TimeComplexity-AverageCase θ(n) - the element is in the middle of the matrix and  e != NULL_TELEM. It depends on the
 * position of the node in the matrix to be modified, so we can say that it is based on the average of non zero elements
 * @TimeComplexity-WorstCase θ(n) - the element or the node is located near the end of a row or a column, the algorithm
 * has to iterate through the entire row or column to find the node to be modified.
 * @note n = number of elements in the matrix
 *
 */

// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::invalid_argument("Invalid indexes!");

    // Find the line and column header nodes
    int lineHead = head;
    while (nodes[lineHead].line < i)
        lineHead = nodes[lineHead].nextLine;

    int columnHead = head;
    while (nodes[columnHead].column < j)
        columnHead = nodes[columnHead].nextColumn;

    // Find the node with (i, j)
    int nodePrev = lineHead;
    int nodeCurr = nodes[lineHead].nextColumn;

    while (nodeCurr != lineHead && nodes[nodeCurr].column < j) {
        nodePrev = nodeCurr;
        nodeCurr = nodes[nodeCurr].nextColumn;
    }

    if (nodeCurr != lineHead && nodes[nodeCurr].column == j) { // node with (i,j) already exists
        TElem oldValue = nodes[nodeCurr].value;
        if (e == NULL_TELEM) { // Case when a non-null element is modified to a null element
            cout << "non null to null when node exists" << endl;
            // Delete the node with (i,j)
            nodes[nodePrev].nextColumn = nodes[nodeCurr].nextColumn;
            nodes[nodeCurr].nextColumn = firstEmpty;
//            nodes[nodeCurr].line = -1;
//            nodes[nodeCurr].column = -1;
            nodes[nodeCurr].value = NULL_TELEM;
            firstEmpty = nodeCurr;
            size--;
            automaticResize();
        }
        else { // Case when a non-null element is modified to another non-null element or a null element is modified to a non-null element
            cout << "non null to non null when node exists" << endl;
            nodes[nodeCurr].value = e;
        }
        return oldValue;
    }
    else { // node with (i,j) doesn't exist
        if (e == NULL_TELEM) { // Case when a null element is turned to a non-null element
            cout << "null to non null when node does not exist" << endl;
            // Do nothing, return NULL_TELEM
            return NULL_TELEM;
        }
        else { // Case when a non-null element is inserted
            // Create a new node with (i,j)
            cout << "non null inserted when node does not exist" << endl;
//            if (firstEmpty == -1 &&)// No more empty slots in the array, resize the array
            automaticResize();
            int newNode = firstEmpty;
            firstEmpty = nodes[firstEmpty].nextColumn;
            nodes[newNode].line = i;
            nodes[newNode].column = j;
            nodes[newNode].value = e;
            nodes[newNode].nextColumn = nodeCurr;//updates the nextColumn pointer of the new node to point to the next node.
            nodes[nodePrev].nextColumn = newNode;//updates the nextColumn pointer of the previous node to point to the new node
            size++;
            return NULL_TELEM;
        }
    }
}

// 1 2 3
// 4 0 6
// 7 8 9



/**
 * @brief The destructor function for the Matrix class
 * @details it frees the memory allocated for the nodes array
 * @Best_case  θ(1)
 * @Medium_case  θ(1)
 * @Worst_case θ(1)
 */
Matrix::~Matrix() {
    delete[] nodes;
}



/**
 * @brief function used to automatically resize the nodes array
 * @details the function calls the function resize with a new capacity determined by the fullness of the array.
 * takes the time complexity of the resizeRowIndexes function
 * @Best_case - θ(1)
 * @Average_case - θ(1)
 * @Worst_case - θ(n)
 */
void Matrix::automaticResize() {
    if (firstEmpty == -1 && size != capacity) {
        cout << "resize up" << endl;
        resize(capacity * 2);
    }
    else if (size <= capacity / 4 && capacity >= 10) {
        resize(capacity / 2);
    }
}

/**
 * @brief function used to resize the nodes array
 * @details the function resizes the capacity of the nodes array when needed with a newCapacity that is given by the
 * function automaticElementsIndexes. It check whether the new capacity is smaller than the current one and if it is
 * it throws an exception. A new nodes array is created with the new capacity. A for loop is used to copy the elements
 * from the old array to the new one then the old array gets deleted. The pointer to the old array is set
 * to the new nodes array. The capacity of the nodes array is modified to the new capacity
 * @param newCapacity: represents the new capacity of the nodes array
 * @Best_case - θ(n)
 * @Average_case - θ(n)
 * @Worst_case - θ(n)
 */

// 1 -> 2 3 4 5 6 7 8 9 -> 0 -> 0 -> 0 0 0 0 0

void Matrix::resize(int newCapacity) {
    if (newCapacity < size)
        throw std::invalid_argument("New capacity cannot be smaller than the actual size");

    Node *newNodes = new Node[newCapacity];

    for (int i = 0; i < std::min(capacity,newCapacity); ++i) {
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

/**
 * @brief function used to print the matrix
 * @details the function prints the matrix by using a for loop to iterate through the lines and columns of the matrix
 * and calls the function element to print the element at the current position. Only used for debugging and testing
 * purposes
 */
void Matrix::print() const {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << this->element(i, j) << " ";
        }
        std::cout << std::endl;
    }
}


