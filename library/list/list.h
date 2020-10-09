#include <stdbool.h>
#ifndef SPBU_2020_C_HOMEWORKS_LIST_H
#define SPBU_2020_C_HOMEWORKS_LIST_H

typedef struct List List;
typedef struct ListElement ListElement;

List* createList();

ListElement* createListElement();

ListElement* tail(List* list);

ListElement* head(List* list);

bool listPositionExists(int index, List* list);

bool isListEmpty(List* list);

int listSize(List* list);

bool insert(ListElement* value, int position, List* list);

int locate(ListElement* value, List* list);

ListElement* retrieve(int position, List* list);

bool delete(int postion, List* list);

void deleteList(List* list);

void printList(List* list);

#endif
