#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int delete_min() {
    int min_val = INT_MAX;
    if (is_empty()) {
        return min_val;
    }
    int popped = pop();
    if (popped < min_val) {
        min_val = popped;
    }
    int remaining_min = delete_min();
    if (popped != min_val) {
        push(popped);
    }
    if (remaining_min < min_val) {
        return remaining_min;
    } else {
        return min_val;
    }
}
