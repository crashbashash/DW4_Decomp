/* Construction of the memory-reference field descriptor (igMemoryRefMetaField), the reflection
 * descriptor of a field that points at a block of memory. Field layout comes from the reflected
 * struct in include/dw4/reflected.h; the descriptor's vtable is at 0x532a50. Functions are in
 * retail address order. */
#include "dw4/reflected.h"
void *igRefMetaField_Construct(igRefMetaField *);
void *igRefMetaField_Init(igRefMetaField *);
igMemoryRefMetaField *igMemoryRefMetaField_Init(igMemoryRefMetaField *);
/* vtable of igMemoryRefMetaField (the 0x532a50 table whose slot 124 builds the memory value). */
extern int g_igMemoryRefMetaField_vtable[4];

/* Run the base-class constructor, point the descriptor at its own vtable and
 * clear the two reference members, then (for a live object) apply the field
 * defaults with igMemoryRefMetaField_Init. */
igMemoryRefMetaField *igMemoryRefMetaField_Construct(igMemoryRefMetaField *self) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    if (self) igMemoryRefMetaField_Init(self);
    return self;
}

/* Default values of a memory-reference descriptor: reference counted, no size
 * or memory type, reset method 3, release on reset and on copy, alignment
 * type -1 and shallow-copy method 2. */
igMemoryRefMetaField *igMemoryRefMetaField_Init(igMemoryRefMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    self->_refCounted = 1;
    self->_memSize = 0;
    self->_memType = 0;
    self->_resetMethod = 3;
    self->_releaseOnReset = 1;
    self->_releaseOnCopy = 1;
    self->_alignmentType = -1;
    self->_shallowCopyMethod = 2;
    return self;
}
