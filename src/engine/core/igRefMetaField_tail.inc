namespace Gap {
namespace Core {

unsigned short igRefMetaField::computeSize()
{
    return 4;
}

void igRefMetaField::commission(igObject *src)
{
    char *dst = (char *)src + _offset;
    memset(dst, 0, computeSize());
}

void igRefMetaField::decommission(igObject *src)
{
    char *dst = (char *)src + _offset;
    memset(dst, 0, computeSize());
}

int igRefMetaField::readRawFieldMemory(void *fieldMem, const void *srcMem, igDirectory *dir, bool endianSwap) const
{
    int index;
    int *object = (int *)fieldMem;
    int stored;
    igDirEntry *entry;

    if ((dir != 0) && (stored = *(const int *)srcMem, (stored != -1))) {
        index = stored;
        if (endianSwap) {
            igIntMetaField::getMetaField()->endianSwapMemory(&index, 1);
        }
        entry = (igDirEntry *)igDirectory_GetEntry((int *)dir, index);
        if (entry != 0) {
            *object = entry->_ref;
        } else {
            *object = 0;
        }
    } else {
        *object = 0;
    }
    return 4;
}
}
}

unsigned char g_igMemoryRefMetaField_unresolvedFieldRefWarned;
unsigned char g_igMemoryRefMetaField_unresolvedRefWarned;

/* Writes the directory index of the referenced object, or -1 for none. A reference to an object
 * the directory does not hold is reported once per kind of field. */
namespace Gap {
namespace Core {

int igRefMetaField::writeRawFieldMemory(const void *fieldMem, void *dstMem, igDirectory *dir, bool endianSwap) const {
    int *index = (int *)dstMem;
    igDirEntryView *entry;
    if (dir != 0 && *(const int *)fieldMem != 0) {
        entry = (igDirEntryView *)igDirectory_GetEntryByRef((igDirectoryView *)dir, *(const int *)fieldMem);
        if (*(const int *)fieldMem != 0 && entry == 0) {
            if (_parentMetaObject != 0) {
                if (!g_igMemoryRefMetaField_unresolvedFieldRefWarned) {
                    igMetaObject *meta = getMeta();
                    int answer = igReportError("%s->%s(%s)->writeRawFieldMem()0x%x[0] = 0x%x,Not in directory\nDid you modify the object after adding it to the directory ?\n", ((igMetaObject *)_parentMetaObject)->_name, getFieldName(), meta->_name, fieldMem, (unsigned int)*(const int *)fieldMem);
                    if (answer != 1 && answer == 2) g_igMemoryRefMetaField_unresolvedFieldRefWarned = 1;
                }
            } else {
                if (!g_igMemoryRefMetaField_unresolvedRefWarned) {
                    igMetaObject *meta = getMeta();
                    int answer = igReportError("%s->writeRawFieldMem()0x%x[0] = 0x%x,Not in directory\nDid you modify an object after adding it to the directory ?\n", meta->_name, fieldMem, (unsigned int)*(const int *)fieldMem);
                    if (answer != 1 && answer == 2) g_igMemoryRefMetaField_unresolvedRefWarned = 1;
                }
            }
        }
        if (entry != 0) {
            *index = entry->_index;
        } else {
            *index = -1;
        }
    } else {
        *index = -1;
    }
    if (endianSwap) {
        endianSwapMemory(index, 1);
    }
    return 4;
}
}
}


char *igRefMetaField_SkipPastChar(char *s, char ch) {
    char *r;
    while (*s != ch && *s != 0 && *s != -1) s++;
    r = s + 1;
    if (*s != ch) r = 0;
    return r;
}

char g_igRefMetaField_defaultArrayPrefix;

namespace Gap {
namespace Core {

igStringRef igRefMetaField::convertMemoryToString(const void *mem, int num, igDirectory *dir, const char *hdr, int fieldIndent)
{
    char item[256];
    char itemFormat[32];
    igMemoryPoolView *a;
    char *buf;
    char *w;
    int i;

    if (hdr == 0) hdr = &g_igRefMetaField_defaultArrayPrefix;
    if (fieldIndent == -1) fieldIndent = strlen(hdr) + 5;
    sprintf(itemFormat, "%%-%ds", fieldIndent);
    a = (igMemoryPoolView *)getMemoryPool();
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    buf = (char *)a->Allocate(num * (strlen(itemFormat) + 0x80));
    w = buf;
    for (i = 0; i < num; i++) {
        sprintf(item, itemFormat, hdr);
        if (i == 0) {
            if (num > 1) {
                sprintf(w, "%s{{ ", item);
            } else {
                goto block12;
            }
        } else {
block12:
            sprintf(w, "%s{ ", item);
        }
        w = buf + strlen(buf);
        if (dir != 0) {
            igDirEntryView *r = (igDirEntryView *)igDirectory_GetEntryByRef((igDirectoryView *)dir, (unsigned)(*(const int *)mem));
            if (r != 0) {
                sprintf(w, "Reference[ %d ]", r->_index);
            } else {
                sprintf(w, "Reference[ -1 ]");
            }
        } else {
            sprintf(w, "Reference[ -1 ]");
        }
    }
    igStringRef text(buf);
    a = (igMemoryPoolView *)getMemoryPool();
    a = g_useOwnerAllocator ? a : ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary));
    a->Free(buf);
    return text;
}

int igRefMetaField::convertStringToMemory(const char *val, void *mem, int num, igDirectory *dir)
{
    int idx;
    const char *s = val;
    int *o = (int *)mem;
    int i;
    for (i = 0; i < num; i++) {
        igDirEntry *e;
        s = igRefMetaField_SkipPastChar((char *)s, '{');
        if (dir != 0) {
            s = igRefMetaField_SkipPastChar((char *)s, '[');
            if (sscanf(s, (const char *)&percent_d_7[0], &idx) == 0) idx = -1;
            if (idx >= 0 && idx < dir->_count) {
                e = ((igDirEntry *)igDirectory_GetEntry((int *)dir, idx));
                if (e != 0) o[i] = e->_ref;
                else o[i] = 0;
            } else o[i] = 0;
        } else o[i] = 0;
    }
    return s - val;
}

int igRefMetaField::compare(const igObject *obj1, const igObject *obj2) const
{
    int offset;

    offset = _offset;
    return *(const int *)((const char *)obj1 + offset) - *(const int *)((const char *)obj2 + offset);
}

igRefMetaField::igRefMetaField(bool boot) : igMetaField(boot)
{
    new (this, 0) igRefMetaField;
}

igRefMetaField::igRefMetaField()
{
    _construct = 0;
    _destruct = 0;
}
}
}



/* Copy the base metadata field, stamp the reference-field vtable and copy the construct/destruct
 * flags. */
namespace Gap {
namespace Core {

igRefMetaField::igRefMetaField(const igRefMetaField &other) : igMetaField(other)
{
    _construct = other._construct;
    _destruct = other._destruct;
}
}
}



/* The reference field adds no teardown of its own to the igMetaField base. */
namespace Gap {
namespace Core {

void igRefMetaField::__bootstrapDestruct()
{
    igMetaField::__bootstrapDestruct();
}

int igRefMetaField::constructPerformsReset() const
{
    return _construct;
}

int igRefMetaField::computeRequiredAlignment()
{
    return 4;
}
}
}

int igRegistry_IsLoadingEnabled(void)
{
    return 1;
}

