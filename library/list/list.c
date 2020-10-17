#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct ListElement {
    int value;
    ListElement* next;
};

struct List {
    ListElement* head;
    ListElement* tail;
    int size;
};

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

ListElement* createListElement(int value)
{
    ListElement* listElement = (ListElement*)malloc(sizeof(ListElement));
    listElement->value = value;
    listElement->next = NULL;

    return listElement;
}

ListElement* getListTail(List* list)
{
    return list->tail;
}

ListElement* getListHead(List* list)
{
    return list->head;
}

int getListSize(List* list)
{
    return list->size;
}

bool isListEmpty(List* list)
{
    return getListSize(list) == 0;
}

bool isListPositionExists(int index, List* list)
{
    return (index >= 0) && (index < getListSize(list));
}

bool insertElement(ListElement* value, int position, List* list)
{
    if (!isListPositionExists(position, list) && position != getListSize(list))
        return false;

    if (isListEmpty(list)) {
        list->head = value;
        list->tail = value;
        list->size++;

        return true;
    }

    if (position == 0) {
        value->next = list->head;
        list->head = value;
    } else {
        ListElement* currentElement = list->head;
        for (int i = 0; i < position - 1; ++i)
            currentElement = currentElement->next;

        value->next = currentElement->next;
        currentElement->next = value;

        if (position == getListSize(list))
            list->tail = value;
    }

    list->size++;

    return true;
}

int locateElementPosition(ListElement* value, List* list)
{
    int locatePosition = 0;
    ListElement* currentElement = list->head;

    while (currentElement != value && currentElement != NULL) {
        currentElement = currentElement->next;
        locatePosition++;
    }

    if (currentElement == NULL)
        return -1;

    return locatePosition;
}

ListElement* retrieveElement(int position, List* list)
{
    if (!isListPositionExists(position, list))
        return NULL;

    ListElement* currentElement = list->head;

    for (int i = 0; i < position; ++i)
        currentElement = currentElement->next;

    return currentElement;
}

bool deleteElement(int position, List* list)
{
    if (!isListPositionExists(position, list))
        return false;

    if (position == 0) {
        ListElement* deletedElement = list->head;
        list->head = deletedElement->next;

        if (getListSize(list) == 1)
            list->tail = NULL;

        free(deletedElement);
    } else {
        ListElement* currentElement = list->head;
        for (int i = 0; i < position - 1; ++i)
            currentElement = currentElement->next;

        ListElement* deletedElement = currentElement->next;
        currentElement->next = deletedElement->next;

        if (position + 1 == getListSize(list))
            list->tail = currentElement;

        free(deletedElement);
    }

    list->size--;

    return true;
}

void deleteList(List* list)
{
    int size = getListSize(list);

    for (int i = 0; i < size; ++i)
        deleteElement(0, list);

    free(list);
}

void printList(List* list)
{
    ListElement* currentElement = list->head;
    for (int i = 0; i < getListSize(list); ++i) {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }

    printf("\n");
}
