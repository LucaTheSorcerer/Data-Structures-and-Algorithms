//
// Created by Luca Tudor on 18.03.2023.
//

#pragma once
#include "Vector.h"

typedef int TElem;

#define NULL_TELEM 0

class Matrix {
private:
    /* aici e reprezentarea */
    int nr_Linii;
    int nr_Coloane;
    Vector Line, Col;
    Vector1 Val;
public:
    //constructor
    //se arunca exceptie daca nrLines<=0 sau nrColumns<=0
    Matrix(int nrLinii, int nrColoane);


    //destructor
    ~Matrix(){};

    //returnare element de pe o linie si o coloana
    //se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
    //indicii se considera incepand de la 0
    TElem element(int i, int j) const;


    // returnare numar linii
    int nrLines() const;

    // returnare numar coloane
    int nrColumns() const;


    // modificare element de pe o linie si o coloana si returnarea vechii valori
    // se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
    TElem modify(int i, int j, TElem);

};







