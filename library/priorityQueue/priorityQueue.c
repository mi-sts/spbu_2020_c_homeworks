#include "priorityQueue.h"
#include "../list/list.h"
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    List* values;
    List* priorities;
};

PriorityQueue* createPriorityQueue()
{
    PriorityQueue* priorityQueue = (PriorityQueue*)malloc(sizeof(PriorityQueue));

    priorityQueue->values = createList();
    priorityQueue->priorities = createList();

    return priorityQueue;
}

void destroyPriorityQueue(PriorityQueue* priorityQueue)
{
    if (priorityQueue == NULL)
        return;

    deleteList(priorityQueue->values);
    deleteList(priorityQueue->priorities);

    free(priorityQueue);
}

int getPriorityQueueSize(PriorityQueue* priorityQueue)
{
    return getListSize(priorityQueue->values);
}

int getPriorityQueueElementPriority(PriorityQueue* priorityQueue, int index)
{
    return getElementValue(index, priorityQueue->priorities);
}

int getPriorityQueueElementValue(PriorityQueue* priorityQueue, int index)
{
    return getElementValue(index, priorityQueue->values);
}

int findElementIndex(int priority, PriorityQueue* priorityQueue)
{
    int index = 0;

    for (index = 0; index < getPriorityQueueSize(priorityQueue); ++index) {
        if (getPriorityQueueElementPriority(priorityQueue, index) < priority)
            break;
    }

    return index;
}

void enqueue(int value, int priority, PriorityQueue* priorityQueue)
{
    if (priorityQueue == NULL)
        return;

    int index = findElementIndex(priority, priorityQueue);

    ListElement* priorityElement = createListElement(priority);
    ListElement* valueElement = createListElement(value);

    insertElement(priorityElement, index, priorityQueue->priorities);
    insertElement(valueElement, index, priorityQueue->values);
}

int dequeue(PriorityQueue* priorityQueue)
{
    if (priorityQueue == NULL)
        return 0;

    if (getPriorityQueueSize(priorityQueue) == 0)
        return 0;

    int value = getElementValue(0, priorityQueue->values);
    deleteElement(0, priorityQueue->values);
    deleteElement(0, priorityQueue->priorities);

    return value;
}

void printPriorityQueueElements(PriorityQueue* priorityQueue)
{
    for (int i = 0; i < getPriorityQueueSize(priorityQueue); ++i)
        printf("%d - %d\n", getPriorityQueueElementValue(priorityQueue, i), getPriorityQueueElementPriority(priorityQueue, i));

    printf("\n");
}
