/*
	Title:      HashEntry.h
	Author:	    April Crockett & John Grzegorczyk (Later code added)
	Date:       October 6, 2020 -> April 14, 2023
	Purpose:    Hash Table Implementation
				Values					-	Costume objects
				Hash Function			-	modulus operator
				Collision resolution	-	quadratic probing			
*/

#ifndef HASHENTRY_H
#define HASHENTRY_H

#include <iostream>
#include "Costume.h"
using namespace std;

class HashEntry
{
	private:
		int key;
		Costume* value;
		
	public:
		HashEntry(int k, Costume* v)
		{
			this->key = k;
			this->value = v;
		}

		~HashEntry() {
			delete value;
		}
		
		int getKey()
		{
			return key;
		}
		Costume* getValue()
		{
			return value;
		}
		void setValue(Costume* v)
		{
			value = v;
		}
};

#endif