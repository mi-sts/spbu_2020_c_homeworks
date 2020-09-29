#include <stdio.h>
#include <stdlib.h>

// Функция поиска слагаемых. Принимает аргументами разницу между N и суммой текущего набора, максимальое слагаемое,
// которое можно выбрать на данной итерации, индекс элемента, свободного для записи и ссылка на массив слагаемых.
void findTerms(int difference, int maxTermValue, int findedTermsIndex, int* termsArray)
{
    if (difference == 0) { // Если сумма слагемых равна N.
        for (int i = 0; i < findedTermsIndex; ++i)
            printf("%d%s", termsArray[i], " ");
        printf("%s", "\n");
    } else if (difference > 0) {
        if (difference - maxTermValue >= 0) { // Если есть возможность взять слагаемое со значением maxTermValue.
            termsArray[findedTermsIndex] = maxTermValue;
            findTerms(difference - maxTermValue, maxTermValue, findedTermsIndex + 1, termsArray);
        }
        if (maxTermValue > 1)
            findTerms(difference, maxTermValue - 1, findedTermsIndex, termsArray); // Варианты с меньшим максимальным слагаемым.
    }
}

int main()
{
    int N = 0;
    printf("%s", "Введите число которое хотите разложить на слагаемые: ");
    scanf("%d", &N);

    int* termsArray = (int*) calloc(N, sizeof(int));
    for (int i = 0; i < N; ++i)
        termsArray[i] = 0;

    printf("%s", "Полученные разложения на слагаемые:\n");

    findTerms(N, N, 0, termsArray); // Вызов функции с начальными значениями.

    free(termsArray);

    return 0;
}