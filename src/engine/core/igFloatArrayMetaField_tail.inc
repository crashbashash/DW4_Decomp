/* Storage size in bytes of the field's array: `_num` elements of 4 bytes (float), truncated to the
 * 16-bit size the meta field system uses. */

namespace Gap {
namespace Core {

unsigned short igFloatArrayMetaField::computeSize()
{
    return getNum() * sizeof(float);
}

void igFloatArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igFloatMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

int igFloatMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%f%n", (float *)dstMem, &consumed);
    return consumed;
}

igStringRef igFloatMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%f", fptodp(*(const float *)srcMem));
    return igStringRef(buffer);
}
}
}

