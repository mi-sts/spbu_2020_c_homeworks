#include "complexNumber.h"
#include <stdlib.h>

struct ComplexNumber {
    double realPart;
    double imaginaryPart;
};

ComplexNumber* createComplex(double realPart, double imaginaryPart)
{
    ComplexNumber* complexNumber = (ComplexNumber*)malloc(sizeof(ComplexNumber));
    complexNumber->realPart = realPart;
    complexNumber->imaginaryPart = imaginaryPart;

    return complexNumber;
}

void deleteComplex(ComplexNumber* complexNumber)
{
    free(complexNumber);
}

double getRealPart(ComplexNumber* complexNumber)
{
    return complexNumber->realPart;
}

double getImaginaryPart(ComplexNumber* complexNumber)
{
    return complexNumber->imaginaryPart;
}

ComplexNumber* addComplex(ComplexNumber* a, ComplexNumber* b) // a + b
{
    double realPartSum = getRealPart(a) + getRealPart(b);
    double imaginarySum = getImaginaryPart(a) + getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartSum, imaginarySum);

    return resultComplex;
}

ComplexNumber* subtractComplex(ComplexNumber* a, ComplexNumber* b) // a - b
{
    double realPartSubtraction = getRealPart(a) - getRealPart(b);
    double imaginarySubraction = getImaginaryPart(a) - getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartSubtraction, imaginarySubraction);

    return resultComplex;
}

ComplexNumber* multiplyComplex(ComplexNumber* a, ComplexNumber* b) // a * b
{
    double realPartMultiplication = getRealPart(a) * getRealPart(b) - getImaginaryPart(a) * getImaginaryPart(b);
    double imaginaryMultiplication = getImaginaryPart(a) * getRealPart(b) + getRealPart(a) * getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartMultiplication, imaginaryMultiplication);

    return resultComplex;
}

ComplexNumber* divideComplex(ComplexNumber* a, ComplexNumber* b) // a / b
{
    double realPartDivision = (getRealPart(a) * getRealPart(b) + getImaginaryPart(a) * getImaginaryPart(b))
    double imaginaryDivision = getImaginaryPart(a) * getRealPart(b) + getRealPart(a) * getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartDivision, imaginaryDivision);

    return resultComplex;
}