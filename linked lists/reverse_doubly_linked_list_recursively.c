#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node* rev_list(struct node* head) {
    if (head == NULL || head -> next == NULL) // Base case: empty list or list with one element
        return head;

    struct node* rest = rev_list(head -> next); // Recursively reverse the rest of the list

    head -> prev = head -> next; // Swap prev and next pointers for the current node
    head->next = rest;

    if (rest != NULL)
        rest -> prev = head;

    return head; // Return the new head of the reversed list
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
