#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Costume.h"
#include "HashEntry.h"

class HashTable {
public:
    HashTable();

private:
    HashEntry* table;
};

#endif