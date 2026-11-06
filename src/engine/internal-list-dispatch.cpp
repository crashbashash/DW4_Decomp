/* Exact constructor/free dispatch. Virtual classes are ABI views; do not instantiate. */
#include "dw4/reflected.h"

/* The raw pointer list is the ancestor of the retained list (__internalObjectList):
 * object header, then data buffer +8 and signed count +12, the layout of
 * __internalNonRefCountedObjectList.  It stamps vtable 0x00532770 and takes its
 * buffer from the object's allocator (docs/engine/internal-object-lists.md). */

/* 0x002ea4f0 - ObjectPointerList_Construct: build the header, run the raw
 * initializer, then ask the object's allocator (virtual slot 216, allocate) for
 * the 16-byte data buffer (docs/engine/internal-object-lists.md). */
extern "C" {
int ObjectPointerList_Init(...);
int igObject_ConstructHeader(...);
void **igObject_GetAllocator(...);
/* vtable of the raw pointer list (finding #882) */
extern int g_ObjectPointerList_vtable[4];
void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self);
}
/* ABI view of the allocator: slot 216 allocates the requested number of bytes. */
class AllocatorSlot216View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self) {
    void **allocator;

    igObject_ConstructHeader(self);
    self->_vtable = (int)(&g_ObjectPointerList_vtable[0]);
    if (self != 0) {
        ObjectPointerList_Init(self);
    }
    allocator = (void **)(igObject_GetAllocator(self));
    self->_data = ((AllocatorSlot216View *)(allocator))->vX((int)(0x10));
    return self;
}

/* 0x002ea630 - ObjectPointerList_Destruct: free the data buffer, if any, through
 * the object's allocator (virtual slot 264, free), then run the base object
 * destructor.  The buffer pointer is not cleared (docs/engine/internal-object-lists.md). */
extern "C" {
void **igObject_GetAllocator(...);
int Gap__Core__igObject__vfunc_00__002ff0a0(...);
void ObjectPointerList_Destruct(__internalNonRefCountedObjectList *self);
}
/* ABI view of the allocator: slot 264 frees the given buffer. */
class AllocatorSlot264View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
void ObjectPointerList_Destruct(__internalNonRefCountedObjectList *self) {
    int buffer;
    void **allocator;

    buffer = self->_data;
    if (buffer != 0) {
        allocator = (void **)(igObject_GetAllocator(self));
        ((AllocatorSlot264View *)(allocator))->vX((int)(buffer));
    }
    Gap__Core__igObject__vfunc_00__002ff0a0(self);
}
