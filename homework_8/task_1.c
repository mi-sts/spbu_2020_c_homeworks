#include "../library/commonUtils/inputFunctions.h"
#include "../library/deterministicFiniteAutomaton/dfa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addTransitionsForDigits(DFAState* startTransition, DFAState* endTransition)
{
    for (int i = (int)'0'; i <= (int)'9'; ++i) {
        char symbol = (char)i;
        addTransition(startTransition, symbol, endTransition);
    }
}

void addStates(DFAState* initialState, DFAState*** createdStatesPointer, int* createdStatesCount)
{
    const int STATES_SIZE = 7;

    DFAState* numberSignState = createDFAState(1, false);
    DFAState* integerPartState = createDFAState(2, true);
    DFAState* pointState = createDFAState(3, false);
    DFAState* floatPartState = createDFAState(4, true);
    DFAState* exponentSymbolState = createDFAState(5, false);
    DFAState* orderSignState = createDFAState(6, false);
    DFAState* orderValueState = createDFAState(7, true);

    addTransition(initialState, '+', numberSignState); // Знаки числа.
    addTransition(initialState, '-', numberSignState);
    addTransitionsForDigits(numberSignState, integerPartState); // Переход со знаком.
    addTransitionsForDigits(initialState, integerPartState); // Переход без знака.
    addTransitionsForDigits(integerPartState, integerPartState);

    addTransition(integerPartState, '.', pointState); // Запись с точкой.
    addTransitionsForDigits(pointState, floatPartState);
    addTransitionsForDigits(floatPartState, floatPartState);

    addTransition(floatPartState, 'E', exponentSymbolState); // Экспоненциаьная форма.
    addTransition(exponentSymbolState, '+', orderSignState); // Знаки порядка.
    addTransition(exponentSymbolState, '-', orderSignState);
    addTransitionsForDigits(orderSignState, orderValueState); // Переход со знаком.
    addTransitionsForDigits(exponentSymbolState, orderValueState); // Переход без знака.
    addTransitionsForDigits(orderValueState, orderValueState);

    *createdStatesPointer = (DFAState**)malloc(7 * sizeof(DFAState*));
    (*createdStatesPointer)[0] = numberSignState;
    (*createdStatesPointer)[1] = integerPartState;
    (*createdStatesPointer)[2] = pointState;
    (*createdStatesPointer)[3] = floatPartState;
    (*createdStatesPointer)[4] = exponentSymbolState;
    (*createdStatesPointer)[5] = orderSignState;
    (*createdStatesPointer)[6] = orderValueState;

    *createdStatesCount = STATES_SIZE;
}

void destroyStates(DFAState** createdStates, int createdStatesCount)
{
    for (int i = 0; i < createdStatesCount; ++i)
        destroyDFAState(createdStates[i]);
}

bool isFloatNumber(char* string)
{
    DFAState* initialState = createDFAState(0, false);
    DFA* dfa = createDFA(initialState);

    DFAState** createdStates = NULL;
    int createdStatesCount = 0;
    addStates(initialState, &createdStates, &createdStatesCount);

    bool isFloatNumber = isStringCorrect(string, dfa);

    destroyDFA(dfa);
    destroyStates(createdStates, createdStatesCount);
    free(createdStates);

    return isFloatNumber;
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