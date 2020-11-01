#include "../library/stack/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9' || symbol == '.';
}

bool isMathOperation(char symbol)
{
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

bool isSpace(char symbol)
{
    return symbol == ' ';
}

void printUserInformation()
{
    printf("Введите выражение в постфиксной записи:\n(Например 2.5 4 * 5 /)\n");
}

char* getSubstring(char* string, int startPosition, int length)
{
    char* subString = (char*)calloc(length + 1, sizeof(char));

    for (int i = 0; i < length; ++i)
        subString[i] = string[i + startPosition];

    return subString;
}

char* getInput()
{
    int stringLengthBorder = 2;
    char* input = (char*)malloc(stringLengthBorder * sizeof(char));
    int currentStringLength = 0;
    char inputChar = (char)getchar(); // Посимвольное считывание.

    while (inputChar != '\n') {
        if (currentStringLength == stringLengthBorder) {
            stringLengthBorder *= 2;
            input = (char*)realloc(input, stringLengthBorder * sizeof(char)); // Перевыделение памяти.
        }

        input[currentStringLength] = inputChar;
        currentStringLength++;

        inputChar = (char)getchar();
    }

    return input;
}

bool isInputRight(char* input)
{
    char currentSymbol = ' ';

    for (int i = 0; i < strlen(input); ++i) {
        currentSymbol = input[i];
        if (!isDigit(currentSymbol) && !isMathOperation(currentSymbol) && !isSpace(currentSymbol))
            return false;
    }

    return true;
}

bool handleMathOperationInInput(char* input, int* index, Stack* numbersStack)
{
    if (!isMathOperation(input[*index])) // Если текущий символ - не символ операции.
        return false;

    StackElement* firstNumberElement = popStackElement(numbersStack);
    StackElement* secondNumberElement = popStackElement(numbersStack);

    double secondNumber = getStackElementValue(firstNumberElement);
    double firstNumber = getStackElementValue(secondNumberElement);

    double resultNumber = 0;

    if (input[*index] == '+')
        resultNumber = firstNumber + secondNumber;
    else if (input[*index] == '-')
        resultNumber = firstNumber - secondNumber;
    else if (input[*index] == '*')
        resultNumber = firstNumber * secondNumber;
    else if (input[*index] == '/')
        resultNumber = firstNumber / secondNumber;

    StackElement* pushedElement = createStackElement(resultNumber);
    pushStackElement(numbersStack, pushedElement);

    *index += 2;

    deleteStackElement(firstNumberElement);
    deleteStackElement(secondNumberElement);

    return true;
}

bool handleNumberInInput(char* input, int* index, Stack* numbersStack)
{
    if (!isDigit(input[*index])) // Если текущий символ - не цифра.
        return false;

    int j = *index;
    while (j < strlen(input) && !isSpace(input[j])) // Поиск индекса первого пробела после искомого числа.
        j++;

    int currentNumberLength = j - *index; // Длина получившегося числа.
    char* currentNumberString = getSubstring(input, *index, currentNumberLength); // Получение подстроки, содержащей число.

    double currentNumber = strtod(currentNumberString, NULL); // Переводим строку в число.
    free(currentNumberString); // Освобождаем память, выделенную под подстроку.

    StackElement* pushedElement = createStackElement(currentNumber);
    pushStackElement(numbersStack, pushedElement);

    *index = j + 1;

    return true;
}

double findResult(char* input)
{
    Stack* numbersStack = createStack(); // Стек с числами.

    int i = 0; // Итератор по строке input.

    while (i < strlen(input)) { // Пока не просмотрена вся строка.
        handleMathOperationInInput(input, &i, numbersStack);
        handleNumberInInput(input, &i, numbersStack);
    }

    double result = getStackElementValue(popStackElement(numbersStack)); // Извлекаем число из стека, которое и является результатом.

    deleteStack(numbersStack);
    free(input);

    return result;
}

void printInputError()
{
    printf("Неверный формат ввода!");
}

bool isDoubleIntegerValued(double number)
{
    return number == (long long)number;
}

void printResult(double result)
{
    if (isDoubleIntegerValued(result)) // Если число целое.
        printf("Вычисленное значение: %lld", (long long)result);
    else
        printf("Вычисленное значение: %lf", result);
}

int main()
{
    printUserInformation();

    char* input = getInput();

    if (isInputRight(input)) {
        double result = findResult(input);

        printResult(result);
    } else
        printInputError();

    return 0;
}
