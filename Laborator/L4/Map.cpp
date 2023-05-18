#include <iostream>
#include "Map.h"
#include "MapIterator.h"

const double Map::LOAD_FACTOR_THRESHOLD = 0.7;

Map::Map() {
	//TODO - Implementation
    capacity = INITIAL_CAPACITY;
    size_ = 0;
    table1 = new Node[capacity];
    table2 = new Node[capacity];
}

Map::~Map() {
	//TODO - Implementation
    delete[] table1;
    delete[] table2;
}



TValue Map::add(TKey key, TValue value) {
    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD)
        automaticResize();

    size_t index1 = hashFunction1(key);
    size_t index2 = hashFunction2(key);

    Node newNode;
    newNode.element = std::make_pair(key, value);
    newNode.occupied = true;

    for (int i = 0; i < MAX_REHASHES; i++) {
        if (!table1[index1].occupied) {
            table1[index1] = newNode;
            size_++;
            return NULL_TVALUE;
        } else if (table1[index1].element.first == key) {
            TValue oldValue = table1[index1].element.second;
            table1[index1].element.second = value;
            return oldValue;
        }

        std::swap(table1[index1], newNode);

        if (!table2[index2].occupied) {
            table2[index2] = newNode;
            size_++;
            return NULL_TVALUE;
        } else if (table2[index2].element.first == key) {
            TValue oldValue = table2[index2].element.second;
            table2[index2].element.first = value;
            return oldValue;
        }

        std::swap(table2[index2], newNode);

        index1 = hashFunction1(newNode.element.first);
        index2 = hashFunction2(newNode.element.first);
    }

    automaticResize();
    return add(key, value);
}

TValue Map::search(TKey c) const{
	//TODO - Implementation
    size_t hash1 = hashFunction1(c);
    size_t hash2 = hashFunction2(c);

    if(table1[hash1].occupied && table1[hash1].element.first == c) {
        return table1[hash1].element.second;
    } else if(table2[hash2].occupied && table2[hash2].element.first == c) {
        return table2[hash2].element.second;
    }

    return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//TODO - Implementation

    size_t hash1 = hashFunction1(c);
    size_t hash2 = hashFunction2(c);

    if(table1[hash1].occupied && table1[hash1].element.first == c) {
        TValue oldValue = table1[hash1].element.second;
        table1[hash1].occupied = false;
        size_--;
        automaticResize();
        return oldValue;
    } else if(table2[hash2].occupied && table2[hash2].element.first == c) {
        TValue oldValue = table2[hash2].element.second;
        table2[hash2].occupied = false;
        size_--;
        automaticResize();
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

size_t Map::hashFunction1(TKey key) const {
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key % capacity;
}

size_t Map::hashFunction2(TKey key) const {
    key = ((key >> 16) ^ key) * 0x2d83bfb;
    key = ((key >> 16) ^ key) * 0x2d83bfb;
    key = (key >> 16) ^ key;
    return key % capacity;
}

void Map::automaticResize() {
    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD) {
        resize(capacity * 2);
    } else if (size_ <= capacity / 4) {
        resize(capacity / 2);
    }
}



void Map::resize(int newCapacity) {
    Node* newTable1 = new Node[newCapacity];
    Node* newTable2 = new Node[newCapacity];

    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            TKey key = table1[i].element.first;
            TValue value = table1[i].element.second;
            size_t pos1 = hashFunction1(key);
            size_t pos2 = hashFunction2(key);

            if (!newTable1[pos1].occupied) {
                newTable1[pos1].element = std::make_pair(key, value);
                newTable1[pos1].occupied = true;
            } else if (!newTable2[pos2].occupied) {
                newTable2[pos2].element = std::make_pair(key, value);
                newTable2[pos2].occupied = true;
            } else {
                // Unable to rehash element, revert the resize and throw an exception
                delete[] newTable1;
                delete[] newTable2;
                throw std::runtime_error("Unable to rehash element during resize.");
            }
        }
    }

    delete[] table1;
    delete[] table2;
    table1 = newTable1;
    table2 = newTable2;
    capacity = newCapacity;
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



