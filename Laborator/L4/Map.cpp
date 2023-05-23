#include <iostream>
#include "Map.h"
#include "MapIterator.h"

const double Map::LOAD_FACTOR_THRESHOLD = 0.5;

Map::Map() {
    capacity = 3;
    size_ = 0;
    table1 = new Node[capacity];
    table2 = new Node[capacity];

}

Map::~Map() {
    delete[] table1;
    delete[] table2;
}


//TValue Map::add(TKey c, TValue v) {
//    if (size_ == capacity)
////        automaticResize();
//        resize();
//
//    int position1 = hashFunction1(c);
//    int position2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    TKey currentKey = c;
//    TValue currentValue = v;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        std::cout << table1[position1].occupied << " Occupied element: " << table1[position1].element.first << " " << table1[position1].element.second << std::endl;
//        //If the position1 in the first table is not occupied, we add the element there
//        if (!table1[position1].occupied) {
//            table1[position1] = newNode;
//            table1[position1].occupied = true;
//            size_++;
////            resize();
////            std::cout << "Table 1: " << "key: " << table1[position1].element.first << " " <<  "value: " << table1[position1].element.second << std::endl;
//            return NULL_TVALUE;
//        } else if (table1[position1].element.first == c) {
//            TValue oldValue = table1[position1].element.second;
//            table1[position1].element.second = v;
//
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[position1], newNode);
//        position2 = hashFunction2(newNode.element.first);
////        Node evictedNode = table1[position1];
////        newNode = evictedNode;  // Assign evictedNode to newNode
////        std::swap(table1[position1], newNode);
////        position2 = hashFunction2(evictedNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[position2].occupied) {
//            table2[position2] = newNode;
//            size_++;
////            std::cout << "Table 2: " << "key: " << table1[position1].element.first << " " <<  "value: " << table1[position1].element.second << std::endl;
//
//            return NULL_TVALUE;
//
//        } else if (table2[position2].element.first == c) {
//            TValue oldValue = table2[position2].element.second;
//            table2[position2].element.second = v;
//            return oldValue;
//        }
//
////
////        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[position2], newNode);
//        position1 = hashFunction1(newNode.element.first);
//
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
////        automaticResize();
//        resize();
//        add(c, v);
//    }
//
//    return NULL_TVALUE;
//}
//TValue Map::add(TKey c, TValue v) {
//    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD)
//        resize();
//
//    int position1 = hashFunction1(c);
//    int position2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[position1].occupied) {
//            table1[position1] = newNode;
//            table1[position1].occupied = true;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table1[position1].element.first == c) {
//            TValue oldValue = table1[position1].element.second;
//            table1[position1].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[position1], newNode);
//        position2 = hashFunction2(newNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[position2].occupied) {
//            table2[position2] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table2[position2].element.first == c) {
//            TValue oldValue = table2[position2].element.second;
//            table2[position2].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[position2], newNode);
//        position1 = hashFunction1(newNode.element.first);
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
//        resize();
//        return add(c, v);
//    }
//
//    return NULL_TVALUE;
//}

//TValue Map::add(TKey c, TValue v) {
//    if (size_ == capacity)
//        resize();
//
//    int index1 = hashFunction1(c);
//    int index2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[index1].occupied) {
//            table1[index1] = newNode;
//            table1[index1].occupied = true;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table1[index1].element.first == c) {
//            TValue oldValue = table1[index1].element.second;
//            table1[index1].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        Node evictedNode = table1[index1];
//        table1[index1] = newNode;
//        index2 = hashFunction2(evictedNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[index2].occupied) {
//            table2[index2] = evictedNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table2[index2].element.first == evictedNode.element.first) {
//            TValue oldValue = table2[index2].element.second;
//            table2[index2].element.second = evictedNode.element.second;
//            return oldValue;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        evictedNode = table2[index2];
//        table2[index2] = newNode;
//        index1 = hashFunction1(evictedNode.element.first);
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
//        resize();
//        add(c, v);
//    }
//
//    return NULL_TVALUE;
//}

//TValue Map::add(TKey c, TValue v) {
//    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD)
//        resize();
//
//    int position1 = hashFunction1(c);
//    int position2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[position1].occupied) {
//            table1[position1] = newNode;
//            table1[position1].occupied = true;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table1[position1].element.first == c) {
//            TValue oldValue = table1[position1].element.second;
//            table1[position1].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[position1], newNode);
//        position2 = hashFunction2(newNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[position2].occupied) {
//            table2[position2] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table2[position2].element.first == c) {
//            TValue oldValue = table2[position2].element.second;
//            table2[position2].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[position2], newNode);
//        position1 = hashFunction1(newNode.element.first);
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
//        resize();
//        return add(c, v);
//    }
//
//    return NULL_TVALUE;
//}


//TValue Map::add(TKey c, TValue v) {
//    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD)
//        resize();
//
//    int position1 = hashFunction1(c);
//    int position2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    TKey currentKey = c;
//    TValue currentValue = v;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[position1].occupied) {
//            table1[position1] = newNode;
//            table1[position1].occupied = true;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table1[position1].element.first == c) {
//            TValue oldValue = table1[position1].element.second;
//            table1[position1].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[position1], newNode);
//        position2 = hashFunction2(newNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[position2].occupied) {
//            table2[position2] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table2[position2].element.first == c) {
//            TValue oldValue = table2[position2].element.second;
//            table2[position2].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[position2], newNode);
//        position1 = hashFunction1(newNode.element.first);
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
//        resize();
//        return add(currentKey, currentValue);
//    }
//
//    return NULL_TVALUE;
//}

//TValue Map::add(TKey c, TValue v) {
//    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD)
//        resize();
//
//    int position1 = hashFunction1(c);
//    int position2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    // Check if the key already exists in the map
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    TKey currentKey = c;
//    TValue currentValue = v;
//
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[position1].occupied) {
//            table1[position1] = newNode;
//            table1[position1].occupied = true;
//            size_++;
//            return NULL_TVALUE;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[position1], newNode);
//        position2 = hashFunction2(newNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[position2].occupied) {
//            table2[position2] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[position2], newNode);
//        position1 = hashFunction1(newNode.element.first);
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
//        resize();
//        return add(currentKey, currentValue);
//    }
//
//    return NULL_TVALUE;
//}
//TValue Map::add(TKey c, TValue v) {
//    if (size_ == capacity)
////        automaticResize();
//        resize();
//
//    int index1 = hashFunction1(c);
//    int index2 = hashFunction2(c);
//
//    Node newNode;
//    newNode.element = std::make_pair(c, v);
//    newNode.occupied = true;
//
//    if (search(c) != NULL_TVALUE) {
//        int hash1 = hashFunction1(c);
//        int hash2 = hashFunction2(c);
//        TValue oldValue;
//
//        if (table1[hash1].element.first == c) {
//            oldValue = table1[hash1].element.second;
//            table1[hash1].element.second = v;
//        } else {
//            oldValue = table2[hash2].element.second;
//            table2[hash2].element.second = v;
//        }
//        return oldValue;
//    }
//
//    int rehashCount = 0;
//    std::cout << table2[index2].element.first << " " << table2[index2].element.second << std::endl;
//    while (rehashCount < MAX_REHASHES) {
//        // Try to insert the element in the first table
//        if (!table1[index1].occupied) {
//            table1[index1] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table1[index1].element.first == c) {
//            TValue oldValue = table1[index1].element.second;
//            table1[index1].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the first table and try placing it in the second table
//        std::swap(table1[index1], newNode);
//        index2 = hashFunction2(newNode.element.first);
//
//        // Check if the evicted element can be placed in the second table
//        if (!table2[index2].occupied) {
//            table2[index2] = newNode;
//            size_++;
//            return NULL_TVALUE;
//        } else if (table2[index2].element.first == c) {
//            TValue oldValue = table2[index2].element.second;
//            table2[index2].element.second = v;
//            return oldValue;
//        }
//
//        // Evict the element in the second table and try placing it in the first table
//        std::swap(table2[index2], newNode);
//        index1 = hashFunction1(newNode.element.first);
//
//
//        rehashCount++;
//    }
//
//    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
//    if (rehashCount == MAX_REHASHES) {
////        automaticResize();
//        resize();
//        return add(c, v);
//    }
//
//    return NULL_TVALUE;
//}

TValue Map::add(TKey c, TValue v) {
    if (size_ == capacity)
//        automaticResize();
        resize();

    int index1 = hashFunction1(c);
    int index2 = hashFunction2(c);

    Node newNode;
    newNode.element = std::make_pair(c, v);
    newNode.occupied = true;

    if (search(c) != NULL_TVALUE) {
        int hash1 = hashFunction1(c);
        int hash2 = hashFunction2(c);
        TValue oldValue;

        if (table1[hash1].element.first == c) {
            oldValue = table1[hash1].element.second;
            table1[hash1].element.second = v;
        } else {
            oldValue = table2[hash2].element.second;
            table2[hash2].element.second = v;
        }
        return oldValue;
    }

    int rehashCount = 0;
    std::cout << table2[index2].element.first << " " << table2[index2].element.second << std::endl;
    while (rehashCount < MAX_REHASHES) {
        // Try to insert the element in the first table
        if (!table1[index1].occupied) {
            table1[index1] = newNode;
            size_++;
            return NULL_TVALUE;
        } else if (table1[index1].element.first == c) {
            TValue oldValue = table1[index1].element.second;
            table1[index1].element.second = v;
            return oldValue;
        }

        // Evict the element in the first table and try placing it in the second table
        std::swap(table1[index1], newNode);
        index2 = hashFunction2(newNode.element.first);

        // Check if the evicted element can be placed in the second table
        if (!table2[index2].occupied) {
            table2[index2] = newNode;
            size_++;
            return NULL_TVALUE;
        } else if (table2[index2].element.first == c) {
            TValue oldValue = table2[index2].element.second;
            table2[index2].element.second = v;
            return oldValue;
        }

        // Evict the element in the second table and try placing it in the first table
        std::swap(table2[index2], newNode);
        index1 = hashFunction1(newNode.element.first);


        rehashCount++;
    }

    // Rehashing is not possible within the maximum rehashes limit, resize and rehash the table instead
    if (rehashCount == MAX_REHASHES) {
//        automaticResize();
        resize();
        return add(c, v);
    }

    return NULL_TVALUE;
}

void Map::resize()
{
    int oldCapacity = capacity;
    capacity *= 2;

    Node* oldTable1 = table1;
    Node* oldTable2 = table2;

    table1 = new Node[capacity];
    table2 = new Node[capacity];

    for (int i = 0; i < capacity; i++)
    {
        table1[i].element = NULL_TELEM;
        table2[i].element = NULL_TELEM;
    }

    this->size_ = 0;

    for (int i = 0; i < oldCapacity; i++)
    {
        if (oldTable1[i].element != NULL_TELEM)
        {
            TKey key = oldTable1[i].element.first;
            TValue value = oldTable1[i].element.second;
            add(key, value);
        }
        if (oldTable2[i].element != NULL_TELEM)
        {
            TKey key = oldTable2[i].element.first;
            TValue value = oldTable2[i].element.second;
            add(key, value);
        }
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

TValue Map::remove(TKey c){
	//TODO - Implementation

    int hash1 = hashFunction1(c);
    int hash2 = hashFunction2(c);

    if(table1[hash1].occupied && table1[hash1].element.first == c) {
        TValue oldValue = table1[hash1].element.second;
        table1[hash1].occupied = false;
        size_--;
        automaticResize();
    //        resize();
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

//TValue Map::remove(TKey c) {
//    int index1 = hashFunction1(c);
//    int index2 = hashFunction2(c);
//
//    if (table1[index1].element.first == c) {
//        TValue oldValue = table1[index1].element.second;
//        table1[index1].occupied = false;
//        size_--;
//        return oldValue;
//    } else if (table2[index2].element.first == c) {
//        TValue oldValue = table2[index2].element.second;
//        table2[index2].occupied = false;
//        size_--;
//        return oldValue;
//    }
//
//    return NULL_TVALUE;
//}


int Map::size() const {
    return size_;
}

bool Map::isEmpty() const{
	return size_ == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}




void Map::automaticResize() {
    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD) {
        resizeAndRehash(capacity * 2);
    } else if (size_ < capacity / 4 && capacity >= 10) {
        resizeAndRehash(capacity / 2);
    }
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



int Map::Jenkins1(TKey key) const {
    key += (key << 12);
    key ^= (key >> 22);
    key += (key << 4);
    key ^= (key >> 9);
    key += (key << 10);
    key ^= (key >> 2);
    key += (key << 7);
    key ^= (key >> 12);
    return key % capacity;
}

int Map::Jenkins2(TKey key) const {
    key += (key << 17);
    key ^= (key >> 5);
    key += (key << 4);
    key ^= (key >> 13);
    key += (key << 11);
    key ^= (key >> 3);
    key += (key << 16);
    key ^= (key >> 7);
    return key % capacity;
}


//size_t Map::hashFunction1(TKey key) const {
//    key = ((key >> 16) ^ key) * 0x45d9f3b;
//    key = ((key >> 16) ^ key) * 0x45d9f3b;
//    key = (key >> 16) ^ key;
//    return key % capacity;
//}
//
//size_t Map::hashFunction2(TKey key) const {
//    key = ((key >> 16) ^ key) * 0x2d83bfb;
//    key = ((key >> 16) ^ key) * 0x2d83bfb;
//    key = (key >> 16) ^ key;
//    return key % capacity;
//}

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
    return (abs(key) * 13 ) % capacity;
}