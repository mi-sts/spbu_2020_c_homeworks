#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const ARRAY_SIZE = 10000;

int main()
{
    char s1[ARRAY_SIZE];
    char s2[ARRAY_SIZE];
    int containNumber = 0;

    scanf("%s", s1);
    scanf("%s", s2);

    for (int i = 0; i <= strlen(s1) - strlen(s2); ++i) { // От каждого элемента s1 идёт сравнение с s2.
        bool isContain = true;

        for (int j = 0; j < strlen(s2); ++j)
            if (s2[j] != s1[j + i]) {
                isContain = false;
                break;
            }

        if (isContain)
            containNumber++;
    }

    printf("%d", containNumber);

    return 0;
}