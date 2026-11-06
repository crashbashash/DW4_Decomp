struct RefObj { int w0; int references; int count; int capacity; void **data; };
extern "C" {
void FUN_002ed5c0(void *);
int FUN_001afc90(void *, void *);
RefObj *FUN_002c8e10(void *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(RefObj *, void *);
void *igAttr_GetMetaObject();
int FUN_002fe290(void *, void *);
extern RefObj *DAT_00562578[4];
extern RefObj *DAT_00562580[4];
extern int DAT_00587038[4];
}
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
void FUN_001afb60(char *arg0) {
    int n;
    int i;
    int idx;
    if (FUN_002fe290(arg0, igAttr_GetMetaObject()) != 0 && *(unsigned char *)(arg0 + 26) == 0) {
        if (DAT_00562578[0] == 0) {
            DAT_00562578[0] = FUN_002c8e10(Memory_GetAllocatorBySelector(DAT_00587038[0]));
        }
        K key(arg0);
        idx = Finder::Find(DAT_00562578[0], key);
        if (idx < 0) {
            ObjectList_AppendRetained(DAT_00562578[0], arg0);
            if (DAT_00562580[0] != 0) {
                n = DAT_00562580[0]->count;
                for (i = 0; i < n; i++) {
                    FUN_001afc90(DAT_00562580[0]->data[i], arg0);
                }
            }
        }
    }
}
}
