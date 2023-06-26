#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;  
};


struct node* rev_list(struct node* head) {
    struct node *temp1, *temp2;
    temp1 = NULL;

    while (head != NULL) {
        temp2 = head -> next;
        head -> next = temp1;
        temp1 = head;
        head = temp2;
    }

    head = temp1;
    return head;
}


int main() {
    struct node* head = NULL;
    struct node* current = NULL;
    int value;

    printf("Enter elements to create a linked list (enter -1 to stop)\n\n");

    do {
        printf("Enter a value: ");
        scanf("%d", &value);

        if (value != -1) {
            struct node* new_node = malloc(sizeof(struct node));
            new_node -> data = value;
            new_node -> next = NULL;

            if (head == NULL) {
                head = new_node;
                current = new_node;
            } else {
                current -> next = new_node;
                current = new_node;
            }
        }
    } while (value != -1);

    // Print the linked list
    printf("\nLinked list elements: ");
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp -> next;
    }
    printf("\n");

    // Reverse the linked list
    head = rev_list(head);

    // Print the reversed linked list
    printf("Reversed linked list elements: ");
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    // Free memory allocated to the linked list
    temp = head;
    while (temp != NULL) {
        struct node* next_node = temp->next;
        free(temp);
        temp = next_node;
    }

    return 0;
}