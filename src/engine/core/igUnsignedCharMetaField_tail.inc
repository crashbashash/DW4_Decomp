namespace Gap {
namespace Core {

int igUnsignedCharMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;
    int parsed;

    consumed = 0;
    parsed = 0;
    sscanf(strVal, "%u%n", &parsed, &consumed);
    *(char *)dstMem = parsed;
    return consumed;
}

igStringRef igUnsignedCharMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, (const char *)&percent_u[0], *(const unsigned char *)srcMem);
    return igStringRef(buffer);
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. An unsigned char is a single
 * byte. The field constructor stores this result as the field's `_size` (+0x14). */
unsigned short igUnsignedCharMetaField::computeSize() {
    return 1;
}

void igUnsignedCharMetaField::setDefault(unsigned char def)
{
    setDefaultMemory(&def);
}

int igUnsignedCharMetaField::computeRequiredAlignment() {
    return 1;
}
}
}

