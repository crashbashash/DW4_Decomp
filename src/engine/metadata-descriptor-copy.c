#include "dw4/reflected.h"
void *igObject_CopyConstructHeader(void *, void *);
void *igObject_AllocateStorage(void *, int);
void *memcpy(void *, const void *, unsigned int);
void StringChunk_ReleaseHeader(int, void *);
extern int g_igMetaField_vtable[4];
typedef struct {
    char prefix[32];
    void *value;
} DefaultPointerView;

igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source) {
    int name;
    int refCount;
    int *nameHeader;

    igObject_CopyConstructHeader(dest, source);
    dest->_vtable = (int)g_igMetaField_vtable;
    dest->_fieldName = 0;
    dest->_offset = source->_offset;
    dest->_isRunTime = source->_isRunTime;
    dest->_typeIndex = source->_typeIndex;
    dest->_size = source->_size;
    dest->_internalIndex = source->_internalIndex;
    dest->_externalEnumStorage = source->_externalEnumStorage;

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

    dest->_default = (int)igObject_AllocateStorage(dest, dest->_size);
    memcpy((void *)dest->_default, (void *)source->_default, dest->_size);
    return dest;
}
