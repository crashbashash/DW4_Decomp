typedef struct N { int a; int b; int c; int pad; int d; int e; char pad2[32]; void *next; void *f; struct L *owner; } N;
typedef struct L { int pad; int ok; void *head; } L;
void FUN_00113f20(void);
void FUN_00113f78(void);
void FUN_0010e578(N *n, int a, int b, int c, int d, int e, L *l) {
    N *p;
    FUN_00113f20();
    n->f = 0;
    n->next = 0;
    n->a = a;
    n->b = b;
    n->c = c;
    n->d = d;
    n->e = e;
    n->owner = l;
    if (l->head == 0) {
        l->head = n;
    } else {
        for (p = l->head; p->next != 0; p = p->next);
        p->next = n;
    }
    FUN_00113f78();
}
