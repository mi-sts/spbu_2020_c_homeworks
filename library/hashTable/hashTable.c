#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CellType { empty,
        used,
        deleted };

typedef struct HashElement {
    char* key;
    int value;
    int probeCount;
} HashElement;

typedef struct HashTable {
    HashElement** hashTable;
    int bucketCount;
    int elementCount;
    int polynomFactor;
    enum CellType* types;
} HashTable;

const float maxLoadFactor = 0.7;

float getLoadFactor(HashTable* hashTable)
{
    return (float)hashTable->elementCount / (float)hashTable->bucketCount;
}

HashElement* createHashElement(char* key, int value, int probesNumber)
{
    HashElement* newElement = (HashElement*)malloc(sizeof(HashElement));
    int keySize = strlen(key);

    newElement->key = (char*)calloc(keySize + 1, sizeof(char));
    strcpy(newElement->key, key);
    newElement->value = value;
    newElement->probeCount = probesNumber;

    return newElement;
}

HashTable* createHashTableWithSize(int polynomFactor, int size)
{
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    newTable->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(newTable->types, (int)empty, size * sizeof(enum CellType));
    newTable->bucketCount = size;
    memset(newTable->hashTable, 0, size * sizeof(HashElement*));
    newTable->elementCount = 0;
    newTable->polynomFactor = polynomFactor;
    return newTable;
}

HashTable* createHashTable(int polynomFactor)
{
    return createHashTableWithSize(polynomFactor, 1);
}

bool isHashTableEmpty(HashTable* table)
{
    return table->bucketCount == 0;
}

int getHash(HashTable* table, char* key)
{
    /*
    key[0] * p^n + key[1] * p^(n - 1) + ... + key[n - 1] =
    ((key[0] * p + key[1]) * p + key[2]) * p + ... + key[n - 1]
    */
    int polynomFactor = table->polynomFactor;
    int module = table->bucketCount;

    int size = strlen(key);
    int currentHash = 0;
    for (int i = 0; i < size; ++i)
        currentHash = ((currentHash * polynomFactor) + (key[i] - 'a')) % module;

    return currentHash;
}

void destroyHashElement(HashElement* hashElement)
{
    if (hashElement == NULL)
        return;

    if (hashElement->key != NULL)
        free(hashElement->key);
    free(hashElement);
}

void destroyHashTable(HashTable* table)
{
    for (int i = 0; i < table->bucketCount; ++i)
        destroyHashElement(table->hashTable[i]);

    free(table->hashTable);
    free(table->types);
    free(table);
}

void expandTable(HashTable* table)
{
    HashElement** oldElements = table->hashTable;
    enum CellType* oldTypes = table->types;

    int oldBucketSize = table->bucketCount;
    int size = table->bucketCount * 2;

    table->hashTable = (HashElement**)malloc(sizeof(HashElement*) * size);
    table->types = (enum CellType*)malloc(sizeof(enum CellType) * size);
    memset(table->hashTable, 0, size * sizeof(HashElement*));
    memset(table->types, (int)empty, size * sizeof(enum CellType));
    table->bucketCount = size;
    table->elementCount = 0;

    for (int i = 0; i < oldBucketSize; ++i) {
        HashElement* currentElement = oldElements[i];
        if (oldTypes[i] != used)
            continue;

        addElement(table, currentElement->key, currentElement->value);
        destroyHashElement(currentElement);
    }

    free(oldElements);
    free(oldTypes);
}

int getProbeSequenceIndex(HashTable* table, int startIndex, int probeNumber)
{
    int index = (startIndex + (1 + probeNumber) * probeNumber / 2) % table->bucketCount;

    return index;
}

void addElement(HashTable* table, char* key, int value)
{
    int startIndex = getHash(table, key);
    int currentIndex = startIndex;
    int currentProbeIndex = 0;

    while (table->types[currentIndex] == used) {
        currentIndex = getProbeSequenceIndex(table, startIndex, currentProbeIndex);
        currentProbeIndex++;
    }
    HashElement* newElement = createHashElement(key, value, currentProbeIndex + 1);

    table->types[currentIndex] = used;
    table->hashTable[currentIndex] = newElement;
    table->elementCount++;

    if (getLoadFactor(table) > maxLoadFactor)
        expandTable(table);
}

bool deleteElement(HashTable* table, char* key)
{
    if (isHashTableEmpty(table))
        return false;

    int startIndex = getHash(table, key);
    int currentIndex = startIndex;
    int currentProbeIndexNumber = 1;

    while (table->types[currentIndex] == used) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            table->types[currentIndex] = deleted;
            destroyHashElement(table->hashTable[currentIndex]);
            return true;
        }

        currentIndex = getProbeSequenceIndex(table, startIndex, currentProbeIndexNumber);
        currentProbeIndexNumber++;
    }

    return false;
}

int getElementValue(HashElement* element)
{
    if (element == NULL)
        return 0;

    return element->value;
}

char* getElementKey(HashElement* element)
{
    if (element == NULL)
        return NULL;

    char* key = (char*)calloc(1, sizeof(char) * (strlen(element->key) + 1));
    strcpy(key, element->key);
    return key;
}

int getElementProbesSequenceLength(HashElement* element)
{
    if (element == NULL)
        return 0;

    return element->probeCount;
}

bool getElementValueByKey(HashTable* table, char* key, int* result)
{
    int startIndex = getHash(table, key);
    int currentIndex = startIndex;
    int currentProbeIndexNumber = 1;

    while (table->types[currentIndex] == used) {
        if (strcmp(table->hashTable[currentIndex]->key, key) == 0) {
            *result = table->hashTable[currentIndex]->value;
            return true;
        }

        currentIndex = getProbeSequenceIndex(table, startIndex, currentProbeIndexNumber);
        currentProbeIndexNumber++;
    }

    return false;
}

int getBucketCount(HashTable* table)
{
    return table->bucketCount;
}

HashElement** getHashTableElements(HashTable* hashTable, int* elementNumber)
{
    HashElement** hashTableElements = (HashElement**)malloc(hashTable->elementCount * sizeof(HashElement*));
    *elementNumber = 0;
    int currentElementIndex = 0;

    for (int i = 0; i < hashTable->bucketCount; i++) {
        if (hashTable->types[i] != used)
            continue;
        HashElement* currentElement = hashTable->hashTable[i];
        hashTableElements[currentElementIndex] = createHashElement(currentElement->key, currentElement->value, currentElement->probeCount);
        (*elementNumber)++;
        currentElementIndex++;
    }

    return hashTableElements;
}

void printHashTableElements(HashTable* hashTable)
{
    for (int i = 0; i < hashTable->bucketCount; ++i) {
        if (hashTable->types[i] != used)
            continue;
        HashElement* currentElement = hashTable->hashTable[i];
        printf("%s - %d ", currentElement->key, currentElement->value);
    }
    printf("\n");
}