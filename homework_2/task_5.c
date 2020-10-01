#include <stdio.h>

long long findFactorial(long long n)
{
    return n > 1 ? findFactorial(n - 1) * n : 1;
}

void getInputNumber(int* number)
{
    printf("Введите число, факториал которого хотите найти: ");
    scanf("%lld", number);

    while (*number < 0) {
        printf("Число должно быть неотрицательным!\n");
        printf("Введите число, факториал которого хотите найти: ");
        scanf("%lld", number);
    }
}

void printRecursiveFactorial(int number)
{
    long long numberFactorial = findFactorial(number);
    printf("Факториал %lld, найденный рекурсивно, равен %lld\n", number, numberFactorial);
}

void printIterativeFactorial(int number)
{
    long long numberFactorial = 1;
    long long numberMultiplier = number;

    while (numberMultiplier != 0) {
        numberFactorial *= numberMultiplier;
        numberMultiplier--;
    }

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