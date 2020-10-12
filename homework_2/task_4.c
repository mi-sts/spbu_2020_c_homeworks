#include "../library/commonUtils/inputFunctions.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Получить длину числа.
int getNumberLength(long long number)
{
    int numberLength = 0;

    long long numberIterator = number;
    while (numberIterator != 0) {

        numberIterator /= 10;
        numberLength++;
    }

    return numberLength;
}

// Получить массив цифр числа.
int* getNumberDigits(long long number, int numberLength)
{
    int* numberDigits = (int*)calloc(numberLength, sizeof(int));

    for (int i = numberLength - 1; i >= 0; --i) {
        numberDigits[i] = number % 10;
        number /= 10;
    }

    return numberDigits;
}

// Подсчёт количества вхождений числа в массив.
int getNumberCountInArray(int* array, int number, int arrayLength)
{
    int count = 0;

    for (int i = 0; i < arrayLength; ++i)
        if (array[i] == number)
            count++;

    return count;
}

// Найти минимальное натуральное число, получающееся перестановкой цифр в числе.
long long findMinNaturalNumber(long long number)
{
    int numberLength = getNumberLength(number);
    int* numberDigits = getNumberDigits(number, numberLength); // Массив цифр числа.
    int zeroCount = getNumberCountInArray(numberDigits, 0, numberLength); // Количество нулей в числе.

    long long minNaturalNumber = 0;
    bool isZerosAdded = false; // Добавлены ли нули в новое число.

    for (int i = 1; i <= 9; ++i) // Перебор всех цифр от 1 до 9.
        for (int j = 0; j < numberLength; ++j) {
            if (i == numberDigits[j]) { // Если j-я по индексу цифра number равна цифре i.
                minNaturalNumber = minNaturalNumber * 10 + i;
                if (!isZerosAdded) { // Если после добавления первой ненулевой цифры нули ещё не были добавлены.
                    isZerosAdded = true;
                    for (int k = 0; k < zeroCount; k++) // Добавляем нули после первой цифры.
                        minNaturalNumber *= 10;
                }
            }
        }

    free(numberDigits);
    return minNaturalNumber;
}

void printResult(long long minNaturalNumber)
{
    printf("Получившееся перестановкой цифр минимальное натуральное число: %lld", minNaturalNumber);
}

int main()
{
    long long number = naturalNumberInput("Введите натуральное число: ");
    long long minNaturalNumber = findMinNaturalNumber(number);

    printResult(minNaturalNumber);

    return 0;
}