#include "inputFunctions.h"
#include <stdio.h>


long long nonnegativeNumberInput(char* preInputMessage)
{
    long long number = 0;

    printf("%s", preInputMessage);
    scanf("%lld", &number);

    while (number < 0) {
        printf("Число должно быть неотрицательным!\n");
        printf("%s", preInputMessage);
        scanf("%lld", &number);
    }

    return number;
}

long long naturalNumberInput(char* preInputMessage)
{
    long long number = 0;

    printf("%s", preInputMessage);
    scanf("%lld", &number);

    while (number <= 0) {
        printf("Число должно быть натуральным!\n");
        printf("%s", preInputMessage);
        scanf("%lld", &number);
    }

    return number;
}
