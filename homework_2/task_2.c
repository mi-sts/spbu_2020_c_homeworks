#include "../library/commonUtils/numericOperations.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Проверка на налчичие цифры currentDigit в массиве numberDigits.
bool isDigitHave(int* numberDigits, int currentDigit, int currentNumberLength)
{
    for (int i = 0; i < currentNumberLength; ++i)
        if (currentDigit == numberDigits[i])
            return true;

    return false;
}

// Генерация псевдоослучайного числа заданной длины.
long generateRandomNumber(int numberLength)
{
    srand(time(NULL)); // Инициализируем генератор песвдослучайных чисел.

    int* numberDigits = (int*)calloc(numberLength, sizeof(int)); // Массив с имеющимися разрядами числа.
    int digitIndex = 1;

    int currentDigit = (rand() % 9) + 1; // Добавление старшего ненулевого разряда.
    numberDigits[0] = currentDigit;
    long randomNumber = currentDigit;

    for (int i = 1; i < numberLength; ++i) { // Генерация псвдослучайного числа по разрядам.
        do {
            currentDigit = rand() % 10;
        } while (isDigitHave(numberDigits, currentDigit, digitIndex));

        numberDigits[digitIndex] = currentDigit;
        digitIndex++;
        randomNumber = randomNumber * 10 + currentDigit; // Добавление цифры в конец числа.
    }

    free(numberDigits);

    return randomNumber;
}

// Проверка input на команды старта и окончания игры(0 - старт, 1 - окончание). В случае нахождения несуществующей команды возвращает 3.
int gameState(char* input)
{
    if (input[0] == 's')
        return 1;
    if (input[0] == 'e')
        return 0;

    return 3;
}

// Взаимодействие с пользователем при запуске приложения.
void printGameMenu(char* input, int inputLength)
{
    printf("================================\n");
    printf("%s", "Игра \"Быки и коровы\"\nВведите \"s\" чтобы начать новую игру\n");
    printf("%s", "(Чтобы закончить игру вы можете ввести \"e\")\n");
    printf("================================\n");
    scanf("%s", input);

    while (!(strlen(input) == 1 && gameState(input) != 3)) {
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
void scanPlayerNumber(long* playerNumber, int numberLength)
{
    printf("Введите загаданное число: ");
    scanf("%ld", playerNumber);

    while (!isNumberInRange(numberLength, *playerNumber)) {
        printf("Число должно быть длины %d и не должно иметь незначащих нулей!\n", numberLength);
        printf("Введите загаданное число: ");
        scanf("%ld", playerNumber);
    }
}

// Взаимодействие с пользователемм при запуске новой игровой сессии.
void startNewGame(int* numberLength, bool* isNewGame, long* secretNumber)
{
    printf("Введите длину отгадываемого числа(1..10): ");
    scanf("%d", numberLength);

    while (*numberLength <= 0 || *numberLength > 10) {
        printf("Длина числа - натуральное число(1..10)!\n");
        printf("Введите длину отгадываемого числа: ");
        scanf("%d", numberLength);
    }

    printf("Сгенерированное число - длины %d, не имеющее незначащих нулей\n", *numberLength);

    *secretNumber = generateRandomNumber(*numberLength);
    *isNewGame = false;
}

// Разделить число на массив его разрядов.
int* shareNumber(long number, int numberLength)
{
    int* sharedNumber = (int*)calloc(numberLength, sizeof(int));
    for (int i = numberLength - 1; i >= 0; --i) {
        //Получение разрядов числа от старшего к младшему.
        int numberDigit = number % 10;
        sharedNumber[i] = numberDigit;
        number /= 10;
    }

    return sharedNumber;
}

// Вывести результат попытки угадать число.
void printResultOfAttemt(int cows, int bulls)
{
    printf("Результат: %d коров и %d быков.\n", cows, bulls);
}

// Проверка на победу игрока.
bool isWin(int bulls, int numberLength)
{
    if (bulls == numberLength)
        return true;

    return false;
}

// Действия в случае выигрыша.
void winInitialization(char* input, int inputLength, bool* isNewGame)
{
    printf("Поздравляем, вы угадали число!!!\n\n\n");
    printGameMenu(input, inputLength); // В случае выигрыша вызываем игровое меню.
    *isNewGame = true;
}

// Найти результат попытки угадать число
void findResultOfAttempt(int* cows, int* bulls, long playerNumber, long secretNumber, int numberLength)
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
    long playerNumber = 0;
    long secretNumber = 0;
    int bulls = 0;
    int cows = 0;

    printGameMenu(input, INPUT_LENGTH); // Вывод меню при запуске приложения.

    while (gameState(input)) {
        if (isNewGame) // Инициализация в случае новой игровой сессии.
            startNewGame(&numberLength, &isNewGame, &secretNumber);

        scanPlayerNumber(&playerNumber, numberLength); // Считывание загаданного игроком числа.

        findResultOfAttempt(&cows, &bulls, playerNumber, secretNumber, numberLength); // Сравнение чисел.
        printResultOfAttemt(cows, bulls); // Вывод резульата.

        if (isWin(bulls, numberLength)) { // Проверка выигрыша игрока
            winInitialization(input, INPUT_LENGTH, &isNewGame);
        }
    }

    free(input);

    return 0;
}
