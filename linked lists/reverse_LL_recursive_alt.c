#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

/*
 * Reverse a linked list recursively
 *
 * Arguments:
 * - head: A pointer to the head node of the linked list to be reversed
 *
 * Returns:
 * - A pointer to the new head node of the reversed list
 * 
 * Algorithm:
 * The function reverses the list by recursively reversing the rest of the list
 * starting from the second element, and then linking the first element (head)
 * to the end of the reversed rest.
 * 
 * Base Cases:
 * - If the list is empty (i.e., head is NULL), return NULL.
 * - If the list contains only one element (i.e., head->next is NULL), return head.
 * 
 * Recursive Case:
 * - Store the second element of the list in a temporary variable.
 * - Unlink the first element (head) from the rest of the list by setting head->next to NULL.
 * - Recursively reverse the rest of the list (i.e., starting from the second element).
 * - Link the second element (stored earlier) to the end of the reversed rest by setting its
 *   next pointer to head.
 * - Return the pointer to the new head node of the reversed list (which is the end of the original list).
 */ 
struct node* rev_list(struct node* head) {

    if (head == NULL || head -> next == NULL) // Base case: empty list has no reverse and list with one element is its own reverse
        return head;

    struct node* second_ele = head -> next;
    head -> next = NULL; // Unlink list from rest
    struct node* reverseRest = rev_list(second_ele); // Recursively reverse the rest of the list
    second_ele -> next = head; // Link the second element to the end of the reversed rest

    return reverseRest; // Return the pointer to the new head node of the reversed list
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
            new_node->data = value;
            new_node->next = NULL;

            if (head == NULL) {
                head = new_node;
                current = new_node;
            } else {
                current->next = new_node;
                current = new_node;
            }
        }
    } while (value != -1);

    // Print the linked list
    printf("\nLinked list elements: ");
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
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