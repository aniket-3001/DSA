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

int main() {
    int size = 0;
    int capacity = 1;
    int* arr = malloc(capacity * sizeof(int));

    // insert some elements into the array
    insert(&arr, &size, &capacity, 1);
    insert(&arr, &size, &capacity, 2);
    insert(&arr, &size, &capacity, 3);
    insert(&arr, &size, &capacity, 4);
    insert(&arr, &size, &capacity, 5);

    // print the array
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // delete an element from the array
    delete(&arr, &size, &capacity);

    // print the array again
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // insert some more elements into the array
    insert(&arr, &size, &capacity, 6);
    insert(&arr, &size, &capacity, 7);

    // print the array again
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // free the memory used by the array
    free(arr);

    return 0;
}
