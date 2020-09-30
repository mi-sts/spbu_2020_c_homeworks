#include <stdio.h>

int main()
{
    int number = 0;
    int result = 0;

    printf("%s", "Введите число: ");

    scanf("%d", &number);

    if (number < 2)
        printf("%s", "Простых чисел, меньше заданного нет.");
    else {
        int numberDivisor = 0;
        result = 1; // Для любого числа двойка будет являться простым, ему предшетсвующим.

        for (int numberCurrent = 3; numberCurrent < number + 1; ++numberCurrent) {
            if (numberCurrent % 2 != 0) { // Перебор делителей нечётного numberCurrent до корня из numberCurrent.
                numberDivisor = 3;

                while (numberDivisor * numberDivisor <= numberCurrent) {
                    if (numberCurrent % numberDivisor == 0)
                        break;
                    numberDivisor += 2;
                }

                if (numberDivisor * numberDivisor > numberCurrent)
                    result++;
            }
        }
        printf("%s%d%s%d", "Количество простых чисел, не превосходящих ", number, ": ", result);
    }

    return 0;
}