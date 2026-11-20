namespace Gap {
namespace Core {

void igShortArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igShortMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* Storage size in bytes of an array field of _num shorts, truncated to 16 bits. Vtable slot 25 is
 * the element-size query that the aligned array allocation calls through slot 100 and truncates
 * the same way. */

unsigned short igShortArrayMetaField::computeSize()
{
    return getNum() * sizeof(short);
}
}
}

