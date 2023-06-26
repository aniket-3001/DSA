#include <stdio.h>
#include <stdlib.h>

struct queue {
    int head;
    int tail;
    int capacity;
    int *arr;
};

struct queue* create_queue(int max_elements) {
    struct queue *Q = malloc(sizeof(struct queue));

    if (Q == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    Q -> head = Q -> tail = 0;
    Q -> capacity = max_elements;
    Q -> arr = malloc(max_elements * sizeof(int));

    return Q;
}

int is_empty(struct queue* Q) {
    if (Q -> head == Q -> tail)
        return 1;
    return 0;
}

int next_head(struct queue* Q) {
    if (Q -> head == Q -> capacity-1)
        return 0;
    return Q -> head+1;
}

int next_tail(struct queue* Q) {
    if (Q -> tail == Q -> capacity-1)
        return 0;
    return Q -> tail+1;
}

int is_full(struct queue* Q) {
    if (next_tail(Q) == Q -> head)
        return 1;
    return 0;
}

void enqueue(struct queue* Q, int val) {
    if (is_full(Q)) {
        printf("overflow");
        exit(0);
    }

    Q -> arr[Q -> tail] = val;
    Q -> tail = next_tail(Q);
}

int dequeue(struct queue* Q) {
    if (is_empty(Q)) {
        printf("underflow");
        exit(0);
    }

    int val = Q -> arr[Q -> head];
    Q -> head = next_head(Q);
    return val;
}

int main() {
    struct queue *Q = create_queue(5);
    enqueue(Q, 1);
    enqueue(Q, 2);
    enqueue(Q, 3);

    while (!is_empty(Q)) {
        int val = dequeue(Q);
        printf("%d ", val);
    }

    free(Q -> arr);
    free(Q);
    return 0;
}
