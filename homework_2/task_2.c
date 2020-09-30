#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Генерация псевдоослучайного числа заданной длины.
int generateRandomNumber(int numberLength)
{
    int randomNumber = 0;

    srand(time(NULL)); // Инициализируем генератор песвдослучайных чисел.

    int leftBorder = (int)pow(10, numberLength - 1); // Минимальное число заданной длины.
    int rightBorder = (int)pow(10, numberLength); // Минимальное число большей длины.

    randomNumber = leftBorder + rand() % (rightBorder - leftBorder);

    return randomNumber;
}

// Заполнение символьного массива input символами пробела.
void clearInput(char* input, int inputLength)
{
    for (int i = 0; i < inputLength; ++i)
        input[i] = ' ';
}

// Взаимодействие с пользователем при запуске приложения.
void printGameMenu(char* input, int inputLength)
{
    printf("================================\n");
    printf("%s", "Игра \"Быки и коровы\"\nВведите \"s\" чтобы начать новую игру\n");
    printf("%s", "(Чтобы закончить игру вы можете ввести \"e\")\n");
    printf("================================\n");
    clearInput(input, inputLength);
    scanf("%s", input);

    while (!((input[0] == 's' || input[0] == 'e') && strlen(input) == 1)) {
        printf("Неверный ввод!\n");
        clearInput(input, inputLength);
        scanf("%s", input);
    }
}

// Проверка числа на длину.
bool isNumberInRange(int numberLength, int number)
{
    int leftNumber = (int)pow(10, numberLength - 1); // Минимальное число заданной длины.
    int rightNumber = (int)pow(10, numberLength) + 1; // Максимальное число заданной длины.

    return (number >= leftNumber) && (number <= rightNumber);
}

// Считывание числа, загаданного игроком.
int scanPlayerNumber(int* playerNumber, int numberLength)
{
    printf("Введите загаданное число: ");
    scanf("%d", playerNumber);

    while (!isNumberInRange(numberLength, *playerNumber)) {
        printf("Число должно быть длины %d!\n", numberLength);
        printf("Введите загаданное число: ");
        scanf("%d", playerNumber);
    }
}

// Взаимодействие с пользователемм при запуске новой игровой сессии.
void startNewGame(int* numberLength, bool* isNewGame, int* secretNumber)
{
    printf("Введите длину отгадываемого числа: ");
    scanf("%d", numberLength);
    *secretNumber = generateRandomNumber(*numberLength);
    printf("%d", *secretNumber);
    *isNewGame = false;
}

// Разделить число на массив его разрядов.
int* shareNumber(int number, int numberLength)
{
    int* sharedPlayerNumber = (int*)calloc(numberLength, sizeof(int));
    for (int i = 0; i < numberLength; ++i) {
        //Получение разрядов числа от старшего к младшему.
        int numberDigit = number % (int)pow(10, numberLength - i) / (int)pow(10, numberLength - i - 1);
        sharedPlayerNumber[i] = numberDigit;
    }

    return sharedPlayerNumber;
}

// Найти количество быков. Последие два аргумента показывают, какие разряды были просмотрены(в этом случае true).
int findBulls(int* sharedPlayerNumber, int* sharedSecretNumber, int numberLength, bool* isPlayerPositionsChecked, bool* isSecretPositionsChecked)
{
    int bulls = 0;

    for (int position = 0; position < numberLength; ++position) {
        isPlayerPositionsChecked[position] = false;
        isSecretPositionsChecked[position] = false;
    }

    for (int position = 0; position < numberLength; ++position)
        if (sharedPlayerNumber[position] == sharedSecretNumber[position]) {
            bulls++;
            isPlayerPositionsChecked[position] = true;
            isSecretPositionsChecked[position] = true;
        }

    return bulls;
}

// Найти количество коров. Последие два аргумента показывают, какие разряды были просмотрены(в этом случае true).
int findCows(int* sharedPlayerNumber, int* sharedSecretNumber, int numberLength, bool* isPlayerPositionsChecked, bool* isSecretPositionsChecked)
{
    int cows = 0;

    for (int playerPosition = 0; playerPosition < numberLength; ++playerPosition)
        for (int secretPosition = 0; secretPosition < numberLength; ++secretPosition) {
            if (isPlayerPositionsChecked[playerPosition] || isSecretPositionsChecked[secretPosition])
                continue;

            if (sharedPlayerNumber[playerPosition] == sharedSecretNumber[secretPosition]) {
                cows++;
                isPlayerPositionsChecked[playerPosition] = true;
                isSecretPositionsChecked[secretPosition] = true;
            }
        }

    return cows;
}

// Вывести результат попытки угадать число.
void printResultOfAttemt(int cows, int bulls)
{
    printf("Результат: %d коров и %d быков.\n", cows, bulls);
}

// Проверка на победу игрока.
void winCheck(int bulls, int numberLength, bool* isNewGame, char* input, int inputLength)
{
    if (bulls == numberLength) {
        printf("Поздравляем, вы угадали число!!!\n\n\n");
        printGameMenu(input, inputLength); // В случае выигрыша вызываем игровое меню.
        *isNewGame = true;
    }
}

// Проверка input на команду выхода из приложения
bool isGameEnded(char* input)
{
    return input[0] == 'e';
}

// Найти результат попытки угадать число
void findResultOfAttempt(int* cows, int* bulls, int playerNumber, int secretNumber, int numberLength)
{
    bool* isPlayerPositionChecked = (bool*)calloc(numberLength, sizeof(bool)); // Массивы, показывающие разряды, которые были просмотрены.
    bool* isSecretPositionChecked = (bool*)calloc(numberLength, sizeof(bool));
    int* sharedPlayerNumber = shareNumber(playerNumber, numberLength); // Массивы с разрядами чисел.
    int* sharedSecretNumber = shareNumber(secretNumber, numberLength);

    *bulls = findBulls(sharedPlayerNumber, sharedSecretNumber, numberLength, isPlayerPositionChecked, isSecretPositionChecked);
    *cows = findCows(sharedPlayerNumber, sharedSecretNumber, numberLength, isPlayerPositionChecked, isSecretPositionChecked);

    free(sharedSecretNumber);
    free(sharedPlayerNumber);
    free(isPlayerPositionChecked);
    free(isSecretPositionChecked);
}

int main()
{
    const int INPUT_LENGTH = 30; // Максимальныая длина считываемой строки

    char* input = (char*)calloc(INPUT_LENGTH, sizeof(char));
    clearInput(input, INPUT_LENGTH); // Инициализация input.

    bool isNewGame = true;
    int numberLength = 0;
    int playerNumber = 0;
    int secretNumber = 0;
    int bulls = 0;
    int cows = 0;

    printGameMenu(input, INPUT_LENGTH); // Вывод меню при запуске приложения.

    while (!isGameEnded(input)) {
        if (isNewGame) // Инициализация в случае новой игровой сессии.
            startNewGame(&numberLength, &isNewGame, &secretNumber);

        scanPlayerNumber(&playerNumber, numberLength); // Считывание загаданного игроком числа.

        findResultOfAttempt(&cows, &bulls, playerNumber, secretNumber, numberLength); // Сравнение чисел.
        printResultOfAttemt(cows, bulls); // Вывод резульата.

        winCheck(bulls, numberLength, &isNewGame, input, INPUT_LENGTH); // Проверка выигрыша игрока.
    }

    free(input);

    return 0;
}