#include "../library/binarySearchTree/AVLTree.h"
#include <stdio.h>
#include <stdlib.h>

void printUserInterface()
{
    printf("Доступны следующие операции для AVL:\n");
    printf("1 - Добавить значение целого типа в множество.\n");
    printf("2 - Удалить значение целого типа.\n");
    printf("3 - Проверить значение целого типа на принадлженость множетсву.\n");
    printf("4 - Вывести текущие элементы множества в возрастающем, убывающем и прямом порядках.\n");
    printf("0 - Завершить работу\n");
}

void printPreInputSelectionInformation()
{
    printf("Для осуществления операции введите соотвествующий ей номер.\n");
}

void printInputSelectionError()
{
    printf("Неккоректный ввод, нужно ввести номер операции!\n");
}

bool getInputSelection(char* input)
{
    char currentChar = (char)getchar();
    while (currentChar == '\n')
        currentChar = (char)getchar();

    input[0] = currentChar;

    currentChar = (char)getchar();

    if (currentChar != '\n') { // Если строка состоит не из одного символа.
        while (currentChar != '\n') // Считываем текущую строку.
            currentChar = (char)getchar();

        printInputSelectionError();
        return false;
    }

    return true;
}

void printPreInputNumberInformation()
{
    printf("Введите целочисленное значение: ");
}

void printInputNumberError()
{
    printf("Неккоректный ввод! Введите целочисленное значение: ");
}

bool getInputNumber(long long* number)
{
    int inputResult = 0; // Результат ввода(1 - верно, иначе неверно).
    inputResult = scanf("%lld", number);

    if (inputResult != 1) {
        fflush(stdin); // Очищаем поток ввода.
        printInputNumberError();
        return false;
    }

    return true;
}

void getCorrectInputNumber(long long* number)
{
    bool isInputNumberCorrect = false; // Верно ли введёно целочисленное значение.

    while (!isInputNumberCorrect)
        isInputNumberCorrect = getInputNumber(number);
}

void getCorrectInputSelection(char* input)
{
    bool isInputSelectionCorrect = false; // Верно ли введён символ операции.

    while (!isInputSelectionCorrect)
        isInputSelectionCorrect = getInputSelection(input);
}

void printIsExistElementInformation(bool isExist)
{
    if (isExist)
        printf("Содержится.\n");
    else
        printf("Не содержится.\n");
}

int main()
{
    AVLTree* binarySearchAVLTree = createTree();
    bool isRun = true;
    bool isExist = false;

    char* input = calloc(2, sizeof(char));
    long long number = 0;

    printUserInterface();

    while (isRun) {
        printPreInputSelectionInformation();
        getCorrectInputSelection(input);

        switch (input[0]) {
        case '1': {
            printPreInputNumberInformation();
            getCorrectInputNumber(&number);
            addValueInAVL(binarySearchAVLTree, number);
            break;
        }
        case '2': {
            printPreInputNumberInformation();
            getCorrectInputNumber(&number);
            removeValueFromAVL(binarySearchAVLTree, number);
            break;
        }
        case '3': {
            printPreInputNumberInformation();
            getCorrectInputNumber(&number);
            isExist = isExists(binarySearchAVLTree, number);
            printIsExistElementInformation(isExist);
            break;
        }
        case '4': {
            printTreeInAscendingOrder(binarySearchAVLTree);
            printTreeInDescendingOrder(binarySearchAVLTree);
            printTreeInDirectOrder(binarySearchAVLTree);
            break;
        }
        case '0': {
            isRun = false;
            break;
        }
        default: {
            printInputSelectionError();
            break;
        }
        }
    }

    removeTree(binarySearchAVLTree);
    free(input);

    return 0;
}
