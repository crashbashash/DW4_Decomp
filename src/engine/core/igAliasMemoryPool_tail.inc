int igAliasMemoryPool_GetAliasedMemoryPool(void *self) {
    return (int)((igAliasMemoryPool *)self)->_aliasedMemoryPool;
}

/* Bind `alias` as the pool this one forwards to. The new alias is retained before the previous one
 * is released (so assigning the same object is safe); the previous alias is destroyed when its
 * reference count drops to zero. The alias is then asked (vfunc_94) whether this pool may alias it
 * and the answer becomes _isReassignable; a null alias clears it. */
void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, igMemoryPoolView *alias) {
    igMemoryPoolView *old;
    if (alias) ((igObject *)alias)->_refCount++;
    old = (igMemoryPoolView *)self->_aliasedMemoryPool;
    igObject::release(((igObject *)old));
    self->_aliasedMemoryPool = (int)alias;
    if (alias) self->_isReassignable = alias->CanTransferTo((igMemoryPoolView *)self);
    else self->_isReassignable = 0;
}

/* slot 30, reset the allocation counters and mark the pool active. */
void igAliasMemoryPool_Activate(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
    self->_isActive = 1;
}

/* Slot 31, the same counter reset without touching _isActive. */
void igAliasMemoryPool_Reset(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
}

/* Disable the pool: run the receiver's virtual at vtable offset 124 (the reset callback), then
 * clear _isActive afterwards, even if the callback wrote it. */
void igAliasMemoryPool_Deactivate(igAliasMemoryPool *self) {
    ((igMemoryPoolView *)self)->Reset();
    self->_isActive = 0;
}

/* Slot 33, report whether the pool is active. */
unsigned char igAliasMemoryPool_IsActive(igAliasMemoryPool *self) {
    return self->_isActive;
}

/* Slot 26, fixed result 0. */
int igAliasMemoryPool_GetRawMemory(void) {
    return 0;
}

/* Slot 24, output the allocator failure-status word. */
void igAliasMemoryPool_SetRawMemory(int *outStatus) {
    *outStatus = g_resultFailure.v;
}

/* Slot 25, fixed result 0. */
int igAliasMemoryPool_IsAlchemyMemory(void) {
    return 0;
}

/* Slot 29, fixed result 0. */
int igAliasMemoryPool_IsSecondaryAllocator(void) {
    return 0;
}

static inline void setLock(igAliasMemoryPool *pool, igSemaphoreView *lock) {
    igSemaphoreView *previous;
    if (lock != 0) {
        lock->_refCount = lock->_refCount + 1;
    }
    previous = (igSemaphoreView *)pool->_allocationLock;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    pool->_allocationLock = (int)lock;
}

igResult igAliasMemoryPool_EnableAllocationLock(igAliasMemoryPool *pool, int enable) {
    if ((enable & 0xFF) == 0) {
        igSmartPointer<igSemaphoreView> kept((igSemaphoreView *)pool->_allocationLock);
        kept.retain();
        setLock(pool, 0);
        if (kept.get() != 0) {
            kept.get()->Wait(1);
            kept.get()->Destroy();
        }
    } else if ((enable & 0xFF) == 1) {
        if (pool->_allocationLock != 0) {
            return g_resultSuccess.v;
        }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)igSemaphore_Create((int)(((void *)((Gap::Core::igObject *)pool)->getMemoryPool()))));
        created.get()->Create();
        setLock(pool, created.get());
    }
    return g_resultSuccess.v;
}

/* IgAliasMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument. */
void igAliasMemoryPool_SetSize(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

int igAliasMemoryPool_GetSize(void) {
    return 0;
}

/* Set the pool's size limit (`_maxSize`) and report success through the status word. Sibling
 * setters (vfunc_37 alignment, vfunc_39 element size) share the shape. */
void igAliasMemoryPool_SetMaxSize(int *status, igAliasMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_resultSuccess.v;
}

/* Vtable slot 42: the pool's capacity in bytes (_maxSize). */
long long igAliasMemoryPool_GetMaxSize(igAliasMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's alignment (`_alignment`) and report success through the status word. */
void igAliasMemoryPool_SetAlignment(int *status, igAliasMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_resultSuccess.v;
}

/* IgAliasMemoryPool slot 38, returns the reflected _alignment (+176, unsigned short). */
unsigned short igAliasMemoryPool_GetAlignment(igAliasMemoryPool *self) {
    return self->_alignment;
}

/* IgAliasMemoryPool setter for `_elementSize` (+172). Stores the new element size and reports
 * success through the out cell (the cell receives the shared success status word, see
 * g_resultSuccess). */
void igAliasMemoryPool_SetElementSize(int *status_out, igAliasMemoryPool *self, int element_size) {
    self->_elementSize = element_size;
    *status_out = g_resultSuccess.v;
}

/* IgAliasMemoryPool slot 40, returns the reflected _elementSize (+172). */
int igAliasMemoryPool_GetElementSize(igAliasMemoryPool *self) {
    return self->_elementSize;
}

/* Configures the pool from its info record: the base class's step only. The result is a local
 * copied out, as in the pools that go on to read the info's strings. */
igResult igAliasMemoryPool_Configure(igAliasMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result = igMemoryPool_Configure((void **)self, (void *)info);
    return result;
}

long long Gap__Core__igAliasMemoryPool__vfunc_46(igAliasMemoryPool *self) {
    return self->_maxSize - self->_allocedBytes;
}

/* Vtable slot 47: total bytes currently allocated from the pool (_allocedBytes). */
long long igAliasMemoryPool_GetLocalNetAllocated(igAliasMemoryPool *self) {
    return self->_allocedBytes;
}

/* Accessor: the alias pool's reflected _allocedBytes field (igUnsignedLongMetaField, +128). */
long long igAliasMemoryPool_GetLocalNetAllocatedWithOverhead(igAliasMemoryPool *self) {
    return self->_allocedBytes;
}

long long igAliasMemoryPool_GetLocalNetAllocatedHigh(igAliasMemoryPool *self) {
    return self->_allocedBytesHigh;
}

long long igAliasMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igAliasMemoryPool *self) {
    return self->_allocedBytesHigh;
}

long long igAliasMemoryPool_GetFreeSize(igAliasMemoryPool *self) {
    return self->_maxSize - self->_allocedBytes;
}

void *igAliasMemoryPool_AllocateElement(igAliasMemoryPool *self){return ((igMemoryPoolView *)self)->Allocate(self->_elementSize);}

/* Take the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 132 with 1. The status it returns is discarded. */
void igAliasMemoryPool_Lock(igAliasMemoryPool *self) {
    igResult status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((igSemaphoreView *)(lockObject))->Wait((int)(1));
    }
}

/* Release the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 124. The status it returns is discarded. */
void igAliasMemoryPool_Unlock(igAliasMemoryPool *self) {
    igResult status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((igSemaphoreView *)(lockObject))->Signal();
    }
}

/* Release the pool's allocation lock, then hand back the value the caller supplied: when a lock
 * object is attached (_allocationLock), call its virtual method at vtable offset 124 (the same
 * unlock call as igAliasMemoryPool_Unlock); the status it returns is discarded. This lets a caller
 * write `return igAliasMemoryPool_UnlockAndReturn(pool, result)` to leave a locked section while
 * preserving its result. */
int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result) {
    igResult status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((igSemaphoreView *)(lockObject))->Signal();
    }
    return result;
}

void *igAliasMemoryPool_Allocate(igAliasMemoryPool *self,unsigned int size){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation(0,size,self->_alignment);}

void *igAliasMemoryPool_AllocateAligned(igAliasMemoryPool *self,unsigned int size,unsigned short alignment){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation(0,size,alignment);}

int igAliasMemoryPool_Callocate(igAliasMemoryPool *self, int count, int size) {
    int total;
    int block;
    total = count * size;
    block = ((igAliasMemoryPoolView *)self)->ManageAllocation(0, total, self->_alignment);
    if (block != 0) {
        if (total != 0) {
            memset((void *)block, 0, total);
        }
    }
    return block;
}

int igAliasMemoryPool_CallocateAligned(igAliasMemoryPool *self, int count, int size, unsigned short alignment) {
    int total;
    int block;

    total = count * size;
    block = ((igAliasMemoryPoolView *)self)->ManageAllocation(0, total, alignment);
    if (block != 0) {
        if (total != 0) {
            memset((void *)block, 0, total);
        }
    }
    return block;
}

void *igAliasMemoryPool_Reallocate(igAliasMemoryPool *self,void *old,unsigned int size){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,size,self->_alignment);}

void *igAliasMemoryPool_ReallocateAligned(igAliasMemoryPool *self,void *old,unsigned int size,unsigned short alignment){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,size,alignment);}

int igAliasMemoryPool_AllocateFromSystem(igAliasMemoryPool *self, int size) {
    long long allocatedBefore;
    int result;
    long long added;

    if (self->_aliasedMemoryPool != 0) {
        allocatedBefore = ((igMemoryPoolView *)self->_aliasedMemoryPool)->GetLocalNetAllocatedWithOverhead();
        result = ((igMemoryPoolView *)self->_aliasedMemoryPool)->AllocateFromSystem(size);
        added = ((igMemoryPoolView *)self->_aliasedMemoryPool)->GetLocalNetAllocatedWithOverhead() - allocatedBefore;
        if (self->_updateStatistics != 0) {
            ((igMemoryPoolView *)self)->UpdateStatistics(size, (int)added, 1);
        }
        return result;
    }
    return 0;
}

igResult igAliasMemoryPool_GangAlloc(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        return pool->GangAlloc(count, sizes, blocks);
    }
    return g_resultFailure;
}

igResult igAliasMemoryPool_GangAllocAligned(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks, unsigned short *alignments) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        return pool->GangAllocAligned(count, sizes, blocks, alignments);
    }
    return g_resultFailure;
}

void igAliasMemoryPool_GangFree(igAliasMemoryPool *self, int count, void **blocks) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        pool->GangFree(count, blocks);
    }
}

void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,-1,self->_alignment);}

/* The aliased pool's slot 93 (offset 380) answers its own pool index. */
class AliasedPoolIndexView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual int PoolIndex(); };

/* Whether this pool owns the allocation the registry resolves for the caller's second argument: a
 * reassignable pool compares its index with its alias's; any other asks the allocator registry to
 * resolve the index to a pool and checks that it is this pool. The second argument is forwarded
 * untouched to Memory_LookupAllocation. */
int igAliasMemoryPool_OwnsAllocation(igAliasMemoryPool *self, int poolIndex) {
    int resolved;
    int status;
    if (self->_isReassignable != 0) {
        if (self->_poolIndex == ((AliasedPoolIndexView *)self->_aliasedMemoryPool)->PoolIndex()) {
            return 1;
        }
    } else {
        status = Memory_LookupAllocation(poolIndex, &resolved).get();
        if (status == g_resultSuccess.v) {
            return resolved == (int)self;
        }
    }
    return 0;
}

unsigned int igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old){return ((igMemoryPoolView *)self->_aliasedMemoryPool)->GetAllocationSize(old);}

void igAliasMemoryPool_PrintStatistics(igAliasMemoryPoolView *self, char *name) {
    int netCountHigh;
    long long netCount;
    int freeCount;
    int allocCount;
    const char *poolName;
    long long allocated;
    long long allocatedWithOverhead;
    long long allocatedHigh;
    __int128 allocatedWithOverheadHigh;
    __int128 maxSize;
    if (name != 0 && *name != 0) {
        igReport_Printf("%s:\n");
        igReport_Flush();
    }
    igAliasMemoryPool *pool = (igAliasMemoryPool *)self;
    freeCount = pool->_nFrees;
    allocCount = pool->_nAllocs;
    netCountHigh = pool->_netAllocsHigh;
    netCount = allocCount - freeCount;
    if (self->GetAliasedMemoryPool() != 0) {
        poolName = ((const char *)Memory_GetPoolName(self->GetAliasedMemoryPool()));
    } else {
        poolName ="(null)";
    }
    allocated = self->GetLocalNetAllocated();
    allocatedWithOverhead = (int)self->GetLocalNetAllocatedWithOverhead();
    allocatedHigh = self->GetLocalNetAllocatedHigh();
    allocatedWithOverheadHigh = (long long)self->GetLocalNetAllocatedWithOverheadHigh();
    maxSize = (long long)self->GetMaxSize();
    igReport_Printf("    Aliased memory pool:                  %s\n    Total allocation:                     %u\n    Total allocation with overhead:       %u\n    Total allocation high:                %u\n    Total allocation with overhead high:  %u\n    Allocation count:                     %u\n    Free count:                           %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\n    Max size limit:                       %u\n    Pool index:                           %d\n", poolName, allocated, allocatedWithOverhead, allocatedHigh, allocatedWithOverheadHigh, (long long)allocCount, (long long)freeCount, (long long)(int)netCount, (long long)netCountHigh, (long long)maxSize, self->GetPoolIndex());
    igReport_Flush();
}

/* The pool's event tracker (reflected `_eventTracker`), stored as a raw handle. */
int igAliasMemoryPool_GetEventTracker(igAliasMemoryPool *self) {
    return self->_eventTracker;
}

/* Reference-counted assignment of the _eventTracker field (+0x98). Retain the new tracker, release
 * the previous one (destroying it when its count reaches zero), then store. The refcount is the
 * low 23 bits of igObject::_refCount. */
void igAliasMemoryPool_SetEventTracker(igAliasMemoryPool *self, igObject *tracker) {
    igObject *previous;
    igObject::ref(tracker);
    previous = (igObject *)(self->_eventTracker);
    igObject::release(previous);
    self->_eventTracker = (int)(tracker);
}

void igAliasMemoryPool_Dump(igAliasMemoryPool *self, int a1, int a2, int a3, int t0) {
    const char *g;
    igAliasMemoryPool_Lock(self);
    g = "The method dump() has no meaning for an igAliasMemoryPool\n";
    if (t0 != 0) {
        igSmartPointer<Gap::Core::igFile> r(Gap::Core::igFile::_instantiateFromPool((igMemoryPoolView *)(void *)((Gap::Core::igObject *)self)->getMemoryPool()));
        if (r.p->fopen((const char *)t0, "w") == 0) {
            igAliasMemoryPool_Unlock(self);
            return;
        }
        r.p->fprintf(g);
        r.p->fclose();
    } else {
        printf(g);
    }
    igAliasMemoryPool_Unlock(self);
}

/* The pool's index (reflected `_poolIndex`). */
int igAliasMemoryPool_GetPoolIndex(igAliasMemoryPool *self) {
    return self->_poolIndex;
}

/* Setter for the `_poolIndex` field. */
void igAliasMemoryPool_SetPoolIndex(igAliasMemoryPool *self, int poolIndex) {
    self->_poolIndex = poolIndex;
}

int igAliasMemoryPool_ManageAllocation(igAliasMemoryPool *self, int block, int size, unsigned short alignment) {
    int result = 0;
    long long requested;
    int netCount;
    igAliasMemoryPool_Lock(self);
    if ((alignment & 0xFFFF) < self->_alignment) alignment = self->_alignment;
    requested = size;
    for (;;) {
        if (size == -1) {
            result = 0;
            if (block == 0) {
                igAliasMemoryPool_Unlock(self);
                return 0;
            }
            { int t = ((igMemoryPoolView *)self)->GetAllocationSize((void *)block); self->_allocedBytes = self->_allocedBytes - t; }
            self->_nFrees = self->_nFrees + 1;
            if (self->_isReassignable != 0) {
                igResult unregistered = ((igMemoryPoolView *)self->_aliasedMemoryPool)->TransferAllocation((char *)block, (igMemoryPoolView *)self->_aliasedMemoryPool);
            } else {
                igResult unregistered = Memory_UnregisterAllocation(block, (igMemoryPoolView *)self);
            }
            ((igMemoryPoolView *)self->_aliasedMemoryPool)->Free((void *)block);
            break;
        }
        if (self->_allocedBytes + requested > self->_maxSize) {
            if (((igMemoryPoolView *)self)->HandleOutOfMemory(size, 1) == 0) {
                result = 0;
                break;
            }
            continue;
        }
        if (block != 0) {
            if (self->_aliasedMemoryPool != 0) {
                if (block != 0) {
                    { int t = ((igMemoryPoolView *)self)->GetAllocationSize((void *)block); self->_allocedBytes = self->_allocedBytes - t; }
                    self->_nFrees = self->_nFrees + 1;
                }
                if (self->_isReassignable != 0) {
                    igResult unregistered = ((igMemoryPoolView *)self->_aliasedMemoryPool)->TransferAllocation((char *)block, (igMemoryPoolView *)self->_aliasedMemoryPool);
                } else {
                    igResult unregistered = Memory_UnregisterAllocation(block, (igMemoryPoolView *)self);
                }
                result = (int)((igMemoryPoolView *)self->_aliasedMemoryPool)->ReallocateAligned((void *)block, size, alignment);
            }
        } else {
            if (self->_aliasedMemoryPool != 0) {
                result = (int)((igMemoryPoolView *)self->_aliasedMemoryPool)->AllocateAligned(size, alignment);
            }
        }
        if (result != 0) {
            self->_allocedBytes = self->_allocedBytes + size;
            if (self->_allocedBytesHigh < self->_allocedBytes) self->_allocedBytesHigh = self->_allocedBytes;
            self->_nAllocs = self->_nAllocs + 1;
            netCount = self->_nAllocs - self->_nFrees;
            if (self->_netAllocsHigh < netCount) self->_netAllocsHigh = netCount;
            if (self->_isReassignable != 0) {
                igResult registered = ((igMemoryPoolView *)self->_aliasedMemoryPool)->TransferAllocation((char *)result, (igMemoryPoolView *)self);
            } else {
                igResult registered = Memory_RegisterAllocation(result, (igMemoryPoolView *)self);
            }
        }
        break;
    }
    return igAliasMemoryPool_UnlockAndReturn(self, result);
}

/* Initialization helper of the alias pool: runs the base-pool initialization
 * (igMemoryPool_Initialize: igObject_InitHeader, then the base vtable), publishes the
 * igAliasMemoryPool vtable and clears the allocation lock, event tracker and aliased-pool
 * references (offsets 116, 152 and 180). Returns `self`. */
void *igAliasMemoryPool_Initialize(igAliasMemoryPool *self) {
    igMemoryPool_Initialize((int **)self);
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    return self;
}

/* igAliasMemoryPool constructor. Runs the base-class constructor, publishes the pool's vtable and
 * clears the lock, event-tracker and aliased-pool references (offsets 116, 152, 180), then calls
 * igAliasMemoryPool_Initialize on a non-null receiver and returns it. */
void *igAliasMemoryPool_Construct(igAliasMemoryPool *self, int extra1) {
    igMemoryPool_Construct((int **)self);
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    if (self != 0) {
        igAliasMemoryPool_Initialize(self);
    }
    return self;
}

/* Copy-construct counterpart of igAliasMemoryPool_Initialize: runs the base-pool copy-construct
 * step (igMemoryPool_CopyConstruct: igObject_CopyConstructHeader, then the base vtable), publishes
 * the igAliasMemoryPool vtable and clears the allocation lock, event tracker and aliased-pool
 * references. Returns `self`. */
void *igAliasMemoryPool_CopyConstruct(igAliasMemoryPool *self, int extra1) {
    igMemoryPool_CopyConstruct((igMemoryPool *)self, (igMemoryPool *)extra1);
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    return self;
}

/* Alias-pool teardown: release the aliased pool (low 23-bit reference count), run the receiver's
 * close slot, then the igObject base step. */
void igAliasMemoryPool_Destruct(igAliasMemoryPool *self){
    igObject *old=(igObject *)self->_aliasedMemoryPool;
    if(old){--old->_refCount;if(!(old->_refCount&0x7fffff))igObject_Destroy(old);}
    ((igMemoryPoolView *)self)->Shutdown();
    igMemoryPool_Destruct((int)self);
}

void __do_global_ctors()
{
    __init_cpp();
}

void __do_global_dtors()
{
    __fini_cpp();
}

void FUN_002d1660(void) {
    __do_global_ctors();
    __do_global_dtors();
}

void FUN_002d1690(int extra0)
{
}

long long g_objectSystemRefCount;

void igObjectSystem_Acquire(int headerVersion) {
    int *probe;
    int system;

    if (g_objectSystemRefCount++ == 0) {
        /* The first set-up writes the two status constants again, with the values the static initialiser
         * gives them. */
        const_cast<igResult &>(g_resultSuccess).v = 0;
        const_cast<igResult &>(g_resultFailure).v = 1;
        igPsx2_InitializeIop();
        system = (int)igObjectSystem_OperatorNew(0x3A0);
        if (system != 0) {
            system = ((int)igObjectSystem_Construct((ObjectSystemView *)system));
        }
        (*(int *)&g_objectSystem) = system;
        igObjectSystem_Startup((ObjectSystemView *)system);
        igStringObj_EnsureRegistered();
        igStringObjList_EnsureRegistered();
        Gap::Core::igFile::arkRegister();
        Gap::Core::igRegistry::arkRegister();
        igResource_EnsureRegistered();
        probe = (int *)(&DAT_00530d80[0]);
        FUN_002d1690((int)&probe);
        igObjectSystem_Initialize(g_objectSystem);
    }
    igObjectSystem_CheckHeaderVersion((void *)((*(int *)&g_objectSystem)), headerVersion);
}

void igObjectSystem_Release(void) {
    ObjectSystemView *core;
    void *p;
    int *h;
    int rc;

    if (g_objectSystem->preExitDone == 0) {
        igObjectSystem_PreExit(g_objectSystem);
    }
    if (--g_objectSystemRefCount == 0) {
        igObjectSystem_Finalize(g_objectSystem);
        igObjectSystem_Shutdown(g_objectSystem);
        core = g_objectSystem;
        if (core != 0) {
            if (&core->basePath.p) {
                p = core->basePath.p;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                    }
                }
            }
            if (&core->rootPath.p) {
                p = core->rootPath.p;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (StringTokenHeader *)h);
                    }
                }
            }
            igObjectSystem_OperatorDelete(core);
        }
        (*(void * *)&g_objectSystem) = 0;
    }
}

int g_emptyMetaEnum;

int igMetaEnum_GetEmpty(void) {
    if (g_emptyMetaEnum == 0) {
        g_emptyMetaEnum = ((int)Gap::Core::igMetaEnum::createMetaEnum((char *)(""), 0, 0, 0));
    }
    return g_emptyMetaEnum;
}

void igObjectSystem_SetIniText(const char *text) {
    *(const char **)0x586DE0 = text;
}

unsigned char g_headerVersionWarned;

void igObjectSystem_CheckHeaderVersion(void *self, int headerVersion) {
    int answer;

    if ((headerVersion != 0xC80) && (((ObjectSystemView *)self)->reportHeaderVersionMismatch == 1) && (g_headerVersionWarned == 0)) {
        answer = igReportError("The headers used to build the Alchemy Core (version %d) do not match the currently registring dll or application (version %d).\nThis usually means some API changed and you are likely to get unexpected behaviour.\nTo try and load the dll or application anyways, try putting \nfailOnDllVersionMismatch = false in the CORE section of your alchemy.ini", 0xC80, headerVersion);
        if ((answer != 1) && (answer == 2)) {
            g_headerVersionWarned = 1;
        }
    }
}

void *igObjectSystem_Construct(ObjectSystemView *self) {
    self->rootPath.p = 0;
    self->basePath.p = 0;
    self->started = 0;
    self->preExitDone = 0;
    self->exitDone = 0;
    self->active = 0;
    self->metaRegistry = 0;
    self->bootstrapPool = 0;
    self->f32 = 0;
    self->metaEnumList = 0;
    self->exitCallbacks = 0;
    self->registrationCallbacks = 0;
    self->configRegistry = 0;
    self->resourceTempPool = 0;
    self->resourceTempPoolSize = 0;
    self->useGlobalEventTracker = 0;
    self->saveEventTrackerOnExit = 0;
    self->showLeaksOnExit = 0;
    self->showMemoryStatisticsOnExit = 0;
    self->showObjectStatisticsOnExit = 0;
    self->reportHeaderVersionMismatch = 0;
    self->warnOnDllDateMismatch = 0;
    self->eventTrackerInitialCapacity = (void *)0x80000;
    self->eventTrackerEventTypeFilter = -1;
    self->eventTrackerMarkerTypeFilter = -1;
    self->eventTrackerNotificationTypeFilter = -1;
    self->eventTrackerNotificationCodeFilter = -1;
    self->memoryEventFormat[0] = 0;
    self->markerEventFormat[0] = 0;
    self->notificationEventFormat[0] = 0;
    self->eventTrackerFileName[0] = 0;
    self->symbolsFileName[0] = 0;
    self->symbolTable = 0;
    self->globalEventTracker = 0;
    self->systemPool = 0;
    self->f92 = 0;
    self->fastPool = 0;
    self->driverDataPool = 0;
    self->copyVTables = 0;
    self->vtableClassNames = 0;
    self->driverDatabase = 0;
    self->vtableProbeOffset = 0;
    self->pluginHelper = 0;
    self->f108 = 0;
    self->retainedObject = 0;
    return self;
}

