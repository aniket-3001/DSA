#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node* next;
};

void swap(struct node* a, struct node* b) {
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void bubble_sort(struct node* head) {
    if (!head || !head->next)
        return;

    int swapped;
    struct node *ptr1 = head, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->val > ptr1->next->val) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }

        lptr = ptr1;
    } while (swapped);
}

int count_nodes(struct node* head) {
    int count = 0;
    struct node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int find_median(struct node* head) {
    int n = count_nodes(head);
    if (n == 0) {
        printf("Error: Empty list\n");
        return 0;
    }

    bubble_sort(head);

    if (n % 2 != 0) {
        struct node* middle = head;
        for (int i = 0; i < n / 2; i++) {
            middle = middle->next;
        }
        return middle->val;
    } else {
        struct node* middle = head;
        for (int i = 0; i < n / 2 - 1; i++) {
            middle = middle->next;
        }
        return (int) ((middle->val + middle->next->val) / 2);
    }
}


void insert_node(struct node** head, int new_data) {
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->val = new_data;
    new_node->next = (*head);
    (*head) = new_node;
}

void print_list(struct node* node) {
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    struct node* head = NULL;
    insert_node(&head, 10);
    insert_node(&head, 30);
    insert_node(&head, 20);
    insert_node(&head, 50);
    insert_node(&head, 40);

    printf("Original list:\n");
    print_list(head);

    float median = find_median(head);
    printf("Median: %.2f\n", median);

    return 0;
}
