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
    double imaginaryPartSum = getImaginaryPart(a) + getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartSum, imaginaryPartSum);

    return resultComplex;
}

ComplexNumber* subtractComplex(ComplexNumber* a, ComplexNumber* b) // a - b
{
    double realPartSubtraction = getRealPart(a) - getRealPart(b);
    double imaginaryPartSubraction = getImaginaryPart(a) - getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartSubtraction, imaginaryPartSubraction);

    return resultComplex;
}

ComplexNumber* multiplyComplex(ComplexNumber* a, ComplexNumber* b) // a * b
{
    double realPartMultiplication = getRealPart(a) * getRealPart(b) - getImaginaryPart(a) * getImaginaryPart(b);
    double imaginaryPartMultiplication = getImaginaryPart(a) * getRealPart(b) + getRealPart(a) * getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartMultiplication, imaginaryPartMultiplication);

    return resultComplex;
}

ComplexNumber* divideComplex(ComplexNumber* a, ComplexNumber* b) // a / b
{
    double realPartDivision = (getRealPart(a) * getRealPart(b) + getImaginaryPart(a) * getImaginaryPart(b)) / (getRealPart(b) * getRealPart(b) + getImaginaryPart(b) * getImaginaryPart(b));
    double imaginaryPartDivision = (getImaginaryPart(a) * getRealPart(b) + getRealPart(a) * getImaginaryPart(b)) / (getRealPart(b) * getRealPart(b) + getImaginaryPart(b) * getImaginaryPart(b));

    ComplexNumber* resultComplex = createComplex(realPartDivision, imaginaryPartDivision);

    return resultComplex;
}