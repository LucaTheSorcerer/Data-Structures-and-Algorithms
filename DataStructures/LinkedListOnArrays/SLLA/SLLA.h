#pragma once

class SLLAIterator;
typedef int TComp;
#define NULL_TELEM (-11111);

struct SLLANode{
    TComp info;
    int next;
};

class SingleLinkedListOnArrays{
    friend class SLLAIterator;

private:
    SLLANode *array;
    int size;
    int capacity;
    int head;
    int firstEmpty;

public:
    SingleLinkedListOnArrays();

    ~SingleLinkedListOnArrays();

    void addToStart(TComp element);

    void addToPosition(int position, TComp elem);

    TComp removeFromStart();
    TComp removeElement(TComp element);
    TComp removeFromPosition(int position);

    [[nodiscard]] SLLAIterator getIterator() const;
};