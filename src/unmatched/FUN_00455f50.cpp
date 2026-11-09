#include "dw4/igSmartPointer.h"

struct Obj : public igObject { };
struct Y { char pad[8]; int f8; char pad2[8]; float f20; };
struct Z { char pad[24]; float f24; unsigned char f28; char pad2[3]; Obj *f32; };
extern "C" {
Obj *FUN_0019f630(...);
int FUN_001c5790(...);
int igObject_GetAllocator(...);
void FUN_00455f50(Z *arg0, Y *arg1);
}

static inline void setPick(Z *z, const igSmartPointer<Obj> &value) {
    Obj *held = value.get();
    Obj *old;
    if (held != 0) held->_refCount = held->_refCount + 1;
    old = z->f32;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    z->f32 = held;
}
void FUN_00455f50(Z *arg0, Y *arg1) {
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        setPick(arg0, igSmartPointer<Obj>(FUN_0019f630(igObject_GetAllocator(arg0))));
        FUN_001c5790(arg0->f32, s1);
    }
}
