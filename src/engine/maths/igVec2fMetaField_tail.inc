namespace Gap {
namespace Math {

void igVec2fMetaField::endianSwapMemory(void *rawMem, int num) const
{
    int numElts = getSize() / sizeof(float);
    igFloatMetaField::getMetaField()->endianSwapMemory(rawMem, num * numElts);
}

int igVec2fMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return FUN_0018be80(strVal, dstMem, 2, 4, 1);
}

igStringRef igVec2fMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];
    const float *value = (const float *)srcMem;

    sprintf(buffer, "%f,%f", value[0], value[1]);
    return igStringRef(buffer);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec2f is two 32-bit
 * floats, 8 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
unsigned short igVec2fMetaField::computeSize()
{
    return 8;
}

void igVec2fMetaField::setDefault(const igVec2f &def)
{
    setDefaultMemory(&def);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 8-byte element size. The receiver is not read. */
int igVec2fMetaField::computeRequiredAlignment()
{
    return 0x10;
}
}
}

