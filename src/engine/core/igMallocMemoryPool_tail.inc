void Gap__Core__igMallocMemoryPool__vfunc_45(int *arg0, struct A1 *arg1, struct A2 *arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s2;
    int temp_s1;
    int r;
    int sp6C;
    FUN_002f0880(&sp6C, (void **)arg1, (void *)arg2);
    r = sp6C;
    temp_s1 = arg2->f76;
    if (temp_s1 != 0) {
        var_s2 = arg1->f152;
        if (((int)strstr(temp_s1, &NoMessages[0])) != 0) {
            var_s2 = 0;
        } else if (((int)strstr(temp_s1, &ErrorMessages[0])) != 0) {
            var_s2 = 1;
        } else if (((int)strstr(temp_s1, &WarningMessages[0])) != 0) {
            var_s2 = 2;
        } else if (((int)strstr(temp_s1, &Notifications[0])) != 0) {
            var_s2 = 3;
        }
        arg1->f152 = var_s2;
    }
    *arg0 = r;
}

/* Empties the pool and marks it active: the 64-bit _size (+136) is cleared and _isActive (+112)
 * set. */
void Gap__Core__igMallocMemoryPool__vfunc_30(igMallocMemoryPool *self) {
    self->_size = 0;
    self->_isActive = 1;
}

R_3223d0 Gap__Core__igMallocMemoryPool__vfunc_34(OB_3223d0 *arg1, unsigned char arg2) {
    R_3223d0 a;
    R_3223d0 b;
    R_3223d0 c;
    if (arg2 == 0) {
        igSmartPointer<Rc_3223d0> held(arg1->lock);
        arg1->lock.clear();
        if (held.p != 0) {
            a = held.p->v132(1);
            b = held.p->v96();
        }
        arg1->lock.clear();
    } else if (arg2 == 1) {
        if (arg1->lock.p != 0) return R_3223d0(g_statusSucceeded.v);
        igSmartPointer<Rc_3223d0> created((Rc_3223d0 *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)arg1)))));
        c = created.p->v92();
        arg1->lock = created;
    }
    return R_3223d0(g_statusSucceeded.v);
}

void Gap__Core__igMallocMemoryPool__vfunc_35(int *outStatus, igMallocMemoryPool *self, long long size) {
    self->_size = size;
    *outStatus = g_statusSucceeded.v;
}

/* Accessor: the pool's reflected _size field (igUnsignedLongMetaField, +136). */
long long Gap__Core__igMallocMemoryPool__vfunc_36(igMallocMemoryPool *self) {
    return self->_size;
}

void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded.v;
}

/* Accessor: the pool's reflected _maxSize field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igMallocMemoryPool__vfunc_42(igMallocMemoryPool *self) {
    return self->_maxSize;
}

void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_statusSucceeded.v;
}

/* Returns the pool's allocation alignment, _alignment (+144). */
unsigned short Gap__Core__igMallocMemoryPool__vfunc_38(igMallocMemoryPool *self) {
    return self->_alignment;
}

void Gap__Core__igMallocMemoryPool__vfunc_39(int *status, igMallocMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_statusSucceeded.v;
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
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_132_1_3223d0 *)(temp_a1))->vX((int)(1));
    }
}

void FUN_00322860(void *arg0) {
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    }
}

int FUN_00322890(void *arg0, int arg1) {
    DW4SR4 sp2C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp2C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    }
    return arg1;
}

void *Gap__Core__igMallocMemoryPool__vfunc_54(igMallocMemoryPoolView *self, unsigned int size)
{
    return self->vfunc_99(0, size, self->_alignment);
}

void *Gap__Core__igMallocMemoryPool__vfunc_55(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->vfunc_99(0, size, alignment);
}

static inline int flag2_3223d0(MallocPoolFlags *p) { return (p->flags & 2) != 0; }

static inline int flag4_3223d0(MallocPoolFlags *p) { return (p->flags & 4) != 0; }

void *Gap__Core__igMallocMemoryPool__vfunc_56(Pool56_3223d0 *self, int count, int size) {
    int total = count * size;
    void *p = self->Alloc(0, total, ((MallocPoolFlags *)self)->align);
    if (p != 0) {
        if (total != 0) {
            if (flag2_3223d0((MallocPoolFlags *)self) || !flag4_3223d0((MallocPoolFlags *)self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int Gap__Core__igMallocMemoryPool__vfunc_57(igMallocMemoryPool *arg0, int arg1, int arg2) {
    int temp_s1;
    int temp_v0;
    int temp_v1;

    temp_s1 = arg1 * arg2;
    temp_v0 = ((DW4VC_404_2 *)(((char *)(arg0) + 0)))->vX((int)(0), (int)(temp_s1));
    if (temp_v0 != 0) {
        if (temp_s1 != 0) {
            temp_v1 = arg0->_poolOptionFlags;
            if (H57::has(temp_v1, 2) || !H57::has(temp_v1, 4)) {
                memset(temp_v0, 0, temp_s1);
            }
        }
    }
    return temp_v0;
}

void *Gap__Core__igMallocMemoryPool__vfunc_58(igMallocMemoryPoolView *self, void *block, unsigned int size)
{
    return self->vfunc_99(block, size, self->_alignment);
}

void *Gap__Core__igMallocMemoryPool__vfunc_59(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->vfunc_99(block, size, alignment);
}

void Gap__Core__igMallocMemoryPool__vfunc_63(int *arg0) {
    *arg0 = g_allocatorFailureStatus.v;
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

void Gap__Core__igMallocMemoryPool__vfunc_64(MallocPoolFreeView *self, unsigned int size, char **block) {
    char *q = padRecord(blockHeader(*block));
    self->_localFreeCount += *(unsigned short *)(q + 2);
    self->_localNetAllocationCount -= size;
    self->Release((char *)((int)q - 4) - 4);
}

void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self, int extra1) {
    Gap__Core__igObject__vfunc_11((int)self, extra1);
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c25f8[0];
}

void Gap__Core__igMallocMemoryPool__vfunc_97(O_3223d0 *o) {
    Ref_3223d0 *r;
    o->f4.w = 0;
    o->f4.b.cnt = 1;
    *((char *)o + 7) = 0;
    o->f120 = 0;
    o->v49();
    o->f124 = 0;
    o->f128 = (long long)(unsigned __int128)(unsigned long long)-1LL;
    o->f136 = 0;
    o->f144 = 1;
    r = o->f148;
    if (r != 0) {
        r->rc = r->rc - 1;
        if (((unsigned long long)((long long)r->rc << 0x29) >> 0x29) == 0) igObject_Destroy(r);
    }
    o->f148 = 0;
    o->f112 = 0;
    GPR_00554dbc += 1;
    r = (Ref_3223d0 *)o->f116;
    if (r != 0) {
        r->rc = r->rc - 1;
        if (((unsigned long long)((long long)r->rc << 0x29) >> 0x29) == 0) igObject_Destroy(r);
    }
    o->f116 = 0;
    o->f152 = 1;
    o->f156 = 12;
}

void *FUN_003235c0(igMallocMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *FUN_00323600(igMallocMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void Gap__Core__igMallocMemoryPool__vfunc_02(igMallocMemoryPool *self) {
    ((MallocPoolSlot392View *)self)->Slot392();
    Gap__Core__igObject__vfunc_00((int)self);
}

void Gap__Core__igMallocMemoryPool__vfunc_66(igMallocMemoryPoolView *self, void *block)
{
    self->vfunc_99(block, -1, self->_alignment);
}

int Gap__Core__igMallocMemoryPool__vfunc_85(int arg0, char *arg1) {
    H85 *h;
    int v;
    int r;
    int a;

    a = arg0;
    h = (H85 *)(arg1 - 4);
    if (((T85 *)(arg1 - 1))->flag == 1) {
        h = (H85 *)(arg1 - 12);
    }
    if (h == 0) {
        return 0;
    }
    if (h->flag == 0) {
        v = h->lo * 2;
    } else {
        v = (h->lo + (h->ext << 5)) * 2;
    }
    r = igAllocator_ResolveEncodedIndex(v);
    return r == a;
}

int Gap__Core__igMallocMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int Gap__Core__igMallocMemoryPool__vfunc_84(int arg0, char *arg1) {
    H84 *hdr;

    hdr = (H84 *)(arg1 - 4);
    if (hdr->flag == 1) {
        hdr = (H84 *)(arg1 - 0xC);
    }
    if (hdr == 0) {
        return 0;
    }
    if (hdr->flag == 0) {
        return hdr->size;
    }
    return hdr->size + (hdr->s2 << 0x13);
}

void Gap__Core__igMallocMemoryPool__vfunc_87(Pool87 *self, char *title) {
    char buf[64];
    char *name;
    if (title != 0 && title[0] != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
    }
    if (((struct Ctx { char p[36]; int on; } * *)g_objectSystem)[0]->on != 0) {
        name = FUN_00312140(buf, 64, self->name, FUN_002ce1b0());
    } else {
        name = ((char *)DAT_004f7910);
    }
    {
        long long v96 = self->s96;
        long long v88 = self->s88;
        long long v80 = self->s80;
        long long v72 = self->s72;
        long long v64 = self->s64;
        long long v56 = self->s56;
        long long v48 = self->s48;
        long long v40 = self->s40;
        long long v32 = self->s32;
        long long v24 = self->s24;
        long long v16 = self->s16;
        long long v8 = self->s8;
        FUN_00304430(DAT_004fef30, (int)v8, (int)v16, (int)v24, (int)v32, (int)v40, (int)v48, (int)v56, (int)v64, (int)v72, (int)v80, (int)v88, (int)v96, (int)self->Used(), name);
    }
    FUN_00304680();
}

int Gap__Core__igMallocMemoryPool__vfunc_89(void *arg0) {
    return *(int *)((char *)(arg0) + 148);
}

void Gap__Core__igMallocMemoryPool__vfunc_90(S0_3223d0 *arg0, S1_3223d0 *arg1) {
    S1_3223d0 *temp_a0;
    if ((arg1 == 0) || (((void *)igObject_GetAllocator((int)arg1)) != arg0)) {
        if (arg1 != 0) {
            arg1->f4 = (int)((int) (arg1->f4 + 1));
        }
        temp_a0 = arg0->f94;
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->f94 = arg1;
    }
}

void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0) {
    int *g;
    FUN_00322820(self);
    g = &DAT_004ff1b0[0];
    if (t0 != 0) {
        igSmartPointer<V> r((V *)igFile_Create((int)(((void *)igObject_GetAllocator((int)self)))));
        if (r.p->v23(t0, &DAT_004f92f0[0]) == 0) {
            if (((M_3223d0 *)self)->f152 >= 2) {
                FUN_00308390(DAT_004ff1f0, t0);
            }
            FUN_00322860(self);
            return;
        }
        r.p->v29(g);
        r.p->v24();
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

static inline int Chk(int x, int y) { if (x < 64) { if (y >= 64) { return 0; } return 1; } return 1; }

static inline int Chk2(int x, int y) { int r = 1; if (x < 64) { r = 0; if (y >= 64) { } else { r = 1; } } return r; }

void Gap__Core__igMallocMemoryPool__vfunc_93(int *arg0, S_3223d0 *arg1, char *arg2, DW4VC_364_0 *arg3) {
    int v = arg3->vX();
    int ok;
    H93 *h;
    int a;
    ok = arg1->Chk(v);
    if (ok != 0) {
        h = (H93 *)(arg2 - 4);
        if (((T93 *)(arg2 - 1))->flag == 1) {
            h = (H93 *)(arg2 - 12);
        }
        a = arg3->vX() >> 1;
        h->lo = a;
        if (h->flag == 1) {
            h->ext = a >> 5;
        }
        *arg0 = g_statusSucceeded.v;
    } else {
        *arg0 = g_allocatorFailureStatus.v;
    }
}

int Gap__Core__igMallocMemoryPool__vfunc_94(void *arg0, void **arg1) {
    int temp_v0;
    int var_v0;

    temp_v0 = ((DW4VC_364_0 *)(arg1))->vX();
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
    struct Hdr *h;

    if (arg1 == 0) {
        return -1;
    }
    h = (struct Hdr *)(arg1 - 4);
    if (((struct B8_3223d0 *)(arg1 - 1))->flag == 1) {
        h = (struct Hdr *)(arg1 - 12);
    }
    if (h == 0) {
        return -1;
    }
    if (h->flag == 0) {
        return h->lo * 2;
    }
    return (h->lo + (h->hi << 5)) * 2;
}

/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char Gap__Core__igMallocMemoryPool__vfunc_33(igMallocMemoryPool *self) {
    return self->_isActive;
}

static inline int usesAligned(TaggedPool *p) { return (p->flags & 0x20) != 0; }

static inline int usesSized(TaggedPool *p) { return (p->flags & 0x10) != 0; }

void *FUN_00324be0(TaggedPool *self, unsigned size) {
    unsigned overhead;
    unsigned total;
    void *block;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot = self->index >> 1;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total = overhead + size;
    if (usesAligned(self)) {
        block = (*(TaggedHeap * *)DAT_00587218)->AllocateAligned(total + 4);
    } else if (usesSized(self)) {
        block = (*(TaggedHeap * *)DAT_00587218)->AllocateSized(total + 4);
    } else {
        block = (*(TaggedHeap * *)DAT_00587218)->Allocate(total + 4);
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

static inline int f20(Pool_324ec0 *p) { return (p->flags & 0x20) != 0; }

static inline int f10(Pool_324ec0 *p) { return (p->flags & 0x10) != 0; }

void FUN_00324ec0(Pool_324ec0 *self, unsigned char *p) {
    H_324ec0 *h = (H_324ec0 *)(p - 4);
    unsigned size;
    if (((T_324ec0 *)(p - 1))->flag == 1) {
        h = (H_324ec0 *)(p - 12);
    }
    size = h->w.sz;
    if (h->b.big == 1) {
        size = size + (h->w.ext << 19);
    }
    size = (size + 3) & ~3;
    size = size + (h->b.words + 1) * 4;
    if (h->b.offset != 0) {
        int off = *(unsigned short *)((char *)h - 2);
        char *base = (char *)h - off;
        size = size + ((char *)h - base);
        if (f20(self)) {
            ((Heap * *)DAT_00587218)[0]->FreeAligned(base, size);
        } else if (f10(self)) {
            ((Heap * *)DAT_00587218)[0]->FreeSized(base, size);
        } else {
            ((Heap * *)DAT_00587218)[0]->Free(base);
        }
    } else {
        char *base = (char *)h - 4;
        if (f20(self)) {
            ((Heap * *)DAT_00587218)[0]->FreeAligned(base, size + 4);
        } else if (f10(self)) {
            ((Heap * *)DAT_00587218)[0]->FreeSized(base, size + 4);
        } else {
            ((Heap * *)DAT_00587218)[0]->Free(base);
        }
    }
}

void *FUN_00325060(TaggedPool *self, char *p, unsigned size) {
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
    slot = self->index >> 1;
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
            FUN_00324ec0((Pool_324ec0 *)self, (unsigned char *)p);
        }
        return moved;
    }
    if (usesAligned(self)) {
        block = (char *)(*(TaggedReallocHeap * *)DAT_00587218)->ReallocateAligned(base, newSize, total + 4);
    } else if (usesSized(self)) {
        block = (char *)(*(TaggedReallocHeap * *)DAT_00587218)->ReallocateSized(base, newSize, total + 4);
    } else {
        block = (char *)(*(TaggedReallocHeap * *)DAT_00587218)->Reallocate(base, newSize, total);
    }
    if (block == 0) {
        return 0;
    }
    if (newOverhead + 4 != oldOverhead + 4) {
        memmove(block + (newOverhead + 4), block + (oldOverhead + 4), kept < size ? kept : size);
    }
    fresh = (TaggedBlockHeader *)(block + 4);
    index = self->index >> 1;
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

static inline int usesAligned_3254a0(TaggedAlignedPool *p) { return (p->flags & 0x20) != 0; }

static inline int usesSized_3254a0(TaggedAlignedPool *p) { return (p->flags & 0x10) != 0; }

void *FUN_003254a0(TaggedAlignedPool *self, unsigned alignment, unsigned size) {
    unsigned overhead;
    unsigned total;
    char *block;
    char *p;
    TaggedBlockHeader *h;
    int id;
    unsigned end;
    unsigned aligned;
    unsigned slot;
    unsigned minimum = self->minAlignment;
    alignment = minimum < alignment ? alignment : minimum;
    if (alignment <= 3) {
        alignment = 4;
    }
    slot = self->index >> 1;
    total = size + alignment;
    if (size >= 0x80000 || slot >= 32) {
        overhead = 12;
    } else {
        overhead = 4;
    }
    total += overhead;
    if (usesAligned_3254a0(self)) {
        block = (char *)(*(TaggedHeap * *)DAT_00587218)->AllocateAligned(total);
    } else if (usesSized_3254a0(self)) {
        block = (char *)(*(TaggedHeap * *)DAT_00587218)->AllocateSized(total);
    } else {
        block = (char *)(*(TaggedHeap * *)DAT_00587218)->Allocate(total);
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

