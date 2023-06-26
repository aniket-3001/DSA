#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node* prev;
    struct node* next;
};


struct node* add_beg(struct node *head, int val) {
    struct node *ptr = malloc(sizeof(struct node));
    ptr -> data = val;
    ptr -> prev = ptr -> next = NULL;
    ptr -> next = head;
    if (head != NULL)
        head -> prev = ptr;
    head = ptr;
    return head;
}



void add_end(struct node *head, int val) {
    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1 -> data = val;
    ptr1 -> prev = ptr1 -> next = NULL;
    struct node *ptr2 = head;

    while (ptr2 -> next != NULL)
        ptr2 = ptr2 -> next;

    ptr2 -> next = ptr1;
    ptr1 -> prev = ptr2;
}



void add_pos(struct node *head, int val, int pos) {
    struct node *ptr1 = malloc(sizeof(struct node));
    ptr1 -> data = val;
    ptr1 -> prev = ptr1 -> next = NULL;
    struct node *ptr2 = head;

    while (pos > 2) {
        ptr2 = ptr2 -> next;
        pos--;
    }

    ptr1 -> next = ptr2 -> next;
    if (ptr2 -> next != NULL)
        ptr2 -> next -> prev = ptr1;
    ptr2 -> next = ptr1;
    ptr1 -> prev = ptr2;
}



int main() {
    struct node *head = malloc(sizeof(struct node));
    head -> data = NULL;
    head -> prev = NULL;
    head -> next = NULL;
    printf("Enter value of head: ");
    scanf("%d", &(head -> data));
    return 0;
}