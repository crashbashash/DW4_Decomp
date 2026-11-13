#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
extern "C" {
int memset(...);
int printf(int *);
void *igObject_GetAllocator(void *);
void Gap__Core__igObject__vfunc_00(void *);
int FUN_002f0880(int *);
void *FUN_002ba650(...);
void *igFile_Create(void *);
int *FUN_002f89a0(int);
int FUN_00304430(const char *, ...);
int FUN_00304680();
int igMemoryPool_Initialize(...);
int igMemoryPool_CopyConstruct(...);
int FUN_002effb0(...);  /* Base-pool constructor: igObject header init, then the base vtable. */
/* Allocator failure-status word: the value every allocator status leaf publishes. Paired with the
 * success word. */
extern int g_allocatorFailureStatus[4];
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
/* Vtable image of igAliasMemoryPool; the array form keeps the address load absolute. */
extern int g_igAliasMemoryPool_vtable[4];
extern int g_statusSucceeded[4];
extern int g_allocatorFailureStatus[4];
extern int DAT_004f90b0[4];
extern int text_null[4];
extern int DAT_004f90c0[4];
extern int DAT_004f92b0[4];
extern int DAT_004f92f0[4];

int Gap__Core__igAliasMemoryPool__vfunc_99(void *arg0);

/* Retail ABI views, not original class definitions. Virtual tables include
 * an eight-byte header; Object projects slot376. Never instantiate these views. */
class Object { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual unsigned char Check(void *); unsigned refs; };

/* Bind `alias` as the pool this one forwards to. The new alias is retained before the previous one
 * is released (so assigning the same object is safe); the previous alias is destroyed when its
 * reference count drops to zero. The alias is then asked (virtual slot 376) whether it accepts
 * this pool and the low byte of the answer becomes _isReassignable; a null alias clears it. */
void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, Object *alias);

/* slot 30, reset the allocation counters and mark the pool active. */
void Gap__Core__igAliasMemoryPool__vfunc_30(igAliasMemoryPool *self);

/* Slot 31, the same counter reset without touching _isActive. */
void Gap__Core__igAliasMemoryPool__vfunc_31(igAliasMemoryPool *self);

class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); };

/* Disable the pool: run the receiver's virtual at vtable offset 124 (the reset callback), then
 * clear _isActive afterwards, even if the callback wrote it. */
void Gap__Core__igAliasMemoryPool__vfunc_32(igAliasMemoryPool *self);

/* Slot 33, report whether the pool is active. */
unsigned char Gap__Core__igAliasMemoryPool__vfunc_33(igAliasMemoryPool *self);

/* Slot 26, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_26(void);

/* Slot 24, output the allocator failure-status word. */
void Gap__Core__igAliasMemoryPool__vfunc_24(int *outStatus);

/* Slot 25, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_25(void);

/* Slot 29, fixed result 0. */
int Gap__Core__igAliasMemoryPool__vfunc_29(void);

struct LockStatus { int v; LockStatus() {} LockStatus(int x) { v = x; } };
class Lock : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual LockStatus open(); virtual LockStatus close(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual LockStatus wait(int); };

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
LockStatus Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable);

/* IgAliasMemoryPool vtable slot 35: status leaf. Ignores the pool and writes the engine's failure-
 * status word (set to 1 by the engine init) through the output-first argument. */
void Gap__Core__igAliasMemoryPool__vfunc_35(int *statusOut);

int Gap__Core__igAliasMemoryPool__vfunc_36(void);

/* Set the pool's size limit (`_maxSize`) and report success through the status word. Sibling
 * setters (vfunc_37 alignment, vfunc_39 element size) share the shape. */
void Gap__Core__igAliasMemoryPool__vfunc_41(int *status, igAliasMemoryPool *self, long long maxSize);

/* Vtable slot 42: the pool's capacity in bytes (_maxSize). */
long long Gap__Core__igAliasMemoryPool__vfunc_42(igAliasMemoryPool *self);

/* Set the pool's alignment (`_alignment`) and report success through the status word. */
void Gap__Core__igAliasMemoryPool__vfunc_37(int *status, igAliasMemoryPool *self, short alignment);

/* IgAliasMemoryPool slot 38, returns the reflected _alignment (+176, unsigned short). */
unsigned short Gap__Core__igAliasMemoryPool__vfunc_38(igAliasMemoryPool *self);

/* IgAliasMemoryPool setter for `_elementSize` (+172). Stores the new element size and reports
 * success through the out cell (the cell receives the shared success status word, see
 * g_statusSucceeded). */
void Gap__Core__igAliasMemoryPool__vfunc_39(int *status_out, igAliasMemoryPool *self, int element_size);

/* IgAliasMemoryPool slot 40, returns the reflected _elementSize (+172). */
int Gap__Core__igAliasMemoryPool__vfunc_40(igAliasMemoryPool *self);

/* Output-first status wrapper. The status word is returned through the hidden output pointer (a0).
 * The shared helper also reads a1 (the pool) and a2 (a request descriptor) from its asm, and this
 * wrapper passes both through untouched, which is why only the local cell is named at the call.
 * The helper leaves the success word (g_statusSucceeded) in the cell. */
void Gap__Core__igAliasMemoryPool__vfunc_45(int *outStatus);

long long Gap__Core__igAliasMemoryPool__vfunc_46(igAliasMemoryPool *arg0);

/* Vtable slot 47: total bytes currently allocated from the pool (_allocedBytes). */
long long Gap__Core__igAliasMemoryPool__vfunc_47(igAliasMemoryPool *self);

/* Accessor: the alias pool's reflected _allocedBytes field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igAliasMemoryPool__vfunc_48(igAliasMemoryPool *self);

long long Gap__Core__igAliasMemoryPool__vfunc_101(igAliasMemoryPool *arg0);

long long Gap__Core__igAliasMemoryPool__vfunc_102(igAliasMemoryPool *arg0);

long long Gap__Core__igAliasMemoryPool__vfunc_49(igAliasMemoryPool *arg0);

/* PoolView is an ABI projection (vtable slots), never instantiated. */
class PoolView {public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void *AllocateDefault(long long); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual long long Size(void *); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void Close(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void *Backend(void *,long long,unsigned short); };

void *Gap__Core__igAliasMemoryPool__vfunc_53(igAliasMemoryPool *self);

/* The lock calls return a 4-byte struct by value; MWCC passes it through a hidden return buffer,
 * which the stack slot in each caller reproduces. */
struct LockCallStatus { int word; };
/* The lock object's vtable: unnamed padding slots, the unlock call (offset 124) and the lock call
 * (offset 132), with the two-word class header in front of the slots. */
class AllocationLockVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual LockCallStatus unlock(); virtual void d30(); virtual LockCallStatus lock(int); };

/* Take the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 132 with 1. The status it returns is discarded. */
void igAliasMemoryPool_Lock(igAliasMemoryPool *self);

/* Release the pool's allocation lock: when a lock object is attached (_allocationLock), call its
 * virtual method at vtable offset 124. The status it returns is discarded. */
void igAliasMemoryPool_Unlock(igAliasMemoryPool *self);

/* Release the pool's allocation lock, then hand back the value the caller supplied: when a lock
 * object is attached (_allocationLock), call its virtual method at vtable offset 124 (the same
 * unlock call as igAliasMemoryPool_Unlock); the status it returns is discarded. This lets a caller
 * write `return igAliasMemoryPool_UnlockAndReturn(pool, result)` to leave a locked section while
 * preserving its result. */
int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result);

void *Gap__Core__igAliasMemoryPool__vfunc_54(igAliasMemoryPool *self,long long size);

void *Gap__Core__igAliasMemoryPool__vfunc_55(igAliasMemoryPool *self,long long size,unsigned short alignment);

class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual int vX(int, int, int); };
int Gap__Core__igAliasMemoryPool__vfunc_56(igAliasMemoryPool *arg0, int arg1, int arg2);

class DW4VC_412_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual int vX(int, int); };
int Gap__Core__igAliasMemoryPool__vfunc_57(void **arg0, int arg1, int arg2);

void *Gap__Core__igAliasMemoryPool__vfunc_58(igAliasMemoryPool *self,void *old,long long size);

void *Gap__Core__igAliasMemoryPool__vfunc_59(igAliasMemoryPool *self,void *old,long long size,unsigned short alignment);

class DW4VC_192_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual long long vX(); };
class DW4VC_200_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int vX(int, int, int); };
class DW4VC_260_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual int vX(int); };
int Gap__Core__igAliasMemoryPool__vfunc_65(igAliasMemoryPool *arg0, int arg1);

struct R62 { int w0; R62(int v) { w0 = v; } R62() {} };
class DW4VC_248_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual R62 vX(); };
R62 Gap__Core__igAliasMemoryPool__vfunc_62(igAliasMemoryPool *arg1);

/* matching construct: dummy virtual slots so the vX() call dispatches through retail vtable offset 252 */
struct R63 { int v; R63(int x) { v = x; } R63() {} };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual R63 vX(); };
R63 Gap__Core__igAliasMemoryPool__vfunc_63(igAliasMemoryPool *arg1);

class DW4VC_256_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual int vX(); };
void Gap__Core__igAliasMemoryPool__vfunc_64(igAliasMemoryPool *arg0);

void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old);

struct OwnsStatus { int v; OwnsStatus(int x) { v = x; } int get() { return v; } };
class P { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92();  virtual int vX(); };
OwnsStatus FUN_002f0180(int, int*);
int igAliasMemoryPool_OwnsAllocation(void *arg0) {
    igAliasMemoryPool *s = (igAliasMemoryPool *)arg0;
    int u;
    int sp3C;
    if (s->_isReassignable != 0) { int t = s->_poolIndex; if (t == ((P *)s->_aliasedMemoryPool)->vX()) return 1; } else { int x = FUN_002f0180(u, &sp3C).get(); if (x == g_statusSucceeded[0]) { return sp3C == (int)arg0; } }
    return 0;
}

long long igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old);

/* Dummy-virtual pool class (100 slots); the first call is variadic-declared so it passes only the
 * format. */
struct StatsPool {
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
    virtual int f40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual int f45();
    virtual int f46();
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
    virtual int f89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual int f97();
    virtual void d98();
    virtual int f99();
    virtual int f100();
};
void igAliasMemoryPool_PrintStatistics(StatsPool *arg0, char *arg1);

/* The pool's event tracker (reflected `_eventTracker`), stored as a raw handle. */
int igAliasMemoryPool_GetEventTracker(igAliasMemoryPool *self);

/* Reference-counted assignment of the _eventTracker field (+0x98). Retain the new tracker, release
 * the previous one (destroying it when its count reaches zero), then store. The refcount is the
 * low 23 bits of igObject::_refCount. */
void igAliasMemoryPool_SetEventTracker(igAliasMemoryPool *self, igObject *tracker);

class V : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, int *); virtual void v24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v29(int *); };

void igAliasMemoryPool_Dump(igAliasMemoryPool *self, int a1, int a2, int a3, int t0);

/* The pool's index (reflected `_poolIndex`). */
int igAliasMemoryPool_GetPoolIndex(igAliasMemoryPool *self);

/* Setter for the `_poolIndex` field. */
void igAliasMemoryPool_SetPoolIndex(igAliasMemoryPool *self, int poolIndex);

struct ManageStatus { int v; ManageStatus() {} };
class Tk {
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
    virtual int v220(long long, unsigned short);
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual int v236(int, long long, unsigned short);
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual int v264(int);
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
    virtual ManageStatus v372(int, void *);
};
class ManagedPool {
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
    virtual int v92(long long, int);
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
    virtual int v336(int);
    int pad4;
    char pad8[105];
    unsigned char f113;
    char pad114[14];
    unsigned long long f128;
    int f136;
    int f140;
    unsigned long long f144;
    char pad152[8];
    unsigned long long f160;
    int f168;
    char pad172[4];
    unsigned short f176;
    char pad178[2];
    Tk *f180;
};
ManageStatus FUN_002f0220(int, ManagedPool *);
ManageStatus FUN_002f0320(int, ManagedPool *);
int igAliasMemoryPool_ManageAllocation(ManagedPool *arg0, int arg1, long long arg2, unsigned short arg3);

/* Initialization helper of the alias pool: runs the base-pool initialization
 * (igMemoryPool_Initialize: igObject_InitHeader, then the base vtable), publishes the
 * igAliasMemoryPool vtable and clears the allocation lock, event tracker and aliased-pool
 * references (offsets 116, 152 and 180). Returns `self`. */
void *igAliasMemoryPool_Initialize(igAliasMemoryPool *self);

/* igAliasMemoryPool constructor. Runs the base-class constructor, publishes the pool's vtable and
 * clears the lock, event-tracker and aliased-pool references (offsets 116, 152, 180), then calls
 * igAliasMemoryPool_Initialize on a non-null receiver and returns it. */
void *igAliasMemoryPool_Construct(igAliasMemoryPool *self);

/* Copy-construct counterpart of igAliasMemoryPool_Initialize: runs the base-pool copy-construct
 * step (igMemoryPool_CopyConstruct: igObject_CopyConstructHeader, then the base vtable), publishes
 * the igAliasMemoryPool vtable and clears the allocation lock, event tracker and aliased-pool
 * references. Returns `self`. */
void *igAliasMemoryPool_CopyConstruct(igAliasMemoryPool *self);

/* Alias-pool teardown: release the aliased pool (low 23-bit reference count), run the receiver's
 * close slot, then the igObject base step. */
void Gap__Core__igAliasMemoryPool__vfunc_02(igAliasMemoryPool *self);
}
