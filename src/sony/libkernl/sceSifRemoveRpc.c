typedef struct N { char pad[56]; struct N *next; } N;
typedef struct { int pad[2]; N *head; } L;
void DIntr(void);
void EIntr(void);
N *sceSifRemoveRpc(N *n, L *l) {
    N *p;
    DIntr();
    p = l->head;
    if (p == n) {
        l->head = p->next;
    } else {
        while (p != 0) {
            if (p->next == n) {
                p->next = n->next;
                break;
            }
            p = p->next;
        }
    }
    EIntr();
    return p;
}
