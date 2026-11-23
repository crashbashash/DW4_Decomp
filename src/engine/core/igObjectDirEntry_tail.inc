static inline const char *entryNameOf(const igObjectDirEntry *entry) {
    return entry->_name != 0 ? (const char *)entry->_name : ((char *)emptyString);
}

static inline igObjectList *asObjectEntryList(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)Gap::Core::igObjectList::getClassMeta()) != 0) return (igObjectList *)object;
    return 0;
}

namespace Gap {
namespace Core {

/* Drop the entry's object reference: the _ref setter retains the new value and releases the old one,
 * so calling it with 0 releases the held object; the igObject default then runs. */
void igObjectDirEntry::releaseDefaults() {
    setRef(0);
    igObject_ReleaseDefaults((::igObject *)this);
}

igDirEntry *igObjectDirEntry::share(igIGBFile *file) {
    igSmartPointer< ::igObjectList> lists((::igObjectList *)file->_entryPool.p, kRetainReference);
    if (lists.p == 0) return this;
    int index = ((igObjectDispatchView *)this)->GetMeta()->_index;
    if (lists->_count <= index) {
        ((igObjectList *)((::igTDataList< ::igObject *> *)lists.p))->setCount(index + 1);
        objectListSetRetained(index, 0, lists.p);
    }
    igSmartPointer< ::igObjectList> entries(asObjectEntryList(((::igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = (int)file->_temporaryMemoryPool.p;
        entries.release();
        entries.p = ((::igObjectList *)igObjectList::_instantiateFromPool((igMemoryPoolView *)pool));
        objectListSetRetained(index, entries.p, lists.p);
    }
    int i;
    ::igObjectList *list;
    igObjectDirEntry *entry;
    int count;
    count = entries->_count;
    _index = -1;
    list = entries.p;
    for (i = 0; i < count; i++) {
        entry = ((igObjectDirEntry **)list->_data)[i];
        if (entry->_typeMeta == _typeMeta && entryNameOf((::igObjectDirEntry *)entry) == entryNameOf((::igObjectDirEntry *)this) &&
            entry->_memoryPoolHandle == _memoryPoolHandle) {
            return (igObjectDirEntry *)objectDirEntryAt(list, i);
        }
    }
    ((igObjectList *)list)->append(this);
    return this;
}

/* Takes one more reference on `ref` (null-safe). */
void igObjectDirEntry::refEntry(void *ref) {
    igObject::ref((igObject *)ref);
}

/* Releases one reference to `ref`, destroying it when its count reaches zero. */
void igObjectDirEntry::releaseEntry(void *ref) {
    igObject::release((igObject *)ref);
}

void igObjectDirEntry::setTypeMeta(igMetaObject *meta) {
    _typeMeta = meta;
    if (meta) {
        _typeMetaName = (const char *)meta->_name;
    } else {
        _typeMetaName = "NoMeta";
    }
}

/* _ref is reflected as a raw ref, but an object entry counts the object it holds: retain the new one,
 * release the old one, then store the new one. */
void igObjectDirEntry::setRef(void *ref) {
    igObject *previousObject;
    igObject::ref((igObject *)ref);
    previousObject = (igObject *)_ref;
    igObject::release(previousObject);
    _ref = (int)ref;
}

/* Write the referenced object's persistent fields at the file's object cursor and move past them. */
void igObjectDirEntry::writeWrite(igIGBFile *igb) {
    char *cursor = (char *)igb->getObjectBufferPlace();
    igb->setObjectBufferPlace(cursor + igObject_WritePersistentFields((igObjectDispatchView *)_ref, (int *)cursor, igb,
                                                                      (::igTDataList<igMetaObject *> *)igb->_metaObjectListInFile.p, igb->_endianSwap));
}

void igObjectDirEntry::writeMakeProxy(igIGBFile *igb) {
    igObjectDispatchView *object = (igObjectDispatchView *)_ref;
    if (object != 0) {
        int (*writeProxy)() = (int (*)())object->GetMeta()->_writeProxy;
        if (writeProxy != 0) {
            setTypeMeta((igMetaObject *)writeProxy());
        }
    }
}

void igObjectDirEntry::writeComputeBufferSize(igIGBFile *file) {
    int bufferSize;
    void *(*writeProxy)();
    igObjectDispatchView *object;
    void *meta;

    object = (igObjectDispatchView *)_ref;
    igMetaObject *objectMeta = object->GetMeta();
    meta = objectMeta;
    writeProxy = (void *(*)())objectMeta->_writeProxy;
    if (writeProxy != 0) {
        meta = writeProxy();
    }
    _typeMetaIndex = igMetaObject_AddToMetaObjectList((::igTDataList<igMetaObject *> *)file->_metaObjectListInFile.p, (igMetaObject *)meta);
    bufferSize = file->_objectBufferSize;
    file->_objectBufferSize = bufferSize + ((igObject *)object)->getIoSize();
    file->_objectCount = file->_objectCount + 1;
}

void igObjectDirEntry::readFinishConstruction(bool doMakeConcrete) {
    int ref;

    ref = _ref;
    if (ref != 0) {
        if (doMakeConcrete) {
            igObject_RegisterInstance((void **)ref, (void *)_typeMeta.get());
            return;
        }
        igObject_RegisterInstance((void **)ref, (void *)0);
    }
}

void igObjectDirEntry::readPostRead(igIGBFile *igb)
{
    ((igObjectDispatchView *)_ref)->userPostLoad();
}

/* Read the referenced object's fields from the file's object cursor and move past them. */
void igObjectDirEntry::readReadVersion3(igIGBFile *igb) {
    igObjectDispatchView *object = (igObjectDispatchView *)_ref;
    int read = igObject_ReadFields(object, (FieldRecordHead *)igb->getObjectBufferPlace(), igb,
                            (::igTDataList<igMetaObject *> *)igb->_metaObjectListInFile.p, igb->_endianSwap);
    char *cursor = (char *)igb->getObjectBufferPlace();
    igb->setObjectBufferPlace(cursor + read);
}

/* Resolve the referenced object's references to other entries the same way, from the object cursor. */
void igObjectDirEntry::readRead(igIGBFile *igb) {
    igObjectDispatchView *object = (igObjectDispatchView *)_ref;
    int read = igObject_ReadPersistentFields(object, (FieldRecordHead *)igb->getObjectBufferPlace(), igb,
                            (::igTDataList<igMetaObject *> *)igb->_metaObjectListInFile.p, igb->_endianSwap);
    char *cursor = (char *)igb->getObjectBufferPlace();
    igb->setObjectBufferPlace(cursor + read);
}

void igObjectDirEntry::readSetup(igIGBFile *igb) {
    int index;
    igObject *obj;
    int pool;
    int sel;
    index = _typeMetaIndex;
    if (index == -1) {
        _typeMeta = (igMetaObject *)igObjectSystem_FindMetaByNameDefault(_typeMetaName.p);
    } else {
        _typeMeta = ((igMetaObject **)igb->_metaObjectListInFile->_data)[index];
    }
    if (_typeMeta != 0) {
        sel = _memoryPoolHandle;
        if (sel == -1 || sel == 1 || sel == 2) {
            pool = (int)igb->_objectMemoryPool.p;
        } else {
            pool = ((int)Memory_GetAllocatorBySelector(sel));
            if (pool == 0) {
                pool = (int)igb->_objectMemoryPool.p;
            }
        }
        obj = (igObject *)igMetaObject_CreateInstanceWithPool(_typeMeta, (igMemoryPoolView *)pool);
        if (obj == 0) {
            igb->_hasCriticalFailure = 1;
            igb->setRef(_index, (void *)(0));
            return;
        }
        igb->setRef(_index, (void *)obj);
        obj->release();
    } else {
        igb->setRef(_index, (void *)(0));
    }
}

/* Takes one more reference on `refParam` (null-safe). */
void igObjectDirEntry::refRef(void *refParam) {
    igObject::ref((igObject *)refParam);
}

/* Releases one reference to `refParam`, destroying it when its count reaches zero. */
void igObjectDirEntry::releaseRef(void *refParam) {
    igObject::release((igObject *)refParam);
}

void igObjectDirEntry::setMemoryPoolHandle(int handle) {
    _memoryPoolHandle = handle;
}

int igObjectDirEntry::getMemoryPoolHandle() {
    return _memoryPoolHandle;
}
}
}
