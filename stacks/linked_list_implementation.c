#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

void add_front(struct node **head, struct node* n) {
    n->next = *head;
    *head = n;
}

struct del_info {
    struct node *head;
    struct node *deleted_node;
};

struct del_info del_front(struct node *head) {
    if (head == NULL) {
        printf("cannot delete from an empty list");
        exit(1);
    }

    struct del_info ret;
    ret.head = head->next;
    ret.deleted_node = head;
    return ret;
}

struct stack {
    struct node* head;
};

struct node* allocate_node(int val) {
    struct node *n = malloc(sizeof(struct node));

    if (n == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    n->data = val;
    n->next = NULL;

    return n;
}

struct stack* create_stack() {
    struct stack *S = malloc(sizeof(struct stack));

    if (S == NULL) {
        printf("failed to allocate memory");
        return NULL;
    }

    S->head = NULL;
    return S;
}

int is_empty(struct stack *S) {
    if (S->head == NULL)
        return 1;
    return 0;
}

void push(struct stack *S, int val) {
    struct node *n = allocate_node(val);
    add_front(&(S->head), n);
}

int pop(struct stack *S) {
    if (is_empty(S)) {
        printf("stack underflow");
        exit(1);
    }

    struct del_info ret = del_front(S->head);
    struct node *deleted_node = ret.deleted_node;
    int retval = deleted_node->data;
    free(deleted_node);
    S->head = ret.head;
    return retval;
}

int top(struct stack *S) {
    if (is_empty(S)) {
        printf("stack is empty");
        exit(0);
    }
    return S -> head -> data;
}

int size(struct stack *S) {
    int cnt = 0;
    struct node *curr = S -> head;

    while (curr != NULL) {
        cnt++;
        curr = curr -> next;
    }
    return cnt;
}

void dispose_stack(struct stack *S) {
    struct node *curr = S -> head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr -> next;
        free(temp);
    }
    free(S);
}

void print_stack(struct stack *S) {
    struct node *curr = S -> head;
    while (curr != NULL) {
        printf("%d ", curr -> data);
        curr = curr -> next;
    }
    printf("\n");
}

int main() {
    struct stack *S = create_stack();
    
    // pushing elements into the stack
    push(S, 10);
    push(S, 20);
    push(S, 30);
    push(S, 40);
    
    // printing the size of the stack
    printf("Size of stack: %d\n", size(S));
    
    // printing the top element of the stack
    printf("Top element: %d\n", top(S));
    
    // popping elements from the stack
    int val = pop(S);
    printf("Popped element: %d\n", val);
    
    val = pop(S);
    printf("Popped element: %d\n", val);
    
    // printing the size of the stack
    printf("Size of stack: %d\n", size(S));
    
    // printing the elements of the stack
    printf("Elements of stack: ");
    print_stack(S);
    
    // freeing the memory used by the stack
    dispose_stack(S);
    
    return 0;
}
