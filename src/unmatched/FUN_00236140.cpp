extern "C" {
struct NamedObject { int word0; int references; int name; };
void igObject_Destroy(NamedObject *);
NamedObject *FUN_002c43b0(...);
int FUN_002e3850(...);
int FUN_002eb010(...);
int FUN_00304720(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
extern int DAT_004e9740[4];
extern int DAT_004e9748[4];
extern int DAT_004e9750[4];
extern int DAT_00587038[4];
extern int DAT_00586f20[4];
}
struct G { char p[76]; int f76; };
extern G *DAT_00586dc8[4];
struct NamedObjectRef {
    NamedObject *p;
    NamedObjectRef(NamedObject *object) : p(object) {}
    ~NamedObjectRef() { NamedObject *o = p; if (o != 0) { o->references = o->references - 1; if ((o->references & 0x7FFFFF) == 0) igObject_Destroy(o); } }
    NamedObject *get() const { return p; }
    NamedObject *operator->() const { return p; }
};
static inline int internedPool(void) {
    if (DAT_00586f20[0] == 0) {
        int v = FUN_002eb010(0x10);
        if (v != 0) { v = StringPool_Construct(v); }
        DAT_00586f20[0] = v;
    }
    return DAT_00586f20[0];
}
extern "C" void FUN_00236140(void) {
    NamedObjectRef r(FUN_002c43b0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    NamedObject *s0 = r.get();
    int *s1 = (int *)StringPool_Intern(internedPool(), &DAT_004e9740[0]);
    int *old = (int *)s0->name;
    if (old != 0) {
        int *hdr = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->name = (int)s1;
    FUN_002e3850(r.get(), &DAT_004e9748[0]);
    FUN_00304720(DAT_00586dc8[0]->f76, &DAT_004e9750[0], r->name, 1);
}
