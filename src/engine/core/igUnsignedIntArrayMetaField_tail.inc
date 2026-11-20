namespace Gap {
namespace Core {

void igUnsignedIntArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igUnsignedIntMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Size in bytes of the array field: `_num` unsigned-int elements, truncated to the 16-bit `_size`
 * field width of the meta-field (`_num` +52, `_size` +20 unsigned short). */

unsigned short igUnsignedIntArrayMetaField::computeSize()
{
    return getNum() * sizeof(unsigned int);
}
}
}

