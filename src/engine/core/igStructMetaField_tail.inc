namespace Gap {
namespace Core {

unsigned short igStructMetaField::computeSize()
{
    return _size;
}

int igStructMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return strlen(strVal);
}

igStringRef igStructMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    return igStringRef(getFieldName());
}

/* Accessor: returns the field's byte alignment (`_alignment`, igIntMetaField, +52). */
int igStructMetaField::computeRequiredAlignment()
{
    return getAlignment();
}

void igStructMetaField::construct(igObject *src)
{
    if (_cppConstructor != 0) {
        ((void (*)(void *))_cppConstructor)((char *)src + _offset);
        return;
    }
    igMetaField::construct(src);
}

void igStructMetaField::destruct(igObject *src)
{
    if (_cppDestructor != 0) {
        ((void (*)(void *))_cppDestructor)((char *)src + _offset);
        return;
    }
    igMetaField::destruct(src);
}

void igStructMetaField::resetByValue(igObject *src)
{
    if (_cppConstructor != 0) {
        ((void (*)(void *))_cppDestructor)((char *)src + _offset);
        ((void (*)(void *))_cppConstructor)((char *)src + _offset);
        return;
    }
    igMetaField::resetByValue(src);
}

void igStructMetaField::resetByReference(igObject *src)
{
    resetByValue(src);
}

/* Predicate: true when the struct field metadata has a C++ constructor hook (`_cppConstructor`,
 * igRawRefMetaField, +56) set. */
int igStructMetaField::constructPerformsReset() const
{
    return _cppConstructor != 0;
}
}
}

void igSymbolTable_SetCapacity(int table, int capacity)
{
    ((igSymbolTable *)table)->_capacity = capacity;
}

