#include <stdio.h>

void exchange(int arr[], int i, int j);
int return_min_index(int arr[],int index,int len);
void selection_sort(int arr[], int index, int len);

void selection_sort(int arr[], int index, int len) {
    if (index == len)
        return;

    int min_index = return_min_index(arr,index,len);
    exchange(arr, index, min_index);
    selection_sort(arr, index+1, len);
}

void exchange(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int return_min_index(int arr[], int index, int len) {
    int min_index = index;

    for (int i = index; i < len; i++) {
        if (arr[i] < arr[min_index])
            min_index = i;
    }
    return min_index;
}

int main() {
    int arr[10] = {83, 86, 77, 15, 93, 35, 86, 92, 49, 21};
    int len = 10;
    int index = 0;
    selection_sort(arr, index, len);
    for (int i = 0; i < len; i++)
        printf("%d ", arr[i]);

    return 0;
}