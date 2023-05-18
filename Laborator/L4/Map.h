#pragma once
#include <utility>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111)
const int INITIAL_SIZE = 10;
class MapIterator;

struct Node
{
    bool occupied;
    TElem element;

    Node()
    {
        occupied = false;
        element.first = NULL_TVALUE;
        element.second = NULL_TVALUE;
    }
};


class Map {
	//DO NOT CHANGE THIS PART
	friend class MapIterator;
	private:
		//TODO - Representation
        static const int INITIAL_CAPACITY = 10;
        static const int MAX_REHASHES = 20;
        static const double LOAD_FACTOR_THRESHOLD;

        Node* table1;
        Node* table2;
        int capacity;
        int size_;

        size_t hashFunction1(TKey key) const;
        size_t hashFunction2(TKey key) const;
        void automaticResize();
        void resize(int newCapacity);
        void rehash();

public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	int size() const;

	//checks whether the map is empty or not
	bool isEmpty() const;

	//returns an iterator for the map
	MapIterator iterator() const;

	// destructor
	~Map();

    void printMap() const;
};



