int Gap__Core__igAliasMemoryPool__vfunc_99(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}

/* Bind `alias` as the pool this one forwards to. The new alias is retained before the previous one
 * is released (so assigning the same object is safe); the previous alias is destroyed when its
 * reference count drops to zero. The alias is then asked (virtual slot 376) whether it accepts
 * this pool and the low byte of the answer becomes _isReassignable; a null alias clears it. */
void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, Object *alias) {
    Object *old;
    if (alias) alias->refs++;
    old = (Object *)self->_aliasedMemoryPool;
    if (old) {
        old->refs--;
        if ((old->refs & 0x7fffff) == 0)
            igObject_Destroy(old);
    }
    self->_aliasedMemoryPool = (int)alias;
    if (alias) self->_isReassignable = alias->Check(self);
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
    ((DW4VC_124_0 *)(((char *)(self) + 0)))->vX();
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
    *outStatus = g_allocatorFailureStatus[0];
}

/* Slot 25, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_25(void) {
    return 0;
}

/* Slot 29, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_29(void) {
    return 0;
}

static inline void setLock(igAliasMemoryPool *pool, Lock *lock) {
    Lock *previous;
    if (lock != 0) {
        lock->_refCount = lock->_refCount + 1;
    }
    previous = (Lock *)pool->_allocationLock;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    pool->_allocationLock = (int)lock;
}

LockStatus Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable) {
    if ((enable & 0xFF) == 0) {
        igSmartPointer<Lock> kept((Lock *)pool->_allocationLock);
        kept.retain();
        setLock(pool, 0);
        if (kept.get() != 0) {
            kept.get()->wait(1);
            kept.get()->close();
        }
    } else if ((enable & 0xFF) == 1) {
        if (pool->_allocationLock != 0) {
            return DAT_004fb410.v;
        }
        igSmartPointer<Lock> created((Lock *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)pool)))));
        created.get()->open();
        setLock(pool, created.get());
    }
    return DAT_004fb410.v;
}

/* IgAliasMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument. */
void Gap__Core__igAliasMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}

int Gap__Core__igAliasMemoryPool__vfunc_36(void) {
    return 0;
}

/* Set the pool's size limit (`_maxSize`) and report success through the status word. Sibling
 * setters (vfunc_37 alignment, vfunc_39 element size) share the shape. */
void Gap__Core__igAliasMemoryPool__vfunc_41(int *status, igAliasMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}

/* Vtable slot 42: the pool's capacity in bytes (_maxSize). */
long long Gap__Core__igAliasMemoryPool__vfunc_42(igAliasMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's alignment (`_alignment`) and report success through the status word. */
void Gap__Core__igAliasMemoryPool__vfunc_37(int *status, igAliasMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_statusSucceeded[0];
}

/* IgAliasMemoryPool slot 38, returns the reflected _alignment (+176, unsigned short). */
unsigned short Gap__Core__igAliasMemoryPool__vfunc_38(igAliasMemoryPool *self) {
    return self->_alignment;
}

/* IgAliasMemoryPool setter for `_elementSize` (+172). Stores the new element size and reports
 * success through the out cell (the cell receives the shared success status word, see
 * g_statusSucceeded). */
void Gap__Core__igAliasMemoryPool__vfunc_39(int *status_out, igAliasMemoryPool *self, int element_size) {
    self->_elementSize = element_size;
    *status_out = g_statusSucceeded[0];
}

/* IgAliasMemoryPool slot 40, returns the reflected _elementSize (+172). */
int Gap__Core__igAliasMemoryPool__vfunc_40(igAliasMemoryPool *self) {
    return self->_elementSize;
}

/* Output-first status wrapper. The status word is returned through the hidden output pointer (a0).
 * The shared helper also reads a1 (the pool) and a2 (a request descriptor) from its asm, and this
 * wrapper passes both through untouched, which is why only the local cell is named at the call.
 * The helper leaves the success word (g_statusSucceeded) in the cell. */
void Gap__Core__igAliasMemoryPool__vfunc_45(int *outStatus, int extra1, int extra2) {
    int status;

    FUN_002f0880(&status, (void **)extra1, (void *)extra2);
    *outStatus = status;
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

void *Gap__Core__igAliasMemoryPool__vfunc_53(igAliasMemoryPool *self){return ((PoolView *)self)->AllocateDefault((int)self->_elementSize);}

/* Take the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 132 with 1. The status it returns is discarded. */
void igAliasMemoryPool_Lock(igAliasMemoryPool *self) {
    LockCallStatus status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((AllocationLockVtable *)(lockObject))->lock((int)(1));
    }
}

/* Release the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 124. The status it returns is discarded. */
void igAliasMemoryPool_Unlock(igAliasMemoryPool *self) {
    LockCallStatus status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((AllocationLockVtable *)(lockObject))->unlock();
    }
}

/* Release the pool's allocation lock, then hand back the value the caller supplied: when a lock
 * object is attached (_allocationLock), call its virtual method at vtable offset 124 (the same
 * unlock call as igAliasMemoryPool_Unlock); the status it returns is discarded. This lets a caller
 * write `return igAliasMemoryPool_UnlockAndReturn(pool, result)` to leave a locked section while
 * preserving its result. */
int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result) {
    LockCallStatus status;
    void **lockObject;

    lockObject = (void **)(self->_allocationLock);
    if (lockObject != 0) {
        status = ((AllocationLockVtable *)(lockObject))->unlock();
    }
    return result;
}

void *Gap__Core__igAliasMemoryPool__vfunc_54(igAliasMemoryPool *self,long long size){return ((PoolView *)self)->Backend(0,size,self->_alignment);}

void *Gap__Core__igAliasMemoryPool__vfunc_55(igAliasMemoryPool *self,long long size,unsigned short alignment){return ((PoolView *)self)->Backend(0,size,alignment);}

int Gap__Core__igAliasMemoryPool__vfunc_56(igAliasMemoryPool *arg0, int arg1, int arg2) {
    int n;
    int p;
    n = arg1 * arg2;
    p = ((VC *)arg0)->vX(0, n, arg0->_alignment);
    if (p != 0) {
        if (n != 0) {
            memset(p, 0, n);
        }
    }
    return p;
}

int Gap__Core__igAliasMemoryPool__vfunc_57(void **arg0, int arg1, int arg2) {
    int temp_s1;
    int temp_v0;

    temp_s1 = arg1 * arg2;
    temp_v0 = ((DW4VC_412_2 *)(arg0))->vX((int)(0), (int)(temp_s1));
    if (temp_v0 != 0) {
        if (temp_s1 != 0) {
            memset(temp_v0, 0, temp_s1);
        }
    }
    return temp_v0;
}

void *Gap__Core__igAliasMemoryPool__vfunc_58(igAliasMemoryPool *self,void *old,long long size){return ((PoolView *)self)->Backend(old,size,self->_alignment);}

void *Gap__Core__igAliasMemoryPool__vfunc_59(igAliasMemoryPool *self,void *old,long long size,unsigned short alignment){return ((PoolView *)self)->Backend(old,size,alignment);}

int Gap__Core__igAliasMemoryPool__vfunc_65(igAliasMemoryPool *arg0, int arg1) {
    long long temp_s1;
    int temp_s0;
    long long temp_v1;

    if (arg0->_aliasedMemoryPool != 0) {
        temp_s1 = ((DW4VC_192_0 *)arg0->_aliasedMemoryPool)->vX();
        temp_s0 = ((DW4VC_260_1 *)arg0->_aliasedMemoryPool)->vX(arg1);
        temp_v1 = ((DW4VC_192_0 *)arg0->_aliasedMemoryPool)->vX() - temp_s1;
        if (arg0->_updateStatistics != 0) {
            ((DW4VC_200_3 *)(arg0))->vX(arg1, (int)temp_v1, 1);
        }
        return temp_s0;
    }
    return 0;
}

R62 Gap__Core__igAliasMemoryPool__vfunc_62(igAliasMemoryPool *arg1) {
    DW4VC_248_0 *o = (DW4VC_248_0 *)arg1->_aliasedMemoryPool;
    if (o != 0) {
        return o->vX();
    }
    return R62(DAT_004fb418.v);
}

R63 Gap__Core__igAliasMemoryPool__vfunc_63(igAliasMemoryPool *arg1) {
    C_2d0550 *p = (C_2d0550 *)arg1->_aliasedMemoryPool;
    if (p != 0) {
        return p->vX();
    }
    return R63(DAT_004fb418.v);
}

void Gap__Core__igAliasMemoryPool__vfunc_64(igAliasMemoryPool *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(arg0->_aliasedMemoryPool);
    if (temp_a0 != 0) {
        ((DW4VC_256_0 *)(temp_a0))->vX();
    }
}

void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old){return ((PoolView *)self)->Backend(old,-1,self->_alignment);}

long long igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old){return ((PoolView *)self->_aliasedMemoryPool)->Size(old);}

void igAliasMemoryPool_PrintStatistics(StatsPool *arg0, char *arg1) {
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
    igAliasMemoryPool *pool = (igAliasMemoryPool *)arg0;
    s2 = pool->_nFrees;
    s1 = pool->_nAllocs;
    s4 = pool->_netAllocsHigh;
    s3 = s1 - s2;
    if (arg0->f97() != 0) {
        s0 = ((int *)FUN_002f89a0(arg0->f97()));
    } else {
        s0 = DAT_004f90b8;
    }
    s6 = arg0->f45();
    s7 = arg0->f46();
    s8 = arg0->f99();
    spD0 = (long long)arg0->f100();
    spC0 = (long long)arg0->f40();
    FUN_00304430(DAT_004f90c0, s0, s6, s7, s8, spD0, (long long)s1, (long long)s2, (long long)(int)s3, (long long)s4, (long long)spC0, arg0->f89());
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
        igSmartPointer<V> r((V *)FUN_002c4ca0((int)(((void *)igObject_GetAllocator((int)self)))));
        if (r.p->v23(t0, &DAT_004f92f0[0]) == 0) {
            igAliasMemoryPool_Unlock(self);
            return;
        }
        r.p->v29(g);
        r.p->v24();
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

int igAliasMemoryPool_ManageAllocation(ManagedPool *arg0, int arg1, long long arg2, unsigned short arg3) {
    int s1 = 0;
    long long s0;
    int v0;
    igAliasMemoryPool_Lock((igAliasMemoryPool *)arg0);
    if ((arg3 & 0xFFFF) < arg0->f176) arg3 = arg0->f176;
    s0 = (int)arg2;
    for (;;) {
        if (arg2 == -1) {
            s1 = 0;
            if (arg1 == 0) {
                igAliasMemoryPool_Unlock((igAliasMemoryPool *)arg0);
                return 0;
            }
            { int t = arg0->v336(arg1); arg0->f128 = arg0->f128 - t; }
            arg0->f140 = arg0->f140 + 1;
            if (arg0->f113 != 0) {
                ManageStatus sp8C = arg0->f180->v372(arg1, arg0->f180);
            } else {
                R_2f0320 sp88 = FUN_002f0320(arg1, (V_2f0220 *)arg0);
            }
            arg0->f180->v264(arg1);
            break;
        }
        if (arg0->f128 + s0 > arg0->f144) {
            if (arg0->v92(arg2, 1) == 0) {
                s1 = 0;
                break;
            }
            continue;
        }
        if (arg1 != 0) {
            if (arg0->f180 != 0) {
                if (arg1 != 0) {
                    { int t = arg0->v336(arg1); arg0->f128 = arg0->f128 - t; }
                    arg0->f140 = arg0->f140 + 1;
                }
                if (arg0->f113 != 0) {
                    ManageStatus sp84 = arg0->f180->v372(arg1, arg0->f180);
                } else {
                    R_2f0320 sp80 = FUN_002f0320(arg1, (V_2f0220 *)arg0);
                }
                s1 = arg0->f180->v236(arg1, arg2, arg3);
            }
        } else {
            if (arg0->f180 != 0) {
                s1 = arg0->f180->v220(arg2, arg3);
            }
        }
        if (s1 != 0) {
            arg0->f128 = arg0->f128 + (int)arg2;
            if (arg0->f160 < arg0->f128) arg0->f160 = arg0->f128;
            arg0->f136 = arg0->f136 + 1;
            v0 = arg0->f136 - arg0->f140;
            if (arg0->f168 < v0) arg0->f168 = v0;
            if (arg0->f113 != 0) {
                ManageStatus sp7C = arg0->f180->v372(s1, arg0);
            } else {
                R_2f0220 sp78 = FUN_002f0220(s1, (V_2f0220 *)arg0);
            }
        }
        break;
    }
    return igAliasMemoryPool_UnlockAndReturn((igAliasMemoryPool *)arg0, s1);
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
    ((PoolView *)self)->Close();
    Gap__Core__igObject__vfunc_00((int)self);
}

int thunk_FUN_001029d0()
{
    return FUN_001029d0();
}

int thunk_FUN_00100bc0__002d1650()
{
    return thunk_FUN_00100bc0();
}

void FUN_002d1660(void) {
    thunk_FUN_001029d0();
    thunk_FUN_00100bc0__002d1650();
}

void FUN_002d1690(int extra0)
{
}

void FUN_002d16a0(int arg0) {
    int *sp2C;
    int var_v0;

    if (DAT_00586dd8[0]++ == 0) {
        DAT_004fb410.v = 0;
        DAT_004fb418.v = 1;
        FUN_0032d1f0();
        var_v0 = thunk_malloc(0x3A0);
        if (var_v0 != 0) {
            var_v0 = ((int)FUN_002d1930((void *)var_v0));
        }
        ((int *)DAT_00586dc8)[0] = var_v0;
        FUN_002d1a00((S_2d1a00 *)var_v0);
        FUN_002b9620();
        FUN_002b9470();
        FUN_002c4d80();
        FUN_002bb200();
        FUN_002bad40();
        sp2C = (int *)(&DAT_00530d80[0]);
        FUN_002d1690((int)&sp2C);
        FUN_002d1e40(((int *)DAT_00586dc8)[0]);
    }
    FUN_002d18d0((void *)(((int *)DAT_00586dc8)[0]), arg0);
}

void FUN_002d1770(void) {
    struct Core *core;
    void *p;
    int *h;
    int rc;

    if (((struct Core *)((void * *)DAT_00586dc8)[0])->f21 == 0) {
        FUN_002d27a0((S_2d27a0 *)(((void * *)DAT_00586dc8)[0]));
    }
    if (--DAT_00586dd8[0] == 0) {
        FUN_002d2800(((void * *)DAT_00586dc8)[0]);
        FUN_002d2e60((S_2d2e60 *)(((void * *)DAT_00586dc8)[0]));
        core = (struct Core *)((void * *)DAT_00586dc8)[0];
        if (core != 0) {
            if (&core->f924) {
                p = core->f924;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
                    }
                }
            }
            if (&core->f920) {
                p = core->f920;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
                    }
                }
            }
            thunk_free((int)core);
        }
        ((void * *)DAT_00586dc8)[0] = 0;
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
        temp_v0 = FUN_00308320(DAT_004f9300, 0xC80, arg1);
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

