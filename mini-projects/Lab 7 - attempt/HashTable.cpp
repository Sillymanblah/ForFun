#include "HashTable.h"

HashTable::HashTable() : _table(), _size() {}

HashTable::HashTable( size_t __size ) : _table( new HashEntry*[__size] ), _size( __size ) {}