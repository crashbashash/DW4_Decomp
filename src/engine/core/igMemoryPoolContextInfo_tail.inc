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
    ((BF *)&self->_refCount)->lo = 1;
    memset(self->records, 0, sizeof(self->records));
    ((ContextVirtuals *)self)->InitializeRecordNames();
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
        memset(self->records, 0, 6624); ((ContextVirtuals *)self)->InitializeRecordNames();
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

int FUN_002f2730(Ctx_2f25d0 *arg0, int arg1) {
    int i, j;
    int r = 0;
    if (arg1 >= 0 && arg1 < 46) {
        char *e = (char *)(arg1 * 144) + (int)arg0;
        int *pk = (int *)(e + 20);
        r = *pk;
        if (r == 0) {
            if (*(int *)(e + 160) & 0x04000000) {
                arg0->v208(arg1);
                return *pk;
            }
            if (1 < DAT_00587010[0]) {
                for (i = DAT_00587010[0] - 1; i >= 0; i--) {
                    if (DAT_00587000[i] == (VC_2f25d0 *)arg0) break;
                }
                j = i - 1;
                if (j >= 0) {
                    VC_2f25d0 *p = (VC_2f25d0 *)DAT_00587000[j];
                    if (p != (VC_2f25d0 *)arg0) r = p->v92(arg1);
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
void *FUN_002f2830(ContextVirtuals2 *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!strcmp(((ContextRecords *)self)->records[i].name, name)) return self->Lookup(i);
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
            if (previous) ((ContextVirtuals *)self)->Clear(index);
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
int *FUN_002f29d0(Ctx2 *arg0, int arg1) {
    int i, j;
    if (arg1 != 0) {
        for (i = 0; i < 46; i++) {
            { int k = arg0->e[i].key; if (k == arg1) return arg0->e[i].val; }
        }
    }
    if (1 < DAT_00587010[0]) {
        for (i = DAT_00587010[0] - 1; i >= 0; i--) {
            if (DAT_00587000[i] == (VC2 *)arg0) break;
        }
        j = i - 1;
        if (j >= 0) {
            VC2 *p = (VC2 *)DAT_00587000[j];
            if (p != (VC2 *)arg0) return p->v108(arg1);
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
            igNamedObject_SetName((N_2fecb0 *)boundObject, name);
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

R2 FUN_002f2d20(OB *arg1, int arg2, int arg3) {
    int temp_s0;
    RO_2f25d0 *temp_a0;
    if (arg1->f16 == 0) {
        temp_s0 = ((int)igObject_GetAllocator((int)arg1));
        temp_a0 = arg1->f16;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        arg1->f16 = (RO_2f25d0 *)FUN_002c01f0(temp_s0);
    }
    if (arg2 == 0) {
        arg2 = *(int *)((char *)(*(void * *)g_objectSystem) + 56);
    }
    R2 sp6C = ((Child *)arg1->f16)->vA(arg2, arg3);
    if (sp6C.v == g_resultSuccess.v) {
        R2 sp68 = ((Self_2f25d0 *)arg1)->vB((int)arg1->f16, 1);
        sp6C = sp68;
    }
    return sp6C;
}

R2 FUN_002f2e30(OB *arg1, int arg2, int arg3) {
    int temp_s0;
    RO_2f25d0 *temp_a0;
    if (arg1->f16 == 0) {
        temp_s0 = ((int)igObject_GetAllocator((int)arg1));
        temp_a0 = arg1->f16;
        if (temp_a0 != 0) {
            temp_a0->u.w = temp_a0->u.w - 1;
            if (temp_a0->u.b.cnt == 0) igObject_Destroy(temp_a0);
        }
        arg1->f16 = (RO_2f25d0 *)FUN_002c01f0(temp_s0);
    }
    if (arg2 == 0) {
        arg2 = *(int *)((char *)(*(void * *)g_objectSystem) + 56);
    }
    R2 sp6C = ((Child2 *)arg1->f16)->vA(arg2, arg3);
    if (sp6C.v == g_resultSuccess.v) {
        R2 sp68 = ((Self_2f25d0 *)arg1)->vB((int)arg1->f16, 1);
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
        igNamedObject_SetName((N_2fecb0 *)handle, (int)entry->name);
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
        if (p != 0) { p = ((void *)StringPool_Construct((struct S_2eadf0 *)p)); }
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
        slot->record = ((PoolDescRecord *)FUN_002f8be0((struct O_2f8be0 *)self->table, (int)(descName(desc))));
        if (slot->record == 0) { slot->record = ((PoolDescRecord *)FUN_002f8ca0((struct Own_2f8ca0 *)self->table, desc->alias)); }
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
    ((ContextVirtuals *)self)->setFlags(self->flags | 8);
}

void FUN_002f4110(Par *arg0) {
    Obj2 **p;
    int i;
    p = (Obj2 **)((char *)arg0 + 0x14);
    for (i = 0; i < 0x2E; i++) {
        Obj2 *o = *p;
        if (o != 0 && (o->f4 & 0x7FFFFF) == 1) {
            if (o->v45() != 0) {
                (*p)->v85(0);
            }
            (*p)->v30();
        }
        p = (Obj2 **)((char *)p + 0x90);
    }
    arg0->v36(arg0->f12 & ~8);
}

void FUN_002f41e0(char *arg0) {
    Obj3 **p;
    int i;
    p = (Obj3 **)(arg0 + 20);
    i = 0;
    do {
        Obj3 *o = *p;
        if (o != 0) {
            if (o->u.b.cnt == 1) {
                o->v29();
            }
        }
        i++;
        p = (Obj3 **)((char *)p + 144);
    } while (i < 46);
}

void FUN_002f4250(void **arg0) {
    int var_s0;

    ((DW4VC_196_0 *)(arg0))->vX();
    ((DW4VC_220_0 *)(arg0))->vX();
    var_s0 = 0x2D;
    do {
        ((DW4VC_212_1 *)(arg0))->vX((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 20, 0, 0x19E0);
    ((DW4VC_180_0 *)(arg0))->vX();
}

void FUN_002f42e0(void **arg0, int arg1) {
    memset((char *)arg0 + 0x14, 0, 0x19E0);
    ((DW4VC_180_0 *)(arg0))->vX();
    Gap__Core__igObject__resetFields((int)arg0, arg1);
}

void FUN_002f4340(void **arg0) {
    int var_s0;

    Gap__Core__igObject__destructFields((int)arg0);
    var_s0 = 0x2D;
    do {
        ((DW4VC_212_1 *)(arg0))->vX((int)(var_s0));
        var_s0 -= 1;
    } while (var_s0 >= 0);
    memset((char *)arg0 + 0x14, 0, 0x19E0);
}

static inline PoolObject *newLargePool() {
    void *p = FUN_002f0040(0xd0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((PoolObject *)FUN_0031eb90((igArenaMemoryPool *)p)); }
    return (PoolObject *)p;
}

static inline PoolObject *newSmallPool() {
    void *p = FUN_002f0040(0xa0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((PoolObject *)FUN_003235c0((igMallocMemoryPool *)p)); }
    return (PoolObject *)p;
}

void FUN_002f43a0(PoolSlotTable *self) {
    PoolObject *p;
    int i;
    FUN_002f86e0(self);
    i = 0;
    do {
        switch (i) {
        case 0:
            NEW_POOL(p)
            break;
        case 4: case 5: case 6:
            if (g_useOwnerAllocator != 0) { p = self->first; } else { NEW_POOL(p) }
            break;
        default:
            p = self->first;
            break;
        }
        *(PoolObject **)((char *)self + i * 144 + 20) = p;
        if (g_useOwnerAllocator != 0) {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                ((PoolContext *)(*(void * *)g_objectSystem))->main = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                ((PoolContext *)(*(void * *)g_objectSystem))->second = p;
                break;
            }
        } else {
            switch (i) {
            case 0:
                p->prepare();
                if (DAT_00586fd8[0] != 0) { p->setName(DAT_00586fd8[0]); }
                p->finish();
                ((PoolContext *)(*(void * *)g_objectSystem))->main = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                ((PoolContext *)(*(void * *)g_objectSystem))->second = p;
                p->prepare();
                if (DAT_00586fe0[0] != 0) { p->setName(DAT_00586fe0[0]); }
                FUN_002f0370((void **)p);
                p->finish();
                break;
            case 5:
                p->prepare();
                if (DAT_00586fe8[0] != 0) { p->setName(DAT_00586fe8[0]); }
                FUN_002f0370((void **)p);
                p->finish();
                break;
            case 6:
                p->prepare();
                if (DAT_00586ff0[0] != 0) { p->setName(DAT_00586ff0[0]); }
                FUN_002f0370((void **)p);
                p->finish();
                break;
            }
        }
        i++;
        p->rc = p->rc + 1;
    } while (i < 46);
}

void FUN_002f48c0(void) {

}

void FUN_002f48d0(char *arg0) {
    int i;
    V_2f25d0 *obj;
    V_2f25d0 ***pp;
    void *ent;

    while (D_00587010[0] > 1) {
        FUN_002f8760();
    }
    *(int *)((char *)(*(void * *)g_objectSystem) + 52) = 0;
    i = 6;
    if (g_useOwnerAllocator == 0) {
        do {
            pp = (V_2f25d0 ***)(arg0 + i * 0x90 + 20);
            obj = (V_2f25d0 *)*pp;
            if (obj != 0) {
                FUN_002f0460((void **)obj);
                obj->v96();
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
        entry = (ContextPrefixedRecord *)((char *)self + index * sizeof(ContextRecord2));
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
void FUN_002f50e0(Mgr *arg0) {
    int s0;
    Sub_2f25d0 *p;
    Cnt *c;
    arg0->f47();
    if ((void *)arg0 == (*(void * *)DAT_00586fd0)) {
        FUN_002f00f0((void *)0);
    }
    arg0->f53();
    if (*(unsigned char *)((char *)(*(void * *)g_objectSystem) + 119) != 0) {
        arg0->f64(0);
    }
    s0 = 45;
    do {
        p = *(Sub_2f25d0 **)((char *)arg0 + s0 * 144 + 20);
        switch (s0) {
        case 0: case 4: case 5: case 6:
            break;
        default:
            if (p != 0) {
                arg0->f51(s0);
            }
        }
        s0--;
    } while (s0 >= 0);
    while (s0 >= 0) {
        p = *(Sub_2f25d0 **)((char *)arg0 + s0 * 144 + 20);
        if (p != 0) {
            c = p->f20();
            c->count = c->count - 1;
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
        igNamedObject_SetName((N_2fecb0 *)rec, (int)(self->recordName(i)));
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
    T_2f25d0 *t = (T_2f25d0 *)arg0;
    Sub2 *s;
    Obj4 *o;
    s = &t->f20;
    goto set;
back:
    if (t->f16 != 0) {
        FUN_002f8b20(t->f16);
        o = t->f16;
        if (o != 0) {
            o->refs = o->refs - 1;
            if (((unsigned long long)((long long)(int)o->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        t->f16 = 0;
    }
    return;
set:
    s->f132 = 0;
    goto back;
}

void FUN_002f5cc0(int *arg0) {
    *arg0 = g_resultSuccess.v;
}

void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag) {
    MC *ctx = (MC *)arg1;
    R3 r0, r1, r2, r3, r4, r5, r6, r7;
    igMemoryPool *obj;
    int meta;
    Slot *slot;
    igMemoryPool *allocA;
    igMemoryPoolInfo *cfg;
    int al;
    int aligned;
    igMemoryPool *mbc;
    char *sub;
    igMemoryPool *allocB;
    igMemoryPool **pslot;
    bool owned;
    igMemoryPool *a;
    slot = &ctx->slots[idx];
    meta = (int)g_igArenaMemoryPool_metaObject[0];
    allocA = ctx->slots[0].obj;
    allocB = ctx->slots[1].obj;
    mbc = ctx->slots[3].obj;
    cfg = slot->cfg;
    owned = true;
    obj = slot->obj;
    if (allocA == 0) allocA = ((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap));
    if (allocB == 0) {
        allocB = ((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault));
        if (allocB == 0) allocB = allocA;
    }
    if (mbc == 0) Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked);
    if (idx == 2) {
        slot->obj = allocB;
        allocB->_refCount = allocB->_refCount + 1;
    }
    if (cfg == 0) {
        if (idx >= 30) { *out = g_resultSuccess.v; return; }
        *out = g_resultFailure.v;
        return;
    }
    if (cfg->_scope != 0) {
        slot->f140 = 0;
        if (strstr((char *)cfg->_scope, text_LongTerm) == 0) {
            if (strstr((char *)cfg->_scope, text_Level) != 0) slot->f140 = slot->f140 | 1;
            else if (strstr((char *)cfg->_scope, text_Frame) != 0) slot->f140 = slot->f140 | 2;
        }
        if (strstr((char *)cfg->_scope, text_Create) != 0) slot->f140 = slot->f140 | 0x01000000;
        if (strstr((char *)cfg->_scope, text_Reset) != 0) slot->f140 = slot->f140 | 0x02000000;
        if (strstr((char *)cfg->_scope, text_OnDemand) != 0) slot->f140 = slot->f140 | 0x04000000;
        if (flag == 0) {
            int f = slot->f140;
            if ((((unsigned long long)((long long)f << 0x28)) >> 0x28) != 0 && (f & 0x05000000) != 0) {
                *out = g_resultSuccess.v;
                return;
            }
        }
    }
    if (obj != 0) {
        int size = cfg->_size;
        if (size != 0 && (cfg->_arenaType == 0 || strcmp((char *)cfg->_arenaType, text_Dynamic) == 0)) {
            r0 = ((OV *)obj)->v172(size);
        }
    } else {
        char *name = (char *)cfg->_aliasedTo;
        if (name != 0 && *name != 0) {
            int j = ctx->v116(name);
            obj = 0;
            if (j != -1) {
                Slot *o = (Slot *)((char *)(j * 144) + (int)ctx + 20);
                pslot = &o->obj;
                obj = o->obj;
                if (obj == 0) {
                    int rv = ctx->v204(j, flag).get();
                    if (rv != g_resultSuccess.v) { *out = g_resultFailure.v; return; }
                    obj = *pslot;
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
                        if (((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)) == 0) ctx->slots[5].obj = allocA;
                    }
                    {
                        igMemoryPool *old = obj;
                        obj = ((igMemoryPool *)igAliasMemoryPool_Create((void *)allocA));
                        ((OV *)obj)->v400(old);
                    }
                    if (idx == 5 && ctx->slots[5].obj == allocA) ctx->slots[5].obj = 0;
                } else {
                    owned = false;
                }
                ctx->v100(idx, obj);
                if (owned) {
                    obj->_refCount = obj->_refCount - 1;
                    if (RC(obj) == 0) igObject_Destroy(obj);
                }
                if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
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
        al = size + (((Gl *)((void * *)g_activeSystemAllocator)[0])->v84() - 1);
        aligned = al & ~(((Gl *)((void * *)g_activeSystemAllocator)[0])->v84() - 1);
        if (size != 0) {
            char *kind = (char *)cfg->_arenaType;
            if (kind == 0 || strcmp(kind, text_Dynamic) == 0) {
                r2 = ((OV *)o2)->v172(size);
            } else if (strcmp((char *)cfg->_arenaType, text_Fixed) == 0) {
                sub = (char *)cfg->_source;
                if (sub == 0 || *sub == 0) { a = allocB; goto common; }
                if (strcmp(sub, text_SystemMemory) == 0) {
b78:
                    int v = ((Gl *)((void * *)g_activeSystemAllocator)[0])->v68(0, aligned);
                    r3 = ((OV *)o2)->v96(v, aligned, 0);
                    slot->f136 = slot->f136 | 2;
                } else if (strcmp(sub, text_Low) == 0 || strcmp(sub, text_High) == 0 || strcmp(sub, text_Virtual) == 0) {
                    goto b78;
                } else if (strcmp(sub, text_HighSpeed) == 0) {
                    int dfl = cfg->_address;
                    int a2;
                    if (dfl != 0) a2 = dfl;
                    else a2 = 0x70000000;
                    r4 = ((OV *)o2)->v96(a2, (long long)size, 0);
                } else if (strcmp(sub, text_Raw) != 0 && strcmp(sub, text_Custom) != 0) {
                    a = ctx->v96(sub);
                    if (a == 0) a = allocB;
common:
                    if (((OV *)a)->v132() == 0) ((OV *)a)->v120();
                    r5 = ((OV *)o2)->v96(((OV *)a)->v216(size), (long long)size, 1);
                    a->_refCount = a->_refCount + 1;
                    slot->f136 = slot->f136 | 1;
                }
            }
        }
        r6 = ((OV *)o2)->v180(cfg);
        ctx->v100(idx, o2);
        o2->_refCount = o2->_refCount - 1;
        if (RC(o2) == 0) igObject_Destroy(o2);
    }
    }
    if (((OV *)obj)->v132() == 0) ((OV *)obj)->v120();
    *out = g_resultSuccess.v;
}

void MemoryContext_BuildAndAttachEventTracker(R4 *out, Ctx3 *self, int idx) {
    void *ty;
    Trk *trk;
    Obj5 *o2;
    igMemoryPoolInfo **ps2;
    Obj5 *o;
    int tv;
    igMemoryPoolInfo **ps;
    R4 t = self->v204(idx, 1); tv = t.v;
    int off = idx * 0x90; Slot2 *slot = (Slot2 *)(off + (int)self);
    trk = slot->trk;
    /* +12 of the context is igInfo::_directory in reflection but is read here as a flag word. The second flag test below stays on Ctx3::flags: typing both makes MWCC hoist the member address into a saved register. */
    int h1 = (((igMemoryPoolContextInfo *)self)->_directory & 1) != 0;
    if (h1) {
        ty = 0;
        ps = &slot->sub; igMemoryPoolInfo *sub = *ps;
        if (sub != 0) ty = (void *)sub->_releaseOptions;
        if (ty == 0 || strstr(ty, &text_InhibitEventTracker[0]) == 0) {
            int h2 = (self->flags & 2) != 0;
            if ((h2 && idx != 1) || (ty != 0 && strstr(ty, &text_UseEventTracker[0]) != 0)) {
                o = (Obj5 *)FUN_002c5780((int)(self->v92(3)));
                void *b = ((Gl2 *)(*(void * *)g_objectSystem))->f124;
                void *f = (void *)(*ps)->_eventTrackerCapacity;
                if (f != 0) b = f;
                FUN_002dcc40((int)o, (int)b);
                o->v92();
                trk->v360(o);
                ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
                if (RC2(o) == 0) igObject_Destroy(o);
            } else {
                void *x = self->v92(1)->v356();
                if (x != 0) trk->v360(x);
            }
        }
    } else {
        void *ty2 = 0;
        ps2 = &slot->sub; igMemoryPoolInfo *sub2 = *ps2;
        if (sub2 != 0) ty2 = (void *)sub2->_releaseOptions;
        if (ty2 != 0 && strstr(ty2, &text_UseEventTracker[0]) != 0) {
            o2 = (Obj5 *)FUN_002c5780((int)(self->v92(3)));
            void *b2 = ((Gl2 *)(*(void * *)g_objectSystem))->f124;
            void *f2 = (void *)(*ps2)->_eventTrackerCapacity;
            if (f2 != 0) b2 = f2;
            FUN_002dcc40((int)o2, (int)b2);
            o2->v92();
            trk->v360(o2);
            ((igObject *)o2)->_refCount = ((igObject *)o2)->_refCount - 1;
            if (RC2(o2) == 0) igObject_Destroy(o2);
        }
    }
    out->v = tv;
}

void MemoryContext_RemoveAllocator(void *arg0, int arg1) {
    R4 sp6C, sp68, sp64;
    if (arg1 >= 0 && arg1 < 0x2E) {
        Obj6 *o = *(Obj6 **)((char *)arg0 + arg1 * 0x90 + 20);
        Slot3 *slot = (Slot3 *)((char *)arg0 + arg1 * 0x90 + 20);
        if (o != 0) {
            slot->obj = 0;
            if (RC(o) == 1) {
                if (((C188 *)o)->vX() != 0) {
                    ((C348 *)o)->vX(0);
                }
                ((C128 *)o)->vX();
                {
                    int fl = slot->flags;
                    if (fl & 1) {
                        int a;
                        slot->flags = fl & ~1;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            void *own;
                            sp6C = ((C96 *)o)->vX(0, 0, 0);
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
                        slot->flags = fl & ~2;
                        a = ((C104 *)o)->vX(fl);
                        if (a != 0) {
                            long long b = (long long)((C144 *)o)->vX();
                            sp68 = ((C96 *)o)->vX(0, 0, 0);
                            sp64 = ((C72 *)((void * *)g_activeSystemAllocator)[0])->vX(a, b);
                        }
                    }
                }
            }
            o->_refCount = o->_refCount - 1;
            if (RC(o) == 0) igObject_Destroy(o);
            { Ctx4 *c = (Ctx4 *)arg0; if (arg1 == c->f8 + 1) c->f8 = arg1; }
        }
    }
}

static inline int trackerSizeFor(PoolDescRecord *record, int fallback) {
    int size = fallback;
    int n = record->a80;
    if (n != 0) { size = n; }
    return size;
}

void FUN_002f69b0(PoolSetup *self) {
    int registry = ((MemoryContextState *)g_objectSystem[0])->getConfig();
    TrackedPool *mainPool = ((MemoryContextState *)g_objectSystem[0])->main;
    TrackedPool *secondPool = ((MemoryContextState *)g_objectSystem[0])->getSecond();
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
    ((MemoryContextState *)g_objectSystem[0])->trackEvents = useGlobalEventTracker;
    FUN_00306e50(registry, 2, text_useSeparateEventTrackers, (char *)&useSeparateEventTrackers, useSeparateEventTrackers, 0);
    self->setFlags(useSeparateEventTrackers ? self->flags | 2 : self->flags & ~2);
    FUN_00306e50(registry, 2, text_showLeaksOnExit, (char *)&showLeaksOnExit, 0, 0);
    ((MemoryContextState *)g_objectSystem[0])->flag118 = showLeaksOnExit;
    FUN_00306e50(registry, 2, text_showMemoryStatisticsOnExit, (char *)&showMemoryStatisticsOnExit, 0, 0);
    ((MemoryContextState *)g_objectSystem[0])->flag119 = showMemoryStatisticsOnExit;
    FUN_00306e50(registry, 2, text_showObjectStatisticsOnExit, (char *)&showObjectStatisticsOnExit, 0, 0);
    ((MemoryContextState *)g_objectSystem[0])->flag120 = showObjectStatisticsOnExit;
    FUN_003065f0(registry, 2, text_eventTrackerInitialCapacity, &initialCapacity, 0x80000, 0);
    ((MemoryContextState *)g_objectSystem[0])->value124 = initialCapacity;
    FUN_003065f0(registry, 2, text_eventTrackerEventTypeFilter, &eventTypeFilter, -1, 0);
    ((MemoryContextState *)g_objectSystem[0])->value128 = eventTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerMarkerTypeFilter, &markerTypeFilter, -1, 0);
    ((MemoryContextState *)g_objectSystem[0])->value132 = markerTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerMaxCallStackDepth, &DAT_004c1eb0, DAT_004c1eb0, 0);
    FUN_003065f0(registry, 2, text_eventTrackerNotificationTypeFilt, &notificationTypeFilter, -1, 0);
    ((MemoryContextState *)g_objectSystem[0])->value136 = notificationTypeFilter;
    FUN_003065f0(registry, 2, text_eventTrackerNotificationCodeFilt, &notificationCodeFilter, -1, 0);
    ((MemoryContextState *)g_objectSystem[0])->value140 = notificationCodeFilter;
    FUN_00306910(registry, 2, text_memoryEventFormat, (int **)&memoryEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d31d0((N *)g_objectSystem[0], (char *)memoryEventFormat.p);
    FUN_00306910(registry, 2, text_markerEventFormat, (int **)&markerEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d3240((S_2d3240 *)g_objectSystem[0], (char *)markerEventFormat.p);
    FUN_00306910(registry, 2, text_notificationEventFormat, (int **)&notificationEventFormat, (char *)DAT_004f7910, 0);
    FUN_002d32b0((O_2d32b0 *)g_objectSystem[0], (char *)notificationEventFormat.p);
    FUN_003065f0(registry, 2, text_eventTrackerScopeFlags, &scopeFlags, -1, 0);
    FUN_002f0db0(scopeFlags);
    FUN_00306e50(registry, 2, text_saveEventTrackerOnExit, (char *)&saveEventTrackerOnExit, 0, 0);
    ((MemoryContextState *)g_objectSystem[0])->flag117 = saveEventTrackerOnExit;
    FUN_00306910(registry, 2, text_eventTrackerFileName, (int **)&eventTrackerFileName, (char *)DAT_004f7910, 0);
    FUN_002d3320((char *)g_objectSystem[0], (char *)eventTrackerFileName.p);
    FUN_00306910(registry, 2, text_systemPoolEventTrackerFileName, (int **)&systemPoolEventTrackerFileName, (char *)DAT_004f7910, 0);
    FUN_002d3370((char *)g_objectSystem[0], (char *)systemPoolEventTrackerFileName.p);
    FUN_00306910(registry, 2, text_symbolsFileName, (int **)&symbolsFileName, (char *)DAT_004f7910, 0);
    FUN_002d33c0(g_objectSystem[0], (int)symbolsFileName.p);
    if (symbolsFileName.p != 0 && *symbolsFileName.p != 0) {
        PoolLoader *loader = (PoolLoader *)FUN_002cec00(alloc);
        LoadedObject *loaded = (LoadedObject *)FUN_002b8500(alloc);
        if (loader != 0) {
            if (loader->load((char *)symbolsFileName.p) == g_resultSuccess) {
                if (loader->attach(loaded, 1) == g_resultFailure) {
                    loaded->rc.u.w = loaded->rc.u.w - 1;
                    if (loaded->rc.u.b.cnt == 0) igObject_Destroy(loaded);
                    loaded = 0;
                }
                unsigned char showSectionHeaders = 0;
                FUN_00306e50(registry, 2, text_showSectionHeaders, (char *)&showSectionHeaders, 0, 0);
                if (showSectionHeaders != 0) { loader->optionA(); }
                unsigned char showSymbols = 0;
                FUN_00306e50(registry, 2, text_showSymbols, (char *)&showSymbols, 0, 0);
                if (showSymbols != 0) { loader->optionB(); }
                loader->finish();
            }
            loader->rc.u.w = loader->rc.u.w - 1;
            if (loader->rc.u.b.cnt == 0) igObject_Destroy(loader);
        }
        ((MemoryContextState *)g_objectSystem[0])->loaded = loaded;
    }
    if (useGlobalEventTracker != 0) {
        EventTracker *tracker = (EventTracker *)FUN_002c5780(alloc);
        FUN_002dcc40((int)tracker, initialCapacity);
        tracker->start();
        tracker->users = tracker->users + 1;
        if (*systemPoolEventTrackerFileName.p != 0) {
            if (secondPool != mainPool) {
                EventTracker *own = (EventTracker *)FUN_002c5780(alloc);
                FUN_002dcc40((int)own, 0x6000);
                own->start();
                secondPool->setTracker(own);
                own->rc.u.w = own->rc.u.w - 1;
                if (own->rc.u.b.cnt == 0) igObject_Destroy(own);
            }
        }
        for (int i = 0; i < 46; i++) {
            if (i != 3) {
                TrackedPool *pool = (TrackedPool *)self->slots[i].pool;
                char *options = 0;
                if (self->slots[i].record != 0) { options = self->slots[i].record->s60; }
                if (pool != 0 && pool->hasTracker() == 0 && (options == 0 || strstr(options, text_InhibitEventTracker) == 0)) {
                    if ((useSeparateEventTrackers != 0 && i != 1) || (options != 0 && strstr(options, text_UseEventTracker) != 0)) {
                        EventTracker *own = (EventTracker *)FUN_002c5780(alloc);
                        FUN_002dcc40((int)own, trackerSizeFor(self->slots[i].record, initialCapacity));
                        own->start();
                        pool->setTracker(own);
                        own->rc.u.w = own->rc.u.w - 1;
                        if (own->rc.u.b.cnt == 0) igObject_Destroy(own);
                    } else {
                        pool->setTracker(tracker);
                    }
                }
            }
        }
        tracker->users = tracker->users - 1;
        if ((int)tracker->rc.u.b.cnt > 1) {
            ((MemoryContextState *)g_objectSystem[0])->tracker = tracker;
        } else {
            tracker->rc.u.w = tracker->rc.u.w - 1;
            if (tracker->rc.u.b.cnt == 0) igObject_Destroy(tracker);
        }
    } else {
        for (int i = 0; i < 46; i++) {
            if (i != 3) {
                TrackedPool *pool = (TrackedPool *)self->slots[i].pool;
                char *options = 0;
                if (self->slots[i].record != 0) { options = self->slots[i].record->s60; }
                if (pool != 0 && pool->hasTracker() == 0 && options != 0 && strstr(options, text_UseEventTracker) != 0) {
                    EventTracker *own = (EventTracker *)FUN_002c5780(alloc);
                    FUN_002dcc40((int)own, trackerSizeFor(self->slots[i].record, initialCapacity));
                    own->start();
                    pool->setTracker(own);
                    own->rc.u.w = own->rc.u.w - 1;
                    if (own->rc.u.b.cnt == 0) igObject_Destroy(own);
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

void FUN_002f7420(LeakReportSlot *self) {
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
    LeakReportTracker *tracker = ((LeakReportContext *)(*(void * *)g_objectSystem))->tracker;
    int i;
    if (tracker != 0) {
        if (((LeakReportContext *)(*(void * *)g_objectSystem))->dumpNames != 0) {
            int n;
            int names;
            int k;
            int it;
            int bytes;
            int *list;
            names = tracker->names;
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
                    tracker->describe(0, -1, name, &sizeA, &sizeB, &sizeC, &sizeD);
                    sprintf(line, DAT_004fa988, name);
                    FUN_00304430(DAT_004fa990, line, sizeA, sizeB, sizeC, sizeD);
                    FUN_00304680();
                }
            }
        }
        if (((LeakReportContext *)(*(void * *)g_objectSystem))->dumpSummary != 0) {
            total = 0; f = 0; g = 0; h = 0; i2 = 0; j2 = 0; k2 = 0; l2 = 0; m2 = 0;
            tracker->summary(0, -1, &total, counts, &f, &g, &h, &i2, &j2, &k2, &l2, 1, 1, &m2, 2, -1);
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
        LeakReportPool *p = self[i].pool;
        if (p != 0) {
            int j;
            int seen;
            LeakReportOwner *o;
            o = p->owner();
            seen = 0;
            if (o != 0) {
                for (j = 0; j < i; j++) {
                    LeakReportPool *q = self[j].pool;
                    if (q != 0 && q->owner() == o) { seen = 1; break; }
                }
                if (o != 0 && seen == 0) {
                    if (((LeakReportContext *)(*(void * *)g_objectSystem))->dumpLeaks != 0) {
                        if (o->count() > 0) { o->dump(); }
                    }
                    o->flush();
                }
            }
        }
    }
    {
        LeakReportTracker *t = ((LeakReportContext *)(*(void * *)g_objectSystem))->tracker;
        if (t != 0) {
            t->rc = t->rc - 1;
            if (((unsigned long long)((long long)(int)t->rc << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            ((LeakReportContext *)(*(void * *)g_objectSystem))->tracker = 0;
        }
    }
    for (int k = 0; k < 46; k++) {
        LeakReportPool *p = self[k].pool;
        if (p != 0 && p->owner() != 0) { p->release(0); }
    }
}

void FUN_002f78b0(VA_2f25d0 *arg0) {
    char sp70[256];

    int s4;
    int s3;
    int s2;
    VB *s1;
    bool s0;

    VB *t;
    R_2f25d0 r;
    s4 = 0;
    s0 = false;
    do {
        t = *(VB **)((char *)arg0 + s4 * 144 + 20);
        if (t != 0) {
            s1 = (VB *)t->v356();
            s2 = 0;
            if (s1 != 0) {
                s3 = 0;
                while (s3 < s4) {
                    t = *(VB **)((char *)arg0 + s3 * 144 + 20);
                    if (t != 0 && t->v356() == s1) {
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
                        sprintf(sp70, text_s_igm, arg0->v104(s4));
                    }
                    if (FUN_002dcc50((int *)s1) != 0) {
                        r = s1->v176(sp70);
                    }
                }
            }
        }
        s4 += 1;
    } while (s4 < 46);
}

igResult FUN_002f7a70(SlotPool *self, unsigned int kind, int free) {
    int i;
    PoolSlotEntry *e;
    igResult r;
    unsigned int flags;
    i = 0;
    e = (PoolSlotEntry *)((char *)self + 20);
    r = g_resultSuccess;
    do {
        flags = e->flags;
        if ((flags & 0xFBFFFFFF) != 0 && (flags & 0xFFFFFF) == kind) {
            if (free != 0) {
                if (e->owner != 0) {
                    if (flags & 0x02000000) {
                        e->owner->vDrop();
                    }
                    if (e->flags & 0x01000000) {
                        self->vFree(i);
                    }
                }
            } else if (flags & 0x01000000) {
                if (self->vRelease(i, 1) == g_resultFailure) {
                    r = g_resultFailure;
                }
            }
        }
        i++;
        e++;
    } while (i < 46);
    return r;
}

void FUN_002f7bc0(Ent_2f25d0 *arg0, int arg1) {
    int i, j, found, id;
    DW4VC_356_0 *o;
    for (i = 0; i < 46; i++) {
        o = arg0[i].obj;
        if (o != 0) {
            id = o->vX();
            found = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    DW4VC_356_0 *o2 = arg0[j].obj;
                    if (o2 != 0) {
                        int r2 = o2->vX();
                        if (r2 == id) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found == 0 && id != 0) {
                    FUN_002dcc60((FileRequest *)id, arg1);
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
            FUN_002dcc60((FileRequest *)tracker, arg1);
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
            FUN_002dcc60((FileRequest *)tracker, *paths);
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
                    FUN_002dcd70((W_2dcd70 *)tracker, arg1);
                }
            }
        }
    }
}

void FUN_002f8020(Slot4 *slots, int arg1, int *out, int n) {
    int i;
    int j;
    int found;
    int id;
    for (i = 0; i < 46; i++) {
        Obj7 *o = slots[i].obj;
        if (o != 0 && (id = o->vid(), found = 0, id != 0)) {
            for (j = 0; j < i; j++) {
                Obj7 *o2 = slots[j].obj;
                int k;
                if (o2 != 0 && (k = o2->vid(), k == id)) {
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
                FUN_002dcd70((W_2dcd70 *)id, arg1);
            }
        }
    }
}

/* The comma expression pins the operand order of the duplicate test. */
void FUN_002f8160(Slot5 *arg0, int *arg1, int arg2) {
    int i;
    int j;
    int dup;
    int id;
    for (i = 0; i < 46; i++) {
        V2 *o = arg0[i].f20;
        if (o != 0) {
            id = o->vX();
            dup = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    V2 *o2 = arg0[j].f20;
                    int r;
                    if (o2 != 0 && (r = o2->vX(), r == id)) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0 && id != 0) {
                    if (arg2 > 0) {
                        FUN_002dcd70((W_2dcd70 *)id, *arg1);
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
void FUN_002f8280(Slot6 *arg0, int arg1, int arg2, int arg3) {
    int sp[40];
    int i;
    int j;
    int found;
    Res *r;
    Dev_2f25d0 *d;
    for (i = 0; i < 46; i++) {
        d = arg0[i].dev;
        if (d != 0) {
            r = d->getRes();
            found = 0;
            if (r != 0) {
                for (j = 0; j < i; j++) {
                    Dev_2f25d0 *e = arg0[j].dev;
                    if (e != 0 && e->getRes() == r) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && r != 0 && ((r->flags & 0x2000) ? 1 : 0) && ((r->mask & (1 << arg1)) ? 1 : 0)) {
                    FUN_002e2250((void *)sp, arg1, arg2, arg3, 0, 0, 0, 0, (int)0, (int)0);
                    r->v24(sp, -1);
                    FUN_002e2300(sp, (long long)(-1));
                }
            }
        }
    }
}

void FUN_002f8420(VA_2f25d0 *arg0, char *arg1, VB2 *arg2) {
    int index, matches, first;
    Z *stats;
    matches = 0;
    first = -1;
    if (arg1 == 0) {
        arg1 = text_Pool_statistics;
    }
    index = 0;
    do {
        if (arg2 == *(VB2 **)((char *)arg0 + index * 144 + 20)) {
            stats = (Z *)arg2->v88();
            FUN_00304430(DAT_004fab20, arg1, arg0->v104(index), stats->f28);
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
    arg2->v348(0);
    if (first != -1) {
        FUN_00304430(DAT_004fab30, g_memoryContextNames[first], first);
        FUN_00304680();
    }
}

void FUN_002f8580(E3 *arg0, int *arg1) {
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
        temp_a2 = arg0[i].f20;
        found = 0;
        if (temp_a2 != 0) {
            for (j = 0; j < i; j++) {
                int w = arg0[j].f20;
                if (w == temp_a2) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                ((DW4VC_260_2 *)(arg0))->vX((int)(0), (int)(temp_a2));
            }
        }
        i += 1;
    } while (i < 0x2E);
    FUN_00304430(DAT_004f95c8);
    FUN_00304680();
    FUN_002f0a60((char *)&text_Combined_pool_statistics[0]);
    ((DW4VC_144_0 *)((void **)((void * *)g_activeSystemAllocator)[0]))->vX();
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
        ((DW4VC_260_2 *)(((void ** *)DAT_00586fd0)[0]))->vX((int)(arg0), (int)(pool));
        return;
    }
    ((DW4VC_264_2 *)(((void ** *)DAT_00586fd0)[0]))->vX((int)(arg0), (int)(pool));
}

int Memory_GetCurrentContextAlias()
{
    return Memory_GetCurrentContext();
}

void * Memory_GetAllocatorBySelector(int selector) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(context))->vX((int)(selector)));
}

void * Memory_GetAllocatorByName(int name) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext_2f8920 *)(context))->vX((int)(name)));
}

int FUN_002f8960(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((DW4VC_104_1 *)(temp_v0))->vX((int)(arg0));
}

void * FUN_002f89a0(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((DW4VC_108_1_2f89a0 *)(temp_v0))->vX((int)(arg0)));
}

int FUN_002f89e0(int arg0) {
    void **temp_v0;

    temp_v0 = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((DW4VC_116_1 *)(temp_v0))->vX((int)(arg0));
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

struct Item_2f8be0 *FUN_002f8be0(struct O_2f8be0 *arg0, int arg1) {
    int i;
    int n;
    struct Item_2f8be0 *it;
    int *name;
    i = 0;
    n = arg0->list->count;
    for (; i < n; i++) {
        it = arg0->list->items[i];
        if (it != 0) {
            name = it->name != 0 ? it->name : emptyString;
            if (strcmp(name, arg1) == 0) return it;
        }
    }
    return 0;
}

struct Item_2f8ca0 *FUN_002f8ca0(struct Own_2f8ca0 *arg0, char *arg1) {
    int i;
    char *s;
    int n;
    struct Item_2f8ca0 *it;

    n = arg0->list->count;
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
        it = arg0->list->data[i];
        if (it != 0) {
            s = it->name;
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
igResult Gap__Core__igMemoryPoolContextInfo__vfunc_25(Dev_2f8e10 *self, IniSectionsView *ini, char *section) {
    igSmartPointer<igObject> unused;
    int index;
    if (ini == 0) {
        ini = (IniSectionsView *)((MemoryContextState *)g_objectSystem[0])->config;
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
    if (self->get(ini, index) == g_resultSuccess) {
        return g_resultSuccess;
    }
    return g_resultFailure;
}
