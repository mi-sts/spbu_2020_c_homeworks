#include <stdio.h>


const ARRAY_SIZE = 100000;

int main()
{
    int m, n;
    int x[ARRAY_SIZE];

    scanf("%d%d", &m, &n);

    for (int i = 0; i < m + n; ++i)
        scanf("%d", &x[i]);

    int t;

    for (int i = m; i < m+n; ++i) { // Сдвиг первого отрезка по всему массиву.
        t = x[i];
        for (int j = i-1; j >= i - m; --j) {
            x[j+1] = x[j];
            x[j] = t;
        }
    }

    for (int i = 0; i < m + n; ++i)
        printf("%d%s", x[i], " ");
}