void *igPageMemoryPool_Initialize(igPageMemoryPool *self) {
    igMemoryPool_Initialize((int **)self);
    self->_vtable = (int)(&g_igPageMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

void *igPageMemoryPool_CopyConstruct(igPageMemoryPool *self, int extra1) {
    igMemoryPool_CopyConstruct((igMemoryPool *)self, (igMemoryPool *)extra1);
    self->_vtable = (int)&g_igPageMemoryPool_vtable[0];
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    return self;
}

/* igPageMemoryPool slot 2: tail-call forwarder to the igObject slot-0 body, which is empty; the
 * pool adds no teardown of its own in this slot. */
void igPageMemoryPool_Destruct(int extra0) {
    igMemoryPool_Destruct(extra0);
}

void Gap__Core__igPageMemoryPool__constructFields(int extra0, int extra1) {
    Gap__Core__igObject__constructFields((igObject *)extra0, extra1);
}

void Gap__Core__igPageMemoryPool__destructFields(igPageMemoryPoolView *self) {
    igMemoryPoolView *alloc = (igMemoryPoolView *)((void *)((Gap::Core::igObject *)self)->getMemoryPool());
    int i;
    for (i = 0; i < 32; i++) {
        if (self->pageTables[i] != 0) {
            alloc->Free(self->pageTables[i]);
            self->pageTables[i] = 0;
        }
    }
    Gap__Core__igObject__destructFields((igObject *)self);
}

/* Initialise the pool: run the igObject base step (an empty stub), take the default
 * `_poolOptionFlags` from a global word (6 in the retail image) and clear the page tables that
 * follow the reflected fields. */
void Gap__Core__igPageMemoryPool__resetFields(igPageMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((igObject *)self, extra1);
    self->_poolOptionFlags = g_igPageMemoryPool_defaultPoolOptionFlags;
    memset(((igPageMemoryPoolView *)self)->pageTables, 0, sizeof(((igPageMemoryPoolView *)self)->pageTables));
}

igResult igPageMemoryPool_Configure(igPageMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result;
    result = igMemoryPool_Configure((void **)self, (void *)info);
    const char *options = igMemoryPoolInfo_options(info);
    const char *messages = igMemoryPoolInfo_messages(info);
    const char *source = igMemoryPoolInfo_source(info);
    if (options != 0) {
        int flags = 0;
        if (strstr(options, (char *)"Fill") != 0) {
            flags |= 1;
        }
        if (strstr(options, (char *)"Zero") != 0) {
            flags |= 2;
        }
        if (strstr(options, (char *)"Physical") != 0) {
            flags |= 8;
        }
        if (strstr(options, (char *)"AutoLock") != 0) {
            flags |= 4;
        }
        if (strstr(options, (char *)"SystemMemoryExhausted") != 0) {
            flags |= 0x20;
        }
        if (strstr(options, (char *)"MaxSizeReached") != 0) {
            flags |= 0x10;
        }
        igPageMemoryPool_SetPoolOptionFlags(self, flags);
    }
    if (source != 0 && strstr(source, (char *)"Physical") != 0) {
        igPageMemoryPool_SetPoolOptionFlags(self, self->_poolOptionFlags | 8);
    }
    if (messages != 0) {
        int level = self->_messageLevel;
        if (strstr(messages, (char *)"NoMessages") != 0) {
            level = 0;
        } else if (strstr(messages, (char *)"ErrorMessages") != 0) {
            level = 1;
        } else if (strstr(messages, (char *)"WarningMessages") != 0) {
            level = 2;
        } else if (strstr(messages, (char *)"Notifications") != 0) {
            level = 3;
        }
        self->_messageLevel = level;
    }
    return result;
}

void igPageMemoryPool_Activate(igPageMemoryPool *self) {
    if (self->_isActive == 0) {
        ((igMemoryPoolView *)self)->ResetStatistics();
        self->_isActive = 1;
        if (self->_poolOptionFlags & 4) {
            igResult r = ((igMemoryPoolView *)self)->EnableAllocationLock(1);
        }
    }
}

void igPageMemoryPool_Reset(igPageMemoryPoolView *self) {
    igMemoryPoolView *alloc;
    int i;
    unsigned **table;
    unsigned *pages;
    self->ResetStatistics();
    alloc = (igMemoryPoolView *)((Gap::Core::igObject *)self)->getMemoryPool();
    i = 0;
    do {
        table = &self->pageTables[i];
        pages = *table;
        if (pages != 0) {
            alloc->Free(pages);
            *table = 0;
        }
        i++;
    } while (i < 32);
}

unsigned char g_igPageMemoryPool_ignoreE84Notice;
unsigned char g_igPageMemoryPool_ignoreE85Notice;

void igPageMemoryPool_Deactivate(igPageMemoryPool *self) {
    int r;
    if (self->_isActive != 0) {
        if ((int)self->_localNetAllocated != 0) {
            if (self->_messageLevel >= 3 && g_igPageMemoryPool_ignoreE84Notice == 0) {
                r = igReportNotice("igPageMemoryPool[%d](E84) being reset with outstanding memory blocks of %d bytes.\n", self->_poolIndex, (int)self->_localNetAllocated);
                if (r != 1 && r == 2) {
                    g_igPageMemoryPool_ignoreE84Notice = 1;
                }
            }
            ((igMemoryPoolView *)self)->DisplayOutstandingAllocations();
        } else {
            if (self->_localNetAllocationCount != 0) {
                if (self->_messageLevel >= 3 && g_igPageMemoryPool_ignoreE85Notice == 0) {
                    r = igReportNotice("igPageMemoryPool[%d](E85) being reset with %d outstanding allocations.\n", self->_poolIndex, (int)self->_localNetAllocationCount);
                    if (r != 1 && r == 2) {
                        g_igPageMemoryPool_ignoreE85Notice = 1;
                    }
                }
                ((igMemoryPoolView *)self)->DisplayOutstandingAllocations();
            }
        }
        self->_isActive = 0;
        ((igMemoryPoolView *)self)->Reset();
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

int igPageMemoryPool_IsSecondaryAllocator(igPageMemoryPool *self) {
    return 1;
}

igResult igPageMemoryPool_EnableAllocationLock(igPageMemoryPoolView *self, int enable) {
    int flags;
    if (enable != 0) {
        flags = self->poolOptionFlags | 4;
    } else {
        flags = self->poolOptionFlags & ~4;
    }
    igPageMemoryPool_SetPoolOptionFlags((igPageMemoryPool *)self, flags);
    if ((enable & 0xFF) == 0) {
        igSmartPointer<Gap::Core::igSemaphore> held(self->allocationLock);
        self->allocationLock.clear();
        if (held.p != 0) {
            held.p->obtainResource(true);
            held.p->deactivate();
        }
    } else if ((enable & 0xFF) == 1) {
        if (self->allocationLock.p != 0) {
            return g_resultSuccess.v;
        }
        igSmartPointer<Gap::Core::igSemaphore> created(Gap::Core::igSemaphore::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()));
        created.p->activate();
        self->allocationLock = created;
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

long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
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

long long igPageMemoryPool_GetLocalNetAllocatedHigh(igPageMemoryPool *self) {
    return self->_localNetAllocatedHigh;
}

long long igPageMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igPageMemoryPool *self) {
    return self->_localNetAllocatedWithOverheadHigh;
}

long long igPageMemoryPool_GetSystemAllocated(igPageMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long igPageMemoryPool_GetFreeSize(igPageMemoryPool *self) {
    return self->_maxSize - self->_localNetAllocatedWithOverhead;
}

int igPageMemoryPool_AllocateElement(igPageMemoryPool *self) {
    return 0;
}

void igPageMemoryPool_Lock(igPageMemoryPoolView *self) {
    igResult waited;
    Gap::Core::igSemaphore *lock;

    lock = self->allocationLock.p;
    if (lock != 0) {
        waited = lock->obtainResource(true);
    }
}

int igPageMemoryPool_UnlockAndReturn(igPageMemoryPoolView *self, int result) {
    igResult signalled;
    Gap::Core::igSemaphore *lock;

    lock = self->allocationLock.p;
    if (lock != 0) {
        signalled = lock->releaseResource();
    }
    return result;
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

void igPageMemoryPool_GangAlloc(int *status) {
    *status = g_resultFailure.v;
}

void igPageMemoryPool_GangAllocAligned(int *status) {
    *status = g_resultFailure.v;
}

void igPageMemoryPool_GangFree(void) {

}

void igPageMemoryPool_Free(igPageMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, 0);
}

unsigned int igPageMemoryPool_OwnsAllocation(igPageMemoryPoolView *self, void *block)
{
    return self->IsPageAllocated(block);
}

int Gap__Core__igPageMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int igPageMemoryPool_GetAllocationSize(igPageMemoryPoolView *self, void *block)
{
    return self->GetBlockSize(block);
}

void igPageMemoryPool_SetPoolOptionFlags(igPageMemoryPool *self, int flags)
{
    self->_poolOptionFlags = flags;
}

int igPageMemoryPool_GetEventTracker(igPageMemoryPool *self) {
    return self->_eventTracker;
}

void igPageMemoryPool_SetEventTracker(igPageMemoryPool *self, igObject *tracker) {
    igObject *o;
    if (tracker == 0 || (void *)((Gap::Core::igObject *)tracker)->getMemoryPool() != self) {
        igObject::ref(tracker);
        o = (igObject *)self->_eventTracker;
        igObject::release(o);
        self->_eventTracker = (int)tracker;
    }
}

void igPageMemoryPool_Dump(void) {

}

int igPageMemoryPool_GetPoolIndex(igPageMemoryPool *self) {
    return self->_poolIndex;
}

void igPageMemoryPool_SetPoolIndex(igPageMemoryPool *self, int index) {
    self->_poolIndex = index;
}

unsigned char g_igPageMemoryPool_ignoreE110Notice;
unsigned char g_igPageMemoryPool_ignoreE101Notice;
unsigned char g_igPageMemoryPool_ignoreE91Notice;
unsigned char g_igPageMemoryPool_ignoreE94Notice;

/* The page pool's allocate / reallocate / free core: size -1 frees `block`; otherwise the size is
 * rounded up to whole 4KB pages and the block (re)allocated from the system allocator, with the
 * out-of-memory hook given a chance to make room before the maximum size refuses the request. */
void *igPageMemoryPool_MemoryOperation(igPageMemoryPoolView *self, void *block, int size, unsigned short alignment) {
    unsigned int blockSize = 0;
    void *result;
    void *pages;
    int r;

    if (hasPageOption(self->poolOptionFlags, 0x40)) {
        if (self->messageLevel >= 2 && g_igPageMemoryPool_ignoreE110Notice == 0) {
            r = igReportNotice("igPageMemoryPool(E110): Assert-on-memory-operation is in effect and %s was requested.",
                               (size == -1 && block == 0) ?"a deallocation" :"an allocation");
            if (r != 1 && r == 2) {
                g_igPageMemoryPool_ignoreE110Notice = 1;
            }
        }
        if (self->HandleOutOfMemory(size, 4) == 0) {
            return 0;
        }
    }
    igPageMemoryPool_Lock(self);
    if (alignment < 4096) {
        alignment = 4096;
    }
    for (;;) {
        if (size == -1) {
            result = 0;
            blockSize = block != 0 ? self->GetBlockSize(block) : 0;
            if (blockSize != 0 && hasPageOption(self->poolOptionFlags, 1)) {
                memset(block, 0xFD, blockSize);
            }
            if (self->updateStatistics) {
                self->UpdateStatistics(blockSize, blockSize, 0);
            }
            igPageMemoryPool_FreePages(self, (int)block, blockSize);
            break;
        }
        if (size < 4096) {
            size = 4096;
        } else {
            int partial = size % 4096;
            if (partial != 0) {
                size += 4096 - partial;
            }
        }
        if ((unsigned int)(size + (int)self->localNetAllocated) > self->maxSize) {
            if (self->HandleOutOfMemory(size, 1) != 0) {
                continue;
            }
            if (hasPageOption(self->poolOptionFlags, 0x10)) {
                if (self->messageLevel > 0) {
                    if ((unsigned int)(size + (int)self->localNetAllocated) > self->maxSize && self->messageLevel > 0) {
                        Memory_PrintPoolStatistics(0, self);
                        if (g_igPageMemoryPool_ignoreE101Notice == 0) {
                            r = igReportNotice("igPageMemoryPool(E101): Maximum memory size limit of %d bytes reached.  %d bytes already allocated.", (int)self->maxSize, (int)self->localNetAllocated);
                            if (r != 1 && r == 2) {
                                g_igPageMemoryPool_ignoreE101Notice = 1;
                            }
                        }
                    }
                }
            } else if (self->messageLevel >= 3 && g_igPageMemoryPool_ignoreE91Notice == 0) {
                r = igReportNotice("igPageMemoryPool::memoryOperation[%d](E91) - Operation refused request of %d bytes\nPool has already allocated %u bytes of maximum %u bytes\n", self->poolIndex, size, (int)self->localNetAllocated, (int)self->maxSize);
                if (r != 1 && r == 2) {
                    g_igPageMemoryPool_ignoreE91Notice = 1;
                }
            }
            result = 0;
            break;
        }
        if (block != 0) {
            blockSize = self->GetBlockSize(block);
            if (alignment <= 4096) {
                pages = (void *)igPageMemoryPool_ReallocatePages(self, (int)block, size, blockSize);
            } else {
                pages = (void *)igPageMemoryPool_AllocatePagesAligned(self, alignment, size);
            }
        } else if (alignment > 4096) {
            pages = (void *)igPageMemoryPool_AllocatePagesAligned(self, alignment, size);
        } else {
            pages = (void *)igPageMemoryPool_AllocatePages(self, size);
        }
        if (pages != 0) {
            if (block != 0 && alignment > 4096) {
                if (self->updateStatistics) {
                    self->UpdateStatistics(blockSize, blockSize, 0);
                }
                igPageMemoryPool_FreePages(self, (int)block, blockSize);
            }
            if (self->updateStatistics) {
                self->UpdateStatistics(size, size, 1);
            }
            result = pages;
        } else {
            if (self->messageLevel >= 3 && g_igPageMemoryPool_ignoreE94Notice == 0) {
                r = igReportNotice("igPageMemoryPool::memoryOperation[%d](E94) - Operation failed on request of %d bytes\n", self->poolIndex, size);
                if (r != 1 && r == 2) {
                    g_igPageMemoryPool_ignoreE94Notice = 1;
                }
            }
            result = 0;
        }
        if (result != 0 && block == 0) {
            if (hasPageOption(self->poolOptionFlags, 1)) {
                memset(result, 0xCD, size);
            } else if (hasPageOption(self->poolOptionFlags, 2)) {
                memset(result, 0, size);
            }
        }
        break;
    }
    return (void *)igPageMemoryPool_UnlockAndReturn(self, (int)result);
}

int igPageMemoryPool_AllocatePages(igPageMemoryPoolView *self, int size) {
    int pages;

    if (self->poolOptionFlags & 8) {
        pages = (int)g_activeSystemAllocator->AllocateAligned(size);
    } else {
        pages = (int)g_activeSystemAllocator->AllocateSized(size);
    }
    if (pages != 0) {
        self->MarkPages(pages, size, 1);
    }
    return pages;
}

void igPageMemoryPool_FreePages(igPageMemoryPoolView *self, int block, int size) {
    int physical = (self->poolOptionFlags & 8) != 0; /* The flag test is normalised to 0/1 first; a `bool physical = flags & 8` idiom would drop the sltu. */
    if (physical) {
        g_activeSystemAllocator->FreeAligned((void *)block, size);
    } else {
        g_activeSystemAllocator->FreeSized((void *)block, size);
    }
    if (block != 0) {
        self->MarkPages(block, size, 0);
    }
}

int igPageMemoryPool_ReallocatePages(igPageMemoryPoolView *self, int block, int size, int oldSize) {
    int pages;
    if ((block != 0) && (size == oldSize)) {
        return block;
    }
    if (block != 0) {
        self->MarkPages(block, oldSize, 0);
    }
    if (self->poolOptionFlags & 8) {
        pages = (int)g_activeSystemAllocator->ReallocateAligned((void *)block, size, oldSize);
    } else {
        pages = (int)g_activeSystemAllocator->ReallocateSized((void *)block, size, oldSize);
    }
    if (pages != 0) {
        self->MarkPages(pages, size, 1);
    }
    return pages;
}

int igPageMemoryPool_AllocatePagesAligned(igPageMemoryPoolView *self, int alignment, int size) {
    int pages;

    if (self->poolOptionFlags & 8) {
        pages = (int)g_activeSystemAllocator->AllocateAligned(size);
    } else {
        pages = (int)g_activeSystemAllocator->AllocateSized(size);
    }
    if (pages != 0) {
        self->MarkPages(pages, size, 1);
    }
    return pages;
}

int igPageMemoryPool_IsPageAllocated(igPageMemoryPoolView *self, unsigned int address) {
    unsigned int *t;
    unsigned int v;
    t = self->pageTables[address >> 27];
    if (t == 0) return 0;
    v = (address & 0x7ffffff) >> 12;
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
        if (t == 0) { t = (unsigned int *)((igMemoryPoolView *)((void *)((Gap::Core::igObject *)self)->getMemoryPool()))->Callocate(0x800, 4); self->pageTables[a >> 27] = t; }
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
        if (t == 0) { t = (unsigned int *)((igMemoryPoolView *)((void *)((Gap::Core::igObject *)self)->getMemoryPool()))->Callocate(0x800, 4); *slot = t; }
        if (set != 0) t[idx] |= bit; else t[idx] &= ~bit;
    }
}

unsigned char g_igPageMemoryPool_ignoreGetBlockSizeNotice;

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
                if (g_igPageMemoryPool_ignoreGetBlockSizeNotice == 0) {
                    int r = igReportNotice((const char *)"igPageMemoryPool::getBlockSize - Should not be reached.");
                    if (r != 1 && r == 2) {
                        g_igPageMemoryPool_ignoreGetBlockSizeNotice = 1;
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
                            igReport_Printf((const char *)"    Outstanding allocation at 0x%08x size %d\n", address, self->GetBlockSize((void *)address));
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

