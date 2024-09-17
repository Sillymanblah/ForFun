#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Costume.h"
#include "HashEntry.h"

class HashTable {
public:
    HashTable();
    HashTable( size_t __size );

private:
    HashEntry** _table;
    size_t _size;
};

#endif