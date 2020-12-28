#include "../library/priorityQueue/priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

void printElements(PriorityQueue* priorityQueue)
{
    printf("Элементы очереди:\n");
    printPriorityQueueElements(priorityQueue);
}

void showAdding(PriorityQueue* priorityQueue)
{
    int insertElementValue = 0;
    int insetElementPriority = 0;
    printf("Введите число для добавления в приоритетную очередь и его приоритет: ");
    scanf("%d %d", &insertElementValue, &insetElementPriority);
    enqueue(insertElementValue, insetElementPriority, priorityQueue);
    printElements(priorityQueue);
}

void showGetting(PriorityQueue* priorityQueue)
{
    printf("Извлечённое значение: %d\n", dequeue(priorityQueue));
    printElements(priorityQueue);
}

int main()
{
    PriorityQueue* priorityQueue = createPriorityQueue();
    printf("Демонстрация работы приритетной очереди.\n");

    showAdding(priorityQueue);
    showAdding(priorityQueue);
    showGetting(priorityQueue);
    showAdding(priorityQueue);
    showGetting(priorityQueue);
    showAdding(priorityQueue);
    showAdding(priorityQueue);
    showGetting(priorityQueue);

    destroyPriorityQueue(priorityQueue);

    return 0;
}