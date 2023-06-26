#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int next;
};

struct node* FindIntersectingNode(struct node* h1, struct node* h2) {
    int L1 = 0, L2 = 0, diff = 0;
    struct node* tmp1 = h1;
    struct node* tmp2 = h2;

    while (tmp1 != NULL) {
        L1++;
        tmp1 = tmp1 -> next;
    }

    while (tmp2 != NULL) {
        L2++;
        tmp2 = tmp2 -> next;
    }

    if (L1 < L2)
        tmp1 = h2; tmp2 = h1; diff = L2 - L1;
    else
        tmp1 = h1; tmp2 = h2; diff = L1 - L2;

    for (int i = 0, i < diff; i++)
        tmp1 = tmp1 -> next;

    while (tmp1 != NULL && tmp2 != NULL) {
        if (tmp1 == tmp2)
            return tmp1 -> data;

        tmp1 = tmp1 -> next;
        tmp2 = tmp2 -> next;
    }
    return NULL;
}