#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int arr[], int lo, int mid, int hi) {
    int i, j, k;
    int len1 = mid-lo+1;
    int len2 = hi-mid;

    int tmp1[len1+1];
    int tmp2[len2+1];

    for (i = 0; i < len1; i++)
        tmp1[i] = arr[lo+i];

    for (j = 0; j < len2; j++)
        tmp2[j] = arr[mid+1+j];

    tmp1[i] = tmp2[j] = INT_MAX;
    i = j = 0;

    for (k = lo; k <= hi; k++) {
        if (tmp1[i] <= tmp2[j])
            arr[k] = tmp1[i++];
        else
            arr[k] = tmp2[j++];
    }
}

void merge_sort(int arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = (lo+hi)/2;
        merge_sort(arr, lo, mid);
        merge_sort(arr, mid+1, hi);
        merge(arr, lo, mid, hi);
    }
}

int main() {
    int arr[] = {28, 43, 72, 79, 23, 70, 55, 39, 68, 1, 41, 40, 5, 25, 95, 4, 42, 54, 79, 55};
    int n = sizeof(arr)/sizeof(arr[0]);

    merge_sort(arr, 0, n-1);

    printf("Sorted array: ");
    
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
