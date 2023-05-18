#include <iostream>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM std::make_pair(-111111, -111111)

class MapIterator;

class Map {
    friend class MapIterator;

private:
    static const int INITIAL_CAPACITY = 16;
    static const int MAX_ITERATIONS = 100;
    static const float LOAD_FACTOR_THRESHOLD;
    static const float SHRINK_FACTOR_THRESHOLD;

    struct Node {
        TElem elem;
        bool valid;

        Node() : valid(false) {}
    };

    Node* table1;
    Node* table2;
    int capacity;
    int size;

    int hashFunction1(TKey key) const {
        return key % capacity;
    }

    int hashFunction2(TKey key) const {
        return (key / capacity) % capacity;
    }

    void resizeAndRehash();
    void rehashNode(Node& node);
    void insertNode(Node& node);
    bool findNode(TKey key, int& tableIndex, int& position) const;

public:
    Map();
    ~Map();
    TValue add(TKey key, TValue value);
    TValue search(TKey key) const;
    TValue remove(TKey key);
    int getSize() const;
    bool isEmpty() const;
    MapIterator iterator() const;
};

const float Map::LOAD_FACTOR_THRESHOLD = 0.75;
const float Map::SHRINK_FACTOR_THRESHOLD = 0.25;

Map::Map() {
    capacity = INITIAL_CAPACITY;
    size = 0;
    table1 = new Node[capacity];
    table2 = new Node[capacity];
}

Map::~Map() {
    delete[] table1;
    delete[] table2;
}

void Map::resizeAndRehash() {
    int newCapacity = capacity * 2;
    Node* newTable1 = new Node[newCapacity];
    Node* newTable2 = new Node[newCapacity];

    for (int i = 0; i < capacity; i++) {
        if (table1[i].valid) {
            rehashNode(table1[i], newTable1, newTable2, newCapacity);
        }
        if (table2[i].valid) {
            rehashNode(table2[i], newTable1, newTable2, newCapacity);
        }
    }

    delete[] table1;
    delete[] table2;

    table1 = newTable1;
    table2 = newTable2;
    capacity = newCapacity;
}

void Map::rehashNode(Node& node, Node* newTable1, Node* newTable2, int newCapacity) {
    int tableIndex = hashFunction1(node.elem.first);
    int position = tableIndex;

    for (int i = 0; i < newCapacity; i++) {
        std::swap(node, newTable1[position]);

        if (!newTable2[position].valid) {
            std::swap(node, newTable2[position]);
            return;
        }

        tableIndex = hashFunction2(node.elem.first);
        position = tableIndex;
    }

    insertNode(node);
}

void Map::insertNode(Node& node) {
    int tableIndex = hashFunction1(node.elem.first);
    int position = tableIndex;

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        std::swap(node, table1[position]);

        if (!table2[position].valid) {
            std::swap(node, table2[position]);
            size++;
            return;
        }

        tableIndex = hashFunction2(node.elem.first);
        position = tableIndex;
    }

    resizeAndRehash();
    insertNode(node);
}

bool Map::findNode(TKey key, int& tableIndex, int& position) const {
    tableIndex = hashFunction1(key);
    position = tableIndex;

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (table1[position].valid && table1[position].elem.first == key) {
            return true;
        }
        if (table2[position].valid && table2[position].elem.first == key) {
            tableIndex = 1;
            return true;
        }

        tableIndex = hashFunction2(key);
        position = tableIndex;
    }

    return false;
}

TValue Map::add(TKey key, TValue value) {
    if (size >= capacity * LOAD_FACTOR_THRESHOLD) {
        resizeAndRehash();
    }

    int tableIndex, position;
    if (findNode(key, tableIndex, position)) {
        TValue oldValue;

        if (tableIndex == 0) {
            oldValue = table1[position].elem.second;
            table1[position].elem.second = value;
        }
        else {
            oldValue = table2[position].elem.second;
            table2[position].elem.second = value;
        }

        return oldValue;
    }

    Node newNode;
    newNode.elem = std::make_pair(key, value);
    newNode.valid = true;
    insertNode(newNode);

    return NULL_TVALUE;
}

TValue Map::search(TKey key) const {
    int tableIndex, position;
    if (findNode(key, tableIndex, position)) {
        if (tableIndex == 0) {
            return table1[position].elem.second;
        }
        else {
            return table2[position].elem.second;
        }
    }

    return NULL_TVALUE;
}

TValue Map::remove(TKey key) {
    int tableIndex, position;
    if (findNode(key, tableIndex, position)) {
        TValue oldValue;

        if (tableIndex == 0) {
            oldValue = table1[position].elem.second;
            table1[position].valid = false;
        }
        else {
            oldValue = table2[position].elem.second;
            table2[position].valid = false;
        }

        size--;

        if (size <= capacity * SHRINK_FACTOR_THRESHOLD && capacity > INITIAL_CAPACITY) {
            resizeAndRehash();
        }

        return oldValue;
    }

    return NULL_TVALUE;
}

int Map::getSize() const {
    return size;
}

bool Map::isEmpty() const {
    return size == 0;
}

class MapIterator {
    // TODO: Implement MapIterator class if necessary
};

int main() {
    Map map;

    // Add 1000 elements
    for (int i = 0; i < 1000; i++) {
        map.add(i, i * 10);
    }

    // Remove 500 elements
    for (int i = 0; i < 500; i++) {
        map.remove(i);
    }

    std::cout << "Size: " << map.getSize() << std::endl;

    return 0;
}
