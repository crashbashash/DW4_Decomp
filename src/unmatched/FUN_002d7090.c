int FUN_002d7130();
int FUN_002d7280();
int List_Resize();
struct It { int a; int b; };
struct Q { char p0[8]; int count; int cap; struct It *items; };
struct O { char p0[12]; struct Q *q; };

static inline int count_of(const struct Q *list) { return list->count; }
void FUN_002d7090(struct O *arg0, int arg1, int arg2) {
    int n; struct Q *q; struct It *it;
    q = arg0->q;
    n = q->count;
    if (n < q->cap) {
        q->count = count_of(q) + 1;
    } else {
        List_Resize(q, n + 1, 8);
    }
    it = (struct It *)((char *)q->items + n * 8);
    it->a = arg1;
    it->b = arg2;
    FUN_002d7280(arg0);
    FUN_002d7130(arg0);
}
