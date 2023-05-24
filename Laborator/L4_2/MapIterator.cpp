#include "Map.h"
#include "MapIterator.h"


/**
 * @brief This is the constructor for the MapIterator class, which initializes the iterator with a reference to the map.
 * objects it iterates over. It also calls the function first() to initialize the iterator to the first valid position.
 * @param m The map to be iterated over
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(n)
 * @TimeComplexity-WorstCase: θ(n)
 * @note the time complexity is dominated by the time complexity of the first() function
 */
MapIterator::MapIterator(const Map& m) : map(m) {
    // Initialize the iterator to the first valid position
    first();
}

/**
 * @brief This is the function that initializes the iterator to the first valid position.
 * @details It iterates through the hash tables to find the first occupied position.
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(n) if the occupied position is randomly distributed
 * @TimeComplexity-WorstCase: θ(n) if all positions in both tables need to be checked
 * @note n is the number of elements in the hash map
 */
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


/**
 * @brief This is the function that moves the iterator to the next position.
 * @details It increments the position and searches for the next occupied position in the current table or switches to
 * the next table if necessary.
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(n) if the occupied position is randomly distributed
 * @TimeComplexity-WorstCase: θ(n) if all positions in both tables need to be checked
 */
void MapIterator::next() {
    // Check if the iterator is already at an invalid position
    if (!valid()) {
        throw std::exception();  // Throw an exception to indicate invalid operation
    }

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

/**
 * @brief This is the function that returns the element at the current position from the iterator.
 * @details It retrieves the element from either the table1 or table2 based on the current table and the position.
 * @return The element at the current position
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
TElem MapIterator::getCurrent() {
    // Check if the iterator is valid
    if (!valid()) {
        throw std::exception();  // Throw an exception to indicate invalid operation
    }

    // Get the key-value pair at the current position
    if (currentTable == 1) {
        return map.table1[currentPosition].element;
    } else if (currentTable == 2) {
        return map.table2[currentPosition].element;
    }

    // This point should not be reached
    return {};
}

/**
 * @brief This is the function that checks if the iterator is at a valid position.
 * @details It verifies that the current position is within the capacity of the hash tables and that the corresponding
 * position in the current table is occupied.
 * @return True if the iterator is at a valid position, false otherwise
 * @TimeComplexity-BestCase: θ(1)
 * @TimeComplexity-AverageCase: θ(1)
 * @TimeComplexity-WorstCase: θ(1)
 */
bool MapIterator::valid() const {
    // Check if the iterator is at a valid position
    if (currentTable == 1) {
        return currentPosition < map.capacity && map.table1[currentPosition].occupied;
    } else if (currentTable == 2) {
        return currentPosition < map.capacity && map.table2[currentPosition].occupied;
    }

    return false;
}

