#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(char *arr[], int lo, int mid, int hi) {
    int i, j, k;
    int n_elem_1 = mid-lo+1;
    int n_elem_2 = hi-mid;

    char **tmp1 = malloc((n_elem_1+1) * sizeof(char *));
    char **tmp2 = malloc((n_elem_2+1) * sizeof(char *));

    for (i = 0; i < n_elem_1; i++)
        tmp1[i] = arr[lo+i];

    for (j = 0; j < n_elem_2; j++)
        tmp2[j] = arr[mid+1+j];

    tmp1[i] = tmp2[j] = (char *) "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    i = j = 0;

    for (k = lo; k <= hi; k++) {
        if (strcmp(tmp1[i], tmp2[j]) <= 0)
            arr[k] = tmp1[i++];
        else
            arr[k] = tmp2[j++];
    }

    free(tmp1);
    free(tmp2);
}

void merge_sort(char *arr[], int lo, int hi) {
    if (lo < hi) {
        int mid = (lo+hi)/2;
        merge_sort(arr, lo, mid);
        merge_sort(arr, mid+1, hi);
        merge(arr, lo, mid, hi);
    }
}

int main() {
    char *arr[] = {"pear", "apple", "banana", "orange", "grape", "cherry", "kiwi"};
    int len = sizeof(arr)/sizeof(arr[0]);

    merge_sort(arr, 0, len-1);

    for (int i = 0; i < len; i++)
        printf("%s ", arr[i]);

    return 0;
}
