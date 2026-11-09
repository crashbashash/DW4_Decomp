#include "dw4/igSmartPointer.h"

extern "C" {
void *FUN_0014bff0(void *);
void *igObject_GetAllocator(void *);
}
class Buf { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual int v92(unsigned, int, int);
 int f4_pad[0];
};
struct R : public igObject { int w8; unsigned cap; };

class T { public:
 char pad0[4]; char pad1[16]; int f20; unsigned f24; int f28; char pad2[16]; Buf *f48; int dummy;
 void setBuffer(const igSmartPointer<R> &buffer);
};
inline void T::setBuffer(const igSmartPointer<R> &buffer) {
    R *held = buffer.get();
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    R *previous = (R *)f48;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    f48 = (Buf *)held;
}
extern "C" int Gap__Attrs__igGeometryAttr1_5__vfunc_39(T *arg0, int arg1, unsigned arg2, int arg3) {
    arg0->f20 = arg1;
    arg0->f24 = arg2;
    arg0->f28 = arg3;
    int t = arg0->f20;
    if ((unsigned)(t - 4) <= 1U || t == 2) {
        if (arg0->f48 == 0) {
            arg0->setBuffer(igSmartPointer<R>((R *)FUN_0014bff0(igObject_GetAllocator(arg0))));
        }
        if (((R *)arg0->f48)->cap < arg2) {
            arg0->f48->v92(arg2, 0x20, 0);
        }
    }
    return 1;
}
