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
void Gap__Core__igStackMemoryPool__vfunc_45(int *outStatus) {
    int status;

    FUN_002f0880(&status);
    *outStatus = status;
}

typedef struct { char pad[116]; unsigned a; unsigned long long len; int pad2; unsigned c; int d; unsigned char flag; } S30;
void Gap__Core__igStackMemoryPool__vfunc_30(S30 *p) {
    unsigned v = p->a;
    if (v != 0) {
        p->c = v;
        p->d = (int)((unsigned long long)p->c + p->len + 0xFFFFFFFFFFFFFFFCULL);
        p->d = p->d - (p->d & 3);
        p->flag = 1;
    }
}

typedef struct S31 { char pad[116]; int f116; long long f120; unsigned f128; unsigned f132; int f136; } S31;
void Gap__Core__igStackMemoryPool__vfunc_31(S31 *s) {
    s->f132 = s->f116;
    s->f136 = (int)(s->f132 + s->f120 + (long long)(unsigned __int128)(unsigned long long)-4LL);
    s->f136 = s->f136 - (s->f136 & 3);
}

/* Disable step of the stack pool: run virtual slot 124 (vfunc_31, which copies +116 to +132 and
 * recomputes +136 as the 4-byte-aligned end: +132 plus the 64-bit size at +120, less 4), then
 * clear _isActive. The alias pool has the same pair: its slot 128 calls the receiver's slot 124
 * and then clears the active byte. */
/* ABI dispatch view of virtual slot 124 (29 leading virtuals); never instantiated. */
class StackPoolSlot124View { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void Reset();
};

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
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb410[2];
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

struct E47 { unsigned sz : 31; unsigned f : 1; };
struct P47 { char p[116]; int raw; char q[12]; int top; struct E47 *e; unsigned char active; };
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

class DW4VC_196_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual long long vX(); };
long long Gap__Core__igStackMemoryPool__vfunc_48(igStackMemoryPool *arg0) {
    return arg0->_totalSize - ((DW4VC_196_0 *)(((char *)(arg0) + 0)))->vX();
}

long long Gap__Core__igStackMemoryPool__vfunc_49(igStackMemoryPool *arg0) {
    long long r = (long long)arg0->_nextInt - (long long)arg0->_stackPtr;
    if (r > 0) return r;
    return 0;
}

struct S53 { char p[112]; unsigned short align; char q[14]; int size; int top; int *end; unsigned char active; };
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

struct S54 { char p[112]; unsigned short align; char q[18]; int top; int *end; };
int Gap__Core__igStackMemoryPool__vfunc_54(struct S54 *arg0, int arg1) {
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

int Gap__Core__igStackMemoryPool__vfunc_55(struct S54 *arg0, int size, unsigned short arg2) {
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

void *Gap__Core__igStackMemoryPool__vfunc_56(struct S54 *s, int count, int size) {
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

void *Gap__Core__igStackMemoryPool__vfunc_57(struct S54 *s, int count, int size, unsigned short a) {
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

class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class DW4VC_264_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
class DW4VC_336_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual int vX(int); };
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

class DW4VC_220_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
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
        *result = DAT_004fb410[0];
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
            *result = DAT_004fb410[0];
            return;
        }
    }
    for (l = 0; l < count; l++) {
        out[l] = 0;
    }
    *result = DAT_004fb418[0];
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
        *result = DAT_004fb410[0];
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
            *result = DAT_004fb410[0];
            return;
        }
    }
    for (l = 0; l < count; l++) {
        out[l] = 0;
    }
    *result = DAT_004fb418[0];
}

struct E84 { unsigned int len : 31; unsigned int fl : 1; };
class DW4VC_340_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int vX(); char pad4[128]; int f132; E84 *f136; };
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

struct S85 { char pad[116]; unsigned start; unsigned long long len; };
bool Gap__Core__igStackMemoryPool__vfunc_85(S85 *s, unsigned a) {
    bool r = false;
    if (a >= s->start) {
        if ((unsigned long long)a < (unsigned long long)s->start + s->len) r = true;
    }
    return r;
}

typedef struct Stack64 { char pad[116]; unsigned base; char pad2[12]; unsigned top; unsigned *end; } Stack64;
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

class Stack66 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int Owns(); char pad[112]; unsigned base; char pad2[12]; unsigned top; unsigned *end; };
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

typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad148[148]; S1 *f94; } S0;
void Gap__Core__igStackMemoryPool__vfunc_90(S0 *arg0, S1 *arg1) {
    S1 *temp_a0;
    if ((arg1 == 0) || (igObject_GetAllocator(arg1) != arg0)) {
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
    FUN_002ed610(a1, a2, a3, a[29], (unsigned int)(a[33] - a[29]), a4);
}

int Gap__Core__igStackMemoryPool__vfunc_91(void *arg0) {
    return *(int *)((char *)(arg0) + 144);
}

void Gap__Core__igStackMemoryPool__vfunc_92(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 144) = arg1;
}

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
