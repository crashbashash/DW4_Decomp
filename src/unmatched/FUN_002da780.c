struct L { int p0; int p1; int n; int cap; int *arr; };
struct S { char pad[40]; struct { int a; int b; int c; } *src; int f44; int f48; int f52; };
struct L *FUN_002c8450();
int FUN_002dae40();
int List_Resize();
int igObject_GetAllocator();
extern int DAT_004c22f0[4];
static inline int n_of(const struct L *list) { return list->n; }
struct L *FUN_002da780(struct S *s) {
    int cnt;
    int r;
    struct L *l;
    int v;

    l = FUN_002c8450(igObject_GetAllocator());
    s->f44 = 1;
    v = s->src->c;
    if (v == 0) {
        v = DAT_004c22f0[0];
    }
    s->f52 = v;
    do {
        r = FUN_002dae40(s);
        if (r != 0) {
            cnt = l->n;
            if (cnt < l->cap) {
                l->n = n_of(l) + 1;
            } else {
                List_Resize(l, cnt + 1, 4);
            }
            l->arr[cnt] = r;
        }
    } while (r != 0);
    return l;
}
