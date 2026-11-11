#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

class igObjectDispatchView {
public:
    virtual void slot_00(); virtual void slot_01(); virtual void slot_02();
    virtual void slot_03(); virtual void slot_04(); virtual void slot_05();
    virtual void slot_06(); virtual void slot_07(); virtual void slot_08();
    virtual void slot_09(); virtual void slot_10(); virtual void slot_11();
    virtual void slot_12(); virtual void slot_13(); virtual void slot_14();
    virtual void slot_15(); virtual void slot_16(); virtual void slot_17();
    virtual void slot_18(); virtual void slot_19();
    virtual igMetaObject *slot_20();
};

/* RESERVED(n) declares unused virtual slot n so the named slots land on the
 * right byte offsets. */
#define RESERVED(n) virtual void reserved_##n()
/* Observed ABI view of the allocator vtable byte offsets the storage helpers call through, not an
 * original type; it is never instantiated. Only slots 216 (AllocateStorage) and 264 (FreeStorage)
 * are named by the original symbols; the other slots keep their byte offset. */
class Allocator {
public:
    /* The first two vtable words are the class header, so slot n sits at byte
     * offset 8 + 4 * n (slot 52 = +216). */
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4);
    RESERVED(5); RESERVED(6); RESERVED(7); RESERVED(8); RESERVED(9);
    RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13); RESERVED(14);
    RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19);
    RESERVED(20); RESERVED(21); RESERVED(22); RESERVED(23); RESERVED(24);
    RESERVED(25); RESERVED(26); RESERVED(27); RESERVED(28); RESERVED(29);
    RESERVED(30); RESERVED(31); RESERVED(32); RESERVED(33); RESERVED(34);
    RESERVED(35); RESERVED(36); RESERVED(37); RESERVED(38); RESERVED(39);
    RESERVED(40); RESERVED(41); RESERVED(42); RESERVED(43); RESERVED(44);
    RESERVED(45); RESERVED(46); RESERVED(47); RESERVED(48); RESERVED(49);
    RESERVED(50); RESERVED(51);
    virtual int allocate_storage(int size);                                   /* +216 */
    virtual int slot_220(int size, int alignment);                            /* +220: callers pass 0x10/0x80 */
    virtual int slot_224(int size, int option);                               /* +224: metadata default storage passes 1 */
    RESERVED(55);                                                             /* +228 */
    virtual int slot_232(int storage, int size);                              /* +232: callers pass (old storage, size) */
    virtual int slot_236(int storage, int size, int alignment);               /* +236: callers pass 0x80 */
    RESERVED(58); RESERVED(59); RESERVED(60); RESERVED(61); RESERVED(62);     /* +240..+260 */
    RESERVED(63);
    virtual void free_storage(int storage);                                   /* +264 */
};

/* Byte-swapping descriptor of a metafield type: slot 50 swaps `count` words in place. */
class SwapDescriptor { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
 virtual void Swap(void *, int);
};

struct ObjectHeader { int *vt; unsigned refs : 23; unsigned flag : 1; unsigned char b7; };

class DW4VC_12_1 { public: virtual void d0(); virtual int vX(int); };
class DW4VC_20_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual int vX(int); };
class DW4VC_36_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual int vX(int); };
class DW4VC_52_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual int vX(int); };
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
class DW4VC_80_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual int vX(); };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };

extern "C" {
int strcpy(...);
int strlen(...);
int sprintf(...);
char *malloc(int);
int Memory_FreeBuffer(...);
int Memory_AllocateBufferDirect(...);
void **Memory_GetAllocatorBySelector(...);
void *Memory_FindOwningAllocator(...);
char igAllocator_EncodeIndex(...);
Allocator *igAllocator_ResolveEncodedIndex(int);
int igArray_Construct(...);
int ObjectPointerList_Append(...);
void ObjectPointerList_EraseAt(void *,int);
int ObjectPointerList_FindIndex(void *,void *);
int FUN_002eb010(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int StringChunk_ReleaseHeader(...);
int igMetaField_WritePersistentValue(...);
int FUN_002fc740(...);
int FUN_002fc780(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int FUN_002fe600(...);
void igMetaObject_RunStaticInit(void *(*)(void));
void *igMetaObject_RegisterClass(...);
int igMetaObject_FinalizeAndAppendField(...);
int igMetaObject_CreateInstance(...);
int igMetaField_SetFieldName(...);
int igMetaField_Reset(...);
int igMetaField_ConstructCopy(...);
int igMetaField_DeepCopy(...);
int igMetaField_ShallowCopy(...);
int igMetaField_IsAlikeDeep(...);
int igMetaField_IsAlikeShallow(...);
int igMetaField_IsAlikeExactly(...);
igUnsignedIntMetaField *igUnsignedIntMetaField_Create(...);
SwapDescriptor *igIntMetaField_GetDefaultDescriptor();
SwapDescriptor *igShortMetaField_GetDefaultDescriptor();
int FUN_00304430(...);
int FUN_00304680(...);

extern int g_igObject_vtable[4];
/* object-system runtime pointer; byte 0 is the "object system active" flag */
extern unsigned char *g_objectSystem[4];
extern igMetaObject *g_igObject_metaObject[4];
/* Allocator selector used for metadata objects (queried here and before every
 * igMetaObject_Create). */
extern int g_metadataAllocatorKey[4];
/* Selector word the provider is queried with when no allocator is passed. */
extern int g_allocatorSelector[4];
extern char igObject_className[];
extern int DAT_004faf40[4];
extern int DAT_004faf50[4];
extern int DAT_004faf60[4];
extern int DAT_004faf78[4];
extern int DAT_004faf80[4];
extern int DAT_004faf88[4];
extern int DAT_00585a60[4];
extern int DAT_00586f20[4];
extern int DAT_005871a0[4];
extern int DAT_005871a8[4];

struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p);
int igObject_CreateEmptyInitCallbacks(void);
void *igObject_GetNoParentMetaObject(void);
int igObject_GetVTable(void);
void *igObject_Register(void);
void *igObject_GetMetaObject(void);
void igObject_InitFields(void);
char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator);
void igObject_Destroy(void *);
void igObject_ZeroFields(void **arg0);
void igObject_ConstructFields(void **arg0);
void igObject_ResetUnconstructedFields(void **arg0);
void igObject_DestructFieldValues(int *arg0);
void igObject_ClearFieldValues(int *arg0);
int igObject_IsKindOf(void *object, igMetaObject *kind);
void *igObject_GetAllocationBase(void *self);
int igObject_AllocateStorage(int object, int size);
void FUN_00300f50(int object, int storage);
Allocator *igObject_GetAllocator(int object);
}

extern "C" struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p) {
    p->vt = &g_igObject_vtable[0];
    p->refs = 1;
    p->flag = 0;
    p->b7 = 0;
    return p;
}

typedef struct CopyHeader { int vt; char pad[2]; unsigned char lo : 7; unsigned char hi : 1; unsigned char b7; } CopyHeader;
extern "C" CopyHeader *igObject_CopyConstructHeader(CopyHeader *arg0, CopyHeader *arg1) {
    arg0->vt = (int)&g_igObject_vtable[0];
    if (arg0 != 0) {
        igObject_InitHeader((ObjectHeader *)arg0);
    }
    arg0->hi = arg1->hi;
    if (*g_objectSystem[0] != 0) {
        arg0->b7 = igAllocator_EncodeIndex(Memory_FindOwningAllocator(igObject_GetAllocationBase(arg0)));
    }
    return arg0;
}

/* Stamps the igObject vtable, runs igObject_InitHeader, then fills the header's allocator byte
 * (+7): with the object system active it is the result of the owning allocator's virtual slot 364
 * (the owner-derived encoded allocator index); otherwise zero. */
class DW4VC_364_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int vX(); };
extern "C" igObject *igObject_ConstructHeader(igObject *self) {
    void **owner;

    self->_vtable = (int)(&g_igObject_vtable[0]);
    if (self != 0) {
        igObject_InitHeader((ObjectHeader *)self);
    }
    if (*g_objectSystem[0] != 0) {
        owner = (void **)(Memory_FindOwningAllocator(igObject_GetAllocationBase(self)));
        if (owner != 0) {
            *(unsigned char *)((char *)(self) + 7) = ((DW4VC_364_0 *)(owner))->vX();
        } else {
            *(unsigned char *)((char *)(self) + 7) = 0;
        }
    } else {
        *(unsigned char *)((char *)(self) + 7) = 0;
    }
    return self;
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
extern "C" void Gap__Core__igObject__vfunc_00__002ff0a0(void)
{
}

/* Slot 1 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_01(void)
{
}

/* Slot 2 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_02(void)
{
}

/* Slot 3 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_03(void)
{
}

/* Slot 7 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_07(void)
{
}

extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(void)
{
}

/* Slot 4 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_04(void)
{
}

/* Slot 5 default: always 1. */
extern "C" int Gap__Core__igObject__vfunc_05(void)
{
    return 1;
}

/* Slot 6 default: always 1. */
extern "C" int Gap__Core__igObject__vfunc_06(void)
{
    return 1;
}

/* Slot 11 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_11(void)
{
}

/* Slot 9 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_09(void)
{
}

/* Slot 10 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_10(void)
{
}

/* Slot 12 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_12(void)
{
}

/* Slot 13 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_13(void)
{
}

/* Slot 15 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_15(void)
{
}

/* Slot 14 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_14(void)
{
}

/* Slot 16 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_16(void)
{
}

/* Slot 17 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_17(void)
{
}

/* Slot 18 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_18(void)
{
}

struct Lst { char pad[44]; int cnt; int list; };
class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual char vA();  };
class ConstructedObject { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void v9(int); virtual void d8(); virtual void v11(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual Lst *v22(); union { int w4; struct { unsigned cnt:23; unsigned f:9; } b; struct { unsigned char b0; unsigned char b1; unsigned char lo:7; unsigned char hi:1; unsigned char id; } c; } u; };
extern "C" void igObject_Construct(ConstructedObject *arg0, char *arg1) {
    Alloc *a;
    Lst *l;
    *(int *)((char *)arg0 + *(int *)((char *)g_objectSystem[0] + 916)) = *(int *)(arg1 + 92);
    arg0->u.w4 = 0;
    arg0->u.b.cnt = 1;
    arg0->u.c.hi = 0;
    a = (Alloc *)Memory_FindOwningAllocator(igObject_GetAllocationBase(arg0));
    if (a != 0) {
        arg0->u.c.id = a->vA();
    } else {
        arg0->u.c.id = 0;
    }
    igObject_ZeroFields((void **)arg0);
    igObject_ConstructFields((void **)arg0);
    igObject_ResetUnconstructedFields((void **)arg0);
    arg0->v11();
    arg0->v9(0);
    l = arg0->v22();
    if (l != 0) {
        l->cnt = l->cnt + 1;
        if (l->list != 0) {
            ObjectPointerList_Append(l->list, arg0);
        }
    }
}

class G { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual unsigned char vX(); };
struct PooledHeader { int w0; unsigned refs : 23; unsigned flag : 1; unsigned rest : 8; };
extern "C" void igObject_ConstructPooled(PooledHeader *arg0, char *arg1) {
    G *g;

    *(int *)((char *)arg0 + *(int *)((char *)(g_objectSystem[0]) + 916)) = *(int *)(arg1 + 92);
    arg0->refs = 1;
    arg0->flag = 0 & 1;
    g = (G *)Memory_FindOwningAllocator(igObject_GetAllocationBase(arg0));
    if (g != 0) {
        arg0->rest = g->vX();
    } else {
        arg0->rest = 0;
    }
    igObject_ZeroFields((void **)arg0);
}

extern "C" void igObject_RegisterInstance(void **arg0, void *arg1) {
    int temp_a0;
    void *temp_v0;

    if ((arg1 != 0) && (*(int *)((char *)(arg1) + 60) != 0)) {
        ((DW4VC_80_0 *)(arg0))->vX();
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(0));
    ((DW4VC_52_1 *)(arg0))->vX((int)(0));
    ((DW4VC_36_1 *)(arg0))->vX((int)(1));
    temp_v0 = (void *)(((DW4VC_88_0 *)(arg0))->vX());
    if (temp_v0 != 0) {
        *(int *)((char *)(temp_v0) + 44) = (int)((int) (*(int *)((char *)(temp_v0) + 44) + 1));
        temp_a0 = *(int *)((char *)(temp_v0) + 48);
        if (temp_a0 != 0) {
            ObjectPointerList_Append(temp_a0, arg0);
        }
    }
}

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass
 * by igObject_Register): allocate a 12-byte callback array from the metadata allocator selector
 * and construct it empty. Returns the array, or 0 when the allocation fails. */
extern "C" int igObject_CreateEmptyInitCallbacks(void) {
    int callbacks;

    callbacks = Memory_AllocateBufferDirect(0xC, Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    if (callbacks != 0) {
        callbacks = igArray_Construct(callbacks);
    }
    return callbacks;
}

extern "C" void *igObject_GetNoParentMetaObject(void){return 0;}

extern "C" int igObject_GetVTable(void) {
    int o[2];

    igObject_InitHeader((ObjectHeader *)o);
    return *(int *)((char *)o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

extern "C" void igObject_EnsureRegistered(void){igMetaObject_RunStaticInit(igObject_Register);}

extern "C" void *igObject_Register(void) {
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObject_metaObject,
        igObject_CreateEmptyInitCallbacks,
        igObject_GetNoParentMetaObject,
        igObject_GetMetaObject,
        igObject_className,
        8, /* instance size */
        igObject_GetVTable,
        &igObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

extern "C" void *igObject_GetMetaObject(void){return (void *)g_igObject_metaObject[0];}

extern "C" void igObject_InitFields(void) {
    void *sp2C;
    void *sp28;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0_2;
    int temp_v0_4;
    int var_v0_2;
    int var_v0_4;
    igUnsignedIntMetaField *temp_v0;
    igUnsignedIntMetaField *temp_v0_3;
    void *var_v0;
    void *var_v0_3;

    temp_v0 = igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    temp_v0->_offset = 4;
    temp_v0->_externalEnumStorage = (int)(&DAT_005871a0[0]);
    if (&DAT_004faf40[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_2 = FUN_002eb010(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            DAT_00586f20[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004faf40[0]));
    }
    sp2C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_v0, &sp2C);
    if (sp2C != 0) {
        temp_a1 = (int *)((char *)sp2C - 8);
        temp_v0_2 = *(int *)((char *)(sp2C) - 4) - 1;
        *(int *)((char *)(sp2C) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    temp_v0->_persistent = 0;
    temp_v0->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0);
    temp_v0->_refCount = (int)temp_v0->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    temp_v0_3 = igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    temp_v0_3->_offset = 4;
    temp_v0_3->_externalEnumStorage = (int)(&DAT_005871a8[0]);
    if (&DAT_004faf50[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0_4 = FUN_002eb010(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            DAT_00586f20[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(DAT_00586f20[0], &DAT_004faf50[0]));
    }
    sp28 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_v0_3, &sp28);
    if (sp28 != 0) {
        temp_a1_2 = (int *)((char *)sp28 - 8);
        temp_v0_4 = *(int *)((char *)(sp28) - 4) - 1;
        *(int *)((char *)(sp28) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    temp_v0_3->_persistent = 0;
    temp_v0_3->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0_3);
    temp_v0_3->_refCount = (int)temp_v0_3->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0_3->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_3);
    }
}

/* Storage for a new object. Reserves size + prefix_size bytes from the given allocator, falls back
 * to the default allocator (looked up by selector) when none is passed, and to the global heap
 * when there is no allocator at all. It returns the address prefix_size bytes into the block, so a
 * header can precede the object. The allocator method called is vtable offset 216 (vfunc_54), the
 * allocate-bytes slot. */
/* matching construct: dummy-virtual allocator class; only vtable offset 216 (vfunc_54) is called */
class DW4VC_216_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *vX(int); };
extern "C" char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator) {
    int total_size;
    void **allocator;

    allocator = requested_allocator;
    total_size = size + prefix_size;
    if (allocator == 0) {
        allocator = (void **)Memory_GetAllocatorBySelector(g_allocatorSelector[0]);
    }
    if (allocator == 0) {
        /* no allocator at all: the prefix is not added on this path (retail behaviour) */
        return malloc(total_size);
    }
    return ((DW4VC_216_2 *)allocator)->vX(total_size) + prefix_size;
}

extern "C" void *igObject_AllocateRawStorageDefault(int size,int prefix){return igObject_AllocateRawStorage(size,prefix,0);}

extern "C" int thunk_FUN_002ed460__002ff810()
{
    return Memory_FreeBuffer();
}

extern "C" void igObject_Destroy(void *input){
    igObjectDispatchView *object;
    igMetaObject *type;
    void *instances;
    if(g_objectSystem[0]){
        unsigned char mode=*g_objectSystem[0];
        /* matching construct: hand search — the copy is taken after the mode load; taken at the top of the function it moves into the null-system branch's delay slot */
        object=(igObjectDispatchView *)input;
        if(!mode){
            object->slot_08();object->slot_10();object->slot_00();
            Memory_FreeBuffer(object);return;
        }
        type=object->slot_20();
        type->_instanceCount=(int)((unsigned)type->_instanceCount-1);
        instances=(void *)type->_instances;
        if(instances)ObjectPointerList_EraseAt(instances,ObjectPointerList_FindIndex(instances,object));
        object->slot_16();object->slot_08();object->slot_10();
        igObject_DestructFieldValues((int *)object);igObject_ClearFieldValues((int *)object);
        Memory_FreeBuffer(igObject_GetAllocationBase(object));
    }
}

class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }
extern "C" void igObject_ZeroFields(void **arg0) {
    igMetaObject *temp_v0;
    int var_s3;
    void **temp_a0;
    void *temp_s1;
    int temp_s0;

    temp_v0 = (igMetaObject *)(((DW4VC_88_0 *)(arg0))->vX());
    if (((temp_v0 != 0) && isValid(temp_v0)) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 20) == 0) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 0) != 0)) {
        temp_s1 = (void *)(temp_v0->_metaFields);
        var_s3 = *(int *)((char *)(g_igObject_metaObject[0]->_metaFields) + 12);
        temp_s0 = *(int *)((char *)(temp_s1) + 12);
        for (; var_s3 < temp_s0; var_s3++) {
            temp_a0 = (void **)(*(int *)(*(int *)((char *)(temp_s1) + 8) + (var_s3 * 4)));
            ((DW4VC_132_1 *)(temp_a0))->vX((int)(arg0));
        }
    }
}

class DW4VC_124_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
extern "C" void igObject_ConstructFields(void **arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    char *meta;
    void **o;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    i = *(int *)((char *)(*(int *)((char *)(g_igObject_metaObject[0]) + 40)) + 12);
    n = *(int *)(meta + 12);
    while (i < n) {
        o = (void **)(*(int *)(*(int *)(meta + 8) + (i * 4)));
        ((DW4VC_124_1 *)(o))->vX((int)(arg0));
        i++;
    }
    ((DW4VC_12_1 *)(arg0))->vX((int)(1));
}

struct List { char pad[8]; int *data; int count; };
struct ResetMeta { char pad[40]; List *f40; };
class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual ResetMeta * vX(); };
class V52 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void vX(int); };
extern "C" void igObject_ResetFields(void **arg0) {
    /* matching construct: variant search — decl order [2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    List *temp_s2;
    int temp_s1;
    int var_s0;

    temp_s2 = ((V88 *)arg0)->vX()->f40;
    var_s0 = ((ResetMeta *)g_igObject_metaObject[0])->f40->count;
    temp_s1 = temp_s2->count;
    while (var_s0 < temp_s1) {
        igMetaField_Reset(temp_s2->data[var_s0], arg0);
        var_s0++;
    }
    ((V52 *)arg0)->vX(1);
}

class DW4VC_240_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual int vX(); };
extern "C" void igObject_ResetUnconstructedFields(void **arg0) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    char *meta;
    void **o;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    i = *(int *)((char *)(*(int *)((char *)(g_igObject_metaObject[0]) + 40)) + 12);
    n = *(int *)(meta + 12);
    while (i < n) {
        o = (void **)(*(int *)(*(int *)(meta + 8) + (i * 4)));
        if (((DW4VC_240_0 *)(o))->vX() == 0) {
            igMetaField_Reset(o, arg0);
        }
        i++;
    }
    ((DW4VC_52_1 *)(arg0))->vX((int)(1));
}

class MetaSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int *vX(); };
class DestructSelf { public: virtual void d0(); virtual void d1(); virtual void vX(); };
class DestructField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int *); };
struct DestructFieldList { int p0; int p1; DestructField **data; int count; };
extern "C" void igObject_DestructFieldValues(int *arg0) {
    DestructFieldList *q;
    int i;
    int n;

    ((DestructSelf *)arg0)->vX();
    q = (DestructFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((DestructFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

class ClearField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(int *); };
struct ClearFieldList { int p0; int p1; ClearField **data; int count; };
extern "C" void igObject_ClearFieldValues(int *arg0) {
    ClearFieldList *q;
    int i;
    int n;

    q = (ClearFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((ClearFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

struct SizeMeta;
struct SizeObject {
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
  virtual struct SizeMeta *GetMeta();
};
struct SizeMeta { char p0[25]; unsigned char b19; char p1[38]; SizeMeta *(*f40)(); };
struct SizeField {
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
  virtual int GetSize(SizeObject *o);
};
extern "C" int igObject_GetSerializedSize(SizeObject *arg0) {
    SizeMeta *m0 = arg0->GetMeta();
    SizeMeta *m;
    int size, i, n;
    SizeMeta *(*fp)();
    fp = m0->f40;
    if (fp != 0) { m = fp(); } else { m = m0; }
    if (m->b19 == 0) return 0;
    size = 8;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    n = igMetaObject_GetFieldCount(m);
    for (; i < n; i++) { size += ((SizeField *)igMetaObject_GetFieldAt(m, i))->GetSize(arg0); }
    return size;
}

struct WriteMeta { char p[25]; unsigned char persistent; char p26[38]; void *(*getter)(); };
struct FI { char p[37]; unsigned char f37; unsigned char f38; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void v56(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual WriteMeta *v88(); };
extern "C" int igObject_WritePersistentFields(O * arg0, int * arg1, int arg2, void * r3, void * r4) {
    int arg3 = (int)r3;
    int arg4 = (int)r4;
    WriteMeta *m;
    int id;
    int i;
    FI *f;

    m = arg0->v88();
    if (m->persistent == 0) {
        return 0;
    }
    arg0->v56();
    id = 0;
    m = (m->getter != 0) ? (WriteMeta *)m->getter() : m;
    if (arg3 != 0) {
        id = FUN_002fe600(arg3, m);
    }
    arg3 = igMetaObject_GetFieldCount(m);
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    arg1[0] = id;
    id = i;
    arg1[1] = igObject_GetSerializedSize((SizeObject *)arg0);
    if (arg4 != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(arg1, 2);
    }
    arg1 += 2;
    for (; id < arg3; id++) {
        f = (FI *)igMetaObject_GetFieldAt(m, id);
        if (f->f38 == 1 && f->f37 == 0) {
            arg1 = (int *)((char *)arg1 + igMetaField_WritePersistentValue(f, arg0, arg1, arg2, arg4));
        }
    }
    return igObject_GetSerializedSize((SizeObject *)arg0);
}

struct ReadField { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(void*); };
struct Dat { char p0[4]; int f4; int f8; short s12; };
struct ReadObject { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual igMetaObject* v20(); };
extern "C" int FUN_002fff90(ReadObject *arg0, Dat *arg1, int arg2, int arg3, int arg4) {
    igMetaObject *m;
    char *s2;
    int s1;
    int cnt;
    int s6, s7;
    igMetaField *f;
    m = arg0->v20();
    if (m->_persistent == 0) return 0;
    if (arg4 != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(arg1, 3);
    }
    s2 = (char *)arg1 + 12;
    s1 = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    cnt = igMetaObject_GetFieldCount(m);
    s6 = 0;
    s7 = 0;
    for (; s1 < cnt; s1++) {
        f = (igMetaField *)igMetaObject_GetFieldAt(m, s1);
        if (f->_isRunTime != 0) {
            s6 += 1;
            ((ReadField *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (igMetaObject *)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else if (s7 >= arg1->f8) {
            ((ReadField *)f)->v29(arg0);
            if (igObject_IsKindOf(f, (igMetaObject *)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
        } else {
            if (arg4 != 0) igShortMetaField_GetDefaultDescriptor()->Swap(s2, 2);
            if (s1 < *(short *)s2 + s6) {
                ((ReadField *)f)->v29(arg0);
                if (igObject_IsKindOf(f, (igMetaObject *)DAT_00585a60[0]) == 0 || *(unsigned char *)((char *)f + 52) == 0) igMetaField_Reset(f, arg0);
                if (arg4 != 0) igShortMetaField_GetDefaultDescriptor()->Swap(s2, 2);
            } else {
                s7 += 1;
                s2 += FUN_002fc740(f, arg0, s2, arg2, arg4);
            }
        }
    }
    {
        int r = arg1->f4;
        if (arg4 != 0) igIntMetaField_GetDefaultDescriptor()->Swap(arg1, 3);
        arg0->v14();
        return r;
    }
}

struct FieldMetaView { char pad[25]; unsigned char _persistent; };
class FieldObjectView { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
 virtual void Finish();
 virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
 virtual FieldMetaView *Meta();
};
class FieldEntryView { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual void Prepare(FieldObjectView *);
 char pad[48]; unsigned char _skipReset;
};
struct FieldOffsetList { char pad[8]; int count; int cap; short *data; };
struct FieldListTable { char pad[16]; FieldOffsetList **data; };
struct FieldDirView { char pad[60]; FieldListTable *lists; };
struct FieldRecordHead { int kind; int size; };
extern "C" int FUN_00300250(FieldObjectView *object, FieldRecordHead *head, FieldDirView *dir, int unused, int swap) {
    FieldMetaView *meta;
    FieldListTable *lists;
    FieldOffsetList *offsets;
    char *data;
    int i;
    int first;
    int count;
    int done;
    int next;
    short limit;
    FieldEntryView *field;
    int size;
    meta = object->Meta();
    if (meta->_persistent == 0) {
        return 0;
    }
    lists = dir->lists;
    if (swap != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(head, 2);
    }
    offsets = lists->data[head->kind];
    data = (char *)head + 8;
    first = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    count = igMetaObject_GetFieldCount(meta);
    done = 0;
    next = 0;
    if (offsets->count == 0) {
        limit = count;
    } else {
        limit = offsets->data[next++];
    }
    for (i = first; i < count; i++) {
        field = (FieldEntryView *)igMetaObject_GetFieldAt(meta, i);
        if (i < limit) {
            field->Prepare(object);
            if (igObject_IsKindOf(field, (igMetaObject *)DAT_00585a60[0]) == 0 || field->_skipReset == 0) {
                igMetaField_Reset(field, object);
            }
        } else {
            done++;
            data += FUN_002fc780(field, object, data, dir, swap);
            if (done == offsets->count) {
                limit = count;
            } else {
                limit = offsets->data[next++];
            }
        }
    }
    size = head->size;
    if (swap != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(head, 2);
    }
    object->Finish();
    return size;
}

class DW4VC_88_meta { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual igMetaObject * vX(); };
class DW4VC_164_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int, int); };
extern "C" void FUN_00300490(void **arg0, int arg1, int arg2) {
    void **temp_a0;
    void *temp_s3;
    int temp_v0;
    unsigned int temp_s1;
    unsigned int var_s0;

    temp_s3 = (void *)(((DW4VC_88_meta *)(arg0))->vX()->_metaFields);
    FUN_00304430(&DAT_004faf60[0], arg2, arg0, ((DW4VC_88_meta *)(arg0))->vX()->_name);
    FUN_00304680();
    if (arg1 != 0) {
        temp_v0 = igObject_AllocateStorage((int)arg0, (strlen(arg2) + 2) * 4);
        sprintf(temp_v0, &DAT_004faf78[0], arg2);
        ((DW4VC_72_0 *)(arg0))->vX();
        temp_s1 = *(int *)((char *)(temp_s3) + 12);
        var_s0 = *(int *)((char *)(g_igObject_metaObject[0]->_metaFields) + 12);
        FUN_00304430(&DAT_004faf80[0], arg2);
        FUN_00304680();
        for (; var_s0 < temp_s1; var_s0++) {
            int *base = *(int **)((char *)(temp_s3) + 8);
            temp_a0 = (void **)base[var_s0];
            { int d = arg1 - 1; ((DW4VC_164_3 *)(temp_a0))->vX((int)(arg0), d, (int)(temp_v0)); }
        }
        FUN_00304430(&DAT_004faf88[0], arg2);
        FUN_00304680();
        FUN_00300f50((int)arg0, temp_v0);
    }
}

extern "C" void FUN_00300600(void **arg0, int arg1) {
    /* matching construct: variant search — decl order [2, 1, 0]; the declaration order of the locals sets their stack slot and register assignment */
    char *meta;
    int n;
    int i;

    meta = (char *)(*(int *)((char *)(((DW4VC_88_0 *)(arg0))->vX()) + 40));
    n = *(int *)(meta + 12);
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    while (i < n) {
        igMetaField_ConstructCopy(*(int *)(*(int *)(meta + 8) + (i * 4)), arg0, arg1);
        i++;
    }
}

extern "C" void FUN_003006a0(void **arg0, void **arg1) {
    void *temp_s0;
    void *temp_s2;
    int temp_s1;
    int var_s0;

    temp_s0 = (void *)(((DW4VC_88_0 *)(arg0))->vX());
    ((DW4VC_72_0 *)(arg0))->vX();
    ((DW4VC_72_0 *)(arg1))->vX();
    temp_s2 = (void *)(*(int *)((char *)(temp_s0) + 40));
    temp_s1 = *(int *)((char *)(temp_s2) + 12);
    var_s0 = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    for (; var_s0 < temp_s1; var_s0++) {
        igMetaField_DeepCopy(*(int *)(*(int *)((char *)(temp_s2) + 8) + (var_s0 * 4)), arg0, arg1);
    }
    ((DW4VC_20_1 *)(arg0))->vX((int)(arg1));
}

struct ShallowFields { int pad[2]; int *arr; int count; };
struct ShallowHolder { char pad[40]; ShallowFields *meta; };
struct ShallowObject { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void v4(int); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual ShallowHolder *v20();  };
extern "C" void FUN_00300770(ShallowObject *arg0, int arg1) {
    ShallowFields *m = arg0->v20()->meta;
    int n = m->count;
    int i;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < n; i++) {
        igMetaField_ShallowCopy(m->arr[i], arg0, arg1);
    }
    arg0->v4(arg1);
}

struct DeepFieldList { int p0, p1; int *items; int count; };
struct DeepMeta { char pad[40]; DeepFieldList *fields; };
class DeepObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual int v5(DeepObject *);
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual DeepMeta *v20();
};
extern "C" int igObject_IsAlikeDeep(DeepObject *a, DeepObject *b) {
    int i;
    DeepFieldList *fl;
    int n;
    if (b->v20() != a->v20()) return 0;
    fl = a->v20()->fields;
    n = fl->count;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    for (; i < n; i++) {
        if (igMetaField_IsAlikeDeep(fl->items[i], a, b) == 0) return 0;
    }
    return a->v5(b);
}

struct M { char pad[8]; int *f8; int f12; };
struct W { char pad[40]; M *f40; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual int v32(V *); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual W *v88(); };
extern "C" int igObject_IsAlikeShallow(V *arg0, V *arg1) {
    W *s0;
    int i;
    M *s1;
    int cnt;
    s0 = arg1->v88();
    if (s0 != arg0->v88()) {
        return 0;
    }
    s1 = arg0->v88()->f40;
    cnt = s1->f12;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < cnt; i++) {
        if (igMetaField_IsAlikeShallow(s1->f8[i], arg0, arg1) == 0) {
            return 0;
        }
    }
    return arg0->v32(arg1);
}

struct T { char pad8[8]; int *f8; int f12; };
struct K { char pad40[40]; T *f40; };
extern "C" int igObject_IsAlikeExactly(void *arg0, void *arg1) {
    int temp_s0;
    int i;
    T *temp_s1;
    int temp_s0_2;

    temp_s0 = ((DW4VC_88_0 *)arg1)->vX();
    if (temp_s0 != ((DW4VC_88_0 *)arg0)->vX()) {
        return 0;
    }
    temp_s1 = ((K *)((DW4VC_88_0 *)arg0)->vX())->f40;
    temp_s0_2 = temp_s1->f12;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < temp_s0_2; i++) {
        if (igMetaField_IsAlikeExactly(temp_s1->f8[i], arg0, arg1) == 0) {
            return 0;
        }
    }
    return 1;
}

/* Callback-driven object and field traversal; the virtual types project observed ABI slots. */
class VisitorObjectView {public:
virtual void o0();
virtual void o1();
virtual void o2();
virtual void o3();
virtual void o4();
virtual void o5();
virtual void o6();
virtual void o7();
virtual void o8();
virtual void o9();
virtual void o10();
virtual void o11();
virtual void o12();
virtual void o13();
virtual void o14();
virtual void o15();
virtual void Prepare();virtual void o76();virtual void o80();virtual void o84();virtual igMetaObject *Meta();};
typedef int (*Visitor)(void *,void *,void *);
class VisitorFieldView {public:
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
virtual void f6();
virtual void f7();
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
virtual void f16();
virtual void f17();
virtual void f18();
virtual void f19();
virtual void f20();
virtual void f21();
virtual void f22();
virtual void f23();
virtual void f24();
virtual void f25();
virtual void f26();
virtual void f27();
virtual void f28();
virtual void f29();
virtual void f30();
virtual void f31();
virtual void f32();
virtual void f33();
virtual void f34();
virtual void f35();
virtual void f36();
virtual void f37();
virtual void f38();
virtual void f39();
virtual void Visit(void *,Visitor,void *);};
struct FieldVector {int vt,refs;VisitorFieldView **data;int count;};
extern "C" void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context){
    FieldVector *fields;
    int count;
    int i;
    VisitorFieldView *field;
    if(callback(object,0,context)==1)return;
    object->Prepare();
    fields=(FieldVector *)object->Meta()->_metaFields;
    count=fields->count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);i<count;++i){
        field=fields->data[i];
        if(callback(object,field,context)!=1)field->Visit(object,callback,context);
    }
}

extern "C" void FUN_00300c00(int arg0, int arg1, int arg2) {
    switch (arg2) {
    case 1:
        FUN_003006a0((void **)arg0, (void **)arg1);
        break;
    case 0:
        FUN_00300770((ShallowObject *)arg0, arg1);
        break;
    case 2:
        FUN_00300600((void **)arg0, arg1);
        break;
    }
}

/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot), creates an instance of that class on the source's own allocator and copies
 * the contents across. `copyMode` is passed to the contents copy unchanged (the copy dispatches on
 * 0, 1 and 2). */
extern "C" int igObject_CloneViaMetadata(void **source, int copyMode) {
    int metaObject;
    int copy;

    metaObject = ((DW4VC_88_0 *)(source))->vX();
    copy = igMetaObject_CreateInstance(metaObject, igObject_GetAllocator((int)source));
    FUN_00300c00(copy, (int)source, copyMode);
    return copy;
}

/* Class-membership test: asks `object` for its metaobject (virtual slot 20) and walks the
 * metaobject's `_parent` chain looking for `kind`. Returns 1 when `kind` is the object's own class
 * or one of its ancestors, else 0. The accessor is called with `kind` still in the second argument
 * register; slot 20 has no use for it. */
/* Stand-in for the object's vtable: vX is slot 20, the metaobject accessor. */
class KindVC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(int); };
extern "C" int igObject_IsKindOf(void *object, igMetaObject *kind) {
    igMetaObject *meta = (igMetaObject *)((KindVC *)object)->vX((int)kind);
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

/* MetadataDispatchView declares observed byte slot 88; do not instantiate. */
class MetadataDispatchView { public:
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
virtual igMetaObject *GetMetadata(); };
extern "C" void *igObject_GetAllocationBase(void *self) {
    return (char *)self - ((MetadataDispatchView *)self)->GetMetadata()->_runTimeSize;
}

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
extern "C" int igObject_AllocateStorage(int object, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->allocate_storage(size);
}

extern "C" int FUN_00300db0(int object, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_220(size, alignment);
}

extern "C" int FUN_00300e00(int object, int size, int option) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_224(size, option);
}

extern "C" int FUN_00300e50(int object, int storage, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_232(storage, size);
}

extern "C" int FUN_00300ea0(int object, int storage, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_236(storage, size, alignment);
}

/* A null storage pointer returns without touching the allocator */
extern "C" void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Same instruction body as igObject_FreeStorage. */
extern "C" void FUN_00300f50(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, igObject_AllocateStorage), strcpy into it and return the
 * copy. */
extern "C" int igObject_DuplicateString(int self, int string) {
    int copy;

    copy = igObject_AllocateStorage(self, strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}

extern "C" Allocator *igObject_GetAllocator(int a0) {
    return igAllocator_ResolveEncodedIndex(*(unsigned char *)((char *)a0 + 7));
}

struct ClonedObject : public igObject { };
class CloneSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual ClonedObject *v84(int); };
extern "C" igSmartPointer<ClonedObject> FUN_00301010(CloneSource *arg1, int arg2) {
    igSmartPointer<ClonedObject> created(arg1->v84(arg2), kRetainReference);
    created.release();
    return created;
}
