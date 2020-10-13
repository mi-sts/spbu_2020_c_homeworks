#ifndef SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
#define SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

typedef struct ComplexNumber ComplexNumber;

ComplexNumber* createComplex(double realPart, double imaginaryPart);

void deleteComplex(ComplexNumber* complexNumber);

double getRealPart(ComplexNumber* complexNumber);

double getImaginaryPart(ComplexNumber* complexNumber);

ComplexNumber* addComplex(ComplexNumber* a, ComplexNumber* b); // a + b

ComplexNumber* subtractComplex(ComplexNumber* a, ComplexNumber* b); // a - b

ComplexNumber* multiplyComplex(ComplexNumber* a, ComplexNumber* b); // a * b

ComplexNumber* divideComplex(ComplexNumber* a, ComplexNumber* b); // a / b

void printComplexNumber(ComplexNumber* complexNumber);

#endif //SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
