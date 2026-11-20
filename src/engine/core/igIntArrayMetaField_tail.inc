namespace Gap {
namespace Core {

void igIntArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igIntMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

unsigned short igIntArrayMetaField::computeSize()
{
    return getNum() * sizeof(int);
}

void igIntArrayMetaField::setDefault(int val)
{
    int *mem;
    int i;

    setDefaultMemory(0);
    mem = (int *)_default;
    for (i = 0; i < getNum(); i++) {
        mem[i] = val;
    }
}
}
}

