#include "Map.h"
#include "MapIterator.h"


MapIterator::MapIterator(const Map& m) : map(m) {
    // Initialize the iterator to the first valid position
    first();
}

void MapIterator::first() {
    // Start from the first position in the first table
    currentTable = 1;
    currentPosition = 0;

    // Find the first occupied position
    while (currentPosition < map.capacity && !map.table1[currentPosition].occupied) {
        currentPosition++;
    }

    // If no occupied position found in the first table, move to the second table
    if (currentPosition == map.capacity) {
        currentTable = 2;
        currentPosition = 0;

        // Find the first occupied position in the second table
        while (currentPosition < map.capacity && !map.table2[currentPosition].occupied) {
            currentPosition++;
        }
    }
}

void MapIterator::next() {
    // Move to the next position in the current table
    currentPosition++;

    // Check if there are more occupied positions in the current table
    if (currentTable == 1) {
        while (currentPosition < map.capacity && !map.table1[currentPosition].occupied) {
            currentPosition++;
        }

        // If no more occupied positions in the first table, move to the second table
        if (currentPosition == map.capacity) {
            currentTable = 2;
            currentPosition = 0;

            // Find the first occupied position in the second table
            while (currentPosition < map.capacity && !map.table2[currentPosition].occupied) {
                currentPosition++;
            }
        }
    } else if (currentTable == 2) {
        // Find the next occupied position in the second table
        while (currentPosition < map.capacity && !map.table2[currentPosition].occupied) {
            currentPosition++;
        }
    }
}

TElem MapIterator::getCurrent() {
    // Check if the iterator is valid
    if (valid()) {
        // Get the key-value pair at the current position
        if (currentTable == 1) {
            return map.table1[currentPosition].element;
        } else if (currentTable == 2) {
            return map.table2[currentPosition].element;
        }
    }

    // If iterator is not valid, return a default-constructed TElem
    return {};
}

bool MapIterator::valid() const {
    // Check if the iterator is at a valid position
    if (currentTable == 1) {
        return currentPosition < map.capacity && map.table1[currentPosition].occupied;
    } else if (currentTable == 2) {
        return currentPosition < map.capacity && map.table2[currentPosition].occupied;
    }

    return false;
}
