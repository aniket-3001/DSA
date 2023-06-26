#include <stdio.h>
#include <sys/time.h>

struct retval 
{
    int x;
    int y;
};

struct retval fib(int n) 
{
    struct retval ret, r;

    if (n == 1) 
    {
        r.x = 1; r.y = 0;
        return r;
    }

    ret = fib((n-1) % 10000);
    r.x = (ret.x + ret.y);
    r.y = ret.x;
    return r;
}

int main() {
    int n;
    scanf("%d", &n);
    struct timeval start, end;
    unsigned long t;
    struct retval r;
    gettimeofday(&start, 0);
    r = fib(n);
    gettimeofday(&end, 0);
    t = ((end.tv_sec * 1000000) + end.tv_usec) - ((start.tv_sec * 1000000) + start.tv_usec);
    printf("r: %d\n", r.x);
    printf("elapsed time: %1f milliseconds\n", t/1000.0);
    return 0;
}