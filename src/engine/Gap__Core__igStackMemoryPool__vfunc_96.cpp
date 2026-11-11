#include "dw4/reflected.h"
extern "C" {
int FUN_002f0880(int *);
void *memset(void *, int, int);
int memcpy(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
void FUN_002ed610(int, int, int, int, unsigned long long, int);
int FUN_002d6e60(...);
int FUN_002f89a0(...);
void *FUN_0032a100(...);
int FUN_0032a180(...);
int FUN_0032a1b0(...);
void *FUN_0032a1e0(...);
int List_InsertWords(...);
void FUN_0032a260(void);
extern int g_allocatorFailureStatus[4];
extern int g_statusSucceeded[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_004ff570[4];

/* Output-first status wrapper. The status word is returned through the hidden output pointer (a0).
 * The shared helper also reads a1 (the pool) and a2 (a request descriptor) from its asm, and this
 * wrapper passes both through untouched, which is why only the local cell is named at the call.
 * The helper leaves the success word (g_statusSucceeded) in the cell. */
void Gap__Core__igStackMemoryPool__vfunc_45(int *outStatus);

typedef struct { char pad[116]; unsigned a; unsigned long long len; int pad2; unsigned c; int d; unsigned char flag; } S30;
void Gap__Core__igStackMemoryPool__vfunc_30(S30 *p);

typedef struct S31 { char pad[116]; int f116; long long f120; unsigned f128; unsigned f132; int f136; } S31;
void Gap__Core__igStackMemoryPool__vfunc_31(S31 *s);

/* Disable step of the stack pool: run virtual slot 124 (vfunc_31, which copies +116 to +132 and
 * recomputes +136 as the 4-byte-aligned end: +132 plus the 64-bit size at +120, less 4), then
 * clear _isActive. The alias pool has the same pair: its slot 128 calls the receiver's slot 124
 * and then clears the active byte. */
/* ABI dispatch view of virtual slot 124 (29 leading virtuals); never instantiated. */
class StackPoolSlot124View { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void Reset();
};

void Gap__Core__igStackMemoryPool__vfunc_32(igStackMemoryPool *self);

/* Reports whether the pool is active: returns _isActive (+140), same slot as
 * igAliasMemoryPool::vfunc_33. */
unsigned char Gap__Core__igStackMemoryPool__vfunc_33(igStackMemoryPool *self);

/* IgStackMemoryPool vtable slot 35: status leaf. Ignores the object and writes the engine's
 * current failure-status word (the one an allocation failure publishes) through the output-first
 * argument. */
void Gap__Core__igStackMemoryPool__vfunc_35(int *status_out);

/* Slot 36 getter: returns the pool's _totalSize field (an int widened to 64 bits). */
long long Gap__Core__igStackMemoryPool__vfunc_36(igStackMemoryPool *self);

/* Set the pool's alignment (`_alignment`, +112) and report success through the status word.
 * vfunc_38 is the matching getter. */
void Gap__Core__igStackMemoryPool__vfunc_37(int *status, igStackMemoryPool *self, short alignment);

/* IgStackMemoryPool slot 38, returns the reflected _alignment (+112, unsigned short). */
unsigned short Gap__Core__igStackMemoryPool__vfunc_38(igStackMemoryPool *self);

/* Set the pool's element size (`_elementSize`, +128) and report success through the status word. */
void Gap__Core__igStackMemoryPool__vfunc_39(int *status, igStackMemoryPool *self, int elementSize);

/* Getter: the pool's _elementSize (+128, reflected as igUnsignedIntMetaField). */
int Gap__Core__igStackMemoryPool__vfunc_40(igStackMemoryPool *self);

void Gap__Core__igStackMemoryPool__vfunc_24(int *arg0, void *arg1, int arg2, long long arg3, char arg4);

/* Getter: the pool's _rawMemory reference (+116, reflected as igRawRefMetaField), the backing
 * block the stack pointer walks through. */
int Gap__Core__igStackMemoryPool__vfunc_26(igStackMemoryPool *self);

/* IgStackMemoryPool vtable slot 42: getter for the reflected _totalSize (+120,
 * igUnsignedLongMetaField). Returned as a 64-bit value, like igArenaMemoryPool slot 42 for its
 * _maxSize. */
long long Gap__Core__igStackMemoryPool__vfunc_42(igStackMemoryPool *self);

long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0);

struct E47 { unsigned sz : 31; unsigned f : 1; };
struct P47 { char p[116]; int raw; char q[12]; int top; struct E47 *e; unsigned char active; };
long long Gap__Core__igStackMemoryPool__vfunc_47(struct P47 *arg0);

class DW4VC_196_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual long long vX(); };
long long Gap__Core__igStackMemoryPool__vfunc_48(igStackMemoryPool *arg0);

long long Gap__Core__igStackMemoryPool__vfunc_49(igStackMemoryPool *arg0);

struct S53 { char p[112]; unsigned short align; char q[14]; int size; int top; int *end; unsigned char active; };
int Gap__Core__igStackMemoryPool__vfunc_53(struct S53 *arg0);

struct S54 { char p[112]; unsigned short align; char q[18]; int top; int *end; };
int Gap__Core__igStackMemoryPool__vfunc_54(struct S54 *arg0, int arg1);

int Gap__Core__igStackMemoryPool__vfunc_55(struct S54 *arg0, int size, unsigned short arg2);

void *Gap__Core__igStackMemoryPool__vfunc_56(struct S54 *s, int count, int size);

void *Gap__Core__igStackMemoryPool__vfunc_57(struct S54 *s, int count, int size, unsigned short a);

class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
class DW4VC_336_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual int vX(int); };
int Gap__Core__igStackMemoryPool__vfunc_58(void **arg0, int arg1, unsigned int arg2);

class DW4VC_220_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
int Gap__Core__igStackMemoryPool__vfunc_59(void **arg0, int arg1, unsigned int arg2, int arg3);

typedef struct StackPoolFields {
    char pad0[112];
    unsigned short alignment;
    char pad1[18];
    unsigned top;
    unsigned *end;
} StackPoolFields;
static inline unsigned short effectiveAlign(StackPoolFields *pool, unsigned short wanted) {
    return wanted > pool->alignment ? wanted : pool->alignment;
}
void Gap__Core__igStackMemoryPool__vfunc_62(int *result, StackPoolFields *pool, int n, unsigned *sizes, unsigned *out);

void Gap__Core__igStackMemoryPool__vfunc_63(int *result, StackPoolFields *pool, int n, unsigned *sizes, unsigned *out, unsigned short *aligns);

struct E84 { unsigned int len : 31; unsigned int fl : 1; };
class DW4VC_340_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int vX(); char pad4[128]; int f132; E84 *f136; };
int Gap__Core__igStackMemoryPool__vfunc_84(DW4VC_340_0 *arg0, unsigned int arg1);

struct S85 { char pad[116]; unsigned start; unsigned long long len; };
bool Gap__Core__igStackMemoryPool__vfunc_85(S85 *s, unsigned a);

typedef struct Stack64 { char pad[116]; unsigned base; char pad2[12]; unsigned top; unsigned *end; } Stack64;
void Gap__Core__igStackMemoryPool__vfunc_64(Stack64 *self, unsigned count, unsigned *ptrs);

class Stack66 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int Owns(); char pad[112]; unsigned base; char pad2[12]; unsigned top; unsigned *end; };
void Gap__Core__igStackMemoryPool__vfunc_66(Stack66 *self, unsigned size);

int Gap__Core__igStackMemoryPool__vfunc_89(void *arg0);

typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad148[148]; S1 *f94; } S0;
void Gap__Core__igStackMemoryPool__vfunc_90(S0 *arg0, S1 *arg1);

void Gap__Core__igStackMemoryPool__vfunc_86(int *a, int a1, int a2, int a3, int a4);

int Gap__Core__igStackMemoryPool__vfunc_91(void *arg0);

void Gap__Core__igStackMemoryPool__vfunc_92(void *arg0, int arg1);

class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
void Gap__Core__igStackMemoryPool__vfunc_96(void *arg0, int arg1) {
    void *sp3C;
    void *var_v0;

    if (((DW4VC_132_0 *)(((char *)(arg0) + 0)))->vX() != 0) {
        var_v0 = (void *)(FUN_0032a1e0(0xA8));
        if (var_v0 != 0) {
            var_v0 = (void *)(FUN_0032a100(var_v0));
        }
        sp3C = (void *)(var_v0);
        *(int *)((char *)(var_v0) + 0) = (int)((int) *(int *)((char *)(arg0) + 116));
        *(int *)((char *)(sp3C) + 4) = (int)((int) *(int *)((char *)(arg0) + 120));
        FUN_0032a180(sp3C, &DAT_004ff570[0]);
        FUN_0032a1b0(sp3C, FUN_002f89a0(arg0));
        List_InsertWords(arg1, FUN_002d6e60(arg1, &sp3C, FUN_0032a260), 1, &sp3C);
    }
}
}
