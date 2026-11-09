#include "dw4/igSmartPointer.h"
extern "C" {
int igObject_GetAllocator(void *);
}
struct R : public igObject { int w8; int wc; };
struct X { char p[12]; R *f12; R *f16; };
struct A { char p[8]; X *f8; int f12; int f16; R *f20; char q[4]; int f28; };
extern "C" {
int FUN_001c5d10(R *, int);
R *FUN_0044e990(int);
R *FUN_0044ecb0(int);
R *FUN_0044f0b0(int);
int FUN_00457e90(R *, int);
int Gap__Core__igObject__vfunc_11(A *);
int ObjectList_AppendRetained(int, R *);
}

static inline void set(R *&field, R *value) {
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    R *old = field;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    field = value;
}
extern "C" void Gap__Gui__igGuiSystem__vfunc_13(A *self) {
    Gap__Core__igObject__vfunc_11(self);
    igSmartPointer<R> first(0);
    int allocator = igObject_GetAllocator(self);
    first.release();
    first.p = FUN_0044f0b0(allocator);
    FUN_00457e90(first.get(), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    igSmartPointer<R> second(FUN_0044ecb0(igObject_GetAllocator(self)));
    second.get()->wc = (int)self;
    FUN_00457e90(second.get(), self->f12);
    ObjectList_AppendRetained(self->f16, second.get());
    allocator = igObject_GetAllocator(self);
    first.release();
    first.p = FUN_0044e990(allocator);
    FUN_00457e90(first.get(), self->f12);
    ObjectList_AppendRetained(self->f16, first.get());
    FUN_001c5d10(self->f20, self->f28);
    R *value = self->f20;
    X *x = self->f8;
    set(x->f12, value);
    value = (R *)self->f12;
    x = self->f8;
    set(x->f16, value);
}
