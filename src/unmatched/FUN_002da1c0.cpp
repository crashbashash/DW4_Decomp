#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
extern "C" {
struct T : public igObject { int f8; };
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
static inline void release(T *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

struct Mem { T *p; Mem() {} ~Mem() { release(p); } };
static inline void releaseString(const char *h) {
    if (h != 0) {
        int *header = (int *)h - 2;
        int count = ((int *)h)[-1] - 1;
        ((int *)h)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
}
struct StringRef {
    const char *p;
    StringRef(const char *string) : p(string) {}
    ~StringRef() { releaseString(p); }
};
struct O100 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(const char *, int *); };
struct O104 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); };
struct O92 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Mem vX(const char *); };
static inline int openPath(igDriverDatabase *database, const Mem &path) {
    O100 *file = (O100 *)database->_databaseFile;
    int text = path.p->f8;
    if (text == 0) text = DAT_004c22f0[0];
    return file->vX((const char *)text, &DAT_004f96a8[0]);
}
#define POOL() { if (DAT_00586f20[0] == 0) { void *pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } }
#define BLOCK(ctor, strsrc) { \
    igSmartPointer<T> candidate(ctor(igObject_GetAllocator(arg0))); \
    const char *src = strsrc; \
    T *o = candidate.p; \
    POOL() \
    src = StringPool_Intern(DAT_00586f20[0], src); \
    { const char *old = (const char *)o->f8; releaseString(old); o->f8 = (int)src; } \
    s0 = openPath(arg0, ((O92 *)candidate.p)->vX(name.p)); \
    }
extern "C" int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2) {
    int s0;
    const char *tok;
    if (arg1 == 0) {
        tok = 0;
    } else {
        POOL()
        tok = StringPool_Intern(DAT_00586f20[0], arg1);
    }
    StringRef name(tok);
    const char *p5 = name.p;
    if (p5 == 0 || strlen(p5) == 0) {
        POOL()
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)&DAT_004f9698[0]);
        releaseString(name.p);
        name.p = tok;
    }
    {
        int al = igObject_GetAllocator(arg0);
        release((T *)arg0->_databaseFile);
        arg0->_databaseFile = (int)FUN_002c4ca0(al);
    }
    s0 = ((O100 *)arg0->_databaseFile)->vX(name.p, &DAT_004f96a8[0]);
    if (s0 == 0) {
        if (arg2 == 0 || strlen(arg2) == 0) {
            arg2 = FUN_002d1c20(DAT_00586dc8[0]);
        }
        if (arg2 != 0 && strlen(arg2) != 0) {
            BLOCK(FUN_002c43b0, arg2)
        }
    }
    if (s0 == 0) {
        BLOCK(FUN_002c43b0, FUN_002d1c30(DAT_00586dc8[0]))
    }
    if (s0 == 0) {
        release((T *)arg0->_databaseFile);
        arg0->_databaseFile = 0;
        return 0;
    }
    FUN_0030b3c0(arg0->_databaseFileName, *(int *)((char *)s0 + 12));
    FUN_002daac0(arg0, arg0->_databaseFile);
    ((O104 *)arg0->_databaseFile)->vX();
    release((T *)arg0->_databaseFile);
    arg0->_databaseFile = 0;
    return 1;
}
