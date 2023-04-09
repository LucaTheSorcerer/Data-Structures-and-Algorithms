#include <assert.h>
#include "Matrix.h"
#include "ExtendedTest.h"
#include <iostream>
#include <exception>

using namespace std;


void testCreate() {
	cout << "Test create" << endl;
	Matrix m(10, 10);
	assert(m.nrLines() == 10);
	assert(m.nrColumns() == 10);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			assert(m.element(i, j) == NULL_TELEM);
}

void testModify() {
	cout << "Test modify" << endl;
	Matrix m(10, 10);
	for (int j = 0; j < m.nrColumns(); j++)
		m.modify(4, j, 3);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i == 4)
				assert(m.element(i, j) == 3);
			else
				assert(m.element(i, j) == NULL_TELEM);
}

void testQuantity() {
	cout << "Test quantity" << endl;
	Matrix m(200, 300);
    assert(m.element(5, 5) == 0);
    m.modify(5,5,1);
    assert(m.element(5, 5) == 1);
    m.modify(5,5,0);
    assert(m.element(5, 5) == 0);
	for (int i = m.nrLines() / 2; i < m.nrLines(); i++) {
		for (int j = 0; j <= m.nrColumns() / 2; j++)
		{
			int v1 = j;
			int v2 = m.nrColumns() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				m.modify(i, v1, i*v1);
			else
				if (v1 % 3 == 0)
					m.modify(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				m.modify(i, v2, i*v2);
			else
				if (v2 % 3 == 0)
					m.modify(i, v2, i + v2);
		}
	}
	for (int i = 0; i <= m.nrLines() / 2; i++) {
		for (int j = 0; j <= m.nrColumns() / 2; j++)
		{
			int v1 = j;
			int v2 = m.nrColumns() - v1 - 1;
			if (i % 2 == 0 && v1 % 2 == 0)
				m.modify(i, v1, i*v1);
			else
				if (v1 % 3 == 0)
					m.modify(i, v1, i + v1);
			if (i % 2 == 0 && v2 % 2 == 0)
				m.modify(i, v2, i*v2);
			else
				if (v2 % 3 == 0)
					m.modify(i, v2, i + v2);
		}
	}
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				assert(m.element(i, j) == i * j);
			else
				if (j % 3 == 0)
					assert(m.element(i, j) == i + j);
				else assert(m.element(i, j) == NULL_TELEM);
}

void testExceptions() {
	cout << "Test exceptions" << endl;
	Matrix m(10, 10);
	try {
		m.element(-10, 0);
		assert(false);
	}
	catch (exception&) {
		assert(true); 
	}
	try {
		m.modify(12, 0, 1);
		assert(false);
	}
	catch (exception&) {
		assert(true); 
	}
	try {
		assert(m.nrLines());
	}
	catch (exception&) {
		assert(false); 
	}
}

void testMix() {
	cout << "Test mix" << endl;
	int size = 2000;
	Matrix m(size/2, size);
	for (int i = 0; i < size/2; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				m.modify(i, j, 11);
			}
			else if (i == 100 * j) {
				m.modify(i, j, 111);
			}
			else if ((i + j) % 1111 == 0) {
				m.modify(i, j, 1111);
			}
		}
	}

	for (int i = 0; i < size/2; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				m.modify(i, j, NULL_TELEM);
			}
			else if (i == 100 * j) {
				m.modify(i, j, -111);
			}
			else if ((i + j) % 1111 == 3) {
				m.modify(i, j, 1);
			}
		}
	}
	for (int i = 0; i < size/2; i++) {
		for (int j = 0; j < size; j++) {
			TElem e = m.element(i, j);
			if (i == j) {
				assert(e == NULL_TELEM);
			}
			else if (i == 100 * j) {
				assert(e == -111);
			}
			else if ((i + j) % 1111 == 3) {
				assert(e == 1);
			}
			else if ((i + j) % 1111 == 0) {
				assert(e == 1111);
			}
			else {
				assert(e == NULL_TELEM);
			}
		}
	}
}

void testTranspose() {
    cout << "Test transpose" << endl;
    Matrix mat{3, 4};

    mat.modify(0, 0, 1);
    mat.modify(1, 1, 6);
    mat.modify(1, 2, 7);

   mat.transpose();

    assert(mat.nrLines() == 4);
    assert(mat.nrColumns() == 3);
    assert(mat.element(0, 0) == 1);
    assert(mat.element(1, 1) == 6);
    assert(mat.element(2, 1) == 7);
    cout << "Test transpose passed" << endl;
}

void testTranspose2() {
    //This function tests the transpose() function
    cout << "Test transpose square mat" << endl;
    Matrix mat(3, 3);
    mat.modify(0, 0, 1);
    mat.modify(1, 1, 6);
    mat.modify(1, 2, 7);
    mat.modify(2, 1, 8); // Corrected row and column indices

    //transpose() function
    mat.transpose();

    //checks if the size of the matrix is correct
    assert(mat.nrLines() == 3);
    assert(mat.nrColumns() == 3);

    //check if the elements are in the correct position
    assert(mat.element(0, 0) == 1);
    assert(mat.element(1, 1) == 6);
    assert(mat.element(2, 1) == 7); // Corrected row and column indices
    assert(mat.element(1, 2) == 8); // Corrected row and column indices

    cout << "Test transpose square mat passed" << endl;
}


void testTranspose3() {
    //This function tests the transpose() function for a specific matrix
    cout << "Test transpose specific matrix" << endl;
    Matrix mat(3, 3);
    mat.modify(0, 0, 1);
    mat.modify(0, 1, 1);
    mat.modify(0, 2, 1);
    mat.modify(1, 0, 2);
    mat.modify(1, 1, 2);
    mat.modify(1, 2, 2);
    mat.modify(2, 0, 3);
    mat.modify(2, 1, 3);
    mat.modify(2, 2, 3);

    //transpose() function
    mat.print();
    mat.transpose();

    cout << endl;

    mat.print();

    //checks if the size of the matrix is correct
    assert(mat.nrLines() == 3);
    assert(mat.nrColumns() == 3);

    //check if the elements are in the correct position
    assert(mat.element(0, 0) == 1);
    assert(mat.element(0, 1) == 2);
    assert(mat.element(0, 2) == 3);
    assert(mat.element(1, 0) == 1);
    assert(mat.element(1, 1) == 2);
    assert(mat.element(1, 2) == 3);
    assert(mat.element(2, 0) == 1);
    assert(mat.element(2, 1) == 2);
    assert(mat.element(2, 2) == 3);

    cout << "Test transpose specific matrix passed" << endl;
}
//void test_unsparse_matrix() {
//    //This function tests the unsparse_matrix() function
//    cout << "Test unsparse_matrix" << endl;
//    Matrix m(3, 3);
//    m.modify(0, 0, 1);
//    m.modify(0, 1, 2);
//    m.modify(0, 2, 3);
//    m.modify(1, 0, 4);
//    m.modify(1, 1, 5);
//    m.modify(1, 2, 6);
//    m.modify(2, 0, 7);
//    m.modify(2, 1, 8);
//    m.modify(2, 2, 9);
//
//    //unsparse_matrix() function
//    m.unsparse_matrix();
//
//    //checks if the matrix is unsparse
//    assert(m.element(0, 0) == 1);
//    assert(m.element(0, 1) == 2);
//    assert(m.element(0, 2) == 3);
//    assert(m.element(1, 0) == 4);
//    assert(m.element(1, 1) == 5);
//    assert(m.element(1, 2) == 6);
//    assert(m.element(2, 0) == 7);
//    assert(m.element(2, 1) == 8);
//    assert(m.element(2, 2) == 9);
//
//    cout << "The test has passed" << endl;
//
//}
void test_add() {
    cout << "Test add" << endl;

    Matrix m{3, 3};
    Matrix n{3, 3};

    m.modify(0, 0, 1);
    m.modify(1, 1, 2);
    m.modify(2, 2, 3);

    n.modify(0, 0, 1);
    n.modify(1, 1, 2);
    n.modify(2, 2, 3);

    Matrix* res = m.add(n);

    assert(res->element(0, 0) == 2);
    assert(res->element(1, 1) == 4);
    assert(res->element(2, 2) == 6);

    cout << "The test has passed" << endl;

    delete res;
}

void testSubtract() {
    Matrix A(3, 3);
    A.modify(0, 0, 1);
    A.modify(0, 1, 2);
    A.modify(0, 2, 3);
    A.modify(1, 0, 4);
    A.modify(1, 1, 5);
    A.modify(1, 2, 6);
    A.modify(2, 0, 7);
    A.modify(2, 1, 8);
    A.modify(2, 2, 9);

    Matrix B(3, 3);
    B.modify(0, 0, 1);
    B.modify(0, 1, 2);
    B.modify(0, 2, 3);
    B.modify(1, 0, 4);
    B.modify(1, 1, 5);
    B.modify(1, 2, 6);
    B.modify(2, 0, 7);
    B.modify(2, 1, 8);
    B.modify(2, 2, 9);

    A.subtract(B);

    assert(A.element(0, 0) == 0);
    assert(A.element(0, 1) == 0);
    assert(A.element(0, 2) == 0);
    assert(A.element(1, 0) == 0);
    assert(A.element(1, 1) == 0);
    assert(A.element(1, 2) == 0);
    assert(A.element(2, 0) == 0);
    assert(A.element(2, 1) == 0);
    assert(A.element(2, 2) == 0);
}

void testMatrixEquality() {
    Matrix a(3, 3);
    a.modify(0, 0, 1);
    a.modify(1, 1, 1);
    a.modify(2, 2, 1);

    Matrix b(3, 3);
    b.modify(0, 0, 1);
    b.modify(1, 1, 1);
    b.modify(2, 2, 1);

    Matrix c(3, 3);
    c.modify(0, 0, 1);
    c.modify(1, 1, 2);
    c.modify(2, 2, 1);

    if (a == b) {
        cout << "Matrices a and b are equal" << endl;
    } else {
        cout << "Matrices a and b are not equal" << endl;
    }

    if (a == c) {
        cout << "Matrices a and c are equal" << endl;
    } else {
        cout << "Matrices a and c are not equal" << endl;
    }
}




void testAllExtended() {
	testCreate(); //passed
	testModify(); //passed
	testQuantity(); //passed
	testMix(); //passed
	testExceptions(); //passed
    testTranspose();
    testTranspose2();
    testTranspose3();
    test_add();
    testMatrixEquality();
}