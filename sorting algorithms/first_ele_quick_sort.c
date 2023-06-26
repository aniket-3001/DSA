#include <stdio.h>


void swap(int arr[], int i, int j);
int partition(int arr[], int lo, int hi);
void quick_sort(int arr[], int lo, int hi);


void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


void quick_sort(int arr[], int lo, int hi) {
    if (lo >= hi)
        return;

    int p = partition(arr, lo, hi);
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
            swap(arr, left, right);
            left++; right--;
        }
    }

    swap(arr, lo, right);
    return right;
}


int main() {
    int arr[] = {5, 2, 7, 1, 9, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    quick_sort(arr, 0, n-1);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
