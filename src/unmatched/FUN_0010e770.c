typedef struct N { char pad[60]; struct N *next; } N;
typedef struct { int pad; int ok; int pad2; N *head; } L;
void FUN_00113f20(void);
void FUN_00113f78(void);
N *FUN_0010e770(L *l) {
    N *n;
    FUN_00113f20();
    n = l->head;
    if (n == 0) {
        l->ok = 0;
    } else {
        l->ok = 1;
        l->head = n->next;
    }
    FUN_00113f78();
    return n;
}
