namespace Gap {
namespace Core {

int igDoubleMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%lg%n", (double *)dstMem, &consumed);
    return consumed;
}

igStringRef igDoubleMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%g", *(const double *)srcMem);
    return igStringRef(buffer);
}

unsigned short igDoubleMetaField::computeSize() {
    return 8;
}

void igDoubleMetaField::setDefault(double def)
{
    setDefaultMemory(&def);
}

int igDoubleMetaField::computeRequiredAlignment() {
    return 8;
}
}
}

