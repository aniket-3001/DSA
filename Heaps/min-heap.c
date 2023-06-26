#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARENT(i) (i/2)
#define LEFT(i) (2*i)
#define RIGHT(i) (2*i+1)

struct Heap {
    int *arr;
    int capacity; // maximum size of heap
    int heap_size; // number of elements in the heap
};

void exchange(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Min_Heap_insert(struct Heap *H, int x) {
    if (H->heap_size == H->capacity) {
        perror("heap overflow");
        return;
    }

    H->heap_size++;
    H->arr[H->heap_size] = x;
    int i = H->heap_size;

    while (i > 1 && H->arr[PARENT(i)] > H->arr[i]) {
        exchange(&H->arr[i], &H->arr[PARENT(i)]);
        i = PARENT(i);
    }
}

void Min_Heapify(struct Heap *H, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest;

    if (l <= H->heap_size && H->arr[l] < H->arr[i])
        smallest = l;
    else
        smallest = i;

    if (r <= H->heap_size && H->arr[r] < H->arr[smallest])
        smallest = r;

    if (smallest != i) {
        exchange(&H->arr[i], &H->arr[smallest]);
        Min_Heapify(H, smallest);
    }
}

int Min_Heap_Min(struct Heap *H) {
    if (H->heap_size == 0) {
        perror("Heap empty");
        exit(1);
    }
    return H->arr[1];
}

void Min_Heap_Decrease_Key(struct Heap *H, int i, int keyval) {
    if (H->arr[i] > keyval) {
        H->arr[i] = keyval;
        while (i > 1 && H->arr[PARENT(i)] > H->arr[i]) {
            exchange(&H->arr[i], &H->arr[PARENT(i)]);
            i = PARENT(i);
        }
    }
}

int Min_Heap_Extract_Min(struct Heap *H) {
    int min = Min_Heap_Min(H);
    H->arr[1] = H->arr[H->heap_size];
    H->heap_size--;
    Min_Heapify(H, 1);
    return min;
}

struct Heap* Build_Min_Heap(int *A, int n) {
    struct Heap *H = malloc(sizeof(struct Heap));
    H->arr = malloc(sizeof(int) * (n + 1));
    H->capacity = n;
    H->heap_size = n;
    memcpy(H->arr + 1, A, sizeof(int) * n);

    for (int i = n/2; i >= 1; i--) {
        Min_Heapify(H, i);
    }

    return H;
}

void HeapSort(int *arr, int n) {
    struct Heap *H = Build_Min_Heap(arr, n);
    for (int i = H->heap_size; i > 1; i--) {
        exchange(&H->arr[1], &H->arr[i]);
        H->heap_size--;
        Min_Heapify(H, 1);
    }
    memcpy(arr, H->arr + 1, sizeof(int) * n);
    free(H->arr);
    free(H);
}

int main() {
    // Initialize an array of integers
    int arr[] = {12, 11, 13, 5, 9, 7, 1, 2, 3, 50, 45, 10, 19, 4, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Build the min heap
    struct Heap *H = Build_Min_Heap(arr, n);

    // Print the min heap array
    printf("Min Heap array: ");
    for (int i = 1; i <= n; i++) {
        printf("%d ", H->arr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(H->arr);
    free(H);

    return 0;
}

