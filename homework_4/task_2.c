#include "../library/commonUtils/numericOperations.h"
#include "../library/commonUtils/stringOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUserInformation()
{
    printf("Введите число: ");
}

void getInput(double* number)
{
    scanf("%lf", number);
}

// Найти индекс последней единицы в двоичной записи binaryNotation.
int findLastOneDigitIndexInBinaryNotation(char* binaryNotation)
{
    int lastOneIndex = strlen(binaryNotation) - 1;
    for (int i = 1; i < strlen(binaryNotation); ++i)
        if (binaryNotation[i] == '0' && binaryNotation[i - 1] == '1')
            lastOneIndex = i - 1;

    return lastOneIndex;
}

// Составить экспоненциальную форму записи double.
char* createExponentialFormString(char numberSign, long long exponentValue, double numberValue, char numberSing, int exponentialFormLength)
{
    char* numberValueString = convertDoubleToString(numberValue); // Получение строки, содержащей мантиссу.
    char* exponentValueString = convertIntegerToString(exponentValue); // Получение строки, содержащей экспоненту.

    char* exponentialFormString = (char*)malloc(exponentialFormLength * sizeof(char));
    char signSymbol = numberSing == '0' ? '+' : '-';

    sprintf(exponentialFormString, "%c%s%s%s%s", signSymbol, numberValueString, "*2^{", exponentValueString, "}");

    free(numberValueString);
    free(exponentValueString);

    return exponentialFormString;
}

// Получить экспоненциальную форму записи double в компьютерном представлении.
char* getExponentialForm(double number)
{
    int formStringLength = strlen("-*2^{}");
    int numberLength = 17; // Максимальная длина double(с точкой).
    int exponentialFormLength = formStringLength + numberLength;
    if (number == 0) {
        char* exponentialForm = (char*)malloc(exponentialFormLength * sizeof(char));
        sprintf(exponentialForm, "%s", "0*2^{0}");

        return exponentialForm;
    }

    char* doubleBinary = convertDoubleToBinaryNotation(number); // Получаем двоичную запись number.

    char numberSign = doubleBinary[0]; // Знак числа.
    char* exponentBinary = getSubstring(doubleBinary, 1, 11); // Двоичная запись порядка.
    char* numberBinary = getSubstring(doubleBinary, 12, 52); // Двоичная запись мантиссы.
    insertSymbolInString(0, '1', numberBinary); // Добавляем единицу в начало двоичной записи мантиссы(которая подразумевается).
    insertSymbolInString(1, '.', numberBinary); // Отделяем целую и дробную части.
    int lastOneDigitIndex = findLastOneDigitIndexInBinaryNotation(numberBinary); // Обрезаем строку до последней единицы.
    char* cutNumberBinary = getSubstring(numberBinary, 0, lastOneDigitIndex + 1);

    long long exponentValue =\
    (long long)convertBinaryNotationToDouble(exponentBinary) - (long long)getBinaryDegreeValue(10) + 1; // Получем исходное значение порядка.
    double numberValue = convertBinaryNotationToDouble(cutNumberBinary); // Получем значение мантиссы в десятичном представлении.

    char* exponentialForm = createExponentialFormString(numberSign, exponentValue, numberValue, numberSign, exponentialFormLength);

    free(doubleBinary);
    free(exponentBinary);
    free(numberBinary);
    free(cutNumberBinary);

    return exponentialForm;
}

void printResult(char* exponentialForm)
{
    printf("Число в экспоненциальной форме: %s", exponentialForm);
}

int main()
{
    double number = 0;
    printUserInformation();
    getInput(&number);
    char* exponentialForm = getExponentialForm(number);
    printResult(exponentialForm);
    free(exponentialForm);

    return 0;
}