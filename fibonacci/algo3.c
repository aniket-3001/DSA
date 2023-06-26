#include <stdio.h>
#include <sys/time.h>

int fib(int n) {
    int a = 0, b= 1, res;

    if (n <= 1)
        return n;

    for (int i = 2; i <= n; i++) {
        res = (a+b) % 10000;
        a = b;
        b = res;
    }

    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    struct timeval start, end;
    unsigned long t;
    int r;
    gettimeofday(&start, 0);
    r = fib(n);
    gettimeofday(&end, 0);
    t = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
    printf("r: %d\n", r);
    printf("elapsed time: %1f milliseconds\n", t/1000.0);
    return 0;
}
