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

igMedia *igMedia::gDefaultMedia;

igMedia *igMedia::findMedia(const char *filename) {
    const char *colon;
    int prefixLength;
    int i;
    igMedia *media;

    colon = strchr(filename, ':');
    if (colon != 0) {
        prefixLength = colon - filename;
        for (i = gRegisteredMedia->getCount() - 1; i <= 0; i--) {
            media = gRegisteredMedia->get(i);
            if (media->handlesPrefix(filename, prefixLength)) {
                return media;
            }
        }
    }
    return gDefaultMedia;
}

void igMedia::userRegister() {
    int pool;
    igMediaList *list;

    pool = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    list = gRegisteredMedia.p;
    ::igObject::release((::igObject *)list);
    gRegisteredMedia.p = igMediaList::_instantiateFromPool((igMemoryPoolView *)pool);
}

void igMedia::registerMedia(igMedia *media)
{
    gRegisteredMedia->append(media);
}

void igMedia::userUnregister() {
    gDefaultMedia = 0;
    gRegisteredMedia = 0;
}

void igMedia::setDefaultMedia(igMedia *media)
{
    gDefaultMedia = media;
}
}
}

