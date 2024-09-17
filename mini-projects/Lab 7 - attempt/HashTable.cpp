#include "HashTable.h"

HashTable::HashTable() : _table(), _size() {}

HashTable::HashTable( size_t __size ) : _table( new HashEntry*[__size] ), _size( __size ) {}

size_t HashTable::hash( int __key )
{
    return __key % _size;
}

void HashTable::putValue(HashEntry *&__current, int __key, Costume *__value)
{ if ( !__current ) __current = new HashEntry( __key, __value ); }

void HashTable::putValue( int __key, Costume* __value )
{ putValue( _table[ hash( __key ) ], __key, __value ); }
