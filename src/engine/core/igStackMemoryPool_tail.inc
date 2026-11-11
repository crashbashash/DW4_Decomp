/* Output-first status wrapper. The status word is returned through the hidden output pointer (a0).
 * The shared helper also reads a1 (the pool) and a2 (a request descriptor) from its asm, and this
 * wrapper passes both through untouched, which is why only the local cell is named at the call.
 * The helper leaves the success word (g_statusSucceeded) in the cell. */
void Gap__Core__igStackMemoryPool__vfunc_45(int *outStatus, int extra1, int extra2) {
    int status;

    FUN_002f0880(&status, (void **)extra1, (void *)extra2);
    *outStatus = status;
}

void Gap__Core__igStackMemoryPool__vfunc_30(S30 *p) {
    unsigned v = p->a;
    if (v != 0) {
        p->c = v;
        p->d = (int)((unsigned long long)p->c + p->len + 0xFFFFFFFFFFFFFFFCULL);
        p->d = p->d - (p->d & 3);
        p->flag = 1;
    }
}

void Gap__Core__igStackMemoryPool__vfunc_31(S31 *s) {
    s->f132 = s->f116;
    s->f136 = (int)(s->f132 + s->f120 + (long long)(unsigned __int128)(unsigned long long)-4LL);
    s->f136 = s->f136 - (s->f136 & 3);
}

void Gap__Core__igStackMemoryPool__vfunc_32(igStackMemoryPool *self) {
    ((StackPoolSlot124View *)self)->Reset();
    self->_isActive = 0;
}

/* Reports whether the pool is active: returns _isActive (+140), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char Gap__Core__igStackMemoryPool__vfunc_33(igStackMemoryPool *self) {
    return self->_isActive;
}

/* IgStackMemoryPool vtable slot 35: status leaf. Ignores the object and writes the engine's
 * current failure-status word (the one an allocation failure publishes) through the output-first
 * argument. */
void Gap__Core__igStackMemoryPool__vfunc_35(int *status_out) {
    *status_out = g_allocatorFailureStatus[0];
}

/* Slot 36 getter: returns the pool's _totalSize field (an int widened to 64 bits). */
long long Gap__Core__igStackMemoryPool__vfunc_36(igStackMemoryPool *self) {
    return self->_totalSize;
}

/* Set the pool's alignment (`_alignment`, +112) and report success through the status word.
 * vfunc_38 is the matching getter. */
void Gap__Core__igStackMemoryPool__vfunc_37(int *status, igStackMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *status = g_statusSucceeded[0];
}

/* IgStackMemoryPool slot 38, returns the reflected _alignment (+112, unsigned short). */
unsigned short Gap__Core__igStackMemoryPool__vfunc_38(igStackMemoryPool *self) {
    return self->_alignment;
}

/* Set the pool's element size (`_elementSize`, +128) and report success through the status word. */
void Gap__Core__igStackMemoryPool__vfunc_39(int *status, igStackMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_statusSucceeded[0];
}

/* Getter: the pool's _elementSize (+128, reflected as igUnsignedIntMetaField). */
int Gap__Core__igStackMemoryPool__vfunc_40(igStackMemoryPool *self) {
    return self->_elementSize;
}

void Gap__Core__igStackMemoryPool__vfunc_24(int *arg0, void *arg1, int arg2, long long arg3, char arg4) {
    if (*(unsigned char *)((char *)(arg1) + 140) == 0) {
        *(int *)((char *)(arg1) + 116) = arg2;
        *(long long *)((char *)(arg1) + 120) = arg3;
        *(char *)((char *)(arg1) + 141) = arg4;
        *arg0 = DAT_004fb410.v;
    } else {
        *arg0 = DAT_004fb418.v;
    }
}

/* Getter: the pool's _rawMemory reference (+116, reflected as igRawRefMetaField), the backing
 * block the stack pointer walks through. */
int Gap__Core__igStackMemoryPool__vfunc_26(igStackMemoryPool *self) {
    return self->_rawMemory;
}

/* IgStackMemoryPool vtable slot 42: getter for the reflected _totalSize (+120,
 * igUnsignedLongMetaField). Returned as a 64-bit value, like igArenaMemoryPool slot 42 for its
 * _maxSize. */
long long Gap__Core__igStackMemoryPool__vfunc_42(igStackMemoryPool *self) {
    return self->_totalSize;
}

long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}

long long Gap__Core__igStackMemoryPool__vfunc_47(struct P47 *arg0) {
    int cur;
    long long total = 0;
    struct E47 *e;
    int raw;
    if (arg0->active == 0) {
        return 0;
    }
    cur = arg0->top;
    e = arg0->e + 1;
    raw = arg0->raw;
    while (cur != raw) {
        unsigned t = e->sz;
        e++;
        total += t;
        cur -= t;
    }
    return total;
}

long long Gap__Core__igStackMemoryPool__vfunc_48(igStackMemoryPool *arg0) {
    return arg0->_totalSize - ((DW4VC_196_0_3275e0 *)(((char *)(arg0) + 0)))->vX();
}

long long Gap__Core__igStackMemoryPool__vfunc_49(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}

int Gap__Core__igStackMemoryPool__vfunc_53(struct S53 *arg0) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    int size;
    if (arg0->active == 0) { return 0; }
    size = arg0->size;
    if (size == 0) { return 0; }
    if (size == 0) { return 0; }
    align = arg0->align;
    mask = align - 1;
    pad = (align - (arg0->top & mask)) & mask;
    total = size + pad;
    if ((int)arg0->end - arg0->top < total) { return 0; }
    cur = arg0->top + pad;
    arg0->top += total;
    *arg0->end = total;
    arg0->end--;
    return cur;
}

int Gap__Core__igStackMemoryPool__vfunc_54(struct S54_3275e0 *arg0, int arg1) {
    int total, pad, mask;
    int cur;
    unsigned short align;
    if (arg1 == 0) {
        return 0;
    }
    align = arg0->align;
    mask = align - 1;
    cur = arg0->top;
    pad = mask & (align - (cur & mask));
    total = arg1 + pad;
    if ((int)arg0->end - cur < total) {
        return 0;
    }
    arg0->top = cur + total;
    *arg0->end = total;
    arg0->end--;
    return cur + pad;
}

int Gap__Core__igStackMemoryPool__vfunc_55(struct S54_3275e0 *arg0, int size, unsigned short arg2) {
    int total, pad, mask, ret;
    unsigned short align;
    unsigned short pool;
    if (size == 0) { size = 1; }
    pool = arg0->align;
    if (size == 0) { return 0; }
    arg2 = (arg2 > pool) ? arg2 : pool;
    align = arg2;
    mask = align - 1;
    pad = (align - (arg0->top & mask)) & mask;
    total = size + pad;
    if ((int)arg0->end - arg0->top < total) { return 0; }
    ret = arg0->top + pad;
    arg0->top += total;
    *arg0->end = total;
    arg0->end--;
    return ret;
}

void *Gap__Core__igStackMemoryPool__vfunc_56(struct S54_3275e0 *s, int count, int size) {
    int total = count * size;
    if (total == 0) { total = 1; }
    if (total == 0) {
        return 0;
    } else {
        void *p;
        int pad;
        int mask;
        int need;
        unsigned short align = s->align;
        mask = align - 1;
        pad = (align - (s->top & mask)) & mask;
        need = total + pad;
        if ((int)s->end - s->top < need) { return 0; }
        p = (void *)(s->top + pad);
        s->top += need;
        *s->end = need;
        s->end--;
        memset(p, 0, total);
        return p;
    }
}

void *Gap__Core__igStackMemoryPool__vfunc_57(struct S54_3275e0 *s, int count, int size, unsigned short a) {
    int total = count * size;
    unsigned short pool;
    if (total == 0) { total = 1; }
    pool = s->align;
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
        pad = (align - (s->top & mask)) & mask;
        need = total + pad;
        if ((int)s->end - s->top < need) { return 0; }
        p = (void *)(s->top + pad);
        s->top += need;
        *s->end = need;
        s->end--;
        memset(p, 0, total);
        return p;
    }
}

int Gap__Core__igStackMemoryPool__vfunc_58(void **arg0, int arg1, unsigned int arg2) {
    int var_v0;
    unsigned int temp_v0;
    unsigned int temp_v0_2;

    if (arg2 != 0) {
        var_v0 = ((DW4VC_216_1 *)(arg0))->vX((int)(arg2));
    } else {
        var_v0 = 0;
    }
    if (arg1 != 0) {
        if (var_v0 != 0) {
            temp_v0 = ((DW4VC_336_1 *)(arg0))->vX((int)(arg1));
            temp_v0_2 = (temp_v0 < arg2) ? temp_v0 : arg2;
            if (var_v0 != 0) {
                memcpy(var_v0, arg1, temp_v0_2);
            }
        }
        ((DW4VC_264_1 *)(arg0))->vX((int)(arg1));
    }
    return var_v0;
}

int Gap__Core__igStackMemoryPool__vfunc_59(void **arg0, int arg1, unsigned int arg2, int arg3) {
    int var_v0;
    unsigned int temp_v0;
    unsigned int temp_v0_2;

    if (arg2 != 0) {
        var_v0 = ((DW4VC_220_2 *)(arg0))->vX((int)(arg2), (int)(arg3));
    } else {
        var_v0 = 0;
    }
    if (arg1 != 0) {
        if (var_v0 != 0) {
            temp_v0 = ((DW4VC_336_1 *)(arg0))->vX((int)(arg1));
            temp_v0_2 = (temp_v0 < arg2) ? temp_v0 : arg2;
            if (var_v0 != 0) {
                memcpy(var_v0, arg1, temp_v0_2);
            }
        }
        ((DW4VC_264_1 *)(arg0))->vX((int)(arg1));
    }
    return var_v0;
}

static inline unsigned short effectiveAlign(StackPoolFields *pool, unsigned short wanted) {
    return wanted > pool->alignment ? wanted : pool->alignment;
}

void Gap__Core__igStackMemoryPool__vfunc_62(int *result, StackPoolFields *pool, int n, unsigned *sizes, unsigned *out) {
    /* matching construct: declaration-order sweep (random shuffles, then single moves) — the order of the locals sets their registers */
    unsigned pad;
    unsigned i;
    unsigned total = 0;
    unsigned mask;
    unsigned start;
    unsigned avail;
    unsigned start2;
    unsigned *end;
    unsigned size;
    unsigned low;
    unsigned count;
    unsigned j;
    unsigned scaled;
    unsigned l;
    unsigned pad2;
    unsigned size2;
    unsigned k;
    i = 0;
    count = (unsigned short)n;
    for (; i < count; i++) {
        total += sizes[i];
    }
    mask = pool->alignment - 1;
    total += (mask + 4) * count;
    low = pool->top;
    end = pool->end;
    avail = (unsigned)(end + 1) - low;
    if (total <= avail) {
        for (j = 0; j < count; j++) {
            start = pool->top;
            pad = mask & (pool->alignment - (start & mask));
            size = pad + sizes[j];
            out[j] = start + pad;
            pool->top += size;
            *end = size;
            end--;
        }
        pool->end = end;
        *result = DAT_004fb410.v;
        return;
    }
    if (total - mask * count <= avail) {
        for (k = 0; k < count; k++) {
            start2 = pool->top;
            pad2 = mask & (pool->alignment - (start2 & mask));
            scaled = k * 4;
            size2 = pad2 + *(unsigned *)((char *)sizes + scaled);
            if ((unsigned)end - low < size2) {
                break;
            }
            *(unsigned *)((char *)out + scaled) = start2 + pad2;
            low += size2;
            *end = size2;
            end--;
        }
        if (k == count) {
            pool->top = low;
            pool->end = end;
            *result = DAT_004fb410.v;
            return;
        }
    }
    for (l = 0; l < count; l++) {
        out[l] = 0;
    }
    *result = DAT_004fb418.v;
}

void Gap__Core__igStackMemoryPool__vfunc_63(int *result, StackPoolFields *pool, int n, unsigned *sizes, unsigned *out, unsigned short *aligns) {
    unsigned total = 0;
    unsigned padding = 0;
    unsigned size2;
    unsigned align;
    unsigned align2;
    unsigned mask2;
    unsigned i;
    unsigned l;
    unsigned *end;
    unsigned low;
    unsigned pad;
    unsigned count;
    unsigned mask;
    unsigned start;
    unsigned start2;
    unsigned size;
    unsigned avail;
    unsigned pad2;
    unsigned scaled;
    unsigned k;
    unsigned j;
    i = 0;
    count = (unsigned short)n;
    for (; i < count; i++) {
        total += sizes[i];
        padding += effectiveAlign(pool, aligns[i]);
    }
    padding -= n & 0xffff;
    total += padding + count * 4;
    low = pool->top;
    end = pool->end;
    avail = (unsigned)(end + 1) - low;
    if (total <= avail) {
        for (j = 0; j < count; j++) {
            align = effectiveAlign(pool, aligns[j]);
            start = pool->top;
            mask = align - 1;
            mask &= align - (start & mask);
            pad = mask;
            size = pad + sizes[j];
            out[j] = start + pad;
            pool->top += size;
            *end = size;
            end--;
        }
        pool->end = end;
        *result = DAT_004fb410.v;
        return;
    }
    if (total - padding <= avail) {
        for (k = 0; k < count; k++) {
            align2 = effectiveAlign(pool, aligns[k]);
            start2 = pool->top;
            mask2 = align2 - 1;
            mask2 &= align2 - (start2 & mask2);
            pad2 = mask2;
            scaled = k * 4;
            size2 = pad2 + *(unsigned *)((char *)sizes + scaled);
            if ((unsigned)end - low < size2) {
                break;
            }
            *(unsigned *)((char *)out + scaled) = start2 + pad2;
            low += size2;
            *end = size2;
            end--;
        }
        if (k == count) {
            pool->top = low;
            pool->end = end;
            *result = DAT_004fb410.v;
            return;
        }
    }
    for (l = 0; l < count; l++) {
        out[l] = 0;
    }
    *result = DAT_004fb418.v;
}

int Gap__Core__igStackMemoryPool__vfunc_84(DW4VC_340_0 *arg0, unsigned int arg1) {
    E84 *a1;
    unsigned int a0;
    unsigned int v1;
    if (arg0->vX() == 0) {
        return 0;
    }
    a1 = arg0->f136 + 1;
    v1 = a1->len;
    a0 = arg0->f132 - v1;
    while (a0 > arg1) {
        a1 += 1;
        v1 = a1->len;
        a0 -= v1;
    }
    return v1 - (arg1 - a0);
}

bool Gap__Core__igStackMemoryPool__vfunc_85(S85 *s, unsigned a) {
    bool r = false;
    if (a >= s->start) {
        if ((unsigned long long)a < (unsigned long long)s->start + s->len) r = true;
    }
    return r;
}

void Gap__Core__igStackMemoryPool__vfunc_64(Stack64 *self, unsigned count, unsigned *ptrs) {
    unsigned last;
    unsigned *end;
    unsigned top;
    unsigned avail;
    unsigned *e;
    unsigned i;
    end = self->end;
    last = ptrs[count - 1];
    top = self->top;
    avail = top - end[1];
    e = end + 1;
    if (!(avail > last)) {
        self->top = avail;
        for (i = 0; i < count - 1; i++) {
            e++;
            self->top = self->top - (*e & 0x7fffffff);
        }
        while (self->top != self->base && (*e & 0x80000000)) {
            self->top = self->top - (*e & 0x7fffffff);
            e++;
        }
        self->end = e - 1;
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

void Gap__Core__igStackMemoryPool__vfunc_66(Stack66 *self, unsigned size) {
    unsigned *e;
    unsigned avail;
    unsigned top;
    unsigned v;
    if (size != 0 && self->Owns() != 0) {
        e = self->end + 1;
        top = self->top;
        v = *e;
        avail = top - v;
        if (!(avail > size)) {
            e++;
            self->top = top - (v & 0x7fffffff);
            while (self->top != self->base && (*e & 0x80000000)) {
                self->top = self->top - (*e & 0x7fffffff);
                e++;
            }
            self->end = e - 1;
            return;
        }
        e++;
        avail = avail - (*e & 0x7fffffff);
        while (avail > size) {
            e++;
            avail = avail - (*e & 0x7fffffff);
        }
        *e = *e | 0x80000000;
    }
}

int Gap__Core__igStackMemoryPool__vfunc_89(void *arg0) {
    return *(int *)((char *)(arg0) + 148);
}

void Gap__Core__igStackMemoryPool__vfunc_90(S0_3275e0 *arg0, S1_3275e0 *arg1) {
    S1_3275e0 *temp_a0;
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

void Gap__Core__igStackMemoryPool__vfunc_86(int *a, int a1, int a2, int a3, int a4) {
    FUN_002ed610((unsigned int)a1, (unsigned int)a2, (unsigned int)a3, (unsigned int)a[29], (long long)((unsigned int)(a[33] - a[29])), (const char *)a4);
}

int Gap__Core__igStackMemoryPool__vfunc_91(void *arg0) {
    return *(int *)((char *)(arg0) + 144);
}

void Gap__Core__igStackMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 144) = arg1;
}

