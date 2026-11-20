namespace Gap {
namespace Core {

int igIntMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%d%n", (int *)dstMem, &consumed);
    return consumed;
}

igStringRef igIntMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, (const char *)&percent_d_7[0], *(const int *)srcMem);
    return igStringRef(buffer);
}

unsigned short igIntMetaField::computeSize()
{
    return 4;
}

igIntMetaField::igIntMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igIntMetaField;
}

igIntMetaField::igIntMetaField()
{
}

igIntMetaField::igIntMetaField(const igIntMetaField &other) : igMetaField(other)
{
}

void igIntMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

void igIntMetaField::setDefault(int def)
{
    setDefaultMemory(&def);
}

int igIntMetaField::computeRequiredAlignment()
{
    return 4;
}
}
}
