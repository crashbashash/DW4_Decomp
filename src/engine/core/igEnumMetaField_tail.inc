namespace Gap {
namespace Core {

int igEnumMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;
    int named;
    int scanned;

    consumed = 0;
    scanned = sscanf(strVal, "%d%n", (int *)dstMem, &consumed);
    if (((scanned == 0) || (scanned == -1)) && (strVal != 0)) {
        if (g_resultSuccess == igMetaEnum_GetValueByName((igMetaEnum *)getMetaEnum(), strVal, &named)) {
            *(int *)dstMem = named;
            consumed = strlen(strVal);
        }
    }
    return consumed;
}

igStringRef igEnumMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    return igMetaEnum_GetNameByValue(getMetaEnum(), *(const int *)srcMem);
}

igEnumMetaField::igEnumMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igEnumMetaField;
}

igEnumMetaField::igEnumMetaField()
{
}

igEnumMetaField::igEnumMetaField(const igEnumMetaField &other) : igMetaField(other)
{
}

void igEnumMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

unsigned short igEnumMetaField::computeSize()
{
    return 4;
}

int igEnumMetaField::computeRequiredAlignment()
{
    return 4;
}
}
}

int igErrorHandler_GetInstanceAlias()
{
    return igErrorHandler_GetInstance();
}

unsigned char g_igErrorHandler_released;
void *g_igErrorHandler_instance;

void igErrorHandler_ReleaseInstance(void) {
    if (g_igErrorHandler_instance != 0) {
        {
            igObject *held = (igObject *)g_igErrorHandler_instance;
            held->release();
        }
    }
    g_igErrorHandler_instance = (void *)(0);
    g_igErrorHandler_released = 1;
}

int igErrorHandler_GetInstance(void) {
    if (((*(int *)&g_igErrorHandler_instance) == 0) && (g_igErrorHandler_metaObject != 0) && (g_igErrorHandler_released == 0)) {
        (*(int *)&g_igErrorHandler_instance) = igErrorHandler_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
    }
    return (*(int *)&g_igErrorHandler_instance);
}

