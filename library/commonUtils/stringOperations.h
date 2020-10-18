#ifndef SPBU_2020_C_HOMEWORKS_STRINGOPERATIONS_H
#define SPBU_2020_C_HOMEWORKS_STRINGOPERATIONS_H

#include <stdbool.h>

char* getSubstring(char* string, int startPosition, int length);

void swapSymbolsInString(char* firstSymbol, char* secondSymbol);

void reflectString(char* string);

bool isStringPositionExists(int position, char* string);

void insertSymbolInString(int position, char symbol, char* string);

char* convertDoubleToString(double number);

char* convertIntegerToString(long long number);

char* convertUnsignedIntegerToBinaryNotation(unsigned long long number);

char* convertNonnegativeDoubleToBinaryNotation(double number);

double convertBinaryNotationToDouble(char* binaryNotation);

char invertBit(char bit);

char* getSumOfBinaryNumbers(char* firstNumberBinary, char* secondNumberBinary);

char* getIncrementedAdditionalBinary(char* binaryNotation);

void invertAdditionalBinary(char* binaryNotation);

char* getConvertedAdditionalInDirectBinaryNotation(char* binaryNotation);

char* convertIntegerInAdditionalBinaryNotation(long long number);

char getSignBitInAdditionalBinaryNotation(char* binaryNotation);

long long convertAdditionalBinaryNotationToInteger(char* binaryNotation);

int convertBitInInteger(char bit);

char convertIntegerInBit(int number);

void removeInsignificantZerosInBinary(char* binary);

#endif
