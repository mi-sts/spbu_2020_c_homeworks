#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../library/hashTable/hashTable.h"

const int POLYNOM_FACTOR = 5;

void printUserInfo()
{
    printf("Введите целые числа(для завершения ввода введите 0): ");
}

int getNumberLength(int number) {
    int length = 0;
    while (number != 0) {
        number /= 10;
        length++;
    }

    return length;
}

void scanNumbers(HashTable* hashTable)
{
    int currentNumber = 0;
    scanf("%d", &currentNumber);

    while (currentNumber != 0) {
        int numberLength = getNumberLength(currentNumber);
        char* numberString = (char*)calloc(numberLength + 1, sizeof(char));
        sprintf(numberString, "%d", currentNumber);
        for (int i = 0; i < numberLength; ++i)
            numberString[i] += 'A';
        addElement(hashTable, numberString, 1);
        free(numberString);
        scanf("%d", &currentNumber);
    }
}

void createHashTableWithNumbers(HashTable* hashTable)
{
    printUserInfo();
    scanNumbers(hashTable);
}

int compareByOccurrence(const void* firstElement, const void* secondElement)
{
    return (getElementValue(*(HashElement**)firstElement) - getElementValue(*(HashElement**)secondElement));
}

void sortNumbersByOccurrence(HashElement** numbers, int numbersCount)
{
    qsort(numbers, numbersCount, sizeof(HashElement*), compareByOccurrence);
}

void destroyHashElementArray(HashElement** array, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
        destroyHashElement(array[i]);

    free(array);
}

void printNumbers(HashTable* numbers) {
    int numbersCount = 0;
    HashElement** numbersElements = getHashTableElements(numbers, &numbersCount);
    sortNumbersByOccurrence(numbersElements, numbersCount);
    for (int i = 0; i < numbersCount; ++i) {
        char* key = getElementKey(numbersElements[i]);
        for (int j = 0; j < strlen(key); ++j)
            key[j] -= 'A';
        printf("%s - %d\n", key, getElementValue(numbersElements[i]));

        free(key);
    }

    destroyHashElementArray(numbersElements, numbersCount);
}

int main()
{
    HashTable* numbers = createHashTable(POLYNOM_FACTOR);
    createHashTableWithNumbers(numbers);
    printNumbers(numbers);

    destroyHashTable(numbers);

    return 0;
}