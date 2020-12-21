#include "inputFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char* getInputString()
{
    char* inputString = (char*)calloc(2, sizeof(char));
    int currentLength = 0;
    int lengthBorder = 1;

    char currentSymbol = (char)getchar();

    while (currentSymbol != '\n') {
        inputString[currentLength] = currentSymbol;
        currentLength++;

        if (currentLength == lengthBorder) {
            lengthBorder *= 2;
            inputString = (char*)realloc(inputString, (lengthBorder + 1) * sizeof(char));
            memset(inputString + currentLength * sizeof(char), 0, (lengthBorder - currentLength) * sizeof(char));
        }

        currentSymbol = (char)getchar();
    }

    return inputString;
}