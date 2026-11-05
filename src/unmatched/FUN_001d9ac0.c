typedef struct R { int w0; int refs; } R;
typedef struct L { char pad[8]; int cnt; char pad2[4]; R **arr; } L;
struct B { char pad[32]; L *list; };
struct A { char pad[100]; struct B *b; };
int FUN_001db720();
int ObjectList_AppendRetained();
int igObject_Destroy();

void FUN_001d9ac0(struct A *arg0, int arg1, int arg2) {
    int i;
    int j;
    int n1;
    int n2;
    L *l;
    R *p;

    ObjectList_AppendRetained(arg0->b->list);
    FUN_001db720(arg0, arg0->b, arg2);
    l = arg0->b->list;
    n1 = l->cnt;
    for (i = 0; i < n1; i++) {
        p = l->arr[i];
        if (p != 0) {
            p->refs = p->refs - 1;
            if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    n2 = l->cnt;
    for (j = 0; j < n2; j++) {
        l->arr[j] = 0;
    }
    l->cnt = 0;
}
