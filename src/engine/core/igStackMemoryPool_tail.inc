/* Configures the pool from its info record: the base class's step only. The result is a local
 * copied out, as in the pools that go on to read the info's strings. */
igResult igStackMemoryPool_Configure(igStackMemoryPool *self, igMemoryPoolInfo *info) {
    igResult result = igMemoryPool_Configure((void **)self, (void *)info);
    return result;
}

void igStackMemoryPool_Activate(igStackMemoryPool *p) {
    unsigned v = p->_rawMemory;
    if (v != 0) {
        p->_stackPtr = v;
        p->_nextInt = (int)((unsigned long long)p->_stackPtr + p->_totalSize + 0xFFFFFFFFFFFFFFFCULL);
        p->_nextInt = p->_nextInt - (p->_nextInt & 3);
        p->_isActive = 1;
    }
}

void igStackMemoryPool_Reset(igStackMemoryPool *s) {
    s->_stackPtr = s->_rawMemory;
    s->_nextInt = (int)(s->_stackPtr + s->_totalSize + (long long)(unsigned __int128)(unsigned long long)-4LL);
    s->_nextInt = s->_nextInt - (s->_nextInt & 3);
}

void igStackMemoryPool_Deactivate(igStackMemoryPool *self) {
    ((igMemoryPoolView *)self)->vfunc_31();
    self->_isActive = 0;
}

/* Reports whether the pool is active: returns _isActive (+140), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char igStackMemoryPool_IsActive(igStackMemoryPool *self) {
    return self->_isActive;
}

/* IgStackMemoryPool vtable slot 35: status leaf. Ignores the object and writes the engine's
 * current failure-status word (the one an allocation failure publishes) through the output-first
 * argument. */
void igStackMemoryPool_SetSize(int *status_out) {
    *status_out = g_resultFailure.v;
}

/* Slot 36 getter: returns the pool's _totalSize field (an int widened to 64 bits). */
long long igStackMemoryPool_GetSize(igStackMemoryPool *self) {
    return self->_totalSize;
}

/* Set the pool's alignment (`_alignment`, +112) and report success through the status word.
 * vfunc_38 is the matching getter. */
void igStackMemoryPool_SetAlignment(int *status, igStackMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_resultSuccess.v;
}

/* IgStackMemoryPool slot 38, returns the reflected _alignment (+112, unsigned short). */
unsigned short igStackMemoryPool_GetAlignment(igStackMemoryPool *self) {
    return self->_alignment;
}

/* Set the pool's element size (`_elementSize`, +128) and report success through the status word. */
void igStackMemoryPool_SetElementSize(int *status, igStackMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_resultSuccess.v;
}

/* Getter: the pool's _elementSize (+128, reflected as igUnsignedIntMetaField). */
int igStackMemoryPool_GetElementSize(igStackMemoryPool *self) {
    return self->_elementSize;
}

void igStackMemoryPool_SetRawMemory(int *arg0, void *arg1, int arg2, long long arg3, char arg4) {
    if (*(unsigned char *)((char *)(arg1) + 140) == 0) {
        *(int *)((char *)(arg1) + 116) = arg2;
        *(long long *)((char *)(arg1) + 120) = arg3;
        *(char *)((char *)(arg1) + 141) = arg4;
        *arg0 = g_resultSuccess.v;
    } else {
        *arg0 = g_resultFailure.v;
    }
}

/* Getter: the pool's _rawMemory reference (+116, reflected as igRawRefMetaField), the backing
 * block the stack pointer walks through. */
int igStackMemoryPool_GetRawMemory(igStackMemoryPool *self) {
    return self->_rawMemory;
}

/* IgStackMemoryPool vtable slot 42: getter for the reflected _totalSize (+120,
 * igUnsignedLongMetaField). Returned as a 64-bit value, like igArenaMemoryPool slot 42 for its
 * _maxSize. */
long long igStackMemoryPool_GetMaxSize(igStackMemoryPool *self) {
    return self->_totalSize;
}

long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}

long long igStackMemoryPool_GetLocalNetAllocated(igStackMemoryPool *arg0) {
    int cur;
    long long total = 0;
    StackBlockRecord *e;
    int raw;
    if (arg0->_isActive == 0) {
        return 0;
    }
    cur = arg0->_stackPtr;
    e = (StackBlockRecord *)arg0->_nextInt + 1;
    raw = arg0->_rawMemory;
    while (cur != raw) {
        unsigned t = e->size;
        e++;
        total += t;
        cur -= t;
    }
    return total;
}

long long igStackMemoryPool_GetLocalNetAllocatedWithOverhead(igStackMemoryPool *arg0) {
    return arg0->_totalSize - ((igMemoryPoolView *)arg0)->vfunc_49();
}

long long igStackMemoryPool_GetFreeSize(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}

int igStackMemoryPool_AllocateElement(igStackMemoryPool *arg0) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    int size;
    if (arg0->_isActive == 0) { return 0; }
    size = arg0->_elementSize;
    if (size == 0) { return 0; }
    if (size == 0) { return 0; }
    align = arg0->_alignment;
    mask = align - 1;
    pad = (align - ((int)arg0->_stackPtr & mask)) & mask;
    total = size + pad;
    if ((int)arg0->_nextInt - (int)arg0->_stackPtr < total) { return 0; }
    cur = (int)arg0->_stackPtr + pad;
    arg0->_stackPtr += total;
    *(int *)arg0->_nextInt = total;
    arg0->_nextInt -= 4;
    return cur;
}

int igStackMemoryPool_Allocate(igStackMemoryPool *arg0, int arg1) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    if (arg1 == 0) {
        return 0;
    }
    align = arg0->_alignment;
    mask = align - 1;
    cur = arg0->_stackPtr;
    pad = mask & (align - (cur & mask));
    total = arg1 + pad;
    if ((int)arg0->_nextInt - cur < total) {
        return 0;
    }
    arg0->_stackPtr = cur + total;
    *(int *)arg0->_nextInt = total;
    arg0->_nextInt -= 4;
    return cur + pad;
}

int igStackMemoryPool_AllocateAligned(igStackMemoryPool *arg0, int size, unsigned short arg2) {
    int total, pad, mask, ret;
    unsigned short align;
    unsigned short pool;
    if (size == 0) { size = 1; }
    pool = arg0->_alignment;
    if (size == 0) { return 0; }
    arg2 = (arg2 > pool) ? arg2 : pool;
    align = arg2;
    mask = align - 1;
    pad = (align - ((int)arg0->_stackPtr & mask)) & mask;
    total = size + pad;
    if ((int)arg0->_nextInt - (int)arg0->_stackPtr < total) { return 0; }
    ret = (int)arg0->_stackPtr + pad;
    arg0->_stackPtr += total;
    *(int *)arg0->_nextInt = total;
    arg0->_nextInt -= 4;
    return ret;
}

void *igStackMemoryPool_Callocate(igStackMemoryPool *s, int count, int size) {
    int total = count * size;
    if (total == 0) { total = 1; }
    if (total == 0) {
        return 0;
    } else {
        void *p;
        int pad;
        int mask;
        int need;
        unsigned short align = s->_alignment;
        mask = align - 1;
        pad = (align - ((int)s->_stackPtr & mask)) & mask;
        need = total + pad;
        if ((int)s->_nextInt - (int)s->_stackPtr < need) { return 0; }
        p = (void *)((int)s->_stackPtr + pad);
        s->_stackPtr += need;
        *(int *)s->_nextInt = need;
        s->_nextInt -= 4;
        memset(p, 0, total);
        return p;
    }
}

void *igStackMemoryPool_CallocateAligned(igStackMemoryPool *s, int count, int size, unsigned short a) {
    int total = count * size;
    unsigned short pool;
    if (total == 0) { total = 1; }
    pool = s->_alignment;
    if (total == 0) {
        return 0;
    } else {
        void *p;
        int pad;
        int mask;
        int need;
        unsigned short align;
        a = (a > pool) ? a : pool;
        align = a;
        mask = align - 1;
        pad = (align - ((int)s->_stackPtr & mask)) & mask;
        need = total + pad;
        if ((int)s->_nextInt - (int)s->_stackPtr < need) { return 0; }
        p = (void *)((int)s->_stackPtr + pad);
        s->_stackPtr += need;
        *(int *)s->_nextInt = need;
        s->_nextInt -= 4;
        memset(p, 0, total);
        return p;
    }
}

int igStackMemoryPool_Reallocate(void **arg0, int arg1, unsigned int arg2) {
    int var_v0;
    unsigned int temp_v0;
    unsigned int temp_v0_2;

    if (arg2 != 0) {
        var_v0 = (int)((igMemoryPoolView *)arg0)->Allocate(arg2);
    } else {
        var_v0 = 0;
    }
    if (arg1 != 0) {
        if (var_v0 != 0) {
            temp_v0 = ((igMemoryPoolView *)arg0)->GetAllocationSize((void *)arg1);
            temp_v0_2 = (temp_v0 < arg2) ? temp_v0 : arg2;
            if (var_v0 != 0) {
                memcpy(var_v0, arg1, temp_v0_2);
            }
        }
        ((igMemoryPoolView *)arg0)->Free((void *)arg1);
    }
    return var_v0;
}

int igStackMemoryPool_ReallocateAligned(void **arg0, int arg1, unsigned int arg2, unsigned short arg3) {
    int var_v0;
    unsigned int temp_v0;
    unsigned int temp_v0_2;

    if (arg2 != 0) {
        var_v0 = (int)((igMemoryPoolView *)arg0)->AllocateAligned(arg2, arg3);
    } else {
        var_v0 = 0;
    }
    if (arg1 != 0) {
        if (var_v0 != 0) {
            temp_v0 = ((igMemoryPoolView *)arg0)->GetAllocationSize((void *)arg1);
            temp_v0_2 = (temp_v0 < arg2) ? temp_v0 : arg2;
            if (var_v0 != 0) {
                memcpy(var_v0, arg1, temp_v0_2);
            }
        }
        ((igMemoryPoolView *)arg0)->Free((void *)arg1);
    }
    return var_v0;
}

static inline unsigned short effectiveAlign(igStackMemoryPool *pool, unsigned short wanted) {
    return wanted > pool->_alignment ? wanted : pool->_alignment;
}

/* Allocates `count` blocks at once. Three attempts: the worst-case total (every block padded by a
 * full alignment) fits, so each block is carved off the pool directly; the total without padding
 * fits, so the blocks are laid out against a local copy of the top and committed only if all of
 * them fit; otherwise every result is cleared. One index serves all four loops (its later uses
 * are numbered after every other local), and the pool's top is read from the pool where it is
 * used: the second attempt reads the unmoved top for each block, as retail does. */
void igStackMemoryPool_GangAlloc(int *result, igStackMemoryPool *pool, unsigned short count, unsigned *sizes, unsigned *out) {
    unsigned i;
    unsigned total = 0;
    for (i = 0; i < count; i++) {
        total += sizes[i];
    }
    unsigned mask = pool->_alignment - 1;
    total += (mask + 4) * count;
    unsigned avail = pool->_nextInt + 4 - pool->_stackPtr;
    if (total <= avail) {
        unsigned *end = (unsigned *)pool->_nextInt;
        for (i = 0; i < count; i++) {
            unsigned pad = mask & (pool->_alignment - (pool->_stackPtr & mask));
            unsigned size = pad + sizes[i];
            out[i] = pool->_stackPtr + pad;
            pool->_stackPtr += size;
            *end = size;
            end--;
        }
        pool->_nextInt = (unsigned)end;
        *result = g_resultSuccess.v;
        return;
    }
    if (total - mask * count <= avail) {
        unsigned *end = (unsigned *)pool->_nextInt;
        unsigned low = pool->_stackPtr;
        for (i = 0; i < count; i++) {
            unsigned pad = mask & (pool->_alignment - (pool->_stackPtr & mask));
            unsigned size = pad + sizes[i];
            if ((unsigned)end - low < size) {
                break;
            }
            out[i] = pool->_stackPtr + pad;
            low += size;
            *end = size;
            end--;
        }
        if (i == count) {
            pool->_stackPtr = low;
            pool->_nextInt = (unsigned)end;
            *result = g_resultSuccess.v;
            return;
        }
    }
    for (i = 0; i < count; i++) {
        out[i] = 0;
    }
    *result = g_resultFailure.v;
}

void igStackMemoryPool_GangAllocAligned(int *result, igStackMemoryPool *pool, unsigned short count, unsigned *sizes, unsigned *out, unsigned short *aligns) {
    unsigned i;
    unsigned total = 0;
    unsigned padding = 0;
    for (i = 0; i < count; i++) {
        total += sizes[i];
        padding += effectiveAlign(pool, aligns[i]);
    }
    padding -= count;
    total += padding + count * 4;
    unsigned avail = pool->_nextInt + 4 - pool->_stackPtr;
    if (total <= avail) {
        unsigned *end = (unsigned *)pool->_nextInt;
        for (i = 0; i < count; i++) {
            unsigned align = effectiveAlign(pool, aligns[i]);
            unsigned mask = align - 1;
            unsigned pad = mask & (align - (pool->_stackPtr & mask));
            unsigned size = pad + sizes[i];
            out[i] = pool->_stackPtr + pad;
            pool->_stackPtr += size;
            *end = size;
            end--;
        }
        pool->_nextInt = (unsigned)end;
        *result = g_resultSuccess.v;
        return;
    }
    if (total - padding <= avail) {
        unsigned *end = (unsigned *)pool->_nextInt;
        unsigned low = pool->_stackPtr;
        for (i = 0; i < count; i++) {
            unsigned align = effectiveAlign(pool, aligns[i]);
            unsigned mask = align - 1;
            unsigned pad = mask & (align - (pool->_stackPtr & mask));
            unsigned size = pad + sizes[i];
            if ((unsigned)end - low < size) {
                break;
            }
            out[i] = pool->_stackPtr + pad;
            low += size;
            *end = size;
            end--;
        }
        if (i == count) {
            pool->_stackPtr = low;
            pool->_nextInt = (unsigned)end;
            *result = g_resultSuccess.v;
            return;
        }
    }
    for (i = 0; i < count; i++) {
        out[i] = 0;
    }
    *result = g_resultFailure.v;
}

int igStackMemoryPool_GetAllocationSize(igStackMemoryPool *arg0, unsigned int arg1) {
    StackBlockRecord *a1;
    unsigned int a0;
    unsigned int v1;
    if (((igMemoryPoolView *)arg0)->OwnsAllocation((void *)arg1) == 0) {
        return 0;
    }
    a1 = (StackBlockRecord *)arg0->_nextInt + 1;
    v1 = a1->size;
    a0 = arg0->_stackPtr - v1;
    while (a0 > arg1) {
        a1 += 1;
        v1 = a1->size;
        a0 -= v1;
    }
    return v1 - (arg1 - a0);
}

bool igStackMemoryPool_OwnsAllocation(igStackMemoryPool *s, unsigned a) {
    bool r = false;
    if (a >= (unsigned)s->_rawMemory) {
        if ((unsigned long long)a < (unsigned long long)(unsigned)s->_rawMemory + s->_totalSize) r = true;
    }
    return r;
}

void igStackMemoryPool_GangFree(igStackMemoryPool *self, unsigned count, unsigned *ptrs) {
    unsigned last;
    unsigned *end;
    unsigned top;
    unsigned avail;
    unsigned *e;
    unsigned i;
    end = (unsigned *)self->_nextInt;
    last = ptrs[count - 1];
    top = self->_stackPtr;
    avail = top - end[1];
    e = end + 1;
    if (!(avail > last)) {
        self->_stackPtr = avail;
        for (i = 0; i < count - 1; i++) {
            e++;
            self->_stackPtr = self->_stackPtr - (*e & 0x7fffffff);
        }
        while (self->_stackPtr != (unsigned)self->_rawMemory && (*e & 0x80000000)) {
            self->_stackPtr = self->_stackPtr - (*e & 0x7fffffff);
            e++;
        }
        self->_nextInt = (unsigned)(e - 1);
        return;
    }
    e++;
    avail = avail - (*e & 0x7fffffff);
    while (avail > last) {
        e++;
        avail = avail - (*e & 0x7fffffff);
    }
    for (i = 0; i < count; i++) {
        *e = *e | 0x80000000;
        e++;
    }
}

void igStackMemoryPool_Free(igStackMemoryPool *self, unsigned block) {
    unsigned *e;
    unsigned avail;
    unsigned top;
    unsigned v;
    if (block != 0 && ((igMemoryPoolView *)self)->OwnsAllocation((void *)block) != 0) {
        e = (unsigned *)self->_nextInt + 1;
        top = self->_stackPtr;
        v = *e;
        avail = top - v;
        if (!(avail > block)) {
            e++;
            self->_stackPtr = top - (v & 0x7fffffff);
            while (self->_stackPtr != (unsigned)self->_rawMemory && (*e & 0x80000000)) {
                self->_stackPtr = self->_stackPtr - (*e & 0x7fffffff);
                e++;
            }
            self->_nextInt = (unsigned)(e - 1);
            return;
        }
        e++;
        avail = avail - (*e & 0x7fffffff);
        while (avail > block) {
            e++;
            avail = avail - (*e & 0x7fffffff);
        }
        *e = *e | 0x80000000;
    }
}

int igStackMemoryPool_GetEventTracker(void *arg0) {
    return *(int *)((char *)(arg0) + 148);
}

void igStackMemoryPool_SetEventTracker(igStackMemoryPool *arg0, igObject *arg1) {
    igObject *temp_a0;
    if ((arg1 == 0) || (((void *)igObject_GetAllocator((int)arg1)) != arg0)) {
        if (arg1 != 0) {
            arg1->_refCount = (int)((int) (arg1->_refCount + 1));
        }
        temp_a0 = (igObject *)arg0->_eventTracker;
        IG_OBJECT_RELEASE(temp_a0);
        arg0->_eventTracker = (int)arg1;
    }
}

void igStackMemoryPool_Dump(int *a, int a1, int a2, int a3, int a4) {
    Memory_DumpMemory((unsigned int)a1, (unsigned int)a2, (unsigned int)a3, (unsigned int)a[29], (long long)((unsigned int)(a[33] - a[29])), (const char *)a4);
}

int igStackMemoryPool_GetPoolIndex(void *arg0) {
    return *(int *)((char *)(arg0) + 144);
}

void igStackMemoryPool_SetPoolIndex(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 144) = arg1;
}

void igStackMemoryPool_CollectMemoryRegions(igStackMemoryPool *self, igDataList *list) {
    DumpRegion *entry;
    DumpRegion *created;

    if (((igMemoryPoolView *)self)->isActive() != 0) {
        created = DumpRegion_Allocate(sizeof(DumpRegion));
        if (created != 0) {
            created = DumpRegion_Init(created);
        }
        entry = created;
        created->start = self->_rawMemory;
        entry->size = self->_totalSize;
        DumpRegion_SetAnnotation(entry, text_Pool_igStackMemoryPool);
        DumpRegion_SetPoolName(entry, (const char *)Memory_GetPoolName((int)self));
        List_InsertWords(list, List_LowerBound(list, &entry, (Cmp)DumpRegion_CompareStart), 1, &entry);
    }
}
