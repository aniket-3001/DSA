struct node
{
    int val;
    struct node *next;
};

struct node *reverse_list(struct node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    struct node *reversed_list_head = reverse_list(head->next);
    head->next->next = head;
    head->next = NULL;
    return reversed_list_head;
}
