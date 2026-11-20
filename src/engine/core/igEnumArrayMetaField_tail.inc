namespace Gap {
namespace Core {

void igEnumArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igEnumMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

/* IgEnumArrayMetaField virtual getter 25. Returns the array's storage size in bytes truncated to
 * 16 bits: `_num` elements of 4 bytes each (the enum values are ints). The 16-bit result matches
 * the reflected `_size` field (unsigned short, +20) that the metafield base class carries. */

unsigned short igEnumArrayMetaField::computeSize()
{
    return getNum() * sizeof(int);
}

void igEnumArrayMetaField::setDefault(int val)
{
    int *mem;
    int i;

    setDefaultMemory(0);
    mem = (int *)_default;
    for (i = 0; i < getNum(); i++) {
        mem[i] = val;
    }
}

void igEnumMetaField::setDefault(const int &def)
{
    setDefaultMemory(&def);
}
}
}

