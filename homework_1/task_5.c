#include <stdbool.h>
#include <stdio.h>

const ARRAY_SIZE = 10000;

int main()
{
    int n = 0;
    int numbers[ARRAY_SIZE];
    int maxNumber = 0;

    printf("%s", "Введите количество элементов в массиве: ");

    scanf("%d", &n);

    printf("%s", "Введите элементы массива: ");

    for (int i = 0; i < n; ++i) {
        scanf("%d", &numbers[i]);
    }

    bool isInitialized = false;

    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j)
            if (numbers[i] == numbers[j] && (!isInitialized || numbers[i] > maxNumber)) {
                maxNumber = numbers[i];
                isInitialized = true;
            }

    printf("%s%d", "Максимальный элемент, встречающийся более 1-го раза: ", maxNumber);

    return 0;
}
