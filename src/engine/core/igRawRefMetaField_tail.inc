namespace Gap {
namespace Core {

/* Prints `<indent><field> = 0x<value>`: a raw reference is a pointer, shown as its address. */
void igRawRefMetaField::print(const igObject *src, unsigned int deep, const char *indent)
{
    igReport_Printf("%s%s = 0x%x\n", indent, getFieldName(), (int)*(void **)((char *)src + _offset));
    igReport_Flush();
}

int igRawRefMetaField::addToDirectory(igObject *obj, igDirectory *dir)
{
    if (_persistent == 1) {
        return igDirectory_AddRawRef((igDirectoryView *)dir, *(int *)((char *)obj + _offset), 0, 0);
    }
    return -1;
}

igRawRefMetaField::igRawRefMetaField(bool boot) : igRefMetaField(boot)
{
    new (this, 0) igRawRefMetaField;
}

igRawRefMetaField::igRawRefMetaField()
{
}

igRawRefMetaField::igRawRefMetaField(const igRawRefMetaField &other) : igRefMetaField(other)
{
}

void igRawRefMetaField::__bootstrapDestruct()
{
    igRefMetaField::__bootstrapDestruct();
}

int igRefMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    return 0;
}

igStringRef igRefMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    return igStringRef();
}
}
}

