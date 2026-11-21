namespace Gap {
namespace Math {

void igMatrix44fMetaField::endianSwapMemory(void *rawMem, int num) const
{
    int numElts = getSize() / sizeof(float);
    igFloatMetaField::getMetaField()->endianSwapMemory(rawMem, num * numElts);
}

int igMatrix44fMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return FUN_0018be80(strVal, dstMem, 16, 4, 1);
}

igStringRef igMatrix44fMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];
    const float *value = (const float *)srcMem;

    sprintf(buffer, "\n%f,%f,%f,%f,\n%f,%f,%f,%f,\n%f,%f,%f,%f,\n%f,%f,%f,%f\n", value[0], value[1], value[2], value[3], value[4], value[5], value[6], value[7], value[8], value[9], value[10], value[11], value[12], value[13], value[14], value[15]);
    return igStringRef(buffer);
}

/* igMatrix44fMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A 4x4 float
 * matrix is 16 floats * 4 bytes = 0x40. */
unsigned short igMatrix44fMetaField::computeSize()
{
    return 0x40;
}

void igMatrix44fMetaField::setDefault(const igMatrix44f &def)
{
    setDefaultMemory(&def);
}

/* Override of the igMetaField slot at vtable +0x6c (slot 27): returns 16, one quadword rather than
 * the 64-byte matrix size. The receiver is not read. */
int igMatrix44fMetaField::computeRequiredAlignment()
{
    return 0x10;
}
}
}

