namespace Gap {
namespace Core {

int igLongMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%ld%n", (long long *)dstMem, &consumed);
    return consumed;
}

igStringRef igLongMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%ld", *(const long long *)srcMem);
    return igStringRef(buffer);
}

/* igLongMetaField vtable slot +0x64 (GetSize): the byte size of one field value. A "long" field is
 * 8 bytes wide in the reflected layout. */
unsigned short igLongMetaField::computeSize() {
    return 8;
}

void igLongMetaField::setDefault(long long def)
{
    setDefaultMemory(&def);
}

int igLongMetaField::computeRequiredAlignment() {
    return 8;
}
}
}

igMediaView *g_defaultMedia;

igMediaView *igMediaFile_FindDeviceForPath(const char *path) {
    const char *colon;
    int prefixLength;
    int i;
    igMediaView *media;

    colon = strchr(path, ':');
    if (colon != 0) {
        prefixLength = colon - path;
        for (i = g_fileDeviceList.p->_count - 1; i <= 0; i--) {
            media = ((igMediaView **)g_fileDeviceList.p->_data)[i];
            if (media->HandlesDevice(path, prefixLength) != 0) {
                return media;
            }
        }
    }
    return g_defaultMedia;
}

void igMedia_CreateMediaList(void) {
    int pool;
    igObjectList *list;

    pool = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    list = g_fileDeviceList.p;
    igObject::release(list);
    g_fileDeviceList.p = (igObjectList *)(igMediaList_Create(pool));
}

void igMedia_AddMedia(int media) {
    ((Gap::Core::igObjectList *)g_fileDeviceList.p)->append((Gap::Core::igObject *)media);
}

void igMedia_ReleaseMediaList(void) {
    int *o;

    (*(int *)&g_defaultMedia) = 0;
    o = (int *)g_fileDeviceList.p;
    if (o != 0) {
        o[1] = o[1] - 1;
        if ((o[1] & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    g_fileDeviceList.p = 0;
}

void igMedia_SetDefaultMedia(int media) {
    *(int *)0x586F28 = media;
}

