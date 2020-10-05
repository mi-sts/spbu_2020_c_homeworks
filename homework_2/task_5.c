#include "../library/commonUtils/inputFunctions.h"
#include <stdio.h>

// Поиск факториала рекурсивно.
long long findRecursiveFactorial(long long number)
{
    return number > 1 ? findRecursiveFactorial(number - 1) * number : 1;
}

// Поиск факториала итеративно.
long long findIterativeFactorial(long long number)
{
    long long numberFactorial = 1;
    long long numberMultiplier = number;

    while (numberMultiplier != 0) {
        numberFactorial *= numberMultiplier;
        numberMultiplier--;
    }

    return numberFactorial;
}

void getInputNumber(int* number)
{
    *number = (int)nonnegativeNumberInput("Введите число, факториал которого хотите найти: ");
}

void printRecursiveFactorial(int number)
{
    long long numberFactorial = findRecursiveFactorial(number);
    printf("Факториал %lld, найденный рекурсивно, равен %lld\n", number, numberFactorial);
}

void printIterativeFactorial(int number)
{
    long long numberFactorial = findIterativeFactorial(number);
    printf("Факториал %lld, найденный итеративно, равен %lld\n", number, numberFactorial);
}

int main()
{
    long long number = 0;
    getInputNumber(&number);
    printRecursiveFactorial(number);
    printIterativeFactorial(number);

    return 0;
}