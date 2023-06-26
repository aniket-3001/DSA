#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node* link;
};


void add_at_pos(struct node* head, int val, int pos) {
    struct node* ptr2 = head;
    struct node* ptr1 = malloc(sizeof(struct node));
    ptr1 -> data = val;
    ptr1 -> link = NULL;

    while (pos != 2) {
        ptr2 = ptr2 -> link;
        pos--;
    }

    ptr1 -> link = ptr2 -> link;
    ptr2 -> link = ptr1;
}


int main() {

    return 0;
}