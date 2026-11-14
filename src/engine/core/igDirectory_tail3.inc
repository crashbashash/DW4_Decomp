int FUN_002d8e70(int arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(((void *)igProperty_FindByName((igObjectList *)arg0, (igMetaField *)g_propertyNameField[0], arg1)));
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)(temp_v0) + 24);
}

int FUN_002d8eb0(int arg0, int arg1) {
    igObjectDirEntry *s0;
    s0 = (igObjectDirEntry *)((void *)igProperty_FindByName((igObjectList *)arg0, (igMetaField *)g_propertyNameField[0], arg1)); if (s0 == 0) return 0; if (igObject_IsKindOf(s0, (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) return s0->_ref; return 0;
}

void *FUN_002d8f10(int arg0, int arg1) {
    return ((void *)igProperty_FindByName((igObjectList *)arg0, (igMetaField *)g_propertyNameField[0], arg1));
}

void FUN_002d8f20(igDirectoryView *arg0) {
    unsigned n;
    unsigned i;
    igObjectDirEntry *e;
    if (arg0->_concreteState != 1) {
        n = arg0->_count;
        i = 0;
        while (i < n) {
            e = (igObjectDirEntry *)FUN_002d7e90((int *)arg0, i);
            if (e != 0 && igObject_IsKindOf(e, (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                if (e->_typeMeta != 0 && ((igMetaObject *)e->_typeMeta)->_abstractProxy != 0) {
                    ((igObjectDispatchView *)e->_ref)->vfunc_18((igMetaObject *)e->_typeMeta);
                }
            }
            i++;
        }
        arg0->_concreteState = 1;
    }
}

void FUN_002d8fe0(igDirectoryView *arg0, int arg1) {
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
    temp_s0 = (int *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1);
    temp_a0 = (int *)arg0->_name;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_name = (int)temp_s0;
}

int Gap__Core__igDirectory__vfunc_25(igDirectoryView *c, igExternalDirEntryView *o) {
if (o->_entryName != 0) { igDirEntryView *it = (igDirEntryView *)FUN_002d8f10((int)c, o->_entryName); if (it) { o->vfunc_23(it->_ref); return 1; } } else { int i = o->_entryIndex; int n = c->_count; if (i >= 0 && i < n) { igDirEntryView *it = (igDirEntryView *)FUN_002d7e90((int *)c, i); o->vfunc_23(it->_ref); return 1; } } return 0;
}

int FUN_002d9120(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 28)) + 8);
}

int FUN_002d9130(igDirectoryView *arg0) {
    igResult a;
    igResult b;
    int v;

    if (arg0->_loadingSemaphore == 0) {
        v = arg0->_loadedRefCount + 1;
        arg0->_loadedRefCount = v;
        return v;
    }
    a = arg0->_loadingSemaphore->wait(1);
    v = arg0->_loadedRefCount;
    if (a.v == g_resultSuccess.v) {
        v += 1;
        arg0->_loadedRefCount = v;
        b = arg0->_loadingSemaphore->signal();
    }
    return v;
}

int FUN_002d91c0(igDirectoryView *self) {
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
    directory->_loadingSemaphore = ((igSemaphoreView *)FUN_002ba650(0));
    return directory->_loadingSemaphore;
}

void FUN_002d9330(igDirectoryView *directory) {
    if (directory->_loadingSemaphore == 0) {
        recreateLoadingSemaphore(directory, AdoptReference())->create();
    }
}

