/* Exact shallow value copy: duplicate raw storage, then retain its elements. */
#include "dw4/reflected.h"
extern "C" {
void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *,void *);
void igMemoryRefMetaField_AddElementRefs(igMemoryRefMetaField *,void *);
void Memory_FreeOwnedBufferUnchecked(void *);
void *Memory_DuplicateBuffer(void *);
}
extern "C" void igMemoryRefMetaField_ShallowCopy(igMemoryRefMetaField *field,void *dest,void *source){
    igMemoryRefMetaField_ReleaseElementRefs(field,dest);
    if(field->_releaseOnCopy){void *old=*(void **)((char *)dest+field->_offset);if(old)Memory_FreeOwnedBufferUnchecked(old);}
    void *value=*(void **)((char *)source+field->_offset);
    void *copy=value?Memory_DuplicateBuffer(value):0;
    *(void **)((char *)dest+field->_offset)=copy;
    igMemoryRefMetaField_AddElementRefs(field,dest);
}
