#include <stdio.h>

int main()
{
    int n;
    int result = 0;

    scanf("%d", &n);

    if (n > 1) {
        int l;

        for (int i = 2; i < n+1; ++i) {
            if (i % 2 != 0) { // Перебор делителей нечётного i до корня из i.
                for (l = 3; (l * l <= i) && (i % l != 0); l += 2) {};

                if (l * l > i)
                    result++;
            } else if (i == 2) { // Единственное простое чётное i.
                result++;
            }
        }
    }

    printf("%d", result);

    return 0;
}