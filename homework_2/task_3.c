#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;

    printf("Введите длину массива: ");
    scanf("%d", &n);

    int* array = (int*)calloc(n, sizeof(int));

    printf("Введите элементы массива:\n");
    for (int i = 0; i < n; ++i)
        scanf("%d", &array[i]);

    int difference = 0; // Переменая, показывающая, сколько нулей встретилось при обходе массива(разница в индексе).
    int temp = 0;

    for (int i = 0; i < n; ++i) {
        if (array[i] == 0) {
            difference++;
            continue;
        }

        if (difference == 0)
            continue;

        temp = array[i - difference]; // Меняем местами текущий элемент и стоящий на different меньше по индексу элемент.
        array[i - difference] = array[i];
        array[i] = temp;
    }

    printf("Массив с перемещёнными в конец нулями:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);

    return 0;
}