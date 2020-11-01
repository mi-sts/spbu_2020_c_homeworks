#include "stringOperations.h"
#include "numericOperations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int binaryNotationBits = 64;

const int maxIntegerLength = 20;

char* getSubstring(char* string, int startPosition, int length)
{
    char* subString = (char*)calloc(length + 1, sizeof(char));

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

char* getStringWithInsertedSymbol(int position, char symbol, char* string)
{
    if (!isStringPositionExists(position, string))
        return NULL;

    int stringLength = strlen(string);
    char* increasedString = (char*)calloc(stringLength + 2, sizeof(char));

    strcpy(increasedString, string);

    for (int i = stringLength; i > position; --i)
        increasedString[i] = increasedString[i - 1];

    increasedString[position] = symbol;

    return increasedString;
}

char* convertDoubleToString(double number)
{
    char* numberString = (char*)calloc(binaryNotationBits + 1, sizeof(char));
    sprintf(numberString, "%.20g", number);

    return numberString;
}

char* convertIntegerToString(long long number)
{
    char* numberString = (char*)calloc(maxIntegerLength + 1, sizeof(char));
    sprintf(numberString, "%lld", number);
    return numberString;

// Получить двоичную запись unsigned long long в виде строки.
char* convertUnsignedIntegerToBinaryNotation(unsigned long long number)
{
    unsigned long long bitChecker = 1; // Создаём переменную для нахождения двоичного представления числа.
    bitChecker <<= 63; // Сдвигаем единичный бит в старший разряд.

    char* binaryUnsignedInteger = (char*)calloc(binaryNotationBits + 1, sizeof(char));

    for (int i = 0; i < binaryNotationBits; ++i) {
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

char invertBit(char bit)
{
    return bit == '0' ? '1' : '0';
}

char* getSumOfBinaryNumbers(char* firstNumberBinary, char* secondNumberBinary)
{
    int binaryLength = strlen(firstNumberBinary); // Получаем длину числа(они идентичные).
    char* binarySum = (char*)calloc(binaryLength + 1, sizeof(char));

    int firstNumberDigit = 0; // Текущее значение разрядов чисел.
    int secondNumberDigit = 0;
    int portableUnit = 0; // Переносимое число(1 или 0, если ничего не переносим).
    int digitSum = 0; // Сумма разрядов и переносимого числа.
    for (int i = binaryLength - 1; i >= 0; --i) {
        firstNumberDigit = convertBitInInteger(firstNumberBinary[i]);
        secondNumberDigit = convertBitInInteger(secondNumberBinary[i]);

        digitSum = firstNumberDigit + secondNumberDigit + portableUnit;
        binarySum[i] = convertIntegerInBit(digitSum % 2); // Рассчитываем текущий бит числа.
        portableUnit = digitSum >= 2 ? 1 : 0; // Если сумма в разряде больше двух, переносим единицу.
    }

    return binarySum;
}

char* getIncrementedAdditionalBinary(char* binaryNotation)
{
    char signBit = getSignBitInAdditionalBinaryNotation(binaryNotation);
    char* summand = convertUnsignedIntegerToBinaryNotation(1);
    char* incrementedBinary = getSumOfBinaryNumbers(binaryNotation, summand);

    free(summand);
    return incrementedBinary;
}

char getSignBitInAdditionalBinaryNotation(char* binaryNotation)
{
    return binaryNotation[0];
}

void invertAdditionalBinary(char* binaryNotation)
{
    for (int i = 1; i < strlen(binaryNotation); ++i) // Первый знаковый бит не учитывается.
        binaryNotation[i] = invertBit(binaryNotation[i]);
}

char* getConvertedAdditionalInDirectBinaryNotation(char* binaryNotation)
{
    invertAdditionalBinary(binaryNotation); // Инверсия всех разрядов.
    char* directBinary = getIncrementedAdditionalBinary(binaryNotation); // Прибавление единицы.
    invertAdditionalBinary(binaryNotation);

    return directBinary;
}

char* convertIntegerInAdditionalBinaryNotation(long long number)
{
    if (number >= 0)
        return convertUnsignedIntegerToBinaryNotation(number);

    number = -number;
    char* binaryInteger = convertUnsignedIntegerToBinaryNotation(number);
    binaryInteger[0] = '1'; // Знаковый бит в отрицательном числе.
    invertAdditionalBinary(binaryInteger); // Получение обратного кода.
    char* convertedBinary = getIncrementedAdditionalBinary(binaryInteger); // Увеличение числа на единицу.

    free(binaryInteger);
    return convertedBinary;
}

long long convertAdditionalBinaryNotationToInteger(char* binaryNotation)
{
    char signBit = getSignBitInAdditionalBinaryNotation(binaryNotation); // Знаковый бит.

    if (signBit == '0') {
        long long number = (long long)convertBinaryNotationToDouble(binaryNotation);

        return number;
    }

    char* directConvertedBinary = getConvertedAdditionalInDirectBinaryNotation(binaryNotation); // Получаем прямой код.
    directConvertedBinary[0] = '0'; // Убираем единицу с старшего разряда(для перевода).
    long long number = -(long long)convertBinaryNotationToDouble(directConvertedBinary);

    free(directConvertedBinary);
    return number;
}

int convertBitInInteger(char bit)
{
    return bit == '0' ? 0 : 1;
}

char convertIntegerInBit(int number)
{
    return number == 0 ? '0' : '1';
}

// Удаление всех незначащих нулей из двоичной записи.
void removeInsignificantZerosInBinary(char* binary)
{
    reflectString(binary); // Отражаем строку для простоты редактирования.

    int i = strlen(binary) - 1;
    while (binary[i] == '0') {
        binary[i] = '\0';
        i--;
    }

    reflectString(binary);
}
