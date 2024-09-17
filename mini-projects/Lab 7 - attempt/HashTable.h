#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Costume.h"
#include "HashEntry.h"

class HashTable {
public:
    HashTable();
    HashTable( size_t __size );

private:
    size_t hash( int __key );
    void putValue( HashEntry*& current, int __key, Costume* __value );

public:
    void putValue( int __key, Costume* __value );

private:
    HashEntry** _table;
    size_t _size;
};

#endif