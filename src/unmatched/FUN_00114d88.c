typedef struct Node {
    struct Node *next;
    struct Node *prev;
} Node;

extern Node *D_00483520;

Node *FUN_00114d88(Node *node)
{
    Node *next = node->next;
    if (node->prev != 0) {
        node->prev->next = next;
    } else {
        D_00483520 = next;
    }
    if (next != 0) {
        next->prev = node->prev;
    }
    node->prev = 0;
    return next;
}
