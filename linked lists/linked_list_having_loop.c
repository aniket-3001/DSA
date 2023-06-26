#include <stdio.h>

struct node {
    int data;
    struct node* next;
};

struct node* FindLoop(struct node* head) {
    struct node *SlowPtr = head, *FastPtr = head;
    int LoopExists = 0;
    while (SlowPtr && FastPtr -> next) {
        SlowPtr = SlowPtr -> next;
        FastPtr = FastPtr -> next -> next;

        if (SlowPtr == FastPtr) {
            LoopExists = 1;
            break;
        }
    }
    if (LoopExists) {
        SlowPtr = head;
        while (SlowPtr != FastPtr) {
            FastPtr = FastPtr -> next;
            SlowPtr = SlowPtr -> next;
        }
        return SlowPtr;
    }
    return NULL;
}
