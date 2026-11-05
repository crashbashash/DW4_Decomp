/* Copy constructors of the reference-field descriptors (igRefMetaField and its
 * subclass igMemoryRefMetaField), the two upper layers of the descriptor copy
 * chain igMemoryRefMetaField -> igRefMetaField -> igMetaField
 * (docs/engine/list-descriptor-copy.md, finding #887).  Functions are in
 * retail address order. */
#include "dw4/reflected.h"
igMetaField *igMetaField_CopyConstruct(igMetaField *, igMetaField *);
igRefMetaField *igRefMetaField_CopyConstruct(igRefMetaField *, igRefMetaField *);
/* vtables stamped over the base-class copy (the base constructor leaves its own). */
extern int g_igRefMetaField_vtable_0052ec50[4];
extern int g_igMemoryRefMetaField_vtable_00532a50[4];

/* 0x002fb9a0 — Copy the reference layer, stamp the memory-reference vtable and
 * clear the two borrowed references (_memTypeRef, _poolName), then copy the
 * ref-counting, memory type/size, reset, release and alignment settings. */
igMemoryRefMetaField *igMemoryRefMetaField_CopyConstruct(igMemoryRefMetaField *self, igMemoryRefMetaField *source) {
    igRefMetaField_CopyConstruct((igRefMetaField *)self, (igRefMetaField *)source);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable_00532a50;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    self->_refCounted = source->_refCounted;
    self->_memType = source->_memType;
    self->_memSize = source->_memSize;
    self->_resetMethod = source->_resetMethod;
    self->_releaseOnReset = source->_releaseOnReset;
    self->_releaseOnCopy = source->_releaseOnCopy;
    self->_alignmentType = source->_alignmentType;
    return self;
}

/* 0x00305c70 — Copy the base metadata field, stamp the reference-field vtable
 * and copy the construct/destruct flags. */
igRefMetaField *igRefMetaField_CopyConstruct(igRefMetaField *self, igRefMetaField *source) {
    igMetaField_CopyConstruct((igMetaField *)self, (igMetaField *)source);
    self->_vtable = (int)g_igRefMetaField_vtable_0052ec50;
    self->_construct = source->_construct;
    self->_destruct = source->_destruct;
    return self;
}
