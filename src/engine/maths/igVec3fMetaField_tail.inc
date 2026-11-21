namespace Gap {
namespace Math {

void igVec3fMetaField::endianSwapMemory(void *rawMem, int num) const
{
    int numElts = getSize() / sizeof(float);
    igFloatMetaField::getMetaField()->endianSwapMemory(rawMem, num * numElts);
}

int igVec3fMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return FUN_0018be80(strVal, dstMem, 3, 4, 1);
}

igStringRef igVec3fMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];
    const float *value = (const float *)srcMem;

    sprintf(buffer, "%f,%f,%f", value[0], value[1], value[2]);
    return igStringRef(buffer);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. A Vec3f is three 32-bit
 * floats, 12 bytes. The field constructor stores this result as the field's `_size` (+0x14). */
unsigned short igVec3fMetaField::computeSize()
{
    return 0xC;
}

void igVec3fMetaField::setDefault(const igVec3f &def)
{
    setDefaultMemory(&def);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 12-byte element size. The receiver is not read. */
int igVec3fMetaField::computeRequiredAlignment()
{
    return 0x10;
}
}
}

