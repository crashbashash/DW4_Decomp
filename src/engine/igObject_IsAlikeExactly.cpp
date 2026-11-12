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
extern int g_igRefMetaField_metaObject[4];
extern int g_stringPool[4];
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

extern "C" struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p);

typedef struct CopyHeader { int vt; char pad[2]; unsigned char lo : 7; unsigned char hi : 1; unsigned char b7; } CopyHeader;
extern "C" CopyHeader *igObject_CopyConstructHeader(CopyHeader *arg0, CopyHeader *arg1);

/* Stamps the igObject vtable, runs igObject_InitHeader, then fills the header's allocator byte
 * (+7): with the object system active it is the result of the owning allocator's virtual slot 364
 * (the owner-derived encoded allocator index); otherwise zero. */
class DW4VC_364_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int vX(); };
extern "C" igObject *igObject_ConstructHeader(igObject *self);

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
extern "C" void Gap__Core__igObject__vfunc_00__002ff0a0(void);

/* Slot 1 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_01(void);

/* Slot 2 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_02(void);

/* Slot 3 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_03(void);

/* Slot 7 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_07(void);

extern "C" void Gap__Core__igObject__vfunc_08__002ff0f0(void);

/* Slot 4 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_04(void);

/* Slot 5 default: always 1. */
extern "C" int Gap__Core__igObject__vfunc_05(void);

/* Slot 6 default: always 1. */
extern "C" int Gap__Core__igObject__vfunc_06(void);

/* Slot 11 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_11(void);

/* Slot 9 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_09(void);

/* Slot 10 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_10(void);

/* Slot 12 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_12(void);

/* Slot 13 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_13(void);

/* Slot 15 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_15(void);

/* Slot 14 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_14(void);

/* Slot 16 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_16(void);

/* Slot 17 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_17(void);

/* Slot 18 default: empty. */
extern "C" void Gap__Core__igObject__vfunc_18(void);

struct Lst { char pad[44]; int cnt; int list; };
class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual char vA();  };
class ConstructedObject { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void v9(int); virtual void d8(); virtual void v11(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual Lst *v22(); union { int w4; struct { unsigned cnt:23; unsigned f:9; } b; struct { unsigned char b0; unsigned char b1; unsigned char lo:7; unsigned char hi:1; unsigned char id; } c; } u; };
extern "C" void igObject_Construct(ConstructedObject *arg0, char *arg1);

class G { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual unsigned char vX(); };
struct PooledHeader { int w0; unsigned refs : 23; unsigned flag : 1; unsigned rest : 8; };
extern "C" void igObject_ConstructPooled(PooledHeader *arg0, char *arg1);

extern "C" void igObject_RegisterInstance(void **arg0, void *arg1);

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass
 * by igObject_Register): allocate a 12-byte callback array from the metadata allocator selector
 * and construct it empty. Returns the array, or 0 when the allocation fails. */
extern "C" int igObject_CreateEmptyInitCallbacks(void);

extern "C" void *igObject_GetNoParentMetaObject(void);

extern "C" int igObject_GetVTable(void);

extern "C" void igObject_EnsureRegistered(void);

extern "C" void *igObject_Register(void);

extern "C" void *igObject_GetMetaObject(void);

extern "C" void igObject_InitFields(void);

/* Storage for a new object. Reserves size + prefix_size bytes from the given allocator, falls back
 * to the default allocator (looked up by selector) when none is passed, and to the global heap
 * when there is no allocator at all. It returns the address prefix_size bytes into the block, so a
 * header can precede the object. The allocator method called is vtable offset 216 (vfunc_54), the
 * allocate-bytes slot. */
/* matching construct: dummy-virtual allocator class; only vtable offset 216 (vfunc_54) is called */
class DW4VC_216_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *vX(int); };
extern "C" char *igObject_AllocateRawStorage(int size, int prefix_size, void **requested_allocator);

extern "C" void *igObject_AllocateRawStorageDefault(int size,int prefix);

extern "C" int thunk_FUN_002ed460__002ff810();

extern "C" void igObject_Destroy(void *input);

class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }
extern "C" void igObject_ZeroFields(void **arg0);

class DW4VC_124_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
extern "C" void igObject_ConstructFields(void **arg0);

struct List { char pad[8]; int *data; int count; };
struct ResetMeta { char pad[40]; List *f40; };
class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual ResetMeta * vX(); };
class V52 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void vX(int); };
extern "C" void igObject_ResetFields(void **arg0);

class DW4VC_240_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual int vX(); };
extern "C" void igObject_ResetUnconstructedFields(void **arg0);

class MetaSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int *vX(); };
class DestructSelf { public: virtual void d0(); virtual void d1(); virtual void vX(); };
class DestructField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int *); };
struct DestructFieldList { int p0; int p1; DestructField **data; int count; };
extern "C" void igObject_DestructFieldValues(int *arg0);

class ClearField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(int *); };
struct ClearFieldList { int p0; int p1; ClearField **data; int count; };
extern "C" void igObject_ClearFieldValues(int *arg0);

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
extern "C" int igObject_GetSerializedSize(SizeObject *arg0);

struct WriteMeta { char p[25]; unsigned char persistent; char p26[38]; void *(*getter)(); };
struct FI { char p[37]; unsigned char f37; unsigned char f38; };
class O { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void v56(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual WriteMeta *v88(); };
extern "C" int igObject_WritePersistentFields(O * arg0, int * arg1, int arg2, void * r3, void * r4);

struct ReadField { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(void*); };
struct Dat { char p0[4]; int f4; int f8; short s12; };
struct ReadObject { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual igMetaObject* v20(); };
extern "C" int FUN_002fff90(ReadObject *arg0, Dat *arg1, int arg2, int arg3, int arg4);

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
extern "C" int FUN_00300250(FieldObjectView *object, FieldRecordHead *head, FieldDirView *dir, int unused, int swap);

class DW4VC_88_meta { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual igMetaObject * vX(); };
class DW4VC_164_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int, int); };
extern "C" void FUN_00300490(void **arg0, int arg1, int arg2);

extern "C" void FUN_00300600(void **arg0, int arg1);

extern "C" void FUN_003006a0(void **arg0, void **arg1);

struct ShallowFields { int pad[2]; int *arr; int count; };
struct ShallowHolder { char pad[40]; ShallowFields *meta; };
struct ShallowObject { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void v4(int); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual ShallowHolder *v20();  };
extern "C" void FUN_00300770(ShallowObject *arg0, int arg1);

struct DeepFieldList { int p0, p1; int *items; int count; };
struct DeepMeta { char pad[40]; DeepFieldList *fields; };
class DeepObject {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual int v5(DeepObject *);
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual DeepMeta *v20();
};
extern "C" int igObject_IsAlikeDeep(DeepObject *a, DeepObject *b);

struct M { char pad[8]; int *f8; int f12; };
struct W { char pad[40]; M *f40; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual int v32(V *); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual W *v88(); };
extern "C" int igObject_IsAlikeShallow(V *arg0, V *arg1);

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
extern "C" void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context);

extern "C" void FUN_00300c00(int arg0, int arg1, int arg2);

/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot), creates an instance of that class on the source's own allocator and copies
 * the contents across. `copyMode` is passed to the contents copy unchanged (the copy dispatches on
 * 0, 1 and 2). */
extern "C" int igObject_CloneViaMetadata(void **source, int copyMode);

/* Class-membership test: asks `object` for its metaobject (virtual slot 20) and walks the
 * metaobject's `_parent` chain looking for `kind`. Returns 1 when `kind` is the object's own class
 * or one of its ancestors, else 0. The accessor is called with `kind` still in the second argument
 * register; slot 20 has no use for it. */
/* Stand-in for the object's vtable: vX is slot 20, the metaobject accessor. */
class KindVC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(int); };
extern "C" int igObject_IsKindOf(void *object, igMetaObject *kind);

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
extern "C" void *igObject_GetAllocationBase(void *self);

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
extern "C" int igObject_AllocateStorage(int object, int size);

extern "C" int FUN_00300db0(int object, int size, int alignment);

extern "C" int FUN_00300e00(int object, int size, int option);

extern "C" int FUN_00300e50(int object, int storage, int size);

extern "C" int FUN_00300ea0(int object, int storage, int size, int alignment);

/* A null storage pointer returns without touching the allocator */
extern "C" void igObject_FreeStorage(int object, int storage);

/* Same instruction body as igObject_FreeStorage. */
extern "C" void FUN_00300f50(int object, int storage);

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, igObject_AllocateStorage), strcpy into it and return the
 * copy. */
extern "C" int igObject_DuplicateString(int self, int string);

extern "C" Allocator *igObject_GetAllocator(int a0);

struct ClonedObject : public igObject { };
class CloneSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual ClonedObject *v84(int); };
extern "C" igSmartPointer<ClonedObject> FUN_00301010(CloneSource *arg1, int arg2);
