#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function declarations
int quick_sort(int arr[], int lo, int hi, int pos);
int partition(int arr[], int lo, int hi);
int get_random_idx(int lo, int hi);
void exchange(int arr[], int i, int j);
float find_median(int arr[], int len);


int main() {
    // Initialize a test array
    int arr[] = {28, 43, 72, 79, 23, 70, 55, 39, 68, 1, 41, 40, 5, 25, 95, 4, 42, 54, 79, 55};

    // Calculate the size of the array
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Seed the random number generator
    srand(time(NULL));

    // Sort the array using quick sort
    float median = find_median(arr, n);

    printf("Median = %f", median);
    return 0;
}


int get_random_idx(int lo, int hi) {
    // Returns a random integer between lo and hi (inclusive)
    return (rand() % (hi - lo + 1)) + lo;
}


void exchange(int arr[], int i, int j) {
    // Swaps the elements at indices i and j in the array arr
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}


int quick_sort(int arr[], int lo, int hi, int pos) {
    if (lo >= hi)
        return arr[lo];

    int p = partition(arr, lo, hi);

    if (p == pos)
        return arr[p];

    else if (p < pos)
        quick_sort(arr, p+1, hi, pos);

    else
        quick_sort(arr, lo, p-1, pos);
}


int partition(int arr[], int lo, int hi) {
    int idx = get_random_idx(lo, hi);
    exchange(arr, lo, idx);
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


float find_median(int arr[], int len) {
    int lo = 0;
    int hi = len-1;

    if (len % 2 != 0) {
        int pos = (len-1)/2;
        float median = quick_sort(arr, lo, hi, pos);
        return median;
    }

    else {
        int pos = (len/2)-1;
        int temp1 = quick_sort(arr, lo, hi, pos);
                
        pos = len/2;
        int temp2 = quick_sort(arr, lo, hi, pos);
        
        float median = (temp1 + temp2)/2.0;
        return median;
    }
}