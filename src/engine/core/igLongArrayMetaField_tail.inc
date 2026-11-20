namespace Gap {
namespace Core {

void igLongArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igLongMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Storage size in bytes of the field's array: `_num` elements of 8 bytes (long), truncated to the
 * 16-bit size the meta field system uses. */

unsigned short igLongArrayMetaField::computeSize()
{
    return getNum() * sizeof(long long);
}
}
}

