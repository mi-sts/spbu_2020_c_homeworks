#include <stdio.h>

#define ARRAY_SIZE 10000

int termsArray[ARRAY_SIZE]; // Массив, использующийся для перебора вариантов.

// Функция поиска слагаемых. Принимает аргументами разницу между N и суммой текущего набора, максимальое слагаемое,
// которое можно выбрать на данной итерации и индекс элемента, свободного для записи.
void findTerms(int difference, int maxTermValue, int findedTermsIndex)
{
    if (difference == 0) { // Если сумма слагемых равна N.
        for (int i = 0; i < findedTermsIndex; ++i)
            printf("%d%s", termsArray[i], " ");
        printf("%s", "\n");
    } else if (difference > 0) {
        if (difference - maxTermValue >= 0) { // Если есть возможность взять слагаемое со значением maxTermValue.
            termsArray[findedTermsIndex] = maxTermValue;
            findTerms(difference - maxTermValue, maxTermValue, findedTermsIndex + 1);
        }
        if (maxTermValue > 1)
            findTerms(difference, maxTermValue - 1, findedTermsIndex); // Варианты с меньшим максимальным слагаемым.
    }
}

int main()
{
    int N = 0;
    printf("%s", "Введите число которое хотите разложить на слагаемые: ");
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
        termsArray[i] = 0;

    printf("%s", "Полученные разложения на слагаемые:\n");

    findTerms(N, N, 0); // Вызов функции с начальными значениями.

    return 0;
}