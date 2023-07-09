#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* prev;
    struct node* next;
};

struct node *rev_list(struct node *head)
{
    struct node *curr_elem = head;       // corresponds to the current element in our DLL iteration
    struct node *prev_elem = NULL;       // corresponds to the element preceeding curr_elem
    struct node *next_elem = head->next; // corresponds to the element proceeding curr_elem
    struct node *temp;                   // temporary for storing the variable next to curr since we break the link

    while (curr_elem->next != NULL)
    {
        temp = curr_elem->next;

        // updating the links
        curr_elem->prev = next_elem;
        curr_elem->next = prev_elem;

        next_elem = temp->next;
        prev_elem = temp->prev;

        curr_elem = temp;
    }

    // updating links for the last element since it couldn't be done in the loop itself without having to return in between
    curr_elem->prev = next_elem;
    curr_elem->next = prev_elem;

    return curr_elem;
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
