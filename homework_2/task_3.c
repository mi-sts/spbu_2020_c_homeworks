#include "../library/commonUtils/numericOperations.h"
#include <stdio.h>
#include <stdlib.h>

// Функция ввода данных.
int* getInputArray(int* n)
{
    printf("Введите длину массива: ");
    scanf("%d", n);

    int* array = (int*)calloc(*n, sizeof(int));

    printf("Введите элементы массива:\n");
    for (int i = 0; i < *n; ++i)
        scanf("%d", &array[i]);

    return array;
}

// Функция перемещающая нули в массиве в конец.
void moveZeros(int* array, int arrayLength)
{
    int difference = 0; // Переменая, показывающая, сколько нулей встретилось при обходе массива(разница в индексе).

    for (int i = 0; i < arrayLength; ++i) {
        if (array[i] == 0) {
            difference++;
            continue;
        }

        if (difference == 0)
            continue;

        swap(&array[i - difference], &array[i]); // Меняем местами текущий элемент и стоящий на different меньше по индексу элемент.
    }
}

// Функция вывода массива.
void printArray(int* array, int arrayLength)
{
    printf("Массив с перемещёнными в конец нулями:\n");

    for (int i = 0; i < arrayLength; ++i)
        printf("%d ", array[i]);
}

int main()
{
    int n = 0;

    int* array = getInputArray(&n);
    moveZeros(array, n);
    printArray(array, n);

    free(array);

    return 0;
}