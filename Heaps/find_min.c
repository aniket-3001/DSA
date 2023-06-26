#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PARENT(i) (i / 2)
#define LEFT(i) (2 * i)
#define RIGHT(i) (2 * i + 1)

struct Heap
{
    int *arr;
    int capacity;  // maximum size of heap
    int heap_size; // number of elements in the heap
};

int minimum(int a, int b)
{
    return a < b ? a : b;
}

// Function to find the minimum element in a max heap
int findMinimumElement(struct Heap *h)
{
    int minimumElement = h->arr[h->heap_size / 2];

    for (int i = 1 + h->heap_size / 2; i < h->heap_size; ++i)
        minimumElement = minimum(minimumElement, h->arr[i]);

    return minimumElement;
}

// Driver code
int main()
{
    // Number of nodes
    int n = 10;
    // heap represents the following max heap:
    //   20
    //  / \
    // 18  10
    // / \ / \
    // 12  9 9 3
    // / \ /
    // 5  6 8
    int elts[] = {20, 18, 10, 12, 9, 9, 3, 5, 6, 8};
    struct Heap *h = malloc(sizeof(struct Heap));
    h->arr = malloc(n * sizeof(int));
    h->heap_size = n;
    h->capacity = n;

    for (int i = 0; i < n; i++)
    {
        h->arr[i] = elts[i];
    }

    printf("%d\n", findMinimumElement(h));

    free(h->arr);
    free(h);

    return 0;
}

// Starting from floor(n/2) ensures that we start from the first leaf node in the heap.
// This is because all the nodes after floor(n/2) are leaf nodes.
// The nodes before floor(n/2) are internal nodes that have children.