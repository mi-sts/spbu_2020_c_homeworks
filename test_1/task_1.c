#include <stdio.h>
#include <stdlib.h>

void getCountInput(int* firstCount, int* secondCount)
{
    printf("Введите количество тетрадей в первой стопке: ");
    scanf("%d", firstCount);
    printf("Введите количество тетрадей во второй стопке: ");
    scanf("%d", secondCount);
}

void getNotebooksDifficulty(int* firstNotebooks, int firstCount, int* secondNotebooks, int secondCount)
{
    printf("Введите по убыванию сложность конспектов в первой стопке: ");
    for (int i = 0; i < firstCount; ++i)
        scanf("%d", &firstNotebooks[i]);

    printf("Введите по убыванию сложность конспектов во второй стопке: ");
    for (int i = 0; i < secondCount; ++i)
        scanf("%d", &secondNotebooks[i]);
}

int* combineNotebooks(int* firstNotebooks, int firstCount, int* secondNotebooks, int secondCount, int* totalNotebooks) {
    int curFirstMin = firstNotebooks[0]; // Минимальный встречавшийся элемент в первом массиве на момент обохода.
    int curSecondMin = secondNotebooks[0]; // Минимальный встречавшийся элемент во втором массиве на момент обохода.
    int totalCount = firstCount + secondCount;

    int i = 0; // Итераторы первого массива, второго массива и общего массива соотвественно.
    int j = 0;
    int k = 0;

    int curFirstDifficulty = 0; // Текущие элементы первого и второго массива при обходе соотвественно.
    int curSecondDifficulty = 0;

    while (k != totalCount)
    {
        if (curFirstMin >= curSecondMin && i < firstCount || i == 0)
            curFirstDifficulty = firstNotebooks[i];
        if (curSecondMin >= curFirstMin && j < secondCount || j == 0)
            curSecondDifficulty = secondNotebooks[j];

        if (curFirstDifficulty < curFirstMin)
            curFirstMin = curFirstDifficulty;
        if (curSecondDifficulty < curSecondMin)
            curSecondMin = curSecondDifficulty;

        if ((curFirstMin >= curSecondMin || j == secondCount) && i < firstCount) {
            totalNotebooks[k] = curFirstMin;
            i++;
            k++;
        }
        if ((curSecondMin >= curFirstMin || i == firstCount) && j < secondCount) {
            totalNotebooks[k] = curSecondMin;
            j++;
            k++;
        }
    }

    return totalNotebooks;
}

void printResult(int* totalNotebooks, int totalCount)
{
    printf("Объединённая отсортированная стопка:\n");
    for (int i = 0; i < totalCount; ++i)
        printf("%d ", totalNotebooks[i]);
}

int main()
{
    int firstCount = 0, secondCount = 0;

    getCountInput(&firstCount, &secondCount);

    int* firstNotebooks = (int*)calloc(firstCount, sizeof(int));
    int* secondNotebooks = (int*)calloc(secondCount, sizeof(int));
    int* totalNotebooks = (int*)calloc(firstCount + secondCount, sizeof(int));

    getNotebooksDifficulty(firstNotebooks, firstCount, secondNotebooks, secondCount);

    totalNotebooks = combineNotebooks(firstNotebooks, firstCount, secondNotebooks, secondCount, totalNotebooks);

    printResult(totalNotebooks, firstCount + secondCount);

    free(firstNotebooks);
    free(secondNotebooks);
    free(totalNotebooks);

    return 0;
}