#pragma once


typedef int TComp;
#define NULL_TELEM (-11111);

class SLLIterator;

struct SLLNode {
    TComp info;
    SLLNode *next;
};

class SLL {
    friend class SLLIterator;

private:
    SLLNode *head;
    int size;

public:
    SLL();

    void addFirst(TComp element);

    void AddBeforeNode(SLLNode *currentNode, TComp element);

    void addAfterNode(SLLNode *currentNode, TComp element);

    void insertPosition(int position, TComp element);

    TComp deleteFirst();

    TComp deleteElement(TComp element);

    [[nodiscard]] int getSize() const;

    [[nodiscard]] bool isEmpty() const;

    SLLIterator getIterator();

    ~SLL();
};