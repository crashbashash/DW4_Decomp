int igDirectory_GetRefByName(int directory, int name) {
    igDirEntryView *entry;

    entry = (igDirEntryView *)(((void *)igProperty_FindByName((igObjectList *)directory, (igMetaField *)g_propertyNameField[0], name)));
    if (entry == 0) {
        return 0;
    }
    return entry->_ref;
}

int igDirectory_GetObjectByName(int directory, int name) {
    igObjectDirEntry *entry;
    entry = (igObjectDirEntry *)((void *)igProperty_FindByName((igObjectList *)directory, (igMetaField *)g_propertyNameField[0], name)); if (entry == 0) return 0; if (igObject_IsKindOf(entry, (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) return entry->_ref; return 0;
}

void *igDirectory_GetEntryByName(int directory, int name) {
    return ((void *)igProperty_FindByName((igObjectList *)directory, (igMetaField *)g_propertyNameField[0], name));
}

void igDirectory_MakeConcrete(igDirectoryView *self) {
    unsigned count;
    unsigned i;
    igObjectDirEntry *entry;
    if (self->_concreteState != 1) {
        count = self->_count;
        i = 0;
        while (i < count) {
            entry = (igObjectDirEntry *)igDirectory_GetEntry((int *)self, i);
            if (entry != 0 && igObject_IsKindOf(entry, (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                if (entry->_typeMeta != 0 && ((igMetaObject *)entry->_typeMeta)->_abstractProxy != 0) {
                    ((igObjectDispatchView *)entry->_ref)->userMakeConcrete((igMetaObject *)entry->_typeMeta);
                }
            }
            i++;
        }
        self->_concreteState = 1;
    }
}

void igDirectory_SetName(igDirectoryView *self, int name) {
    int *header;
    int refs;
    int pool;
    int *oldName;
    int *interned;

    if (g_stringPool[0] == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool[0] = pool;
    }
    interned = (int *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)name);
    oldName = (int *)self->_name;
    if (oldName != 0) {
        header = oldName - 2;
        refs = oldName[-1] - 1;
        oldName[-1] = refs;
        if (refs == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    self->_name = (int)interned;
}

int igDirectory_ResolveExternalEntry(igDirectoryView *c, igExternalDirEntryView *o) {
if (o->_entryName != 0) { igDirEntryView *it = (igDirEntryView *)igDirectory_GetEntryByName((int)c, o->_entryName); if (it) { o->setRef(it->_ref); return 1; } } else { int i = o->_entryIndex; int n = c->_count; if (i >= 0 && i < n) { igDirEntryView *it = (igDirEntryView *)igDirectory_GetEntry((int *)c, i); o->setRef(it->_ref); return 1; } } return 0;
}

int igDirectory_GetInfoCount(void *directory) {
    return ((igDirectoryView *)directory)->_infoList->_count;
}

int igDirectory_AddLoadedRef(igDirectoryView *self) {
    igResult waited;
    igResult signalled;
    int count;

    if (self->_loadingSemaphore == 0) {
        count = self->_loadedRefCount + 1;
        self->_loadedRefCount = count;
        return count;
    }
    waited = self->_loadingSemaphore->wait(1);
    count = self->_loadedRefCount;
    if (waited.v == g_resultSuccess.v) {
        count += 1;
        self->_loadedRefCount = count;
        signalled = self->_loadingSemaphore->signal();
    }
    return count;
}

int igDirectory_UnrefLoaded(igDirectoryView *self) {
    int left;
    if (self->_loadingSemaphore == 0) {
        left = self->_loadedRefCount - 1;
        self->_loadedRefCount = left;
    } else {
        self->_loadingSemaphore->wait(1);
        left = self->_loadedRefCount - 1;
        self->_loadedRefCount = left;
    }
    if (left <= 0) {
        if (self->_loadingSemaphore != 0) {
            self->_loadingSemaphore->signal();
        }
        if (self->_managingResource != 0) {
            igTDataList<igDirectoryView *> *list = (igTDataList<igDirectoryView *> *)self->_managingResource->_directoryList;
            int index = list->find(self);
            igDirectoryView *o = list->_data[index];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt((igDataList *)list, index);
            list->_data[list->_count] = 0;
        }
    } else {
        if (self->_loadingSemaphore != 0) {
            self->_loadingSemaphore->signal();
        }
    }
    return left;
}

/* The new semaphore arrives with its reference already counted (an adopted reference). */
static inline igSemaphoreView *recreateLoadingSemaphore(igDirectoryView *directory, AdoptReference) {
    igRelease(directory->_loadingSemaphore);
    directory->_loadingSemaphore = ((igSemaphoreView *)igSemaphore_Create(0));
    return directory->_loadingSemaphore;
}

void igDirectory_CreateLoadingSemaphore(igDirectoryView *directory) {
    if (directory->_loadingSemaphore == 0) {
        recreateLoadingSemaphore(directory, AdoptReference())->create();
    }
}

