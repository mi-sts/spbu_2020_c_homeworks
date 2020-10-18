#include "numericOperations.h"

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Получить значение двойки в степени degree.
double getBinaryDegreeValue(int degree)
{
    if (degree >= 0) { // Если степень неотрицательная.
        int binaryDegree = 1;
        binaryDegree <<= degree;
        return (double)binaryDegree;
    }

    double binaryDegree = 1; // Если степень отрицательная.
    for (int i = 0; i < -degree; ++i)
        binaryDegree /= 2.0;

    return binaryDegree;
}
