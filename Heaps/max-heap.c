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

void Max_Heap_insert(struct Heap *H, int x) {
    if (H->heap_size == H->capacity) {
        perror("heap overflow");
        return;
    }

    H->heap_size++;
    H->arr[H->heap_size] = x;
    int i = H->heap_size;

    while (i > 1 && H->arr[PARENT(i)] < H->arr[i]) {
        exchange(&H->arr[i], &H->arr[PARENT(i)]);
        i = PARENT(i);
    }
}

void Max_Heapify(struct Heap *H, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;

    if (l <= H->heap_size && H->arr[l] > H->arr[i])
        largest = l;
    else
        largest = i;

    if (r <= H->heap_size && H->arr[r] > H->arr[largest])
        largest = r;

    if (largest != i) {
        exchange(&H->arr[i], &H->arr[largest]);
        Max_Heapify(H, largest);
    }
}

int Max_Heap_Max(struct Heap *H) {
    if (H->heap_size == 0) {
        perror("Heap underflow");
        exit(1);
    }
    return H->arr[1];
}

void Max_Heap_Increase_Key(struct Heap *H, int i, int keyval) {
    if (H->arr[i] < keyval) {
        H->arr[i] = keyval;
        while (i > 1 && H->arr[PARENT(i)] < H->arr[i]) {
            exchange(&H->arr[i], &H->arr[PARENT(i)]);
            i = PARENT(i);
        }
    }
}

int Max_Heap_Extract_Max(struct Heap *H) {
    int max = Max_Heap_Max(H);
    H->arr[1] = H->arr[H->heap_size];
    H->heap_size--;
    Max_Heapify(H, 1);
    return max;
}

struct Heap* Build_Max_Heap(int *A, int n) {
    struct Heap *H = malloc(sizeof(struct Heap));
    H->arr = malloc(sizeof(int) * (n + 1));
    memcpy(H->arr + 1, A, sizeof(int) * n);
    H->capacity = n;
    H->heap_size = n;
    for (int i = n/2; i >= 1; i--) {
        Max_Heapify(H, i);
    }

    return H;
}

void HeapSort(int *arr, int n) {
    struct Heap *H = Build_Max_Heap(arr, n);
    for (int i = H->heap_size; i > 1; i--) {
        exchange(&H->arr[1], &H->arr[i]);
        H->heap_size--;
        Max_Heapify(H, 1);
    }
    memcpy(arr, H->arr + 1, sizeof(int) * n);
    free(H->arr);
    free(H);
}


int main() {
    // Initialize an array of integers
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    // Print the unsorted array
    printf("Unsorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array using heap sort
    HeapSort(arr, 6);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}