#pragma once

typedef int TComp;
#define NULL_TELEM (-11111)
class DLLIterator;

struct DLLNode{
    TComp info;
    DLLNode *next;
    DLLNode *previous;
};

class DLL{
    friend class DLLIterator;
private:
    DLLNode *head;
    DLLNode *tail;
    int size;

public:
    DLL();

    ~DLL();

    void addToPosition(int position, TComp elem);

    void addToStart(TComp elem);
    void addToEnd(TComp element);

    TComp removeStart();

    TComp removeElement(TComp element);

    [[nodiscard]] bool isEmpty() const;

    int getSize() const;

    DLLIterator getIterator();
};