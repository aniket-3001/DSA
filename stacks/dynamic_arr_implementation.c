#include <stdio.h>
#include <stdlib.h>

void insert(int** arr, int* size, int* capacity, int element) {
    if (*size == *capacity) {
        *capacity *= 2;
        int* new_arr = realloc(*arr, *capacity * sizeof(int));
        if (new_arr == NULL) {
            printf("Error: Memory allocation failed!");
            exit(1);
        }
        *arr = new_arr;
    }
    (*arr)[*size] = element;
    (*size)++;
}

void delete(int** arr, int* size, int* capacity) {
    if (*size == 0) {
        printf("Error: Array is empty!");
        exit(1);
    }
    (*size)--;
    if (*size <= (*capacity / 4)) {
        *capacity /= 2;
        int* new_arr = malloc((*capacity) * sizeof(int));
        if (new_arr == NULL) {
            printf("Error: Memory allocation failed!");
            exit(1);
        }
        for (int i = 0; i < (*size); i++) {
            new_arr[i] = (*arr)[i];
        }
        free(*arr);
        *arr = new_arr;
    }
}

struct stack {
    int size;
    int capacity;
    int* arr;
};

struct stack* create_stack() {
    struct stack* S = malloc(sizeof(struct stack));
    if (S == NULL) {
        printf("Error: Memory allocation failed!");
        exit(1);
    }
    S->size = 0;
    S->capacity = 1;
    S->arr = malloc(S->capacity * sizeof(int));
    if (S->arr == NULL) {
        printf("Error: Memory allocation failed!");
        exit(1);
    }
    return S;
}

int is_empty(struct stack* S) {
    return S->size == 0;
}

void push(struct stack* S, int val) {
    insert(&(S->arr), &(S->size), &(S->capacity), val);
}

int pop(struct stack* S) {
    int val = S->arr[S->size - 1];
    delete(&(S->arr), &(S->size), &(S->capacity));
    return val;
}

void pushb(struct stack* S, int v) {
    if (is_empty(S)) {
        push(S, v);
    } else {
        int x = pop(S);
        pushb(S, v);
        push(S, x);
    }
}

int main() {
    struct stack* S = create_stack();

    push(S, 1);
    push(S, 2);
    push(S, 3);
    push(S, 4);
    push(S, 5);

    printf("Stack elements: ");
    while (!is_empty(S)) {
        printf("%d ", pop(S));
    }
    printf("\n");

    pushb(S, 1);
    pushb(S, 2);
    pushb(S, 3);
    pushb(S, 4);
    pushb(S, 5);

    printf("Stack elements (after pushb): ");
    while (!is_empty(S)) {
        printf("%d ", pop(S));
    }
    printf("\n");

    free(S->arr);
    free(S);

    return 0;
}
