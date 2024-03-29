#pragma once
#include <utility>
#include <cinttypes>
#include <cstdlib>
#include <vector>
#include <unordered_set>
//DO NOT INCLUDE MAPITERATOR


//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)
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
    static const int MAX_REHASHES = 10;
    static const double LOAD_FACTOR_THRESHOLD;

    Node* table1;
    Node* table2;
    int capacity;
    int size_;



    int hashFunction1( TKey& key) const;
    int hashFunction2( TKey& key) const;

    void resizeAndRehash(int newCapacity);
    void automaticResize();


public:

	// implicit constructor
	Map();

	// adds a pair (key,value) to the map
	//if the key already exists in the map, then the value associated to the key is replaced by the new value and the old value is returned
	//if the key does not exist, a new pair is added and the value null is returned
	TValue add(TKey c, TValue v);

	//searches for the key and returns the value associated with the key if the map contains the key or null: NULL_TVALUE otherwise
	[[nodiscard]] TValue search(TKey c) const;

	//removes a key from the map and returns the value associated with the key if the key existed ot null: NULL_TVALUE otherwise
	TValue remove(TKey c);

	//returns the number of pairs (key,value) from the map
	[[nodiscard]] int size() const;

	//checks whether the map is empty or not
	[[nodiscard]] bool isEmpty() const;


	//returns an iterator for the map
	[[nodiscard]] MapIterator iterator() const;

	// destructor
	~Map();

    void printMap() const;

    //Assignment operator for copy constructor

    Map& operator=(const Map& other);

    //function that returns a new map with the keys in the interval [key1, key2]
    Map mapInterval(TKey key1, TKey key2) const;

    //function that returns all the keys from a map in a vector
    std::vector<TKey> keySet() const;

    //function that returns all the values from a map in a vector
    std::vector<TValue> valueSet() const;

    //function that returns the number of pairs (key, value) from the map that have the value equal to the one given as parameter
    int countValues(TValue value) const;

    //function that updates an existing value for a given key if it exists

    bool update(TKey& key, TValue& newValue);

    //Copy constructor

    Map(const Map& other);

    //function that returns a new map with only the even keys from another map using the copy constructor

    Map getEvenKeys(const Map& other) const;

    //function that returns all the collision between elements from a map

    std::vector<TElem> getCollisions() const;

    //function that returns all the collision in map in a form of key value pairs

    std::vector<std::pair<TKey, TValue>> getCollisionsPairs() const;


};



