extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(int);
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
}
extern "C" void FUN_002ed5c0(void *);
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct AttrStackList {
    int w0; int rc; int n; int w12; void **data;
};
struct Finder {
    static int Find(AttrStackList *l, K &key) {
        int cnt = l->n;
        int i = 0;
        for (; i < cnt; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" AttrStackList *DAT_00562580[4];
extern "C" void Gap__Sg__igAttrStackManager__vfunc_10(int arg0) {
    int i;
    AttrStackList *p;
    K key((void *)arg0);
    i = Finder::Find(DAT_00562580[0], key);
    if (i >= 0) {
        List_RemoveWordAt(DAT_00562580[0], i);
    }
    p = DAT_00562580[0];
    if (p->n == 0) {
        p->rc = p->rc - 1;
        if ((p->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(p);
        }
        DAT_00562580[0] = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
