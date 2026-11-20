namespace Gap {
namespace Core {

int igUnsignedLongMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%ld%n", (unsigned long long *)dstMem, &consumed);
    return consumed;
}

igStringRef igUnsignedLongMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%ld", *(const unsigned long long *)srcMem);
    return igStringRef(buffer);
}

unsigned short igUnsignedLongMetaField::computeSize() {
    return 8;
}

igUnsignedLongMetaField::igUnsignedLongMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igUnsignedLongMetaField;
}

igUnsignedLongMetaField::igUnsignedLongMetaField()
{
}

igUnsignedLongMetaField::igUnsignedLongMetaField(const igUnsignedLongMetaField &other) : igMetaField(other)
{
}

void igUnsignedLongMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

void igUnsignedLongMetaField::setDefault(unsigned long long def)
{
    setDefaultMemory(&def);
}

/* igUnsignedLongArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 8, the byte size of
 * one unsigned long element (a 64-bit value on this target). The same igMetaField slot is the
 * base's `return -1` and igStructMetaField's `_alignment` accessor. */
int igUnsignedLongMetaField::computeRequiredAlignment() {
    return 8;
}
}
}

