#pragma once

#include <cstddef>
#include "DynamicArray.h"

class DynamicArray;

class DynamicArrayIterator{
    friend class DynamicArray;

private:
    size_t current;
    const DynamicArray &array;

    explicit DynamicArrayIterator(const DynamicArray &a);

public:
    ~DynamicArrayIterator() = default;

    TComp getCurrent();

    bool valid();

    void next();

    void first();
};