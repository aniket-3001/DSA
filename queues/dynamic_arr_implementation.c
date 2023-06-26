#include <stdio.h>
#include <stdlib.h>

void insert(int** arr, int* curr_size, int* capacity, int element) {
    if (*curr_size == *capacity) {
        *capacity *= 2;
        int* new_arr = realloc(*arr, *capacity * sizeof(int));
        if (new_arr == NULL) {
            printf("Error: Memory allocation failed!");
            exit(1);
        }
        *arr = new_arr;
    }
    (*arr)[*curr_size] = element;
    (*curr_size)++;
}

void delete(int** arr, int* curr_size, int* capacity) {
    if (*curr_size == 0) {
        printf("Error: Array is empty!");
        exit(1);
    }
    (*curr_size)--;
    if (*curr_size <= (*capacity / 4)) {
        *capacity /= 2;
        int* new_arr = realloc(*arr, (*capacity) * sizeof(int));
        if (new_arr == NULL) {
            printf("Error: Memory allocation failed!");
            exit(1);
        }
        *arr = new_arr;
    }
}


struct queue {
    int head;
    int tail;
    int curr_size;
    int capacity;
    int *arr;
};

struct queue* create_queue() {
    struct queue *Q = malloc(sizeof(struct queue));

    if (Q == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    Q -> head = Q -> tail = Q -> curr_size = 0;
    Q -> capacity = 1;
    Q -> arr = malloc(Q -> capacity * sizeof(int));

    return Q;
}

int is_empty(struct queue* Q) {
    if (Q -> curr_size == 0)
        return 1;
    return 0;
}

void enqueue(struct queue* Q, int val) {
    insert(&(Q -> arr), &(Q -> curr_size), &(Q -> capacity), val);
    Q -> tail = Q -> curr_size;
}

int dequeue(struct queue* Q) {
    if (is_empty(Q)) {
        printf("underflow");
        exit(0);
    }

    int val = Q -> arr[Q -> head];
    delete(&(Q -> arr), &(Q -> curr_size), &(Q -> capacity));
    Q -> head = 0;
    Q -> tail = Q -> curr_size - 1;
    return val;
}

int main() {
    struct queue *Q = create_queue();
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
