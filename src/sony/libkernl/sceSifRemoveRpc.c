typedef struct N { char pad[56]; struct N *next; } N;
typedef struct { int pad[2]; N *head; } L;
void FUN_00113f20(void);
void FUN_00113f78(void);
N *sceSifRemoveRpc(N *n, L *l) {
    N *p;
    FUN_00113f20();
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
    FUN_00113f78();
    return p;
}
