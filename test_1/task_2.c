#include "../library/matrix/matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* getInputMatrix()
{
    printf("Введите высоту и ширину матрицы и введите элементы матрицы через пробел(новая строка матрицы на новой строке):\n");

    int width = 0; int height = 0;
    scanf("%d %d", &height, &width);

    float** matrixArray = (float**)calloc(height, sizeof(float*));
    for (int i = 0; i < height; ++i)
        matrixArray[i] = (float*)calloc(width, sizeof(float));

    for (int i = 0; i < height; ++i)
        for (int j = 0; j < width; ++j)
            scanf("%f", &matrixArray[i][j]);

    Matrix* inputMatrix = createMatrix(height, width, matrixArray);

    return inputMatrix;
}

int main()
{
    Matrix* firstMatrix = getInputMatrix();
    Matrix* secondMatrix = getInputMatrix();

    printf("Первая матрица:\n");
    printMatrix(firstMatrix);
    printf("Вторая матрица:\n");
    printMatrix(secondMatrix);

    Matrix* sumMatrix = addMatrix(firstMatrix, secondMatrix);

    printf("Сумма этих матриц:\n");
    printMatrix(sumMatrix);

    Matrix* subtractionMatrix = subtractMatrix(firstMatrix, secondMatrix);

    printf("Разность первой и второй матрицы:\n");
    printMatrix(subtractionMatrix);

    Matrix* multiplicationMatrix = multiplyMatrix(firstMatrix, secondMatrix);

    printf("Произведение первой и второй матрицы:\n");
    printMatrix(multiplicationMatrix);

    printf("Введите число для умножения на матрицу: ");
    float multiplicationNumber = 0;
    scanf("%f", &multiplicationNumber);

    Matrix* numberMultiplicationMatrix = multiplyMatrixByNumber(firstMatrix, multiplicationNumber);

    printf("Первая матрица, умноженная на %f:\n", multiplicationNumber);
    printMatrix(numberMultiplicationMatrix);
}