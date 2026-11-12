void *FUN_003257d0(igPageMemoryPool *arg0) {
    igMemoryPool_Initialize((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

void *FUN_00325810(igPageMemoryPool *arg0, int extra1) {
    igMemoryPool_CopyConstruct((int **)arg0);
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_005311f0[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

/* igPageMemoryPool slot 2: tail-call forwarder to the igObject slot-0 body, which is empty; the
 * pool adds no teardown of its own in this slot. */
void Gap__Core__igPageMemoryPool__vfunc_02(int extra0) {
    Gap__Core__igObject__vfunc_00(extra0);
}

void thunk_Gap__Core__igObject__vfunc_01(int extra0, int extra1) {
    Gap__Core__igObject__vfunc_01(extra0, extra1);
}

void Gap__Core__igPageMemoryPool__vfunc_04(Pool04 *self) {
    Alloc_325850 *alloc = (Alloc_325850 *)((void *)igObject_GetAllocator((int)self));
    int i;
    for (i = 0; i < 32; i++) {
        if (self->slots[i] != 0) {
            alloc->Free(self->slots[i]);
            self->slots[i] = 0;
        }
    }
    Gap__Core__igObject__vfunc_02((int)self);
}

/* Initialise the pool: run the igObject base step (an empty stub), take the default
 * `_poolOptionFlags` from a global word (6 in the retail image) and clear the 128 bytes that
 * follow the reflected fields (+0x90). */
void Gap__Core__igPageMemoryPool__vfunc_13(igPageMemoryPool *self, int extra1) {
    Gap__Core__igObject__vfunc_11((int)self, extra1);
    self->_poolOptionFlags = g_igPageMemoryPool_defaultPoolOptionFlags[0];
    memset((char *)self + 0x90, 0, 0x80);
}

void Gap__Core__igPageMemoryPool__vfunc_45(int *arg0, struct A1_325850 *arg1, struct A2_325850 *arg2) {
    /* matching construct: variant search — decl order [7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s6;
    int var_s3;
    int var_a1;
    int temp_s5;
    int temp_s4;
    int temp_s3;
    int r;
    int sp8C;

    FUN_002f0880(&sp8C, (void **)arg1, (void *)arg2);
    r = sp8C;
    temp_s5 = arg2->f60;
    temp_s4 = arg2->f76;
    temp_s3 = arg2->f48;
    if (temp_s5 != 0) {
        var_s6 = 0;
        if (((int)strstr(temp_s5, &DAT_004fd2f8[0])) != 0) {
            var_s6 |= 1;
        }
        if (((int)strstr(temp_s5, &DAT_004fd300[0])) != 0) {
            var_s6 |= 2;
        }
        if (((int)strstr(temp_s5, &DAT_004ff230[0])) != 0) {
            var_s6 |= 8;
        }
        if (((int)strstr(temp_s5, &DAT_004fd328[0])) != 0) {
            var_s6 |= 4;
        }
        if (((int)strstr(temp_s5, &DAT_004fd340[0])) != 0) {
            var_s6 |= 0x20;
        }
        var_a1 = var_s6;
        if (((int)strstr(temp_s5, &DAT_004fd368[0])) != 0) {
            var_a1 = var_s6 | 0x10;
        }
        FUN_00326330(arg1, var_a1);
    }
    if ((temp_s3 != 0) && (((int)strstr(temp_s3, &DAT_004ff230[0])) != 0)) {
        FUN_00326330(arg1, arg1->f140 | 8);
    }
    if (temp_s4 != 0) {
        var_s3 = arg1->f136;
        if (((int)strstr(temp_s4, &DAT_004fd3c8[0])) != 0) {
            var_s3 = 0;
        } else if (((int)strstr(temp_s4, &DAT_004fd3d8[0])) != 0) {
            var_s3 = 1;
        } else if (((int)strstr(temp_s4, &DAT_004fd3f0[0])) != 0) {
            var_s3 = 2;
        } else if (((int)strstr(temp_s4, &DAT_004fd400[0])) != 0) {
            var_s3 = 3;
        }
        arg1->f136 = var_s3;
    }
    *arg0 = r;
}

void Gap__Core__igPageMemoryPool__vfunc_30(C30_325850 *arg0) {
    if (arg0->f112 == 0) {
        arg0->vA();
        arg0->f112 = 1;
        if (arg0->f140 & 4) {
            R30 r = arg0->vB(1);
        }
    }
}

void Gap__Core__igPageMemoryPool__vfunc_31(void **arg0) {
    void **alloc;
    int i;
    int *q;
    int v;
    ((DW4VC_204_0 *)(arg0))->vX();
    alloc = (void **)(((void *)igObject_GetAllocator((int)arg0)));
    i = 0;
    do {
        q = (int *)((char *)arg0 + i * 4 + 144);
        v = *q;
        if (v != 0) {
            ((DW4VC_264_1 *)(alloc))->vX(v);
            *q = 0;
        }
        i++;
    } while (i < 0x20);
}

void Gap__Core__igPageMemoryPool__vfunc_32(T_325850 *t) {
    int r;
    if (t->f112 != 0) {
        if (t->f24 != 0) {
            if (t->f136 >= 3 && GPR_00554dc0 == 0) {
                r = FUN_003081d0(DAT_004ff240, t->f132, t->f24);
                if (r != 1 && r == 2) {
                    GPR_00554dc0 = 1;
                }
            }
            t->v86();
        } else {
            if (t->f88 != 0) {
                if (t->f136 >= 3 && GPR_00554dc4 == 0) {
                    r = FUN_003081d0(DAT_004ff2a0, t->f132, (int)t->f88);
                    if (r != 1 && r == 2) {
                        GPR_00554dc4 = 1;
                    }
                }
                t->v86();
            }
        }
        t->f112 = 0;
        t->v29();
    }
}

/* Reports whether the pool is active: returns _isActive (+112), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char Gap__Core__igPageMemoryPool__vfunc_33(igPageMemoryPool *self) {
    return self->_isActive;
}

int Gap__Core__igPageMemoryPool__vfunc_26(igPageMemoryPool *self) {
    return 0;
}

/* IgPageMemoryPool vtable slot 24: status leaf. Same leaf as igMallocMemoryPool slot 24. Ignores
 * the pool and writes the engine's failure-status word (the one an allocation failure publishes)
 * through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_24(int *statusOut) {
    *statusOut = g_allocatorFailureStatus.v;
}

int Gap__Core__igPageMemoryPool__vfunc_25(igPageMemoryPool *self) {
    return 0;
}

int Gap__Core__igPageMemoryPool__vfunc_29(igPageMemoryPool *self) {
    return 1;
}

R4_325850 Gap__Core__igPageMemoryPool__vfunc_34(Pool34_325850 *arg1, int arg2) {
    int a1;
    if (arg2 != 0) {
        a1 = arg1->f140 | 4;
    } else {
        a1 = arg1->f140 & ~4;
    }
    FUN_00326330(arg1, a1);
    if ((arg2 & 0xFF) == 0) {
        igSmartPointer<Ob_325850> held(arg1->f116);
        arg1->f116.clear();
        if (held.p != 0) {
            held.p->a132(1);
            held.p->a96();
        }
    } else if ((arg2 & 0xFF) == 1) {
        if (arg1->f116.p != 0) {
            return g_statusSucceeded.v;
        }
        igSmartPointer<Ob_325850> created((Ob_325850 *)FUN_002ba650((int)(((void *)igObject_GetAllocator((int)arg1)))));
        created.p->a92();
        arg1->f116 = created;
    }
    return g_statusSucceeded.v;
}

/* IgPageMemoryPool vtable slot 35: status leaf. On igMallocMemoryPool this slot sets _size; the
 * page pool has no such field. Ignores the pool and writes the engine's failure-status word (the
 * one an allocation failure publishes) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_allocatorFailureStatus.v;
}

/* Slot 36 getter: returns the pool's _maxSize field (same field as slot 42). */
long long Gap__Core__igPageMemoryPool__vfunc_36(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's size limit (`_maxSize`, +120) and report success through the status word. */
void Gap__Core__igPageMemoryPool__vfunc_41(int *status, igPageMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded.v;
}

/* Slot 42 getter: returns the pool's _maxSize field (same field as slot 36). */
long long Gap__Core__igPageMemoryPool__vfunc_42(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* IgPageMemoryPool vtable slot 37: status leaf. On igMallocMemoryPool this slot sets _alignment;
 * the page pool has no such field. Ignores the pool and writes the engine's failure-status word
 * (the one an allocation failure publishes) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_37(int *statusOut) {
    *statusOut = g_allocatorFailureStatus.v;
}

/* igPageMemoryPool slot 38. igAliasMemoryPool fills the same slot with a getter for its
 * `_alignment`; the page pool reports a fixed 0x1000 (4 KiB, one page). */

int Gap__Core__igPageMemoryPool__vfunc_38(igPageMemoryPool *self) {
    return PAGE_POOL_ALIGNMENT;
}

/* igPageMemoryPool vtable slot 39: status leaf. On igMallocMemoryPool this slot sets _elementSize;
 * the page pool accepts the call and stores nothing. Ignores the pool and writes the engine's
 * success-status word (zero in the pristine ELF) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_39(int *statusOut) {
    *statusOut = g_statusSucceeded.v;
}

/* igPageMemoryPool slot 40. igAliasMemoryPool fills the same slot with a getter for its
 * `_elementSize`; the page pool has no fixed element size and returns zero. */
int Gap__Core__igPageMemoryPool__vfunc_40(igPageMemoryPool *self) {
    return 0;
}

long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

/* Slot 47 getter: returns the pool's _localNetAllocated field (bytes currently allocated from this
 * pool). */
long long Gap__Core__igPageMemoryPool__vfunc_47(igPageMemoryPool *self) {
    return self->_localNetAllocated;
}

/* Slot 48 getter: returns the pool's _localNetAllocatedWithOverhead field (bytes currently
 * allocated from this pool, overhead included). */
long long Gap__Core__igPageMemoryPool__vfunc_48(igPageMemoryPool *self) {
    return self->_localNetAllocatedWithOverhead;
}

long long Gap__Core__igPageMemoryPool__vfunc_99(void *arg0) {
    return *(long long *)((char *)arg0 + 32);
}

long long Gap__Core__igPageMemoryPool__vfunc_100(void *arg0) {
    return *(long long *)((char *)arg0 + 64);
}

long long Gap__Core__igPageMemoryPool__vfunc_101(void *arg0) {
    return *(long long *)((char *)arg0 + 56);
}

long long Gap__Core__igPageMemoryPool__vfunc_49(igPageMemoryPool *arg0) {
    return arg0->_maxSize - arg0->_localNetAllocatedWithOverhead;
}

int Gap__Core__igPageMemoryPool__vfunc_53(igPageMemoryPool *self) {
    return 0;
}

void FUN_00326090(void *arg0) {
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_132_1_325850 *)(temp_a1))->vX((int)(1));
    }
}

int FUN_003260d0(void *arg0, int arg1) {
    DW4SR4 sp2C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp2C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    }
    return arg1;
}

void *Gap__Core__igPageMemoryPool__vfunc_54(igPageMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, 0);
}

void *Gap__Core__igPageMemoryPool__vfunc_55(igPageMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

static inline int flag2_325850(PagePoolFlags *p) { return (p->flags & 1) != 0; }

static inline int flag4_325850(PagePoolFlags *p) { return (p->flags & 2) != 0; }

void *Gap__Core__igPageMemoryPool__vfunc_56(Pool56_325850 *self, int count, int size) {
    int total = count * size;
    void *p = self->Alloc_325850(0, total, 0);
    if (p != 0) {
        if (total != 0) {
            if (flag2_325850((PagePoolFlags *)self) || !flag4_325850((PagePoolFlags *)self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

int Gap__Core__igPageMemoryPool__vfunc_57(V_325850 *self, int n, int sz) {
    int total = n * sz;
    int r = self->a(0, total);
    if (r != 0) {
        if (total != 0) {
            unsigned f = ((P_325850 *)self)->flags;
            if (((f & 1) ? 1 : 0) || !((f & 2) ? 1 : 0)) {
                memset(r, 0, total);
            }
        }
    }
    return r;
}

void *Gap__Core__igPageMemoryPool__vfunc_58(igPageMemoryPoolView *self, void *block, unsigned int size)
{
    return self->MemoryOperation(block, size, 0);
}

void *Gap__Core__igPageMemoryPool__vfunc_59(igPageMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->MemoryOperation(block, size, alignment);
}

void Gap__Core__igPageMemoryPool__vfunc_62(int *arg0) {
    *arg0 = g_allocatorFailureStatus.v;
}

void Gap__Core__igPageMemoryPool__vfunc_63(int *arg0) {
    *arg0 = g_allocatorFailureStatus.v;
}

void Gap__Core__igPageMemoryPool__vfunc_64(void) {

}

void Gap__Core__igPageMemoryPool__vfunc_66(igPageMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, 0);
}

unsigned int Gap__Core__igPageMemoryPool__vfunc_85(igPageMemoryPoolBlockView *self, void *block)
{
    return self->vfunc_101(block);
}

int Gap__Core__igPageMemoryPool__vfunc_83(void) {
    return 1;
}

unsigned int Gap__Core__igPageMemoryPool__vfunc_84(igPageMemoryPoolBlockView *self, void *block)
{
    return self->GetBlockSize(block);
}

void FUN_00326330(void *a0, int a1)
{
    *(int *)((char *)a0 + 140) = a1;
}

int Gap__Core__igPageMemoryPool__vfunc_89(void *arg0) {
    return *(int *)((char *)(arg0) + 128);
}

void Gap__Core__igPageMemoryPool__vfunc_90(int *arg0, Obj_325850 *arg1) {
    Obj_325850 *o;
    if (arg1 == 0 || (int *)((void *)igObject_GetAllocator((int)arg1)) != arg0) {
        if (arg1 != 0) {
            arg1->refs++;
        }
        o = (Obj_325850 *)arg0[32];
        if (o != 0) {
            --o->refs;
            if ((o->refs & 0x7fffff) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0[32] = (int)arg1;
    }
}

void Gap__Core__igPageMemoryPool__vfunc_86(void) {

}

int Gap__Core__igPageMemoryPool__vfunc_91(void *arg0) {
    return *(int *)((char *)(arg0) + 132);
}

void Gap__Core__igPageMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 132) = arg1;
}

int FUN_00326920(void *arg0, int arg1) {
    int var_v0;

    if (*(int *)((char *)(arg0) + 140) & 8) {
        var_v0 = ((DW4VC_52_0 *)(((void * *)DAT_00587218)[0]))->vX();
    } else {
        var_v0 = ((DW4VC_40_0 *)(((void * *)DAT_00587218)[0]))->vX();
    }
    if (var_v0 != 0) {
        ((DW4VC_416_3 *)(((char *)(arg0) + 0)))->vX((int)(var_v0), (int)(arg1), (int)(1));
    }
    return var_v0;
}

void FUN_003269d0(O9d0 *arg0, int arg1, int arg2) {
    int t = (arg0->flags & 8) != 0; /* The flag test is normalised to 0/1 first; a `bool t = flags & 8` idiom would drop the sltu. */
    if (t) {
        ((G_325850 *)((void * *)DAT_00587218)[0])->v56();
    } else {
        ((G_325850 *)((void * *)DAT_00587218)[0])->v44();
    }
    if (arg1 != 0) {
        arg0->vX(arg1, arg2, 0);
    }
}

int FUN_00326a80(void *arg0, int arg1, int arg2, int arg3) {
    int r;
    if ((arg1 != 0) && (arg2 == arg3)) {
        return arg1;
    }
    if (arg1 != 0) {
        ((DW4VC_416_3 *)arg0)->vX(arg1, arg3, 0);
    }
    if (*(int *)((char *)(arg0) + 140) & 8) {
        r = (*(DW4VC_60_3 **)0x00587218)->vX(arg1, arg2, arg3);
    } else {
        r = (*(DW4VC_48_3 **)0x00587218)->vX(arg1, arg2, arg3);
    }
    if (r != 0) {
        ((DW4VC_416_3 *)arg0)->vX(r, arg2, 1);
    }
    return r;
}

int FUN_00326b80(int *arg0, int arg1, int arg2) {
    int v;

    if (arg0[35] & 8) {
        v = ((A_325850 *)((void * *)DAT_00587218)[0])->vX(arg2);
    } else {
        v = ((B_325850 *)((void * *)DAT_00587218)[0])->vX(arg2);
    }
    if (v != 0) {
        ((Cb80 *)arg0)->vX(v, arg2, 1);
    }
    return v;
}

int Gap__Core__igPageMemoryPool__vfunc_103(O_325850 *o, unsigned int arg1) {
    unsigned int *t;
    unsigned int v;
    t = o->tab[arg1 >> 27];
    if (t == 0) return 0;
    v = (arg1 & 0x7ffffff) >> 12;
    return ((1 << ((v & 0xF) * 2)) & t[v >> 4]) != 0;
}

void Gap__Core__igPageMemoryPool__vfunc_104(O_325850 *o, unsigned int a, int n, int set) {
    {
        unsigned int idx, bit;
        unsigned int *t;
        unsigned int pg;
        t = o->tab[a >> 27];
        pg = (a & 0x7ffffff) >> 12;
        idx = pg >> 4;
        bit = 1 << ((pg & 0xF) * 2);
        if (t == 0) { t = ((VC_325850 *)((void *)igObject_GetAllocator((int)o)))->vX(0x800, 4); o->tab[a >> 27] = t; }
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
        slot = (unsigned int **)((char *)o + 144) + (a >> 27);
        t = *slot;
        pg = (a & 0x7ffffff) >> 12;
        idx = pg >> 4;
        bit = 2 << ((pg & 0xF) * 2);
        if (t == 0) { t = ((VC_325850 *)((void *)igObject_GetAllocator((int)o)))->vX(0x800, 4); *slot = t; }
        if (set != 0) t[idx] |= bit; else t[idx] &= ~bit;
    }
}

void Gap__Core__igPageMemoryPool__vfunc_87(int extra0, int extra1) {
    FUN_002f08d0((igMemoryPool *)extra0, (char *)extra1);
}

void Gap__Core__igPageMemoryPool__vfunc_96(void) {
    FUN_002f0750();
}

