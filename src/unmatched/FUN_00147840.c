typedef struct R { int w0; int refs; } R;
typedef struct L { char pad[8]; int cnt; char pad2[4]; R **arr; } L;
struct A { char pad[8]; L *list; };
int List_Reserve();
int igObject_Destroy();

void FUN_00147840(struct A *arg0) {
    int n2; int j; L *l; int n1; int i; R *p;
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
    if (0 >= arg0->list->cnt) {
        List_Reserve(arg0->list, 0, 4);
    }
}
