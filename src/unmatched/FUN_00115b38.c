typedef struct Node {
    struct Node *next;
    volatile int id;
    int (*func)(int, int, int, int);
    int arg;
} Node;
extern Node *DAT_0055cd40;
int FUN_00115b38(int id, int a1, int a2, Node *n) {
    int r;
    r = n->func(((int)n << 4) | (id & 0xfe) | 1, a1, a2, n->arg);
    if (r == 0) {
        n->next = DAT_0055cd40;
        DAT_0055cd40 = n;
        n->id = 0;
        return -1;
    }
    return r;
}
