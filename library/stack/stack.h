#ifndef PRACTICE_STACK_H
#define PRACTICE_STACK_H
#include <stdbool.h>

struct Stack typedef Stack;

struct StackElement typedef StackElement;

StackElement* popStackElement(struct Stack* stack);

void pushStackElement(struct Stack* stack, StackElement* newElement);

StackElement* createStackElement(double value);

Stack* createStack();

int sizeOfStack(Stack* stack);

bool isEmpty(Stack* stack);

void deleteStackElement(StackElement* deletingElement);

void deleteStack(Stack* deletingStack);

double getStackElementValue(StackElement* stackElement);

void printStack(Stack* stack);

#endif
