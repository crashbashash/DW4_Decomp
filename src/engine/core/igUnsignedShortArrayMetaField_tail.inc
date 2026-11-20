namespace Gap {
namespace Core {

void igUnsignedShortArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igUnsignedShortMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Byte size of the array field's storage: `_num` elements of 2 bytes each, truncated to 16 bits
 * like the field descriptor's `_size`. */
unsigned short igUnsignedShortArrayMetaField::computeSize()
{
    return getNum() * sizeof(unsigned short);
}
}
}

