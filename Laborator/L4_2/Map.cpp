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




void Map::automaticResize() {
    if (size_ < capacity / 4 && capacity >= 10) {
        resize(capacity / 2);
        std::cout << "Resizing downwards\n";

    } else {
        resize(capacity * 2);
    }
}

void Map::resize(int newCapacity)
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

TValue Map::search(TKey c) const{
    int hash1 = hashFunction1(c);
    int hash2 = hashFunction2(c);

    if(table1[hash1].occupied && table1[hash1].element.first == c)
        return table1[hash1].element.second;
    if(table2[hash2].occupied && table2[hash2].element.first == c)
        return table2[hash2].element.second;

    return NULL_TVALUE;
}


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



int Map::size() const {
    return size_;
}

bool Map::isEmpty() const{
    return size_ == 0;
}

MapIterator Map::iterator() const {
    return MapIterator(*this);
}



void Map::resizeAndRehash(int newCapacity) {
    Node* newTable1 = new Node[newCapacity];
    Node* newTable2 = new Node[newCapacity];

    int oldCapacity = capacity;
    capacity = newCapacity;
    size_ = 0;

    for (int i = 0; i < oldCapacity; i++) {
        if (table1[i].occupied) {
            TKey key = table1[i].element.first;
            TValue value = table1[i].element.second;

            int index1 = hashFunction1(key);
            int index2 = hashFunction2(key);

            int rehashCount = 0;
            while (rehashCount < MAX_REHASHES) {
                // Try to insert the element into newTable1
                if (!newTable1[index1].occupied) {
                    newTable1[index1].element = std::make_pair(key, value);
                    newTable1[index1].occupied = true;
                    size_++;
                    break;
                } else {
                    std::swap(key, newTable1[index1].element.first);
                    std::swap(value, newTable1[index1].element.second);
                    std::swap(table1[i], newTable1[index1]);
                    index1 = hashFunction1(key);
                }

                // Try to insert the element into newTable2
                if (!newTable2[index2].occupied) {
                    newTable2[index2].element = std::make_pair(key, value);
                    newTable2[index2].occupied = true;
                    size_++;
                    break;
                } else {
                    std::swap(key, newTable2[index2].element.first);
                    std::swap(value, newTable2[index2].element.second);
                    std::swap(table1[i], newTable2[index2]);
                    index2 = hashFunction2(key);
                }

                rehashCount++;
            }

            if (rehashCount == MAX_REHASHES) {
                // Rehashing is not possible within the maximum rehashes limit, revert the resizeAndRehash and throw an exception
                delete[] newTable1;
                delete[] newTable2;
                capacity = oldCapacity;
                throw std::runtime_error("Unable to rehash element during resizeAndRehash.");
            }
        }
    }

    delete[] table1;
    delete[] table2;
    table1 = newTable1;
    table2 = newTable2;
}




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

int Map::hashFunction1( TKey& key) const {
    return abs(key) % capacity;
}


int Map::hashFunction2( TKey& key) const {
    return (abs(key) * 17 ) % capacity;
}
