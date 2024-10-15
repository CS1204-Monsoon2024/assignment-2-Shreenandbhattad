#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    int currentSize;
    int numElements;
    double loadFactorThreshold = 0.8;

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Function to find the next prime greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) n++;
        return n;
    }

    // Hash function
    int hash(int key) {
        return key % currentSize;
    }

    // Rehash the table when resizing
    void rehash() {
        int oldSize = currentSize;
        currentSize = nextPrime(currentSize * 2);
        std::vector<int> newTable(currentSize, -1);

        for (int i = 0; i < oldSize; ++i) {
            if (table[i] != -1) {
                int key = table[i];
                int idx = hash(key);
                int step = 1;
                while (newTable[idx] != -1) {
                    idx = (idx + step * step) % currentSize;
                    step++;
                }
                newTable[idx] = key;
            }
        }
        table = newTable;
    }

public:
    // Constructor
    HashTable(int size) {
        currentSize = nextPrime(size);
        table.resize(currentSize, -1);
        numElements = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            std::cout << "Duplicate key insertion is not allowed\n";
            return;
        }

        if ((double)numElements / currentSize > loadFactorThreshold) {
            rehash();
        }

        int idx = hash(key);
        int step = 1;
        while (table[idx] != -1) {
            idx = (idx + step * step) % currentSize;
            if (step > currentSize / 2) {
                std::cout << "Max probing limit reached!\n";
                return;
            }
            step++;
        }

        table[idx] = key;
        numElements++;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int idx = search(key);
        if (idx == -1) {
            std::cout << "Element not found\n";
            return;
        }
        table[idx] = -1;
        numElements--;
    }

    // Search for a key and return its index or -1 if not found
    int search(int key) {
        int idx = hash(key);
        int step = 1;
        while (table[idx] != -1) {
            if (table[idx] == key) {
                return idx;
            }
            idx = (idx + step * step) % currentSize;
            step++;
            if (step > currentSize / 2) {
                return -1;
            }
        }
        return -1;
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < currentSize; ++i) {
            if (table[i] == -1) {
                std::cout << "- ";
            } else {
                std::cout << table[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

// Example main function
int main() {
    HashTable ht(5);

    ht.insert(1);
    ht.insert(4);
    ht.insert(17);
    ht.printTable();  // Example output: "- 1 - 4 - 17 -"

    ht.remove(4);
    ht.printTable();  // Example output: "- 1 - - 17 -"

    std::cout << ht.search(17) << std::endl;  // Example output: 6
    std::cout << ht.search(4) << std::endl;   // Example output: -1

    ht.insert(4);
    ht.insert(17);  // Should print "Duplicate key insertion is not allowed"
    
    return 0;
}
