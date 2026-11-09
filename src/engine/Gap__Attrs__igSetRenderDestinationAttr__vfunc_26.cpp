#include "dw4/igSmartPointer.h"
class Destination : public igObject { public: };
class Renderable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(int); };
struct Attr { char p[12]; Destination *f12; };
extern "C" {
Destination *FUN_001341b0(...);
int igObject_GetAllocator(...);
void Gap__Attrs__igSetRenderDestinationAttr__vfunc_26(Attr *self, int value);
}

static inline void setDestination(Attr *self, const igSmartPointer<Destination> &destination) {
    Destination *held = destination.get();
    Destination *previous;
    if (held != 0) {
        held->_refCount = held->_refCount + 1;
    }
    previous = self->f12;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->f12 = held;
}
void Gap__Attrs__igSetRenderDestinationAttr__vfunc_26(Attr *self, int value) {
    if (self->f12 == 0) {
        setDestination(self, igSmartPointer<Destination>(FUN_001341b0(igObject_GetAllocator())));
    }
    ((Renderable *)self->f12)->vX(value);
}
