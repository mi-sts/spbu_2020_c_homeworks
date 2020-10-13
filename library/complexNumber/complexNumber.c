#include "complexNumber.h"
#include <stdlib.h>

struct ComplexNumber {
    int realPart;
    int imaginaryPart;
};

ComplexNumber* createComplex(int realPart, int imaginaryPart)
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

int getRealPart(ComplexNumber* complexNumber)
{
    return complexNumber->realPart;
}

int getImaginaryPart(ComplexNumber* complexNumber)
{
    return complexNumber->imaginaryPart;
}

ComplexNumber* addComplex(ComplexNumber* a, ComplexNumber* b) // a + b
{
    int realPartSum = getRealPart(a) + getRealPart(b);
    int imaginarySum = getImaginaryPart(a) + getImaginaryPart(b);

    ComplexNumber* resultComplex = createComplex(realPartSum, imaginarySum);

    return resultComplex;
}

ComplexNumber* subtractComplex(ComplexNumber* a, ComplexNumber* b) // a - b
{

}

ComplexNumber* multiplyComplex(ComplexNumber* a, ComplexNumber* b); // a * b
{

}

ComplexNumber* divideComplex(ComplexNumber* a, ComplexNumber* b); // a / b
{
    
}