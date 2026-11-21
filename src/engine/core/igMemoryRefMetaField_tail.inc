namespace Gap {
namespace Core {

unsigned short igMemoryRefMetaField::computeSize()
{
    return 4;
}

void igMemoryRefMetaField::setDefault(void *val)
{
    setDefaultMemory(&val);
}

/* Allocates the array a memory-reference field points at, if the field is constructed
 * (_construct). The element count is memSize rounded up to whole elements of the element type's
 * size (element-size virtual, low 16 bits); the pool name picks a named allocator, falling back to
 * the owning object's allocator when the name is empty or unknown. */
void igMemoryRefMetaField::construct(igObject *src)
{
    int status;
    igMemoryPoolView *pool;
    const char *poolName;
    unsigned int elementCount;
    unsigned int elementSize;

    if (_construct != 0) {
        elementSize = ((igMetaField *)_memType)->computeSize() & 0xFFFF;
        poolName = _poolName.p;
        elementCount = (unsigned int)((_memSize + elementSize) - 1) / elementSize;
        if ((poolName != 0) && (*poolName != 0)) {
            pool = Memory_GetAllocatorByName(poolName);
            if (pool == 0) {
                pool = src->getMemoryPool();
            }
        } else {
            pool = src->getMemoryPool();
        }
        igMetaField_AllocateArray(&status, (::igMemoryRefMetaField *)this, src, elementCount, pool);
    }
}

void igMemoryRefMetaField::destruct(igObject *src)
{
    if (_destruct) {
        releaseObjects(src);
        Memory_FreeBuffer(*(void **)((char *)src + _offset));
        *(void **)((char *)src + _offset) = 0;
    }
}

void igMemoryRefMetaField::refObjects(igObject *obj)
{
    ::igObject **data;
    int n;
    int i;
    ::igObject *value;

    if (!_refCounted) {
        return;
    }
    if (!_memType) {
        return;
    }
    if (!((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta())) {
        return;
    }
    data = *(::igObject ***)((char *)obj + _offset);
    if (!data) {
        return;
    }
    n = Memory_GetBufferSize(data) >> 2;
    for (i = 0; i < n; i++) {
        value = data[i];
        if (value) {
            value->ref();
        }
    }
}

void igMemoryRefMetaField::releaseObjects(igObject *obj)
{
    ::igObject **data;
    int n;
    int i;
    ::igObject *value;

    if (!_refCounted) {
        return;
    }
    if (!_memType) {
        return;
    }
    if (!((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta())) {
        return;
    }
    data = *(::igObject ***)((char *)obj + _offset);
    if (!data) {
        return;
    }
    n = Memory_GetBufferSize(data) >> 2;
    for (i = 0; i < n; i++) {
        value = data[i];
        if (value) {
            --value->_refCount;
            if (!(value->_refCount & 0x7fffff)) {
                igObject_Destroy(value);
            }
        }
    }
}

void igMemoryRefMetaField::resetByValue(igObject *src)
{
    void *value;
    void *result;

    releaseObjects(src);
    if (_releaseOnReset) {
        value = *(void **)((char *)src + _offset);
        if (value) {
            Memory_FreeOwnedBufferUnchecked(value);
        }
    }
    value = *(void **)_default;
    result = value ? Memory_DuplicateBuffer(value) : 0;
    *(void **)((char *)src + _offset) = result;
    refObjects(src);
}

void igMemoryRefMetaField::copyByValue(igObject *dst, const igObject *src)
{
    int copy;

    releaseObjects(dst);
    if (_releaseOnCopy != 0) {
        int owned = *(int *)((char *)dst + _offset);
        if (owned != 0) {
            Memory_FreeOwnedBufferUnchecked((void *)owned);
        }
    }
    {
        int buffer = *(int *)((const char *)src + _offset);
        if (buffer != 0) {
            copy = (int)Memory_DuplicateBuffer((void *)buffer);
        } else {
            copy = 0;
        }
        *(int *)((char *)dst + _offset) = copy;
    }
    if (_memType != 0) {
        if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) != 0) {
            int from = *(int *)((const char *)src + _offset);
            int to = *(int *)((char *)dst + _offset);
            if (from != 0 && to != 0) {
                unsigned n = Memory_GetBufferSize((void *)from) >> 2;
                int i;
                for (i = 0; i < (int)n; i++) {
                    igObject *e = *(igObject **)(from + i * 4);
                    int clone = 0;
                    if (e != 0) {
                        clone = (int)e->cloneViaMetadata(1);
                    }
                    *(int *)(to + i * 4) = clone;
                }
            }
        } else if (((igMetaField *)_memType)->isOfType(igMemoryRefMetaField::getClassMeta()) != 0) {
            int from = *(int *)((const char *)src + _offset);
            int to = *(int *)((char *)dst + _offset);
            unsigned n = Memory_GetBufferSize((void *)from) >> 2;
            int i;
            for (i = 0; i < (int)n; i++) {
                int e = *(int *)(from + i * 4);
                int clone;
                if (e != 0) {
                    clone = (int)Memory_DuplicateBuffer((void *)e);
                } else {
                    clone = 0;
                }
                *(int *)(to + i * 4) = clone;
            }
        }
    }
}

void igMemoryRefMetaField::copyByValueShallow(igObject *dst, const igObject *src)
{
    void *old;
    void *value;
    void *copy;

    releaseObjects(dst);
    if (_releaseOnCopy) {
        old = *(void **)((char *)dst + _offset);
        if (old) {
            Memory_FreeOwnedBufferUnchecked(old);
        }
    }
    value = *(void **)((const char *)src + _offset);
    copy = value ? Memory_DuplicateBuffer(value) : 0;
    *(void **)((char *)dst + _offset) = copy;
    refObjects(dst);
}

void igMemoryRefMetaField::print(const igObject *src, unsigned int deep, const char *indent)
{
    unsigned int count;
    unsigned int elementSize;
    int buffer;
    int i;

    buffer = *(int *)((const char *)src + _offset);
    igReport_Printf("%s%s = 0x%x\n", indent, getFieldName(), buffer);
    igReport_Flush();
    if (deep != 0 && buffer != 0) {
        elementSize = ((igMetaField *)_memType)->computeTypeSize();
        count = Memory_GetBufferSize((void *)buffer) / elementSize;
        if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) != 0) {
            for (i = 0; i < (int)count; i++) {
                igObject *e = *(igObject **)(buffer + i * 4);
                if (e != 0) {
                    e->printFields(deep, (int)indent);
                }
            }
        }
    }
}

void igMemoryRefMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData)
{
    igObject **elements;
    unsigned int count;
    int i;
    igObject *element;

    if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) != 0) {
        elements = *(igObject ***)((char *)obj + _offset);
        if (elements != 0) {
            count = Memory_GetBufferSize((void *)elements) >> 2;
            for (i = 0; i < (int)count; i++) {
                element = elements[i];
                if (element != 0) {
                    element->trimCapacity();
                    elements[i]->traverseFields((Visitor)visitFunc, traversalData);
                }
            }
        }
    }
}
}
}

