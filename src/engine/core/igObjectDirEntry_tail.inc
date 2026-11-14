/* Drop the entry's object reference: the _ref setter retains the new value and releases the old one,
 * so calling it with 0 releases the held object; the igObject default then runs. */
void igObjectDirEntry_ReleaseDefaults(igObjectDirEntry *self) {
    ((igDirEntryView *)self)->SetRef(0);
    igObject_ReleaseDefaults((int)self);
}

static inline const char *entryNameOf(const igObjectDirEntry *entry) {
    return entry->_name != 0 ? (const char *)entry->_name : ((char *)emptyString);
}

static inline igObjectList *asObjectEntryList(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, (igMetaObject *)g_igObjectList_metaObject[0]) != 0) return (igObjectList *)object;
    return 0;
}

igObjectDirEntry *igObjectDirEntry_GetSharedEntry(igObjectDirEntry *self, igIGBFile *file) {
    igSmartPointer<igObjectList> lists((igObjectList *)file->_entryPool, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((igObjectDispatchView *)self)->GetMeta()->_index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained((igTDataList<igObject *> *)lists.p, index + 1);
        objectListSetRetained(index, 0, lists.p);
    }
    igSmartPointer<igObjectList> entries(asObjectEntryList(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->_temporaryMemoryPool;
        entries.release();
        entries.p = ((igObjectList *)igObjectList_Create(pool));
        objectListSetRetained(index, entries.p, lists.p);
    }
    int i;
    igObjectList *list;
    igObjectDirEntry *entry;
    int count;
    count = entries->_count;
    self->_index = -1;
    list = entries.p;
    for (i = 0; i < count; i++) {
        entry = ((igObjectDirEntry **)list->_data)[i];
        if (entry->_typeMeta == self->_typeMeta && entryNameOf(entry) == entryNameOf(self) &&
            entry->_memoryPoolHandle == self->_memoryPoolHandle) {
            return objectDirEntryAt(list, i);
        }
    }
    ObjectList_AppendRetained((igObjectList *)list, (igObject *)self);
    return self;
}

int igObjectDirEntry_GetMeta(void) {
    return ((int *)g_igObjectDirEntry_metaObject)[0];
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
void igObjectDirEntry_RetainSharedRef(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
void igObjectDirEntry_ReleaseSharedRef(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

void igObjectDirEntry_SetTypeMeta(igObjectDirEntry *self, igMetaObject *meta) {
    char *interned;
    (igSmartPointer<igMetaObject> &)self->_typeMeta = meta;
    if (meta) {
        char *name = (char *)meta->_name;
        StringPool *pool = InternedStrings::get();
        interned = ((char *)StringPool_Intern(pool, (const char *)name));
        releaseString((const char *)self->_typeMetaName);
        self->_typeMetaName = (int)interned;
    } else {
        StringPool *pool = InternedStrings::get();
        interned = ((char *)StringPool_Intern(pool, (const char *)text_NoMeta));
        releaseString((const char *)self->_typeMetaName);
        self->_typeMetaName = (int)interned;
    }
}

/* slot 23 of igObjectDirEntry: set the _ref reference (+24; reflected as a raw ref, but the code
 * treats it as a counted igObject). Reference-counted assignment: retain the new object, release
 * the old one (destroying it when its 23-bit count reaches zero), then store the new one. */
void igObjectDirEntry_SetRef(igObjectDirEntry *self, igObject *object) {
    igObject *previousObject;
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
    previousObject = (igObject *)(self->_ref);
    if (previousObject != 0) {
        previousObject->_refCount = previousObject->_refCount - 1;
        if ((previousObject->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousObject);
        }
    }
    self->_ref = (int)object;
}

/* Write the referenced object's persistent fields at the file's object cursor and move past them. */
void igObjectDirEntry_WriteObject(igObjectDirEntry *self, igIGBFileView *file) {
    int cursor = file->ObjectCursor();
    file->SetObjectCursor(cursor + igObject_WritePersistentFields((igObjectDispatchView *)self->_ref, (int *)cursor, (igIGBFile *)file,
                                                                  (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap));
}

void igObjectDirEntry_PrepareWrite(igObjectDirEntryView *self) {
    igObjectDispatchView *object = (igObjectDispatchView *)self->_ref;
    if (object != 0) {
        int (*writeProxy)() = (int (*)())object->GetMeta()->_writeProxy;
        if (writeProxy != 0) {
            igObjectDirEntry_SetTypeMeta((igObjectDirEntry *)self, (igMetaObject *)writeProxy());
        }
    }
}

void igObjectDirEntry_ComputeWriteSize(igObjectDirEntryView *self, igIGBFile *file) {
    int bufferSize;
    void *(*writeProxy)();
    igObjectDispatchView *object;
    void *meta;

    object = (igObjectDispatchView *)self->_ref;
    igMetaObject *objectMeta = object->GetMeta();
    meta = objectMeta;
    writeProxy = (void *(*)())objectMeta->_writeProxy;
    if (writeProxy != 0) {
        meta = writeProxy();
    }
    self->_typeMetaIndex = igMetaObject_AddToMetaObjectList((igTDataList<igMetaObject *> *)file->_metaObjectListInFile, (igMetaObject *)meta);
    bufferSize = file->_objectBufferSize;
    file->_objectBufferSize = bufferSize + igObject_GetSerializedSize((igObjectDispatchView *)object);
    file->_objectCount = file->_objectCount + 1;
}

void igObjectDirEntry_RegisterRef(igObjectDirEntry *self, int withMeta) {
    int ref;

    ref = self->_ref;
    if (ref != 0) {
        if (withMeta != 0) {
            igObject_RegisterInstance((void **)ref, (void *)self->_typeMeta);
            return;
        }
        igObject_RegisterInstance((void **)ref, (void *)0);
    }
}

void igObjectDirEntry_PostProcess(igObjectDirEntryView *self)
{
    ((igObjectDispatchView *)self->_ref)->userPostLoad();
}

/* Read the referenced object's fields from the file's object cursor and move past them. */
void igObjectDirEntry_ResolveRefOld(igObjectDirEntry *self, igIGBFileView *file) {
    igObjectDispatchView *object = (igObjectDispatchView *)self->_ref;
    int read = igObject_ReadFields(object, (FieldRecordHead *)file->ObjectCursor(), (igIGBFile *)file,
                            (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
    int cursor = file->ObjectCursor();
    file->SetObjectCursor(cursor + read);
}

/* Resolve the referenced object's references to other entries the same way, from the object cursor. */
void igObjectDirEntry_ResolveRef(igObjectDirEntry *self, igIGBFileView *file) {
    igObjectDispatchView *object = (igObjectDispatchView *)self->_ref;
    int read = igObject_ReadPersistentFields(object, (FieldRecordHead *)file->ObjectCursor(), (igDirectoryView *)file,
                            (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
    int cursor = file->ObjectCursor();
    file->SetObjectCursor(cursor + read);
}

static inline void addRef(igObject *o) { if (o != 0) { o->_refCount = (int)o->_refCount + 1; } }

static inline void dropRef(igObject *o) {
    o->_refCount = (int)o->_refCount - 1;
    if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
}

static inline void setMeta(igObjectDirEntryView *self, igMetaObject *m) {
    igMetaObject *old;
    addRef(m);
    old = self->_typeMeta;
    if (old != 0) { dropRef(old); }
    self->_typeMeta = m;
}

void igObjectDirEntry_CreateObject(igObjectDirEntryView *self, igIGBFileView *file) {
    int index;
    igObject *obj;
    int pool;
    int sel;
    index = self->_typeMetaIndex;
    if (index == -1) {
        setMeta(self, ((igMetaObject *)igObjectSystem_FindMetaByNameDefault((const char *)self->_typeMetaName)));
    } else {
        setMeta(self, ((igMetaObject **)file->_metaObjectListInFile->_data)[index]);
    }
    if (self->_typeMeta != 0) {
        sel = self->_memoryPoolHandle;
        if (sel == -1 || sel == 1 || sel == 2) {
            pool = (int)file->_objectMemoryPool;
        } else {
            pool = ((int)Memory_GetAllocatorBySelector(sel));
            if (pool == 0) {
                pool = (int)file->_objectMemoryPool;
            }
        }
        obj = ((igObject *)igMetaObject_CreateInstanceWithPool(self->_typeMeta, (igMemoryPoolView *)pool));
        if (obj == 0) {
            file->_hasCriticalFailure = 1;
            igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, (int)0);
            return;
        }
        igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, (int)obj);
        dropRef(obj);
    } else {
        igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, (int)0);
    }
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
void igObjectDirEntry_RetainRef(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
void igObjectDirEntry_ReleaseRef(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

/* igObjectDirEntry vtable slot 29: setter for `_memoryPoolHandle` (+44), the pool handle field of
 * the directory entry. Slot 30 is the matching getter; igMemoryDirEntry has the same pair. */
void igObjectDirEntry_SetMemoryPoolHandle(igObjectDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}

/* IgObjectDirEntry vtable slot 30, a plain getter that returns the reflected field
 * _memoryPoolHandle (+44). */
int igObjectDirEntry_GetMemoryPoolHandle(igObjectDirEntry *self) {
    return self->_memoryPoolHandle;
}

void ObjectList_FillRetained(igTDataList<igObject *> *list, igObject *object) {
    int n;
    int i;
    int j;
    int cnt;
    igObject **data;
    int k;
    igObject *t;
    n = list->_count;
    if (object != 0) {
        for (i = 0; i < n; i++) {
            object->_refCount = object->_refCount + 1;
        }
    }
    for (j = 0; j < n; j++) {
        t = list->_data[j];
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    cnt = list->_count;
    data = list->_data;
    for (k = 0; k < cnt; k++) {
        data[k] = object;
    }
}

void ObjectList_ClearRetainedPreserveCount(igTDataList<igObject *> *list, int unused) {
    int n;
    int i;
    igObject *o;

    n = list->_count;
    for (i = 0; i < n; i++) {
        o = list->_data[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (list->_count != 0) {
        memset(list->_data, 0, list->_count * 4);
    }
}

