#pragma once
#include <utility>
#include <complex>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::pair<TKey, TValue>(-111111, -111111)

class Map {
private:
    static const int INITIAL_CAPACITY = 16;
    static const double LOAD_FACTOR_THRESHOLD;

    struct Node {
        bool occupied;
        TElem element;

        Node() : occupied(false), element(NULL_TELEM) {}
    };

    Node* table1;
    Node* table2;
    int capacity;
    int size_;
    int MAX_REHASHES = 10;

    int hashFunction1(TKey key) const {
        return std::abs(key) % capacity;
    }

    int hashFunction2(TKey key) const {
        return (std::abs(key) * 13) % capacity;
    }

    void automaticResize();
    void resizeAndRehash(int newCapacity);
    bool insertElement(Node *table, TElem element);
    TValue searchElement(Node *table, TKey key) const;
    TValue removeElement(Node *table, TKey key);

public:
    // implicit constructor
    Map();

    // adds a pair (key, value) to the map
    // if the key already exists in the map, then the value associated with the key is replaced by the new value,
    // and the old value is returned
    // if the key does not exist, a new pair is added, and the value NULL_TVALUE is returned
    TValue add(TKey key, TValue value);

    // searches for the key and returns the value associated with the key if the map contains the key,
    // or NULL_TVALUE otherwise
    TValue search(TKey key) const;

    // removes a key from the map and returns the value associated with the key if the key existed,
    // or NULL_TVALUE otherwise
    TValue remove(TKey key);

    // returns the number of pairs (key, value) in the map
    int size() const;

    // checks whether the map is empty or not
    bool isEmpty() const;

    // destructor
    ~Map();
};