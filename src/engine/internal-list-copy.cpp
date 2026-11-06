#include "dw4/reflected.h"

/* 0x002ea590 - ObjectPointerList_CopyConstruct: copy-construct a raw pointer list.
 * Copy the object header, stamp the raw pointer-list vtable (finding #3187), copy the
 * element count and, when the source owns a buffer, allocate a buffer of the same size
 * from this object's allocator (virtual slot 216, allocate) and copy the pointers over;
 * an empty source leaves the buffer null (docs/engine/internal-object-lists.md). */
/* ABI view of the allocator: only the allocate slot is used. */
class AllocatorView { public: virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void d49();virtual void d50();virtual void d51();virtual void *Allocate(int); };
extern "C" {
extern int g_ObjectPointerList_vtable[4];
void *igObject_CopyConstructHeader(void *, void *);
AllocatorView *igObject_GetAllocator(void *);
void memcpy(void *, void *, int);

__internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source) {
    int bytes;
    igObject_CopyConstructHeader(self, source);
    self->_vtable = (int)g_ObjectPointerList_vtable;
    self->_count = source->_count;
    if (source->_data) {
        bytes = self->_count * 4;
        AllocatorView *allocator = igObject_GetAllocator(self);
        self->_data = (int)allocator->Allocate(bytes);
        memcpy((void *)self->_data, (void *)source->_data, bytes);
    } else {
        self->_data = 0;
    }
    return self;
}
}
