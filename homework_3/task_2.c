#include "../library/list/list.h"
#include <stdio.h>

void getInputValues(int* n, int* m)
{
    printf("Всего войнов: ");
    scanf("%d", n);
    printf("Убивают каждого: ");
    scanf("%d", m);
}

List* createCycle(int cycleSize)
{
    List* cycle = createList();

    ListElement* createdElement = NULL;
    for (int i = 0; i < cycleSize; ++i) {
        createdElement = createListElement(i + 1); // Создаём элемент со значением начальной позиции(от единицы).
        insertElement(createdElement, i, cycle);
    }

    return cycle;
}

int findSurvivor(int n, int m, List* cycle)
{
    ListElement* killedElement = getListHead(cycle);
    int killedElementPosition = 0;

    while (getListSize(cycle) != 1) {
        for (int i = 0; i < m - 1; ++i) // Получение каждого m-го элемента.
            killedElement = getNextElement(killedElement, cycle);

        killedElementPosition = locateElementPosition(killedElement, cycle);
        killedElement = getNextElement(killedElement, cycle);
        deleteElement(killedElementPosition, cycle);
    }

    return getElementValue(0, cycle);
}

void printResult(int k)
{
    printf("Выживет воин, который стоял на %d позиции", k);
}

int main()
{
    int n = 0, m = 0, k = 0;
    getInputValues(&n, &m);
    List* cycle = createCycle(n);
    k = findSurvivor(n, m, cycle);
    deleteList(cycle);
    printResult(k);

    return 0;
}
