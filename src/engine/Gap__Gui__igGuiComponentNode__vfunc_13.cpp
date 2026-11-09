#include "dw4/reflected.h"
extern "C" int igObject_Destroy(void *);
struct Vec3 { int x; int y; int z; };
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
struct Node : igObject { int fc_pad; igObject *child; };
extern "C" {
igObject *FUN_0018a660(int);
int FUN_001900d0(igObject *, Vec3 *);
int FUN_001d3550(Node *);
int igObject_GetAllocator(Node *);
void Gap__Gui__igGuiComponentNode__vfunc_13(Node *self) {
    Vec3 origin;
    FUN_001d3550(self);
    igSmartPointer<igObject> transform(FUN_0018a660(igObject_GetAllocator(self)));
    origin.x = 0;
    origin.y = 0;
    origin.z = 0;
    FUN_001900d0(transform.get(), &origin);
    igObject *retained = transform.get();
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    igObject *previous = self->child;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->child = retained;
}
}
