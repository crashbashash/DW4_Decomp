int g_resourceLoaderStackSize = 0x100000;

void igResource_StartAsyncLoading(igResourceView *self) {
    self->_loadQueue = (igStandardQueueView *)igSmartPointer<igObject>((igObject *)igQueue_Create((int)((Gap::Core::igObject *)self)->getMemoryPool())).get();
    self->_loadQueue->Create();
    self->_loadThread = (igPsx2ThreadView *)igQueue_StartServiceThread(self->_loadQueue, (int)&igResource_AsyncLoadThreadProc, g_resourceLoaderStackSize);
    self->_loadThread->SetPriority(255);
    self->_asyncLoadState = 1;
    ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault))->EnableAllocationLock(1);
}

void igResource_StopAsyncLoading(igResourceView *self) {
    igResult joined;
    igPsx2ThreadView *thread;
    igStandardQueueView *queue;
    if (self->_asyncLoadState != 0) {
        self->_asyncLoadState = 0;
        self->_loadQueue->Insert(0, 1);
        igPsx2ThreadView *current;
        thread = self->_loadThread;
        current = ((igPsx2ThreadManagerView **)&g_threadManager)[0]->GetCurrentThread();
        joined = current->Join(thread);
        igStandardQueue_StopServiceThreads(self->_loadQueue);
        queue = self->_loadQueue;
        if (queue != 0) {
            queue->_refCount = (int)queue->_refCount - 1;
            if (((unsigned long long) ((long long)(int) queue->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(queue);
        }
        self->_loadQueue.p = 0;
        thread = self->_loadThread;
        if (thread != 0) {
            thread->_refCount = (int)thread->_refCount - 1;
            if (((unsigned long long) ((long long)(int) thread->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(thread);
        }
        self->_loadThread.p = 0;
    }
}

void igResource_ReleaseDefaults(igResource *self) {
    igObject *strings;
    igObject *values;

    if (self->_asyncLoadState == 1) {
        igResource_StopAsyncLoading((igResourceView *)self);
    }
    strings = (igObject *)self->_alignmentStrings;
    if (strings != 0) {
        strings->_refCount = strings->_refCount - 1;
        if (((unsigned long long) ((long long)(int) strings->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(strings);
        }
    }
    self->_alignmentStrings = 0;
    values = (igObject *)self->_alignmentValues;
    if (values != 0) {
        values->_refCount = values->_refCount - 1;
        if (((unsigned long long) ((long long)(int) values->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(values);
        }
    }
    self->_alignmentValues = 0;
    igObject_ReleaseDefaults((igObject *)self);
}

/* The pool the resource assigns to its files: the configured one, else the resource's own allocator. */
#define RESOURCE_POOL(self, pool) ((self)->pool != 0 ? (igObject *)(self)->pool : (igObject *)((Gap::Core::igObject *)(self))->getMemoryPool())

/* Returns the directory named `path`, else creates its IGB file (configured like the resource's
 * files, in the resource's pools) and reads it synchronously through the search paths. */
void *igResource_GetOrLoadDirectory(igResource *self, int path) {
    igIGBFile *o;
    igObject *pool;
    int *old;
    int v;
    o = (igIGBFile *)igResource_GetDirectory(self, (const char *)path).p;
    if (o != 0) {
        igDirectory_AddLoadedRef((igDirectoryView *)o);
        return o;
    }
    igSmartPointer<igIGBFile> file((igIGBFile *)igIGBFile_Create((int)RESOURCE_POOL(self, _temporaryMemoryPool)));
    file.p->_sharingState = self->_IGBSharingState;
    file.p->_forceChunkSize = self->_IGBChunkSize;
    file.p->_useMemoryPoolAssignmentsState = self->_useMemoryPoolAssignmentsState;
    pool = RESOURCE_POOL(self, _temporaryMemoryPool);
    o = file.p;
    if (pool != 0) pool->_refCount = pool->_refCount + 1;
    REL_O(o->_temporaryMemoryPool)
    o->_temporaryMemoryPool = (int)pool;
    pool = RESOURCE_POOL(self, _dataMemoryPool);
    o = file.p;
    if (pool != 0) pool->_refCount = pool->_refCount + 1;
    REL_O(o->_dataMemoryPool)
    o->_dataMemoryPool = (int)pool;
    pool = RESOURCE_POOL(self, _objectMemoryPool);
    o = file.p;
    if (pool != 0) pool->_refCount = pool->_refCount + 1;
    REL_O(o->_objectMemoryPool)
    o->_objectMemoryPool = (int)pool;
    if (self->_asyncLoadState == 1) {
        file.p->_autoReadFilePostProcessState = self->_postProcessAsyncronousFilesState;
    }
    file.p->_validState = 0;
    file.p->_loadPendingState = 1;
    o = file.p;
    if (g_stringPool == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool = (StringPool *)v;
    }
    v = (int)StringPool_Intern((StringPool *)g_stringPool, (const char *)path);
    old = (int *)o->_name;
    if (old != 0) {
        int *hd = old - 2;
        int c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
    }
    o->_name = v;
    file.p->_managingResource = (int)self;
    igDirectory_AddLoadedRef((igDirectoryView *)file.p);
    igResource_AddDirectory((int *)self, (int)file.p);
    return igResource_ReadFileWithSearchPaths(self, (igIGBFileView *)file.p);
}

igDirectory *igResource_LoadDirectory(igResource *self, const char *path) {
    igResult queued;
    igObject *r;
    int v;
    igObject *pool;
    int *old;
    int *hd;
    int c;
    igIGBFile *o;
    void *res;
    igObject *t;
    r = (igObject *)igResource_GetDirectory(self, path).p;
    if (r != 0) {
        igDirectory_AddLoadedRef((igDirectoryView *)r);
        return (igDirectory *)r;
    }
    igSmartPointer<igIGBFile> file((igIGBFile *)igIGBFile_Create(self->_temporaryMemoryPool));
    file.p->_sharingState = self->_IGBSharingState;
    file.p->_forceChunkSize = self->_IGBChunkSize;
    file.p->_useMemoryPoolAssignmentsState = self->_useMemoryPoolAssignmentsState;
    pool = (igObject *)self->_temporaryMemoryPool;
    if (pool != 0) { ASSIGN_O(o, _temporaryMemoryPool, pool) }
    pool = (igObject *)self->_dataMemoryPool;
    if (pool != 0) { ASSIGN_O(o, _dataMemoryPool, pool) }
    pool = (igObject *)self->_objectMemoryPool;
    if (pool != 0) { ASSIGN_O(o, _objectMemoryPool, pool) }
    if (self->_asyncLoadState == 1) {
        file.p->_autoReadFilePostProcessState = self->_postProcessAsyncronousFilesState;
        igDirectory_CreateLoadingSemaphore((igDirectoryView *)file.p);
    }
    file.p->_validState = 0;
    file.p->_loadPendingState = 1;
    o = file.p;
    if (g_stringPool == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool = (StringPool *)v;
    }
    v = (int)StringPool_Intern((StringPool *)g_stringPool, path);
    old = (int *)o->_name;
    if (old != 0) {
        hd = old - 2;
        c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd), (StringTokenHeader *)hd);
    }
    o->_name = v;
    file.p->_managingResource = (int)self;
    igDirectory_AddLoadedRef((igDirectoryView *)file.p);
    igResource_AddDirectory((int *)self, (int)file.p);
    if (self->_asyncLoadState == 0) {
        return (igDirectory *)igResource_ReadFileWithSearchPaths(self, (igIGBFileView *)file.p);
    }
    igDirectory_AddLoadedRef((igDirectoryView *)file.p);
    queued = ((igStandardQueueView *)self->_loadQueue)->Insert((int)file.p, 1);
    res = file.p;
    return (igDirectory *)res;
}

igIGBFileView *igResource_ReadFileWithSearchPaths(igResource *self, igIGBFileView *file) {
    char buf[2048];
    int r;
    if (file == 0) return 0;
    r = 0;
    if (self->_relativeFilePath != 0 && strlen((const char *)self->_relativeFilePath) != 0) {
        sprintf(buf, "%s/%s", self->_relativeFilePath, file->_name);
        r = file->ReadFile(buf) > 0;
    }
    if (r == 0) {
        if (self->_absoluteFilePath != 0 && strlen((const char *)self->_absoluteFilePath) != 0) {
            sprintf(buf, "%s/%s", self->_absoluteFilePath, file->_name);
            r = file->ReadFile(buf) > 0;
        }
    }
    if (r == 0) {
        file->ReadFile((const char *)file->_name);
    }
    return file;
}

/* The directory is read from `found` twice. The second read, the call's argument, goes through the
 * smart pointer's accessor: calling a member takes `found`'s address, so the release in its
 * destructor binds the object to a temporary once instead of reading `found` again after the count
 * is stored, and the read is repeated behind the store through `entry`. The first read is the
 * member itself, an unmarked read the early return's release shares; the shared class's accessors
 * are `const`, and a read through one is not shared with the destructor's (the original accessor
 * left an unmarked read, as a non-const one does). */
unsigned char igResource_IsDirectoryLoaded(igResource *self, igDirectory *directory) {
    return !directory->_loadPendingState;
}

void igResource_UnloadDirectory(igResource *self, const char *name) {
    igSmartPointer<igObject> found = igResource_GetDirectory(self, name);
    igIGBFile *entry = (igIGBFile *)found.p;
    if (entry == 0) {
        return;
    }
    bool current = false;
    if (entry == (igIGBFile *)self->_imageDirectory) {
        current = true;
    }
    if (entry->_managingResource == 0) {
        entry->_managingResource = (int)self;
    }
    int remaining = igDirectory_UnrefLoaded((igDirectoryView *)found.get());
    if (current && remaining <= 0) {
        igRelease((igObject *)self->_imageDirectory);
        self->_imageDirectory = 0;
    }
}

void igResource_ClearDirectories(igResource *self) {
    int m;
    int j;
    igTDataList<igObject *> *l;
    int n;
    int i;
    igObject *p;
    igObject *q;

    l = (igTDataList<igObject *> *)self->_directoryList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = l->_data[i];
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    m = l->_count;
    for (j = 0; j < m; j++) {
        l->_data[j] = 0;
    }
    l->_count = 0;
    q = (igObject *)self->_imageDirectory;
    if (q != 0) {
        q->_refCount = q->_refCount - 1;
        if (((unsigned long long)((long long)(int)q->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(q);
        }
    }
    self->_imageDirectory = 0;
}

void igResource_RemoveIGBFiles(igResource *self) {
    int i;
    igTDataList<igObject *> *l;
    int off;
    igObject *o;
    for (i = ((igTDataList<igObject *> *)self->_directoryList)->_count - 1; i >= 0; i--) {
        off = i * 4;
        if (((Gap::Core::igObject *)(*(igObject **)((char *)((igTDataList<igObject *> *)self->_directoryList)->_data + off)))->isOfType((igMetaObject *)((int)g_igIGBFile_metaObject)) != 0) {
            l = (igTDataList<igObject *> *)self->_directoryList;
            o = *(igObject **)((char *)l->_data + off);
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy((igObject *)o);
                }
            }
            List_RemoveWordAt((igDataList *)l, i);
            *(igObject **)((char *)l->_data + l->_count * 4) = 0;
        }
    }
}

int igResource_GetDefaultResource(void) {
    return *(int *)((char *)((*(void **)0x586DC8)) + 64);
}

/* Returns the `wanted`th info object (counting from 0) of the kind named `metaName` in the resource's
 * directory `name`, or 0. */
int igDirectory_GetNthObjectOfType(igResource *resource, const char *name, const char *metaName, int wanted) {
    igSmartPointer<igObject> directory = igResource_GetDirectory(resource, (const char *)name);
    igSmartPointer<igObject> meta((igObject *)igObjectSystem_FindMetaByNameDefault(metaName), kRetainReference);
    int found;
    unsigned int i;
    if (directory.get() == 0 || meta.get() == 0) {
        return 0;
    }
    found = 0;
    for (i = 0; i < (unsigned int)igDirectory_GetInfoCount(directory.get()); i++) {
        if (((Gap::Core::igObject *)(igDirectory_GetInfo(directory.get(), i)))->isOfType((igMetaObject *)meta.get()) != 0) {
            if (found++ == wanted) {
                return igDirectory_GetInfo(directory.get(), i);
            }
        }
    }
    return 0;
}

static inline igObjectDirEntryView *AsObjectDirEntry(void *p) {
    if (p != 0 && ((Gap::Core::igObject *)p)->isOfType((igMetaObject *)g_igObjectDirEntry_metaObject) != 0) { return (igObjectDirEntryView *)p; }
    return 0;
}

/* Replaces every object of the class named `fromName` in the directory by a new instance of the
 * class named `toName`, copying the fields the two classes share by name and kind beyond igObject's;
 * a converted object that is an igInfo is also added to the directory's info list. */
void igDirectory_ConvertObjectsOfType(igDirectory *directory, const char *fromName, const char *toName) {
    igMetaObject *fromMeta;
    igMetaObject *toMeta;
    int count;
    int i;
    int fieldCount;
    int field;
    igObjectDirEntryView *entry;
    if (directory != 0) {
        fromMeta = (igMetaObject *)igObjectSystem_FindMetaByNameDefault(fromName);
        toMeta = (igMetaObject *)igObjectSystem_FindMetaByNameDefault(toName);
        if (fromMeta != 0) {
            count = directory->_count;
            for (i = 0; i < count; i++) {
                entry = AsObjectDirEntry(igDirectory_GetEntry((int *)directory, i));
                if (entry != 0 && ((Gap::Core::igObject *)entry->_ref)->isOfType(fromMeta) != 0) {
                    if (toMeta == 0) return;
                    igSmartPointer<igObject> source((igObject *)entry->_ref, kRetainReference);
                    igSmartPointer<igObject> target((igObject *)igMetaObject_CreateInstanceDefault(toMeta), kRetainReference);
                    {
                        /* drop the reference the creation returned */
                        igObject *created = target.p;
                        created->_refCount = created->_refCount - 1;
                        if (((unsigned long long)(long long)created->_refCount & 0x7fffffULL) == 0) igObject_Destroy(created);
                    }
                    fieldCount = igMetaObject_GetFieldCount(fromMeta);
                    for (field = igMetaObject_GetFieldCount((igMetaObject *)Gap::Core::igObject::getClassMeta()); field < fieldCount; field++) {
                        igMetaField *from = (igMetaField *)igMetaObject_GetFieldAt(fromMeta, field);
                        igMetaField *to = (igMetaField *)igMetaObject_FindFieldByName(toMeta, (const char *)from->_fieldName);
                        if (to != 0) {
                            bool compatible = ((Gap::Core::igObject *)to)->isOfType(((igObjectDispatchView *)from)->GetMeta()) != 0;
                            /* matching construct: the negation is materialised (sltu; xori; bnez); `!compatible`
                             * folds into the branch, and only the explicit xor keeps it (understanding-shapes.md,
                             * "A negated flag ... normalises first") */
                            if (compatible ^ true) continue;
                            ((Gap::Core::igMetaField *)((int)from))->copyShallow((Gap::Core::igObject *)((int)((char *)target.p + to->_offset - from->_offset)), (Gap::Core::igObject *)((int)source.p));
                        }
                    }
                    igDirectory_ReplaceReference((igDirectoryView *)directory, igSmartPointer<igVirtualObject>(source), igSmartPointer<igVirtualObject>(target));
                    if (((Gap::Core::igObject *)target.p)->isOfType((igMetaObject *)g_igInfo_metaObject) != 0) {
                        igDirectory_AddInfo(directory, target.p);
                    }
                }
            }
        }
    }
}

void igResource_WrapRootInSceneInfo(int directory) {
    int nodeMeta, infoMeta;
    void *root;
    igObject *info;
    if (directory != 0) {
        nodeMeta = igObjectSystem_FindMetaByNameDefault((const char *)"igNode");
        if (nodeMeta != 0) {
            root = ((void *)igDirectory_GetObjectByName(directory, (int)"root"));
            if (root != 0 && ((Gap::Core::igObject *)root)->isOfType((igMetaObject *)nodeMeta) != 0) {
                infoMeta = igObjectSystem_FindMetaByNameDefault((const char *)"igSceneInfo");
                if (infoMeta != 0) {
                    igObject *t;
                    igObjectRefMetaField *sceneGraphField, *camerasField, *sceneGraphListField;
                    void *sceneGraphList;
                    info = (igObject *)igMetaObject_CreateInstanceDefault((igMetaObject *)infoMeta);
                    t = *(igObject **)&info;
                    if (t) t->_refCount = t->_refCount + 1;
                    {
                        igObject *u = info;
                        u->_refCount = u->_refCount - 1;
                        if (((unsigned long long)(long long)(int)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                    }
                    sceneGraphField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_sceneGraph"));
                    igObjectRefMetaField_Assign(sceneGraphField, (void *)info, (igObject *)root);
                    camerasField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_cameras"));
                    sceneGraphListField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_sceneGraphList"));
                    sceneGraphList = AsObjectList(*(void **)((char *)info + sceneGraphListField->_offset));
                    if (sceneGraphList != 0) ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)sceneGraphList, (igObject *)root);
                    igObjectRefMetaField_Assign(camerasField, (void *)info, (igObject *)0);
                    igDirectory_AddInfo((void *)directory, (void *)info);
                    {
                        igObject *u = info;
                        if (u != 0) {
                            u->_refCount = u->_refCount - 1;
                            if (((unsigned long long)(long long)(int)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                        }
                    }
                }
            }
        }
    }
}

/* With _autoCompatibility, brings directory `name` up to date: converts its igSceneWrapper objects
 * to igSceneInfo, wraps a bare root in one and marks the directory compatible. */
void igResource_FinishAsyncLoad(igResource *self, int name) {
    igDirectory *directory;
    if (self->_autoCompatibility != 0) {
        directory = (igDirectory *)igResource_GetDirectory(self, (const char *)name).p;
        if (directory != 0) {
            igDirectory_ConvertObjectsOfType(directory, (const char *)"igSceneWrapper", (const char *)"igSceneInfo");
            igResource_WrapRootInSceneInfo((int)directory);
            directory->_compatibleState = 1;
        }
    }
}
