#include <stdio.h>

int arr[] = {13, 46, 24, 52, 20, 9};

void swap(int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubble_sort(int end_idx) {
    if (end_idx < 2)
        return;

    int i;
    int didSwap = 0;

    for (i = 0; i < end_idx-1; i++) {
        if (arr[i] > arr[i+1]) {
            swap(i, i+1);
            didSwap = 1;
        }
    }

    if (didSwap)
        bubble_sort(end_idx-1);
}

int main() {
    int len = sizeof(arr)/sizeof(arr[0]);
    bubble_sort(len);
    int i;

    for (i = 0; i < len; i++)
        printf("%d ", arr[i]);

    return 0;
}
