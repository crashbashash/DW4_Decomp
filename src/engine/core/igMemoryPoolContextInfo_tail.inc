/* Constructor: 30 records in use, no flags, an empty context-info reference (its smart-pointer
 * constructor retains what it is given), a reference count of one in the low 23 bits of the
 * reference word, the records cleared and then named. */
MemoryContext *igMemoryPoolContextInfo_Construct(MemoryContext *self) {
    igObject_InitHeader((igObject *)self);
    *(char **)self = g_MemoryContext_vtable;
    self->usedRecords = 30;
    self->flags = 0;
    self->contextInfo = 0;
    if (self->contextInfo != 0) {
        self->contextInfo->_refCount += 1;
    }
    self->_refCount = 0;
    ((igRefCountWord *)&self->_refCount)->bits.count = 1;
    memset(self->records, 0, sizeof(self->records));
    self->InitializeRecordNames();
    return self;
}

/* IgMemoryPoolContextInfo: the destructor and the retained-allocator slot setter. A context holds
 * 46 records of 144 bytes starting at +0x14 (clearing them is the 6,624-byte memset in the
 * destructor). Each record is the allocator bound to that slot, a 128-byte inline name, a
 * descriptor and flag words. The object header is the igObject vtable word and reference word,
 * followed by a count at +8 (30 after construction, then the highest populated slot + 1), a flag
 * word at +12 and the context info at +16 that the destructor releases with the igObject reference-
 * count idiom. The views below describe the observed 32-bit layout, not the original C++ spelling. */
/* Destructor: republish the vtable, clear the reference word and all records, rebuild the 46
 * record names, release the context info, and free the allocation when the low 16 bits of `deleteFlags`
 * are positive (deleting destructor). The context-info word is left in place. */
void *igMemoryPoolContextInfo_Destruct(MemoryContext *self, long long deleteFlags) {
    if (self) {
        *(char **)self = g_MemoryContext_vtable; self->_refCount = 0;
        memset(self->records, 0, 6624); self->InitializeRecordNames();
        if (&self->contextInfo) {
            igMemoryPoolContextInfoView *parent = self->contextInfo;
            if (parent) {
                --parent->_refCount;
                if (!(parent->_refCount & 0x7fffff)) igObject_Destroy((igObject *)parent);
            }
        }
        if ((short)deleteFlags > 0) igMemoryPoolContextInfo_DeleteAllocation(self);
    }
    return self;
}

void *g_memoryContextStack[4];
int g_memoryContextStackDepth;

int igMemoryPoolContextInfo_GetAllocatorBySelector(MemoryContext *self, int selector) {
    int i, j;
    int r = 0;
    if (selector >= 0 && selector < 46) {
        char *recordBase = (char *)(selector * 144) + (int)self;
        int *allocator = (int *)&((ContextRecord *)(recordBase + 20))->allocator;
        r = *allocator;
        if (r == 0) {
            if (((ContextRecord *)(recordBase + 20))->flags & 0x04000000) {
                self->BuildAndAttachEventTracker(selector);
                return *allocator;
            }
            if (1 < g_memoryContextStackDepth) {
                for (i = g_memoryContextStackDepth - 1; i >= 0; i--) {
                    if (g_memoryContextStack[i] == (MemoryContext *)self) break;
                }
                j = i - 1;
                if (j >= 0) {
                    MemoryContext *parent = (MemoryContext *)g_memoryContextStack[j];
                    if (parent != (MemoryContext *)self) r = (int)parent->GetAllocatorBySelector(selector);
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
void *igMemoryPoolContextInfo_GetMemoryPoolByName(MemoryContext *self, const char *name) {
    if (name) {
        if (*name) {
            for (int i = 0; i < 46; ++i)
                if (!strcmp(self->records[i].name, name)) return self->GetAllocatorBySelector(i);
        }
    }
    return 0;
}

/* (vtable offset 100) Bind `value` to record `index` (0..45). Re-binding the same object is a no-
 * op; a different old binding is released through Clear first. The new object is retained, and a
 * non-null binding raises the used-record count. */
void igMemoryPoolContextInfo_SetAllocator(MemoryContext *self, int index, igObject *value) {
    if (index >= 0 && index < 46) {
        /* record address spelled as index * 144 + self (+ 20 for the allocator word); the
         * typed spelling &self->records[index] changes the bytes */
        unsigned int address = (unsigned int)index * 9; address <<= 4; address += (unsigned int)self;
        igObject **slot = (igObject **)(address + 20);
        igObject *previous = *slot;
        if (!previous || previous != value) {
            if (previous) self->RemoveAllocator(index);
            *slot = value;
            if (value) {
                ++value->_refCount;
                if (index >= self->usedRecords) self->usedRecords = index + 1;
            }
        }
    }
}

int igMemoryPoolContextInfo_GetPoolInfo(int self, int index) {
    if ((index >= 0) && (index < 0x2E)) {
        return self + (index * 0x90) + 0x18;
    }
    return (int)&((char *)"")[0];
}

/* The global count test is written `1 < n`. */
int *igMemoryPoolContextInfo_GetPoolName(MemoryContext *self, void *pool) {
    int i, j;
    if (pool != 0) {
        for (i = 0; i < 46; i++) {
            { void *k = self->records[i].allocator; if (k == pool) return (int *)self->records[i].name; }
        }
    }
    if (1 < g_memoryContextStackDepth) {
        for (i = g_memoryContextStackDepth - 1; i >= 0; i--) {
            if (g_memoryContextStack[i] == (MemoryContext *)self) break;
        }
        j = i - 1;
        if (j >= 0) {
            MemoryContext *p = (MemoryContext *)g_memoryContextStack[j];
            if (p != (MemoryContext *)self) return (int *)p->GetPoolName(pool);
        }
    }
    return (int *)((char *)"");
}

/* Renames record `recordIndex` of the context: copies at most 127 characters into the record's
 * inline 128-byte name field, terminates it, and renames the record's bound named object (if any)
 * to match. Out-of-range indices are ignored. The context holds 46 records of 144 bytes starting
 * at +0x14, each with a 128-byte inline name at +4. */
void igMemoryPoolContextInfo_SetPoolName(int self, int recordIndex, int name) {
    igNamedObject *boundObject;
    ContextRecord *record;

    if ((recordIndex >= 0) && (recordIndex < CONTEXT_RECORD_COUNT)) {
        record = (ContextRecord *)(self + (recordIndex * CONTEXT_RECORD_SIZE) + CONTEXT_RECORDS_OFFSET);
        strncpy(record->name, (const char *)name, CONTEXT_RECORD_NAME_MAX);
        record->name[CONTEXT_RECORD_NAME_MAX] = 0;
        boundObject = (igNamedObject *)record->descriptor;
        if (boundObject != 0) {
            igNamedObject_SetName(boundObject, (const char *)name);
        }
    }
}

int igMemoryPoolContextInfo_FindPoolIndexByName(int self, char *name) {
    int i;

    if (name != 0 && *name != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (strcmp((const char *)(self + (i * 0x90) + 0x18), name) == 0) {
                return i;
            }
        }
    }
    return -1;
}

char *g_memoryContextNames[46] = { "Bootstrap", "Default", "Current", "NonTracked", "System", "MetaData", "String", "Fast", "List", "Temporary", "Vertex", "RenderList", "Texture", "Application", "World", "Actor", "Level", "Frame", "Physics", "AI", "DriverData", "Clut", "DMA", "Audio", "Video", "Handles", "Image", "ImageObject", "Attribute", "Node", "User0", "User1", "User2", "User3", "User4", "User5", "User6", "User7", "User8", "User9", "User10", "User11", "User12", "User13", "User14", "User15" };

int igMemoryPoolContextInfo_GetPoolIndexByName(int self, char *name) {
    int i;
    char *s = name;
    if (s != 0 && *s != 0) {
        if (strncmp(s, (const char *)"kIGMemoryPoolHandle", 0x13) == 0) {
            s += 0x13;
        } else if (strncmp(s, (const char *)"kIGMemoryPool", 0xD) == 0) {
            s += 0xD;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp((const char *)(self + i * 0x90 + 0x18), s) == 0) return i;
        }
        for (i = 0; i < 0x2E; i++) {
            if (strcmp(g_memoryContextNames[i], s) == 0) return i;
        }
    }
    return -1;
}

int igMemoryPoolContextInfo_FindPoolIndex(int self, int pool) {
    int i;
    if (pool != 0) {
        for (i = 0; i < 0x2E; i++) {
            if (pool == *(int *)((char *)((self + (i * 0x90))) + 20)) {
                return i;
            }
        }
    }
    return -1;
}

igResult igMemoryPoolContextInfo_ReadConfiguration(MemoryContext *self, int config, int section) {
    int allocator;
    igObject *old;
    if (self->contextInfo == 0) {
        allocator = ((int)igObject_GetAllocator((igObject *)self));
        old = (igObject *)self->contextInfo;
        if (old != 0) {
            ((igRefCountWord *)&old->_refCount)->word = ((igRefCountWord *)&old->_refCount)->word - 1;
            if (((igRefCountWord *)&old->_refCount)->bits.count == 0) igObject_Destroy(old);
        }
        self->contextInfo = (igMemoryPoolContextInfoView *)igMemoryPoolContextInfo_Create(allocator);
    }
    if (config == 0) {
        config = (int)g_objectSystem->configRegistry;
    }
    igResult result = self->contextInfo->ReadFromRegistry((igRegistry *)config, (char *)section);
    if (result.v == g_resultSuccess.v) {
        igResult applied = self->SetPoolInfos((int)self->contextInfo, 1);
        result = applied;
    }
    return result;
}

igResult igMemoryPoolContextInfo_LoadFromRegistry(MemoryContext *self, int config, int index) {
    int allocator;
    igObject *old;
    if (self->contextInfo == 0) {
        allocator = ((int)igObject_GetAllocator((igObject *)self));
        old = (igObject *)self->contextInfo;
        if (old != 0) {
            ((igRefCountWord *)&old->_refCount)->word = ((igRefCountWord *)&old->_refCount)->word - 1;
            if (((igRefCountWord *)&old->_refCount)->bits.count == 0) igObject_Destroy(old);
        }
        self->contextInfo = (igMemoryPoolContextInfoView *)igMemoryPoolContextInfo_Create(allocator);
    }
    if (config == 0) {
        config = (int)g_objectSystem->configRegistry;
    }
    igResult result = self->contextInfo->ReadFromRegistrySection((igRegistry *)config, index);
    if (result.v == g_resultSuccess.v) {
        igResult applied = self->SetPoolInfos((int)self->contextInfo, 1);
        result = applied;
    }
    return result;
}

igResult igMemoryPoolContextInfo_GetPoolInfos(MemoryContext *self, int file) {
    igResult result = g_resultSuccess;
    int i;
    igMemoryPoolContextInfo_ClearMemoryPoolInfos((void *)file);
    for (i = 0; i < 46; i++) {
        if (self->records[i].descriptor != 0) {
            igMemoryPoolInfo *o = (igMemoryPoolInfo *)igMemoryPoolInfo_Create(((int)igObject_GetAllocator((igObject *)file)));
            if (self->FillMemoryPoolInfo(i, o) == g_resultFailure) {
                result = g_resultFailure;
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
            } else {
                igMemoryPoolContextInfo_AdoptMemoryPoolInfo((void *)file, (void *)o);
            }
        }
    }
    return result;
}

igResult igMemoryPoolContextInfo_SetPoolInfos(MemoryContext *self, int file, int arg) {
    int count = igMemoryPoolContextInfo_GetMemoryPoolInfoCount((void *)file);
    igResult result = g_resultSuccess;
    int i;
    if (self->contextInfo == 0) {
        int allocator = ((int)igObject_GetAllocator((igObject *)self));
        igMemoryPoolContextInfoView *old = self->contextInfo;
        if (old != 0) { old->_refCount = old->_refCount - 1; if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
        self->contextInfo = (igMemoryPoolContextInfoView *)igMemoryPoolContextInfo_Create(allocator);
    }
    for (i = 0; i < count; i++) {
        igMemoryPoolInfo *r;
        if ((r = (igMemoryPoolInfo *)((void *)igMemoryPoolContextInfo_GetMemoryPoolInfo((void *)file, i))) != 0) {
            if (self->SetPoolInfo(self->GetPoolIndexByName(r->_handleName), r, arg) == g_resultFailure) {
                result = g_resultFailure;
            }
        }
    }
    return result;
}

/* MemoryContext slot 34: fills `info` from record `index`. When the index is in 0..45 it copies the
 * record name via igNamedObject_SetName and, if the record has a descriptor, the descriptor's
 * integer fields and its ten interned strings (each assigned through the shared StringPool with the
 * usual retain/release of the old token). The record's allocator updates the descriptor's _size
 * first when it reports a size. _handleName is built from 'kIGMemoryPoolHandle%s' and the record's
 * context name. The status written through `result` is g_resultSuccess on success and
 * g_resultFailure for an out-of-range index. */
void igMemoryPoolContextInfo_FillMemoryPoolInfo(int *result, MemoryContext *context, int index, igMemoryPoolInfo *info)
{
    StringToken *old;
    const char *text;
    igMemoryPoolView *object;
    StringTokenHeader *header;
    ContextRecord *entry;
    char nameBuf[128];
    void *poolObj;
    int count;
    StringToken *token;
    int status;

    status = g_resultSuccess.v;
    if (index >= 0 && index < 46) {
        entry = &context->records[index];
        igNamedObject_SetName((igNamedObject *)info, (const char *)entry->name);
        if (entry->descriptor != 0) {
            ASSIGN_TOKEN(info->_aliasedTo, entry->descriptor->_aliasedTo);
            object = (igMemoryPoolView *)context->records[index].allocator;
            if (object != 0) {
                if (igObject_IsKindOf((igObject *)object, (igMetaObject *)g_igArenaMemoryPool_metaObject) != 0) {
                    if (object->GetPreSize() != 0) {
                        if (((igArenaMemoryPoolView *)object)->GetLocalNetAllocatedWithOverheadHigh() > object->GetPreSize()) {
                            entry->descriptor->_size = (int)((igArenaMemoryPoolView *)object)->GetLocalNetAllocatedWithOverheadHigh();
                        }
                    } else if (object->IsSecondaryAllocator() != 0) {
                        entry->descriptor->_size = (int)object->GetSize();
                    }
                } else if (object->GetSize() != 0) {
                    entry->descriptor->_size = (int)object->GetSize();
                }
            }
            info->_size = entry->descriptor->_size;
            info->_maxSize = entry->descriptor->_maxSize;
            info->_address = entry->descriptor->_address;
            ASSIGN_TOKEN(info->_class, entry->descriptor->_class);
            ASSIGN_TOKEN(info->_arenaType, entry->descriptor->_arenaType);
            ASSIGN_TOKEN(info->_source, entry->descriptor->_source);
            ASSIGN_TOKEN(info->_scope, entry->descriptor->_scope);
            ASSIGN_TOKEN(info->_debugOptions, entry->descriptor->_debugOptions);
            ASSIGN_TOKEN(info->_releaseOptions, entry->descriptor->_releaseOptions);
            ASSIGN_TOKEN(info->_debugChecking, entry->descriptor->_debugChecking);
            ASSIGN_TOKEN(info->_releaseChecking, entry->descriptor->_releaseChecking);
            ASSIGN_TOKEN(info->_debugMessages, entry->descriptor->_debugMessages);
            ASSIGN_TOKEN(info->_releaseMessages, entry->descriptor->_releaseMessages);
            info->_eventTrackerCapacity = entry->descriptor->_eventTrackerCapacity;
        }
        sprintf(nameBuf,"kIGMemoryPoolHandle%s", g_memoryContextNames[index]);
        ASSIGN_TOKEN_DIRECT(info->_handleName, nameBuf);
    } else {
        status = g_resultFailure.v;
    }
    *result = status;
}

/* Interns `src` into a reflected igStringMetaField word, releasing the previous token. */
static inline void setDescString(int *dst, char *src) {
    char *v = ((char *)StringPool_Intern(InternedStrings::get(), src));
    char *old = (char *)*dst;
    if (old != 0) {
        StringTokenHeader *h = (StringTokenHeader *)(old - 8);
        int n = h->refCount - 1;
        h->refCount = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunk *)h->owner, (StringTokenHeader *)h); }
    }
    *dst = (int)v;
}

static inline char *descName(igMemoryPoolInfo *r) { char *n = (char *)r->_name; if (n != 0) { return n; } return ((char *)emptyString); }

igResult igMemoryPoolContextInfo_SetPoolInfo(MemoryContext *self, int index, igMemoryPoolInfo *desc, int build) {
    igResult result = g_resultSuccess;
    ContextRecord *slot;
    if (index == -1) {
        index = self->usedRecords;
        if (index < 46) {
            setDescString(&desc->_handleName, g_memoryContextNames[index]);
            self->usedRecords = self->usedRecords + 1;
        }
    } else if (index >= self->usedRecords) {
        self->usedRecords = index + 1;
    }
    if (index >= 0 && index < 46) {
        slot = &self->records[index];
        strncpy(slot->name, descName(desc), 0x7f);
        slot->name[127] = 0;
        slot->descriptor = ((igMemoryPoolInfo *)igMemoryPoolContextInfo_FindMemoryPoolInfoByName((igMemoryPoolContextInfo *)self->contextInfo, (int)(descName(desc))));
        if (slot->descriptor == 0) { slot->descriptor = igMemoryPoolContextInfo_FindMemoryPoolInfoByHandle((igMemoryPoolContextInfo *)self->contextInfo, (char *)desc->_handleName); }
        if (slot->descriptor == 0) {
            slot->descriptor = (igMemoryPoolInfo *)igMemoryPoolInfo_Create((int)((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap)));
            igMemoryPoolContextInfo_AdoptMemoryPoolInfo((void *)self->contextInfo, (void *)slot->descriptor);
        }
        if (slot->descriptor != desc) {
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_aliasedTo; d = slot->descriptor; setDescString(&d->_aliasedTo, src); }
            slot->descriptor->_size = desc->_size;
            slot->descriptor->_maxSize = desc->_maxSize;
            slot->descriptor->_address = desc->_address;
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_class; d = slot->descriptor; setDescString(&d->_class, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_arenaType; d = slot->descriptor; setDescString(&d->_arenaType, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_source; d = slot->descriptor; setDescString(&d->_source, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_scope; d = slot->descriptor; setDescString(&d->_scope, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_debugOptions; d = slot->descriptor; setDescString(&d->_debugOptions, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_releaseOptions; d = slot->descriptor; setDescString(&d->_releaseOptions, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_debugChecking; d = slot->descriptor; setDescString(&d->_debugChecking, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_releaseChecking; d = slot->descriptor; setDescString(&d->_releaseChecking, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_debugMessages; d = slot->descriptor; setDescString(&d->_debugMessages, src); }
            { igMemoryPoolInfo *d; char *src; src = (char *)desc->_releaseMessages; d = slot->descriptor; setDescString(&d->_releaseMessages, src); }
            slot->descriptor->_eventTrackerCapacity = desc->_eventTrackerCapacity;
        }
        if (build != 0) {
            if (self->BuildAllocator(index, 0) == g_resultFailure) { result = g_resultFailure; }
        }
    } else {
        result = g_resultFailure;
    }
    return result;
}

void igMemoryPoolContextInfo_SetDirectory(igMemoryPoolContextInfo *self, int directory) {
    self->_directory = directory;
}

void igMemoryPoolContextInfo_Activate(MemoryContext *self) {
    ContextRecord *record = self->records;
    for (int i = 0; i < 46; i++) {
        if (record->allocator != 0 && !((igMemoryPoolView *)record->allocator)->IsActive()) {
            ((igMemoryPoolView *)record->allocator)->Activate();
        }
        record++;
    }
    self->SetFlags(self->flags | 8);
}

void igMemoryPoolContextInfo_DeactivatePools(MemoryContext *self) {
    igMemoryPoolView **p;
    int i;
    p = (igMemoryPoolView **)&self->records[0].allocator;
    for (i = 0; i < 0x2E; i++) {
        igMemoryPoolView *o = *p;
        if (o != 0 && (((igObject *)o)->_refCount & 0x7FFFFF) == 1) {
            if (o->GetLocalNetAllocated() != 0) {
                (*p)->PrintStatistics(0);
            }
            (*p)->Deactivate();
        }
        p = (igMemoryPoolView **)((ContextRecord *)p + 1);
    }
    self->SetFlags(self->flags & ~8);
}

void igMemoryPoolContextInfo_ResetPools(MemoryContext *self) {
    igMemoryPoolView **p;
    int i;
    p = (igMemoryPoolView **)&self->records[0].allocator;
    i = 0;
    do {
        igMemoryPoolView *o = *p;
        if (o != 0) {
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 1) {
                o->Reset();
            }
        }
        i++;
        p = (igMemoryPoolView **)((ContextRecord *)p + 1);
    } while (i < 46);
}

void igMemoryPoolContextInfo_TrimCapacity(void **self) {
    int index;

    ((MemoryContext *)(self))->ReleaseContextInfo();
    ((MemoryContext *)(self))->ShutdownEventTrackers();
    index = 0x2D;
    do {
        ((MemoryContext *)(self))->RemoveAllocator((int)(index));
        index -= 1;
    } while (index >= 0);
    memset(((MemoryContext *)(self))->records, 0, 0x19E0);
    ((MemoryContext *)(self))->InitializeRecordNames();
}

void Gap__Core__igMemoryPoolContextInfo__resetFields(void **self, int flags) {
    memset(((MemoryContext *)(self))->records, 0, 0x19E0);
    ((MemoryContext *)(self))->InitializeRecordNames();
    Gap__Core__igObject__resetFields((igObject *)self, flags);
}

void Gap__Core__igMemoryPoolContextInfo__destructFields(void **self) {
    int index;

    Gap__Core__igObject__destructFields((igObject *)self);
    index = 0x2D;
    do {
        ((MemoryContext *)(self))->RemoveAllocator((int)(index));
        index -= 1;
    } while (index >= 0);
    memset(((MemoryContext *)(self))->records, 0, 0x19E0);
}

static inline igMemoryPoolView *newLargePool() {
    void *p = igObject_OperatorNew(0xd0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((igMemoryPoolView *)igArenaMemoryPool_Initialize((igArenaMemoryPool *)p)); }
    return (igMemoryPoolView *)p;
}

static inline igMemoryPoolView *newSmallPool() {
    void *p = igObject_OperatorNew(0xa0, 0, ((int)Memory_GetDefaultAllocator()));
    if (p != 0) { p = ((igMemoryPoolView *)igMallocMemoryPool_Initialize((igMallocMemoryPool *)p)); }
    return (igMemoryPoolView *)p;
}

int g_bootstrapPoolPreSize;
int g_systemPoolPreSize;
int g_metaDataPoolPreSize;
int g_stringPoolPreSize;

void igMemoryPoolContextInfo_CreateDefaultPools(MemoryContext *self) {
    igMemoryPoolView *p;
    int i;
    igMemoryPoolContextInfo_PushContext(self);
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
                p->SetDefaults();
                if (g_bootstrapPoolPreSize != 0) { p->SetPreSize(g_bootstrapPoolPreSize); }
                p->Activate();
                g_objectSystem->bootstrapPool = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                g_objectSystem->systemPool = p;
                break;
            }
        } else {
            switch (i) {
            case 0:
                p->SetDefaults();
                if (g_bootstrapPoolPreSize != 0) { p->SetPreSize(g_bootstrapPoolPreSize); }
                p->Activate();
                g_objectSystem->bootstrapPool = p;
                Memory_InitializeAllocatorRegistries((igObject *)p);
                break;
            case 4:
                g_objectSystem->systemPool = p;
                p->SetDefaults();
                if (g_systemPoolPreSize != 0) { p->SetPreSize(g_systemPoolPreSize); }
                igMemoryPool_RegisterPool((void **)p);
                p->Activate();
                break;
            case 5:
                p->SetDefaults();
                if (g_metaDataPoolPreSize != 0) { p->SetPreSize(g_metaDataPoolPreSize); }
                igMemoryPool_RegisterPool((void **)p);
                p->Activate();
                break;
            case 6:
                p->SetDefaults();
                if (g_stringPoolPreSize != 0) { p->SetPreSize(g_stringPoolPreSize); }
                igMemoryPool_RegisterPool((void **)p);
                p->Activate();
                break;
            }
        }
        i++;
        ((igObject *)p)->_refCount = ((igObject *)p)->_refCount + 1;
    } while (i < 46);
}

void MemoryContext_OnStartupComplete(void) {

}

void igMemoryPoolContextInfo_Shutdown(char *self) {
    int i;
    igMemoryPoolView *obj;
    igMemoryPoolView ***pp;
    void *ent;

    while (g_memoryContextStackDepth > 1) {
        igMemoryPoolContextInfo_PopContext();
    }
    *(int *)((char *)((*(void * *)&g_objectSystem)) + 52) = 0;
    i = 6;
    if (g_useOwnerAllocator == 0) {
        do {
            pp = (igMemoryPoolView ***)(self + i * 0x90 + 20);
            obj = (igMemoryPoolView *)*pp;
            if (obj != 0) {
                igMemoryPool_UnregisterPool((void **)obj);
                obj->Shutdown();
                igObject_OperatorDelete(obj);
                *pp = 0;
            }
            i--;
        } while (i > 0);
    }
    ent = *(void **)(self + 20);
    Memory_ShutdownAllocatorRegistries((void **)ent);
    while (g_memoryContextStackDepth > 0) {
        igMemoryPoolContextInfo_PopContext();
    }
    *(int *)((char *)((*(void * *)&g_objectSystem)) + 48) = 0;
    igObject_OperatorDelete(ent);
}

/* IgMemoryPoolContextInfo slot 180: write the 46 original context names (Bootstrap, Default,
 * Current, NonTracked, ...) into the name field of each 144-byte context record. Each name is
 * copied with a 127-character limit and the 128th byte is cleared explicitly. Called by the
 * constructor and the destructor. strncpy is a strncpy-like bounded string copy (dest, source,
 * limit). */
void igMemoryPoolContextInfo_InitializeRecordNames(MemoryContext *self) {
    int index;

    index = 0;
    do {
        strncpy(self->records[index].name, g_memoryContextNames[index], CONTEXT_NAME_LIMIT);
        self->records[index].name[CONTEXT_NAME_LIMIT] = 0;
        index += 1;
    } while (index < CONTEXT_RECORD_COUNT);
}

char *g_memoryPoolsSectionName = "MEMORYPOOLS";

igResult igMemoryPoolContextInfo_Initialize(MemoryContext *self) {
    unsigned char useFlag;
    unsigned char lockFlag;
    unsigned char optFlag;
    int options;
    int optB;
    int optC;
    int mainSize;
    int nextSize;
    igMemoryPoolView *mainPool;
    int i;
    int config;
    igMemoryPoolView *o;
    igMemoryPoolView *second;
    config = (int)g_objectSystem->configRegistry;
    mainPool = g_objectSystem->bootstrapPool;
    second = g_objectSystem->systemPool;
    options = g_igArenaMemoryPool_defaultPoolOptionFlags;
    mainSize = 0;
    nextSize = 0;
    optB = g_igArenaMemoryPool_defaultMessageLevel;
    optC = g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel;
    igResult result = g_resultSuccess;
    useFlag = (self->flags & 4) != 0;
    lockFlag = g_igMemoryPool_defaultUpdateStatistics;
    igRegistry_GetValueInt((igRegistry *)config, 2,"bootstrapPoolPreSize", &mainSize, 0, 0);
    if (mainSize > 0) { mainPool->SetPreSize(mainSize); }
    igRegistry_GetValueBool((igRegistry *)config, 2,"updatePoolStatistics", &lockFlag, lockFlag, 0);
    g_igMemoryPool_defaultUpdateStatistics = lockFlag;
    igRegistry_GetValueBool((igRegistry *)config, 2,"useAliasMemoryPoolRelease", &useFlag, useFlag, 0);
    self->SetFlags(useFlag != 0 ? self->flags | 4 : self->flags & ~4);
    igRegistry_GetValueFlags(config, 2,"arenaMemoryPoolOptionFlagsRelease", igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum(), &options, g_igArenaMemoryPool_defaultPoolOptionFlags, 0);
    igRegistry_GetValueEnum(config, 2,"arenaMemoryPoolMessageLevelRelease", igArenaMemoryPool_GetMessageLevelMetaEnum(), &optB, g_igArenaMemoryPool_defaultMessageLevel, 0);
    igRegistry_GetValueEnum(config, 2,"arenaMemoryPoolHeapIntegrityCheckLevelRelease", igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum(), &optC, g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel, 0);
    {
        int v = (options & 0x200) != 0;
        optFlag = v;
        igRegistry_GetValueBool((igRegistry *)config, 2,"inhibitArenaCountMessage", &optFlag, v, 0);
    }
    if (optFlag != 0) { options |= 0x200; }
    g_igArenaMemoryPool_defaultPoolOptionFlags = options;
    g_igArenaMemoryPool_defaultMessageLevel = optB;
    g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel = optC;
    for (i = 0; i < 46; i++) {
        o = (igMemoryPoolView *)self->records[i].allocator;
        if (o != 0 && igObject_IsKindOf((igObject *)o, g_igArenaMemoryPool_metaObject) != 0) {
            igArenaMemoryPool_SetPoolOptionFlags((igArenaMemoryPool *)o, (options & ~1) | (((igArenaMemoryPool *)o)->_poolOptionFlags & 1));
        }
    }
    igRegistry_GetValueInt((igRegistry *)config, 2,"nonTrackedPoolPreSize", &nextSize, 0, 0);
    MemoryContext *top = g_currentMemoryContext;
    igMemoryPoolView *fb = (igMemoryPoolView *)self->records[3].allocator;
    if (self == top && fb == mainPool) {
        o = (igMemoryPoolView *)igArenaMemoryPool_Create((int)mainPool);
        if (nextSize > 0) { o->SetPreSize(nextSize); }
        o->Activate();
        self->SetAllocator(3, (igObject *)o);
        ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
        if (((unsigned long long)((long long)(int)((igObject *)o)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)o);
    }
    if (self->CreateDefaultContextInfo(config, g_memoryPoolsSectionName) == g_resultFailure) { result = g_resultFailure; }
    if (self->SetPoolInfos((int)self->contextInfo, 0) == g_resultFailure) { result = g_resultFailure; }
    if (self->vfunc_50() == g_resultFailure) { result = g_resultFailure; }
    if (g_useOwnerAllocator == 0) {
        for (i = 0; i < 46; i++) {
            if (i != 0) {
                igMemoryPoolView **slot = (igMemoryPoolView **)&self->records[i].allocator;
                igMemoryPoolView *p = *slot;
                if (p == mainPool) {
                    ((igObject *)p)->_refCount = ((igObject *)p)->_refCount - 1;
                    if (((unsigned long long)((long long)(int)((igObject *)p)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)p);
                    *slot = 0;
                }
            }
        }
        for (i = 0; i < 46; i++) {
            if (i == 2) {
                self->SetAllocator(i, (igObject *)self->records[1].allocator);
            } else {
                if (self->BuildAllocator(i, 0) == g_resultFailure) { result = g_resultFailure; }
            }
        }
    } else {
        self->SetAllocator(2, (igObject *)self->records[1].allocator);
    }
    self->ConfigureEventTracking();
    o = self->GetAllocatorBySelector(20);
    if (o != mainPool && o != second) { g_objectSystem->driverDataPool = o; }
    o = self->GetAllocatorBySelector(7);
    if (o != mainPool && o != second) { g_objectSystem->fastPool = o; }
    for (i = 0; i < 46; i++) {
        o = (igMemoryPoolView *)self->records[i].allocator;
        if (o != 0 && o->IsActive() == 0) { o->Activate(); }
    }
    if (g_igArenaMemoryPool_defaultPoolOptionFlags & 8) {
        mainPool->EnableAllocationLock(1);
        if (second != mainPool) { second->EnableAllocationLock(1); }
    }
    if (result == g_resultSuccess) { self->SetFlags(self->flags | 8); }
    return result;
}

/* The skip list 6/5/4/0 is a switch, which leaves the compare-chain delay slots empty. The second
 * loop is dead code and is kept. */
void igMemoryPoolContextInfo_RemoveAllAllocators(MemoryContext *self) {
    int index;
    igMemoryPoolView *pool;
    igMetaObject *meta;
    self->ReleaseContextInfo();
    if ((void *)self == ((*(void * *)&g_currentMemoryContext))) {
        igMemoryDictionary_SetCurrent((void *)0);
    }
    self->ShutdownEventTrackers();
    if (*(unsigned char *)((char *)((*(void * *)&g_objectSystem)) + 119) != 0) {
        self->PrintStatistics(0);
    }
    index = 45;
    do {
        pool = *(igMemoryPoolView **)((char *)self + index * 144 + 20);
        switch (index) {
        case 0: case 4: case 5: case 6:
            break;
        default:
            if (pool != 0) {
                self->RemoveAllocator(index);
            }
        }
        index--;
    } while (index >= 0);
    while (index >= 0) {
        pool = *(igMemoryPoolView **)((char *)self + index * 144 + 20);
        if (pool != 0) {
            meta = pool->GetMeta();
            meta->_instanceCount = meta->_instanceCount - 1;
        }
        index--;
    }
}

igMetaObject *igMemoryPool_GetMeta(void) {
    return g_igMemoryPool_metaObject;
}

static inline void releaseTable(igMemoryPoolContextInfoView *t) {
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
    }
}

char *g_presetPoolClassName;

void igMemoryPoolContextInfo_CreateDefaultContextInfo(int *out, MemoryContext *self, int config, char *name) {
    int defaultSize;
    int systemSize;
    int scratchSize;
    int driverSize;
    char buf[256];
    int i;
    igMemoryPoolInfo *rec;
    ContextRecord *slot;
    int ctxConfig;
    ctxConfig = (int)g_objectSystem->configRegistry;
    slot = self->records;
    if (self->contextInfo != 0) {
        igMemoryPoolContextInfo_ClearMemoryPoolInfos(self->contextInfo);
        releaseTable(self->contextInfo);
        self->contextInfo = 0;
    }
    {
        int alloc = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap);
        releaseTable(self->contextInfo);
        self->contextInfo = (igMemoryPoolContextInfoView *)igMemoryPoolContextInfo_Create(alloc);
    }
    i = 0;
    do {
        rec = (igMemoryPoolInfo *)igMemoryPoolInfo_Create((int)((igMemoryPool *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap)));
        igNamedObject_SetName((igNamedObject *)rec, (const char *)self->GetPoolInfo(i));
        setDescString(&rec->_handleName, g_memoryContextNames[i]);
        switch (i) {
        case 0:
            if (rec->_releaseOptions != 0 && *(char *)rec->_releaseOptions != 0) {
                strncpy(buf, (char *)rec->_releaseOptions, 255);
                buf[255] = 0;
            } else {
                buf[0] = 0;
            }
            if (strstr(buf,"InhibitEventTracker") == 0 && strstr(buf,"UseEventTracker") == 0) {
                if (buf[0] != 0) {
                    __memcpy(buf, (void *)" | InhibitEventTracker", 23);
                } else {
                    strncpy(buf,"InhibitEventTracker", 255);
                }
                setDescString(&rec->_releaseOptions, buf);
            }
            break;
        case 1:
            if (self == ((*(void * *)&g_currentMemoryContext))) {
                defaultSize = 0;
                igRegistry_GetValueInt((igRegistry *)config, 2,"defaultPoolPreSize", &defaultSize, 0, 0);
                if (defaultSize > 0) {
                    rec->_size = defaultSize;
                    char *n = g_presetPoolClassName;
                    if (n != 0) { setDescString(&rec->_class, n); }
                }
            }
            break;
        case 2:
            break;
        case 4:
            if (self == ((*(void * *)&g_currentMemoryContext))) {
                systemSize = 0;
                igRegistry_GetValueInt((igRegistry *)config, 2,"systemPoolPreSize", &systemSize, 0, 0);
                if (systemSize > 0) {
                    rec->_size = systemSize;
                    char *n = g_presetPoolClassName;
                    if (n != 0) { setDescString(&rec->_class, n); }
                }
            }
            break;
        case 5:
        case 6:
            break;
        case 7:
            igRegistry_GetValueInt((igRegistry *)ctxConfig, 2,"scratchPoolSize", &scratchSize, 0, 0);
            igRegistry_GetValueInt((igRegistry *)ctxConfig, 2,"scratchPadPoolSize", &scratchSize, scratchSize, 0);
            if (scratchSize != 0) {
                if (scratchSize > 16384) { scratchSize = 16384; }
                rec->_address = 0x70000000;
                rec->_size = 16384;
                setDescString(&rec->_arenaType,"Fixed");
                setDescString(&rec->_source,"HighSpeed");
                rec->_size = scratchSize;
            } else {
                setDescString(&rec->_aliasedTo, g_memoryContextNames[1]);
            }
            if (rec->_scope == 0 || *(char *)rec->_scope == 0) { setDescString(&rec->_scope,"OnDemand"); }
            break;
        case 20:
            if (self == ((*(void * *)&g_currentMemoryContext))) {
                driverSize = 0;
                igRegistry_GetValueInt((igRegistry *)config, 2,"driverPoolSize", &driverSize, 0, 0);
                if (driverSize != 0) {
                    rec = self->records[20].descriptor;
                    rec->_size = driverSize;
                } else {
                    setDescString(&rec->_aliasedTo, g_memoryContextNames[1]);
                }
            } else {
                setDescString(&rec->_aliasedTo, g_memoryContextNames[1]);
            }
            if (rec->_scope == 0 || *(char *)rec->_scope == 0) { setDescString(&rec->_scope,"OnDemand"); }
            break;
        default:
            if (rec->_scope == 0 || *(char *)rec->_scope == 0) { setDescString(&rec->_scope,"OnDemand"); }
            setDescString(&rec->_aliasedTo, g_memoryContextNames[1]);
            break;
        }
        igMemoryPoolContextInfo_AdoptMemoryPoolInfo(self->contextInfo, rec);
        i++;
        slot->descriptor = rec;
        slot++;
    } while (i < 30);
    if (config != 0 && name != 0 && *name != 0) {
        self->contextInfo->ReadFromRegistry((igRegistry *)config, name);
    }
    *out = g_resultSuccess.v;
}

void igMemoryPoolContextInfo_ReleaseContextInfo(void *object) {
    MemoryContext *t = (MemoryContext *)object;
    ContextRecord *s;
    igMemoryPoolContextInfoView *o;
    s = &t->records[0];
    goto set;
back:
    if (t->contextInfo != 0) {
        igMemoryPoolContextInfo_ClearMemoryPoolInfos(t->contextInfo);
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

void FUN_002f5cc0(int *result) {
    *result = g_resultSuccess.v;
}

void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *context, int idx, int flag) {
    MemoryContext *ctx = (MemoryContext *)context;
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
    meta = (int)g_igArenaMemoryPool_metaObject;
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
        if (strstr((char *)cfg->_scope,"LongTerm") == 0) {
            if (strstr((char *)cfg->_scope,"Level") != 0) slot->flags = slot->flags | 1;
            else if (strstr((char *)cfg->_scope,"Frame") != 0) slot->flags = slot->flags | 2;
        }
        if (strstr((char *)cfg->_scope,"Create") != 0) slot->flags = slot->flags | 0x01000000;
        if (strstr((char *)cfg->_scope,"Reset") != 0) slot->flags = slot->flags | 0x02000000;
        if (strstr((char *)cfg->_scope,"OnDemand") != 0) slot->flags = slot->flags | 0x04000000;
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
        if (size != 0 && (cfg->_arenaType == 0 || strcmp((char *)cfg->_arenaType,"Dynamic") == 0)) {
            r0 = ((igMemoryPoolView *)obj)->SetPreSize(size);
        }
    } else {
        char *name = (char *)cfg->_aliasedTo;
        if (name != 0 && *name != 0) {
            int j = ctx->FindPoolIndexByName((int)name);
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
                        if ((strstr((char *)cfg->_scope,"OnDemand") != 0 || strstr((char *)cfg->_scope,"ONDEMAND") != 0 || strstr((char *)cfg->_scope,"ondemand") != 0) && flag == 0) {
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
                        ((igAliasMemoryPoolView *)obj)->AssignAlias(old);
                    }
                    if (idx == 5 && ctx->records[5].allocator == allocA) ctx->records[5].allocator = 0;
                } else {
                    owned = false;
                }
                ctx->SetAllocator(idx, (igObject *)obj);
                if (owned) {
                    obj->_refCount = obj->_refCount - 1;
                    if (RC(obj) == 0) igObject_Destroy(obj);
                }
                if (((igMemoryPoolView *)obj)->IsActive() == 0) ((igMemoryPoolView *)obj)->Activate();
                *out = g_resultSuccess.v;
                return;
            }
        }
    {
        char *mname = (char *)cfg->_class;
        if (mname != 0 && *mname != 0) {
            int m = igObjectSystem_FindMetaByNameDefault((const char *)mname);
            meta = m;
            if (m == 0) meta = (int)g_igArenaMemoryPool_metaObject;
        }
    }
    {
        obj = ((igMemoryPool *)igMetaObject_CreateInstance((igMetaObject *)meta, (igMemoryPoolView *)allocA));
        igMemoryPool *o2 = obj;
        int size = cfg->_size;
        al = size + (g_activeSystemAllocator->GetPageSize() - 1);
        aligned = al & ~(g_activeSystemAllocator->GetPageSize() - 1);
        if (size != 0) {
            char *kind = (char *)cfg->_arenaType;
            if (kind == 0 || strcmp(kind,"Dynamic") == 0) {
                r2 = ((igMemoryPoolView *)o2)->SetPreSize(size);
            } else if (strcmp((char *)cfg->_arenaType,"Fixed") == 0) {
                sub = (char *)cfg->_source;
                if (sub == 0 || *sub == 0) { a = allocB; goto common; }
                if (strcmp(sub,"SystemMemory") == 0) {
b78:
                    int v = g_activeSystemAllocator->AllocateRange(0, aligned);
                    r3 = ((igMemoryPoolView *)o2)->SetRawMemory(v, aligned, 0);
                    slot->storageFlags = slot->storageFlags | 2;
                } else if (strcmp(sub,"Low") == 0 || strcmp(sub,"High") == 0 || strcmp(sub,"Virtual") == 0) {
                    goto b78;
                } else if (strcmp(sub,"HighSpeed") == 0) {
                    int dfl = cfg->_address;
                    int a2;
                    if (dfl != 0) a2 = dfl;
                    else a2 = 0x70000000;
                    r4 = ((igMemoryPoolView *)o2)->SetRawMemory(a2, (long long)size, 0);
                } else if (strcmp(sub,"Raw") != 0 && strcmp(sub,"Custom") != 0) {
                    a = (igMemoryPool *)ctx->GetAllocatorByName((int)sub);
                    if (a == 0) a = allocB;
common:
                    if (((igMemoryPoolView *)a)->IsActive() == 0) ((igMemoryPoolView *)a)->Activate();
                    r5 = ((igMemoryPoolView *)o2)->SetRawMemory((int)((igMemoryPoolView *)a)->Allocate(size), (long long)size, 1);
                    a->_refCount = a->_refCount + 1;
                    slot->storageFlags = slot->storageFlags | 1;
                }
            }
        }
        r6 = ((igMemoryPoolView *)o2)->Configure(cfg);
        ctx->SetAllocator(idx, (igObject *)o2);
        o2->_refCount = o2->_refCount - 1;
        if (RC(o2) == 0) igObject_Destroy(o2);
    }
    }
    if (((igMemoryPoolView *)obj)->IsActive() == 0) ((igMemoryPoolView *)obj)->Activate();
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
    trk = (igMemoryPoolView *)self->records[idx].allocator;
    /* +12 of the context is igInfo::_directory in reflection but is read here as a flag word. The second flag test below stays on MemoryContext::flags: typing both makes MWCC hoist the member address into a saved register. */
    int h1 = (((igMemoryPoolContextInfo *)self)->_directory & 1) != 0;
    if (h1) {
        ty = 0;
        ps = &self->records[idx].descriptor; igMemoryPoolInfo *sub = *ps;
        if (sub != 0) ty = (void *)sub->_releaseOptions;
        if (ty == 0 || strstr((const char *)ty, "InhibitEventTracker") == 0) {
            int h2 = (self->flags & 2) != 0;
            if ((h2 && idx != 1) || (ty != 0 && strstr((const char *)ty, "UseEventTracker") != 0)) {
                o = (igEventTrackerView *)igEventTracker_Create((int)(self->GetAllocatorBySelector(3)));
                void *b = g_objectSystem->eventTrackerInitialCapacity;
                void *f = (void *)(*ps)->_eventTrackerCapacity;
                if (f != 0) b = f;
                igEventTracker_SetCapacity((int)o, (int)b);
                o->Initialize();
                trk->SetEventTracker(o);
                ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
                if (RC2(o) == 0) igObject_Destroy(o);
            } else {
                void *x = self->GetAllocatorBySelector(1)->GetEventTracker();
                if (x != 0) trk->SetEventTracker(x);
            }
        }
    } else {
        void *ty2 = 0;
        ps2 = &self->records[idx].descriptor; igMemoryPoolInfo *sub2 = *ps2;
        if (sub2 != 0) ty2 = (void *)sub2->_releaseOptions;
        if (ty2 != 0 && strstr((const char *)ty2, "UseEventTracker") != 0) {
            o2 = (igEventTrackerView *)igEventTracker_Create((int)(self->GetAllocatorBySelector(3)));
            void *b2 = g_objectSystem->eventTrackerInitialCapacity;
            void *f2 = (void *)(*ps2)->_eventTrackerCapacity;
            if (f2 != 0) b2 = f2;
            igEventTracker_SetCapacity((int)o2, (int)b2);
            o2->Initialize();
            trk->SetEventTracker(o2);
            ((igObject *)o2)->_refCount = ((igObject *)o2)->_refCount - 1;
            if (RC2(o2) == 0) igObject_Destroy(o2);
        }
    }
    out->v = tv;
}

void MemoryContext_RemoveAllocator(void *self, int index) {
    igResult detached, released, freed;
    if (index >= 0 && index < 0x2E) {
        Obj6 *o = *(Obj6 **)((char *)self + index * 0x90 + 20);
        ContextRecord *slot = (ContextRecord *)((char *)self + index * 0x90 + 20);
        if (o != 0) {
            slot->allocator = 0;
            if (RC(o) == 1) {
                if (((igMemoryPoolView *)o)->GetLocalNetAllocated() != 0) {
                    ((igMemoryPoolView *)o)->PrintStatistics(0);
                }
                ((igMemoryPoolView *)o)->Deactivate();
                {
                    int fl = slot->storageFlags;
                    if (fl & 1) {
                        int a;
                        slot->storageFlags = fl & ~1;
                        a = ((igMemoryPoolView *)o)->GetRawMemory();
                        if (a != 0) {
                            void *own;
                            detached = ((igMemoryPoolView *)o)->SetRawMemory(0, 0, 0);
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
                        a = ((igMemoryPoolView *)o)->GetRawMemory();
                        if (a != 0) {
                            long long b = (int)((igMemoryPoolView *)o)->GetSize();
                            released = ((igMemoryPoolView *)o)->SetRawMemory(0, 0, 0);
                            freed = g_activeSystemAllocator->FreeRange(a, b);
                        }
                    }
                }
            }
            o->_refCount = o->_refCount - 1;
            if (RC(o) == 0) igObject_Destroy(o);
            { MemoryContext *c = (MemoryContext *)self; if (index == c->usedRecords + 1) c->usedRecords = index; }
        }
    }
}

static inline int trackerSizeFor(igMemoryPoolInfo *record, int fallback) {
    int size = fallback;
    int n = record->_eventTrackerCapacity;
    if (n != 0) { size = n; }
    return size;
}

void igMemoryPoolContextInfo_ConfigureEventTracking(MemoryContext *self) {
    int registry = g_objectSystem->getConfigRegistry();
    igMemoryPoolView *mainPool = g_objectSystem->bootstrapPool;
    igMemoryPoolView *secondPool = g_objectSystem->getSystemPool();
    int alloc = Memory_GetNonTrackedAllocator();
    int globalTrackerByDefault = (self->flags & 1) != 0;
    unsigned char useGlobalEventTracker = globalTrackerByDefault;
    unsigned char useSeparateEventTrackers = (self->flags & 2) != 0;
    unsigned char showLeaksOnExit;
    unsigned char saveEventTrackerOnExit;
    unsigned char showMemoryStatisticsOnExit;
    unsigned char showObjectStatisticsOnExit;
    igStringRef memoryEventFormat;
    igStringRef markerEventFormat;
    igStringRef notificationEventFormat;
    igStringRef eventTrackerFileName;
    igStringRef symbolsFileName;
    int initialCapacity;
    int scopeFlags;
    int eventTypeFilter;
    int markerTypeFilter;
    int notificationTypeFilter;
    int notificationCodeFilter;
    igStringRef systemPoolEventTrackerFileName;
    igRegistry_GetValueBool((igRegistry *)registry, 2,"useGlobalEventTracker", &useGlobalEventTracker, globalTrackerByDefault, 0);
    self->SetFlags(useGlobalEventTracker ? self->flags | 1 : self->flags & ~1);
    g_objectSystem->useGlobalEventTracker = useGlobalEventTracker;
    igRegistry_GetValueBool((igRegistry *)registry, 2,"useSeparateEventTrackers", &useSeparateEventTrackers, useSeparateEventTrackers, 0);
    self->SetFlags(useSeparateEventTrackers ? self->flags | 2 : self->flags & ~2);
    igRegistry_GetValueBool((igRegistry *)registry, 2,"showLeaksOnExit", &showLeaksOnExit, 0, 0);
    g_objectSystem->showLeaksOnExit = showLeaksOnExit;
    igRegistry_GetValueBool((igRegistry *)registry, 2,"showMemoryStatisticsOnExit", &showMemoryStatisticsOnExit, 0, 0);
    g_objectSystem->showMemoryStatisticsOnExit = showMemoryStatisticsOnExit;
    igRegistry_GetValueBool((igRegistry *)registry, 2,"showObjectStatisticsOnExit", &showObjectStatisticsOnExit, 0, 0);
    g_objectSystem->showObjectStatisticsOnExit = showObjectStatisticsOnExit;
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerInitialCapacity", &initialCapacity, 0x80000, 0);
    g_objectSystem->eventTrackerInitialCapacity = (void *)initialCapacity;
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerEventTypeFilter", &eventTypeFilter, -1, 0);
    g_objectSystem->eventTrackerEventTypeFilter = eventTypeFilter;
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerMarkerTypeFilter", &markerTypeFilter, -1, 0);
    g_objectSystem->eventTrackerMarkerTypeFilter = markerTypeFilter;
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerMaxCallStackDepth", &g_eventTrackerMaxCallStackDepth, g_eventTrackerMaxCallStackDepth, 0);
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerNotificationTypeFilter", &notificationTypeFilter, -1, 0);
    g_objectSystem->eventTrackerNotificationTypeFilter = notificationTypeFilter;
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerNotificationCodeFilter", &notificationCodeFilter, -1, 0);
    g_objectSystem->eventTrackerNotificationCodeFilter = notificationCodeFilter;
    igRegistry_GetValueString((igRegistry *)registry, 2,"memoryEventFormat", &memoryEventFormat.p, (char *)"", 0);
    igObjectSystem_SetMemoryEventFormat(g_objectSystem, (char *)memoryEventFormat.p);
    igRegistry_GetValueString((igRegistry *)registry, 2,"markerEventFormat", &markerEventFormat.p, (char *)"", 0);
    igObjectSystem_SetMarkerEventFormat(g_objectSystem, (char *)markerEventFormat.p);
    igRegistry_GetValueString((igRegistry *)registry, 2,"notificationEventFormat", &notificationEventFormat.p, (char *)"", 0);
    igObjectSystem_SetNotificationEventFormat(g_objectSystem, (char *)notificationEventFormat.p);
    igRegistry_GetValueInt((igRegistry *)registry, 2,"eventTrackerScopeFlags", &scopeFlags, -1, 0);
    igMemoryPool_SetScopeFlags(scopeFlags);
    igRegistry_GetValueBool((igRegistry *)registry, 2,"saveEventTrackerOnExit", &saveEventTrackerOnExit, 0, 0);
    g_objectSystem->saveEventTrackerOnExit = saveEventTrackerOnExit;
    igRegistry_GetValueString((igRegistry *)registry, 2,"eventTrackerFileName", &eventTrackerFileName.p, (char *)"", 0);
    igObjectSystem_SetEventTrackerFileName((char *)g_objectSystem, (char *)eventTrackerFileName.p);
    igRegistry_GetValueString((igRegistry *)registry, 2,"systemPoolEventTrackerFileName", &systemPoolEventTrackerFileName.p, (char *)"", 0);
    igObjectSystem_SetSystemPoolEventTrackerFileName((char *)g_objectSystem, (char *)systemPoolEventTrackerFileName.p);
    igRegistry_GetValueString((igRegistry *)registry, 2,"symbolsFileName", &symbolsFileName.p, (char *)"", 0);
    igObjectSystem_SetSymbolsFileName(g_objectSystem, (int)symbolsFileName.p);
    if (symbolsFileName.p != 0 && *symbolsFileName.p != 0) {
        ElfFileView *loader = (ElfFileView *)igElfFile_Create(alloc);
        igSymbolTable *loaded = (igSymbolTable *)igSymbolTable_Create(alloc);
        if (loader != 0) {
            if (loader->Open((char *)symbolsFileName.p) == g_resultSuccess) {
                if (loader->LoadSymbolTable(loaded, 1) == g_resultFailure) {
                    loaded->_refCount = loaded->_refCount - 1;
                    if (((unsigned long long)((long long)(int)loaded->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(loaded);
                    loaded = 0;
                }
                unsigned char showSectionHeaders = 0;
                igRegistry_GetValueBool((igRegistry *)registry, 2,"showSectionHeaders", &showSectionHeaders, 0, 0);
                if (showSectionHeaders != 0) { loader->PrintSectionHeaders(); }
                unsigned char showSymbols = 0;
                igRegistry_GetValueBool((igRegistry *)registry, 2,"showSymbols", &showSymbols, 0, 0);
                if (showSymbols != 0) { loader->PrintSymbols(); }
                loader->Close();
            }
            loader->refCount = loader->refCount - 1;
            if (((unsigned long long)((long long)(int)loader->refCount << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)loader);
        }
        g_objectSystem->symbolTable = loaded;
    }
    if (useGlobalEventTracker != 0) {
        igEventTrackerView *tracker = (igEventTrackerView *)igEventTracker_Create(alloc);
        igEventTracker_SetCapacity((int)tracker, initialCapacity);
        tracker->Initialize();
        tracker->_detachAllocationsCounter = tracker->_detachAllocationsCounter + 1;
        if (*systemPoolEventTrackerFileName.p != 0) {
            if (secondPool != mainPool) {
                igEventTrackerView *own = (igEventTrackerView *)igEventTracker_Create(alloc);
                igEventTracker_SetCapacity((int)own, 0x6000);
                own->Initialize();
                secondPool->SetEventTracker(own);
                own->_refCount = own->_refCount - 1;
                if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
            }
        }
        for (int i = 0; i < 46; i++) {
            if (i != 3) {
                igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
                char *options = 0;
                if (self->records[i].descriptor != 0) { options = (char *)self->records[i].descriptor->_releaseOptions; }
                if (pool != 0 && pool->GetEventTracker() == 0 && (options == 0 || strstr(options,"InhibitEventTracker") == 0)) {
                    if ((useSeparateEventTrackers != 0 && i != 1) || (options != 0 && strstr(options,"UseEventTracker") != 0)) {
                        igEventTrackerView *own = (igEventTrackerView *)igEventTracker_Create(alloc);
                        igEventTracker_SetCapacity((int)own, trackerSizeFor(self->records[i].descriptor, initialCapacity));
                        own->Initialize();
                        pool->SetEventTracker(own);
                        own->_refCount = own->_refCount - 1;
                        if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
                    } else {
                        pool->SetEventTracker(tracker);
                    }
                }
            }
        }
        tracker->_detachAllocationsCounter = tracker->_detachAllocationsCounter - 1;
        if ((long long)((unsigned long long)((long long)(int)tracker->_refCount << 0x29) >> 0x29) > 1) {
            g_objectSystem->globalEventTracker = tracker;
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
                if (pool != 0 && pool->GetEventTracker() == 0 && options != 0 && strstr(options,"UseEventTracker") != 0) {
                    igEventTrackerView *own = (igEventTrackerView *)igEventTracker_Create(alloc);
                    igEventTracker_SetCapacity((int)own, trackerSizeFor(self->records[i].descriptor, initialCapacity));
                    own->Initialize();
                    pool->SetEventTracker(own);
                    own->_refCount = own->_refCount - 1;
                    if (((unsigned long long)((long long)(int)own->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(own);
                }
            }
        }
    }
}

static inline void releaseString_2f25d0(char *p) {
    if (p != 0) {
        StringTokenHeader *h = (StringTokenHeader *)(p - 8);
        int n = h->refCount - 1;
        h->refCount = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunk *)h->owner, (StringTokenHeader *)h); }
    }
}

void igMemoryPoolContextInfo_CompareNames(const char **a, const char **b) {
    strcmp(*a, *b);
}

void igMemoryPoolContextInfo_ShutdownEventTrackers(MemoryContext *self) {
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
    igEventTrackerView *tracker = g_objectSystem->globalEventTracker;
    int i;
    if (tracker != 0) {
        if (g_objectSystem->showObjectStatisticsOnExit != 0) {
            int n;
            int names;
            int k;
            int it;
            int bytes;
            int *list;
            names = tracker->_classNames;
            if (names != 0) {
                n = igStringTable_GetCount((igStringTableView *)names);
                bytes = n * 4;
                it = 0;
                list = ((int *)Memory_SystemAllocate((unsigned int)bytes));
                memset(list, 0, bytes);
                igReport_Printf("    Class                                      allocCnt   freeCnt  allocSum   freeSum\n");
                igReport_Flush();
                for (k = 0; k < n; k++) {
                    if (it == -1) { break; }
                    list[k] = ((int)igStringTable_GetString((int *)names, it));
                    it = igStringTable_GetNextStringIndex((igStringTableView *)names, it);
                }
                qsort(list, n, 4, (int (*)(const void *, const void *))igMemoryPoolContextInfo_CompareNames);
                for (it = 0; it < n; it++) {
                    int name = list[it];
                    tracker->GetStatisticsByName(0, -1, name, &sizeA, &sizeB, &sizeC, &sizeD);
                    sprintf(line,"%s,", name);
                    igReport_Printf("    %-42s %8d, %8d, %8d, %8d\n", line, sizeA, sizeB, sizeC, sizeD);
                    igReport_Flush();
                }
            }
        }
        if (g_objectSystem->showMemoryStatisticsOnExit != 0) {
            total = 0; f = 0; g = 0; h = 0; i2 = 0; j2 = 0; k2 = 0; l2 = 0; m2 = 0;
            tracker->GetStatistics(0, -1, &total, counts, &f, &g, &h, &i2, &j2, &k2, &l2, 1, 1, &m2, 2, -1);
            for (LeakKind t = LeakKindFirst; t < LeakKindCount; t = (LeakKind)(t + 1)) {
                int *c = &counts[t];
                if (*c != 0) {
                    sprintf(type, (const char *)percent_s, igEventTracker_GetEventTypeName(tracker, t));
                    igReport_Printf("        %-21s %8d\n", type, *c);
                    igReport_Flush();
                }
            }
            igReport_Printf("    Total events:             %8d\n    Leak count:               %8d\n    Total allocation sum:     %8d\n    Total deallocation sum:   %8d\n    Total outstanding:        %8d\n    Second frame outstanding: %8d\n    Last frame outstanding:   %8d\n    Highest outstanding:      %8d\n    Largest allocation:       %8d\n", total, f, g, h, i2, l2, m2, j2, k2);
            igReport_Flush();
        }
    }
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *p = (igMemoryPoolView *)self->records[i].allocator;
        if (p != 0) {
            int j;
            int seen;
            igEventTrackerView *o;
            o = (igEventTrackerView *)p->GetEventTracker();
            seen = 0;
            if (o != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *q = (igMemoryPoolView *)self->records[j].allocator;
                    if (q != 0 && q->GetEventTracker() == o) { seen = 1; break; }
                }
                if (o != 0 && seen == 0) {
                    if (g_objectSystem->showLeaksOnExit != 0) {
                        if (o->GetLeakCount() > 0) { o->PrintLeaks(); }
                    }
                    o->Shutdown();
                }
            }
        }
    }
    {
        igEventTrackerView *t = g_objectSystem->globalEventTracker;
        if (t != 0) {
            t->_refCount = t->_refCount - 1;
            if (((unsigned long long)((long long)(int)t->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(t);
            g_objectSystem->globalEventTracker = 0;
        }
    }
    for (int k = 0; k < 46; k++) {
        igMemoryPoolView *p = (igMemoryPoolView *)self->records[k].allocator;
        if (p != 0 && p->GetEventTracker() != 0) { p->SetEventTracker(0); }
    }
}

void igMemoryPoolContextInfo_SaveEventTrackers(MemoryContext *self) {
    char fileName[256];

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
        t = *(igMemoryPoolView **)((char *)self + s4 * 144 + 20);
        if (t != 0) {
            s1 = (igEventTrackerView *)t->GetEventTracker();
            s2 = 0;
            if (s1 != 0) {
                s3 = 0;
                while (s3 < s4) {
                    t = *(igMemoryPoolView **)((char *)self + s3 * 144 + 20);
                    if (t != 0 && t->GetEventTracker() == s1) {
                        s2 = 1;
                        break;
                    }
                    s3 += 1;
                }
                if (s2 == 0 && s1 != 0) {
                    fileName[255] = 0;
                    if (!s0) {
                        if (s4 == 0 || s4 == 1) {
                            strncpy(fileName, (char *)((*(void * *)&g_objectSystem)) + 528, 255);
                            s0 = true;
                        } else {
                            goto b16;
                        }
                    } else {
b16:
                        if (s4 == 4) {
                            strncpy(fileName, (char *)((*(void * *)&g_objectSystem)) + 656, 255);
                        } else {
                            fileName[0] = 0;
                        }
                    }
                    if (fileName[0] == 0) {
                        sprintf(fileName,"%s.igm", self->GetPoolInfo(s4));
                    }
                    if (igEventTracker_GetCount((int *)s1) != 0) {
                        r = s1->WriteFile(fileName);
                    }
                }
            }
        }
        s4 += 1;
    } while (s4 < 46);
}

igResult igMemoryPoolContextInfo_UpdateAllocatorsOfKind(MemoryContext *self, unsigned int kind, int free) {
    int i;
    ContextRecord *e;
    igResult r;
    unsigned int flags;
    i = 0;
    e = self->records;
    r = g_resultSuccess;
    do {
        flags = e->flags;
        if ((flags & 0xFBFFFFFF) != 0 && (flags & 0xFFFFFF) == kind) {
            if (free != 0) {
                if (e->allocator != 0) {
                    if (flags & 0x02000000) {
                        ((igMemoryPoolView *)e->allocator)->Reset();
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

void igMemoryPoolContextInfo_SetEventTag(MemoryContext *self, int tag) {
    int i, j, found, id;
    igMemoryPoolView *o;
    for (i = 0; i < 46; i++) {
        o = (igMemoryPoolView *)self->records[i].allocator;
        if (o != 0) {
            id = (int)o->GetEventTracker();
            found = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *o2 = (igMemoryPoolView *)self->records[j].allocator;
                    if (o2 != 0) {
                        int r2 = (int)o2->GetEventTracker();
                        if (r2 == id) {
                            found = 1;
                            break;
                        }
                    }
                }
                if (found == 0 && id != 0) {
                    igEventTracker_SetEventTag((igEventTrackerView *)id, tag);
                }
            }
        }
    }
}

void igMemoryPoolContextInfo_GetEventTag(MemoryContext *self, int value, int *out, int n) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool == 0) { continue; }
        tracker = (char *)pool->GetEventTracker();
        found = 0;
        if (tracker == 0) { continue; }
        for (j = 0; j < i; j++) {
            igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
            if (earlier != 0 && earlier->GetEventTracker() == tracker) {
                found = 1;
                break;
            }
        }
        if (found == 0 && tracker != 0) {
            if (n <= 0) { return; }
            *out = (int)(tracker + 0x2328);
            n--;
            out++;
            igEventTracker_SetEventTag((igEventTrackerView *)tracker, value);
        }
    }
}

void igMemoryPoolContextInfo_SetEventTags(MemoryContext *self, int *paths, int n) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool == 0) { continue; }
        tracker = (char *)pool->GetEventTracker();
        found = 0;
        if (tracker == 0) { continue; }
        for (j = 0; j < i; j++) {
            igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
            if (earlier != 0 && earlier->GetEventTracker() == tracker) {
                found = 1;
                break;
            }
        }
        if (found == 0 && tracker != 0) {
            if (n <= 0) { return; }
            igEventTracker_SetEventTag((igEventTrackerView *)tracker, *paths);
            paths++;
            n--;
        }
    }
}

void igMemoryPoolContextInfo_SetEventClassName(MemoryContext *self, int value) {
    int i, j, found;
    char *tracker;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *pool = (igMemoryPoolView *)self->records[i].allocator;
        if (pool != 0) {
            tracker = (char *)pool->GetEventTracker();
            found = 0;
            if (tracker != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *earlier = (igMemoryPoolView *)self->records[j].allocator;
                    if (earlier != 0 && earlier->GetEventTracker() == tracker) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && tracker != 0) {
                    igEventTracker_SetEventClassName((igEventTrackerView *)tracker, value);
                }
            }
        }
    }
}

void igMemoryPoolContextInfo_GetEventClassName(MemoryContext *slots, int value, int *out, int n) {
    int i;
    int j;
    int found;
    int id;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *o = (igMemoryPoolView *)slots->records[i].allocator;
        if (o != 0 && (id = (int)o->GetEventTracker(), found = 0, id != 0)) {
            for (j = 0; j < i; j++) {
                igMemoryPoolView *o2 = (igMemoryPoolView *)slots->records[j].allocator;
                int k;
                if (o2 != 0 && (k = (int)o2->GetEventTracker(), k == id)) {
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
                igEventTracker_SetEventClassName((igEventTrackerView *)id, value);
            }
        }
    }
}

/* The comma expression pins the operand order of the duplicate test. */
void igMemoryPoolContextInfo_SetEventClassNames(MemoryContext *self, int *names, int count) {
    int i;
    int j;
    int dup;
    int id;
    for (i = 0; i < 46; i++) {
        igMemoryPoolView *o = (igMemoryPoolView *)self->records[i].allocator;
        if (o != 0) {
            id = (int)o->GetEventTracker();
            dup = 0;
            if (id != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *o2 = (igMemoryPoolView *)self->records[j].allocator;
                    int r;
                    if (o2 != 0 && (r = (int)o2->GetEventTracker(), r == id)) {
                        dup = 1;
                        break;
                    }
                }
                if (dup == 0 && id != 0) {
                    if (count > 0) {
                        igEventTracker_SetEventClassName((igEventTrackerView *)id, *names);
                        names += 1;
                        count--;
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
void igMemoryPoolContextInfo_SendMarker(MemoryContext *self, int markerType, int markerData, int markerValue) {
    int event[40];
    int i;
    int j;
    int found;
    igEventTrackerView *r;
    igMemoryPoolView *d;
    for (i = 0; i < 46; i++) {
        d = (igMemoryPoolView *)self->records[i].allocator;
        if (d != 0) {
            r = (igEventTrackerView *)d->GetEventTracker();
            found = 0;
            if (r != 0) {
                for (j = 0; j < i; j++) {
                    igMemoryPoolView *e = (igMemoryPoolView *)self->records[j].allocator;
                    if (e != 0 && e->GetEventTracker() == r) {
                        found = 1;
                        break;
                    }
                }
                if (found == 0 && r != 0 && ((r->_eventTypeFilterFlags & 0x2000) ? 1 : 0) && ((r->_markerTypeFilterFlags & (1 << markerType)) ? 1 : 0)) {
                    igEventTracker_InitMarkerEvent((void *)event, markerType, markerData, markerValue, 0, 0, 0, 0, (int)0, (int)0);
                    r->AddEvent((EventRecord *)event, -1);
                    igEventTracker_DestructEvent(event, (long long)(-1));
                }
            }
        }
    }
}

void igMemoryPoolContextInfo_PrintPoolStatistics(MemoryContext *self, char *title, igMemoryPoolView *pool) {
    int index, matches, first;
    igMetaObject *stats;
    matches = 0;
    first = -1;
    if (title == 0) {
        title ="Pool statistics";
    }
    index = 0;
    do {
        if (pool == *(igMemoryPoolView **)((char *)self + index * 144 + 20)) {
            stats = pool->GetMeta();
            igReport_Printf("%s (%s - %s):\n", title, self->GetPoolInfo(index), stats->_name);
            igReport_Flush();
            matches += 1;
            if (matches == 1) {
                first = index;
            }
        }
        index += 1;
    } while (index < 46);
    if (matches == 0) {
        igReport_Printf("%s:\n", title);
        igReport_Flush();
    }
    pool->PrintStatistics(0);
    if (first != -1) {
        igReport_Printf("    Handle                                %s (%d)\n", g_memoryContextNames[first], first);
        igReport_Flush();
    }
}

void igMemoryPoolContextInfo_PrintStatistics(MemoryContext *self, int *titleArg) {
    int *title;
    int pool;
    int j;
    int i;
    int found;
    title = titleArg;
    if (title == 0) {
        title = (int *)("Memory pool statistics:\n");
    }
    igReport_Printf((const char *)title, title);
    igReport_Flush();
    i = 0;
    do {
        pool = (int)self->records[i].allocator;
        found = 0;
        if (pool != 0) {
            for (j = 0; j < i; j++) {
                int w = (int)self->records[j].allocator;
                if (w == pool) {
                    found = 1;
                    break;
                }
            }
            if (found == 0) {
                self->PrintPoolStatistics((int)(0), (int)(pool));
            }
        }
        i += 1;
    } while (i < 0x2E);
    igReport_Printf(newline_2);
    igReport_Flush();
    igMemoryPool_PrintGlobalStatistics((char *)"Combined pool statistics");
    g_activeSystemAllocator->PrintStatistics();
}

int Memory_GetCurrentContext(void) {
    if ((g_memoryContextStackDepth > 0) && (g_memoryContextStackDepth < 4)) {
        return (int)g_memoryContextStack[g_memoryContextStackDepth - 1];
    }
    if ((g_memoryContextStackDepth == 0) && (((*(void * *)&g_currentMemoryContext)) != 0)) {
        return (int)((*(void * *)&g_currentMemoryContext));
    }
    return 0;
}

igResult igMemoryPoolContextInfo_PushContext(void *context) {

    if ((context != 0) && (g_memoryContextStackDepth >= 0) && (g_memoryContextStackDepth < 4)) {
        g_memoryContextStack[g_memoryContextStackDepth] = context;
        g_memoryContextStackDepth += 1;
        ((igObject *)context)->_refCount = (int)((int) (((igObject *)context)->_refCount + 1));
        return g_resultSuccess;
    } else {
        return g_resultFailure;
    }
}

igObject *igMemoryPoolContextInfo_PopContext(void) {
    int n;
    igObject *s;
    if (g_memoryContextStackDepth > 0 && g_memoryContextStackDepth < 5) {
        n = g_memoryContextStackDepth - 1;
        g_memoryContextStackDepth = n;
        s = (igObject *)g_memoryContextStack[n];
        if (s != 0) {
            ((igRefCountWord *)&s->_refCount)->word = ((igRefCountWord *)&s->_refCount)->word - 1;
            if (((igRefCountWord *)&s->_refCount)->bits.count == 0) igObject_Destroy(s);
        }
        return s;
    }
    return 0;
}

void * igMemoryPoolContextInfo_Allocate(int size) {
    if (g_objectSystem->active != 0) {
        return igObject_AllocateRawStorageDefault(size, 0);
    }
    return malloc(size);
}

/* Releases an allocation owned by a pool context. While the object system is active (flag byte at
 * the start of the record behind &g_objectSystem) the call goes to Memory_FreeBuffer through its
 * j-thunk; otherwise it takes the early-boot path free. Neither callee's argument is
 * touched here: `allocation` is passed straight through in the first argument register. */
/* Object-system record pointer; byte 0 is the "object system active" flag. */
void igMemoryPoolContextInfo_DeleteAllocation(void *allocation) {
    if (g_objectSystem->active != 0) {
        Memory_FreeBufferAliasC(allocation);
        return;
    }
    free(allocation);
}

void Memory_PrintPoolStatistics(int title, void *pool) {
    if (pool != 0) {
        ((MemoryContext *)((*(void ** *)&g_currentMemoryContext)))->PrintPoolStatistics((int)(title), (int)(pool));
        return;
    }
    ((MemoryContext *)((*(void ** *)&g_currentMemoryContext)))->PrintStatistics((int)(title));
}

int Memory_GetCurrentContextAlias()
{
    return Memory_GetCurrentContext();
}

igMemoryPoolView *Memory_GetAllocatorBySelector(int selector) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (igMemoryPoolView *)(((MemoryContext *)(context))->GetAllocatorBySelector((int)(selector)));
}

void * Memory_GetAllocatorByName(int name) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(context))->GetAllocatorByName((int)(name)));
}

int Memory_GetPoolNameByIndex(int index) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((MemoryContext *)(context))->GetPoolInfo((int)(index));
}

void * Memory_GetPoolName(int pool) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return (void *)(((MemoryContext *)(context))->GetPoolName((void *)(pool)));
}

int igMemoryPoolContextInfo_GetMemoryPoolHandle(int name) {
    void **context;

    context = (void **)(((void **)Memory_GetCurrentContextAlias()));
    return ((MemoryContext *)(context))->FindPoolIndexByName((int)(name));
}

igMemoryPoolView *Memory_GetCurrentAllocator(void) {
    if (Memory_GetAllocatorBySelector(2) == 0) {
        Memory_GetAllocatorBySelector(0);
    }
}

int igMemoryPoolContextInfo_GetMemoryPoolInfoCount(void *info) {
    return ((igMemoryPoolInfoList *)((igMemoryPoolContextInfo *)info)->_memoryPoolInfos)->_count;
}

int igMemoryPoolContextInfo_GetMemoryPoolInfo(void *info, int index) {
    return ((int *)((igMemoryPoolInfoList *)((igMemoryPoolContextInfo *)info)->_memoryPoolInfos)->_data)[index];
}

void igMemoryPoolContextInfo_AdoptMemoryPoolInfo(void *info, void *poolInfo) {
    if (poolInfo != 0) {
        ObjectList_AppendRetained((igObjectList *)((igMemoryPoolContextInfo *)info)->_memoryPoolInfos, (igObject *)poolInfo);
        ((igObject *)poolInfo)->_refCount = (int) (((igObject *)poolInfo)->_refCount - 1);
        if (((unsigned long long) ((long long)(int)((igObject *)poolInfo)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)poolInfo);
        }
    }
}

int igMemoryPoolContextInfo_AddMemoryPoolInfo(igMemoryPoolContextInfo *self, int poolInfo)
{
    return ObjectList_AppendRetained((igObjectList *)self->_memoryPoolInfos, (igObject *)poolInfo);
}

void igMemoryPoolContextInfo_RemoveMemoryPoolInfo(igMemoryPoolContextInfo *info, igMemoryPoolInfo *poolInfo) {
    ObjectList_RemoveFirstRetained((igTDataList<igObject *> *)info->_memoryPoolInfos, (igObject *)poolInfo, 0);
}

void igMemoryPoolContextInfo_ClearMemoryPoolInfos(void *info) {
    igMemoryPoolInfoList *list = (igMemoryPoolInfoList *)((igMemoryPoolContextInfo *)info)->_memoryPoolInfos;
    int n = list->_count;
    int i;
    int m;
    igObject *poolInfo;
    int count;
    for (i = 0; i < n; i++) {
        poolInfo = ((igObject **)list->_data)[i];
        if (poolInfo != 0) {
            count = poolInfo->_refCount - 1;
            poolInfo->_refCount = count;
            if ((poolInfo->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)poolInfo);
            }
        }
    }
    m = list->_count;
    for (i = 0; i < m; i++) {
        ((igObject **)list->_data)[i] = 0;
    }
    list->_count = 0;
}

igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByName(igMemoryPoolContextInfo *self, int name) {
    int i;
    int n;
    igMemoryPoolInfo *it;
    int *infoName;
    i = 0;
    n = ((igMemoryPoolInfoList *)self->_memoryPoolInfos)->_count;
    for (; i < n; i++) {
        it = ((igMemoryPoolInfo **)((igMemoryPoolInfoList *)self->_memoryPoolInfos)->_data)[i];
        if (it != 0) {
            infoName = it->_name != 0 ? (int *)it->_name : (int *)emptyString;
            if (strcmp((const char *)infoName, (const char *)name) == 0) return it;
        }
    }
    return 0;
}

igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByHandle(igMemoryPoolContextInfo *self, char *handle) {
    int i;
    char *s;
    int n;
    igMemoryPoolInfo *it;

    n = ((igMemoryPoolInfoList *)self->_memoryPoolInfos)->_count;
    if ((handle == 0) || (*handle == 0)) {
        return 0;
    }
    if (strncmp(handle, ((char *)"kIGMemoryPool"), 0xD) == 0) {
        handle += 0xD;
    }
    if (strncmp(handle,"Handle", 6) == 0) {
        if (strlen(handle) != 6) {
            handle += 6;
        }
    }
    for (i = 0; i < n; i++) {
        it = ((igMemoryPoolInfo **)((igMemoryPoolInfoList *)self->_memoryPoolInfos)->_data)[i];
        if (it != 0) {
            s = (char *)it->_handleName;
            if ((s != 0) && (*s != 0)) {
                if (strncmp(s, ((char *)"kIGMemoryPool"), 0xD) == 0) {
                    s += 0xD;
                }
                if (strncmp(s,"Handle", 6) == 0) {
                    if (strlen(handle) != 6) {
                        s += 6;
                    }
                }
                if (strcmp(s, handle) == 0) {
                    return it;
                }
            }
        }
    }
    return 0;
}

/* The smart pointer is declared and never assigned: retail clears its slot on entry and releases it on
 * every return, so the source had the local with its use compiled out. */
igResult igMemoryPoolContextInfo_ReadFromRegistry(igMemoryPoolContextInfoView *self, igRegistry *ini, char *section) {
    igSmartPointer<igObject> unused;
    int index;
    if (ini == 0) {
        ini = g_objectSystem->configRegistry;
    }
    if (ini == 0) {
        return g_resultFailure;
    }
    if (section == 0 || *section == 0) {
        section = g_memoryPoolsSectionName;
    }
    index = igRegistry_GetSectionIndex(ini, section, 0);
    if (index == -1) {
        return g_resultFailure;
    }
    if (self->ReadFromRegistrySection(ini, index) == g_resultSuccess) {
        return g_resultSuccess;
    }
    return g_resultFailure;
}

static inline const char *poolInfoName(igMemoryPoolInfo *info) {
    return info->_name != 0 ? (const char *)info->_name : (const char *)emptyString;
}

/* Read every key of section `index` of `ini` (the memory pools section by default) as a memory pool info:
 * the key names the info and its value names the section the info reads its settings from. An info the
 * context already holds is reset first; a new one is added once it has read. An info that takes over
 * another info's handle replaces it. */
igResult igMemoryPoolContextInfo_ReadFromRegistrySection(igMemoryPoolContextInfo *self, igRegistry *ini, int index) {
    if (ini == 0) {
        ini = g_objectSystem->configRegistry;
    }
    if (ini == 0) {
        return g_resultFailure;
    }
    if (index == -1) {
        index = igRegistry_GetSectionIndex(ini, g_memoryPoolsSectionName, 0);
        if (index == -1) {
            return g_resultFailure;
        }
    }
    unsigned int count = igRegistry_GetNumValuesInSection((int)ini, index);
    igSmartPointer<igStringObj> key;
    igSmartPointer<igStringObj> infoSection;
    igSmartPointer<igMemoryPoolInfo> poolInfo;
    for (unsigned int i = 0; i < count; i++) {
        if (!igRegistry_GetKeyName((int)ini, index, i, &key.p)) {
            break;
        }
        if (igRegistry_GetValueStringObj(ini, index, igStringObj_Text(key), &infoSection.p, (const char *)"", 0)
            && infoSection.p != 0 && infoSection->_length != 0) {
            bool created;
            poolInfo = igMemoryPoolContextInfo_FindMemoryPoolInfoByName(self, (int)igStringObj_Text(key));
            if (poolInfo.p == 0) {
                igMemoryPoolView *pool = igObject_GetAllocator((igObject *)self);
                poolInfo.release();
                poolInfo.p = (igMemoryPoolInfo *)igMemoryPoolInfo_Create((int)pool);
                created = true;
            } else {
                { igMemoryPoolInfo *info = poolInfo; SETSTR(_aliasedTo) }
                poolInfo->_size = 0;
                poolInfo->_maxSize = 0;
                poolInfo->_address = 0;
                { igMemoryPoolInfo *info = poolInfo; SETSTR(_class) }
                { igMemoryPoolInfo *info = poolInfo; SETSTR(_arenaType) }
                { igMemoryPoolInfo *info = poolInfo; SETSTR(_source) }
                { igMemoryPoolInfo *info = poolInfo; SETSTR(_scope) }
                created = false;
            }
            igInfoView *loader = (igInfoView *)poolInfo.p;
            if (loader->ReadFromRegistry(ini, igStringObj_Text(infoSection)) == g_resultSuccess) {
                if (poolInfoName(poolInfo) == 0 || *poolInfoName(poolInfo) == 0) {
                    igNamedObject_SetName((igNamedObject *)poolInfo.p, (const char *)igStringObj_Text(key));
                }
                char *handle = (char *)poolInfo->_handleName;
                if (handle != 0 && *handle != 0) {
                    igMemoryPoolInfo *previous = igMemoryPoolContextInfo_FindMemoryPoolInfoByHandle(self, handle);
                    if (previous != poolInfo.p) {
                        igMemoryPoolContextInfo_RemoveMemoryPoolInfo(self, previous);
                    }
                }
            }
            if (created) {
                igMemoryPoolContextInfo_AddMemoryPoolInfo(self, (int)poolInfo.p);
            }
        }
    }
    return g_resultSuccess;
}

/* Print the context's name, then each of its memory pool infos after a blank line. */
void igMemoryPoolContextInfo_Print(igMemoryPoolContextInfoView *self) {
    int count = igMemoryPoolContextInfo_GetMemoryPoolInfoCount(self);
    int i;
    igInfoView *info;
    igReport_Printf("igMemoryPoolContextInfo:  %s\n", self->_name != 0 ? (const char *)self->_name : (const char *)emptyString);
    igReport_Flush();
    for (i = 0; i < count; i++) {
        if ((info = (igInfoView *)igMemoryPoolContextInfo_GetMemoryPoolInfo(self, i)) != 0) {
            igReport_Printf(newline_2);
            igReport_Flush();
            info->Print();
        }
    }
}
