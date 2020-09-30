#include <stdio.h>

long long findFactorial(long long n)
{
    return n > 1 ? findFactorial(n - 1) * n : 1;
}

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

    long long numberFactorial = findFactorial(number);
    printf("Факториал %lld равен %lld", number, numberFactorial);

    return 0;
}