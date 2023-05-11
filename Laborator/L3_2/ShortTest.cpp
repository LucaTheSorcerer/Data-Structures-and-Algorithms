#include <cassert>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == NULL_TELEM);

    m.modify(0, 0, 1);
    m.modify(0, 1, 2);
    m.modify(0, 2, 3);
    m.modify(0, 3, 4);
    m.modify(1, 0, 5);
    m.modify(1, 1, 6);
    m.modify(1, 2, 7);
    m.modify(1, 3, 8);
    m.modify(2, 0, 9);
    m.modify(2, 1, 10);
    m.modify(2, 2, 11);
    m.modify(2, 3, 12);
    m.modify(3, 0, 13);
    m.modify(3, 1, 14);
    m.modify(3, 2, 15);
    m.modify(3, 3, 16);
    m.modify(0, 1, NULL_TELEM);
    m.modify(1, 2, NULL_TELEM);


    assert(m.element(0, 0) == 1);
    assert(m.element(0, 1) == NULL_TELEM);
    assert(m.element(0, 2) == 3);
    assert(m.element(0, 3) == 4);
    assert(m.element(1, 0) == 5);
    assert(m.element(1, 1) == 6);
    assert(m.element(1, 2) == NULL_TELEM);
    assert(m.element(1, 3) == 8);
    assert(m.element(2, 0) == 9);
    assert(m.element(2, 1) == 10);
    assert(m.element(2, 2) == 11);
    assert(m.element(2, 3) == 12);
    assert(m.element(3, 0) == 13);
    assert(m.element(3, 1) == 14);
    assert(m.element(3, 2) == 15);
    assert(m.element(3, 3) == 16);
    m.print();

    //extra

}