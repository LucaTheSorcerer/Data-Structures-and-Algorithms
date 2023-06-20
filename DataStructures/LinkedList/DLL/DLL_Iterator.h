#pragma once
#include "DLL.h"

class DLLIterator{
    friend class DLL;

private:
    DLL dll;
    DLLNode *current;

    explicit DLLIterator(const DLL &d);

public:
    void first();

    void next();

    bool valid();

    TComp getCurrent();
};