void igResource_StartAsyncLoading(igResourceView *self) {
    self->_loadQueue = (igStandardQueueView *)igSmartPointer<igObject>((igObject *)igQueue_Create((int)igObject_GetAllocator((int)self))).get();
    self->_loadQueue->create();
    self->_loadThread = (igPsx2ThreadView *)igQueue_StartServiceThread(self->_loadQueue, (int)&igResource_AsyncLoadThreadProc, g_resourceLoaderStackSize[0]);
    self->_loadThread->setPriority(255);
    self->_asyncLoadState = 1;
    ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault))->vfunc_34(1);
}

void igResource_StopAsyncLoading(igResourceView *self) {
    igResult joined;
    igPsx2ThreadView *thread;
    igStandardQueueView *queue;
    if (self->_asyncLoadState != 0) {
        self->_asyncLoadState = 0;
        self->_loadQueue->insert(0, 1);
        igPsx2ThreadView *current;
        thread = self->_loadThread;
        current = ((igPsx2ThreadManagerView **)g_threadManager)[0]->getCurrentThread();
        joined = current->join(thread);
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
    igObject *temp_a0;
    igObject *temp_a0_2;

    if (self->_asyncLoadState == 1) {
        igResource_StopAsyncLoading((igResourceView *)self);
    }
    temp_a0 = (igObject *)self->_alignmentStrings;
    if (temp_a0 != 0) {
        temp_a0->_refCount = temp_a0->_refCount - 1;
        if (((unsigned long long) ((long long)(int) temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    self->_alignmentStrings = 0;
    temp_a0_2 = (igObject *)self->_alignmentValues;
    if (temp_a0_2 != 0) {
        temp_a0_2->_refCount = temp_a0_2->_refCount - 1;
        if (((unsigned long long) ((long long)(int) temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    self->_alignmentValues = 0;
    igObject_ReleaseDefaults((int)self);
}

void *igResource_LoadDirectory(igResource *self, int path) {
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
        return r;
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
    if (g_stringPool[0] == 0) {
        v = ((int)StringPool_Allocate(16));
        if (v != 0) v = ((int)StringPool_Construct((StringPool *)v));
        g_stringPool[0] = v;
    }
    v = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)path);
    old = (int *)o->_name;
    if (old != 0) {
        hd = old - 2;
        c = old[-1] - 1;
        old[-1] = c;
        if (c == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd), (int)hd);
    }
    o->_name = v;
    file.p->_managingResource = (int)self;
    igDirectory_AddLoadedRef((igDirectoryView *)file.p);
    igResource_AddDirectory((int *)self, (int)file.p);
    if (self->_asyncLoadState == 0) {
        return igResource_ReadFileWithSearchPaths(self, (igIGBFileView *)file.p);
    }
    igDirectory_AddLoadedRef((igDirectoryView *)file.p);
    queued = ((igStandardQueueView *)self->_loadQueue)->insert((int)file.p, 1);
    res = file.p;
    return res;
}

igIGBFileView *igResource_ReadFileWithSearchPaths(igResource *self, igIGBFileView *file) {
    char buf[2048];
    int r;
    if (file == 0) return 0;
    r = 0;
    if (self->_relativeFilePath != 0 && strlen(self->_relativeFilePath) != 0) {
        sprintf(buf, &DAT_004f9a78[0], self->_relativeFilePath, file->_name);
        r = file->ReadFile(buf) > 0;
    }
    if (r == 0) {
        if (self->_absoluteFilePath != 0 && strlen(self->_absoluteFilePath) != 0) {
            sprintf(buf, &DAT_004f9a78[0], self->_absoluteFilePath, file->_name);
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
bool igResource_IsDirectoryLoaded(igResource *self, igDirectoryView *directory) {
    return !directory->_loadPendingState;
}

void igResource_UnloadDirectory(igResource *self, int name) {
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
        if (igObject_IsKindOf((void *)(*(igObject **)((char *)((igTDataList<igObject *> *)self->_directoryList)->_data + off)), (igMetaObject *)(((int *)g_igIGBFile_metaObject)[0])) != 0) {
            l = (igTDataList<igObject *> *)self->_directoryList;
            o = *(igObject **)((char *)l->_data + off);
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if ((o->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy((void *)o);
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

void igResource_WrapRootInSceneInfo(int arg0) {
    int s0m, s1m;
    void *s1;
    igObject *sp5C;
    if (arg0 != 0) {
        s0m = igObjectSystem_FindMetaByNameDefault((const char *)&text_igNode[0]);
        if (s0m != 0) {
            s1 = ((void *)igDirectory_GetObjectByName(arg0, (int)&text_root[0]));
            if (s1 != 0 && igObject_IsKindOf(s1, (igMetaObject *)s0m) != 0) {
                s1m = igObjectSystem_FindMetaByNameDefault((const char *)&text_igSceneInfo[0]);
                if (s1m != 0) {
                    igObject *t;
                    igObjectRefMetaField *f1, *f2, *f3;
                    void *l;
                    sp5C = (igObject *)igMetaObject_CreateInstanceDefault((void *)s1m);
                    t = *(igObject **)&sp5C;
                    if (t) t->_refCount = t->_refCount + 1;
                    {
                        igObject *u = sp5C;
                        u->_refCount = u->_refCount - 1;
                        if (((unsigned long long)(long long)(int)u->_refCount & 0x7fffffULL) == 0) igObject_Destroy(u);
                    }
                    f1 = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)sp5C)->getMeta(), (const char *)&text_sceneGraph[0]));
                    igObjectRefMetaField_Assign(f1, (void *)sp5C, (igObject *)s1);
                    f2 = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)sp5C)->getMeta(), (const char *)&text_cameras[0]));
                    f3 = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)sp5C)->getMeta(), (const char *)&text_sceneGraphList[0]));
                    l = AsObjectList(*(void **)((char *)sp5C + f3->_offset));
                    if (l != 0) ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)l, (igObject *)s1);
                    igObjectRefMetaField_Assign(f2, (void *)sp5C, (igObject *)0);
                    igDirectory_AddInfo((void *)arg0, (void *)sp5C);
                    {
                        igObject *u = sp5C;
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

