namespace Gap {
namespace Core {

int igResource::_asynchronousLoadingThreadStackSize = 0x100000;

void igResource::enableAsynchronousLoading() {
    _loadQueue = igSmartPointer< ::igQueue>((::igQueue *)igQueue_Create((int)getMemoryPool()));
    ((igStandardQueueView *)_loadQueue.p)->Create();
    _loadThread = (::igThread *)igQueue_StartServiceThread(_loadQueue.p, (int)&igResource_AsyncLoadThreadProc, _asynchronousLoadingThreadStackSize);
    ((igPsx2ThreadView *)_loadThread.p)->SetPriority(255);
    _asyncLoadState = 1;
    ((igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault))->EnableAllocationLock(1);
}

void igResource::disableAsynchronousLoading() {
    igResult joined;
    igPsx2ThreadView *thread;
    igPsx2ThreadView *current;
    if (_asyncLoadState != 0) {
        _asyncLoadState = 0;
        ((igStandardQueueView *)_loadQueue.p)->Insert(0, 1);
        thread = (igPsx2ThreadView *)_loadThread.p;
        current = ((igPsx2ThreadManagerView **)&g_threadManager)[0]->GetCurrentThread();
        joined = current->Join(thread);
        igStandardQueue_StopServiceThreads((igStandardQueueView *)_loadQueue.p);
        _loadQueue.clear();
        _loadThread.clear();
    }
}

void igResource::releaseDefaults() {
    if (_asyncLoadState == 1) {
        disableAsynchronousLoading();
    }
    _alignmentStrings.clear();
    _alignmentValues.clear();
    igObject_ReleaseDefaults((::igObject *)this);
}
}
}

/* The pool the resource assigns to its files: the configured one, else the resource's own allocator. */
#define RESOURCE_POOL(pool) ((pool).p != 0 ? (::igObject *)(pool).p : (::igObject *)getMemoryPool())

namespace Gap {
namespace Core {

/* Returns the directory named `path`, else creates its IGB file (configured like the resource's
 * files, in the resource's pools) and reads it synchronously through the search paths. */
igDirectory *igResource::loadSynchronous(char const *path) {
    igIGBFile *o;
    o = (igIGBFile *)getDirectory((const char *)path).p;
    if (o != 0) {
        o->loadRef();
        return o;
    }
    igSmartPointer<igIGBFile> file(igIGBFile::_instantiateFromPool((igMemoryPoolView *)RESOURCE_POOL(_temporaryMemoryPool)));
    file->_sharingState = _IGBSharingState;
    file->_forceChunkSize = _IGBChunkSize;
    file->_useMemoryPoolAssignmentsState = _useMemoryPoolAssignmentsState;
    file->setTemporaryMemoryPool((::igMemoryPool *)RESOURCE_POOL(_temporaryMemoryPool));
    file->setDataMemoryPool((::igMemoryPool *)RESOURCE_POOL(_dataMemoryPool));
    file->setObjectMemoryPool((::igMemoryPool *)RESOURCE_POOL(_objectMemoryPool));
    if (_asyncLoadState == 1) {
        file->_autoReadFilePostProcessState = _postProcessAsyncronousFilesState;
    }
    file->_validState = 0;
    file->_loadPendingState = 1;
    file->setName(path);
    file->setManagingResource(this);
    file->loadRef();
    appendDirectory(file);
    return doLoad(file);
}

igDirectory *igResource::load(const char *path) {
    igResult queued;
    igDirectory *r;
    ::igMemoryPool *pool;
    r = getDirectory(path).p;
    if (r != 0) {
        r->loadRef();
        return r;
    }
    igSmartPointer<igIGBFile> file(igIGBFile::_instantiateFromPool((igMemoryPoolView *)_temporaryMemoryPool.p));
    file->_sharingState = _IGBSharingState;
    file->_forceChunkSize = _IGBChunkSize;
    file->_useMemoryPoolAssignmentsState = _useMemoryPoolAssignmentsState;
    pool = _temporaryMemoryPool;
    if (pool != 0) file->setTemporaryMemoryPool(pool);
    pool = _dataMemoryPool;
    if (pool != 0) file->setDataMemoryPool(pool);
    pool = _objectMemoryPool;
    if (pool != 0) file->setObjectMemoryPool(pool);
    if (_asyncLoadState == 1) {
        file->_autoReadFilePostProcessState = _postProcessAsyncronousFilesState;
        file->createLoadingSemaphore();
    }
    file->_validState = 0;
    file->_loadPendingState = 1;
    file->setName(path);
    file->setManagingResource(this);
    file->loadRef();
    appendDirectory(file);
    if (_asyncLoadState == 0) {
        return doLoad(file);
    }
    file->loadRef();
    queued = ((igStandardQueueView *)_loadQueue.p)->Insert((int)file.p, 1);
    return file;
}

igIGBFile *igResource::doLoad(igIGBFile *file) {
    char buf[2048];
    int r;
    if (file == 0) return 0;
    r = 0;
    if (_relativeFilePath.p != 0 && strlen(_relativeFilePath.p) != 0) {
        sprintf(buf, "%s/%s", _relativeFilePath.p, file->_name.p);
        r = file->readFile(buf) > 0;
    }
    if (r == 0) {
        if (_absoluteFilePath.p != 0 && strlen(_absoluteFilePath.p) != 0) {
            sprintf(buf, "%s/%s", _absoluteFilePath.p, file->_name.p);
            r = file->readFile(buf) > 0;
        }
    }
    if (r == 0) {
        file->readFile(file->_name.p);
    }
    return file;
}

bool igResource::isLoadFinished(igDirectory *directory) {
    return !directory->_loadPendingState;
}

/* The directory is read from `found` twice. The second read, the call's argument, goes through the
 * smart pointer's accessor: calling a member takes `found`'s address, so the release in its
 * destructor binds the object to a temporary once instead of reading `found` again after the count
 * is stored, and the read is repeated behind the store through `entry`. The first read is the
 * member itself, an unmarked read the early return's release shares; the shared class's accessors
 * are `const`, and a read through one is not shared with the destructor's (the original accessor
 * left an unmarked read, as a non-const one does). */
void igResource::unload(const char *name) {
    igSmartPointer<igDirectory> found = getDirectory(name);
    igDirectory *entry = found.p;
    if (entry == 0) {
        return;
    }
    bool current = false;
    if (entry == _imageDirectory.p) {
        current = true;
    }
    if (entry->_managingResource == 0) {
        entry->_managingResource = this;
    }
    int remaining = found.get()->loadRelease();
    if (current && remaining <= 0) {
        _imageDirectory.clear();
    }
}

void igResource::unloadAll() {
    int m;
    int j;
    ::igTDataList< ::igObject *> *l;
    int n;
    int i;
    ::igObject *p;

    l = (::igTDataList< ::igObject *> *)_directoryList.p;
    n = l->_count;
    for (i = 0; i < n; i++) {
        p = l->_data[i];
        ::igObject::release(p);
    }
    m = l->_count;
    for (j = 0; j < m; j++) {
        l->_data[j] = 0;
    }
    l->_count = 0;
    _imageDirectory.clear();
}

void igResource::unloadAllIGBs() {
    int i;
    ::igTDataList< ::igObject *> *l;
    int off;
    ::igObject *o;
    for (i = _directoryList->_count - 1; i >= 0; i--) {
        off = i * 4;
        if (_directoryList->get(i)->isOfType((igMetaObject *)((int)Gap::Core::igIGBFile::getClassMeta())) != 0) {
            l = (::igTDataList< ::igObject *> *)_directoryList.p;
            o = *(::igObject **)((char *)l->_data + off);
            ::igObject::release(o);
            List_RemoveWordAt((::igDataList *)l, i);
            *(::igObject **)((char *)l->_data + l->_count * 4) = 0;
        }
    }
}

igResource *igResource::getGlobalResource() {
    return g_objectSystem->resource;
}

/* Returns the `wanted`th info object (counting from 0) of the kind named `metaName` in the resource's
 * directory `name`, or 0. */
igInfo *igResource::getInfoByType(const char *name, const char *metaName, int wanted) {
    igSmartPointer<igDirectory> directory = getDirectory(name);
    igSmartPointer< ::igObject> meta((::igObject *)igObjectSystem_FindMetaByNameDefault(metaName), kRetainReference);
    int found;
    unsigned int i;
    if (directory.get() == 0 || meta.get() == 0) {
        return 0;
    }
    found = 0;
    for (i = 0; i < (unsigned int)directory->getInfoCount(); i++) {
        if (directory->getInfo(i)->isOfType((igMetaObject *)meta.get()) != 0) {
            if (found++ == wanted) {
                return directory->getInfo(i);
            }
        }
    }
    return 0;
}
}
}

static inline igObjectDirEntryView *AsObjectDirEntry(void *p) {
    if (p != 0 && ((Gap::Core::igObject *)p)->isOfType((igMetaObject *)Gap::Core::igObjectDirEntry::getClassMeta()) != 0) { return (igObjectDirEntryView *)p; }
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
                entry = AsObjectDirEntry(((Gap::Core::igDirectory *)directory)->get(i));
                if (entry != 0 && ((Gap::Core::igObject *)entry->_ref)->isOfType(fromMeta) != 0) {
                    if (toMeta == 0) return;
                    igSmartPointer<igObject> source((igObject *)entry->_ref, kRetainReference);
                    igSmartPointer<igObject> target((igObject *)igMetaObject_CreateInstanceDefault(toMeta), kRetainReference);
                    {
                        /* drop the reference the creation returned */
                        igObject *created = target.p;
                        created->release();
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
                    igDirectory_ReplaceReference((Gap::Core::igDirectory *)directory, igSmartPointer<igVirtualObject>(source), igSmartPointer<igVirtualObject>(target));
                    if (((Gap::Core::igObject *)target.p)->isOfType((igMetaObject *)Gap::Core::igInfo::getClassMeta()) != 0) {
                        ((Gap::Core::igDirectory *)directory)->appendInfo((Gap::Core::igInfo *)target.p);
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
            root = ((void *)((Gap::Core::igDirectory *)directory)->findObjectRefByEntryName((char const *)("root")));
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
                        u->release();
                    }
                    sceneGraphField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_sceneGraph"));
                    ((Gap::Core::igObjectRefMetaField *)sceneGraphField)->set((Gap::Core::igObject *)info, (Gap::Core::igObject *)root);
                    camerasField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_cameras"));
                    sceneGraphListField = AsObjectRefMetaField(igMetaObject_FindFieldByName(((igObjectDispatchView *)info)->GetMeta(), (const char *)"_sceneGraphList"));
                    sceneGraphList = AsObjectList(*(void **)((char *)info + sceneGraphListField->_offset));
                    if (sceneGraphList != 0) ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)sceneGraphList))->appendUnique((Gap::Core::igObject *)root);
                    ((Gap::Core::igObjectRefMetaField *)camerasField)->set((Gap::Core::igObject *)info, (Gap::Core::igObject *)0);
                    ((Gap::Core::igDirectory *)directory)->appendInfo((Gap::Core::igInfo *)info);
                    {
                        igObject *u = info;
                        igObject::release(u);
                    }
                }
            }
        }
    }
}

namespace Gap {
namespace Core {

/* With _autoCompatibility, brings directory `name` up to date: converts its igSceneWrapper objects
 * to igSceneInfo, wraps a bare root in one and marks the directory compatible. */
void igResource::makeCompatible(char const *name) {
    ::igDirectory *directory;
    if (_autoCompatibility != 0) {
        directory = (::igDirectory *)getDirectory((const char *)name).p;
        if (directory != 0) {
            igDirectory_ConvertObjectsOfType(directory, (const char *)"igSceneWrapper", (const char *)"igSceneInfo");
            igResource_WrapRootInSceneInfo((int)directory);
            directory->_compatibleState = 1;
        }
    }
}
}
}
