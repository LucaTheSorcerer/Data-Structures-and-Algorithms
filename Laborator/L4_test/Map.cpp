#include "Map.h"

// Constructor
Map::Map() {
    tableSize = 0;
}

// Destructor
Map::~Map() {
    // No dynamic memory to deallocate
}

// Adds a pair (key, value) to the map
TValue Map::add(TKey key, TValue value) {
    // Check if the key already exists in the map
    TValue oldValue = search(key);
    if (oldValue != NULL_TVALUE) {
        // Update the value and return the old value
        int h1 = hashFunction1(key);
        int h2 = hashFunction2(key);
        if (table1[h1].element.first == key) {
            table1[h1].element.second = value;
        } else {
            table2[h2].element.second = value;
        }
        return oldValue;
    }

    // Attempt to add the pair to the tables
    int rehashesCount = 0;
    TKey currentKey = key;
    TValue currentValue = value;
    while (rehashesCount < TABLE_SIZE) {
        int h1 = hashFunction1(currentKey);
        int h2 = hashFunction2(currentKey);
        Bucket& bucket1 = table1[h1];
        Bucket& bucket2 = table2[h2];

        // Check if the slot in table1 is available
        if (!bucket1.occupied) {
            bucket1.occupied = true;
            bucket1.element = std::make_pair(currentKey, currentValue);
            tableSize++;
            return NULL_TVALUE;
        }

        // Check if the slot in table2 is available
        if (!bucket2.occupied) {
            bucket2.occupied = true;
            bucket2.element = std::make_pair(currentKey, currentValue);
            tableSize++;
            return NULL_TVALUE;
        }

        // If both slots are occupied, perform a swap and continue rehashing
        std::swap(currentKey, bucket1.element.first);
        std::swap(currentValue, bucket1.element.second);
        rehashesCount++;
    }

    // If the maximum number of rehashes is reached, resize the tables and try again
    resize();
    return add(currentKey, currentValue);
}

// Searches for the key and returns the value associated with the key if found, or NULL_TVALUE otherwise
TValue Map::search(TKey key) const {
    int h1 = hashFunction1(key);
    int h2 = hashFunction2(key);

    if (table1[h1].occupied && table1[h1].element.first == key) {
        return table1[h1].element.second;
    }

    if (table2[h2].occupied && table2[h2].element.first == key) {
        return table2[h2].element.second;
    }

    return NULL_TVALUE;
}

// Removes a key from the map and returns the value associated with the key if found, or NULL_TVALUE otherwise
TValue Map::remove(TKey key) {
    int h1 = hashFunction1(key);
    int h2 = hashFunction2(key);

    if (table1[h1].occupied && table1[h1].element.first == key) {
        TValue value = table1[h1].element.second;
        table1[h1].occupied = false;
        table1[h1].element = NULL_TELEM;
        tableSize--;
        return value;
    }

    if (table2[h2].occupied && table2[h2].element.first == key) {
        TValue value = table2[h2].element.second;
        table2[h2].occupied = false;
        table2[h2].element = NULL_TELEM;
        tableSize--;
        return value;
    }

    return NULL_TVALUE;
}

void Map::resize() {
    Bucket* oldTable1 = table1;
    Bucket* oldTable2 = table2;
    int oldSize = TABLE_SIZE;

    TABLE_SIZE *= 2;
    tableSize = 0;

    table1 = new Bucket[TABLE_SIZE];
    table2 = new Bucket[TABLE_SIZE];

    for (int i = 0; i < oldSize; i++) {
        if (oldTable1[i].occupied) {
            add(oldTable1[i].element.first, oldTable1[i].element.second);
        }
        if (oldTable2[i].occupied) {
            add(oldTable2[i].element.first, oldTable2[i].element.second);
        }
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

// Returns the number of pairs (key, value) in the map
int Map::size() const {
    return tableSize;
}

// Checks whether the map is empty
bool Map::isEmpty() const {
    return tableSize == 0;
}