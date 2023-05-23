#include "ShortTest.h"
#include <cassert>
#include "Map.h"
#include "MapIterator.h"

void basicTest(){
    Map m;
    assert(m.isEmpty() == true);
    assert(m.size() == 0); //add elements
    assert(m.add(13,13)==NULL_TVALUE);
    assert(m.add(25,25)==NULL_TVALUE);
    assert(m.add(37,37)==NULL_TVALUE);
    m.printMap();
}
void testAll() { //call each function to see if it is implemented
	Map m;
	assert(m.isEmpty() == true);
	assert(m.size() == 0); //add elements
	assert(m.add(5,5)==NULL_TVALUE);
	assert(m.add(1,111)==NULL_TVALUE);
	assert(m.add(10,110)==NULL_TVALUE);
	assert(m.add(7,7)==NULL_TVALUE);
	assert(m.add(1,1)==111);
	assert(m.add(10,10)==110);
	assert(m.add(-3,-3)==NULL_TVALUE);
	assert(m.size() == 5);
    m.printMap();
	assert(m.search(10) == 10);
	assert(m.search(16) == NULL_TVALUE);
	assert(m.remove(1) == 1);
	assert(m.remove(6) == NULL_TVALUE);
	assert(m.size() == 4);


	TElem e;
	MapIterator id = m.iterator();
	id.first();
	int s1 = 0, s2 = 0;
	while (id.valid()) {
		e = id.getCurrent();
		s1 += e.first;
		s2 += e.second;
		id.next();
	}
	assert(s1 == 19);
	assert(s2 == 19);

}


//test the function mapInterval

void testMapInterval() {
    Map m;
    assert(m.isEmpty() == true);
    assert(m.size() == 0); //add elements
    assert(m.add(5, 5) == NULL_TVALUE);
    assert(m.add(1, 111) == NULL_TVALUE);
    assert(m.add(10, 110) == NULL_TVALUE);
    assert(m.add(7, 7) == NULL_TVALUE);
    assert(m.add(1, 1) == 111);
    assert(m.add(10, 10) == 110);
    assert(m.add(-3, -3) == NULL_TVALUE);
    assert(m.size() == 5);
    m.printMap();
    assert(m.search(10) == 10);
    assert(m.search(16) == NULL_TVALUE);
    assert(m.remove(1) == 1);
    assert(m.remove(6) == NULL_TVALUE);
    assert(m.size() == 4);

    Map m2;
    m2 = m.mapInterval(2, 7);
//    assert(m2.size() == 3);
    m2.printMap();
    assert(m2.search(5) == 5);
    assert(m2.search(7) == 7);
    assert(m2.search(10) == 10);
    assert(m2.search(1) == NULL_TVALUE);
    assert(m2.search(-3) == NULL_TVALUE);
}

