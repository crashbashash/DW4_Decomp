namespace Gap {
namespace Core {

void igStringArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igStringMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

int igStringArrayMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    igStringRef *field = (igStringRef *)fieldMem;
    const char *src = (const char *)srcMem;
    const char *start = src;
    int i;

    for (i = 0; i < getNum(); i++) {
        src += igStringMetaField::readRawFieldMemory(field, src, dir, endianSwap);
        field++;
    }
    return src - start;
}

int igStringArrayMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    const igStringRef *field = (const igStringRef *)fieldMem;
    char *dst = (char *)dstMem;
    char *start = dst;
    int i;

    for (i = 0; i < getNum(); i++) {
        dst += igStringMetaField::writeRawFieldMemory(field, dst, dir, endianSwap);
        field++;
    }
    return ((dst - start) + 3) & ~3;
}

void igStringArrayMetaField::destruct(igObject *src)
{
    igStringRef *mem;
    int i;

    if (_destruct) {
        mem = (igStringRef *)((char *)src + _offset);
        for (i = 0; i < getNum(); i++) {
            *mem = (const char *)0;
            mem++;
        }
    }
}

unsigned short igStringArrayMetaField::computeSize()
{
    return getNum() * sizeof(igStringRef);
}
}
}

