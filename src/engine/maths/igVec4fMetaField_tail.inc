namespace Gap {
namespace Math {

void igVec4fMetaField::endianSwapMemory(void *rawMem, int num) const
{
    int numElts = getSize() / sizeof(float);
    igFloatMetaField::getMetaField()->endianSwapMemory(rawMem, num * numElts);
}

int igVec4fMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return FUN_0018be80(strVal, dstMem, 4, 4, 1);
}

igStringRef igVec4fMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];
    const float *value = (const float *)srcMem;

    sprintf(buffer, "%f,%f,%f,%f", value[0], value[1], value[2], value[3]);
    return igStringRef(buffer);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec4f is four 32-bit
 * floats, 16 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
unsigned short igVec4fMetaField::computeSize()
{
    return 0x10;
}

void igVec4fMetaField::setDefault(const igVec4f &def)
{
    setDefaultMemory(&def);
}

int igVec4fMetaField::computeRequiredAlignment()
{
    return 0x10;
}
}
}

