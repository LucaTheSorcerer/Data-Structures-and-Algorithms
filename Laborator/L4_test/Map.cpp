#include "Map.h"

 const double Map::LOAD_FACTOR_THRESHOLD = 0.5;

Map::Map() {
    capacity = INITIAL_CAPACITY;
    size_ = 0;
    table1 = new Node[capacity];
    table2 = new Node[capacity];
}

Map::~Map() {
    delete[] table1;
    delete[] table2;
}

void Map::automaticResize() {
    if (size_ >= capacity * LOAD_FACTOR_THRESHOLD) {
        int newCapacity = capacity * 2;
        resizeAndRehash(newCapacity);
    }
}

void Map::resizeAndRehash(int newCapacity) {
    Node* newTable1 = new Node[newCapacity];
    Node* newTable2 = new Node[newCapacity];

    for (int i = 0; i < capacity; i++) {
        if (table1[i].occupied) {
            insertElement(newTable1, table1[i].element);
        }
        if (table2[i].occupied) {
            insertElement(newTable2, table2[i].element);
        }
    }

    delete[] table1;
    delete[] table2;

    table1 = newTable1;
    table2 = newTable2;
    capacity = newCapacity;
}

bool Map::insertElement(Node *table, TElem element) {
    int position = hashFunction1(element.first);
    for (int i = 0; i < MAX_REHASHES; i++) {
        if (!table[position].occupied) {
            table[position].occupied = true;
            table[position].element = element;
            size_++;
            return true;
        }
        std::swap(table[position].element, element);
        position = hashFunction2(element.first);
    }
    return false;
}

TValue Map::add(TKey key, TValue value) {
    automaticResize();

    TElem element(key, value);
    if (insertElement(table1, element)) {
        return NULL_TVALUE;
    }

    resizeAndRehash(capacity * 2);

    if (insertElement(table1, element)) {
        return NULL_TVALUE;
    }

    return value;
}

TValue Map::searchElement(Node *table, TKey key) const {
    int position1 = hashFunction1(key);
    int position2 = hashFunction2(key);

    if (table[position1].occupied && table[position1].element.first == key) {
        return table[position1].element.second;
    }

    if (table[position2].occupied && table[position2].element.first == key) {
        return table[position2].element.second;
    }

    return NULL_TVALUE;
}

TValue Map::search(TKey key) const {
    return searchElement(table1, key);
}

TValue Map::removeElement(Node *table, TKey key) {
    int position1 = hashFunction1(key);
    int position2 = hashFunction2(key);

    if (table[position1].occupied && table[position1].element.first == key) {
        TValue value = table[position1].element.second;
        table[position1].occupied = false;
        table[position1].element = NULL_TELEM;
        size_--;
        return value;
    }

    if (table[position2].occupied && table[position2].element.first == key) {
        TValue value = table[position2].element.second;
        table[position2].occupied = false;
        table[position2].element = NULL_TELEM;
        size_--;
        return value;
    }

    return NULL_TVALUE;
}

TValue Map::remove(TKey key) {
    TValue value = removeElement(table1, key);
    if (value != NULL_TVALUE) {
        return value;
    }
    value = removeElement(table2, key);
    return value;
}

int Map::size() const {
    return size_;
}

bool Map::isEmpty() const {
    return size_ == 0;
}