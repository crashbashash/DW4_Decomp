static inline void dropNames(igTDataList<igStringObj *> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline int countOf(igTDataList<igStringObj *> *l) { if (l != 0) { return l->_count; } return 0; }

namespace Gap {
namespace Core {

void igMemoryRefMetaField::setAlignmentType(const char *name) {
    ::igTDataList<igStringObj *> *names;
    ::igTDataList<igStringObj *> *held;
    int n;
    int i;
    if (name == 0) {
        _alignmentType = -1;
        return;
    }
    *(::igTDataList<igStringObj *> **)&names = g_globalContext->_alignmentStrings;
    held = names;
    if (held != 0) { held->ref(); }
    n = countOf(names);
    for (i = 0; i < n; i++) {
        if (strcmp(igStringObj_Text(names->_data[i]), name) == 0) {
            _alignmentType = i;
            dropNames(names);
            return;
        }
    }
    dropNames(names);
}

int igMemoryRefMetaField::addToDirectory(igObject *obj, igDirectory *dir)
{
    unsigned int n;
    int p;
    int ref;
    int i;

    if (_persistent == 0) {
        return -1;
    }
    p = *(int *)((char *)obj + _offset);
    if (p == 0) {
        return -1;
    }
    if (((igMetaField *)_memType)->isOfType(igMemoryRefMetaField::getClassMeta()) != 0) {
        n = Memory_GetBufferSize((void *)p) >> 2;
        ref = igDirectory_AddMemoryRef((igDirectoryView *)dir, (int)this, p, _memType, _alignmentType, 0, 0, 1);
        for (i = 0; i < (int)n; i++) {
            int e = *(int *)(p + i * 4);
            if (e != 0) {
                igDirectory_AddMemoryRef((igDirectoryView *)dir, (int)this, e, 0, _alignmentType, 0, 0, 1);
            }
        }
        return ref;
    }
    if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) != 0) {
        ref = igDirectory_AddMemoryRef((igDirectoryView *)dir, (int)this, p, _memType, _alignmentType, 0, 0, _refCounted);
        return ref;
    }
    return igDirectory_AddMemoryRef((igDirectoryView *)dir, (int)this, p, _memType, _alignmentType, 0, 0, 1);
}

bool igMemoryRefMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const
{
    int offset;

    offset = _offset;
    return *(const int *)((const char *)obj1 + offset) == *(const int *)((const char *)obj2 + offset);
}

bool igMemoryRefMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    int off;
    int n;
    int a;
    int b;
    int i;

    if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) == 0) {
        return isAlikeCompareShallow(obj1, obj2);
    }
    off = _offset;
    a = *(const int *)((const char *)obj1 + off);
    b = *(const int *)((const char *)obj2 + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = (int)Memory_GetBufferSize((void *)a);
    if (n != (int)Memory_GetBufferSize((void *)b)) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (!((*(igObject **)(a + i * 4))->isAlikeDeep(*(igObject **)(b + i * 4)) & 0xFF)) {
            return 0;
        }
    }
    return 1;
}

int igMemoryRefMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    struct { int w0; } index;
    int *out = (int *)fieldMem;
    int raw;
    igMemoryDirEntry *entry;

    if (dir != 0 && (raw = *(const int *)srcMem) != -1) {
        index.w0 = raw;
        if (endianSwap) {
            igIntMetaField::getMetaField()->endianSwapMemory(&index.w0, 1);
        }
        entry = (igMemoryDirEntry *)igDirectory_GetEntry((int *)dir, index.w0);
        if (entry != 0) {
            *out = entry->_ref;
            if (_memType == 0 && this != _MetaField) {
                ((igMemoryRefMetaField *)this)->_memType = entry->_memType;
            }
        } else {
            *out = 0;
        }
    } else {
        *out = 0;
    }
    return 4;
}

bool igMemoryRefMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    int off;
    int n;
    char *a;
    char *b;
    int i;

    off = _offset;
    a = *(char **)((const char *)obj1 + off);
    b = *(char **)((const char *)obj2 + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = (int)Memory_GetBufferSize(a);
    if (n != (int)Memory_GetBufferSize(b)) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void igMemoryRefMetaField::setPool(const char *poolName)
{
    _poolName = poolName;
}

const char *igMemoryRefMetaField::getPool()
{
    return _poolName.p;
}
}
}

/* Run the base-class constructor, point the descriptor at its own vtable and
 * clear the two reference members, then (for a live object) apply the field
 * defaults with igMemoryRefMetaField_Init. */
namespace Gap {
namespace Core {

igMemoryRefMetaField::igMemoryRefMetaField(bool boot) : igRefMetaField(boot)
{
    new (this, 0) igMemoryRefMetaField;
}
}
}



/* Default values of a memory-reference descriptor: reference counted, no size
 * or memory type, reset method 3, release on reset and on copy, alignment
 * type -1 and shallow-copy method 2. */
namespace Gap {
namespace Core {

igMemoryRefMetaField::igMemoryRefMetaField()
{
    _refCounted = 1;
    _memSize = 0;
    _memType = 0;
    _resetMethod = 3;
    _releaseOnReset = 1;
    _releaseOnCopy = 1;
    _alignmentType = -1;
    _shallowCopyMethod = 2;
}
}
}



/* Copy the reference layer, stamp the memory-reference vtable and clear the two borrowed
 * references (_memTypeRef, _poolName), then copy the ref-counting, memory type/size, reset,
 * release and alignment settings. */
namespace Gap {
namespace Core {

igMemoryRefMetaField::igMemoryRefMetaField(const igMemoryRefMetaField &other) : igRefMetaField(other)
{
    _refCounted = other._refCounted;
    _memType = other._memType;
    _memSize = other._memSize;
    _resetMethod = other._resetMethod;
    _releaseOnReset = other._releaseOnReset;
    _releaseOnCopy = other._releaseOnCopy;
    _alignmentType = other._alignmentType;
}

void igMemoryRefMetaField::__bootstrapDestruct()
{
    igRefMetaField::__bootstrapDestruct();
}
}
}



