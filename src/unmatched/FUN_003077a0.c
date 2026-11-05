typedef struct R { int w0; int refs; } R;
typedef struct L { char pad[8]; int cnt; char pad2[4]; R **arr; } L;
struct A { char pad[8]; int w8; char pad2[4]; L *list; };
int ObjectList_ClearRetainedPreserveCount();
int igObject_Destroy();

void FUN_003077a0(struct A *arg0) {
    int n2;
    int i;
    int n1;
    int j;
    L *l;
    R *p;

    l = arg0->list;
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
    ObjectList_ClearRetainedPreserveCount(arg0->w8, n2);
}
