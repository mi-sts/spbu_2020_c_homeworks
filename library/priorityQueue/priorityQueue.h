#ifndef SPBU_2020_C_HOMEWORKS_PRIORITYQUEUE_H
#define SPBU_2020_C_HOMEWORKS_PRIORITYQUEUE_H

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* createPriorityQueue();

void destroyPriorityQueue(PriorityQueue* priorityQueue);

void enqueue(int value, int priority, PriorityQueue* priorityQueue);

int dequeue(PriorityQueue* priorityQueue);

int getPriorityQueueSize(PriorityQueue* priorityQueue);

void printPriorityQueueElements(PriorityQueue* priorityQueue);

#endif