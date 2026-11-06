/* The holder keeps its address taken through the release method while the release body reads the
 * field directly. */
extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
T *FUN_002c8e10(int);
int FUN_002fe600(T *, int);
int FUN_002fe300(int, unsigned);
int ObjectList_AppendUniqueRetained(T *, int);
unsigned int igMetaObject_CountTree(int);
extern int DAT_004fb410[4];
extern int DAT_00586710[4];
}
struct Holder {
    T *ref;
    inline void release() {
        T **self = &ref;
        if (self) {
            if (ref) {
                --ref->references;
                if (((unsigned long long)(long long)ref->references & 0x7fffffULL) == 0)
                    igObject_Destroy(ref);
            }
        }
    }
};
struct Owner { char p[192]; T *f192; char p2[84]; int f280; };
extern "C" void FUN_002e3f50(int *arg0, Owner *arg1) {
    int meta;
    Holder h;
    T *np;
    T *old;
    unsigned int n;
    unsigned int i;
    h.ref = FUN_002c8e10(arg1->f280);
    np = h.ref;
    if (np) {
        ++np->references;
    }
    old = arg1->f192;
    if (old) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    arg1->f192 = np;
    h.release();
    FUN_002fe600(arg1->f192, DAT_00586710[0]);
    meta = DAT_00586710[0];
    n = igMetaObject_CountTree(meta);
    for (i = 0; i < n; i++) {
        ObjectList_AppendUniqueRetained(arg1->f192, FUN_002fe300(meta, i));
    }
    *arg0 = DAT_004fb410[0];
}
