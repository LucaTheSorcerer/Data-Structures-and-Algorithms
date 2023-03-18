//
// Created by Luca Tudor on 18.03.2023.
//
#include "HelperArray.h"
#include <stdexcept>


Array::Array() {
    this -> len = 0;
    this -> capacity = 2;
    this->vec = new int[this->capacity];
    //this->vec = nullptr;
}

Array::~Array() {
    free(this->vec);
}

void Array::Adauga(int x)
{
    /// Adaugam un element in vector
    /// in cazul in care avem nevoie de mai multa memorie , dublam capacitatea
    /// vectorului
    if (this->len + 1 >= this->capacity)
    {
        int new_capacity = 2 * this->capacity;
        int* new_v = (int*)malloc(sizeof(int) * new_capacity);
        for (int i = 0; i < this->len; i++)
            new_v[i] = this->vec[i];
        free(this->vec);
        this->vec = new_v;
        this->capacity = new_capacity;
    }

    vec[this->len++] = x;
}

void Array::Sterge(int x)
{
    /// Stergem un element din vector
    int ok = 0;
    for (int i = 0; i < this->len; i++)
    {
        if (!ok && x == this->vec[i])
            ok = 1;

        if (ok && i != this->len-1)
            this->vec[i] = this->vec[i + 1];
    }

    if (ok)
        this->len--;
}



void Array::resize(int newCapacity) {
    if(newCapacity < this->len)
        throw std::out_of_range("New capacity cannot be less than the actual one");

    this->capacity = newCapacity;

    int *new_vec = new int[this->capacity];

    for(size_t i = 0; i < this->len; i++) {
        new_vec[i] = vec[i];
    }

    delete[] vec;
    this-> vec = new_vec;
}

void Array::automaticResize() {

    this->capacity *= 2;

    int *new_vec = new int[this->capacity];

    for(size_t i = 0; i < this->len; i++) {
        new_vec[i] = vec[i];
    }

    delete[] vec;
    vec = new_vec;
}

void Array::addElement(int elem) {

    if(this->len + 1 == this->capacity){
        automaticResize();
    }

    for(size_t i = 0; i < this->len; i++)
        this->vec[i] = this->vec[i+1];

    vec[this->len++] = elem;
}

void Array::deleteElement(int elem) {
    int check = 0;
    for(size_t i = 0; i < this->len; i++)
    {
        if(!check && elem == this->vec[i])
            check = 1;

        if(check && i != this->len-1)
            this->vec[i] = this->vec[i+1];
    }

    if(check)
        this -> len--;
}

int Array::getLen()  {
    return this->len;
}


//////////////////////////////



Arraytelem::Arraytelem() {
    this->len = 0;
    this->capacity = 0;
    this->vec = new TElem[this->capacity];
}

Arraytelem::~Arraytelem() {
    free(this->vec);
}

void Arraytelem::Adauga(TElem x)
{
    /// Adaugam un element in vector
    /// in cazul in care avem nevoie de mai multa memorie , dublam capacitatea
    /// vectorului
    if (this->len + 1 >= this->capacity)
    {
        int new_capacity = 2 * this->capacity;
        int* new_v = (int*)malloc(sizeof(int) * new_capacity);
        for (int i = 0; i < this->len; i++)
            new_v[i] = this->vec[i];
        free(this->vec);
        this->vec = new_v;
        this->capacity = new_capacity;
    }

    vec[this->len++] = x;
}

void Arraytelem::Sterge(TElem x)
{
    /// Stergem un element din vector
    int ok = 0;
    for (int i = 0; i < this->len; i++)
    {
        if (!ok && x == this->vec[i])
            ok = 1;

        if (ok && i != this->len-1)
            this->vec[i] = this->vec[i + 1];
    }

    if (ok)
        this->len--;
}


void Arraytelem::resize(int newCapacity) {
    if(newCapacity < this->len)
        throw std::out_of_range("New capacity cannot be less than the actual one");

    this->capacity = newCapacity;

    int *new_vec = new TElem[this->capacity];

    for(size_t i = 0; i < this->len; i++) {
        new_vec[i] = vec[i];
    }

    delete[] vec;
    this-> vec = new_vec;
}

void Arraytelem::automaticResize() {

    this->capacity *= 2;

    int *new_vec = new TElem[this->capacity];

    for(size_t i = 0; i < this->len; i++) {
        new_vec[i] = vec[i];
    }

    delete[] vec;
    vec = new_vec;
}

void Arraytelem::addElement(int elem) {

    if(this->len + 1 == this->capacity){
        automaticResize();
    }

    for(size_t i = 0; i < this->len; i++)
        this->vec[i] = this->vec[i+1];

    vec[this->len++] = elem;
}

void Arraytelem::deleteElement(TElem elem) {
    int check = 0;
    for(size_t i = 0; i < this->len; i++)
    {
        if(!check && elem == this->vec[i])
            check = 1;

        if(check && i != this->len-1)
            this->vec[i] = this->vec[i+1];
    }

    if(check)
        this -> len--;
}

int Arraytelem::getLen()  {
    return this->len;
}
