#include "../library/commonUtils/numericOperations.h"
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

    int* numberDigits = (int*)calloc(numberLength, sizeof(int)); // Массив с имеющимися разрядами числа.
    int digitIndex = 0;

    int currentDigit = 0; // Текущий разряд псевдослучайного числа.

    currentDigit = (rand() % 9) + 1; // Добавление старшего ненулевого разряда.
    numberDigits[0] = currentDigit;
    randomNumber = currentDigit;
    digitIndex++;

    for (int i = 1; i < numberLength; ++i) { // Генерация псвдослучайного числа по разрядам.
        bool isDigitHave = false; // Находится ли эта цифра уже в числе.

        do {
            isDigitHave = false;

            currentDigit = rand() % 10;

            for (int j = 0; j < digitIndex; j++) // Проверка на наличие такой же цифры.
                if (currentDigit == numberDigits[j]) {
                    isDigitHave = true;
                    break;
                }
        } while (isDigitHave);

        numberDigits[digitIndex] = currentDigit;
        digitIndex++;
        randomNumber = randomNumber * 10 + currentDigit; // Добавление цифры в конец числа.
    }

    free(numberDigits);

    return randomNumber;
}

// Проверка input на команду выхода из приложения.
bool isGameEnded(char* input)
{
    return input[0] == 'e';
}

// Проверка input на комнаду начала новой игры.
bool isGameStarted(char* input)
{
    return input[0] == 's';
}

// Взаимодействие с пользователем при запуске приложения.
void printGameMenu(char* input, int inputLength)
{
    printf("================================\n");
    printf("%s", "Игра \"Быки и коровы\"\nВведите \"s\" чтобы начать новую игру\n");
    printf("%s", "(Чтобы закончить игру вы можете ввести \"e\")\n");
    printf("================================\n");
    scanf("%s", input);

    while (!(strlen(input) == 1 && (isGameStarted(input) || isGameEnded(input)))) {
        printf("Неверный ввод!\n");
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
        printf("Число должно быть длины %d и не должно иметь незначащих нулей!\n", numberLength);
        printf("Введите загаданное число: ");
        scanf("%d", playerNumber);
    }
}

// Взаимодействие с пользователемм при запуске новой игровой сессии.
void startNewGame(int* numberLength, bool* isNewGame, int* secretNumber)
{
    printf("Введите длину отгадываемого числа: ");
    scanf("%d", numberLength);

    while (*numberLength <= 0) {
        printf("Длина числа - натуральное число!\n");
        printf("Введите длину отгадываемого числа: ");
        scanf("%d", numberLength);
    }

    printf("Сгенерированное число - длины %d, не имеющее незначащих нулей\n", *numberLength);

    *secretNumber = generateRandomNumber(*numberLength);
    *isNewGame = false;
}

// Разделить число на массив его разрядов.
int* shareNumber(int number, int numberLength)
{
    int* sharedNumber = (int*)calloc(numberLength, sizeof(int));
    for (int i = 0; i < numberLength; ++i) {
        //Получение разрядов числа от старшего к младшему.
        int numberDigit = number % (int)pow(10, numberLength - i) / (int)pow(10, numberLength - i - 1);
        sharedNumber[i] = numberDigit;
    }

    return sharedNumber;
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

// Найти результат попытки угадать число
void findResultOfAttempt(int* cows, int* bulls, int playerNumber, int secretNumber, int numberLength)
{
    int* sharedPlayerNumber = shareNumber(playerNumber, numberLength); // Массивы с разрядами чисел.
    int* sharedSecretNumber = shareNumber(secretNumber, numberLength);

    *bulls = 0;
    *cows = 0;

    int* playerDigitsNumber = (int*)calloc(10, sizeof(int)); // Массивы, показывающие количество цифр в числах(элемент n показывает, сколько цифр n встречалась в числе).
    int* secretDigitsNumber = (int*)calloc(10, sizeof(int));

    for (int i = 0; i < numberLength; ++i) {
        playerDigitsNumber[sharedPlayerNumber[i]]++; // Инкерментация количества соотвествующих цифр.
        secretDigitsNumber[sharedSecretNumber[i]]++;

        if (sharedPlayerNumber[i] == sharedSecretNumber[i]) // Подсчёт быков.
            (*bulls)++;
    }

    int cowsWithBulls = 0;

    for (int i = 0; i < 10; ++i)
        cowsWithBulls += min(playerDigitsNumber[i], secretDigitsNumber[i]); // Число коров c быками(минимум из количества соответсвующих цифр)

    *cows = cowsWithBulls - *bulls;

    free(sharedSecretNumber);
    free(sharedPlayerNumber);
    free(playerDigitsNumber);
    free(secretDigitsNumber);
}

int main()
{
    const int INPUT_LENGTH = 30; // Максимальныая длина считываемой строки.

    char* input = (char*)calloc(INPUT_LENGTH, sizeof(char));

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
