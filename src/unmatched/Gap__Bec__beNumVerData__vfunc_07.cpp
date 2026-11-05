extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int Gap__Core__igObject__vfunc_07(...);
int igMetaObject_CountInstances(...);
void *igObject_GetAllocator(...);
void *Memory_GetAllocatorBySelector(...);
T *FUN_0034de60(...);
int ObjectList_AppendRetained(...);
extern unsigned char GPR_00554c14;
extern int DAT_00587110[4];
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Ref { T *p; Ref(T *x) : p(x) {} ~Ref() { Rel::go(p); } };
struct Obj {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual int v88();
    int f4; int f8; void *list;
};
extern "C" void Gap__Bec__beNumVerData__vfunc_07(Obj *arg0, int arg1) {
    int i;
    void *alloc;
    Gap__Core__igObject__vfunc_07(arg0, arg1);
    igMetaObject_CountInstances(arg0->v88(), 1);
    if (!(arg1 & 0xFF)) {
        i = 0;
        do {
            alloc = igObject_GetAllocator(arg0);
            alloc = (GPR_00554c14 != 0) ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            { Ref sp3C(FUN_0034de60(alloc));
            ObjectList_AppendRetained(arg0->list, sp3C.p); }
            i += 1;
        } while (i < 6);
    }
}
