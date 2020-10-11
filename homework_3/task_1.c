#include "../library/list/list.h"
#include <stdio.h>

int main()
{
    printf("Использование функций структуры \"List\":\n");

    List* list = createList();
    ListElement* listElement1 = createListElement(1);
    ListElement* listElement2 = createListElement(2);
    ListElement* listElement3 = createListElement(3);
    ListElement* listElement4 = createListElement(4);
    ListElement* listElement5 = createListElement(5);

    insertElement(listElement1, 0, list);
    insertElement(listElement2, 1, list);
    insertElement(listElement3, 2, list);
    insertElement(listElement4, 3, list);
    insertElement(listElement5, 4, list);

    printf("Вывод списка с добавленными элементами(1, 2, 3, 4, 5):\n");
    printList(list);

    printf("Длина списка: %d\n", getListSize(list));

    deleteElement(1, list);
    deleteElement(3, list);

    printf("Выведем список после последовательного удаления 1 и 3 элемента списка(нумерация с нуля):\n");
    printList(list);

    printf("Найдём индекс первого вхождения listElement4(значение равно 4) в list: %d\n", locateElementPosition(listElement4, list));

    ListElement* listElement6 = createListElement(6);

    printf("Вставим новый элемент 6 на место 1 позиции и выведем список:\n");
    insertElement(listElement6, 1, list);
    printList(list);

    deleteList(list);

    return 0;
}