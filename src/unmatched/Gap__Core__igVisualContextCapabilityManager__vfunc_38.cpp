/* The lookup key lives in a stack object with a destructor (kept in memory, load hoisted), emitted
 * dtor is the retail copy at 0x002e2300 (config/SLUS-20836/unit-objects.json duplicates). */
struct RefObj { int w0; int references; int count; int capacity; void **data; };
extern "C" {
int Gap__Core__igObject__vfunc_10(void *);
int List_RemoveWordAt(void *, int);
int igObject_Destroy(void *);
extern RefObj *DAT_00560758[4];
}
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
void Gap__Core__igVisualContextCapabilityManager__vfunc_38(char *arg0) {
    int i;
    RefObj *o;
    RefObj *l;
    o = *(RefObj **)(arg0 + 56);
    --o->references;
    if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
        igObject_Destroy(o);
    }
    K key(arg0);
    i = Finder::Find(DAT_00560758[0], key);
    if (i >= 0) {
        List_RemoveWordAt(DAT_00560758[0], i);
    }
    l = DAT_00560758[0];
    if (l->count == 0) {
        --l->references;
        if (((unsigned long long)((long long)l->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(l);
        }
        DAT_00560758[0] = 0;
    }
    Gap__Core__igObject__vfunc_10(arg0);
}
}
