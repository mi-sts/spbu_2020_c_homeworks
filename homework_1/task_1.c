#include <stdio.h>

const ARRAY_SIZE = 100;

int main()
{
    int nubmerArray[ARRAY_SIZE][ARRAY_SIZE];
    int n;

    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            nubmerArray[i][j] = i * n + (j + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d%s", nubmerArray[i][j], " | ");

        printf("%s", "\n");
    }

    int sideLength = 1;
    int sideCounter = -1; // Счётчик по длине стороны обхода спирали. -1 установлено для первого элемнта.
    int sideNumber = 0; // Счётчик по количеству итераций. При обоходе спирали длина стороны увеличивается каждые 2 итерации.
    int x = n / 2;
    int y = n / 2;
    int directions[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} }; // Направление обхода(x, y).
    int directionIndex = 0;

    while (!(sideLength == n && sideCounter == n - 1)) // Цикл прерывается, когда длина стороны обхода равна n.
    {
        printf("%d%s", nubmerArray[y][x], " ");

        sideCounter += 1;

        if (sideCounter == sideLength) { //  Условие при окончании обхода одной стороны.
            directionIndex = (directionIndex + 1) % 4;
            sideCounter = 0;
            sideNumber += 1;

            if (sideNumber == 2) {
                sideLength += 1; // Увеличение длины стороны обхода.
                sideNumber = 0;
            }
        }
        x += directions[directionIndex][0]; // Изменение координат обхода.
        y += directions[directionIndex][1];
    }

    return 0;
}