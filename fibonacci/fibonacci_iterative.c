#include <stdio.h>

int main()
{
    int n, a = 0, b = 1, res;
    scanf("%d", &n);

    if (n == 0)
        res = 0;
    else if (n == 1)
        res = 1;
    else {
        for (int i = 2; i <= n; i++) {
            res = a + b;
            a = b;
            b = res;
        }
    }
    printf("%d", res);

    return 0;
}
