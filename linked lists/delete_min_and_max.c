#include <stdio.h>
#include <stdlib.h>


struct node {
    int val;
    struct node *next;
};


struct delete_info {
    struct node *head; // head of the new linked list
    struct node *min; // the deleted node that contains minimum value
    struct node *max; // the deleted node that contains maximum value
};


struct delete_info delete_min_max(struct node *head);

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
            new_node->val = value;
            new_node->next = NULL;

            if (head == NULL) {
                head = new_node;
                current = new_node;
            } 
            else {
                current->next = new_node;
                current = new_node;
            }
        }

    } 
    while (value != -1);

    // Print the linked list
    printf("\nLinked list elements: ");
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp -> val);
        temp = temp -> next;
    }
    printf("\n");

    // Delete minimum and maximum elements of the linked list
    struct delete_info data = delete_min_max(head);
    head = data.head;

    // Print the modified linked list
    printf("Modified linked list elements: ");
    temp = head;
    while (temp != NULL) {
        printf("%d ", temp -> val);
        temp = temp -> next;  
    }
    printf("\n\n");

    // print values contained by min and max nodes
    printf("min: %d", (data.min) -> val);
    printf("\n");
    printf("max: %d", (data.max) -> val);

    // Free memory allocated to the linked list
    temp = head;
    while (temp != NULL) {
        struct node* next_node = temp -> next;
        free(temp);
        temp = next_node;
    }

    return 0;
}


struct delete_info delete_min_max(struct node *head) {
    struct delete_info data;
    data.head = NULL;
    data.min = NULL;
    data.max = NULL;

    if (head == NULL)
        return data; // in this case the min and max elements would be displayed as 0

    struct node *min_prev = NULL;
    struct node *max_prev = NULL;
    struct node *min_node = head;
    struct node *max_node = head;
    struct node *prev = NULL;
    struct node *curr = head;

    while (curr != NULL) {
        if (curr -> val < min_node -> val) {
            min_node = curr;
            min_prev = prev;
        }
        if (curr -> val > max_node -> val) {
            max_node = curr;
            max_prev = prev;
        }
        prev = curr;
        curr = curr -> next;
    }

    curr = NULL;
    prev = NULL;

    if (head -> next == NULL) { // case where there is only one element present in the array
        data.head = NULL;
        data.min = head;
        data.max = head;
        // free(head);
    }

    else {
        if (max_node == head) {
            min_prev -> next = min_node -> next;
            head = head -> next;
        }

        else if (min_node == head) {
            if (max_prev == min_node) {
                max_prev -> next = max_node -> next;
                head = head -> next;
            }
            else {
                head = head -> next;
                max_prev -> next = max_node -> next;
            }
        }

        else {
            if (max_prev == min_node) {
                max_prev -> next = max_node -> next;
                min_prev -> next = min_node -> next;
            }

            else {
                min_prev -> next = min_node -> next;
                max_prev -> next = max_node -> next;
            }
        }

        data.head = head;
        data.min = min_node;
        data.max = max_node;

        // free(min_node);
        // free(max_node);
    }

    return data;
}

