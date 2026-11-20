namespace Gap {
namespace Core {

int igUnsignedShortMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%hd%n", (unsigned short *)dstMem, &consumed);
    return consumed;
}

igStringRef igUnsignedShortMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%hd", *(const unsigned short *)srcMem);
    return igStringRef(buffer);
}

unsigned short igUnsignedShortMetaField::computeSize() {
    return 2;
}

void igUnsignedShortMetaField::setDefault(unsigned short def)
{
    setDefaultMemory(&def);
}

igUnsignedShortMetaField::igUnsignedShortMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igUnsignedShortMetaField;
}

igUnsignedShortMetaField::igUnsignedShortMetaField()
{
}

igUnsignedShortMetaField::igUnsignedShortMetaField(const igUnsignedShortMetaField &other) : igMetaField(other)
{
}

void igUnsignedShortMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

/* igUnsignedShortArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 2, the byte size
 * of one unsigned short element. The same igMetaField slot is the base's `return -1` and
 * igStructMetaField's `_alignment` accessor. */
int igUnsignedShortMetaField::computeRequiredAlignment() {
    return 2;
}
}
}

