typedef struct N { char pad[60]; struct N *next; } N;
typedef struct { int pad; int ok; int pad2; N *head; } L;
void DIntr(void);
void EIntr(void);
N *sceSifGetNextRequest(L *l) {
    N *n;
    DIntr();
    n = l->head;
    if (n == 0) {
        l->ok = 0;
    } else {
        l->ok = 1;
        l->head = n->next;
    }
    EIntr();
    return n;
}
