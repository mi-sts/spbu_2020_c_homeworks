#include "../library/commonUtils/numericOperations.h"
#include "../library/commonUtils/stringOperations.h"
#include <stdio.h>
#include <stdlib.h>

void printUserInformation()
{
    printf("Введите два целых числа: ");
}

void getInputNumbers(long long* firstNumber, long long* secondNumber)
{
    scanf("%lld%lld", firstNumber, secondNumber);
}

void printResult(char* firstNumberBinary, char* secondNumberBinary, char* sumBinary, long long sum)
{
    printf("Все представления двоичных чисел - в дополнительном коде.\n");
    printf("Первое число в двоичном представлении: %s\nВторое число в двоичном представлении: %s\n", firstNumberBinary, secondNumberBinary);
    printf("Их сумма в двоичной системе: %s\nИх сумма в десятичной системе: %lld", sumBinary, sum);
}

int main()
{
    printUserInformation();
    long long firstNumber = 0, secondNumber = 0;
    getInputNumbers(&firstNumber, &secondNumber);

    char* firstNumberBinary = convertIntegerInAdditionalBinaryNotation(firstNumber);
    char* secondNumberBinary = convertIntegerInAdditionalBinaryNotation(secondNumber);
    char* sumBinary = getSumOfBinaryNumbers(firstNumberBinary, secondNumberBinary);
    long long sum = convertAdditionalBinaryNotationToInteger(sumBinary); // Перевод суммы из двоичного представления в десятичное.

    printResult(firstNumberBinary, secondNumberBinary, sumBinary, sum);

    free(firstNumberBinary);
    free(secondNumberBinary);
    free(sumBinary);

    return 0;
}