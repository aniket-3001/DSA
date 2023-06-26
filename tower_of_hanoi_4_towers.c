#include <stdio.h>

void move(int n, char src_t[], char dst_t[], char tmp1[], char tmp2[]) {

    if (n == 0)
        return;

    if (n == 1)
        printf("Moving from %s to %s\n", src_t, dst_t);

    else {
        move(n-2, src_t, tmp2, tmp1, dst_t);
        printf("Moving from %s to %s\n", src_t, tmp1);
        printf("Moving from %s to %s\n", src_t, dst_t);
        printf("Moving from %s to %s\n", tmp1, dst_t);
        move(n-2, tmp2, dst_t, src_t, tmp1);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    move(n, "T1", "T4", "T2", "T3");

    return 0;
}