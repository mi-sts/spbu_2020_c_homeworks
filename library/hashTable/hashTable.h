#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <stdbool.h>

typedef struct HashTable HashTable;

typedef struct HashElement HashElement;

HashElement* createHashElement(char* key, int value, int probesNumber);

HashTable* createHashTable(int polynomFactor);

int getHash(HashTable* table, char* key);

float getLoadFactor(HashTable* table);

void addElement(HashTable* table, char* key, int value);

bool deleteElement(HashTable* table, char* key);

int getElementValue(HashElement* element);

char* getElementKey(HashElement* element);

int getElementProbesSequenceLength(HashElement* element);

bool getElementValueByKey(HashTable* table, char* key, int* result);

int getBucketCount(HashTable* table);

void destroyHashElement(HashElement* hashElement);

void destroyHashTable(HashTable* table);

HashElement** getHashTableElements(HashTable* hashTable, int* elementNumber);

void printHashTableElements(HashTable* hashTable);

#endif