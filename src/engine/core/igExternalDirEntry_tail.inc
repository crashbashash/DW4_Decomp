void igExternalDirEntry_ReadFile(igExternalDirEntryView *self, void *file) {
    int path, pool, old, answer;
    int *hd;
    path = ((igIGBFile *)file)->_basePath;
    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    path = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)path);
    old = self->_externalFilePath;
    if (old != 0) {
        hd = (int *)(old - 8);
        pool = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = pool;
        if (pool == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (int)hd);
        }
    }
    self->_externalFilePath = path;
    self->resolveDirectory(((igIGBFile *)file)->_userLoadFunction);
    if (self->_ref == 0 && g_igExternalDirEntry_loadFailureWarned == 0) {
        answer = igReport_Warning(text_igIGBFile_readFile_External_Entr, self->_entryName, self->_externalFilePath);
        if (answer != 1 && answer == 2) {
            g_igExternalDirEntry_loadFailureWarned = 1;
        }
    }
    igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, self->_ref);
}

void igExternalDirEntry_SetDirectoryName(igExternalDirEntry *self, int name) {
    int *header;
    int refCount;
    int pool;
    int *old;
    int *interned;
    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    interned = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)name)));
    old = (int *)self->_directoryName;
    if (old != 0) {
        header = old - 2;
        refCount = old[-1] - 1;
        old[-1] = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    self->_directoryName = (int)interned;
}

void igExternalDirEntry_SetRef(igDirEntry *self, igObject *ref) {
    igObject *old;
    if (ref != 0) {
        ref->_refCount = (int)((int) (ref->_refCount + 1));
    }
    old = (igObject *)((void *)(self->_ref));
    if (old != 0) {
        old->_refCount = (int)((int) (old->_refCount - 1));
        if (((unsigned long long) ((long long)(int) old->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_ref = (int)(ref);
}

int igExternalDirEntry_LoadExternalFile(igExternalDirEntryView *self, int loadFunction) {
    igSmartPointer<igIGBFileView> stream(((igIGBFileView *)igIGBFile_Create(((int)igObject_GetAllocator((int)self)))));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->_userLoadFunction = loadFunction;
    stream.get()->ReadFile((char *)self->_directoryName);
    if (stream.get()->_count == 0) {
        s1 = (char *)self->_directoryName;
        len = strlen(self->_externalFilePath);
        len = len + strlen(s1);
        c = strlen(&text_slash[0]);
        buf = (char *)igObject_AllocateStorage((int)self, c + len + 1);
        strcpy(buf, self->_externalFilePath);
        strcat(buf, &text_slash[0]);
        strcat(buf, self->_directoryName);
        stream.get()->ReadFile(buf);
        igObject_FreeMemory((int)self, (int)buf);
    }
    self->setRef(igDirectory_GetRefByName((int)(stream.get()), self->_entryName));
    if (self->_ref == 0) {
        self->setRef(igDirectory_GetRefByName((int)(stream.get()), (int)&text_root[0]));
    }
    return self->_ref != 0;
}

/* Drops the reference the clone was created with; the smart pointer holding it keeps its own. */
static inline void dropCreationReference(igVirtualObject *object) {
    object->_refCount = object->_refCount - 1;
    if ((object->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(object);
    }
}

/* Resolve the entry through the resource manager's directory of its name, creating and registering
 * that directory if it is missing. When the directory cannot resolve it, the entry loads its file and
 * then calls `loadFunction`; a resolved entry is cloned into the directory so later lookups find it. */
int igExternalDirEntry_ResolveDirectory(igExternalDirEntryView *self, int loadFunction) {
    igMemoryPoolView *pool;
    igResource *resource = ((ObjectSystemView *)g_objectSystem[0])->resource;
    igSmartPointer<igObject> directory = igResource_GetDirectory(resource, self->_directoryName);
    if (directory.get() == 0) {
        pool = igObject_GetAllocator((int)self);
        directory.release();
        directory.p = (igObject *)igDirectory_Create((int)pool);
        igDirectory_SetName((igDirectoryView *)directory.get(), self->_directoryName);
        igResource_AddDirectory((int *)resource, (int)directory.get());
    }
    ((igDirectoryDispatchView *)directory.get())->resolveExternalEntry(self);
    if (self->_ref == 0) self->loadExternalFile(loadFunction);
    if (self->_ref == 0 && loadFunction != 0) ((void (*)(igExternalDirEntryView *))loadFunction)(self);
    if (self->_ref != 0) {
        igSmartPointer<igDirEntryView> entry(self->cloneViaMetadata(1), kRetainReference);
        dropCreationReference(entry.get());
        igNamedObject_SetName((igNamedObject *)entry.get(), self->_entryName);
        entry->_refType = 0;
        entry->setRef(self->_ref);
        entry->_index = ((igDirectoryView *)directory.get())->_count;
        ObjectList_AppendRetained((igObjectList *)directory.get(), (igObject *)entry.get());
        return 1;
    }
    return 0;
}

void igExternalDirEntry_InitDefaults(igDirEntry *self) {
    igDirEntry_InitDefaults((int)self);
    self->_resolveMethod = 2;
    self->_refType = 0;
}

void igExternalDirEntry_ReleaseDefaults(void **self) {
    ((igDirEntryView *)(self))->setRef((int)(0));
    igObject_ReleaseDefaults((int)self);
}

