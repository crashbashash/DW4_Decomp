void *igPageMemoryPool_Initialize(igPageMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *igPageMemoryPool_CopyConstruct(igPageMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((igMemoryPool *)arg0, (igMemoryPool *)extra1);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

/* igPageMemoryPool slot 2: tail-call forwarder to the igObject slot-0 body, which is empty; the
 * pool adds no teardown of its own in this slot. */
void igPageMemoryPool_Destruct(int extra0) {
    igMemoryPool_Destruct(extra0);
}

void Gap__Core__igPageMemoryPool__constructFields(int extra0, int extra1) {
    Gap__Core__igObject__constructFields(extra0, extra1);
}

void Gap__Core__igPageMemoryPool__destructFields(igPageMemoryPoolView *self) {
    igMemoryPoolView *alloc = (igMemoryPoolView *)((void *)igObject_GetAllocator((int)self));
    int i;
    for (i = 0; i < 32; i++) {
        if (self->pageTables[i] != 0) {
            alloc->Free(self->pageTables[i]);
            self->pageTables[i] = 0;
        }
    }
    Gap__Core__igObject__destructFields((int)self);
}

/* Initialise the pool: run the igObject base step (an empty stub), take the default
 * `_poolOptionFlags` from a global word (6 in the retail image) and clear the 128 bytes that
 * follow the reflected fields (+0x90). */
void Gap__Core__igPageMemoryPool__resetFields(igPageMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = g_igPageMemoryPool_defaultPoolOptionFlags[0];
    memset((char *)self + 0x90, 0, 0x80);
}

igResult igPageMemoryPool_Configure(igPageMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result;
    result = igMemoryPool_Configure((void **)self, (void *)info);
    const char *options = igMemoryPoolInfo_options(info);
    const char *messages = igMemoryPoolInfo_messages(info);
    const char *source = igMemoryPoolInfo_source(info);
    if (options != 0) {
        int flags = 0;
        if (strstr(options, (char *)text_Fill) != 0) {
            flags |= 1;
        }
        if (strstr(options, (char *)text_Zero) != 0) {
            flags |= 2;
        }
        if (strstr(options, (char *)text_Physical) != 0) {
            flags |= 8;
        }
        if (strstr(options, (char *)text_AutoLock) != 0) {
            flags |= 4;
        }
        if (strstr(options, (char *)text_SystemMemoryExhausted) != 0) {
            flags |= 0x20;
        }
        if (strstr(options, (char *)text_MaxSizeReached) != 0) {
            flags |= 0x10;
        }
        igPageMemoryPool_SetPoolOptionFlags(self, flags);
    }
    if (source != 0 && strstr(source, (char *)text_Physical) != 0) {
        igPageMemoryPool_SetPoolOptionFlags(self, self->_poolOptionFlags | 8);
    }
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

void igPageMemoryPool_Activate(igPageMemoryPool *self) {
    if (self->_isActive == 0) {
        ((igMemoryPoolView *)self)->vfunc_51();
        self->_isActive = 1;
        if (self->_poolOptionFlags & 4) {
            igResult r = ((igMemoryPoolView *)self)->vfunc_34(1);
        }
    }
}

void igPageMemoryPool_Reset(void **arg0) {
    void **alloc;
    int i;
    int *q;
    int v;
    ((igMemoryPoolView *)(arg0))->vfunc_51();
    alloc = (void **)(((void *)igObject_GetAllocator((int)arg0)));
    i = 0;
    do {
        q = (int *)((char *)arg0 + i * 4 + 144);
        v = *q;
        if (v != 0) {
            ((igMemoryPoolView *)alloc)->Free((void *)v);
            *q = 0;
        }
        i++;
    } while (i < 0x20);
}

void igPageMemoryPool_Deactivate(igPageMemoryPool *self) {
    int r;
    if (self->_isActive != 0) {
        if ((int)self->_localNetAllocated != 0) {
            if (self->_messageLevel >= 3 && GPR_00554dc0 == 0) {
                r = igReportNotice(DAT_004ff240, self->_poolIndex, (int)self->_localNetAllocated);
                if (r != 1 && r == 2) {
                    GPR_00554dc0 = 1;
                }
            }
            ((igMemoryPoolView *)self)->vfunc_88();
        } else {
            if (self->_localNetAllocationCount != 0) {
                if (self->_messageLevel >= 3 && GPR_00554dc4 == 0) {
                    r = igReportNotice(DAT_004ff2a0, self->_poolIndex, (int)self->_localNetAllocationCount);
                    if (r != 1 && r == 2) {
                        GPR_00554dc4 = 1;
                    }
                }
                ((igMemoryPoolView *)self)->vfunc_88();
            }
        }
        self->_isActive = 0;
        ((igMemoryPoolView *)self)->vfunc_31();
    }
}

/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char igPageMemoryPool_IsActive(igPageMemoryPool *self) {
    return self->_isActive;
}

int igPageMemoryPool_GetRawMemory(igPageMemoryPool *self) {
    return 0;
}

/* IgPageMemoryPool vtable slot 24: status leaf. Same leaf as igMallocMemoryPool slot 24. Ignores
 * the pool and writes the engine's failure-status word (the one an allocation failure publishes)
 * through the output-first argument. */
void igPageMemoryPool_SetRawMemory(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

int igPageMemoryPool_IsAlchemyMemory(igPageMemoryPool *self) {
    return 0;
}

int Gap__Core__igPageMemoryPool__vfunc_29(igPageMemoryPool *self) {
    return 1;
}

igResult igPageMemoryPool_EnableAllocationLock(igPageMemoryPoolView *arg1, int arg2) {
    int a1;
    if (arg2 != 0) {
        a1 = arg1->poolOptionFlags | 4;
    } else {
        a1 = arg1->poolOptionFlags & ~4;
    }
    igPageMemoryPool_SetPoolOptionFlags(arg1, a1);
    if ((arg2 & 0xFF) == 0) {
        igSmartPointer<igSemaphoreView> held(arg1->allocationLock);
        arg1->allocationLock.clear();
        if (held.p != 0) {
            held.p->wait(1);
            held.p->destroy();
        }
    } else if ((arg2 & 0xFF) == 1) {
        if (arg1->allocationLock.p != 0) {
            return g_resultSuccess.v;
        }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)igSemaphore_Create((int)(((void *)igObject_GetAllocator((int)arg1)))));
        created.p->create();
        arg1->allocationLock = created;
    }
    return g_resultSuccess.v;
}

/* IgPageMemoryPool vtable slot 35: status leaf. On igMallocMemoryPool this slot sets _size; the
 * page pool has no such field. Ignores the pool and writes the engine's failure-status word (the
 * one an allocation failure publishes) through the output-first argument. */
void igPageMemoryPool_SetSize(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

/* Slot 36 getter: returns the pool's _maxSize field (same field as slot 42). */
long long igPageMemoryPool_GetSize(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's size limit (`_maxSize`, +120) and report success through the status word. */
void igPageMemoryPool_SetMaxSize(int *status, igPageMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_resultSuccess.v;
}

/* Slot 42 getter: returns the pool's _maxSize field (same field as slot 36). */
long long igPageMemoryPool_GetMaxSize(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* IgPageMemoryPool vtable slot 37: status leaf. On igMallocMemoryPool this slot sets _alignment;
 * the page pool has no such field. Ignores the pool and writes the engine's failure-status word
 * (the one an allocation failure publishes) through the output-first argument. */
void igPageMemoryPool_SetAlignment(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

/* igPageMemoryPool slot 38. igAliasMemoryPool fills the same slot with a getter for its
 * `_alignment`; the page pool reports a fixed 0x1000 (4 KiB, one page). */

int igPageMemoryPool_GetAlignment(igPageMemoryPool *self) {
    return PAGE_POOL_ALIGNMENT;
}

/* igPageMemoryPool vtable slot 39: status leaf. On igMallocMemoryPool this slot sets _elementSize;
 * the page pool accepts the call and stores nothing. Ignores the pool and writes the engine's
 * success-status word (zero in the pristine ELF) through the output-first argument. */
void igPageMemoryPool_SetElementSize(int *statusOut) {
    *statusOut = g_resultSuccess.v;
}

/* igPageMemoryPool slot 40. igAliasMemoryPool fills the same slot with a getter for its
 * `_elementSize`; the page pool has no fixed element size and returns zero. */
int igPageMemoryPool_GetElementSize(igPageMemoryPool *self) {
    return 0;
}

long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

/* Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this
 * pool). */
long long igPageMemoryPool_GetLocalNetAllocated(igPageMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Slot 48 getter: returns the pool's _localNetAllocatedWithOverhead field (bytes currently
 * allocated from this pool, overhead included). */
long long igPageMemoryPool_GetLocalNetAllocatedWithOverhead(igPageMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long igPageMemoryPool_GetLocalNetAllocatedHigh(void *arg0) {
    return *(long long *)((char *)arg0 + 32);
}

long long igPageMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *arg0) {
    return *(long long *)((char *)arg0 + 64);
}

long long Gap__Core__igPageMemoryPool__vfunc_101(void *arg0) {
    return *(long long *)((char *)arg0 + 56);
}

long long igPageMemoryPool_GetFreeSize(igPageMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

int igPageMemoryPool_AllocateElement(igPageMemoryPool *self) {
    return 0;
}

void igPageMemoryPool_Lock(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igPageMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->wait(1);
    }
}

int igPageMemoryPool_UnlockAndReturn(void *arg0, int arg1) {
    igResult sp2C;
    void **temp_a1;

    temp_a1 = (void **)((igPageMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp2C = ((igSemaphoreView *)(temp_a1))->signal();
    }
    return arg1;
}

void *igPageMemoryPool_Allocate(igPageMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, 0);
}

void *igPageMemoryPool_AllocateAligned(igPageMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

static inline int hasPageOption(int flags, int mask) { return (flags & mask) != 0; }

void *igPageMemoryPool_Callocate(igPageMemoryPool *self, int count, int size) {
    int total = count * size;
    void *p = ((igPageMemoryPoolView *)self)->MemoryOperation(0, total, 0);
    if (p != 0) {
        if (total != 0) {
            if (hasPageOption(self->_poolOptionFlags, 1) || !hasPageOption(self->_poolOptionFlags, 2)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int igPageMemoryPool_CallocateAligned(igPageMemoryPool *self, int n, int sz) {
    int total = n * sz;
    void *r = ((igPageMemoryPoolView *)self)->MemoryOperation(0, total);
    if (r != 0) {
        if (total != 0) {
            unsigned f = self->_poolOptionFlags;
            if (((f & 1) ? 1 : 0) || !((f & 2) ? 1 : 0)) {
                memset(r, 0, total);
            }
        }
    }
    return (int)r;
}

void *igPageMemoryPool_Reallocate(igPageMemoryPoolView *self, void *block, unsigned int size)
{
    return self->MemoryOperation(block, size, 0);
}

void *igPageMemoryPool_ReallocateAligned(igPageMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->MemoryOperation(block, size, alignment);
}

void igPageMemoryPool_GangAlloc(int *arg0) {
    *arg0 = g_resultFailure.v;
}

void igPageMemoryPool_GangAllocAligned(int *arg0) {
    *arg0 = g_resultFailure.v;
}

void igPageMemoryPool_GangFree(void) {

}

void igPageMemoryPool_Free(igPageMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, 0);
}

unsigned int igPageMemoryPool_OwnsAllocation(igPageMemoryPoolView *self, void *block)
{
    return self->vfunc_103(block);
}

int Gap__Core__igPageMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int igPageMemoryPool_GetAllocationSize(igPageMemoryPoolView *self, void *block)
{
    return self->GetBlockSize(block);
}

void igPageMemoryPool_SetPoolOptionFlags(void *a0, int a1)
{
    *(int *)((char *)a0 + 140) = a1;
}

int igPageMemoryPool_GetEventTracker(void *arg0) {
    return *(int *)((char *)(arg0) + 128);
}

void igPageMemoryPool_SetEventTracker(igPageMemoryPool *self, igObject *tracker) {
    igObject *o;
    if (tracker == 0 || (void *)igObject_GetAllocator((int)tracker) != self) {
        if (tracker != 0) {
            tracker->_refCount++;
        }
        o = (igObject *)self->_eventTracker;
        if (o != 0) {
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(o);
            }
        }
        self->_eventTracker = (int)tracker;
    }
}

void igPageMemoryPool_Dump(void) {

}

int igPageMemoryPool_GetPoolIndex(void *arg0) {
    return *(int *)((char *)(arg0) + 132);
}

void igPageMemoryPool_SetPoolIndex(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 132) = arg1;
}

int igPageMemoryPool_AllocatePages(igPageMemoryPoolView *arg0, int arg1) {
    int var_v0;

    if (arg0->poolOptionFlags & 8) {
        var_v0 = (int)g_activeSystemAllocator[0]->AllocateAligned(arg1);
    } else {
        var_v0 = (int)g_activeSystemAllocator[0]->AllocateSized(arg1);
    }
    if (var_v0 != 0) {
        arg0->vfunc_104(var_v0, arg1, 1);
    }
    return var_v0;
}

void igPageMemoryPool_FreePages(igPageMemoryPoolView *arg0, int arg1, int arg2) {
    int t = (arg0->poolOptionFlags & 8) != 0; /* The flag test is normalised to 0/1 first; a `bool t = flags & 8` idiom would drop the sltu. */
    if (t) {
        g_activeSystemAllocator[0]->FreeAligned((void *)arg1, arg2);
    } else {
        g_activeSystemAllocator[0]->FreeSized((void *)arg1, arg2);
    }
    if (arg1 != 0) {
        arg0->vfunc_104(arg1, arg2, 0);
    }
}

int igPageMemoryPool_ReallocatePages(igPageMemoryPoolView *arg0, int arg1, int arg2, int arg3) {
    int r;
    if ((arg1 != 0) && (arg2 == arg3)) {
        return arg1;
    }
    if (arg1 != 0) {
        arg0->vfunc_104(arg1, arg3, 0);
    }
    if (arg0->poolOptionFlags & 8) {
        r = (int)g_activeSystemAllocator[0]->ReallocateAligned((void *)arg1, arg2, arg3);
    } else {
        r = (int)g_activeSystemAllocator[0]->ReallocateSized((void *)arg1, arg2, arg3);
    }
    if (r != 0) {
        arg0->vfunc_104(r, arg2, 1);
    }
    return r;
}

int igPageMemoryPool_AllocatePagesAligned(igPageMemoryPoolView *arg0, int arg1, int arg2) {
    int v;

    if (arg0->poolOptionFlags & 8) {
        v = (int)g_activeSystemAllocator[0]->AllocateAligned(arg2);
    } else {
        v = (int)g_activeSystemAllocator[0]->AllocateSized(arg2);
    }
    if (v != 0) {
        arg0->vfunc_104(v, arg2, 1);
    }
    return v;
}

int igPageMemoryPool_IsPageAllocated(igPageMemoryPoolView *self, unsigned int arg1) {
    unsigned int *t;
    unsigned int v;
    t = self->pageTables[arg1 >> 27];
    if (t == 0) return 0;
    v = (arg1 & 0x7ffffff) >> 12;
    return ((1 << ((v & 0xF) * 2)) & t[v >> 4]) != 0;
}

void igPageMemoryPool_MarkPages(igPageMemoryPoolView *self, unsigned int a, int n, int set) {
    {
        unsigned int idx, bit;
        unsigned int *t;
        unsigned int pg;
        t = self->pageTables[a >> 27];
        pg = (a & 0x7ffffff) >> 12;
        idx = pg >> 4;
        bit = 1 << ((pg & 0xF) * 2);
        if (t == 0) { t = (unsigned int *)((igMemoryPoolView *)((void *)igObject_GetAllocator((int)self)))->vfunc_56(0x800, 4); self->pageTables[a >> 27] = t; }
        if (set != 0) t[idx] |= bit; else t[idx] &= ~bit;
    }
    if (n > 0) n -= 1;
    a += n;
    {
        unsigned int *t;
        unsigned int pg;
        unsigned int **slot;
        unsigned int idx;
        unsigned int bit;
        slot = (unsigned int **)(char *)self->pageTables + (a >> 27); /* the char * conversion keeps retail's addu operand order */
        t = *slot;
        pg = (a & 0x7ffffff) >> 12;
        idx = pg >> 4;
        bit = 2 << ((pg & 0xF) * 2);
        if (t == 0) { t = (unsigned int *)((igMemoryPoolView *)((void *)igObject_GetAllocator((int)self)))->vfunc_56(0x800, 4); *slot = t; }
        if (set != 0) t[idx] |= bit; else t[idx] &= ~bit;
    }
}

/* Size of the block that starts at `block`, 0 when no block starts there. A table word holds two
 * bits per page, "first page of a block" (even bits) and "last page of a block" (odd bits,
 * 0xAAAAAAAA); the size is counted page by page up to the first last-page bit. */
unsigned igPageMemoryPool_GetBlockSize(igPageMemoryPoolView *self, void *block) {
    unsigned slot = (unsigned)block >> 27;
    unsigned *tbl = self->pageTables[slot];
    unsigned size = 4096;
    unsigned page;
    unsigned bit;
    unsigned end;
    unsigned word;
    unsigned mask;
    if (tbl == 0) {
        return 0;
    }
    page = ((unsigned)block & 0x7ffffff) >> 12;
    bit = page & 15;
    word = page >> 4;
    end = 2 << (bit * 2);
    if (((1 << (bit * 2)) & tbl[word]) == 0) {
        return 0;
    }
    if ((tbl[word] & 0xAAAAAAAA) != 0) {
        for (; end != 0; end <<= 2) {
            if (end & tbl[word]) {
                return size;
            }
            size += 4096;
        }
    } else {
        size += (16 - bit) << 12;
    }
    for (;;) {
        word++;
        if (word >= 2048) {
            slot++;
            if (slot >= 32) {
                return 0;
            }
            word = 0;
            tbl = self->pageTables[slot];
            if (tbl == 0) {
                return 0;
            }
        }
        if ((tbl[word] & 0xAAAAAAAA) != 0) {
            for (mask = 2; mask != 0; mask <<= 2) {
                if (mask & tbl[word]) {
                    return size;
                }
                size += 4096;
            }
            if (self->messageLevel >= 1) {
                Memory_PrintPoolStatistics(0, self);
                if (GPR_00554dd8 == 0) {
                    int r = igReportNotice((const char *)text_igPageMemoryPool_getBlockSize_Sh);
                    if (r != 1 && r == 2) {
                        GPR_00554dd8 = 1;
                    }
                }
            }
        } else {
            size += 0x10000;
        }
    }
}

void igPageMemoryPool_DisplayOutstandingAllocations(igPageMemoryPoolView *self) {
    int table;
    unsigned int *bits;
    unsigned int word;
    unsigned int page;
    int address;
    int tableBase;

    table = 0;
    do {
        bits = self->pageTables[table];
        word = 0;
        if (bits != 0) {
            tableBase = table << 27;
            do {
                if (*bits != 0) {
                    page = 0;
                    do {
                        if (*bits & (1 << page)) {
                            address = (page << 12) + (tableBase + (word << 17));
                            igReport_Printf((const char *)DAT_004fc120, address, self->GetBlockSize((void *)address));
                            igReport_Flush();
                        }
                        page++;
                    } while (page < 32U);
                }
                word++;
                bits++;
            } while (word < 0x800U);
        }
        table++;
    } while (table < 32);
}

void igPageMemoryPool_PrintStatistics(int extra0, int extra1) {
    igMemoryPool_PrintStatistics((igMemoryPool *)extra0, (char *)extra1);
}

void igPageMemoryPool_CollectMemoryRegions(void) {
    igMemoryPool_CollectMemoryRegions();
}

