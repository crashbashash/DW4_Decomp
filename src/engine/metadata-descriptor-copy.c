/* 0x002fc0e0 igMetaField_CopyConstruct: the copy constructor of a field
 * descriptor.  The fields it copies are the reflected igMetaField members in
 * include/dw4/reflected.h; the reference-counted name string is shared with the
 * source, and a fresh default-value buffer is allocated for the copy.
 * Walkthrough: docs/engine/list-descriptor-copy.md.
 *
 * DefaultPointerView projects the default-value pointer at +32 (reflected as
 * the int `_default`) as a real pointer: with an int, MWCC changes the load
 * schedule and the bytes differ.  It is a matching construct, not an original
 * C++ class declaration. */
#include "dw4/reflected.h"
void *igObject_CopyConstructHeader(void *, void *);
void *igObject_AllocateStorage(void *, int);
void *memcpy(void *, const void *, unsigned int);
void StringChunk_ReleaseHeader(int, void *);
extern int g_igMetaField_vtable_0052f230[4];
typedef struct {
    char prefix[32];
    void *value;
} DefaultPointerView;

igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source) {
    int name;
    int refCount;
    int *nameHeader;
    unsigned short defaultSize;
    void *defaultBuffer;

    igObject_CopyConstructHeader(dest, source);
    dest->_vtable = (int)g_igMetaField_vtable_0052f230;
    dest->_fieldName = 0;
    dest->_offset = source->_offset;
    dest->_isRunTime = source->_isRunTime;
    dest->_typeIndex = source->_typeIndex;
    dest->_size = source->_size;
    dest->_internalIndex = source->_internalIndex;
    dest->_externalEnumStorage = source->_externalEnumStorage;

    /* Share the name string: take a reference on the source's, then drop the
     * reference held by the destination's old name (a string chunk keeps its
     * count at -4 and its chunk header at -8; the last release frees it). */
    name = source->_fieldName;
    if (name) {
        ++*(int *)(name - 4);
    }
    name = dest->_fieldName;
    if (name) {
        nameHeader = (int *)(name - 8);
        refCount = *(int *)(name - 4) - 1;
        *(int *)(name - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader(*nameHeader, nameHeader);
        }
    }
    dest->_fieldName = source->_fieldName;

    dest->_parentMetaObject = source->_parentMetaObject;
    dest->_invarianceFunction = source->_invarianceFunction;
    dest->_resetMethod = source->_resetMethod;
    dest->_shallowCopyMethod = source->_shallowCopyMethod;
    dest->_deepCopyMethod = source->_deepCopyMethod;
    dest->_constructCopyMethod = source->_constructCopyMethod;
    dest->_isAlikeExactlyMethod = source->_isAlikeExactlyMethod;
    dest->_isAlikeDeepMethod = source->_isAlikeDeepMethod;
    dest->_isAlikeShallowMethod = source->_isAlikeShallowMethod;
    dest->_persistent = source->_persistent;

    /* Allocate the copy's own default-value storage, then copy the bytes.  Size
     * and pointers are re-read after the allocation on purpose (see the doc). */
    ((DefaultPointerView *)dest)->value = igObject_AllocateStorage(dest, dest->_size);
    defaultSize = dest->_size;
    defaultBuffer = ((DefaultPointerView *)dest)->value;
    memcpy(defaultBuffer, ((DefaultPointerView *)source)->value, defaultSize);
    return dest;
}
