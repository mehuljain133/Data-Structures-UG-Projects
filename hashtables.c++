/* Hash Tables: Introduction to hashing, hash tables and hashing functions -insertion, resolving
collision by open addressing, deletion, searching and their analysis, properties of a good hash
function. */

#include <iostream>
using namespace std;

/////////////////////////////////////////////////
// Hash Table using Open Addressing (Linear Probing)
/////////////////////////////////////////////////

enum Status { EMPTY, OCCUPIED, DELETED };

struct HashNode {
    int key;
    Status status;

    HashNode() : key(-1), status(EMPTY) {}
};

class HashTable {
private:
    HashNode* table;
    int capacity;
    int size;

    int hashFunction(int key) {
        // Simple but decent hash: modulo prime number
        return key % capacity;
    }

public:
    HashTable(int cap) {
        capacity = cap;
        size = 0;
        table = new HashNode[capacity];
    }

    bool insert(int key) {
        if (size == capacity) {
            cout << "Hash Table Full\n";
            return false;
        }
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;
        while (table[index].status == OCCUPIED) {
            index = (originalIndex + (++i)) % capacity;
        }
        table[index].key = key;
        table[index].status = OCCUPIED;
        size++;
        return true;
    }

    bool search(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;
        while (table[index].status != EMPTY) {
            if (table[index].status == OCCUPIED && table[index].key == key)
                return true;
            index = (originalIndex + (++i)) % capacity;
            if (i == capacity) break; // full cycle done
        }
        return false;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        int originalIndex = index;
        int i = 0;
        while (table[index].status != EMPTY) {
            if (table[index].status == OCCUPIED && table[index].key == key) {
                table[index].status = DELETED;
                size--;
                return true;
            }
            index = (originalIndex + (++i)) % capacity;
            if (i == capacity) break;
        }
        return false;
    }

    void display() {
        cout << "Hash Table contents:\n";
        for (int i = 0; i < capacity; i++) {
            cout << i << ": ";
            if (table[i].status == OCCUPIED)
                cout << table[i].key;
            else if (table[i].status == DELETED)
                cout << "DELETED";
            else
                cout << "EMPTY";
            cout << endl;
        }
    }
};

/////////////////////////////////////////////////
// MAIN FUNCTION
/////////////////////////////////////////////////
int main() {
    HashTable ht(7); // Size chosen as a prime number for better distribution

    ht.insert(10);
    ht.insert(20);
    ht.insert(5);
    ht.insert(15);
    ht.insert(7);

    ht.display();

    cout << "\nSearching 5: " << (ht.search(5) ? "Found" : "Not Found") << endl;
    cout << "Searching 25: " << (ht.search(25) ? "Found" : "Not Found") << endl;

    cout << "\nDeleting 5...\n";
    ht.remove(5);
    ht.display();

    cout << "\nSearching 5 after deletion: " << (ht.search(5) ? "Found" : "Not Found") << endl;

    return 0;
}
