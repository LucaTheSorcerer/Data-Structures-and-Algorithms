#include "Matrix.h"
#include <exception>

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

    for (int i = 0; i < size; i++) {
//        cout << '[' << i << "]. ";
//        nodes[i].print();
    }
}

void Matrix::createHeaderNodes() {
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


int Matrix::nrLines() const {
    return lines;
}

int Matrix::nrColumns() const {
    return columns;
}

TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();

    Node *curr = &nodes[head];

    // curr = header node for line i
    while (curr->line != i) {
        curr = &nodes[curr->nextLine];
//        cout << "curr.line = " << curr->line << endl;
    }

    // curr = node(i, j) || head
    while (nodes[curr->nextColumn].column != -1) {
        curr = &nodes[curr->nextColumn];
//        cout << "curr.column = " << curr->column << endl;
        if (curr->column == j)
            return curr->value;
    }

    return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= lines || j < 0 || j >= columns)
        throw std::exception();

    Node *curr = &nodes[head];

    // Find the header node for line i
    while (curr->line != i) {
        curr = &nodes[curr->nextLine];
    }

    Node *prev = curr;

    // Find the node with column j in line i, or the node before where it should be
    while (nodes[curr->nextColumn].column != -1 && nodes[curr->nextColumn].column <= j) {
        prev = curr;
        curr = &nodes[curr->nextColumn];
        if (curr->column == j) {
            TElem oldValue = curr->value;
            if (e == NULL_TELEM) {
                // Delete the node
                prev->nextColumn = curr->nextColumn;
                curr->nextColumn = firstEmpty;
                firstEmpty = int(curr - nodes)/sizeof(Node);
                curr->line = -1;
                curr->column = -1;
                curr->value = NULL_TELEM;
                size--;
            } else {
                // Update the value of the existing node
                curr->value = e;
            }
            automaticResize();
            return oldValue;
        }
    }

    // Node with column j not found, so insert a new node
    if (e != NULL_TELEM) {
        int newNodeIdx;
        if (firstEmpty != -1) {
            newNodeIdx = firstEmpty;
            firstEmpty = nodes[firstEmpty].nextColumn;
        } else {
            newNodeIdx = size;
            size++;
            if (size >= capacity) {
                resize(capacity * 2);
            }
        }
        Node *newNode = &nodes[newNodeIdx];
        newNode->line = i;
        newNode->column = j;
        newNode->value = e;
        newNode->nextColumn = curr->nextColumn;
        curr->nextColumn = newNodeIdx;
        automaticResize();
        return NULL_TELEM;
    }

    return NULL_TELEM;
}



/**
 * @brief Search Node with indexes i and j
 * @returns SearchResult(prevLine, prevCol, idx) \n
 * idx = the index of the element with index (i, j)               || -1 \n
 * prevLine = the index of element with index (i-z, j) , z ∈ N    || -1 \n
 * prevCol = the index of element with index (i, j-z)  , z ∈ N    || -1
 * @param i
 * @param j
 */
SearchResult Matrix::searchIndex(int i, int j) const {
    Node *curr = &nodes[head];
    int prevLineIdx = head;
    int prevColIdx = head;
    int currIdx = head;

    while (curr->line != i)
        curr = &nodes[curr->nextLine];

    // find prevColIdx and currIdx
    while (nodes[curr->nextColumn].column != -1 && nodes[curr->nextColumn].column < j) {
        if (nodes[curr->nextColumn].column == j) {
            prevColIdx = (curr - nodes) / sizeof(Node);
            currIdx = curr->nextColumn;
            break;
        }
        curr = &nodes[curr->nextColumn];
    }

    curr = &nodes[head];

    while (curr->column != j)
        curr = &nodes[curr->nextColumn];

    while (nodes[curr->nextLine].line != -1 && nodes[curr->nextLine].line < i) {
        if (nodes[curr->nextLine].line == i) {
            prevLineIdx = (curr - nodes) / sizeof(Node);
            break;
        }
        curr = &nodes[curr->nextLine];
    }

    return {prevLineIdx, prevColIdx, currIdx};
}

//SearchResult Matrix::searchIndex(int i, int j) const {
//    Node *curr = &nodes[head];
//    int prevLineIdx = -1;
//    int prevColIdx = -1;
//    int currIdx = -1;
//
//    // find prevLineIdx and currIdx
//    while (curr->line != i && nodes[curr->nextLine].line != -1 && nodes[curr->nextLine].line < i) {
//        curr = &nodes[curr->nextLine];
//    }
//
//    if (curr->line == i) {
//        prevLineIdx = (curr - nodes)/sizeof(Node);
//        currIdx = curr->nextColumn;
//    }
//
//    // find prevColIdx
//    curr = &nodes[head];
//    while (curr->column != j && nodes[curr->nextColumn].column != -1 && nodes[curr->nextColumn].column < j) {
//        curr = &nodes[curr->nextColumn];
//    }
//
//    if (curr->column == j) {
//        prevColIdx = (curr - nodes)/sizeof(Node);
//    }
//
//    return {prevLineIdx, prevColIdx, currIdx};
//}


Matrix::~Matrix() {
    delete[] nodes;
}

void Matrix::automaticResize() {
    if (firstEmpty == -1)
        resize(capacity * 2);
    else if (size <= capacity / 4 && capacity >= 10)
        resize(capacity / 2);
}

void Matrix::resize(int newCapacity) {
    if (newCapacity < size)
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

void Matrix::print() const {
    for (int i = 0; i < lines; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << this->element(i, j) << " ";
        }
        std::cout << std::endl;
    }
}
