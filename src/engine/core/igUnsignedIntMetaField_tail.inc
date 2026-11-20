namespace Gap {
namespace Core {

int igUnsignedIntMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%u%n", (unsigned int *)dstMem, &consumed);
    return consumed;
}

igStringRef igUnsignedIntMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%ud", *(const unsigned int *)srcMem);
    return igStringRef(buffer);
}

/* Vtable slot 53 of igNonRefCountedThreadList: a constant leaf returning 4. The list's element
 * type is igUnsignedIntMetaField (slots 50 and 51 hand out that class's metaobject and
 * descriptor), so 4 is read as the element size in bytes. The receiver is not touched, hence no
 * parameters. */
unsigned short igUnsignedIntMetaField::computeSize() {
    return 4;
}

igUnsignedIntMetaField::igUnsignedIntMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igUnsignedIntMetaField;
}

igUnsignedIntMetaField::igUnsignedIntMetaField()
{
}

igUnsignedIntMetaField::igUnsignedIntMetaField(const igUnsignedIntMetaField &other) : igMetaField(other)
{
}

void igUnsignedIntMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

void igUnsignedIntMetaField::setDefault(unsigned int def)
{
    setDefaultMemory(&def);
}

int igUnsignedIntMetaField::computeRequiredAlignment() {
    return 4;
}
}
}

