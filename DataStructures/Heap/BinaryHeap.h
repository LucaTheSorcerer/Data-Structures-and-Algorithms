#pragma once

#include <iostream>

typedef int TElem;
typedef TElem TComp;

typedef bool(*Relation)(TComp, TComp);

using std::cout;

class BinaryHeap {
private:
    int size;
    int capacity;
    TComp *array;
    Relation relation;

    void resize(int newCapacity);

    void autoResize();

    void bubbleUp();

    void bubbleDown();

public:
    static inline bool relationLowerEqual(TComp e1, TElem e2) {
        return e1 <= e2;
    }

    static inline bool relationGreaterEqual(TComp e1, TComp e2) {
        return e1 >= e2;
    }

    explicit BinaryHeap(Relation r);

    ~BinaryHeap();

    void add(TComp element);

    TComp remove();

    void print();
};