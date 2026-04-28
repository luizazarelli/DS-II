#include "libs.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef void* HashTable;

HashTable createHT(int n);

void insertHT(HashTable t, char* chave, void* info);

int existsHT(HashTable t, char* chave);

void* getHT(HashTable t, char* chave);

void* removeHT(HashTable t, char* chave);

void killHT(HashTable t);

int sizeHT(HashTable t);

#endif
