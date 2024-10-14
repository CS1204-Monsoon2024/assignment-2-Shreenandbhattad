#include <iostream>
#include <vector>
#include <cmath>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> deleted;
    int size;
    int count;
    const double loadFactorThreshold = 0.8;

    int nextPrime(int n) {
        while (true) {
            n++;
            if (isPrime(n)) return n;
        }
    }

    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i <= std::sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int hash(int key) {
        return key % size;
    }

    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2);
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
    HashTable(int initSize = 5) : size(initSize), count(0) {
        table.resize(size, -1);
        deleted.resize(size, false);
    }

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

    int search(int key) {
        int idx = hash(key);
        int i = 0;

        while (table[(idx + i * i) % size] != key) {
            if (table[(idx + i * i) % size] == -1 || i > size / 2) {
                return -1;
            }
            i++;
        }

        return (idx + i * i) % size;
    }

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

int main() {
    int initialSize = 7;
    HashTable ht(initialSize);

    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable();
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);
    ht.printTable();

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
