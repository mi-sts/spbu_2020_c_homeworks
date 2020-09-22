#include <stdio.h>
#include <stdbool.h>

const ARRAY_SIZE = 10000;

int main()
{
    int n;
    int numbers[ARRAY_SIZE];
    int maxNumber;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &numbers[i]);
    }

    int i, j;
    bool isInitialized = false;

    for (i = 0; i < n - 1 && !isInitialized; ++i) // Инициализация maxNumber.
        for (j = i + 1; j < n; ++j)
            if (numbers[i] == numbers[j]) {
                maxNumber = numbers[i];
                isInitialized = true;
                break;
            }

    for ( ; i < n - 1; ++i) // Дальнейший обход массива.
        for (j = i + 1; j < n; ++j)
            if (numbers[i] > maxNumber && numbers[i] == numbers[j])
                maxNumber = numbers[i];

    printf("%d", maxNumber);

    return 0;
}