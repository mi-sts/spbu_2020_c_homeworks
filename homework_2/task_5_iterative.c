#include <stdio.h>

int main()
{
    long long number = 0;

    printf("Введите число, факториал которого хотите найти: ");
    scanf("%lld", &number);

    while (number < 0) {
        printf("Число должно быть неотрицательным!\n");
        printf("Введите число, факториал которого хотите найти: ");
        scanf("%lld", &number);
    }

    long long numberFactorial = 1;
    long long numberMultiplier = number;

    while (numberMultiplier != 0) {
        numberFactorial *= numberMultiplier;
        numberMultiplier--;
    }

    printf("Факториал %lld равен %lld", number, numberFactorial);

    return 0;
}