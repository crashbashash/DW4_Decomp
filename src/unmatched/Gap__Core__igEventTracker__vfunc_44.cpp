#include "dw4/igSmartPointer.h"
struct R { int a; R(int x) : a(x) {} };
struct Tk { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42();  virtual void v180(); int p4; int p8; unsigned flags; };
struct Ob : public igVirtualObject { virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25();  virtual int v112(int); char pad0[57]; char f65; char pad1[214]; igObject *f280; igObject *f284; igObject *f288; };
extern "C" {
Ob *FUN_002c37e0(igObject *);
int FUN_002d8620(Ob *, Tk *, int, int);
igObject *igObject_GetAllocator(Tk *);
extern int DAT_004c1ed8[4];
}
static inline bool hasFlag(const Tk *tracker, unsigned mask) { return (tracker->flags & mask) != 0; }

extern "C" R Gap__Core__igEventTracker__vfunc_44(Tk *arg1, int arg2) {
    bool had;
    bool trk;
    int r;
    igObject *a;
    igObject *old;
    Ob *o;
    had = hasFlag(arg1, 2);
    arg1->flags = arg1->flags | 2;
    trk = hasFlag(arg1, 4);
    if (trk == false) {
        arg1->v180();
    }
    {
    igSmartPointer<Ob> sp7C(FUN_002c37e0(igObject_GetAllocator(arg1)));
    a = igObject_GetAllocator(arg1);
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f280;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f280 = a;
    a = igObject_GetAllocator(arg1);
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f288;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f288 = a;
    a = igObject_GetAllocator(arg1);
    o = sp7C.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    old = o->f284;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0) igObject_Destroy(old);
    }
    o->f284 = a;
    sp7C.p->f65 = 1;
    FUN_002d8620(sp7C.p, arg1, DAT_004c1ed8[0], 0);
    r = sp7C.p->v112(arg2);
    }
    arg1->flags = had ? (arg1->flags | 2) : (arg1->flags & ~2);
    return R(r);
}
