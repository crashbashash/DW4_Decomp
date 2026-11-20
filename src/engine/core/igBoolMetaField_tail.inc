namespace Gap {
namespace Core {

int igBoolMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;
    int number;

    consumed = 0;
    number = 0;
    sscanf(strVal, "%d%n", &number, &consumed);
    if (consumed > 0) {
        *(bool *)dstMem = number != 0;
        return consumed;
    }
    if (strncasecmp("true", strVal, 4) == 0) {
        *(bool *)dstMem = true;
        return 4;
    }
    if (strncasecmp("false", strVal, 5) == 0) {
        *(bool *)dstMem = false;
        return 5;
    }
    return 0;
}

igStringRef igBoolMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, (const char *)&percent_s[0], *(const bool *)srcMem ? "true" : "false");
    return igStringRef(buffer);
}

igBoolMetaField::igBoolMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igBoolMetaField;
}

igBoolMetaField::igBoolMetaField()
{
}

igBoolMetaField::igBoolMetaField(const igBoolMetaField &other) : igMetaField(other)
{
}

void igBoolMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

unsigned short igBoolMetaField::computeSize() {
    return 1;
}

void igBoolMetaField::setDefault(bool def)
{
    setDefaultMemory(&def);
}

int igBoolMetaField::computeRequiredAlignment() {
    return 1;
}
}
}

void igCallStackTable_SetCapacity(int table, int capacity)
{
    ((igCallStackTable *)table)->_capacity = capacity;
}

