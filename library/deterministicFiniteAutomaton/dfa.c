#include "dfa.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transition {
    char symbol;
    DFAState* transitionState;
} Transition;

struct DFAState {
    int id;
    bool isFinal;
    int transitionsSize;
    int transitionAllocationSize;
    Transition** transitions;
};

struct DFA {
    DFAState* initialState;
    DFAState* failState;
};

Transition* createTransition(char symbol, DFAState* transitionState)
{
    Transition* transition = (Transition*)malloc(sizeof(Transition));
    transition->symbol = symbol;
    transition->transitionState = transitionState;

    return transition;
}

void destroyDFAState(DFAState* dfaState)
{
    if (dfaState == NULL)
        return;

    for (int i = 0; i < dfaState->transitionsSize; ++i)
        if (dfaState->transitions[i] != NULL)
            free(dfaState->transitions[i]);
    free(dfaState->transitions);

    free(dfaState);
}

void destroyDFA(DFA* dfa)
{
    destroyDFAState(dfa->initialState);
    destroyDFAState(dfa->failState);
    free(dfa);
}

DFAState* createDFAState(int id, bool isFinal)
{
    DFAState* dfaState = (DFAState*)malloc(sizeof(DFAState));
    dfaState->id = id;
    dfaState->isFinal = isFinal;
    dfaState->transitionsSize = 0;
    dfaState->transitionAllocationSize = 1;
    dfaState->transitions = (Transition**)calloc(1, sizeof(Transition*));

    return dfaState;
}

DFA* createDFA(DFAState* initialState)
{
    DFA* dfa = (DFA*)malloc(sizeof(DFA));
    dfa->initialState = initialState;
    dfa->failState = createDFAState(-1, false);

    return dfa;
}

void reallocTransition(DFAState* dfaState)
{
    dfaState->transitions = (Transition**)realloc(dfaState->transitions, dfaState->transitionAllocationSize * 2 * sizeof(Transition*));
    memset(dfaState->transitions + dfaState->transitionAllocationSize, 0, dfaState->transitionAllocationSize * sizeof(Transition*));
    dfaState->transitionAllocationSize *= 2;
}

void addTransition(DFAState* firstState, char value, DFAState* secondState)
{
    Transition* newTransition = createTransition(value, secondState);
    if (firstState->transitionAllocationSize == firstState->transitionsSize)
        reallocTransition(firstState);

    firstState->transitions[firstState->transitionsSize] = newTransition;
    firstState->transitionsSize++;
}

bool isStringCorrect(char* string, DFA* dfa)
{
    DFAState* currentDfaState = dfa->initialState;
    for (int i = 0; i < strlen(string); ++i) {
        bool isSymbolFound = false;
        for (int j = 0; j < currentDfaState->transitionsSize; ++j) {
            if (currentDfaState->transitions[j]->symbol == string[i]) {
                currentDfaState = currentDfaState->transitions[j]->transitionState;
                isSymbolFound = true;
                break;
            }
        }
        if (!isSymbolFound)
            currentDfaState = dfa->failState;
    }

    return currentDfaState->isFinal;
}

void reallocBoolArray(bool** arrayPointer, int oldSize)
{
    *arrayPointer = (bool*)realloc(*arrayPointer, sizeof(bool) * oldSize * 2);
    memset(*arrayPointer + oldSize * sizeof(bool), 0, oldSize * sizeof(bool));
}

void printDFAStateTransitions(DFAState* dfaState)
{
    for (int i = 0; i < dfaState->transitionsSize; ++i) {
        Transition* transition = dfaState->transitions[i];
        printf("(%d %c) -> %d\n", dfaState->id, transition->symbol, transition->transitionState->id);
    }
}

void printDFATransitionsRecursive(DFAState* currentState, bool* used, int* usedSize)
{
    while (*usedSize <= currentState->id) {
        reallocBoolArray(&used, *usedSize);
        *usedSize *= 2;
    }

    used[currentState->id] = true;
    printDFAStateTransitions(currentState);

    for (int i = 0; i < currentState->transitionsSize; ++i) {
        DFAState* currentTransitionState = currentState->transitions[i]->transitionState;
        if (!used[currentTransitionState->id])
            printDFATransitionsRecursive(currentTransitionState, used, usedSize);
    }
}

void printDFATransitions(DFA* dfa)
{
    int usedSize = 1;
    bool* used = (bool*)calloc(usedSize, sizeof(bool));
    DFAState* initialState = dfa->initialState;
    printDFATransitionsRecursive(initialState, used, &usedSize);

    free(used);
}