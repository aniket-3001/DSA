// We want to store (key, value) pairs of type “struct pair” in a data structure
// called priority-queue. The priority-queue supports three operations: insert, find, and
// delete. The insert operation inserts a (key, value) pair in O(log n) operations. The find
// operation returns a (key, value) pair corresponding to the largest key. If multiple pairs
// contain the largest key, find returns the one that was inserted first. The time-complexity
// of the find operation is O(1). The delete operation deletes a pair that contains the largest
// key. If multiple pairs contain the largest key, the one that was inserted first is deleted.
// The time complexity of the delete operation is O(log n). Give a pseudocode for the insert,
// find, and delete operations. What is the type of node in the priority-queue? The type
// “struct pair” is as follows.

// struct pair {
//  int key, value;
// };

// We can insert the elements in a heap. The type of node in the priority queue is struct
// entry, as shown below. A global arrival time is maintained, which gets updated every
// time an entry is added to the priority queue. If multiple entries contain the maximum key,
// the one with the least arrival time has the highest priority. The corresponding
// pseudocode is shown below.

struct entry
{
    struct pair p;
    int arrival_time;
};

struct Heap
{
    struct entry *arr;
    int capacity;  // maximum size of heap
    int heap_size; // number of elements in the heap
};

PARENT(i)
{
    return (i / 2);
}

cmp_entries(e1, e2)
{
    // compare two elements e1 and e2 of type struct entry
    // return true if e1 has more priority than e2; otherwise, return false
    if (e1.p.key == e2.p.key)
        return e1.arrival_time < e2.arrival_time;
    return e1.p.key > e2.p.key;
}

int global_arrival_time = 0; // global variable

void insert(struct Heap *H, struct pair x)
{
    // H is a reference to the heap of type struct Heap
    // x is a struct pair input that needs to be inserted
    // Output: insert x in the heap
    if (H->heap_size == H->capacity)
        perror("heap overflow");
    H->heap_size = H->heap_size + 1;
    H->arr[H->heap_size].p = x;
    H->arr[H->heap_size].arrival_time = global_arrival_time;
    global_arrival_time = global_arrival_time + 1;
    int i = H->heap_size;
    while (i > 1 && cmp_entries(H->arr[i], H->arr[PARENT(i)]))
    {
        exchange H->arr[i] with H->arr[PARENT(i)];
        i = PARENT(i);
    }
}

struct pair find(struct Heap *H)
{
    // H is a reference to the heap of type struct Heap
    // Output: return the value with maximum key, if multiple
    // elements contain the maximum key, return the one that came first
    if (H->heap_size == 0)
        perror("Heap underflow");
    return H->arr[1].p;
}

int LEFT(int i)
{
    return 2 * i;
}

int RIGHT(int i)
{
    return (2 * i) + 1;
}

void heapify(struct Heap *H, int i)
{
    // H is a reference to the heap of type struct Heap
    // i is the index at which the heapify needs to be performed
    // Output: node at index i satisfies the max heap property
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;

    if (l <= H->heap_size && cmp_entries(H->arr[l], H->arr[i]))
        largest = l;
    else
        largest = i;

    if (r <= H->heap_size && cmp_entries(H->arr[r], H->arr[largest]))
        largest = r;

    if (largest != i)
    {
        exchange H->arr[i] with H->arr[largest];
        heapify(H, largest);
    }
}

struct pair delete(struct Heap *H)
{
    // H is a reference to the heap of type struct Heap
    // Output: delete the entry with maximum key from the heap, if multiple
    // elements contain the maximum key, delete the one that came first
    // return the value of the deleted node
    struct pair max = find(H);
    H->arr[1] = H->arr[H->heap_size];
    H->heap_size = H->heap_size - 1;
    heapify(H, 1);
    return max;
}
