namespace Gap {
namespace Core {

int igShortMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%hd%n", (short *)dstMem, &consumed);
    return consumed;
}

igStringRef igShortMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%hd", *(const short *)srcMem);
    return igStringRef(buffer);
}

igShortMetaField::igShortMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igShortMetaField;
}

igShortMetaField::igShortMetaField()
{
}

igShortMetaField::igShortMetaField(const igShortMetaField &other) : igMetaField(other)
{
}

void igShortMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

unsigned short igShortMetaField::computeSize() {
    return 2;
}

void igShortMetaField::setDefault(short def)
{
    setDefaultMemory(&def);
}

int igShortMetaField::computeRequiredAlignment() {
    return 2;
}
}
}

