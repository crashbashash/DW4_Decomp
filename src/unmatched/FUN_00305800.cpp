class Alloc {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual char *alloc(int);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void release(char *);
};
extern "C" {
extern char DAT_004fb0c8[];
extern char DAT_004fb0d0[];
extern char DAT_004fb0d8[];
extern char DAT_004fb0e0[];
extern char DAT_004fb0f0[];
extern int DAT_00586f20[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
extern char GPR_00554c2c;
int sprintf(...);
int strlen(...);
struct Rec { char p[12]; char *name; };
Rec *FUN_002d7c50(int, int);
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int *StringPool_Intern(int, char *);
Alloc *Memory_GetAllocatorBySelector(int);
Alloc *igObject_GetAllocator(void *);
}
struct RecoveryString {
    int *p;
    RecoveryString() : p(0) {}
    RecoveryString(int *x) : p(x) {}
    ~RecoveryString() {
        int *q = p;
        if (q != 0) {
            int *t = (int *)((char *)q - 8);
            int v = t[1] - 1;
            t[1] = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
    }
};

extern "C" int FUN_00305800(RecoveryString *arg0, void *arg1, int *arg2, int arg3, int arg4, char *arg5, int arg6) {
    char spC0[256];
    char spA0[32];
    Alloc *a;
    char *buf;
    char *w;
    int i;
    int v;

    if (arg5 == 0) arg5 = &GPR_00554c2c;
    if (arg6 == -1) arg6 = strlen(arg5) + 5;
    sprintf(spA0, DAT_004fb0c8, arg6);
    a = igObject_GetAllocator(arg1);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587060[0]);
    buf = a->alloc(arg3 * (strlen(spA0) + 0x80));
    w = buf;
    for (i = 0; i < arg3; i++) {
        sprintf(spC0, spA0, arg5);
        if (i == 0) {
            if (arg3 > 1) {
                sprintf(w, DAT_004fb0d0, spC0);
            } else {
                goto block12;
            }
        } else {
block12:
            sprintf(w, DAT_004fb0d8, spC0);
        }
        w = buf + strlen(buf);
        if (arg4 != 0) {
            Rec *r = FUN_002d7c50(arg4, *arg2);
            if (r != 0) {
                sprintf(w, DAT_004fb0e0, r->name);
            } else {
                sprintf(w, DAT_004fb0f0);
            }
        } else {
            sprintf(w, DAT_004fb0f0);
        }
    }
    int *pi;
    if (buf == 0) {
        pi = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            v = FUN_002eb010(16);
            if (v != 0) v = StringPool_Construct(v);
            DAT_00586f20[0] = v;
        }
        pi = StringPool_Intern(DAT_00586f20[0], buf);
    }
    RecoveryString sp1CC(pi);
    a = igObject_GetAllocator(arg1);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587060[0]);
    a->release(buf);
    int *src = sp1CC.p;
    arg0->p = src;
    if (arg0->p != 0) *(int *)((char *)arg0->p - 4) = *(int *)((char *)arg0->p - 4) + 1;
    return 0;
}
