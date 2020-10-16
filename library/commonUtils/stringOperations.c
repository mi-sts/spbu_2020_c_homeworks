#include "stringOperations.h"
#include "numericOperations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getSubstring(char* string, int startPosition, int length)
{
    char* subString = (char*)malloc(length * sizeof(char));

    for (int i = 0; i < length; ++i)
        subString[i] = string[i + startPosition];

    return subString;
}

void swapSymbolsInString(char* firstSymbol, char* secondSymbol)
{
    char temp = *firstSymbol;
    *firstSymbol = *secondSymbol;
    *secondSymbol = temp;
}

void reflectString(char* string)
{
    int stringLength = strlen(string);
    for (int i = 0; i < stringLength / 2; ++i)
        swapSymbolsInString(&string[i], &string[stringLength - (i + 1)]);
}

bool isStringPositionExists(int position, char* string)
{
    return position >= 0 && position < strlen(string);
}

void insertSymbolInString(int position, char symbol, char* string)
{
    if (!isStringPositionExists(position, string))
        return;

    int stringLength = strlen(string);
    for (int i = stringLength; i > position; --i)
        string[i] = string[i - 1];

    string[position] = symbol;
}

char* convertDoubleToString(double number)
{
    char* numberString = (char*)malloc(64 * sizeof(char));
    sprintf(numberString, "%.20g", number);

    return numberString;
}

char* convertIntegerToString(long long number)
{
    char* numberString = (char*)malloc(20 * sizeof(char));
    sprintf(numberString, "%lld", number);
    return numberString;
}

// Получить двоичную запись unsigned long long в виде строки.
char* convertUnsignedIntegerToBinaryNotation(unsigned long long number)
{
    unsigned long long bitChecker = 1; // Создаём переменную для нахождения двоичного представления числа.
    bitChecker <<= 63; // Сдвигаем единичный бит в старший разряд.

    char* binaryUnsignedInteger = (char*)malloc(64 * sizeof(char));

    for (int i = 0; i < 64; ++i) {
        binaryUnsignedInteger[i] = bitChecker & number ? '1' : '0';
        bitChecker >>= 1;
    }

    return binaryUnsignedInteger;
}

// Получить двоичную запись double в виде строки.
char* convertDoubleToBinaryNotation(double number)
{
    typedef union udouble { // Создание объединения для получения двоичного представления double в десятичной системе.
        double doubleNumber;
        unsigned long long unsignedIntegerNumber; // Двоичное представление double в десятичной системе.
    } udouble;

    udouble uNumber;
    uNumber.doubleNumber = number;

    char* doubleBinary = convertUnsignedIntegerToBinaryNotation(uNumber.unsignedIntegerNumber);

    return doubleBinary;
}

// Получить double из двоичной записи binaryNotation.
double convertBinaryNotationToDouble(char* binaryNotation)
{
    double number = 0;
    int digit = 0; // Текущий разряд.

    int pointIndex = -1; // Индекс разряда точки(если число нецелое).
    for (int i = strlen(binaryNotation) - 1; i >= 0; --i)
        if (binaryNotation[i] == '.') {
            pointIndex = strlen(binaryNotation) - 1 - i; // Получаем индекс разряда числа(от младших разрядов).
            break;
        }

    int binaryDegree = 0; // Степень двойки для перевода в десятичное число.
    if (pointIndex != -1)
        binaryDegree = -pointIndex; // В случае, если имеется точка в записи, начальная степень двойки для перевода отрицательна.

    for (int i = strlen(binaryNotation) - 1; i >= 0; --i) {
        if (binaryNotation[i] == '.')
            continue;
        digit = binaryNotation[i] == '1' ? 1 : 0;
        number += digit * getBinaryDegreeValue(binaryDegree); // Добавляем в сумму текущий разряд.
        binaryDegree++; // Увеличиваем степень двойки.
    }

    return number;
}
