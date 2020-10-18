#ifndef SPBU_2020_C_HOMEWORKS_LIST_H
#define SPBU_2020_C_HOMEWORKS_LIST_H
#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;

List* createList();

ListElement* createListElement();

ListElement* getListTail(List* list);

ListElement* getListHead(List* list);

bool isListPositionExists(int index, List* list);

bool isListEmpty(List* list);

int getListSize(List* list);

bool insertElement(ListElement* value, int position, List* list);

int locateElementPosition(ListElement* value, List* list);

ListElement* retrieveElement(int position, List* list);

bool deleteElement(int position, List* list);

void deleteList(List* list);

void printList(List* list);

ListElement* getNextCycleElement(ListElement* previousElement, List* list);

int getElementValue(int position, List* list);

#endif
