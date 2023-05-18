#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	//TODO - Implementation
    first();
}


void MapIterator::first() {
	//TODO - Implementation

    currentPosition = -1;
    currentTable = 0;
    next();
}


void MapIterator::next() {
	//TODO - Implementation
    if(!valid()) {
        throw std::exception();
    }

    if (currentTable == 0) {
        currentPosition++;
        if (currentPosition >= map.capacity || !map.table1[currentPosition].occupied) {
            currentTable = 1;
            currentPosition = -1;
            next();
        }
    }
    else {
        currentPosition++;
        while (currentPosition < map.capacity && !map.table2[currentPosition].occupied) {
            currentPosition++;
        }
    }
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation

    if (!valid()) {
        throw std::exception();
    }

    if (currentTable == 0) {
        return map.table1[currentPosition].element;
    }
    else {
        return map.table2[currentPosition].element;
    }
	return NULL_TELEM;
}


bool MapIterator::valid() const {
	//TODO - Implementation
    return currentPosition < map.capacity;
}



