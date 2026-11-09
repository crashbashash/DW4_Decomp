#include "dw4/igSmartPointer.h"
typedef struct Obj : public igObject { } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
typedef struct Hold { char pad[28]; List *l28; } Hold;
typedef struct X { char pad[12]; int f12; } X;
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); int pad; int f4x; };
typedef struct Mk : public igObject { int f8; int f12; Obj *f16; } Mk;
typedef struct A { char pad[12]; X *f12; char pad2[32]; Hold *f48; char pad3[8]; List *f60; List *f64; char pad4[16]; Obj *f84; } A;
extern "C" {
Obj *FUN_001361b0(int);
int FUN_001c5d10(Hold *, int);
int FUN_00460790(A *, int);
int ObjectList_AppendRetained(int, int);
}
#define CLEAR(src) { \
    List *l = (src); \
    int n = l->count; \
    int i; \
    int m; \
    int j; \
    Obj *o; \
    for (i = 0; i < n; i++) { \
        o = l->data[i]; \
        if (o != 0) { \
            o->_refCount = o->_refCount - 1; \
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->count; \
    for (j = 0; j < m; j++) { \
        l->data[j] = 0; \
    } \
    l->count = 0; }
static inline void release(Obj *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}

struct RemovedRef {
    Obj *p;
    RemovedRef(const RemovedRef &);
    ~RemovedRef() {
        release(p);
    }
};
extern "C" RemovedRef FUN_001c5eb0(Hold *, int);
struct ItemType {};
static inline Obj *createItem(ItemType) { return FUN_001361b0(0); }
extern "C" void FUN_00460330(A *arg0) {
    int s5;
    int n3;
    Obj *s3;
    Mk *s2;
    int s0;
    Hold *a1 = arg0->f48;
    List *v1 = a1->l28;
    int var_v1;
    if (v1 != 0) {
        var_v1 = v1->count;
    } else {
        var_v1 = 0;
    }
    if (var_v1 > 0) {
        FUN_001c5eb0(a1, 0);
    }
    CLEAR(arg0->f64)
    CLEAR(arg0->f60)
    if (arg0->f12->f12 != 0) {
        FUN_001c5d10(arg0->f48, arg0->f12->f12);
        FUN_00460790(arg0, arg0->f12->f12);
    }
    n3 = arg0->f60->count;
    s5 = 0;
    if (0 < n3) {
        s0 = 0;
        do {
            {
            igSmartPointer<Obj> item(createItem(ItemType()));
            s3 = *(Obj **)((char *)arg0->f60->data + s0);
            s2 = (Mk *)item.p;
            if (s3 != 0) s3->_refCount = s3->_refCount + 1;
            release(s2->f16);
            s2->f16 = s3;
            ((Ob *)item.p)->v128(0);
            ObjectList_AppendRetained((int)arg0->f64, (int)item.p);
            }
            s5 += 1;
            s0 += 4;
        } while (s5 < n3);
    }
    release(arg0->f84);
    arg0->f84 = 0;
}
