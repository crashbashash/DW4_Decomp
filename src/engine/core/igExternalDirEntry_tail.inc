unsigned char g_igExternalDirEntry_loadFailureWarned;

void igExternalDirEntry_ReadFile(igExternalDirEntryView *self, void *file) {
    int path, pool, old, answer;
    int *hd;
    path = ((igIGBFile *)file)->_basePath;
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    path = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)path);
    old = self->_externalFilePath;
    if (old != 0) {
        hd = (int *)(old - 8);
        pool = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = pool;
        if (pool == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
        }
    }
    self->_externalFilePath = path;
    self->ResolveDirectory(((igIGBFile *)file)->_userLoadFunction);
    if (self->_ref == 0 && g_igExternalDirEntry_loadFailureWarned == 0) {
        answer = igReport_Warning("igIGBFile::readFile() - External Entry \"%s\" failed to load with base path (\"%s\")\n", self->_entryName, self->_externalFilePath);
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
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = (StringPool *)pool;
    }
    interned = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)name)));
    old = (int *)self->_directoryName;
    if (old != 0) {
        header = old - 2;
        refCount = old[-1] - 1;
        old[-1] = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    self->_directoryName = (int)interned;
}

void igExternalDirEntry_SetRef(igDirEntry *self, igObject *ref) {
    igObject *old;
    igObject::ref(ref);
    old = (igObject *)((void *)(self->_ref));
    igObject::release(old);
    self->_ref = (int)(ref);
}

int igExternalDirEntry_LoadExternalFile(igExternalDirEntryView *self, int loadFunction) {
    igSmartPointer<igIGBFileView> stream(((igIGBFileView *)igIGBFile_Create(((int)((Gap::Core::igObject *)self)->getMemoryPool()))));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->_userLoadFunction = loadFunction;
    stream.get()->ReadFile((char *)self->_directoryName);
    if (stream.get()->_count == 0) {
        s1 = (char *)self->_directoryName;
        len = strlen((const char *)self->_externalFilePath);
        len = len + strlen(s1);
        c = strlen("/");
        buf = (char *)((Gap::Core::igObject *)self)->malloc(c + len + 1);
        strcpy(buf, (const char *)self->_externalFilePath);
        strcat(buf, "/");
        strcat(buf, (const char *)self->_directoryName);
        stream.get()->ReadFile(buf);
        ((Gap::Core::igObject *)self)->free((void *)buf);
    }
    self->SetRef(igDirectory_GetRefByName((int)(stream.get()), self->_entryName));
    if (self->_ref == 0) {
        self->SetRef(igDirectory_GetRefByName((int)(stream.get()), (int)"root"));
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
    igResource *resource = g_objectSystem->resource;
    igSmartPointer<igObject> directory = igResource_GetDirectory(resource, (const char *)self->_directoryName);
    if (directory.get() == 0) {
        pool = ((Gap::Core::igObject *)self)->getMemoryPool();
        directory.release();
        directory.p = (igObject *)igDirectory_Create((int)pool);
        igDirectory_SetName((igDirectoryView *)directory.get(), self->_directoryName);
        igResource_AddDirectory((int *)resource, (int)directory.get());
    }
    ((igDirectoryDispatchView *)directory.get())->ResolveExternalEntry(self);
    if (self->_ref == 0) self->LoadExternalFile(loadFunction);
    if (self->_ref == 0 && loadFunction != 0) ((void (*)(igExternalDirEntryView *))loadFunction)(self);
    if (self->_ref != 0) {
        igSmartPointer<igDirEntryView> entry(self->CloneViaMetadata(1), kRetainReference);
        dropCreationReference(entry.get());
        igNamedObject_SetName((igNamedObject *)entry.get(), (const char *)self->_entryName);
        entry->_refType = 0;
        entry->SetRef(self->_ref);
        entry->_index = ((igDirectoryView *)directory.get())->_count;
        ((Gap::Core::igObjectList *)(directory.get()))->append((Gap::Core::igObject *)entry.get());
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
    ((igDirEntryView *)(self))->SetRef((int)(0));
    igObject_ReleaseDefaults((igObject *)self);
}

