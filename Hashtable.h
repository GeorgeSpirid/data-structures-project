#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

class HashTable {
public:
    HashTable(int Size);//constructor
    ~HashTable();//destructor
    void insert(int key);//insert key and value pair in the hashtable
    bool search(int key);//searching the key and returning the value
    void buildFromFile(const std::string& filename);//building hashtable from file
    int getsize();


private:
    struct HashNode {
        int key;
        HashNode* next;
    };//struct for a node of the hashtable
    int tableSize;//size of the hashtable
    int Size;//number of keys in the hashtable
    int hashFunction(int key);//hash function to map the keys
    HashNode** table;

};

#endif
