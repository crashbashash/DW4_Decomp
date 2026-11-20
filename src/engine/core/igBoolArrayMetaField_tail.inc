namespace Gap {
namespace Core {

void igBoolArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igBoolMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

unsigned short igBoolArrayMetaField::computeSize()
{
    return getNum() * sizeof(bool);
}

void igBoolArrayMetaField::setDefault(bool val)
{
    bool *mem;
    int i;

    setDefaultMemory(0);
    mem = (bool *)_default;
    for (i = 0; i < getNum(); i++) {
        mem[i] = val;
    }
}
}
}

