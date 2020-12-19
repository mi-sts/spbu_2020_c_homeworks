#include "../library/deterministicFiniteAutomaton/dfa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTransitionsForDigits(DFAState* startTransition, DFAState* endTransition)
{
    for (char i = '0'; i <= '9'; ++i)
        addTransition(startTransition, i, endTransition);
}

bool isFloatNumber(char* string)
{
    DFAState* initialState = createDFAState(0, false);
    DFA* dfa = createDFA(initialState);

    DFAState* firstState = createDFAState(1, false);
    DFAState* secondState = createDFAState(2, false);
    DFAState* thirdState = createDFAState(3, false);
    DFAState* fourthState = createDFAState(4, false);
    DFAState* fifthState = createDFAState(5, false);
    DFAState* sixthState = createDFAState(6, false);
    DFAState* seventhState = createDFAState(7, true);

    addTransition(initialState, '+', firstState);
    addTransition(initialState, '-', firstState);
    addTransitionsForDigits(firstState, secondState);
    addTransitionsForDigits(secondState, secondState);
    addTransition(secondState, '.', thirdState);
    addTransitionsForDigits(thirdState, fourthState);
    addTransitionsForDigits(fourthState, fourthState);
    addTransition(fourthState, 'E', fifthState);
    addTransition(fifthState, '+', sixthState);
    addTransition(fifthState, '-', sixthState);
    addTransitionsForDigits(sixthState, seventhState);
    addTransitionsForDigits(seventhState, seventhState);

    bool isFloatNumber = isStringCorrect(string, dfa);

    destroyDFA(dfa);
    destroyDFAState(firstState);
    destroyDFAState(secondState);
    destroyDFAState(thirdState);
    destroyDFAState(fourthState);
    destroyDFAState(fifthState);
    destroyDFAState(sixthState);
    destroyDFAState(seventhState);

    return isFloatNumber;
}

char* getInputString()
{
    char* inputString = (char*)calloc(2, sizeof(char));
    int currentLength = 0;
    int lengthBorder = 1;

    char currentSymbol = (char)getchar();

    while (currentSymbol != '\n') {
        inputString[currentLength] = currentSymbol;
        currentLength++;

        if (currentLength == lengthBorder) {
            lengthBorder *= 2;
            inputString = (char*)realloc(inputString, (lengthBorder + 1) * sizeof(char));
            memset(inputString + currentLength * sizeof(char), 0, (lengthBorder - currentLength) * sizeof(char));
        }

        currentSymbol = (char)getchar();
    }

    return inputString;
}

void printResultInfo(bool isFloat)
{
    if (isFloat)
        printf("Введённая последовательность символов является вещественным числом.");
    else
        printf("Введённая последовательность символов не является вещественным числом.");
}

int main()
{
    char* inputString = getInputString();

    bool isFloat = isFloatNumber(inputString);

    printResultInfo(isFloat);

    free(inputString);

    return 0;
}