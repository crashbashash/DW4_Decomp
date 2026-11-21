namespace Gap {
namespace Core {

void igObjectRefArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igObjectRefMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

void igObjectRefArrayMetaField::set(igObject *obj, int index, igObject *val) const
{
    ::igObject *value = (::igObject *)val;
    ::igObject *old = ((::igObject **)((char *)obj + _offset))[index];

    if (_refCounted) {
        if (value != 0) {
            value->_refCount = value->_refCount + 1;
        }
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
    }
    ((::igObject **)((char *)obj + _offset))[index] = value;
}

int igObjectRefArrayMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    igObject * *field = (igObject * *)fieldMem;
    const char *src = (const char *)srcMem;
    const char *start = src;
    int i;

    for (i = 0; i < getNum(); i++) {
        src += igObjectRefMetaField::readRawFieldMemory(field, src, dir, endianSwap);
        field++;
    }
    return src - start;
}

void igObjectRefArrayMetaField::construct(igObject *src)
{
    ::igObject *element;
    igMemoryPoolView *pool;
    int i;
    const char *name;

    if (_construct) {
        name = _poolName.p;
        if ((name != 0) && (*name != 0)) {
            pool = (igMemoryPoolView *)Memory_GetAllocatorByName(name);
            if (pool == 0) {
                pool = src->getMemoryPool();
            }
        } else {
            pool = src->getMemoryPool();
        }
        for (i = 0; i < getNum(); i++) {
            element = (::igObject *)igMetaObject_CreateInstance((igMetaObject *)_metaObject, pool);
            set(src, i, (igObject *)element);
            if (_refCounted) {
                element->_refCount = element->_refCount - 1;
                if ((element->_refCount & 0x7fffff) == 0) {
                    igObject_Destroy(element);
                }
            }
        }
    }
}

void igObjectRefArrayMetaField::destruct(igObject *src)
{
    int i;
    ::igObject *element;

    if (_destruct) {
        for (i = 0; i < getNum(); i++) {
            element = ((::igObject **)((char *)src + _offset))[i];
            if (element != 0) {
                element->_refCount = element->_refCount - 1;
                if ((element->_refCount & 0x7fffff) == 0) {
                    igObject_Destroy(element);
                }
            }
        }
    }
}

void igObjectRefArrayMetaField::decommission(igObject *src)
{
    int i;
    ::igObject *element;

    if (_persistent) {
        if (_refCounted) {
            for (i = 0; i < getNum(); i++) {
                element = ((::igObject **)((char *)src + _offset))[i];
                if (element != 0) {
                    element->_refCount = element->_refCount - 1;
                    if ((element->_refCount & 0x7fffff) == 0) {
                        igObject_Destroy(element);
                    }
                }
            }
        }
        igRefMetaField::decommission(src);
    }
}

void igObjectRefArrayMetaField::resetByValue(igObject *src)
{
    int i;
    igObject *element;

    for (i = 0; i < getNum(); i++) {
        element = ((igObject **)((char *)src + _offset))[i];
        if (element != 0) {
            igObject_ResetFields((igObjectDispatchView *)element);
        }
    }
}

void igObjectRefArrayMetaField::resetByReference(igObject *src)
{
    int i;

    for (i = 0; i < getNum(); i++) {
        set(src, i, ((igObject **)_default)[i]);
    }
}

void igObjectRefArrayMetaField::copyByReference(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < getNum(); i++) {
        set(dst, i, ((igObject *const *)((const char *)src + _offset))[i]);
    }
}

void igObjectRefArrayMetaField::copyByValue(igObject *dst, const igObject *src)
{
    int i = 0;

    while (i < getNum()) {
        int base = _offset;
        int off = i * 4;
        ::igObject *to = *(::igObject **)((char *)dst + base + off);
        igObject *from = *(igObject *const *)((const char *)src + base + off);

        if (to == 0 && from == 0) break;
        if (to != 0 && from != 0) {
            ((igObject *)to)->copyDeep(from);
        } else if (to == 0) {
            set(dst, i, from->cloneViaMetadata(1));
        } else if (from == 0) {
            to->_refCount = to->_refCount - 1;
            if ((to->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(to);
            }
            set(dst, i, 0);
        }
        i++;
    }
}

void igObjectRefArrayMetaField::copyByValueShallow(igObject *dst, const igObject *src)
{
    int i;
    int offset;
    char *dstBase;
    const char *srcBase;
    int byteOffset;
    ::igObject *to;
    igObject *from;

    i = 0;
    while (i < getNum()) {
        offset = _offset;
        byteOffset = i * 4;
        dstBase = (char *)dst + offset;
        srcBase = (const char *)src + offset;
        to = *(::igObject **)(dstBase + byteOffset);
        from = *(igObject *const *)(srcBase + byteOffset);
        if (to != 0 || from != 0) {
            if (to != 0 && from != 0) {
                ((igObject *)to)->copyShallow((int)from);
            } else if (to == 0) {
                set(dst, i, from->cloneViaMetadata(1));
            } else if (from == 0) {
                to->_refCount = to->_refCount - 1;
                if ((to->_refCount & 0x7fffff) == 0) {
                    igObject_Destroy(to);
                }
                set(dst, i, 0);
            }
            i += 1;
        } else {
            break;
        }
    }
}

void igObjectRefArrayMetaField::copyByReset(igObject *dst, const igObject *src)
{
    int i;

    for (i = 0; i < getNum(); i++) {
        igObject *element = ((igObject **)((char *)dst + _offset))[i];

        if (element != 0) {
            igObject_ResetFields((igObjectDispatchView *)element);
        }
    }
}

int igObjectRefArrayMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    const igObject * *field = (const igObject * *)fieldMem;
    char *dst = (char *)dstMem;
    char *start = dst;
    int i;

    for (i = 0; i < getNum(); i++) {
        dst += igObjectRefMetaField::writeRawFieldMemory(field, dst, dir, endianSwap);
        field++;
    }
    return ((dst - start) + 3) & ~3;
}

unsigned short igObjectRefArrayMetaField::computeSize()
{
    return getNum() * sizeof(igObject *);
}

void igObjectRefArrayMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData)
{
    igObject *element;
    int i;

    for (i = 0; i < getNum(); i++) {
        element = ((igObject **)((char *)obj + _offset))[i];
        if (element != 0) {
            element->traverseFields((Visitor)visitFunc, traversalData);
        }
    }
}

bool igObjectRefArrayMetaField::isAlikeCompareExactly(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < getNum(); i++) {
        igObject *a = ((igObject *const *)((const char *)obj1 + _offset))[i];
        igObject *b = ((igObject *const *)((const char *)obj2 + _offset))[i];

        if (a != b) {
            if (a == 0 || b == 0) {
                return false;
            }
            if (a->isAlikeExactly(b) == false) {
                return false;
            }
        }
    }
    return true;
}

bool igObjectRefArrayMetaField::isAlikeCompareDeep(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < getNum(); i++) {
        igObject *a = ((igObject *const *)((const char *)obj1 + _offset))[i];
        igObject *b = ((igObject *const *)((const char *)obj2 + _offset))[i];

        if (a != b) {
            if (a == 0 || b == 0) {
                return false;
            }
            if (a->isAlikeDeep((igObject *)b) == false) {
                return false;
            }
        }
    }
    return true;
}

bool igObjectRefArrayMetaField::isAlikeCompareShallow(const igObject *obj1, const igObject *obj2) const
{
    int i;

    for (i = 0; i < getNum(); i++) {
        igObject *a = ((igObject *const *)((const char *)obj1 + _offset))[i];
        igObject *b = ((igObject *const *)((const char *)obj2 + _offset))[i];

        if (a != b) {
            if (a == 0 || b == 0) {
                return false;
            }
            if (a->isAlikeShallow((igObject *)b) == false) {
                return false;
            }
        }
    }
    return true;
}
}
}

