#ifndef SPBU_2020_C_HOMEWORKS_MATRIX_H
#define SPBU_2020_C_HOMEWORKS_MATRIX_H

typedef struct Matrix Matrix;

Matrix* createMatrix(int height, int width, float** matrixArray);

void destroyMatrix(Matrix* matrix);

Matrix* addMatrix(Matrix* firstMatrix, Matrix* secondMatrix);

Matrix* subtractMatrix(Matrix* firstMatrix, Matrix* secondMatrix);

Matrix* multiplyMatrix(Matrix* firstMatrix, Matrix* secondMatrix);

Matrix* multiplyMatrixByNumber(Matrix* matrix, float number);

void printMatrix(Matrix* matrix);

#endif
