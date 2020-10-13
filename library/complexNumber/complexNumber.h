#ifndef SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
#define SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H

typedef struct ComplexNumber ComplexNumber;

ComplexNumber* createComplex(int realPart, int imaginaryPart);

void deleteComplex(ComplexNumber* complexNumber);

int getRealPart(ComplexNumber* complexNumber);

int getImaginaryPart(ComplexNumber* complexNumber);

ComplexNumber* addComplex(ComplexNumber* a, ComplexNumber* b); // a + b

ComplexNumber* subtractComplex(ComplexNumber* a, ComplexNumber* b); // a - b

ComplexNumber* multiplyComplex(ComplexNumber* a, ComplexNumber* b); // a * b

ComplexNumber* divideComplex(ComplexNumber* a, ComplexNumber* b); // a / b

#endif //SPBU_2020_C_HOMEWORKS_COMPLEXNUMBER_H
