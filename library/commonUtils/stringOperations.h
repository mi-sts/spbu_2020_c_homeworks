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

char* convertDoubleToBinaryNotation(double number);

double convertBinaryNotationToDouble(char* binaryNotation);

#endif
