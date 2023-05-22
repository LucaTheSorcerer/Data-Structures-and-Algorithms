#pragma once
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::make_pair(-111111, -111111)
const int INITIAL_SIZE = 0;
const long long int INITIAL_CAPACITY = 20;
const int MAX_REHASHES = 100000;
const double LOAD_FACTOR_THRESHOLD = 0.75;
#define TABLE_SIZE 10

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
    friend class MapIterator;

private:
    static const int INITIAL_CAPACITY = 16;
    static const float MAX_LOAD_FACTOR;
    static const int MAX_REHASHES;



    struct Bucket {
        bool occupied = false;
        TElem element = NULL_TELEM;
    };

    Bucket table1[TABLE_SIZE];
    Bucket table2[TABLE_SIZE];
    int tableSize;

    int hashFunction1(TKey key) const {
        return key % TABLE_SIZE;
    }

    int hashFunction2(TKey key) const {
        return (key * 13) % TABLE_SIZE;
    }

    void resize();
public:
    Map();
    ~Map();

    TValue add(TKey key, TValue value);
    TValue search(TKey key) const;
    TValue remove(TKey key);
    int size() const;
    bool isEmpty() const;
};