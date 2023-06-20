#pragma once

typedef int TComp;

#define NULL_TELEM (-11111);

class DLLAIterator;

struct DLLANode {
    TComp info;
    int next;
    int previous;
};

class DLLA {
    friend class DLLAIterator;

private:
    int capacity, head, tail, firstEmpty, size;
    DLLANode *array;

public:
    DLLA();

    ~DLLA();

    void addToStart(TComp elem);

    TComp removeFromStart();

    DLLAIterator getIterator();
};