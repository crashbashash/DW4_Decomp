namespace Gap {
namespace Core {

void igDirectory::userRegister() {
    Gap::Core::igDirEntry::getClassTypeSafe();
    Gap::Core::igObjectDirEntry::getClassTypeSafe();
    Gap::Core::igMemoryDirEntry::getClassTypeSafe();
    Gap::Core::igExternalDirEntry::getClassTypeSafe();
    Gap::Core::igExternalIndexedEntry::getClassTypeSafe();
    Gap::Core::igExternalInfoEntry::getClassTypeSafe();
    igInfo_GetMetaObject();
    igResource_GetMetaObject();
}

void igDirectory::releaseDefaults() {
    igResult destroyed;
    int infoCount;
    int i;
    igInfoView *info;

    if (_managingResource != 0) {
        for (i = 0; i < _externalDirectoryList->_count; i++) {
            igResource_UnloadDirectory((igResource *)_managingResource, _externalDirectoryList->get(i)->_name.p);
        }
    }
    infoCount = getInfoCount();
    for (i = 0; i < infoCount; i++) {
        info = (igInfoView *)getInfo(i);
        if (info->_directory == (int)this) {
            info->_directory = 0;
        }
    }
    igObject::releaseDefaults();
    if (_loadingSemaphore != 0 && ((igSemaphoreView *)_loadingSemaphore.p)->IsCreated() != 0) {
        destroyed = ((igSemaphoreView *)_loadingSemaphore.p)->Destroy();
    }
}

igDirEntry *igDirectory::fastFindRefEntry(void *ref) const {
    igPointerList *refs = _refList;
    int lo, hi, mid, idx, n;
    void *value;
    if (refs != 0) {
        n = refs->_count;
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            value = refs->get(mid);
            if (value < ref) {
                lo = mid + 1;
            } else if (ref < value) {
                hi = mid - 1;
            } else {
                idx = mid;
                goto found;
            }
        }
        if (n == 0) {
            idx = -1;
        } else {
            value = refs->get(lo);
            if (ref < value || value < ref) {
                idx = -1;
            } else {
                idx = lo;
            }
        }
found:
        value = refs->get(idx);
        if (value == ref) {
            return get(idx);
        }
        return 0;
    }
    return (igDirEntry *)sortedSearch((igRefMetaField *)igDirEntry::k_ref, ref);
}
}
}

void *igDirectory_GetEntryAlias(int *directory, int index)
{
    return ((Gap::Core::igDirectory *)directory)->get(index);
}

namespace Gap {
namespace Core {

void *igDirectory::getRef(int index) const {
    igPointerList *refs;

    refs = _refList;
    if (refs != 0) {
        return refs->get(index);
    }
    return getNonShared(index)->getRef();
}

void igDirectory::setRef(int index, void *ref) {
    if (_refList != 0 && _uniqueEntryList != 0) {
        igDirEntry *entry = getNonShared(index);
        entry->setRef(ref);
        entry->refRef(ref);
        _refList->set(index, ref);
    } else {
        getNonShared(index)->setRef(ref);
    }
}

igDirEntry *igDirectory::get(int index) const {
    if (_refList != 0) {
        igDirEntry *entry = getNonShared(index);
        entry->setRef(getRef(index));
        entry->_index = index;
        return entry;
    }
    return getNonShared(index);
}
}
}

static inline igObjectDirEntry *castBinding(igObjectDirEntry *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType((igMetaObject *)Gap::Core::igObjectDirEntry::getClassMeta()) != 0) {
        return o;
    }
    return 0;
}

static inline igObjectRefMetaField *castRefField(igObjectRefMetaField *o) {
    if (o != 0 && ((Gap::Core::igObject *)o)->isOfType((igMetaObject *)(((int)Gap::Core::igObjectRefMetaField::getClassMeta()))) != 0) {
        return o;
    }
    return 0;
}

/* Points every reference to `field`'s object (directory slots and the object-reference fields of
 * the directory's objects) at `value`'s; returns the number replaced. */
int igDirectory_ReplaceReference(Gap::Core::igDirectory *self, const igSmartPointer<igVirtualObject> &field, const igSmartPointer<igVirtualObject> &value) {
    int changed = 0;
    int i;
    int j;
    int n;
    igObjectDispatchView *current;
    igObjectDirEntry *item;
    for (i = 0; i < self->_count; i++) {
        current = ((igObjectDispatchView *)field.p);
        if ((igObjectDispatchView *)self->getRef(i) == current) {
            if (self->_refList != 0) {
                void *ref;
                igVirtualObject::release(field.p);
                igVirtualObject::ref(value.p);
                ref = value.p;
                self->_refList->set(i, ref);
            } else {
                self->getNonShared(i)->setRef((void *)value.p);
            }
            changed++;
        }
        item = castBinding((igObjectDirEntry *)self->get(i));
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
                        ((Gap::Core::igObjectRefMetaField *)f)->set((Gap::Core::igObject *)(source.get()), (Gap::Core::igObject *)((igObjectDispatchView *)value.p));
                        changed++;
                    }
                }
            }
        }
    }
    return changed;
}

namespace Gap {
namespace Core {

void igDirectory::removeInfo(const char *infoName) {
    removeInfo((igInfo *)((igObjectList *)_infoList.p)->search((igStringMetaField *)igNamedObject::k_name, infoName));
}

void igDirectory::removeInfo(igInfo *info) {
    int idx;
    ::igTDataList< ::igObject *> *f;
    f = (::igTDataList< ::igObject *> *)_infoList.p;
    idx = f->find((::igObject *)info);
    if (-1 < idx) {
        objectListRemoveRetained((::igTDataList< ::igObject *> *)_infoList.p, idx);
    }
}

void igDirectory::appendInfo(igInfo *info) {
    ((igObjectList *)_infoList.p)->append((igObject *)info);
    info->_directory = (int)this;
}

igInfo *igDirectory::getInfo(const char *infoName) {
    return (igInfo *)((igObjectList *)_infoList.p)->search((igStringMetaField *)igNamedObject::k_name, infoName);
}

/* The lower bound is spelled `index <= -1` so it fuses into slti at. */
igInfo *igDirectory::getInfo(int index) {
    ::igTDataList<igInfo *> *infos;
    if (!(index <= -1)) {
        infos = (::igTDataList<igInfo *> *)_infoList.p;
        if (index < infos->_count) {
            return infos->_data[index];
        }
    }
    return 0;
}

bool igDirectory::attemptResolve(igDirectory *parentDir, void *ref) {
    int i;
    igInfoView *info;

    for (i = 0; i < ((::igTDataList<igInfoView *> *)_infoList.p)->_count; i++) {
        info = ((::igTDataList<igInfoView *> *)_infoList.p)->_data[i];
        if (info->_resolveState == 1 && (info->FindObjectReference(parentDir, ref) & 0xFF) == 1) {
            return 1;
        }
    }
    return 0;
}

bool igDirectory::contains(void *ref) {
    igSmartPointer<igDirEntry> h(fastFindRefEntry(ref), kRetainReference);
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}
}
}

int igDirectory_AddObjectCallback(int object, igMetaFieldView *field, Gap::Core::igDirectory *directory) {
    int i;
    int n;
    if (object == 0) {
        return 1;
    }
    if (field != 0) {
        return field->Write(object, (int)directory) == -1;
    }
    if (directory->contains((void *)object) == 1) {
        return 1;
    }
    n = directory->_externalDirectoryList->_count;
    for (i = 0; i < n; i++) {
        if (directory->_externalDirectoryList->get(i)->attemptResolve(directory, (void *)object) == 1) {
            return 1;
        }
    }
    directory->addObjectRef((Gap::Core::igObject *)object, 0, 0);
    return 0;
}

namespace Gap {
namespace Core {

int igDirectory::addObject(igObject *obj, const char *name, int resolveMethod) {
    int index;

    if (obj != 0) {
        obj->traverseFields((int (*)(void *, void *, void *))&igDirectory_AddObjectCallback, (void *)this);
        index = binaryFind((igRefMetaField *)igDirEntry::k_ref, obj);
        get(index)->setName(name);
        return index;
    }
    return -1;
}

int igDirectory::binaryFind(const igRefMetaField *field, const void *key) const {
    int n;
    int lo;
    int hi;
    int mid;
    const void *value;
    if (field == 0) return -1;
    n = _count;
    hi = n - 1;
    if (n <= 0) return 0;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        value = *(const void **)((char *)get(mid) + field->_offset);
        if (value < key) {
            lo = mid + 1;
        } else if (key < value) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    value = *(const void **)((char *)get(lo) + field->_offset);
    if (value < key) lo++;
    return lo;
}

int igDirectory::addObjectRef(igObject *obj, const char *name, int resolveMethod) {
    int index = 0;
    igMetaObject *info;
    void *pool;
    int mode;
    if (obj == 0) {
        return -1;
    }
    if (_count > 0) {
        index = binaryFind((igRefMetaField *)igDirEntry::k_ref, obj);
        if (_count > index && (igObject *)getRef(index) == obj) {
            return -1;
        }
    }
    if (obj != 0) {
        obj->trimCapacity();
        if (isOfType((igMetaObject *)(((int)g_igIGBFile_metaObject))) != 0) {
            if (_autoWriteFilePreProcessState == 1) {
                obj->userWriteFilePreProcess();
            }
            {
                igMetaObject *m = obj->getMeta();
                int (*fn)() = (int (*)())m->_writeProxy;
                if (fn != 0) {
                    _concreteState = 0;
                    obj->userApplyWriteProxy(fn());
                }
            }
        }
    }
    igSmartPointer<igObjectDirEntry> record(igObjectDirEntry::_instantiateFromPool(getMemoryPool()));
    record->_index = index;
    insertObject((::igDataList *)this, index, record.get());
    if (name != 0) {
        record->setName(name);
    }
    record->_resolveMethod = resolveMethod;
    record->_refType = 0;
    record->setRef(obj);
    if (_useMemoryPoolAssignmentsState != 0) {
        info = obj->getMeta();
        pool = 0;
        if (_forceWriteMemoryPoolInfoFromMetaState != 0 && info != 0 && ((char *)igMetaObject_GetPoolName((int *)info)) != 0) {
            pool = Memory_GetAllocatorByName((char *)igMetaObject_GetPoolName((int *)info));
        }
        if (pool == 0) {
            pool = ((void *)obj->getMemoryPool());
        }
        if (pool != 0) {
            mode = ((MemoryContext *)Memory_GetCurrentContextAlias())->IndexOfAllocator(pool);
            if (mode == 1 || mode == 2) {
                mode = -1;
            }
            record->setMemoryPoolHandle(mode);
        }
    }
    if (obj != 0) {
        record->setTypeMeta(obj->getMeta());
    }
    return index;
}

int igDirectory::addMemoryRef(igMemoryRefMetaField *containingMetaField, void *mem, igMetaField *memType, int alignmentIndex, const char *name, int resolveMethod, unsigned char doRefOnRead) {
    int index;
    void *pool;
    int poolIndex;
    if (mem == 0) return -1;
    index = 0;
    if (_count > 0) {
        index = binaryFind((igRefMetaField *)igDirEntry::k_ref, mem);
        if (index < _count) { void *r = getRef(index); if (r == mem) return -1; }
    }
    if (memType == 0) memType = igCharMetaField::getMetaField();
    igSmartPointer<igMemoryDirEntry> record(igMemoryDirEntry::_instantiateFromPool(getMemoryPool()));
    record->_index = index;
    insertObject((::igDataList *)this, index, record.get());
    if (name) record->setName(name);
    record->_resolveMethod = resolveMethod;
    record->_refType = 1;
    record->setMemType(memType);
    int size = ((int)Memory_GetBufferSize(mem));
    record->_memSize = size;
    record->_alignmentTypeIndex = alignmentIndex;
    record->setRef(mem);
    record->_refCounted = doRefOnRead;
    if (_useMemoryPoolAssignmentsState) {
        pool = 0;
        if (_forceWriteMemoryPoolInfoFromMetaState && containingMetaField && containingMetaField->getPool()) pool = Memory_GetAllocatorByName(containingMetaField->getPool());
        if (pool == 0) pool = Memory_FindOwningAllocator((int)mem);
        if (pool) {
            poolIndex = ((MemoryContext *)Memory_GetCurrentContextAlias())->IndexOfAllocator(pool);
            if (poolIndex == 1 || poolIndex == 2) poolIndex = -1;
            record->setMemoryPoolHandle(poolIndex);
        }
    }
    return record->_index;
}

int igDirectory::addRawRef(void *raw, const char *name, int resolveMethod) {
    int idx, cnt;
    if (raw == 0) {
        return -1;
    }
    idx = binaryFind((igRefMetaField *)igDirEntry::k_ref, raw);
    cnt = _count;
    if (cnt > 0) {
        if (idx < cnt) {
            void *f = getRef(idx);
            if (f == raw) return -1;
        }
    }
    igSmartPointer<igDirEntry> entry(igDirEntry::_instantiateFromPool(getMemoryPool()));
    entry->setName(name);
    entry->_resolveMethod = resolveMethod;
    entry->_refType = 2;
    entry->setRef(raw);
    entry->_index = idx;
    insertObject((::igDataList *)this, idx, entry.get());
    return entry->_index;
}
}
}
