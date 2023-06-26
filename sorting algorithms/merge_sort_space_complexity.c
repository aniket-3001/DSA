#include <stdio.h>

void merge(int arr[], int lo, int mid, int hi) {
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
        if (arr[i] <= arr[j])
            i++;
        else {
            int temp = arr[j];

            for (int k = j - 1; k >= i; k--)
                arr[k+1] = arr[k];

            arr[i] = temp;
            i++; mid++; j++;
        }
    }
}

void merge_sort(int arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = (lo + hi) / 2;
        merge_sort(arr, lo, mid);
        merge_sort(arr, mid + 1, hi);
        merge(arr, lo, mid, hi);
    }
}

int main() {
    int arr[] = {5, 3, 8, 4, 2, 7, 1, 10, 6, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    merge_sort(arr, 0, n-1);
    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
