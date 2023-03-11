//
// Created by Luca Tudor on 11.03.2023.
//
#include "Dynamic_Array.h"


template <class T>
DynamicArray<T>::DynamicArray() {
    length = 0;
    capacity = 0;
    array = nullptr;
}

template <class T>
DynamicArray<T>::DynamicArray(size_t _length, T *_array) {
    length = _length;
    capacity = 2 * (length + 1);
    array = new T[capacity];

    size_t  i;
    for(i = 0; i < length; i++)
    {
        array[i] = _array[i];
    }
}

template <class T>
DynamicArray<T>::DynamicArray(size_t _length) {
    length = _length;
    capacity = 2 * (length + 1);
    array = new T[capacity];
}

template <class T>
DynamicArray<T>::DynamicArray(size_t _length, size_t _capacity, T *_array) {
    length = _length;
    capacity = _capacity;
    array = new T[capacity];

    size_t i;
    for(i = 0; i < length; i++)
    {
        array[i] = _array[i];
    }
}

template <class T>
DynamicArray<T>::~DynamicArray()
{
    delete[] array;
}


template<class T>
size_t DynamicArray<T>::size() {
    return length;
}

template<class T>
void DynamicArray<T>::resize(size_t newCapacity) {
    if(newCapacity < length)
        throw std::out_of_range("New capacity cannot be less than the actual one");

    capacity = newCapacity;

    T *newArray = new T[newCapacity];
    size_t i;
    for(i = 0; i < length; i++){
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

template<class T>
void DynamicArray<T>::automaticResize()
{
    capacity *= 2;

    T *newArray = new T[capacity];
    for(size_t i = 0; i < length; i++) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
}


template<class T>
T DynamicArray<T>::getElement(size_t index) {
    if(index >= length)
        throw std::out_of_range("Index out of range");

    return array[index];
}

template<class T>
void DynamicArray<T>::setElement(size_t index, T value) {
    if(index >= length)
        throw std::out_of_range("Index out of range");

    array[index] = value;
}

template<class T>
void DynamicArray<T>::addToEnd(T value) {
    if(length == capacity)
        automaticResize();

    array[length++] = value;
}

template<class T>
void DynamicArray<T>::addToPosition(size_t index, T value) {
    if(index < 0 || index >= length)
        throw std::out_of_range("Index out of range");

    if (length == capacity)
        automaticResize();

    size_t i;
    for(i = index; i < length - 1; i++)
        array[i] = array[i+1];

    array[index] = value;
    length++;
}

template<class T>
void DynamicArray<T>::deleteFromEnd() {
    length--;

    if(length == capacity / 4)
        resize(capacity/2);
}

template<class T>
void DynamicArray<T>::deleteFromPosition(size_t index) {
    if(index < 0 || index >= length)
        throw std::out_of_range("Index out of range");

    size_t i;
    for(i = index; i < length - 1; i++)
        array[i] = array[i + 1];

    length--;

    if(length == capacity / 4)
        resize(capacity / 2);
}

template<class T>
void DynamicArray<T>::display() {
    std::cout << "Your array has the length: " << length << " and it looks like this: ";
    int i;
    for(i = 0; i < length; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}