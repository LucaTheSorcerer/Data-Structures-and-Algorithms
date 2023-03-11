//
// Created by Luca Tudor on 11.03.2023.
//
#include <iostream>

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_DYNAMIC_ARRAY_H
#define DATA_STRUCTURES_AND_ALGORITHMS_DYNAMIC_ARRAY_H
template <class T>
class DynamicArray
{
private:
    T *array;
    size_t length;
    size_t capacity;
    void swap(int *x, int *y);
    void automaticResize();


public:
    explicit DynamicArray();

    explicit DynamicArray(size_t length);

    DynamicArray(size_t length, T *array);

    DynamicArray(size_t length, size_t capacity, T *array);

    //Destructor
    ~DynamicArray();

    size_t size();

    void resize(size_t newCapacity);

    void display();

    /*
     * Some basic operation for the ADT array and the majority
     * that are required for uni
     */
    T delete_element(size_t index);

    T getElement(size_t index);

    void setElement(size_t index, T value);

    void addToEnd(T value);

    void addToPosition(size_t index, T value);

    void deleteFromEnd();

    void deleteFromPosition(size_t index);

    /*
     * Some extra function to play around with the array
     */
    T maximum();

    T minimum();

    T sum();

    T average();

    void reverseArray();

    void reverseArray2();

    void insertionSort();

    T isSorted();

    void rearrangeArray();

    /*
     * Sorting Algorithms and others
     */
    DynamicArray* mergeSort(DynamicArray array2);

    DynamicArray* unionArray(DynamicArray array2);

    DynamicArray* diffArray(DynamicArray array2);

    DynamicArray* interArray(DynamicArray array2);

};

#endif //DATA_STRUCTURES_AND_ALGORITHMS_DYNAMIC_ARRAY_H


