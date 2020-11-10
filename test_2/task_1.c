#include <stdio.h>
#include <stdlib.h>

void getInput(long long* number)
{
    printf("Введите искомое число Фибоначчи: ");
    scanf("%lld", number);
}

long long* getInitializedPreviousNumbers()
{
    long long* previousNumbers = (long long*)calloc(2, sizeof(long long));
    previousNumbers[0] = 0;
    previousNumbers[1] = 1;

    return previousNumbers;
}

long long findFibonacciNumber(long long number, long long* previousNumbers)
{
    if (number <= 0)
        return -1;

    if (number == 1 || number == 2)
        return previousNumbers[number - 1];

    for (long long i = 2; i < number; ++i) {
        long long temp = previousNumbers[1];
        previousNumbers[1] = previousNumbers[0] + previousNumbers[1];
        previousNumbers[0] = temp;
    }

    return previousNumbers[1];
}

void printResult(long long fibonacciNumber)
{
    printf("Искомое число Фибоначчи: %lld", fibonacciNumber);
}

void printInputError()
{
    printf("Некорректный ввод! Номер числа Фибоначчи - натуральное число.");
}

int main()
{
    long long number = 0;
    long long* previousNumbers = NULL;
    getInput(&number);
    previousNumbers = getInitializedPreviousNumbers();

    long long fibonacciNumber = findFibonacciNumber(number, previousNumbers);

    if (fibonacciNumber != -1) // Если число надено верно.
        printResult(fibonacciNumber);
    else
        printInputError();

    free(previousNumbers);

    return 0;
}
