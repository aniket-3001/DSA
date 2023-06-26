// Propose a data structure called MaxStack that supports push, pop, and
// find_max operations in O(1) operations. MaxStack stores elements of type int. You are
// given a cmp_val routine that compares two values of type int and returns -1, 0, or 1 if
// the first value is less than, equals to, or greater than the second value, respectively. You
// are not allowed to store multiple copies of an existing stack element or the input value
// during the push operation. You can use a linked list in your implementation.
// a. What is the type of a MaxStack node?
// b. Write the pseudocode for push, pop, and find_max routines. You can use
// list_empty, insert_front, delete_front, and cmp_val directly in your
// pseudocode.

#include <stdio.h>
#include <stdlib.h> // Added for the 'exit' and 'free' functions

struct node
{
    int val;
    struct node *next;
    struct node *max;
};

int find_max(struct node *S)
{
    // S is a handle to stack
    // returns the maximum element in the stack
    if (S == NULL)
    {
        printf("error: stack empty\n");
        exit(1);
    }
    return S->max->val;
}

void push(struct node **S, int val)
{
    // S is a handle to stack
    // val is the value that needs to be pushed on the stack
    struct node *n = (struct node *)malloc(sizeof(struct node));
    n->val = val;
    n->next = *S;
    n->max = n;
    if (*S != NULL && (*S)->max->val > val)
        n->max = (*S)->max;
    *S = n;
}

int pop(struct node **S)
{
    // S is a handle to stack
    // return the last inserted value
    if (*S == NULL)
    {
        printf("error: stack empty\n");
        exit(1);
    }
    struct node *deleted_node = *S;
    int retval = deleted_node->val;
    *S = (*S)->next;
    free(deleted_node);
    return retval;
}
