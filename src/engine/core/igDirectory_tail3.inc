namespace Gap {
namespace Core {

void *igDirectory::findRefByEntryName(const char *name) const {
    igDirEntry *entry;

    entry = (igDirEntry *)search((igStringMetaField *)igNamedObject::k_name, name);
    if (entry == 0) {
        return 0;
    }
    return entry->getRef();
}

igObject *igDirectory::findObjectRefByEntryName(const char *name) const {
    igObjectDirEntry *entry;
    entry = (igObjectDirEntry *)search((igStringMetaField *)igNamedObject::k_name, name);
    if (entry == 0) return 0;
    if (entry->isOfType(igObjectDirEntry::getClassMeta()) != 0) return (igObject *)entry->getRef();
    return 0;
}

igDirEntry *igDirectory::findEntryByEntryName(const char *s) const {
    return (igDirEntry *)search((igStringMetaField *)igNamedObject::k_name, s);
}

void igDirectory::makeAllConcrete() {
    unsigned count;
    unsigned i;
    igObjectDirEntry *entry;
    if (_concreteState != 1) {
        count = _count;
        i = 0;
        while (i < count) {
            entry = (igObjectDirEntry *)get(i);
            if (entry != 0 && entry->isOfType(igObjectDirEntry::getClassMeta()) != 0) {
                if (entry->_typeMeta != 0 && entry->_typeMeta->_abstractProxy != 0) {
                    ((igObject *)entry->getRef())->userMakeConcrete(entry->_typeMeta);
                }
            }
            i++;
        }
        _concreteState = 1;
    }
}

void igDirectory::setDirectoryName(const char *newName) {
    _name = newName;
}

bool igDirectory::resolveExternal(igExternalDirEntry *externalEntry) {
    if (externalEntry->_entryName.p != 0) {
        igDirEntry *it = findEntryByEntryName(externalEntry->_entryName.p);
        if (it) {
            externalEntry->setRef(it->getRef());
            return 1;
        }
    } else {
        int i = externalEntry->_entryIndex;
        int n = _count;
        if (i >= 0 && i < n) {
            igDirEntry *it = get(i);
            externalEntry->setRef(it->getRef());
            return 1;
        }
    }
    return 0;
}

unsigned int igDirectory::getInfoCount() const {
    return _infoList->_count;
}

int igDirectory::loadRef() {
    igResult waited;
    igResult signalled;
    int count;

    if (_loadingSemaphore == 0) {
        count = _loadedRefCount + 1;
        _loadedRefCount = count;
        return count;
    }
    waited = _loadingSemaphore->obtainResource(true);
    count = _loadedRefCount;
    if (waited.v == g_resultSuccess.v) {
        count += 1;
        _loadedRefCount = count;
        signalled = _loadingSemaphore->releaseResource();
    }
    return count;
}

int igDirectory::loadRelease() {
    int left;
    if (_loadingSemaphore == 0) {
        left = _loadedRefCount - 1;
        _loadedRefCount = left;
    } else {
        _loadingSemaphore->obtainResource(true);
        left = _loadedRefCount - 1;
        _loadedRefCount = left;
    }
    if (left <= 0) {
        if (_loadingSemaphore != 0) {
            _loadingSemaphore->releaseResource();
        }
        if (_managingResource != 0) {
            ::igTDataList< ::igObject *> *list = (::igTDataList< ::igObject *> *)((igResource *)_managingResource)->_directoryList;
            int index = list->find((::igObject *)this);
            ::igObject *o = list->_data[index];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt((::igDataList *)list, index);
            list->_data[list->_count] = 0;
        }
    } else {
        if (_loadingSemaphore != 0) {
            _loadingSemaphore->releaseResource();
        }
    }
    return left;
}

/* The new semaphore arrives with its reference already counted (an adopted reference). */
static inline igSemaphore *recreateLoadingSemaphore(igSmartPointer<igSemaphore> &held, AdoptReference) {
    held.release();
    held.p = igSemaphore::_instantiateFromPool(0);
    return held.p;
}

void igDirectory::createLoadingSemaphore() {
    if (_loadingSemaphore == 0) {
        recreateLoadingSemaphore(_loadingSemaphore, AdoptReference())->activate();
    }
}
}
}
