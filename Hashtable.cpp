#include "Hashtable.h"
#include <fstream>
#include <iostream>
//constructor that initializes the hash table from the given size and sets all table entries to nullptr
HashTable::HashTable(int tableSize) : tableSize(tableSize),Size(0) {
    table = new HashNode*[tableSize];
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}
//destructor that deletes all nodes of the table and the array
HashTable::~HashTable() {
    for (int i = 0; i < tableSize; ++i) {
        HashNode* entry = table[i];
        while (entry != nullptr) {
            HashNode* prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = nullptr;
    }
    delete[] table;
}
//hash function to map the keys
int HashTable::hashFunction(int key) {
    return key % tableSize;
}
//inserts key and value to the hashtable
void HashTable::insert(int key) {
    int index = hashFunction(key);
    HashNode* newNode = new HashNode{key, nullptr};

    if (table[index] == nullptr) {
        table[index] = newNode;
    } else {
        HashNode* entry = table[index];
        while (entry->next != nullptr) {
            entry = entry->next;
        }
        entry->next = newNode;
    }
    Size++;
}
//search for a key and returning the value
bool HashTable::search(int key) {
    int index = hashFunction(key);
    HashNode* entry = table[index];
    while (entry != nullptr) {
        if (entry->key == key) {
            return true;//if the key is found the function returns true
        }
        entry = entry->next;
    }
    return false;//if the key isn't found the function returns false
}
//builds the hashtable form the given file
void HashTable::buildFromFile(const std::string& filename) {
    std::ifstream file(filename);
    int key;

    while (file >> key ) {
        insert(key);//insert key and value
    }
    file.close();//close file
}
int HashTable::getsize(){
    return (Size);
}
