/* Drop the entry's object reference: virtual slot 92 (vfunc_23) is the setter of _ref (+24) that
 * retains the new value and releases the old one, so calling it with 0 releases the held object;
 * the igObject default of this slot (an empty stub) then runs. */
void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self) {
    ((DirEntryRefSetterView *)self)->SetRef((int)(0));
    Gap__Core__igObject__vfunc_10((int)self);
}

static inline const char *nameOf_3010f0(const igObjectDirEntry *entry) {
    return entry->_name != 0 ? (const char *)entry->_name : ((char *)emptyString);
}

static inline EntryList_3010f0 *asEntryList_3010f0(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, (igMetaObject *)g_igObjectList_metaObject[0]) != 0) return (EntryList_3010f0 *)object;
    return 0;
}

igObjectDirEntry *Gap__Core__igObjectDirEntry__vfunc_26(igObjectDirEntry *self, DirFile_3010f0 *file) {
    igSmartPointer<EntryList_3010f0> lists(file->sharedEntries, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((DirEntryView *)self)->getMeta()->index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained((L_301ee0 *)lists.p, index + 1);
        lists->set(index, 0);
    }
    igSmartPointer<EntryList_3010f0> entries(asEntryList_3010f0(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->pool;
        entries.release();
        entries.p = ((EntryList_3010f0 *)FUN_002bd680(pool));
        lists->set(index, entries.p);
    }
    int i;
    EntryList_3010f0 *list;
    igObjectDirEntry *entry;
    int count;
    count = entries->_count;
    self->_index = -1;
    list = entries.p;
    for (i = 0; i < count; i++) {
        entry = ((igObjectDirEntry **)list->_data)[i];
        if (entry->_typeMeta == self->_typeMeta && nameOf_3010f0(entry) == nameOf_3010f0(self) &&
            entry->_memoryPoolHandle == self->_memoryPoolHandle) {
            return list->at(i);
        }
    }
    ObjectList_AppendRetained((igObjectList *)list, (igObject *)self);
    return self;
}

int Gap__Core__igObjectDirEntry__vfunc_22(void) {
    return ((int *)g_igObjectDirEntry_metaObject)[0];
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
void Gap__Core__igObjectDirEntry__vfunc_27(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
void Gap__Core__igObjectDirEntry__vfunc_28(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1) {
    char *s0;
    (igSmartPointer<igMetaObject> &)arg0->_typeMeta = arg1;
    if (arg1) {
        char *name = (char *)arg1->_name;
        void *pool = Pool::get();
        s0 = ((char *)StringPool_Intern((StringPool *)pool, (const char *)name));
        releaseString((const char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    } else {
        void *pool = Pool::get();
        s0 = ((char *)StringPool_Intern((StringPool *)pool, (const char *)text_NoMeta));
        releaseString((const char *)arg0->_typeMetaName);
        arg0->_typeMetaName = (int)s0;
    }
}

/* slot 23 of igObjectDirEntry: set the _ref reference (+24; reflected as a raw ref, but the code
 * treats it as a counted igObject). Reference-counted assignment: retain the new object, release
 * the old one (destroying it when its 23-bit count reaches zero), then store the new one. */
void Gap__Core__igObjectDirEntry__vfunc_23(igObjectDirEntry *self, igObject *object) {
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

void Gap__Core__igObjectDirEntry__vfunc_38(void *arg0) {
    DW4VC_88_0_3010f0 *a = *(DW4VC_88_0_3010f0 **)((char *)arg0 + 24);
    if (a != 0) {
        int (*f)() = a->vX()->fn;
        if (f != 0) {
            FUN_00301590((igObjectDirEntry *)arg0, (igMetaObject *)f());
        }
    }
}

void Gap__Core__igObjectDirEntry__vfunc_39(S_3010f0 *arg0, A_3010f0 *arg1) {
    int temp_s0_2;
    void *(*temp_v1)();
    V_3010f0 *temp_s0;
    void *var_v0;

    temp_s0 = arg0->f24;
    R_3010f0 *r = temp_s0->vX();
    var_v0 = r;
    temp_v1 = r->f64;
    if (temp_v1 != 0) {
        var_v0 = temp_v1();
    }
    arg0->f48 = FUN_002fe600((igTDataList<ChainMeta *> *)arg1->f192, (ChainMeta *)var_v0);
    temp_s0_2 = arg1->f148;
    arg1->f148 = temp_s0_2 + igObject_GetSerializedSize((SizeObject *)temp_s0);
    arg1->f144 = arg1->f144 + 1;
}

void Gap__Core__igObjectDirEntry__vfunc_36(igObjectDirEntry *arg0, int arg1) {
    int temp_a0;

    temp_a0 = arg0->_ref;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            igObject_RegisterInstance((void **)temp_a0, (void *)arg0->_typeMeta);
            return;
        }
        igObject_RegisterInstance((void **)temp_a0, (void *)0);
    }
}

void Gap__Core__igObjectDirEntry__vfunc_37(igObjectDirEntryView *self)
{
    self->_ref->vfunc_15();
}

static inline void addRef(DirEntryCounted *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }

static inline void dropRef(DirEntryCounted *o) {
    o->_refCount = o->_refCount - 1;
    if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
}

static inline void setMeta(DirEntrySelf *self, DirEntryCounted *m) {
    DirEntryCounted *old;
    addRef(m);
    old = self->typeMeta;
    if (old != 0) { dropRef(old); }
    self->typeMeta = m;
}

void Gap__Core__igObjectDirEntry__vfunc_31(DirEntrySelf *self, DirEntryFileView *file) {
    int index;
    DirEntryCounted *m;
    DirEntryCounted *obj;
    int pool;
    int sel;
    index = self->typeMetaIndex;
    if (index == -1) {
        setMeta(self, ((DirEntryCounted *)igObjectSystem_FindMetaByNameDefault((const char *)self->typeMetaName)));
    } else {
        setMeta(self, file->metas->data[index]);
    }
    if (self->typeMeta != 0) {
        sel = self->pool;
        if (sel == -1 || sel == 1 || sel == 2) {
            pool = file->pool;
        } else {
            pool = ((int)Memory_GetAllocatorBySelector(sel));
            if (pool == 0) {
                pool = file->pool;
            }
        }
        obj = ((DirEntryCounted *)igMetaObject_CreateInstanceWithPool((PooledMeta *)self->typeMeta, (MemoryPool *)pool));
        if (obj == 0) {
            file->failed = 1;
            FUN_002d7da0((A7da0 *)file, self->index, (int)0);
            return;
        }
        FUN_002d7da0((A7da0 *)file, self->index, (int)obj);
        dropRef(obj);
    } else {
        FUN_002d7da0((A7da0 *)file, self->index, (int)0);
    }
}

/* Takes one more reference on `object` (null-safe): bumps its shared igObject _refCount. */
void Gap__Core__igObjectDirEntry__vfunc_24(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

/* Release one reference to `object`: drop its reference count and destroy it when the 23-bit count
 * (the `<< 0x29 >> 0x29` mask) reaches zero. `self` is not used. */
void Gap__Core__igObjectDirEntry__vfunc_25(igObjectDirEntry *self, igObject *object) {
    if (object != 0) {
        object->_refCount = (int)object->_refCount - 1;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(object);
        }
    }
}

/* igObjectDirEntry vtable slot 29: setter for `_memoryPoolHandle` (+44), the pool handle field of
 * the directory entry. Slot 30 is the matching getter; igMemoryDirEntry has the same pair. */
void Gap__Core__igObjectDirEntry__vfunc_29(igObjectDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}

/* IgObjectDirEntry vtable slot 30, a plain getter that returns the reflected field
 * _memoryPoolHandle (+44). */
int Gap__Core__igObjectDirEntry__vfunc_30(igObjectDirEntry *self) {
    return self->_memoryPoolHandle;
}

void ObjectList_FillRetained(L_301c90 *arg0, R_301c90 *arg1) {
    int n;
    int i;
    int j;
    int cnt;
    R_301c90 **data;
    int k;
    R_301c90 *t;
    n = arg0->cnt;
    if (arg1 != 0) {
        for (i = 0; i < n; i++) {
            arg1->f4 = arg1->f4 + 1;
        }
    }
    for (j = 0; j < n; j++) {
        t = arg0->data[j];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    cnt = arg0->cnt;
    data = arg0->data;
    for (k = 0; k < cnt; k++) {
        data[k] = arg1;
    }
}

void ObjectList_ClearRetainedPreserveCount(struct L_301d80 *arg0, int extra1) {
    int n;
    int i;
    struct R_301d80 *o;

    n = arg0->count;
    for (i = 0; i < n; i++) {
        o = arg0->data[i];
        if (o != 0) {
            o->refs = o->refs - 1;
            if ((o->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (arg0->count != 0) {
        memset(arg0->data, 0, arg0->count * 4);
    }
}

