namespace Gap {
namespace Core {

void igUnsignedLongArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igUnsignedLongMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Byte size of the array field's storage: `_num` elements of 8 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
unsigned short igUnsignedLongArrayMetaField::computeSize()
{
    return getNum() * sizeof(unsigned long long);
}
}
}

