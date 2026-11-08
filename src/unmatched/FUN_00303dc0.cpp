struct RefObj { int w0; int references; int count; int capacity; void **data; };
struct Holder { char pad[8]; RefObj *l; };
extern "C" void FUN_002ed5c0(void *);
struct K { volatile int p; K(int x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
inline int indexOf(RefObj *l, const K &v) {
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
extern "C" {
void *igProperty_FindByName(RefObj *, int, int);
extern int DAT_00585be0[4];
int FUN_00303dc0(Holder *arg0, int arg1);
}
int FUN_00303dc0(Holder *arg0, int arg1) {
    void *v = igProperty_FindByName(arg0->l, DAT_00585be0[0], arg1);
    if (v == 0) {
        return -1;
    }
    RefObj *l = arg0->l;
    return indexOf(l, K((int)v));
}
