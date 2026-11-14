#ifndef DW4_CORE_LIBRARY_H
#define DW4_CORE_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#include "dw4/igMemoryPoolView.h"
extern "C" {
#include "dw4/eekernel.h"
#define __extension__
#include "dw4/newlib_reent.h"
#undef __extension__
}

/* The allocator selector of each memory context, in the order of g_memoryContextNames: the program
 * constructs every one at start-up. */
struct igMemoryPoolHandle {
    int value;
    igMemoryPoolHandle(int v) : value(v) {}
    operator int() const { return value; }
};
extern "C" {
extern igMemoryPoolHandle kIGMemoryPoolHandleBootstrap;
extern igMemoryPoolHandle kIGMemoryPoolHandleDefault;
extern igMemoryPoolHandle kIGMemoryPoolHandleCurrent;
extern igMemoryPoolHandle kIGMemoryPoolHandleNonTracked;
extern igMemoryPoolHandle kIGMemoryPoolHandleSystem;
extern igMemoryPoolHandle kIGMemoryPoolHandleMetaData;
extern igMemoryPoolHandle kIGMemoryPoolHandleString;
extern igMemoryPoolHandle kIGMemoryPoolHandleFast;
extern igMemoryPoolHandle kIGMemoryPoolHandleList;
extern igMemoryPoolHandle kIGMemoryPoolHandleTemporary;
extern igMemoryPoolHandle kIGMemoryPoolHandleVertex;
extern igMemoryPoolHandle kIGMemoryPoolHandleRenderList;
extern igMemoryPoolHandle kIGMemoryPoolHandleTexture;
extern igMemoryPoolHandle kIGMemoryPoolHandleApplication;
extern igMemoryPoolHandle kIGMemoryPoolHandleWorld;
extern igMemoryPoolHandle kIGMemoryPoolHandleActor;
extern igMemoryPoolHandle kIGMemoryPoolHandleLevel;
extern igMemoryPoolHandle kIGMemoryPoolHandleFrame;
extern igMemoryPoolHandle kIGMemoryPoolHandlePhysics;
extern igMemoryPoolHandle kIGMemoryPoolHandleAI;
extern igMemoryPoolHandle kIGMemoryPoolHandleDriverData;
extern igMemoryPoolHandle kIGMemoryPoolHandleClut;
extern igMemoryPoolHandle kIGMemoryPoolHandleDMA;
extern igMemoryPoolHandle kIGMemoryPoolHandleAudio;
extern igMemoryPoolHandle kIGMemoryPoolHandleVideo;
extern igMemoryPoolHandle kIGMemoryPoolHandleHandles;
extern igMemoryPoolHandle kIGMemoryPoolHandleImage;
extern igMemoryPoolHandle kIGMemoryPoolHandleImageObject;
extern igMemoryPoolHandle kIGMemoryPoolHandleAttribute;
extern igMemoryPoolHandle kIGMemoryPoolHandleNode;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser0;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser1;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser2;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser3;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser4;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser5;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser6;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser7;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser8;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser9;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser10;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser11;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser12;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser13;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser14;
extern igMemoryPoolHandle kIGMemoryPoolHandleUser15;
}
#define POOL() { if (((void * *)g_stringPool)[0] == 0) { void *pool = StringPool_Allocate(0x10); if (pool != 0) pool = ((void *)StringPool_Construct((StringPool *)pool)); ((void * *)g_stringPool)[0] = pool; } }
#define BLOCK(ctor, strsrc) { \
    igSmartPointer<igFolder> candidate((igFolder *)ctor(((int)igObject_GetAllocator((int)arg0)))); \
    const char *src = strsrc; \
    igFolder *o = candidate.p; \
    POOL() \
    src = ((const char *)StringPool_Intern((StringPool *)(((void * *)g_stringPool)[0]), src)); \
    { const char *old = (const char *)o->_folderName; releaseString(old); o->_folderName = (int)src; } \
    s0 = openPath(arg0, ((igFolderView *)candidate.p)->vfunc_23(name.p)); \
    }
#include "dw4/igobject_release.h"
/* Releases a reference field through a copy, so the field is read once. */
#define RELEASE_REF(p) do { igObject *t_ = (igObject *)(p); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long)((long long)(int)t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } } while (0)
#define REF_COUNT_MASK 0x7fffff
#define PAD(n) virtual void pad##n();
#define EMIT(...) \
    do { \
        if (file) { file->Print(__VA_ARGS__); } \
        else { FUN_00304430(__VA_ARGS__); FUN_00304680(); } \
    } while (0)
#define V1(p) virtual void p();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##a) V4(p##b) V4(p##c) V4(p##d)
#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_RECORD_SIZE 0x90
#define CONTEXT_RECORDS_OFFSET 0x14
#define CONTEXT_RECORD_NAME_MAX 0x7F
#define ASSIGN_TOKEN(field, source)                                           \
    text = (source);                                                          \
    if ((*(void * *)g_stringPool) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        (*(void * *)g_stringPool) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), text));          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunkOwnerView *)header->owner, (int)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token
#define ASSIGN_TOKEN_DIRECT(field, source)                                           \
    if ((*(void * *)g_stringPool) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        (*(void * *)g_stringPool) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), (source)));          \
    old = (field);                                                            \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunkOwnerView *)header->owner, (int)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = token
#define NEW_LARGE_POOL(p) { p = newLargePool(); }
#define NEW_SMALL(p) { p = newSmallPool(); }
#define NEW_POOL(p) { if (DAT_00586de8 != 0) { if (strcmp(DAT_00586de8, igArenaMemoryPool_className) == 0) { NEW_LARGE_POOL(p) } else if (strcmp(DAT_00586de8, igMallocMemoryPool_className) == 0) { NEW_SMALL(p) } else { NEW_LARGE_POOL(p) } } else { NEW_LARGE_POOL(p) } }
#define CONTEXT_NAME_LIMIT 0x7F
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
#define RC2(o) ((unsigned long long)(long long)((igObject *)(o))->_refCount & 0x7fffffULL)
#define SETSTR(field) { \
    int v_; int s_; int old_; int *hd_; \
    if (g_stringPool[0] == 0) { \
        v_ = ((int)StringPool_Allocate(0x10)); \
        if (v_ != 0) v_ = ((int)StringPool_Construct((StringPool *)v_)); \
        g_stringPool[0] = v_; \
    } \
    s_ = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)0); \
    old_ = arg0->field; \
    if (old_ != 0) { \
        hd_ = (int *)(old_ - 8); \
        v_ = *(int *)(old_ - 4) - 1; \
        *(int *)(old_ - 4) = v_; \
        if (v_ == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hd_), (int)hd_); \
    } \
    arg0->field = s_; }
#define RESERVED(n) virtual void reserved_##n()
#define REL(o) if ((o) != 0) { (o)->_refCount = (int)(o)->_refCount - 1; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy((void *)o); } }
#define REL_O(p) { igObject *q_ = (igObject *)(p); if (q_) { q_->_refCount = q_->_refCount - 1; if (((unsigned long long)(long long)(int)q_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q_); } }
#define ASSIGN_O(o, fld, val) { igObject *n_ = (val); (o) = (igIGBFile *)file.p; if (n_ != 0) n_->_refCount = n_->_refCount + 1; REL_O((o)->fld) (o)->fld = (int)n_; }
#define OFF(p) (((struct LinkByte *)(p))->b7 == 0 ? 4 : 12)
#define NEXT(p) (*(int *)((char *)(p) + OFF(p) + 4))
#define PREV(p) (*(int *)((char *)(p) + OFF(p)))
#define VCALL(o, off) (*(PF *)(*(char **)(o) + (off)))
#define PAGE_POOL_ALIGNMENT 0x1000
#define TRACER_PAGE_SIZE 0x1000
#define TRACER_BLOCK_SIZE 0x10000
#define NANOSECONDS_PER_SECOND 0x3B9ACA00

extern "C" int __init_cpp(...);
extern "C" int __fini_cpp(...);
struct StringChunkOwnerView;
extern "C" void StringChunk_ReleaseHeader(StringChunkOwnerView *self, int header);
extern "C" void * StringPool_Allocate(int arg0);
/* 16-byte string intern pool (g_stringPool[0]). */
typedef struct StringPool {
    int table;      /* +0   StringTable (hash of interned strings) */
    int chunks;     /* +4   head StringChunk of the storage chain */
    int chunkSize;  /* +8   bytes per new chunk (0x4000) */
    int pool;       /* +12  igMemoryPool the table and chunks come from */
} StringPool;
extern "C" StringPool *StringPool_Construct(StringPool *arg0);
extern "C" void FUN_002b5d50(void);
extern "C" int igVirtualCFuncMetaField_GetVTable(void);
extern "C" void FUN_002b5e80(void);
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igVirtualCFuncMetaField_Register(void);
extern "C" void thunk_igVirtualCFuncMetaField_GetMetaObject(void);
extern "C" void FUN_002b5f10(void);
extern "C" void **FUN_002b5fe0(int arg0);
extern "C" int Gap__Core__igUnsignedShortMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igUnsignedShortMetaField_GetVTable(void);
extern "C" void FUN_002b61d0(void);
extern "C" void igUnsignedShortMetaField_Register(void);
extern "C" void thunk_igUnsignedShortMetaField_GetMetaObject(void);
extern "C" void FUN_002b6260(void);
extern "C" int FUN_002b6330(void);
extern "C" void FUN_002b6370(int arg0);
extern "C" int igUnsignedShortArrayMetaField_GetVTable(void);
extern "C" void FUN_002b6490(void);
extern "C" void igUnsignedShortArrayMetaField_Register(void);
extern "C" void thunk_igUnsignedShortArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b6530(void);
extern "C" void igUnsignedShortArrayMetaField_InitFields(void);
extern "C" void FUN_002b65d0(void);
extern "C" void **FUN_002b66a0(int arg0);
extern "C" int Gap__Core__igUnsignedLongMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igUnsignedLongMetaField_GetVTable(void);
extern "C" void FUN_002b6890(void);
extern "C" void igUnsignedLongMetaField_Register(void);
extern "C" void thunk_igUnsignedLongMetaField_GetMetaObject(void);
extern "C" void FUN_002b6920(void);
extern "C" int FUN_002b69f0(void);
extern "C" int igUnsignedLongArrayMetaField_GetVTable(void);
extern "C" void FUN_002b6b10(void);
extern "C" void igUnsignedLongArrayMetaField_Register(void);
extern "C" void thunk_igUnsignedLongArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b6bb0(void);
extern "C" void igUnsignedLongArrayMetaField_InitFields(void);
extern "C" void FUN_002b6c50(void);
extern "C" void **igUnsignedIntMetaField_Create(int allocator);
extern "C" int Gap__Core__igUnsignedIntMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igUnsignedIntMetaField_GetVTable(void);
extern "C" void igUnsignedIntMetaField_EnsureRegistered(void);
extern "C" void igUnsignedIntMetaField_Register(void);
extern "C" void thunk_igUnsignedIntMetaField_GetMetaObject(void);
extern "C" void FUN_002b6fa0(void);
extern "C" int igUnsignedIntMetaField_GetDefaultDescriptor(void);
extern "C" void FUN_002b70b0(int arg0);
extern "C" int igUnsignedIntArrayMetaField_GetVTable(void);
extern "C" void FUN_002b71d0(void);
extern "C" void igUnsignedIntArrayMetaField_Register(void);
extern "C" void thunk_igUnsignedIntArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b7270(void);
extern "C" void igUnsignedIntArrayMetaField_InitFields(void);
extern "C" void FUN_002b7310(void);
extern "C" void FUN_002b73e0(int arg0);
extern "C" int igUnsignedCharMetaField_GetVTable(void);
extern "C" void igUnsignedCharMetaField_EnsureRegistered(void);
extern "C" void igUnsignedCharMetaField_Register(void);
extern "C" void thunk_igUnsignedCharMetaField_GetMetaObject(void);
extern "C" void FUN_002b7590(void);
extern "C" int igUnsignedCharMetaField_GetDefaultDescriptor(void);
extern "C" int igObjectRefMetaField_GetDefaultDescriptor(void);
extern "C" int igObjectList_GetOrCreateMetaObject(void);
extern "C" int igIntMetaField_GetDefaultDescriptor(void);
extern "C" int igDataList_GetOrCreateMetaObject(void);
extern "C" int igIntList_GetOrCreateMetaObject(void);
extern "C" void FUN_002b76a0(int arg0);
extern "C" int igUnsignedCharArrayMetaField_GetVTable(void);
extern "C" void FUN_002b77c0(void);
extern "C" void igUnsignedCharArrayMetaField_Register(void);
extern "C" void thunk_igUnsignedCharArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b7860(void);
extern "C" void igUnsignedCharArrayMetaField_InitFields(void);
extern "C" void FUN_002b7900(void);
extern "C" void FUN_002b79d0(int arg0);
extern "C" igMetaObject *FUN_002b7a10(void);
extern "C" void FUN_002b7ab0(void);
extern "C" void igTimer_Register(void);
extern "C" void thunk_igTimer_GetMetaObject(void);
extern "C" void FUN_002b7b40(void);
extern "C" void thunk_FUN_002c1860(void);
extern "C" void * FUN_002b7b70(int arg0);
extern "C" void FUN_002b7c00(void);
extern "C" void igThreadManager_Register(void);
extern "C" void thunk_igThreadManager_GetMetaObject(void);
extern "C" void igThreadManager_InitFields(void);
extern "C" void thunk_igPsx2ThreadManager_GetMetaObject(void);
extern "C" void thunk_FUN_0030e480(void);
extern "C" void thunk_FUN_0030e540(void);
extern "C" int FUN_002b7dc0(void);
extern "C" int FUN_002b7e20(void);
extern "C" int FUN_002b7e80(void);
extern "C" int FUN_002b7ee0(void);
extern "C" void * FUN_002b7f40(int arg0);
extern "C" igMetaObject *FUN_002b7f80(void);
extern "C" void FUN_002b8020(void);
extern "C" void igThread_Register(void);
extern "C" void thunk_igThread_GetMetaObject(void);
extern "C" void igThread_InitFields(void);
extern "C" void thunk_igPsx2Thread_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b8220(void);
extern "C" int igNonRefCountedThreadList_GetVTable(void);
extern "C" void FUN_002b8300(void);
extern "C" void igNonRefCountedThreadList_Register(void);
extern "C" void thunk_igNonRefCountedThreadList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b8390(void);
extern "C" int igThreadList_GetVTable(void);
extern "C" void FUN_002b8470(void);
extern "C" void igThreadList_Register(void);
extern "C" void thunk_igThreadList_GetMetaObject(void);
extern "C" void * FUN_002b8500(int arg0);
extern "C" int igSymbolTable_GetVTable(void);
extern "C" int __dl__FPv(...);
extern "C" void **FUN_002b86c0(void **arg0, short arg1);
extern "C" void FUN_002b87c0(void);
extern "C" void igSymbolTable_Register(void);
extern "C" void thunk_igSymbolTable_GetMetaObject(void);
extern "C" void igSymbolTable_InitFields(void);
extern "C" void FUN_002b8990(int arg0);
extern "C" int igStructMetaField_GetVTable(void);
extern "C" void FUN_002b8ab0(void);
extern "C" void igStructMetaField_Register(void);
extern "C" void thunk_igStructMetaField_GetMetaObject(void);
extern "C" void FUN_002b8b50(void);
extern "C" void FUN_002b8c80(void);
extern "C" void FUN_002b8d50(int arg0);
extern "C" igMetaObject *FUN_002b8d90(void);
/* The destructor of an object-reference field, inlined through the field's address. */
static inline void ReleaseObjectField(int *slot) {
    if (slot) {
        igObject *object = (igObject *)*slot;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
    }
}
extern "C" int igStringTable_GetVTable(void);
extern "C" void FUN_002b8f90(void);
extern "C" void igStringTable_Register(void);
extern "C" void thunk_igStringTable_GetMetaObject(void);
extern "C" void igStringTable_InitFields(void);
extern "C" void * igStringRefList_Create(int arg0);
extern "C" igMetaObject *FUN_002b9120(void);
extern "C" int igStringRefList_GetVTable(void);
extern "C" void FUN_002b9200(void);
extern "C" void igStringRefList_Register(void);
extern "C" void thunk_igStringRefList_GetMetaObject(void);
extern "C" void FUN_002b9290(void);
extern "C" void * FUN_002b9350(int arg0);
extern "C" igMetaObject *FUN_002b9390(void);
extern "C" int igStringObjList_GetVTable(void);
extern "C" void FUN_002b9470(void);
extern "C" void igStringObjList_Register(void);
extern "C" void thunk_igStringObjList_GetMetaObject(void);
extern "C" void * igStringObj_Create(int arg0);
extern "C" igMetaObject *FUN_002b9540(void);
extern "C" int igStringObj_GetVTable(void);
extern "C" void FUN_002b9620(void);
extern "C" void igStringObj_Register(void);
extern "C" void thunk_igStringObj_GetMetaObject(void);
extern "C" void igStringObj_InitFields(void);
extern "C" void **igStringMetaField_Create(int allocator);
extern "C" void **igObjectRefMetaField_Create(int allocator);
extern "C" void **igIntMetaField_Create(int allocator);
extern "C" void igStringMetaField_InitDefaults(void **self);
extern "C" int Gap__Core__igStringMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igStringMetaField_GetVTable(void);
extern "C" void igStringMetaField_EnsureRegistered(void);
extern "C" void igStringMetaField_Register(void);
extern "C" void thunk_igStringMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b99d0(void);
extern "C" void igStringMetaField_InitFields(void);
extern "C" void FUN_002b9b90(void);
extern "C" int FUN_002b9c60(void);
extern "C" int igStringArrayMetaField_GetVTable(void);
extern "C" void FUN_002b9d80(void);
extern "C" void igStringArrayMetaField_Register(void);
extern "C" void thunk_igStringArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002b9e20(void);
extern "C" void igStringArrayMetaField_InitFields(void);
extern "C" void FUN_002b9ec0(void);
extern "C" void **FUN_002b9f90(int arg0);
extern "C" int Gap__Core__igShortMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igShortMetaField_GetVTable(void);
extern "C" void igShortMetaField_EnsureRegistered(void);
extern "C" void igShortMetaField_Register(void);
extern "C" void thunk_igShortMetaField_GetMetaObject(void);
extern "C" void FUN_002ba210(void);
extern "C" int igShortMetaField_GetDefaultDescriptor(void);
extern "C" void FUN_002ba320(int arg0);
extern "C" int igShortArrayMetaField_GetVTable(void);
extern "C" void FUN_002ba440(void);
extern "C" void igShortArrayMetaField_Register(void);
extern "C" void thunk_igShortArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002ba4e0(void);
extern "C" void igShortArrayMetaField_InitFields(void);
extern "C" void FUN_002ba580(void);
extern "C" void * FUN_002ba650(int arg0);
extern "C" igMetaObject *FUN_002ba690(void);
extern "C" void FUN_002ba730(void);
extern "C" void igSemaphore_Register(void);
extern "C" void thunk_igSemaphore_GetMetaObject(void);
extern "C" void FUN_002ba7c0(void);
extern "C" void thunk_igPsx2Semaphore_GetMetaObject(void);
extern "C" void **FUN_002ba870(void **arg0, int arg1);
extern "C" void **FUN_002ba8f0(void **arg0, short arg1);
extern "C" void FUN_002ba9f0(int arg0);
extern "C" igMetaObject *FUN_002baa30(void);
extern "C" int FUN_001432d0(...);
extern "C" int FUN_001509f0(...);
extern "C" int FUN_001a0790(...);
extern "C" int FUN_001d36d0(...);
extern "C" int ObjectRef_Destruct_00150eb0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int igResource_GetVTable(void);
extern "C" void **FUN_002bac40(void **arg0, long long arg1);
extern "C" void FUN_002bad40(void);
extern "C" void igResource_Register(void);
extern "C" void thunk_igResource_GetMetaObject(void);
extern "C" void igResource_InitFields(void);
extern "C" void * FUN_002baff0(int arg0);
extern "C" igMetaObject *FUN_002bb030(void);
extern "C" int igRegistry_GetVTable(void);
extern "C" void FUN_002bb200(void);
extern "C" void igRegistry_Register(void);
extern "C" void thunk_igRegistry_GetMetaObject(void);
extern "C" void igRegistry_InitFields(void);
extern "C" igMetaObject *FUN_002bb390(void);
extern "C" int igRegistryValueList_GetVTable(void);
extern "C" void FUN_002bb470(void);
extern "C" void igRegistryValueList_Register(void);
extern "C" void thunk_igRegistryValueList_GetMetaObject(void);
extern "C" void * FUN_002bb500(int arg0);
extern "C" int igRegistryValue_GetVTable(void);
extern "C" void FUN_002bb670(void);
extern "C" void igRegistryValue_Register(void);
extern "C" void thunk_igRegistryValue_GetMetaObject(void);
extern "C" void igRegistryValue_InitFields(void);
extern "C" void FUN_002bb830(void);
extern "C" void igRefMetaField_Register(void);
extern "C" void thunk_igRefMetaField_GetMetaObject(void);
extern "C" void igRefMetaField_InitFields(void);
extern "C" void FUN_002bb930(void);
extern "C" void **FUN_002bba00(int arg0);
extern "C" int Gap__Core__igRawRefMetaField__vfunc_21(int arg0, int arg1);
extern "C" igMetaObject *FUN_002bbb20(void);
extern "C" int igRawRefMetaField_GetVTable(void);
extern "C" void igRawRefMetaField_EnsureRegistered(void);
extern "C" void igRawRefMetaField_Register(void);
extern "C" void thunk_igRawRefMetaField_GetMetaObject(void);
extern "C" void FUN_002bbcd0(void);
extern "C" int igRawRefMetaField_GetDefaultDescriptor(void);
extern "C" int igRawRefArrayMetaField_GetVTable(void);
extern "C" void FUN_002bbec0(void);
extern "C" void igRawRefArrayMetaField_Register(void);
extern "C" void thunk_igRawRefArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002bbf60(void);
extern "C" void igRawRefArrayMetaField_InitFields(void);
extern "C" void FUN_002bc000(void);
extern "C" void * FUN_002bc0d0(int arg0);
extern "C" igMetaObject *FUN_002bc110(void);
extern "C" void FUN_002bc1b0(void);
extern "C" void igQueue_Register(void);
extern "C" void thunk_igQueue_GetMetaObject(void);
extern "C" void igQueue_InitFields(void);
extern "C" void thunk_igStandardQueue_GetMetaObject(void);
extern "C" void FUN_002bc300(int arg0);
extern "C" int igPluginHelper_GetVTable(void);
extern "C" void **FUN_002bc440(void **arg0, long long arg1);
extern "C" void **FUN_002bc4c0(void **arg0, short arg1);
extern "C" void FUN_002bc5c0(void);
extern "C" void igPluginHelper_Register(void);
extern "C" void thunk_igPluginHelper_GetMetaObject(void);
extern "C" void igPluginHelper_InitFields(void);
extern "C" igMetaObject *FUN_002bc760(void);
extern "C" int igPluginRepositoryList_GetVTable(void);
extern "C" void FUN_002bc840(void);
extern "C" void igPluginRepositoryList_Register(void);
extern "C" void thunk_igPluginRepositoryList_GetMetaObject(void);
extern "C" int FUN_002bc8d0(void);
extern "C" int FUN_002bc930(int arg0);
extern "C" int igPluginRepository_GetVTable(void);
extern "C" void FUN_002bca90(void);
extern "C" void igPluginRepository_Register(void);
extern "C" void thunk_igPluginRepository_GetMetaObject(void);
extern "C" void igPluginRepository_InitFields(void);
extern "C" igMetaObject *FUN_002bcbb0(void);
extern "C" int igObjectStringMap_GetVTable(void);
extern "C" void FUN_002bcd30(void);
extern "C" void igObjectStringMap_Register(void);
extern "C" void thunk_igObjectStringMap_GetMetaObject(void);
extern "C" void igObjectStringMap_InitFields(void);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igObjectRefMetaField_GetVTable(void);
extern "C" void igObjectRefMetaField_EnsureRegistered(void);
extern "C" void igObjectRefMetaField_Register(void);
extern "C" void thunk_igObjectRefMetaField_GetMetaObject(void);
extern "C" void igObjectRefMetaField_InitFields(void);
extern "C" void FUN_002bd210(void);
extern "C" void FUN_002bd320(int arg0);
extern "C" int igObjectRefArrayMetaField_GetVTable(void);
extern "C" void FUN_002bd470(void);
extern "C" void igObjectRefArrayMetaField_Register(void);
extern "C" void thunk_igObjectRefArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002bd510(void);
extern "C" void igObjectRefArrayMetaField_InitFields(void);
extern "C" void FUN_002bd5b0(void);
extern "C" void * FUN_002bd680(int arg0);
extern "C" int igObjectList_GetVTable(void);
extern "C" void igObjectList_EnsureRegistered(void);
extern "C" void *igObjectList_Register(void);
extern "C" void thunk_igObjectList_GetMetaObject(void);
extern "C" void igObjectList_InitFields(void);
extern "C" int FUN_002bd8f0(int arg0);
extern "C" int FUN_0019c840(...);
extern "C" int FUN_0014f4e0(...);
extern "C" int igObjectDirEntry_GetVTable(void);
extern "C" void FUN_002bda10(void);
extern "C" void igObjectDirEntry_Register(void);
extern "C" void thunk_igObjectDirEntry_GetMetaObject(void);
extern "C" igMetaObject *FUN_002bdab0(void);
extern "C" void igObjectDirEntry_InitFields(void);
extern "C" int igNonRefCountedObjectList_GetVTable(void);
extern "C" void FUN_002bdd30(void);
extern "C" void igNonRefCountedObjectList_Register(void);
extern "C" void thunk_igNonRefCountedObjectList_GetMetaObject(void);
extern "C" void FUN_002bddc0(void);
extern "C" int igNamedObjectInfo_GetVTable(void);
extern "C" void FUN_002bdfc0(void);
extern "C" void igNamedObjectInfo_Register(void);
extern "C" void thunk_igNamedObjectInfo_GetMetaObject(void);
extern "C" void igNamedObjectInfo_InitFields(void);
extern "C" igMetaObject *FUN_002be100(void);
extern "C" int igNamedObjectList_GetVTable(void);
extern "C" void FUN_002be1e0(void);
extern "C" void igNamedObjectList_Register(void);
extern "C" void thunk_igNamedObjectList_GetMetaObject(void);
extern "C" void * FUN_002be270(int arg0);
extern "C" igMetaObject *FUN_002be2b0(void);
extern "C" int igNamedObject_GetVTable(void);
extern "C" void FUN_002be3d0(void);
extern "C" void igNamedObject_Register(void);
extern "C" void thunk_igNamedObject_GetMetaObject(void);
extern "C" void igNamedObject_InitFields(void);
extern "C" void **igMetaObject_Create(int allocator);
extern "C" void *Gap__Core__igMetaObject__vfunc_21(int arg0, int arg1);
extern "C" igMetaObject *FUN_002be610(void);
extern "C" int igMetaObject_GetVTable(void);
extern "C" void igMetaObject_EnsureRegistered(void);
extern "C" void igMetaObject_Register(void);
extern "C" void thunk_igMetaObject_GetMetaObject(void);
extern "C" void igMetaObject_InitFields(void);
extern "C" void FUN_002bea90(int arg0);
extern "C" int igMetaFieldInfo_GetVTable(void);
extern "C" void FUN_002bebb0(void);
extern "C" void igMetaFieldInfo_Register(void);
extern "C" void thunk_igMetaFieldInfo_GetMetaObject(void);
extern "C" int FUN_002bec40(void);
extern "C" igMetaObject *FUN_002beca0(void);
extern "C" void FUN_002bed40(void);
extern "C" void igMetaField_Register(void);
extern "C" void thunk_igMetaField_GetMetaObject(void);
extern "C" void igMetaField_InitFields(void);
extern "C" void * FUN_002befe0(int arg0);
extern "C" int igMetaEnum_GetVTable(void);
extern "C" void FUN_002bf190(void);
extern "C" void igMetaEnum_Register(void);
extern "C" void thunk_igMetaEnum_GetMetaObject(void);
extern "C" void igMetaEnum_InitFields(void);
extern "C" void **igMemoryRefMetaField_Create(int arg0);
extern "C" int FUN_0014ec50(...);
extern "C" int igMemoryRefMetaField_GetVTable(void);
extern "C" void igMemoryRefMetaField_EnsureRegistered(void);
extern "C" void igMemoryRefMetaField_Register(void);
extern "C" void thunk_igMemoryRefMetaField_GetMetaObject(void);
extern "C" void igMemoryRefMetaField_InitFields(void);
extern "C" void FUN_002bf990(void);
extern "C" int FUN_002bfa60(void);
extern "C" int igMemoryRefArrayMetaField_GetVTable(void);
extern "C" void FUN_002bfb50(void);
extern "C" void igMemoryRefArrayMetaField_Register(void);
extern "C" void thunk_igMemoryRefArrayMetaField_GetMetaObject(void);
extern "C" int FUN_002bfbf0(void);
extern "C" void igMemoryRefArrayMetaField_InitFields(void);
extern "C" void FUN_002bfc90(void);
extern "C" igMetaObject *FUN_002bfd60(void);
extern "C" int igMemoryPoolInfoList_GetVTable(void);
extern "C" void FUN_002bfe40(void);
extern "C" void igMemoryPoolInfoList_Register(void);
extern "C" void thunk_igMemoryPoolInfoList_GetMetaObject(void);
extern "C" void * FUN_002bfed0(int arg0);
extern "C" int FUN_00131b20(...);
extern "C" int igMemoryPoolInfo_GetVTable(void);
extern "C" void FUN_002c00f0(void);
extern "C" void igMemoryPoolInfo_Register(void);
extern "C" void thunk_igMemoryPoolInfo_GetMetaObject(void);
extern "C" void igMemoryPoolInfo_InitFields(void);
extern "C" void * FUN_002c01f0(int arg0);
extern "C" int igMemoryPoolContextInfo_GetVTable(void);
extern "C" void FUN_002c0360(void);
extern "C" void igMemoryPoolContextInfo_Register(void);
extern "C" void thunk_igMemoryPoolContextInfo_GetMetaObject(void);
extern "C" void igMemoryPoolContextInfo_InitFields(void);
extern "C" igMetaObject *igMemoryPool_GetOrCreateMetaObject(void);
extern "C" void FUN_002c0540(void);
extern "C" void igMemoryPool_Register(void);
extern "C" void thunk_igMemoryPool_GetMetaObject(void);
extern "C" void igMemoryPool_InitFields(void);
extern "C" void thunk_igArenaMemoryPool_GetMetaObject(void);
extern "C" void FUN_002c0690(int arg0);
extern "C" int igMemoryFile_GetVTable(void);
extern "C" void FUN_002c0890(void);
extern "C" void igMemoryFile_Register(void);
extern "C" void thunk_igMemoryFile_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c0930(void);
extern "C" void igMemoryFile_InitFields(void);
extern "C" void thunk_igFile_GetMetaObject(void);
extern "C" void thunk_FUN_002ef9a0(void);
extern "C" void thunk_FUN_002ef9d0(void);
extern "C" int FUN_002c0a00(int arg0);
extern "C" int igMemoryFileEntryList_GetVTable(void);
extern "C" void FUN_002c0ad0(void);
extern "C" void igMemoryFileEntryList_Register(void);
extern "C" void thunk_igMemoryFileEntryList_GetMetaObject(void);
extern "C" void * FUN_002c0b60(int arg0);
extern "C" int igMemoryFileEntry_GetVTable(void);
extern "C" void FUN_002c0c80(void);
extern "C" void igMemoryFileEntry_Register(void);
extern "C" void thunk_igMemoryFileEntry_GetMetaObject(void);
extern "C" void igMemoryFileEntry_InitFields(void);
extern "C" int FUN_002c0d80(int arg0);
extern "C" int igMemoryDirEntry_GetVTable(void);
extern "C" void FUN_002c0ea0(void);
extern "C" void igMemoryDirEntry_Register(void);
extern "C" void thunk_igMemoryDirEntry_GetMetaObject(void);
extern "C" void igMemoryDirEntry_InitFields(void);
extern "C" void * FUN_002c1070(int arg0);
extern "C" int igMemoryDictionary_GetVTable(void);
extern "C" void FUN_002c1190(void);
extern "C" void igMemoryDictionary_Register(void);
extern "C" void thunk_igMemoryDictionary_GetMetaObject(void);
extern "C" void igMemoryDictionary_InitFields(void);
extern "C" int igMediaFile_GetVTable(void);
extern "C" void **FUN_002c13b0(void **arg0, short arg1);
extern "C" void FUN_002c1430(void);
extern "C" void igMediaFile_Register(void);
extern "C" void thunk_igMediaFile_GetMetaObject(void);
extern "C" void igMediaFile_InitFields(void);
extern "C" void * FUN_002c1580(int arg0);
extern "C" int igMediaList_GetVTable(void);
extern "C" void FUN_002c1650(void);
extern "C" void igMediaList_Register(void);
extern "C" void thunk_igMediaList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c16e0(void);
extern "C" void FUN_002c1780(void);
extern "C" void igMedia_Register(void);
extern "C" void thunk_igMedia_GetMetaObject(void);
extern "C" void FUN_002c1810(void);
extern "C" void thunk_igPsx2Media_GetMetaObject(void);
extern "C" void thunk_FUN_002ebcf0(void);
extern "C" void thunk_FUN_002ebd70(void);
extern "C" void FUN_002c18b0(void);
extern "C" void igLongTimer_Register(void);
extern "C" igMetaObject *FUN_002c1930(void);
extern "C" void igLongTimer_InitFields(void);
extern "C" void thunk_igPsx2LongTimer_GetMetaObject(void);
extern "C" void FUN_002c19f0(int arg0);
extern "C" int igLongMetaField_GetVTable(void);
extern "C" void FUN_002c1b10(void);
extern "C" void igLongMetaField_Register(void);
extern "C" void thunk_igLongMetaField_GetMetaObject(void);
extern "C" void FUN_002c1ba0(void);
extern "C" int FUN_002c1c70(void);
extern "C" int igLongArrayMetaField_GetVTable(void);
extern "C" void FUN_002c1d90(void);
extern "C" void igLongArrayMetaField_Register(void);
extern "C" void thunk_igLongArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c1e30(void);
extern "C" void igLongArrayMetaField_InitFields(void);
extern "C" void FUN_002c1ed0(void);
extern "C" igMetaObject *FUN_002c1fa0(void);
extern "C" int igLocationTable_GetVTable(void);
extern "C" void FUN_002c20f0(void);
extern "C" void igLocationTable_Register(void);
extern "C" void thunk_igLocationTable_GetMetaObject(void);
extern "C" void igLocationTable_InitFields(void);
extern "C" igMetaObject *FUN_002c2290(void);
extern "C" void FUN_002c2330(void);
extern "C" void igLibraryLoader_Register(void);
extern "C" void thunk_igLibraryLoader_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c23b0(void);
extern "C" int igLibraryList_GetVTable(void);
extern "C" void FUN_002c2490(void);
extern "C" void igLibraryList_Register(void);
extern "C" void thunk_igLibraryList_GetMetaObject(void);
extern "C" void FUN_002c2570(void);
extern "C" void igLibrary_Register(void);
extern "C" void thunk_igLibrary_GetMetaObject(void);
extern "C" void igLibrary_InitFields(void);
extern "C" void **InternalObjectList_Create(int allocator);
extern "C" int FUN_002c2710(int arg0, int arg1);
extern "C" igMetaObject *FUN_002c2790(void);
extern "C" int __internalObjectList_GetVTable(void);
extern "C" void __internalObjectList_EnsureRegistered(void);
extern "C" void __internalObjectList_Register(void);
extern "C" void thunk___internalObjectList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c28f0(void);
extern "C" void __internalObjectList_InitFields(void);
extern "C" void **FUN_002c29c0(int arg0);
extern "C" int FUN_002c2a60(int arg0, int arg1);
extern "C" igMetaObject *FUN_002c2ae0(void);
extern "C" int __internalNonRefCountedObjectList_GetVTable(void);
extern "C" void FUN_002c2bb0(void);
extern "C" void __internalNonRefCountedObjectList_Register(void);
extern "C" void thunk___internalNonRefCountedObjectList_GetMetaObject(void);
extern "C" void __internalNonRefCountedObjectList_InitFields(void);
extern "C" void *Gap__Core__igIntMetaField__vfunc_21(void *self, void *src);
extern "C" igMetaObject *FUN_002c2e10(void);
extern "C" int FUN_002ea420(...);
extern "C" int igIntMetaField_GetVTable(void);
extern "C" void igIntMetaField_EnsureRegistered(void);
extern "C" void igIntMetaField_Register(void);
extern "C" void thunk_igIntMetaField_GetMetaObject(void);
extern "C" void FUN_002c2fc0(void);
extern "C" void FUN_002c30d0(int arg0);
extern "C" int igIntArrayMetaField_GetVTable(void);
extern "C" void FUN_002c31f0(void);
extern "C" void igIntArrayMetaField_Register(void);
extern "C" void thunk_igIntArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c3290(void);
extern "C" void igIntArrayMetaField_InitFields(void);
extern "C" void FUN_002c3330(void);
extern "C" void FUN_002c3400(int arg0);
extern "C" igMetaObject *FUN_002c3440(void);
extern "C" int igInfoList_GetVTable(void);
extern "C" void FUN_002c3520(void);
extern "C" void igInfoList_Register(void);
extern "C" void thunk_igInfoList_GetMetaObject(void);
extern "C" int igInfo_GetVTable(void);
extern "C" void FUN_002c3690(void);
extern "C" void igInfo_Register(void);
extern "C" void thunk_igInfo_GetMetaObject(void);
extern "C" void igInfo_InitFields(void);
extern "C" void * FUN_002c37e0(int arg0);
extern "C" int FUN_002c3820(void);
extern "C" int FUN_0013a880(...);
extern "C" int FUN_0014aa70(...);
extern "C" int FUN_0014e420(...);
extern "C" int FUN_00150180(...);
extern "C" int FUN_001510d0(...);
extern "C" int FUN_001a4510(...);
extern "C" int FUN_00229270(...);
extern "C" int igIGBFile_GetVTable(void);
extern "C" int *FUN_002c3d10(int *p);
extern "C" int *FUN_002c3d20(int *p);
extern "C" int *FUN_002c3d30(int *p);
extern "C" int *FUN_002c3d40(int *p);
extern "C" int *FUN_002c3d50(int *p);
extern "C" void FUN_002c3de0(void);
extern "C" void igIGBFile_Register(void);
extern "C" void thunk_igIGBFile_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c3e80(void);
extern "C" void igIGBFile_InitFields(void);
extern "C" void FUN_002c43a0(void);
extern "C" void * FUN_002c43b0(int arg0);
extern "C" int igFolder_GetVTable(void);
extern "C" void FUN_002c44c0(void);
extern "C" void igFolder_Register(void);
extern "C" void thunk_igFolder_GetMetaObject(void);
extern "C" void igFolder_InitFields(void);
extern "C" void thunk_igPsx2Folder_GetMetaObject(void);
extern "C" void FUN_002c45f0(int arg0);
extern "C" int igFloatMetaField_GetVTable(void);
extern "C" void FUN_002c4710(void);
extern "C" void igFloatMetaField_Register(void);
extern "C" void thunk_igFloatMetaField_GetMetaObject(void);
extern "C" void FUN_002c47a0(void);
extern "C" int FUN_002c4870(void);
extern "C" void FUN_002c48b0(int arg0);
extern "C" int FUN_002fbfe0(...);
extern "C" int igFloatArrayMetaField_GetVTable(void);
extern "C" void FUN_002c49d0(void);
extern "C" void igFloatArrayMetaField_Register(void);
extern "C" void thunk_igFloatArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c4a70(void);
extern "C" void igFloatArrayMetaField_InitFields(void);
extern "C" void FUN_002c4b10(void);
extern "C" int FUN_002c4be0(void);
extern "C" int FUN_002c4c40(void);
extern "C" void * igFile_Create(int arg0);
extern "C" igMetaObject *FUN_002c4ce0(void);
extern "C" void FUN_002c4d80(void);
extern "C" void igFile_Register(void);
extern "C" void igFile_InitFields(void);
extern "C" void thunk_igPsx2File_GetMetaObject(void);
extern "C" void FUN_002c4f80(int arg0);
extern "C" int FUN_00130720(...);
extern "C" int igExternalInfoEntry_GetVTable(void);
extern "C" void FUN_002c50a0(void);
extern "C" void igExternalInfoEntry_Register(void);
extern "C" void thunk_igExternalInfoEntry_GetMetaObject(void);
extern "C" void igExternalInfoEntry_InitFields(void);
extern "C" int igExternalIndexedEntry_GetVTable(void);
extern "C" void FUN_002c52d0(void);
extern "C" void igExternalIndexedEntry_Register(void);
extern "C" void thunk_igExternalIndexedEntry_GetMetaObject(void);
extern "C" void igExternalIndexedEntry_InitFields(void);
extern "C" int igExternalDirEntry_GetVTable(void);
extern "C" void FUN_002c5550(void);
extern "C" void igExternalDirEntry_Register(void);
extern "C" void thunk_igExternalDirEntry_GetMetaObject(void);
extern "C" void igExternalDirEntry_InitFields(void);
extern "C" void * FUN_002c5780(int arg0);
extern "C" igMetaObject *FUN_002c57c0(void);
extern "C" int igEventTracker_GetVTable(void);
extern "C" void FUN_002c59e0(void);
extern "C" void igEventTracker_Register(void);
extern "C" void thunk_igEventTracker_GetMetaObject(void);
extern "C" void igEventTracker_InitFields(void);
extern "C" int FUN_002c5e10(int arg0);
extern "C" int igErrorHandler_GetVTable(void);
extern "C" void FUN_002c5ee0(void);
extern "C" void igErrorHandler_Register(void);
extern "C" void thunk_igErrorHandler_GetMetaObject(void);
extern "C" void FUN_002c5f80(void);
extern "C" void thunk_thunk_FUN_002dca20(void);
extern "C" void thunk_FUN_002dc9c0(void);
extern "C" void **FUN_002c5fb0(int arg0);
extern "C" int Gap__Core__igEnumMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igEnumMetaField_GetVTable(void);
extern "C" void igEnumMetaField_EnsureRegistered(void);
extern "C" void igEnumMetaField_Register(void);
extern "C" void thunk_igEnumMetaField_GetMetaObject(void);
extern "C" void igEnumMetaField_InitFields(void);
extern "C" void FUN_002c62b0(void);
extern "C" int igEnumMetaField_GetDefaultDescriptor(void);
extern "C" void FUN_002c63c0(int arg0);
extern "C" int igEnumArrayMetaField_GetVTable(void);
extern "C" void FUN_002c64e0(void);
extern "C" void igEnumArrayMetaField_Register(void);
extern "C" void thunk_igEnumArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c6580(void);
extern "C" void igEnumArrayMetaField_InitFields(void);
extern "C" void FUN_002c6620(void);
extern "C" int FUN_002c66f0(void);
extern "C" void FUN_002c6750(int arg0);
extern "C" int FUN_001489a0(...);
extern "C" int FUN_0019eeb0(...);
extern "C" int FUN_00227e70(...);
extern "C" int igDriverDatabase_GetVTable(void);
extern "C" void FUN_002c68f0(void);
extern "C" void igDriverDatabase_Register(void);
extern "C" void thunk_igDriverDatabase_GetMetaObject(void);
extern "C" void igDriverDatabase_InitFields(void);
extern "C" void FUN_002c6ba0(int arg0);
extern "C" int igDoubleMetaField_GetVTable(void);
extern "C" void FUN_002c6cc0(void);
extern "C" void igDoubleMetaField_Register(void);
extern "C" void thunk_igDoubleMetaField_GetMetaObject(void);
extern "C" void FUN_002c6d50(void);
extern "C" int FUN_002c6e20(void);
extern "C" int igDoubleArrayMetaField_GetVTable(void);
extern "C" void FUN_002c6f40(void);
extern "C" void igDoubleArrayMetaField_Register(void);
extern "C" void thunk_igDoubleArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c6fe0(void);
extern "C" void igDoubleArrayMetaField_InitFields(void);
extern "C" void FUN_002c7080(void);
extern "C" igMetaObject *FUN_002c7150(void);
extern "C" int igDirectoryList_GetVTable(void);
extern "C" void FUN_002c7230(void);
extern "C" void igDirectoryList_Register(void);
extern "C" void thunk_igDirectoryList_GetMetaObject(void);
extern "C" void * FUN_002c72c0(int arg0);
extern "C" igMetaObject *FUN_002c7300(void);
extern "C" int FUN_00135430(...);
extern "C" int FUN_001d35d0(...);
extern "C" int igDirectory_GetVTable(void);
extern "C" void FUN_002c74b0(void);
extern "C" void igDirectory_Register(void);
extern "C" void thunk_igDirectory_GetMetaObject(void);
extern "C" void igDirectory_InitFields(void);
extern "C" void thunk_FUN_002d7b00(void);
extern "C" int FUN_002c7720(void);
extern "C" int FUN_002c7780(void);
extern "C" void * FUN_002c77e0(int arg0);
extern "C" int igDirEntry_GetVTable(void);
extern "C" void FUN_002c7900(void);
extern "C" void igDirEntry_Register(void);
extern "C" void thunk_igDirEntry_GetMetaObject(void);
extern "C" void igDirEntry_InitFields(void);
extern "C" int ObjectRef_Destruct_001c6460(...);
extern "C" int FUN_00233590(...);
extern "C" int igDependencyOrderedList_GetVTable(void);
extern "C" void FUN_002c7ba0(void);
extern "C" void igDependencyOrderedList_Register(void);
extern "C" void thunk_igDependencyOrderedList_GetMetaObject(void);
extern "C" void igDependencyOrderedList_InitFields(void);
extern "C" igMetaObject *FUN_002c7d40(void);
extern "C" int igDependencyList_GetVTable(void);
extern "C" void FUN_002c7e20(void);
extern "C" void igDependencyList_Register(void);
extern "C" void thunk_igDependencyList_GetMetaObject(void);
extern "C" void FUN_002c7eb0(void);
extern "C" int igDependencyMetaField_GetVTable(void);
extern "C" void FUN_002c8090(void);
extern "C" void igDependencyMetaField_Register(void);
extern "C" void thunk_igDependencyMetaField_GetMetaObject(void);
extern "C" void FUN_002c8120(void);
extern "C" int FUN_002c81f0(void);
extern "C" int Gap__Core__igDependencyMetaField__vfunc_25(void);
extern "C" void Gap__Core__igDependencyMetaField__vfunc_11(void *arg0);
extern "C" void FUN_002c8250(int arg0);
extern "C" void * FUN_002c8450(int arg0);
extern "C" int igDataList_GetVTable(void);
extern "C" void igDataList_EnsureRegistered(void);
extern "C" void *igDataList_Register(void);
extern "C" void thunk_igDataList_GetMetaObject(void);
extern "C" void igDataList_InitFields(void);
extern "C" igMetaObject *FUN_002c86a0(void);
extern "C" int igStringRefListList_GetVTable(void);
extern "C" void FUN_002c8780(void);
extern "C" void igStringRefListList_Register(void);
extern "C" void thunk_igStringRefListList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c8810(void);
extern "C" int igObjectListList_GetVTable(void);
extern "C" void FUN_002c88f0(void);
extern "C" void igObjectListList_Register(void);
extern "C" void thunk_igObjectListList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c8980(void);
extern "C" int igIntListList_GetVTable(void);
extern "C" void FUN_002c8a60(void);
extern "C" void igIntListList_Register(void);
extern "C" void thunk_igIntListList_GetMetaObject(void);
extern "C" void * FUN_002c8af0(int arg0);
extern "C" igMetaObject *FUN_002c8b30(void);
extern "C" int igMetaFieldList_GetVTable(void);
extern "C" void FUN_002c8c10(void);
extern "C" void igMetaFieldList_Register(void);
extern "C" void thunk_igMetaFieldList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c8ca0(void);
extern "C" int igMetaObjectListList_GetVTable(void);
extern "C" void FUN_002c8d80(void);
extern "C" void igMetaObjectListList_Register(void);
extern "C" void thunk_igMetaObjectListList_GetMetaObject(void);
extern "C" void * FUN_002c8e10(int arg0);
extern "C" igMetaObject *FUN_002c8e50(void);
extern "C" int igMetaObjectList_GetVTable(void);
extern "C" void FUN_002c8f30(void);
extern "C" void igMetaObjectList_Register(void);
extern "C" void thunk_igMetaObjectList_GetMetaObject(void);
extern "C" igMetaObject *FUN_002c8fc0(void);
extern "C" int igPointerListList_GetVTable(void);
extern "C" void FUN_002c90a0(void);
extern "C" void igPointerListList_Register(void);
extern "C" void thunk_igPointerListList_GetMetaObject(void);
extern "C" void * FUN_002c9130(int arg0);
extern "C" igMetaObject *FUN_002c9170(void);
extern "C" int igPointerList_GetVTable(void);
extern "C" void FUN_002c9250(void);
extern "C" void igPointerList_Register(void);
extern "C" void thunk_igPointerList_GetMetaObject(void);
extern "C" void FUN_002c92e0(void);
extern "C" igMetaObject *FUN_002c93a0(void);
extern "C" int igDoubleList_GetVTable(void);
extern "C" void FUN_002c9480(void);
extern "C" void igDoubleList_Register(void);
extern "C" void thunk_igDoubleList_GetMetaObject(void);
extern "C" void FUN_002c9510(void);
extern "C" igMetaObject *FUN_002c95d0(void);
extern "C" int igFloatListList_GetVTable(void);
extern "C" void FUN_002c96b0(void);
extern "C" void igFloatListList_Register(void);
extern "C" void thunk_igFloatListList_GetMetaObject(void);
extern "C" void FUN_002c9740(int arg0);
extern "C" igMetaObject *FUN_002c9780(void);
extern "C" int igFloatList_GetVTable(void);
extern "C" void FUN_002c9860(void);
extern "C" void igFloatList_Register(void);
extern "C" void thunk_igFloatList_GetMetaObject(void);
extern "C" void FUN_002c98f0(void);
extern "C" void FUN_002c99b0(int arg0);
extern "C" int igUnsignedCharList_GetVTable(void);
extern "C" void FUN_002c9a80(void);
extern "C" void igUnsignedCharList_Register(void);
extern "C" void thunk_igUnsignedCharList_GetMetaObject(void);
extern "C" void FUN_002c9b10(void);
extern "C" void FUN_002c9bd0(int arg0);
extern "C" igMetaObject *FUN_002c9c10(void);
extern "C" int igShortListList_GetVTable(void);
extern "C" void FUN_002c9cf0(void);
extern "C" void igShortListList_Register(void);
extern "C" void thunk_igShortListList_GetMetaObject(void);
extern "C" void FUN_002c9d80(int arg0);
extern "C" igMetaObject *FUN_002c9dc0(void);
extern "C" int igShortList_GetVTable(void);
extern "C" void FUN_002c9ea0(void);
extern "C" void igShortList_Register(void);
extern "C" void thunk_igShortList_GetMetaObject(void);
extern "C" void FUN_002c9f30(void);
extern "C" void FUN_002c9ff0(int arg0);
extern "C" igMetaObject *FUN_002ca030(void);
extern "C" int igUnsignedShortList_GetVTable(void);
extern "C" void FUN_002ca110(void);
extern "C" void igUnsignedShortList_Register(void);
extern "C" void thunk_igUnsignedShortList_GetMetaObject(void);
extern "C" void FUN_002ca1a0(void);
extern "C" void * FUN_002ca260(int arg0);
extern "C" igMetaObject *FUN_002ca2a0(void);
extern "C" int igUnsignedIntListNoClean_GetVTable(void);
extern "C" void FUN_002ca380(void);
extern "C" void igUnsignedIntListNoClean_Register(void);
extern "C" void thunk_igUnsignedIntListNoClean_GetMetaObject(void);
extern "C" void FUN_002ca410(int arg0);
extern "C" igMetaObject *FUN_002ca450(void);
extern "C" int igUnsignedIntList_GetVTable(void);
extern "C" void FUN_002ca530(void);
extern "C" void igUnsignedIntList_Register(void);
extern "C" void thunk_igUnsignedIntList_GetMetaObject(void);
extern "C" void FUN_002ca5c0(void);
extern "C" igMetaObject *FUN_002ca680(void);
extern "C" int igLongList_GetVTable(void);
extern "C" void FUN_002ca760(void);
extern "C" void igLongList_Register(void);
extern "C" void thunk_igLongList_GetMetaObject(void);
extern "C" void FUN_002ca7f0(void);
extern "C" void * FUN_002ca8b0(int arg0);
extern "C" igMetaObject *FUN_002ca8f0(void);
extern "C" int igIntListNoClean_GetVTable(void);
extern "C" void FUN_002ca9d0(void);
extern "C" void igIntListNoClean_Register(void);
extern "C" void thunk_igIntListNoClean_GetMetaObject(void);
extern "C" igMetaObject *FUN_002caa60(void);
extern "C" void * igIntList_Create(int arg0);
extern "C" int igIntList_GetVTable(void);
extern "C" void igIntList_EnsureRegistered(void);
extern "C" void *igIntList_Register(void);
extern "C" void thunk_igIntList_GetMetaObject(void);
extern "C" void igIntList_InitFields(void);
extern "C" igMetaObject *FUN_002cace0(void);
extern "C" int igCharListNoClean_GetVTable(void);
extern "C" void FUN_002cadc0(void);
extern "C" void igCharListNoClean_Register(void);
extern "C" void thunk_igCharListNoClean_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cae50(void);
extern "C" void FUN_002cae60(int arg0);
extern "C" igMetaObject *FUN_002caea0(void);
extern "C" int igCharList_GetVTable(void);
extern "C" void FUN_002caf80(void);
extern "C" void igCharList_Register(void);
extern "C" void thunk_igCharList_GetMetaObject(void);
extern "C" void FUN_002cb010(void);
extern "C" void igBoolList_Create(int arg0);
extern "C" igMetaObject *FUN_002cb110(void);
extern "C" int igBoolList_GetVTable(void);
extern "C" void FUN_002cb1f0(void);
extern "C" void igBoolList_Register(void);
extern "C" void thunk_igBoolList_GetMetaObject(void);
extern "C" void FUN_002cb280(void);
extern "C" igMetaObject *FUN_002cb340(void);
extern "C" int igContextExtList_GetVTable(void);
extern "C" void FUN_002cb420(void);
extern "C" void igContextExtList_Register(void);
extern "C" void thunk_igContextExtList_GetMetaObject(void);
extern "C" void * FUN_002cb4b0(int arg0);
extern "C" igMetaObject *FUN_002cb4f0(void);
extern "C" int igContextExtInfoList_GetVTable(void);
extern "C" void FUN_002cb5d0(void);
extern "C" void igContextExtInfoList_Register(void);
extern "C" void thunk_igContextExtInfoList_GetMetaObject(void);
extern "C" void * FUN_002cb660(int arg0);
extern "C" int igContextExtInfo_GetVTable(void);
extern "C" void FUN_002cb7c0(void);
extern "C" void igContextExtInfo_Register(void);
extern "C" void thunk_igContextExtInfo_GetMetaObject(void);
extern "C" void igContextExtInfo_InitFields(void);
extern "C" void FUN_002cb980(void);
extern "C" void igContextExt_Register(void);
extern "C" void thunk_igContextExt_GetMetaObject(void);
extern "C" void FUN_002cba00(int arg0);
extern "C" int igContextList_GetVTable(void);
extern "C" void FUN_002cbad0(void);
extern "C" void igContextList_Register(void);
extern "C" void thunk_igContextList_GetMetaObject(void);
extern "C" void FUN_002cbbb0(void);
extern "C" void igContext_Register(void);
extern "C" void thunk_igContext_GetMetaObject(void);
extern "C" void igContext_InitFields(void);
extern "C" void FUN_002cbd40(void);
extern "C" void igCompoundMetaField_Register(void);
extern "C" void thunk_igCompoundMetaField_GetMetaObject(void);
extern "C" void igCompoundMetaField_InitFields(void);
extern "C" void FUN_002cbe70(void);
extern "C" int FUN_002cbf40(void);
extern "C" void FUN_002cbf60(int value);
extern "C" void **FUN_002cbf70(int arg0);
extern "C" void *Gap__Core__igCharMetaField__vfunc_21(void *arg0, void *arg1);
extern "C" int igCharMetaField_GetVTable(void);
extern "C" void FUN_002cc160(void);
extern "C" void igCharMetaField_Register(void);
extern "C" void thunk_igCharMetaField_GetMetaObject(void);
extern "C" void FUN_002cc1f0(void);
extern "C" int FUN_002cc2c0(void);
extern "C" void FUN_002cc300(int arg0);
extern "C" int igCharArrayMetaField_GetVTable(void);
extern "C" void FUN_002cc420(void);
extern "C" void igCharArrayMetaField_Register(void);
extern "C" void thunk_igCharArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cc4c0(void);
extern "C" void igCharArrayMetaField_InitFields(void);
extern "C" void FUN_002cc560(void);
extern "C" igMetaObject *FUN_002cc630(void);
extern "C" int igCallStackTracer_GetVTable(void);
extern "C" void FUN_002cc710(void);
extern "C" void igCallStackTracer_Register(void);
extern "C" void thunk_igCallStackTracer_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cc7a0(void);
extern "C" void FUN_002cc7b0(void);
extern "C" void thunk_igPsx2CallStackTracer_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cc7e0(void);
extern "C" int igCallStackTable_GetVTable(void);
extern "C" void FUN_002cc960(void);
extern "C" void igCallStackTable_Register(void);
extern "C" void thunk_igCallStackTable_GetMetaObject(void);
extern "C" void igCallStackTable_InitFields(void);
extern "C" void **FUN_002ccab0(int arg0);
extern "C" int FUN_00300c60(int, int);
extern "C" int FUN_002ff800(int, int);
extern "C" int Gap__Core__igBoolMetaField__vfunc_21(int arg0, int arg1);
extern "C" int igBoolMetaField_GetVTable(void);
extern "C" void FUN_002ccca0(void);
extern "C" void igBoolMetaField_Register(void);
extern "C" void thunk_igBoolMetaField_GetMetaObject(void);
extern "C" void FUN_002ccd30(void);
extern "C" int FUN_002cce00(void);
extern "C" void FUN_002cce40(int arg0);
extern "C" int igBoolArrayMetaField_GetVTable(void);
extern "C" void FUN_002ccf60(void);
extern "C" void igBoolArrayMetaField_Register(void);
extern "C" void thunk_igBoolArrayMetaField_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cd000(void);
extern "C" void igBoolArrayMetaField_InitFields(void);
extern "C" void FUN_002cd0a0(void);
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_21(int arg0, int arg1);
extern "C" int FUN_002d1500(...);
extern "C" int igAliasMemoryPool_GetVTable(void);
extern "C" void igAliasMemoryPool_EnsureRegistered(void);
extern "C" void igAliasMemoryPool_Register(void);
extern "C" void thunk_igAliasMemoryPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_002cd480(void);
extern "C" void igAliasMemoryPool_InitFields(void);
extern "C" int FUN_002cd5c0(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_21(int arg0, int arg1);
extern "C" int igPageMemoryPool_GetVTable(void);
extern "C" void FUN_002cd7c0(void);
extern "C" void igPageMemoryPool_Register(void);
extern "C" void thunk_igPageMemoryPool_GetMetaObject(void);
extern "C" void igPageMemoryPool_InitFields(void);
extern "C" int FUN_002cd990(void);
extern "C" int FUN_002cd9f0(void);
extern "C" int FUN_002cda50(void);
extern "C" void **FUN_002cdab0(int arg0);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_21(int arg0, int arg1);
extern "C" int igArenaMemoryPool_GetVTable(void);
extern "C" void FUN_002cdcf0(void);
extern "C" void igArenaMemoryPool_Register(void);
extern "C" void igArenaMemoryPool_InitFields(void);
extern "C" void FUN_002cdf30(int arg0);
extern "C" int igStackMemoryPool_GetVTable(void);
extern "C" void FUN_002ce050(void);
extern "C" void igStackMemoryPool_Register(void);
extern "C" void thunk_igStackMemoryPool_GetMetaObject(void);
extern "C" void igStackMemoryPool_InitFields(void);
extern "C" int FUN_002ce1b0(void);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_11(int extra0);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_21(void *self, void *src);
extern "C" int igMallocMemoryPool_GetVTable(void);
extern "C" void FUN_002ce3c0(void);
extern "C" void igMallocMemoryPool_Register(void);
extern "C" void thunk_igMallocMemoryPool_GetMetaObject(void);
extern "C" void igMallocMemoryPool_InitFields(void);
extern "C" int igMemoryDescriptorMetaField_GetVTable(void);
extern "C" void FUN_002ce6d0(void);
extern "C" void igMemoryDescriptorMetaField_Register(void);
extern "C" void thunk_igMemoryDescriptorMetaField_GetMetaObject(void);
extern "C" void FUN_002ce760(void);
extern "C" int Gap__Core__igMemoryDescriptorMetaField__vfunc_25(void);
extern "C" void Gap__Core__igMemoryDescriptorMetaField__vfunc_11(void *arg0);
extern "C" void FUN_002ce850(int arg0);
extern "C" int igProgramFile_GetVTable(void);
extern "C" void FUN_002cea80(void);
extern "C" void igProgramFile_Register(void);
extern "C" void thunk_igProgramFile_GetMetaObject(void);
extern "C" void igProgramFile_InitFields(void);
extern "C" void thunk_igElfFile_GetMetaObject(void);
extern "C" void * FUN_002cec00(int arg0);
extern "C" int igElfFile_GetVTable(void);
extern "C" void FUN_002ced70(void);
extern "C" void igElfFile_Register(void);
extern "C" int FUN_002cedf0(void);
extern "C" void igElfFile_InitFields(void);
extern "C" int igStandardQueue_GetVTable(void);
extern "C" void FUN_002cf0e0(void);
extern "C" void igStandardQueue_Register(void);
extern "C" igMetaObject *FUN_002cf170(void);
extern "C" void igStandardQueue_InitFields(void);
extern "C" int igPsx2ThreadManager_GetVTable(void);
extern "C" void FUN_002cf360(void);
extern "C" void igPsx2ThreadManager_Register(void);
extern "C" int FUN_002cf3e0(void);
extern "C" void FUN_002cf3f0(void);
extern "C" int igPsx2Thread_GetVTable(void);
extern "C" void FUN_002cf540(void);
extern "C" void igPsx2Thread_Register(void);
extern "C" igMetaObject *FUN_002cf5d0(void);
extern "C" void igPsx2Thread_InitFields(void);
extern "C" int igPsx2Semaphore_GetVTable(void);
extern "C" void FUN_002cf7a0(void);
extern "C" void igPsx2Semaphore_Register(void);
extern "C" igMetaObject *FUN_002cf820(void);
extern "C" void igPsx2Semaphore_InitFields(void);
extern "C" void FUN_002cf900(int arg0);
extern "C" int igPsx2Media_GetVTable(void);
extern "C" void FUN_002cfac0(void);
extern "C" void igPsx2Media_Register(void);
extern "C" igMetaObject *FUN_002cfb50(void);
extern "C" void igPsx2Media_InitFields(void);
extern "C" int igPsx2LongTimer_GetVTable(void);
extern "C" void FUN_002cfd70(void);
extern "C" void igPsx2LongTimer_Register(void);
extern "C" int FUN_002cfdf0(void);
extern "C" void FUN_002cfe00(void);
extern "C" void FUN_002cfe10(int arg0);
extern "C" igMetaObject *FUN_002cfe50(void);
extern "C" int igPsx2IopRpcConnection_GetVTable(void);
extern "C" void FUN_002cff30(void);
extern "C" void igPsx2IopRpcConnection_Register(void);
extern "C" void thunk_igPsx2IopRpcConnection_GetMetaObject(void);
extern "C" void igPsx2IopRpcConnection_InitFields(void);
extern "C" int igPsx2Folder_GetVTable(void);
extern "C" void FUN_002d0110(void);
extern "C" void igPsx2Folder_Register(void);
extern "C" igMetaObject *FUN_002d0190(void);
extern "C" int FUN_002d01a0(int arg0);
extern "C" int igPsx2File_GetVTable(void);
extern "C" void FUN_002d02b0(void);
extern "C" void igPsx2File_Register(void);
extern "C" void igPsx2File_InitFields(void);
extern "C" void thunk_FUN_0032c0c0(void);
extern "C" int igPsx2CallStackTracer_GetVTable(void);
extern "C" void FUN_002d04a0(void);
extern "C" void igPsx2CallStackTracer_Register(void);
extern "C" igMetaObject *FUN_002d0520(void);
extern "C" void FUN_002d0530(void);
extern "C" int memset(...);
extern "C" int printf(...);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_99(void *arg0);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_26(void);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_24(int *outStatus);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_25(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_29(void);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_35(int *statusOut);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_36(void);
class igResult;
extern "C" igResult Gap__Core__igAliasMemoryPool__vfunc_45(igAliasMemoryPool *self, igMemoryPoolInfo *info);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_57(igAliasMemoryPool *arg0, int arg1, int arg2, unsigned short alignment);
extern "C" int igAliasMemoryPool_OwnsAllocation(igAliasMemoryPool *self, int poolIndex);
extern "C" int __do_global_ctors();
extern "C" int __do_global_dtors();
extern "C" void FUN_002d1660(void);
extern "C" void FUN_002d1690(int extra0);
extern "C" int FUN_002d1e40(...);
extern "C" void FUN_002d16a0(int arg0);
extern "C" int FUN_002d2800(...);
extern "C" void FUN_002d1770(void);
extern "C" int FUN_002d1870(void);
extern "C" void FUN_002d18c0(int arg0);
extern "C" void FUN_002d18d0(void *arg0, int arg1);
extern "C" void *FUN_002d1930(void *arg0);
extern "C" int FUN_002d1c20(int *p);
extern "C" int FUN_002d1c30(int *p);
extern "C" int *getenv(...);
extern "C" igMetaObject *FUN_002d2790(void);
extern "C" int FUN_002d30b0(int *p, int extra1);
extern "C" int FUN_002d30c0(int *p, int extra1);
extern "C" void FUN_002d3150(int *arg0, int arg1);
extern "C" int strncpy(...);
extern "C" void FUN_002d3320(char *arg0, char *arg1);
extern "C" void FUN_002d3370(char *a, char *b);
extern "C" void FUN_002d33c0(void *arg0, int arg1);
extern "C" void FUN_002ed5c0(void *);
extern "C" int thunk_malloc(int extra0);
extern "C" int thunk_free(int extra0);
extern "C" unsigned short Gap__Core__igBoolArrayMetaField__vfunc_25(void *arg0);
extern "C" int sscanf(...);
extern "C" int strncasecmp(...);
extern "C" int Gap__Core__igBoolMetaField__vfunc_56(void *arg0, char *arg1, int arg2);
extern "C" int sprintf(...);
extern "C" void Gap__Core__igBoolMetaField__vfunc_57(int *arg0, void *arg1, unsigned char *arg2);
extern "C" int **FUN_002d37b0(int **arg0, int extra1);
extern "C" int **FUN_002d37f0(int **arg0);
extern "C" int **FUN_002d3830(int **arg0, int extra1);
extern "C" void Gap__Core__igBoolMetaField__vfunc_02(int extra0);
extern "C" int FUN_002d3880(void);
extern "C" void FUN_002d3890(void **arg0, char arg1);
extern "C" int Gap__Core__igBoolMetaField__vfunc_27(void);
extern "C" void FUN_002d38d0(int a0, int a1);
class igResult;
/* igCallStackTable (reflected layout in dw4/reflected.h) with the virtuals its callers use. Its
 * call stacks are zero-terminated return-address runs packed end to end; the hash index holds
 * their word offsets, -1 for an empty slot. */
class igCallStackTableView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int vfunc_23();
    virtual igResult vfunc_24(int count);
    virtual unsigned int *vfunc_25(int offset);
    virtual int addCallStack(int *stack);
    virtual void d25();
    virtual int findCallStack(unsigned int *stack);
    virtual void d27();
    virtual int vfunc_30(unsigned int *stack, int offset);
    virtual void vfunc_31(int hashCapacity);
    int _capacity;
    int _hashCapacity;
    igTDataList<unsigned int> *_callStacks;
    igTDataList<int> *_hashIndex;
};
extern "C" void FUN_002d38e0(igCallStackTableView *table, int hashCapacity);
extern "C" void FUN_002d38f0(igCallStackTableView *table);
extern "C" void FUN_002d3a20(igCallStackTableView *table);
extern "C" int Gap__Core__igCallStackTable__vfunc_23(igCallStackTableView *table);
extern "C" int *Gap__Core__igCallStackTracer__vfunc_24(int *arg0);
extern "C" int Gap__Core__igCallStackTracer__vfunc_25(void);
extern "C" void Gap__Core__igCallStackTracer__vfunc_29(void);
extern "C" void Gap__Core__igCallStackTracer__vfunc_30(void);
extern "C" void FUN_002d4c20(void *arg0, int arg1, char arg2);
extern "C" int Gap__Core__igCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2);
extern "C" void Gap__Core__igCharMetaField__vfunc_57(int *arg0, int arg1, char *arg2);
extern "C" int **FUN_002d4d60(int **arg0, int extra1);
extern "C" int **FUN_002d4da0(int **arg0);
extern "C" int **FUN_002d4de0(int **arg0, int extra1);
extern "C" void Gap__Core__igCharMetaField__vfunc_02(int extra0);
extern "C" int FUN_002d4e30(void);
extern "C" void FUN_002d4e40(void **arg0, char arg1);
extern "C" int Gap__Core__igCharMetaField__vfunc_27(void);
extern "C" unsigned short FUN_002d4e80(void *arg0);
extern "C" void FUN_002d4f20(void *arg0, int arg1);
extern "C" void FUN_002d4fa0(void *arg0, int arg1);
extern "C" void FUN_002d5220(void *arg0, int arg1, int arg2);
extern "C" void FUN_002d52b0(void *arg0, int arg1, int arg2);
extern "C" int FUN_002d5c80(void);
extern "C" void FUN_002d5c90(void *arg0, int arg1);
extern "C" int FUN_002d5d10(int *arg0, int arg1, int arg2, int arg3);
extern "C" int strcpy(...);
extern "C" int strlen(...);
extern "C" void FUN_002d6090(void);
extern "C" int FUN_002d60a0(void);
extern "C" int FUN_002d6380(void);
extern "C" int strcmp(...);
extern "C" int Gap__Core__igDataList__vfunc_23(void);
extern "C" int memcpy(...);
extern "C" int List_Resize(void *list, int count, int extra2);
extern "C" int memmove(...);
extern "C" int FUN_002d7280(...);
extern "C" void igRendererOrderedList_Clear(char *arg0);
extern "C" int FUN_00301000(...);
extern "C" int FUN_002fb8d0(int);
extern "C" int FUN_002f8920(int);
extern "C" int FUN_002f04f0(int);
extern "C" void FUN_002d78e0(void *arg0, int arg1);
extern "C" void Gap__Core__igDirEntry__vfunc_27(void);
extern "C" void Gap__Core__igDirEntry__vfunc_28(void);
extern "C" int Gap__Core__igDirEntry__vfunc_26(int arg0);
extern "C" int Gap__Core__igDirEntry__vfunc_42(void);
extern "C" void Gap__Core__igDirEntry__vfunc_29(void);
extern "C" int Gap__Core__igDirEntry__vfunc_30(void);
extern "C" void Gap__Core__igDirEntry__vfunc_41(void);
extern "C" void Gap__Core__igDirEntry__vfunc_40(void);
extern "C" void Gap__Core__igDirEntry__vfunc_38(void);
extern "C" void Gap__Core__igDirEntry__vfunc_39(void);
extern "C" void Gap__Core__igDirEntry__vfunc_35(void);
extern "C" void Gap__Core__igDirEntry__vfunc_36(void);
extern "C" void Gap__Core__igDirEntry__vfunc_37(void);
extern "C" void Gap__Core__igDirEntry__vfunc_33(void);
extern "C" void Gap__Core__igDirEntry__vfunc_34(void);
extern "C" void Gap__Core__igDirEntry__vfunc_32(void);
extern "C" void Gap__Core__igDirEntry__vfunc_31(void);
extern "C" void Gap__Core__igDirEntry__vfunc_11(int arg0);
extern "C" void Gap__Core__igDirEntry__vfunc_23(void *arg0, int arg1);
extern "C" void Gap__Core__igDirEntry__vfunc_24(void);
extern "C" void Gap__Core__igDirEntry__vfunc_25(void);
extern "C" void FUN_002d7b00(void);
extern "C" void *thunk_FUN_002d7e90(int *arg0, int arg1);
extern "C" int FUN_002d7d60(void *arg0, int arg1);
extern "C" void *FUN_002d7e90(int *arg0, int arg1);
extern "C" void FUN_002d81f0(void *arg0, int arg1);
extern "C" void FUN_002d8310(void *arg0, void *arg1);
extern "C" void * igDirectory_FindInfoByName(int *arg0, int arg1);
extern "C" int FUN_002d8370(void *arg0, int arg1);
extern "C" int FUN_002d8460(void *dir, unsigned key);
extern "C" int FUN_002d8620(int arg0, int arg1, int arg2, int extra3);
extern "C" igMetaObject *Gap__Core__igDirEntry__vfunc_22(void);
extern "C" int FUN_002d8e70(int arg0, int arg1);
extern "C" int FUN_002d8eb0(int arg0, int arg1);
extern "C" void *FUN_002d8f10(int arg0, int arg1);
extern "C" int FUN_002d9120(void *arg0);
struct igDirectoryView;
extern "C" int FUN_002d9130(igDirectoryView *arg0);
extern "C" int Gap__Core__igDoubleMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igDoubleMetaField__vfunc_57(int *arg0, int arg1, long long *arg2);
extern "C" int Gap__Core__igDoubleMetaField__vfunc_25(void);
extern "C" void FUN_002d9500(void **arg0, long long arg1);
extern "C" int Gap__Core__igDoubleMetaField__vfunc_27(void);
extern "C" void Gap__Core__igDriverDatabase__vfunc_12(int self);
extern "C" void FUN_002d96f0(void *arg0, int arg1, int arg2);
extern "C" int FUN_002d9710(void *arg0, int arg1);
extern "C" int StringList_CopyRetained(...);
extern "C" int FUN_002da710(void *arg0, int arg1, int arg2);
extern "C" int FUN_002da770(int *p);
extern "C" int FUN_002dae40(...);
extern "C" void *FUN_002da940(void *arg0, long long arg1);
extern "C" int FUN_002daab0(void);
extern "C" void FUN_002dab80(void *arg0, int arg1);
extern "C" int FUN_002dac30(void *arg0);
extern "C" int FUN_002dac60(void *arg0);
extern "C" int FUN_002dac90(void *arg0);
extern "C" int FUN_002dada0(void *self, char **cursor, char *out, int size);
extern "C" int FUN_0012a78c(void *);
extern "C" void FUN_002db040(void *self, int entry, void *a, void *b);
extern "C" void FUN_002db480(int *arg0);
extern "C" void FUN_002db4e0(int arg0, char *arg1);
extern "C" bool FUN_002db5e0(char *arg0, int *arg1);
extern "C" bool FUN_002db690(char *arg0, int *arg1);
extern "C" int FUN_002dbca0(int arg0, int arg1);
extern "C" unsigned char FUN_002dbd10(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int strcasecmp(...);
extern "C" int FUN_002dbfb0(int dummy0, int arg1, int arg2, int arg3);
extern "C" int FUN_002dc050(int dummy0, int arg1, int arg2, int arg3);
extern "C" int FUN_002dc0a0(int arg0, int arg1, float fparg0, float fparg1);
extern "C" int FUN_002dc120(int p, unsigned char a, int m, unsigned char b);
extern "C" void *FUN_002dc180(void *arg0);
extern "C" void *FUN_002dc2a0(void *arg0);
extern "C" void *FUN_002dc490(void *arg0, int arg1);
extern "C" void FUN_002dc730(void *arg0, int arg1);
extern "C" int Gap__Core__igEnumMetaField__vfunc_56(void *arg0, int *arg1, int arg2);
extern "C" int **FUN_002dc8c0(int **arg0, int extra1);
extern "C" int **FUN_002dc900(int **arg0);
extern "C" int **FUN_002dc940(int **arg0, int extra1);
extern "C" void Gap__Core__igEnumMetaField__vfunc_02(int extra0);
extern "C" int FUN_002dc990(void);
extern "C" int Gap__Core__igEnumMetaField__vfunc_27(void);
extern "C" int thunk_FUN_002dca20();
extern "C" void FUN_002dc9c0(void);
extern "C" int FUN_002dca20(void);
extern "C" void FUN_002dca90(void);
extern "C" void FUN_002dcc40(int a0, int a1);
extern "C" int FUN_002dcc50(int *p);
extern "C" void Gap__Core__igEventTracker__vfunc_28(int *arg0, char *arg1, char *arg2, int *arg3);
extern "C" void Gap__Core__igEventTracker__vfunc_29(int *arg0, char *arg1, char *arg2, int *arg3);
extern "C" void Gap__Core__igEventTracker__vfunc_30(int *result, igEventTracker *self, char *record, int *value);
extern "C" int Gap__Core__igEventTracker__vfunc_34(class igEventTrackerView *self, int offset);
extern "C" int FUN_002e14b0(void *arg0, int arg1);
extern "C" int FUN_002e1500(void *arg0, int arg1);
extern "C" int FUN_002e15f0(void *arg0, int arg1);
extern "C" int FUN_002e2130(int arg0);
extern "C" int FUN_002e2160(int arg0, int arg1);
extern "C" void *FUN_002e2190(void *arg0, int arg1, void *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18);
extern "C" void *FUN_002e2250(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8);
extern "C" void *FUN_002e2300(void *arg0, long long arg1);
extern "C" void FUN_002e2350(int arg0);
extern "C" int FUN_002e2360(void *arg0);
extern "C" int FUN_002e23e0(int arg0, int arg1);
extern "C" void FUN_002e2400(void *arg0, int arg1, int arg2);
extern "C" int FUN_002e2450(int arg0, int arg1);
extern "C" void FUN_002e2470(void *arg0, int arg1, int arg2);
extern "C" int FUN_002e24c0(int arg0, int arg1);
extern "C" void FUN_002e24e0(void *arg0, int arg1, int arg2);
extern "C" void FUN_002e2520(int arg0, int arg1, void *arg2);
extern "C" int strcat(...);
extern "C" void Gap__Core__igExternalDirEntry__vfunc_12(void **arg0);
extern "C" void ***FUN_002e2fb0(void);
extern "C" void FUN_002e30b0(int *arg0, const char *name);
class igFileView;
extern "C" void Gap__igAdxFile__vfunc_38(igFileView *arg0, long long arg1);
extern "C" void FUN_002e31b0(int a0, int a1);
extern "C" bool FilePath_IsAbsolute(const char *path);
extern "C" bool FilePath_HasDirectory(const char *path);
extern "C" void FUN_002e3280(int arg0);
extern "C" void Gap__igAdxFile__vfunc_26(igFileView *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4);
extern "C" void FUN_002e33d0(void);
extern "C" int FUN_002e34a0(void);
extern "C" char * strchr(...);
extern "C" int FUN_002e34d0(char **arg0, char *arg1, int arg2);
extern "C" int Gap__Core__igFloatArrayMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" int fptodp(float);
extern "C" void Gap__Core__igFloatArrayMetaField__vfunc_57(int *arg0, int arg1, float *arg2);
extern "C" int Gap__Core__igFloatMetaField__vfunc_25(void);
extern "C" void FUN_002e3810(void **arg0, float fparg0);
extern "C" int Gap__Core__igFloatMetaField__vfunc_27(void);
extern "C" int dpsub(...);
extern "C" int FUN_002e3a10(void *arg0, int arg1);
extern "C" void FUN_002e3d30(int *arg0);
extern "C" void FUN_002e7000(void);
class igIGBFileView;
extern "C" int Gap__Core__igIGBFile__vfunc_27(igIGBFileView *arg0);
extern "C" void FUN_002e8a10(igIGBFileView *arg0);
extern "C" int FUN_002e9470(igIGBFileView *arg0);
extern "C" void Gap__Core__igIGBFile__vfunc_32(int *arg0, void *arg1);
extern "C" int FUN_002e2d30(...);
extern "C" int FUN_002ea0d0(void **arg0, int arg1, int arg2);
extern "C" int igObject_GetFieldValueByName(void **arg0, int arg1);
extern "C" int Gap__Core__igIntArrayMetaField__vfunc_25(void *arg0);
extern "C" void FUN_002ea290(void **arg0, int arg1);
extern "C" int Gap__Core__igIntMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igIntMetaField__vfunc_57(int *arg0, int arg1, int *arg2);
extern "C" int FUN_002ea3d0(void);
extern "C" int **FUN_002ea460(int **arg0, int extra1);
extern "C" void Gap__Core__igIntMetaField__vfunc_02(int extra0);
extern "C" void FUN_002ea4b0(void **arg0, int arg1);
extern "C" int Gap__Core__igIntMetaField__vfunc_27(void);
extern "C" int ObjectPointerList_FindIndex(char *arg0, int arg1);
extern "C" struct StringPool *StringPool_Destroy(struct StringPool *self, long long delete_flag);
extern "C" void FUN_002eb050(int arg0);
extern "C" void FUN_002eb090(int a0, int a1);
extern "C" void FUN_002eb0a0(int a0, int a1);
class igLocationTableView;
extern "C" void FUN_002eb0b0(igLocationTableView *arg0);
extern "C" int FUN_002eb210(void *arg0);
extern "C" void Gap__Core__igLocationTable__vfunc_24(int *arg0, void *arg1, int arg2);
extern "C" int Gap__Core__igLongMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igLongMetaField__vfunc_57(int *arg0, int arg1, long long *arg2);
extern "C" int igLongMetaField_GetSize(void);
extern "C" void FUN_002ebc00(void **arg0, long long arg1);
extern "C" int Gap__Core__igLongMetaField__vfunc_27(void);
extern "C" void FUN_002ebcf0(void);
extern "C" void FUN_002ebd60(int arg0);
extern "C" void FUN_002ebd70(void);
extern "C" void FUN_002ebdd0(int arg0);
extern "C" void **Gap__Core__igMediaFile__vfunc_25(void **arg0, const char *fileName, int arg2);
class igMediaFileView;
extern "C" void Gap__Core__igMediaFile__vfunc_28(igMediaFileView *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4);
extern "C" int vsprintf(...);
extern "C" int Gap__Core__igMediaFile__vfunc_34(igMediaFileView *a, int c);
extern "C" int free(...);
extern "C" void *Memory_AllocateDefaultBuffer(unsigned int size);
extern "C" void *FUN_002ed260(unsigned int size, unsigned int alignment);
extern "C" void *FUN_002ed2e0(unsigned int size, unsigned int alignment);
extern "C" void *Memory_ReallocateBuffer(void *buffer, unsigned int size);
extern "C" void *FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment);
extern "C" void *thunk_Memory_ReallocateBuffer(void *buffer, unsigned int size);
extern "C" void *thunk_FUN_002ed3b0(void *buffer, unsigned int size, unsigned int alignment);
extern "C" int Memory_FreeBuffer(void *buffer);
extern "C" int Memory_FreeBufferAliasA(void *buffer);
extern "C" unsigned int Memory_GetBufferSize(void *buffer);
extern "C" void *Memory_DuplicateBuffer(void *source);
extern "C" void Memory_FreeBufferAliasB(void *buffer);
extern "C" void Memory_FreeOwnedBufferUnchecked(void *buffer);
extern "C" void FUN_002ed610(unsigned int size, unsigned int perLine, unsigned int digits, unsigned int addr, long long length, const char *name);
extern "C" void *FUN_002ee430(unsigned int size);
extern "C" void FUN_002ee4a0(void *block);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_42(int arg0);
extern "C" int Gap__Core__igMemoryDirEntry__vfunc_22(void);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_36(void);
extern "C" void FUN_002ef9a0(void);
extern "C" void FUN_002ef9d0(void);
extern "C" void FUN_002efa20(int arg0, int arg1, int arg2);
extern "C" void FUN_002efae0(int arg0, int *arg1, int *arg2);
extern "C" void Gap__Core__igMemoryFile__vfunc_24(void *arg0);
extern "C" int Gap__Core__igMemoryFile__vfunc_29(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_30(void *arg0, int arg1, ...);
extern "C" int Gap__Core__igMemoryFile__vfunc_31(int a, int b, ...);
extern "C" int Gap__Core__igMemoryFile__vfunc_32(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_35(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_36(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_37(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_38(int *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igMemoryFile__vfunc_34(void);
extern "C" int **igMemoryPool_Initialize(int **arg0);
extern "C" int **FUN_002effb0(int **arg0);
extern "C" int **igMemoryPool_CopyConstruct(int **arg0);
extern "C" int Gap__Core__igObject__vfunc_00(int extra0);
extern "C" int malloc(...);
extern "C" void * FUN_002f0040(int a0, int a1, int extra2);
extern "C" int thunk_free_2(int extra0);
extern "C" int (*DAT_00586f50)();
extern "C" int FUN_002f0060(int arg0, int arg1, int arg2);
extern "C" void FUN_002f00a0(void *arg0);
extern "C" void thunk_FUN_002f0460(void);
extern "C" void FUN_002f00c0(void);
extern "C" void * Memory_GetDefaultAllocator(void);
extern "C" int FUN_002f00e0(void);
extern "C" void FUN_002f00f0(void *arg0);
extern "C" void FUN_002f0370(void **arg0);
extern "C" void FUN_002f0460(void **arg0);
extern "C" void *Memory_FindOwningAllocator(int arg0);
extern "C" void FUN_002f0620(int *arg0);
extern "C" int FUN_002f0630(void);
extern "C" int FUN_002f0640(void);
extern "C" void igAllocator_EncodeIndexAlias(int extra0);
extern "C" void FUN_002f0660(void);
extern "C" int igAllocator_ResolveEncodedIndex(int arg0);
extern "C" void FUN_002f0750(void);
extern "C" void FUN_002f0760(int arg0, int extra1);
extern "C" void FUN_002f0860(int *arg0);
extern "C" int FUN_002f0870(void);
extern "C" igResult FUN_002f0880(void **arg1, void *arg2);
extern "C" void FUN_002f0a60(char *arg0);
extern "C" void FUN_002f0b30(void);
extern "C" int FUN_002f0b40(void);
extern "C" bool FUN_002f0b50(int arg0, int arg1);
extern "C" int FUN_002f0c90(void **arg0, int arg1);
extern "C" int FUN_002f0cf0(void **arg0, int arg1, int arg2);
extern "C" int FUN_002f0d60(void);
extern "C" void FUN_002f0db0(int arg0);
extern "C" void FUN_002f0dc0(void **arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_002f0e40(void *arg0, int arg1, int arg2, long long arg3, long long arg4, long long arg5, int arg6);
extern "C" int FUN_002f0f70(void *arg0, int arg1, int arg2, int arg3, long long arg4, long long arg5, long long arg6, int arg7);
extern "C" int FUN_002f10a0(void **arg0, int arg1, int arg2, int arg3, int arg4, long long arg5, long long arg6, long long arg7, int arg_sp0);
extern "C" int FUN_002f11c0(void *arg0, int arg1, int arg2, int arg3, int arg4, long long arg5, long long arg6, long long arg7, int arg8);
extern "C" int FUN_002f12f0(void **arg0, int arg1, int arg2, int arg3, int arg4, int arg5, long long arg6, long long arg7, int arg_sp0, int arg_sp8);
extern "C" int FUN_002f15e0(void **arg0, int arg1, int arg2, int arg3, int arg4, int arg5, long long arg6, long long arg7, int arg_sp0, int arg_sp8);
extern "C" int FUN_002f17a0(void **arg0, int arg1, int arg2, int arg3, long long arg4, long long arg5, long long arg6, int arg7);
extern "C" int FUN_002f18d0(void **arg0, int arg1, int arg2, int arg3, int arg4, long long arg5, long long arg6, long long arg7, int arg_sp0);
extern "C" void FUN_002f1cd0(void **arg0, unsigned int arg1, int *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
extern "C" int FUN_002f1e30(void *arg0, int arg1, int arg2, int arg3, long long arg4, long long arg5, long long arg6, int arg7);
extern "C" void FUN_002f1f60(void **arg0, int arg1, int arg2, int arg3, long long arg4, long long arg5, long long arg6, int arg7);
extern "C" void FUN_002f2070(void **arg0, int arg1, int arg2, int arg3, long long arg4, long long arg5, long long arg6, int arg7);
extern "C" void Memory_ShutdownAllocatorRegistries(void **rootAllocator);
extern "C" void FUN_002f2260(void *arg0);
extern "C" void FUN_002f2270(void);
extern "C" void FUN_002f2450(long long arg0, long long arg1, int arg2);
extern "C" void Gap__Core__igMemoryPool__vfunc_34(int *status_out);
extern "C" char * strstr(...);
extern "C" int FUN_002f2990(int arg0, int arg1);
extern "C" void FUN_002f2ab0(int self, int recordIndex, int name);
extern "C" int FUN_002f2b30(int arg0, char *arg1);
extern "C" int strncmp(...);
extern "C" int FUN_002f2bc0(int arg0, char *arg1);
extern "C" int FUN_002f2cd0(int arg0, int arg1);
extern "C" void FUN_002f4060(void *arg0, int arg1);
extern "C" void FUN_002f41e0(char *arg0);
extern "C" void FUN_002f4250(void **arg0);
extern "C" void FUN_002f42e0(void **arg0, int arg1);
extern "C" void FUN_002f4340(void **arg0);
extern "C" void FUN_002f48c0(void);
extern "C" void FUN_002f48d0(char *arg0);
extern "C" igMetaObject *FUN_002f5220(void);
extern "C" void FUN_002f5c30(void *arg0);
extern "C" void FUN_002f5cc0(int *arg0);
extern "C" void MemoryContext_RemoveAllocator(void *arg0, int arg1);
extern "C" void FUN_002f7410(int arg0, int arg1);
extern "C" void qsort(void *, int, int, int (*)(const void *, const void *));

extern "C" int Memory_GetCurrentContext(void);
extern "C" void * FUN_002f87f0(int arg0);
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *allocation);
extern "C" void Memory_PrintPoolStatistics(int arg0, void *pool);
extern "C" int Memory_GetCurrentContextAlias();
extern "C" void * Memory_GetAllocatorBySelector(int selector);
extern "C" void * Memory_GetAllocatorByName(int name);
extern "C" int FUN_002f8960(int arg0);
extern "C" void * FUN_002f89a0(int arg0);
extern "C" int FUN_002f89e0(int arg0);
extern "C" void * FUN_002f8a20(void);
extern "C" int FUN_002f8a50(void *arg0);
extern "C" int FUN_002f8a60(void *arg0, int arg1);
extern "C" void FUN_002f8a80(void *arg0, void *arg1);
extern "C" int FUN_002f8ae0(int *p, int extra1);
extern "C" void FUN_002f8b20(void *arg0);
extern "C" void Gap__Core__igMemoryPoolInfo__vfunc_26(int *arg0, int *arg1, int arg2, int arg3);
extern "C" void igMemoryPoolInfo_Print(int *arg0);
extern "C" void *igMemoryPoolInfoList_Allocate(unsigned int size);
extern "C" void igMemoryPoolInfoList_Delete(void *block);
extern "C" int igMemoryRefArrayMetaField_ReadRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern "C" int igMemoryRefMetaField_WriteRawFieldMem(...);
extern "C" int igMemoryRefArrayMetaField_WriteRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern "C" int igMemoryRefMetaField_GetSize(void);
extern "C" void igMemoryRefMetaField_SetDefaultWord(void **self, int defaultWord);
extern "C" int igMemoryRefMetaField_GetPoolName(int *p);
extern "C" void igMemoryRefMetaField_Destruct(void);
extern "C" void igMetaEnum_GetNameAt(int *arg0, void *arg1, int arg2);
extern "C" int igMetaEnum_GetValueAt(void *arg0, int arg1);
extern "C" int FUN_002fc250(void);
extern "C" int FUN_002fc2a0(void);
extern "C" int igMetaField_GetSize(void);
extern "C" void igMetaField_IgnoreReset(void);
extern "C" int FUN_002fc620(void);
extern "C" int igMetaField_AlignSize(void *p, int size);
extern "C" int FUN_002fc780(void *field, void *object, char *data, void *directory, unsigned char swap);
extern "C" unsigned short igMetaField_WriteRawFieldMem(unsigned short *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void igMetaField_ShallowCopy(int a0, int a1, int a2);
extern "C" void igMetaField_DeepCopy(int a0, int a1, int a2);
extern "C" void igMetaField_ConstructCopy(int a0, int a1, int a2);
extern "C" void FUN_002fc9d0(void *arg0, int arg1, int arg2);
extern "C" void FUN_002fca10(void *arg0, int arg1, int arg2);
extern "C" void FUN_002fca40(void);
extern "C" int FUN_002fca50(void **arg0);
extern "C" void FUN_002fce10(int arg0, int arg1, int arg2);
extern "C" void FUN_002fce20(int *arg0, void *arg1);
extern "C" int igMetaField_IsAlikeByTechnique(void **arg0, int arg1, int arg2, int arg3);
extern "C" int igMetaField_IsAlikeExactly(int a0, int a1, int a2);
extern "C" int igMetaField_IsAlikeDeep(int a0, int a1, int a2);
extern "C" int igMetaField_IsAlikeShallow(int a0, int a1, int a2);
extern "C" int FUN_002fd000(void);
extern "C" unsigned char FUN_002fd010(int a0, int a1, int a2, int a3);
extern "C" void igMetaField_ReleaseElements(void);
extern "C" void igMetaField_ConstructValue(void);
extern "C" void igMetaField_DestructValue(void);
extern "C" void igMetaField_ZeroValue(void);
extern "C" void igMetaField_ClearValue(void);
extern "C" void igMetaField_Print(void *arg0, int arg1, int arg2, const char *arg3);
extern "C" void FUN_002fd200(int arg0);
extern "C" int igMetaField_IsConstruct(void);
extern "C" void *igMetaObject_CreateInstanceDefault(void *meta);
extern "C" void igMetaObject_FinalizeAndAppendField(void *meta,void *field);
extern "C" int FUN_002fdef0(int a0, int a1);
extern "C" int igObjectSystem_FindMetaByNameDefault(const char *name);
extern "C" void FUN_002fe480(int arg0);
extern "C" void FUN_002fe490(int arg0);
extern "C" void FUN_002fe5a0(int arg0);
extern "C" int FUN_002fe730(int arg0);
extern "C" int igMetaObject_GetPoolName(int *p);
extern "C" int Gap__Core__igObject__vfunc_00__002ff0a0(int extra0);
extern "C" void Gap__Core__igObject__constructFields(int extra0, int extra1);
extern "C" void Gap__Core__igObject__destructFields(int extra0);
extern "C" void Gap__Core__igObject__vfunc_03(void);
extern "C" void Gap__Core__igObject__userConstruct(void);
extern "C" void Gap__Core__igObject__userDestruct(void);
extern "C" void Gap__Core__igObject__vfunc_04(void);
extern "C" int Gap__Core__igObject__vfunc_05(void);
extern "C" int Gap__Core__igObject__vfunc_06(void);
extern "C" void Gap__Core__igObject__resetFields(int extra0, int extra1);
extern "C" void Gap__Core__igObject__vfunc_09(int extra0);
extern "C" void Gap__Core__igObject__vfunc_10(int extra0);
extern "C" void Gap__Core__igObject__vfunc_12(void);
extern "C" void Gap__Core__igObject__vfunc_13(void);
extern "C" void Gap__Core__igObject__vfunc_15(void);
extern "C" void Gap__Core__igObject__vfunc_14(void);
extern "C" void Gap__Core__igObject__vfunc_16(int extra0);
extern "C" void Gap__Core__igObject__vfunc_17(void);
extern "C" void Gap__Core__igObject__vfunc_18(void);
extern "C" void igObject_RegisterInstance(void **arg0, void *arg1);
extern "C" int igObject_CreateEmptyInitCallbacks(void);
extern "C" void *igObject_GetNoParentMetaObject(void);
extern "C" int igObject_GetVTable(void);
extern "C" void igObject_EnsureRegistered(void);
extern "C" void *igObject_Register(void);
extern "C" void *igObject_GetMetaObject(void);
extern "C" void igObject_InitFields(void);
extern "C" char *igObject_AllocateRawStorage(int size, int prefix_size, igMemoryPoolView *requested_pool);
extern "C" void *igObject_AllocateRawStorageDefault(int size,int prefix);
extern "C" int thunk_FUN_002ed460__002ff810(int extra0);
extern "C" void igObject_Destroy(void *input);
class igObjectDispatchView;
extern "C" void igObject_ZeroFields(igObjectDispatchView *object);
extern "C" void igObject_ConstructFields(igObjectDispatchView *object);
extern "C" void igObject_ResetFields(igObjectDispatchView *object);
extern "C" void igObject_ResetUnconstructedFields(igObjectDispatchView *object);
extern "C" void igObject_DestructFieldValues(int *arg0);
extern "C" void igObject_ClearFieldValues(int *arg0);
extern "C" void FUN_00300490(void **arg0, int arg1, int arg2);
struct ShallowObject;
extern "C" void FUN_00300600(ShallowObject *self, int source);
extern "C" void FUN_003006a0(ShallowObject *self, ShallowObject *source);
extern "C" void FUN_00300770(ShallowObject *self, int source);
extern "C" int igObject_IsAlikeExactly(void *arg0, void *arg1);
extern "C" void FUN_00300c00(int arg0, int arg1, int arg2);
extern "C" int igObject_CloneViaMetadata(void **source, int copyMode);
extern "C" void *igObject_GetAllocationBase(void *self);
extern "C" int igObject_AllocateStorage(int object, int size);
extern "C" int FUN_00300db0(int object, int size, int alignment);
extern "C" int FUN_00300e00(int object, int size, int option);
extern "C" int FUN_00300e50(int object, int storage, int size);
extern "C" int FUN_00300ea0(int object, int storage, int size, int alignment);
extern "C" void igObject_FreeStorage(int object, int storage);
extern "C" void FUN_00300f50(int object, int storage);
extern "C" int igObject_DuplicateString(int self, int string);
extern "C" int Gap__Core__igObjectDirEntry__vfunc_22(void);
class igObjectDirEntryView;
extern "C" void Gap__Core__igObjectDirEntry__vfunc_38(igObjectDirEntryView *arg0);
extern "C" int igProperty_FindByPointer(void *arg0, void *arg1, int arg2);
extern "C" int igProperty_FindBySortedKey(void *arg0, void *arg1, int arg2);
extern "C" int igProperty_FindInsertionIndex(void *arg0, void *arg1, unsigned int arg2);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_51(void *arg0, int arg1, char *arg2, int arg3, int arg4);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_28(void *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_37(void *arg0, int arg1, int arg2);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_38(int *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_25(void *arg0);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_12(int arg0);
extern "C" void igObjectRefMetaField_InitDefaults(void **self);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_24(int a0, int a1, int a2);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_28(void *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_30(char *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_37(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_02(void);
extern "C" int FUN_00303d70(void *arg0, int extra1);
extern "C" int FUN_00303e50(void *arg0);
extern "C" int FUN_00303e60(void *arg0, int arg1);
extern "C" int *FUN_00303e80(void *arg0, int arg1);
extern "C" void FUN_00304430(const char *arg0, ...);
extern "C" int vprintf(...);
extern "C" int vsnprintf(...);
extern "C" void FUN_003044a0(const char *arg0, int arg1);
extern "C" int FUN_00304550(int arg0, ...);
extern "C" int fprintf(...);
extern "C" int vfprintf(...);
extern "C" int FUN_003045c0(int arg0, int arg1);
extern "C" int fflush(...);
extern "C" void FUN_00304680(void);
extern "C" void FUN_003046d0(void);
extern "C" void Gap__Core__igFolder__vfunc_24(void **arg0);
extern "C" void FUN_00304b10(void *self);
extern "C" void **FUN_00304f00(void *arg0, int arg1, unsigned stackSize);
extern "C" int thunk_FUN_00305000(int extra0);
extern "C" int **FUN_00305400(int **arg0, int extra1);
extern "C" int **FUN_00305440(int **arg0);
extern "C" int **FUN_00305480(int **arg0, int extra1);
extern "C" void Gap__Core__igRawRefMetaField__vfunc_02(void);
extern "C" int FUN_003054d0(void);
extern "C" void FUN_003054e0(int *arg0);
extern "C" int igRefMetaField_GetSize(void);
extern "C" int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4);
extern "C" int FUN_003057a0(void);
extern "C" char *FUN_003057b0(char *s, char ch);
extern "C" void igRefMetaField_Destruct(void);
extern "C" int FUN_00305ce0(void);
extern "C" int FUN_00305cf0(void);
extern "C" void Gap__Core__igRegistry__vfunc_11(void *arg0);
extern "C" int FUN_003064b0(int arg0, int arg1);
extern "C" bool FUN_003065f0(int arg0, int arg1, const char *arg2, int *arg3, int arg4, int arg5);
extern "C" bool FUN_003066b0(int arg0, int arg1, const char *arg2, float *arg3, int arg4, float fparg0);
extern "C" int FUN_00306910(int arg0, int arg1, const char *arg2, int **out, char *def, int create);
extern "C" unsigned char FUN_00306e50(int arg0, int arg1, const char *arg2, char *arg3, int arg4, int arg5);
extern "C" bool FUN_00306f10(char *arg0, int *arg1, int arg2, char *arg3);
extern "C" int FUN_00307200(char *text, int value, void *meta, char *format);
extern "C" int FUN_00307470(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6);
extern "C" int FUN_00307550(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6);
extern "C" int FUN_00307630(void *arg0, int arg1);
extern "C" int FUN_00307650(void *arg0);
extern "C" int FUN_00307660(void *arg0, int arg1, const char *arg2, int arg3);
extern "C" int FUN_0030b730(int, void *, float);
extern "C" int FUN_003076b0(int a0, int a1, const char *a2, float x);
extern "C" int FUN_00307700(void *arg0, int arg1, const char *arg2, int arg3);
extern "C" int FUN_00307750(int arg0, int arg1, const char *arg2, int arg3);
extern "C" int FUN_00307f80(void *arg0, int arg1);
extern "C" int igReportNotice(const char *arg0, ...);
extern "C" int FUN_00308240(const char *arg0, ...);
extern "C" void FUN_003082b0(const char *arg0, ...);
extern "C" int igReportError(const char *arg0, ...);
extern "C" int FUN_00308390(const char *arg0, ...);
extern "C" int FUN_00308400(int arg0, int arg1);
extern "C" int FUN_00308540(int arg0, const char *arg1, int arg2);
extern "C" void FUN_003085c0(void);
extern "C" void FUN_00308770(void);
extern "C" int FUN_00308850(int *p, int extra1);
extern "C" void FUN_00308c00(int *arg0, void *arg1);
extern "C" int igResource_IsDirectoryLoaded(int arg0, void *arg1);
extern "C" int FUN_00309a50(void);
extern "C" int FUN_00309a60(int directory, int name, int metaName, int wanted);
extern "C" void FUN_00309fe0(int arg0);
extern "C" int Gap__Core__igShortMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igShortMetaField__vfunc_57(int *arg0, int arg1, short *arg2);
extern "C" int **FUN_0030a440(int **arg0, int extra1);
extern "C" int **FUN_0030a480(int **arg0);
extern "C" int **FUN_0030a4c0(int **arg0, int extra1);
extern "C" void Gap__Core__igShortMetaField__vfunc_02(int extra0);
extern "C" void FUN_0030a520(void **arg0, short arg1);
extern "C" int Gap__Core__igShortMetaField__vfunc_27(void);
extern "C" int igStringMetaField_ReadRawValue(...);
extern "C" int Gap__Core__igStringArrayMetaField__vfunc_25(void *arg0);
extern "C" void Gap__Core__igStringMetaField__vfunc_12(int arg0);
extern "C" void Gap__Core__igStringMetaField__vfunc_56(int arg0, int a1, int arg2);
extern "C" int igStringMetaField_AssignRetainedToken(...);
extern "C" void Gap__Core__igStringMetaField__vfunc_57(void **output, void *field, void **sourceCell);
extern "C" int igStringMetaField_GetTypeSize(void);
extern "C" void igStringMetaField_SwapValue(void);
extern "C" void Gap__Core__igStringMetaField__vfunc_53(void);
extern "C" void igStringMetaField_ConstructValue(void);
extern "C" void igStringMetaField_SetDefaultText(int *arg0, int arg1);
extern "C" void **FUN_002c3090(...);
extern "C" int igStringMetaField_WriteRawValue(void *self, void *value, void *dst, int a3, int swap);
extern "C" void igStringMetaField_ResetValue(int *arg0, int arg1);
extern "C" void *FUN_0030b2c0(void *arg0, void *arg1);
extern "C" void Gap__Core__igStringMetaField__vfunc_02(void);
extern "C" void igStringObj_Set(int arg0, int arg1);
extern "C" int strlwr(int);
extern "C" void igStringObj_ToLower(void *arg0);
extern "C" int igStringObj_ToInt(void *arg0, int arg1);
extern "C" int igStringObj_ToFloat(void *arg0, int arg1);
extern "C" void FUN_0030b720(int arg0, int arg1, int arg2);
extern "C" void FUN_0030b770(int arg0, int arg1, int arg2);
extern "C" int FUN_0030b7e0(int arg0, int arg1, ...);
extern "C" int FUN_0030b840(int arg0, int extra1, int extra2);
extern "C" void igStringObj_StripDirectory(int *arg0);
extern "C" int FUN_0030ba90(void *arg0, char *arg1);
extern "C" int FUN_0030bb40(char *arg0, char *arg1);
extern "C" int thunk_strcasecmp(const char *s1, const char *s2);
extern "C" int StringChunk_ReturnBlock(...);
extern "C" void *StringTable_Construct(void *arg0, void *arg1, int arg2);
extern "C" void StringTable_SetSynchronization(int arg0);
extern "C" int StringTable_Find(int arg0, int arg1);
extern "C" void *StringTable_Register(int arg0, void *arg1, int arg2, int arg3);
extern "C" void StringTable_RemoveHeader(int arg0, int arg1);
extern "C" int StringTable_DeleteObject(int object);
extern "C" int StringChunk_DeleteObject(int object);
extern "C" void Gap__Core__igStringRefList__vfunc_12(void *self0);
extern "C" void FUN_0030cf20(int a0, int a1);
extern "C" void FUN_0030cf30(int a0, int a1);
extern "C" void FUN_0030cf40(void *arg0);
extern "C" void FUN_0030d050(int arg0);
extern "C" void FUN_0030d0d0(int *arg0, void *arg1, int arg2);
extern "C" char *FUN_0030d1d0(int *arg0, int arg1);
extern "C" int FUN_0030d300(int arg0, int arg1);
extern "C" unsigned short Gap__Core__igStructMetaField__vfunc_25(void *arg0);
extern "C" void Gap__Core__igStructMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igStructMetaField__vfunc_57(int *arg0, void *arg1);
extern "C" void FUN_0030da00(int a0, int a1);
extern "C" void FUN_0030da10(int a0, int a1);
class igSymbolTableView;
extern "C" void FUN_0030daa0(igSymbolTableView *arg0);
extern "C" void FUN_0030e480(void);
extern "C" void FUN_0030e540(void);
extern "C" int Gap__Core__igUnsignedCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2);
extern "C" void Gap__Core__igUnsignedCharMetaField__vfunc_57(int *arg0, int arg1, unsigned char *arg2);
extern "C" int igUnsignedCharMetaField_GetSize(void);
extern "C" void FUN_0030e750(void **arg0, char arg1);
extern "C" int Gap__Core__igUnsignedCharMetaField__vfunc_27(void);
extern "C" int Gap__Core__igUnsignedIntMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igUnsignedIntMetaField__vfunc_57(int *arg0, void *arg1, int *arg2);
extern "C" int FUN_0030e8d0(void);
extern "C" int **FUN_0030e960(int **arg0, int extra1);
extern "C" void Gap__Core__igUnsignedIntMetaField__vfunc_02(int extra0);
extern "C" void FUN_0030e9b0(void **arg0, int arg1);
extern "C" int Gap__Core__igUnsignedIntMetaField__vfunc_27(void);
extern "C" int Gap__Core__igUnsignedLongMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igUnsignedLongMetaField__vfunc_57(int *arg0, int arg1, long long *arg2);
extern "C" int FUN_0030eb30(void);
extern "C" int **FUN_0030eb40(int **arg0, int extra1);
extern "C" int **FUN_0030eb80(int **arg0);
extern "C" int **FUN_0030ebc0(int **arg0, int extra1);
extern "C" void Gap__Core__igUnsignedLongMetaField__vfunc_02(int extra0);
extern "C" void FUN_0030ec10(void **arg0, long long arg1);
extern "C" int Gap__Core__igUnsignedShortMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igUnsignedShortMetaField__vfunc_57(int *arg0, int arg1, unsigned short *arg2);
extern "C" int FUN_0030ed90(void);
extern "C" void FUN_0030eda0(void **arg0, short arg1);
extern "C" int **FUN_0030edd0(int **arg0, int extra1);
extern "C" int **FUN_0030ee10(int **arg0);
extern "C" int **FUN_0030ee50(int **arg0, int extra1);
extern "C" void Gap__Core__igUnsignedShortMetaField__vfunc_02(int extra0);
extern "C" int Gap__Core__igVirtualCFuncMetaField__vfunc_56(int arg0, int arg1, int arg2);
extern "C" void Gap__Core__igVirtualCFuncMetaField__vfunc_57(int *arg0, int arg1, int *arg2);
extern "C" int Gap__Core__igVirtualCFuncMetaField__vfunc_25(void);
extern "C" void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1);
extern "C" void Gap__Core__igVirtualCFuncMetaField__vfunc_30(int *arg0, int arg1);
extern "C" int Gap__Core__igVirtualCFuncMetaField__vfunc_27(void);
extern "C" void FUN_00310b60(void *arg0, unsigned char *arg1, int extra2);
extern "C" int igArenaMemoryPool_DisplayOutstandingAllocationsBlock(...);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_88(void *self0);
extern "C" int strncat(char *, int *, int);
extern "C" char *igMetaEnum_GetNamesByMask(char *arg0, int arg1, int arg2, int arg3);
extern "C" char *igMetaEnum_GetValueName(char *arg0, int arg1, int arg2, int arg3);
extern "C" char *FUN_00312140(char *, int, int, int);
extern "C" char *FUN_00312020(char *, int, int, int);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_87(void *arg0, int extra1);
extern "C" void List_InsertWords(igDataList *list, int index, int count, const void *src);
extern "C" int FUN_00310c00(int);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_103(int *arg0, int arg1);
extern "C" int FUN_00318b40(...);
extern "C" void FUN_00314510(void *, int, int);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_32(void *arg0);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_29(void);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_35(int *statusOut);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_41(int *arg0, char *arg1, unsigned long long arg2);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_43(int *arg0, void *arg1, int arg2);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_99(void *arg0);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_100(void *arg0);
extern "C" int FUN_0031d370(void *arg0);
extern "C" int FUN_0031d390(void *arg0);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_101(void *arg0);
extern "C" void FUN_0031d3f0(void *arg0);
extern "C" void FUN_0031d430(void *arg0);
extern "C" int FUN_0031d460(void *arg0, int arg1);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_63(int *arg0);
class MallocPoolFreeView;
extern "C" void Gap__Core__igArenaMemoryPool__freeSized(MallocPoolFreeView *self, unsigned int size, char **block);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_02(void **self);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_85(void *self, unsigned char *p);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_83(void);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_84(int arg0, unsigned char *p);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_89(void *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_86(void);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_91(void *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_92(void *arg0, int arg1);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_94(void *arg0, void **arg1);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_95(int arg0, unsigned char *p);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_108(void);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_109(void *arg0);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_110(void *arg0);
extern "C" void FUN_003209a0(unsigned char *p);
extern "C" void FUN_00320a20(unsigned char *arg0, int arg1);
extern "C" void FUN_00320aa0(unsigned char *arg0, int arg1);
class ElfFileView;
extern "C" void Gap__Core__igElfFile__vfunc_25(int *result, ElfFileView *self);
extern "C" int FUN_00320f70(void *arg0, int arg1);
extern "C" void FUN_00321530(const char *in, char *out, int size);
extern "C" void Gap__Core__igElfFile__vfunc_29(int *result, void *self, char *mangled, char *out, int size);
extern "C" int *FUN_00321c10(int arg0, int *arg1);
extern "C" char *FUN_00321c50(int arg0, int arg1, char *arg2);
extern "C" void Gap__Core__igElfFile__vfunc_31(int *arg0);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_99(void *arg0);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_100(void *arg0);
extern "C" void FUN_00322820(void *arg0);
extern "C" void FUN_00322860(void *arg0);
extern "C" int FUN_00322890(void *arg0, int arg1);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_63(int *arg0);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_85(int arg0, char *arg1);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_83(void);
extern "C" unsigned int Gap__Core__igMallocMemoryPool__vfunc_84(int arg0, char *arg1);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_89(void *arg0);
extern "C" void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_91(void *arg0);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_92(void *arg0, int arg1);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_94(void *arg0, void **arg1);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_95(int arg0, char *arg1);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_02(int extra0);
extern "C" void thunk_Gap__Core__igObject__constructFields(int extra0, int extra1);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_31(void **arg0);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_24(int *statusOut);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_35(int *statusOut);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_37(int *statusOut);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_39(int *statusOut);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_99(void *arg0);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_100(void *arg0);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_101(void *arg0);
extern "C" void FUN_00326090(void *arg0);
extern "C" int FUN_003260d0(void *arg0, int arg1);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_62(int *arg0);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_63(int *arg0);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_64(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_83(void);
extern "C" void FUN_00326330(void *a0, int a1);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_89(void *arg0);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_86(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_91(void *arg0);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_92(void *arg0, int arg1);
class igPageMemoryPoolView;
extern "C" int FUN_00326920(igPageMemoryPoolView *arg0, int arg1);
extern "C" int FUN_00326a80(igPageMemoryPoolView *arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_00326b80(igPageMemoryPoolView *arg0, int arg1, int arg2);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_87(int extra0, int extra1);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_96(void);
class ProgramFileView;
extern "C" void Gap__Core__igProgramFile__vfunc_25(int *result, ProgramFileView *self);
extern "C" void Gap__Core__igProgramFile__vfunc_27(int *status_out);
extern "C" void Gap__Core__igProgramFile__vfunc_28(int *status_out);
extern "C" void Gap__Core__igProgramFile__vfunc_29(int *status_out);
extern "C" igResult Gap__Core__igStackMemoryPool__vfunc_45(igStackMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_35(int *status_out);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_24(int *arg0, void *arg1, int arg2, long long arg3, char arg4);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_58(void **arg0, int arg1, unsigned int arg2);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_59(void **arg0, int arg1, unsigned int arg2, int arg3);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_89(void *arg0);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_86(int *a, int a1, int a2, int a3, int a4);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_91(void *arg0);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_92(void *arg0, int arg1);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_96(igStackMemoryPool *self, igDataList *list);
class igStandardQueueView;
extern "C" void Gap__Core__igStandardQueue__vfunc_12(igStandardQueueView *self);
extern "C" int **FUN_00328de0(int **arg0);
extern "C" int calloc(...);
extern "C" void realloc(int, int);
class SystemAllocator;
extern "C" void FUN_00328e50(SystemAllocator *self);
extern "C" int FUN_00328ed0(void *arg0, int arg1);
extern "C" int FUN_00328f20(int arg0, int arg1);
extern "C" void FUN_00328f70(int unused, int a, int b);
extern "C" void FUN_00328f80(int arg0, int arg1, int arg2);
extern "C" int FUN_00328f90(SystemAllocator *self, int *arg1);
extern "C" void FUN_00329000(int a0, int a1);
extern "C" void FUN_00329030(SystemAllocator *self, int arg1, int arg2);
extern "C" int FUN_00329070(SystemAllocator *self, int arg1, unsigned int arg2, unsigned int arg3);
extern "C" int FUN_00329570(void);
extern "C" int FUN_003295b0(void);
extern "C" int FUN_003295c0(void);
extern "C" int FUN_00329860(void *self, unsigned int addr, unsigned int len);
extern "C" unsigned int FUN_00329980(void *self, int size);
extern "C" int FUN_00329b00(void);
extern "C" int FUN_00329b10(void);
extern "C" void FUN_00329b20(void *arg0, int *arg1, int *arg2, int *arg3);
extern "C" int FUN_00329b40(void *arg0, void *arg1, int *arg2, int *arg3);
extern "C" void FUN_00329ca0(int unused, unsigned int addr, int len);
struct DumpRegion;
extern "C" DumpRegion *FUN_0032a130(DumpRegion *row, short flags);
extern "C" void FUN_0032a180(DumpRegion *row, const char *annotation);
extern "C" void FUN_0032a1b0(DumpRegion *row, const char *poolName);
extern "C" void FUN_0032a220(void *block);
extern "C" int FUN_0032a260(DumpRegion **a, DumpRegion **b);
extern "C" void FUN_0032a5f0(int extra0);
extern "C" void FUN_0032ab90(int a0, int a1);
extern "C" int FUN_0032aba0(void);
extern "C" void FUN_0032abb0(int *arg0, SystemAllocator *self, int arg2, int arg3);
extern "C" void FUN_0032ac60(int *arg0);
extern "C" int FUN_0032ac70(int arg0, unsigned int arg1);
extern "C" void FUN_0032aca0(int arg0, unsigned int arg1, int arg2);
extern "C" void FUN_0032ace0(int arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_0032ad50(int arg0, unsigned int arg1, int arg2, int arg3, int arg4);
extern "C" void FUN_0032ae00(int arg0, void *arg1);
extern "C" void FUN_0032ae70(void);
extern "C" void FUN_0032aea0(void);
extern "C" void thunk_Gap__Core__igCallStackTracer__vfunc_25(void);
extern "C" int sceClose(...);
class igPsx2FileView;
extern "C" void Gap__Core__igPsx2File__vfunc_24(igPsx2FileView *arg0);
extern "C" void **Gap__Core__igPsx2File__vfunc_25(void **arg0, const char *fileName, int arg2);
extern "C" int sceLseek(...);
extern "C" int sceRead(...);
extern "C" int sceWrite(...);
extern "C" int Gap__Core__igPsx2File__vfunc_38(igPsx2FileView *arg0, int arg1, int arg2);
extern "C" void FUN_0032c0c0(void);
extern "C" char *FUN_0032c110(char *path);
extern "C" char _toupper(...);
extern "C" int sceDopen(int);
extern "C" int sceDclose(int);
extern "C" int sceDread(...);
extern "C" void StringList_AppendRetained(...);
/* sceOpen flags and sceLseek origins (Sony sifdev.h). */
enum { SCE_RDONLY = 0x1, SCE_WRONLY = 0x2, SCE_RDWR = 0x3, SCE_APPEND = 0x100, SCE_CREAT = 0x200, SCE_TRUNC = 0x400 };
enum { SCE_SEEK_SET = 0, SCE_SEEK_CUR = 1, SCE_SEEK_END = 2 };
extern "C" int sceOpen(const char *path, int flags, ...);
extern "C" char *FUN_0032cb50(char *name, int kind);
extern "C" int igPsx2_LoadIopModule(int a, int b, int c, int d, int e);
extern "C" int sceSifLoadModule(...);
extern "C" int FUN_0032cf70(int *arg0, int arg1, int arg2, int arg3, int arg4, int *arg5);
extern "C" void FUN_0032d070(void);
extern "C" int sceDmaReset(...);
extern "C" int sceSifInitCmd(...);
extern "C" int sceSifSetCmdBuffer(...);
extern "C" int sceSifInitRpc(...);
extern "C" int sceFsReset(...);
extern "C" int sceSifLoadFileReset(...);
extern "C" int sceSifSyncIop(...);
extern "C" int sceSifRebootIop(...);
extern "C" int sceCdInit(...);
extern "C" int sceCdMmode(...);
extern "C" void FUN_0032d080(void);
extern "C" void FUN_0032d1f0(void);
extern "C" void FUN_0032d220(void);
extern "C" void FUN_0032d4b0(int *arg0, char *arg1);
extern "C" void Gap__Core__igPsx2IopRpcConnection__vfunc_11(int *arg0);
extern "C" int sceSifBindRpc(...);
extern "C" int sceSifCallRpc(...);
extern "C" int SyncDCache(...);
extern "C" void thunk_iSignalSema(int sema);
extern "C" int p2ReadNanoseconds(...);
extern "C" long long Gap__Core__igPsx2LongTimer__vfunc_37(void);
extern "C" int Gap__Core__igPsx2LongTimer__vfunc_24(void);
extern "C" void p2InitTimer(void);
extern "C" void FUN_0032dae0(void);
extern "C" void FUN_0032daf0(void);
extern "C" void iSyncDCache(char *, char *);
extern "C" void Gap__Core__igPsx2Media__vfunc_09(int arg0);
extern "C" void DIntr(void);
extern "C" void EIntr(void);
extern "C" void sceSifAddCmdHandler(int, void *, int);
extern "C" void FUN_0032ded0(int arg0);
extern "C" int Gap__Core__igPsx2Media__vfunc_32(void);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_26(int *arg0, void *arg1, int arg2);
extern "C" int ReferSemaStatus(...);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_24(int *arg0, int *arg1);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_32(int *arg0, void *arg1);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_35(int *arg0, void *arg1);
extern "C" int iPollSema(int);
extern "C" void FUN_0032f300(void);
extern "C" void FUN_0032f330(void);
extern "C" int FUN_0032f370(void);
extern "C" void FUN_0032f4b0(int arg0, int arg1);
extern "C" void FUN_0032f5d0(int arg0, int arg1);
extern "C" int sbrk(...);
extern "C" int FUN_0032f780(int arg0, int arg1);
extern "C" int p2SleepMilliseconds(int);
extern "C" int FUN_0032f7f0(...);
extern "C" long long __udivdi3(int, int);
extern "C" int iSuspendThread(int);
extern "C" int iResumeThread(int);
extern "C" int iChangeThreadPriority(int, int);
extern "C" int TerminateThread(...);
extern "C" int DeleteThread(...);
extern "C" int Gap__Core__igPsx2Thread__vfunc_23(void *arg0, void *arg1);
class igPsx2ThreadView;
class igSemaphoreView;
class igPsx2ThreadManagerView;
extern "C" void Gap__Core__igPsx2Thread__vfunc_11(igPsx2ThreadView *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_25(int *arg0, int arg1, int arg2);
extern "C" void Gap__Core__igPsx2Thread__vfunc_26(void *arg0, int arg1);
extern "C" void Gap__Core__igPsx2Thread__vfunc_29(int *arg0);
extern "C" void Gap__Core__igPsx2Thread__vfunc_27(int *arg0, void *arg1);
extern "C" void Gap__Core__igPsx2Thread__vfunc_28(int *arg0, void *arg1);
extern "C" void FUN_003303f0(void *arg0);
extern "C" void FUN_00330430(void *arg0);
extern "C" int FUN_003306f0(int extra0);
extern "C" void FUN_00330730(int arg0, int arg1);
extern "C" void FUN_00330770(int arg0, int arg1);
extern "C" void FUN_003307b0(int arg0, int arg1, int arg2);
extern "C" int Gap__Core__igPsx2ThreadManager__vfunc_22(void);
extern "C" int Gap__Core__igPsx2Thread__vfunc_22(void);
extern "C" int Gap__Core__igPsx2Thread__vfunc_42(void);
extern "C" int Gap__Core__igPsx2Thread__vfunc_43(void);
extern "C" void Gap__Core__igPsx2Thread__vfunc_12(void *arg0);
extern "C" void Gap__Core__igPsx2Thread__vfunc_52(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_53(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_54(int *result);
extern "C" int Gap__Core__igPsx2Semaphore__vfunc_22(void);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_12(igSemaphoreView *self);
extern "C" int Gap__Core__igPsx2Media__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igPsx2LongTimer__vfunc_22(void);
extern "C" int __divdi3(...);
extern "C" int __moddi3(...);
extern "C" int __floatdidf(...);
extern "C" int dpadd(...);
extern "C" int dpdiv(...);
extern "C" int litodp(...);
extern "C" int __fixdfdi(...);
extern "C" int dpmul(...);
extern "C" int Gap__Core__igPsx2IopRpcConnection__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igPsx2Folder__vfunc_22(void);
extern "C" int Gap__Core__igPsx2File__vfunc_22(void);
extern "C" int Gap__Core__igPsx2CallStackTracer__vfunc_22(void);
extern "C" void Gap__Core__igUnsignedIntListNoClean__vfunc_18(void);
extern "C" int Gap__Core__igStandardQueue__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igStackMemoryPool__vfunc_22(void);
extern "C" unsigned char Gap__Core__igStackMemoryPool__vfunc_25(void *arg0);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_41(int *status_out);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_83(void);
extern "C" int Gap__Core__igProgramFile__vfunc_22(void);
extern "C" int Gap__Core__igElfFile__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igVirtualCFuncMetaField__vfunc_22(void);
extern "C" int Gap__Core__igVirtualCFuncMetaField__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedShortArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedShortArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedLongArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedLongArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedIntArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedIntArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedCharMetaField__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedCharMetaField__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedCharArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedCharArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igSymbolTable__vfunc_22(void);
extern "C" int Gap__Core__igStructMetaField__vfunc_22(void);
extern "C" int Gap__Core__igStructMetaField__vfunc_23(void);
extern "C" int Gap__Core__igStringTable__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igStringRefList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igStringArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igStringArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igShortArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igShortArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igResource__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igRegistry__vfunc_22(void);
extern "C" int FUN_00331180(void);
extern "C" int Gap__Core__igRawRefArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igRawRefArrayMetaField__vfunc_23(void);
extern "C" igMetaObject *FUN_003311b0(void);
extern "C" int Gap__Core__igPluginHelper__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igObjectRefArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igNamedObjectInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMetaFieldInfo__vfunc_22(void);
extern "C" int Gap__Core__igMemoryRefArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igMemoryRefArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igMemoryPoolInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMemoryPoolContextInfo__vfunc_22(void);
extern "C" int FUN_00331250(void);
extern "C" int Gap__Core__igMemoryFile__vfunc_22(void);
extern "C" int Gap__Core__igMemoryDictionary__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMediaFile__vfunc_22(void);
extern "C" int Gap__Core__igLongMetaField__vfunc_22(void);
extern "C" int Gap__Core__igLongMetaField__vfunc_23(void);
extern "C" int Gap__Core__igLongArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igLongArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igLocationTable__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igIntArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igIntArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igIGBFile__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igFolder__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igFloatMetaField__vfunc_22(void);
extern "C" int Gap__Core__igFloatMetaField__vfunc_23(void);
extern "C" int Gap__Core__igFloatArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igFloatArrayMetaField__vfunc_23(void);
extern "C" igMetaObject *FUN_00331360(void);
extern "C" int Gap__Core__igExternalInfoEntry__vfunc_22(void);
extern "C" int Gap__Core__igExternalIndexedEntry__vfunc_22(void);
extern "C" int Gap__Core__igExternalDirEntry__vfunc_22(void);
extern "C" int Gap__Core__igEventTracker__vfunc_22(void);
extern "C" int Gap__Core__igEnumArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igEnumArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igDriverDatabase__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igDoubleMetaField__vfunc_22(void);
extern "C" int Gap__Core__igDoubleMetaField__vfunc_23(void);
extern "C" int Gap__Core__igDoubleArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igDoubleArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igDirectory__vfunc_22(void);
extern "C" int Gap__Core__igCharArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igCharArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igCallStackTracer__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igCallStackTable__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igBoolArrayMetaField__vfunc_22(void);
extern "C" int Gap__Core__igBoolArrayMetaField__vfunc_23(void);
extern "C" int Gap__Core__igMemoryDescriptorMetaField__vfunc_22(void);
extern "C" int Gap__Core__igMemoryDescriptorMetaField__vfunc_23(void);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_22(void);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_12(void);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_31(void);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_24(int *statusOut);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_25(void);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_26(void);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_29(void);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_22(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_22(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_22(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_83(void);
extern "C" igMetaObject *FUN_00331570(void);
extern "C" int FUN_00331580(void);
extern "C" igMetaObject *FUN_00331590(void);
extern "C" int FUN_003315a0(void);
extern "C" igMetaObject *FUN_003315b0(void);
extern "C" int Gap__Core__igContextList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igContextExtInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igContextExtInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igContextExtList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igBoolList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igCharListNoClean__vfunc_22(void);
extern "C" void Gap__Core__igCharListNoClean__vfunc_18(void);
extern "C" igMetaObject *Gap__Core__igCharList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igIntListNoClean__vfunc_22(void);
extern "C" void Gap__Core__igIntListNoClean__vfunc_18(void);
extern "C" int igIntList_GetMetaObject_Virtual(void);
extern "C" igMetaObject *Gap__Core__igLongList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igUnsignedIntListNoClean__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igUnsignedShortList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igShortList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igShortListList__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedCharList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igFloatList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igFloatListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igPointerList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igPointerListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMetaObjectList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMetaObjectListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMetaFieldList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igIntListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igObjectListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igStringRefListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igDependencyMetaField__vfunc_22(void);
extern "C" int Gap__Core__igDependencyMetaField__vfunc_23(void);
extern "C" int Gap__Core__igDependencyList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igDirectoryList__vfunc_22(void);
extern "C" int FUN_003317b0(void);
extern "C" int FUN_003317c0(void);
extern "C" int Gap__Core__igErrorHandler__vfunc_22(void);
extern "C" int Gap__Core__igInfoList__vfunc_22(void);
extern "C" int FUN_003317f0(void);
extern "C" int FUN_00331800(void);
extern "C" igMetaObject *FUN_00331810(void);
extern "C" igMetaObject *FUN_00331820(void);
extern "C" int Gap__Core__igLibraryList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMediaList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMemoryFileEntry__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMemoryFileEntryList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igMemoryPoolInfoList__vfunc_22(void);
extern "C" int Gap__Core__igMemoryRefMetaField__vfunc_22(void);
extern "C" int Gap__Core__igMemoryRefMetaField__vfunc_23(void);
extern "C" int Gap__Core__igMetaEnum__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igNamedObjectList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igObjectRefMetaField__vfunc_22(void);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_23(void);
extern "C" int Gap__Core__igObjectStringMap__vfunc_22(void);
extern "C" int Gap__Core__igPluginRepository__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igPluginRepositoryList__vfunc_22(void);
extern "C" int FUN_00331910(void);
extern "C" int FUN_00331920(void);
extern "C" int Gap__Core__igRegistryValue__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igRegistryValueList__vfunc_22(void);
extern "C" int FUN_00331950(void);
extern "C" int FUN_00331960(void);
extern "C" igMetaObject *FUN_00331970(void);
extern "C" int FUN_00331980(void);
extern "C" int Gap__Core__igStringObj__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igStringObjList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igThreadList__vfunc_22(void);
extern "C" igMetaObject *Gap__Core__igNonRefCountedThreadList__vfunc_22(void);
extern "C" int FUN_003319d0(void);
extern "C" int FUN_003319e0(void);
extern "C" igMetaObject *FUN_003319f0(void);
extern "C" int FUN_00331a00(void);
extern "C" igMetaObject *FUN_00331a10(void);
extern "C" int FUN_00331a20(void);
extern "C" int Gap__Core__igContextList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igNonRefCountedThreadList__vfunc_24(void);
extern "C" int Gap__Core__igDependencyList__vfunc_23(void);
extern "C" int Gap__Core__igPointerList__vfunc_23(void);
extern "C" int Gap__Core__igFloatList__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedCharList__vfunc_23(void);
extern "C" int Gap__Core__igShortList__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedShortList__vfunc_23(void);
extern "C" int Gap__Core__igIntList__vfunc_23(void);
extern "C" int Gap__Core__igCharList__vfunc_23(void);
extern "C" int Gap__Core__igBoolList__vfunc_23(void);
extern "C" int Gap__Core__igStringRefList__vfunc_23(void);
extern "C" igMetaObject *Gap__Core__igContextExtList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igContextExtInfoList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMediaList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMemoryFileEntryList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMemoryPoolInfoList__vfunc_24(void);
extern "C" int Gap__Core__igInfoList__vfunc_24(void);
extern "C" int Gap__Core__igPluginRepositoryList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igRegistryValueList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igDirectoryList__vfunc_24(void);
extern "C" igMetaObject *FUN_00331c20(void);
extern "C" igMetaObject *Gap__Core__igStringObjList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igThreadList__vfunc_24(void);
extern "C" int Gap__Bec__beDataObjList__vfunc_22(void);
extern "C" int Gap__Core__igLibraryList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igStringRefListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igObjectListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igIntListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMetaFieldList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMetaObjectListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igMetaObjectList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igPointerListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igFloatListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Core__igShortListList__vfunc_24(void);
extern "C" unsigned char DAT_00554bf4;
extern "C" igMetaObject *g_igVirtualCFuncMetaField_metaObject[4];
extern "C" igMetaObject *igVirtualCFuncMetaField_GetMetaObject(void);
extern "C" int DAT_0052e130[4];
extern "C" int g_igMetaField_vtable[4];
extern "C" char igMetaField_GetPublishedMetaObject[];
extern "C" char g_igVirtualCFuncMetaField_callbackList[];
extern "C" char igVirtualCFuncMetaField_className[];
extern "C" void * DAT_005856e0[4];
extern "C" igMetaObject *g_igUnsignedShortMetaField_metaObject[4];
extern "C" unsigned char * g_objectSystem[4];
extern "C" igMetaObject *igUnsignedShortMetaField_GetMetaObject(void);
extern "C" char g_igUnsignedShortMetaField_callbackList[];
extern "C" char igUnsignedShortMetaField_className[];
extern "C" void * DAT_005856f0[4];
extern "C" igMetaObject *g_igUnsignedShortArrayMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedShortArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052e230[4];
extern "C" char igUnsignedShortMetaField_GetPublishedMetaObject[];
extern "C" char g_igUnsignedShortArrayMetaField_callbackList[];
extern "C" char igUnsignedShortArrayMetaField_className[];
extern "C" int g_igUnsignedShortArrayMetaField_ctorTable[4];
extern "C" int g_igUnsignedShortArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf2c8[4];
extern "C" int DAT_004bf2d0[4];
extern "C" igUnsignedShortArrayMetaField *g_igUnsignedShortArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igUnsignedLongMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedLongMetaField_GetMetaObject(void);
extern "C" char g_igUnsignedLongMetaField_callbackList[];
extern "C" char igUnsignedLongMetaField_className[];
extern "C" void * DAT_00585718[4];
extern "C" igMetaObject *g_igUnsignedLongArrayMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedLongArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052e330[4];
extern "C" char igUnsignedLongMetaField_GetPublishedMetaObject[];
extern "C" char g_igUnsignedLongArrayMetaField_callbackList[];
extern "C" char igUnsignedLongArrayMetaField_className[];
extern "C" int g_igUnsignedLongArrayMetaField_ctorTable[4];
extern "C" int g_igUnsignedLongArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf2f8[4];
extern "C" int DAT_004bf300[4];
extern "C" igUnsignedLongArrayMetaField *g_igUnsignedLongArrayMetaField_descriptor[4];
extern "C" unsigned char * g_objectSystem[4];
extern "C" igMetaObject *g_igUnsignedIntMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedIntMetaField_GetMetaObject(void);
extern "C" char g_igUnsignedIntMetaField_callbackList[];
extern "C" char igUnsignedIntMetaField_className[];
extern "C" void * g_igUnsignedIntMetaField_descriptor[4];
extern "C" igMetaObject *g_igUnsignedIntArrayMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedIntArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052e430[4];
extern "C" char igUnsignedIntMetaField_GetPublishedMetaObject[];
extern "C" char g_igUnsignedIntArrayMetaField_callbackList[];
extern "C" char igUnsignedIntArrayMetaField_className[];
extern "C" int g_igUnsignedIntArrayMetaField_ctorTable[4];
extern "C" int g_igUnsignedIntArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf328[4];
extern "C" int DAT_004bf330[4];
typedef struct LST { char pad[12]; int count; } LST;
extern "C" igUnsignedIntArrayMetaField *g_igUnsignedIntArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igUnsignedCharMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedCharMetaField_GetMetaObject(void);
extern "C" int DAT_0052e530[4];
extern "C" char g_igUnsignedCharMetaField_callbackList[];
extern "C" char igUnsignedCharMetaField_className[];
extern "C" void * g_igUnsignedCharMetaField_descriptor[4];
extern "C" igMetaObject *g_igUnsignedCharArrayMetaField_metaObject[4];
extern "C" igMetaObject *igUnsignedCharArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052e630[4];
extern "C" char igUnsignedCharMetaField_GetPublishedMetaObject[];
extern "C" char g_igUnsignedCharArrayMetaField_callbackList[];
extern "C" char igUnsignedCharArrayMetaField_className[];
extern "C" int g_igUnsignedCharArrayMetaField_ctorTable[4];
extern "C" int g_igUnsignedCharArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf358[4];
extern "C" int DAT_004bf360[4];
extern "C" igUnsignedCharArrayMetaField *g_igUnsignedCharArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igTimer_metaObject[4];
extern "C" igMetaObject *igTimer_GetMetaObject(void);
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igTimer_className[];
extern "C" igMetaObject *g_igThreadManager_metaObject[4];
extern "C" igMetaObject *igThreadManager_GetMetaObject(void);
extern "C" char g_igThreadManager_callbackList[];
extern "C" char igThreadManager_className[];
extern "C" int g_igThreadManager_ctorTable[4];
extern "C" int g_igThreadManager_fieldTable[4];
extern "C" int DAT_004bf388[4];
extern "C" int DAT_004bf390[4];
extern "C" int DAT_004bf3a0[4];
extern "C" int DAT_004bf3c0[4];
extern "C" int text_Priority[4];
extern "C" int DAT_005857a8[4];
extern "C" int DAT_004bf3d8[4];
extern "C" int DAT_004bf3e0[4];
extern "C" int text_State[4];
extern "C" int DAT_005857b0[4];
extern "C" int DAT_004bf3e8[4];
extern "C" int DAT_004bf3f8[4];
extern "C" int text_Scope[4];
extern "C" int DAT_005857b8[4];
extern "C" int DAT_004bf408[4];
extern "C" int DAT_004bf410[4];
extern "C" int text_Type[4];
extern "C" int DAT_005857c0[4];
extern "C" igMetaObject *g_igThread_metaObject[4];
extern "C" igMetaObject *igThread_GetMetaObject(void);
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" char igThread_className[];
extern "C" int g_igThread_ctorTable[4];
extern "C" int g_igThread_fieldTable[4];
extern "C" int DAT_004bf480[4];
extern "C" int DAT_004bf4b0[4];
extern "C" int DAT_004bf4d8[4];
extern "C" int DAT_004bf4e0[4];
extern "C" int DAT_004bf4e8[4];
extern "C" int DAT_004bf4f0[4];
extern "C" igMetaObject *g_igNonRefCountedThreadList_metaObject[4];
extern "C" igMetaObject *igNonRefCountedThreadList_GetMetaObject(void);
extern "C" int DAT_005333c0[4];
extern "C" char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern "C" char g_igNonRefCountedThreadList_callbackList[];
extern "C" char igNonRefCountedThreadList_className[];
extern "C" igMetaObject *g_igThreadList_metaObject[4];
extern "C" igMetaObject *igThreadList_GetMetaObject(void);
extern "C" int DAT_00533350[4];
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char g_igThreadList_callbackList[];
extern "C" char igThreadList_className[];
extern "C" igMetaObject *g_igSymbolTable_metaObject[4];
extern "C" igMetaObject *igSymbolTable_GetMetaObject(void);
extern "C" int DAT_0052e730[4];
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord {
    ObjectRefTarget *value;
    /* Both releases keep the word's address taken; release reads the field once into a local,
     * releaseField reads the field directly each time. */
    inline void release() {
        ObjectRefTarget **self = &value;
        if (self) {
            ObjectRefTarget *object = value;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((void *)object);
            }
        }
    }
    inline void releaseField() {
        ObjectRefTarget **self = &value;
        if (self) {
            if (value) {
                --value->references;
                if (((unsigned long long)(long long)value->references & 0x7fffffULL) == 0)
                    igObject_Destroy(value);
            }
        }
    }
} ObjectRefWord;
extern "C" ObjectRefWord *FUN_002b8640(ObjectRefWord *self,int delete_storage);
extern "C" ObjectRefWord *FUN_002b8740(ObjectRefWord *self,int delete_storage);
extern "C" char g_igSymbolTable_callbackList[];
extern "C" char igSymbolTable_className[];
extern "C" int g_igSymbolTable_ctorTable[4];
extern "C" int g_igSymbolTable_fieldTable[4];
extern "C" int DAT_004bf580[4];
extern "C" int DAT_004bf5b0[4];
extern "C" igMetaObject *g_igStructMetaField_metaObject[4];
extern "C" igMetaObject *igStructMetaField_GetMetaObject(void);
extern "C" int DAT_0052e7c0[4];
extern "C" char g_igStructMetaField_callbackList[];
extern "C" char igStructMetaField_className[];
extern "C" int igStructMetaField_InitFields_002b8b50[4];
extern "C" int g_igStructMetaField_ctorTable[4];
extern "C" int g_igStructMetaField_fieldTable[4];
extern "C" int DAT_004bf600[4];
extern "C" int DAT_004bf610[4];
extern "C" int text_size[4];
extern "C" igMetaObject *g_igStructMetaField_metaObject[4];
extern "C" int DAT_00585890[4];
extern "C" igStructMetaField *DAT_00585888[4];
extern "C" igMetaObject *g_igStringTable_metaObject[4];
extern "C" igMetaObject *igStringTable_GetMetaObject(void);
extern "C" int DAT_0052e8c0[4];
extern "C" igObject **FUN_002b8f10(igObject **arg0, short arg1);
extern "C" char g_igStringTable_callbackList[];
extern "C" char igStringTable_className[];
extern "C" int g_igStringTable_ctorTable[4];
extern "C" int g_igStringTable_fieldTable[4];
extern "C" int DAT_004bf650[4];
extern "C" int DAT_004bf660[4];
extern "C" igMetaObject *g_igStringRefList_metaObject[4];
extern "C" igMetaObject *igStringRefList_GetMetaObject(void);
extern "C" int DAT_0052e930[4];
extern "C" char igDataList_GetPublishedMetaObject[];
extern "C" char igStringRefList_className[];
extern "C" int igStringRefList_InitFields_002b9290[4];
extern "C" int DAT_005858e0[4];
extern "C" igMetaObject *g_igStringObjList_metaObject[4];
extern "C" igMetaObject *igStringObjList_GetMetaObject(void);
extern "C" int DAT_005332e0[4];
extern "C" char g_igStringObjList_callbackList[];
extern "C" char igStringObjList_className[];
extern "C" igMetaObject *g_igStringObj_metaObject[4];
extern "C" igMetaObject *igStringObj_GetMetaObject(void);
extern "C" int DAT_00533280[4];
extern "C" char igStringObj_className[];
extern "C" int g_igStringObj_ctorTable[4];
extern "C" int g_igStringObj_fieldTable[4];
extern "C" int DAT_004bf688[4];
extern "C" int DAT_004bf690[4];
extern "C" igMetaObject *g_igStringMetaField_metaObject[4];
extern "C" igMetaObject *igStringMetaField_GetMetaObject(void);
extern "C" char igRefMetaField_GetPublishedMetaObject[];
extern "C" char g_igStringMetaField_callbackList[];
extern "C" char igStringMetaField_className[];
extern "C" igMetaObject *g_igRefMetaField_metaObject[4];
extern "C" int g_igStringMetaField_ctorTable[4];
extern "C" int g_igStringMetaField_fieldTable[4];
extern "C" int DAT_004bf6b0[4];
extern "C" int DAT_004bf6b8[4];
extern "C" int text_shallowCopyMethod[4];
extern "C" int text_destruct[4];
extern "C" int DAT_00585918[4];
extern "C" int DAT_00585920[4];
extern "C" int *DAT_00585910[4];
extern "C" igMetaObject *g_igStringArrayMetaField_metaObject[4];
extern "C" igMetaObject *igStringArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052e990[4];
extern "C" char igStringMetaField_GetPublishedMetaObject[];
extern "C" char g_igStringArrayMetaField_callbackList[];
extern "C" char igStringArrayMetaField_className[];
extern "C" int g_igStringArrayMetaField_ctorTable[4];
extern "C" int g_igStringArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf6d8[4];
extern "C" int DAT_004bf6e0[4];
extern "C" int *DAT_00585938[4];
extern "C" igMetaObject *g_igShortMetaField_metaObject[4];
extern "C" igMetaObject *igShortMetaField_GetMetaObject(void);
extern "C" char g_igShortMetaField_callbackList[];
extern "C" char igShortMetaField_className[];
extern "C" void * g_igShortMetaField_descriptor[4];
extern "C" igMetaObject *g_igShortArrayMetaField_metaObject[4];
extern "C" igMetaObject *igShortArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052ea90[4];
extern "C" char igShortMetaField_GetPublishedMetaObject[];
extern "C" char g_igShortArrayMetaField_callbackList[];
extern "C" char igShortArrayMetaField_className[];
extern "C" int g_igShortArrayMetaField_ctorTable[4];
extern "C" int g_igShortArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf708[4];
extern "C" int DAT_004bf710[4];
extern "C" igShortArrayMetaField *g_igShortArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igSemaphore_metaObject[4];
extern "C" igMetaObject *igSemaphore_GetMetaObject(void);
extern "C" char igSemaphore_className[];
extern "C" int igSemaphore_InitFields_002ba7c0[4];
extern "C" ObjectRefWord *FUN_002ba7f0(ObjectRefWord *self,int delete_storage);
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" void **FUN_002ba970(struct Ref **self, short flag);
extern "C" igMetaObject *g_igResource_metaObject[4];
extern "C" igMetaObject *igResource_GetMetaObject(void);
extern "C" int DAT_0052eb90[4];
extern "C" igQueue **FUN_002bacc0(igQueue **arg0, short arg1);
extern "C" char g_igResource_callbackList[];
extern "C" char igResource_className[];
extern "C" int g_igResource_ctorTable[4];
extern "C" int g_igResource_fieldTable[4];
extern "C" int DAT_004bf7e0[4];
extern "C" int DAT_004bf830[4];
extern "C" igMetaObject *g_igRegistry_metaObject[4];
extern "C" igMetaObject *igRegistry_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int DAT_0052ebf0[4];
extern "C" char g_igRegistry_callbackList[];
extern "C" char igRegistry_className[];
extern "C" int g_igRegistry_ctorTable[4];
extern "C" int g_igRegistry_fieldTable[4];
extern "C" int DAT_004bf8d0[4];
extern "C" int DAT_004bf8f0[4];
extern "C" igMetaObject *g_igRegistryValueList_metaObject[4];
extern "C" igMetaObject *igRegistryValueList_GetMetaObject(void);
extern "C" int DAT_00533010[4];
extern "C" char g_igRegistryValueList_callbackList[];
extern "C" char igRegistryValueList_className[];
extern "C" igMetaObject *g_igRegistryValue_metaObject[4];
extern "C" igMetaObject *igRegistryValue_GetMetaObject(void);
extern "C" int DAT_00532fb0[4];
extern "C" char g_igRegistryValue_callbackList[];
extern "C" char igRegistryValue_className[];
extern "C" int g_igRegistryValue_ctorTable[4];
extern "C" int g_igRegistryValue_fieldTable[4];
extern "C" int DAT_004bf938[4];
extern "C" int DAT_004bf948[4];
extern "C" igMetaObject *igRefMetaField_GetMetaObject(void);
extern "C" char g_igRefMetaField_callbackList[];
extern "C" char igRefMetaField_className[];
extern "C" int g_igRefMetaField_ctorTable[4];
extern "C" int g_igRefMetaField_fieldTable[4];
extern "C" int DAT_004bf970[4];
extern "C" int DAT_004bf978[4];
extern "C" void * g_igRefMetaField_descriptor[4];
extern "C" igMetaObject *g_igRawRefMetaField_metaObject[4];
extern "C" igMetaObject *igRawRefMetaField_GetMetaObject(void);
extern "C" char g_igRawRefMetaField_callbackList[];
extern "C" char igRawRefMetaField_className[];
extern "C" void * g_igRawRefMetaField_descriptor[4];
extern "C" igMetaObject *g_igRawRefArrayMetaField_metaObject[4];
extern "C" igMetaObject *igRawRefArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052ed50[4];
extern "C" char igRawRefMetaField_GetPublishedMetaObject[];
extern "C" char g_igRawRefArrayMetaField_callbackList[];
extern "C" char igRawRefArrayMetaField_className[];
extern "C" int g_igRawRefArrayMetaField_ctorTable[4];
extern "C" int g_igRawRefArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf9a0[4];
extern "C" int DAT_004bf9a8[4];
extern "C" igRawRefArrayMetaField *g_igRawRefArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igQueue_metaObject[4];
extern "C" igMetaObject *igQueue_GetMetaObject(void);
extern "C" char g_igQueue_callbackList[];
extern "C" char igQueue_className[];
extern "C" int g_igQueue_ctorTable[4];
extern "C" int g_igQueue_fieldTable[4];
extern "C" int DAT_004bf9c8[4];
extern "C" int DAT_004bf9d0[4];
extern "C" igMetaObject *g_igPluginHelper_metaObject[4];
extern "C" igMetaObject *igPluginHelper_GetMetaObject(void);
extern "C" int DAT_0052eee0[4];
extern "C" ObjectRefWord *FUN_002bc540(ObjectRefWord *self,int delete_storage);
extern "C" char g_igPluginHelper_callbackList[];
extern "C" char igPluginHelper_className[];
extern "C" int g_igPluginHelper_ctorTable[4];
extern "C" int g_igPluginHelper_fieldTable[4];
extern "C" int DAT_004bfa10[4];
extern "C" int DAT_004bfa20[4];
extern "C" int DAT_004f6340[4];
extern "C" igMetaObject *g_igPluginRepositoryList_metaObject[4];
extern "C" igMetaObject *igPluginRepositoryList_GetMetaObject(void);
extern "C" int DAT_00532e40[4];
extern "C" char g_igPluginRepositoryList_callbackList[];
extern "C" char igPluginRepositoryList_className[];
extern "C" int DAT_004bfa38[4];
extern "C" int DAT_004bfa48[4];
extern "C" int LOCATION_TYPE[4];
extern "C" int DAT_00585ae8[4];
extern "C" igMetaObject *g_igPluginRepository_metaObject[4];
extern "C" igMetaObject *igPluginRepository_GetMetaObject(void);
extern "C" int g_igNamedObject_vtable[4];
extern "C" int DAT_00532de0[4];
extern "C" char igPluginRepository_className[];
extern "C" int g_igPluginRepository_ctorTable[4];
extern "C" int g_igPluginRepository_fieldTable[4];
extern "C" int DAT_004bfa68[4];
extern "C" int DAT_004bfa70[4];
extern "C" igMetaObject *g_igPluginRepository_metaObject[4];
extern "C" igMetaObject *g_igObjectStringMap_metaObject[4];
extern "C" igMetaObject *igObjectStringMap_GetMetaObject(void);
extern "C" int DAT_00532d80[4];
extern "C" char g_igObjectStringMap_callbackList[];
extern "C" char igObjectStringMap_className[];
extern "C" int g_igObjectStringMap_ctorTable[4];
extern "C" int g_igObjectStringMap_fieldTable[4];
extern "C" int DAT_004bfa98[4];
extern "C" int DAT_004bfaa0[4];
extern "C" igMetaObject *g_igObjectRefMetaField_metaObject[4];
extern "C" igMetaObject *igObjectRefMetaField_GetMetaObject(void);
extern "C" int g_igObjectRefMetaField_vtable[4];
extern "C" char g_igObjectRefMetaField_callbackList[];
extern "C" char igObjectRefMetaField_className[];
extern "C" int g_igObjectRefMetaField_ctorTable[4];
extern "C" int g_igObjectRefMetaField_fieldTable[4];
extern "C" int DAT_004bfad8[4];
extern "C" int DAT_004bfae8[4];
extern "C" igObjectRefMetaField *g_igObjectRefMetaField_descriptor[4];
extern "C" igMetaObject *g_igObjectRefArrayMetaField_metaObject[4];
extern "C" igMetaObject *igObjectRefArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052ef40[4];
extern "C" char igObjectRefMetaField_GetPublishedMetaObject[];
extern "C" char g_igObjectRefArrayMetaField_callbackList[];
extern "C" char igObjectRefArrayMetaField_className[];
extern "C" int g_igObjectRefArrayMetaField_ctorTable[4];
extern "C" int g_igObjectRefArrayMetaField_fieldTable[4];
extern "C" int DAT_004bfb10[4];
extern "C" int DAT_004bfb18[4];
extern "C" igObjectRefArrayMetaField *DAT_00585b50[4];
extern "C" igMetaObject *g_igObjectList_metaObject[4];
extern "C" igMetaObject *igObjectList_GetMetaObject(void);
extern "C" int DAT_005249b0[4];
extern "C" char igObjectList_className[];
extern "C" char data[];
extern "C" int g_igObjectList_dataDescriptorCell[4];
extern "C" igMetaObject *g_igObjectDirEntry_metaObject[4];
extern "C" igMetaObject *igObjectDirEntry_GetMetaObject(void);
extern "C" int DAT_0052f040[4];
extern "C" char igDirEntry_GetPublishedMetaObject[];
extern "C" char g_igObjectDirEntry_callbackList[];
extern "C" char igObjectDirEntry_className[];
extern "C" igMetaObject *g_igDirEntry_metaObject[4];
extern "C" int g_igObjectDirEntry_ctorTable[4];
extern "C" int g_igObjectDirEntry_fieldTable[4];
extern "C" int DAT_004bfb70[4];
extern "C" int DAT_004bfb90[4];
extern "C" int text_NoMeta[4];
extern "C" int text_ref[4];
extern "C" igMetaField *DAT_00585b98[4];
extern "C" igMetaObject *g_igObject_metaObject[4];
extern "C" igMetaObject *g_igNonRefCountedObjectList_metaObject[4];
extern "C" igMetaObject *igNonRefCountedObjectList_GetMetaObject(void);
extern "C" int DAT_00524500[4];
extern "C" char igNonRefCountedObjectList_className[];
extern "C" int igNonRefCountedObjectList_InitFields_002bddc0[4];
extern "C" int DAT_00585bb8[4];
extern "C" igMetaObject *g_igNamedObjectInfo_metaObject[4];
extern "C" igMetaObject *igNamedObjectInfo_GetMetaObject(void);
extern "C" int DAT_0052f150[4];
extern "C" char igInfo_GetPublishedMetaObject[];
extern "C" char g_igNamedObjectInfo_callbackList[];
extern "C" char igNamedObjectInfo_className[];
extern "C" int g_igNamedObjectInfo_ctorTable[4];
extern "C" int g_igNamedObjectInfo_fieldTable[4];
extern "C" int DAT_004bfbc0[4];
extern "C" int DAT_004bfbc8[4];
extern "C" igMetaObject *g_igNamedObjectList_metaObject[4];
extern "C" igMetaObject *igNamedObjectList_GetMetaObject(void);
extern "C" int DAT_00532c10[4];
extern "C" char g_igNamedObjectList_callbackList[];
extern "C" char igNamedObjectList_className[];
extern "C" igMetaObject *g_igNamedObject_metaObject[4];
extern "C" igMetaObject *igNamedObject_GetMetaObject(void);
extern "C" char igNamedObject_className[];
extern "C" int g_igNamedObject_ctorTable[4];
extern "C" int g_igNamedObject_fieldTable[4];
extern "C" int DAT_004bfbe8[4];
extern "C" int DAT_004bfbf0[4];
extern "C" igMetaObject *g_igMetaObject_metaObject[4];
extern "C" igMetaObject *igMetaObject_GetMetaObject(void);
extern "C" int g_igMetaObject_vtable[4];
extern "C" char g_igMetaObject_callbackList[];
extern "C" char igMetaObject_className[];
extern "C" int g_igMetaObject_ctorTable[4];
extern "C" int g_igMetaObject_fieldTable[4];
extern "C" int DAT_004bfcf0[4];
extern "C" int DAT_004bfd60[4];
extern "C" igMetaObject *g_igMetaFieldInfo_metaObject_00585cb8[4];
extern "C" igMetaObject *igMetaFieldInfo_GetMetaObject(void);
extern "C" int DAT_0052f1c0[4];
extern "C" char igMetaFieldInfo_className[];
extern "C" int DAT_004bfdd0[4];
extern "C" int DAT_004bfde0[4];
extern "C" int text_ResetType[4];
extern "C" int DAT_00585cc0[4];
extern "C" igMetaObject *g_igMetaField_metaObject[4];
extern "C" igMetaObject *igMetaField_GetMetaObject(void);
extern "C" char g_igMetaField_callbackList[];
extern "C" char igMetaField_className[];
extern "C" int g_igMetaField_ctorTable[4];
extern "C" int g_igMetaField_fieldTable[4];
extern "C" int DAT_004bfea0[4];
extern "C" int DAT_004bfef0[4];
struct Fld { char p0[38]; char f38; char f39; char f40; char p41[12]; char f53; char p54[2]; int f56; char f60; char p61[3]; char f64; char f65; };
extern "C" igMetaObject *g_igMetaEnum_metaObject[4];
extern "C" igMetaObject *igMetaEnum_GetMetaObject(void);
extern "C" int DAT_00532b50[4];
extern "C" char g_igMetaEnum_callbackList[];
extern "C" char igMetaEnum_className[];
extern "C" int g_igMetaEnum_ctorTable[4];
extern "C" int g_igMetaEnum_fieldTable[4];
extern "C" int DAT_004bff68[4];
extern "C" int DAT_004bff78[4];
extern "C" igMemoryRefMetaField *igMemoryRefMetaField_Clone(igMemoryRefMetaField *source, int copyMode);
extern "C" igMetaObject *g_igMemoryRefMetaField_metaObject[4];
extern "C" igMetaObject *igMemoryRefMetaField_GetMetaObject(void);
extern "C" int g_igMemoryRefMetaField_vtable[4];
extern "C" int g_igRefMetaField_vtable[4];
extern "C" void *FUN_002bf4c0(igMemoryRefMetaField *arg0, long long arg1);
extern "C" void *FUN_002bf5e0(igRefMetaField *arg0, short arg1);
extern "C" char g_igMemoryRefMetaField_callbackList[];
extern "C" char igMemoryRefMetaField_className[];
extern "C" int g_igMemoryRefMetaField_ctorTable[4];
extern "C" int g_igMemoryRefMetaField_fieldTable[4];
extern "C" int DAT_004bffe0[4];
extern "C" int DAT_004c0000[4];
extern "C" int DAT_004c0020[4];
extern "C" int text_resetMethod[4];
extern "C" igMetaObject *g_igMemoryRefMetaField_metaObject[4];
extern "C" igMetaField *DAT_00585d90[4];
extern "C" igMetaField *DAT_00585db8[4];
extern "C" igMemoryRefMetaField *DAT_00585d88[4];
extern "C" igMetaObject *g_igMemoryRefArrayMetaField_metaObject_00585de0[4];
extern "C" igMetaObject *igMemoryRefArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052f330[4];
extern "C" char igMemoryRefMetaField_GetPublishedMetaObject[];
extern "C" char g_igMemoryRefArrayMetaField_callbackList[];
extern "C" char igMemoryRefArrayMetaField_className[];
extern "C" int g_igMemoryRefArrayMetaField_ctorTable[4];
extern "C" int g_igMemoryRefArrayMetaField_fieldTable[4];
extern "C" int DAT_004c0040[4];
extern "C" int DAT_004c0048[4];
extern "C" igMemoryRefArrayMetaField *DAT_00585de8[4];
extern "C" igMetaObject *g_igMemoryPoolInfoList_metaObject[4];
extern "C" igMetaObject *igMemoryPoolInfoList_GetMetaObject(void);
extern "C" int DAT_005329e0[4];
extern "C" char g_igMemoryPoolInfoList_callbackList[];
extern "C" char igMemoryPoolInfoList_className[];
extern "C" igMetaObject *g_igMemoryPoolInfo_metaObject[4];
extern "C" igMetaObject *igMemoryPoolInfo_GetMetaObject(void);
extern "C" int DAT_0052f430[4];
extern "C" char igMemoryPoolInfo_className[];
extern "C" int g_igMemoryPoolInfo_ctorTable[4];
extern "C" int g_igMemoryPoolInfo_fieldTable[4];
extern "C" int DAT_004c00e0[4];
extern "C" int DAT_004c0120[4];
extern "C" igMetaObject *g_igMemoryPoolContextInfo_metaObject_00585e88[4];
extern "C" igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void);
extern "C" int DAT_0052f4a0[4];
extern "C" char g_igMemoryPoolContextInfo_callbackList[];
extern "C" char igMemoryPoolContextInfo_className[];
extern "C" int g_igMemoryPoolContextInfo_ctorTable[4];
extern "C" int g_igMemoryPoolContextInfo_fieldTable[4];
extern "C" int DAT_004c0178[4];
extern "C" int DAT_004c0180[4];
extern "C" igMetaObject *g_igMemoryPool_metaObject[4];
extern "C" igMetaObject *igMemoryPool_GetMetaObject(void);
extern "C" char igMemoryPool_className[];
extern "C" int g_igMemoryPool_ctorTable[4];
extern "C" int g_igMemoryPool_fieldTable[4];
extern "C" int DAT_004c0210[4];
extern "C" int DAT_004c0250[4];
extern "C" igMetaObject *g_igMemoryFile_metaObject[4];
extern "C" igMetaObject *igMemoryFile_GetMetaObject(void);
extern "C" int DAT_0052f7b0[4];
extern "C" int DAT_00530150[4];
extern "C" void *FUN_002c0790(igFile *arg0, short arg1);
extern "C" char igFile_GetPublishedMetaObject[];
extern "C" char igMemoryFile_className[];
extern "C" igMetaObject *g_igFile_metaObject[4];
extern "C" int g_igMemoryFile_ctorTable[4];
extern "C" int g_igMemoryFile_fieldTable[4];
extern "C" int DAT_004c02b0[4];
extern "C" int DAT_004c02c0[4];
extern "C" igMetaObject *g_igMemoryFileEntryList_metaObject[4];
extern "C" igMetaObject *igMemoryFileEntryList_GetMetaObject(void);
extern "C" int DAT_00532970[4];
extern "C" char g_igMemoryFileEntryList_callbackList[];
extern "C" char igMemoryFileEntryList_className[];
extern "C" igMetaObject *g_igMemoryFileEntry_metaObject[4];
extern "C" igMetaObject *igMemoryFileEntry_GetMetaObject(void);
extern "C" int DAT_00532910[4];
extern "C" char igMemoryFileEntry_className[];
extern "C" int g_igMemoryFileEntry_ctorTable[4];
extern "C" int g_igMemoryFileEntry_fieldTable[4];
extern "C" int DAT_004c02e8[4];
extern "C" int DAT_004c02f0[4];
extern "C" igMetaObject *g_igMemoryDirEntry_metaObject[4];
extern "C" igMetaObject *igMemoryDirEntry_GetMetaObject(void);
extern "C" int DAT_0052f860[4];
extern "C" char g_igMemoryDirEntry_callbackList[];
extern "C" char igMemoryDirEntry_className[];
extern "C" int g_igMemoryDirEntry_ctorTable[4];
extern "C" int g_igMemoryDirEntry_fieldTable[4];
extern "C" int DAT_004c0340[4];
extern "C" int DAT_004c0360[4];
extern "C" igMetaObject *g_igMemoryDictionary_metaObject[4];
extern "C" igMetaObject *igMemoryDictionary_GetMetaObject(void);
extern "C" int DAT_0052f910[4];
extern "C" char g_igMemoryDictionary_callbackList[];
extern "C" char igMemoryDictionary_className[];
extern "C" int g_igMemoryDictionary_ctorTable[4];
extern "C" int g_igMemoryDictionary_fieldTable[4];
extern "C" int DAT_004c03b0[4];
extern "C" int DAT_004c03c0[4];
extern "C" igMetaObject *g_igMediaFile_metaObject[4];
extern "C" igMetaObject *igMediaFile_GetMetaObject(void);
extern "C" int DAT_0052f9a0[4];
extern "C" char g_igMediaFile_callbackList[];
extern "C" char igMediaFile_className[];
extern "C" int g_igMediaFile_ctorTable[4];
extern "C" int g_igMediaFile_fieldTable[4];
extern "C" int DAT_004c0440[4];
extern "C" int DAT_004c0470[4];
extern "C" igMetaObject *g_igMediaList_metaObject[4];
extern "C" igMetaObject *igMediaList_GetMetaObject(void);
extern "C" int DAT_005328a0[4];
extern "C" char g_igMediaList_callbackList[];
extern "C" char igMediaList_className[];
extern "C" igMetaObject *g_igMedia_metaObject[4];
extern "C" igMetaObject *igMedia_GetMetaObject(void);
extern "C" char igMedia_className[];
extern "C" int igMedia_InitFields_002c1810[4];
extern "C" igMetaObject *g_igLongTimer_metaObject[4];
extern "C" igMetaObject *FUN_002c1860(void);
extern "C" char thunk_igLongTimer_GetMetaObject_002b7b60[];
extern "C" char igTimer_GetPublishedMetaObject[];
extern "C" char igLongTimer_className[];
extern "C" int g_igLongTimer_ctorTable[4];
extern "C" int g_igLongTimer_fieldTable[4];
extern "C" int DAT_004c04c0[4];
extern "C" int DAT_004c04d0[4];
extern "C" igMetaObject *g_igLongMetaField_metaObject[4];
extern "C" igMetaObject *igLongMetaField_GetMetaObject(void);
extern "C" int DAT_0052fa50[4];
extern "C" char g_igLongMetaField_callbackList[];
extern "C" char igLongMetaField_className[];
extern "C" void * g_igLongMetaField_descriptor[4];
extern "C" igMetaObject *g_igLongArrayMetaField_metaObject[4];
extern "C" igMetaObject *igLongArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052fb50[4];
extern "C" char igLongMetaField_GetPublishedMetaObject[];
extern "C" char g_igLongArrayMetaField_callbackList[];
extern "C" char igLongArrayMetaField_className[];
extern "C" int g_igLongArrayMetaField_ctorTable[4];
extern "C" int g_igLongArrayMetaField_fieldTable[4];
extern "C" int DAT_004c0500[4];
extern "C" int DAT_004c0508[4];
extern "C" igLongArrayMetaField *g_igLongArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igLocationTable_metaObject[4];
extern "C" igMetaObject *igLocationTable_GetMetaObject(void);
extern "C" int DAT_0052fc50[4];
extern "C" char g_igLocationTable_callbackList[];
extern "C" char igLocationTable_className[];
extern "C" int g_igLocationTable_ctorTable[4];
extern "C" int g_igLocationTable_fieldTable[4];
extern "C" int DAT_004c0560[4];
extern "C" int DAT_004c0580[4];
extern "C" igMetaObject *g_igLibraryLoader_metaObject[4];
extern "C" igMetaObject *igLibraryLoader_GetMetaObject(void);
extern "C" char igLibraryLoader_className[];
extern "C" igMetaObject *g_igLibraryList_metaObject[4];
extern "C" igMetaObject *igLibraryList_GetMetaObject(void);
extern "C" int DAT_00532830[4];
extern "C" char g_igLibraryList_callbackList[];
extern "C" char igLibraryList_className[];
extern "C" igMetaObject *g_igLibrary_metaObject[4];
extern "C" igMetaObject *igLibrary_GetMetaObject(void);
extern "C" char igLibrary_className[];
extern "C" int g_igLibrary_ctorTable[4];
extern "C" int g_igLibrary_fieldTable[4];
extern "C" int DAT_004c05b0[4];
extern "C" int DAT_004c05b8[4];
extern "C" igMetaObject *g___internalObjectList_metaObject[4];
extern "C" igMetaObject *__internalObjectList_GetMetaObject(void);
extern "C" char __internalNonRefCountedObjectList_GetPublishedMetaObject_002c28f0[];
extern "C" char __internalObjectList_className[];
extern "C" igMetaObject *g___internalNonRefCountedObjectList_metaObject[4];
extern "C" int DAT_005860d8[4];
extern "C" igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void);
extern "C" char __internalNonRefCountedObjectList_className[];
extern "C" int g___internalNonRefCountedObjectList_ctorTable[4];
extern "C" int g___internalNonRefCountedObjectList_fieldTable[4];
extern "C" int DAT_004c05d0[4];
extern "C" int DAT_004c05d8[4];
extern "C" igMetaObject *g_igIntMetaField_metaObject[4];
extern "C" igMetaObject *igIntMetaField_GetMetaObject(void);
extern "C" char g_igIntMetaField_callbackList[];
extern "C" char igIntMetaField_className[];
extern "C" void * g_igIntMetaField_descriptor[4];
extern "C" igMetaObject *g_igIntArrayMetaField_metaObject[4];
extern "C" igMetaObject *igIntArrayMetaField_GetMetaObject(void);
extern "C" int DAT_0052fce0[4];
extern "C" char igIntMetaField_GetPublishedMetaObject[];
extern "C" char g_igIntArrayMetaField_callbackList[];
extern "C" char igIntArrayMetaField_className[];
extern "C" int g_igIntArrayMetaField_ctorTable[4];
extern "C" int g_igIntArrayMetaField_fieldTable[4];
extern "C" int DAT_004c0600[4];
extern "C" int DAT_004c0608[4];
extern "C" igIntArrayMetaField *DAT_00586110[4];
extern "C" igMetaObject *g_igInfoList_metaObject[4];
extern "C" igMetaObject *igInfoList_GetMetaObject(void);
extern "C" int DAT_00532600[4];
extern "C" char g_igInfoList_callbackList[];
extern "C" char igInfoList_className[];
extern "C" igMetaObject *g_igInfo_metaObject[4];
extern "C" igMetaObject *igInfo_GetMetaObject(void);
extern "C" int DAT_0052fde0[4];
extern "C" char g_igInfo_callbackList[];
extern "C" char igInfo_className[];
extern "C" int g_igInfo_ctorTable[4];
extern "C" int g_igInfo_fieldTable[4];
extern "C" int DAT_004c0630[4];
extern "C" int DAT_004c0638[4];
extern "C" igMetaObject *g_igIGBFile_metaObject[4];
extern "C" igMetaObject *igIGBFile_GetMetaObject(void);
extern "C" int DAT_0052fe50[4];
extern "C" int DAT_0052fe40[8];
extern "C" ObjectRefWord *FUN_002c3a80(ObjectRefWord *self,int delete_storage);
extern "C" int DAT_00530890[4];
/* A pooled-string field: the string's chunk and reference count sit in the two words ahead of it. */
struct PooledStringWord {
    int *v;
    inline void release() {
        int **self = &v;
        if (self) {
            int *o = v;
            if (o) {
                int *h = o - 2;
                int c = o[-1] - 1;
                o[-1] = c;
                if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
            }
        }
    }
};
extern "C" igDirectory *FUN_002c3b00(igDirectory *p, short n);
extern "C" int DAT_00524a20[4];
extern "C" int DAT_005309b0[4];
extern "C" int DAT_00532590[4];
extern "C" void *FUN_002c3d60(igIGBFile *arg0);
extern "C" char igDirectory_GetPublishedMetaObject[];
extern "C" char g_igIGBFile_callbackList[];
extern "C" char igIGBFile_className[];
extern "C" igMetaObject *g_igDirectory_metaObject[4];
extern "C" int g_igIGBFile_ctorTable[4];
extern "C" int g_igIGBFile_fieldTable[4];
extern "C" int DAT_004c0880[4];
extern "C" int DAT_004c0990[4];
extern "C" int text_capacity[4];
extern "C" int text_count[4];
extern "C" igMetaObject *g_igIGBFile_metaObject[4];
extern "C" int DAT_00586148[4];
extern "C" int DAT_00586150[4];
extern "C" int DAT_00586158[4];
extern "C" igMetaObject *g_igFolder_metaObject[4];
extern "C" igMetaObject *igFolder_GetMetaObject(void);
extern "C" int DAT_0052fee0[4];
extern "C" char igFolder_className[];
extern "C" int g_igFolder_ctorTable[4];
extern "C" int g_igFolder_fieldTable[4];
extern "C" int DAT_004c0aa8[4];
extern "C" int DAT_004c0ab0[4];
extern "C" igMetaObject *g_igFloatMetaField_metaObject[4];
extern "C" igMetaObject *igFloatMetaField_GetMetaObject(void);
extern "C" int DAT_0052ff50[4];
extern "C" char g_igFloatMetaField_callbackList[];
extern "C" char igFloatMetaField_className[];
extern "C" void * DAT_00586380[4];
extern "C" igMetaObject *g_igFloatArrayMetaField_metaObject[4];
extern "C" igMetaObject *igFloatArrayMetaField_GetMetaObject(void);
extern "C" int DAT_00530050[4];
extern "C" char igFloatMetaField_GetPublishedMetaObject[];
extern "C" char g_igFloatArrayMetaField_callbackList[];
extern "C" char igFloatArrayMetaField_className[];
extern "C" int g_igFloatArrayMetaField_ctorTable[4];
extern "C" int g_igFloatArrayMetaField_fieldTable[4];
extern "C" int DAT_004c0ad8[4];
extern "C" int DAT_004c0ae0[4];
extern "C" igFloatArrayMetaField *g_igFloatArrayMetaField_descriptor[4];
extern "C" int DAT_004c0ae8[4];
extern "C" int DAT_004c0af8[4];
extern "C" int text_ReadMode[4];
extern "C" int DAT_005863a0[4];
extern "C" int DAT_004c0b10[4];
extern "C" int DAT_004c0b40[4];
extern "C" int text_OpenMode[4];
extern "C" int DAT_005863a8[4];
extern "C" igMetaObject *igFile_GetMetaObject(void);
extern "C" char igFile_className[];
extern "C" int g_igFile_ctorTable[4];
extern "C" int g_igFile_fieldTable[4];
extern "C" int DAT_004c0bb0[4];
extern "C" int DAT_004c0bd0[4];
extern "C" int DAT_004c0bf0[4];
extern "C" int DAT_004c0bf8[4];
extern "C" int text_DefaultFileName[4];
extern "C" igMetaObject *g_igExternalInfoEntry_metaObject[4];
extern "C" igMetaObject *igExternalInfoEntry_GetMetaObject(void);
extern "C" int DAT_00530200[4];
extern "C" char igExternalInfoEntry_className[];
extern "C" int g_igExternalInfoEntry_ctorTable[4];
extern "C" int g_igExternalInfoEntry_fieldTable[4];
extern "C" int DAT_004c0c20[4];
extern "C" int DAT_004c0c30[4];
extern "C" igMetaObject *g_igExternalIndexedEntry_metaObject[4];
extern "C" igMetaObject *igExternalIndexedEntry_GetMetaObject(void);
extern "C" int DAT_005302b0[4];
extern "C" char g_igExternalIndexedEntry_callbackList[];
extern "C" char igExternalIndexedEntry_className[];
extern "C" int g_igExternalIndexedEntry_ctorTable[4];
extern "C" int g_igExternalIndexedEntry_fieldTable[4];
extern "C" int DAT_004c0c90[4];
extern "C" int DAT_004c0cb0[4];
extern "C" igMetaObject *g_igExternalDirEntry_metaObject[4];
extern "C" igMetaObject *igExternalDirEntry_GetMetaObject(void);
extern "C" int DAT_00530360[4];
extern "C" char g_igExternalDirEntry_callbackList[];
extern "C" char igExternalDirEntry_className[];
extern "C" int g_igExternalDirEntry_ctorTable[4];
extern "C" int g_igExternalDirEntry_fieldTable[4];
extern "C" int DAT_004c0cf0[4];
extern "C" int DAT_004c0d00[4];
extern "C" int text_Intrinsic[4];
extern "C" int text_default_2[4];
extern "C" int DAT_004f7910[4];
extern "C" igMetaObject *g_igExternalDirEntry_metaObject[4];
extern "C" igMetaField *DAT_00586458[4];
extern "C" igMetaObject *g_igEventTracker_metaObject[4];
extern "C" igMetaObject *igEventTracker_GetMetaObject(void);
extern "C" int DAT_00530420[4];
extern "C" char g_igEventTracker_callbackList[];
extern "C" char igEventTracker_className[];
extern "C" int g_igEventTracker_ctorTable[4];
extern "C" int g_igEventTracker_fieldTable[4];
extern "C" int DAT_004c0e50[4];
extern "C" int DAT_004c0ee0[4];
extern "C" igMetaObject *g_igErrorHandler_metaObject[4];
extern "C" igMetaObject *igErrorHandler_GetMetaObject(void);
struct igErrorHandler : public igObject { };
extern "C" int DAT_00532530[4];
extern "C" char igErrorHandler_className[];
extern "C" igMetaObject *g_igEnumMetaField_metaObject[4];
extern "C" igMetaObject *igEnumMetaField_GetMetaObject(void);
extern "C" char g_igEnumMetaField_callbackList[];
extern "C" char igEnumMetaField_className[];
extern "C" int g_igEnumMetaField_ctorTable[4];
extern "C" int g_igEnumMetaField_fieldTable[4];
extern "C" int DAT_004c0f80[4];
extern "C" int DAT_004c0f88[4];
extern "C" int *g_igEnumMetaField_descriptor[4];
extern "C" igMetaObject *g_igEnumArrayMetaField_metaObject[4];
extern "C" igMetaObject *igEnumArrayMetaField_GetMetaObject(void);
extern "C" int DAT_005304f0[4];
extern "C" char igEnumMetaField_GetPublishedMetaObject[];
extern "C" char g_igEnumArrayMetaField_callbackList[];
extern "C" char igEnumArrayMetaField_className[];
extern "C" int g_igEnumArrayMetaField_ctorTable[4];
extern "C" int g_igEnumArrayMetaField_fieldTable[4];
extern "C" int DAT_004c0fa8[4];
extern "C" int DAT_004c0fb0[4];
extern "C" int *g_igEnumArrayMetaField_descriptor[4];
extern "C" int DAT_004c0fb8[4];
extern "C" int DAT_004c0fc0[4];
extern "C" int SECTION_OVERRIDE_MODE[4];
extern "C" int DAT_005865c8[4];
extern "C" igMetaObject *g_igDriverDatabase_metaObject[4];
extern "C" igMetaObject *igDriverDatabase_GetMetaObject(void);
extern "C" int DAT_00530630[4];
extern "C" char g_igDriverDatabase_callbackList[];
extern "C" char igDriverDatabase_className[];
extern "C" int g_igDriverDatabase_ctorTable[4];
extern "C" int g_igDriverDatabase_fieldTable[4];
extern "C" int DAT_004c1050[4];
extern "C" int DAT_004c1080[4];
extern "C" int DAT_004c10b0[4];
extern "C" igMetaObject *g_igDoubleMetaField_metaObject[4];
extern "C" igMetaObject *igDoubleMetaField_GetMetaObject(void);
extern "C" int DAT_00530690[4];
extern "C" char g_igDoubleMetaField_callbackList[];
extern "C" char igDoubleMetaField_className[];
extern "C" void * DAT_00586640[4];
extern "C" igMetaObject *g_igDoubleArrayMetaField_metaObject[4];
extern "C" igMetaObject *igDoubleArrayMetaField_GetMetaObject(void);
extern "C" int DAT_00530790[4];
extern "C" char igDoubleMetaField_GetPublishedMetaObject[];
extern "C" char g_igDoubleArrayMetaField_callbackList[];
extern "C" char igDoubleArrayMetaField_className[];
extern "C" int g_igDoubleArrayMetaField_ctorTable[4];
extern "C" int g_igDoubleArrayMetaField_fieldTable[4];
extern "C" int DAT_004c10d8[4];
extern "C" int DAT_004c10e0[4];
extern "C" igDoubleArrayMetaField *g_igDoubleArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igDirectoryList_metaObject[4];
extern "C" igMetaObject *igDirectoryList_GetMetaObject(void);
extern "C" int DAT_005323c0[4];
extern "C" char g_igDirectoryList_callbackList[];
extern "C" char igDirectoryList_className[];
extern "C" igMetaObject *igDirectory_GetMetaObject(void);
extern "C" char g_igDirectory_callbackList[];
extern "C" char igDirectory_className[];
extern "C" int g_igDirectory_ctorTable[4];
extern "C" int g_igDirectory_fieldTable[4];
extern "C" int DAT_004c11b0[4];
extern "C" int DAT_004c1200[4];
extern "C" int DAT_004c1248[4];
extern "C" int DAT_004c1258[4];
extern "C" int text_RefType[4];
extern "C" int DAT_00586700[4];
extern "C" int DAT_004c1268[4];
extern "C" int DAT_004c1278[4];
extern "C" int text_ResolveMethod[4];
extern "C" int DAT_00586708[4];
extern "C" igMetaObject *igDirEntry_GetMetaObject(void);
extern "C" int DAT_00530900[4];
extern "C" char igDirEntry_className[];
extern "C" int g_igDirEntry_ctorTable[4];
extern "C" int g_igDirEntry_fieldTable[4];
extern "C" int DAT_004c12b0[4];
extern "C" int DAT_004c12c0[4];
extern "C" int DAT_004c12d0[4];
extern "C" int DAT_004c12d8[4];
extern "C" igMetaObject *g_igDependencyOrderedList_metaObject[4];
extern "C" igMetaObject *igDependencyOrderedList_GetMetaObject(void);
extern "C" int DAT_0052cc20[4];
extern "C" char g_igDependencyOrderedList_callbackList[];
extern "C" char igDependencyOrderedList_className[];
extern "C" int g_igDependencyOrderedList_ctorTable[4];
extern "C" int g_igDependencyOrderedList_fieldTable[4];
extern "C" int DAT_004c1340[4];
extern "C" int DAT_004c1360[4];
extern "C" igMetaObject *g_igDependencyList_metaObject[4];
extern "C" igMetaObject *igDependencyList_GetMetaObject(void);
extern "C" int DAT_00532360[4];
extern "C" char igDependencyList_className[];
extern "C" int DAT_00586770[4];
extern "C" igMetaObject *g_igDependencyMetaField_metaObject[4];
extern "C" igMetaObject *igDependencyMetaField_GetMetaObject(void);
extern "C" int DAT_00532260[4];
extern "C" int DAT_00531740[4];
extern "C" char igCompoundMetaField_GetPublishedMetaObject[];
extern "C" char g_igDependencyMetaField_callbackList[];
extern "C" char igDependencyMetaField_className[];
extern "C" void * DAT_00586780[4];
extern "C" int text_before[4];
extern "C" int text_after[4];
extern "C" int g_stringPool[4];
extern "C" igMetaObject *g_igDataList_metaObject[4];
extern "C" igMetaObject *igDataList_GetMetaObject(void);
extern "C" char igDataList_className[];
extern "C" int g_igDataList_ctorTable[4];
extern "C" int g_igDataList_fieldTable[4];
extern "C" int DAT_004c13a0[4];
extern "C" int DAT_004c13b0[4];
extern "C" igMetaObject *g_igStringRefListList_metaObject[4];
extern "C" igMetaObject *igStringRefListList_GetMetaObject(void);
extern "C" int DAT_005321f0[4];
extern "C" char g_igStringRefListList_callbackList[];
extern "C" char igStringRefListList_className[];
extern "C" igMetaObject *g_igObjectListList_metaObject[4];
extern "C" igMetaObject *igObjectListList_GetMetaObject(void);
extern "C" int DAT_00532180[4];
extern "C" char g_igObjectListList_callbackList[];
extern "C" char igObjectListList_className[];
extern "C" igMetaObject *g_igIntListList_metaObject[4];
extern "C" igMetaObject *igIntListList_GetMetaObject(void);
extern "C" int DAT_00532110[4];
extern "C" char g_igIntListList_callbackList[];
extern "C" char igIntListList_className[];
extern "C" igMetaObject *g_igMetaFieldList_metaObject[4];
extern "C" igMetaObject *igMetaFieldList_GetMetaObject(void);
extern "C" int DAT_005320a0[4];
extern "C" char g_igMetaFieldList_callbackList[];
extern "C" char igMetaFieldList_className[];
extern "C" igMetaObject *g_igMetaObjectListList_metaObject[4];
extern "C" igMetaObject *igMetaObjectListList_GetMetaObject(void);
extern "C" int DAT_00532030[4];
extern "C" char g_igMetaObjectListList_callbackList[];
extern "C" char igMetaObjectListList_className[];
extern "C" igMetaObject *g_igMetaObjectList_metaObject[4];
extern "C" igMetaObject *igMetaObjectList_GetMetaObject(void);
extern "C" int DAT_00531fc0[4];
extern "C" char g_igMetaObjectList_callbackList[];
extern "C" char igMetaObjectList_className[];
extern "C" igMetaObject *g_igPointerListList_metaObject[4];
extern "C" igMetaObject *igPointerListList_GetMetaObject(void);
extern "C" int DAT_00531f50[4];
extern "C" char g_igPointerListList_callbackList[];
extern "C" char igPointerListList_className[];
extern "C" igMetaObject *g_igPointerList_metaObject[4];
extern "C" igMetaObject *igPointerList_GetMetaObject(void);
extern "C" int DAT_00531ef0[4];
extern "C" char igPointerList_className[];
extern "C" int igPointerList_InitFields_002c92e0[4];
extern "C" int DAT_005867e8[4];
extern "C" igMetaObject *g_igDoubleList_metaObject[4];
extern "C" igMetaObject *igDoubleList_GetMetaObject(void);
extern "C" int DAT_0052b630[4];
extern "C" char igDoubleList_className[];
extern "C" int DAT_005867f8[4];
extern "C" igMetaObject *g_igFloatListList_metaObject[4];
extern "C" igMetaObject *igFloatListList_GetMetaObject(void);
extern "C" int DAT_00531e80[4];
extern "C" char g_igFloatListList_callbackList[];
extern "C" char igFloatListList_className[];
extern "C" igMetaObject *g_igFloatList_metaObject[4];
extern "C" igMetaObject *igFloatList_GetMetaObject(void);
extern "C" int DAT_00531e20[4];
extern "C" char igFloatList_className[];
extern "C" int igFloatList_InitFields_002c98f0[4];
extern "C" int DAT_00586810[4];
extern "C" igMetaObject *g_igUnsignedCharList_metaObject[4];
extern "C" igMetaObject *igUnsignedCharList_GetMetaObject(void);
extern "C" int DAT_00531dc0[4];
extern "C" char igUnsignedCharList_className[];
extern "C" int igUnsignedCharList_InitFields_002c9b10[4];
extern "C" int DAT_00586820[4];
extern "C" igMetaObject *g_igShortListList_metaObject[4];
extern "C" igMetaObject *igShortListList_GetMetaObject(void);
extern "C" int DAT_00531d50[4];
extern "C" char g_igShortListList_callbackList[];
extern "C" char igShortListList_className[];
extern "C" igMetaObject *g_igShortList_metaObject[4];
extern "C" igMetaObject *igShortList_GetMetaObject(void);
extern "C" int DAT_00531cf0[4];
extern "C" char igShortList_className[];
extern "C" int igShortList_InitFields_002c9f30[4];
extern "C" int DAT_00586838[4];
extern "C" igMetaObject *g_igUnsignedShortList_metaObject[4];
extern "C" igMetaObject *igUnsignedShortList_GetMetaObject(void);
extern "C" int DAT_00531c90[4];
extern "C" char igUnsignedShortList_className[];
extern "C" int igUnsignedShortList_InitFields_002ca1a0[4];
extern "C" int DAT_00586848[4];
extern "C" igMetaObject *g_igUnsignedIntListNoClean_metaObject[4];
extern "C" igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void);
extern "C" int DAT_00531c30[4];
extern "C" char igUnsignedIntList_GetPublishedMetaObject[];
extern "C" char igUnsignedIntListNoClean_className[];
extern "C" igMetaObject *g_igUnsignedIntList_metaObject[4];
extern "C" igMetaObject *igUnsignedIntList_GetMetaObject(void);
extern "C" int DAT_0052a3a0[4];
extern "C" char igUnsignedIntList_className[];
extern "C" int igUnsignedIntList_InitFields_002ca5c0[4];
extern "C" int DAT_00586860[4];
extern "C" igMetaObject *g_igLongList_metaObject[4];
extern "C" igMetaObject *igLongList_GetMetaObject(void);
extern "C" int DAT_00531bd0[4];
extern "C" char igLongList_className[];
extern "C" int igLongList_InitFields_002ca7f0[4];
extern "C" int DAT_00586870[4];
extern "C" igMetaObject *g_igIntListNoClean_metaObject[4];
extern "C" igMetaObject *igIntListNoClean_GetMetaObject(void);
extern "C" int DAT_00531b10[4];
extern "C" char igIntList_GetPublishedMetaObject[];
extern "C" char igIntListNoClean_className[];
extern "C" igMetaObject *g_igIntList_metaObject[4];
extern "C" igMetaObject *igIntList_GetMetaObject(void);
extern "C" int DAT_00531b70[4];
extern "C" char igIntList_className[];
extern "C" int g_igIntList_dataDescriptorCell[4];
extern "C" igMetaObject *g_igCharListNoClean_metaObject[4];
extern "C" igMetaObject *igCharListNoClean_GetMetaObject(void);
extern "C" int DAT_00531a50[4];
extern "C" char igCharList_GetPublishedMetaObject[];
extern "C" char igCharListNoClean_className[];
extern "C" igMetaObject *g_igCharList_metaObject[4];
extern "C" igMetaObject *igCharList_GetMetaObject(void);
extern "C" int DAT_00531ab0[4];
extern "C" char igCharList_className[];
extern "C" int DAT_005868a0[4];
extern "C" igMetaObject *g_igBoolList_metaObject[4];
extern "C" igMetaObject *igBoolList_GetMetaObject(void);
extern "C" int DAT_005319f0[4];
extern "C" char igBoolList_className[];
extern "C" int DAT_005868b0[4];
extern "C" igMetaObject *g_igContextExtList_metaObject[4];
extern "C" igMetaObject *igContextExtList_GetMetaObject(void);
extern "C" int DAT_00531980[4];
extern "C" char g_igContextExtList_callbackList[];
extern "C" char igContextExtList_className[];
extern "C" igMetaObject *g_igContextExtInfoList_metaObject[4];
extern "C" igMetaObject *igContextExtInfoList_GetMetaObject(void);
extern "C" int DAT_00531910[4];
extern "C" char g_igContextExtInfoList_callbackList[];
extern "C" char igContextExtInfoList_className[];
extern "C" igMetaObject *g_igContextExtInfo_metaObject[4];
extern "C" igMetaObject *igContextExtInfo_GetMetaObject(void);
extern "C" int DAT_005318b0[4];
extern "C" char g_igContextExtInfo_callbackList[];
extern "C" char igContextExtInfo_className[];
extern "C" int g_igContextExtInfo_ctorTable[4];
extern "C" int g_igContextExtInfo_fieldTable[4];
extern "C" int DAT_004c1440[4];
extern "C" int DAT_004c1450[4];
extern "C" igMetaObject *g_igContextExt_metaObject[4];
extern "C" igMetaObject *igContextExt_GetMetaObject(void);
extern "C" char igContext_GetPublishedMetaObject[];
extern "C" char igContextExt_className[];
extern "C" igMetaObject *g_igContextList_metaObject[4];
extern "C" igMetaObject *igContextList_GetMetaObject(void);
extern "C" int DAT_00531840[4];
extern "C" char g_igContextList_callbackList[];
extern "C" char igContextList_className[];
extern "C" igMetaObject *g_igContext_metaObject[4];
extern "C" igMetaObject *igContext_GetMetaObject(void);
extern "C" char g_igContext_callbackList[];
extern "C" char igContext_className[];
extern "C" int g_igContext_ctorTable[4];
extern "C" int g_igContext_fieldTable[4];
extern "C" int DAT_004c1498[4];
extern "C" int DAT_004c14a8[4];
extern "C" igMetaObject *g_igCompoundMetaField_metaObject[4];
extern "C" igMetaObject *igCompoundMetaField_GetMetaObject(void);
extern "C" char g_igCompoundMetaField_callbackList[];
extern "C" char igCompoundMetaField_className[];
extern "C" int g_igCompoundMetaField_ctorTable[4];
extern "C" int g_igCompoundMetaField_fieldTable[4];
extern "C" int DAT_004c14d8[4];
extern "C" int DAT_004c14e0[4];
extern "C" void * DAT_00586920[4];
typedef struct Owner {
    char pad[52];
    int field52;
} Owner;
extern "C" void FUN_002cbf50(Owner *owner);
extern "C" igMetaObject *g_igCharMetaField_metaObject[4];
extern "C" igMetaObject *igCharMetaField_GetMetaObject(void);
extern "C" char g_igCharMetaField_callbackList[];
extern "C" char igCharMetaField_className[];
extern "C" void * DAT_00586938[4];
extern "C" igMetaObject *g_igCharArrayMetaField_metaObject[4];
extern "C" igMetaObject *igCharArrayMetaField_GetMetaObject(void);
extern "C" int DAT_00530a80[4];
extern "C" char igCharMetaField_GetPublishedMetaObject[];
extern "C" char g_igCharArrayMetaField_callbackList[];
extern "C" char igCharArrayMetaField_className[];
extern "C" int g_igCharArrayMetaField_ctorTable[4];
extern "C" int g_igCharArrayMetaField_fieldTable[4];
extern "C" int DAT_004c1508[4];
extern "C" int DAT_004c1510[4];
extern "C" igCharArrayMetaField *g_igCharArrayMetaField_descriptor[4];
extern "C" igMetaObject *g_igCallStackTracer_metaObject[4];
extern "C" igMetaObject *igCallStackTracer_GetMetaObject(void);
extern "C" int DAT_00530b80[4];
extern "C" char igUnsignedIntListNoClean_GetPublishedMetaObject[];
extern "C" char igCallStackTracer_className[];
extern "C" igMetaObject *g_igCallStackTable_metaObject[4];
extern "C" igMetaObject *igCallStackTable_GetMetaObject(void);
extern "C" int DAT_00530c00[4];
extern "C" char g_igCallStackTable_callbackList[];
extern "C" char igCallStackTable_className[];
extern "C" int g_igCallStackTable_ctorTable[4];
extern "C" int g_igCallStackTable_fieldTable[4];
extern "C" int DAT_004c1550[4];
extern "C" int DAT_004c1560[4];
extern "C" igMetaObject *g_igBoolMetaField_metaObject[4];
extern "C" igMetaObject *igBoolMetaField_GetMetaObject(void);
extern "C" char g_igBoolMetaField_callbackList[];
extern "C" char igBoolMetaField_className[];
extern "C" void * DAT_00586990[4];
extern "C" igMetaObject *g_igBoolArrayMetaField_metaObject[4];
extern "C" igMetaObject *igBoolArrayMetaField_GetMetaObject(void);
extern "C" int DAT_00530c80[4];
extern "C" char igBoolMetaField_GetPublishedMetaObject[];
extern "C" char g_igBoolArrayMetaField_callbackList[];
extern "C" char igBoolArrayMetaField_className[];
extern "C" int g_igBoolArrayMetaField_ctorTable[4];
extern "C" int g_igBoolArrayMetaField_fieldTable[4];
extern "C" int DAT_004c1590[4];
extern "C" int DAT_004c1598[4];
extern "C" igBoolArrayMetaField *DAT_005869a0[4];
/* Class factory of igAliasMemoryPool. Once the object system is running it registers the class and
 * creates the pool through its metaobject on `allocator`. During bootstrap, before the object
 * system exists, it allocates the 184-byte pool by hand, constructs it, and then runs virtual slot
 * 44 and slot 36 (with 0) on it. Those calls are not guarded against a failed allocation.
 * FactoryPoolView is an ABI dispatch view of slots 36 and 44 and must not be instantiated. */
class FactoryPoolView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void Set(int); virtual void d8(); virtual void Init(); };
extern "C" FactoryPoolView *igAliasMemoryPool_Create(void *allocator);
extern "C" igMetaObject *g_igAliasMemoryPool_metaObject[4];
extern "C" igMetaObject *igAliasMemoryPool_GetMetaObject(void);
extern "C" int g_igAliasMemoryPool_vtable[4];
extern "C" char igMemoryPool_GetPublishedMetaObject[];
extern "C" char g_igAliasMemoryPool_callbackList[];
extern "C" char igAliasMemoryPool_className[];
extern "C" int g_igAliasMemoryPool_ctorTable[4];
extern "C" int g_igAliasMemoryPool_fieldTable[4];
extern "C" int DAT_004c1630[4];
extern "C" int DAT_004c1670[4];
extern "C" int DAT_004c16b0[4];
extern "C" int DAT_004c16c0[4];
extern "C" int text_MessageLevel[4];
extern "C" int DAT_00586a28[4];
extern "C" igMetaObject *g_igPageMemoryPool_metaObject[4];
extern "C" igMetaObject *igPageMemoryPool_GetMetaObject(void);
extern "C" int DAT_005311f0[4];
extern "C" char g_igPageMemoryPool_callbackList[];
extern "C" char igPageMemoryPool_className[];
extern "C" int g_igPageMemoryPool_ctorTable[4];
extern "C" int g_igPageMemoryPool_fieldTable[4];
extern "C" int DAT_004c1720[4];
extern "C" int DAT_004c1740[4];
extern "C" int DAT_004c2600[4];
extern "C" int g_igPageMemoryPool_defaultPoolOptionFlags[4];
extern "C" int DAT_004c1760[4];
extern "C" int DAT_004c1790[4];
extern "C" int text_ArenaMemoryPoolFlags[4];
extern "C" int DAT_00586a70[4];
extern "C" int DAT_004c17c0[4];
extern "C" int DAT_004c17d0[4];
extern "C" int DAT_00586a78[4];
extern "C" int DAT_004c17e0[4];
extern "C" int DAT_004c17f0[4];
extern "C" int text_HeapIntegrityCheckLevel[4];
extern "C" int DAT_00586a80[4];
extern "C" igMetaObject *g_igArenaMemoryPool_metaObject[4];
extern "C" igMetaObject *igArenaMemoryPool_GetMetaObject(void);
extern "C" int DAT_00531030[4];
extern "C" char g_igArenaMemoryPool_callbackList[];
extern "C" char igArenaMemoryPool_className[];
extern "C" int g_igArenaMemoryPool_ctorTable[4];
extern "C" int g_igArenaMemoryPool_fieldTable[4];
extern "C" int DAT_004c18b0[4];
extern "C" int DAT_004c1900[4];
extern "C" int DAT_004c2368[4];
extern "C" int DAT_004c2370[4];
extern "C" int DAT_005871f8[4];
extern "C" igMetaObject *g_igStackMemoryPool_metaObject[4];
extern "C" igMetaObject *igStackMemoryPool_GetMetaObject(void);
extern "C" int DAT_0052de80[4];
extern "C" char g_igStackMemoryPool_callbackList[];
extern "C" char igStackMemoryPool_className[];
extern "C" int g_igStackMemoryPool_ctorTable[4];
extern "C" int g_igStackMemoryPool_fieldTable[4];
extern "C" int DAT_004c19b0[4];
extern "C" int DAT_004c19e0[4];
extern "C" int DAT_004c1a10[4];
extern "C" int DAT_004c1a20[4];
extern "C" int DAT_00586b78[4];
extern "C" unsigned char GPR_00554dbc;
extern "C" igMetaObject *g_igMallocMemoryPool_metaObject[4];
extern "C" igMetaObject *igMallocMemoryPool_GetMetaObject(void);
extern "C" int DAT_00530e90[4];
extern "C" char g_igMallocMemoryPool_callbackList[];
extern "C" char igMallocMemoryPool_className[];
extern "C" int g_igMallocMemoryPool_ctorTable[4];
extern "C" int g_igMallocMemoryPool_fieldTable[4];
extern "C" int DAT_004c1aa0[4];
extern "C" int DAT_004c1ad0[4];
extern "C" int DAT_004c25f0[4];
extern "C" int DAT_004c25f8[4];
extern "C" igMetaObject *g_igMemoryDescriptorMetaField_metaObject[4];
extern "C" igMetaObject *igMemoryDescriptorMetaField_GetMetaObject(void);
extern "C" int DAT_00530d90[4];
extern "C" char g_igMemoryDescriptorMetaField_callbackList[];
extern "C" char igMemoryDescriptorMetaField_className[];
extern "C" void * g_igMemoryDescriptorMetaField_descriptor[4];
extern "C" int text_sizeAndStatus[4];
extern "C" igMetaObject *g_igProgramFile_metaObject[4];
extern "C" igMetaObject *igProgramFile_GetMetaObject(void);
extern "C" int DAT_0052e010[4];
extern "C" char g_igProgramFile_callbackList[];
extern "C" char igProgramFile_className[];
extern "C" int g_igProgramFile_ctorTable[4];
extern "C" int g_igProgramFile_fieldTable[4];
extern "C" int DAT_004c1b18[4];
extern "C" int DAT_004c1b20[4];
extern "C" igMetaObject *g_igElfFile_metaObject[4];
extern "C" igMetaObject *igElfFile_GetMetaObject(void);
extern "C" int DAT_0052e0a0[4];
extern "C" char igProgramFile_GetPublishedMetaObject[];
extern "C" char igElfFile_className[];
extern "C" int g_igElfFile_ctorTable[4];
extern "C" int g_igElfFile_fieldTable[4];
extern "C" int DAT_004c1b90[4];
extern "C" int DAT_004c1bc0[4];
extern "C" igMetaObject *g_igStandardQueue_metaObject[4];
extern "C" igMetaObject *igStandardQueue_GetMetaObject(void);
extern "C" int DAT_0052ddf0[4];
extern "C" int DAT_0052ee50[4];
extern "C" void *FUN_002cf040(igQueue *arg0, short arg1);
extern "C" char igQueue_GetPublishedMetaObject[];
extern "C" char g_igStandardQueue_callbackList[];
extern "C" char igStandardQueue_className[];
extern "C" int g_igStandardQueue_ctorTable[4];
extern "C" int g_igStandardQueue_fieldTable[4];
extern "C" int DAT_004c1c30[4];
extern "C" int DAT_004c1c50[4];
extern "C" igMetaObject *g_igPsx2ThreadManager_metaObject[4];
extern "C" igMetaObject *igPsx2ThreadManager_GetMetaObject(void);
extern "C" int DAT_0052d750[4];
extern "C" char igThreadManager_GetPublishedMetaObject[];
extern "C" char igPsx2ThreadManager_className[];
extern "C" int igPsx2ThreadManager_InitFields_002cf3f0[4];
extern "C" igMetaObject *g_igPsx2Thread_metaObject[4];
extern "C" igMetaObject *igPsx2Thread_GetMetaObject(void);
extern "C" int DAT_0052d7c0[4];
extern "C" char igThread_GetPublishedMetaObject[];
extern "C" char g_igPsx2Thread_callbackList[];
extern "C" char igPsx2Thread_className[];
extern "C" int g_igPsx2Thread_ctorTable[4];
extern "C" int g_igPsx2Thread_fieldTable[4];
extern "C" int DAT_004c1cc0[4];
extern "C" int DAT_004c1ce0[4];
extern "C" igMetaObject *g_igPsx2Semaphore_metaObject[4];
extern "C" igMetaObject *igPsx2Semaphore_GetMetaObject(void);
extern "C" int DAT_0052d970[4];
extern "C" char igSemaphore_GetPublishedMetaObject[];
extern "C" char igPsx2Semaphore_className[];
extern "C" int g_igPsx2Semaphore_ctorTable[4];
extern "C" int g_igPsx2Semaphore_fieldTable[4];
extern "C" int DAT_004c1d18[4];
extern "C" int DAT_004c1d28[4];
extern "C" igMetaObject *g_igPsx2Media_metaObject[4];
extern "C" igMetaObject *igPsx2Media_GetMetaObject(void);
extern "C" int DAT_0052da00[4];
extern "C" char igMedia_GetPublishedMetaObject[];
extern "C" char g_igPsx2Media_callbackList[];
extern "C" char igPsx2Media_className[];
extern "C" int g_igPsx2Media_ctorTable[4];
extern "C" int g_igPsx2Media_fieldTable[4];
extern "C" int DAT_004c1d90[4];
extern "C" int DAT_004c1db0[4];
extern "C" igMetaObject *g_igPsx2LongTimer_metaObject[4];
extern "C" igMetaObject *igPsx2LongTimer_GetMetaObject(void);
extern "C" int DAT_0052da90[4];
extern "C" char igLongTimer_GetPublishedMetaObject[];
extern "C" char igPsx2LongTimer_className[];
extern "C" igMetaObject *g_igPsx2IopRpcConnection_metaObject[4];
extern "C" igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void);
extern "C" int DAT_0052db30[4];
extern "C" char igPsx2IopRpcConnection_className[];
extern "C" int g_igPsx2IopRpcConnection_ctorTable[4];
extern "C" int g_igPsx2IopRpcConnection_fieldTable[4];
extern "C" int DAT_004c1df0[4];
extern "C" int DAT_004c1e00[4];
extern "C" igMetaObject *g_igPsx2Folder_metaObject[4];
extern "C" igMetaObject *igPsx2Folder_GetMetaObject(void);
extern "C" int DAT_0052db90[4];
extern "C" char igFolder_GetPublishedMetaObject[];
extern "C" char igPsx2Folder_className[];
extern "C" igMetaObject *g_igPsx2File_metaObject[4];
extern "C" igMetaObject *igPsx2File_GetMetaObject(void);
extern "C" int DAT_0052dc00[4];
extern "C" char igPsx2File_className[];
extern "C" int g_igPsx2File_ctorTable[4];
extern "C" int g_igPsx2File_fieldTable[4];
extern "C" int DAT_004c1e50[4];
extern "C" int DAT_004c1e70[4];
extern "C" igMetaObject *g_igPsx2CallStackTracer_metaObject[4];
extern "C" igMetaObject *igPsx2CallStackTracer_GetMetaObject(void);
extern "C" int DAT_0052dcb0[4];
extern "C" char igCallStackTracer_GetPublishedMetaObject[];
extern "C" char igPsx2CallStackTracer_className[];
extern "C" int igPsx2CallStackTracer_InitFields_002d0530[4];
extern "C" int g_igAliasMemoryPool_vtable[4];
extern "C" char DAT_004f90b0[];
extern "C" int text_null[4];
extern "C" char DAT_004f90c0[];
extern "C" int DAT_004f92b0[4];
extern "C" int DAT_004f92f0[4];
/* Retail ABI views, not original class definitions. Virtual tables include
 * an eight-byte header; Object projects slot376. Never instantiate these views. */
class Object { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual unsigned char Check(void *); unsigned refs; };
extern "C" void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, Object *alias);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_30(igAliasMemoryPool *self);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_31(igAliasMemoryPool *self);
/* igAliasMemoryPool's virtuals: the igMemoryPool table, then the alias pool's own slots 97-101
 * (vfunc_99 to vfunc_103). */
class igAliasMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97();
    virtual void vfunc_100(igMemoryPool *aliased);                               /* slot 98, byte 400 */
    virtual void d99(); virtual void d100();
    virtual int ManageAllocation(int block, int size, unsigned short alignment); /* slot 101, byte 412 */
};
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_32(igAliasMemoryPool *self);
extern "C" unsigned char Gap__Core__igAliasMemoryPool__vfunc_33(igAliasMemoryPool *self);
struct LockStatus { int v; LockStatus() {} LockStatus(int x) { v = x; } };
class Lock : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual LockStatus open(); virtual LockStatus close(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual LockStatus wait(int); };
extern "C" LockStatus Gap__Core__igAliasMemoryPool__vfunc_34(igAliasMemoryPool *pool, int enable);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_41(int *status, igAliasMemoryPool *self, long long maxSize);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_42(igAliasMemoryPool *self);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_37(int *status, igAliasMemoryPool *self, short alignment);
extern "C" unsigned short Gap__Core__igAliasMemoryPool__vfunc_38(igAliasMemoryPool *self);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_39(int *status_out, igAliasMemoryPool *self, int element_size);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_40(igAliasMemoryPool *self);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_46(igAliasMemoryPool *arg0);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_47(igAliasMemoryPool *self);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_48(igAliasMemoryPool *self);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_101(igAliasMemoryPool *arg0);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_102(igAliasMemoryPool *arg0);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_49(igAliasMemoryPool *arg0);
/* PoolView is an ABI projection (vtable slots), never instantiated. */
class PoolView {public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void *AllocateDefault(long long); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual long long Size(void *); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void Close(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void *Backend(void *,long long,unsigned short); };
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_53(igAliasMemoryPool *self);
/* The lock calls return a 4-byte struct by value; MWCC passes it through a hidden return buffer,
 * which the stack slot in each caller reproduces. */
struct LockCallStatus { int word; };
/* The lock object's vtable: unnamed padding slots, the unlock call (offset 124) and the lock call
 * (offset 132), with the two-word class header in front of the slots. */
class AllocationLockVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual LockCallStatus unlock(); virtual void d30(); virtual LockCallStatus lock(int); };
extern "C" void igAliasMemoryPool_Lock(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_Unlock(igAliasMemoryPool *self);
extern "C" int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result);
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_54(igAliasMemoryPool *self,long long size);
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_55(igAliasMemoryPool *self,long long size,unsigned short alignment);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_56(igAliasMemoryPool *arg0, int arg1, int arg2);
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_58(igAliasMemoryPool *self,void *old,long long size);
extern "C" void *Gap__Core__igAliasMemoryPool__vfunc_59(igAliasMemoryPool *self,void *old,long long size,unsigned short alignment);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_65(igAliasMemoryPool *arg0, int arg1);
extern "C" igResult Gap__Core__igAliasMemoryPool__vfunc_62(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks);
extern "C" igResult Gap__Core__igAliasMemoryPool__vfunc_63(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks, unsigned short *alignments);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_64(igAliasMemoryPool *self, int count, void **blocks);
extern "C" void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old);
struct OwnsStatus { int v; OwnsStatus(int x) { v = x; } int get() { return v; } };
extern "C" long long igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old);
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
extern "C" void igAliasMemoryPool_PrintStatistics(StatsPool *arg0, char *arg1);
extern "C" int igAliasMemoryPool_GetEventTracker(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_SetEventTracker(igAliasMemoryPool *self, igObject *tracker);
/* igFile's virtuals (vfunc_N at vtable byte 4 * N; the slot symbols are unnamed) and fields; the
 * view igMediaFileView, igPsx2FileView and igAdxFileView derive from. ABI view only: never instantiated. */
class igFileView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igResult vfunc_23(int mode);                                            /* +92: open in a mode number */
    virtual void vfunc_24();                                                        /* +96: close the handle */
    /* Names the file and opens it in a mode string ("r", "wb", ...); nonzero (the file) on success. */
    virtual int Open(const char *name, const char *mode);                           /* +100 */
    virtual void Close();                                                           /* +104 */
    virtual int Read(void *buffer, int size, int count);                            /* +108 */
    virtual void vfunc_28(void *buffer, int count, int (*done)(int, int), int context); /* +112 */
    virtual int Write(const void *buffer, int size, int count);                     /* +116 */
    virtual void vfunc_30();
    virtual void Print(const char *text);                                           /* +124: printf */
    virtual void vfunc_32();                                                        /* +128: flush */
    virtual int vfunc_33();                                                         /* +132: getc */
    virtual void vfunc_34(); virtual void vfunc_35(); virtual void vfunc_36(); virtual void vfunc_37();
    virtual int Seek(int offset, int whence);                                       /* +152: -1 on failure */
    virtual int vfunc_39();                                                         /* +156: tell */
    virtual void vfunc_40();
    /* Prefixes the device of the file's folder (cdrom0:, host0:) and keeps the result as _completeFilename. */
    virtual char *makeCompleteFilename(const char *name);                           /* +164 */
    char *_name;
    char *_fileName;
    int _readMode;
    int _openMode;
    int _fileHandle;
    int _optimalReadChunkSize;
    int _optimalWriteChunkSize;
    unsigned short _pageSize; /* an int field; its readers load the low halfword */
    char *_completeFilename;
};
extern "C" void igAliasMemoryPool_Dump(igAliasMemoryPool *self, int a1, int a2, int a3, int t0);
extern "C" int igAliasMemoryPool_GetPoolIndex(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_SetPoolIndex(igAliasMemoryPool *self, int poolIndex);
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
extern "C" int igAliasMemoryPool_ManageAllocation(ManagedPool *arg0, int arg1, long long arg2, unsigned short arg3);
extern "C" void *igAliasMemoryPool_Initialize(igAliasMemoryPool *self);
extern "C" void *igAliasMemoryPool_Construct(igAliasMemoryPool *self, int extra1);
extern "C" void *igAliasMemoryPool_CopyConstruct(igAliasMemoryPool *self, int extra1);
extern "C" void Gap__Core__igAliasMemoryPool__vfunc_02(igAliasMemoryPool *self);
extern "C" int DAT_00530d80[4];
extern "C" long long DAT_00586dd8[4];
struct Core {
    char pad[21];
    unsigned char f21;
    char pad2[920 - 22];
    void *f920;
    void *f924;
};
extern "C" int DAT_00586dc0[4];
extern "C" char DAT_004f9300[];
extern "C" unsigned char GPR_00554bf8;
struct ObjectSystemView;
class igEventTrackerView;
extern "C" void FUN_002d1a00(ObjectSystemView *self);
extern "C" int IG_ROOT[4];
extern "C" int DAT_004f9468[4];
extern "C" int DAT_004f9470[4];
struct igString {
    char *p;
    igString() : p(0) {}
    igString(char *text) : p(text) {}
    ~igString() {
        char *s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)*header, (int)header);
            }
        }
    }
    void adopt(char *text) {
        char *s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)*header, (int)header);
            }
        }
        p = text;
    }
    void assign(const igString &other) {
        char *o = other.p;
        char *s;
        if (o) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
        s = p;
        if (s) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)*header, (int)header);
            }
        }
        p = other.p;
    }
};
struct Pool { static inline void *get() {
    if (((void * *)g_stringPool)[0] == 0) {
        void *p = (void *)StringPool_Allocate(16);
        if (p != 0) {
            p = ((void *)StringPool_Construct((StringPool *)p));
        }
        ((void * *)g_stringPool)[0] = p;
    }
    return ((void * *)g_stringPool)[0];
} };
extern "C" void FUN_002d1c40(ObjectSystemView *arg0);
extern "C" int text_exitPre[4];
extern "C" void FUN_002d27a0(ObjectSystemView *arg0);
extern "C" int text_exitIn[4];
extern "C" void FUN_002d2de0(ObjectSystemView *arg0);
class MemoryContext;
extern "C" MemoryContext *DAT_00586fd0[4];
extern "C" __internalObjectList *DAT_00587188[4];
extern "C" void FUN_002d2e60(ObjectSystemView *arg0);
/* The object system: only the metadata registry (a pointer list of every registered igMetaObject,
 * +24) is used. */
typedef struct ObjectSystemRecord {
    char unknown0[24];
    int metaRegistry;
} ObjectSystemRecord;
extern "C" void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta);
/* Looks a registered metaobject up by class name. The object system's metadata registry (the
 * pointer list at +24) is searched on the `_name` field of igMetaObject; an inactive object system
 * (flag byte at +0 clear) finds nothing. */


/* The object system behind g_objectSystem: the activity flags, the metadata registry and the
 * counts it held at boot, the callbacks run for every registered meta object, the configuration
 * registry and the event formats are used here. */
typedef struct ObjectSystemView {
    unsigned char active;
    char unknown1[3];
    int bootMetaObjectCount;      /* metaRegistry count when the boot registration finished */
    int bootMetaFieldCount;       /* meta-field registry count at the same point */
    int metaObjectCount;
    char unknown16[4];
    unsigned char started;        /* set first at start-up, cleared last at shut-down */
    unsigned char preExitDone;    /* the "exitPre" marker has been sent */
    char unknown22[2];
    void *metaRegistry;
    char unknown28[8];
    void *auxObjectList;
    void *startupCallbacks;
    void *registrationCallbacks;
    void *bootstrapPool;          /* the allocator of record 0 (Bootstrap) */
    void *systemPool;             /* the allocator of record 4 (System) */
    igRegistry *configRegistry;
    char unknown60[24];
    igEventTrackerView *exitMarkerSink; /* receives the "exitPre" and "exitIn" markers */
    char unknown88[24];
    igObject *retainedObject;     /* released at shut-down */
    char unknown116[1];
    unsigned char dumpEventTrackersAtExit; /* MemoryContext::vfunc_56 runs at exit */
    char unknown118[6];
    void *eventTrackerInitialCapacity;
    char unknown128[16];
    char memoryEventFormat[128];
    char markerEventFormat[128];
    char notificationEventFormat[128];
    char unknown528[388];
    int vtableProbeOffset;        /* zero: the EnsureRegistered probes read the vtable word through it */
    igString rootPath;            /* IG_ROOT from the environment */
    igString basePath;
} ObjectSystemView;
extern "C" igMetaField *g_igMetaObjectNameField[4];
extern "C" int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className);
extern "C" void FUN_002d30d0(ObjectSystemView *arg0, int (*arg1)(int));
extern "C" char *DAT_004c1eb8[4];
extern "C" void FUN_002d31d0(ObjectSystemView *objectSystem, char *format);
extern "C" void * DAT_004c1ec0[4];
extern "C" void FUN_002d3240(ObjectSystemView *objectSystem, char *format);
extern "C" void * DAT_004c1ec8[4];
extern "C" void FUN_002d32b0(ObjectSystemView *objectSystem, char *format);
/* The growable callback array of the class-registration protocol (data pointer, count, capacity).
 * The growth rule is retail's, not a conventional 1.5x: the first capacity is 4 and every later
 * growth multiplies the capacity by (capacity * 3) / 2, so ordinary capacities advance 4 -> 24 ->
 * 864. Do not "fix" it. */
typedef struct {int *data;int count;int capacity;} CallbackArray;
extern "C" CallbackArray *igArray_Construct(CallbackArray *array);
extern "C" CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag);
extern "C" int igArray_Append(CallbackArray *array,int item);
extern "C" void Gap__Core__igBoolArrayMetaField__vfunc_52(igBoolArrayMetaField *self, int buffer, int count);
extern "C" void FUN_002d35d0(igBoolArrayMetaField *arg0, int arg1);
extern "C" int DAT_004f9588[4];
extern "C" int text_true_2[4];
extern "C" int text_false_2[4];
extern "C" int DAT_004f95a0[4];
extern "C" int DAT_00531540[4];
/* igMetaField's virtual functions: slot n sits at vtable byte offset 4 * n (the first two words are
 * the class header). The reflected igMetaField is the same object seen as data. Named slots carry
 * the root-class symbol names (igMetaField_<Name>, or the igMemoryRefMetaField override that names
 * the slot); vfunc_NN slots have no name yet. Slots 2-22 are igObject's. ABI view only: never
 * instantiated. */
struct RecoveryString;
class igMetaFieldView {
public:
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19); RESERVED(20);
    virtual igCompoundMetaField *vfunc_23();                                    /* +92 */
    virtual void vfunc_24(int object, int value);                               /* +96 */
    virtual int GetSize();                                                      /* +100 */
    virtual unsigned int vfunc_26();                                            /* +104 */
    virtual int vfunc_27();                                                     /* +108 */
    virtual int SetToDefault(int object);                                       /* +112 */
    virtual int IgnoreReset(int object);                                        /* +116 */
    virtual int CopyDefaultToValue(int object);                                 /* +120 */
    virtual int ConstructValue(int object);                                     /* +124 */
    virtual int DestructValue(int object);                                      /* +128 */
    virtual void ZeroValue(int object);                                         /* +132 */
    virtual void ClearValue(int object);                                        /* +136 */
    virtual int SetDefault(const void *value);                                          /* +140 */
    virtual void DeepCopy(int dest, int source);                                /* +144 */
    virtual int vfunc_37(int dest, int source);                                 /* +148 */
    virtual void ShallowCopy(int dest, int source);                             /* +152 */
    virtual int vfunc_39(int dest, int source);                                 /* +156 */
    virtual void vfunc_40(int dest, int source);                                /* +160 */
    virtual void Print(int object, int a2, int a3);                             /* +164 */
    virtual int ReleaseElements(int object, int a2, int a3);                    /* +168 */
    virtual int Write(int object, int file);                                    /* +172 */
    virtual int vfunc_44(int a, int b);                                         /* +176 */
    virtual int vfunc_45(int a, int b);                                         /* +180 */
    virtual int IsAlikeDeep(int a, int b);                                      /* +184 */
    virtual int IsAlikeShallow(int a, int b);                                   /* +188 */
    virtual int vfunc_48(int a, int b);                                         /* +192 */
    RESERVED(47);                                                               /* +196 */
    virtual int WriteRawFieldMem(int dest, int source, int a3, int a4);         /* +200 */
    virtual int ReadRawFieldMem(int dest, int source, int a3, int a4);          /* +204 */
    virtual int SwapBytes(void *buffer, int count);                               /* +208 */
    virtual void SwapValue(int object);                                         /* +212 */
    RESERVED(52); RESERVED(53);                                                 /* +216, +220 */
    virtual void vfunc_56(int object, int text, int a3);                        /* +224 */
    virtual RecoveryString vfunc_57(int object, int a2);                        /* +228 */
};
extern "C" void FUN_002d3950(igCallStackTableView *table);
extern "C" void Gap__Core__igCallStackTable__vfunc_24(igResult *result, igCallStackTableView *table, int count);
extern "C" unsigned int *Gap__Core__igCallStackTable__vfunc_25(igCallStackTableView *table, int offset);
extern "C" void Gap__Core__igCallStackTable__vfunc_27(igCallStackTableView *table, int *stack);
typedef struct CallStackHashTable { int vt; int rc; unsigned int count; } CallStackHashTable;
typedef struct CallStackTableView { char pad[20]; CallStackHashTable *table; } CallStackTableView;
extern "C" unsigned int Gap__Core__igCallStackTable__vfunc_29(CallStackTableView *self, unsigned int *stack);
struct CallStackIndexList { int vt; int rc; int count; int capacity; int *data; };
struct CallStackIndexCells { int vt; int rc; int count; int capacity; unsigned int *data; };
class CallStackTableHashView { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual int Hash(int *key);
    virtual void s28();
    virtual void Rehash(int size);
    int rc; int pad8; int pad12; CallStackIndexList *words; CallStackIndexList *index;
};
extern "C" int Gap__Core__igCallStackTable__vfunc_30(CallStackTableHashView *self, int *key, int value);
extern "C" int DAT_004c1e98[];
extern "C" void Gap__Core__igCallStackTable__vfunc_31(igCallStackTableView *table, int hashCapacity);
extern "C" int DAT_004c1ea0[4];
class igResult {
public:
    int v;
    igResult() {}
    igResult(int x) : v(x) {}
    igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    bool operator!=(const igResult &o) const { return v != o.v; }
    inline bool failed() const;
    int get() { return v; }
};
/* igCallStackTracer (reflected layout in dw4/reflected.h; an igUnsignedIntListNoClean of return
 * addresses) with the virtuals its callers use. */
class igCallStackTracerView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vfunc_25();
    virtual void d24();
    virtual igResult vfunc_27(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual igResult vfunc_28(int addr, char *buf, int offset, char *name, int line, int format, long long output, long long outputSize);
    virtual void vfunc_29();
    virtual void vfunc_30();
    int _count;
    int _capacity;
    unsigned int *_data;
};
extern "C" void Gap__Core__igCallStackTracer__vfunc_26(igResult *result, igCallStackTracerView *self, int addr, int format, long long output, long long outputSize);
extern "C" const igResult g_resultSuccess;
extern "C" const igResult g_resultFailure;
extern "C" igResult FUN_0030e430(igPsx2Thread *self, int priority);
class Resolver { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual int IsReady();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual igResult Lookup(int addr, char *buf, int size, int *base, int *other, char *name, int nameSize, int *line);
};
extern "C" igResult Gap__Core__igCallStackTracer__vfunc_27(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" void Gap__Core__igCharArrayMetaField__vfunc_52(igCharArrayMetaField *self, int buffer, int count);
extern "C" unsigned short Gap__Core__igCharArrayMetaField__vfunc_25(igCharArrayMetaField *self);
extern "C" int DAT_004f95c0[4];
extern "C" int DAT_00531640[4];
extern "C" int FUN_002d4e90(igCompoundMetaField *arg0);
extern "C" void FUN_002d5020(igCompoundMetaField *arg0, int arg1);
extern "C" void FUN_002d50a0(igCompoundMetaField *arg0, int arg1);
extern "C" void FUN_002d5120(igCompoundMetaField *a, int x);
extern "C" void FUN_002d51a0(igCompoundMetaField *arg0, int arg1);
extern "C" void FUN_002d5340(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" void FUN_002d53d0(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" void FUN_002d5460(igCompoundMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_002d5500(igCompoundMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_002d55a0(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d5640(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d56e0(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d5780(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d5820(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d58c0(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int FUN_002d59f0(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int FUN_002d5ad0(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void FUN_002d5bb0(igMetaFieldView *arg0, int arg1, int arg2);
extern "C" int DAT_004f95e8[4];
extern "C" int DAT_004f95f0[4];
extern "C" int DAT_004f95f8[4];
extern "C" int DAT_004f9600[4];
struct RecoveryString {
    char *p;
    RecoveryString(char *q) { p = q; }
    RecoveryString(const RecoveryString &o) { p = o.p; if (p != 0) *(int *)(p - 4) = *(int *)(p - 4) + 1; }
    ~RecoveryString() {
        if (p != 0) {
            int *t = (int *)(p - 8);
            int v = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = v;
            if (v == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)*t, (int)t);
        }
    }
    RecoveryString &operator=(const RecoveryString &o) {
        if (o.p != 0) *(int *)(o.p - 4) = *(int *)(o.p - 4) + 1;
        if (p != 0) {
            int *t = (int *)(p - 8);
            int v = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = v;
            if (v == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)*t, (int)t);
        }
        p = o.p;
        return *this;
    }
};
extern "C" int FUN_002d5df0(RecoveryString *out, igMetaFieldView *ctx, int a2, int a3);
struct Util {
    static inline void rel(igObject *o) { if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)o); } }
};
extern "C" void FUN_002d60b0(igContext *arg0);
extern "C" int FUN_002d6390(igContext *arg0);
extern "C" int FUN_002d63e0(igContext *arg0, int arg1);
/* igContextExt's own virtual functions past igObject's (slot n at vtable byte offset 4 * n); no
 * symbol names them. ABI view only: never instantiated. */
class igContextExtView {
public:
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19); RESERVED(20);
    RESERVED(21); RESERVED(22); RESERVED(23); RESERVED(24); RESERVED(25);
    virtual int vfunc_28(igVisualContext *context);                             /* +112 */
    virtual int vfunc_29(igVisualContext *context);                             /* +116 */
};
extern "C" void *FUN_002d64c0(igVisualContext *arg0, int extra1);
extern "C" int FUN_002d65e0(igContext *arg0, int arg1);
extern "C" igMetaField *DAT_005867a0[4];
extern "C" void List_Reserve(igDataList *list, int capacity, int elementSize);
extern "C" void List_AppendBytes(igDataList *l, int cnt, int src, int sz);
extern "C" void List_RemoveAt(igDataList *l, int i, int sz);
extern "C" int List_BinarySearch(igDataList *arg0, int arg1, int (*arg2)(int, int), int arg3);
extern "C" int List_AppendWord(igDataList *list, int value);
extern "C" int ObjectList_AppendRetained(igObjectList *list, igObject *object);
typedef struct WordList { char pad[8]; int count; int cap; int *data; } WordList;
extern "C" void List_AppendWords(WordList *arg0, int arg1, int arg2);
extern "C" void List_RemoveWordAt(igDataList *l, int i);
extern "C" int List_BinarySearchWords(igDataList *arg0, int arg1, int (*arg2)(int, int));
typedef int (*Cmp)(int *, void *);
extern "C" int FUN_002d6e60(igDataList *l, void *key, Cmp cmp);
struct DependencyPair { int a; int b; };
struct igDependencyListView {
    int _vtable; unsigned int _refCount; int _count; int _capacity; DependencyPair *_data;
    int Find(int k1, int k2) { int i; for (i = 0; i < _count; i++) { DependencyPair *p = &_data[i]; int v = (k1 == p->a); if (v) { v = (k2 == p->b); } if (v) { return i; } } return -1; }
};
struct ObjectList : igObject { int count; int capacity; igObject **data; };
struct igDependencyOrderedListView {
    int _vtable; unsigned int _refCount;
    ObjectList *_objectList;
    igDependencyListView *_dependencies;
    int _order;
    int _checkPoints;
    unsigned char _hasCircularDependencies;
};
extern "C" void FUN_002d7090(igDependencyOrderedListView *arg0, int arg1, int arg2);
extern "C" int igRendererOrderedList_Append(igDependencyOrderedListView *, igObject *, int);
extern "C" void FUN_002d7130(igDependencyOrderedListView *owner);
extern "C" void FUN_002d7750(igResult *result, igDependencyOrderedListView *list, igObject *object);
extern "C" void FUN_002d7760(int *arg0, igDependencyOrderedListView *arg1, int arg2, int arg3);
extern "C" void FUN_002d7840(igDependencyOrderedListView *arg0, int arg1);
class igSemaphoreView;
struct igDirectoryView;
struct igDirectoryListView { int _vtable; unsigned int _refCount; int _count; int _capacity; igDirectoryView **_data; };
struct igDirectoryView {
    int _vtable; unsigned int _refCount; int _count; int _capacity; int _data; int _name;
    igDirectoryListView *_externalDirectoryList; int _infoList; int _managingResource;
    char _pad36[16]; int _loadedRefCount; char _pad56[12]; igSemaphoreView *_loadingSemaphore;
};
typedef struct L7c50 { char pad0[8]; int n; char pad1[4]; unsigned *data; } L7c50;
typedef struct O7c50 { char pad[44]; L7c50 *l; } O7c50;
class igIGBFileView;
class igDirEntryView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_23(int ref);
    virtual void vfunc_24(int ref);
    virtual void d25();
    virtual igDirEntryView *resolve(igIGBFileView *file);                       /* vfunc_26 */
    virtual void setReferenceIndex(int index);                                  /* vfunc_27 */
    virtual void vfunc_28(int ref);
    virtual void setMemoryPool(int pool);                                       /* vfunc_29 */
    virtual int memoryPoolIndex();                                              /* vfunc_30 */
    virtual void readFinished(igIGBFileView *file);                             /* vfunc_31 */
    virtual void vfunc_32(igIGBFileView *file);
    virtual void vfunc_33(igIGBFileView *file);
    virtual void vfunc_34(igIGBFileView *file);
    virtual void vfunc_35(igIGBFileView *file);
    virtual void vfunc_36(int flag);
    virtual void vfunc_37(igIGBFileView *file);
    virtual int vfunc_38(igIGBFileView *file);
    virtual int vfunc_39(igIGBFileView *file);
    virtual void vfunc_40(igIGBFileView *file);
    virtual int vfunc_41(igIGBFileView *file);
    virtual void d42();
    virtual void vfunc_43(int index);
    int _name; int _index; int _resolveMethod; int _refType; int _ref;
};
class igExternalDirEntryView : public igDirEntryView { public:
    int _directoryName; int _entryName; int _entryIndex; int _externalFilePath;
};
struct L7da0 { char pad[8]; int cnt; char pad2[4]; int *arr; };
struct A7da0 { char pad[16]; igDirEntryView **arr; char pad2[20]; int f40; struct L7da0 *l; };
class VC7e90 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); };
struct FieldBindMeta;
class FieldBindObject : public igVirtualObject { public:
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual FieldBindMeta *GetMeta();
    virtual void Assign(void *value);

};
struct FieldBindSlotList : public igObject { int count; int capacity; FieldBindObject **data; };
struct FieldBindSet : public igObject { int count; int pad12; FieldBindObject **targets; char pad20[24]; FieldBindSlotList *overrides; };
struct FieldBindItem { int pad0; int pad4; int offset; char pad12[12]; FieldBindObject *source; };
struct RemovableList : igTDataList<igObject *> {
    void removeAt(int index) {
        igObject *o = _data[index];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt((igDataList *)this, index);
        _data[_count] = 0;
    }
};
struct RemovableListHolder { char pad[28]; RemovableList *list; };
class O83b0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vf(int, int); int a; int b; int c; unsigned char flag; };
struct Lst83b0 { int pad0; int pad1; int count; int pad3; O83b0 **data; };
struct T83b0 { char pad[28]; Lst83b0 *list; };
struct Ent8520;
typedef struct A86b0 { char p[8]; int n; } A86b0;
typedef struct K86b0 { char p[8]; int f8; } K86b0;
struct FieldLinkInfo;
class FieldLinkObject : public igVirtualObject { public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual void Prepare();
    virtual void s14(); virtual void s15();
    virtual void Touch();
    virtual void SetPool(int pool);
    virtual void s18(); virtual void s19();
    virtual FieldLinkInfo *GetMeta();
    virtual void Assign(void *value);
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void SetContext(int mode);
    virtual void s28();
    virtual int Classify(void *pool);
};
struct FieldLinkInfo { char pad[64]; int (*poolFor)(); };
struct FieldLinkRecord : FieldLinkObject { int pad8; int index; int user; int extra; };
struct FieldLinkSet : public igObject { int count; char pad12[44]; char reset; char pad57[7]; unsigned char mode; unsigned char tracks; unsigned char namedPools; };
struct Ctx8a80 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual int v29(int); };
struct E8a80 : public igVirtualObject { virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(int); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(int); int p8; int idx; int f16; int f20; int p24; int f28; char p32[12]; int f44; int p48; char f52; };
struct L8a80 { char p0[8]; int count; char p12[53]; unsigned char f65; unsigned char f66; };
class R8d00 : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(int); int f8; int f12; int f16; int f20; };
struct Lst8d00 { char pad[8]; int n; };
struct P8eb0 { int pad[6]; int val; };
class Tgt { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void v80(void *);  };
struct Coll { char pad[8]; unsigned n; char pad2[44]; unsigned char done; };
typedef struct A8fe0 { char pad[20]; int *f20; } A8fe0;
struct Item { int pad[6]; int f24; };
struct Cont { int pad[2]; int count; };
struct RefCountResult { int w0; RefCountResult() {} RefCountResult(const RefCountResult &o) { w0 = o.w0; } };
class RefCountLock { public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual RefCountResult Unlock();
    virtual void s30();
    virtual RefCountResult Acquire(int wait);
};
struct RefCountedHandle;
typedef igTDataList<RefCountedHandle *> RefCountOwnerList;
struct RefCountOwnerHolder { char pad[16]; RefCountOwnerList *list; };
struct RefCountedHandle { int _vtable; unsigned int _refCount; char pad8[24]; RefCountOwnerHolder *holder; char pad36[16]; int refs; char pad56[12]; RefCountLock *lock; };
struct ConfigureResult { int value; };
struct Driver {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20();
    virtual ConfigureResult configure();
    int references;
};
struct DriverOwner { char pad[68]; Driver *driver; };
struct DriverType {};
extern "C" Ctx8a80 *FUN_002f88d0(...);
extern "C" int DAT_00586730[4];
extern "C" int g_propertyNameField[4];
extern "C" void Gap__Core__igDirectory__vfunc_12(igDirectoryView *arg0);
extern "C" int FUN_002d7c50(O7c50 *arg0, unsigned key);
extern "C" void FUN_002d7da0(A7da0 *a, int i, int x);
extern "C" int FUN_002d7f10(FieldBindSet *self, FieldBindObject **field, FieldBindObject **value);
extern "C" void FUN_002d8230(RemovableListHolder *h, igObject *object);
extern "C" int FUN_002d83b0(T83b0 *arg0, int arg1, int arg2);
class VisitorFieldView;
extern "C" int FUN_002d8520(int arg0, VisitorFieldView *arg1, igDirectoryView *arg2);
extern "C" int FUN_002d86b0(A86b0 *arg0, K86b0 *arg1, unsigned arg2);
template <class T> struct RetainedWord {
    T *p;
    RetainedWord(T *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};
extern "C" int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user);
extern "C" int FUN_002d8a80(L8a80 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7);
struct Retained {
    R8d00 *p;
    Retained(R8d00 *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};
extern "C" int FUN_002d8d00(Lst8d00 *list, int key, int name, int val);
extern "C" void FUN_002d8f20(Coll *arg0);
extern "C" void FUN_002d8fe0(A8fe0 *arg0, int arg1);
extern "C" int Gap__Core__igDirectory__vfunc_25(Cont *c, igExternalDirEntryView *o);
extern "C" int FUN_002d91c0(RefCountedHandle *self);
extern "C" void FUN_002d9330(DriverOwner *owner);
extern "C" void igDoubleArrayMetaField_SwapBytes(igDoubleArrayMetaField *arg0, int arg1, int arg2);
extern "C" int igDoubleArrayMetaField_GetSize(igDoubleArrayMetaField *self);
extern "C" int text_lg_n[4];
extern "C" int DAT_004f9610[4];
extern "C" int text_driverDatabaseVerbose[4];
static inline void release(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)object);
        }
    }
}
struct PropertyRef;
static inline void setAt_2d9540(igDriverDatabase *database, int index, const PropertyRef &value);
struct PropertyRef {
    igObject *p;
    PropertyRef(igObject *object) : p(object) {}
    ~PropertyRef() { release(p); }
};
extern "C" void Gap__Core__igDriverDatabase__vfunc_11(igDriverDatabase *database);
extern "C" int FUN_001cafc0(igObject *, int *, int);
extern "C" int FUN_002d9cf0(igDriverDatabase *arg0, int arg1, int arg2);
struct ConfigPlatformText : public igObject { char *text; };
class ConfigPlatformSource {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void Describe(void *target);
};
struct ConfigPlatformSourceList : public igObject { int count; int capacity; ConfigPlatformSource **data; };
extern "C" char *g_stringObjEmptyText[4];
extern "C" void FUN_002da010(void *self, ConfigPlatformSourceList *list);
extern "C" int text_drivers_ini[4];
extern "C" int DAT_004f96a8[4];
static inline void release_2da1c0(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct Mem { igStringObj *p; Mem() {} ~Mem() { release_2da1c0(p); } };
/* Header stored in front of every interned string token. */
struct StringTokenHeader { int owner; int refCount; };
static inline void releaseString(const char *string) {
    if (string != 0) {
        StringTokenHeader *header = (StringTokenHeader *)string - 1;
        int count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)header->owner, (int)header);
        }
    }
}
struct StringRef {
    const char *p;
    StringRef() : p(0) {}
    StringRef(const char *string) : p(string) {}
    ~StringRef() { releaseString(p); }
};
struct igFolderView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual Mem vfunc_23(const char *name); };
extern "C" int FUN_002da1c0(igDriverDatabase *arg0, const char *arg1, const char *arg2);
class TrackedEntry { public: int f0; virtual void Delete(int flags); };
struct TrackedEntryList { int vt; unsigned int _refCount; int count; int cap; TrackedEntry **data; };
extern "C" TrackedEntryList *FUN_002da780(igDriverDatabase *s);
extern "C" void FUN_002da850(void *self, TrackedEntryList *list);
extern "C" int DAT_00530618[4];
extern "C" int FUN_002da990(igDriverDatabase *arg0, int arg1, int arg2, int arg3);
/* The character variable is an int; a char would add a sign extension. */
extern "C" void FUN_002daac0(igDriverDatabase *arg0, int arg1);
extern "C" int text_psx2_2[4];
extern "C" int text_mips[4];
extern "C" bool FUN_002dacc0(void *a0, igFileView *s, char *buf, int n);
struct ConfigOutputList;
struct ConfigTreeToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigTreeNode;
struct ConfigTreeChildren { int vt; int rc; int count; int capacity; ConfigTreeNode **data; };
struct ConfigTreeNode { int kind; int pad4; void *name; ConfigTreeToken *value; ConfigTreeChildren *children; int attributes; ConfigTreeToken *selector; };
struct KeyValueText { int a; int b; char *text; };
struct KeyValuePair { KeyValueText *key; KeyValueText *value; };
struct KeyValuePairList { int vt; int rc; int count; int cap; KeyValuePair **data; };
extern "C" void FUN_002db1d0(void *self, KeyValuePairList *list, void *a, void *b);
struct ConfigValueToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigValueResolver { char pad[20]; void *table; void *scope; int mode; };
extern "C" int FUN_002db2f0(ConfigValueResolver *self, ConfigValueToken *token, int key, int fallback);
extern "C" char _ctype_[];
extern "C" int text_abcdefghijklmnopqrstuvwxyzABCDEF[4];
extern "C" bool FUN_002db540(igDriverDatabase *arg0, int *arg1);
extern "C" int DAT_004f9718[4];
extern "C" int DAT_004f9670[4];
extern "C" int DAT_004f9728[4];
struct ConfigToken { int vt; unsigned int _refCount; char *text; int kind; };
struct ConfigChildList { int vt; int rc; int count; int capacity; int *data; int getCount() const { return count; } };
extern "C" int FUN_002dba50(igDriverDatabase *self, struct ConfigSectionNode *out);
extern "C" int FUN_002dbc10(igDriverDatabase *parser, int arg1);
extern "C" int DAT_004f9730[4];
extern "C" int DAT_004f9738[4];
extern "C" int DAT_00530608[4];
class ConfigPair { public: igStringObj *key; igStringObj *value; virtual void Delete(int flags); };
extern "C" ConfigPair *FUN_002dc1e0(ConfigPair *self, int delete_storage);
extern "C" int DAT_005305f8[4];
extern "C" unsigned char g_useOwnerAllocator;
struct ConfigSettingsNode { int kind; int vtable; igTDataList<ConfigPair *> *entries; igStringObj *name; };
extern "C" int FUN_002db750(igDriverDatabase *self, ConfigSettingsNode *out);
extern "C" void *FUN_002dc340(ConfigSettingsNode *arg0, long long arg1);
extern "C" int DAT_005305e8[4];
struct ConfigSectionNode { int kind; int vtable; int id; igStringObj *name; igTDataList<TrackedEntry *> *children; int attributes; igObject *selector; };
extern "C" void *FUN_002dc530(ConfigSectionNode *arg0, long long arg1);
extern "C" void Gap__Core__igEnumArrayMetaField__vfunc_52(igEnumArrayMetaField *self, int buffer, int count);
extern "C" int Gap__Core__igEnumArrayMetaField__vfunc_25(igEnumArrayMetaField *self);
extern "C" void FUN_002dc7a0(igMetaFieldView *self, const int *value);
extern "C" void Gap__Core__igEnumMetaField__vfunc_57(int result, igEnumArrayMetaField *self, int *value);
extern "C" int DAT_00532430[4];
extern "C" void * DAT_00586df8[4];
extern "C" char GPR_00554bfc;
extern "C" unsigned char DAT_00554bfc;
class RefPool : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igResult open();
    virtual igResult close();
    
};
struct PoolOwner { char p[8]; RefPool *pool; };
extern "C" void FUN_002dcaa0(PoolOwner *self, int open);
class igEventTrackerView;
extern "C" void FUN_002dcc60(igEventTrackerView *tracker, int tag);
struct LocationRecord { int address; int name; int offset; int file; int line; };
/* igLocationTable (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
class igLocationTableView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vfunc_26(int address);
    virtual igResult vfunc_27(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void d26();
    virtual void vfunc_29(int addr, char *buf, int offset, char *name, int line);
    virtual int vfunc_30(int address);
    virtual int vfunc_31(int address, int index);
    virtual void vfunc_32(int capacity);
    int _capacity; int _hashCapacity; igTDataList<unsigned int> *_locations; igTDataList<int> *_hashIndex; int _symbolNames; int _sourceFileNames;
};
/* An event record decoded from the tracker's record stream. */
struct EventRecord { int type; int pad[2]; int val; int pad2[8]; char *str; int rest[26]; int getVal() const { return val; } };
/* igEventTracker (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
/* A bare result word: igResult's constructors would change how the caller takes the return. */
struct EventReadResult { int code; int Code() { return code; } };
struct EventRecordInfo;
class igEventTrackerView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_23();                                                    /* slot 21, byte 92 */
    virtual void d22(); virtual void d23();
    virtual void vfunc_26(EventRecordInfo *info, int mode);
    virtual EventReadResult vfunc_27(int offset, EventRecord *record);
    virtual void d26();
    virtual igResult vfunc_29(int offset, int *value);
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual int vfunc_34(int offset);
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
    virtual igResult vfunc_40(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void vfunc_41(int offset);
    virtual void d40(); virtual void d41();
    virtual igResult vfunc_44(char *name);                                      /* slot 42, byte 176 */
    virtual void vfunc_45();
    virtual int vfunc_46();                                                     /* slot 44, byte 184 */
    virtual int vfunc_47();                                                     /* slot 45, byte 188 */
    virtual int vfunc_48(int hash);
    virtual void vfunc_49(int value, int offset);
    virtual void vfunc_50(int capacity);
    igSemaphoreView *_lock;
    int _flags;
    unsigned int _eventTypeFilterFlags;
    unsigned int _memoryFieldFilterFlags;
    unsigned int _markerTypeFilterFlags;
    unsigned int _notificationTypeFilterFlags;
    unsigned int _notificationCodeFilterFlags;
    int _capacity;
    int _count;
    int _detachAllocationsCounter;
    int _names;
    int _groups;
    int _classNames;
    int _memberNames;
    int _annotations;
    int _sourceFileNames;
    int _callStacks;
    igLocationTableView *_locations;
    igTDataList<signed char> *_eventRecords;
    igTDataList<int> *_hashIndex;
    int _codeReferenceAddress;
    igCallStackTracerView *_callStackTracer;
    int _eventFormatOffsets[32];
    int _defaultMemoryEventFormat;
    int _eventTypeNameOffsets[32];
    int _markerTypeNameOffsets[32];
    int _notificationTypeNameOffsets[16];
    int _notificationCodeNameOffsets[64];
    char _formatBuffer[8196];
    char _eventTag[256];
    int _eventTagOffset;
    char _eventClassName[256];
    int _eventClassNameOffset;
    int getFlags() const { return _flags; }
    bool isBusy() const { return _flags & 2; }
};
extern "C" void FUN_002dcd70(igEventTrackerView *tracker, int className);
extern "C" void Gap__Core__igEventTracker__vfunc_23(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_24(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_25(igEventTrackerView *self);
extern "C" int DAT_004c1ea8[4];
extern "C" void Gap__Core__igEventTracker__vfunc_33(igEventTrackerView *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7);
extern "C" int Gap__Core__igEventTracker__vfunc_31(igEventTrackerView *self, int value);
struct EventRecordInfo { int kind; char pad4[64]; int f68; int f72; int *pending; char pad80[80]; };
extern "C" char text_main[];
extern "C" void Gap__Core__igEventTracker__vfunc_37(igEventTrackerView *self, char *wanted);
extern "C" unsigned int Gap__Core__igEventTracker__vfunc_48(igEventTracker *self, unsigned int hash);
extern "C" void Gap__Core__igEventTracker__vfunc_49(igEventTrackerView *self, int arg1, int arg2);
extern "C" int DAT_004c2120[4];
extern "C" void Gap__Core__igEventTracker__vfunc_50(igEventTrackerView *self, int n);
extern "C" int FUN_002e1550(igEventTrackerView *tracker, int type);
extern "C" int FUN_002e15a0(igEventTrackerView *tracker, int type);
extern "C" igResult Gap__Core__igEventTracker__vfunc_39(igEventTrackerView *self, int addr, int format, long long output, long long outputSize);
extern "C" int DAT_00586e00[4];
extern "C" int DAT_00586e08[4];
extern "C" int DAT_00586e10[4];
/* The result type has a constructor, so the return writes straight through the saved hidden
 * pointer. */
extern "C" igResult Gap__Core__igEventTracker__vfunc_40(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" void Gap__Core__igEventTracker__vfunc_41(igEventTrackerView *self, int arg);
extern "C" void Gap__Core__igEventTracker__vfunc_42(igEventTrackerView *self);
extern "C" int DAT_004c1ed8[4];
extern "C" igResult Gap__Core__igEventTracker__vfunc_44(igEventTrackerView *self, int arg2);
extern "C" void Gap__Core__igEventTracker__vfunc_45(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_46(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_47(igEventTrackerView *self);
typedef struct Cfg { char pad[128]; int a; int b; int c; int d; } Cfg;
extern "C" int DAT_004c1ee0[32];
extern "C" int DAT_004c1f60[32];
extern "C" int DAT_004c1fe0[16];
extern "C" int DAT_004c2020[64];
extern "C" void Gap__Core__igEventTracker__vfunc_13(igEventTrackerView *self);
struct BitSlots { char pad[80]; unsigned int bits; };
extern "C" int FUN_002e23b0(struct BitSlots *arg0, int arg1);
extern "C" char DAT_004f99f0[];
extern "C" unsigned char GPR_00554c00;
extern "C" void Gap__Core__igExternalDirEntry__vfunc_31(igExternalDirEntryView *arg0, void *arg1);
extern "C" void FUN_002e26b0(igExternalDirEntry *arg0, int arg1);
extern "C" void Gap__Core__igExternalDirEntry__vfunc_23(igDirEntry *arg0, igObject *arg1);
extern "C" int DAT_004f9a48[4];
extern "C" int text_root[4];
class igIGBFileView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual int vfunc_28(int);
    virtual int ReadFile(const char *path);
    virtual igResult vfunc_30();
    virtual igResult vfunc_31();
    virtual igResult vfunc_32();
    virtual igResult vfunc_33();
    virtual int vfunc_34();
    int _count;                                                     /* +8 */
    int _capacity;
    igDirEntryView **_data;
    char *_name;
    igDirectoryListView *_externalDirectoryList;                    /* +24 */
    igObjectList *_infoList;
    igResource *_managingResource;
    unsigned char _sharingState; unsigned char _trackUniqueEntries; char _pad38[2];
    igObjectList *_uniqueEntryList;                                 /* +40 */
    igIntList *_refList;
    unsigned char _loadPendingState; unsigned char _validState; unsigned char _compatibleState; char _pad51[1];
    int _loadedRefCount;
    unsigned char _concreteState; char _pad57[3];
    igIntList *_metaFieldPerObjectIndices;                          /* +60 */
    unsigned char _autoWriteFilePreProcessState; unsigned char _useMemoryPoolAssignmentsState; unsigned char _forceWriteMemoryPoolInfoFromMetaState; char _pad67[1];
    igSemaphoreView *_loadingSemaphore;
    int _majorVersion; int _minorVersion;                           /* +72 */
    int _chunkPlace; int _bufferPlace; int _bufferSize;             /* +80 */
    igObject *_entryPool;                                           /* +92 */
    int _magicCookie; int _magicVersion;
    igFileView *_file;                                              /* +104 */
    unsigned char _hasTemplates; char _pad109[3];
    int _entryCount; int _indexBufferSize;                          /* +112 */
    void *_indexBuffer;                                             /* +120 */
    int _entryBufferSize; int _metaObjectCount; int _metaObjectBufferSize; int _metaFieldCount; int _metaFieldBufferSize;
    int _objectCount; int _objectBufferSize; int _memoryRefCount; int _memoryRefBufferSize; /* +144 */
    int _userLoadFunction; int _forceChunkSize;                     /* +160 */
    unsigned char _endianSwap; char _pad169[3];
    void *_metaObjectBuffer; void *_dirBuf; void *_objBuf; char *_mfBuf; /* +172 */
    igObjectList *_metaFieldListInFile;                             /* +188 */
    igObjectList *_metaObjectListInFile;
    int _autoOpened;
    char *_basePath;                                                /* +200 */
    igMetaFieldView *imf; igMetaFieldView *smf;
    unsigned char _hasInfo; unsigned char _hasExternal; unsigned char _sharedEntries; unsigned char _hasVersion1Cruft; /* +212 */
    int _version1CruftMultiply; int _infoListPlace;
    int *_externalDirectoryBuffer; int _externalDirectoryBufferSize; /* +224 */
    char *_previousResourceFilePath;
    int *_alignmentBuffer; int _alignmentBufferSize;                /* +236 */
    igIntList *_alignmentListInFile; int _alignmentCount;
    int _objectBufferPlace; int _memoryBufferPlace; int _chunkSize; /* +252 */
    char *_chunk;                                                   /* +264 */
    int _memoryBytesCopied; int _bytesRemainingInChunk;
    unsigned char _hasCriticalFailure; unsigned char _autoReadFilePostProcessState; unsigned char _autoWriteFilePostProcessState; unsigned char _readFilePostProcessedState;
    igMemoryPoolView *_temporaryMemoryPool; igMemoryPoolView *_dataMemoryPool; igMemoryPoolView *_objectMemoryPool; /* +280 */
    unsigned char _hasMemoryPoolNames; char _pad293[3];
    int _memoryPoolNameBufferSize; int *_memoryPoolNameBuffer;      /* +296 */
    igIntList *_memoryPoolHandles;                                  /* +304 */

    /* Stores an entry, retaining it and releasing the one it replaces. */
    void setEntry(int i, const igSmartPointer<igDirEntryView> &held) {
        igDirEntryView *entry = held.p;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
    void setEntryRaw(int i, igDirEntryView *entry) {
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igVirtualObject *old = _data[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && i >= 0 && i < _count) {
            _data[i] = entry;
        }
    }
};
extern "C" int Gap__Core__igExternalDirEntry__vfunc_44(igExternalDirEntryView *arg0, int arg1);
extern "C" void Gap__Core__igExternalDirEntry__vfunc_11(igDirEntry *arg0);
extern "C" void Gap__Core__igExternalIndexedEntry__vfunc_32(igExternalIndexedEntry *arg0, void *arg1);
class igInfoView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual int GetFieldValueByName(int name);
};
extern "C" void Gap__Core__igExternalInfoEntry__vfunc_31(igExternalInfoEntry *self, igDirectory *directory);
extern "C" int DAT_004c2128[4];
extern "C" void **DAT_00586e18[4];
extern "C" int text_searchFilePath[4];
extern "C" int Gap__igAdxFile__vfunc_39(igFileView *arg0, int arg1);
extern "C" int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self);
extern "C" void igFloatArrayMetaField_SwapBytes(igFloatArrayMetaField *arg0, int arg1, int arg2);
extern "C" int DAT_004f9a68[4];
extern "C" int DAT_004f9a70[4];
struct Holder { igStringObj *p; Holder() {} Holder(const Holder &o) { p = o.p; } };
class Named { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual Holder Find(int key);
    int rc;
    char *name;
};
extern "C" void FUN_002e3850(Named *self, int key);
extern "C" int DAT_004f9a78[4];
extern "C" igSmartPointer<igObject> Gap__Core__igFolder__vfunc_23(igFolder *folder, int name);
class Clock {
public:
  virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22();
  virtual int now();
};
struct LogContext { char pad[56]; int f56; };
struct FieldOffsetInfo { char pad[8]; int f8; };
struct ReflectedRefObject { int vt; int rc; };
struct ReflectedNameObject { int vt; int rc; char *name; };
struct ReflectedNameList { int vt; int rc; int count; int cap; ReflectedNameObject **data; };
struct ReflectedValueList { int vt; int rc; int count; int cap; int *data; };
struct ReflectedRegistry { char p0[44]; ReflectedNameList *names; ReflectedValueList *values; };
extern "C" int DAT_004c2130[4];
extern "C" int DAT_004c2138[4];
extern "C" int DAT_004c2140[4];
extern "C" char text_forceWriteMemoryPoolInfoFromMeta[];
extern "C" char text_blindObjects[];
extern "C" int text_readFile_s[4];
extern "C" char DAT_004f9af0[];
extern "C" char text_Total_Time_to_load_s_f_seconds[];
extern "C" FieldOffsetInfo *DAT_00586280[4];
extern "C" ReflectedRegistry *g_globalContext;
extern "C" char DAT_00586e20[64];
extern "C" Clock *DAT_005871d8[4];
extern "C" char GPR_00554c04;
extern "C" unsigned char GPR_00554c08;
extern "C" unsigned char GPR_00554c0c;
extern "C" unsigned char g_useOwnerAllocator;
extern "C" igResult FUN_002e4f60(void *);
extern "C" igResult FUN_002e63e0(void *);
struct StreamHolder { igFileView *p; StreamHolder(igFileView *v) { p = v; } ~StreamHolder(); };
extern "C" igResult FUN_002e3a60(igIGBFileView *self, const char *fileName, int mode);
extern "C" void FUN_002e3cb0(igIGBFileView *self);
extern "C" igResult FUN_002e3e30(igIGBFileView *f, const char *fileName);
extern "C" igResult FUN_002e3f50(igIGBFileView *arg1);
extern "C" igResult FUN_002e4090(igIGBFileView *arg1);
extern "C" igResult FUN_002e4120(igIGBFileView *o);
extern "C" igResult FUN_002e4240(igIGBFile *arg1);
struct MetaTableField { char p0[18]; short size; unsigned short offset; char p22[15]; unsigned char inherited; unsigned char persistent; };
struct MetaTableFieldList { char p0[8]; MetaTableField **data; int count; };
struct MetaTableType { char p0[16]; int a16; int a20; char p24[4]; char *name; char p32[8]; MetaTableFieldList *fields; char p44[12]; int parent; };
struct MetaTableWords { int vt; int rc; int count; int cap; int *data; };
struct MetaTableRecord { int nameSize; int a4; int a8; int fieldCount; int parent; int persistCount; };
class IntListHolder { public: MetaTableWords *p; IntListHolder(MetaTableWords *o) : p(o) { }
 ~IntListHolder() { MetaTableWords *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
struct MetaTableKey { int v; };
extern "C" igResult FUN_002e42d0(igIGBFileView *self);
extern "C" igResult FUN_002e47f0(igIGBFileView *arg1);
class NameListHolder { public: ReflectedNameList *p; NameListHolder(ReflectedNameList *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~NameListHolder() { ReflectedNameList *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
extern "C" igResult FUN_002e4a40(igIGBFileView *self);
extern "C" igResult FUN_002e4c90(igIGBFileView *self);
extern "C" igResult FUN_002e4e60(igIGBFile *file);
struct IgbFixRetain { igDirEntryView *p; IgbFixRetain(igDirEntryView *o) : p(o) { if (p != 0) { p->_refCount = p->_refCount + 1; } } };
extern "C" int FUN_00142bb0(igObjectList *, IgbFixRetain *);
extern "C" igResult FUN_002e5110(igIGBFileView *self);
extern "C" igResult FUN_002e53f0(igIGBFile *file);
extern "C" igResult FUN_002e54e0(igIGBFileView *o);
extern "C" igResult FUN_002e5590(igIGBFileView *o);
extern "C" igResult FUN_002e56f0(igIGBFileView *arg1);
extern "C" igResult FUN_002e5950(igIGBFileView *arg1);
extern "C" igResult FUN_002e5990(igIGBFileView *o);
extern "C" igResult FUN_002e5ac0(void *arg1);
extern "C" int Gap__Core__igIGBFile__vfunc_28(igIGBFileView *arg0, const char *fileName);
extern "C" igResult FUN_002e5f70(igIGBFileView *arg1, const char *fileName);
/* The 48-byte .igb header: the table sizes and counts, the magic cookie, then the version word whose
 * top bits carry the file's flags. */
struct IgbFileHeader {
    int entryBufferSize; int entryCount; int metaObjectBufferSize; int metaObjectCount; int objectBufferSize; int objectCount;
    int memoryRefBufferSize; int memoryRefCount; int metaFieldBufferSize; int metaFieldCount; int magicCookie; int magicVersion;
};
extern "C" igResult igIGBFile_ReadHeader(igIGBFileView *arg1);
extern "C" igResult FUN_002e6330(igIGBFileView *arg1);
extern "C" igResult FUN_002e6f50(igIGBFileView *arg1);
extern "C" igResult FUN_002e7030(igIGBFileView *arg1);
struct IgbReadEntry : public igObject {
    void release() {
        _refCount = _refCount - 1;
        if ((_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(this);
        }
    }
};
typedef igSmartPointer<igDirEntryView> SectionObjectRef;
extern "C" SectionObjectRef igIGBFile_ReadObject(igIGBFile *file);
extern "C" igResult igIGBFile_ReadObjectSection(igIGBFileView *file);
extern "C" igResult FUN_002e7640(igIGBFileView *self);
extern "C" igResult FUN_002e78b0(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadObjectSectionOld(igIGBFileView *file);
extern "C" void Gap__Core__igIGBFile__vfunc_26(igIGBFileView *self, int at);
extern "C" igResult FUN_002e7ed0(igIGBFileView *arg1);
/* The registered meta-field descriptors FUN_002fc250 returns; each entry's getMeta is its meta object. */
struct IgbRegistryTable { char p0[8]; igObjectDispatchView **data; int count; };
extern "C" igResult FUN_002e7f20(igIGBFileView *self);
extern "C" void Gap__Core__igIGBFile__vfunc_13(igIGBFileView *arg0);
struct ReflectedTypeList { int vt; int rc; int count; int cap; int *data; int getCount() const { return count; } };
class RefObjectHolder { public: ReflectedRefObject *p; RefObjectHolder(void *o) : p((ReflectedRefObject *)o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~RefObjectHolder() { ReflectedRefObject *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
class TypeListHolder { public: ReflectedTypeList *p; TypeListHolder(ReflectedTypeList *v) { p = v; }
 ~TypeListHolder() { if (p != 0) { p->rc = p->rc - 1; if (((unsigned long long)((long long)(int)p->rc << 0x29) >> 0x29) == 0) { igObject_Destroy(p); } } } };
/* An .igb table section header: its byte size, a version word and the entry count. */
struct IgbSectionHeader { int size; int pad; int count; };
extern "C" igResult FUN_002e82a0(igIGBFileView *self);
struct DirEntryHolder {
    igDirEntryView *p;
    DirEntryHolder(igDirEntryView *o) : p(o) { if (p != 0) { p->_refCount = p->_refCount + 1; } }
    ~DirEntryHolder() {
        igDirEntryView *object = p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" igResult FUN_002e8670(igIGBFileView *arg1);
extern "C" igResult FUN_002e8880(igIGBFileView *arg1);
extern "C" void FUN_002e8a40(igIGBFileView *a);
extern "C" void Gap__Core__igIGBFile__vfunc_04(igIGBFileView *arg0);
extern "C" igResult FUN_002e8d40(igIGBFileView *arg1);
struct PooledStringHead { int chunk; int refs; };
extern "C" igResult FUN_002e8e50(igIGBFileView *self);
struct IgbNameList { int vt; int rc; int count; int cap; int *data; int getCount() const { return count; } };
struct NameHeader { int size; int count; };
extern "C" igResult FUN_002e91e0(igIGBFileView *self);
extern "C" igResult FUN_002e94b0(igIGBFileView *arg1);
extern "C" igResult FUN_002e9560(igIGBFileView *arg1);
/* ReadFile(path): the Alchemy .igb loader driver. Logs "readFile(%s)", notes the clock, then runs
 * the section readers in file order (header, then the version-dependent tables, then the object
 * sections). A reader that fails sends the loader to its error path FUN_002e9470. After the last
 * reader the load time is reported once through the assert/log hook; an old-format file that still
 * has external references is reported once through the same hook, which prints the file's name.
 * Each reader result is an unnamed temporary with its own stack word. */
extern "C" int igIGBFile_ReadFile(igIGBFileView *self, const char *path);
extern "C" void Gap__Core__igIGBFile__vfunc_30(int *arg0, igIGBFileView *arg1);
class ExternalFileHolder { public: igIGBFileView *p; ExternalFileHolder(igIGBFileView *o) : p(o) { if (p != 0) { p->_refCount = p->_refCount + 1; } }
 ~ExternalFileHolder() { igIGBFileView *object = p; if (object) { --object->_refCount; if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
extern "C" igResult Gap__Core__igIGBFile__vfunc_31(igIGBFileView *self);
extern "C" int Gap__Core__igIGBFile__vfunc_34(igIGBFileView *o);
extern "C" igResult igIGBFile_GetSectionBuffer(igIGBFileView *arg1, int arg2);
extern "C" void Gap__Core__igIGBFile__vfunc_33(int *arg0, igIGBFileView *arg1);
extern "C" void Gap__Core__igIntArrayMetaField__vfunc_52(igIntArrayMetaField *self, int passThrough, int perElement);
extern "C" int g_igIntMetaField_vtable[4];
extern "C" void *igIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" void *igIntMetaField_Init(igMetaField *self);
typedef struct PointerList {
    int header[2];
    int *data;
    int count;
} PointerList;
typedef struct FieldPointerList {
    int header[2];
    void **data;
    int count;
} FieldPointerList;
extern "C" int g_ObjectPointerList_vtable[4];
class AllocatorSlot216View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class AllocatorView { public: virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void d49();virtual void d50();virtual void d51();virtual void *Allocate(int); };
class AllocatorSlot264View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int vX(int); };
extern "C" void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self, int extra1);
extern "C" PointerList *ObjectPointerList_Init(PointerList *list);
extern "C" __internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source);
extern "C" void ObjectPointerList_Destruct(__internalNonRefCountedObjectList *self);
extern "C" void ObjectPointerList_EnsureIndex(PointerList *list, int index);
extern "C" void *ObjectPointerList_FindByStringField(FieldPointerList *list,igMetaField *selector,const char *name);
extern "C" void ObjectPointerList_ClearUnused(PointerList *list);
extern "C" void ObjectPointerList_Insert(PointerList *list,int index,int value);
extern "C" void ObjectPointerList_SetCount(PointerList *list, int count);
extern "C" int ObjectPointerList_EraseAt(PointerList *list,int index);
extern "C" int ObjectPointerList_Append(PointerList *list,int value);
extern "C" void ObjectPointerList_SetAt(PointerList *list, int index, int value);
typedef struct RefHeader {
    int vtable;
    unsigned refs;
} RefHeader;
extern "C" int g_InternalObjectList_vtable[4];
extern "C" void *InternalObjectList_Construct(PointerList *list, int extra1);
extern "C" void *InternalObjectList_Init(PointerList *list);
extern "C" void *InternalObjectList_CopyConstruct(PointerList *list, PointerList *source);
extern "C" void InternalObjectList_Destruct(PointerList *list);
extern "C" void InternalObjectList_InsertRetained(PointerList *list, int index, RefHeader *value);
extern "C" void InternalObjectList_SetCount(PointerList *list,int count);
extern "C" int MetaRefList_AppendRetained(PointerList *list, RefHeader *value);
extern "C" void InternalObjectList_SetAtRetained(PointerList *list, int index, RefHeader *value);
extern "C" void StringPool_DestroyChunks(StringPool *pool);
extern "C" int StringPool_Intern(StringPool *pool, const char *name);
extern "C" void * StringPool_Allocate(int arg0);
extern "C" void FUN_002eb150(igLocationTableView *table);
extern "C" int Gap__Core__igLocationTable__vfunc_23(igLocationTable *self);
extern "C" void Gap__Core__igLocationTable__vfunc_25(int *arg0, igLocationTableView *arg1, int arg2, int *arg3, char *arg4, int arg5, int *arg6, char *arg7, int arg8, int *arg9);
extern "C" int Gap__Core__igLocationTable__vfunc_26(igLocationTableView *o, int key);
extern "C" void Gap__Core__igLocationTable__vfunc_27(int *arg0, igLocationTableView *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0);
extern "C" void Gap__Core__igLocationTable__vfunc_28(igLocationTableView *o, int a1, char *a2, int a3, char *a4, int a5);
extern "C" unsigned int Gap__Core__igLocationTable__vfunc_30(igLocationTable *self, unsigned int key);
struct LocationHashWords { int vt; int rc; int count; int cap; int *data; };
class LocationHashTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slot(int); virtual void p29(); virtual void rehash(int);
  char q4[16]; LocationHashWords *table; };
extern "C" int Gap__Core__igLocationTable__vfunc_31(LocationHashTable *self, int key, int value);
/* The pointer difference is divided by 20 (the division is kept) and the capacity test is spelled
 * `arg1 <= cap`. */

extern "C" int DAT_004c2148;
extern "C" void Gap__Core__igLocationTable__vfunc_32(igLocationTableView *arg0, int arg1);
extern "C" void igLongArrayMetaField_SwapBytes(igLongArrayMetaField *arg0, int arg1, int arg2);
extern "C" int igLongArrayMetaField_GetSize(igLongArrayMetaField *self);
extern "C" int text_ld_n[4];
extern "C" int DAT_004f9bc0[4];
/* igMedia's own virtual functions past igObject's (vfunc_N at vtable byte offset 4 * N); the slot
 * symbols are unnamed (Gap::Core::igPsx2Media::vfunc_NN). ABI view only: never instantiated. */
class igMediaView : public igVirtualObject {
public:
    RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19);
    virtual void vfunc_22(); virtual void vfunc_23();
    virtual int vfunc_24(int handle);                                           /* +96: close */
    virtual void vfunc_25();
    virtual int vfunc_26(int handle);                                           /* +104 */
    virtual int vfunc_27(int handle, const void *buffer, int size);             /* +108: write */
    virtual int vfunc_28(int handle, void *buffer, int size);                   /* +112: read */
    virtual int vfunc_29(int handle, void *buffer, int size, int (*done)(int, int), int context); /* +116: read async */
    virtual int vfunc_30(int handle, int offset, int whence);                  /* +120: seek */
    virtual int vfunc_31(int handle);                                           /* +124: tell */
    virtual int vfunc_32(int path, int prefixLength);                           /* +128 */
};
extern "C" igMediaView *DAT_00586f28[4];
extern "C" igSmartPointer<igObjectList> g_fileDeviceList;
extern "C" igMediaView *FUN_002ebc40(int arg0);
/* igMediaFile: a file on an igMedia device, either read straight through the device (_isBinary)
 * or held whole in _fBuf. */
class igMediaFileView : public igFileView { public:
    unsigned char _isBinary;
    unsigned char _isOpen;
    unsigned char _write;
    unsigned char _read;
    int _bufSize;
    int _fileSize;
    int _bufPos;
    unsigned char *_fBuf;
    igMediaView *_media;
};
extern "C" void Gap__Core__igMediaFile__vfunc_24(igMediaFileView *arg0);
extern "C" char DAT_004f9c48[];
extern "C" char DAT_004f9c58[];
extern "C" char DAT_004f9c68[];
extern "C" char DAT_004f9c78[];
extern "C" char DAT_004f9c88[];
extern "C" int DAT_004f9c60[4];
extern "C" int DAT_004f9c70[4];
extern "C" int DAT_004f9c80[4];
extern "C" int DAT_004f9c90[4];
extern "C" void Gap__Core__igMediaFile__vfunc_26(igMediaFileView *self);
extern "C" void FUN_002ec570(igMediaFileView *arg0, int arg1);
extern "C" int Gap__Core__igMediaFile__vfunc_27(igMediaFileView *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igMediaFile__vfunc_29(igMediaFileView *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igMediaFile__vfunc_32(igMediaFileView *arg0);
extern "C" int Gap__Core__igMediaFile__vfunc_31(igMediaFileView *self, int fmt, ...);
extern "C" int Gap__Core__igMediaFile__vfunc_33(igMediaFileView *arg0);
extern "C" int Gap__Core__igMediaFile__vfunc_35(igMediaFileView *arg0, unsigned char arg1);
extern "C" char *Gap__Core__igMediaFile__vfunc_36(igMediaFileView *arg0, char *arg1, int arg2);
extern "C" int Gap__Core__igMediaFile__vfunc_37(igMediaFileView *arg0, int arg1);
extern "C" int Gap__Core__igMediaFile__vfunc_38(igMediaFileView *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igMediaFile__vfunc_39(igMediaFileView *p);
/* Unused vtable slots, declared only so the used ones land at their real offsets. */


class DumpFile {
public:
    PAD(0) PAD(1) PAD(2) PAD(3) PAD(4) PAD(5) PAD(6) PAD(7) PAD(8) PAD(9)
    PAD(10) PAD(11) PAD(12) PAD(13) PAD(14) PAD(15) PAD(16) PAD(17) PAD(18) PAD(19)
    PAD(20) PAD(21) PAD(22)
    virtual int Open(const char *name, const char *mode); /* +100 */
    virtual void Close();                                 /* +104 */
    PAD(27) PAD(28) PAD(29) PAD(30)
    virtual void Print(const char *fmt, ...);             /* +124 */
    int refs; /* +4 */
};
/* The statistics the system allocator reports (slot 23) and prints (slot 34, "System memory
 * statistics:"); the member names are the printed labels. */
struct SystemMemoryStatistics {
    int totalSystemMemorySize;
    int allocationSpan;
    int maximumSpan;
    int allocatedAndInUse;
    int allocatedAndAvailable;
    int freeFromTop;
    int codeStart;
    int codeSize;
    int dataStart;
    int dataSize;
    int initializedStart;
    int initializedSize;
    int uninitializedStart;
    int uninitializedSize;
    int stackStart;
    int stackSize;
    int fastStart;
    int fastSize;
    int virtualStart;
    int virtualSize;
    int heapTop;
};
/* The process's memory map and system allocator, built at start-up. Its base class's constructor and
 * destructor are compiled elsewhere in the library. Slot k sits at byte 8 + 4k; the page-map slots
 * (15-17, 25-27, 40-44) work on 4KB pages tracked two bits each in 64 tables of 64MB. */
class SystemAllocatorBase { public: SystemAllocatorBase(); virtual ~SystemAllocatorBase(); };
class SystemAllocator : public SystemAllocatorBase {
public:
    SystemAllocator();
    virtual ~SystemAllocator() {}
    virtual int vfunc_3();                      /* +12 */
    virtual void *Allocate(unsigned int size); /* +16 */
    virtual void d3();
    virtual void *AllocateAligned(unsigned int size, unsigned int alignment); /* +24 */
    virtual void *Reallocate(void *block, int size); /* +28 */
    virtual void d6();
    virtual void Free(void *block);            /* +36 */
    virtual void *AllocateSized(unsigned int size);                                      /* +40 */
    virtual void FreeSized(void *block, int size);                                       /* +44 */
    virtual void *ReallocateSized(void *block, unsigned int size, unsigned int old);     /* +48 */
    virtual void *AllocateAligned(unsigned int size);                                    /* +52 */
    virtual void FreeAligned(void *block, int size);                                     /* +56 */
    virtual void *ReallocateAligned(void *block, unsigned int size, unsigned int old);   /* +60 */
    virtual void d14();
    virtual int vfunc_17(int address, int size);
    virtual igResult vfunc_18(int address, ...); /* size: an int from the page code, a long long from the context dump */
    virtual int GetStackSize();
    virtual void d18();
    virtual int vfunc_21();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual void GetStatistics(SystemMemoryStatistics *stats);                           /* +100 */
    virtual void d24();
    virtual igResult vfunc_27(int state, unsigned int address, int size);                /* +108 */
    virtual int vfunc_28(unsigned int address, int size);                                /* +112 */
    virtual unsigned int vfunc_29(int size);                                             /* +116 */
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
    virtual void vfunc_36();                                                             /* +144 */
    virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual int vfunc_42(int delta);                                                     /* +168 */
    virtual igResult vfunc_43(int address, int size);                                    /* +172 */
    virtual void *vfunc_44(unsigned int size);                                           /* +176 */
    virtual void vfunc_45(void *block);                                                  /* +180 */
    virtual igResult vfunc_46(int address, int size, int set);                           /* +184 */
};
extern "C" SystemAllocator g_systemAllocator;
extern "C" char text_0x_0_x[];
extern "C" char text_0x_08x_2[];
extern "C" char text_02x[];
extern "C" char text_04x[];
extern "C" char text_06x[];
extern "C" char text_08x[];
extern "C" char text_010lx[];
extern "C" char text_012lx[];
extern "C" char text_014lx[];
extern "C" char text_016lx[];
/* The allocator the memory services use; FUN_0032f300 installs g_systemAllocator here when it is empty. */
extern "C" SystemAllocator *g_activeSystemAllocator[4];
extern "C" void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPoolView *pool);
extern "C" void *FUN_002ed1e0(int, unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned int alignment, igMemoryPoolView *pool);
extern "C" void Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool);
extern "C" igMemoryPoolView *Memory_FindBufferOwner(void *buffer);
extern "C" int FUN_002ed5a0(void *block, igMemoryPoolView *pool);
extern "C" int Gap__Core__igMemoryDictionary__vfunc_23(igMemoryDictionary *self);
extern "C" void Gap__Core__igMemoryDictionary__vfunc_24(igMemoryDictionary *self, int capacity);
/* One slot of igMemoryDictionary's open-addressed table: a key, and its value or -1 for a never-used
 * slot, -2 for a removed one. */
struct MemoryDictionaryEntry { int key; int value; };
/* igMemoryDictionary's entry list (an igUnsignedIntListNoClean); its count is in words, two per entry. */
struct MemoryDictionaryEntryList : public igObject { int _count; int _capacity; MemoryDictionaryEntry *_data; };
/* igMemoryDictionary (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
class igMemoryDictionaryView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vfunc_24(int); virtual int vfunc_25(); virtual int vfunc_26();
    virtual void vfunc_27();
    virtual void d26(); virtual void d27();
    virtual igResult vfunc_30(int key, int *value);
    virtual igResult vfunc_31(int key, int value);
    virtual igResult vfunc_32(int);
    virtual int vfunc_33(int key);
    virtual igResult vfunc_34(int capacity);
    int _capacity;
    int _count;
    MemoryDictionaryEntryList *_memoryEntries;
    int _cachedIndex;
};
extern "C" void Gap__Core__igMemoryDictionary__vfunc_25(igMemoryDictionaryView *self);
extern "C" void Gap__Core__igMemoryDictionary__vfunc_26(igMemoryDictionaryView *self);
extern "C" int Gap__Core__igMemoryDictionary__vfunc_28(igMemoryDictionary *self);
extern "C" int DAT_004c2150[4];
extern "C" void Gap__Core__igMemoryDictionary__vfunc_27(igMemoryDictionaryView *self);
extern "C" int Gap__Core__igMemoryDictionary__vfunc_29(igMemoryDictionary *self);
extern "C" void Gap__Core__igMemoryDictionary__vfunc_30(igResult *result, igMemoryDictionaryView *self, int key, int *value);
extern "C" igResult Gap__Core__igMemoryDictionary__vfunc_31(igMemoryDictionaryView *self, int key, int value);
extern "C" igResult Gap__Core__igMemoryDictionary__vfunc_32(igMemoryDictionaryView *self, int key);
extern "C" unsigned int Gap__Core__igMemoryDictionary__vfunc_33(igMemoryDictionary *self, unsigned int key);
extern "C" char DAT_004c2158[];
extern "C" int Gap__Core__igMemoryDictionary__vfunc_34(igResult *result, igMemoryDictionaryView *self, int capacity);
extern "C" void FUN_002eed00(igMemoryDirEntry *arg0, igObjectDispatchView *arg1);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_31(igMemoryDirEntry *self, igIGBFile *file);
struct Cod {
    V16(a) V16(b) V16(c)
    virtual void v48(int, int, igIGBFile *, unsigned char);
    virtual void v49();
    virtual void v50(int, int);
};
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_41(igMemoryDirEntry *arg0, igIGBFile *arg1);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_39(igMemoryDirEntry *self, igIGBFile *file);
struct MetaInfo { char pad0[12]; int index; };
class DirEntryView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual MetaInfo *getMeta();
};
struct EntryList : public igObjectList {
    void set(int index, igObject *object) {
        if (object != 0) object->_refCount = object->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igObject **)_data)[index] = object;
        }
    }
};
struct DirFile { char pad0[92]; EntryList *sharedEntries; char pad96[184]; int pool; };
extern "C" igMemoryDirEntry *Gap__Core__igMemoryDirEntry__vfunc_26(igMemoryDirEntry *self, DirFile *file);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_35(igMemoryDirEntry *arg0, igIGBFile *arg1);
class igMemoryDirEntryView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void vfunc_32();
};
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_33(igMemoryDirEntryView *self);
struct MemoryDirReader;
class MemoryDirField { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void fix(int, int, MemoryDirReader *, unsigned char); virtual void swapArray(int, int);
 char q4[16]; unsigned short elementSize; char q22[38]; unsigned char swapFlag; };
struct MemoryDirList { char p0[16]; MemoryDirField **data; };
struct MemoryDirReader { char p0[168]; unsigned char swapped; char p169[19]; MemoryDirList *fields; };
struct MemoryDirEntryView { char p0[24]; int base; int size; char p32[4]; MemoryDirField *field; int fieldIndex; char p44[8]; unsigned char swapFlag; };
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_34(MemoryDirEntryView *self, MemoryDirReader *r);
extern "C" void Gap__Core__igMemoryDirEntry__vfunc_29(igMemoryDirEntry *self, int memoryPoolHandle);
extern "C" int Gap__Core__igMemoryDirEntry__vfunc_30(igMemoryDirEntry *self);
extern "C" int *DAT_00586f48[4];
struct MemoryFileHead { char p[12]; int f12; char p16[4]; unsigned int f20; int f24; char p28[16]; unsigned char open; char p2[3]; int data; int size; int pos; };
extern "C" void Gap__Core__igMemoryFile__vfunc_23(int *arg0, struct MemoryFileHead *arg1, unsigned int arg2);
extern "C" igFileView *Gap__Core__igMemoryFile__vfunc_25(igFileView *arg0, const char *fileName, int arg2);
class igMemoryFileView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22();
};
extern "C" void Gap__Core__igMemoryFile__vfunc_26(igMemoryFileView *self);
struct MemoryFileBody { char p[44]; unsigned char open; char p2[3]; char *data; int size; int pos; };
extern "C" int Gap__Core__igMemoryFile__vfunc_27(struct MemoryFileBody *arg0, void *arg1, int arg2, int arg3);
extern "C" char Gap__Core__igMemoryFile__vfunc_33(igMemoryFile *arg0);
extern "C" int Gap__Core__igMemoryFile__vfunc_39(igMemoryFile *self);
extern "C" int DAT_0052f620[4];
extern "C" int g_beModelCtrlInfo_metaObject[4];
extern "C" unsigned char GPR_00554994;
extern "C" igResult FUN_002f0180(int arg1, int *arg2);
/* The struct result is returned through the hidden pointer (a0 is the caller's return slot, this
 * is in a1), so the function returns the struct by value. */
extern "C" char text_memoryDictionarySize[];
extern "C" igMemoryDictionaryView *DAT_00586f68[4];
extern "C" igResult FUN_002f0220(int arg1, igMemoryPoolView *arg2);
extern "C" igResult FUN_002f0320(int arg1, igMemoryPoolView *pool);
extern "C" char DAT_00580000[];
/* Allocator registry index lookup and encoded-index publication. An allocator is identified in
 * saved data by "registry index << 1 | which-registry": the primary list gives an even code, the
 * secondary list an odd one. The class below is an observed ABI view that projects the original
 * virtual slots by number (a0.. are unnamed padding); it must not be instantiated. */
class AllocatorLookupView {public:
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
virtual void a22();
virtual void a23();
virtual void a24();
virtual void a25();
virtual void a26();
virtual int Kind();
virtual void a120();virtual void a124();virtual void a128();virtual int Available();
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual igResult vfunc_41(long long maxSize);
virtual void b8();
virtual void b9();
virtual void b10();
virtual void b11();
virtual void b12();
virtual void b13();
virtual void b14();
virtual void b15();
virtual void b16();
virtual void b17();
virtual void b18();
virtual void b19();
virtual void b20();
virtual void b21();
virtual void b22();
virtual void b23();
virtual void b24();
virtual void b25();
virtual void b26();
virtual void b27();
virtual void b28();
virtual void b29();
virtual void b30();
virtual void b31();
virtual void b32();
virtual void b33();
virtual void b34();
virtual void b35();
virtual void b36();
virtual void b37();
virtual void b38();
virtual void b39();
virtual void b40();
virtual void b41();
virtual void b42();
virtual void b43();
virtual void b44();
virtual void b45();
virtual void b46();
virtual void b47();
virtual void b48();
virtual void b49();
virtual void b50();
virtual int Owns(void *);
virtual void a84();
virtual void a85();
virtual void a86();
virtual void a87();
virtual void a88();
virtual void a89();
virtual void a90();
virtual void a91();
virtual void a92();
virtual void a93();
virtual void vfunc_96(int list);
};
/* Growable pointer list of allocators: data, signed count, capacity (same layout as igMemoryPoolInfoList). */
struct AllocatorRegistry {AllocatorLookupView **data;int count;int capacity;};
extern "C" AllocatorRegistry *g_primaryAllocatorList[4];
extern "C" AllocatorRegistry *g_secondaryAllocatorList[4];
extern "C" int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *list,AllocatorLookupView *allocator);
extern "C" int igAllocator_EncodeIndex(AllocatorLookupView *allocator);
extern "C" char DAT_004f9d60[];
extern "C" void FUN_002f08d0(igMemoryPool *arg0, char *arg1);
extern "C" char DAT_004f9fe0[];
extern "C" char * DAT_00586f70[4];
extern "C" int DAT_00586f78[4];
extern "C" int DAT_00586f90[4];
extern "C" int DAT_00586f98[4];
extern "C" int DAT_00586fb0[4];
extern "C" int DAT_00586fb8[4];
extern "C" void *FUN_002f0c80(igMemoryPoolView *self, unsigned int size);
extern "C" void FUN_002f0d70(int dummy0, igObject *arg1);
extern "C" int DAT_004c2160[4];
extern "C" int FUN_002f1410(igMemoryPoolView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
extern "C" void FUN_002f19f0(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10);
extern "C" void FUN_002f1b70(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18);
extern "C" void Memory_InitializeAllocatorRegistries(igObject *rootAllocator);
/* The root allocator's vtable: 96 unnamed padding slots, then the call at offset 392. */
class RootAllocatorVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual int afterRegistriesCleared(); };
extern "C" void FUN_002f2280(igMemoryPool *arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_002f22f0(igMemoryPool *arg0);
extern "C" void FUN_002f2340(igMemoryPool *arg0, int arg1, int arg2, int arg3);
extern "C" long long DAT_00586f80[4];
extern "C" long long DAT_00586f88[4];
extern "C" long long DAT_00586fa0[4];
extern "C" long long DAT_00586fa8[4];
extern "C" long long DAT_00586fc0[4];
extern "C" long long DAT_00586fc8[4];
struct PoolDescRecord { int vt; int rc; char *name; char q12[8]; char *alias; char *s24; int a28; int a32; int a36; char *s40; char *s44; char *s48; char *s52; char *s56; char *s60; char *s64; char *s68; char *s72; char *s76; int a80; };
struct PoolDescSlot { int pool; char name[128]; PoolDescRecord *record; char q136[8]; };
struct ContextStackEntry;
extern "C" void *DAT_00587000[4];
extern "C" char *g_memoryContextNames[46];
extern "C" char text_InhibitEventTracker[];
extern "C" char text_UseEventTracker[];
struct ContextRecord {
    void *allocator;       /* retained by the slot setter */
    char name[128];        /* 127 characters copied in plus an explicit terminator */
    void *descriptor;
    unsigned storageFlags, flags;
};
/* igMemoryPoolContextInfo (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
struct IniSectionsView;
class igMemoryPoolContextInfoView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual igResult vfunc_25(IniSectionsView *ini, char *section);
    virtual igResult vfunc_26(IniSectionsView *ini, int index);
    int _name;
    int _directory;
    unsigned char _resolveState;
    int _memoryPoolInfos;
};
/* The memory context: 46 records, each an allocator slot with its name and descriptor. Its vtable
 * is g_igMemoryPoolContextInfo_vtable; the slots past 20 are its own. */
class MemoryContext : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igMemoryPoolView *getAllocatorBySelector(int index);
    virtual int getAllocatorByName(int name);
    virtual void vfunc_25(int index, igObject *allocator);
    virtual int vfunc_26(int);
    virtual int vfunc_27(void *pool);
    virtual void d26();
    virtual int vfunc_29(int);
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual igResult vfunc_35(int, int);
    virtual void d34(); virtual void d35();
    virtual void setFlags(unsigned flags);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void vfunc_42();
    virtual void vfunc_43();
    virtual int vfunc_44();
    virtual void InitializeRecordNames();
    virtual void d44();
    virtual int vfunc_47();
    virtual void d46();
    virtual int vfunc_49();
    virtual void d48();
    virtual igResult BuildAllocator(int index, int flag);
    virtual igResult BuildAndAttachEventTracker(int index);
    virtual void RemoveAllocator(int index);
    virtual void d52();
    virtual int vfunc_55();
    virtual void vfunc_56();
    virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60();
    virtual void d61(); virtual void d62();
    virtual void vfunc_65(int, int);
    virtual void vfunc_66(int);
    virtual void Destruct(int flags);
    int usedRecords;
    unsigned flags;
    igMemoryPoolContextInfoView *contextInfo;
    ContextRecord records[46];
};
struct ContextView : igObject {
    int usedRecords;       /* +8: highest populated slot + 1 (30 right after construction) */
    unsigned flags;        /* +12 */
    igObject *parent;      /* +16 */
    ContextRecord records[46];
};
extern "C" char g_igMemoryPoolContextInfo_vtable[];
extern "C" ContextView *igMemoryPoolContextInfo_Construct(ContextView *self);
extern "C" void *igMemoryPoolContextInfo_Destruct(ContextView *self, long long deleteFlags);
extern "C" void FUN_002f4070(ContextView *self);
extern "C" void FUN_002f7f20(ContextView *self, int arg1);
extern "C" int DAT_00587010[4];
extern "C" int FUN_002f2730(MemoryContext *arg0, int arg1);
extern "C" void *FUN_002f2830(MemoryContext *self, const char *name);
extern "C" void FUN_002f28d0(ContextView *self, int index, igObject *value);
extern "C" int *FUN_002f29d0(MemoryContext *arg0, void *pool);
extern "C" int text_kIGMemoryPoolHandle[4];
extern "C" int text_kIGMemoryPool[4];
extern "C" igResult FUN_002f2d20(MemoryContext *self, int config, int section);
extern "C" igResult FUN_002f2e30(MemoryContext *self, int config, int index);
struct igRefHead { int vt; int rc; };
class SlotReadTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual igResult readOne(int, igRefHead *);
};
extern "C" igResult FUN_002f2f40(SlotReadTable *self, int file);
struct DirSlotObject { int vt; int rc; };
struct DirSourceRecord { char p0[20]; int id; };
class DirSlotTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual int slotFor(int); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual igResult fillSlot(int, DirSourceRecord *, int);
  char q4[12]; DirSlotObject *slots; };
extern "C" igResult FUN_002f3060(DirSlotTable *self, int file, int arg);
typedef void StringToken;
/* a token points at the interned text; its header precedes it */
/* The descriptor's attached object: only the four virtuals this function calls are named; the others
 * are placeholders that keep the vtable byte offsets (8 + 4 * slot) right. */
class SizedObject {
public:
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26();
    virtual unsigned int hasLimitOrSize();/* byte 116 */
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33();
    virtual long long limit();/* byte 144 */
    virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41();
    virtual unsigned int count();/* byte 176 */
    virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50();
    virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58();
    virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66();
    virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74();
    virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82();
    virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90();
    virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void p95(); virtual void p96(); virtual void p97();
    virtual unsigned long long total();/* byte 400 */
};
/* Pool descriptor defaults (entry +0x84): interned-string sources and integer limits. */
struct PoolDefaults {
    char pad0[0x18];
    const char *text0;       /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    const char *text1;       /* +0x28 */
    const char *text2;
    const char *text3;
    const char *text4;
    const char *text5;
    const char *text6;
    const char *text7;
    const char *text8;
    const char *text9;
    const char *text10;      /* +0x4c */
    int field50;             /* +0x50 */
};
struct PoolEntry {
    SizedObject *object;     /* +0x00 */
    char name[0x80];         /* +0x04 */
    PoolDefaults *defaults;  /* +0x84 */
    char pad88[8];
};
struct PoolTable {
    char pad0[0x14];
    PoolEntry entries[46];   /* +0x14, 0x90 bytes each */
};
/* The pool handle object being filled; string members hold interned tokens. */
struct PoolHandle {
    char pad0[0x14];
    StringToken *handleName; /* +0x14 */
    StringToken *token0;     /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    StringToken *token1;     /* +0x28 */
    StringToken *token2;
    StringToken *token3;
    StringToken *token4;
    StringToken *token5;
    StringToken *token6;
    StringToken *token7;
    StringToken *token8;
    StringToken *token9;
    StringToken *token10;    /* +0x4c */
    int field50;             /* +0x50 */
};
extern "C" char text_kIGMemoryPoolHandle_s[];
extern "C" void FUN_002f31b0(int *result, PoolTable *table, int index, PoolHandle *handle);
struct PoolDescString { int chunk; int refs; };
class PoolDescManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual igResult build(int, int); };
class PoolDescManager : public PoolDescManagerBase { public: char q4[4]; int nextSlot; char q12[4]; int table; };
extern "C" igResult FUN_002f3910(PoolDescManager *self, int index, PoolDescRecord *desc, int build);
extern "C" void FUN_002f4110(MemoryContext *arg0);
extern "C" char *DAT_00586de8;
extern "C" int DAT_00586fd8[4];
extern "C" int DAT_00586fe0[4];
extern "C" int DAT_00586fe8[4];
extern "C" int DAT_00586ff0[4];
class PoolObjectBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90(); virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void prepare(); };
class PoolObject : public PoolObjectBase { public: int rc; };
struct PoolSlotTable { char p0[20]; PoolObject *first; };
extern "C" void FUN_002f43a0(PoolSlotTable *self);
extern "C" int D_00587010[4];
/* The 46 records follow the 20-byte object header.  Retail steps one pointer
 * by whole records from the context base, so that pointer sits 20 bytes before
 * the record it works on; this view reproduces it (name is 24 bytes in). */
/* The records seen in 144-byte strides from the object base: entry i's allocator word is
 * records[i].allocator (base + 20 + 144 * i). Retail indexes the context this way when it walks the
 * allocators. */
struct ContextRecordStride { char head[20]; void *allocator; char rest[120]; };
typedef struct ContextPrefixedRecord {
    char header[20];
    ContextRecord record;
} ContextPrefixedRecord;
extern "C" void igMemoryPoolContextInfo_InitializeRecordNames(igMemoryPoolContextInfo *self);
extern "C" char text_bootstrapPoolPreSize[];
extern "C" char text_updatePoolStatistics[];
extern "C" char text_useAliasMemoryPoolRelease[];
extern "C" char text_arenaMemoryPoolOptionFlagsReleas[];
extern "C" char text_arenaMemoryPoolMessageLevelRelea[];
extern "C" char text_arenaMemoryPoolHeapIntegrityChec[];
extern "C" char text_inhibitArenaCountMessage[];
extern "C" char text_nonTrackedPoolPreSize[];
class PoolConfigObject { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void finish(); virtual void p29(); virtual void p30(); virtual int inUse(); virtual igResult lock(int); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual igResult setName(int); int rc; char q8[184]; int options; };
struct PoolConfigContext { char p0[48]; PoolConfigObject *main; PoolConfigObject *second; int config; char p60[28]; PoolConfigObject *a88; char p92[4]; PoolConfigObject *a96; };
class PoolConfigManagerBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual PoolConfigObject *poolFor(int); virtual void p22(); virtual void setPool(int, PoolConfigObject *); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual igResult setDefault(int, int); virtual void p34(); virtual void p35(); virtual void setFlags(int); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual igResult readConfig(int, int); virtual void p47(); virtual igResult apply(); virtual igResult build(int, int); virtual void p50(); virtual void p51(); virtual void finish(); };
class PoolConfigManager : public PoolConfigManagerBase { public: char q4[8]; int flags; int defaultSize; PoolConfigObject *first; char q24[140]; PoolConfigObject *third; char q168[284]; PoolConfigObject *fallback; };
extern "C" igResult FUN_002f4a60(PoolConfigManager *self);
extern "C" void FUN_002f50e0(MemoryContext *arg0);
extern "C" char text_defaultPoolPreSize[];
extern "C" char text_systemPoolPreSize[];
extern "C" char text_scratchPoolSize[];
extern "C" char text_scratchPadPoolSize[];
extern "C" char text_Fixed[];
extern "C" char text_HighSpeed[];
extern "C" char text_OnDemand[];
extern "C" char text_driverPoolSize[];
class PoolDescTable { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual igResult load(int, char *); int rc; };
class PoolDescSetupBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual char *recordName(int); };
class PoolDescSetup : public PoolDescSetupBase { public: char q4[12]; PoolDescTable *table; PoolDescSlot slots[46]; };
struct PoolDescContext { char p0[56]; int config; };
extern "C" void FUN_002f5230(int *out, PoolDescSetup *self, int config, char *name);
extern "C" char text_Level[];
extern "C" char text_Frame[];
extern "C" char text_LongTerm[];
extern "C" char text_Create[];
extern "C" char text_Reset[];
extern "C" char text_Dynamic[];
extern "C" char ONDEMAND[];
extern "C" char text_ondemand[];
extern "C" char text_SystemMemory[];
extern "C" char text_Low[];
extern "C" char text_High[];
extern "C" char text_Virtual[];
extern "C" char text_Raw[];
extern "C" char text_Custom[];
extern "C" void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag);
extern "C" void MemoryContext_BuildAndAttachEventTracker(igResult *out, MemoryContext *self, int idx);
typedef igObject Obj6;
struct RefCount { union { int w; struct { unsigned cnt : 23; unsigned f : 9; } b; } u; };
struct StringHeader { int chunk; int refs; };
class EventTracker { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void start();
    RefCount rc; char q8[36]; int users; };
class PoolLoader { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual igResult load(char *); virtual igResult finish(); virtual void p24(); virtual void p25(); virtual igResult attach(void *, int); virtual void p27(); virtual void p28(); virtual void optionA(); virtual void optionB();
    RefCount rc; };
struct LoadedObject { int vt; RefCount rc; };
class TrackedPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual int hasTracker(); virtual void setTracker(EventTracker *); };
class PoolSetupBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void setFlags(int); };
class PoolSetup : public PoolSetupBase { public: char q4[8]; int flags; char q16[4]; PoolDescSlot slots[46]; };
struct MemoryContextState {
    char p0[48]; TrackedPool *main; TrackedPool *second; int config; char p60[20];
    LoadedObject *loaded; EventTracker *tracker; char p88[28];
    unsigned char trackEvents; unsigned char flag117; unsigned char flag118; unsigned char flag119; unsigned char flag120; char p121[3];
    int value124; int value128; int value132; int value136; int value140;
    TrackedPool *getSecond() { return second; }
    int getConfig() { return config; }
};
extern "C" int DAT_004c1eb0;
extern "C" char text_useGlobalEventTracker[];
extern "C" char text_useSeparateEventTrackers[];
extern "C" char text_showLeaksOnExit[];
extern "C" char text_showMemoryStatisticsOnExit[];
extern "C" char text_showObjectStatisticsOnExit[];
extern "C" char text_eventTrackerInitialCapacity[];
extern "C" char text_eventTrackerEventTypeFilter[];
extern "C" char text_eventTrackerMarkerTypeFilter[];
extern "C" char text_eventTrackerMaxCallStackDepth[];
extern "C" char text_eventTrackerNotificationTypeFilt[];
extern "C" char text_eventTrackerNotificationCodeFilt[];
extern "C" char text_memoryEventFormat[];
extern "C" char text_markerEventFormat[];
extern "C" char text_notificationEventFormat[];
extern "C" char text_eventTrackerScopeFlags[];
extern "C" char text_saveEventTrackerOnExit[];
extern "C" char text_eventTrackerFileName[];
extern "C" char text_systemPoolEventTrackerFileName[];
extern "C" char text_symbolsFileName[];
extern "C" char text_showSectionHeaders[];
extern "C" char text_showSymbols[];
extern "C" void FUN_002f69b0(PoolSetup *self);
extern "C" char DAT_004fa930[];
extern "C" int DAT_004fa988[4];
extern "C" char DAT_004fa990[];
extern "C" char DAT_004fa9b0[];
extern "C" char DAT_004fa9d0[];
enum LeakKind { LeakKindFirst = 0, LeakKindCount = 32 };
class LeakReportTracker { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void summary(int, int, int *, int *, int *, int *, int *, int *, int *, int *, int *, int, int, int *, int, int); virtual void describe(int, int, int, int *, int *, int *, int *);
  int rc; char q8[48]; int names; };
struct LeakReportContext { char p0[84]; LeakReportTracker *tracker; char p88[30]; unsigned char dumpLeaks; unsigned char dumpSummary; unsigned char dumpNames; };
class LeakReportOwner { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void flush(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual int count(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void dump(); };
class LeakReportPool { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66(); virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74(); virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82(); virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual LeakReportOwner *owner(); virtual void release(int); };
struct LeakReportSlot { char p0[20]; LeakReportPool *pool; char p24[120]; };
extern "C" void FUN_002f7420(LeakReportSlot *self);
extern "C" char text_s_igm[];
extern "C" void FUN_002f78b0(MemoryContext *arg0);
class SlotOwnerObject { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual void vDrop();
};
class SlotPool { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48();
 virtual igResult vRelease(int, int);
 virtual void e51();
 virtual void vFree(int);
};
struct PoolSlotEntry { SlotOwnerObject *owner; char pad[136]; unsigned int flags; };
extern "C" igResult FUN_002f7a70(SlotPool *self, unsigned int kind, int free);
extern "C" void FUN_002f7bc0(ContextRecordStride *arg0, int arg1);
extern "C" void FUN_002f7cc0(ContextView *self, int arg1, int *out, int n);
extern "C" void FUN_002f7e00(ContextView *self, int *paths, int n);
extern "C" void FUN_002f8020(ContextRecordStride *slots, int arg1, int *out, int n);
extern "C" void FUN_002f8160(ContextRecordStride *arg0, int *arg1, int arg2);
struct Res {
    virtual void r0();
    virtual void r1();
    virtual void r2();
    virtual void r3();
    virtual void r4();
    virtual void r5();
    virtual void r6();
    virtual void r7();
    virtual void r8();
    virtual void r9();
    virtual void r10();
    virtual void r11();
    virtual void r12();
    virtual void r13();
    virtual void r14();
    virtual void r15();
    virtual void r16();
    virtual void r17();
    virtual void r18();
    virtual void r19();
    virtual void r20();
    virtual void r21();
    virtual void r22();
    virtual void r23();
    virtual void v24(int *, int);
    int p[3];
    int flags;
    int p2;
    int mask;
};
extern "C" void FUN_002f8280(ContextRecordStride *arg0, int arg1, int arg2, int arg3);
extern "C" char text_Pool_statistics[];
extern "C" char DAT_004fab20[];
extern "C" char DAT_004fab30[];
extern "C" void FUN_002f8420(MemoryContext *arg0, char *arg1, igMemoryPoolView *arg2);
extern "C" char DAT_004f95c8[];
extern "C" int DAT_004fab70[4];
extern "C" int text_Combined_pool_statistics[4];
extern "C" void FUN_002f8580(ContextRecordStride *arg0, int *arg1);
extern "C" int DAT_00586ffc[4];
extern "C" igResult FUN_002f86e0(void *arg1);
struct ContextStackEntry {
    int pad;
    union {
        int w;
        struct {
            unsigned cnt : 23;
            unsigned f : 9;
        } b;
    } u;
};
extern "C" struct ContextStackEntry *FUN_002f8760(void);
extern "C" void FUN_002f8af0(igMemoryPoolContextInfo *info, int arg1);
extern "C" int emptyString[4];
extern "C" igMemoryPoolInfo *FUN_002f8be0(igMemoryPoolContextInfo *arg0, int arg1);
extern "C" char text_Handle[];
extern "C" igMemoryPoolInfo *FUN_002f8ca0(igMemoryPoolContextInfo *arg0, char *arg1);
struct IniSectionsView;
extern "C" char *DAT_004c2228[4];
extern "C" igResult Gap__Core__igMemoryPoolContextInfo__vfunc_25(igMemoryPoolContextInfoView *self, IniSectionsView *ini, char *section);
extern "C" int DAT_004fabc0[4];
extern "C" void Gap__Core__igMemoryPoolContextInfo__vfunc_27(igInfo *arg0);
extern "C" int Gap__Core__igMemoryPoolInfo__vfunc_25(int *arg0, igMemoryPoolInfo *self, int arg2, char *arg3);
extern "C" char *DAT_004c2230;
extern "C" char *DAT_004c2238;
extern "C" char *DAT_004c2240;
extern "C" char *DAT_004c2248;
extern "C" char *DAT_004c2250;
extern "C" char *DAT_004c2258;
extern "C" char *DAT_004c2260;
extern "C" char *DAT_004c2268;
extern "C" char *DAT_004c2270;
extern "C" char *DAT_004c2278;
extern "C" char *DAT_004c2280;
extern "C" char *DAT_004c2288;
extern "C" char *DAT_004c2290;
extern "C" char *DAT_004c2298;
extern "C" char *DAT_004c22a0;
extern "C" char *DAT_004c22a8;
extern "C" char *DAT_004c22b0;
extern "C" void Gap__Core__igMemoryPoolInfo__vfunc_18(igMemoryPoolInfo *arg0);
extern "C" int DAT_004facc0[4];
extern "C" int DAT_004face0[4];
extern "C" int DAT_004fad00[4];
extern "C" int DAT_004fad20[4];
extern "C" int DAT_004fad40[4];
extern "C" int DAT_004fad60[4];
extern "C" int DAT_004fad90[4];
extern "C" int DAT_004fadb0[4];
extern "C" int DAT_004fadd0[4];
extern "C" int DAT_004fadf0[4];
extern "C" int DAT_004fae10[4];
extern "C" int DAT_004fae30[4];
extern "C" int DAT_004fae50[4];
extern "C" int DAT_004fae70[4];
extern "C" int DAT_004fae90[4];
extern "C" int DAT_004faeb0[4];
extern "C" int DAT_004faed0[4];
/* The growable pointer list shared by the allocator registries (igMemoryPoolInfoList): data,
 * signed count, capacity. Initial capacity 64 entries, growing four at a time. The allocator used
 * for the storage is the one the object system keeps at +48 (g_objectSystem). The classes are
 * observed ABI projections of the allocator's virtual slots (a0.. are padding). */
struct RegistryList {void **data;int count,capacity;};
class RegistryAllocatorView {public:
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
virtual void a22();
virtual void a23();
virtual void a24();
virtual void a25();
virtual void a26();
virtual void a27();
virtual void a28();
virtual void a29();
virtual void a30();
virtual void a31();
virtual void a32();
virtual void a33();
virtual void a34();
virtual void a35();
virtual void a36();
virtual void a37();
virtual void a38();
virtual void a39();
virtual void a40();
virtual void a41();
virtual void a42();
virtual void a43();
virtual void a44();
virtual void a45();
virtual void a46();
virtual void a47();
virtual void a48();
virtual void a49();
virtual void a50();
virtual void a51();
virtual void *Allocate(unsigned);
virtual void a220();virtual void a224();virtual void a228();
virtual void *Reallocate(void *,unsigned);
virtual void b0();
virtual void b1();
virtual void b2();
virtual void b3();
virtual void b4();
virtual void b5();
virtual void b6();
virtual void Free(void *);};
/* Object system as seen from here: only its allocator reference (+48) is used. */
struct BootstrapSystem {char prefix[48];RegistryAllocatorView *allocator;};
extern "C" RegistryList *igMemoryPoolInfoList_Init(RegistryList *list);
extern "C" RegistryList *igMemoryPoolInfoList_Release(RegistryList *list,int deleteFlag);
extern "C" void igMemoryPoolInfoList_Append(RegistryList *list,void *entry);
extern "C" void Gap__Core__igMemoryRefArrayMetaField__vfunc_52(igMemoryRefArrayMetaField *self, int buffer, int count);
extern "C" int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *arg0);
extern "C" void igMemoryRefArrayMetaField_ReleaseElements(igMemoryRefArrayMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" void igMemoryRefMetaField_ConstructValue(igMemoryRefMetaField *self, int object);
extern "C" void igMemoryRefMetaField_DestructValue(igMemoryRefMetaField *field,void *object, int extra2);
extern "C" void igMemoryRefMetaField_SetToDefault(igMemoryRefMetaField *field,void *object, int extra2);
extern "C" void igMemoryRefMetaField_AddElementRefs(igMemoryRefMetaField *field,void *object);
extern "C" void igMemoryRefMetaField_ReleaseElementRefs(igMemoryRefMetaField *field,void *object, int extra2);
extern "C" void igMemoryRefMetaField_DeepCopy(igMemoryRefMetaField *m, int arg1, int arg2);
extern "C" void igMemoryRefMetaField_ShallowCopy(igMemoryRefMetaField *field,void *dest,void *source);
extern "C" char DAT_004faef0[];
extern "C" void igMemoryRefMetaField_Print(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" void igMemoryRefMetaField_ReleaseElements(igMemoryRefMetaField *arg0, int arg1, int arg2, int arg3);
/* Allocates the backing array of a memory-reference field. The element descriptor (_memType)
 * supplies the element size and alignment through its virtual methods; the allocator is asked for
 * count * size bytes at that alignment and the pointer is published into the owning object at the
 * field's _offset. AlignedAllocatorView projects only the allocator slot this routine calls;
 * do not instantiate it. */

class AlignedAllocatorView {public:
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
virtual void a22();
virtual void a23();
virtual void a24();
virtual void a25();
virtual void a26();
virtual void a27();
virtual void a28();
virtual void a29();
virtual void a30();
virtual void a31();
virtual void a32();
virtual void a33();
virtual void a34();
virtual void a35();
virtual void a36();
virtual void a37();
virtual void a38();
virtual void a39();
virtual void a40();
virtual void a41();
virtual void a42();
virtual void a43();
virtual void a44();
virtual void a45();
virtual void a46();
virtual void a47();
virtual void a48();
virtual void a49();
virtual void a50();
virtual void a51();
virtual void a52();
virtual void *Allocate(int,int);};
extern "C" void igMetaField_AllocateArray(int *outStatus,igMemoryRefMetaField *field,void *object,int count,AlignedAllocatorView *allocator);
typedef struct AlignmentName { char pad[8]; char *text; } AlignmentName;
typedef struct AlignmentNameList { char pad[4]; int _refCount; int count; int cap; } AlignmentNameList;
typedef struct AlignmentFieldView { char pad[68]; int alignmentType; } AlignmentFieldView;
extern "C" void igMemoryRefMetaField_SetAlignmentType(AlignmentFieldView *self, char *name);
extern "C" int igMemoryRefMetaField_Write(igMemoryRefMetaField *f, int off, int a2);
extern "C" int Gap__Core__igMemoryRefMetaField__vfunc_45(igMemoryRefMetaField *arg0, int arg1, int arg2);
extern "C" int igMemoryRefMetaField_IsAlikeDeep(igMemoryRefMetaField *arg0, int arg1, int arg2);
extern "C" int igMemoryRefMetaField_ReadRawFieldMem(igMemoryRefMetaField *arg0, int a1, int *arg2, void *arg3, int arg4);
extern "C" int igMemoryRefMetaField_IsAlikeShallow(igMemoryRefMetaField *arg0, int arg1, int arg2);
extern "C" void igMemoryRefMetaField_SetPoolName(igMemoryRefMetaField *arg0, int arg1);
extern "C" int g_igMemoryRefMetaField_vtable[4];
extern "C" igMemoryRefMetaField *igMemoryRefMetaField_Construct(igMemoryRefMetaField *self, int extra1);
extern "C" igMemoryRefMetaField *igMemoryRefMetaField_Init(igMemoryRefMetaField *self);
extern "C" int g_igRefMetaField_vtable[4];
extern "C" igMemoryRefMetaField *igMemoryRefMetaField_CopyConstruct(igMemoryRefMetaField *self, igMemoryRefMetaField *source);
extern "C" igRefMetaField *igRefMetaField_CopyConstruct(igRefMetaField *self, igRefMetaField *source);
typedef struct NameList {
    char pad[8];
    int count;
    int capacity;
    int *data;
} NameList;
extern "C" int igMetaEnum_GetValueByName(int *status, igMetaEnum *meta, const char *name, int *value);
/* The parameter is const so the list pointer is reloaded per iteration, the loop is tested at the
 * bottom via goto, and the locals are declared in the order a4, n, i. */
extern "C" void igMetaEnum_GetNameByValue(int *arg0, const igMetaEnum *arg1, int arg2);
extern "C" int igMetaEnum_GetNameCount(igMetaEnum *self);
typedef struct MetaEnumNameList { char pad[4]; int _refCount; int count; int capacity; char **data; } MetaEnumNameList;
typedef struct MetaEnumValueList { char pad[4]; int _refCount; int count; int capacity; int *data; } MetaEnumValueList;
typedef struct MetaEnumView { char pad[4]; int _refCount; char *name; MetaEnumNameList *names; MetaEnumValueList *values; } MetaEnumView;
extern "C" MetaEnumView *igMetaEnum_Create(char *name, char **names, int *values, int count);
struct FieldNameView { char pad12[12]; char *f12; };
struct MetaObjectNameView { char pad28[28]; char *f28; };
struct MetaObjectListView { char pad8[8]; MetaObjectNameView **data; int n; };
struct MetaObjectRegistryView { char pad24[24]; MetaObjectListView *f24; };
extern "C" int g_igMetaField_vtable[4];
extern "C" int g_stringPool[4];
extern "C" int g_igMetaFieldInfo_metaObject_00587190[4];
extern "C" char DAT_004faf00[];
extern "C" char GPR_00554c28;
extern "C" char *DAT_004c22b8[4];
extern "C" char *DAT_004c22c0[4];
extern "C" void *igMetaField_Construct(igMetaField *self);
extern "C" igMetaField *igMetaField_Init(igMetaField *field);
extern "C" igMetaField *igMetaField_CopyConstruct(igMetaField *dest, igMetaField *source);
extern "C" void igMetaField_Destruct(igMetaField *arg0);
extern "C" void igMetaField_Configure(igMetaField *self, const char *fieldName, igMetaField **externalEnumStorage, int offset, igMetaObject *parentMetaObject);
class FieldSizeDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int GetTypeSize(); };
extern "C" void igMetaField_EnsureDefaultStorage(igMetaField *field);
extern "C" void igMetaField_SetDefault(igMetaField *self, int defaultValue);
extern "C" void igMetaField_SetFieldName(igMetaField *self, void **newName);
class FieldResetDispatchView {public: virtual void reserved0(); virtual void reserved1(); virtual void reserved2(); virtual void reserved3(); virtual void reserved4(); virtual void reserved5(); virtual void reserved6(); virtual void reserved7(); virtual void reserved8(); virtual void reserved9(); virtual void reserved10(); virtual void reserved11(); virtual void reserved12(); virtual void reserved13(); virtual void reserved14(); virtual void reserved15(); virtual void reserved16(); virtual void reserved17(); virtual void reserved18(); virtual void reserved19(); virtual void reserved20(); virtual void reserved21(); virtual void reserved22(); virtual void reserved23(); virtual void reserved24(); virtual void reserved25(); virtual void Reset0(void *); virtual void Reset3(void *); virtual void Reset2(void *);};
extern "C" void igMetaField_Reset(igMetaField *field,void *object);
struct DefaultCopyField { int a, b; int off; int c[2]; unsigned short sz; short d; int e[2]; int def; };
extern "C" void igMetaField_SetToDefault(DefaultCopyField *arg0, int arg1);
struct DefaultValueField { int pad0[2]; int f8; int pad1[2]; unsigned short f20; short pad2; int pad3[2]; int f32; };
extern "C" void igMetaField_CopyDefaultToValue(DefaultValueField *arg0, int arg1);
struct igMetaObj { char pad[18]; short id; };
class TypeIndexView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual igMetaObj *vX();
    char pad[12];
    short typeIndex;
};
extern "C" short igMetaField_GetTypeIndex(TypeIndexView *arg0);
class FieldBuildDispatchView { public: virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void *TypeInfo(); virtual void r96(); virtual int TypeSize(); virtual void r104(); virtual void r108(); virtual void r112(); virtual void r116(); virtual void r120(); virtual void r124(); virtual void r128(); virtual void r132(); virtual void r136(); virtual void SetDefault(void *); };
extern "C" void igMetaField_FinalizeDescriptor(igMetaField *field);
/* Rounds size up to a multiple of the field's alignment: (size + a - 1) & ~(a - 1). Reusing the
 * mask local for its complement (m = ~m) orders the temporaries so the nor lands in v0 and the sum
 * in v1. */
struct AlignmentView {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual int v25();
};
class FieldWriteDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int Write(void *,void *,void *,unsigned char); };
extern "C" int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,unsigned char swap);
/* The class lists its virtual methods first so the vptr stays at offset 0 and the data words
 * follow at +4/+8. */
struct PersistentSizeView { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();  virtual int v49(int, int); int pad; int f; };
extern "C" int FUN_002fc740(PersistentSizeView *field, char *object, char *data, igIGBFile *file, unsigned char endianSwap);
class ReadSizeView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(int); };
class RawReadView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int, int); char pad4[16]; unsigned short f20; };
extern "C" unsigned short igMetaField_ReadRawFieldMem(RawReadView *arg0, int arg1, int arg2, int arg3, int arg4);
class RawWriteView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vX(int, int); };
extern "C" int FUN_002fc8a0(igMetaField *arg0);
class CopyDispatchView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};
extern "C" void igMetaField_CopyByTechnique(CopyDispatchView *arg0, int arg1, int arg2, int arg3);
extern "C" void FUN_002fc9f0(igMetaField *arg0, int arg1, int arg2);
extern "C" void FUN_002fca30(igMetaField *field, void *object);
class TypeSizeView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
struct InternedStrings {
    static inline int get() {
        if (g_stringPool[0] == 0) {
            int pool = ((int)StringPool_Allocate(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool[0] = pool;
        }
        return g_stringPool[0];
    }
};
extern "C" RecoveryString FUN_002fca80(igMetaFieldView *arg1, int arg2, int arg3, int arg4);
class ElementWriteView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vB(); virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13(); virtual void e14(); virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19(); virtual void e20(); virtual void e21(); virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual int vC(int, int, int); };
extern "C" int FUN_002fcce0(ElementWriteView *arg0, int arg1, int arg2, int arg3, int arg4);
class FieldValueView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual int vX(int); };
extern "C" int FUN_002fcdb0(igMetaField *arg0, int arg1);
class igMetaFieldResultView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
    virtual igResult vfunc_55(void *value);
    unsigned int _refCount;
    int _offset;
};
extern "C" igResult FUN_002fcdf0(igMetaFieldResultView *self, char *object);
extern "C" int igMetaField_Write(igMetaField *arg0);
class IsAlikeExactlyView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual int vX(); };
class IsAlikeDeepView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(); };
class IsAlikeShallowView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(); };
class IsAlikeSlot46View { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual int vX(); };
struct ByteCompareField { char pad[8]; int base; char pad2[8]; unsigned short n; };
extern "C" int FUN_002fcf90(ByteCompareField *arg0, unsigned char *arg1, unsigned char *arg2);
class igMetaFieldSlots {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void ConstructValue(void *object);
    virtual void d30();
    virtual void ZeroValue(void *object);
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42();
    virtual bool vfunc_43(const void *left, const void *right);
    virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57();
    virtual int IsConstruct();
};
extern "C" bool FUN_002fcfe0(igMetaFieldSlots *self, const void *left, const void *right);
extern "C" bool FUN_002fcff0(igMetaFieldSlots *self, const void *left, const void *right);
struct PrintString { char *p; PrintString() {} };
struct PrintView {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual PrintString vX(int, int);
};
struct PrintField { int vt; int pad; int f8; int fc; };
struct CopyInField { int p[2]; int a; int q[2]; unsigned short h; };
extern "C" void FUN_002fd130(CopyInField *arg0, int arg1, int arg2);
class igMetaFieldAssignView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22(void *object, const void *value);
    unsigned int _refCount;
    int _offset;
};
extern "C" void FUN_002fd150(igMetaFieldAssignView *self, void *object, igMetaFieldAssignView *field, char *source);
struct SwapBytesField { char p[20]; unsigned short size; };
extern "C" void igMetaField_SwapBytes(SwapBytesField *arg0, unsigned char *arg1, int arg2);
class igMetaFieldSwapView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49();
    virtual void SwapBytes(void *value, int count);
    unsigned int _refCount;
    int _offset;
};
extern "C" void igMetaField_SwapValue(igMetaFieldSwapView *self, char *object);
class MangledNameAllocatorView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
extern "C" int igMetaField_GetMangledName(igMetaField *arg0, void **arg1);
/* igMetaFieldInfo's own virtual functions past igObject's (slot n at vtable byte offset 4 * n);
 * slot 24 is igMetaField_FindByName (config names/ObjectModel.tsv). ABI view only. */
class igMetaFieldInfoView {
public:
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19); RESERVED(20);
    RESERVED(21);
    virtual int FindByName(int name);                                           /* +96 */
};
extern "C" int Gap__Core__igMetaFieldInfo__vfunc_23(igMetaFieldInfoView *arg0, int arg1, void *arg2);
extern "C" FieldNameView *igMetaField_FindByName(int arg0, char *arg1);
struct Instance : public igObject { };
struct MetaTreeNode;
struct MetaTreeList { char p[8]; MetaTreeNode **arr; int n; };
struct MetaTreeNode { char p[44]; int f44; char q[4]; MetaTreeList *f52; };
struct FieldPointerStorage { int prefix[2]; igMetaField **data; int count; };
typedef igMetaField *(*FieldFactory)(void *);
struct StaticInitCallbacks { void (**functions)(); int count; };
/* A memory pool's virtuals: slot 31 is igMemoryPool::vfunc_33, IsActive() (returns _isActive);
 * slot 32 is vfunc_34, EnableAllocationLock(enable) (igArenaMemoryPool and igAliasMemoryPool create
 * or drop the pool's _allocationLock semaphore); slot 52 allocates. The callers take IsActive's
 * result at full width: declared unsigned char or bool, the `== 0` test in FUN_002f4070 gains the
 * `andi 0xff` of a byte-returning callee (156 bytes against retail's 152). */
class MemoryPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int IsActive(); virtual igResult EnableAllocationLock(int enable); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
struct CreateMeta { char p[26]; unsigned char f26; char q[5]; int f32; char r[24]; CreateMeta *(*f60)(); char s[8]; int f72; char t[20]; char *f96; };
struct PooledMeta { char p[26]; unsigned char f26; char q[5]; int f32; int f36; char r[20]; PooledMeta *(*f60)(); char s[8]; int f72; char t[20]; char *f96; };
class LayoutField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); char p0[4]; int off; char p1[6]; short idx; unsigned short sz; char p2[2]; void *owner; char p3[9]; unsigned char neg; };
struct LayoutMeta {
    char p0[32]; int w32; int w36; char p1[16]; LayoutMeta *parent; char p2[12]; int w72; char p3[12]; unsigned short w88;
};
struct AncestorMeta { char p[56]; AncestorMeta *f56; };
struct ChainMeta { char p[4]; int refs; char p8[48]; ChainMeta *parent; };
struct ChainRef { ChainMeta *p; ChainRef(ChainMeta *o) : p(o) { if (p != 0) { p->refs = p->refs + 1; } } };
struct PoolNameMeta { char pad[26]; unsigned char f26; char pad2[65]; int *buf; };
extern "C" int g_igMetaObject_vtable[4];
extern "C" igMetaField *g_fieldNameMember[4];
extern "C" int FUN_002fd610(Instance **out, int meta);
static inline void releaseObject_2fd610(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
    }
}
struct CreatedRef {
    igObject *p;
    CreatedRef(igObject *object) : p(object) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    CreatedRef(const CreatedRef &other) : p(other.p) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~CreatedRef() { releaseObject_2fd610(p); }
    igObject *get() const { return p; }
};
extern "C" CreatedRef FUN_002fd6e0(int meta, int pool);
extern "C" void *igMetaObject_Construct(igMetaObject *meta, int extra1);
extern "C" igMetaObject *igMetaObject_Init(igMetaObject *meta);
extern "C" void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source);
extern "C" void igMetaObject_ReleaseLists(igMetaObject *meta);
extern "C" int igMetaObject_CreateInstance(CreateMeta *arg0, MemoryPool *arg1);
extern "C" int igMetaObject_CreateInstanceWithPool(PooledMeta *arg0, MemoryPool *arg1);
extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent);
extern "C" int igMetaObject_CountInstances(MetaTreeNode *arg0, int arg1);
extern "C" void igMetaObject_SetName(igMetaObject *meta, int name);
extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);
extern "C" void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field);
extern "C" int igMetaObject_GetFieldAt(igMetaObject *self, int index);
extern "C" void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name);
extern "C" void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count);
extern "C" void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start);
extern "C" void igMetaObject_FinalizeFieldLayout(LayoutMeta *arg0);
extern "C" int FUN_002fe290(AncestorMeta *arg0, AncestorMeta *arg1);
extern "C" int igMetaObject_GetChildCount(igMetaObject *arg0);
extern "C" int igMetaObject_GetChildAt(igMetaObject *self, int index);
extern "C" void *FUN_002fe300(igMetaObject *arg0, int arg1);
extern "C" int igMetaObject_CountTree(MetaTreeNode *arg0);
extern "C" int igMetaObject_GetFieldCount(igMetaObject *self);
extern "C" void igMetaObject_AddField(igMetaObject *arg0, void *arg1);
extern "C" void FUN_002fe570(igMetaObject *arg0, void *arg1);
extern "C" int FUN_002fe600(igTDataList<ChainMeta *> *list, ChainMeta *object);
extern "C" void igMetaObject_AssignTypeId(igMetaObject *meta);
extern "C" void FUN_002fe810(int *out, PoolNameMeta *s, MemoryPool *a);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)());
extern "C" void igNamedObject_SetName(igNamedObject *arg0, int arg1);
/* Name-or-default is a ?: expression, not an if with an empty then-arm. */
extern "C" void Gap__Core__igNamedObjectInfo__vfunc_23(igNamedObjectInfo *self, int file, igNamedObject *object);
extern "C" int FUN_002feeb0(igTDataList<int> *list, igMetaField *field, int value);
/* igObject's virtual functions: slot n sits at vtable byte offset 8 + 4 * n (the first two words
 * are the class header). The reflected igObject is the same object seen as data. Named slots carry
 * the igObject symbol names (Gap::Core::igObject::<name>, igObject_CloneViaMetadata); vfunc_NN
 * keeps the symbol's slot number. ABI view only: never instantiated. */
class igObjectDispatchView {
public:
    virtual void vfunc_00();
    virtual void constructFields(int flag);
    virtual void destructFields();
    virtual void vfunc_03(); virtual void vfunc_04(); virtual void vfunc_05();
    virtual int vfunc_06(igObjectDispatchView *other);
    virtual void userConstruct(int flag);
    virtual void userDestruct();
    virtual void vfunc_09(); virtual void vfunc_10();
    virtual void resetFields(int flag);
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14();
    virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18();
    virtual igObject *cloneViaMetadata(int copyMode);
    virtual igMetaObject *getMeta();
};
/* RESERVED(n) declares unused virtual slot n so the named slots land on the
 * right byte offsets. */

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
extern "C" int g_igObject_vtable[4];
extern "C" char igObject_className[];
extern "C" int text_refCount[4];
extern "C" int text_memPoolIndex[4];
extern "C" char DAT_004faf60[];
extern "C" int DAT_004faf78[4];
extern "C" char DAT_004faf80[];
extern "C" char DAT_004faf88[];
extern "C" int DAT_005871a0[4];
extern "C" int DAT_005871a8[4];
extern "C" struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p);
typedef struct CopyHeader { int vt; char pad[2]; unsigned char lo : 7; unsigned char hi : 1; unsigned char b7; } CopyHeader;
extern "C" CopyHeader *igObject_CopyConstructHeader(CopyHeader *arg0, CopyHeader *arg1);
/* Stamps the igObject vtable, runs igObject_InitHeader, then fills the header's allocator byte
 * (+7): with the object system active it is the result of the owning allocator's virtual slot 364
 * (the owner-derived encoded allocator index); otherwise zero. */
extern "C" igObject *igObject_ConstructHeader(igObject *self);
class ConstructedObject { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void v9(int); virtual void d8(); virtual void v11(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual igMetaObject *v22(); union { int w4; struct { unsigned cnt:23; unsigned f:9; } b; struct { unsigned char b0; unsigned char b1; unsigned char lo:7; unsigned char hi:1; unsigned char id; } c; } u; };
extern "C" void igObject_Construct(ConstructedObject *arg0, char *arg1);
struct PooledHeader { int w0; unsigned refs : 23; unsigned flag : 1; unsigned rest : 8; };
extern "C" void igObject_ConstructPooled(PooledHeader *arg0, char *arg1);
/* Storage for a new object. Reserves size + prefix_size bytes from the given allocator, falls back
 * to the default allocator (looked up by selector) when none is passed, and to the global heap
 * when there is no allocator at all. It returns the address prefix_size bytes into the block, so a
 * header can precede the object. The allocator method called is vtable offset 216 (vfunc_54), the
 * allocate-bytes slot. */
class MetaSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int *vX(); };
class DestructSelf { public: virtual void d0(); virtual void d1(); virtual void vX(); };
class DestructField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int *); };
struct DestructFieldList { int p0; int p1; DestructField **data; int count; };
class ClearField { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(int *); };
struct ClearFieldList { int p0; int p1; ClearField **data; int count; };
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
extern "C" int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, igIGBFile *file, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap);
struct ReadField { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(void*); };
/* An object record in an .igb object section: its meta-object index and byte size, then (old format)
 * the count of persistent fields written. */
struct FieldRecordHead { int kind; int size; int fieldCount; };
struct ReadObject { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual igMetaObject* v20(); };
extern "C" int FUN_002fff90(ReadObject *object, FieldRecordHead *head, igIGBFile *file, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap);
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
extern "C" int FUN_00300250(FieldObjectView *object, FieldRecordHead *head, FieldDirView *dir, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap);
struct ShallowFields { int pad[2]; int *arr; int count; };
struct ShallowHolder { char pad[40]; ShallowFields *meta; };
struct ShallowObject { virtual void a0(); virtual void a1(); virtual void a2(); virtual int v3(ShallowObject *); virtual void v4(int); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual int v16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual ShallowHolder *v20();  };
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
extern "C" int igObject_IsAlikeShallow(igObjectDispatchView *arg0, igObjectDispatchView *arg1);
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
virtual void Visit(void *,Visitor,void *);
virtual int Write(int object);};
struct FieldVector {int vt,refs;VisitorFieldView **data;int count;};
extern "C" void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context);
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
extern "C" Allocator *igObject_GetAllocator(int a0);
struct ClonedObject : public igObject { };
class CloneSource { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual ClonedObject *v84(int); };
extern "C" igSmartPointer<ClonedObject> FUN_00301010(CloneSource *arg1, int arg2);
/* ABI dispatch view of virtual slot 92 (21 leading virtuals); never instantiated. */
class DirEntryRefSetterView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int SetRef(int);
};
extern "C" void Gap__Core__igObjectDirEntry__vfunc_12(igObjectDirEntry *self);
/* An igObjectList of igObjectDirEntry, or of such lists (an igIGBFile's _entryPool, one per type meta). */
struct ObjectDirEntryList : public igObjectList {
    igObjectDirEntry *at(int index) const { return ((igObjectDirEntry *const *)_data)[index]; }
    void set(int index, igObject *object) {
        if (object != 0) object->_refCount = object->_refCount + 1;
        igObject *old = ((igObject **)_data)[index];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (_count != 0 && index >= 0 && index < _count) {
            ((igObject **)_data)[index] = object;
        }
    }
};
extern "C" igObjectDirEntry *Gap__Core__igObjectDirEntry__vfunc_26(igObjectDirEntry *self, igIGBFile *file);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_27(igObjectDirEntry *self, igObject *object);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_28(igObjectDirEntry *self, igObject *object);
extern "C" void FUN_00301590(igObjectDirEntry *arg0, igMetaObject *arg1);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_23(igObjectDirEntry *self, igObject *object);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_40(igObjectDirEntry *arg0, void *arg1);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_36(igObjectDirEntry *arg0, int arg1);
class igObjectDirEntryView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igObjectDispatchView *_ref;
    int _typeMeta;
    int _typeMetaName;
    int _majorVersion;
    int _minorVersion;
    int _memoryPoolHandle;
    int _typeMetaIndex;
};
extern "C" void Gap__Core__igObjectDirEntry__vfunc_39(igObjectDirEntryView *arg0, igIGBFile *arg1);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_37(igObjectDirEntryView *self);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_33(igObjectDirEntry *arg0, void *arg1);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_34(igObjectDirEntry *arg0, void *arg1);
typedef struct DirEntryCounted { char pad[4]; int _refCount; } DirEntryCounted;
typedef struct DirEntryMetaList { char pad[16]; DirEntryCounted **data; } DirEntryMetaList;
typedef struct DirEntryFileView { char pad[192]; DirEntryMetaList *metas; char pad2[80]; char failed; char pad3[11]; int pool; } DirEntryFileView;
typedef struct DirEntrySelf { char pad[12]; int index; char pad2[12]; DirEntryCounted *typeMeta; int typeMetaName; char pad3[8]; int pool; int typeMetaIndex; } DirEntrySelf;
extern "C" void Gap__Core__igObjectDirEntry__vfunc_31(DirEntrySelf *self, DirEntryFileView *file);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_24(igObjectDirEntry *self, igObject *object);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_25(igObjectDirEntry *self, igObject *object);
extern "C" void Gap__Core__igObjectDirEntry__vfunc_29(igObjectDirEntry *self, int memoryPoolHandle);
extern "C" int Gap__Core__igObjectDirEntry__vfunc_30(igObjectDirEntry *self);
extern "C" void ObjectList_FillRetained(igTDataList<igObject *> *arg0, igObject *arg1);
extern "C" void ObjectList_ClearRetainedPreserveCount(igTDataList<igObject *> *arg0, int extra1);
extern "C" void ObjectList_AppendRetainedList(int arg0, igTDataList<igObject *> *arg1);
extern "C" void ObjectList_ResizeRetained(igTDataList<igObject *> *arg0, int arg1);
struct ObjectListItem { int vt; int _refCount; };
struct ObjectListView { char pad[8]; int count; int cap; ObjectListItem **data; };
extern "C" igResult ObjectList_RemoveFirstRetained(ObjectListView *self, ObjectListItem *value, int start, int extra3);
extern "C" int ObjectList_RemoveAllRetained(igTDataList<igObject *> *list, igObject *object, int start);
extern "C" int ObjectList_AppendUniqueRetained(igTDataList<igObject *> *list, igObject *object);
extern "C" int igProperty_FindByName(igObjectList *arg0, igMetaField *arg1, int arg2);
typedef struct Field { char pad[8]; int _offset; } Field;
extern "C" void FUN_00302540(ObjectListView *self, Field *field);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_52(igObjectRefArrayMetaField *self, int passThrough, int perElement);
extern "C" void FUN_00302780(igObjectRefArrayMetaField *arg0, int arg1, int arg2, igObject *arg3);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_31(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_32(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_34(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_30(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_36(igObjectRefArrayMetaField *s, char *a1, char *a2);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_39(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_50(igObjectRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" void Gap__Core__igObjectRefArrayMetaField__vfunc_42(igObjectRefArrayMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_45(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_46(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igObjectRefArrayMetaField__vfunc_47(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
class CopyableObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15();
    virtual void prepareCopy();
    virtual void s17(); virtual void s18();
    virtual CopyableObject *duplicate(int deep);
    unsigned int _refCount;
};
extern "C" int g_igObjectRefMetaField_vtable[4];
extern "C" void igObjectRefMetaField_Assign(igObjectRefMetaField *field,void *object,igObject *value);
extern "C" int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *);
extern "C" void FUN_00303460(igObjectRefMetaField *arg0, igObject *arg1);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_51(igObjectRefMetaField *self, igObject **valueSlot, int extra2, int extra3, int extra4);
extern "C" void igObjectRefMetaField_ConstructValue(igObjectRefMetaField *field,void *object);
extern "C" void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_34(igObjectRefMetaField *field,void *object);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_36(igObjectRefMetaField *self, char *dst, char *src);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_38(igObjectRefMetaField *arg0, int arg1, int arg2);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_39(igObjectRefMetaField *self, int instance);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_41(igObjectRefMetaField *self, int arg1, int arg2, int arg3);
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_42(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_44(igObjectRefMetaField *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_45(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_46(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" int Gap__Core__igObjectRefMetaField__vfunc_47(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" void *igObjectRefMetaField_Construct(igObjectRefMetaField *self, int extra1);
extern "C" void *igObjectRefMetaField_Init(igObjectRefMetaField *self);
extern "C" void *FUN_00303c60(igObjectRefMetaField *arg0, void *arg1);
extern "C" void FUN_00303cd0(igObjectStringMap *self, int name, void *object);
typedef igTDataList<igObject *> FieldList;
struct FieldTable { char pad[8]; FieldList *fields; };
extern "C" int FUN_00303dc0(FieldTable *table, int name);
extern "C" void FUN_00303ed0(igObjectStringMap *o);
extern "C" void FUN_00304030(igObjectStringMap *arg0, int arg1);
class igPsx2FileView;
extern "C" igPsx2FileView *DAT_005871b0[4];
extern "C" void FUN_00304350(igPsx2FileView *arg0);
extern "C" igPsx2FileView *DAT_005871b8[4];
extern "C" void FUN_003043c0(igPsx2FileView *arg0);
extern "C" unsigned char GPR_00554998;
extern "C" unsigned char GPR_0055499c;
extern "C" unsigned char GPR_005549a4;
extern "C" unsigned char GPR_005549a8;
extern "C" void FUN_00304720(igPluginHelper *helper, int name, int location, int locationType);
extern "C" int DAT_004c22c8[4];
extern "C" int DAT_004c22d0[4];
extern "C" int DAT_004fafb8[4];
extern "C" int DAT_004fafc0[4];
extern "C" char GPR_00554c18;
extern "C" char GPR_00554c1c;
extern "C" void FUN_00304840(igPluginHelper *self, int name, int path);
typedef struct IniKeyText { char pad[4]; int _refCount; char *text; } IniKeyText;
typedef struct IniValueList { char pad[4]; int _refCount; int count; } IniValueList;
typedef struct IniSystemTables { char pad[56]; void *ini; } IniSystemTables;
extern "C" char PLUGINS[];
extern "C" bool igRegistry_GetKeyName(int registry, int section, int index, IniKeyText **key);
/* igPluginHelper::_libraryLoader; slot 22 (vfunc_24) receives each loaded igLibrary in turn. */
class igLibraryLoaderView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual int vfunc_24(igLibrary **library);
};
extern "C" void Gap__Core__igPluginHelper__vfunc_10(igPluginHelper *self);
class Iter { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual igResult vNext(int *, int); };
struct Args { igResult (*fn)(int); Iter *it; };
extern "C" int FUN_00304e60(Args *args);
extern "C" int FUN_00305000(igStandardQueueView *queue);
extern "C" void Gap__Core__igRawRefArrayMetaField__vfunc_52(igRawRefArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igRawRefArrayMetaField__vfunc_51(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" int Gap__Core__igRawRefArrayMetaField__vfunc_50(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" int Gap__Core__igRawRefArrayMetaField__vfunc_25(igRawRefArrayMetaField *self);
extern "C" int FUN_00305370(igPluginRepositoryList *self);
extern "C" void Gap__Core__igRawRefMetaField__vfunc_41(igRawRefMetaField *self, char *object, int unusedArg, const char *indent);
extern "C" int Gap__Core__igRawRefMetaField__vfunc_43(igRawRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int DAT_00532eb0[4];
extern "C" void igRefMetaField_ZeroValue(igMetaField *field,void *object);
extern "C" void igRefMetaField_ClearValue(igMetaField *field,void *object);
extern "C" unsigned char igRefMetaField_IsConstruct(igRefMetaField *field);
extern "C" char DAT_004fb0c8[];
extern "C" char DAT_004fb0d0[];
extern "C" char DAT_004fb0d8[];
extern "C" char text_Reference_d[];
extern "C" char text_Reference_1[];
extern "C" char GPR_00554c2c;
struct Rec { char p[12]; char *name; };
extern "C" int FUN_00305800(RecoveryString *arg0, void *arg1, int *arg2, int arg3, int arg4, char *arg5, int arg6);
extern "C" int FUN_00305aa0(int self, int str, int *out, int n, igDirectory *list);
extern "C" int FUN_00305bd0(igRefMetaField *arg0, int arg1, int arg2);
extern "C" int g_igStringMetaField_vtable[4];
extern "C" int g_igUnsignedIntMetaField_vtable[4];
extern "C" void *igRefMetaField_Construct(igRefMetaField *self);
extern "C" void *igRefMetaField_Init(igRefMetaField *self);
extern "C" void *igStringMetaField_Construct(igStringMetaField *self, int extra1);
extern "C" void *igStringMetaField_Init(igStringMetaField *self);
extern "C" void *igUnsignedIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" void *igUnsignedIntMetaField_Init(igMetaField *self);
class IniPathObject;
struct IniPathHandle { IniPathObject *p; IniPathHandle() {} IniPathHandle(const IniPathHandle &o) { p = o.p; } };
class IniPathObject { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); 
 virtual IniPathHandle Join(char *);
 int _refCount; char *text;
};
class IniSourceFile { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); 
 virtual int Open(char *, char *);
 virtual void Close();
};
struct IniReaderView { char pad[12]; IniSourceFile *file; };
extern "C" char text_alchemy_ini[];
extern "C" bool FUN_00305d30(IniReaderView *self, char *name, char *dir);
typedef struct IniPairText { char pad[8]; char *text; } IniPairText;
typedef struct IniPairEntry : public igObject { int section; IniPairText *value; IniPairText *key; } IniPairEntry;
typedef struct IniPairList { char pad[8]; int count; int cap; IniPairEntry **data; } IniPairList;
typedef struct IniIncludeView { char pad[8]; IniPairList *pairs; } IniIncludeView;
extern "C" int FUN_003061c0(void *self, IniIncludeView *inc, int overwrite);
extern "C" char *DAT_004fb160[];
typedef struct IniNameText { char pad[4]; int _refCount; char *text_306360; } IniNameText;
typedef struct IniSectionList { char pad[8]; int count; int cap; IniNameText **data; } IniSectionList;
typedef struct IniSectionsView { char pad[16]; IniSectionList *sections; } IniSectionsView;
extern "C" int FUN_00306360(IniSectionsView *self, char *name, int create);
struct Node { char p[12]; igStringObj *f12; };
/* Holds the igStringObj a registry string lookup creates for its default text. */
struct StringObjHolder {
    igStringObj *ref;
    inline void release() {
        igStringObj **self = &ref;
        if (self) {
            igStringObj *object = ref;
            if (object) {
                --object->_refCount;
                if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                    igObject_Destroy((void *)object);
            }
        }
    }
};
extern "C" int FUN_00306770(int arg0, int arg1, const char *arg2, igStringObj **arg3, const char *arg4, int arg5);
typedef struct ShortStr { char pad[8]; char *text_306910; } ShortStr;
typedef struct Pair { char pad[12]; ShortStr *value; } Pair;
extern "C" char DAT_004fb190[];
typedef struct Str { char pad[4]; int _refCount; char *text_306aa0; int length; } Str;
extern "C" int FUN_00306aa0(void *self, int section, const char *key, igStringRefList *list, int create);
extern "C" char DAT_004d3d11[16];
extern "C" char DAT_004fb198[16];
extern "C" char text_0x_x[16];
extern "C" void FUN_003077a0(igRegistry *self);
extern "C" char DAT_004fb1a8[];
extern "C" char text_abcdefghijklmnopqrstuvwxyzABCDEF_2[];
extern "C" char DAT_004fb200[];
extern "C" char text_showRegistryQueries[];
typedef struct Ini { char pad[20]; unsigned char flag; } Ini;
extern "C" void FUN_00307870(Ini *self, int file, int overwrite);
extern "C" bool FUN_00307a50(void *unused, igFileView *s, char *buf, int *lines);
/* Arena handles (4-byte refs) of the reflected int fields are followed through casts. */
struct RegistryValueRef {
    igRegistryValue *p;
    ~RegistryValueRef() {
        igRegistryValue *q = p;
        if (q != 0) {
            q->_refCount = q->_refCount - 1;
            if (((unsigned long long)(long long)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q);
        }
    }
};
extern "C" igRegistryValue *FUN_00307c10(igRegistry *arg0, int arg1, const char *arg2, int arg3);
extern "C" char DAT_004fb280[];
extern "C" int DAT_005871c0;
typedef struct IniIncludeText { char pad[4]; int _refCount; char *text_307fd0; int length; } IniIncludeText;
typedef struct IniIncludeFile { char pad[12]; char *dir; } IniIncludeFile;
extern "C" void FUN_00307fd0(void *self, IniIncludeFile *file, char *line, int lineNo, int overwrite);
extern "C" int UNKNOWN[4];
extern "C" int INTERNAL_ERROR[4];
extern "C" int ERROR[4];
extern "C" int WARNING[4];
extern "C" int DEPRECATION[4];
extern "C" int NOTICE[4];
extern "C" int INFO[4];
extern "C" int DETAIL[4];
extern "C" char DAT_004fb2f0[];
extern "C" int DAT_004fb300[4];
extern "C" unsigned char GPR_005549b0;
extern "C" int (*DAT_004c22e0[4])(int, char *);
extern "C" int DAT_004c22d8;
extern "C" char text_kWarning[];
extern "C" char text_kError[];
extern "C" char text_assertOnErrors[];
extern "C" char text_defaultReportLevel[];
extern "C" char text_kDetail[];
extern "C" char text_kInfo[];
extern "C" char text_kNotice[];
extern "C" char GPR_00554c30;
extern "C" int text_igImageDirectory[4];
extern "C" int DAT_00586670[4];
extern "C" igSmartPointer<igObject> FUN_003087a0(void *directory, int name);
struct MemberRef {
    igObject *p;
    MemberRef(igObject *object) : p(object) {}
    ~MemberRef() {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
extern "C" void FUN_00308860(igResource *self, int name, int value);
extern "C" igDirectory *FUN_00308a90(igResource *self);
extern "C" int g_resourceLoaderStackSize[4];
/* The igQueue an igResource loads through (an igStandardQueue at run time): slot 21 is
 * igStandardQueue::vfunc_23, AllocateStorage() (allocates _data for _capacity elements); slot 24
 * is vfunc_26, Insert(value, block). */
class ResourceLoadQueue { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void AllocateStorage(); virtual void d22(); virtual void d23(); virtual igResult Insert(int value, int block); };
/* The thread FUN_00304f00 starts to service the load queue (an igPsx2Thread): slot 48 is
 * igPsx2Thread::vfunc_50, SetPriority(priority). */
class ResourceLoadThread { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual igResult SetPriority(int priority); };
/* igResource (reflected.h) with its asynchronous-loading fields held as smart pointers. */
struct ResourceAsyncView { char pad[28]; unsigned char _asyncLoadState; char pad29[3]; igSmartPointer<igObject> _loadQueue; igSmartPointer<igObject> _loadThread; };
extern "C" void igResource_StartAsyncLoading(ResourceAsyncView *self);
struct PairCallStatus { int w; };
struct PairCountedObject { int vt; int f4; };
struct PairCountedRef { int vt; int f4; };
class PairQueryTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual PairCallStatus m96(PairCountedObject *); };
class PairQueryHost { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual PairQueryTarget *m92(); };
/* The same igResource fields as ResourceAsyncView, as raw pointers: StopAsyncLoading releases them
 * by hand. */
class ResourceAsyncRawView { public: char pad[28]; unsigned char _asyncLoadState; char p29[3]; ResourceLoadQueue *_loadQueue; PairCountedObject *_loadThread; };
extern "C" void igResource_StopAsyncLoading(ResourceAsyncRawView *self);
extern "C" void Gap__Core__igResource__vfunc_12(igResource *self);
extern "C" void *FUN_00308fb0(igResource *arg0, int arg1);
/* Holds the igIGBFile a directory load creates. */
struct IgbFileHolder { igObject *p; ~IgbFileHolder() {} };
extern "C" void *igResource_LoadDirectory(igResource *self, int path);
extern "C" igIGBFileView *FUN_00309640(igResource *self, igIGBFileView *file);
extern "C" void igResource_UnloadDirectory(igResource *self, int name);
extern "C" void FUN_00309870(igResource *self);
extern "C" void FUN_00309970(igResource *self);
extern "C" void FUN_00309c90(igDirectory *arg0, int arg1, int arg2);
extern "C" int text_igNode[4];
extern "C" int text_igSceneInfo[4];
extern "C" int text_sceneGraph[4];
extern "C" int text_cameras[4];
extern "C" int text_sceneGraphList[4];
static inline igObjectRefMetaField *AsObjectRefMetaField(void *p) {
    if (p != 0 && igObject_IsKindOf(p, (igMetaObject *)(((void * *)g_igObjectRefMetaField_metaObject)[0])) != 0) { return (igObjectRefMetaField *)p; }
    return 0;
}
static inline void *AsObjectList(void *p) {
    if (p != 0 && igObject_IsKindOf(p, (igMetaObject *)(((void * *)g_igObjectList_metaObject)[0])) != 0) { return p; }
    return 0;
}
extern "C" int text_igSceneWrapper[4];
extern "C" void FUN_0030a260(igResource *arg0, int arg1);
extern "C" void Gap__Core__igShortArrayMetaField__vfunc_52(igShortArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igShortArrayMetaField__vfunc_25(igShortArrayMetaField *self);
extern "C" int text_hd_n[4];
extern "C" int DAT_004fb428[4];
extern "C" int DAT_00533080[4];
extern "C" int FUN_0030a510(igRegistryValueList *self);
extern "C" void Gap__Core__igStringArrayMetaField__vfunc_52(igStringArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igStringArrayMetaField__vfunc_51(igStringArrayMetaField *arg0, void *parg1, void *parg2, int arg3, int arg4);
extern "C" int Gap__Core__igStringArrayMetaField__vfunc_50(igStringArrayMetaField *arg0, void *parg1, void *parg2, int arg3, int arg4);
extern "C" void Gap__Core__igStringArrayMetaField__vfunc_32(igStringArrayMetaField *arg0, int arg1);
extern "C" void igStringMetaField_AssignText(igStringMetaField *self, int object, int *textCell);
extern "C" int Gap__Core__igStringMetaField__vfunc_44(igStringArrayMetaField *self, int objectA, int objectB);
extern "C" void igStringMetaField_DestructValue(igStringMetaField *self, int object);
extern "C" int Gap__Core__igStringMetaField__vfunc_49(igStringMetaField *arg0, int arg1);
class Desc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void vSwap(int *, int); };
extern "C" void igStringMetaField_CopyValue(igStringMetaField *arg0, int arg1, int arg2);
extern "C" void Gap__Core__igStringMetaField__vfunc_38(igStringArrayMetaField *arg0, int arg1, int arg2);
extern "C" bool Gap__Core__igStringMetaField__vfunc_45(igStringMetaField *field,const void *one,const void *two);
extern "C" bool Gap__Core__igStringMetaField__vfunc_46(igStringMetaField *field,const void *one,const void *two);
extern "C" bool Gap__Core__igStringMetaField__vfunc_47(igStringMetaField *field,const void *one,const void *two);
extern "C" int g_igStringMetaField_vtable[4];
typedef struct IniStringView { char pad[8]; char *text; unsigned int length; } IniStringView;
extern "C" void FUN_0030b320(IniStringView *arg0, int arg1, int arg2);
extern "C" int igStringObj_Clear(IniStringView *arg0);
extern "C" char *FUN_00300d70(IniStringView *, unsigned int);
extern "C" void igStringObj_Insert(IniStringView *self, char *insert, unsigned int at, unsigned int n);
/* An igStringObj's text: its buffer, or the shared empty text when it has none. */
static inline char *igStringObj_Text(igStringObj *s) { return (char *)s->_buffer == 0 ? g_stringObjEmptyText[0] : (char *)s->_buffer; }
extern "C" bool FUN_0030b670(igStringObj *o, char *out);
extern "C" int TRUE[4];
extern "C" int FALSE[4];
extern "C" void igStringObj_KeepExtension(igStringObj *o);
extern "C" void FUN_0030b980(igStringObj *p);
extern "C" int DAT_004C22F0[4];
extern "C" int igStringObj_Erase(igStringObj *self, unsigned int pos, unsigned int len);
struct SrcStr { char p0[8]; int f8; int f12; };
extern "C" void FUN_0030bce0(SrcStr *src, long long delim, igTDataList<char *> *list);
extern "C" void FUN_0030bee0(igStringObj *self);
extern "C" int FUN_0030bfa0(igStringObjList *self, int key, int (*cmp)(char *, int));
/* 24-byte target ABI view. Field labels do not assert the original C++ member spelling. */
typedef struct {
    int pool;
    unsigned count, step, capacity;
    void **data;
    int cleanup;
} StringTableLayout;
typedef char StringTableLayoutSize[(sizeof(StringTableLayout) == 24) ? 1 : -1];
struct StringTableEntry { int pad4; int rc; };
struct StringTableSearchView { int pad[1]; unsigned int cnt; unsigned int n; int pad12; int *tab; };
struct StringTableInsertView { char pad[4]; unsigned cnt; unsigned f8; int f12; char *f16; };
struct StringTableChunkList { int first; int pad[4]; int cnt; };
/* 36-byte string chunk. References are 4-byte values in this ABI. */
typedef struct StringChunk {
    int table;          /* +0   owning string pool */
    int next;           /* +4   next chunk in the chain */
    int previous;       /* +8   previous chunk in the chain */
    int capacity;       /* +12  storage size in bytes */
    int storage;        /* +16  allocator-provided storage base */
    int storageEnd;     /* +20  end of the storage */
    int freeHead;       /* +24  end address of the first free block */
    int largestFree;    /* +28  cached largest free size, -1 = unknown */
    char isEmpty;       /* +32  no strings live in the chunk */
} StringChunk;
struct StringChunkStorageView {
    int table, next, previous; unsigned int size; int storage, end, head, largest;
    unsigned char empty;
};
typedef char StringChunkSizeCheck[sizeof(StringChunkStorageView)==36 ? 1 : -1];
/* A string chunk as its release path sees it. Field labels do not assert the original member
 * spelling. */
typedef struct StringChunkOwnerView {
    int owner;                  /* +0  the pool that owns the chunk */
    struct StringChunkOwnerView *next; /* +4 */
    struct StringChunkOwnerView *prev; /* +8 */
    unsigned capacity;          /* +12 storage size in bytes */
    char pad16[16];             /* +16 storage pointers, not used here */
    unsigned char is_empty;     /* +32 set at construction, cleared by StringChunk_AllocateToken */
} StringChunkOwnerView;
typedef char StringChunkOwnerViewSize[(sizeof(StringChunkOwnerView) == 36) ? 1 : -1];
struct StringChunkPool { struct StringChunkPool *f0; int f4; int f8; int f12; };
struct StringChunkTokenView { struct StringChunkPool *f0; struct StringChunkTokenView *next; int f8; unsigned f12; int p16[3]; int f28; char f32; };
typedef struct StringBlockHeader { unsigned short next; unsigned short size; } StringBlockHeader;
typedef struct StringChunkState { char pad[24]; char *free; int largest; } StringChunkState;
struct SyncResult { int v; SyncResult() {} };
class SyncLockView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual SyncResult vX(); };
struct SyncLockRef { int word0; int references; };
extern "C" void *DAT_005871c8[4];
extern "C" void *StringTable_Destroy(StringTableLayout *self, long long delete_flag);
extern "C" void StringTable_NotifyEmptyChunk(StringTableChunkList *arg0, void *arg1);
extern "C" int StringTable_SearchRetained(struct StringTableSearchView *arg0, int arg1, int *arg2, unsigned int *arg3);
extern "C" void StringTable_EraseAt(StringTableLayout *self, unsigned index);
extern "C" void StringTable_InsertAt(struct StringTableInsertView *arg0, int arg1, int arg2);
extern "C" void *StringTable_AllocateObject(unsigned int size, igMemoryPoolView *pool);
extern "C" void *StringChunk_Construct(StringChunk *chunk, int previous, int table, int capacity);
extern "C" StringChunk *StringChunk_Destroy(StringChunk *chunk, long long deleteFlags);
extern "C" int StringChunk_AllocateToken(struct StringChunkTokenView *arg0, int arg1, struct StringChunkTokenView **arg2, int *arg3);
extern "C" void StringChunk_ReleaseHeader(StringChunkOwnerView *self, int header);
extern "C" void StringChunk_InitializeStorage(StringChunkStorageView *chunk);
extern "C" int StringChunk_FreeStorage(StringChunk *chunk);
extern "C" char *StringChunk_TakeBlock(StringChunkState *self, unsigned int bytes);
extern "C" int StringChunk_MergeBlocks(StringChunk *chunk, unsigned short *previous, unsigned short *left, unsigned short *right);
extern "C" void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool);
typedef struct StringRefListView { char pad[8]; int count; int cap; int **data; } StringRefListView;
extern "C" void StringList_Resize(StringRefListView *arg0, int arg1);
extern "C" int DAT_004c22f8[4];
struct igDataListView {
    int vtable; int references; int count; int capacity; char *data;
    void reserveFor(int n) const {
        int grown = capacity * 2;
        if (capacity < n) {
            if (!(grown < count)) {
                List_Reserve((igDataList *)this, grown, 1);
            }
        }
    }
};
struct igIntListView { int vtable; int references; int count; int capacity; int *data; };
/* Slot 21 hashes a string, slot 22 records a string offset in the hash table, slot 23 turns the
 * hash table on or off. */
class igStringTableView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int hash(char *s);
    virtual int insert(char *s, int offset);
    virtual void setHashing(int enable);
    int references;
    int f8;
    int hashing;
    igDataListView *strings;
    igIntListView *hashTable;
};
struct ClearList { int p0; int p1; int n; int cap; };
struct ClearOwner { char pad[16]; struct ClearList *a; struct ClearList *b; };
extern "C" void FUN_0030cfa0(struct ClearOwner *arg0);
typedef struct CountList { char pad8[8]; int cnt; char pad12[4]; char *data; } CountList;
typedef struct CountOwner { char pad16[16]; CountList *b; } CountOwner;
extern "C" int FUN_0030d080(CountOwner *arg0);
struct TruncateList {
    int pad[2];
    int count;
    int cap;
    char *data;
    void SetCount(int n) {
        if (n >= 0) {
            if (n <= cap) {
                count = n;
            } else {
                List_Resize(this, n, 1);
            }
        }
    }
};
struct TruncateOwner { char pad[12]; int f12; TruncateList *l; };
extern "C" int FUN_0030d230(igStringTableView *self, char *s);
extern "C" int FUN_0030d350(igStringTableView *arg0, unsigned int arg1);
struct NextIn { int p0, p4; int len; int p12; char *buf; };
struct NextOwner { int p0, p4, p8, p12; struct NextIn *in; };
extern "C" int FUN_0030d4a0(struct NextOwner *o, int i);
extern "C" unsigned int Gap__Core__igStringTable__vfunc_23(igStringTableView *self, char *s);
struct ProbeList { char pad[8]; int count; int capacity; int *data; };
class ProbeTable { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vHash(int); virtual void d22(); virtual void vRehash(int);
 int pad1[3]; int pad2; ProbeList *hash; };
extern "C" int Gap__Core__igStringTable__vfunc_24(ProbeTable *self, int key, int value);
extern "C" void Gap__Core__igStringTable__vfunc_25(igStringTableView *arg0, int arg1);
extern "C" int Gap__Core__igStructMetaField__vfunc_27(igStructMetaField *self);
extern "C" void Gap__Core__igStructMetaField__vfunc_31(igStructMetaField *self, int instance);
extern "C" void Gap__Core__igStructMetaField__vfunc_32(igStructMetaField *self, int instance);
extern "C" void Gap__Core__igStructMetaField__vfunc_28(igStructMetaField *self, int instance);
class igStructMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25();
    virtual void SetToDefault(void *object);
};
extern "C" void Gap__Core__igStructMetaField__vfunc_30(igStructMetaFieldView *self, void *object);
extern "C" int Gap__Core__igStructMetaField__vfunc_60(igStructMetaField *self);
struct SymbolRecord { int name; int address; unsigned int size; int path; };
class igSymbolTableView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual igResult vfunc_25(int, int, int, int, int, int, int);
    virtual int vfunc_26(unsigned int address);
    virtual void d25(); virtual void d26();
    virtual void vfunc_29(int, int, int, int);
    virtual int vfunc_30(int address);
    virtual int vfunc_31(int address, int size, int index);
    virtual void vfunc_32(int capacity);
    unsigned int _refCount; int _capacity; int _hashCapacity; unsigned int _lowAddress; unsigned int _highAddress;
    unsigned int _hashIncrement; igIntListView *_symbols; igIntListView *_hashIndex; int _symbolNames; int _sourceFileNames;
};
extern "C" void FUN_0030da20(igSymbolTableView *arg0, unsigned arg1, unsigned arg2);
extern "C" int Gap__Core__igSymbolTable__vfunc_23(igSymbolTable *self);
extern "C" void Gap__Core__igSymbolTable__vfunc_24(int *arg0, igSymbolTableView *arg1, int arg2);
extern "C" igResult Gap__Core__igSymbolTable__vfunc_25(igSymbolTable *self, int idx, char *name, int nameSize, int *a, int *b, char *path, int pathSize);
extern "C" int Gap__Core__igSymbolTable__vfunc_26(igSymbolTableView *o, unsigned key);
extern "C" void Gap__Core__igSymbolTable__vfunc_27(int *out, igSymbolTableView *o, int a, int b, int c, int d, int e, int f, int g, int *h);
extern "C" void Gap__Core__igSymbolTable__vfunc_28(igSymbolTableView *o, int a, int b, int c, int d);
extern "C" unsigned int Gap__Core__igSymbolTable__vfunc_30(igSymbolTable *arg0, int arg1);
extern "C" int Gap__Core__igSymbolTable__vfunc_31(igSymbolTableView *self, int key, int key2, int value);
extern "C" int DAT_004c2300;
extern "C" void Gap__Core__igSymbolTable__vfunc_32(igSymbolTableView *self, int n);
extern "C" void Gap__Core__igPsx2ThreadManager__vfunc_11(igPsx2ThreadManagerView *self);
extern "C" void igUnsignedCharArrayMetaField_SwapBytes(igUnsignedCharArrayMetaField *arg0, int arg1, int arg2);
extern "C" unsigned short igUnsignedCharArrayMetaField_GetSize(igUnsignedCharArrayMetaField *self);
extern "C" int DAT_004fb440[4];
extern "C" int DAT_004f9948[4];
extern "C" void Gap__Core__igUnsignedIntArrayMetaField__vfunc_52(igUnsignedIntArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igUnsignedIntArrayMetaField__vfunc_25(igUnsignedIntArrayMetaField *self);
extern "C" int DAT_004fb448[4];
extern "C" int g_igUnsignedIntMetaField_vtable[4];
extern "C" void Gap__Core__igUnsignedLongArrayMetaField__vfunc_52(igUnsignedLongArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igUnsignedLongArrayMetaField__vfunc_25(igUnsignedLongArrayMetaField *self);
extern "C" int DAT_00533530[4];
extern "C" int Gap__Core__igUnsignedLongMetaField__vfunc_27(igUnsignedLongArrayMetaField *self);
extern "C" void Gap__Core__igUnsignedShortArrayMetaField__vfunc_52(igUnsignedShortArrayMetaField *self, int item, int count);
extern "C" int Gap__Core__igUnsignedShortArrayMetaField__vfunc_25(igUnsignedShortArrayMetaField *self);
extern "C" int DAT_00533630[4];
extern "C" int Gap__Core__igUnsignedShortMetaField__vfunc_27(igUnsignedShortArrayMetaField *self);
extern "C" int text_0x_08x_n[4];
extern "C" int text_0x_08x[4];
extern "C" int DAT_004c2310[4];
extern "C" int DAT_004c2330[4];
extern "C" int DAT_004c2338[4];
extern "C" int DAT_004c2340[4];
extern "C" int DAT_004c2348[4];
extern "C" int DAT_004c2350[4];
extern "C" int DAT_004c2358[4];
extern "C" int text_Arena_trigger_event_s_address_0x[4];
extern "C" int DAT_005871e0[4];
extern "C" int DAT_005871e8[4];
extern "C" int (*DAT_005871f0[4])(void *, int, int, int, int, int, int);
extern "C" unsigned char GPR_00554c34;
class O30F { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual int v87();
  int pad4[44]; int f180; };
extern "C" void FUN_0030f040(O30F *arg0, int arg1, int arg2, int arg3);
struct ArenaChunkWord { unsigned lo:5; unsigned size:19; unsigned mid:7; unsigned big:1; };
struct ArenaChunkBytes { unsigned char inUse:1; unsigned char align:4; unsigned char pad:3; char p1[2]; unsigned char mid:7; unsigned char big:1; char p2[4]; unsigned short ext:12; unsigned short pad2:4; char p3; unsigned char free:1; };
struct ArenaCheckState { char pad[44]; char *top; char pad2[1968]; int flags; };
class ArenaCheckPool { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106();
 virtual char *Low();
 virtual char *High();
 char pad[108]; ArenaCheckState *state; char pad2[68]; int errorLevel; int checkLevel; int pad3[2]; int minimum;
};
extern "C" char text_igArenaMemoryPool_Invalid_or_cor[];
extern "C" char text_E3_Below_used_address_range[];
extern "C" char text_E4_Above_used_address_range[];
extern "C" char text_E5_Block_size_less_than[];
extern "C" char text_igArenaMemoryPool_Invalid_or_cor_2[];
extern "C" char text_E6_Corrupted_header[];
extern "C" char text_E10_Corrupted_header[];
extern "C" unsigned char GPR_00554c40;
extern "C" unsigned char GPR_00554c44;
extern "C" unsigned char GPR_00554c48;
extern "C" unsigned char GPR_00554c4c;
extern "C" unsigned char GPR_00554c50;
extern "C" void igArenaMemoryPool_CheckChunk(ArenaCheckPool *self, ArenaChunkBytes *h);
extern "C" char text_E21_This_block_should_be_marked[];
extern "C" char text_E22_Corrupted_free_list[];
extern "C" char text_E23_This_block_should_be_marked[];
extern "C" char text_E24_Block_size_too_small_possibl[];
extern "C" unsigned char g_igArenaMemoryPool_ignoreE21Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE22Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE23Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE24Notice;
extern "C" void igArenaMemoryPool_CheckFreeChunk(ArenaCheckPool *self, ArenaChunkBytes *h);
extern "C" void igArenaMemoryPool_CheckInUseChunk(ArenaCheckPool *self, ArenaChunkBytes *h);
extern "C" char text_E25_Below_used_address_range[];
extern "C" char text_E26_Above_used_address_range[];
extern "C" char text_E27_Block_size_less_than[];
extern "C" char text_E28_Corrupted_header[];
extern "C" char text_E32_Corrupted_header[];
extern "C" char text_E33_Block_size_too_small_possibl[];
extern "C" char text_E34_Block_not_aligned_properly[];
extern "C" char text_E35_Block_size_bad_possible_corr[];
extern "C" char text_E36_Block_size_bad_possible_corr[];
extern "C" unsigned char GPR_00554c8c;
extern "C" unsigned char GPR_00554c90;
extern "C" unsigned char GPR_00554c94;
extern "C" unsigned char GPR_00554c98;
extern "C" unsigned char GPR_00554c9c;
extern "C" unsigned char GPR_00554ca0;
extern "C" unsigned char GPR_00554ca4;
extern "C" unsigned char GPR_00554ca8;
extern "C" unsigned char GPR_00554cac;
extern "C" void FUN_003105c0(ArenaCheckPool *self, ArenaChunkBytes *h, int requested);
extern "C" int text_E37_Corrupted_header[4];
extern "C" unsigned char DAT_00554cb0;
extern "C" char text_igArenaMemoryPool_E67_Block_list[];
extern "C" char text_igArenaMemoryPool_E68_Unable_to[];
extern "C" unsigned char GPR_00554ce4;
extern "C" unsigned char GPR_00554ce8;
typedef struct Ranges {
    char pad[2020];
    unsigned int *data;   /* 2020 */
    int cap;              /* 2024 */
    int count;            /* 2028 */
    int half;             /* 2032 */
    char pad2[20];
    int total;            /* 2056 */
} Ranges;
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_111(igArenaMemoryPool *o, unsigned int lo, int len);
typedef struct ArenaBlockTable { char pad[2020]; int *blocks; int capacity; int count; } ArenaBlockTable;
typedef struct ArenaPoolView { char pad[112]; ArenaBlockTable *arena; } ArenaPoolView;
extern "C" int DAT_004f9950[];
extern "C" char DAT_004fc1e0[];
extern "C" int text_Pool_d_of_d_tot_0x_06x[4];
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_96(igArenaMemoryPool *arg0, int arg1);
class igArenaMemoryPoolView;
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_102(int *arg0, igArenaMemoryPoolView *arg1);
struct RefObject { int word0; int references; };
struct TagByte { unsigned char lo:7; unsigned char flag:1; };
class SetFlagsPool;
extern "C" char text_Unable_to_allocate_memory_for_ar[];
extern "C" int DAT_00587200[4];
extern "C" char text_igArenaMemoryPool_checkHeap_E69[];
extern "C" char text_igArenaMemoryPool_checkHeap_E70[];
extern "C" unsigned char GPR_00554cec;
extern "C" unsigned char GPR_00554cf0;
struct CheckHeapArena { char pad[2020]; int *blocks; int capacity; int count; };
struct CheckHeapPool { char pad[112]; CheckHeapArena *arena; char pad2[72]; int verbosity; };
class HeapBoundsPool;
extern "C" igResult igArenaMemoryPool_CheckHeap(CheckHeapPool *self);
extern "C" char DAT_004fc490[];
extern "C" char DAT_004fc500[];
extern "C" char DAT_004fc570[];
extern "C" char DAT_004fc5e0[];
extern "C" char DAT_004fc660[];
extern "C" unsigned char GPR_00554cf4;
extern "C" unsigned char GPR_00554cf8;
extern "C" unsigned char GPR_00554cfc;
extern "C" unsigned char GPR_00554d00;
extern "C" unsigned char GPR_00554d04;
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
extern "C" unsigned char GPR_00554d1c;
extern "C" char text_igArenaMemoryPool_trim_E76_Arena[];
struct TrimArena { char p0[1992]; int top; char p1[24]; int *blocks; int capacity; int count; };
struct TrimPool { char p0[112]; TrimArena *arena; char p1[44]; long long locked; char p2[20]; int debug; };
extern "C" igResult igArenaMemoryPool_TrimArenaBlock(TrimPool *, int, int, int);
extern "C" bool igArenaMemoryPool_Trim(TrimPool *self, int pad);
/* The link pair sits at +4 or +12 depending on the top bit of the node's byte 3; `b7 == 0 ? 4 :
 * 12` gives the movn form. */
struct LinkByte { char pad[3]; unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; };
extern "C" void FUN_00315050(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3);
/* igMemoryPoolInfo's string getters, as the pools' configure functions read them: this build takes
 * the release set of the options, checking and messages strings. */
static inline const char *igMemoryPoolInfo_source(const igMemoryPoolInfo *info) { return (const char *)info->_source; }
static inline const char *igMemoryPoolInfo_options(const igMemoryPoolInfo *info) { return (const char *)info->_releaseOptions; }
static inline const char *igMemoryPoolInfo_checking(const igMemoryPoolInfo *info) { return (const char *)info->_releaseChecking; }
static inline const char *igMemoryPoolInfo_messages(const igMemoryPoolInfo *info) { return (const char *)info->_releaseMessages; }
struct CoreGlobals { char pad0[48]; igArenaMemoryPool *defaultPool; };
extern "C" char text_Sentinels[];
extern "C" char text_Contiguous[];
extern "C" char text_PreSizeReached[];
extern "C" char text_NoChecking[];
extern "C" char text_LightChecking[];
extern "C" char text_ModerateChecking[];
extern "C" char text_HeavyChecking[];
extern "C" igResult Gap__Core__igArenaMemoryPool__vfunc_45(igArenaMemoryPool *pool, igMemoryPoolInfo *info);
class Pool30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual igResult v136(int); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v204(); virtual void d50(); virtual void d51(); virtual int v216(int); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void v264(int); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
 char p4[112]; unsigned char f116; char p5[19]; long long f136; char p6[24]; int f168; char p7[20]; int f192; int f196; };
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_30(Pool30 *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_31(igArenaMemoryPool *self);
class Pool32 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); char pad[116-4]; unsigned char f116; };
extern "C" unsigned char Gap__Core__igArenaMemoryPool__vfunc_33(igArenaMemoryPool *self);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_26(igArenaMemoryPool *self);
struct ArenaState { char pad[2036]; int f2036; int pad2; int f2044; int f2048; int pad3; int f2056; };
class Pool24 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void v51();
    char pad0[105 - 4]; char f105; char pad1[6]; ArenaState *buf; unsigned char busy; char pad3[7]; int f124; char f128; char pad4[7]; long long f136; char pad5[16]; long long f160;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_24(int *out, Pool24 *p, int a2, long long a3, char t0);
extern "C" unsigned char Gap__Core__igArenaMemoryPool__vfunc_25(igArenaMemoryPool *self);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_34(int *ret, igArenaMemoryPool *p, int flag);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_36(igArenaMemoryPool *arg0);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_42(igArenaMemoryPool *self);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_44(igArenaMemoryPool *self);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_37(int *outStatus, igArenaMemoryPool *self, short alignment);
extern "C" unsigned short Gap__Core__igArenaMemoryPool__vfunc_38(igArenaMemoryPool *self);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_39(int *outStatus, igArenaMemoryPool *self, int elementSize);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_40(igArenaMemoryPool *self);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_47(igArenaMemoryPool *self);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_48(igArenaMemoryPool *self);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_49(igArenaMemoryPool *arg0);
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
    virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100();
    virtual igResult vfunc_103();
    virtual void *MemoryOperation(void *block, int size, unsigned int alignment);
    unsigned int _refCount;
    char _pad8[136];
    unsigned int _elementSize;
    char _pad148[24];
    unsigned short _alignment;
};
extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_53(igArenaMemoryPoolView *self);
extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_54(igArenaMemoryPoolView *self, unsigned int size);
extern "C" void *Gap__Core__igArenaMemoryPool__vfunc_55(igArenaMemoryPoolView *self, unsigned int size, unsigned int alignment);
class Pool56 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void *Alloc(int, int, int); };
struct ArenaPoolFlags { void *vt; char pad[168]; unsigned short align; char pad2[18]; unsigned flags; };
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
extern "C" unsigned char GPR_00554d64;
extern "C" unsigned char GPR_00554d68;
static inline void releaseRefObject(RefObject *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)((long long)object->references << 0x29) >> 0x29) == 0)
            igObject_Destroy(object);
    }
}
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
extern "C" char DAT_004fd670[];
extern "C" char DAT_004fd6d0[];
extern "C" char DAT_004fd730[];
extern "C" unsigned int DAT_00587208[4];
extern "C" unsigned int DAT_00587210[4];
extern "C" unsigned char GPR_00554d6c;
extern "C" unsigned char GPR_00554d70;
extern "C" unsigned char GPR_00554d74;
struct Arena98 { char pad[2020]; int f2020; int f2024; int f2028; int f2032; };
class Pool98 { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int v25(int); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual int v86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual igResult v100();
 char p4[20]; long long f24; char p32[24]; int f56; char p60[28]; long long f88; char p96[16]; Arena98 * f112; char p116[44]; long long f160; char p168[12]; int f180; char p184[4]; int f188; unsigned int f192;
};
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_98(Pool98 *arg0);
extern "C" void *FUN_0031eb90(igArenaMemoryPool *arg0);
extern "C" void *FUN_0031ebd0(igArenaMemoryPool *arg0, int extra1);
extern "C" void *FUN_0031ec20(igArenaMemoryPool *arg0, int extra1);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_66(igArenaMemoryPoolView *self, void *block);
struct Header85 { unsigned sz:24; unsigned idx:5; unsigned mid:2; unsigned big:1; unsigned pad4; unsigned rest:12; unsigned ext:12; unsigned top:8; };
struct Header84 { unsigned lo:5; unsigned sz:19; unsigned mid:7; unsigned big:1; unsigned pad4; unsigned ext:12; unsigned rest:20; };
extern "C" char DAT_004fd7a0[];
extern "C" unsigned char GPR_00554d78;
class SetFlagsPool { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();  virtual int vX(int);
 char pad[184]; int cnt; int flags; };
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(SetFlagsPool *p, int f);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_90(int *arg0, igObject *arg1);
typedef struct Header93 { char p0[3]; unsigned char lo : 5; unsigned char mid : 2; unsigned char flag : 1; char p1[4]; unsigned int pad : 12; unsigned int ext : 12; unsigned int rest : 8; } Header93;
typedef struct TagByte93 { unsigned char b : 7; unsigned char flag : 1; } TagByte93;
typedef struct Pool93 { char p[180]; int f180; inline int Chk(int y) { if (f180 < 64 && y >= 64) return 0; return 1; } } Pool93;
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_93(int *arg0, Pool93 *arg1, char *arg2, igMemoryPoolView *arg3);
struct Header95 { char pad[3]; unsigned char sz:5; unsigned char mid:2; unsigned char big:1; char pad2[4]; unsigned int u0:12; unsigned int ext:12; unsigned int u1:8; };
struct Arena03 { char pad[2020]; void *f7e4; int f7e8; int f7ec; int f7f0; char pad2[24]; int f80c; int f810; };
struct Pool03 { char pad[112]; Arena03 *f70; };
extern "C" unsigned char GPR_00554d7c;
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_03(Pool03 *arg0, int arg1);
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
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_04(igArenaMemoryPool *self);
extern "C" int g_poolOptionFlagsDefault_004c2370[4];
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_13(igArenaMemoryPool *self, int extra1);
extern "C" unsigned int Gap__Core__igArenaMemoryPool__vfunc_105(igArenaMemoryPool *arg0, int arg1, int arg2);
extern "C" igResult Gap__Core__igArenaMemoryPool__vfunc_106(void *arg1, int arg2, long long arg3);
class igArenaMemoryPoolView;
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_107(igArenaMemoryPoolView *self);
extern "C" static void FUN_00320930(unsigned char *arg0);
extern "C" static void FUN_00320960(unsigned char *arg0);
extern "C" void Gap__Core__igElfFile__vfunc_23(igElfFile *arg0);
extern "C" char DAT_004fdda0[];
extern "C" int DAT_004fddc0[4];
extern "C" int DAT_004fdde0[4];
extern "C" char GPR_005549b4;
/* igProgramFile (reflected.h) with its own virtuals: slot 21 is vfunc_23, Reset() (drops the name
 * and the stream); 22 is vfunc_24, Open(path); 23 is vfunc_25, Close(); 24 is vfunc_26,
 * Load(offset, size, dest). */
class ProgramFileView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void Reset();
    virtual igResult Open(const char *path);
    virtual igResult Close();
    virtual igResult Load(int offset, int size, void **dest);
    unsigned int refCount; const char *path; igFileView *stream;
};
/* One section header of the ELF file (Elf32_Shdr): type 3 is a string table. */
struct ElfSection { int name; int type; int flags; int addr; int offset; int size; int link; int info; int addressAlign; int entrySize; };
/* igElfFile (reflected.h, an igProgramFile) with its 52-byte ELF header (Elf32_Ehdr) at +16 spelled out. */
class ElfFileView : public ProgramFileView {
public:
    unsigned char magic[4], elfClass, endian, identVersion; char pad23[9];
    unsigned short type, machine; int version; int entry; int programHeaderOffset;
    int sectionHeaderOffset; int flags;
    unsigned short headerSize, programHeaderEntrySize, programHeaderCount;
    unsigned short sectionHeaderEntrySize, sectionHeaderCount, sectionNameIndex;
    int sectionNamesSize; void *sectionNames; int sectionCount; void *sectionHeaders;
    int stringsSize; void *strings; int symbolCount; void *symbols;
};
extern "C" void Gap__Core__igElfFile__vfunc_24(int *result, ElfFileView *self, const char *path);
extern "C" ElfSection *FUN_00320ea0(ElfFileView *self, int index);
extern "C" int FUN_00320ee0(ElfFileView *self, int type, int nth);
struct ElfResult { int w; ElfResult() {} ElfResult(const ElfResult &o) : w(o.w) {} bool operator==(const ElfResult &o) const { return w == o.w; } };
extern "C" char DAT_004fde00[];
extern "C" char DAT_004fde20[];
extern "C" ElfResult Gap__Core__igElfFile__vfunc_27(ElfFileView *self);
class ElfSymbolSink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void Add(const char *name, void *value, unsigned size, int flags); };
class ElfSymbolFileView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual ElfResult Close(); virtual ElfResult Load(int offset, int size, void *dest); virtual ElfResult LoadSymbols(); virtual void d26(); virtual ElfResult ReadString(int offset, char *text, int limit, int flags);
    char pad0[4]; int path; char pad12[76]; char *strings; int symbolCount; };
extern "C" char text_No_symbols_in_s[];
extern "C" ElfResult Gap__Core__igElfFile__vfunc_28(ElfSymbolFileView *self, ElfSymbolSink *sink, int functionsOnly);
typedef struct ElfOperatorName { const char *mangled; const char *name; } ElfOperatorName;
extern "C" ElfOperatorName DAT_004c2380[];
extern "C" char DAT_004fdf80[];
extern "C" char DAT_004fde68[];
extern "C" char DAT_004fde70[];
extern "C" char DAT_004fe080[];
extern "C" char DAT_004fe088[];
extern "C" int DAT_004c23f0[4];
extern "C" int DAT_004c2410[4];
extern "C" int DAT_004c2430[4];
extern "C" int DAT_004c2470[4];
extern "C" char DAT_004fe090[];
extern "C" char DAT_004fe0b0[];
extern "C" char DAT_004fe0d0[];
extern "C" char DAT_004fe0f0[];
extern "C" char DAT_004fe110[];
extern "C" char DAT_004fe130[];
extern "C" char DAT_004fe150[];
extern "C" char DAT_004fe170[];
extern "C" char DAT_004fe190[];
extern "C" char DAT_004fe1b0[];
extern "C" char DAT_004fe1d0[];
extern "C" char DAT_004fe1f0[];
extern "C" char DAT_004fe210[];
extern "C" char DAT_004fe230[];
extern "C" char DAT_004fe250[];
extern "C" char DAT_004fe270[];
extern "C" char DAT_004fe290[];
extern "C" char DAT_004fe2b0[];
extern "C" char DAT_004fe2d0[];
extern "C" char DAT_004fe2f0[];
extern "C" char DAT_004fe310[];
extern "C" char DAT_004fe330[];
extern "C" char DAT_004fe350[];
extern "C" void Gap__Core__igElfFile__vfunc_30(ElfFileView *o);
extern "C" char DAT_004fe370[];
extern "C" int DAT_004c24c0[4];
extern "C" int DAT_004c2550[4];
extern "C" char DAT_004fe4d0[];
extern "C" char DAT_004fe4f0[];
extern "C" char DAT_004fe520[];
extern "C" char DAT_004fe540[];
extern "C" char DAT_004fe570[];
extern "C" char DAT_004fe5a0[];
extern "C" char DAT_004fe5d0[];
extern "C" char DAT_004fe600[];
extern "C" char DAT_004fe630[];
extern "C" char DAT_004fe660[];
extern "C" char DAT_004fe690[];
extern "C" void FUN_00322040(ElfFileView *arg0, int arg1, ElfSection *arg2);
extern "C" char DAT_004fe6c0[];
extern "C" void Gap__Core__igElfFile__vfunc_32(ElfFileView *arg0);
extern "C" char DAT_004c2580[];
extern "C" char DAT_004c25b0[];
extern "C" char DAT_004fe7a0[];
extern "C" char DAT_004fe7c0[];
extern "C" char DAT_004fe7f0[];
extern "C" char DAT_004fe820[];
extern "C" char DAT_004fe850[];
extern "C" char DAT_004fe880[];
extern "C" char DAT_004fe8b0[];
extern "C" char DAT_004fe8e0[];
extern "C" char DAT_004fe910[];
extern "C" void FUN_00322240(igElfFile *arg0, int arg1, unsigned char *arg2);
extern "C" int text_NoMessages[4];
extern "C" int text_ErrorMessages[4];
extern "C" int text_WarningMessages[4];
extern "C" int text_Notifications[4];
extern "C" igResult Gap__Core__igMallocMemoryPool__vfunc_45(igMallocMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_30(igMallocMemoryPool *self);
class igSemaphoreView;
class igMallocMemoryPoolView;
extern "C" igResult Gap__Core__igMallocMemoryPool__vfunc_34(igMallocMemoryPoolView *arg1, unsigned char arg2);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_35(int *outStatus, igMallocMemoryPool *self, long long size);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_36(igMallocMemoryPool *self);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_41(int *status, igMallocMemoryPool *self, long long maxSize);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_42(igMallocMemoryPool *self);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_37(int *outStatus, igMallocMemoryPool *self, short alignment);
extern "C" unsigned short Gap__Core__igMallocMemoryPool__vfunc_38(igMallocMemoryPool *self);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_39(int *status, igMallocMemoryPool *self, int elementSize);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_40(igMallocMemoryPool *self);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_46(igMallocMemoryPool *arg0);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_47(igMallocMemoryPool *self);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_48(igMallocMemoryPool *self);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_49(igMallocMemoryPool *arg0);
/* igMallocMemoryPool appends slot 99 (vfunc_101, byte 404) to the igMemoryPool table: the
 * reallocation core behind allocate, reallocate and free. vfunc_57 calls it with only the block and
 * size (a3 is left as it was), so the trailing alignment is spelled variadic. */
class igMallocMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97(); virtual void d98();
    virtual void *vfunc_101(void *block, unsigned int size, ...);
    unsigned int _refCount;
    char _pad8[108];
    igSmartPointer<igSemaphoreView> _allocationLock;
    int _poolIndex;
    unsigned int _elementSize;
    char _pad128[16];
    unsigned short _alignment;
};
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_53(igMallocMemoryPoolView *self);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_54(igMallocMemoryPoolView *self, unsigned int size);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_55(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_56(igMallocMemoryPool *self, int count, int size);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_57(igMallocMemoryPool *arg0, int arg1, int arg2);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_58(igMallocMemoryPoolView *self, void *block, unsigned int size);
extern "C" void *Gap__Core__igMallocMemoryPool__vfunc_59(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment);
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
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_64(MallocPoolFreeView *self, unsigned int size, char **block);
extern "C" int g_poolOptionFlagsDefault_004c25f8[4];
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_13(igMallocMemoryPool *self, int extra1);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_97(igMallocMemoryPool *self);
extern "C" void *FUN_003235c0(igMallocMemoryPool *arg0);
extern "C" void *FUN_00323600(igMallocMemoryPool *arg0, int extra1);
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
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_02(igMallocMemoryPool *self);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_66(igMallocMemoryPoolView *self, void *block);
class Pool87 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual long long Used(); int f4; unsigned long long s8, s16, s24, s32, s40, s48, s56, s64, s72, s80, s88, s96; char pad[48]; int name; };
extern "C" char DAT_004fef30[];
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_87(Pool87 *self, char *title);
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_90(igMallocMemoryPool *self, igObject *tracker);
extern "C" int DAT_004ff1b0[4];
extern "C" char DAT_004ff1f0[];
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_93(int *arg0, igMallocMemoryPool *arg1, char *arg2, igMemoryPoolView *arg3);
extern "C" unsigned char Gap__Core__igMallocMemoryPool__vfunc_33(igMallocMemoryPool *self);
struct TaggedBlockHeader {
    unsigned char used : 1;
    unsigned char words : 4;
    unsigned size : 19;
    unsigned char poolLow : 5;
    unsigned char marked : 1;
    unsigned char relocated : 1;
    unsigned char big : 1;
    int previous;
    unsigned short sizeHigh : 12;
    unsigned poolHigh : 12;
    unsigned char extraUsed : 1;
    unsigned char extraMarked : 1;
    unsigned char extraTag : 5;
    unsigned char extraBig : 1;
};
class TaggedPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int GetPoolIndex(); char pad4[116]; unsigned index; char pad124[32]; unsigned flags; };
extern "C" void *FUN_00324be0(TaggedPool *self, unsigned size);
extern "C" void FUN_00324ec0(TaggedPool *self, unsigned char *p);
class TaggedReallocHeap { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void *Reallocate(void *block, unsigned size, unsigned old); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void *ReallocateSized(void *block, unsigned size, unsigned old); virtual void d11(); virtual void d12(); virtual void *ReallocateAligned(void *block, unsigned size, unsigned old); };
struct TaggedTailByte { unsigned char low : 7; unsigned char extended : 1; };
extern "C" void *FUN_00325060(TaggedPool *self, char *p, unsigned size);
class TaggedAlignedPool { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual int GetPoolIndex(); char pad4[116]; unsigned index; char pad124[20]; unsigned short minAlignment; char pad146[10]; unsigned flags; };
extern "C" void *FUN_003254a0(TaggedAlignedPool *self, unsigned alignment, unsigned size);
extern "C" void *FUN_003257d0(igPageMemoryPool *arg0);
extern "C" void *FUN_00325810(igPageMemoryPool *arg0, int extra1);
extern "C" int DAT_004fc120[4];
extern "C" int g_igPageMemoryPool_defaultPoolOptionFlags[4];
extern "C" int text_Fill[4];
extern "C" int text_Zero[4];
extern "C" int text_AutoLock[4];
extern "C" int text_SystemMemoryExhausted[4];
extern "C" int text_MaxSizeReached[4];
extern "C" int text_Physical[4];
extern "C" char DAT_004ff240[];
extern "C" char DAT_004ff2a0[];
extern "C" int text_igPageMemoryPool_getBlockSize_Sh[4];
extern "C" unsigned char GPR_00554dc0;
extern "C" unsigned char GPR_00554dc4;
extern "C" unsigned char GPR_00554dd8;
extern "C" void Gap__Core__igPageMemoryPool__vfunc_04(igPageMemoryPoolView *self);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_13(igPageMemoryPool *self, int extra1);
extern "C" igResult Gap__Core__igPageMemoryPool__vfunc_45(igPageMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_30(igPageMemoryPool *self);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_32(igPageMemoryPool *self);
extern "C" unsigned char Gap__Core__igPageMemoryPool__vfunc_33(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_26(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_25(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_29(igPageMemoryPool *self);
extern "C" igResult Gap__Core__igPageMemoryPool__vfunc_34(igPageMemoryPoolView *arg1, int arg2);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_36(igPageMemoryPool *self);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_41(int *status, igPageMemoryPool *self, long long maxSize);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_42(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_38(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_40(igPageMemoryPool *self);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *arg0);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_47(igPageMemoryPool *self);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_48(igPageMemoryPool *self);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_49(igPageMemoryPool *arg0);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_53(igPageMemoryPool *self);
/* igPageMemoryPool (reflected.h) with its own slots after the igMemoryPool table (slot 100 is
 * vfunc_102, 101 and 102 test and set page-table bits, 103 is vfunc_105,
 * igPageMemoryPool_GetBlockSize) and the page tables in its last 128 bytes spelled out: table t
 * covers addresses t << 27, and each of its 2048 words holds the 2-bit states of 16 4KB pages.
 * vfunc_57 calls slot 100 with only the block and size, so the alignment is spelled variadic. */
class igPageMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97(); virtual void d98(); virtual void d99();
    virtual void *MemoryOperation(void *block, int size, ...);
    virtual int vfunc_103(void *block);
    virtual void vfunc_104(unsigned int address, int size, int set);
    virtual unsigned GetBlockSize(void *block);
    unsigned int refCount; char pad8[108]; igSmartPointer<igSemaphoreView> allocationLock; char pad120[16];
    int messageLevel; int poolOptionFlags; unsigned *pageTables[32];
};
extern "C" void *Gap__Core__igPageMemoryPool__vfunc_54(igPageMemoryPoolView *self, unsigned int size);
extern "C" void *Gap__Core__igPageMemoryPool__vfunc_55(igPageMemoryPoolView *self, unsigned int size, unsigned int alignment);
extern "C" void *Gap__Core__igPageMemoryPool__vfunc_56(igPageMemoryPool *self, int count, int size);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_57(igPageMemoryPool *self, int n, int sz);
extern "C" void *Gap__Core__igPageMemoryPool__vfunc_58(igPageMemoryPoolView *self, void *block, unsigned int size);
extern "C" void *Gap__Core__igPageMemoryPool__vfunc_59(igPageMemoryPoolView *self, void *block, int size, unsigned int alignment);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_66(igPageMemoryPoolView *self, void *block);
extern "C" unsigned int Gap__Core__igPageMemoryPool__vfunc_85(igPageMemoryPoolView *self, void *block);
extern "C" unsigned int Gap__Core__igPageMemoryPool__vfunc_84(igPageMemoryPoolView *self, void *block);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_90(igPageMemoryPool *self, igObject *tracker);
extern "C" void FUN_003269d0(igPageMemoryPoolView *arg0, int arg1, int arg2);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_103(igPageMemoryPoolView *self, unsigned int arg1);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_104(igPageMemoryPoolView *self, unsigned int a, int n, int set);
extern "C" unsigned igPageMemoryPool_GetBlockSize(igPageMemoryPoolView *self, void *block);
extern "C" void Gap__Core__igPageMemoryPool__vfunc_88(igPageMemoryPoolView *self);
extern "C" int DAT_004ff4f0[4];
extern "C" char DAT_004ff510[];
extern "C" char DAT_004ff540[];
extern "C" void Gap__Core__igProgramFile__vfunc_23(igProgramFile *arg0);
extern "C" igResult Gap__Core__igProgramFile__vfunc_24(igProgramFile *self, const char *path);
extern "C" void Gap__Core__igProgramFile__vfunc_26(int *result, ProgramFileView *self, int offset, int size, void **dest);
extern "C" void Gap__Core__igProgramFile__vfunc_30(igProgramFile *self);
extern "C" void Gap__Core__igProgramFile__vfunc_31(igProgramFile *self);
extern "C" void Gap__Core__igProgramFile__vfunc_32(igProgramFile *self);
extern "C" char text_Pool_igStackMemoryPool[];
extern "C" void Gap__Core__igStackMemoryPool__vfunc_30(igStackMemoryPool *p);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_31(igStackMemoryPool *s);
/* Disable step of the stack pool: run virtual slot 124 (vfunc_31, which copies +116 to +132 and
 * recomputes +136 as the 4-byte-aligned end: +132 plus the 64-bit size at +120, less 4), then
 * clear _isActive. The alias pool has the same pair: its slot 128 calls the receiver's slot 124
 * and then clears the active byte. */
/* ABI dispatch view of virtual slot 124 (29 leading virtuals); never instantiated. */
class StackPoolSlot124View { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void Reset();
};
extern "C" void Gap__Core__igStackMemoryPool__vfunc_32(igStackMemoryPool *self);
extern "C" unsigned char Gap__Core__igStackMemoryPool__vfunc_33(igStackMemoryPool *self);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_36(igStackMemoryPool *self);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_37(int *status, igStackMemoryPool *self, short alignment);
extern "C" unsigned short Gap__Core__igStackMemoryPool__vfunc_38(igStackMemoryPool *self);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_39(int *status, igStackMemoryPool *self, int elementSize);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_40(igStackMemoryPool *self);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_26(igStackMemoryPool *self);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_42(igStackMemoryPool *self);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0);
/* The stack pool records each block's size in a word pushed down from _nextInt; the top bit marks
 * a freed block. */
struct StackBlockRecord { unsigned size : 31; unsigned freed : 1; };
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_47(igStackMemoryPool *arg0);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_48(igStackMemoryPool *arg0);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_49(igStackMemoryPool *arg0);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_53(igStackMemoryPool *arg0);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_54(igStackMemoryPool *arg0, int arg1);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_55(igStackMemoryPool *arg0, int size, unsigned short arg2);
extern "C" void *Gap__Core__igStackMemoryPool__vfunc_56(igStackMemoryPool *s, int count, int size);
extern "C" void *Gap__Core__igStackMemoryPool__vfunc_57(igStackMemoryPool *s, int count, int size, unsigned short a);
typedef struct StackPoolFields {
    char pad0[112];
    unsigned short alignment;
    char pad1[18];
    unsigned top;
    unsigned *end;
} StackPoolFields;
extern "C" void Gap__Core__igStackMemoryPool__vfunc_62(int *result, StackPoolFields *pool, unsigned short count, unsigned *sizes, unsigned *out);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_63(int *result, StackPoolFields *pool, unsigned short count, unsigned *sizes, unsigned *out, unsigned short *aligns);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_84(igStackMemoryPool *arg0, unsigned int arg1);
extern "C" bool Gap__Core__igStackMemoryPool__vfunc_85(igStackMemoryPool *s, unsigned a);
typedef struct Stack64 { char pad[116]; unsigned base; char pad2[12]; unsigned top; unsigned *end; } Stack64;
extern "C" void Gap__Core__igStackMemoryPool__vfunc_64(Stack64 *self, unsigned count, unsigned *ptrs);
class Stack66 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int Owns(); char pad[112]; unsigned base; char pad2[12]; unsigned top; unsigned *end; };
extern "C" void Gap__Core__igStackMemoryPool__vfunc_66(Stack66 *self, unsigned size);
extern "C" void Gap__Core__igStackMemoryPool__vfunc_90(igStackMemoryPool *arg0, igObject *arg1);
extern "C" void Gap__Core__igStandardQueue__vfunc_11(igStandardQueueView *self);
extern "C" void Gap__Core__igStandardQueue__vfunc_23(igStandardQueue *self);
extern "C" void Gap__Core__igStandardQueue__vfunc_24(igStandardQueue *self);
extern "C" int Gap__Core__igStandardQueue__vfunc_25(igStandardQueue *self);
/* The semaphore interface of igPsx2Semaphore (slot N is the class's vfunc_(N + 2)). */
class igSemaphoreView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igResult create();
    virtual igResult destroy();
    virtual int isCreated();
    virtual igResult setInitialCount(int count);
    virtual int getInitialCount();
    virtual igResult setMaximumCount(int count);
    virtual int getMaximumCount();
    virtual int getCount();
    virtual igResult signal();
    virtual igResult iSignal();
    virtual igResult wait(int block);
};
struct ScopedLock {
    igSemaphoreView *lockable;
    ScopedLock(igSemaphoreView *l) : lockable(l) {
        igSemaphoreView *o = lockable;
        if (o != 0) { o->wait(1); }
    }
    ~ScopedLock() {
        igSemaphoreView *o = lockable;
        if (o != 0) { o->signal(); }
    }
};
struct EventTrackerScopedLock {
    igSemaphoreView *l;
    EventTrackerScopedLock(igSemaphoreView *m) { l = m; if (l != 0) { l->wait(1); } }
    ~EventTrackerScopedLock() { if (l != 0) { l->signal(); } }
};
class igPsx2ThreadView;
/* igPsx2ThreadManager: slot 21 finds the calling thread, slots 22 and 23 add and remove a thread. */
class igPsx2ThreadManagerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igPsx2ThreadView *getCurrentThread();
    virtual void addThread(igPsx2ThreadView *thread);
    virtual void removeThread(igPsx2ThreadView *thread);
    unsigned int _refCount;
    igTDataList<igPsx2ThreadView *> *_threadList;
    igSemaphoreView *_sema;
};
/* igPsx2Thread with the virtuals its callers use: slot 22 waits for another thread to finish, 23
 * sleeps for a number of nanoseconds, 30 tells whether the thread is running, 40 gives the stack
 * alignment and 42 terminates the thread. */
class igPsx2ThreadView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual igResult join(igPsx2ThreadView *thread);
    virtual igResult sleep(int nanoseconds);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual igResult start();
    virtual void d29();
    virtual int isRunning();
    virtual igResult setFunction(int (*function)(...));
    virtual void d32();
    virtual igResult setArg(int arg);
    virtual void d34(); virtual void d35(); virtual void d36();
    virtual igResult setStackSize(unsigned int stackSize);
    virtual void d38();
    virtual void d39();
    virtual int getStackAlignment();
    virtual void d41();
    virtual igResult terminate();
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void d51(); virtual void d52();
    virtual void adoptCurrentThread();
    int _name;
    int _type;
    int _scope;
    int _state;
    int _priority;
    int _arg;
    int _stack;
    unsigned int _stackSize;
    int _function;
    unsigned char _isMaster;
    unsigned char _userStack;
    char _pad46[2];
    igSemaphoreView *_threadDoneSema;
    int _result;
    unsigned char _isDeferred;
    unsigned char _stopRequested;
    unsigned char _atStoppingPoint;
    char _pad59[1];
    int _threadID;
};
/* igStandardQueue with the virtuals its callers use: slots 21 to 23 create, destroy and test the
 * element storage, 26 counts the queued elements and 27 tells whether the queue is full. */
class igStandardQueueView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void create();
    virtual void destroy();
    virtual int isCreated();
    virtual igResult insert(int value, int block);
    virtual void d25();
    virtual unsigned int getCount();
    virtual int isFull();
    int _serviceThreads;
    igSemaphoreView *_insertLock;
    igSemaphoreView *_removeLock;
    igSemaphoreView *_queueSema;
    unsigned int _capacity;
    unsigned int _insertElement;
    unsigned int _removeElement;
    int *_data;
    unsigned int _maxCapacity;
};
extern "C" igResult Gap__Core__igStandardQueue__vfunc_26(igStandardQueueView *self, int val, int block);
extern "C" int Gap__Core__igStandardQueue__vfunc_29(igStandardQueueView *self);
extern "C" igResult Gap__Core__igStandardQueue__vfunc_27(igStandardQueueView *self, int *out, int block);
extern "C" int Gap__Core__igStandardQueue__vfunc_28(igStandardQueueView *self);
extern "C" void FUN_00328ab0(igStandardQueueView *queue, int capacity);
extern "C" igResult Gap__Core__igStandardQueue__vfunc_30(igStandardQueueView *self, unsigned n);
extern "C" int Gap__Core__igStandardQueue__vfunc_31(igStandardQueue *self);
extern "C" void Gap__Core__igStandardQueue__vfunc_32(int *out, igStandardQueueView *self, unsigned a);
extern "C" int Gap__Core__igStandardQueue__vfunc_33(igStandardQueue *self);
extern "C" int g_vtable[4];
/* Pages counted by state (the two-bit page-table values the memory map prints as "Heap: Unknown",
 * "Free", "Blocked" and "Allocated"). */
struct PageStateCounts { int unknown; int available; int blocked; int allocated; };
struct DumpResult { int w; DumpResult() {} DumpResult(const DumpResult &o) : w(o.w) {} };
/* One row of the memory map: a region's first address and size, its annotation and its pool name.
 * Rows are allocated from the non-tracked pool (FUN_0032a1e0), zeroed (FUN_0032a100) and freed
 * (FUN_0032a130 -> FUN_0032a220). */
struct DumpRegion { unsigned start; unsigned size; char annotation[80]; char poolName[80]; };
/* igEventTracker (reflected.h) with the virtual functions the memory map dump calls. */
class EventTrackerDump : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void Begin(); virtual void End(); virtual void d23(); virtual void Add(void *entry, int flags); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual DumpResult Write(char *path);
    int _lock; int _flags; unsigned int _eventTypeFilterFlags; unsigned int _memoryFieldFilterFlags; };
class DumpOwner { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void Describe(char *text); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void CollectA(igPointerList *list); virtual void CollectB(igPointerList *list); virtual void CollectC(igPointerList *list); virtual void CollectD(igPointerList *list); };
extern "C" void FUN_002d6680(igPointerList *, int, int);
extern "C" int g_vtable[4];
extern "C" int DAT_00587220[64];
extern "C" int DAT_00587328[4];
extern "C" char DAT_004ff590[];
extern "C" unsigned int g_rangeStart[4];
extern "C" unsigned int g_rangeEnd[4];
extern "C" int DAT_004ff5c0[4];
extern "C" char DAT_004ff5c8[];
extern "C" char DAT_004ff5e0[];
extern "C" char DAT_004ff600[];
extern "C" char DAT_004ff630[];
extern "C" char DAT_004ff660[];
extern "C" char DAT_004ff690[];
extern "C" char DAT_004ff6c0[];
extern "C" char DAT_004ff6f0[];
extern "C" char DAT_004ff720[];
extern "C" char DAT_004ff750[];
extern "C" char DAT_004ff780[];
extern "C" char DAT_004ff7b0[];
extern "C" char DAT_004ff7e0[];
extern "C" char DAT_004ff810[];
extern "C" char DAT_004ff840[];
extern "C" char DAT_004ff870[];
extern "C" char DAT_004ff8a0[];
extern "C" char DAT_004ff8d0[];
extern "C" char DAT_004ff900[];
extern "C" char DAT_004ff930[];
extern "C" char DAT_004ff960[];
extern "C" char DAT_004ff990[];
extern "C" char DAT_004ff9c0[];
extern "C" char text_Memory_Map[];
extern "C" char DAT_004ffa00[];
extern "C" char DAT_004ffa10[];
extern "C" char text_Start[];
extern "C" char text_End[];
extern "C" char text_Size[];
extern "C" char text_Pool_Name[];
extern "C" char text_Annotation[];
extern "C" char DAT_004ffa60[];
extern "C" char text_Section_Code[];
extern "C" char text_Program[];
extern "C" char text_Section_Data[];
extern "C" char text_Section_Initialized_Data[];
extern "C" char text_Section_Uninitialized_Data[];
extern "C" char text_Section_Stack_Data[];
extern "C" char text_Heap_Unknown[];
extern "C" char text_SystemHeap[];
extern "C" char text_Heap_Free[];
extern "C" char text_Heap_Blocked[];
extern "C" char text_Heap_Allocated[];
extern "C" char text_Heap_Free_from_top[];
extern "C" void FUN_00329010(SystemAllocator *self, unsigned int size);
extern "C" void FUN_00329170(SystemAllocator *self, unsigned int size);
extern "C" void FUN_00329180(SystemAllocator *self, void *block, int size);
extern "C" void FUN_00329190(SystemAllocator *self, void *block, unsigned int size, unsigned int old);
extern "C" void FUN_003291a0(SystemAllocator *self, int n);
extern "C" unsigned FUN_00329280(SystemAllocator *self, unsigned a, int n);
extern "C" igResult FUN_00329460(SystemAllocator *self, int arg2, int arg3);
extern "C" int FUN_00329540(SystemAllocator *self);
extern "C" int FUN_00329590(igPsx2CallStackTracer *self);
extern "C" igObject *FUN_00328e00(igObject *self, long long deleteFlags);
extern "C" int FUN_003295a0(igPsx2CallStackTracer *self);
extern "C" void FUN_003295d0(SystemAllocator *self, int *out);
extern "C" int FUN_003296d0(igPsx2CallStackTracer *self);
extern "C" igResult FUN_003296e0(SystemAllocator *self, int state, unsigned int addr, int len);
extern "C" void FUN_00329b60(SystemAllocator *self);
extern "C" void FUN_00329e70(SystemAllocator *self);
extern "C" DumpRegion *FUN_0032a100(DumpRegion *row);
extern "C" DumpRegion *FUN_0032a1e0(int size);
extern "C" void FUN_0032a280(DumpOwner *self, char *title, char *path, int a, int b, int c, int d);
extern "C" void FUN_0032a600(SystemAllocator *self, int arg1);
extern "C" void FUN_0032a900(SystemAllocator *self, int arg1);
extern "C" void *FUN_0032ac40(SystemAllocator *self, unsigned int size);
extern "C" void FUN_0032ac50(SystemAllocator *self, void *block);
extern "C" int DAT_004c2618[4];
extern "C" int DAT_004c2620;
extern "C" int Gap__Core__igPsx2CallStackTracer__vfunc_24(igCallStackTracerView *tracer);
extern "C" unsigned int *Gap__Core__igPsx2CallStackTracer__vfunc_31(igCallStackTracerView *tracer);
/* igPsx2File: a file opened through the IOP file system (sceOpen); a text file is held whole in _fBuf. */
class igPsx2FileView : public igFileView {
public:
    unsigned char *_fBuf;
    int _bufSize;
    int _bufPos;
    int _fileSize;
    int _isBinary;
    int _isOpen;
    int _stringFile;
    char *_prefix;
};
extern "C" void Gap__Core__igPsx2File__vfunc_26(igPsx2FileView *self);
extern "C" void Gap__Core__igPsx2File__vfunc_23(int *result, igPsx2FileView *file, unsigned int mode);
extern "C" void FUN_0032b5b0(igPsx2FileView *arg0, int arg1);
extern "C" int Gap__Core__igPsx2File__vfunc_27(igPsx2FileView *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igPsx2File__vfunc_29(igPsx2FileView *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igPsx2File__vfunc_32(igPsx2FileView *arg0);
extern "C" int Gap__Core__igPsx2File__vfunc_31(igPsx2FileView *arg0, int arg1, ...);
extern "C" int Gap__Core__igPsx2File__vfunc_33(igPsx2FileView *arg0);
extern "C" int Gap__Core__igPsx2File__vfunc_34(igPsx2FileView *arg0, int arg1);
extern "C" int Gap__Core__igPsx2File__vfunc_35(igPsx2FileView *arg0, unsigned char arg1);
extern "C" char *Gap__Core__igPsx2File__vfunc_36(igPsx2FileView *arg0, char *arg1, int arg2);
extern "C" int Gap__Core__igPsx2File__vfunc_37(igPsx2FileView *arg0, char *arg1);
extern "C" int Gap__Core__igPsx2File__vfunc_39(igPsx2File *arg0);
extern "C" char text_cdrom0[];
extern "C" int text_host0[4];
extern "C" int DAT_00587338[4];
extern "C" int DAT_00587330[4];
extern "C" int *Gap__Core__igPsx2File__vfunc_41(igPsx2File *self, int arg1);
struct Text : public igObject { char *chars; int length; };
extern "C" char DAT_004ffbe8[];
extern "C" char DAT_004ffbf0[];
/* A string interned in the global string pool, held by reference count. */
struct InternedString {
    char *p;
    InternedString(char *chars) {
        char *interned;
        if (chars == 0) {
            interned = 0;
        } else {
            if (g_stringPool[0] == 0) {
                int pool = ((int)StringPool_Allocate(16));
                if (pool != 0) {
                    pool = ((int)StringPool_Construct((StringPool *)pool));
                }
                g_stringPool[0] = pool;
            }
            interned = ((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)chars));
        }
        p = interned;
    }
    InternedString(const InternedString &other) : p(other.p) {
        if (p != 0) {
            ((int *)p)[-1] = ((int *)p)[-1] + 1;
        }
    }
    ~InternedString() {
        char *chars = p;
        if (chars != 0) {
            int *header = (int *)chars - 2;
            int left = header[1] - 1;
            header[1] = left;
            if (left == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)header[0], (int)header);
            }
        }
    }
};
extern "C" InternedString FUN_0032c240(char *prefix, char *path);
struct FolderSelf { int vt; int refCount; int path; };
struct FolderFileStat { int mode; char rest[60]; };
extern "C" int sceGetstat(const char *, FolderFileStat *);
extern "C" igSmartPointer<igObject> Gap__Core__igPsx2Folder__vfunc_24(FolderSelf *self);
extern "C" igSmartPointer<igObject> Gap__Core__igPsx2Folder__vfunc_25(FolderSelf *self);
struct FolderEntryWide { char bytes[328]; };
extern "C" igSmartPointer<igObject> Gap__Core__igPsx2Folder__vfunc_26(FolderSelf *self);
extern "C" void FUN_0032cac0(igStringObj *arg0);
class FolderAllocator { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *Allocate(int); };
struct FolderSearchList;
extern "C" char text_sonyModulePath[];
extern "C" char text_intrinsicModulePath[];
extern "C" char text_MODULES_s[];
extern "C" char text_usr_local_sce_iop_modules[];
extern "C" char text_c_usr_local_sce_iop_modules[];
extern "C" char text_c_cygwin_usr_local_sce_iop_modul[];
extern "C" char text_usr_local_Alchemy_iop_modules[];
extern "C" char text_c_Alchemy_iop_modules[];
extern "C" int DAT_00587340[16];
extern "C" int DAT_00587348[16];
extern "C" int DAT_004c2628[16];
extern "C" unsigned char DAT_005549b8;
extern "C" int DAT_004f9c50[4];
extern "C" int text_useOutputFilesForAtmon[4];
extern "C" char text_stdout_txt[];
extern "C" char text_stderr_txt[];
extern "C" int DAT_00587358[4];
extern "C" int text_atfile[4];
/* The EE side of a SIF RPC client (sceSifClientData in dw4/sony/sif.h, which cannot be included
 * beside this header's variadic sceSif declarations); serve is set once the IOP server is bound. */
struct SifClientData { void *paddr; unsigned int pid; int tid; unsigned int mode; unsigned int command; void *buff; void *gp; void *func; void *para; void *serve; };
/* igPsx2IopRpcConnection: a bound SIF RPC client, its transfer memory and the semaphore that
 * serialises calls. */
struct igPsx2IopRpcConnectionView : public igObject { SifClientData *_sifData; char *_dataMemory; int _sema; };
extern "C" void Gap__Core__igPsx2IopRpcConnection__vfunc_12(igPsx2IopRpcConnectionView *arg0);
extern "C" void FUN_0032d640(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2);
extern "C" int FUN_0032d6d0(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
extern "C" int FUN_0032d850(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int *arg4, int arg5);
extern "C" void FUN_0032d9b0(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3);
extern "C" unsigned char GPR_00554ddc;
typedef struct MediaRpcShared { char pad[8]; char *buffer; } MediaRpcShared;
typedef struct MediaRpcCompletion {
    char pad[12];
    int kind;
    union {
        struct { int headSize; int tailSize; char *head; char *tail; } read;
        struct { void (*callback)(int, int); int thread; int value; int *slot; } wait;
    } u;
} MediaRpcCompletion;
extern "C" MediaRpcShared *DAT_00587360;
extern "C" void FUN_0032db00(MediaRpcCompletion *c);
/* One open-file slot of igPsx2Media's handle table. */
struct MediaHandleRow { char *name; unsigned int mode; int fd; };
/* igPsx2Media's handle table: rows[limit] and a stack of free row indices. */
struct MediaHandlePool { unsigned short limit; unsigned short capacity; unsigned short count; short pad; unsigned short *freeList; MediaHandleRow *rows; };
struct MediaPathBuffer { int vt; int refCount; char *text; int length; };
/* An IOP file request in igPsx2Media's command buffer; the IOP writes its result to reply. */
struct MediaIoRequest { int fd; int buffer; int size; int reserved; int kind; int callback; int context; int extra; int reply; };
struct igPsx2MediaView : public igObject {
    char *_headAndTailBuffer;
    igPsx2IopRpcConnectionView *_connection;
    igSemaphoreView *_sema;
    MediaIoRequest *_commandBuffer;
    char *_writeBuffer;
    MediaHandlePool *_handlePool;
    MediaPathBuffer *_conversionString;
    unsigned char _initialized;
};
extern "C" void Gap__Core__igPsx2Media__vfunc_03(igPsx2MediaView *arg0, int extra1);
extern "C" void Gap__Core__igPsx2Media__vfunc_04(igPsx2MediaView *arg0);
extern "C" int text_libsd_irx[4];
extern "C" int text_igFileIO_irx[4];
extern "C" int *DAT_00587368;
extern "C" bool GPR_00554de0;
extern "C" void Gap__Core__igPsx2Media__vfunc_13(igPsx2MediaView *self);
extern "C" int text_cdrom[4];
extern "C" unsigned short Gap__Core__igPsx2Media__vfunc_23(igPsx2MediaView *self);
extern "C" void Gap__Core__igPsx2Media__vfunc_24(igPsx2MediaView *media, int handle);
extern "C" char *DAT_004c2650[];
extern "C" void FUN_0032e130(igPsx2MediaView *self, int index, char **path);
extern "C" void Gap__Core__igPsx2Media__vfunc_25(int *arg0, igPsx2MediaView *arg1, int arg2, int **arg3, unsigned int arg4);
extern "C" void Gap__Core__igPsx2Media__vfunc_26(igPsx2MediaView *self, int arg1);
extern "C" int Gap__Core__igPsx2Media__vfunc_27(igPsx2Media *arg0, int arg1, int arg2, int arg3);
extern "C" int FUN_0032e950(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
extern "C" int Gap__Core__igPsx2Media__vfunc_28(igPsx2MediaView *self, int arg1, int arg2, int arg3);
extern "C" void Gap__Core__igPsx2Media__vfunc_29(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int Gap__Core__igPsx2Media__vfunc_30(igPsx2Media *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Core__igPsx2Media__vfunc_31(igPsx2Media *arg0, int arg1);
extern "C" int Gap__Core__igPsx2Semaphore__vfunc_27(igPsx2Semaphore *self);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_28(int *arg0, igPsx2Semaphore *self, int arg2);
extern "C" int Gap__Core__igPsx2Semaphore__vfunc_29(igPsx2Semaphore *self);
extern "C" int Gap__Core__igPsx2Semaphore__vfunc_30(igPsx2Semaphore *arg0);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_23(int *arg0, igPsx2Semaphore *self);
extern "C" void Gap__Core__igPsx2Semaphore__vfunc_34(int *arg0, igPsx2Semaphore *self);
extern "C" int DAT_0052d8b0[4];
struct ThreadMemoryMap {
    unsigned stackTop; int p4; int p8; int p12; int p16;
    unsigned stackBottom;
    unsigned textStart;
    unsigned textSize;
    unsigned dataStart;
    unsigned dataSize;
    unsigned bssStart;
    unsigned bssSize;
    unsigned gp;
    unsigned sbssSize;
    unsigned stackRegion;
    unsigned stackRegionSize;
    unsigned scratchpad;
    unsigned scratchpadSize;
    int p72;
    int reserved;
    int stackSize;
};
extern "C" char DAT_00100000[];
extern "C" char DAT_000ffff0[];
extern "C" char Gap__Bec__beFont__vfunc_32[];
extern "C" char __new_handler[];
extern "C" char DAT_0058d280[];
extern "C" char DAT_000d2c64[];
extern "C" char DAT_00554e81[];
extern "C" char DAT_000383ff[];
extern "C" char DAT_70000000[];
extern "C" char DAT_00004000[];
extern "C" void FUN_0032f380(SystemAllocator *self, ThreadMemoryMap *map);
extern "C" int text_Memory_Main[4];
extern "C" int text_Platform[4];
extern "C" int text_Memory_Fast[4];
extern "C" int text_Section_Static_Cons[4];
extern "C" int text_Section_VTables[4];
extern "C" int text_Section_Small_Data[4];
extern "C" char __ctors_start__[];
extern "C" char DAT_00522480[];
extern "C" char __exception_table_start__[];
extern "C" char DAT_00554974[];
extern "C" char DAT_0000050d[];
extern "C" int _gp[4];
extern "C" igPsx2ThreadManagerView *g_threadManager[4];
extern "C" void Gap__Core__igPsx2Thread__vfunc_55(igPsx2Thread *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_24(int *arg0, void *arg1, igPsx2ThreadView *thread);
extern "C" void Gap__Core__igPsx2Thread__vfunc_44(int *arg0, igPsx2ThreadView *arg1);
extern "C" void Gap__Core__igPsx2Thread__vfunc_46(int *status, igPsx2Thread *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_48(int *status, igPsx2Thread *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_50(int *status, igPsx2Thread *self, int priority);
extern "C" igResult Gap__Core__igPsx2Thread__vfunc_45(igPsx2ThreadView *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_47(int *status, igPsx2Thread *thread);
extern "C" void Gap__Core__igPsx2Thread__vfunc_49(int *status, igPsx2Thread *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_51(int *status, igPsx2Thread *self, int priority);
extern "C" void Gap__Core__igPsx2Thread__vfunc_30(int *out, igPsx2ThreadView *thread);
extern "C" unsigned char Gap__Core__igPsx2Thread__vfunc_32(igPsx2Thread *self);
extern "C" igResult Gap__Core__igPsx2Thread__vfunc_31(igPsx2ThreadView *self);
extern "C" igResult Gap__Core__igPsx2Thread__vfunc_41(igPsx2ThreadView *self, int block, int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_56(int *arg0, igPsx2Thread *self, int arg2);
extern "C" void Gap__Core__igPsx2Thread__vfunc_57(igPsx2ThreadView *self);
extern "C" void FUN_00330440(igPsx2ThreadView *thread, int result);
extern "C" int DAT_00586ca8[4];
extern "C" int Gap__Core__igPsx2ThreadManager__vfunc_23(igPsx2ThreadManager *arg0);
extern "C" void FUN_003304e0(igPsx2ThreadManagerView *manager, igPsx2ThreadView *thread);
extern "C" void Gap__Core__igPsx2ThreadManager__vfunc_24(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread);
extern "C" void Gap__Core__igPsx2ThreadManager__vfunc_25(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread);
extern "C" int Gap__Core__igPsx2Thread__vfunc_34(igPsx2Thread *self);
extern "C" int Gap__Core__igPsx2Thread__vfunc_36(igPsx2Thread *self);
extern "C" igResult Gap__Core__igPsx2Thread__vfunc_37(igPsx2ThreadView *self, int stack, int size);
extern "C" int Gap__Core__igPsx2Thread__vfunc_38(igPsx2Thread *self);
extern "C" int Gap__Core__igPsx2Thread__vfunc_40(igPsx2Thread *self);
extern "C" int Gap__Core__igPsx2Semaphore__vfunc_25(igPsx2Semaphore *self);
extern "C" long long Gap__Core__igPsx2LongTimer__vfunc_26(igPsx2LongTimer *arg0);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_30(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_33(igPsx2LongTimer *self, long long resetTime);
extern "C" long long Gap__Core__igPsx2LongTimer__vfunc_35(igPsx2LongTimer *self);
/* The virtuals of the long timer its own methods call, placed at their retail vtable bytes: two
 * header words come first, so vfunc_N sits at byte 4 * N. */
class igLongTimerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual long long vfunc_24();
    virtual void d23();
    virtual long long vfunc_26();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void setResetTime(long long nanoseconds);
    virtual void d32();
    virtual long long getResetTime();
    virtual void d34();
    virtual long long vfunc_37();
};
extern "C" double Gap__Core__igPsx2LongTimer__vfunc_23(igLongTimerView *self);
extern "C" double Gap__Core__igPsx2LongTimer__vfunc_25(igLongTimerView *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_27(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_28(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_29(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_31(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2LongTimer__vfunc_32(igLongTimerView *self, double seconds);
extern "C" double Gap__Core__igPsx2LongTimer__vfunc_34(igLongTimerView *self);
extern "C" unsigned char Gap__Core__igPsx2LongTimer__vfunc_36(igPsx2LongTimer *self);
extern "C" void Gap__Core__igPsx2File__vfunc_11(igPsx2File *arg0);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self);
class igStringRefListView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void vfunc_16();
};
extern "C" void Gap__Core__igStringRefList__vfunc_14(igStringRefListView *self);
extern "C" void Gap__Core__igStringRefList__vfunc_18(igStringRefList *l);
extern "C" int g_igMemoryRefArrayMetaField_metaObject_00585de8[4];
extern "C" int g_igMemoryPoolContextInfo_metaObject_00585e98[4];
extern "C" void Gap__Core__igMallocMemoryPool__vfunc_32(igMallocMemoryPool *self);
extern "C" int FUN_00331a70(igTDataList<unsigned int> *arg0, unsigned int *arg1);
extern "C" int g_beDataObjList_metaObject[4];
extern "C" void Gap__Core__igBoolList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igCharList__vfunc_18(igCharList *arg0);
extern "C" void igIntList_TrimCapacity(igIntList *self);
extern "C" void Gap__Core__igUnsignedShortList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igShortList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igUnsignedCharList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igFloatList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igPointerList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Core__igDependencyList__vfunc_18(igDependencyList *self);

#endif
