namespace Gap {
namespace Core {

void igUnsignedCharArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igUnsignedCharMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Storage size in bytes of the field's array. One byte per element, so the size is the element
 * count `_num` (returned as a 16-bit value, like the `_size` field of igMetaField that it feeds). */

unsigned short igUnsignedCharArrayMetaField::computeSize()
{
    return getNum() * sizeof(unsigned char);
}
}
}

