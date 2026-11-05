#include "dw4/reflected.h"
extern "C" {
struct T { int word0; int references; int f8; };
void igObject_Destroy(T *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int strlen(...);
int igObject_GetAllocator(...);
T *FUN_002c4ca0(int);
T *FUN_002c43b0(int);
const char *FUN_002d1c20(int);
const char *FUN_002d1c30(int);
int FUN_002daac0(...);
int FUN_0030b3c0(...);
extern int DAT_004c22f0[4];
extern int DAT_004f9698[4];
extern int DAT_004f96a8[4];
extern int DAT_00586dc8[4];
extern void *DAT_00586f20[4];
}
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
struct Mem { T *p; Mem() {} ~Mem() {} };
struct O100 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(const char *, int *); };
struct O104 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); };
struct O92 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Mem vX(const char *); };
#define POOL() { if (DAT_00586f20[0] == 0) { void *pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } }
#define RELSTR(held) { const char *h = (held); if (h != 0) { int *hd = (int *)h - 2; int cnt = ((int *)h)[-1] - 1; ((int *)h)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define BLOCK(spN, ctor, strsrc) { \
    spN = ctor(igObject_GetAllocator(arg0)); \
    const char *src = strsrc; \
    T *o = spN; \
    POOL() \
    src = StringPool_Intern(DAT_00586f20[0], src); \
    { const char *old = (const char *)o->f8; RELSTR(old) o->f8 = (int)src; } \
    { Mem r = ((O92 *)spN)->vX(sp5C); \
    { O100 *rcv = (O100 *)arg0->_databaseFile; int a = r.p->f8; if (a == 0) a = DAT_004c22f0[0]; s0 = rcv->vX((const char *)a, &DAT_004f96a8[0]); } \
    if (r.p) { --r.p->references; if (((unsigned long long)(long long)r.p->references & 0x7fffffULL) == 0) igObject_Destroy(r.p); } } \
    { T *q = spN; Rel::go(q); } }
extern "C" int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2);
extern "C" int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2) {
    const char * volatile sp5C;
    T * volatile sp58;
    T * volatile sp54;
    int s0;
    {
        const char *tok;
        if (arg1 == 0) {
            tok = 0;
        } else {
            POOL()
            tok = StringPool_Intern(DAT_00586f20[0], arg1);
        }
        sp5C = tok;
    }
    const char *p5 = sp5C;
    if (p5 == 0 || strlen(p5) == 0) {
        POOL()
        const char *tok = StringPool_Intern(DAT_00586f20[0], (const char *)&DAT_004f9698[0]);
        RELSTR(sp5C)
        sp5C = tok;
    }
    {
        int al = igObject_GetAllocator(arg0);
        Rel::go((T *)arg0->_databaseFile);
        arg0->_databaseFile = (int)FUN_002c4ca0(al);
    }
    s0 = ((O100 *)arg0->_databaseFile)->vX(sp5C, &DAT_004f96a8[0]);
    if (s0 == 0) {
        if (arg2 == 0 || strlen(arg2) == 0) {
            arg2 = FUN_002d1c20(DAT_00586dc8[0]);
        }
        if (arg2 != 0 && strlen(arg2) != 0) {
            BLOCK(sp58, FUN_002c43b0, arg2)
        }
    }
    if (s0 == 0) {
        BLOCK(sp54, FUN_002c43b0, FUN_002d1c30(DAT_00586dc8[0]))
    }
    if (s0 == 0) {
        Rel::go((T *)arg0->_databaseFile);
        arg0->_databaseFile = 0;
        RELSTR(sp5C)
        return 0;
    }
    FUN_0030b3c0(arg0->_databaseFileName, *(int *)((char *)s0 + 12));
    FUN_002daac0(arg0, arg0->_databaseFile);
    ((O104 *)arg0->_databaseFile)->vX();
    Rel::go((T *)arg0->_databaseFile);
    arg0->_databaseFile = 0;
    RELSTR(sp5C)
    return 1;
}
