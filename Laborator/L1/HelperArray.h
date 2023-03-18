//
// Created by Luca Tudor on 16.03.2023.
//

#pragma once
#include <stdlib.h>

typedef int TElem;

class Array {
private:
    int capacity;
    int len;
    void automaticResize();

public:
    int *vec;
    Array();
    ~Array();
    [[nodiscard]] int getLen() ;
    void addElement(int elem);
    void deleteElement(int elem);
    void resize(int newCapacity);
    void Adauga(int x);
    void Sterge(int x);


};



class Arraytelem {
private:
    int capacity;
    int len;
    void automaticResize();


public:
    TElem* vec;
    Arraytelem();
    ~Arraytelem();
    [[nodiscard]] int getLen() ;
    void addElement(TElem element);
    void deleteElement(TElem element);
    void resize(int newCapacity);
    void Adauga(int x);
    void Sterge(int x);
};
