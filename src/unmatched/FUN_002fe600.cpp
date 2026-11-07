extern "C" void List_InsertWords(void *, int, int, ...);
struct M { char p[4]; int refs; char p8[48]; M *parent; };
struct L { char p[8]; int count; char p12[4]; void **data; };
extern "C" void FUN_002ed5c0(void *);
struct K { volatile int p; K(int x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
inline int indexOf(L *l, const K &v) {
    int i;
    int n = l->count;
    void *key = (void *)v.p;
    for (i = 0; i < n; i++) {
        if (key == l->data[i]) {
            return i;
        }
    }
    return -1;
}
struct Ref { M *p; Ref(M *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } } };

extern "C" int FUN_002fe600(L *arg0, M *arg1);
int FUN_002fe600(L *arg0, M *arg1) {
    int n;
    int i;

    i = indexOf(arg0, K((int)arg1));
    if (i != -1) {
        return i;
    }
    n = arg0->count;

    while (i == -1 && arg1 != 0) {
        Ref t(arg1);
        List_InsertWords(arg0, n, 1, &t);
        arg1 = arg1->parent;
        i = indexOf(arg0, K((int)arg1));
    }
    return *(volatile int *)&arg0->count - 1;
}
