namespace Gap {
namespace Math {

void igVec4ucMetaField::endianSwapMemory(void *rawMem, int num) const
{
    int numElts = getSize() / sizeof(unsigned char);
    igUnsignedCharMetaField::getMetaField()->endianSwapMemory(rawMem, num * numElts);
}

int igVec4ucMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return FUN_0018be80(strVal, dstMem, 4, 1, 0);
}

igStringRef igVec4ucMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];
    const unsigned char *value = (const unsigned char *)srcMem;

    sprintf(buffer, "%uc,%uc,%uc,%uc", value[0], value[1], value[2], value[3]);
    return igStringRef(buffer);
}

unsigned short igVec4ucMetaField::computeSize()
{
    return 4;
}

int igVec4ucMetaField::computeRequiredAlignment()
{
    return 1;
}
}
}

