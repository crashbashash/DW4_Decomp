namespace Gap {
namespace Math {

void igVec4fArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igVec4fMetaField::getMetaField()->endianSwapMemory(mem, num * getNum());
}

unsigned short igVec4fArrayMetaField::computeSize()
{
    return getNum() * sizeof(igVec4f);
}
}
}

