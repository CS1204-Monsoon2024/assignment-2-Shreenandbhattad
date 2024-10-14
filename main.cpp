#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> deleted; // To mark deleted elements
    int size;
    int count; // Number of elements in the hash table
    const double loadFactorThreshold = 0.8;

    // Helper function to find next prime greater than n
    int nextPrime(int n) {
        while (true) {
            n++;
            if (isPrime(n)) return n;
        }
    }

    // Check if a number is prime
    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i <= std::sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Hash function
    int hash(int key) {
        return key % size;
    }

    // Resize the table when load factor exceeds threshold
    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2); // Resize to next prime greater than twice the old size
        std::vector<int> oldTable = table;
        std::vector<bool> oldDeleted = deleted;

        table = std::vector<int>(size, -1);
        deleted = std::vector<bool>(size, false);
        count = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1 && !oldDeleted[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    // Constructor
    HashTable(int initSize = 5) : size(initSize), count(0) {
        table.resize(size, -1);
        deleted.resize(size, false);
    }

    // Insert key into hash table
    void insert(int key) {
        if (count + 1 > loadFactorThreshold * size) {
            resize();
        }

        int idx = hash(key);
        int i = 0;
        while (table[(idx + i * i) % size] != -1 && table[(idx + i * i) % size] != key) {
            if (i > size / 2) {
                std::cout << "Max probing limit reached!" << std::endl;
                return;
            }
            i++;
        }

        int finalIdx = (idx + i * i) % size;

        if (table[finalIdx] == key) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        table[finalIdx] = key;
        deleted[finalIdx] = false;
        count++;
    }

    // Remove key from hash table
    void remove(int key) {
        int idx = hash(key);
        int i = 0;

        while (table[(idx + i * i) % size] != key) {
            if (table[(idx + i * i) % size] == -1 || i > size / 2) {
                std::cout << "Element not found" << std::endl;
                return;
            }
            i++;
        }

        table[(idx + i * i) % size] = -1;
        deleted[(idx + i * i) % size] = true;
        count--;
    }

    // Search for a key in the hash table
    int search(int key) {
        int idx = hash(key);
        int i = 0;

        while (table[(idx + i * i) % size] != key) {
            if (table[(idx + i * i) % size] == -1 || i > size / 2) {
                return -1; // Key not found
            }
            i++;
        }

        return (idx + i * i) % size;
    }

    // Print the contents of the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1 && !deleted[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
};

// Sample main.cpp for testing
int main() {
    HashTable ht(5);
    
    ht.insert(1);
    ht.printTable();  // Output: - 1 - - -
    
    ht.insert(4);
    ht.printTable();  // Output: - 1 - 4 -
    
    ht.remove(3);  // Output: Element not found
    
    ht.insert(4);  // Output: Duplicate key insertion is not allowed
    
    ht.insert(17);
    ht.printTable();  // Output: - 1 - 4 17 -
    
    return 0;
}
