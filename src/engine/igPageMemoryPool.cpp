#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
extern "C" {
int Gap__Core__igObject__vfunc_00(...);
int Gap__Core__igObject__vfunc_01(...);
int Gap__Core__igObject__vfunc_02(...);
int Gap__Core__igObject__vfunc_11(...);
void *igObject_GetAllocator(...);
int memset(...);
int strstr(...);
int FUN_002f0880(...);
void *FUN_002ba650(...);
int FUN_003081d0(...);
void FUN_002f8870(...);
void FUN_00326330(void *a0, int a1);
extern int g_igPageMemoryPool_defaultPoolOptionFlags[4];
extern int g_allocatorFailureStatus[4];
extern int g_statusSucceeded[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_004fd2f8[4];
extern int DAT_004fd300[4];
extern int DAT_004fd328[4];
extern int DAT_004fd340[4];
extern int DAT_004fd368[4];
extern int DAT_004fd3c8[4];
extern int DAT_004fd3d8[4];
extern int DAT_004fd3f0[4];
extern int DAT_004fd400[4];
extern int DAT_004ff230[4];
extern int DAT_004ff240[4];
extern int DAT_004ff2a0[4];
extern int DAT_004ff4b0[4];
extern unsigned char GPR_00554dc0;
extern unsigned char GPR_00554dc4;
extern unsigned char GPR_00554dd8;
extern void *DAT_00587218[4];

/* igPageMemoryPool slot 2: tail-call forwarder to the igObject slot-0 body, which is empty; the
 * pool adds no teardown of its own in this slot. */
void Gap__Core__igPageMemoryPool__vfunc_02(void) {
    Gap__Core__igObject__vfunc_00();
}

void thunk_Gap__Core__igObject__vfunc_01(void) {
    Gap__Core__igObject__vfunc_01();
}

class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int Free(int); };
struct Pool04 { char pad[144]; int slots[32]; };
void Gap__Core__igPageMemoryPool__vfunc_04(Pool04 *self) {
    Alloc *alloc = (Alloc *)igObject_GetAllocator(self);
    int i;
    for (i = 0; i < 32; i++) {
        if (self->slots[i] != 0) {
            alloc->Free(self->slots[i]);
            self->slots[i] = 0;
        }
    }
    Gap__Core__igObject__vfunc_02(self);
}

/* Initialise the pool: run the igObject base step (an empty stub), take the default
 * `_poolOptionFlags` from a global word (6 in the retail image) and clear the 128 bytes that
 * follow the reflected fields (+0x90). */
void Gap__Core__igPageMemoryPool__vfunc_13(igPageMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = g_igPageMemoryPool_defaultPoolOptionFlags[0];
    memset((char *)self + 0x90, 0, 0x80);
}

struct A1 { char p[136]; int f136; int f140; };
struct A2 { char p[48]; int f48; char p2[8]; int f60; char p3[12]; int f76; };
void Gap__Core__igPageMemoryPool__vfunc_45(int *arg0, struct A1 *arg1, struct A2 *arg2) {
    /* matching construct: variant search — decl order [7, 6, 5, 4, 3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s6;
    int var_s3;
    int var_a1;
    int temp_s5;
    int temp_s4;
    int temp_s3;
    int r;
    int sp8C;

    FUN_002f0880(&sp8C);
    r = sp8C;
    temp_s5 = arg2->f60;
    temp_s4 = arg2->f76;
    temp_s3 = arg2->f48;
    if (temp_s5 != 0) {
        var_s6 = 0;
        if (strstr(temp_s5, &DAT_004fd2f8[0]) != 0) {
            var_s6 |= 1;
        }
        if (strstr(temp_s5, &DAT_004fd300[0]) != 0) {
            var_s6 |= 2;
        }
        if (strstr(temp_s5, &DAT_004ff230[0]) != 0) {
            var_s6 |= 8;
        }
        if (strstr(temp_s5, &DAT_004fd328[0]) != 0) {
            var_s6 |= 4;
        }
        if (strstr(temp_s5, &DAT_004fd340[0]) != 0) {
            var_s6 |= 0x20;
        }
        var_a1 = var_s6;
        if (strstr(temp_s5, &DAT_004fd368[0]) != 0) {
            var_a1 = var_s6 | 0x10;
        }
        FUN_00326330(arg1, var_a1);
    }
    if ((temp_s3 != 0) && (strstr(temp_s3, &DAT_004ff230[0]) != 0)) {
        FUN_00326330(arg1, arg1->f140 | 8);
    }
    if (temp_s4 != 0) {
        var_s3 = arg1->f136;
        if (strstr(temp_s4, &DAT_004fd3c8[0]) != 0) {
            var_s3 = 0;
        } else if (strstr(temp_s4, &DAT_004fd3d8[0]) != 0) {
            var_s3 = 1;
        } else if (strstr(temp_s4, &DAT_004fd3f0[0]) != 0) {
            var_s3 = 2;
        } else if (strstr(temp_s4, &DAT_004fd400[0]) != 0) {
            var_s3 = 3;
        }
        arg1->f136 = var_s3;
    }
    *arg0 = r;
}

struct R30 { int v; };
class C30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual R30 vB(int); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void vA(); char pad4[108]; unsigned char f112; char pad113[27]; int f140; };
void Gap__Core__igPageMemoryPool__vfunc_30(C30 *arg0) {
    if (arg0->f112 == 0) {
        arg0->vA();
        arg0->f112 = 1;
        if (arg0->f140 & 4) {
            R30 r = arg0->vB(1);
        }
    }
}

class DW4VC_204_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(); };
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
void Gap__Core__igPageMemoryPool__vfunc_31(void **arg0) {
    void **alloc;
    int i;
    int *q;
    int v;
    ((DW4VC_204_0 *)(arg0))->vX();
    alloc = (void **)(igObject_GetAllocator(arg0));
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

class T {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void v29();
    virtual void e30();
    virtual void e31();
    virtual void e32();
    virtual void e33();
    virtual void e34();
    virtual void e35();
    virtual void e36();
    virtual void e37();
    virtual void e38();
    virtual void e39();
    virtual void e40();
    virtual void e41();
    virtual void e42();
    virtual void e43();
    virtual void e44();
    virtual void e45();
    virtual void e46();
    virtual void e47();
    virtual void e48();
    virtual void e49();
    virtual void e50();
    virtual void e51();
    virtual void e52();
    virtual void e53();
    virtual void e54();
    virtual void e55();
    virtual void e56();
    virtual void e57();
    virtual void e58();
    virtual void e59();
    virtual void e60();
    virtual void e61();
    virtual void e62();
    virtual void e63();
    virtual void e64();
    virtual void e65();
    virtual void e66();
    virtual void e67();
    virtual void e68();
    virtual void e69();
    virtual void e70();
    virtual void e71();
    virtual void e72();
    virtual void e73();
    virtual void e74();
    virtual void e75();
    virtual void e76();
    virtual void e77();
    virtual void e78();
    virtual void e79();
    virtual void e80();
    virtual void e81();
    virtual void e82();
    virtual void e83();
    virtual void e84();
    virtual void e85();
    virtual void v86();
    int pad4[5];
    int f24;
    char pad28[60];
    long long f88;
    char pad96[16];
    unsigned char f112;
    char pad113[19];
    int f132;
    int f136;
};
void Gap__Core__igPageMemoryPool__vfunc_32(T *t) {
    int r;
    if (t->f112 != 0) {
        if (t->f24 != 0) {
            if (t->f136 >= 3 && GPR_00554dc0 == 0) {
                r = FUN_003081d0(&DAT_004ff240[0], t->f132, t->f24);
                if (r != 1 && r == 2) {
                    GPR_00554dc0 = 1;
                }
            }
            t->v86();
        } else {
            if (t->f88 != 0) {
                if (t->f136 >= 3 && GPR_00554dc4 == 0) {
                    r = FUN_003081d0(&DAT_004ff2a0[0], t->f132, (int)t->f88);
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
    *statusOut = g_allocatorFailureStatus[0];
}

int Gap__Core__igPageMemoryPool__vfunc_25(igPageMemoryPool *self) {
    return 0;
}

int Gap__Core__igPageMemoryPool__vfunc_29(igPageMemoryPool *self) {
    return 1;
}

struct R4 { int v; R4() {} R4(int x) { v = x; } };
class Ob : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R4 a92(); virtual R4 a96(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual R4 a132(int); };

struct Pool34 { char pad[116]; igSmartPointer<Ob> f116; char p2[20]; int f140; };
R4 Gap__Core__igPageMemoryPool__vfunc_34(Pool34 *arg1, int arg2) {
    int a1;
    if (arg2 != 0) {
        a1 = arg1->f140 | 4;
    } else {
        a1 = arg1->f140 & ~4;
    }
    FUN_00326330(arg1, a1);
    if ((arg2 & 0xFF) == 0) {
        igSmartPointer<Ob> held(arg1->f116);
        arg1->f116.clear();
        if (held.p != 0) {
            held.p->a132(1);
            held.p->a96();
        }
    } else if ((arg2 & 0xFF) == 1) {
        if (arg1->f116.p != 0) {
            return DAT_004fb410[0];
        }
        igSmartPointer<Ob> created((Ob *)FUN_002ba650(igObject_GetAllocator(arg1)));
        created.p->a92();
        arg1->f116 = created;
    }
    return DAT_004fb410[0];
}

/* IgPageMemoryPool vtable slot 35: status leaf. On igMallocMemoryPool this slot sets _size; the
 * page pool has no such field. Ignores the pool and writes the engine's failure-status word (the
 * one an allocation failure publishes) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_35(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}

/* Slot 36 getter: returns the pool's _maxSize field (same field as slot 42). */
long long Gap__Core__igPageMemoryPool__vfunc_36(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* Set the pool's size limit (`_maxSize`, +120) and report success through the status word. */
void Gap__Core__igPageMemoryPool__vfunc_41(int *status, igPageMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}

/* Slot 42 getter: returns the pool's _maxSize field (same field as slot 36). */
long long Gap__Core__igPageMemoryPool__vfunc_42(igPageMemoryPool *self) {
    return self->_maxSize;
}

/* IgPageMemoryPool vtable slot 37: status leaf. On igMallocMemoryPool this slot sets _alignment;
 * the page pool has no such field. Ignores the pool and writes the engine's failure-status word
 * (the one an allocation failure publishes) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_37(int *statusOut) {
    *statusOut = g_allocatorFailureStatus[0];
}

/* igPageMemoryPool slot 38. igAliasMemoryPool fills the same slot with a getter for its
 * `_alignment`; the page pool reports a fixed 0x1000 (4 KiB, one page). */
#define PAGE_POOL_ALIGNMENT 0x1000
int Gap__Core__igPageMemoryPool__vfunc_38(igPageMemoryPool *self) {
    return PAGE_POOL_ALIGNMENT;
}

/* igPageMemoryPool vtable slot 39: status leaf. On igMallocMemoryPool this slot sets _elementSize;
 * the page pool accepts the call and stores nothing. Ignores the pool and writes the engine's
 * success-status word (zero in the pristine ELF) through the output-first argument. */
void Gap__Core__igPageMemoryPool__vfunc_39(int *statusOut) {
    *statusOut = g_statusSucceeded[0];
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

struct DW4SR4 { int w0; };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void FUN_00326090(void *arg0) {
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_132_1 *)(temp_a1))->vX((int)(1));
    }
}

class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
int FUN_003260d0(void *arg0, int arg1) {
    DW4SR4 sp2C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp2C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    }
    return arg1;
}

class igPageMemoryPoolView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *Allocate(unsigned int size);
    virtual void d53(); virtual void d54(); virtual void d55();
    virtual void *Reallocate(void *block, unsigned int size);
    virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void Free(void *block);
    virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72();
    virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80();
    virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88();
    virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96();
    virtual void d97(); virtual void d98(); virtual void d99();
    virtual void *MemoryOperation(void *block, int size, unsigned int alignment);
};

void *Gap__Core__igPageMemoryPool__vfunc_54(igPageMemoryPoolView *self, unsigned int size)
{
    return self->MemoryOperation(0, size, 0);
}

void *Gap__Core__igPageMemoryPool__vfunc_55(igPageMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->MemoryOperation(0, size, alignment);
}

class Pool56 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void *Alloc(int, int, int); };
struct PagePoolFlags { void *vt; char pad[136]; unsigned flags; };
static inline int flag2(PagePoolFlags *p) { return (p->flags & 1) != 0; }
static inline int flag4(PagePoolFlags *p) { return (p->flags & 2) != 0; }
void *Gap__Core__igPageMemoryPool__vfunc_56(Pool56 *self, int count, int size) {
    int total = count * size;
    void *p = self->Alloc(0, total, 0);
    if (p != 0) {
        if (total != 0) {
            if (flag2((PagePoolFlags *)self) || !flag4((PagePoolFlags *)self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual int a(int,int); };
struct P { char pad[140]; unsigned flags; };
int Gap__Core__igPageMemoryPool__vfunc_57(V *self, int n, int sz) {
    int total = n * sz;
    int r = self->a(0, total);
    if (r != 0) {
        if (total != 0) {
            unsigned f = ((P *)self)->flags;
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
    *arg0 = DAT_004fb418[0];
}

void Gap__Core__igPageMemoryPool__vfunc_63(int *arg0) {
    *arg0 = DAT_004fb418[0];
}

void Gap__Core__igPageMemoryPool__vfunc_64(void) {

}

void Gap__Core__igPageMemoryPool__vfunc_66(igPageMemoryPoolView *self, void *block)
{
    self->MemoryOperation(block, -1, 0);
}

class igPageMemoryPoolBlockView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100();
    virtual unsigned int vfunc_101(void *block);
    virtual void d102();
    virtual unsigned int GetBlockSize(void *block);
};

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

typedef struct Obj { int w0; unsigned refs; } Obj;
void Gap__Core__igPageMemoryPool__vfunc_90(int *arg0, Obj *arg1) {
    Obj *o;
    if (arg1 == 0 || (int *)igObject_GetAllocator(arg1) != arg0) {
        if (arg1 != 0) {
            arg1->refs++;
        }
        o = (Obj *)arg0[32];
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

class DW4VC_40_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual int vX(); };
class DW4VC_52_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual int vX(); };
class DW4VC_416_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual int vX(int, int, int); };
int FUN_00326920(void *arg0, int arg1) {
    int var_v0;

    if (*(int *)((char *)(arg0) + 140) & 8) {
        var_v0 = ((DW4VC_52_0 *)(DAT_00587218[0]))->vX();
    } else {
        var_v0 = ((DW4VC_40_0 *)(DAT_00587218[0]))->vX();
    }
    if (var_v0 != 0) {
        ((DW4VC_416_3 *)(((char *)(arg0) + 0)))->vX((int)(var_v0), (int)(arg1), (int)(1));
    }
    return var_v0;
}

class G { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void v44(); virtual void d10(); virtual void d11(); virtual void v56(); };
class O9d0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void vX(int, int, int); char pad[136]; unsigned flags; };
void FUN_003269d0(O9d0 *arg0, int arg1, int arg2) {
    int t = (arg0->flags & 8) != 0; /* The flag test is normalised to 0/1 first; a `bool t = flags & 8` idiom would drop the sltu. */
    if (t) {
        ((G *)DAT_00587218[0])->v56();
    } else {
        ((G *)DAT_00587218[0])->v44();
    }
    if (arg1 != 0) {
        arg0->vX(arg1, arg2, 0);
    }
}

class DW4VC_48_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual int vX(int, int, int); };
class DW4VC_60_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual int vX(int, int, int); };
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

class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual int vX(int); };
class B { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual int vX(int); };
class Cb80 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void vX(int, int, int); };
int FUN_00326b80(int *arg0, int arg1, int arg2) {
    int v;

    if (arg0[35] & 8) {
        v = ((A *)DAT_00587218[0])->vX(arg2);
    } else {
        v = ((B *)DAT_00587218[0])->vX(arg2);
    }
    if (v != 0) {
        ((Cb80 *)arg0)->vX(v, arg2, 1);
    }
    return v;
}

struct O { char pad[144]; unsigned int *tab[32]; };
int Gap__Core__igPageMemoryPool__vfunc_103(O *o, unsigned int arg1) {
    unsigned int *t;
    unsigned int v;
    t = o->tab[arg1 >> 27];
    if (t == 0) return 0;
    v = (arg1 & 0x7ffffff) >> 12;
    return ((1 << ((v & 0xF) * 2)) & t[v >> 4]) != 0;
}

class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual unsigned int *vX(int, int); };
void Gap__Core__igPageMemoryPool__vfunc_104(O *o, unsigned int a, int n, int set) {
    {
        unsigned int idx, bit;
        unsigned int *t;
        unsigned int pg;
        t = o->tab[a >> 27];
        pg = (a & 0x7ffffff) >> 12;
        idx = pg >> 4;
        bit = 1 << ((pg & 0xF) * 2);
        if (t == 0) { t = ((VC *)igObject_GetAllocator(o))->vX(0x800, 4); o->tab[a >> 27] = t; }
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
        if (t == 0) { t = ((VC *)igObject_GetAllocator(o))->vX(0x800, 4); *slot = t; }
        if (set != 0) t[idx] |= bit; else t[idx] &= ~bit;
    }
}

typedef struct PoolGBS { char p[136]; int debug; int p2; unsigned *slots[32]; } PoolGBS;
unsigned igPageMemoryPool_GetBlockSize(PoolGBS *self, unsigned addr) {
    unsigned slot = addr >> 27;
    unsigned *tbl = self->slots[slot];
    unsigned size = 4096;
    unsigned page;
    unsigned first;
    unsigned bit;
    unsigned end;
    unsigned word;
    unsigned mask;
    unsigned *w;
    unsigned v;
    if (tbl == 0) {
        return 0;
    }
    page = (addr & 0x7ffffff) >> 12;
    bit = page & 15;
    word = page >> 4;
    end = 2 << (bit * 2);
    w = tbl + word;
    v = *w;
    first = 1 << (bit * 2);
    if ((first & v) == 0) {
        return 0;
    }
    if ((v & 0xAAAAAAAA) != 0) {
        for (; end != 0; end <<= 2) {
            if (end & *(unsigned *)w) {
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
            tbl = self->slots[slot];
            if (tbl == 0) {
                return 0;
            }
            word = 0;
        }
        w = tbl + word;
        v = *w;
        if ((v & 0xAAAAAAAA) != 0) {
            for (mask = 2; mask != 0; mask <<= 2) {
                if (mask & *(unsigned *)w) {
                    return size;
                }
                size += 4096;
            }
            if (self->debug > 0) {
                FUN_002f8870(0, self);
                if (GPR_00554dd8 == 0) {
                    int r = FUN_003081d0(DAT_004ff4b0);
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
}
