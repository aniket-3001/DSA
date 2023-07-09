#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;  
};


struct node *rev_list(struct node *head)
{
    struct node *curr = head; // corresponds to the current element in our LL iteration
    struct node *prev = NULL; // corresponds to the element preceeding curr
    struct node *temp;        // temporary for storing the variable next to curr since we break the link

    while (curr != NULL)
    {
        temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    // Take care that when we reach the last iteration, i.e when curr corresponds to the last element of our LL, curr would get updated to NULL while prev would store the last element which is also the new head of our LL and needs to be returned, hence, return prev
    return prev; // new head
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
