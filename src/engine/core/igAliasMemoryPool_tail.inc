int Gap__Core__igAliasMemoryPool__vfunc_99(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}

/* Bind `alias` as the pool this one forwards to. The new alias is retained before the previous one
 * is released (so assigning the same object is safe); the previous alias is destroyed when its
 * reference count drops to zero. The alias is then asked (vfunc_94) whether this pool may alias it
 * and the answer becomes _isReassignable; a null alias clears it. */
void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, igMemoryPoolView *alias) {
    igMemoryPoolView *old;
    if (alias) ((igObject *)alias)->_refCount++;
    old = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (old) {
        ((igObject *)old)->_refCount--;
        if ((((igObject *)old)->_refCount & 0x7fffff) == 0)
            igObject_Destroy(old);
    }
    self->_aliasedMemoryPool = (int)alias;
    if (alias) self->_isReassignable = alias->vfunc_94((igMemoryPoolView *)self);
    else self->_isReassignable = 0;
}

/* slot 30, reset the allocation counters and mark the pool active. */
void Gap__Core__igAliasMemoryPool__vfunc_30(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
    self->_isActive = 1;
}

/* Slot 31, the same counter reset without touching _isActive. */
void Gap__Core__igAliasMemoryPool__vfunc_31(igAliasMemoryPool *self) {
    self->_allocedBytes = 0;
    self->_allocedBytesHigh = 0;
    self->_nAllocs = 0;
    self->_nFrees = 0;
    self->_netAllocsHigh = 0;
}

/* Disable the pool: run the receiver's virtual at vtable offset 124 (the reset callback), then
 * clear _isActive afterwards, even if the callback wrote it. */
void Gap__Core__igAliasMemoryPool__vfunc_32(igAliasMemoryPool *self) {
    ((igMemoryPoolView *)self)->vfunc_31();
    self->_isActive = 0;
}

/* Slot 33, report whether the pool is active. */
unsigned char Gap__Core__igAliasMemoryPool__vfunc_33(igAliasMemoryPool *self) {
    return self->_isActive;
}

/* Slot 26, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_26(void) {
    return 0;
}

/* Slot 24, output the allocator failure-status word. */
void Gap__Core__igAliasMemoryPool__vfunc_24(int *outStatus) {
    *outStatus = g_resultFailure.v;
}

/* Slot 25, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_25(void) {
    return 0;
}

/* Slot 29, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_29(void) {
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

igResult Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable) {
    if ((enable & 0xFF) == 0) {
        igSmartPointer<igSemaphoreView> kept((igSemaphoreView *)pool->_allocationLock);
        kept.retain();
        setLock(pool, 0);
        if (kept.get() != 0) {
            kept.get()->wait(1);
            kept.get()->destroy();
        }
    } else if ((enable & 0xFF) == 1) {
        if (pool->_allocationLock != 0) {
            return g_resultSuccess.v;
        }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)pool)))));
        created.get()->create();
        setLock(pool, created.get());
    }
    return g_resultSuccess.v;
}

/* IgAliasMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument. */
void Gap__Core__igAliasMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

int Gap__Core__igAliasMemoryPool__vfunc_36(void) {
    return 0;
}

/* Set the pool's size limit (`_maxSize`) and report success through the status word. Sibling
 * setters (vfunc_37 alignment, vfunc_39 element size) share the shape. */
void Gap__Core__igAliasMemoryPool__vfunc_41(int *status, igAliasMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_resultSuccess.v;
}

/* Vtable slot 42: the pool's capacity in bytes (_maxSize). */
long long Gap__Core__igAliasMemoryPool__vfunc_42(igAliasMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's alignment (`_alignment`) and report success through the status word. */
void Gap__Core__igAliasMemoryPool__vfunc_37(int *status, igAliasMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_resultSuccess.v;
}

/* IgAliasMemoryPool slot 38, returns the reflected _alignment (+176, unsigned short). */
unsigned short Gap__Core__igAliasMemoryPool__vfunc_38(igAliasMemoryPool *self) {
    return self->_alignment;
}

/* IgAliasMemoryPool setter for `_elementSize` (+172). Stores the new element size and reports
 * success through the out cell (the cell receives the shared success status word, see
 * g_resultSuccess). */
void Gap__Core__igAliasMemoryPool__vfunc_39(int *status_out, igAliasMemoryPool *self, int element_size) {
    self->_elementSize = element_size;
    *status_out = g_resultSuccess.v;
}

/* IgAliasMemoryPool slot 40, returns the reflected _elementSize (+172). */
int Gap__Core__igAliasMemoryPool__vfunc_40(igAliasMemoryPool *self) {
    return self->_elementSize;
}

/* Configures the pool from its info record: the base class's step only. The result is a local
 * copied out, as in the pools that go on to read the info's strings. */
igResult Gap__Core__igAliasMemoryPool__vfunc_45(igAliasMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result = FUN_002f0880((void **)self, (void *)info);
    return result;
}

long long Gap__Core__igAliasMemoryPool__vfunc_46(igAliasMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_allocedBytes;
}

/* Vtable slot 47: total bytes currently allocated from the pool (_allocedBytes). */
long long Gap__Core__igAliasMemoryPool__vfunc_47(igAliasMemoryPool *self) {
    return self->_allocedBytes;
}

/* Accessor: the alias pool's reflected _allocedBytes field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igAliasMemoryPool__vfunc_48(igAliasMemoryPool *self) {
    return self->_allocedBytes;
}

long long Gap__Core__igAliasMemoryPool__vfunc_101(igAliasMemoryPool *arg0) {
    return arg0->_allocedBytesHigh;
}

long long Gap__Core__igAliasMemoryPool__vfunc_102(igAliasMemoryPool *arg0) {
    return arg0->_allocedBytesHigh;
}

long long Gap__Core__igAliasMemoryPool__vfunc_49(igAliasMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_allocedBytes;
}

void *Gap__Core__igAliasMemoryPool__vfunc_53(igAliasMemoryPool *self){return ((igMemoryPoolView *)self)->Allocate(self->_elementSize);}

/* Take the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 132 with 1. The status it returns is discarded. */
void igAliasMemoryPool_Lock(igAliasMemoryPool *self) {
    igResult status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((igSemaphoreView *)(lockObject))->wait((int)(1));
    }
}

/* Release the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 124. The status it returns is discarded. */
void igAliasMemoryPool_Unlock(igAliasMemoryPool *self) {
    igResult status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((igSemaphoreView *)(lockObject))->signal();
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
        status = ((igSemaphoreView *)(lockObject))->signal();
    }
    return result;
}

void *Gap__Core__igAliasMemoryPool__vfunc_54(igAliasMemoryPool *self,unsigned int size){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation(0,size,self->_alignment);}

void *Gap__Core__igAliasMemoryPool__vfunc_55(igAliasMemoryPool *self,unsigned int size,unsigned short alignment){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation(0,size,alignment);}

int Gap__Core__igAliasMemoryPool__vfunc_56(igAliasMemoryPool *arg0, int arg1, int arg2) {
    int n;
    int p;
    n = arg1 * arg2;
    p = ((igAliasMemoryPoolView *)arg0)->ManageAllocation(0, n, arg0->_alignment);
    if (p != 0) {
        if (n != 0) {
            memset(p, 0, n);
        }
    }
    return p;
}

int Gap__Core__igAliasMemoryPool__vfunc_57(igAliasMemoryPool *arg0, int arg1, int arg2, unsigned short alignment) {
    int temp_s1;
    int temp_v0;

    temp_s1 = arg1 * arg2;
    temp_v0 = ((igAliasMemoryPoolView *)arg0)->ManageAllocation(0, temp_s1, alignment);
    if (temp_v0 != 0) {
        if (temp_s1 != 0) {
            memset(temp_v0, 0, temp_s1);
        }
    }
    return temp_v0;
}

void *Gap__Core__igAliasMemoryPool__vfunc_58(igAliasMemoryPool *self,void *old,unsigned int size){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,size,self->_alignment);}

void *Gap__Core__igAliasMemoryPool__vfunc_59(igAliasMemoryPool *self,void *old,unsigned int size,unsigned short alignment){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,size,alignment);}

int Gap__Core__igAliasMemoryPool__vfunc_65(igAliasMemoryPool *arg0, int arg1) {
    long long temp_s1;
    int temp_s0;
    long long temp_v1;

    if (arg0->_aliasedMemoryPool != 0) {
        temp_s1 = ((igMemoryPoolView *)arg0->_aliasedMemoryPool)->vfunc_48();
        temp_s0 = ((igMemoryPoolView *)arg0->_aliasedMemoryPool)->vfunc_65(arg1);
        temp_v1 = ((igMemoryPoolView *)arg0->_aliasedMemoryPool)->vfunc_48() - temp_s1;
        if (arg0->_updateStatistics != 0) {
            ((igMemoryPoolView *)arg0)->vfunc_50(arg1, (int)temp_v1, 1);
        }
        return temp_s0;
    }
    return 0;
}

igResult Gap__Core__igAliasMemoryPool__vfunc_62(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        return pool->gangAlloc(count, sizes, blocks);
    }
    return g_resultFailure;
}

igResult Gap__Core__igAliasMemoryPool__vfunc_63(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks, unsigned short *alignments) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        return pool->gangAllocAligned(count, sizes, blocks, alignments);
    }
    return g_resultFailure;
}

void Gap__Core__igAliasMemoryPool__vfunc_64(igAliasMemoryPool *self, int count, void **blocks) {
    igMemoryPoolView *pool = (igMemoryPoolView *)self->_aliasedMemoryPool;
    if (pool != 0) {
        pool->gangFree(count, blocks);
    }
}

void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old){return (void *)((igAliasMemoryPoolView *)self)->ManageAllocation((int)old,-1,self->_alignment);}

/* The aliased pool's slot 93 (offset 380) answers its own pool index. */
class AliasedPoolIndexView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual int PoolIndex(); };

/* Whether this pool owns the allocation the registry resolves for the caller's second argument: a
 * reassignable pool compares its index with its alias's; any other asks the allocator registry to
 * resolve the index to a pool and checks that it is this pool. The second argument is forwarded
 * untouched to FUN_002f0180. */
int igAliasMemoryPool_OwnsAllocation(igAliasMemoryPool *self, int poolIndex) {
    int resolved;
    int status;
    if (self->_isReassignable != 0) {
        if (self->_poolIndex == ((AliasedPoolIndexView *)self->_aliasedMemoryPool)->PoolIndex()) {
            return 1;
        }
    } else {
        status = FUN_002f0180(poolIndex, &resolved).get();
        if (status == g_resultSuccess.v) {
            return resolved == (int)self;
        }
    }
    return 0;
}

unsigned int igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old){return ((igMemoryPoolView *)self->_aliasedMemoryPool)->GetAllocationSize(old);}

void igAliasMemoryPool_PrintStatistics(igAliasMemoryPoolView *self, char *arg1) {
    int s4;
    long long s3;
    int s2;
    int s1;
    int *s0;
    long long s6;
    long long s7;
    long long s8;
    __int128 spD0;
    __int128 spC0;
    if (arg1 != 0 && *arg1 != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
    }
    igAliasMemoryPool *pool = (igAliasMemoryPool *)self;
    s2 = pool->_nFrees;
    s1 = pool->_nAllocs;
    s4 = pool->_netAllocsHigh;
    s3 = s1 - s2;
    if (self->vfunc_99() != 0) {
        s0 = ((int *)FUN_002f89a0(self->vfunc_99()));
    } else {
        s0 = text_null;
    }
    s6 = self->vfunc_47();
    s7 = (int)self->vfunc_48();
    s8 = self->vfunc_101();
    spD0 = (long long)self->vfunc_102();
    spC0 = (long long)self->vfunc_42();
    FUN_00304430(DAT_004f90c0, s0, s6, s7, s8, spD0, (long long)s1, (long long)s2, (long long)(int)s3, (long long)s4, (long long)spC0, self->GetPoolIndex());
    FUN_00304680();
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
    if (tracker != 0) {
        tracker->_refCount = tracker->_refCount + 1;
    }
    previous = (igObject *)(self->_eventTracker);
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_eventTracker = (int)(tracker);
}

void igAliasMemoryPool_Dump(igAliasMemoryPool *self, int a1, int a2, int a3, int t0) {
    int *g;
    igAliasMemoryPool_Lock(self);
    g = &DAT_004f92b0[0];
    if (t0 != 0) {
        igSmartPointer<igFileView> r((igFileView *)igFile_Create((int)(((void *)igObject_GetAllocator((int)self)))));
        if (r.p->Open((const char *)t0, (const char *)&DAT_004f92f0[0]) == 0) {
            igAliasMemoryPool_Unlock(self);
            return;
        }
        r.p->Print((const char *)g);
        r.p->Close();
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
    int s1 = 0;
    long long s0;
    int v0;
    igAliasMemoryPool_Lock(self);
    if ((alignment & 0xFFFF) < self->_alignment) alignment = self->_alignment;
    s0 = size;
    for (;;) {
        if (size == -1) {
            s1 = 0;
            if (block == 0) {
                igAliasMemoryPool_Unlock(self);
                return 0;
            }
            { int t = ((igMemoryPoolView *)self)->GetAllocationSize((void *)block); self->_allocedBytes = self->_allocedBytes - t; }
            self->_nFrees = self->_nFrees + 1;
            if (self->_isReassignable != 0) {
                igResult sp8C = ((igMemoryPoolView *)self->_aliasedMemoryPool)->vfunc_93((char *)block, (igMemoryPoolView *)self->_aliasedMemoryPool);
            } else {
                igResult sp88 = FUN_002f0320(block, (igMemoryPoolView *)self);
            }
            ((igMemoryPoolView *)self->_aliasedMemoryPool)->Free((void *)block);
            break;
        }
        if (self->_allocedBytes + s0 > self->_maxSize) {
            if (((igMemoryPoolView *)self)->vfunc_23(size, 1) == 0) {
                s1 = 0;
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
                    igResult sp84 = ((igMemoryPoolView *)self->_aliasedMemoryPool)->vfunc_93((char *)block, (igMemoryPoolView *)self->_aliasedMemoryPool);
                } else {
                    igResult sp80 = FUN_002f0320(block, (igMemoryPoolView *)self);
                }
                s1 = (int)((igMemoryPoolView *)self->_aliasedMemoryPool)->ReallocateAligned((void *)block, size, alignment);
            }
        } else {
            if (self->_aliasedMemoryPool != 0) {
                s1 = (int)((igMemoryPoolView *)self->_aliasedMemoryPool)->AllocateAligned(size, alignment);
            }
        }
        if (s1 != 0) {
            self->_allocedBytes = self->_allocedBytes + size;
            if (self->_allocedBytesHigh < self->_allocedBytes) self->_allocedBytesHigh = self->_allocedBytes;
            self->_nAllocs = self->_nAllocs + 1;
            v0 = self->_nAllocs - self->_nFrees;
            if (self->_netAllocsHigh < v0) self->_netAllocsHigh = v0;
            if (self->_isReassignable != 0) {
                igResult sp7C = ((igMemoryPoolView *)self->_aliasedMemoryPool)->vfunc_93((char *)s1, (igMemoryPoolView *)self);
            } else {
                igResult sp78 = FUN_002f0220(s1, (igMemoryPoolView *)self);
            }
        }
        break;
    }
    return igAliasMemoryPool_UnlockAndReturn(self, s1);
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
    FUN_002effb0((int **)self);
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
    igMemoryPool_CopyConstruct((int **)self);
    self->_vtable = (int)(&g_igAliasMemoryPool_vtable[0]);
    self->_allocationLock = 0;
    self->_eventTracker = 0;
    self->_aliasedMemoryPool = 0;
    return self;
}

/* Alias-pool teardown: release the aliased pool (low 23-bit reference count), run the receiver's
 * close slot, then the igObject base step. */
void Gap__Core__igAliasMemoryPool__vfunc_02(igAliasMemoryPool *self){
    igObject *old=(igObject *)self->_aliasedMemoryPool;
    if(old){--old->_refCount;if(!(old->_refCount&0x7fffff))igObject_Destroy(old);}
    ((igMemoryPoolView *)self)->vfunc_98();
    Gap__Core__igObject__vfunc_00((int)self);
}

int __do_global_ctors()
{
    return __init_cpp();
}

int __do_global_dtors()
{
    return __fini_cpp();
}

void FUN_002d1660(void) {
    __do_global_ctors();
    __do_global_dtors();
}

void FUN_002d1690(int extra0)
{
}

void FUN_002d16a0(int arg0) {
    int *sp2C;
    int var_v0;

    if (DAT_00586dd8[0]++ == 0) {
        /* The first set-up writes the two status constants again, with the values the static initialiser
         * gives them. */
        const_cast<igResult &>(g_resultSuccess).v = 0;
        const_cast<igResult &>(g_resultFailure).v = 1;
        FUN_0032d1f0();
        var_v0 = thunk_malloc(0x3A0);
        if (var_v0 != 0) {
            var_v0 = ((int)FUN_002d1930((void *)var_v0));
        }
        ((int *)g_objectSystem)[0] = var_v0;
        FUN_002d1a00((ObjectSystemView *)var_v0);
        FUN_002b9620();
        FUN_002b9470();
        FUN_002c4d80();
        FUN_002bb200();
        FUN_002bad40();
        sp2C = (int *)(&DAT_00530d80[0]);
        FUN_002d1690((int)&sp2C);
        FUN_002d1e40(((int *)g_objectSystem)[0]);
    }
    FUN_002d18d0((void *)(((int *)g_objectSystem)[0]), arg0);
}

void FUN_002d1770(void) {
    ObjectSystemView *core;
    void *p;
    int *h;
    int rc;

    if (((ObjectSystemView **)g_objectSystem)[0]->preExitDone == 0) {
        FUN_002d27a0((ObjectSystemView *)(((void * *)g_objectSystem)[0]));
    }
    if (--DAT_00586dd8[0] == 0) {
        FUN_002d2800(((void * *)g_objectSystem)[0]);
        FUN_002d2e60((ObjectSystemView *)(((void * *)g_objectSystem)[0]));
        core = ((ObjectSystemView **)g_objectSystem)[0];
        if (core != 0) {
            if (&core->basePath.p) {
                p = core->basePath.p;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
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
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                    }
                }
            }
            thunk_free((int)core);
        }
        ((void * *)g_objectSystem)[0] = 0;
    }
}

int FUN_002d1870(void) {
    if (DAT_00586dc0[0] == 0) {
        DAT_00586dc0[0] = ((int)igMetaEnum_Create((char *)(&DAT_004f7910[0]), (char **)0, (int *)0, 0));
    }
    return DAT_00586dc0[0];
}

void FUN_002d18c0(int arg0) {
    *(int *)0x586DE0 = arg0;
}

void FUN_002d18d0(void *arg0, int arg1) {
    int temp_v0;

    if ((arg1 != 0xC80) && (*(unsigned char *)((char *)(arg0) + 121) == 1) && (GPR_00554bf8 == 0)) {
        temp_v0 = igReportError(DAT_004f9300, 0xC80, arg1);
        if ((temp_v0 != 1) && (temp_v0 == 2)) {
            GPR_00554bf8 = 1;
        }
    }
}

void *FUN_002d1930(void *arg0) {
    *(int *)((char *)(arg0) + 920) = 0;
    *(int *)((char *)(arg0) + 924) = 0;
    *(char *)((char *)(arg0) + 20) = 0;
    *(char *)((char *)(arg0) + 21) = 0;
    *(char *)((char *)(arg0) + 22) = 0;
    *(char *)((char *)(arg0) + 0) = 0;
    *(int *)((char *)(arg0) + 24) = 0;
    *(int *)((char *)(arg0) + 48) = 0;
    *(int *)((char *)(arg0) + 32) = 0;
    *(int *)((char *)(arg0) + 36) = 0;
    *(int *)((char *)(arg0) + 40) = 0;
    *(int *)((char *)(arg0) + 44) = 0;
    *(int *)((char *)(arg0) + 56) = 0;
    *(int *)((char *)(arg0) + 68) = 0;
    *(int *)((char *)(arg0) + 72) = 0;
    *(char *)((char *)(arg0) + 116) = 0;
    *(char *)((char *)(arg0) + 117) = 0;
    *(char *)((char *)(arg0) + 118) = 0;
    *(char *)((char *)(arg0) + 119) = 0;
    *(char *)((char *)(arg0) + 120) = 0;
    *(char *)((char *)(arg0) + 121) = 0;
    *(char *)((char *)(arg0) + 122) = 0;
    *(int *)((char *)(arg0) + 124) = 0x80000;
    *(int *)((char *)(arg0) + 128) = -1;
    *(int *)((char *)(arg0) + 132) = -1;
    *(int *)((char *)(arg0) + 136) = -1;
    *(int *)((char *)(arg0) + 140) = -1;
    *(char *)((char *)(arg0) + 144) = 0;
    *(char *)((char *)(arg0) + 272) = 0;
    *(char *)((char *)(arg0) + 400) = 0;
    *(char *)((char *)(arg0) + 528) = 0;
    *(char *)((char *)(arg0) + 784) = 0;
    *(int *)((char *)(arg0) + 80) = 0;
    *(int *)((char *)(arg0) + 84) = 0;
    *(int *)((char *)(arg0) + 52) = 0;
    *(char *)((char *)(arg0) + 92) = 0;
    *(int *)((char *)(arg0) + 96) = 0;
    *(int *)((char *)(arg0) + 88) = 0;
    *(int *)((char *)(arg0) + 100) = 0;
    *(int *)((char *)(arg0) + 104) = 0;
    *(int *)((char *)(arg0) + 60) = 0;
    *(int *)((char *)(arg0) + 916) = 0;
    *(int *)((char *)(arg0) + 76) = 0;
    *(int *)((char *)(arg0) + 108) = 0;
    *(int *)((char *)(arg0) + 112) = 0;
    return arg0;
}

