#pragma once
#include <cstddef>
#define NULL_TELEM (-111111)
typedef int TComp;

class DynamicArrayIterator;

class DynamicArray {
    ///Iterator
    friend class DynamicArrayIterator;

private:
    size_t size, capacity;
    TComp *array;

    ///Resize the array
    void resize(size_t newCapacity);
    void automaticResize();

public:
    ///Constructor
    DynamicArray();

    ///Get the size of the array
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;

    ///Get an element
    TComp getElementWithPosition(size_t position);
    TComp getElement(TComp element);

    ///Set the value of an element
    TComp setElement(size_t position, TComp newElement);

    ///Add an element to the array
    void addToPosition(size_t position, TComp element);
    void addToStart(TComp element);
    void addToEnd(TComp element);

    ///Remove an element from the array
    TComp removeElementPosition(size_t position);
    TComp removeElement(TComp element);
    TComp removeFromStart();
    TComp removeFromEnd();

    ///Get an iterator
    DynamicArrayIterator getIterator();

    ///Destructor
    ~DynamicArray();
};