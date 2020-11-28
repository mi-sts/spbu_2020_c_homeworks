#include "../library/commonUtils/numericOperations.h"
#include "../library/hashTable/hashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int POLYNOM_FACTOR = 13;

bool isAlphabetSymbol(char symbol)
{
    return symbol >= 'a' && symbol <= 'z' || symbol >= 'A' && symbol <= 'Z';
}

char toLower(char symbol)
{
    if (!isAlphabetSymbol(symbol))
        return NULL;

    if (symbol >= 'A' && symbol <= 'Z')
        return symbol - 'A' + 'a';

    return symbol;
}

char* getNextWordFromFile(FILE* inputFile)
{
    bool isFileEmpty = feof(inputFile);

    if (isFileEmpty)
        return NULL;

    int currentLengthBorder = 1;
    int currentLength = 0;
    char* word = (char*)calloc(currentLengthBorder + 1, sizeof(char));

    char currentSymbol = (char)fgetc(inputFile);
    while (!isAlphabetSymbol(currentSymbol)) {
        if (feof(inputFile)) {
            isFileEmpty = true;
            break;
        }

        currentSymbol = (char)fgetc(inputFile);
    }

    while (!isFileEmpty && isAlphabetSymbol(currentSymbol)) {
        word[currentLength] = toLower(currentSymbol);

        isFileEmpty = feof(inputFile);
        currentSymbol = (char)fgetc(inputFile);
        currentLength++;

        if (currentLength == currentLengthBorder) {
            currentLengthBorder *= 2;
            word = (char*)realloc(word, (currentLengthBorder + 1) * sizeof(char));
            memset(word + currentLength * sizeof(char), 0, (currentLengthBorder - currentLength + 1) * sizeof(char));
        }
    }

    if (currentLength > 0)
        return word;

    free(word);
    return NULL;
}

void addWordsFromFileToHashTable(HashTable* hashTable, FILE* file)
{
    char* currentWord = getNextWordFromFile(file);
    HashElement* currentWordElement = NULL;
    int sameWordCount = 0;

    while (currentWord != NULL) {
        if (getElementValueByKey(hashTable, currentWord, &sameWordCount)) {
            deleteElement(hashTable, currentWord);
            addElement(hashTable, currentWord, sameWordCount + 1);
        } else {
            addElement(hashTable, currentWord, 1);
        }

        free(currentWord);
        currentWord = getNextWordFromFile(file);
    }
}

int compareWordByOccurrence(const void* firstElement, const void* secondElement)
{
    return (getElementValue(*(HashElement**)secondElement) - getElementValue(*(HashElement**)firstElement));
}

void sortWordElementsByOccurrence(HashElement** wordElements, int wordCount)
{
    qsort(wordElements, wordCount, sizeof(HashElement*), compareWordByOccurrence);
}

float getAverageProbesSequenceLength(HashElement** wordElements, int wordCount) {
    if (wordCount <= 0)
        return 0.0f;

    int probesSequenceLengthsSum = 0;

    for (int i = 0; i < wordCount; ++i) {
        probesSequenceLengthsSum += getElementProbesSequenceLength(wordElements[i]);
    }

    float averageProbesSequenceLength = (float)probesSequenceLengthsSum / (float)wordCount;

    return averageProbesSequenceLength;
}

int getMaxProbesSequenceLength(HashElement** wordElements, int wordCount)
{
    if (wordCount <= 0)
        return 0;

    int maxProbesSequenceLength = getElementProbesSequenceLength(wordElements[0]);

    for (int i = 0; i < wordCount; ++i)
        maxProbesSequenceLength = max(maxProbesSequenceLength, getElementProbesSequenceLength(wordElements[i]));

    return maxProbesSequenceLength;
}

void printMaxProbesSequenceLengthWords(HashElement** wordElements, int wordCount, int maxProbesSequenceLength)
{
    for (int i = 0; i < wordCount; ++i)
        if (getElementProbesSequenceLength(wordElements[i]) == maxProbesSequenceLength) {
            char* elementKey = getElementKey(wordElements[i]);
            printf("%s ", elementKey);
            free(elementKey);
        }

    printf("\n");
}

void printTopMostCommonWords(HashElement** wordElements, int wordCount, int topCount)
{
    topCount = min(topCount, wordCount);
    sortWordElementsByOccurrence(wordElements, wordCount);

    for (int i = 0; i < topCount; ++i) {
        char* elementKey = getElementKey(wordElements[i]);
        printf("%s ", elementKey);
        free(elementKey);
    }
    printf("\n");
}

void printHashTableInfo(HashTable* hashTable, HashElement** wordElements, int wordCount, int topCount)
{
    float loadFactor = getLoadFactor(hashTable);
    float averageProbesSequenceLength = getAverageProbesSequenceLength(wordElements, wordCount);
    int maxProbesSequenceLength = getMaxProbesSequenceLength(wordElements, wordCount);
    int freeBucketCount = getBucketCount(hashTable) - wordCount;

    topCount = min(topCount, wordCount);
    if (topCount < 0)
        topCount = 0;

    printf("Load factor: %f\n", loadFactor);
    printf("Среднее количество проб при добавлении элемента: %f\n", averageProbesSequenceLength);
    printf("Максимальное количество проб при добавлении элемента: %d\n", maxProbesSequenceLength);
    printf("Слова с максимальным количеством проб: ");
    printMaxProbesSequenceLengthWords(wordElements, wordCount, maxProbesSequenceLength);
    printf("Общее число добавленных слов: %d\n", wordCount);
    printf("Число пустых ячеек таблицы: %d\n", freeBucketCount);
    printf("Топ-%d самых встречаемых слов: ", topCount);
    printTopMostCommonWords(wordElements, wordCount, topCount);
}

int main()
{
    FILE* inputFile = fopen("../homework_6/text.txt", "r");
    HashTable* hashTable = createHashTable(POLYNOM_FACTOR);

    addWordsFromFileToHashTable(hashTable, inputFile);

    int wordCount = 0;
    HashElement** wordElements = getHashTableElements(hashTable, &wordCount);

    printHashTableInfo(hashTable, wordElements, wordCount, 10);

    fclose(inputFile);
    for (int i = 0; i < wordCount; ++i)
        destroyHashElement(wordElements[i]);
    free(wordElements);
    destroyHashTable(hashTable);

    return 0;
}