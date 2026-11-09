#include "dw4/reflected.h"
extern "C" {
igObject *FUN_0019f480(int);
igObject *FUN_0019f630(int);
int FUN_001c5730(igObject *, int);
int FUN_001d6410(void *, int, igObject *);
int igObject_Destroy(void *);
int igObject_GetAllocator(void *);
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    T *get() const { return p; }
};
struct O { char pad[20]; int f20; int f24; igObject *f28; };
extern "C" void FUN_001d65e0(O *self) {
    igObject *created = FUN_0019f480(igObject_GetAllocator(self));
    if (created != 0) {
        created->_refCount = created->_refCount + 1;
    }
    igObject *previous = self->f28;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->f28 = created;
    igObject *held = self->f28;
    held->_refCount = held->_refCount - 1;
    if ((held->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(held);
    }
    igSmartPointer<igObject> second(FUN_0019f630(igObject_GetAllocator(self)));
    FUN_001c5730(second.get(), self->f20);
    FUN_001d6410(self, self->f20, second.get());
}
