#include <stdio.h>

int main()
{
    int n = 0;
    int result = 0;

    printf("%s", "Введите число: ");

    scanf("%d", &n);

    if (n > 1) {
        int num;

        for (int nCurrent = 2; nCurrent < n + 1; ++nCurrent) {
            if (nCurrent % 2 != 0) { // Перебор делителей нечётного nCurrent до корня из nCurrent.
                num = 3;

                while (num * num <= nCurrent) {
                    if (nCurrent % num == 0)
                        break;
                    num += 2;
                }

                if (num * num > nCurrent)
                    result++;
            } else if (nCurrent == 2) { // Единственное простое чётное i.
                result++;
            }
        }
    }

    printf("%s%d%s%d", "Количество простых чисел, не превосходящих ", n, ": ", result);

    return 0;
}