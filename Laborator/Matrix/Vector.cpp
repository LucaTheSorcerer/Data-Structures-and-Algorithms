//
// Created by Luca Tudor on 18.03.2023.
//
#include "Vector.h"

// Teta(1)
Vector::Vector()
{
    /// <summary>
    /// Initiem datele si facem loc in memorie pentru ele
    /// </summary>
    this->len = 0;
    this->capacity = 2;
    this->v = (int*)malloc(sizeof(int) * this->capacity);
}

// Teta(1)
Vector::~Vector()
{
    /// <summary>
    /// Eliberam memoria
    /// </summary>
    free(this->v);
}

/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
void Vector::Adauga(int x)
{
    /// Adaugam un element in vector
    /// in cazul in care avem nevoie de mai multa memorie , dublam capacitatea
    /// vectorului
    if (this->len + 1 >= this->capacity)
    {
        int new_capacity = 2 * this->capacity;
        int* new_v = (int*)malloc(sizeof(int) * new_capacity);
        for (int i = 0; i < this->len; i++)
            new_v[i] = this->v[i];
        free(this->v);
        this->v = new_v;
        this->capacity = new_capacity;
    }

    v[this->len++] = x;
}

/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
void Vector::Sterge(int x)
{
    /// Stergem un element din vector
    int ok = 0;
    for (int i = 0; i < this->len; i++)
    {
        if (!ok && x == this->v[i])
            ok = 1;

        if (ok && i != this->len-1)
            this->v[i] = this->v[i + 1];
    }

    if (ok)
        this->len--;
}

// Teta(1)
int Vector::getLen() const{
    /// returnam lungimea vectorului
    return this->len;
}

/// Pentru telement :

// Teta(1)
Vector1::Vector1()
{
    /// <summary>
    /// Initiem datele si facem loc in memorie pentru ele
    /// </summary>
    this->len = 0;
    this->capacity = 2;
    this->v = (TElem*)malloc(sizeof(TElem) * this->capacity);
}

// Teta(1)
Vector1::~Vector1()
{
    /// <summary>
    /// Eliberam memoria
    /// </summary>
    free(this->v);
}

/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
void Vector1::Adauga(TElem x)
{
    /// Adaugam un element in vector
    /// in cazul in care avem nevoie de mai multa memorie , dublam capacitatea
    /// vectorului
    if (this->len + 1 >= this->capacity)
    {
        int new_capacity = 2 * this->capacity;
        TElem* new_v = (TElem*)malloc(sizeof(TElem) * new_capacity);
        for (int i = 0; i < this->len; i++)
            new_v[i] = this->v[i];
        free(this->v);
        this->v = new_v;
        this->capacity = new_capacity;
    }

    v[this->len++] = x;
}

/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
void Vector1::Sterge(TElem x)
{
    /// Stergem un element din vector
    int ok = 0;
    for (int i = 0; i < this->len; i++)
    {
        if (!ok && x == this->v[i])
            ok = 1;

        if (ok && i != this->len - 1)
            this->v[i] = this->v[i + 1];
    }

    if (ok)
        this->len--;
}

// Teta(1)
int Vector1::getLen() const {
    /// returnam lungimea vectorului
    return this->len;
}