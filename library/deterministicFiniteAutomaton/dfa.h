#ifndef __DFA_H__
#define __DFA_H__

#include "stdbool.h"

typedef struct DFAState DFAState;

typedef struct DFA DFA;

DFA* createDFA(DFAState* initialState);

DFAState* createDFAState(int id, bool isFinal);

void addTransition(DFAState* firstState, char value, DFAState* secondState);

bool isStringCorrect(char* string, DFA* dfa);

void printDFATransitions(DFA* dfa);

void destroyDFAState(DFAState* dfaState);

void destroyDFA(DFA* dfa);

#endif