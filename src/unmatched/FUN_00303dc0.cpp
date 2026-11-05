struct RefObj { int w0; int references; int count; int capacity; void **data; };
struct Holder { char pad[8]; RefObj *l; };
extern "C" void FUN_002ed5c0(void *);
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Finder {
    static int Find(RefObj *l, K &key) {
        int n = l->count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
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
    K key(v);
    return Finder::Find(l, key);
}
