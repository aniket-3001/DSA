#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* Insert(struct node* head, struct node* new_node) {
    struct node* ptr = head;

    if (head == NULL || new_node -> data < head -> data) {
        new_node -> next = head;
        head = new_node;
    }

    else {
        while (ptr -> next != NULL && ptr -> next -> data < new_node -> data)
            ptr = ptr -> next;
        
        new_node -> next = ptr -> next;
        ptr -> next = new_node;
    }

    return head;
}
