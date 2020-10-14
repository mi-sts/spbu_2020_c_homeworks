#include "../library/stack/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const MAX_STRING_LENGHT = 10000;

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
    char* subString = (char*)malloc(length * sizeof(char));

    for (int i = 0; i < length; ++i)
        subString[i] = string[i + startPosition];

    return subString;
}

void getInput(char* input)
{
    fgets(input, MAX_STRING_LENGHT, stdin); // Ввод строки.
    int lastIndex = strlen(input) - 1;
    if (input[lastIndex] == '\n')
        input[lastIndex] = '\0'; // Удаление символа перевода строки.
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

double findResult(char* input)
{
    Stack* numbersStack = createStack(); // Стек с числами.

    int i = 0; // Итератор по строке input.

    while (i < strlen(input)) { // Пока не просмотрена вся строка.
        if (isMathOperation(input[i])) { // Если текущий символ - символ операции.
            double secondNumber = getStackElementValue(popStackElement(numbersStack));
            double firstNumber = getStackElementValue(popStackElement(numbersStack));
            double resultNumber = 0;

            if (input[i] == '+')
                resultNumber = firstNumber + secondNumber;
            else if (input[i] == '-')
                resultNumber = firstNumber - secondNumber;
            else if (input[i] == '*')
                resultNumber = firstNumber * secondNumber;
            else if (input[i] == '/')
                resultNumber = firstNumber / secondNumber;

            StackElement* pushedElement = createStackElement(resultNumber);
            pushStackElement(numbersStack, pushedElement);

            i += 2;
        } else { // Если текущий символ - начало числа.
            int j = i;
            while (j < strlen(input) && !isSpace(input[j])) // Поиск индекса первого пробела после искомого числа.
                j++;

            int currentNumberLength = j - i; // Длина получившегося числа.
            char* currentNumberString = getSubstring(input, i , currentNumberLength); // Получение подстроки, содержащей число.

            double currentNumber = strtod(currentNumberString, NULL); // Переводим строку в число.
            free(currentNumberString); // Освобождаем память, выделенную под подстроку.

            StackElement* pushedElement = createStackElement(currentNumber);
            pushStackElement(numbersStack, pushedElement);

            i = j + 1;
        }
    }

    double result = getStackElementValue(popStackElement(numbersStack)); // Извлекаем число из стека, которое и является результатом.

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

    char* input = (char*)malloc(MAX_STRING_LENGHT * sizeof(char));

    getInput(input);

    if (isInputRight(input)) {
        double result = findResult(input);

        printResult(result);
    } else
        printInputError();

    return 0;
}