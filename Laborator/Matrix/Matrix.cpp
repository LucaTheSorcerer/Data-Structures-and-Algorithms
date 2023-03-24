//
// Created by Luca Tudor on 18.03.2023.
//
#include "Matrix.h"
#include <exception>

using namespace std;

/// Teta(1)
Matrix::Matrix(int m, int n) {
    ///
    /// Constructor pentru Matrice
    ///  - verificam ca numarul de matrici si coloane sa fie > 0
    /// daca este atunci modificam daca nu ridicam o eroare

    if (m <= 0 || n <= 0)
    {
        throw "Matricea nu poate fi vida";
    }

    this->nr_Linii = m;
    this->nr_Coloane = n;
}


// Teta(1)
int Matrix::nrLines() const{
    /* returneaza numarul de linii(int) */
    return this->nr_Linii;
}

// Teta(1)
int Matrix::nrColumns() const{
    /* returneaza numarul de coloane(int) */
    return this->nr_Coloane;
}

/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
TElem Matrix::element(int i, int j) const {
    /* cautam elemetul daca exita ii returnam valoarea altfel returnam valoarea 0
    se arunca exceptie daca (i,j) nu e pozitie valida in Matrice  */
    if (i < 0 || j < 0 || j >= this->nrColumns() || i >= this->nrLines())
    {
        throw exception();
        return NULL_TELEM;
    }

    for (int k = 0; k < this->Line.getLen(); k++)
        if (this->Line.v[k] == i && this->Col.v[k] == j)
            return this->Val.v[k];

    return NULL_TELEM;
}


/// Caz Favorabil : Teta(1)
/// Caz Defavorabil : Teta(n)
/// Caz Mediu : Teta(n)
/// Caz Total : O(n)
TElem Matrix::modify(int i, int j, TElem e) {
    /*
    ! se arunca exceptie daca (i,j) nu e pozitie valida in Matrice

    Cautam elementul e de pe linia i , coloana j in vectorii nostri daca exitsa
    il modificam si ii returnam vechea valoare

    Alftel

    Adaugam cate un element nou la finalul fiecaruia dintre cei 3 vectori
    apoi ii cautam pozitia corecta ,, mutam toate elementele la dreapta pentru a
    ii face loc.

    */
    if (i < 0 || j < 0 || j >= this->nrColumns() || i >= this->nrLines())
    {
        throw exception();
        return NULL_TELEM;
    }

    for (int k = 0; k < this->Line.getLen(); k++)
        if (this->Line.v[k] == i && this->Col.v[k] == j)
        {
            TElem aux = this->Val.v[k];
            this->Val.v[k] = e;
            return aux;
        }

    /// adaugam la final
    this->Line.Adauga(i);
    this->Col.Adauga(j);
    this->Val.Adauga(e);

    int k;
    for (k = this->Line.getLen() - 1; k >= 0; k--)
    {
        if (this->Line.v[k] < i)
            break;
        else if(this->Line.v[k] == i && this->Col.v[k] < i)
            break;
    }
    k++;

    /// facem loc
    for (int c = this->Line.getLen() - 1; c > k; c--)
    {
        this->Line.v[c] = this->Line.v[c - 1];
        this->Col.v[c] = this->Col.v[c - 1];
        this->Val.v[c] = this->Val.v[c - 1];
    }

    /// mutam elementul
    this->Line.v[k] = i;
    this->Col.v[k] = j;
    this->Val.v[k] = e;

    return NULL_TELEM;
}

