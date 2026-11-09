#include "dw4/reflected.h"
extern "C" {
igObject *FUN_002b9500(int);
int FUN_0030b7e0(igObject *, int *, int, int);
int igObject_GetAllocator(igFolder *);
int igObject_Destroy(igObject *);
extern int DAT_004f9a78[4];
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    igSmartPointer(const igSmartPointer &other) : p(other.p) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~igSmartPointer() {
        T *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
    T *get() const { return p; }
};
extern "C" igSmartPointer<igObject> Gap__Core__igFolder__vfunc_23(igFolder *folder, int name) {
    igSmartPointer<igObject> item(FUN_002b9500(igObject_GetAllocator(folder)));
    FUN_0030b7e0(item.get(), &DAT_004f9a78[0], folder->_folderName, name);
    return item;
}
