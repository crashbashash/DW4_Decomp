namespace Gap {
namespace Core {

void igMemoryRefArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igMemoryRefMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

int igMemoryRefArrayMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    void * *field = (void * *)fieldMem;
    const char *src = (const char *)srcMem;
    const char *start = src;
    int i;

    for (i = 0; i < getNum(); i++) {
        src += igMemoryRefMetaField::readRawFieldMemory(field, src, dir, endianSwap);
        field++;
    }
    return src - start;
}

int igMemoryRefArrayMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    const void * *field = (const void * *)fieldMem;
    char *dst = (char *)dstMem;
    char *start = dst;
    int i;

    for (i = 0; i < getNum(); i++) {
        dst += igMemoryRefMetaField::writeRawFieldMemory(field, dst, dir, endianSwap);
        field++;
    }
    return ((dst - start) + 3) & ~3;
}

unsigned short igMemoryRefArrayMetaField::computeSize()
{
    return getNum() * sizeof(void *);
}

void igMemoryRefArrayMetaField::traverse(igObject *obj, void *visitFunc, void *traversalData)
{
    int i;

    if (((igMetaField *)_memType)->isOfType(igObjectRefMetaField::getClassMeta()) != 0) {
        for (i = 0; i < getNum(); i++) {
            igObject **elements = ((igObject ***)((char *)obj + _offset))[i];

            if (elements != 0) {
                unsigned int count = Memory_GetBufferSize((void *)elements) >> 2;
                int j;

                for (j = 0; j < (int)count; j++) {
                    if (elements[j] != 0) {
                        elements[j]->trimCapacity();
                        elements[j]->traverseFields((Visitor)visitFunc, traversalData);
                    }
                }
            }
        }
    }
}
}
}

