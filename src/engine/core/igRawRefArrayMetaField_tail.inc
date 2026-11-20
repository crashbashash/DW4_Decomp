namespace Gap {
namespace Core {

void igRawRefArrayMetaField::endianSwapMemory(void *mem, int num) const
{
    igRawRefMetaField::getMetaField()->endianSwapMemory(mem, getNum() * num);
}

int igRawRefArrayMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    void **field = (void **)fieldMem;
    const char *src = (const char *)srcMem;
    const char *start = src;
    int i;

    for (i = 0; i < getNum(); i++) {
        src += igRawRefMetaField::readRawFieldMemory(field, src, dir, endianSwap);
        field++;
    }
    return src - start;
}

int igRawRefArrayMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const
{
    void *const *field = (void *const *)fieldMem;
    char *dst = (char *)dstMem;
    char *start = dst;
    int i;

    for (i = 0; i < getNum(); i++) {
        dst += igRawRefMetaField::writeRawFieldMemory(field, dst, dir, endianSwap);
        field++;
    }
    return ((dst - start) + 3) & ~3;
}

/* Storage size in bytes of an array field of _num raw references (4 bytes each), truncated to 16
 * bits. Vtable slot 25 is the element-size query. */

unsigned short igRawRefArrayMetaField::computeSize()
{
    return getNum() * sizeof(void *);
}
}
}

/* IgPluginRepositoryList slot 53, a constant-returning override that returns 4. */

namespace Gap {
namespace Core {

unsigned short igRawRefMetaField::computeSize()
{
    return 4;
}
}
}

