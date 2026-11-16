void igDirectory_RegisterDependentMetaObjects(void) {
    igDirEntry_GetMetaObject();
    igObjectDirEntry_GetMetaObject();
    igMemoryDirEntry_GetMetaObject();
    igExternalDirEntry_GetMetaObject();
    igExternalIndexedEntry_GetMetaObject();
    igExternalInfoEntry_GetMetaObject();
    igInfo_GetMetaObject();
    igResource_GetMetaObject();
}

void igDirectory_ReleaseDefaults(igDirectoryView *self) {
    igResult destroyed;
    int infoCount;
    int i;
    igInfoView *info;

    if (self->_managingResource != 0) {
        for (i = 0; i < self->_externalDirectoryList->_count; i++) {
            igResource_UnloadDirectory(self->_managingResource, self->_externalDirectoryList->_data[i]->_name);
        }
    }
    infoCount = igDirectory_GetInfoCount(self);
    for (i = 0; i < infoCount; i++) {
        info = (igInfoView *)igDirectory_GetInfo(self, i);
        if (info->_directory == (int)self) {
            info->_directory = 0;
        }
    }
    igObject_ReleaseDefaults((igObject *)self);
    if (self->_loadingSemaphore != 0 && self->_loadingSemaphore->IsCreated() != 0) {
        destroyed = self->_loadingSemaphore->Destroy();
    }
}

int igDirectory_GetEntryByRef(igDirectoryView *self, unsigned key) {
    igTDataList<int> *refs = self->_refList;
    int lo, hi, mid, idx, n;
    unsigned value;
    int r;
    if (refs != 0) {
        n = refs->_count;
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            value = refs->_data[mid];
            if (value < key) {
                lo = mid + 1;
            } else if (key < value) {
                hi = mid - 1;
            } else {
                idx = mid;
                goto found;
            }
        }
        if (n == 0) {
            idx = -1;
        } else {
            value = refs->_data[lo];
            if (key < value || value < key) {
                idx = -1;
            } else {
                idx = lo;
            }
        }
found:
        value = refs->_data[idx];
        if (value == key) {
            return (int)igDirectory_GetEntry((int *)self, idx);
        }
        return 0;
    }
    return igProperty_FindBySortedKey((void *)self, (void *)g_igDirEntry_refField, (int)key);
}

void *igDirectory_GetEntryAlias(int *directory, int index)
{
    return igDirectory_GetEntry(directory, index);
}

int igDirectory_GetObject(void *directory, int index) {
    igTDataList<int> *refs;

    refs = ((igDirectoryView *)directory)->_refList;
    if (refs != 0) {
        return refs->_data[index];
    }
    return ((igDirectoryView *)directory)->_data[index]->_ref;
}

void igDirectory_SetEntryRef(igDirectoryView *self, int index, int ref) {
    if (self->_refList != 0 && self->_uniqueEntryList != 0) {
        igDirEntryView *entry = self->_data[index];
        entry->SetRef(ref);
        entry->RetainRef(ref);
        {
            igTDataList<int> *refs = self->_refList;
            if (refs->_count != 0 && index >= 0 && index < refs->_count) refs->_data[index] = ref;
        }
    } else {
        self->_data[index]->SetRef(ref);
    }
}

void *igDirectory_GetEntry(int *directory, int index) {
    if (((igDirectoryView *)directory)->_refList != 0) {
        igDirEntryView *entry = ((igDirectoryView *)directory)->_data[index];
        entry->SetRef(igDirectory_GetObject(directory, index));
        entry->_index = index;
        return entry;
    }
    return ((igDirectoryView *)directory)->_data[index];
}

static inline void releaseBound(igObjectDispatchView *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
}

static inline igObjectDirEntry *castBinding(igObjectDirEntry *o) {
    if (o != 0 && igObject_IsKindOf(o, (igMetaObject *)g_igObjectDirEntry_metaObject) != 0) {
        return o;
    }
    return 0;
}

static inline igObjectRefMetaField *castRefField(igObjectRefMetaField *o) {
    if (o != 0 && igObject_IsKindOf(o, (igMetaObject *)(((int)g_igObjectRefMetaField_metaObject))) != 0) {
        return o;
    }
    return 0;
}

static inline void setSlot(igTDataList<int> *l, int i, igObjectDispatchView *v) {
    if (l->_count != 0 && i >= 0 && i < l->_count) {
        l->_data[i] = (int)v;
    }
}

/* Points every reference to `field`'s object (directory slots and the object-reference fields of
 * the directory's objects) at `value`'s; returns the number replaced. */
int igDirectory_ReplaceReference(igDirectoryView *self, const igSmartPointer<igVirtualObject> &field, const igSmartPointer<igVirtualObject> &value) {
    int changed = 0;
    int i;
    int j;
    int n;
    igObjectDispatchView *current;
    igObjectDirEntry *item;
    for (i = 0; i < self->_count; i++) {
        current = ((igObjectDispatchView *)field.p);
        if ((igObjectDispatchView *)igDirectory_GetObject(self, i) == (igObjectDispatchView *)current) {
            if (self->_refList != 0) {
                releaseBound(((igObjectDispatchView *)field.p));
                if (((igObjectDispatchView *)value.p) != 0) {
                    ((igObjectDispatchView *)value.p)->_refCount = ((igObjectDispatchView *)value.p)->_refCount + 1;
                }
                setSlot(self->_refList, i, ((igObjectDispatchView *)value.p));
            } else {
                self->_data[i]->SetRef((int)((igObjectDispatchView *)value.p));
            }
            changed++;
        }
        item = castBinding((igObjectDirEntry *)igDirectory_GetEntry((int *)self, i));
        if (item != 0) {
            igSmartPointer<igVirtualObject> source((igVirtualObject *)item->_ref, kRetainReference);
            if (source.get() == 0) {
                continue;
            }
            n = igMetaObject_GetFieldCount(((igObjectDispatchView *)source.get())->GetMeta());
            for (j = 0; j < n; j++) {
                igObjectRefMetaField *f;
                f = castRefField(((igObjectRefMetaField *)igMetaObject_GetFieldAt(((igObjectDispatchView *)source.get())->GetMeta(), j)));
                if (f != 0) {
                    if (*(igObjectDispatchView **)((char *)source.get() + f->_offset) == ((igObjectDispatchView *)field.p)) {
                        igObjectRefMetaField_Assign(f, (void *)(source.get()), (igObject *)((igObjectDispatchView *)value.p));
                        changed++;
                    }
                }
            }
        }
    }
    return changed;
}

void igDirectory_RemoveInfoByName(void *directory, int name) {
    igDirectory_RemoveInfo((igDirectoryView *)directory, (igObject *)((void *)igProperty_FindByName((igObjectList *)((igDirectoryView *)directory)->_infoList, g_propertyNameField, name)));
}

void igDirectory_RemoveInfo(igDirectoryView *h, igObject *object) {
    int idx;
    igTDataList<igObject *> *f;
    f = (igTDataList<igObject *> *)h->_infoList;
    idx = f->find(object);
    if (-1 < idx) {
        objectListRemoveRetained((igTDataList<igObject *> *)h->_infoList, idx);
    }
}

void igDirectory_AddInfo(void *directory, void *info) {
    ObjectList_AppendRetained((igObjectList *)((igDirectoryView *)directory)->_infoList, (igObject *)info);
    ((igInfoView *)info)->_directory = (int)directory;
}

void * igDirectory_FindInfoByName(int *directory, int name) {
    return ((void *)igProperty_FindByName((igObjectList *)((igDirectoryView *)directory)->_infoList, (igMetaField *)g_propertyNameField, name));
}

/* The lower bound is spelled `arg1 <= -1` so it fuses into slti at. */
int igDirectory_GetInfo(void *directory, int index) {
    igTDataList<igInfoView *> *infos;
    if (!(index <= -1)) {
        infos = ((igDirectoryView *)directory)->_infoList;
        if (index < infos->_count) {
            return (int)infos->_data[index];
        }
    }
    return 0;
}

int igDirectory_FindObjectReferenceInInfos(igDirectoryView *self, int directory, int object) {
    int i;
    igInfoView *info;

    for (i = 0; i < self->_infoList->_count; i++) {
        info = self->_infoList->_data[i];
        if (info->_resolveState == 1 && (info->FindObjectReference(directory, object) & 0xFF) == 1) {
            return 1;
        }
    }
    return 0;
}

int igDirectory_HasEntry(void *dir, unsigned key) {
    igSmartPointer<igDirEntry> h((igDirEntry *)igDirectory_GetEntryByRef((igDirectoryView *)dir, key), kRetainReference);
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}

int igDirectory_AddObjectCallback(int object, igMetaFieldView *field, igDirectoryView *directory) {
    int i;
    int n;
    if (object == 0) {
        return 1;
    }
    if (field != 0) {
        return field->Write(object, (int)directory) == -1;
    }
    if ((igDirectory_HasEntry(directory, object) & 0xFF) == 1) {
        return 1;
    }
    n = directory->_externalDirectoryList->_count;
    for (i = 0; i < n; i++) {
        if ((igDirectory_FindObjectReferenceInInfos(directory->_externalDirectoryList->_data[i], (int)directory, object) & 0xFF) == 1) {
            return 1;
        }
    }
    igDirectory_InsertObject(directory, (igObjectDispatchView *)object, 0, 0);
    return 0;
}

int igDirectory_AddObjectRecursive(int directory, int object, int name, int extra3) {
    int index;

    if (object != 0) {
        igObject_VisitFields((igObjectDispatchView *)object, (int (*)(void *, void *, void *))&igDirectory_AddObjectCallback, (void *)directory);
        index = igDirectory_FindSortedInsertIndex((igDirectoryView *)directory, (igMetaField *)g_igDirEntry_refField, object);
        igNamedObject_SetName((igNamedObject *)(igDirectory_GetEntry((int *)directory, index)), name);
        return index;
    }
    return -1;
}

int igDirectory_FindSortedInsertIndex(igDirectoryView *self, igMetaField *field, unsigned key) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned value;
    if (field == 0) return -1;
    n = self->_count;
    hi = n - 1;
    if (n <= 0) return 0;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        value = *(unsigned *)((char *)igDirectory_GetEntry((int *)self, mid) + field->_offset);
        if (value < key) {
            lo = mid + 1;
        } else if (key < value) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    value = *(unsigned *)((char *)igDirectory_GetEntry((int *)self, lo) + field->_offset);
    if (value < key) lo++;
    return lo;
}

int igDirectory_InsertObject(igDirectoryView *self, igObjectDispatchView *obj, char *name, int resolveMethod) {
    int index = 0;
    igMetaObject *info;
    void *pool;
    int mode;
    if (obj == 0) {
        return -1;
    }
    if (self->_count > 0) {
        index = igDirectory_FindSortedInsertIndex(self, (igMetaField *)g_igDirEntry_refField, (unsigned)obj);
        if (self->_count > index && (igObjectDispatchView *)igDirectory_GetObject(self, index) == obj) {
            return -1;
        }
    }
    if (obj != 0) {
        obj->TrimCapacity();
        if (igObject_IsKindOf(self, (igMetaObject *)(((int)g_igIGBFile_metaObject))) != 0) {
            if (self->_autoWriteFilePreProcessState == 1) {
                obj->userWriteFilePreProcess();
            }
            {
                igMetaObject *m = obj->GetMeta();
                int (*fn)() = (int (*)())m->_writeProxy;
                if (fn != 0) {
                    self->_concreteState = 0;
                    obj->userApplyWriteProxy(fn());
                }
            }
        }
    }
    igSmartPointer<igDirEntryView> record(((igDirEntryView *)igObjectDirEntry_Create((int)(((void *)igObject_GetAllocator((igObject *)self))))));
    record.get()->_index = index;
    insertObject((igDataList *)self, index, record.get());
    if (name != 0) {
        igNamedObject_SetName((igNamedObject *)(record.get()), (int)name);
    }
    record.get()->_resolveMethod = resolveMethod;
    record.get()->_refType = 0;
    record.get()->SetRef((int)obj);
    if (self->_useMemoryPoolAssignmentsState != 0) {
        info = obj->GetMeta();
        pool = 0;
        if (self->_forceWriteMemoryPoolInfoFromMetaState != 0 && info != 0 && ((char *)igMetaObject_GetPoolName((int *)info)) != 0) {
            pool = Memory_GetAllocatorByName((int)(((char *)igMetaObject_GetPoolName((int *)info))));
        }
        if (pool == 0) {
            pool = ((void *)igObject_GetAllocator((igObject *)obj));
        }
        if (pool != 0) {
            mode = ((MemoryContext *)Memory_GetCurrentContextAlias())->IndexOfAllocator(pool);
            if (mode == 1 || mode == 2) {
                mode = -1;
            }
            record.get()->SetMemoryPool(mode);
        }
    }
    if (obj != 0) {
        igObjectDirEntry_SetTypeMeta((igObjectDirEntry *)(record.get()), obj->GetMeta());
    }
    return index;
}

int igDirectory_AddMemoryRef(igDirectoryView *self, int field, int memory, int memType, int alignmentTypeIndex, int name, int resolveMethod, unsigned char refCounted) {
    int index;
    int pool;
    int poolIndex;
    if (memory == 0) return -1;
    index = 0;
    if (self->_count > 0) {
        index = igDirectory_FindSortedInsertIndex(self, (igMetaField *)g_igDirEntry_refField, memory);
        if (index < self->_count) { int r = igDirectory_GetObject(self, index); if (r == memory) return -1; }
    }
    if (memType == 0) memType = igCharMetaField_GetDefaultDescriptor();
    igSmartPointer<igMemoryDirEntryView> record(((igMemoryDirEntryView *)igMemoryDirEntry_Create((int)igObject_GetAllocator((igObject *)self))));
    record.get()->_index = index;
    insertObject((igDataList *)self, index, record.get());
    if (name) igNamedObject_SetName((igNamedObject *)(record.get()), name);
    record.get()->_resolveMethod = resolveMethod;
    record.get()->_refType = 1;
    igMemoryDirEntry_SetMemType((igMemoryDirEntry *)(record.get()), (igObjectDispatchView *)memType);
    int size = ((int)Memory_GetBufferSize((void *)memory));
    record.get()->_memSize = size;
    record.get()->_alignmentTypeIndex = alignmentTypeIndex;
    record.get()->SetRef(memory);
    record.get()->_refCounted = refCounted;
    if (self->_useMemoryPoolAssignmentsState) {
        pool = 0;
        if (self->_forceWriteMemoryPoolInfoFromMetaState && field && igMemoryRefMetaField_GetPoolName((igMemoryRefMetaField *)field)) pool = (int)Memory_GetAllocatorByName(igMemoryRefMetaField_GetPoolName((igMemoryRefMetaField *)field));
        if (pool == 0) pool = (int)Memory_FindOwningAllocator(memory);
        if (pool) {
            poolIndex = ((MemoryContext *)Memory_GetCurrentContextAlias())->IndexOfAllocator((void *)pool);
            if (poolIndex == 1 || poolIndex == 2) poolIndex = -1;
            record.get()->SetMemoryPool(poolIndex);
        }
    }
    return record.get()->_index;
}

int igDirectory_AddRawRef(igDirectoryView *list, int key, int name, int val) {
    int idx, cnt;
    if (key == 0) {
        return -1;
    }
    idx = igDirectory_FindSortedInsertIndex(list, (igMetaField *)g_igDirEntry_refField, key);
    cnt = list->_count;
    if (cnt > 0) {
        if (idx < cnt) {
            int f = igDirectory_GetObject(list, idx);
            if (f == key) return -1;
        }
    }
    igSmartPointer<igDirEntryView> entry((igDirEntryView *)igDirEntry_Create((int)(((void *)igObject_GetAllocator((igObject *)list)))));
    igNamedObject_SetName((igNamedObject *)(entry.get()), name);
    entry.get()->_resolveMethod = val;
    entry.get()->_refType = 2;
    entry.get()->SetRef(key);
    entry.get()->_index = idx;
    insertObject((igDataList *)list, idx, entry.get());
    return entry.get()->_index;
}

