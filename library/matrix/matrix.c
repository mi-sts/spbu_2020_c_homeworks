#include "matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int width;
    int height;
    float** matrixArray;
};

Matrix* createMatrix(int height, int width, float** matrixArray)
{
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));

    matrix->height = height;
    matrix->width = width;
    matrix->matrixArray = matrixArray;

    return matrix;
}

bool setMatrixIndexNumber(Matrix* matrix, int x, int y, float number)
{
    if (!((x >= 1 && x <= matrix->width) && (y >= 1 && y <= matrix->height)))
        return false;

    matrix->matrixArray[y - 1][x - 1] = number;

    return true;
}

void destroyMatrix(Matrix* matrix)
{
    if (matrix == NULL)
        return;

    if (matrix->matrixArray != NULL)
        for (int i = 0; i < matrix->height; ++i)
            if (matrix->matrixArray != NULL)
                free(matrix->matrixArray[i]);
        free(matrix->matrixArray);

    free(matrix);
}

Matrix* addMatrix(Matrix* firstMatrix, Matrix* secondMatrix)
{
    int firstHeight = firstMatrix->height;
    int firstWidth = firstMatrix->width;
    int secondHeight = secondMatrix->height;
    int secondWidth = secondMatrix->width;

    if ((firstHeight != secondHeight) || (firstWidth != secondWidth))
        return NULL;

    float** matrixArray = (float**)calloc(firstHeight, sizeof(float*));
    for (int i = 0; i < firstHeight; ++i)
        matrixArray[i] = (float*)calloc(firstWidth, sizeof(float));

    for (int i = 0; i < firstHeight; ++i)
        for (int j = 0; j < firstWidth; ++j)
            matrixArray[i][j] = firstMatrix->matrixArray[i][j] + secondMatrix->matrixArray[i][j];


    Matrix* resultMatrix = createMatrix(firstHeight, firstWidth, matrixArray);

    return resultMatrix;
}

Matrix* subtractMatrix(Matrix* firstMatrix, Matrix* secondMatrix)
{
    int firstHeight = firstMatrix->height;
    int firstWidth = firstMatrix->width;
    int secondHeight = secondMatrix->height;
    int secondWidth = secondMatrix->width;

    if ((firstHeight != secondHeight) || (firstWidth != secondWidth))
        return NULL;

    float** matrixArray = (float**)calloc(firstHeight, sizeof(float*));
    for (int i = 0; i < firstHeight; ++i)
        matrixArray[i] = (float*)calloc(firstWidth, sizeof(float));

    for (int i = 0; i < firstHeight; ++i)
        for (int j = 0; j < firstWidth; ++j)
            matrixArray[i][j] = firstMatrix->matrixArray[i][j] - secondMatrix->matrixArray[i][j];


    Matrix* resultMatrix = createMatrix(firstHeight, firstWidth, matrixArray);

    return resultMatrix;
}

Matrix* multiplyMatrix(Matrix* firstMatrix, Matrix* secondMatrix)
{
    if (firstMatrix->width != secondMatrix->height)
        return NULL;

    int firstHeight = firstMatrix->height;
    int firstWidth = firstMatrix->width;
    int secondHeight = secondMatrix->height;
    int secondWidth = secondMatrix->width;

    float** matrixArray = (float**)calloc(firstHeight, sizeof(float*));
    for (int i = 0; i < firstHeight; ++i)
        matrixArray[i] = (float*)calloc(secondWidth, sizeof(float));

    for (int i = 0; i < firstHeight; ++i)
        for (int j = 0; j < firstHeight; ++j) {
            matrixArray[i][j] = 0;
            for (int k = 0; k < secondHeight; ++k)
                matrixArray[i][j] += firstMatrix->matrixArray[k][i] * secondMatrix->matrixArray[j][k];
        }

    Matrix* resultMatrix = createMatrix(firstHeight, secondWidth, matrixArray);

    return resultMatrix;
}

Matrix* multiplyMatrixByNumber(Matrix* matrix, float number)
{
    int matrixHeight = matrix->height;
    int matrixWidth = matrix->width;

    float** matrixArray = (float**)calloc(matrixHeight, sizeof(float*));
    for (int i = 0; i < matrixHeight; ++i)
        matrixArray[i] = (float*)calloc(matrixWidth, sizeof(float));

    for (int i = 0; i < matrixHeight; ++i)
        for (int j = 0; j < matrixWidth; ++j)
            matrixArray[i][j] = matrix->matrixArray[i][j] * number;

    Matrix* resultMatrix = createMatrix(matrixHeight, matrixWidth, matrixArray);

    return resultMatrix;
}

void printMatrix(Matrix* matrix)
{
    if (matrix == NULL || matrix->matrixArray == NULL)
        return;

    for (int i = 0; i < matrix->height; ++i) {
        printf("| ");
        for (int j = 0; j < matrix->width; ++j)
            printf("%f | ", matrix->matrixArray[i][j]);
        printf("\n");
    }
}