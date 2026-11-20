namespace Gap {
namespace Core {

void igDoubleArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igDoubleMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (double), truncated to
 * the 16-bit size the meta field system uses. */

unsigned short igDoubleArrayMetaField::computeSize()
{
    return getNum() * sizeof(double);
}
}
}

