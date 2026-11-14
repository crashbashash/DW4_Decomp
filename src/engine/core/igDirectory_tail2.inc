void FUN_002d7b00(void) {
    igDirEntry_GetMetaObject();
    igObjectDirEntry_GetMetaObject();
    igMemoryDirEntry_GetMetaObject();
    igExternalDirEntry_GetMetaObject();
    igExternalIndexedEntry_GetMetaObject();
    igExternalInfoEntry_GetMetaObject();
    igInfo_GetMetaObject();
    igResource_GetMetaObject();
}

void Gap__Core__igDirectory__vfunc_12(igDirectoryView *arg0) {
    igResult sp4C;
    int temp_s2;
    int i;
    int *temp_v0;

    if (arg0->_managingResource != 0) {
        for (i = 0; i < arg0->_externalDirectoryList->_count; i++) {
            igResource_UnloadDirectory((igResource *)arg0->_managingResource, arg0->_externalDirectoryList->_data[i]->_name);
        }
    }
    temp_s2 = FUN_002d9120(arg0);
    for (i = 0; i < temp_s2; i++) {
        temp_v0 = (int *)FUN_002d8370(arg0, i);
        if (temp_v0[3] == (int)arg0) {
            temp_v0[3] = 0;
        }
    }
    Gap__Core__igObject__vfunc_10((int)arg0);
    if (arg0->_loadingSemaphore != 0 && arg0->_loadingSemaphore->isCreated() != 0) {
        sp4C = arg0->_loadingSemaphore->destroy();
    }
}

int FUN_002d7c50(O7c50 *arg0, unsigned key) {
    L7c50 *l = arg0->l;
    int lo, hi, mid, idx, n;
    unsigned v;
    int r;
    if (l != 0) {
        n = l->n;
        lo = 0;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            v = l->data[mid];
            if (v < key) {
                lo = mid + 1;
            } else if (key < v) {
                hi = mid - 1;
            } else {
                idx = mid;
                goto found;
            }
        }
        if (n == 0) {
            idx = -1;
        } else {
            v = l->data[lo];
            if (key < v || v < key) {
                idx = -1;
            } else {
                idx = lo;
            }
        }
found:
        v = l->data[idx];
        if (v == key) {
            return (int)FUN_002d7e90((int *)arg0, idx);
        }
        return 0;
    }
    return igProperty_FindBySortedKey((void *)arg0, (void *)DAT_00586730[0], (int)key);
}

void *thunk_FUN_002d7e90(int *arg0, int arg1)
{
    return FUN_002d7e90(arg0, arg1);
}

int FUN_002d7d60(void *arg0, int arg1) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 44));
    if (temp_v0 != 0) {
        return *(int *)(*(int *)((char *)(temp_v0) + 16) + (arg1 * 4));
    }
    return *(int *)((char *)((*(int *)(*(int *)((char *)(arg0) + 16) + (arg1 * 4)))) + 24);
}

void FUN_002d7da0(A7da0 *a, int i, int x) {
    if (a->l != 0 && a->f40 != 0) {
        igDirEntryView *o = a->arr[i];
        o->vfunc_23(x);
        o->vfunc_24(x);
        {
            struct L7da0 *l = a->l;
            if (l->cnt != 0 && i >= 0 && i < l->cnt) l->arr[i] = x;
        }
    } else {
        a->arr[i]->vfunc_23(x);
    }
}

void *FUN_002d7e90(int *arg0, int arg1) {
    if (arg0[11] != 0) {
        VC7e90 *t = (VC7e90 *)((int *)arg0[4])[arg1];
        t->vX(FUN_002d7d60(arg0, arg1));
        ((int *)t)[3] = arg1;
        return t;
    }
    return (void *)((int *)arg0[4])[arg1];
}

static inline void releaseBound(FieldBindObject *o) {
    if (o != 0) {
        o->_refCount = (int)o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
}

static inline FieldBindItem *castBinding(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
        return o;
    }
    return 0;
}

static inline FieldBindItem *castRefField(FieldBindItem *o) {
    if (o != 0 && igObject_IsKindOf(o, (igMetaObject *)((*(int *)g_igObjectRefMetaField_metaObject))) != 0) {
        return o;
    }
    return 0;
}

static inline void setSlot(FieldBindSlotList *l, int i, FieldBindObject *v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = (FieldBindObject *)v;
    }
}

int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value) {
    int changed = 0;
    int i;
    int j;
    int n;
    FieldBindObject *current;
    FieldBindItem *item;
    for (i = 0; i < self->count; i++) {
        current = *field;
        if ((FieldBindObject *)FUN_002d7d60(self, i) == (FieldBindObject *)current) {
            if (self->overrides != 0) {
                releaseBound(*field);
                if (*value != 0) {
                    (*value)->_refCount = (*value)->_refCount + 1;
                }
                setSlot(self->overrides, i, *value);
            } else {
                self->targets[i]->Assign(*value);
            }
            changed++;
        }
        item = castBinding((FieldBindItem *)FUN_002d7e90((int *)self, i));
        if (item != 0) {
            igSmartPointer<igVirtualObject> source(item->source, kRetainReference);
            if (source.get() == 0) {
                continue;
            }
            n = igMetaObject_GetFieldCount((igMetaObject *)(((FieldBindObject *)source.get())->GetMeta()));
            for (j = 0; j < n; j++) {
                FieldBindItem *f;
                f = castRefField(((FieldBindItem *)igMetaObject_GetFieldAt((igMetaObject *)(((FieldBindObject *)source.get())->GetMeta()), j)));
                if (f != 0) {
                    if (*(FieldBindObject **)((char *)source.get() + f->offset) == *field) {
                        igObjectRefMetaField_Assign((igObjectRefMetaField *)f, (void *)(source.get()), (igObject *)(*value));
                        changed++;
                    }
                }
            }
        }
    }
    return changed;
}

void FUN_002d81f0(void *arg0, int arg1) {
    FUN_002d8230((RemovableListHolder *)arg0, (igObject *)((void *)igProperty_FindByName((igObjectList *)(*(int *)((char *)arg0 + 28)), (igMetaField *)(*(int *)0x585BE0), arg1)));
}

void FUN_002d8230(RemovableListHolder *h, igObject *object) {
    int idx;
    RemovableList *f;
    f = h->list;
    idx = f->find(object);
    if (-1 < idx) {
        h->list->removeAt(idx);
    }
}

void FUN_002d8310(void *arg0, void *arg1) {
    ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)(arg0) + 28)), (igObject *)arg1);
    *(int *)((char *)(arg1) + 12) = (int)(arg0);
}

void * igDirectory_FindInfoByName(int *arg0, int arg1) {
    return ((void *)igProperty_FindByName((igObjectList *)arg0[7], (igMetaField *)g_propertyNameField[0], arg1));
}

/* The lower bound is spelled `arg1 <= -1` so it fuses into slti at. */
int FUN_002d8370(void *arg0, int arg1) {
    void *temp_a0;
    if (!(arg1 <= -1)) {
        temp_a0 = (void *)(*(int *)((char *)(arg0) + 28));
        if (arg1 < *(int *)((char *)(temp_a0) + 8)) {
            return *(int *)(*(int *)((char *)(temp_a0) + 16) + (arg1 * 4));
        }
    }
    return 0;
}

int FUN_002d83b0(T83b0 *arg0, int arg1, int arg2) {
    int i;
    O83b0 *o;

    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->data[i];
        if (o->flag == 1 && (o->vf(arg1, arg2) & 0xFF) == 1) {
            return 1;
        }
    }
    return 0;
}

int FUN_002d8460(void *dir, unsigned key) {
    igSmartPointer<igDirEntry> h((igDirEntry *)FUN_002d7c50((O7c50 *)dir, key), kRetainReference);
    if (h.get() != 0) {
        return 1;
    }
    return 0;
}

int FUN_002d8520(int arg0, VisitorFieldView *arg1, igDirectoryView *arg2) {
    int i;
    int n;
    if (arg0 == 0) {
        return 1;
    }
    if (arg1 != 0) {
        return arg1->Write(arg0) == -1;
    }
    if ((FUN_002d8460(arg2, arg0) & 0xFF) == 1) {
        return 1;
    }
    n = arg2->_externalDirectoryList->_count;
    for (i = 0; i < n; i++) {
        if ((FUN_002d83b0((T83b0 *)arg2->_externalDirectoryList->_data[i], (int)arg2, arg0) & 0xFF) == 1) {
            return 1;
        }
    }
    FUN_002d87b0((FieldLinkSet *)arg2, (FieldLinkObject *)arg0, 0, 0);
    return 0;
}

int FUN_002d8620(int arg0, int arg1, int arg2, int extra3) {
    int temp_v0;

    if (arg1 != 0) {
        igObject_VisitFields((VisitorObjectView *)arg1, (int (*)(void *, void *, void *))&FUN_002d8520, (void *)arg0);
        temp_v0 = FUN_002d86b0((A86b0 *)arg0, (K86b0 *)DAT_00586730[0], arg1);
        igNamedObject_SetName((igNamedObject *)(FUN_002d7e90((int *)arg0, temp_v0)), arg2);
        return temp_v0;
    }
    return -1;
}

int FUN_002d86b0(A86b0 *arg0, K86b0 *arg1, unsigned arg2) {
    int n;
    int lo;
    int hi;
    int mid;
    unsigned v;
    if (arg1 == 0) return -1;
    n = arg0->n;
    hi = n - 1;
    if (n <= 0) return 0;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        v = *(unsigned *)((char *)FUN_002d7e90((int *)arg0, mid) + arg1->f8);
        if (v < arg2) {
            lo = mid + 1;
        } else if (arg2 < v) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    v = *(unsigned *)((char *)FUN_002d7e90((int *)arg0, lo) + arg1->f8);
    if (v < arg2) lo++;
    return lo;
}

int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user) {
    int index = 0;
    FieldLinkInfo *info;
    void *pool;
    int mode;
    if (obj == 0) {
        return -1;
    }
    if (self->count > 0) {
        index = FUN_002d86b0((A86b0 *)self, (K86b0 *)DAT_00586730[0], (unsigned)obj);
        if (self->count > index && (FieldLinkObject *)FUN_002d7d60(self, index) == obj) {
            return -1;
        }
    }
    if (obj != 0) {
        obj->Touch();
        if (igObject_IsKindOf(self, (igMetaObject *)((*(int *)g_igIGBFile_metaObject))) != 0) {
            if (self->mode == 1) {
                obj->Prepare();
            }
            {
                FieldLinkInfo *m = obj->GetMeta();
                int (*fn)() = m->poolFor;
                if (fn != 0) {
                    self->reset = 0;
                    obj->SetPool(fn());
                }
            }
        }
    }
    igSmartPointer<FieldLinkRecord> record(((FieldLinkRecord *)FUN_002bd8f0((int)(((void *)igObject_GetAllocator((int)self))))));
    record.get()->index = index;
    RetainedWord<FieldLinkRecord> inserted(record.get());
    List_InsertWords((igDataList *)self, index, 1, &inserted);
    if (name != 0) {
        igNamedObject_SetName((igNamedObject *)(record.get()), (int)name);
    }
    record.get()->user = user;
    record.get()->extra = 0;
    record.get()->Assign(obj);
    if (self->tracks != 0) {
        info = obj->GetMeta();
        pool = 0;
        if (self->namedPools != 0 && info != 0 && ((char *)igMetaObject_GetPoolName((int *)info)) != 0) {
            pool = Memory_GetAllocatorByName((int)(((char *)igMetaObject_GetPoolName((int *)info))));
        }
        if (pool == 0) {
            pool = ((void *)igObject_GetAllocator((int)obj));
        }
        if (pool != 0) {
            mode = ((FieldLinkObject *)Memory_GetCurrentContextAlias())->Classify(pool);
            if (mode == 1 || mode == 2) {
                mode = -1;
            }
            record.get()->SetContext(mode);
        }
    }
    if (obj != 0) {
        FUN_00301590((igObjectDirEntry *)(record.get()), (igMetaObject *)(obj->GetMeta()));
    }
    return index;
}

int FUN_002d8a80(L8a80 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7) {
    int s0;
    int s0b;
    int v;
    if (arg2 == 0) return -1;
    s0 = 0;
    if (arg0->count > 0) {
        s0 = FUN_002d86b0((A86b0 *)arg0, (K86b0 *)DAT_00586730[0], arg2);
        if (s0 < arg0->count) { int r = FUN_002d7d60(arg0, s0); if (r == arg2) return -1; }
    }
    if (arg3 == 0) arg3 = FUN_002cc2c0();
    igSmartPointer<E8a80> record(((E8a80 *)FUN_002c0d80(FUN_00301000(arg0))));
    record.get()->idx = s0;
    RetainedWord<E8a80> inserted(record.get());
    List_InsertWords((igDataList *)arg0, s0, 1, &inserted);
    if (arg5) igNamedObject_SetName((igNamedObject *)(record.get()), arg5);
    record.get()->f16 = arg6;
    record.get()->f20 = 1;
    FUN_002eed00((igMemoryDirEntry *)(record.get()), (igObjectDispatchView *)arg3);
    int size = ((int)Memory_GetBufferSize((void *)arg2));
    record.get()->f28 = size;
    record.get()->f44 = arg4;
    record.get()->v21(arg2);
    record.get()->f52 = arg7;
    if (arg0->f65) {
        s0b = 0;
        if (arg0->f66 && arg1 && FUN_002fb8d0(arg1)) s0b = FUN_002f8920(FUN_002fb8d0(arg1));
        if (s0b == 0) s0b = FUN_002f04f0(arg2);
        if (s0b) {
            v = FUN_002f88d0()->v29(s0b);
            if (v == 1 || v == 2) v = -1;
            record.get()->v27(v);
        }
    }
    return record.get()->idx;
}

int FUN_002d8d00(Lst8d00 *list, int key, int name, int val) {
    int idx, cnt;
    if (key == 0) {
        return -1;
    }
    idx = FUN_002d86b0((A86b0 *)list, (K86b0 *)DAT_00586730[0], key);
    cnt = list->n;
    if (cnt > 0) {
        if (idx < cnt) {
            int f = FUN_002d7d60(list, idx);
            if (f == key) return -1;
        }
    }
    igSmartPointer<R8d00> entry((R8d00 *)FUN_002c77e0((int)(((void *)igObject_GetAllocator((int)list)))));
    igNamedObject_SetName((igNamedObject *)(entry.get()), name);
    entry.get()->f16 = val;
    entry.get()->f20 = 2;
    entry.get()->vX(key);
    entry.get()->f12 = idx;
    Retained retained(entry.get());
    List_InsertWords((igDataList *)list, idx, 1, &retained);
    return entry.get()->f12;
}

