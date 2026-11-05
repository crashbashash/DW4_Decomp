/* 0x002bf380 — igMemoryRefMetaField_Clone: clone of a memory-reference field descriptor
 * (finding #887, docs/engine/list-descriptor-copy.md).  With the object system active it
 * runs the memory-field registration guard and clones through the source's metaobject
 * (igObject_CloneViaMetadata); otherwise (cold path) it raw-allocates the 0x50-byte
 * descriptor and runs the copy constructor.  `copyMode` only matters on the metadata path. */
#include "dw4/reflected.h"
int igMemoryRefMetaField_EnsureRegistered();
void *igObject_AllocateRawStorageDefault();
int igObject_CloneViaMetadata();
igMemoryRefMetaField *igMemoryRefMetaField_CopyConstruct(igMemoryRefMetaField *, igMemoryRefMetaField *);
/* object-system runtime pointer; byte 0 is the "object system active" flag */
extern unsigned char * g_objectSystem_00586dc8[4];
igMemoryRefMetaField *igMemoryRefMetaField_Clone(igMemoryRefMetaField *source, int copyMode) {
    igMemoryRefMetaField *clone;

    if (*g_objectSystem_00586dc8[0] != 0) {
        igMemoryRefMetaField_EnsureRegistered();
        return (igMemoryRefMetaField *)igObject_CloneViaMetadata(source, copyMode);
    }
    clone = (igMemoryRefMetaField *)igObject_AllocateRawStorageDefault(0x50, 0);
    if (clone != 0) {
        clone = igMemoryRefMetaField_CopyConstruct(clone, source);
    }
    return clone;
}
