#include <stdio.h>

const ARRAY_SIZE = 100000;

// Функция, переставляющая элементы массива с индексами от start до end включительно в обратном порядке.
void reflectArray(int array[ARRAY_SIZE], int start, int end)
{
    int temp = 0;

    for (int i = 0; i < (end - start + 1) / 2; ++i) { // За один проход меняем местами пару противоположных элементов.
        temp = array[start + i];
        array[start + i] = array[end - i];
        array[end - i] = temp;
    }
}

int main()
{
    int m = 0, n = 0;
    int shiftArray[ARRAY_SIZE];

    printf("%s", "Введите длины отрезков массива: ");

    scanf("%d%d", &m, &n);

    printf("%s", "Введите элементы массива: ");

    for (int i = 0; i < m + n; ++i)
        scanf("%d", &shiftArray[i]);

    reflectArray(shiftArray, 0, m + n - 1); // Перетавляем весь массив.
    reflectArray(shiftArray, 0, n - 1); // Переставляем первые n элементов.
    reflectArray(shiftArray, n, n + m - 1); // Переставляем m элементов с конца.

    printf("Массив с переставленными началом и концом:\n");

    for (int i = 0; i < m + n; ++i)
        printf("%d%s", shiftArray[i], " ");
}
