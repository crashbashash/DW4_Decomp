/* Constructor: 30 records in use, no flags, an empty parent reference (its smart-pointer
 * constructor retains what it is given), a reference count of one in the low 23 bits of the
 * reference word, the records cleared and then named. */
ContextView *igMemoryPoolContextInfo_Construct(ContextView *self) {
    igObject_InitHeader((struct ObjectHeader *)self);
    self->_vtable = (int)g_igMemoryPoolContextInfo_vtable;
    self->usedRecords = 30;
    self->flags = 0;
    self->parent = 0;
    if (self->parent != 0) {
        self->parent->_refCount += 1;
    }
    self->_refCount = 0;
    ((RefCount *)&self->_refCount)->u.b.cnt = 1;
    memset(self->records, 0, sizeof(self->records));
    ((MemoryContext *)self)->InitializeRecordNames();
    return self;
}

/* IgMemoryPoolContextInfo: the destructor and the retained-allocator slot setter. A context holds
 * 46 records of 144 bytes starting at +0x14 (clearing them is the 6,624-byte memset in the
 * destructor). Each record is the allocator bound to that slot, a 128-byte inline name, a
 * descriptor and flag words. The object header is the igObject vtable word and reference word,
 * followed by a count at +8 (30 after construction, then the highest populated slot + 1), a flag
 * word at +12 and a parent object at +16 that the destructor releases with the igObject reference-
 * count idiom. The views below describe the observed 32-bit layout, not the original C++ spelling. */
/* Destructor: republish the vtable, clear the reference word and all records, rebuild the 46
 * record names, release the parent, and free the allocation when the low 16 bits of `deleteFlags`
 * are positive (deleting destructor). The parent word is left in place. */
void *igMemoryPoolContextInfo_Destruct(ContextView *self, long long deleteFlags) {
    if (self) {
        self->_vtable = (int)g_igMemoryPoolContextInfo_vtable; self->_refCount = 0;
        memset(self->records, 0, 6624); ((MemoryContext *)self)->InitializeRecordNames();
        if ((char *)self + 16) {
            igObject *parent = self->parent;
            if (parent) {
                --parent->_refCount;
                if (!(parent->_refCount & 0x7fffff)) igObject_Destroy(parent);
            }
        }
        if ((short)deleteFlags > 0) igMemoryPoolContextInfo_DeleteAllocation(self);
    }
    return self;
}

int FUN_002f2730(MemoryContext *arg0, int arg1) {
    int i, j;
    int r = 0;
    if (arg1 >= 0 && arg1 < 46) {
        char *e = (char *)(arg1 * 144) + (int)arg0;
        int *pk = (int *)(e + 20);
        r = *pk;
        if (r == 0) {
            if (*(int *)(e + 160) & 0x04000000) {
                arg0->BuildAndAttachEventTracker(arg1);
                return *pk;
            }
            if (1 < DAT_00587010[0]) {
                for (i = DAT_00587010[0] - 1; i >= 0; i--) {
                    if (DAT_00587000[i] == (MemoryContext *)arg0) break;
                }
                j = i - 1;
                if (j >= 0) {
                    MemoryContext *p = (MemoryContext *)DAT_00587000[j];
                    if (p != (MemoryContext *)arg0) r = (int)p->getAllocatorBySelector(arg1);
                }
            }
        }
    }
    return r;
}

/* Lookup of a context record by name. A context holds 46 records of 144 bytes starting at +0x14,
 * each with a 128-byte inline name at +4. The view below describes the observed 32-bit layout, not
 * the original C++ spelling. */
/* Dispatch-only view: the dummies pad the vtable so that Lookup lands on slot 21 (vtable offset
 * 92). */
/* 0 when the strings are equal */
/* Finds the first of the 46 records whose name equals `name` and returns what its slot-21 lookup
 * yields; null or empty names, and unknown names, give null. */
void *FUN_002f2830(MemoryContext *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!strcmp(self->records[i].name, name)) return self->getAllocatorBySelector(i);
        }
    }
    return 0;
}

/* (vtable offset 100) Bind `value` to record `index` (0..45). Re-binding the same object is a no-
 * op; a different old binding is released through Clear first. The new object is retained, and a
 * non-null binding raises the used-record count. */
void FUN_002f28d0(ContextView *self, int index, igObject *value) {
    if (index >= 0 && index < 46) {
        /* record address spelled as index * 144 + self (+ 20 for the allocator word); the
         * typed spelling &self->records[index] changes the bytes */
        unsigned int address = (unsigned int)index * 9; address <<= 4; address += (unsigned int)self;
        igObject **slot = (igObject **)(address + 20);
        igObject *previous = *slot;
        if (!previous || previous != value) {
            if (previous) ((MemoryContext *)self)->RemoveAllocator(index);
            *slot = value;
            if (value) {
                ++value->_refCount;
                if (index >= self->usedRecords) self->usedRecords = index + 1;
            }
        }
    }
}

int FUN_002f2990(int arg0, int arg1) {
    if ((arg1 >= 0) && (arg1 < 0x2E)) {
        return arg0 + (arg1 * 0x90) + 0x18;
    }
    return (int)&((char *)DAT_004f7910)[0];
}

/* The global count test is written `1 < n`. */
int *FUN_002f29d0(MemoryContext *arg0, void *pool) {
    int i, j;
    if (pool != 0) {
        for (i = 0; i < 46; i++) {
            { void *k = arg0->records[i].allocator; if (k == pool) return (int *)arg0->records[i].name; }
        }
    }
    if (1 < DAT_00587010[0]) {
        for (i = DAT_00587010[0] - 1; i >= 0; i--) {
            if (DAT_00587000[i] == (MemoryContext *)arg0) break;
        }
        j = i - 1;
        if (j >= 0) {
            MemoryContext *p = (MemoryContext *)DAT_00587000[j];
            if (p != (MemoryContext *)arg0) return (int *)p->vfunc_27(pool);
        }
    }
    return (int *)((char *)DAT_004f7910);
}

/* Renames record `recordIndex` of the context: copies at most 127 characters into the record's
 * inline 128-byte name field, terminates it, and renames the record's bound named object (if any)
 * to match. Out-of-range indices are ignored. The context holds 46 records of 144 bytes starting
 * at +0x14, each with a 128-byte inline name at +4. */
void FUN_002f2ab0(int self, int recordIndex, int name) {
    int boundObject;
    void *record;

    if ((recordIndex >= 0) && (recordIndex < CONTEXT_RECORD_COUNT)) {
        record = (void *)(self + (recordIndex * CONTEXT_RECORD_SIZE) + CONTEXT_RECORDS_OFFSET);
        strncpy((char *)record + 4, name, CONTEXT_RECORD_NAME_MAX);
        *(char *)((char *)(record) + 131) = 0;
        boundObject = *(int *)((char *)(record) + 132);
        if (boundObject != 0) {
            igNamedObject_SetName((igNamedObject *)boundObject, name);
        }
    }
}

int FUN_002f2b30(int arg0, char *arg1) {
    int i;

    if (arg1 != 0 && *arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(arg0 + (i * 0x90) + 0x18, arg1) == 0) {
                return i;
            }
        }
    }
    return -1;
}

int FUN_002f2bc0(int arg0, char *arg1) {
    int i;
    char *s = arg1;
    if (s != 0 && *s != 0) {
        if (strncmp(s, &text_kIGMemoryPoolHandle[0], 0x13) == 0) {
            s += 0x13;
        } else if (strncmp(s, &text_kIGMemoryPool[0], 0xD) == 0) {
            s += 0xD;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(arg0 + i * 0x90 + 0x18, s) == 0) return i;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(g_memoryContextNames[i], s) == 0) return i;
        }
    }
    return -1;
}

int FUN_002f2cd0(int arg0, int arg1) {
    int i;
    if (arg1 != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (arg1 == *(int *)((char *)((arg0 + (i * 0x90))) + 20)) {
                return i;
            }
        }
    }
    return -1;
}

igResult FUN_002f2d20(MemoryContext *self, int config, int section) {
    int temp_s0;
    Ref *temp_a0;
    if (self->contextInfo == 0) {
        temp_s0 = ((int)igObject_GetAllocator((int)self));
        temp_a0 = (Ref *)self->contextInfo;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        self->contextInfo = (igMemoryPoolContextInfoView *)FUN_002c01f0(temp_s0);
    }
    if (config == 0) {
        config = (int)((ObjectSystemView *)(*(void * *)g_objectSystem))->configRegistry;
    }
    igResult sp6C = self->contextInfo->vfunc_25((IniSectionsView *)config, (char *)section);
    if (sp6C.v == g_resultSuccess.v) {
        igResult sp68 = self->vfunc_35((int)self->contextInfo, 1);
        sp6C = sp68;
    }
    return sp6C;
}

igResult FUN_002f2e30(MemoryContext *self, int config, int index) {
    int temp_s0;
    Ref *temp_a0;
    if (self->contextInfo == 0) {
        temp_s0 = ((int)igObject_GetAllocator((int)self));
        temp_a0 = (Ref *)self->contextInfo;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        self->contextInfo = (igMemoryPoolContextInfoView *)FUN_002c01f0(temp_s0);
    }
    if (config == 0) {
        config = (int)((ObjectSystemView *)(*(void * *)g_objectSystem))->configRegistry;
    }
    igResult sp6C = self->contextInfo->vfunc_26((IniSectionsView *)config, index);
    if (sp6C.v == g_resultSuccess.v) {
        igResult sp68 = self->vfunc_35((int)self->contextInfo, 1);
        sp6C = sp68;
    }
    return sp6C;
}

igResult FUN_002f2f40(SlotReadTable *self, int file) {
    igResult result = g_resultSuccess;
    int i;
    FUN_002f8b20((void *)file);
    for (i = 0; i < 46; i++) {
        if (*(int *)((char *)self + i * 144 + 152) != 0) {
            igRefHead *o = (igRefHead *)FUN_002bfed0(((int)igObject_GetAllocator(file)));
            if (self->readOne(i, o) == g_resultFailure) {
                result = g_resultFailure;
                o->rc = o->rc - 1;
                if (((unsigned long long)((long long)(int)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o);
            } else {
                FUN_002f8a80((void *)file, (void *)o);
            }
        }
    }
    return result;
}

igResult FUN_002f3060(DirSlotTable *self, int file, int arg) {
    int count = FUN_002f8a50((void *)file);
    igResult result = g_resultSuccess;
    int i;
    if (self->slots == 0) {
        int allocator = ((int)igObject_GetAllocator((int)self));
        DirSlotObject *old = self->slots;
        if (old != 0) { old->rc = old->rc - 1; if (((unsigned long long)((long long)(int)old->rc << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->slots = (DirSlotObject *)FUN_002c01f0(allocator);
    }
    for (i = 0; i < count; i++) {
        DirSourceRecord *r;
        if ((r = (DirSourceRecord *)((void *)FUN_002f8a60((void *)file, i))) != 0) {
            if (self->fillSlot(self->slotFor(r->id), r, arg) == g_resultFailure) {
                result = g_resultFailure;
            }
        }
    }
    return result;
}

/* Fills one memory-pool handle object from the pool descriptor table: looks up descriptor `index`
 * (0x90 bytes each, from +0x14 of the table) and, when the index is in 0..45, copies it into the
 * handle object: the descriptor name via igNamedObject_SetName, the integer size/limit fields
 * (+0x1c..+0x24, +0x50), and ten interned strings (+0x18, +0x28..+0x4c, each assigned through the
 * shared StringPool with the usual retain/release of the old token). The descriptor's attached
 * object (+0 of the entry) supplies +0x1c when it reports a size; the handle name (+0x14) is built
 * from the table name 'kIGMemoryPoolHandle%s'. The status written through `result` is g_resultSuccess
 * on success and g_resultFailure for an out-of-range index. */
void FUN_002f31b0(int *result, PoolTable *table, int index, PoolHandle *handle)
{
    StringToken *old;
    const char *text;
    SizedObject *object;
    StringTokenHeader *header;
    PoolEntry *entry;
    char nameBuf[128];
    void *poolObj;
    int count;
    StringToken *token;
    int status;

    status = g_resultSuccess.v;
    if (index >= 0 && index < 46) {
        entry = &table->entries[index];
        igNamedObject_SetName((igNamedObject *)handle, (int)entry->name);
        if (entry->defaults != 0) {
            ASSIGN_TOKEN(handle->token0, entry->defaults->text0);
            object = table->entries[index].object;
            if (object != 0) {
                if (igObject_IsKindOf(object, (igMetaObject *)g_igArenaMemoryPool_metaObject[0]) != 0) {
                    if (object->count() != 0) {
                        if (object->total() > object->count()) {
                            entry->defaults->limit = (int)object->total();
                        }
                    } else if (object->hasLimitOrSize() != 0) {
                        entry->defaults->limit = (int)object->limit();
                    }
                } else if (object->limit() != 0) {
                    entry->defaults->limit = (int)object->limit();
                }
            }
            handle->limit = entry->defaults->limit;
            handle->field20 = entry->defaults->field20;
            handle->field24 = entry->defaults->field24;
            ASSIGN_TOKEN(handle->token1, entry->defaults->text1);
            ASSIGN_TOKEN(handle->token2, entry->defaults->text2);
            ASSIGN_TOKEN(handle->token3, entry->defaults->text3);
            ASSIGN_TOKEN(handle->token4, entry->defaults->text4);
            ASSIGN_TOKEN(handle->token5, entry->defaults->text5);
            ASSIGN_TOKEN(handle->token6, entry->defaults->text6);
            ASSIGN_TOKEN(handle->token7, entry->defaults->text7);
            ASSIGN_TOKEN(handle->token8, entry->defaults->text8);
            ASSIGN_TOKEN(handle->token9, entry->defaults->text9);
            ASSIGN_TOKEN(handle->token10, entry->defaults->text10);
            handle->field50 = entry->defaults->field50;
        }
        sprintf(nameBuf, text_kIGMemoryPoolHandle_s, g_memoryContextNames[index]);
        ASSIGN_TOKEN_DIRECT(handle->handleName, nameBuf);
    } else {
        status = g_resultFailure.v;
    }
    *result = status;
}

static inline void *descPool() {
    if ((*(void * *)g_stringPool) == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0) { p = ((void *)StringPool_Construct((StringPool *)p)); }
        (*(void * *)g_stringPool) = p;
    }
    return (*(void * *)g_stringPool);
}

static inline void setDescString(char **dst, char *src) {
    char *v = ((char *)StringPool_Intern((StringPool *)(descPool()), src));
    char *old = *dst;
    if (old != 0) {
        PoolDescString *h = (PoolDescString *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunkOwnerView *)h->chunk, (int)h); }
    }
    *dst = v;
}

static inline char *descName(PoolDescRecord *r) { char *n = r->name; if (n != 0) { return n; } return ((char *)emptyString); }

igResult FUN_002f3910(PoolDescManager *self, int index, PoolDescRecord *desc, int build) {
    igResult result = g_resultSuccess;
    PoolDescSlot *slot;
    if (index == -1) {
        index = self->nextSlot;
        if (index < 46) {
            setDescString(&desc->alias, g_memoryContextNames[index]);
            self->nextSlot = self->nextSlot + 1;
        }
    } else if (index >= self->nextSlot) {
        self->nextSlot = index + 1;
    }
    if (index >= 0 && index < 46) {
        slot = (PoolDescSlot *)((char *)self + index * 0x90 + 0x14);
        strncpy(slot->name, descName(desc), 0x7f);
        slot->name[127] = 0;
        slot->record = ((PoolDescRecord *)FUN_002f8be0((igMemoryPoolContextInfo *)self->table, (int)(descName(desc))));
        if (slot->record == 0) { slot->record = ((PoolDescRecord *)FUN_002f8ca0((igMemoryPoolContextInfo *)self->table, desc->alias)); }
        if (slot->record == 0) {
            slot->record = (PoolDescRecord *)FUN_002bfed0((int)((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap)));
            FUN_002f8a80((void *)self->table, (void *)slot->record);
        }
        if (slot->record != desc) {
            { PoolDescRecord *d; char *src; src = desc->s24; d = slot->record; setDescString(&d->s24, src); }
            slot->record->a28 = desc->a28;
            slot->record->a32 = desc->a32;
            slot->record->a36 = desc->a36;
            { PoolDescRecord *d; char *src; src = desc->s40; d = slot->record; setDescString(&d->s40, src); }
            { PoolDescRecord *d; char *src; src = desc->s44; d = slot->record; setDescString(&d->s44, src); }
            { PoolDescRecord *d; char *src; src = desc->s48; d = slot->record; setDescString(&d->s48, src); }
            { PoolDescRecord *d; char *src; src = desc->s52; d = slot->record; setDescString(&d->s52, src); }
            { PoolDescRecord *d; char *src; src = desc->s56; d = slot->record; setDescString(&d->s56, src); }
            { PoolDescRecord *d; char *src; src = desc->s60; d = slot->record; setDescString(&d->s60, src); }
            { PoolDescRecord *d; char *src; src = desc->s64; d = slot->record; setDescString(&d->s64, src); }
            { PoolDescRecord *d; char *src; src = desc->s68; d = slot->record; setDescString(&d->s68, src); }
            { PoolDescRecord *d; char *src; src = desc->s72; d = slot->record; setDescString(&d->s72, src); }
            { PoolDescRecord *d; char *src; src = desc->s76; d = slot->record; setDescString(&d->s76, src); }
            slot->record->a80 = desc->a80;
        }
        if (build != 0) {
            if (self->build(index, 0) == g_resultFailure) { result = g_resultFailure; }
        }
    } else {
        result = g_resultFailure;
    }
    return result;
}

void FUN_002f4060(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 12) = arg1;
}

void FUN_002f4070(ContextView *self) {
    ContextRecord *record = self->records;
    for (int i = 0; i < 46; i++) {
        if (record->allocator != 0 && !((igMemoryPoolView *)record->allocator)->isActive()) {
            ((igMemoryPoolView *)record->allocator)->activate();
        }
        record++;
    }
    ((MemoryContext *)self)->setFlags(self->flags | 8);
}

void FUN_002f4110(MemoryContext *arg0) {
    igMemoryPoolView **p;
    int i;
    p = (igMemoryPoolView **)((char *)arg0 + 0x14);
    for (i = 0; i < 0x2E; i++) {
        igMemoryPoolView *o = *p;
        if (o != 0 && (((igObject *)o)->_refCount & 0x7FFFFF) == 1) {
            if (o->vfunc_47() != 0) {
                (*p)->vfunc_87(0);
            }
            (*p)->vfunc_32();
        }
        p = (igMemoryPoolView **)((char *)p + 0x90);
    }
    arg0->setFlags(arg0->flags & ~8);
}

void FUN_002f41e0(char *arg0) {
    igMemoryPoolView **p;
    int i;
    p = (igMemoryPoolView **)(arg0 + 20);
    i = 0;
    do {
        igMemoryPoolView *o = *p;
        if (o != 0) {
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 1) {
                o->vfunc_31();
            }
        }
        i++;
        p = (igMemoryPoolView **)((char *)p + 144);
    } while (i < 46);
}

void FUN_002f4250(void **arg0) {
    int var_s0;

    ((MemoryContext *)(arg0))->vfunc_49();
    ((MemoryContext *)(arg0))->vfunc_55();
    var_s0 = 0x2D;
    do {
        ((MemoryContext *)(arg0))->RemoveAllocator((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 20, 0, 0x19E0);
    ((MemoryContext *)(arg0))->InitializeRecordNames();
}

void FUN_002f42e0(void **arg0, int arg1) {
    memset((char *)arg0 + 0x14, 0, 0x19E0);
    ((MemoryContext *)(arg0))->InitializeRecordNames();
    Gap__Core__igObject__resetFields((int)arg0, arg1);
}

void FUN_002f4340(void **arg0) {
    int var_s0;

    Gap__Core__igObject__destructFields((int)arg0);
    var_s0 = 0x2D;
    do {
        ((MemoryContext *)(arg0))->RemoveAllocator((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 0x14, 0, 0x19E0);
}

static inline igMemoryPoolView *newLargePool() {
    void *p = FUN_002f0040(0xd0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((igMemoryPoolView *)FUN_0031eb90((igArenaMemoryPool *)p)); }
    return (igMemoryPoolView *)p;
}

static inline igMemoryPoolView *newSmallPool() {
    void *p = FUN_002f0040(0xa0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((igMemoryPoolView *)FUN_003235c0((igMallocMemoryPool *)p)); }
    return (igMemoryPoolView *)p;
}

void FUN_002f43a0(MemoryContext *self) {
    igMemoryPoolView *p;
    int i;
    FUN_002f86e0(self);
    i = 0;
    do {
        switch (i) {
        case 0:
            NEW_POOL(p)
            break;
        case 4: case 5: case 6:
            if (g_useOwnerAllocator != 0) { p = (igMemoryPoolView *)self->records[0].allocator; } else { NEW_POOL(p) }
            break;
        default:
            p = (igMemoryPoolView *)self->records[0].allocator;
            break;
        }
        *(igMemoryPoolView **)((char *)self + i * 144 + 20) = p;
        if (g_useOwnerAllocator != 0) {
            switch (i) {
            case 0:
                p->vfunc_97();
                if (DAT_00586fd8[0] != 0) { p->vfunc_43(DAT_00586fd8[0]); }
                p->activate();
                ((ObjectSystemView *)(*(void * *)g_objectSystem))->bootstrapPool = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                ((ObjectSystemView *)(*(void * *)g_objectSystem))->systemPool = p;
                break;
            }
        } else {
            switch (i) {
            case 0:
                p->vfunc_97();
                if (DAT_00586fd8[0] != 0) { p->vfunc_43(DAT_00586fd8[0]); }
                p->activate();
                ((ObjectSystemView *)(*(void * *)g_objectSystem))->bootstrapPool = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                ((ObjectSystemView *)(*(void * *)g_objectSystem))->systemPool = p;
                p->vfunc_97();
                if (DAT_00586fe0[0] != 0) { p->vfunc_43(DAT_00586fe0[0]); }
                FUN_002f0370((void **)p);
                p->activate();
                break;
            case 5:
                p->vfunc_97();
                if (DAT_00586fe8[0] != 0) { p->vfunc_43(DAT_00586fe8[0]); }
                FUN_002f0370((void **)p);
                p->activate();
                break;
            case 6:
                p->vfunc_97();
                if (DAT_00586ff0[0] != 0) { p->vfunc_43(DAT_00586ff0[0]); }
                FUN_002f0370((void **)p);
                p->activate();
                break;
            }
        }
        i++;
        ((igObject *)p)->_refCount = ((igObject *)p)->_refCount + 1;
    } while (i < 46);
}

void FUN_002f48c0(void) {

}

void FUN_002f48d0(char *arg0) {
    int i;
    igMemoryPoolView *obj;
    igMemoryPoolView ***pp;
    void *ent;

    while (D_00587010[0] > 1) {
        FUN_002f8760();
    }
    *(int *)((char *)(*(void * *)g_objectSystem) + 52) = 0;
    i = 6;
    if (g_useOwnerAllocator == 0) {
        do {
            pp = (igMemoryPoolView ***)(arg0 + i * 0x90 + 20);
            obj = (igMemoryPoolView *)*pp;
            if (obj != 0) {
                FUN_002f0460((void **)obj);
                obj->vfunc_98();
                thunk_free_2((int)obj);
                *pp = 0;
            }
            i--;
        } while (i > 0);
    }
    ent = *(void **)(arg0 + 20);
    Memory_ShutdownAllocatorRegistries((void **)ent);
    while (D_00587010[0] > 0) {
        FUN_002f8760();
    }
    *(int *)((char *)(*(void * *)g_objectSystem) + 48) = 0;
    thunk_free_2((int)ent);
}

/* IgMemoryPoolContextInfo slot 180: write the 46 original context names (Bootstrap, Default,
 * Current, NonTracked, ...) into the name field of each 144-byte context record. Each name is
 * copied with a 127-character limit and the 128th byte is cleared explicitly. Called by the
 * constructor and the destructor. strncpy is a strncpy-like bounded string copy (dest, source,
 * limit). */
void igMemoryPoolContextInfo_InitializeRecordNames(igMemoryPoolContextInfo *self) {
    int index;
    ContextPrefixedRecord *entry;

    index = 0;
    do {
        entry = (ContextPrefixedRecord *)((char *)self + index * sizeof(ContextRecord));
        strncpy(entry->record.name, g_memoryContextNames[index], CONTEXT_NAME_LIMIT);
        index += 1;
        entry->record.name[CONTEXT_NAME_LIMIT] = 0;
    } while (index < CONTEXT_RECORD_COUNT);
}

igResult FUN_002f4a60(PoolConfigManager *self) {
    unsigned char useFlag;
    unsigned char lockFlag;
    unsigned char optFlag;
    int options;
    int optB;
    int optC;
    int mainSize;
    int nextSize;
    PoolConfigObject *mainPool;
    int i;
    int config;
    PoolConfigObject *o;
    PoolConfigObject *second;
    config = ((PoolConfigContext *)g_objectSystem[0])->config;
    mainPool = ((PoolConfigContext *)g_objectSystem[0])->main;
    second = ((PoolConfigContext *)g_objectSystem[0])->second;
    options = DAT_004c2370[0];
    mainSize = 0;
    nextSize = 0;
    optB = DAT_004c2368[0];
    optC = DAT_005871f8[0];
    igResult result = g_resultSuccess;
    useFlag = (self->flags & 4) != 0;
    lockFlag = GPR_00554994;
    FUN_003065f0(config, 2, text_bootstrapPoolPreSize, &mainSize, 0, 0);
    if (mainSize > 0) { mainPool->setName(mainSize); }
    FUN_00306e50(config, 2, text_updatePoolStatistics, (char *)&lockFlag, lockFlag, 0);
    GPR_00554994 = lockFlag;
    FUN_00306e50(config, 2, text_useAliasMemoryPoolRelease, (char *)&useFlag, useFlag, 0);
    self->setFlags(useFlag != 0 ? self->flags | 4 : self->flags & ~4);
    FUN_00307550(config, 2, text_arenaMemoryPoolOptionFlagsReleas, FUN_002cd990(), &options, DAT_004c2370[0], 0);
    FUN_00307470(config, 2, text_arenaMemoryPoolMessageLevelRelea, FUN_002cd9f0(), &optB, DAT_004c2368[0], 0);
    FUN_00307470(config, 2, text_arenaMemoryPoolHeapIntegrityChec, FUN_002cda50(), &optC, DAT_005871f8[0], 0);
    {
        int v = (options & 0x200) != 0;
        optFlag = v;
        FUN_00306e50(config, 2, text_inhibitArenaCountMessage, (char *)&optFlag, v, 0);
    }
    if (optFlag != 0) { options |= 0x200; }
    DAT_004c2370[0] = options;
    DAT_004c2368[0] = optB;
    DAT_005871f8[0] = optC;
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && igObject_IsKindOf(o, g_igArenaMemoryPool_metaObject[0]) != 0) {
            igArenaMemoryPool_SetPoolOptionFlags((SetFlagsPool *)o, (options & ~1) | (o->options & 1));
        }
    }
    FUN_003065f0(config, 2, text_nonTrackedPoolPreSize, &nextSize, 0, 0);
    PoolConfigManager *top = (PoolConfigManager *)(*(void **)DAT_00586fd0);
    PoolConfigObject *fb = self->fallback;
    if (self == top && fb == mainPool) {
        o = (PoolConfigObject *)FUN_002cdab0((int)mainPool);
        if (nextSize > 0) { o->setName(nextSize); }
        o->finish();
        self->setPool(3, o);
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)(int)o->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o);
    }
    if (self->readConfig(config, (int)DAT_004c2228[0]) == g_resultFailure) { result = g_resultFailure; }
    if (self->setDefault(self->defaultSize, 0) == g_resultFailure) { result = g_resultFailure; }
    if (self->apply() == g_resultFailure) { result = g_resultFailure; }
    if (g_useOwnerAllocator == 0) {
        for (i = 0; i < 46; i++) {
            if (i != 0) {
                PoolConfigObject **slot = (PoolConfigObject **)((char *)self + i * 144 + 20);
                PoolConfigObject *p = *slot;
                if (p == mainPool) {
                    p->rc = p->rc - 1;
                    if (((unsigned long long)((long long)(int)p->rc << 0x29) >> 0x29) == 0) igObject_Destroy(p);
                    *slot = 0;
                }
            }
        }
        for (i = 0; i < 46; i++) {
            if (i == 2) {
                self->setPool(i, self->third);
            } else {
                if (self->build(i, 0) == g_resultFailure) { result = g_resultFailure; }
            }
        }
    } else {
        self->setPool(2, self->third);
    }
    self->finish();
    o = self->poolFor(20);
    if (o != mainPool && o != second) { ((PoolConfigContext *)g_objectSystem[0])->a88 = o; }
    o = self->poolFor(7);
    if (o != mainPool && o != second) { ((PoolConfigContext *)g_objectSystem[0])->a96 = o; }
    for (i = 0; i < 46; i++) {
        o = *(PoolConfigObject **)((char *)self + i * 144 + 20);
        if (o != 0 && o->inUse() == 0) { o->finish(); }
    }
    if (DAT_004c2370[0] & 8) {
        mainPool->lock(1);
        if (second != mainPool) { second->lock(1); }
    }
    if (result == g_resultSuccess) { self->setFlags(self->flags | 8); }
    return result;
}

/* The skip list 6/5/4/0 is a switch, which leaves the compare-chain delay slots empty. The second
 * loop is dead code and is kept. */
void FUN_002f50e0(MemoryContext *arg0) {
    int s0;
    igMemoryPoolView *p;
    igMetaObject *c;
    arg0->vfunc_49();
    if ((void *)arg0 == (*(void * *)DAT_00586fd0)) {
        FUN_002f00f0((void *)0);
    }
    arg0->vfunc_55();
    if (*(unsigned char *)((char *)(*(void * *)g_objectSystem) + 119) != 0) {
        arg0->vfunc_66(0);
    }
    s0 = 45;
    do {
        p = *(igMemoryPoolView **)((char *)arg0 + s0 * 144 + 20);
        switch (s0) {
        case 0: case 4: case 5: case 6:
            break;
        default:
            if (p != 0) {
                arg0->RemoveAllocator(s0);
            }
        }
        s0--;
    } while (s0 >= 0);
    while (s0 >= 0) {
        p = *(igMemoryPoolView **)((char *)arg0 + s0 * 144 + 20);
        if (p != 0) {
            c = p->getMeta();
            c->_instanceCount = c->_instanceCount - 1;
        }
        s0--;
    }
}

igMetaObject *FUN_002f5220(void) {
    return g_igMemoryPool_metaObject[0];
}

static inline void releaseTable(PoolDescTable *t) {
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)(int)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
}

void FUN_002f5230(int *out, PoolDescSetup *self, int config, char *name) {
    int defaultSize;
    int systemSize;
    int scratchSize;
    int driverSize;
    char buf[256];
    int i;
    PoolDescRecord *rec;
    PoolDescSlot *slot;
    int ctxConfig;
    ctxConfig = ((PoolDescContext *)(*(void * *)g_objectSystem))->config;
    slot = self->slots;
    if (self->table != 0) {
        FUN_002f8b20(self->table);
        releaseTable(self->table);
        self->table = 0;
    }
    {
        int alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap);
        releaseTable(self->table);
        self->table = (PoolDescTable *)FUN_002c01f0(alloc);
    }
    i = 0;
    do {
        rec = (PoolDescRecord *)FUN_002bfed0((int)((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap)));
        igNamedObject_SetName((igNamedObject *)rec, (int)(self->recordName(i)));
        setDescString(&rec->alias, g_memoryContextNames[i]);
        switch (i) {
        case 0:
            if (rec->s60 != 0 && *rec->s60 != 0) {
                strncpy(buf, rec->s60, 255);
                buf[255] = 0;
            } else {
                buf[0] = 0;
            }
            if (strstr(buf, text_InhibitEventTracker) == 0 && strstr(buf, text_UseEventTracker) == 0) {
                if (buf[0] != 0) {
                    __memcpy(buf, (void *)" | InhibitEventTracker", 23);
                } else {
                    strncpy(buf, text_InhibitEventTracker, 255);
                }
                setDescString(&rec->s60, buf);
            }
            break;
        case 1:
            if (self == (*(void * *)DAT_00586fd0)) {
                defaultSize = 0;
                FUN_003065f0(config, 2, text_defaultPoolPreSize, &defaultSize, 0, 0);
                if (defaultSize > 0) {
                    rec->a28 = defaultSize;
                    char *n = DAT_00586de8;
                    if (n != 0) { setDescString(&rec->s40, n); }
                }
            }
            break;
        case 2:
            break;
        case 4:
            if (self == (*(void * *)DAT_00586fd0)) {
                systemSize = 0;
                FUN_003065f0(config, 2, text_systemPoolPreSize, &systemSize, 0, 0);
                if (systemSize > 0) {
                    rec->a28 = systemSize;
                    char *n = DAT_00586de8;
                    if (n != 0) { setDescString(&rec->s40, n); }
                }
            }
            break;
        case 5:
        case 6:
            break;
        case 7:
            FUN_003065f0(ctxConfig, 2, text_scratchPoolSize, &scratchSize, 0, 0);
            FUN_003065f0(ctxConfig, 2, text_scratchPadPoolSize, &scratchSize, scratchSize, 0);
            if (scratchSize != 0) {
                if (scratchSize > 16384) { scratchSize = 16384; }
                rec->a36 = 0x70000000;
                rec->a28 = 16384;
                setDescString(&rec->s44, text_Fixed);
                setDescString(&rec->s48, text_HighSpeed);
                rec->a28 = scratchSize;
            } else {
                setDescString(&rec->s24, g_memoryContextNames[1]);
            }
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, text_OnDemand); }
            break;
        case 20:
            if (self == (*(void * *)DAT_00586fd0)) {
                driverSize = 0;
                FUN_003065f0(config, 2, text_driverPoolSize, &driverSize, 0, 0);
                if (driverSize != 0) {
                    rec = self->slots[20].record;
                    rec->a28 = driverSize;
                } else {
                    setDescString(&rec->s24, g_memoryContextNames[1]);
                }
            } else {
                setDescString(&rec->s24, g_memoryContextNames[1]);
            }
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, text_OnDemand); }
            break;
        default:
            if (rec->s52 == 0 || *rec->s52 == 0) { setDescString(&rec->s52, text_OnDemand); }
            setDescString(&rec->s24, g_memoryContextNames[1]);
            break;
        }
        FUN_002f8a80(self->table, rec);
        i++;
        slot->record = rec;
        slot++;
    } while (i < 30);
    if (config != 0 && name != 0 && *name != 0) {
        self->table->load(config, name);
    }
    *out = g_resultSuccess.v;
}

void FUN_002f5c30(void *arg0) {
    MemoryContext *t = (MemoryContext *)arg0;
    ContextRecord *s;
    igMemoryPoolContextInfoView *o;
    s = &t->records[0];
    goto set;
back:
    if (t->contextInfo != 0) {
        FUN_002f8b20(t->contextInfo);
        o = t->contextInfo;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        t->contextInfo = 0;
    }
    return;
set:
    s->descriptor = 0;
    goto back;
}

void FUN_002f5cc0(int *arg0) {
    *arg0 = g_resultSuccess.v;
}

void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag) {
    MemoryContext *ctx = (MemoryContext *)arg1;
    igResult r0, r1, r2, r3, r4, r5, r6, r7;
    igMemoryPool *obj;
    int meta;
    ContextRecord *slot;
    igMemoryPool *allocA;
    igMemoryPoolInfo *cfg;
    int al;
    int aligned;
    igMemoryPool *mbc;
    char *sub;
    igMemoryPool *allocB;
    void **pslot;
    bool owned;
    igMemoryPool *a;
    slot = &ctx->records[idx];
    meta = (int)g_igArenaMemoryPool_metaObject[0];
    allocA = (igMemoryPool *)ctx->records[0].allocator;
    allocB = (igMemoryPool *)ctx->records[1].allocator;
    mbc = (igMemoryPool *)ctx->records[3].allocator;
    cfg = (igMemoryPoolInfo *)slot->descriptor;
    owned = true;
    obj = (igMemoryPool *)slot->allocator;
    if (allocA == 0) allocA = ((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    if (allocB == 0) {
        allocB = ((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault));
        if (allocB == 0) allocB = allocA;
    }
    if (mbc == 0) Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked);
    if (idx == 2) {
        slot->allocator = allocB;
        allocB->_refCount = allocB->_refCount + 1;
    }
    if (cfg == 0) {
        if (idx >= 30) { *out = g_resultSuccess.v; return; }
        *out = g_resultFailure.v;
        return;
    }
    if (cfg->_scope != 0) {
        slot->flags = 0;
        if (strstr((char *)cfg->_scope, text_LongTerm) == 0) {
            if (strstr((char *)cfg->_scope, text_Level) != 0) slot->flags = slot->flags | 1;
            else if (strstr((char *)cfg->_scope, text_Frame) != 0) slot->flags = slot->flags | 2;
        }
        if (strstr((char *)cfg->_scope, text_Create) != 0) slot->flags = slot->flags | 0x01000000;
        if (strstr((char *)cfg->_scope, text_Reset) != 0) slot->flags = slot->flags | 0x02000000;
        if (strstr((char *)cfg->_scope, text_OnDemand) != 0) slot->flags = slot->flags | 0x04000000;
        if (flag == 0) {
            int f = slot->flags;
            if ((((unsigned long long)((long long)f << 0x28)) >> 0x28) != 0 && (f & 0x05000000) != 0) {
                *out = g_resultSuccess.v;
                return;
            }
        }
    }
    if (obj != 0) {
        int size = cfg->_size;
        if (size != 0 && (cfg->_arenaType == 0 || strcmp((char *)cfg->_arenaType, text_Dynamic) == 0)) {
            r0 = ((igMemoryPoolView *)obj)->vfunc_43(size);
        }
    } else {
        char *name = (char *)cfg->_aliasedTo;
        if (name != 0 && *name != 0) {
            int j = ctx->vfunc_29((int)name);
            obj = 0;
            if (j != -1) {
                ContextRecord *o = (ContextRecord *)((char *)(j * 144) + (int)ctx + 20);
                pslot = &o->allocator;
                obj = (igMemoryPool *)o->allocator;
                if (obj == 0) {
                    if (ctx->BuildAllocator(j, flag) != g_resultSuccess) { *out = g_resultFailure.v; return; }
                    obj = (igMemoryPool *)*pslot;
                }
            }
            if (obj != 0) {
                int refMode = !!(ctx->flags & 4);
                if (refMode) {
                    if (cfg->_scope != 0) {
                        if ((strstr((char *)cfg->_scope, text_OnDemand) != 0 || strstr((char *)cfg->_scope, ONDEMAND) != 0 || strstr((char *)cfg->_scope, text_ondemand) != 0) && flag == 0) {
                            *out = g_resultSuccess.v;
                            return;
                        }
                    }
                    if (idx == 5) {
                        if (((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)) == 0) ctx->records[5].allocator = allocA;
                    }
                    {
                        igMemoryPool *old = obj;
                        obj = ((igMemoryPool *)igAliasMemoryPool_Create((void *)allocA));
                        ((igAliasMemoryPoolView *)obj)->vfunc_100(old);
                    }
                    if (idx == 5 && ctx->records[5].allocator == allocA) ctx->records[5].allocator = 0;
                } else {
                    owned = false;
                }
                ctx->vfunc_25(idx, (igObject *)obj);
                if (owned) {
                    obj->_refCount = obj->_refCount - 1;
                    if (RC(obj) == 0) igObject_Destroy(obj);
                }
                if (((igMemoryPoolView *)obj)->isActive() == 0) ((igMemoryPoolView *)obj)->activate();
                *out = g_resultSuccess.v;
                return;
            }
        }
    {
        char *mname = (char *)cfg->_class;
        if (mname != 0 && *mname != 0) {
            int m = igObjectSystem_FindMetaByNameDefault((const char *)mname);
            meta = m;
            if (m == 0) meta = (int)g_igArenaMemoryPool_metaObject[0];
        }
    }
    {
        obj = ((igMemoryPool *)igMetaObject_CreateInstance((CreateMeta *)meta, (MemoryPool *)allocA));
        igMemoryPool *o2 = obj;
        int size = cfg->_size;
        al = size + (g_activeSystemAllocator[0]->vfunc_21() - 1);
        aligned = al & ~(g_activeSystemAllocator[0]->vfunc_21() - 1);
        if (size != 0) {
            char *kind = (char *)cfg->_arenaType;
            if (kind == 0 || strcmp(kind, text_Dynamic) == 0) {
                r2 = ((igMemoryPoolView *)o2)->vfunc_43(size);
            } else if (strcmp((char *)cfg->_arenaType, text_Fixed) == 0) {
                sub = (char *)cfg->_source;
                if (sub == 0 || *sub == 0) { a = allocB; goto common; }
                if (strcmp(sub, text_SystemMemory) == 0) {
b78:
                    int v = g_activeSystemAllocator[0]->vfunc_17(0, aligned);
                    r3 = ((igMemoryPoolView *)o2)->vfunc_24(v, aligned, 0);
                    slot->storageFlags = slot->storageFlags | 2;
                } else if (strcmp(sub, text_Low) == 0 || strcmp(sub, text_High) == 0 || strcmp(sub, text_Virtual) == 0) {
                    goto b78;
                } else if (strcmp(sub, text_HighSpeed) == 0) {
                    int dfl = cfg->_address;
                    int a2;
                    if (dfl != 0) a2 = dfl;
                    else a2 = 0x70000000;
                    r4 = ((igMemoryPoolView *)o2)->vfunc_24(a2, (long long)size, 0);
                } else if (strcmp(sub, text_Raw) != 0 && strcmp(sub, text_Custom) != 0) {
                    a = (igMemoryPool *)ctx->getAllocatorByName((int)sub);
                    if (a == 0) a = allocB;
common:
                    if (((igMemoryPoolView *)a)->isActive() == 0) ((igMemoryPoolView *)a)->activate();
                    r5 = ((igMemoryPoolView *)o2)->vfunc_24((int)((igMemoryPoolView *)a)->Allocate(size), (long long)size, 1);
                    a->_refCount = a->_refCount + 1;
                    slot->storageFlags = slot->storageFlags | 1;
                }
            }
        }
        r6 = ((igMemoryPoolView *)o2)->vfunc_45(cfg);
        ctx->vfunc_25(idx, (igObject *)o2);
        o2->_refCount = o2->_refCount - 1;
        if (RC(o2) == 0) igObject_Destroy(o2);
    }
    }
    if (((igMemoryPoolView *)obj)->isActive() == 0) ((igMemoryPoolView *)obj)->activate();
    *out = g_resultSuccess.v;
}

void MemoryContext_BuildAndAttachEventTracker(igResult *out, MemoryContext *self, int idx) {
    void *ty;
    igMemoryPoolView *trk;
    igEventTrackerView *o2;
    igMemoryPoolInfo **ps2;
    igEventTrackerView *o;
    int tv;
    igMemoryPoolInfo **ps;
    igResult t = self->BuildAllocator(idx, 1); tv = t.v;
    int off = idx * 0x90; ContextPrefixedRecord *slot = (ContextPrefixedRecord *)(off + (int)self);
    trk = (igMemoryPoolView *)slot->record.allocator;
    /* +12 of the context is igInfo::_directory in reflection but is read here as a flag word. The second flag test below stays on MemoryContext::flags: typing both makes MWCC hoist the member address into a saved register. */
    int h1 = (((igMemoryPoolContextInfo *)self)->_directory & 1) != 0;
    if (h1) {
        ty = 0;
        ps = (igMemoryPoolInfo **)&slot->record.descriptor; igMemoryPoolInfo *sub = *ps;
        if (sub != 0) ty = (void *)sub->_releaseOptions;
        if (ty == 0 || strstr(ty, &text_InhibitEventTracker[0]) == 0) {
            int h2 = (self->flags & 2) != 0;
            if ((h2 && idx != 1) || (ty != 0 && strstr(ty, &text_UseEventTracker[0]) != 0)) {
                o = (igEventTrackerView *)FUN_002c5780((int)(self->getAllocatorBySelector(3)));
                void *b = ((ObjectSystemView *)(*(void * *)g_objectSystem))->eventTrackerInitialCapacity;
                void *f = (void *)(*ps)->_eventTrackerCapacity;
                if (f != 0) b = f;
                FUN_002dcc40((int)o, (int)b);
                o->vfunc_23();
                trk->vfunc_90(o);
                ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
                if (RC2(o) == 0) igObject_Destroy(o);
            } else {
                void *x = self->getAllocatorBySelector(1)->getEventTracker();
                if (x != 0) trk->vfunc_90(x);
            }
        }
    } else {
        void *ty2 = 0;
        ps2 = (igMemoryPoolInfo **)&slot->record.descriptor; igMemoryPoolInfo *sub2 = *ps2;
        if (sub2 != 0) ty2 = (void *)sub2->_releaseOptions;
        if (ty2 != 0 && strstr(ty2, &text_UseEventTracker[0]) != 0) {
            o2 = (igEventTrackerView *)FUN_002c5780((int)(self->getAllocatorBySelector(3)));
            void *b2 = ((ObjectSystemView *)(*(void * *)g_objectSystem))->eventTrackerInitialCapacity;
            void *f2 = (void *)(*ps2)->_eventTrackerCapacity;
            if (f2 != 0) b2 = f2;
            FUN_002dcc40((int)o2, (int)b2);
            o2->vfunc_23();
            trk->vfunc_90(o2);
            ((igObject *)o2)->_refCount = ((igObject *)o2)->_refCount - 1;
            if (RC2(o2) == 0) igObject_Destroy(o2);
        }
    }
    out->v = tv;
}

void MemoryContext_RemoveAllocator(void *arg0, int arg1) {
    igResult sp6C, sp68, sp64;
    if (arg1 >= 0 && arg1 < 0x2E) {
        Obj6 *o = *(Obj6 **)((char *)arg0 + arg1 * 0x90 + 20);
        ContextRecord *slot = (ContextRecord *)((char *)arg0 + arg1 * 0x90 + 20);
        if (o != 0) {
            slot->allocator = 0;
            if (RC(o) == 1) {
                if (((igMemoryPoolView *)o)->vfunc_47() != 0) {
                    ((igMemoryPoolView *)o)->vfunc_87(0);
                }
                ((igMemoryPoolView *)o)->vfunc_32();
                {
                    int fl = slot->storageFlags;
                    if (fl & 1) {
                        int a;
                        slot->storageFlags = fl & ~1;
                        a = ((igMemoryPoolView *)o)->vfunc_26(fl);
                        if (a != 0) {
                            void *own;
                            sp6C = ((igMemoryPoolView *)o)->vfunc_24(0, 0, 0);
                            own = Memory_FindOwningAllocator(a);
                            if (own != 0) {
                                Obj6 *ob = (Obj6 *)own;
                                ob->_refCount = ob->_refCount - 1;
                                if (RC(ob) == 0) igObject_Destroy(ob);
                                Memory_FreeBuffer((void *)a);
                            }
                        }
                    } else if (fl & 2) {
                        int a;
                        slot->storageFlags = fl & ~2;
                        a = ((igMemoryPoolView *)o)->vfunc_26(fl);
                        if (a != 0) {
                            long long b = (long long)((igMemoryPoolView *)o)->vfunc_36();
                            sp68 = ((igMemoryPoolView *)o)->vfunc_24(0, 0, 0);
                            sp64 = g_activeSystemAllocator[0]->vfunc_18(a, b);
                        }
                    }
                }
            }
            o->_refCount = o->_refCount - 1;
            if (RC(o) == 0) igObject_Destroy(o);
            { MemoryContext *c = (MemoryContext *)arg0; if (arg1 == c->usedRecords + 1) c->usedRecords = arg1; }
        }
    }
}

static inline int trackerSizeFor(igMemoryPoolInfo *record, int fallback) {
    int size = fallback;
    int n = record->_eventTrackerCapacity;
    if (n != 0) { size = n; }
    return size;
}

void FUN_002f69b0(MemoryContext *self) {
    int registry = ((ObjectSystemView *)g_objectSystem[0])->getConfigRegistry();
    igMemoryPoolView *mainPool = ((ObjectSystemView *)g_objectSystem[0])->bootstrapPool;
    igMemoryPoolView *secondPool = ((ObjectSystemView *)g_objectSystem[0])->getSystemPool();
    int alloc = FUN_002f00e0();
    int globalTrackerByDefault = (self->flags & 1) != 0;
    unsigned char useGlobalEventTracker = globalTrackerByDefault;
    unsigned char useSeparateEventTrackers = (self->flags & 2) != 0;
    unsigned char showLeaksOnExit;
    unsigned char saveEventTrackerOnExit;
    unsigned char showMemoryStatisticsOnExit;
    unsigned char showObjectStatisticsOnExit;
    StringRef memoryEventFormat;
    StringRef markerEventFormat;
    StringRef notificationEventFormat;
    StringRef eventTrackerFileName;
    StringRef symbolsFileName;
    int initialCapacity;
    int scopeFlags;
    int eventTypeFilter;
    int markerTypeFilter;
    int notificationTypeFilter;
    int notificationCodeFilter;
    StringRef systemPoolEventTrackerFileName;
    FUN_00306e50(registry, 2, text_useGlobalEventTracker, (char *)&useGlobalEventTracker, globalTrackerByDefault, 0);
    self->setFlags(useGlobalEventTracker ? self->flags | 1 : self->flags & ~1);
    ((ObjectSystemView *)g_objectSystem[0])->useGlobalEventTracker = useGlobalEventTracker;
    FUN_00306e50(registry, 2, text_useSeparateEventTrackers, (char *)&useSeparateEventTrackers, useSeparateEventTrackers, 0);
    self->setFlags(useSeparateEventTrackers ? self->flags | 2 : self->flags & ~2);
    FUN_00306e50(registry, 2, text_showLeaksOnExit, (char *)&showLeaksOnExit, 0, 0);
    ((ObjectSystemView *)g_objectSystem[0])->showLeaksOnExit = showLeaksOnExit;
    FUN_00306e50(registry, 2, text_showMemoryStatisticsOnExit, (char *)&showMemoryStatisticsOnExit, 0, 0);
    ((ObjectSystemView *)g_objectSystem[0])->showMemoryStatisticsOnExit = showMemoryStatisticsOnExit;
    FUN_00306e50(registry, 2, text_showObjectStatisticsOnExit, (char *)&showObjectStatisticsOnExit, 0, 0);
    ((ObjectSystemView *)g_objectSystem[0])->showObjectStatisticsOnExit = showObjectStatisticsOnExit;
    FUN_003065f0(registry, 2, text_eventTrackerInitialCapacity, &initialCapacity, 0x80000, 0);
    ((ObjectSystemView *)g_objectSystem[0])->eventTrackerInitialCapacity = (void *)initialCapacity;
    FUN_003065f0(registry, 2, text_eventTrackerEventTypeFilter, &eventTypeFilter, -1, 0);
    ((ObjectSystemView *)g_objectSystem[0])->eventTrackerEventTypeFilter = eventTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerMarkerTypeFilter, &markerTypeFilter, -1, 0);
    ((ObjectSystemView *)g_objectSystem[0])->eventTrackerMarkerTypeFilter = markerTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerMaxCallStackDepth, &DAT_004c1eb0, DAT_004c1eb0, 0);
    FUN_003065f0(registry, 2, text_eventTrackerNotificationTypeFilt, &notificationTypeFilter, -1, 0);
    ((ObjectSystemView *)g_objectSystem[0])->eventTrackerNotificationTypeFilter = notificationTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerNotificationCodeFilt, &notificationCodeFilter, -1, 0);
    ((ObjectSystemView *)g_objectSystem[0])->eventTrackerNotificationCodeFilter = notificationCodeFilter;
    FUN_00306910(registry, 2, text_memoryEventFormat, (int **)&memoryEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d31d0((ObjectSystemView *)g_objectSystem[0], (char *)memoryEventFormat.p);
    FUN_00306910(registry, 2, text_markerEventFormat, (int **)&markerEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d3240((ObjectSystemView *)g_objectSystem[0], (char *)markerEventFormat.p);
    FUN_00306910(registry, 2, text_notificationEventFormat, (int **)&notificationEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d32b0((ObjectSystemView *)g_objectSystem[0], (char *)notificationEventFormat.p);
    FUN_003065f0(registry, 2, text_eventTrackerScopeFlags, &scopeFlags, -1, 0);
    FUN_002f0db0(scopeFlags);
    FUN_00306e50(registry, 2, text_saveEventTrackerOnExit, (char *)&saveEventTrackerOnExit, 0, 0);
    ((ObjectSystemView *)g_objectSystem[0])->saveEventTrackerOnExit = saveEventTrackerOnExit;
    FUN_00306910(registry, 2, text_eventTrackerFileName, (int **)&eventTrackerFileName, (char *)DAT_004f7910, 0);
    FUN_002d3320((char *)g_objectSystem[0], (char *)eventTrackerFileName.p);
    FUN_00306910(registry, 2, text_systemPoolEventTrackerFileName, (int **)&systemPoolEventTrackerFileName, (char *)DAT_004f7910, 0);
    FUN_002d3370((char *)g_objectSystem[0], (char *)systemPoolEventTrackerFileName.p);
    FUN_00306910(registry, 2, text_symbolsFileName, (int **)&symbolsFileName, (char *)DAT_004f7910, 0);
    FUN_002d33c0(g_objectSystem[0], (int)symbolsFileName.p);
    if (symbolsFileName.p != 0 && *symbolsFileName.p != 0) {
        ElfFileView *loader = (ElfFileView *)FUN_002cec00(alloc);
        igSymbolTable *loaded = (igSymbolTable *)FUN_002b8500(alloc);
        if (loader != 0) {
            if (loader->Open((char *)symbolsFileName.p) == g_resultSuccess) {
                if (loader->vfunc_28(loaded, 1) == g_resultFailure) {
                    loaded->_refCount = loaded->_refCount - 1;
                    if (((unsigned long long)((long long)(int)loaded->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(loaded);
                    loaded = 0;
                }
                unsigned char showSectionHeaders = 0;
                FUN_00306e50(registry, 2, text_showSectionHeaders, (char *)&showSectionHeaders, 0, 0);
                if (showSectionHeaders != 0) { loader->PrintSectionHeaders(); }
                unsigned char showSymbols = 0;
                FUN_00306e50(registry, 2, text_showSymbols, (char *)&showSymbols, 0, 0);
                if (showSymbols != 0) { loader->PrintSymbols(); }
                loader->Close();
            }
            loader->refCount = loader->refCount - 1;
            if (((unsigned long long)((long long)(int)loader->refCount << 0x29) >> 0x29) == 0) igObject_Destroy(loader);
        }
        ((ObjectSystemView *)g_objectSystem[0])->symbolTable = loaded;
    }
    if (useGlobalEventTracker != 0) {
        igEventTrackerView *tracker = (igEventTrackerView *)FUN_002c5780(alloc);
        FUN_002dcc40((int)tracker, initialCapacity);
        tracker->vfunc_23();
        tracker->_detachAllocationsCounter = tracker->_detachAllocationsCounter + 1;
        if (*systemPoolEventTrackerFileName.p != 0) {
            if (secondPool != mainPool) {
                igEventTrackerView *own = (igEventTrackerView *)FUN_002c5780(alloc);
                FUN_002dcc40((int)own, 0x6000);
                own->vfunc_23();
                secondPool->vfunc_90(own);
                own->_refCount = own->_refCount - 1;
                if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
            }
        }
        for (int i = 0; i < 46; i++) {
            if (i != 3) {
                igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
                char *options = 0;
                if (self->records[i].descriptor != 0) { options = (char *)self->records[i].descriptor->_releaseOptions; }
                if (pool != 0 && pool->getEventTracker() == 0 && (options == 0 || strstr(options, text_InhibitEventTracker) == 0)) {
                    if ((useSeparateEventTrackers != 0 && i != 1) || (options != 0 && strstr(options, text_UseEventTracker) != 0)) {
                        igEventTrackerView *own = (igEventTrackerView *)FUN_002c5780(alloc);
                        FUN_002dcc40((int)own, trackerSizeFor(self->records[i].descriptor, initialCapacity));
                        own->vfunc_23();
                        pool->vfunc_90(own);
                        own->_refCount = own->_refCount - 1;
                        if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
                    } else {
                        pool->vfunc_90(tracker);
                    }
                }
            }
        }
        tracker->_detachAllocationsCounter = tracker->_detachAllocationsCounter - 1;
        if ((long long)((unsigned long long)((long long)(int)tracker->_refCount << 0x29) >> 0x29) > 1) {
            ((ObjectSystemView *)g_objectSystem[0])->globalEventTracker = tracker;
        } else {
            tracker->_refCount = tracker->_refCount - 1;
            if (((unsigned long long)((long long)(int)tracker->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(tracker);
        }
    } else {
        for (int i = 0; i < 46; i++) {
            if (i != 3) {
                igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
                char *options = 0;
                if (self->records[i].descriptor != 0) { options = (char *)self->records[i].descriptor->_releaseOptions; }
                if (pool != 0 && pool->getEventTracker() == 0 && options != 0 && strstr(options, text_UseEventTracker) != 0) {
                    igEventTrackerView *own = (igEventTrackerView *)FUN_002c5780(alloc);
                    FUN_002dcc40((int)own, trackerSizeFor(self->records[i].descriptor, initialCapacity));
                    own->vfunc_23();
                    pool->vfunc_90(own);
                    own->_refCount = own->_refCount - 1;
                    if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
                }
            }
        }
    }
}

static inline void releaseString_2f25d0(char *p) {
    if (p != 0) {
        StringHeader *h = (StringHeader *)(p - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunkOwnerView *)h->chunk, (int)h); }
    }
}

void FUN_002f7410(int arg0, int arg1) {
    strcmp(*(int *)((char *)(arg0) + 0), *(int *)((char *)(arg1) + 0));
}

void FUN_002f7420(ContextRecordStride *self) {
    int sizeA;
    int sizeB;
    int sizeC;
    int sizeD;
    int total;
    int f;
    int g;
    int h;
    int i2;
    int j2;
    int k2;
    int l2;
    int m2;
    char line[140];
    int counts[32];
    char type[80];
    igEventTrackerView *tracker = ((ObjectSystemView *)(*(void * *)g_objectSystem))->globalEventTracker;
    int i;
    if (tracker != 0) {
        if (((ObjectSystemView *)(*(void * *)g_objectSystem))->showObjectStatisticsOnExit != 0) {
            int n;
            int names;
            int k;
            int it;
            int bytes;
            int *list;
            names = tracker->_classNames;
            if (names != 0) {
                n = FUN_0030d080((CountOwner *)names);
                bytes = n * 4;
                it = 0;
                list = ((int *)FUN_002ee430((unsigned int)bytes));
                memset(list, 0, bytes);
                FUN_00304430(DAT_004fa930);
                FUN_00304680();
                for (k = 0; k < n; k++) {
                    if (it == -1) { break; }
                    list[k] = ((int)FUN_0030d1d0((int *)names, it));
                    it = FUN_0030d4a0((struct NextOwner *)names, it);
                }
                qsort(list, n, 4, (int (*)(const void *, const void *))FUN_002f7410);
                for (it = 0; it < n; it++) {
                    int name = list[it];
                    tracker->vfunc_33(0, -1, name, &sizeA, &sizeB, &sizeC, &sizeD);
                    sprintf(line, DAT_004fa988, name);
                    FUN_00304430(DAT_004fa990, line, sizeA, sizeB, sizeC, sizeD);
                    FUN_00304680();
                }
            }
        }
        if (((ObjectSystemView *)(*(void * *)g_objectSystem))->showMemoryStatisticsOnExit != 0) {
            total = 0; f = 0; g = 0; h = 0; i2 = 0; j2 = 0; k2 = 0; l2 = 0; m2 = 0;
            tracker->vfunc_32(0, -1, &total, counts, &f, &g, &h, &i2, &j2, &k2, &l2, 1, 1, &m2, 2, -1);
            for (LeakKind t = LeakKindFirst; t < LeakKindCount; t = (LeakKind)(t + 1)) {
                int *c = &counts[t];
                if (*c != 0) {
                    sprintf(type, DAT_004f95a0, FUN_002e1500(tracker, t));
                    FUN_00304430(DAT_004fa9b0, type, *c);
                    FUN_00304680();
                }
            }
            FUN_00304430(DAT_004fa9d0, total, f, g, h, i2, l2, m2, j2, k2);
            FUN_00304680();
        }
    }
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *p = (igMemoryPoolView *)self[i].allocator;
        if (p != 0) {
            int j;
            int seen;
            igEventTrackerView *o;
            o = (igEventTrackerView *)p->getEventTracker();
            seen = 0;
            if (o != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *q = (igMemoryPoolView *)self[j].allocator;
                    if (q != 0 && q->getEventTracker() == o) { seen = 1; break; }
                }
                if (o != 0 && seen == 0) {
                    if (((ObjectSystemView *)(*(void * *)g_objectSystem))->showLeaksOnExit != 0) {
                        if (o->vfunc_35() > 0) { o->vfunc_43(); }
                    }
                    o->vfunc_24();
                }
            }
        }
    }
    {
        igEventTrackerView *t = ((ObjectSystemView *)(*(void * *)g_objectSystem))->globalEventTracker;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            ((ObjectSystemView *)(*(void * *)g_objectSystem))->globalEventTracker = 0;
        }
    }
    for (int k = 0; k < 46; k++) {
        igMemoryPoolView *p = (igMemoryPoolView *)self[k].allocator;
        if (p != 0 && p->getEventTracker() != 0) { p->vfunc_90(0); }
    }
}

void FUN_002f78b0(MemoryContext *arg0) {
    char sp70[256];

    int s4;
    int s3;
    int s2;
    igEventTrackerView *s1;
    bool s0;

    igMemoryPoolView *t;
    igResult r;
    s4 = 0;
    s0 = false;
    do {
        t = *(igMemoryPoolView **)((char *)arg0 + s4 * 144 + 20);
        if (t != 0) {
            s1 = (igEventTrackerView *)t->getEventTracker();
            s2 = 0;
            if (s1 != 0) {
                s3 = 0;
                while (s3 < s4) {
                    t = *(igMemoryPoolView **)((char *)arg0 + s3 * 144 + 20);
                    if (t != 0 && t->getEventTracker() == s1) {
                        s2 = 1;
                        break;
                    }
                    s3 += 1;
                }
                if (s2 == 0 && s1 != 0) {
                    sp70[255] = 0;
                    if (!s0) {
                        if (s4 == 0 || s4 == 1) {
                            strncpy(sp70, (char *)(*(void * *)g_objectSystem) + 528, 255);
                            s0 = true;
                        } else {
                            goto b16;
                        }
                    } else {
b16:
                        if (s4 == 4) {
                            strncpy(sp70, (char *)(*(void * *)g_objectSystem) + 656, 255);
                        } else {
                            sp70[0] = 0;
                        }
                    }
                    if (sp70[0] == 0) {
                        sprintf(sp70, text_s_igm, arg0->vfunc_26(s4));
                    }
                    if (FUN_002dcc50((int *)s1) != 0) {
                        r = s1->vfunc_44(sp70);
                    }
                }
            }
        }
        s4 += 1;
    } while (s4 < 46);
}

igResult FUN_002f7a70(MemoryContext *self, unsigned int kind, int free) {
    int i;
    ContextRecord *e;
    igResult r;
    unsigned int flags;
    i = 0;
    e = (ContextRecord *)((char *)self + 20);
    r = g_resultSuccess;
    do {
        flags = e->flags;
        if ((flags & 0xFBFFFFFF) != 0 && (flags & 0xFFFFFF) == kind) {
            if (free != 0) {
                if (e->allocator != 0) {
                    if (flags & 0x02000000) {
                        ((igMemoryPoolView *)e->allocator)->vfunc_31();
                    }
                    if (e->flags & 0x01000000) {
                        self->RemoveAllocator(i);
                    }
                }
            } else if (flags & 0x01000000) {
                if (self->BuildAllocator(i, 1) == g_resultFailure) {
                    r = g_resultFailure;
                }
            }
        }
        i++;
        e++;
    } while (i < 46);
    return r;
}

void FUN_002f7bc0(ContextRecordStride *arg0, int arg1) {
    int i, j, found, id;
    igMemoryPoolView *o;
    for (i = 0; i < 46; i++) {
        o = (igMemoryPoolView *)arg0[i].allocator;
        if (o != 0) {
            id = (int)o->getEventTracker();
            found = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *o2 = (igMemoryPoolView *)arg0[j].allocator;
                    if (o2 != 0) {
                        int r2 = (int)o2->getEventTracker();
                        if (r2 == id) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found == 0 && id != 0) {
                    FUN_002dcc60((igEventTrackerView *)id, arg1);
                }
            }
        }
    }
}

void FUN_002f7cc0(ContextView *self, int arg1, int *out, int n) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool == 0) { continue; }
        tracker = (char *)pool->getEventTracker();
        found = 0;
        if (tracker == 0) { continue; }
        for (j = 0; j < i; j++) {
            igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
            if (earlier != 0 && earlier->getEventTracker() == tracker) {
                found = 1;
                break;
            }
        }
        if (found == 0 && tracker != 0) {
            if (n <= 0) { return; }
            *out = (int)(tracker + 0x2328);
            n--;
            out++;
            FUN_002dcc60((igEventTrackerView *)tracker, arg1);
        }
    }
}

void FUN_002f7e00(ContextView *self, int *paths, int n) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool == 0) { continue; }
        tracker = (char *)pool->getEventTracker();
        found = 0;
        if (tracker == 0) { continue; }
        for (j = 0; j < i; j++) {
            igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
            if (earlier != 0 && earlier->getEventTracker() == tracker) {
                found = 1;
                break;
            }
        }
        if (found == 0 && tracker != 0) {
            if (n <= 0) { return; }
            FUN_002dcc60((igEventTrackerView *)tracker, *paths);
            paths++;
            n--;
        }
    }
}

void FUN_002f7f20(ContextView *self, int arg1) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool != 0) {
            tracker = (char *)pool->getEventTracker();
            found = 0;
            if (tracker != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
                    if (earlier != 0 && earlier->getEventTracker() == tracker) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && tracker != 0) {
                    FUN_002dcd70((igEventTrackerView *)tracker, arg1);
                }
            }
        }
    }
}

void FUN_002f8020(ContextRecordStride *slots, int arg1, int *out, int n) {
    int i;
    int j;
    int found;
    int id;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *o = (igMemoryPoolView *)slots[i].allocator;
        if (o != 0 && (id = (int)o->getEventTracker(), found = 0, id != 0)) {
            for (j = 0; j < i; j++) {
                igMemoryPoolView *o2 = (igMemoryPoolView *)slots[j].allocator;
                int k;
                if (o2 != 0 && (k = (int)o2->getEventTracker(), k == id)) {
                    found = 1;
                    break;
                }
            }
            if (found == 0 && id != 0) {
                if (n <= 0) {
                    return;
                }
                *out = id + 0x242C;
                n--;
                out++;
                FUN_002dcd70((igEventTrackerView *)id, arg1);
            }
        }
    }
}

/* The comma expression pins the operand order of the duplicate test. */
void FUN_002f8160(ContextRecordStride *arg0, int *arg1, int arg2) {
    int i;
    int j;
    int dup;
    int id;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *o = (igMemoryPoolView *)arg0[i].allocator;
        if (o != 0) {
            id = (int)o->getEventTracker();
            dup = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *o2 = (igMemoryPoolView *)arg0[j].allocator;
                    int r;
                    if (o2 != 0 && (r = (int)o2->getEventTracker(), r == id)) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0 && id != 0) {
                    if (arg2 > 0) {
                        FUN_002dcd70((igEventTrackerView *)id, *arg1);
                        arg1 += 1;
                        arg2--;
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

/* The flag tests are `((x & m) ? 1 : 0) &&`; the ternary gives the materialised sltu. The two
 * later virtual slots are dummy-virtual stubs. */
void FUN_002f8280(ContextRecordStride *arg0, int arg1, int arg2, int arg3) {
    int sp[40];
    int i;
    int j;
    int found;
    igEventTrackerView *r;
    igMemoryPoolView *d;
    for (i = 0; i < 46; i++) {
        d = (igMemoryPoolView *)arg0[i].allocator;
        if (d != 0) {
            r = (igEventTrackerView *)d->getEventTracker();
            found = 0;
            if (r != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *e = (igMemoryPoolView *)arg0[j].allocator;
                    if (e != 0 && e->getEventTracker() == r) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && r != 0 && ((r->_eventTypeFilterFlags & 0x2000) ? 1 : 0) && ((r->_markerTypeFilterFlags & (1 << arg1)) ? 1 : 0)) {
                    FUN_002e2250((void *)sp, arg1, arg2, arg3, 0, 0, 0, 0, (int)0, (int)0);
                    r->vfunc_26((EventRecordInfo *)sp, -1);
                    FUN_002e2300(sp, (long long)(-1));
                }
            }
        }
    }
}

void FUN_002f8420(MemoryContext *arg0, char *arg1, igMemoryPoolView *arg2) {
    int index, matches, first;
    igMetaObject *stats;
    matches = 0;
    first = -1;
    if (arg1 == 0) {
        arg1 = text_Pool_statistics;
    }
    index = 0;
    do {
        if (arg2 == *(igMemoryPoolView **)((char *)arg0 + index * 144 + 20)) {
            stats = arg2->getMeta();
            FUN_00304430(DAT_004fab20, arg1, arg0->vfunc_26(index), stats->_name);
            FUN_00304680();
            matches += 1;
            if (matches == 1) {
                first = index;
            }
        }
        index += 1;
    } while (index < 46);
    if (matches == 0) {
        FUN_00304430(DAT_004f90b0, arg1);
        FUN_00304680();
    }
    arg2->vfunc_87(0);
    if (first != -1) {
        FUN_00304430(DAT_004fab30, g_memoryContextNames[first], first);
        FUN_00304680();
    }
}

void FUN_002f8580(ContextRecordStride *arg0, int *arg1) {
    int *var_a1;
    int temp_a2;
    int j;
    int i;
    int found;
    var_a1 = arg1;
    if (var_a1 == 0) {
        var_a1 = (int *)(&DAT_004fab70[0]);
    }
    FUN_00304430((const char *)var_a1, var_a1);
    FUN_00304680();
    i = 0;
    do {
        temp_a2 = (int)arg0[i].allocator;
        found = 0;
        if (temp_a2 != 0) {
            for (j = 0; j < i; j++) {
                int w = (int)arg0[j].allocator;
                if (w == temp_a2) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                ((MemoryContext *)(arg0))->vfunc_65((int)(0), (int)(temp_a2));
            }
        }
        i += 1;
    } while (i < 0x2E);
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
    FUN_002f0a60((char *)&text_Combined_pool_statistics[0]);
    g_activeSystemAllocator[0]->vfunc_36();
}

int Memory_GetCurrentContext(void) {
    if ((DAT_00587010[0] > 0) && (DAT_00587010[0] < 4)) {
        return DAT_00586ffc[DAT_00587010[0]];
    }
    if ((DAT_00587010[0] == 0) && ((*(void * *)DAT_00586fd0) != 0)) {
        return (int)(*(void * *)DAT_00586fd0);
    }
    return 0;
}

igResult FUN_002f86e0(void *arg1) {

    if ((arg1 != 0) && (DAT_00587010[0] >= 0) && (DAT_00587010[0] < 4)) {
        DAT_00587000[DAT_00587010[0]] = arg1;
        DAT_00587010[0] += 1;
        *(int *)((char *)(arg1) + 4) = (int)((int) (*(int *)((char *)(arg1) + 4) + 1));
        return g_resultSuccess;
    } else {
        return g_resultFailure;
    }
}

struct ContextStackEntry *FUN_002f8760(void) {
    int n;
    struct ContextStackEntry *s;
    if (DAT_00587010[0] > 0 && DAT_00587010[0] < 5) {
        n = DAT_00587010[0] - 1;
        DAT_00587010[0] = n;
        s = (struct ContextStackEntry *)DAT_00587000[n];
        if (s != 0) {
            s->u.w = s->u.w - 1;
            if (s->u.b.cnt == 0) igObject_Destroy(s);
        }
        return s;
    }
    return 0;
}

void * FUN_002f87f0(int arg0) {
    if (*(unsigned char *)(*(void * *)g_objectSystem) != 0) {
        igObject_AllocateRawStorageDefault(arg0, 0);
        return;
    }
    return (void *)(malloc());
}

/* Releases an allocation owned by a pool context. While the object system is active (flag byte at
 * the start of the record behind g_objectSystem) the call goes to Memory_FreeBuffer through its
 * j-thunk; otherwise it takes the early-boot path free. Neither callee's argument is
 * touched here: `allocation` is passed straight through in the first argument register. */
/* Object-system record pointer; byte 0 is the "object system active" flag. */
void igMemoryPoolContextInfo_DeleteAllocation(void *allocation) {
    if (*g_objectSystem[0] != 0) {
        thunk_FUN_002ed460__002ff810((int)allocation);
        return;
    }
    free(allocation);
}

void Memory_PrintPoolStatistics(int arg0, void *pool) {
    if (pool != 0) {
        ((MemoryContext *)(((void ** *)DAT_00586fd0)[0]))->vfunc_65((int)(arg0), (int)(pool));
        return;
    }
    ((MemoryContext *)(((void ** *)DAT_00586fd0)[0]))->vfunc_66((int)(arg0));
}

int Memory_GetCurrentContextAlias()
{
    return Memory_GetCurrentContext();
}

void * Memory_GetAllocatorBySelector(int selector) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(context))->getAllocatorBySelector((int)(selector)));
}

void * Memory_GetAllocatorByName(int name) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(context))->getAllocatorByName((int)(name)));
}

int FUN_002f8960(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((MemoryContext *)(temp_v0))->vfunc_26((int)(arg0));
}

void * FUN_002f89a0(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(temp_v0))->vfunc_27((void *)(arg0)));
}

int FUN_002f89e0(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((MemoryContext *)(temp_v0))->vfunc_29((int)(arg0));
}

void * FUN_002f8a20(void) {
    if (((int)Memory_GetAllocatorBySelector(2)) == 0) {
        Memory_GetAllocatorBySelector(0);
    }
}

int FUN_002f8a50(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 8);
}

int FUN_002f8a60(void *arg0, int arg1) {
    return *(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 20)) + 16) + (arg1 * 4));
}

void FUN_002f8a80(void *arg0, void *arg1) {
    if (arg1 != 0) {
        ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)arg0 + 20)), (igObject *)arg1);
        *(int *)((char *)arg1 + 4) = (int) (*(int *)((char *)arg1 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)arg1 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(arg1);
        }
    }
}

int FUN_002f8ae0(int *p, int extra1)
{
    return ObjectList_AppendRetained((igObjectList *)(*(int *)((char *)p + 20)), (igObject *)extra1);
}

void FUN_002f8b20(void *arg0) {
    int *s2 = (int *)*(int *)((char *)arg0 + 20);
    int n = s2[2];
    int i;
    int m;
    int *p;
    int v;
    for (i = 0; i < n; i++) {
        p = ((int **)s2[4])[i];
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)p);
            }
        }
    }
    m = s2[2];
    for (i = 0; i < m; i++) {
        ((int *)s2[4])[i] = 0;
    }
    s2[2] = 0;
}

igMemoryPoolInfo *FUN_002f8be0(igMemoryPoolContextInfo *arg0, int arg1) {
    int i;
    int n;
    igMemoryPoolInfo *it;
    int *name;
    i = 0;
    n = ((igMemoryPoolInfoList *)arg0->_memoryPoolInfos)->_count;
    for (; i < n; i++) {
        it = ((igMemoryPoolInfo **)((igMemoryPoolInfoList *)arg0->_memoryPoolInfos)->_data)[i];
        if (it != 0) {
            name = it->_name != 0 ? (int *)it->_name : emptyString;
            if (strcmp(name, arg1) == 0) return it;
        }
    }
    return 0;
}

igMemoryPoolInfo *FUN_002f8ca0(igMemoryPoolContextInfo *arg0, char *arg1) {
    int i;
    char *s;
    int n;
    igMemoryPoolInfo *it;

    n = ((igMemoryPoolInfoList *)arg0->_memoryPoolInfos)->_count;
    if ((arg1 == 0) || (*arg1 == 0)) {
        return 0;
    }
    if (strncmp(arg1, ((char *)text_kIGMemoryPool), 0xD) == 0) {
        arg1 += 0xD;
    }
    if (strncmp(arg1, text_Handle, 6) == 0) {
        if (strlen(arg1) != 6) {
            arg1 += 6;
        }
    }
    for (i = 0; i < n; i++) {
        it = ((igMemoryPoolInfo **)((igMemoryPoolInfoList *)arg0->_memoryPoolInfos)->_data)[i];
        if (it != 0) {
            s = (char *)it->_handleName;
            if ((s != 0) && (*s != 0)) {
                if (strncmp(s, ((char *)text_kIGMemoryPool), 0xD) == 0) {
                    s += 0xD;
                }
                if (strncmp(s, text_Handle, 6) == 0) {
                    if (strlen(arg1) != 6) {
                        s += 6;
                    }
                }
                if (strcmp(s, arg1) == 0) {
                    return it;
                }
            }
        }
    }
    return 0;
}

/* The smart pointer is declared and never assigned: retail clears its slot on entry and releases it on
 * every return, so the source had the local with its use compiled out. */
igResult Gap__Core__igMemoryPoolContextInfo__vfunc_25(igMemoryPoolContextInfoView *self, IniSectionsView *ini, char *section) {
    igSmartPointer<igObject> unused;
    int index;
    if (ini == 0) {
        ini = (IniSectionsView *)((ObjectSystemView *)g_objectSystem[0])->configRegistry;
    }
    if (ini == 0) {
        return g_resultFailure;
    }
    if (section == 0 || *section == 0) {
        section = DAT_004c2228[0];
    }
    index = FUN_00306360(ini, section, 0);
    if (index == -1) {
        return g_resultFailure;
    }
    if (self->vfunc_26(ini, index) == g_resultSuccess) {
        return g_resultSuccess;
    }
    return g_resultFailure;
}
