#include "../include/common.h"
#include "pa4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// don't remove these globals
struct heap_elem *min_heap_arr = NULL;

// don't modify this function
void initialize_min_heap_arr(struct heap_elem *arr)
{
  min_heap_arr = arr;
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

// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// return r->friends.
struct list_records *get_friends_list(struct record *r)
{
  return r->friends;
}

// Make r1 and r2 friends of each other if they aren't already friends.
// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// Return 1 if r1 and r2 are already friends before this call.
// Otherwise, make r1 a friend of r2 and return 0.
// To make r1 a friend of r2,
// insert r1 into the list r2->friends and insert r2 into the list r1->friends.
int make_friends(struct record *r1, struct record *r2)
{
  // checking if they already are friends
  struct list_records *h1 = r1->friends;
  while (h1 != NULL)
  {
    if (h1->record == r2)
      return 1;

    h1 = h1->next;
  }

  // make them friends

  struct list_records *new_h1 = allocate_memory(sizeof(struct list_records));
  struct list_records *new_h2 = allocate_memory(sizeof(struct list_records));

  new_h1->record = r2;
  new_h1->next = r1->friends;
  r1->friends = new_h1;

  new_h2->record = r1;
  new_h2->next = r2->friends;
  r2->friends = new_h2;

  return 0;
}

// remove all nodes from r->friends and release the corresponding memory
void delete_friends_list(struct record *r)
{
  struct list_records *curr = r->friends;
  struct list_records *next;

  while (curr != NULL)
  {
    next = curr->next;
    free_memory(curr);
    curr = next;
  }

  r->friends = NULL;
}

#define NOT_INSERTED 0
#define YELLOW 1
#define WHITE 2

int num_vertices = 0; // variable which keeps track of the number of vertices in the graph

// Function to initialize a given vertex
void InitializeVertex(struct record *vertex)
{
  vertex->status = YELLOW;
  vertex->distance = INFINITY;
  vertex->pred = NULL;
}

// Function to return the vertex with the minimum distance
struct record *FindMinDistanceVertex()
{
  int min_index = 0;
  double min_dist = INFINITY;

  for (int i = 0; i < num_vertices; i++)
  {
    if (min_heap_arr[i].r->status == YELLOW && min_heap_arr[i].r->distance < min_dist)
    {
      min_dist = min_heap_arr[i].r->distance;
      min_index = i;
    }
  }

  struct record *min_vertex = min_heap_arr[min_index].r;
  return min_heap_arr[min_index].r;
}

// Function which we will use to insert the vertices of type struct record* into our min_heap_arr
void DFS_insert(struct record *vertex)
{
  if (vertex->status == NOT_INSERTED)
  {
    min_heap_arr[num_vertices++].r = vertex;
    InitializeVertex(vertex);
    struct list_records *adj_list = vertex->friends;
    while (adj_list != NULL)
    {
      DFS_insert(adj_list->record);
      adj_list = adj_list->next;
    }
  }
}

void print_min_heap_length()
{
  int length = 0;
  for (int i = 0; i < num_vertices; i++)
  {
    if (min_heap_arr[i].r != NULL)
      length++;
  }
  printf("Length of min_heap_arr: %d\n", length);
}

// Each friend f of r is connected via an undirected
// edge whose weight is the distance between r and f.
// Compute the shortest distance and a shortest path to
// all other vertices reachable from r.
// Initially, the status fields in all records are set to zero.
// Distance and pred fields may contain garbage values.
// You need to use the distance function to compute the distance
// between two records.
// You can use min_heap_arr to implement a min heap or
// a linear scan to find a vertex with the minimum distance.
// In addition to distance and pred, you can also update the
// status field in your implementation.
// Don't modify other fields in struct record.
// At the end of this procedure, distance field in each record
// reachable via r, must contain the minimum distance from r;
// and the pred field must contain the predecessor on a shortest
// path.
void compute_sssp(struct record *r)
{
  num_vertices = 0;
  DFS_insert(r); // now all the vertices have been dumped into min_heap_arr
  // print_min_heap_length();

  // Now, every vertex has been initialized, i.e its distance set to infinity, predecessor NULL
  // num_vertices now stores the total number of vertices in our graph
  // now we will be needing the help of the WHITE and not WHITE fields of status field in struct record

  r->distance = 0;

  for (int cnt = 0; cnt < num_vertices - 1; cnt++)
  {
    struct record *u = FindMinDistanceVertex();
    u->status = WHITE;
    struct list_records *adj_list = u->friends;

    while (adj_list != NULL)
    {
      struct record *v = adj_list->record;
      double shorter_dist = u->distance + distance(&u->loc, &v->loc);
      if (v->status == YELLOW && v->distance > shorter_dist)
      {
        v->distance = shorter_dist;
        v->pred = u;
      }
      adj_list = adj_list->next;
    }
  }
}