#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* link;
};

int main() {
    struct node* head = NULL; // Initialize head pointer to NULL
    char ch = 'y'; // Variable to store user choice to continue or stop
    int val; // Variable to store user input for data
    struct node* current; // Pointer to the current node

    while (ch == 'y' || ch == 'Y') {

        // Allocate memory for a new node
        current = malloc(sizeof(struct node));

        // Get user input for data
        printf("Enter value: ");
        scanf("%d", &val);

        // Assign data to the new node
        current -> data = val;
        current -> link = NULL;

        if (head == NULL)
            // If the list is empty, make the new node the head
            head = current;
        
        else {
            // Otherwise, append the new node to the end of the list
            struct node* temp = head;

            while (temp -> link != NULL)
                temp = temp -> link;

            temp -> link = current;
        }

        // Ask user if they want to continue
        printf("Do you want to continue? (y/n): ");
        scanf("%c", &ch);
    }

    // Print the elements in the linked list
    printf("Linked list elements: ");
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d", temp -> data);
        temp = temp -> link;
    }
    printf("\n");

    // Free memory allocated for nodes
    struct node* temp2;
    temp = head;
    while (temp != NULL) {
        temp2 = temp -> link;
        free(temp);
        temp = temp2;
    }

    return 0;
}
