#include <stdio.h>
#include <stdlib.h>

struct stack {
    int top;
    int capacity;
    int *arr;
};

struct stack* create_stack(int max_elements) {
    struct stack *S = malloc(sizeof(struct stack));

    if (S == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    S -> arr = malloc(max_elements*sizeof(int));

    if (S -> arr == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    S -> top = 0;
    S -> capacity = max_elements;
    return S;
}

int is_empty(struct stack *S) {
    if (S -> top == 0)
        return 1;
    
    return 0;
}

int is_full(struct stack *S) {
    if (S -> top == S -> capacity)
        return 1;

    return 0;
}

void push(struct stack* S, int val) {
    if (is_full(S)) {
        printf("overflow");
        exit(0);
    }

    S -> arr[S -> top] = val;
    S -> top++;
}

int pop(struct stack* S) {
    if (is_empty(S)) {
        printf("underflow");
        exit(0);
    }

    int retval = S -> arr[S -> top-1];
    S -> top--;
    return retval;
}

int main() {
    struct stack *S = create_stack(5);

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

    free(S->arr);
    free(S);

    return 0;
}