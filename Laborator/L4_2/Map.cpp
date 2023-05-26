#include <iostream>
#include "Map.h"
#include "MapIterator.h"

const double Map::LOAD_FACTOR_THRESHOLD = 0.7;

/**
 * @brief This is the constructor of the Map class.
 * @details: It initializes the capacity of the map to 6 and the size to 0. It also initializes the two tables to be of
 * size 6 so capacity
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 *
 */
Map::Map() {
    capacity = 6;
    size_ = 0;
    table1 = new Node[capacity];
    table2 = new Node[capacity];

}

/**
 * @brief This is the destructor of the Map class.
 * @details: It deletes the two tables of the map.
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
Map::~Map() {
    delete[] table1;
    delete[] table2;
}

/**
 * @brief function is responsible for inserting a new key-value pair in the map
 * @details: The function first checks if the map needs to be resized. If it does, it calls the function automaticResize.
 * A new node is created to store the new key-value pair.The node's element is set to the new key-value pair (c,v) and
 * the node's occupied field is set to true. The function then checks if the key already exists in the map by calling
 * the search function. If the key already exists, the value associated with it is updated, and the previous value is
 * returned.If the key is not found, the function enters a loop that attempt to insert the new node into the hash map.
 * The loop will run until either the node is successfully inserted or a maximum number of rehashes is reached.
 * In each iteration of the loop, the positions for the key 'currentKey' are computed using the two hash functions.
 * The function checks if the position in the first table is unoccupied. If it is, the new node is inserted there, the
 * size is incremented, and NULL_TVALUE is returned. If the position in the first table is occupied, the function swaps
 * the current node with the node at that position and updates the current key and value with the key and value of the
 * swapped node. This process is then repeated for the second table. If the maximum number of rehashes is reached, and
 * the node still cannot be inserted, the automaticResize function is called to resizeAndRehash the hash map, and the add
 * function is recursively called with the original key and value. If the insertion is unsuccessful, the function
 * returns NULL_TVALUE.
 * @param c the key of the new node
 * @param v the value of the new node
 * @return the previous value associated with the key if the key already exists in the map, or NULL_TVALUE otherwise
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1) amortized with reasonably high probability
 * @TimeComplexity-WorstCase: θ(n)
 */
TValue Map::add(TKey c, TValue v) {
    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD) {
        automaticResize();
    }

    Node newNode;
    newNode.element = std::make_pair(c, v);
    newNode.occupied = true;

    if (search(c) != NULL_TVALUE) {
        int hash1 = hashFunction1(c);
        int hash2 = hashFunction2(c);
        TValue oldValue;

        if (table1[hash1].occupied && table1[hash1].element.first == c) {
            oldValue = table1[hash1].element.second;
            table1[hash1].element.second = v;
        } else {
            oldValue = table2[hash2].element.second;
            table2[hash2].element.second = v;
        }
        return oldValue;
    }

    int rehashCount = 0;
    TKey currentKey = c;
    TValue currentValue = v;

    while (rehashCount < MAX_REHASHES) {
        int position1 = hashFunction1(currentKey);
        int position2 = hashFunction2(currentKey);

        if (!table1[position1].occupied) {
            table1[position1] = newNode;
            size_++;
            return NULL_TVALUE;
        } else {
            std::swap(table1[position1], newNode);
            currentKey = newNode.element.first;
            currentValue = newNode.element.second;
        }

        if (!table2[position2].occupied) {
            table2[position2] = newNode;
            size_++;
            return NULL_TVALUE;
        } else {
            std::swap(table2[position2], newNode);
            currentKey = newNode.element.first;
            currentValue = newNode.element.second;
        }

        rehashCount++;
    }

    if (rehashCount == MAX_REHASHES) {
        automaticResize();
        return add(currentKey, currentValue);
    }

    return NULL_TVALUE;
}



/**
 * @brief function used to automatically resizeAndRehash the two hash tables
 * @details: the function calls the function resizeAndRehash with a new capacity determined by the fullness of the hash tables
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(n)
 */
void Map::automaticResize() {
    if (size_ < capacity / 4 && capacity >= 10) {
        resizeAndRehash(capacity / 2);
//        std::cout << "Resizing downwards\n";

    } else {
        resizeAndRehash(capacity * 2);
//        std::cout << "Resizing upwards\n";
    }
}

/**
 * @brief function used to resizeAndRehash the two hash tables
 * @details: the function creates two new tables with the new capacity and rehashes all the elements from the old tables
 * @param newCapacity the new capacity of the hash tables
 * @TimeComplexity-BestCase: θ(n)
 * @TimeComplexity-AverageCase: θ(n)
 * @TimeComplexity-WorstCase: θ(n)
 */
void Map::resizeAndRehash(int newCapacity)
{
    int oldCapacity = capacity;
    capacity = newCapacity;

    Node* oldTable1 = table1;
    Node* oldTable2 = table2;

    table1 = new Node[capacity];
    table2 = new Node[capacity];

    for (int i = 0; i < newCapacity; i++)
    {
        table1[i].element = NULL_TELEM;
        table2[i].element = NULL_TELEM;
    }

    this->size_ = 0;

    for (int i = 0; i < oldCapacity; i++)
    {
        if (oldTable1[i].element != NULL_TELEM)
            add(oldTable1[i].element.first, oldTable1[i].element.second);
        if (oldTable2[i].element != NULL_TELEM)
            add(oldTable2[i].element.first, oldTable2[i].element.second);
    }

    delete[] oldTable1;
    delete[] oldTable2;
}

/**
 * @brief function used to find the value associated with a given key in the hash map
 * @details the function uses the two hash functions to find the position of the key in the hash tables and then
 * checks if the key is in the hash tables. If it is, it returns the value associated with the key, otherwise it
 * returns NULL_TVALUE
 * @param c the key of the element we are searching for
 * @return the value associated with the key c if it is in the hash tables, otherwise it returns NULL_TVALUE
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
TValue Map::search(TKey c) const{
    int hash1 = hashFunction1(c);
    int hash2 = hashFunction2(c);

    if(table1[hash1].occupied && table1[hash1].element.first == c)
        return table1[hash1].element.second;
    if(table2[hash2].occupied && table2[hash2].element.first == c)
        return table2[hash2].element.second;

    return NULL_TVALUE;
}


/**
 * @brief function used to remove an element from the hash map
 * @details This function removes an element with the given key from the map. It first calculates the two possible
 * indices for the key using the two hash functions. Then, it checks if the element at the first index matches the key.
 * If it does, it removes the element and returns its value. Otherwise, it checks if the element at the second index
 * matches the key. If it does, it removes the element and returns its value. If neither index contains the key,
 * it returns NULL_TVALUE.
 * @param c the key of the element we want to remove
 * @return the value associated with the key c if it is in the hash tables after removing the element, otherwise it
 * returns NULL_TVALUE
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(n) because when resizing downwards the time complexity of the function is dominated by
 * the time complexity of the automaticResize function that calls the resizeAndRehash function which has a time complexity of
 * θ(n)
 */
TValue Map::remove(TKey c) {
    int index1 = hashFunction1(c);
    int index2 = hashFunction2(c);

    if (table1[index1].occupied && table1[index1].element.first == c) {
        TValue oldValue = table1[index1].element.second;
        table1[index1].occupied = false;
        table1[index1].element = NULL_TELEM; // Reset the element to NULL_TELEM
        size_--;
        if (size_ < capacity / 4 && capacity >= 10) {
            automaticResize();
        }
        return oldValue;
    } else if (table2[index2].occupied && table2[index2].element.first == c) {
        TValue oldValue = table2[index2].element.second;
        table2[index2].occupied = false;
        table2[index2].element = NULL_TELEM; // Reset the element to NULL_TELEM
        size_--;
        if (size_ < capacity / 4 && capacity >= 10) {
            automaticResize();
        }
        return oldValue;
    }
    return NULL_TVALUE;
}


/**
 * @brief function used to return the current size of the hash map
 * @return the current size of the hash map
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
int Map::size() const {
    return size_;
}

/**
 * @brief function used to check if the hash map is empty
 * @return true if the hash map is empty, false otherwise
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
bool Map::isEmpty() const{
    return size_ == 0;
}

/**
 * @brief function used to return an iterator to the hash map
 * @return an iterator to the hash map
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
MapIterator Map::iterator() const {
    return MapIterator(*this);
}



/**
 * @brief first hash function used to calculate the index of an element in the first hash table
 * @param key the key of the element we want to find the index for
 * @return the index of the element in the first hash table
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
int Map::hashFunction1( TKey& key) const {
    return abs(key) % capacity;
}

/**
 * @brief second hash function used to calculate the index of an element in the second hash table
 * @param key the key of the element we want to find the index for
 * @return the index of the element in the second hash table
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
int Map::hashFunction2( TKey& key) const {
    return (abs(key) * 17 ) % capacity;
}


/**
 * @brief simple print function that prints the tables, used for debugging
 */
void Map::printMap() const {
    std::cout << "Map contents: " << std::endl;

    for(int i = 0; i < capacity; i++) {
        if(table1[i].occupied) {
            std::cout << "Table 1 - Position " << i << ": "
                      << table1[i].element.first << "=> " << table1[i].element.second << std::endl;
        }

        if(table2[i].occupied) {
            std::cout << "Table 2 - Position " << i << ": "
                      << table2[i].element.first << "=> " << table2[i].element.second << std::endl;
        }
    }

    std::cout << std::endl;
}




Map &Map::operator=(const Map &other) {

    if (this == &other)
        return *this;

    delete[] table1;
    delete[] table2;

    capacity = other.capacity;
    size_ = other.size_;

    table1 = new Node[capacity];
    table2 = new Node[capacity];

    for (int i = 0; i < capacity; i++) {
        table1[i] = other.table1[i];
        table2[i] = other.table2[i];
    }

    return *this;
}

Map Map::mapInterval(TKey key1, TKey key2) const {

    Map newMap;

    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            if (table1[i].element.first >= key1 && table1[i].element.first <= key2) {
                newMap.add(table1[i].element.first, table1[i].element.second);
            }
        }

        if (table2[i].occupied) {
            if (table2[i].element.first >= key1 && table2[i].element.first <= key2) {
                newMap.add(table2[i].element.first, table2[i].element.second);
            }
        }
    }

    return newMap;
}

std::vector<TKey> Map::keySet() const {

        std::vector<TKey> keys;

        for (int i = 0; i < capacity; i++) {
            if (table1[i].occupied) {
                keys.push_back(table1[i].element.first);
            }

            if (table2[i].occupied) {
                keys.push_back(table2[i].element.first);
            }
        }

        return keys;
}

std::vector<TValue> Map::valueSet() const {

        std::vector<TValue> values;

        for (int i = 0; i < capacity; i++) {
            if (table1[i].occupied) {
                values.push_back(table1[i].element.second);
            }

            if (table2[i].occupied) {
                values.push_back(table2[i].element.second);
            }
        }

        return values;
}

int Map::countValues(TValue value) const {

        int count = 0;

        for (int i = 0; i < capacity; i++) {
            if (table1[i].occupied) {
                if (table1[i].element.second == value) {
                    count++;
                }
            }

            if (table2[i].occupied) {
                if (table2[i].element.second == value) {
                    count++;
                }
            }
        }

        return count;
}

bool Map::update(TKey &key, TValue &newValue) {

        int index1 = hashFunction1(key);
        int index2 = hashFunction2(key);

        if (table1[index1].occupied) {
            if (table1[index1].element.first == key) {
                table1[index1].element.second = newValue;
                return true;
            }
        }

        if (table2[index2].occupied) {
            if (table2[index2].element.first == key) {
                table2[index2].element.second = newValue;
                return true;
            }
        }

        return false;
}

Map::Map(const Map &other) {

        capacity = other.capacity;
        size_ = other.size_;

        table1 = new Node[capacity];
        table2 = new Node[capacity];

        for (int i = 0; i < capacity; i++) {
            table1[i] = other.table1[i];
            table2[i] = other.table2[i];
        }
}

Map Map::getEvenKeys(const Map &other) const {

    Map newMap;

    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            if (table1[i].element.first % 2 == 0) {
                newMap.add(table1[i].element.first, table1[i].element.second);
            }
        }

        if (table2[i].occupied) {
            if (table2[i].element.first % 2 == 0) {
                newMap.add(table2[i].element.first, table2[i].element.second);
            }
        }
    }

    return newMap;
}

std::vector<TElem> Map::getCollisions() const {

    std::vector<TElem> collisions;

    //Check for collisions in table 1
    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            int index2 = hashFunction2(table1[i].element.first);
            if (table2[index2].occupied) {
                collisions.push_back(table1[i].element);
            }
        }
    }

    //Check for collisions in table 2
    for (int i = 0; i < capacity; i++) {
        if (table2[i].occupied) {
            int index1 = hashFunction1(table2[i].element.first);
            if (table1[index1].occupied) {
                collisions.push_back(table2[i].element);
            }
        }
    }


    return collisions;
}

std::vector<std::pair<TKey, TValue>> Map::getCollisionsPairs() const {
    std::vector<std::pair<TKey, TValue>> collisions;
    std::unordered_set<TKey> keys;

    // Check for collisions in table 1
    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            int index2 = hashFunction2(table1[i].element.first);
            if (table2[index2].occupied && table2[index2].element.first == table1[i].element.first) {
                if (keys.find(table1[i].element.first) == keys.end()) {
                    collisions.push_back(table1[i].element);
                    keys.insert(table1[i].element.first);
                }
            }
        }
    }

    // Check for collisions in table 2
    for (int i = 0; i < capacity; i++) {
        if (table2[i].occupied) {
            int index1 = hashFunction1(table2[i].element.first);
            if (table1[index1].occupied && table1[index1].element.first == table2[i].element.first) {
                if (keys.find(table2[i].element.first) == keys.end()) {
                    collisions.push_back(table2[i].element);
                    keys.insert(table2[i].element.first);
                }
            }
        }
    }

    return collisions;
}




