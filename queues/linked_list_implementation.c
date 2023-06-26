#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct queue
{
    struct node *head;
    struct node *tail;
};

struct queue *create_queue()
{
    struct queue *Q = malloc(sizeof(struct queue));

    if (Q == NULL)
    {
        printf("Failed to allocate memory");
        return NULL;
    }

    Q->head = Q->tail = NULL;

    return Q;
}

int is_empty(struct queue *Q)
{
    return (Q->head == NULL);
}

void enqueue(struct queue *Q, int val)
{
    struct node *new_node = malloc(sizeof(struct node));

    if (new_node == NULL)
    {
        printf("Failed to allocate memory");
        exit(0);
    }

    new_node->data = val;
    new_node->next = NULL;

    if (is_empty(Q))
    {
        Q->head = Q->tail = new_node;
    }
    else
    {
        Q->tail->next = new_node;
        Q->tail = new_node;
    }
}

int dequeue(struct queue *Q)
{
    if (is_empty(Q))
    {
        printf("Underflow");
        exit(0);
    }

    struct node *temp = Q->head;
    int val = temp->data;

    Q->head = Q->head->next;
    free(temp);

    if (Q->head == NULL)
    {
        Q->tail = NULL;
    }

    return val;
}
