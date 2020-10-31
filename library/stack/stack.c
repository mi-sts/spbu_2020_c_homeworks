#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

struct StackElement {
    double value;
    StackElement* next;
};

struct Stack {
    StackElement* head;
    int stackSize;
};

StackElement* popStackElement(Stack* stack)
{
    if (isEmpty(stack))
        return NULL;

    StackElement* popElement = stack->head;
    stack->head = stack->head->next;
    popElement->next = NULL;
    stack->stackSize--;

    return popElement;
}

void pushStackElement(Stack* stack, StackElement* newElement)
{
    newElement->next = stack->head;
    stack->head = newElement;
    stack->stackSize++;
}

StackElement* createStackElement(double value)
{
    StackElement* stackElement = (StackElement*)malloc(sizeof(struct StackElement));
    stackElement->value = value;
    stackElement->next = NULL;

    return stackElement;
}

Stack* createStack()
{
    Stack* stack = malloc(sizeof(Stack));
    stack->head = NULL;
    stack->stackSize = 0;

    return stack;
}

int sizeOfStack(Stack* stack)
{
    return stack->stackSize;
}

bool isEmpty(Stack* stack)
{
    return sizeOfStack(stack) == 0;
}

void deleteStackElement(StackElement* deletingElement)
{
    free(deletingElement);
}

void deleteStack(Stack* deletingStack)
{
    StackElement* deletingStackElement = deletingStack->head;
    while (!isEmpty(deletingStack)) {
        StackElement* deletedElement = popStackElement(deletingStack);
        deleteStackElement(deletedElement);
    }

    free(deletingStack);
}

double getStackElementValue(StackElement* stackElement)
{
    return stackElement->value;
}

void printStack(Stack* stack)
{
    StackElement* currentElement = stack->head;
    double currentElementValue = 0;

    while (currentElement != NULL) {
        currentElementValue = getStackElementValue(currentElement);
        printf("%lf ", currentElementValue);
        currentElement = currentElement->next;
    }

    printf("\n");
}
