namespace Gap {
namespace Core {

void igCharArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igCharMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* IgCharArrayMetaField virtual getter 25. Returns the array's storage size in bytes as 16 bits:
 * `_num` elements of one byte each, so it is `_num` itself (compare
 * igEnumArrayMetaField::vfunc_25, which scales by 4). */

unsigned short igCharArrayMetaField::computeSize()
{
    return getNum() * sizeof(char);
}

void igCharArrayMetaField::setDefault(unsigned int index, char val)
{
    setDefaultMemory(0);
    *(char *)(_default + index) = val;
}
}
}

