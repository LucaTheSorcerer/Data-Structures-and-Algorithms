//
// Created by Luca Tudor on 18.03.2023.
//

#pragma once
#include <stdlib.h>

typedef int TElem;

class Vector
{
public:
    int* v;
    Vector();
    ~Vector();
    int getLen() const;
    void Adauga(int x);
    void Sterge(int x);
private:
    int capacity;
    int len;
};

class Vector1
{
public:
    TElem* v;
    Vector1();
    ~Vector1();
    int getLen() const;
    void Adauga(TElem x);
    void Sterge(TElem x);
private:
    int capacity;
    int len;
};