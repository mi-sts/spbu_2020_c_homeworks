#include <stdio.h>
#include <math.h>

// Получить цифру по индексу(от 0 до numberLength - 1).
int getNumberDigit(int number, int digitIndex, int numberLength)
{
    return number % (int)pow(10, numberLength - digitIndex) / (int)pow(10, numberLength - digitIndex - 1);
}

int main()
{
    int number = 0;

    printf("Введите натуральное число: ");
    scanf("%d", &number);

    while (number <= 0) {
        printf("Число должно быть натуральным!\n");
        printf("Введите натуральное число: ");
        scanf("%d", &number);
    }

    int resultNumber = 0;
    int minDigit = 10;
    int minDigitIndex = 0;
    int numberLength = 0;

    int numberIterator = number;
    while (numberIterator != 0) { // Нахождение длины числа.
        numberIterator /= 10;
        numberLength++;
    }

    int currentDigit = 0;

    for (int i = 0; i < numberLength; ++i) { // Инициализация старшего ненулевого разряда.
        currentDigit = getNumberDigit(number, i, numberLength);

        if (minDigit > currentDigit && currentDigit != 0) {
            minDigit = currentDigit;
            minDigitIndex = i;
        }
    }

    resultNumber = minDigit;

    for (int i = 0; i <= 9; ++i) // Перебор всех цифр от меньших к большим.
        for (int j = 0; j < numberLength; ++j) {
            if (j == minDigitIndex)
                continue;

            if (i == getNumberDigit(number, j, numberLength)) // Если j-я по индексу цифра number равна цифре i.
                resultNumber = resultNumber * 10 + i;
        }

    printf("Получившееся перестановкой цифр минимальное натуральное число: %d", resultNumber);

    return 0;
}