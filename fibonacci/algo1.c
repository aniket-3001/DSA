#include <stdio.h>
#include <sys/time.h>
int fib(int n) {
    if (n <= 1)
        return n;
    return (fib(n-1) + fib(n-2)) % 10000;
}
int main() {
    struct timeval start, end;
    unsigned long t;
    int r;
    gettimeofday(&start, 0);
    r = fib(44);
    gettimeofday(&end, 0);
    t = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
    printf("r: %d\n", r);
    printf("elapsed time: %1f milliseconds\n", t/1000.0);
    return 0;
}
