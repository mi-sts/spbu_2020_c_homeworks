#include <stdio.h>


const ARRAY_SIZE = 100000;

int main()
{
    int m = 0, n = 0;
    int shiftArray[ARRAY_SIZE];

    printf("Введите длины отрезков массива: ");

    scanf("%d%d", &m, &n);

    for (int i = 0; i < m + n; ++i)
        scanf("%d", &shiftArray[i]);

    int temp;

    for (int i = m; i < m + n; ++i) { // Сдвиг первого отрезка по всему массиву.
        temp = shiftArray[i];
        for (int j = i - 1; j >= i - m; --j) {
            shiftArray[j + 1] = shiftArray[j];
            shiftArray[j] = temp;
        }
    }

    printf("Массив с переставленными началом и концом:\n");

    for (int i = 0; i < m + n; ++i)
        printf("%d%s", shiftArray[i], " ");
}