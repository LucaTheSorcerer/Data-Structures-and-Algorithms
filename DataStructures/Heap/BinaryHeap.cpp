#include "BinaryHeap.h"
#include <stdexcept>
#include <cmath>

BinaryHeap::BinaryHeap(Relation r) {
    size = 0;
    capacity = 10;
    array = new TComp[capacity];
    relation = r;
}

BinaryHeap::~BinaryHeap() {
    delete[] array;
}

void BinaryHeap::resize(int newCapacity) {
    if (newCapacity < size)
        throw std::invalid_argument("New size is smaller than the actual size");

    auto *newArray = new TComp[newCapacity];
    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

void BinaryHeap::autoResize() {
    if (this->size >= this->capacity)
        resize(this->capacity * 2);
    if (this->size <= this->capacity / 4 && this->capacity > 10)
        resize(this->capacity / 2);
}

void BinaryHeap::add(TComp element) {
    array[size] = element;
    size++;
    bubbleUp();
    autoResize();
}

TComp BinaryHeap::remove() {
    TComp oldValue = array[0];
    array[0] = array[size - 1];
    size--;
    bubbleDown();
    autoResize();
    return oldValue;
}

/// children of i - (i  * 2 ) + 1, ( i * 2 ) + 2
/// parent of i - ( i - 1 ) / 2
void BinaryHeap::bubbleUp() {
    int currIdx = size - 1;
    int parentIdx = (currIdx - 1) / 2;

    cout << array[currIdx] << ' ';
    cout << array[parentIdx] << '\n';
    while (!relation(array[parentIdx], array[currIdx])) {
        TComp temp = array[parentIdx];
        array[parentIdx] = array[currIdx];
        array[currIdx] = temp;

        currIdx = parentIdx;
        parentIdx = (currIdx - 1) / 2;
    }
}

/// children of i - (i  * 2 ) + 1, ( i * 2 ) + 2
/// parent of i - ( i - 1 ) / 2
void BinaryHeap::bubbleDown() {
    int currentIndex = 0;
    int leftChildIndex = 2 * currentIndex + 1;
    int rightChildIndex = 2 * currentIndex + 2;
    int childIndex;

    while (leftChildIndex < size) {
        if (rightChildIndex < size && relation(array[rightChildIndex], array[leftChildIndex]))
            childIndex = rightChildIndex;
        else
            childIndex = leftChildIndex;

        if (relation(array[childIndex], array[currentIndex])) {
            std::swap(array[currentIndex], array[childIndex]);
            currentIndex = childIndex;
            leftChildIndex = 2 * currentIndex + 1;
            rightChildIndex = 2 * currentIndex + 2;
        } else {
            break;
        }
    }
}

void BinaryHeap::print() {
    cout << "Height: " << int(log2(size)) << '\n';
    for (int i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << std::endl;
}