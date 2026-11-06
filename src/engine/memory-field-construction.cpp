/* Element-size dispatch is an observed virtual-slot view; do not instantiate. */
#include "dw4/reflected.h"
extern "C" {
int Memory_GetAllocatorByName(...);
void igMetaField_AllocateArray(...);
int igObject_GetAllocator(...);
void igMemoryRefMetaField_ConstructValue(igMemoryRefMetaField *self, int object);
}
class FieldElementSizeDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
/* Allocates the array a memory-reference field points at, if the field is constructed
 * (_construct). The element count is memSize rounded up to whole elements of the element type's
 * size (element-size virtual, low 16 bits); the pool name picks a named allocator, falling back to
 * the owning object's allocator when the name is empty or unknown. */
void igMemoryRefMetaField_ConstructValue(igMemoryRefMetaField *self, int object) {
    int status;
    int allocator;
    char *poolName;
    unsigned int elementCount;
    unsigned int elementSize;
    void **memType;

    if (self->_construct != 0) {
        memType = (void **)(self->_memType);
        elementSize = ((FieldElementSizeDispatchView *)(memType))->vX() & 0xFFFF;
        poolName = (char *)(self->_poolName);
        elementCount = (int)((unsigned int) ((self->_memSize + elementSize) - 1) / elementSize);
        if ((poolName != 0) && (*poolName != 0)) {
            allocator = Memory_GetAllocatorByName(poolName);
            if (allocator == 0) {
                allocator = igObject_GetAllocator(object);
            }
        } else {
            allocator = igObject_GetAllocator(object);
        }
        igMetaField_AllocateArray(&status, self, object, elementCount, allocator);
    }
}
