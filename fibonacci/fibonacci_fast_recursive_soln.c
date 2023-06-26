#include <stdio.h>

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
        
    ret = fib(n-1);
    r.x = (ret.x + ret.y);
    r.y = ret.x;
    return r;
}

int main()
{
    int n;
    scanf("%d", &n);
    struct retval ans = fib(n);
    printf("%d", ans.x);
    return 0;
}
