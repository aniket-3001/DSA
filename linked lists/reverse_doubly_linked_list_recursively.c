// searched the whole of yt to get a nice recurive implementation of this shit, however all tutorials turned out to be trash. I implemented the following by taking inspiration from the code of reversing singly linked list. Do perform a dry run, you would be able to easily understand this code if you've understood the one for the singly LL.

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

struct node *rev_list(struct node *head)
{
    if (head == NULL) // Base case: empty list or list with one element
        return head;

    if (head->next == NULL)
    {
        head->next = head->prev;
        head->prev = NULL;
        return head;
    }

    struct node *next_elem = head->next;
    struct node *prev_elem = head->prev;

    head->next = NULL;
    head->prev = NULL;

    struct node *RestReverse = rev_list(next_elem);

    head->prev = next_elem;
    head->next = prev_elem;
    return RestReverse;
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
