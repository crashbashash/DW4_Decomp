#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
extern "C" {
int strstr(...);
int FUN_002f0880(...);
extern int DAT_004fd3c8[4];
extern int DAT_004fd3d8[4];
extern int DAT_004fd3f0[4];
extern int DAT_004fd400[4];
struct A1 { char p[152]; int f152; };
struct A2 { char p[76]; int f76; };
void Gap__Core__igMallocMemoryPool__vfunc_45(int *arg0, struct A1 *arg1, struct A2 *arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    int var_s2;
    int temp_s1;
    int r;
    int sp6C;
    FUN_002f0880(&sp6C);
    r = sp6C;
    temp_s1 = arg2->f76;
    if (temp_s1 != 0) {
        var_s2 = arg1->f152;
        if (strstr(temp_s1, &DAT_004fd3c8[0]) != 0) {
            var_s2 = 0;
        } else if (strstr(temp_s1, &DAT_004fd3d8[0]) != 0) {
            var_s2 = 1;
        } else if (strstr(temp_s1, &DAT_004fd3f0[0]) != 0) {
            var_s2 = 2;
        } else if (strstr(temp_s1, &DAT_004fd400[0]) != 0) {
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

extern "C" {
void *FUN_002ba650(...);
void *igObject_GetAllocator(void *);
extern int DAT_004fb410[4];
}
struct R { int v; R() {} R(int x) { v = x; } };
class Rc : public igVirtualObject {
public:
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
    virtual R v92();
    virtual R v96();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual R v132(int);
    
};

struct OB { char pad[116]; igSmartPointer<Rc> lock; };
extern "C" {
R Gap__Core__igMallocMemoryPool__vfunc_34(OB *arg1, unsigned char arg2) {
    R a;
    R b;
    R c;
    if (arg2 == 0) {
        igSmartPointer<Rc> held(arg1->lock);
        arg1->lock.clear();
        if (held.p != 0) {
            a = held.p->v132(1);
            b = held.p->v96();
        }
        arg1->lock.clear();
    } else if (arg2 == 1) {
        if (arg1->lock.p != 0) return R(DAT_004fb410[0]);
        igSmartPointer<Rc> created((Rc *)FUN_002ba650(igObject_GetAllocator(arg1)));
        c = created.p->v92();
        arg1->lock = created;
    }
    return R(DAT_004fb410[0]);
}
}

/* Setter for the pool's 64-bit _size (+136). It reports through a status word, always the
 * "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_35(int *outStatus, igMallocMemoryPool *self, long long size) {
    self->_size = size;
    *outStatus = g_statusSucceeded[0];
}

/* Accessor: the pool's reflected _size field (igUnsignedLongMetaField, +136). */
long long Gap__Core__igMallocMemoryPool__vfunc_36(igMallocMemoryPool *self) {
    return self->_size;
}

/* Set the pool's size limit (`_maxSize`, +128) and report success through the status word. */
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize) {
    self->_maxSize = maxSize;
    *status = g_statusSucceeded[0];
}

/* Accessor: the pool's reflected _maxSize field (igUnsignedLongMetaField, +128). */
long long Gap__Core__igMallocMemoryPool__vfunc_42(igMallocMemoryPool *self) {
    return self->_maxSize;
}

/* Setter for the pool's _alignment (a 16-bit field at +144). Like the other pool setters it
 * reports through a status word, always the "succeeded" one. */
/* Status word reported on success; array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment) {
    self->_alignment = alignment;
    *outStatus = g_statusSucceeded[0];
}

/* Returns the pool's allocation alignment, _alignment (+144). */
unsigned short Gap__Core__igMallocMemoryPool__vfunc_38(igMallocMemoryPool *self) {
    return self->_alignment;
}

/* Set the pool's element size (`_elementSize`, +124) and report success through the status word. */
/* Success status word, zero in the pristine ELF; the array form keeps the load absolute (lui/lw). */
extern int g_statusSucceeded[4];
void Gap__Core__igMallocMemoryPool__vfunc_39(int *status, igMallocMemoryPool *self, int elementSize) {
    self->_elementSize = elementSize;
    *status = g_statusSucceeded[0];
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

class igMallocMemoryPoolView {
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
    virtual void d97(); virtual void d98();
    virtual void *vfunc_99(void *block, int size, unsigned int alignment);
    unsigned int _refCount;
    char _pad8[116];
    unsigned int _elementSize;
    char _pad128[16];
    unsigned short _alignment;
};

extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_53(igMallocMemoryPoolView *self)
{
    return self->Allocate(self->_elementSize);
}

extern "C" {

void FUN_00322820(void *arg0);
}
struct DW4SR4 { int w0; };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void FUN_00322820(void *arg0) {
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_132_1 *)(temp_a1))->vX((int)(1));
    }
}

extern "C" {

void FUN_00322860(void *arg0);
}
class DW4VCSR_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual DW4SR4 vX(); };
void FUN_00322860(void *arg0) {
    DW4SR4 sp1C;
    void **temp_a1;

    temp_a1 = (void **)(*(int *)((char *)(arg0) + 116));
    if (temp_a1 != 0) {
        sp1C = ((DW4VCSR_124_0 *)(temp_a1))->vX();
    }
}

extern "C" {

int FUN_00322890(void *arg0, int arg1);
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

extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_54(igMallocMemoryPoolView *self, unsigned int size)
{
    return self->vfunc_99(0, size, self->_alignment);
}

extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_55(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment)
{
    return self->vfunc_99(0, size, alignment);
}

int memset(...);
class Pool56 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void *Alloc(int, int, int); };
struct MallocPoolFlags { void *vt; char pad[140]; unsigned short align; char pad2[10]; unsigned flags; };
static inline int flag2(MallocPoolFlags *p) { return (p->flags & 2) != 0; }
static inline int flag4(MallocPoolFlags *p) { return (p->flags & 4) != 0; }
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_56(Pool56 *self, int count, int size) {
    int total = count * size;
    void *p = self->Alloc(0, total, ((MallocPoolFlags *)self)->align);
    if (p != 0) {
        if (total != 0) {
            if (flag2((MallocPoolFlags *)self) || !flag4((MallocPoolFlags *)self)) {
                memset(p, 0, total);
            }
        }
    }
    return p;
}

extern "C" {
int Gap__Core__igMallocMemoryPool__vfunc_57(igMallocMemoryPool *arg0, int arg1, int arg2);
}
class DW4VC_404_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual int vX(int, int); };
struct H57 { static inline int has(int v, int m) { return (v & m) != 0; } };
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

extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_58(igMallocMemoryPoolView *self, void *block, unsigned int size)
{
    return self->vfunc_99(block, size, self->_alignment);
}

extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_59(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment)
{
    return self->vfunc_99(block, size, alignment);
}

extern int DAT_004fb418[4];
void Gap__Core__igMallocMemoryPool__vfunc_63(int *arg0) {
    *arg0 = DAT_004fb418[0];
}

class MallocPoolFreeView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void Release(void *block);
    unsigned int _refCount;
    char _pad8[72];
    long long _localFreeCount;
    long long _localNetAllocationCount;
};
struct MallocBlockTag { unsigned char lo : 5; unsigned char mid : 1; unsigned char padded : 1; unsigned char flag : 1; };
struct MallocBlockEnd { unsigned char b : 7; unsigned char flag : 1; };
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

/* Reset the pool after the base-class reset, restoring _poolOptionFlags to the default registered
 * for that field in igMallocMemoryPool_InitFields. */
int Gap__Core__igObject__vfunc_11();
extern int g_poolOptionFlagsDefault_004c25f8[4];
void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = (int) g_poolOptionFlagsDefault_004c25f8[0];
}

extern unsigned char GPR_00554dbc;
struct Ref { int pad; int rc; };
class O { public:virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void v49();
union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } f4; char pad[104]; char f112; int f116; int f120; int f124; long long f128; long long f136; short f144; Ref *f148; int f152; int f156;
};
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_97(O *o) {
    Ref *r;
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
    r = (Ref *)o->f116;
    if (r != 0) {
        r->rc = r->rc - 1;
        if (((unsigned long long)((long long)r->rc << 0x29) >> 0x29) == 0) igObject_Destroy(r);
    }
    o->f116 = 0;
    o->f152 = 1;
    o->f156 = 12;
}

int igMemoryPool_Initialize();
extern int DAT_00530e90[4];
void *FUN_003235c0(igMallocMemoryPool *arg0) {
    igMemoryPool_Initialize();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

int igMemoryPool_CopyConstruct();
extern int DAT_00530e90[4];
void *FUN_00323600(igMallocMemoryPool *arg0) {
    igMemoryPool_CopyConstruct();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00530e90[0]);
    arg0->_allocationLock = 0;
    arg0->_eventTracker = 0;
    return arg0;
}

/* Pool hook: run the class's virtual slot 392 on the receiver, then the igObject default for this
 * slot (which forwards to an empty stub). The malloc and alias pools both bind slot 392 to an
 * empty stub. */
extern "C" {
int Gap__Core__igObject__vfunc_00(...);
void Gap__Core__igMallocMemoryPool__vfunc_02(igMallocMemoryPool *self);
}
/* ABI dispatch view of virtual slot 392 (96 leading virtuals); never instantiated. */
class MallocPoolSlot392View { public:
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

void Gap__Core__igMallocMemoryPool__vfunc_02(igMallocMemoryPool *self) {
    ((MallocPoolSlot392View *)self)->Slot392();
    Gap__Core__igObject__vfunc_00(self);
}

extern "C" void Gap__Core__igMallocMemoryPool__vfunc_66(igMallocMemoryPoolView *self, void *block)
{
    self->vfunc_99(block, -1, self->_alignment);
}

typedef struct H85 { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } H85;
typedef struct T85 { unsigned char b : 7; unsigned char flag : 1; } T85;
int igAllocator_ResolveEncodedIndex(...);

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

typedef struct H84 { unsigned a : 5; unsigned size : 19; unsigned b : 7; unsigned flag : 1; unsigned w4; unsigned s2 : 12; unsigned c : 4; } H84;

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

class Pool87 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual long long Used(); int f4; unsigned long long s8, s16, s24, s32, s40, s48, s56, s64, s72, s80, s88, s96; char pad[48]; int name; };
extern "C" {
extern struct Ctx { char p[36]; int on; } *DAT_00586dc8[4];
extern char DAT_004f7910[], DAT_004f90b0[], DAT_004fef30[];
void FUN_00304430(const char *, ...);
void FUN_00304680(void);
int FUN_002ce1b0(void);
char *FUN_00312140(char *, int, int, int);
}
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_87(Pool87 *self, char *title) {
    char buf[64];
    char *name;
    if (title != 0 && title[0] != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
    }
    if (DAT_00586dc8[0]->on != 0) {
        name = FUN_00312140(buf, 64, self->name, FUN_002ce1b0());
    } else {
        name = DAT_004f7910;
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

typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct S0 { char pad148[148]; S1 *f94; } S0;

void Gap__Core__igMallocMemoryPool__vfunc_90(S0 *arg0, S1 *arg1) {
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

extern "C" {
int printf(int *);
void *FUN_002c4ca0(void *);
int FUN_00308390(int *, int);
void *igObject_GetAllocator(void *);
extern int DAT_004f92f0[4];
extern int DAT_004ff1b0[4];
extern int DAT_004ff1f0[4];
void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0);
}
class V : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, int *); virtual void v24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v29(int *); };
struct M { char p[152]; int f152; };

void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0) {
    int *g;
    FUN_00322820(self);
    g = &DAT_004ff1b0[0];
    if (t0 != 0) {
        igSmartPointer<V> r((V *)FUN_002c4ca0(igObject_GetAllocator(self)));
        if (r.p->v23(t0, &DAT_004f92f0[0]) == 0) {
            if (((M *)self)->f152 >= 2) {
                FUN_00308390(&DAT_004ff1f0[0], t0);
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

extern "C" {
extern int DAT_004fb418[4];
extern int DAT_004fb410[4];
}
typedef struct H93 { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } H93;
typedef struct T93 { unsigned char b : 7; unsigned char flag : 1; } T93;
typedef struct S { char p[120]; int f120; inline int Chk(int y) { if (f120 < 64 && y >= 64) return 0; return 1; } } S;
static inline int Chk(int x, int y) { if (x < 64) { if (y >= 64) { return 0; } return 1; } return 1; }
static inline int Chk2(int x, int y) { int r = 1; if (x < 64) { r = 0; if (y >= 64) { } else { r = 1; } } return r; }

class DW4VC_364_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int vX(); };

extern "C" void Gap__Core__igMallocMemoryPool__vfunc_93(int *arg0, S *arg1, char *arg2, DW4VC_364_0 *arg3) {
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
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}

extern "C" {

int Gap__Core__igMallocMemoryPool__vfunc_94(void *arg0, void **arg1);
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

struct B8 { unsigned char x : 7; unsigned char flag : 1; };
struct Hdr { char pad0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char pad4[4]; unsigned int w0 : 12; unsigned int hi : 12; unsigned int w2 : 8; };
int Gap__Core__igMallocMemoryPool__vfunc_95(int arg0, char *arg1) {
    struct Hdr *h;

    if (arg1 == 0) {
        return -1;
    }
    h = (struct Hdr *)(arg1 - 4);
    if (((struct B8 *)(arg1 - 1))->flag == 1) {
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

}
