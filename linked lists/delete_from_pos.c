struct node {
    struct node* next;
    int data;
};

struct node* delete(int pos, struct node* head) {
    struct node* ptr = head;
    int ctr = 1;
    if (pos == 1) {
        head = head->next;
        free(ptr);
    }

    else {
        while (ctr != pos-1) {
            ptr = ptr->next;
            ctr++;
        }

        struct node* node_to_be_deleted = ptr->next;
        ptr->next = node_to_be_deleted->next;
        free(node_to_be_deleted);
    }
    return head;
}