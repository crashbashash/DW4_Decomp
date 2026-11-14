igResult Gap__Core__igMallocMemoryPool__vfunc_45(igMallocMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result;
    result = FUN_002f0880((void **)self, (void *)info);
    const char *messages = igMemoryPoolInfo_messages(info);
    if (messages != 0) {
        int level = self->_messageLevel;
        if (strstr(messages, (char *)text_NoMessages) != 0) {
            level = 0;
        } else if (strstr(messages, (char *)text_ErrorMessages) != 0) {
            level = 1;
        } else if (strstr(messages, (char *)text_WarningMessages) != 0) {
            level = 2;
        } else if (strstr(messages, (char *)text_Notifications) != 0) {
            level = 3;
        }
        self->_messageLevel = level;
    }
    return result;
}

/* Empties the pool and marks it active: the 64-bit _size (+136) is cleared and _isActive (+112)
 * set. */
void Gap__Core__igMallocMemoryPool__vfunc_30(igMallocMemoryPool *self) {
    self->_size = 0;
    self->_isActive = 1;
}

igResult Gap__Core__igMallocMemoryPool__vfunc_34(igMallocMemoryPoolView *arg1, unsigned char arg2) {
    igResult a;
    igResult b;
    igResult c;
    if (arg2 == 0) {
        igSmartPointer<igSemaphoreView> held(arg1->_allocationLock);
        arg1->_allocationLock.clear();
        if (held.p != 0) {
            a = held.p->wait(1);
            b = held.p->destroy();
        }
        arg1->_allocationLock.clear();
    } else if (arg2 == 1) {
        if (arg1->_allocationLock.p != 0) return igResult(g_resultSuccess.v);
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)arg1)))));
        c = created.p->create();
        arg1->_allocationLock = created;
    }
    return igResult(g_resultSuccess.v);
}

void Gap__Core__igMallocMemoryPool__vfunc_35(int *outStatus, igMallocMemoryPool *self, long long size) {
    self->_size = size;
    *outStatus = g_resultSuccess.v;
}

/* Accessor: the pool's reflected _size field (igUnsignedLongMetaField, +136). */
long long Gap__Core__igMallocMemoryPool__vfunc_36(igMallocMemoryPool *self) {
    return self->_size;
}

void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_resultSuccess.v;
}

/* Accessor: the pool's reflected _maxSize field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igMallocMemoryPool__vfunc_42(igMallocMemoryPool *self) {
    return self->_maxSize;
}

void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_resultSuccess.v;
}

/* Returns the pool's allocation alignment, _alignment (+144). */
unsigned short Gap__Core__igMallocMemoryPool__vfunc_38(igMallocMemoryPool *self) {
    return self->_alignment;
}

void Gap__Core__igMallocMemoryPool__vfunc_39(int *status, igMallocMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_resultSuccess.v;
}

int Gap__Core__igMallocMemoryPool__vfunc_40(igMallocMemoryPool *self) {
    return self->_elementSize;
}

long long Gap__Core__igMallocMemoryPool__vfunc_46(igMallocMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

/* Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this
 * pool). */
long long Gap__Core__igMallocMemoryPool__vfunc_47(igMallocMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Slot 48 getter: returns the pool's _localNetAllocatedWithOverhead field (bytes currently
 * allocated from this pool, overhead included). */
long long Gap__Core__igMallocMemoryPool__vfunc_48(igMallocMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long Gap__Core__igMallocMemoryPool__vfunc_99(void *arg0) {
    return *(long long *)((char *)arg0 + 32);
}

long long Gap__Core__igMallocMemoryPool__vfunc_100(void *arg0) {
    return *(long long *)((char *)arg0 + 64);
}

long long Gap__Core__igMallocMemoryPool__vfunc_49(igMallocMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

void *Gap__Core__igMallocMemoryPool__vfunc_53(igMallocMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

void FUN_00322820(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igMallocMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->wait(1);
    }
}

void FUN_00322860(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igMallocMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->signal();
    }
}

int FUN_00322890(void *arg0, int arg1) {
    igResult sp2C;
    void **temp_a1;

    temp_a1 = (void **)((igMallocMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp2C = ((igSemaphoreView *)(temp_a1))->signal();
    }
    return arg1;
}

void *Gap__Core__igMallocMemoryPool__vfunc_54(igMallocMemoryPoolView *self, unsigned int size)
{
    return self->vfunc_101(0, size, self->_alignment);
}

void *Gap__Core__igMallocMemoryPool__vfunc_55(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->vfunc_101(0, size, alignment);
}

static inline int hasPoolOption(int flags, int mask) { return (flags & mask) != 0; }

void *Gap__Core__igMallocMemoryPool__vfunc_56(igMallocMemoryPool *self, int count, int size) {
    int total = count * size;
    void *p = ((igMallocMemoryPoolView *)self)->vfunc_101(0, total, self->_alignment);
    if (p != 0) {
        if (total != 0) {
            if (hasPoolOption(self->_poolOptionFlags, 2) || !hasPoolOption(self->_poolOptionFlags, 4)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int Gap__Core__igMallocMemoryPool__vfunc_57(igMallocMemoryPool *arg0, int arg1, int arg2) {
    int temp_s1;
    void *temp_v0;
    int temp_v1;

    temp_s1 = arg1 * arg2;
    temp_v0 = ((igMallocMemoryPoolView *)arg0)->vfunc_101(0, temp_s1);
    if (temp_v0 != 0) {
        if (temp_s1 != 0) {
            temp_v1 = arg0->_poolOptionFlags;
            if (hasPoolOption(temp_v1, 2) || !hasPoolOption(temp_v1, 4)) {
                memset(temp_v0, 0, temp_s1);
            }
        }
    }
    return (int)temp_v0;
}

void *Gap__Core__igMallocMemoryPool__vfunc_58(igMallocMemoryPoolView *self, void *block, unsigned int size)
{
    return self->vfunc_101(block, size, self->_alignment);
}

void *Gap__Core__igMallocMemoryPool__vfunc_59(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->vfunc_101(block, size, alignment);
}

void Gap__Core__igMallocMemoryPool__vfunc_63(int *arg0) {
    *arg0 = g_resultFailure.v;
}

void Gap__Core__igMallocMemoryPool__vfunc_64(igMallocMemoryPoolView *self, unsigned int size, char **block) {
    char *q = padRecord(blockHeader(*block));
    self->_localFreeCount += *(unsigned short *)(q + 2);
    self->_localNetAllocationCount -= size;
    self->Free((char *)((int)q - 4) - 4);
}

void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c25f8[0];
}

void Gap__Core__igMallocMemoryPool__vfunc_97(igMallocMemoryPool *self) {
    igObject *r;
    self->_refCount = 0;
    ((igRefCountWord *)&self->_refCount)->bits.count = 1;
    *((char *)self + 7) = 0;
    self->_poolIndex = 0;
    ((igMemoryPoolView *)self)->vfunc_51();
    self->_elementSize = 0;
    self->_maxSize = (long long)(unsigned __int128)(unsigned long long)-1LL;
    self->_size = 0;
    self->_alignment = 1;
    r = (igObject *)self->_eventTracker;
    if (r != 0) {
        r->_refCount = r->_refCount - 1;
        if ((r->_refCount & 0x7fffff) == 0) igObject_Destroy(r);
    }
    self->_eventTracker = 0;
    self->_isActive = 0;
    GPR_00554dbc += 1;
    r = (igObject *)self->_allocationLock;
    if (r != 0) {
        r->_refCount = r->_refCount - 1;
        if ((r->_refCount & 0x7fffff) == 0) igObject_Destroy(r);
    }
    self->_allocationLock = 0;
    self->_messageLevel = 1;
    self->_poolOptionFlags = 12;
}

void *FUN_003235c0(igMallocMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *FUN_00323600(igMallocMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((igMemoryPool *)arg0, (igMemoryPool *)extra1);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void Gap__Core__igMallocMemoryPool__vfunc_02(igMallocMemoryPool *self) {
    ((igMemoryPoolView *)self)->vfunc_98();
    Gap__Core__igObject__vfunc_00((int)self);
}

void Gap__Core__igMallocMemoryPool__vfunc_66(igMallocMemoryPoolView *self, void *block)
{
    self->vfunc_101(block, -1, self->_alignment);
}

int Gap__Core__igMallocMemoryPool__vfunc_85(int arg0, char *arg1) {
    TaggedBlockHeader *h;
    int v;
    int r;
    int a;

    a = arg0;
    h = (TaggedBlockHeader *)(arg1 - 4);
    if (((TaggedTailByte *)(arg1 - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(arg1 - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        v = h->poolLow * 2;
    } else {
        v = (h->poolLow + (h->poolHigh << 5)) * 2;
    }
    r = (int)igAllocator_ResolveEncodedIndex(v);
    return r == a;
}

int Gap__Core__igMallocMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int Gap__Core__igMallocMemoryPool__vfunc_84(int arg0, char *arg1) {
    TaggedBlockHeader *hdr;

    hdr = (TaggedBlockHeader *)(arg1 - 4);
    if (hdr->big == 1) {
        hdr = (TaggedBlockHeader *)(arg1 - 0xC);
    }
    if (hdr == 0) {
        return 0;
    }
    if (hdr->big == 0) {
        return hdr->size;
    }
    return hdr->size + (hdr->sizeHigh << 0x13);
}

void Gap__Core__igMallocMemoryPool__vfunc_87(igMallocMemoryPool *self, char *title) {
    char buf[64];
    char *name;
    if (title != 0 && title[0] != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
    }
    if (((struct Ctx { char p[36]; int on; } * *)g_objectSystem)[0]->on != 0) {
        name = FUN_00312140(buf, 64, self->_messageLevel, FUN_002ce1b0());
    } else {
        name = ((char *)DAT_004f7910);
    }
    {
        long long netCountHigh = self->_localNetAllocationCountHigh;
        long long netCount = self->_localNetAllocationCount;
        long long freeCount = self->_localFreeCount;
        long long allocationCount = self->_localAllocationCount;
        long long netWithOverheadHigh = self->_localNetAllocatedWithOverheadHigh;
        long long netWithOverhead = self->_localNetAllocatedWithOverhead;
        long long freedWithOverhead = self->_localFreedWithOverhead;
        long long allocatedWithOverhead = self->_localAllocatedWithOverhead;
        long long netAllocatedHigh = self->_localNetAllocatedHigh;
        long long netAllocated = self->_localNetAllocated;
        long long freed = self->_localFreed;
        long long allocated = self->_localAllocated;
        FUN_00304430(DAT_004fef30, (int)allocated, (int)freed, (int)netAllocated, (int)netAllocatedHigh, (int)allocatedWithOverhead, (int)freedWithOverhead, (int)netWithOverhead, (int)netWithOverheadHigh, (int)allocationCount, (int)freeCount, (int)netCount, (int)netCountHigh, (int)((igMemoryPoolView *)self)->vfunc_36(), name);
    }
    FUN_00304680();
}

int Gap__Core__igMallocMemoryPool__vfunc_89(void *arg0) {
    return *(int *)((char *)(arg0) + 148);
}

void Gap__Core__igMallocMemoryPool__vfunc_90(igMallocMemoryPool *self, igObject *tracker) {
    igObject *old;
    if ((tracker == 0) || (((void *)igObject_GetAllocator((int)tracker)) != self)) {
        if (tracker != 0) {
            tracker->_refCount = tracker->_refCount + 1;
        }
        old = (igObject *)self->_eventTracker;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        self->_eventTracker = (int)tracker;
    }
}

void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0) {
    int *g;
    FUN_00322820(self);
    g = &DAT_004ff1b0[0];
    if (t0 != 0) {
        igSmartPointer<igFileView> r((igFileView *)igFile_Create((int)(((void *)igObject_GetAllocator((int)self)))));
        if (r.p->Open((const char *)t0, (const char *)&DAT_004f92f0[0]) == 0) {
            if (((igMallocMemoryPool *)self)->_messageLevel >= 2) {
                FUN_00308390(DAT_004ff1f0, t0);
            }
            FUN_00322860(self);
            return;
        }
        r.p->Print((const char *)g);
        r.p->Close();
    } else {
        printf(g);
    }
    FUN_00322860(self);
}

int Gap__Core__igMallocMemoryPool__vfunc_91(void *arg0) {
    return *(int *)((char *)(arg0) + 120);
}

void Gap__Core__igMallocMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 120) = arg1;
}

static inline int poolIndexAccepts(igMallocMemoryPool *p, int y) { if (p->_poolIndex < 64 && y >= 64) return 0; return 1; }

void Gap__Core__igMallocMemoryPool__vfunc_93(int *arg0, igMallocMemoryPool *arg1, char *arg2, igMemoryPoolView *arg3) {
    int v = arg3->GetPoolIndex();
    int ok;
    TaggedBlockHeader *h;
    int a;
    ok = poolIndexAccepts(arg1, v);
    if (ok != 0) {
        h = (TaggedBlockHeader *)(arg2 - 4);
        if (((TaggedTailByte *)(arg2 - 1))->extended == 1) {
            h = (TaggedBlockHeader *)(arg2 - 12);
        }
        a = arg3->GetPoolIndex() >> 1;
        h->poolLow = a;
        if (h->big == 1) {
            h->poolHigh = a >> 5;
        }
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

int Gap__Core__igMallocMemoryPool__vfunc_94(void *arg0, void **arg1) {
    int temp_v0;
    int var_v0;

    temp_v0 = ((igMemoryPoolView *)(arg1))->GetPoolIndex();
    if ((*(int *)((char *)(arg0) + 120) < 0x40) && (temp_v0 >= 0x40)) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        return 1;
    }
    return 0;
}

int Gap__Core__igMallocMemoryPool__vfunc_95(int arg0, char *arg1) {
    TaggedBlockHeader *h;

    if (arg1 == 0) {
        return -1;
    }
    h = (TaggedBlockHeader *)(arg1 - 4);
    if (((TaggedTailByte *)(arg1 - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(arg1 - 12);
    }
    if (h == 0) {
        return -1;
    }
    if (h->big == 0) {
        return h->poolLow * 2;
    }
    return (h->poolLow + (h->poolHigh << 5)) * 2;
}

/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char Gap__Core__igMallocMemoryPool__vfunc_33(igMallocMemoryPool *self) {
    return self->_isActive;
}

static inline int usesAligned(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x20) != 0; }

static inline int usesSized(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x10) != 0; }

void *FUN_00324be0(igMallocMemoryPoolView *self, unsigned size) {
    unsigned overhead;
    unsigned total;
    void *block;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot = (unsigned)self->_poolIndex >> 1;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total = overhead + size;
    if (usesAligned(self)) {
        block = (*(SystemAllocator * *)g_activeSystemAllocator)->AllocateAligned(total + 4);
    } else if (usesSized(self)) {
        block = (*(SystemAllocator * *)g_activeSystemAllocator)->AllocateSized(total + 4);
    } else {
        block = (*(SystemAllocator * *)g_activeSystemAllocator)->Allocate(total + 4);
    }
    if (block != 0) {
    h = (TaggedBlockHeader *)((char *)block + 4);
    id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = 0;
    h->marked = 0;
    h->used = 0;
    if (size >= 0x80000 || id >= 32) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = 0;
        h->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        h->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    h->words = ((end - aligned) >> 2) - 1;
    h->size = size;
    return (char *)h + (h->big == 0 ? 4 : 12);
    }
    return 0;
}

void FUN_00324ec0(igMallocMemoryPoolView *self, unsigned char *p) {
    TaggedBlockHeader *h = (TaggedBlockHeader *)(p - 4);
    unsigned size;
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    size = h->size;
    if (h->big == 1) {
        size = size + (h->sizeHigh << 19);
    }
    size = (size + 3) & ~3;
    size = size + (h->words + 1) * 4;
    if (h->relocated != 0) {
        int off = *(unsigned short *)((char *)h - 2);
        char *base = (char *)h - off;
        size = size + ((char *)h - base);
        if (usesAligned(self)) {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->FreeAligned(base, size);
        } else if (usesSized(self)) {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->FreeSized(base, size);
        } else {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->Free(base);
        }
    } else {
        char *base = (char *)h - 4;
        if (usesAligned(self)) {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->FreeAligned(base, size + 4);
        } else if (usesSized(self)) {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->FreeSized(base, size + 4);
        } else {
            ((SystemAllocator * *)g_activeSystemAllocator)[0]->Free(base);
        }
    }
}

void *FUN_00325060(igMallocMemoryPoolView *self, char *p, unsigned size) {
    TaggedBlockHeader *h;
    unsigned end;
    unsigned aligned;
    int big;
    char *base;
    char *block;
    unsigned kept;
    unsigned total;
    unsigned index;
    unsigned newOverhead;
    unsigned slot;
    unsigned newSize;
    unsigned oldOverhead;
    unsigned used;
    TaggedBlockHeader *fresh;
    h = (TaggedBlockHeader *)(p - 4);
    if (((TaggedTailByte *)(p - 1))->extended == 1) {
        h = (TaggedBlockHeader *)(p - 12);
    }
    big = h->big;
    if (big == 0) {
        used = h->size;
        kept = used;
    } else {
        used = h->size;
        kept = used + (h->sizeHigh << 19);
    }
    if (big == 1) {
        used += h->sizeHigh << 19;
    }
    used = (used + 3) & ~3;
    total = used + (h->words + 1) * 4;
    oldOverhead = big == 0 ? 4 : 12;
    slot = (unsigned)self->_poolIndex >> 1;
    if (size >= 0x80000 || slot >= 32) {
        newOverhead = 12;
    } else {
        newOverhead = 4;
    }
    base = (char *)h - 4;
    newSize = size + (newOverhead + 4);
    if (newOverhead + 4 < oldOverhead + 4) {
        newSize += oldOverhead - newOverhead;
    }
    if (h->relocated != 0) {
        char *moved = (char *)FUN_00324be0(self, size);
        if (moved != 0) {
            memcpy(moved, p, kept < size ? kept : size);
            FUN_00324ec0(self, (unsigned char *)p);
        }
        return moved;
    }
    if (usesAligned(self)) {
        block = (char *)g_activeSystemAllocator[0]->ReallocateAligned(base, newSize, total + 4);
    } else if (usesSized(self)) {
        block = (char *)g_activeSystemAllocator[0]->ReallocateSized(base, newSize, total + 4);
    } else {
        block = (char *)g_activeSystemAllocator[0]->Reallocate(base, newSize);
    }
    if (block == 0) {
        return 0;
    }
    if (newOverhead + 4 != oldOverhead + 4) {
        memmove(block + (newOverhead + 4), block + (oldOverhead + 4), kept < size ? kept : size);
    }
    fresh = (TaggedBlockHeader *)(block + 4);
    index = (unsigned)self->_poolIndex >> 1;
    fresh->poolLow = index;
    fresh->relocated = 0;
    fresh->marked = 0;
    fresh->used = 0;
    if (size >= 0x80000 || index >= 32) {
        fresh->sizeHigh = size >> 19;
        fresh->poolHigh = index >> 5;
        fresh->big = 1;
        fresh->extraBig = 1;
        fresh->extraUsed = 0;
        fresh->extraMarked = 0;
        fresh->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        fresh->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    fresh->words = ((end - aligned) >> 2) - 1;
    fresh->size = size;
    return (char *)fresh + (fresh->big == 0 ? 4 : 12);
}

static inline int usesAligned_3254a0(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x20) != 0; }

static inline int usesSized_3254a0(igMallocMemoryPoolView *p) { return (p->_poolOptionFlags & 0x10) != 0; }

void *FUN_003254a0(igMallocMemoryPoolView *self, unsigned alignment, unsigned size) {
    unsigned overhead;
    unsigned total;
    char *block;
    char *p;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot;
    unsigned minimum = self->_alignment;
    alignment = minimum < alignment ? alignment : minimum;
    if (alignment <= 3) {
        alignment = 4;
    }
    slot = (unsigned)self->_poolIndex >> 1;
    total = size + alignment;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total += overhead;
    if (usesAligned_3254a0(self)) {
        block = (char *)(*(SystemAllocator * *)g_activeSystemAllocator)->AllocateAligned(total);
    } else if (usesSized_3254a0(self)) {
        block = (char *)(*(SystemAllocator * *)g_activeSystemAllocator)->AllocateSized(total);
    } else {
        block = (char *)(*(SystemAllocator * *)g_activeSystemAllocator)->Allocate(total);
    }
    if (block == 0) {
        return 0;
    }
    p = (char *)((unsigned)(block + alignment) & ~(alignment - 1)) - overhead;
    if (!(p > block)) {
        p += alignment;
    }
    ((short *)p)[-1] = p - block;
    h = (TaggedBlockHeader *)p;
    id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = alignment != 0;
    h->marked = 0;
    h->used = 0;
    if (size >= 0x80000 || id >= 32) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = 0;
        h->extraTag = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 12;
    } else {
        h->big = 0;
        aligned = (size + 3) & ~3;
        end = aligned + 4;
    }
    h->words = ((end - aligned) >> 2) - 1;
    h->size = size;
    return (char *)h + (h->big == 0 ? 4 : 12);
}

