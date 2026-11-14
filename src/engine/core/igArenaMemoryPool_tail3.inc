void Gap__Core__igArenaMemoryPool__vfunc_102(int *arg0, igArenaMemoryPoolView *arg1) {
    FUN_0031d3f0(arg1);
    igResult r = arg1->vfunc_103();
    FUN_0031d430(arg1);
    *arg0 = r.v;
}

igResult igArenaMemoryPool_CheckHeap(CheckHeapPool *self) {
    CheckHeapArena *arena = self->arena;
    igResult result;
    int i;
    int r;

    result = g_resultSuccess;
    if (arena->count == 0) {
        return g_resultSuccess;
    }
    if (arena->blocks == 0 || arena->capacity == 0) {
        if (self->verbosity > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cec == 0) {
                r = igReportNotice(text_igArenaMemoryPool_checkHeap_E69);
                if (r != 1 && r == 2) {
                    GPR_00554cec = 1;
                }
            }
        }
        result = g_resultFailure;
    }
    if (arena->count < 0 || arena->capacity < 0 || arena->count > arena->capacity) {
        if (self->verbosity >= 3 && GPR_00554cf0 == 0) {
            r = igReportNotice(text_igArenaMemoryPool_checkHeap_E70);
            if (r != 1 && r == 2) {
                GPR_00554cf0 = 1;
            }
        }
        return g_resultFailure;
    }
    for (i = 0; i < arena->count; i += 2) {
        int *p = &arena->blocks[i];
        if (FUN_00312790((HeapBoundsPool *)self, i, (char *)p[0], (char *)p[1]) == g_resultFailure) {
            result = g_resultFailure;
            break;
        }
    }
    return result;
}

igResult FUN_00312790(HeapBoundsPool *self, int index, char *cur, char *end) {
    char *hi = self->HeapEnd();
    char *lo = self->HeapStart();
    /* Declared with the walk's other pointers, ahead of the flag: `n` and `ok` are the two values kept in
     * argument registers, and the later-numbered one, `ok`, takes a0. */
    ArenaBlockHeader *n;
    unsigned int size = 0;
    int count = 0;
    bool ok = false;
    if (cur < lo || hi < cur) {
        if (self->messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cf4 == 0) {
                int r = igReportNotice(DAT_004fc490, index, cur, lo, hi);
                if (r != 1 && r == 2) {
                    GPR_00554cf4 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < lo || hi < end) {
        if (self->messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cf8 == 0) {
                int r = igReportNotice(DAT_004fc500, index, end, lo, hi);
                if (r != 1 && r == 2) {
                    GPR_00554cf8 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (end < cur) {
        if (self->messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554cfc == 0) {
                int r = igReportNotice(DAT_004fc570, index, end, cur);
                if (r != 1 && r == 2) {
                    GPR_00554cfc = 1;
                }
            }
        }
        return g_resultFailure;
    }
    if (!((ArenaBlockHeader *)cur)->used) {
        if (self->messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554d00 == 0) {
                int r = igReportNotice(DAT_004fc5e0);
                if (r != 1 && r == 2) {
                    GPR_00554d00 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    while (cur < end) {
        ArenaBlockHeader *h = (ArenaBlockHeader *)cur;
        unsigned int sz = h->size;
        if (h->big == 1) {
            sz += h->sizeHigh << 19;
        }
        sz = (sz + 3) & ~3;
        size = sz + (h->padWords + 1) * 4;
        int min = self->minBlockSize;
        n = (ArenaBlockHeader *)(cur + size);
        if (size < min) {
            if (end - cur <= min) {
                ok = true;
                break;
            }
            unsigned int nsz;
            if (n->big == 0) {
                nsz = n->size;
            } else {
                nsz = n->size + (n->sizeHigh << 19);
            }
            if (nsz < min) {
                if (end - (char *)n <= min * 2) {
                    ok = true;
                    break;
                }
            }
            goto bad;
        }
        if ((char *)n > end || (char *)n < cur) {
            goto bad;
        }
        cur = (char *)n;
        count++;
    }
    if (cur != end && !ok) {
bad:
        if (self->messageLevel > 0) {
            Memory_PrintPoolStatistics(0, self);
            if (GPR_00554d04 == 0) {
                int r = igReportNotice(DAT_004fc660, cur, index, count, size);
                if (r != 1 && r == 2) {
                    GPR_00554d04 = 1;
                }
            }
        }
        return g_resultFailure;
    }
    return g_resultSuccess;
}

bool igArenaMemoryPool_Trim(TrimPool *self, int pad) {
    int count;
    int cap;
    TrimArena *a;
    int i;
    bool trimmed;
    a = self->arena;
    trimmed = false;
    FUN_00318b40(self);
    if (self->locked != 0) {
        return false;
    }
    count = a->count;
    if (count < 0 || (cap = a->capacity) < 0 || count > cap) {
        if (self->debug >= 3) {
            if (GPR_00554d1c == 0) {
                int r = igReportNotice(text_igArenaMemoryPool_trim_E76_Arena);
                if (r != 1 && r == 2) {
                    GPR_00554d1c = 1;
                }
            }
        }
        return false;
    }
    for (i = a->count - 2; i >= 0; i -= 2) {
        if (igArenaMemoryPool_TrimArenaBlock(self, i, a->blocks[i], a->blocks[i + 1]) == g_resultSuccess) {
            if (i < a->count - 2) {
                memcpy(a->blocks + i, a->blocks + (i + 2), (a->count - (i + 2)) * 4);
            }
            trimmed = true;
            a->blocks[a->count - 1] = 0;
            a->blocks[a->count - 2] = 0;
            a->count = a->count - 2;
        }
    }
    FUN_00314510(self, a->top, pad);
    return trimmed;
}

void FUN_00315050(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3) {
    char *base;
    int i;
    char *head;
    unsigned int cur;
    int prev;
    base = (char *)arg1->_arenaState;
    head = base + 72;
    for (i = 1; i < 96; i++, head += 20) {
        cur = NEXT(head);
        while (cur != (unsigned)head) {
            if (cur >= arg2 && cur < arg3) {
                prev = PREV(cur);
                cur = NEXT(cur);
                NEXT(prev) = cur;
                PREV(cur) = prev;
            } else {
                cur = NEXT(cur);
            }
        }
    }
    cur = *(unsigned *)(base + 48);
    if (cur != 0 && cur >= arg2 && cur < arg3) {
        *(int *)(base + 48) = 0;
    }
    *arg0 = g_resultSuccess.v;
}

igResult Gap__Core__igArenaMemoryPool__vfunc_45(igArenaMemoryPool *pool, igMemoryPoolInfo *info) {
    igResult result;
    result = FUN_002f0880((void **)pool, (void *)info);
    const char *options = igMemoryPoolInfo_options(info);
    const char *integrityCheck = igMemoryPoolInfo_checking(info);
    const char *messages = igMemoryPoolInfo_messages(info);
    if (options) {
        int flags = 0;
        if (strstr(options, ((char *)text_Fill))) flags |= 2;
        if (strstr(options, ((char *)text_Zero))) flags |= 4;
        if (strstr(options, text_Sentinels)) flags |= 1;
        if (strstr(options, text_Contiguous)) flags |= 0x10;
        if (strstr(options, ((char *)text_AutoLock))) flags |= 8;
        if (strstr(options, ((char *)text_SystemMemoryExhausted))) flags |= 0x80;
        if (strstr(options, text_PreSizeReached)) flags |= 0x40;
        if (strstr(options, ((char *)text_MaxSizeReached))) flags |= 0x20;
        if (pool == ((struct CoreGlobals * *)g_objectSystem)[0]->defaultPool && (flags & 1) != (pool->_poolOptionFlags & 1)) {
            flags ^= 1;
        }
        igArenaMemoryPool_SetPoolOptionFlags((SetFlagsPool *)pool, flags);
    }
    if (integrityCheck) {
        int level = pool->_heapIntegrityCheckLevel;
        if (strstr(integrityCheck, text_NoChecking)) {
            level = 0;
        } else if (strstr(integrityCheck, text_LightChecking)) {
            level = 1;
        } else if (strstr(integrityCheck, text_ModerateChecking)) {
            level = 2;
        } else if (strstr(integrityCheck, text_HeavyChecking)) {
            level = 3;
        }
        pool->_heapIntegrityCheckLevel = level;
    }
    if (messages) {
        int level = pool->_messageLevel;
        if (strstr(messages, ((char *)text_NoMessages))) {
            level = 0;
        } else if (strstr(messages, ((char *)text_ErrorMessages))) {
            level = 1;
        } else if (strstr(messages, ((char *)text_WarningMessages))) {
            level = 2;
        } else if (strstr(messages, ((char *)text_Notifications))) {
            level = 3;
        }
        pool->_messageLevel = level;
    }
    return result;
}

void Gap__Core__igArenaMemoryPool__vfunc_30(Pool30 *arg0) {
    igResult sp2C;
    if (arg0->f116 == 0) {
        arg0->v204();
        arg0->f136 = 0;
        arg0->f116 = 1;
        arg0->f196 = 0;
        if (arg0->f192 & 8) {
            sp2C = arg0->v136(1);
        }
        if (arg0->f168 != 0) {
            arg0->v264(arg0->v216(0x10));
        }
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self) {
    int arenaState;

    if (self->_size != 0) {
        ((igMemoryPoolView *)self)->vfunc_51();
        self->_systemAllocated = 0;
        arenaState = self->_arenaState;
        if (arenaState != 0) {
            memset(arenaState, 0, 0x814);
        }
    } else {
        ((igMemoryPoolView *)self)->Trim(1);
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0) {
    Pool32 *p = (Pool32 *)arg0;
    if (p->f116 != 0) {
        p->f116 = 0;
        p->vX();
    }
}

/* Getter for the reflected `_isActive` member (igBoolMetaField at +116). */

unsigned char Gap__Core__igArenaMemoryPool__vfunc_33(igArenaMemoryPool *self) {
    return self->_isActive;
}

/* IgArenaMemoryPool slot 26, returns the reflected _rawMemory block pointer (+124). */
int Gap__Core__igArenaMemoryPool__vfunc_26(igArenaMemoryPool *self) {
    return self->_rawMemory;
}

void Gap__Core__igArenaMemoryPool__vfunc_24(int *out, Pool24 *p, int a2, long long a3, char t0) {
    if (p->busy == 0) {
        p->f124 = a2;
        p->buf->f2036 = a2;
        unsigned long long m = a3 & 0xFFFFFFFFFFFFFFFCULL;
        p->f160 = m;
        p->f128 = t0;
        p->buf->f2044 = (int)m;
        p->buf->f2048 = (int)m;
        p->buf->f2056 = (int)m;
        p->v51();
        p->f136 = 0;
        p->f105 = t0;
        *out = g_resultSuccess.v;
    } else {
        *out = g_resultFailure.v;
    }
}

/* Getter for the reflected `_isAlchemyMemory` member (igBoolMetaField at +128). */

unsigned char Gap__Core__igArenaMemoryPool__vfunc_25(igArenaMemoryPool *self) {
    return self->_isAlchemyMemory;
}

/* igMemoryPool slot 29 (vtable +116): constant 0 for the arena pool. This is the predicate
 * igAllocator_EncodeIndex calls on an allocator: zero selects the primary allocator list (even
 * encoded index), nonzero the secondary list. igMallocMemoryPool also returns 0; igPageMemoryPool
 * and igStackMemoryPool return 1. The receiver is not read. */
int Gap__Core__igArenaMemoryPool__vfunc_29(void) {
    return 0;
}

static inline void releaseAllocationLock(igArenaMemoryPool *p) {
    igSemaphoreView *x = (igSemaphoreView *)p->_allocationLock;
    if (x) {
        x->_refCount = x->_refCount - 1;
        if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(x);
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_34(int *ret, igArenaMemoryPool *p, int flag) {
    int fl;
    if (flag != 0) {
        fl = p->_poolOptionFlags | 8;
    } else {
        fl = p->_poolOptionFlags & ~8;
    }
    igArenaMemoryPool_SetPoolOptionFlags((SetFlagsPool *)p, fl);
    if ((unsigned char)flag == 0) {
        igSmartPointer<igSemaphoreView> lock((igSemaphoreView *)p->_allocationLock, kRetainReference);
        releaseAllocationLock(p);
        p->_allocationLock = 0;
        if (lock.p != 0) {
            lock->wait(1);
            lock->destroy();
        }
    } else if ((unsigned char)flag == 1) {
        if (p->_allocationLock != 0) { *ret = g_resultSuccess.v; return; }
        igSmartPointer<igSemaphoreView> created((igSemaphoreView *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)p)))));
        created->create();
        igSemaphoreView *t = created.p;
        if (t) t->_refCount = t->_refCount + 1;
        releaseAllocationLock(p);
        p->_allocationLock = (int)t;
    }
    *ret = g_resultSuccess.v;
}

/* igArenaMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument; same leaf as
 * FUN_002f0620 and igMallocMemoryPool slot 24. */
void Gap__Core__igArenaMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_resultFailure.v;
}

long long Gap__Core__igArenaMemoryPool__vfunc_36(igArenaMemoryPool *arg0) {
    long long temp_v0;

    temp_v0 = arg0->_size;
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return arg0->_systemAllocated;
}

/* The comparison is written `arg2 <= lim`, not `lim >= arg2`, and the store is repeated in both
 * arms. */
void Gap__Core__igArenaMemoryPool__vfunc_41(int *arg0, char *arg1, unsigned long long arg2) {
    unsigned long long lim = *(unsigned long long *)(arg1 + 160);
    if (lim == 0 || arg2 <= lim) {
        *(unsigned long long *)(arg1 + 152) = arg2;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* Accessor: the arena's reflected _maxSize field (igUnsignedLongMetaField, +152). */
long long Gap__Core__igArenaMemoryPool__vfunc_42(igArenaMemoryPool *self) {
    return self->_maxSize;
}

void Gap__Core__igArenaMemoryPool__vfunc_43(int *arg0, void *arg1, int arg2) {
    *(int *)((char *)(arg1) + 168) = arg2;
    *(int *)((char *)(arg1) + 196) = 0;
    if (((MemoryPool *)arg1)->IsActive() != 0) {
        ((igMemoryPoolView *)arg1)->Free(((igMemoryPoolView *)arg1)->Allocate(0x10));
    }
    *arg0 = g_resultSuccess.v;
}

/* IgArenaMemoryPool virtual getter 44. Returns the reflected `_preSize` field
 * (igUnsignedIntMetaField, +168). */
int Gap__Core__igArenaMemoryPool__vfunc_44(igArenaMemoryPool *self) {
    return self->_preSize;
}

/* Setter for the pool's _alignment (a 16-bit field at +172). It reports through a status word,
 * always the "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void Gap__Core__igArenaMemoryPool__vfunc_37(int *outStatus, igArenaMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_resultSuccess.v;
}

/* Getter for the reflected `_alignment` member (igUnsignedShortMetaField at +172). */

unsigned short Gap__Core__igArenaMemoryPool__vfunc_38(igArenaMemoryPool *self) {
    return self->_alignment;
}

/* Setter for the pool's _elementSize (+144). It reports through a status word, always the
 * "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void Gap__Core__igArenaMemoryPool__vfunc_39(int *outStatus, igArenaMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *outStatus = g_resultSuccess.v;
}

/* IgArenaMemoryPool slot 40, returns the reflected _elementSize (+144). */
int Gap__Core__igArenaMemoryPool__vfunc_40(igArenaMemoryPool *self) {
    return self->_elementSize;
}

long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

/* Accessor: the arena's reflected _localNetAllocated statistic (igLongMetaField, +24). */
long long Gap__Core__igArenaMemoryPool__vfunc_47(igArenaMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Accessor: the arena's reflected _localNetAllocatedWithOverhead statistic (igLongMetaField, +56). */
long long Gap__Core__igArenaMemoryPool__vfunc_48(igArenaMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long Gap__Core__igArenaMemoryPool__vfunc_99(void *arg0) {
    return *(long long *)((char *)arg0 + 32);
}

long long Gap__Core__igArenaMemoryPool__vfunc_100(void *arg0) {
    return *(long long *)((char *)arg0 + 64);
}

int FUN_0031d370(void *arg0) {
    int temp_v1;
    int var_v0;

    temp_v1 = *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2028);
    var_v0 = temp_v1 >> 1;
    if (temp_v1 < 0) {
        var_v0 = (int) (temp_v1 + 1) >> 1;
    }
    return var_v0;
}

int FUN_0031d390(void *arg0) {
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2032);
}

long long Gap__Core__igArenaMemoryPool__vfunc_101(void *arg0) {
    long long temp_v0;

    temp_v0 = *(long long *)((char *)(arg0) + 160);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return *(long long *)((char *)(arg0) + 136);
}

long long Gap__Core__igArenaMemoryPool__vfunc_49(igArenaMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

void *Gap__Core__igArenaMemoryPool__vfunc_53(igArenaMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

void FUN_0031d3f0(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->wait(1);
    }
}

void FUN_0031d430(void *arg0) {
    igResult sp1C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp1C = ((igSemaphoreView *)(temp_a1))->signal();
    }
}

int FUN_0031d460(void *arg0, int arg1) {
    igResult sp2C;
    void **temp_a1;

    temp_a1 = (void **)((igArenaMemoryPool *)arg0)->_allocationLock;
    if (temp_a1 != 0) {
        sp2C = ((igSemaphoreView *)(temp_a1))->signal();
    }
    return arg1;
}

void *Gap__Core__igArenaMemoryPool__vfunc_54(igArenaMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, self->_alignment);
}

void *Gap__Core__igArenaMemoryPool__vfunc_55(igArenaMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

static inline int flag2(ArenaPoolFlags *p) { return (p->flags & 2) != 0; }

static inline int flag4(ArenaPoolFlags *p) { return (p->flags & 4) != 0; }

void *Gap__Core__igArenaMemoryPool__vfunc_56(Pool56 *self, int count, int size) {
    int total = count * size;
    void *p = self->Alloc(0, total, ((ArenaPoolFlags *)self)->align);
    if (p != 0) {
        if (total != 0) {
            if (flag2((ArenaPoolFlags *)self) || !flag4((ArenaPoolFlags *)self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int Gap__Core__igArenaMemoryPool__vfunc_57(Flags57 *t, int n, int m) {
    int total = n * m;
    int p = ((Pool57 *)t)->vX(0, total);
    if (p != 0) {
        if (total != 0) {
            int f = t->f192;
            if (((f & 2) ? 1 : 0) || !((f & 4) ? 1 : 0)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

void *Gap__Core__igArenaMemoryPool__vfunc_58(igArenaMemoryPoolView *self, void *block, unsigned int size)
{
    return self->MemoryOperation(block, size, self->_alignment);
}

void *Gap__Core__igArenaMemoryPool__vfunc_59(igArenaMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->MemoryOperation(block, size, alignment);
}

void Gap__Core__igArenaMemoryPool__vfunc_63(int *arg0) {
    *arg0 = g_resultFailure.v;
}

static inline char *blockHeader(char *p) {
    char *h = p - 4;
    if (((MallocBlockEnd *)(p - 1))->flag == 1) h = p - 12;
    return h;
}

static inline char *padRecord(char *h) {
    if (((MallocBlockTag *)(h + 3))->padded) return h - 10;
    return h - 8;
}

void Gap__Core__igArenaMemoryPool__freeSized(MallocPoolFreeView *self, unsigned int size, char **block) {
    char *q = padRecord(blockHeader(*block));
    self->_localFreeCount += *(unsigned short *)(q + 2);
    self->_localNetAllocationCount -= size;
    self->Release((char *)((int)q - 4) - 4);
}

void Gap__Core__igArenaMemoryPool__vfunc_97(Pool97 *self) {
    int v;
    FUN_002f2260(self);
    self->w4 = 0;
    ((Bits *)&self->w4)->refs = 1;
    ((char *)self)[7] = 0;
    self->arena = (Arena97 *)g_activeSystemAllocator[0]->Allocate(0x814);
    if (self->arena == 0 && GPR_00554d64 == 0) {
        v = igReportError(text_Unable_to_allocate_memory_for_ar);
        if (v != 1) {
            if (v == 2)
                GPR_00554d64 = 1;
        }
    }
    memset(self->arena, 0, 0x814);
    self->raw = 0;
    self->alch = 0;
    self->sysAlloc = 0;
    self->v49();
    self->maxSize = 0xFFFFFFFFFFFFFFFFULL;
    self->size = 0;
    self->preSize = 0;
    self->alignment = 1;
    releaseRefObject(self->tracker);
    self->tracker = 0;
    self->isActive = 0;
    DAT_00587200[0] = DAT_00587200[0] + 1;
    releaseRefObject(self->lock);
    self->lock = 0;
    self->poolIndex = 0;
    self->heapLevel = 0;
    self->msgLevel = 1;
    self->optFlags = DAT_004c2370[0] & ~8;
    self->preSized = 0;
    self->smallest = 16;
    if (self->arena->f2020 == 0) {
        self->arena->f2020 = (int)g_activeSystemAllocator[0]->AllocateAligned(0x200, 4);
        if (self->arena->f2020 == 0 && GPR_00554d68 == 0) {
            v = igReportError(text_Unable_to_allocate_memory_for_ar);
            if (v != 1) {
                if (v == 2)
                    GPR_00554d68 = 1;
            }
        }
        self->arena->f2024 = 0x200;
        self->arena->f2028 = 0;
        self->arena->f2032 = 0;
        self->arena->f2060 = -1;
        self->arena->f2064 = 0;
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_98(Pool98 *arg0) {
    int *name;
    int r;
    Arena98 *temp_v1;
    int temp_a1;

    if (arg0->f160 == 0) {
        FUN_00318b40();
    }
    if ((int)arg0->f24 != 0) {
        name = ((int *)FUN_002f89a0((int)arg0));
        arg0->v100();
        if ((arg0->f188 >= 3) && (GPR_00554d6c == 0)) {
            long long k24 = arg0->f24;
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd670, name, arg0->f180, (int)k24);
            if ((r != 1) && (r == 2)) {
                GPR_00554d6c = 1;
            }
        }
        arg0->v86();
    } else if (arg0->f88 != 0) {
        name = ((int *)FUN_002f89a0((int)arg0));
        if ((arg0->f188 >= 3) && (GPR_00554d70 == 0)) {
            long long k88 = arg0->f88;
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd6d0, name, arg0->f180, (int)k88);
            if ((r != 1) && (r == 2)) {
                GPR_00554d70 = 1;
            }
        }
        arg0->v86();
    }
    int t = (arg0->f192 & 0x200) != 0;
    if (!t && FUN_0031d390(arg0) > 1U) {
        name = ((int *)FUN_002f89a0((int)arg0));
        if ((arg0->f188 >= 3) && (GPR_00554d74 == 0)) {
            name = name ? name : &DAT_004f7910[0];
            r = igReportNotice(DAT_004fd730, name, arg0->f180, FUN_0031d390(arg0));
            if ((r != 1) && (r == 2)) {
                GPR_00554d74 = 1;
            }
        }
    }
    DAT_00587208[0] += (int)arg0->f24;
    DAT_00587210[0] += arg0->f56;
    if (arg0->f160 == 0) {
        arg0->v25(0);
    }
    temp_v1 = arg0->f112;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1->f2020;
        if (temp_a1 != 0) {
            g_activeSystemAllocator[0]->Free((void *)temp_a1);
            arg0->f112->f2024 = 0;
            arg0->f112->f2028 = 0;
            arg0->f112->f2032 = 0;
        }
        g_activeSystemAllocator[0]->Free((void *)arg0->f112);
        arg0->f112 = 0;
    }
    arg0->f112 = 0;
    DAT_00587200[0] -= 1;
}

void *FUN_0031eb90(igArenaMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *FUN_0031ebd0(igArenaMemoryPool *arg0, int extra1) {
    FUN_002effb0((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    if (arg0 != 0) {
        FUN_0031eb90(arg0);
    }
    return arg0;
}

void *FUN_0031ec20(igArenaMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00531030[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void Gap__Core__igArenaMemoryPool__vfunc_02(void **self) {
    ((igMemoryPoolView *)(self))->vfunc_98();
    Gap__Core__igObject__vfunc_00((int)self);
}

void Gap__Core__igArenaMemoryPool__vfunc_66(igArenaMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, self->_alignment);
}

int Gap__Core__igArenaMemoryPool__vfunc_85(void *self, unsigned char *p) {
    struct Header85 *h;
    unsigned off;
    unsigned idx;
    if (p == 0) {
        return 0;
    }
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) {
            p = p - off;
        } else {
            return 0;
        }
    }
    h = (struct Header85 *)(p - 4);
    if (((struct TagByte *)(p - 1))->flag == 1) {
        h = (struct Header85 *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        idx = h->idx;
    } else {
        idx = h->idx + (h->ext << 5);
    }
    return ((void *)igAllocator_ResolveEncodedIndex(idx * 2)) == self;
}

int Gap__Core__igArenaMemoryPool__vfunc_83(void) {
    return 1;
}

int Gap__Core__igArenaMemoryPool__vfunc_84(int arg0, unsigned char *p) {
    unsigned int off;
    unsigned int v;
    struct Header84 *h;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        p = p - off;
        h = (struct Header84 *)(p - 4);
        if (((struct TagByte *)(p - 1))->flag == 1) {
            h = (struct Header84 *)(p - 12);
        }
        if (h == 0) {
            return 0;
        }
        if (h->big == 0) {
            v = h->sz;
        } else {
            v = h->sz + (h->ext << 19);
        }
        return v - (off + 4);
    }
    h = (struct Header84 *)(p - 4);
    if (((struct TagByte *)(p - 1))->flag == 1) {
        h = (struct Header84 *)(p - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->big == 0) {
        return h->sz;
    }
    return h->sz + (h->ext << 19);
}

void igArenaMemoryPool_SetPoolOptionFlags(SetFlagsPool *p, int f) {
    int r;
    if ((f & 1) != (p->flags & 1)) {
        if (p->vX(f & 1) != 0) {
            if (p->cnt > 0) {
                Memory_PrintPoolStatistics(0, p);
                if (GPR_00554d78 == 0) {
                    r = igReportNotice(DAT_004fd7a0);
                    if (r != 1) { if (r == 2) { GPR_00554d78 = 1; } }
                }
            }
            return;
        }
    }
    p->flags = f;
}

int Gap__Core__igArenaMemoryPool__vfunc_89(void *arg0) {
    return *(int *)((char *)(arg0) + 176);
}

void Gap__Core__igArenaMemoryPool__vfunc_90(int *arg0, igObject *arg1) {
    igObject *o;
    if (arg1 == 0 || (int *)((void *)igObject_GetAllocator((int)arg1)) != arg0) {
        if (arg1 != 0) {
            arg1->_refCount++;
        }
        o = (igObject *)arg0[44];
        if (o != 0) {
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0[44] = (int)arg1;
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_86(void) {

}

int Gap__Core__igArenaMemoryPool__vfunc_91(void *arg0) {
    return *(int *)((char *)(arg0) + 180);
}

void Gap__Core__igArenaMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 180) = arg1;
    if (*(int *)((char *)(arg0) + 180) >= 0x40) {
        *(int *)((char *)(arg0) + 200) = 0x18;
    } else {
        *(int *)((char *)(arg0) + 200) = 0x10;
    }
}

void Gap__Core__igArenaMemoryPool__vfunc_93(int *arg0, Pool93 *arg1, char *arg2, igMemoryPoolView *arg3) {
    int v = arg3->GetPoolIndex();
    int ok;
    Header93 *h;
    int a;
    ok = arg1->Chk(v);
    if (ok != 0) {
        if (*(unsigned int *)(arg2 - 4) == 0xAAAAAAAF) {
            unsigned int off = *(unsigned int *)(arg2 - 8);
            if (off < 0x100011) {
                arg2 = arg2 - off;
            } else {
                *arg0 = g_resultFailure.v;
                return;
            }
        }
        h = (Header93 *)(arg2 - 4);
        if (((TagByte93 *)(arg2 - 1))->flag == 1) {
            h = (Header93 *)(arg2 - 12);
        }
        a = arg3->GetPoolIndex() >> 1;
        h->lo = a;
        if (h->flag == 1) {
            h->ext = a >> 5;
        }
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

int Gap__Core__igArenaMemoryPool__vfunc_94(void *arg0, void **arg1) {
    int temp_v0;
    int var_v0;

    temp_v0 = ((igMemoryPoolView *)(arg1))->GetPoolIndex();
    if ((*(int *)((char *)(arg0) + 180) < 0x40) && (temp_v0 >= 0x40)) {
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }
    if (var_v0 != 0) {
        return 1;
    }
    return 0;
}

int Gap__Core__igArenaMemoryPool__vfunc_95(int arg0, unsigned char *p) {
    struct Header95 *a0; unsigned int off, v;
    if (p == 0) return -1;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) { p = p - off; } else { return -1; }
    }
    a0 = (struct Header95 *)(p - 4);
    if (((struct TagByte *)(p - 1))->flag == 1) { a0 = (struct Header95 *)(p - 12); }
    if (a0 == 0) return -1;
    if (a0->big == 0) { v = a0->sz; } else { v = a0->sz + (a0->ext << 5); }
    return v * 2;
}

void Gap__Core__igArenaMemoryPool__vfunc_03(Pool03 *arg0, int arg1) {
    int t;
    arg0->f70 = (Arena03 *)g_activeSystemAllocator[0]->Allocate(0x814);
    memset(arg0->f70, 0, 0x814);
    if (arg0->f70->f7e4 == 0) {
        arg0->f70->f7e4 = g_activeSystemAllocator[0]->AllocateAligned(0x200, 4);
        if (arg0->f70->f7e4 == 0 && GPR_00554d7c == 0) {
            t = igReportError(text_Unable_to_allocate_memory_for_ar);
            if (t != 1 && t == 2) {
                GPR_00554d7c = 1;
            }
        }
        arg0->f70->f7e8 = 0x200;
        arg0->f70->f7ec = 0;
        arg0->f70->f7f0 = 0;
        arg0->f70->f80c = -1;
        arg0->f70->f810 = 0;
    }
    DAT_00587200[0] += 1;
    Gap__Core__igObject__constructFields((int)arg0, arg1);
}

void Gap__Core__igArenaMemoryPool__vfunc_04(igArenaMemoryPool *self) {
    ((ArenaPoolSlot392View *)self)->Slot392();
    Gap__Core__igObject__destructFields((int)self);
}

void Gap__Core__igArenaMemoryPool__vfunc_13(igArenaMemoryPool *self, int extra1) {
    Gap__Core__igObject__resetFields((int)self, extra1);
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c2370[0];
}

unsigned int Gap__Core__igArenaMemoryPool__vfunc_105(igArenaMemoryPool *arg0, int arg1, int arg2) {
    unsigned int temp_a1;
    unsigned int temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    if (arg0->_size != 0) {
        return -1U;
    }
    temp_v0 = g_activeSystemAllocator[0]->vfunc_17(arg1, arg2);
    if (temp_v0 != -1U) {
        arg0->_systemAllocated = arg0->_systemAllocated + arg2;
        temp_v1 = (void *)(arg0->_arenaState);
        if (temp_v0 < (unsigned int) *(int *)((char *)(temp_v1) + 2060)) {
            *(int *)((char *)(temp_v1) + 2060) = temp_v0;
        }
        temp_v1_2 = (void *)(arg0->_arenaState);
        temp_a1 = temp_v0 + arg2;
        if ((unsigned int) *(int *)((char *)(temp_v1_2) + 2064) < temp_a1) {
            *(int *)((char *)(temp_v1_2) + 2064) = temp_a1;
        }
    }
    return temp_v0;
}

igResult Gap__Core__igArenaMemoryPool__vfunc_106(void *arg1, int arg2, long long arg3) {
    igArenaMemoryPool *f = (igArenaMemoryPool *)arg1;
    if (f->_size != 0) {
        igResult r;
        r.v = g_resultFailure.v;
        return r;
    }
    long long d = (long long)(int)arg3;
    if ((unsigned long long)d < f->_systemAllocated) {
        f->_systemAllocated = f->_systemAllocated - d;
    } else {
        f->_systemAllocated = 0;
    }
    return g_activeSystemAllocator[0]->vfunc_18(arg2, arg3);
}

void Gap__Core__igArenaMemoryPool__vfunc_107(igArenaMemoryPoolView *self)
{
    (*(igObjectDispatchView **)g_activeSystemAllocator)->vfunc_17();
}

void Gap__Core__igArenaMemoryPool__vfunc_108(void) {

}

int Gap__Core__igArenaMemoryPool__vfunc_109(void *arg0) {
    int temp_v0;

    temp_v0 = *(int *)((char *)(arg0) + 124);
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2060);
}

int Gap__Core__igArenaMemoryPool__vfunc_110(void *arg0) {
    int temp_v1;

    temp_v1 = *(int *)((char *)(arg0) + 124);
    if (temp_v1 != 0) {
        return temp_v1 + *(int *)((char *)(arg0) + 160);
    }
    return *(int *)((char *)(*(int *)((char *)(arg0) + 112)) + 2064);
}

