#include <cassert>
#include "Matrix.h"

using namespace std;

void testAll() { 
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
    m.print();
    cout << endl;
	assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    m.print();
    assert(m.element(1, 2) == NULL_TELEM);
}