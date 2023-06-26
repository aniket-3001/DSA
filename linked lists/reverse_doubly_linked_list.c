#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* prev;
    struct node* next;
};

struct node* rev_list(struct node* head) {
    struct node* ptr1 = head;
    struct node* ptr2 = ptr1 -> next;

    ptr1 -> next = NULL;
    ptr1 -> prev = ptr2;

    while (ptr2 != NULL) {
        ptr2 -> prev = ptr2 -> next;
        ptr2 -> next = ptr1;
        ptr1 = ptr2;
        ptr2 = ptr2 -> prev;
    }

    head = ptr1;
    return head;
}

struct node* create_list(struct node* head) {
    int val;
    struct node* curr;
    printf("Enter elements to create a linked list (enter -1 to stop)\n\n");

    do {
        printf("Enter element: ");
        scanf("%d", &val);

        if (val != -1) {
            struct node *new_node = malloc(sizeof(struct node));
            new_node -> data = val;
            new_node -> next = NULL;
            new_node -> prev = NULL;

            if (head == NULL) {
                head = new_node;
                curr = new_node;
            } 

            else {
                curr -> next = new_node;
                new_node -> prev = curr;
                curr = new_node;
            }
        }

    }
    while (val != -1);

    return head;
}

void print_list(struct node* head) {
    while (head != NULL) {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
}


int main() {
    struct node *head = NULL;
    head = create_list(head);

    struct node *ptr = head;

    print_list(head);
    
    head = rev_list(head);

    print_list(head);

    return 0;
}