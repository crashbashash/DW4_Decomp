#include "dw4/reflected.h"

/* Status word: the comparison form keeps the copy as one word. */
struct igResult {
    int w0;
    igResult() {}
    igResult(const igResult &o) { w0 = o.w0; }
    igResult &operator=(const igResult &o) { w0 = o.w0; return *this; }
    bool operator==(const igResult &o) const { return w0 == o.w0; }
    bool operator!=(const igResult &o) const { return w0 != o.w0; }
};
struct DW4SR4 { int w0; };
struct RefObject { int word0; int references; };
struct TagByte { unsigned char lo:7; unsigned char flag:1; };
class SetFlagsPool;

extern "C" {
int FUN_002f8870(...);
int FUN_003081d0(...);
int FUN_00308320(...);
int memset(...);
void *memcpy(void *, void *, int);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int FUN_00318b40(...);
void FUN_00314510(void *, int, int);
void igArenaMemoryPool_SetPoolOptionFlags(SetFlagsPool *, int);
extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
extern int DAT_004fd640[4];
extern int DAT_00587200[4];
extern int DAT_00531030[4];
}

/* System allocator singleton: slot 2 allocates, slot 4 allocates aligned, slot 7 frees. */
class SystemAllocator { public:
    virtual void d0();
    virtual void d1();
    virtual void *Alloc(int);
    virtual void d3();
    virtual void *AllocAligned(int, int);
    virtual void d5();
    virtual void d6();
    virtual int Free(int);
};
extern SystemAllocator *DAT_00587218[4];

extern "C" {
extern char DAT_004fc400[];
extern char DAT_004fc440[];
extern unsigned char GPR_00554cec;
extern unsigned char GPR_00554cf0;
}
struct CheckHeapArena { char pad[2020]; int *blocks; int capacity; int count; };
struct CheckHeapPool { char pad[112]; CheckHeapArena *arena; char pad2[72]; int verbosity; };
class HeapBoundsPool;
extern "C" igResult FUN_00312790(HeapBoundsPool *self, int index, char *cur, char *end);
extern "C" igResult igArenaMemoryPool_CheckHeap(CheckHeapPool *self) {
    CheckHeapArena *arena = self->arena;
    igResult ok = DAT_004fb410;
    igResult result;
    int i;
    int r;

    result.w0 = DAT_004fb410.w0;
    if (arena->count == 0) {
        return ok;
    }
    if (arena->blocks == 0 || arena->capacity == 0) {
        if (self->verbosity > 0) {
            FUN_002f8870(0, self);
            if (GPR_00554cec == 0) {
                r = FUN_003081d0(DAT_004fc400);
                if (r == 1) {
                } else if (r == 2) {
                    GPR_00554cec = 1;
                }
            }
        }
        result = DAT_004fb418;
    }
    if (arena->count < 0 || arena->capacity < 0 || arena->count > arena->capacity) {
        if (self->verbosity >= 3 && GPR_00554cf0 == 0) {
            r = FUN_003081d0(DAT_004fc440);
            if (r == 1) {
            } else if (r == 2) {
                GPR_00554cf0 = 1;
            }
        }
        return DAT_004fb418;
    }
    for (i = 0; i < arena->count; i += 2) {
        int *p = &arena->blocks[i];
        if (FUN_00312790((HeapBoundsPool *)self, i, (char *)p[0], (char *)p[1]) == DAT_004fb418) {
            result = DAT_004fb418;
            break;
        }
    }
    return result;
}

extern "C" {
extern char DAT_004fc490[];
extern char DAT_004fc500[];
extern char DAT_004fc570[];
extern char DAT_004fc5e0[];
extern char DAT_004fc660[];
extern unsigned char GPR_00554cf4;
extern unsigned char GPR_00554cf8;
extern unsigned char GPR_00554cfc;
extern unsigned char GPR_00554d00;
extern unsigned char GPR_00554d04;
}
/* Arena block header: in-use bit, alignment padding in words, size (low 19 bits, high 12 bits in
 * the third word when `big` is set). */
struct ArenaBlockHeader {
    unsigned used : 1;
    unsigned padWords : 4;
    unsigned size : 19;
    unsigned mid : 7;
    unsigned big : 1;
    unsigned w1;
    unsigned sizeHigh : 12;
    unsigned rest : 20;
};
class HeapBoundsPool { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
    virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
    virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
    virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89();
    virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99();
    virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106();
    virtual char *HeapStart();
    virtual char *HeapEnd();
    char pad4[184]; int messageLevel; char pad192[8]; int minBlockSize;
};
extern "C" igResult FUN_00312790(HeapBoundsPool *self, int index, char *cur, char *end);

extern "C" {

extern unsigned char GPR_00554d1c;
extern int DAT_004fcbc0[4];
}
struct TrimArena { char p0[1992]; int top; char p1[24]; int *blocks; int capacity; int count; };
struct TrimPool { char p0[112]; TrimArena *arena; char p1[44]; long long locked; char p2[20]; int debug; };
extern "C" igResult igArenaMemoryPool_TrimArenaBlock(TrimPool *, int, int, int);
extern "C" bool igArenaMemoryPool_Trim(TrimPool *self, int pad);

extern "C" {
/* The link pair sits at +4 or +12 depending on the top bit of the node's byte 3; `b7 == 0 ? 4 :
 * 12` gives the movn form. */
struct LinkByte { char pad[3]; unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; };
#define OFF(p) (((struct LinkByte *)(p))->b7 == 0 ? 4 : 12)
#define NEXT(p) (*(int *)((char *)(p) + OFF(p) + 4))
#define PREV(p) (*(int *)((char *)(p) + OFF(p)))
void FUN_00315050(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3);

}
extern "C" {
struct PoolRequest { char pad0[60]; char *options; char pad64[4]; char *integrityCheck; char pad72[4]; char *messages; };
struct CoreGlobals { char pad0[48]; igArenaMemoryPool *defaultPool; };
char *strstr(const char *, const char *);
void FUN_002f0880(int *status);
extern struct CoreGlobals *DAT_00586dc8[4];
extern char DAT_004fd2f8[];
extern char DAT_004fd300[];
extern char DAT_004fd308[];
extern char DAT_004fd318[];
extern char DAT_004fd328[];
extern char DAT_004fd340[];
extern char DAT_004fd358[];
extern char DAT_004fd368[];
extern char DAT_004fd378[];
extern char DAT_004fd388[];
extern char DAT_004fd3a0[];
extern char DAT_004fd3b8[];
extern char DAT_004fd3c8[];
extern char DAT_004fd3d8[];
extern char DAT_004fd3f0[];
extern char DAT_004fd400[];
void Gap__Core__igArenaMemoryPool__vfunc_45(int *out, igArenaMemoryPool *pool, struct PoolRequest *request);

}
class Pool30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual DW4SR4 v136(int); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v204(); virtual void d50(); virtual void d51(); virtual int v216(int); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void v264(int); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
 char p4[112]; unsigned char f116; char p5[19]; long long f136; char p6[24]; int f168; char p7[20]; int f192; int f196; };
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_30(Pool30 *arg0);
void Gap__Core__igArenaMemoryPool__vfunc_30(Pool30 *arg0);
}

/* Pool teardown/reset step. A pool that has a size (_size at +160) calls the virtual at vtable
 * byte offset 204, clears _systemAllocated and zeroes the 0x814-byte arena state block if one is
 * attached; a pool with no size instead calls the virtual at vtable byte offset 108 with 1. The
 * two vtable calls are spelled through the dummy classes below (one per distinct vtable offset; dN
 * are placeholder virtuals that only position vX). */
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self);
}
class DW4VC_108_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int); };
class DW4VC_204_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(); };
void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self);

extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0);
}
class Pool32 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); char pad[116-4]; unsigned char f116; };
void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0);

extern "C" {
/* Getter for the reflected `_isActive` member (igBoolMetaField at +116). */

unsigned char Gap__Core__igArenaMemoryPool__vfunc_33(igArenaMemoryPool *self);

}
extern "C" {
/* IgArenaMemoryPool slot 26, returns the reflected _rawMemory block pointer (+124). */
int Gap__Core__igArenaMemoryPool__vfunc_26(igArenaMemoryPool *self);

}
struct Buf24 { char pad[2036]; int f2036; int pad2; int f2044; int f2048; int pad3; int f2056; };
class Pool24 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v51();
    char pad0[105 - 4]; char f105; char pad1[6]; Buf24 *buf; unsigned char busy; char pad3[7]; int f124; char f128; char pad4[7]; long long f136; char pad5[16]; long long f160;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_24(int *out, Pool24 *p, int a2, long long a3, char t0);

extern "C" {
/* Getter for the reflected `_isAlchemyMemory` member (igBoolMetaField at +128). */

unsigned char Gap__Core__igArenaMemoryPool__vfunc_25(igArenaMemoryPool *self);

}
extern "C" {
/* igMemoryPool slot 29 (vtable +116): constant 0 for the arena pool. This is the predicate
 * igAllocator_EncodeIndex calls on an allocator: zero selects the primary allocator list (even
 * encoded index), nonzero the secondary list. igMallocMemoryPool also returns 0; igPageMemoryPool
 * and igStackMemoryPool return 1. The receiver is not read. */
int Gap__Core__igArenaMemoryPool__vfunc_29(void);

}
extern "C" {
void *FUN_002ba650(...);
}
class Tracker34 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();  virtual DW4SR4 v21(); virtual DW4SR4 v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();  virtual DW4SR4 v31(int); int rc; };
struct Pool34 {
    char p[120]; Tracker34 *f120; char q[68]; int f192;
    inline void relp() { Tracker34 *x = f120; if (x) { x->rc = x->rc - 1; if (((unsigned long long)((long long)x->rc << 0x29) >> 0x29) == 0) igObject_Destroy(x); } }
};
struct Ref {
    Tracker34 *o;
    ~Ref() {
        Tracker34 *object = o;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_34(int *ret, Pool34 *p, int flag);

extern "C" {
/* igArenaMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument; same leaf as
 * FUN_002f0620 and igMallocMemoryPool slot 24. */
void Gap__Core__igArenaMemoryPool__vfunc_35(int *statusOut);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_36(igArenaMemoryPool *arg0);

}
extern "C" {
/* The comparison is written `arg2 <= lim`, not `lim >= arg2`, and the store is repeated in both
 * arms. */
void Gap__Core__igArenaMemoryPool__vfunc_41(int *arg0, char *arg1, unsigned long long arg2);

}
extern "C" {

/* Accessor: the arena's reflected _maxSize field (igUnsignedLongMetaField, +152). */
long long Gap__Core__igArenaMemoryPool__vfunc_42(igArenaMemoryPool *self);

}
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_43(int *arg0, void *arg1, int arg2);
}
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
void Gap__Core__igArenaMemoryPool__vfunc_43(int *arg0, void *arg1, int arg2);

extern "C" {
/* IgArenaMemoryPool virtual getter 44. Returns the reflected `_preSize` field
 * (igUnsignedIntMetaField, +168). */
int Gap__Core__igArenaMemoryPool__vfunc_44(igArenaMemoryPool *self);

}
extern "C" {
/* Setter for the pool's _alignment (a 16-bit field at +172). It reports through a status word,
 * always the "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void Gap__Core__igArenaMemoryPool__vfunc_37(int *outStatus, igArenaMemoryPool *self, short alignment);

}
extern "C" {
/* Getter for the reflected `_alignment` member (igUnsignedShortMetaField at +172). */

unsigned short Gap__Core__igArenaMemoryPool__vfunc_38(igArenaMemoryPool *self);

}
extern "C" {
/* Setter for the pool's _elementSize (+144). It reports through a status word, always the
 * "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
void Gap__Core__igArenaMemoryPool__vfunc_39(int *outStatus, igArenaMemoryPool *self, int elementSize);

}
extern "C" {
/* IgArenaMemoryPool slot 40, returns the reflected _elementSize (+144). */
int Gap__Core__igArenaMemoryPool__vfunc_40(igArenaMemoryPool *self);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0);

}
extern "C" {

/* Accessor: the arena's reflected _localNetAllocated statistic (igLongMetaField, +24). */
long long Gap__Core__igArenaMemoryPool__vfunc_47(igArenaMemoryPool *self);

}
extern "C" {

/* Accessor: the arena's reflected _localNetAllocatedWithOverhead statistic (igLongMetaField, +56). */
long long Gap__Core__igArenaMemoryPool__vfunc_48(igArenaMemoryPool *self);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_99(void *arg0);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_100(void *arg0);

}
extern "C" {
int FUN_0031d370(void *arg0);

}
extern "C" {
int FUN_0031d390(void *arg0);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_101(void *arg0);

}
extern "C" {
long long Gap__Core__igArenaMemoryPool__vfunc_49(igArenaMemoryPool *arg0);

}
class igArenaMemoryPoolView {
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
    virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101();
    virtual void *MemoryOperation(void *block, int size, unsigned int alignment);
    unsigned int _refCount;
    char _pad8[136];
    unsigned int _elementSize;
    char _pad148[24];
    unsigned short _alignment;
};

extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_53(igArenaMemoryPoolView *self);

extern "C" {

void FUN_0031d3f0(void *arg0);
}
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void FUN_0031d3f0(void *arg0);

extern "C" {

void FUN_0031d430(void *arg0);
}
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
void FUN_0031d430(void *arg0);

extern "C" {

int FUN_0031d460(void *arg0, int arg1);
}
int FUN_0031d460(void *arg0, int arg1);


extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_54(igArenaMemoryPoolView *self, unsigned int size);


extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_55(igArenaMemoryPoolView *self, unsigned int size, unsigned int alignment);

class Pool56 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void *Alloc(int, int, int); };
struct ArenaPoolFlags { void *vt; char pad[168]; unsigned short align; char pad2[18]; unsigned flags; };
static inline int flag2(ArenaPoolFlags *p) { return (p->flags & 2) != 0; }
static inline int flag4(ArenaPoolFlags *p) { return (p->flags & 4) != 0; }
extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_56(Pool56 *self, int count, int size);

class Pool57 {
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
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual int vX(int, int);
};
struct Flags57 { char pad[192]; int f192; };
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_57(Flags57 *t, int n, int m);


extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_58(igArenaMemoryPoolView *self, void *block, unsigned int size);


extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_59(igArenaMemoryPoolView *self, void *block, int size, unsigned int alignment);

extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_63(int *arg0);

}
extern "C" {
int FUN_002f2260(...);
extern int DAT_004c2370[4];
extern unsigned char GPR_00554d64;
extern unsigned char GPR_00554d68;
}
struct Rel { static inline void go(RefObject *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)((long long)object->references << 0x29) >> 0x29) == 0)
            igObject_Destroy(object);
    }
} };
struct Arena97 { char p[2020]; int f2020; int f2024; int f2028; int f2032; char q[24]; int f2060; int f2064; };
struct Bits { unsigned refs : 23; unsigned rest : 9; };
class Pool97 { public:
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
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void v49();
    int w4;
    char pad8[104];
    Arena97 *arena;
    unsigned char isActive;
    char pad117[3];
    RefObject *lock;
    int raw;
    unsigned char alch;
    char pad129[7];
    unsigned long long sysAlloc;
    unsigned int elemSize;
    char pad148[4];
    unsigned long long maxSize;
    unsigned long long size;
    unsigned int preSize;
    unsigned short alignment;
    char pad174[2];
    RefObject *tracker;
    int poolIndex;
    int heapLevel;
    int msgLevel;
    int optFlags;
    int preSized;
    unsigned int smallest;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_97(Pool97 *self);
void Gap__Core__igArenaMemoryPool__vfunc_97(Pool97 *self);

extern "C" {
int *FUN_002f89a0(...);
extern int DAT_004f7910[4];
extern int DAT_004fd670[4];
extern int DAT_004fd6d0[4];
extern int DAT_004fd730[4];
extern unsigned int DAT_00587208[4];
extern unsigned int DAT_00587210[4];
extern unsigned char GPR_00554d6c;
extern unsigned char GPR_00554d70;
extern unsigned char GPR_00554d74;
}
struct igResult98 { int v; igResult98() {} };
struct Arena98 { char pad[2020]; int f2020; int f2024; int f2028; int f2032; };
class Pool98 { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v25(int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual int v86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual igResult98 v100();
 char p4[20]; long long f24; char p32[24]; int f56; char p60[28]; long long f88; char p96[16]; Arena98 * f112; char p116[44]; long long f160; char p168[12]; int f180; char p184[4]; int f188; unsigned int f192;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_98(Pool98 *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_98(Pool98 *arg0);

extern "C" {
int igMemoryPool_Initialize();
void *FUN_0031eb90(igArenaMemoryPool *arg0);

}
extern "C" {
int FUN_002effb0();
void *FUN_0031ebd0(igArenaMemoryPool *arg0);

}
extern "C" {
int igMemoryPool_CopyConstruct();
void *FUN_0031ec20(igArenaMemoryPool *arg0);

}
/* call the virtual at vtable offset 392, then the igObject slot-0 base step. The DW4VC_392_0
 * stand-in class has 96 dummy virtuals so vX() lands at that offset (offset = 8 + 4 * preceding
 * virtuals). */
extern "C" {
int Gap__Core__igObject__vfunc_00(...);
void Gap__Core__igArenaMemoryPool__vfunc_02(void **self);
}
class DW4VC_392_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual int vX(); };
void Gap__Core__igArenaMemoryPool__vfunc_02(void **self);


extern "C" void Gap__Core__igArenaMemoryPool__vfunc_66(igArenaMemoryPoolView *self, void *block);

extern "C" {
struct Header85 { unsigned sz:24; unsigned idx:5; unsigned mid:2; unsigned big:1; unsigned pad4; unsigned rest:12; unsigned ext:12; unsigned top:8; };
void *igAllocator_ResolveEncodedIndex(int);
int Gap__Core__igArenaMemoryPool__vfunc_85(void *self, unsigned char *p);

}
extern "C" {
int Gap__Core__igArenaMemoryPool__vfunc_83(void);

}
extern "C" {
struct Header84 { unsigned lo:5; unsigned sz:19; unsigned mid:7; unsigned big:1; unsigned pad4; unsigned ext:12; unsigned rest:20; };
int Gap__Core__igArenaMemoryPool__vfunc_84(int arg0, unsigned char *p);

}
extern "C" {
extern int DAT_004fd7a0[4];
extern unsigned char GPR_00554d78;
}
class SetFlagsPool { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();  virtual int vX(int);
 char pad[184]; int cnt; int flags; };
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(SetFlagsPool *p, int f);

extern "C" {
int Gap__Core__igArenaMemoryPool__vfunc_89(void *arg0);

}
extern "C" {
typedef struct Obj { int w0; unsigned refs; } Obj;
void Gap__Core__igArenaMemoryPool__vfunc_90(int *arg0, Obj *arg1);

}
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_86(void);

}
extern "C" {
int Gap__Core__igArenaMemoryPool__vfunc_91(void *arg0);

}
extern "C" {
void Gap__Core__igArenaMemoryPool__vfunc_92(void *arg0, int arg1);

}
extern "C" {
}
typedef struct Header93 { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } Header93;
typedef struct TagByte93 { unsigned char b : 7; unsigned char flag : 1; } TagByte93;
typedef struct Pool93 { char p[180]; int f180; inline int Chk(int y) { if (f180 < 64 && y >= 64) return 0; return 1; } } Pool93;

class DW4VC_364_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int vX(); };

extern "C" void Gap__Core__igArenaMemoryPool__vfunc_93(int *arg0, Pool93 *arg1, char *arg2, DW4VC_364_0 *arg3);

extern "C" {

int Gap__Core__igArenaMemoryPool__vfunc_94(void *arg0, void **arg1);
}
int Gap__Core__igArenaMemoryPool__vfunc_94(void *arg0, void **arg1);

extern "C" {
struct Header95 { char pad[3]; unsigned char sz:5; unsigned char mid:2; unsigned char big:1; char pad2[4]; unsigned int u0:12; unsigned int ext:12; unsigned int u1:8; };
int Gap__Core__igArenaMemoryPool__vfunc_95(int arg0, unsigned char *p);

}
extern "C" {
int Gap__Core__igObject__vfunc_01(...);
struct Arena03 { char pad[2020]; void *f7e4; int f7e8; int f7ec; int f7f0; char pad2[24]; int f80c; int f810; };
struct Pool03 { char pad[112]; Arena03 *f70; };
extern unsigned char GPR_00554d7c;
}
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_03(Pool03 *arg0, int arg1);
void Gap__Core__igArenaMemoryPool__vfunc_03(Pool03 *arg0, int arg1);

/* Pool hook: runs the class's virtual slot 392 on the receiver, then the igObject default for this
 * slot (an empty stub). */
extern "C" {
int Gap__Core__igObject__vfunc_02(...);
void Gap__Core__igArenaMemoryPool__vfunc_04(igArenaMemoryPool *self);
}
/* ABI dispatch view of virtual slot 392 (96 leading virtuals); never instantiated. */
class ArenaPoolSlot392View { public:
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
    virtual void Slot392();
};

void Gap__Core__igArenaMemoryPool__vfunc_04(igArenaMemoryPool *self);

extern "C" {
/* Reset the pool after the base-class reset, restoring _poolOptionFlags to the default registered
 * for that field in igArenaMemoryPool_InitFields (the igMallocMemoryPool counterpart is
 * Gap__Core__igMallocMemoryPool__vfunc_13). */
int Gap__Core__igObject__vfunc_11();
extern int g_poolOptionFlagsDefault_004c2370[4];

void Gap__Core__igArenaMemoryPool__vfunc_13(igArenaMemoryPool *self);

}