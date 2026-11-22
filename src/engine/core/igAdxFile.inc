const char *g_searchFilePathDefault = ".";
void **g_searchFilePath;

void ***igAdxFile_GetSearchPathHolder(void) {
    void **a;
    void **al;
    void **cell;
    void **t;
    int name;
    int pool;
    char *old;
    void *nw;
    int *hdr;
    int c;
    if (g_searchFilePath == 0) {
        al = (void **)Memory_GetCurrentAllocator();
        if (g_useOwnerAllocator != 0) {
            a = al;
        } else {
            a = (void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        }
        cell = t = (void **)((igMemoryPoolView *)a)->Allocate(4);
        if (t != 0) { *t = 0; }
        g_searchFilePath = cell;
        name = (int)g_searchFilePathDefault;
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        nw = ((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)name));
        old = (char *)*cell;
        if (old != 0) {
            hdr = (int *)((char *)old - 8);
            c = *(int *)((char *)old - 4) - 1;
            *(int *)((char *)old - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (StringTokenHeader *)hdr);
            }
        }
        *cell = nw;
    }
    return &g_searchFilePath;
}

namespace Gap {
namespace Core {

void igFile::setFileName(const char *fname)
{
    _fileName = fname;
}

void igFile::readPastChar(char c)
{
    char ch;
    do {
        ch = (char)fgetc();
    } while (c != ch && ch != -1);
}

void igFile::setOpenMode(OpenMode openMode)
{
    _openMode = openMode;
}

bool igFile::isAbsolutePath(const char *path) {
    char c;

    if (path == 0) {
        return 0;
    }
    c = *path;
    if (c == '/' || c == '\\') {
        return 1;
    }
    return ((int)strchr(path, ':')) != 0;
}

bool igFile::containsRelativePath(const char *path) {
    if (path == 0) {
        return 0;
    }
    if ((((int)strchr(path, '/')) == 0) && (((int)strchr(path, '\\')) == 0)) {
        return 0;
    }
    return 1;
}

void igFile::setSearchPath(const char *path) {
    int *oldHeader;
    int *header;
    int oldRefCount;
    int refCount;
    int pool;
    void **oldSlot;
    void **slot;
    void *previous;
    void *interned;
    void *oldText;

    if (path == 0) {
        oldSlot = (void **)(*igAdxFile_GetSearchPathHolder());
        if (oldSlot != 0) {
            if (oldSlot != 0) {
                oldText = (void *)(*oldSlot);
                if (oldText != 0) {
                    oldHeader = (int *)((char *)oldText - 8);
                    oldRefCount = *(int *)((char *)(oldText) - 4) - 1;
                    *(int *)((char *)(oldText) - 4) = oldRefCount;
                    if (oldRefCount == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (StringTokenHeader *)oldHeader);
                    }
                }
            }
            Memory_FreeBuffer(oldSlot);
        }
    } else {
        slot = (void **)(*igAdxFile_GetSearchPathHolder());
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)path)));
        previous = (void *)(*slot);
        if (previous != 0) {
            header = (int *)((char *)previous - 8);
            refCount = *(int *)((char *)(previous) - 4) - 1;
            *(int *)((char *)(previous) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
        *slot = interned;
    }
}

void igFile::freadAsynchronous(void *ptr, int sizeInBytes, igIOCallbackFunction *callback, int token)
{
    callback(fread(ptr, 1, sizeInBytes), token);
}

void igFile::setSearchPathFromRegistry() {
    const char *searchPathKey = (const char *)g_searchFilePathDefault;
    int registry = (int)g_objectSystem->configRegistry;
    igStringObj *text;
    const char *path;
    if (registry != 0) {
        text = (igStringObj *)igStringObj_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
        ((Gap::Core::igRegistry *)registry)->getValue(2, (const char *)"searchFilePath", *(igStringObjRef *)&text, searchPathKey, 0);
        path = (const char *)text->_buffer;
        if (path == 0) {
            path = g_stringObjEmptyText;
        }
        setSearchPath(path);
        ::igObject::release(text);
    }
}

const char *igFile::getSearchPath() {
    return (const char *)**((int **)igAdxFile_GetSearchPathHolder());
}

bool igFile::getNextPath(const char **cursor, char *out, unsigned int outSize) {
    const char *start;
    const char *comma;
    char last;
    unsigned int length;

    start = *cursor;
    *out = 0;
    if ((start == 0) || (*start == 0)) {
        return 0;
    }
    comma = strchr(start, 0x2C);
    if (comma == 0) {
        length = ((unsigned int)strlen(start));
        if (outSize - 2 <= length) {
            return 0;
        }
        strcpy(out, start);
        *cursor = 0;
    } else {
        length = comma - start;
        if (outSize - 2 <= length) {
            return 0;
        }
        strncpy(out, start, length);
        out[length] = 0;
        *cursor = comma + 1;
    }
    if (strcmp(out, ((char *)".")) == 0) {
        *out = 0;
    } else {
        last = out[length - 1];
        if (last != 0x2F) {
            if (last != 0x5C) {
                strcat(out, ((char *)"/"));
            }
        }
    }
    return 1;
}

const char *igFile::generateFilename(const char *name)
{
    _completeFilename = name;
    return name;
}
}
}

