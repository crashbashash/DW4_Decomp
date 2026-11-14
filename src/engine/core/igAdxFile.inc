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
    if (g_searchFilePath[0] == 0) {
        al = (void **)Memory_GetCurrentAllocator();
        if (g_useOwnerAllocator != 0) {
            a = al;
        } else {
            a = (void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
        }
        cell = t = (void **)((igMemoryPoolView *)a)->Allocate(4);
        if (t != 0) { *t = 0; }
        g_searchFilePath[0] = cell;
        name = g_searchFilePathDefault[0];
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        nw = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)name));
        old = (char *)*cell;
        if (old != 0) {
            hdr = (int *)((char *)old - 8);
            c = *(int *)((char *)old - 4) - 1;
            *(int *)((char *)old - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
            }
        }
        *cell = nw;
    }
    return &g_searchFilePath[0];
}

void igFile_SetFileName(int *self, const char *name) {
    int *header;
    int refCount;
    int pool;
    void *previous;
    void *interned;

    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], name)));
    previous = (void *)self[3];
    if (previous != 0) {
        header = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)(previous) - 4) - 1;
        *(int *)((char *)(previous) - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    self[3] = (int)interned;
}

void igFile_SkipToChar(igFileView *self, long long character) {
    signed char want = (signed char)character;
    signed char c;
    do {
        c = (signed char)self->GetChar();
    } while (want != c && c != -1);
}

void igAdxFile_SetOpenMode(int object, int openMode)
{
    igAdxFile *self = (igAdxFile *)object;
    self->_openMode = openMode;
}

bool FilePath_IsAbsolute(const char *path) {
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

bool FilePath_HasDirectory(const char *path) {
    if (path == 0) {
        return 0;
    }
    if ((((int)strchr(path, '/')) == 0) && (((int)strchr(path, '\\')) == 0)) {
        return 0;
    }
    return 1;
}

void igAdxFile_SetBasePath(int path) {
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
                        StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (int)oldHeader);
                    }
                }
            }
            Memory_FreeBuffer(oldSlot);
        }
    } else {
        slot = (void **)(*igAdxFile_GetSearchPathHolder());
        if (g_stringPool[0] == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)path)));
        previous = (void *)(*slot);
        if (previous != 0) {
            header = (int *)((char *)previous - 8);
            refCount = *(int *)((char *)(previous) - 4) - 1;
            *(int *)((char *)(previous) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
        *slot = interned;
    }
}

void igFile_ReadAsync(igFileView *self, int buffer, int size, int (*callback)(int, int), int context) {
    callback(self->Read((void *)buffer, 1, size), context);
}

void igAdxFile_LoadSearchFilePath(void) {
    const char *searchPathKey = (const char *)g_searchFilePathDefault[0];
    int registry = (int)((ObjectSystemView **)g_objectSystem)[0]->configRegistry;
    igStringObj *text;
    int path;
    if (registry != 0) {
        text = (igStringObj *)igStringObj_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleString));
        igRegistry_GetValueStringObj(registry, 2, (const char *)text_searchFilePath, &text, searchPathKey, 0);
        path = text->_buffer;
        if (path == 0) {
            path = (int)g_stringObjEmptyText[0];
        }
        igAdxFile_SetBasePath(path);
        igRelease(text);
    }
}

int igAdxFile_GetSearchPaths(void) {
    return **((int **)igAdxFile_GetSearchPathHolder());
}

int igAdxFile_GetNextSearchPath(char **cursor, char *out, int outSize) {
    char *start;
    char *comma;
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
        if ((unsigned int) (outSize - 2) <= length) {
            return 0;
        }
        strcpy(out, start);
        *cursor = 0;
    } else {
        length = comma - start;
        if ((unsigned int) (outSize - 2) <= length) {
            return 0;
        }
        strncpy(out, start, length);
        out[length] = 0;
        *cursor = comma + 1;
    }
    if (strcmp(out, ((char *)text_dot)) == 0) {
        *out = 0;
    } else {
        last = out[length - 1];
        if (last != 0x2F) {
            if (last != 0x5C) {
                strcat(out, ((char *)text_slash));
            }
        }
    }
    return 1;
}

int igFile_SetCompleteFilename(igFileView *self, int path) {
    int s0;
    int *a0;
    int *hdr;
    int v;
    int obj;
    if (g_stringPool[0] == 0) {
        obj = ((int)StringPool_Allocate(0x10));
        if (obj != 0) {
            obj = ((int)StringPool_Construct((StringPool *)obj));
        }
        g_stringPool[0] = obj;
    }
    s0 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)path);
    a0 = (int *)self->_completeFilename;
    if (a0 != 0) {
        hdr = a0 - 2;
        v = a0[-1] - 1;
        a0[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hdr), (int)hdr);
        }
    }
    self->_completeFilename = (char *)s0;
    return path;
}

