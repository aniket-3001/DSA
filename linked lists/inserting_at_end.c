#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *link;
};


void add_at_end(struct node *head, int val) {
    struct node *ptr, *temp;
    ptr = head;
    temp = malloc(sizeof(struct node));

    temp -> data = val;
    temp -> link = NULL;

    while (ptr -> link != NULL)
        ptr = ptr -> link;

    ptr -> link = temp;
}
