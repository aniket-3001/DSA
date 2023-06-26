#include "../include/common.h"

#include "pa1.h"

// don't remove these globals

static struct record *record_arr = NULL;

static size_t max_capacity = 0;

static size_t num_records = 0;

// don't modify this function

struct record *get_record_arr()

{

  return record_arr;
}

// don't modify this function

// compare two uids

// return -1 if uid1 < uid2

// return 0 if uid1 == uid2

// return 1 if uid1 > uid2

static size_t cmp_uid(char *uid1, char *uid2)

{

  size_t i;

  for (i = 0; i < MAX_LEN; i++)
  {

    if (uid1[i] > uid2[i])
    {

      return 1;
    }

    else if (uid1[i] < uid2[i])
    {

      return -1;
    }
  }

  return 0;
}

// don't modify this function

// compare two records when uid is key

// return -1 if record1 < record2

// return 0 if record1 == record2

// return 1 if record1 > record2

static size_t cmp_record(struct record *r1, struct record *r2)

{

  return cmp_uid(r1->uid, r2->uid);
}

// don't modify this function

static void *allocate_memory(size_t size)

{

  return __mymalloc(size);
}

// don't modify this function

static void free_memory(void *ptr)

{

  __myfree(ptr);
}

// ---------------- Add your code below this line ----------------- //

#define NOT_IMPLEMENTED                                      \
  {                                                          \
    printf("%s still needs to be implemented!\n", __func__); \
    abort();                                                 \
  }
#include <limits.h>

size_t return_min_index(struct record *arr, size_t index, size_t len);
void selection_sort(struct record *arr, size_t index, size_t len);
size_t return_min_index(struct record *arr, size_t index, size_t len);

size_t lower(size_t c)
{
  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';

  else
    return c;
}

size_t str_cmp(char str1[], char str2[])
{
  size_t index = 0;

  while (str1[index] != '\0' && str2[index] != '\0')
  {
    if (lower(str1[index]) < lower(str2[index]))
      return -1;

    else if (lower(str1[index]) > lower(str2[index]))
      return 1;

    index++;
  }

  if (str1[index] == '\0' && str2[index] == '\0')
    return 0;

  else
  {

    if (str1[index] == '\0')
      return -1;

    else
      return 1;
  }
}

// compare records on the basis of name
size_t cmp_record_name(struct record *r1, struct record *r2)
{
  return str_cmp(r1->name, r2->name); // using cmp_uid function for this too
}

// function to swap two elements of an array
void exchange(struct record *arr, size_t i, size_t j)
{
  struct record temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

// function which returns the minimum index of an array after a particular index
size_t return_min_index(struct record *arr, size_t index, size_t len)
{
  size_t min_index = index;
  for (size_t i = index; i < len; i++)
  {
    if (cmp_record(&arr[i], &arr[min_index]) == -1)
      min_index = i;
  }

  return min_index;
}

// main driver function for selection sort
void selection_sort(struct record *arr, size_t index, size_t len)
{
  if (index == len)
    return;

  size_t min_index = return_min_index(arr, index, len);
  exchange(arr, index, min_index);
  selection_sort(arr, index + 1, len);
}

// function to implement merge algorithm
void merge(struct record *arr, size_t lo, size_t mid, size_t hi)
{
  size_t i, j, k;
  size_t n1 = mid - lo + 1;
  size_t n2 = hi - mid;

  struct record *tmp1 = allocate_memory(n1 * sizeof(struct record));
  struct record *tmp2 = allocate_memory(n2 * sizeof(struct record));

  for (i = 0; i < n1; i++)
    tmp1[i] = arr[lo + i];

  for (j = 0; j < n2; j++)
    tmp2[j] = arr[mid + 1 + j];

  i = 0;
  j = 0;
  k = lo;

  while (i < n1 && j < n2)
  {
    if (cmp_record(&tmp1[i], &tmp2[j]) <= 0)
      arr[k] = tmp1[i++];

    else
      arr[k] = tmp2[j++];

    k++;
  }

  while (i < n1)
    arr[k++] = tmp1[i++];

  while (j < n2)
    arr[k++] = tmp2[j++];

  free_memory(tmp1);
  free_memory(tmp2);
}

// main driver function for merge sort
void merge_sort(struct record *arr, size_t lo, size_t hi)
{
  if (lo < hi)
  {
    size_t mid = (lo + hi) / 2;
    merge_sort(arr, lo, mid);
    merge_sort(arr, mid + 1, hi);
    merge(arr, lo, mid, hi);
  }
}

// return the total number of records in the
// record_arr
size_t get_num_records()
{
  return num_records;
}

// partition algorithm for quick sort implementation which partitions on basis of uid
size_t partition_uid(struct record *arr, size_t lo, size_t hi)
{
  struct record pivot = arr[lo];
  size_t left = lo;
  size_t right = hi;

  while (left < right)
  {
    while (left <= right && (cmp_record(&arr[left], &pivot) <= 0))
      left++;

    while (right >= left && (cmp_record(&arr[right], &pivot) > 0))
      right--;

    if (left < right)
      exchange(arr, left, right);
  }

  exchange(arr, lo, right);
  return right;
}

// main driver function for quick sort on basis of uid
void quick_sort_uid(struct record *arr, size_t lo, size_t hi)
{
  if (lo >= hi)
    return;

  size_t p = partition_uid(arr, lo, hi);
  quick_sort_uid(arr, lo, p - 1);
  quick_sort_uid(arr, p + 1, hi);
}

// partition algorithm for quick sort implementation which partitions on basis of name
size_t partition_name(struct record *arr, size_t lo, size_t hi)
{
  struct record pivot = arr[lo];
  size_t left = lo + 1;
  size_t right = hi;

  while (left <= right)
  {
    while (left <= right && cmp_record_name(&arr[left], &pivot) == -1)
      left++;

    while (right >= left && cmp_record_name(&arr[right], &pivot) == 1)
      right--;

    if (left <= right)
    {
      exchange(arr, left, right);
      left++;
      right--;
    }
  }

  exchange(arr, lo, right);
  return right;
}

// main driver function for quick sort via uid
void quick_sort_name(struct record *arr, size_t lo, size_t hi)
{
  if (lo >= hi)
    return;

  size_t p = partition_name(arr, lo, hi);
  quick_sort_name(arr, lo, p - 1);
  quick_sort_name(arr, p + 1, hi);
}

// insert record r at the end of the record array
// if the record array is full, allocate
// a new buffer of double size, copy data
// from old buffer to the new buffer
// delete the old buffer
// make record_arr point to the new buffer
void insert_record(struct record r)
{
  size_t modified_capacity;

  if (max_capacity == 0)
  {
    max_capacity = 1;
    num_records = 0;
    record_arr = allocate_memory(max_capacity * sizeof(struct record));
  }

  if (num_records == max_capacity)
  {
    max_capacity = 2 * max_capacity;
    struct record *new_arr = allocate_memory(sizeof(struct record) * max_capacity);

    for (size_t i = 0; i < num_records; i++)
    {
      new_arr[i] = record_arr[i];
    }
    free_memory(record_arr);
    record_arr = new_arr;
  }

  record_arr[num_records++] = r;
}

// return the record corresponding to the uid
// use the linear search algorithm
// you can also use cmp_uid routine defined earlier
// if none of the records contain the input uid
// return a dummy record with status == -1
struct record search_record_linear(char uid[MAX_LEN])
{
  for (size_t i = 0; i < num_records; i++)
  {
    if (cmp_uid(record_arr[i].uid, uid) == 0)
      return record_arr[i];
  }

  struct record dummy_record;
  dummy_record.status = (-1);
  return dummy_record;
}

// return the record corresponding to the uid
// use the binary search algorithm
// you can assume that the record_arr is alaredy sorted
// if none of the records contain the input uid
// return a dummy record with status == -1
struct record search_record_binary(char uid[MAX_LEN])
{
  size_t lt = 0;
  size_t rt = num_records - 1;

  while (lt <= rt)
  {
    size_t mid = (lt + rt) / 2;
    size_t res = cmp_uid(record_arr[mid].uid, uid);

    if (res == 0)
      return record_arr[mid];

    else if (res < 0)
      lt = mid + 1;

    else
      rt = mid - 1;
  }

  struct record dummy_record;
  dummy_record.status = -1;
  return dummy_record;
}

// delete record correspondig to the uid
// if the corresponding record doesn't exist
// return a dummy record with status == -1
// Otherwise, return a copy of the record to the caller
// resize the record array in the following manner
// let's say, x is the size of the array
// and after deletion only x/4
// space in the array is occupied, in this
// case, allocate an array of size x/2,
// copy records from old array to the new
// array, and delete the old array,
// make record_arr point to the new array
struct record delete_record(char uid[MAX_LEN])
{
  if (max_capacity == 0)
  {
    max_capacity = 1;
    num_records = 0;
    record_arr = (struct record *)allocate_memory(max_capacity * sizeof(struct record));
  }

  struct record deleted_record;
  size_t found = 0;
  size_t idx = -1;

  for (size_t i = 0; i < num_records; i++)
  {
    if (cmp_uid(record_arr[i].uid, uid) == 0)
    {
      deleted_record = record_arr[i];
      found = 1;
      idx = i;
      break;
    }
  }

  if (found)
  {
    record_arr[idx] = record_arr[num_records - 1]; // Swap the element to be deleted with the last element
    num_records--;

    if (num_records <= max_capacity / 4)
    { // Check if array needs to be resized
      max_capacity = max_capacity / 2;
      struct record *new_arr = allocate_memory(sizeof(struct record) * max_capacity);

      for (size_t i = 0; i < num_records; i++) // copy elements to new array
        new_arr[i] = record_arr[i];

      // Free the memory of the old array and update the pointer and capacity
      free_memory(record_arr);
      record_arr = new_arr;
    }

    return deleted_record;
  }

  struct record dummy_record;
  dummy_record.status = -1;
  return dummy_record;
}

// delete all records in the record_arr
// free record_arr
void delete_all_records()
{
  num_records = 0;
  free_memory(record_arr);
}

// sort the record array using quick sort
// use cmp_record implementaion to compare two records
void sort_records_quick()
{
  quick_sort_uid(record_arr, 0, num_records - 1);
}

// sort the record_arr using merge sort
// use cmp_record implementaion to compare two records
void sort_records_merge()
{
  merge_sort(record_arr, 0, num_records - 1);
}

// sort the record_arr using selection sort
// use cmp_record implementaion to compare two records
void sort_records_selection()
{
  selection_sort(record_arr, 0, num_records);
}

// return the number of records corresponding to the input name
// use linear search to obtain the results
size_t get_num_records_with_name_linear(char name[MAX_LEN])
{
  size_t cnt = 0;
  for (size_t i = 0; i < num_records; i++)
  {
    if (str_cmp(record_arr[i].name, name) == 0)
      cnt++;
  }

  return cnt;
}

// implement quick sort algorithm to sort the
// record_arr using name as key
void rearrange_data()
{
  quick_sort_name(record_arr, 0, num_records - 1);
}

// return the number of records corresponding to the input name
// use binary search to obtain the results
// you can assume that the caller has sorted
// data using name as key before making these queries
size_t get_num_records_with_name_binary(char name[MAX_LEN])
{
  size_t cnt = 0;
  size_t left = 0;
  size_t right = num_records - 1;

  while (left <= right)
  {
    size_t mid = left + (right - left) / 2;
    size_t res = str_cmp(record_arr[mid].name, name);

    if (res == 0)
    {
      cnt++; // Record with matching name found

      for (size_t i = mid - 1; i >= 0; i--)
      {                                             // check for matching records on the left side
        if (str_cmp(record_arr[i].name, name) == 0) // cmp_uid will come in handy for this too
          cnt++;

        else
          break;
      }

      for (size_t i = mid + 1; i < num_records; i++)
      {                                             // check for matching records on the right side
        if (str_cmp(record_arr[i].name, name) == 0) // cmp_uid will come in handy for this too
          cnt++;

        else
          break;
      }

      break;
    }

    else if (res < 0)
      left = mid + 1;

    else
      right = mid - 1;
  }

  return cnt;
}