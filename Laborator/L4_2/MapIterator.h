#pragma once
#include "Map.h"
#include <exception>
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	//TODO - Representation
    int currentPosition, currentTable;

	MapIterator(const Map& m);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

    //function that removes the current element from the map and goes to the next element

    void deleteCurrentAndMoveNext();


    //function that removes the current element from the map and goes to the next element

    void deleteCurrent();
};


