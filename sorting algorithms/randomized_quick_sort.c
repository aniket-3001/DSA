#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function declarations
void quick_sort(int arr[], int lo, int hi);
int partition(int arr[], int lo, int hi);
void exchange(int arr[], int i, int j);

int main() {
    // Initialize a test array
    int arr[] = {28, 43, 72, 79, 23, 70, 55, 39, 68, 1, 41, 40, 5, 25, 95, 4, 42, 54, 79, 55};
    

    // Calculate the size of the array
    int n = sizeof(arr) / sizeof(arr[0]);

    // Sort the array using quick sort
    quick_sort(arr, 0, n-1);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}



void exchange(int arr[], int i, int j) {
    // Swaps the elements at indices i and j in the array arr
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


void quick_sort(int arr[], int lo, int hi) {
    if (lo >= hi)
        return;

    int p = partition(arr, lo, hi);

    for (int i = 0; i < 20; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    quick_sort(arr, lo, p-1);
    quick_sort(arr, p+1, hi);
}


int partition(int arr[], int lo, int hi) {
    int pivot = arr[lo];
    int left = lo+1;
    int right = hi;

    while (left <= right) {
        while (left <= right && arr[left] < pivot)
            left++;

        while (right >= left && arr[right] > pivot)
            right--;

        if (left <= right) {
            exchange(arr, left, right);
            left++; right--;
        }
    }

    exchange(arr, lo, right);
    return right;
}

