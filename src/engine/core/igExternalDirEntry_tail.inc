void igExternalDirEntry_ReadFile(igExternalDirEntryView *arg0, void *arg1) {
    int s2, v, old, r;
    int *hd;
    s2 = ((igIGBFile *)arg1)->_basePath;
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) {
            v = ((int)StringPool_Construct((StringPool *)v));
        }
        g_stringPool[0] = v;
    }
    s2 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)s2);
    old = arg0->_externalFilePath;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*hd), (int)hd);
        }
    }
    arg0->_externalFilePath = s2;
    arg0->vfunc_43(((igIGBFile *)arg1)->_userLoadFunction);
    if (arg0->_ref == 0 && GPR_00554c00 == 0) {
        r = igReport_Warning(DAT_004f99f0, arg0->_entryName, arg0->_externalFilePath);
        if (r != 1 && r == 2) {
            GPR_00554c00 = 1;
        }
    }
    igDirectory_SetEntryRef((igDirectoryView *)arg1, arg0->_index, arg0->_ref);
}

void igExternalDirEntry_SetDirectoryName(igExternalDirEntry *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;
    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (int *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = (int *)arg0->_directoryName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_directoryName = (int)temp_s0;
}

void igExternalDirEntry_SetRef(igDirEntry *arg0, igObject *arg1) {
    igObject *temp_a0;
    if (arg1 != 0) {
        arg1->_refCount = (int)((int) (arg1->_refCount + 1));
    }
    temp_a0 = (igObject *)((void *)(arg0->_ref));
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
        if (((unsigned long long) ((long long)(int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_ref = (int)(arg1);
}

int igExternalDirEntry_LoadExternalFile(igExternalDirEntryView *arg0, int arg1) {
    igSmartPointer<igIGBFileView> stream(((igIGBFileView *)igIGBFile_Create(((int)igObject_GetAllocator((int)arg0)))));
    char *s1;
    int len;
    int c;
    char *buf;
    stream.get()->_userLoadFunction = arg1;
    stream.get()->ReadFile((char *)arg0->_directoryName);
    if (stream.get()->_count == 0) {
        s1 = (char *)arg0->_directoryName;
        len = strlen(arg0->_externalFilePath);
        len = len + strlen(s1);
        c = strlen(&DAT_004f9a48[0]);
        buf = (char *)igObject_AllocateStorage((int)arg0, c + len + 1);
        strcpy(buf, arg0->_externalFilePath);
        strcat(buf, &DAT_004f9a48[0]);
        strcat(buf, arg0->_directoryName);
        stream.get()->ReadFile(buf);
        igObject_FreeMemory((int)arg0, (int)buf);
    }
    arg0->vfunc_23(igDirectory_GetRefByName((int)(stream.get()), arg0->_entryName));
    if (arg0->_ref == 0) {
        arg0->vfunc_23(igDirectory_GetRefByName((int)(stream.get()), (int)&text_root[0]));
    }
    return arg0->_ref != 0;
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
    if (self->_ref == 0) self->vfunc_44(loadFunction);
    if (self->_ref == 0 && loadFunction != 0) ((void (*)(igExternalDirEntryView *))loadFunction)(self);
    if (self->_ref != 0) {
        igSmartPointer<igDirEntryView> entry(self->cloneViaMetadata(1), kRetainReference);
        dropCreationReference(entry.get());
        igNamedObject_SetName((igNamedObject *)entry.get(), self->_entryName);
        entry->_refType = 0;
        entry->vfunc_23(self->_ref);
        entry->_index = ((igDirectoryView *)directory.get())->_count;
        ObjectList_AppendRetained((igObjectList *)directory.get(), (igObject *)entry.get());
        return 1;
    }
    return 0;
}

void igExternalDirEntry_InitDefaults(igDirEntry *arg0) {
    igDirEntry_InitDefaults((int)arg0);
    arg0->_resolveMethod = 2;
    arg0->_refType = 0;
}

void igExternalDirEntry_ReleaseDefaults(void **arg0) {
    ((igDirEntryView *)(arg0))->vfunc_23((int)(0));
    igObject_ReleaseDefaults((int)arg0);
}

