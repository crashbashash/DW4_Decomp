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

/* igSmartPointer's release for a list held as igTDataList<T>. */
template <class T> static inline void igRelease(igTDataList<T> *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}

/* Assigning a smart pointer to an object-reference field: the field takes its own reference on the
 * new object and drops the one it held. */
template <class T, class U> static inline void assignReference(T *&field, const igSmartPointer<U> &value) {
    U *next = value.p;
    T *old;
    if (next != 0) {
        next->_refCount = next->_refCount + 1;
    }
    old = field;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    field = (T *)next;
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
#include "dw4/igobject_release.h"
/* Releases a reference field through a copy, so the field is read once. */
#define RELEASE_REF(p) do { igObject *t_ = (igObject *)(p); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long)((long long)(int)t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } } while (0)
#define REF_COUNT_MASK 0x7fffff
/* igObject::_refCount as the fields packed into it: the reference count in the low 23 bits, a flag
 * bit, and the owning memory pool's index in the top byte. The views differ only in the width of
 * the access the compiler emits: a word bitfield, a byte store of the pool index, or byte
 * bitfields over the third byte. */
union igRefCountWord {
    int word;
    struct { unsigned count : 23; unsigned rest : 9; } bits;
    struct { unsigned count : 23; unsigned flag : 1; unsigned char poolIndex; } header;
    struct { unsigned count : 23; unsigned flag : 1; unsigned poolIndex : 8; } pooled;
    struct { unsigned char low[2]; unsigned char high : 7; unsigned char flag : 1; unsigned char poolIndex; } bytes;
};
#define EMIT(...) \
    do { \
        if (file) { file->Print(__VA_ARGS__); } \
        else { igReport_Printf(__VA_ARGS__); igReport_Flush(); } \
    } while (0)
#define V1(p) virtual void p();
#define V4(p) V1(p##0) V1(p##1) V1(p##2) V1(p##3)
#define V16(p) V4(p##a) V4(p##b) V4(p##c) V4(p##d)
#define CONTEXT_RECORD_COUNT 46
#define CONTEXT_RECORD_SIZE 0x90
#define CONTEXT_RECORDS_OFFSET 0x14
#define CONTEXT_RECORD_NAME_MAX 0x7F
#define ASSIGN_TOKEN(field, source)                                           \
    text = (const char *)(source);                                            \
    if ((*(void * *)g_stringPool) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        (*(void * *)g_stringPool) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), text));          \
    old = (StringToken *)(field);                                             \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (int)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = (int)token
#define ASSIGN_TOKEN_DIRECT(field, source)                                           \
    if ((*(void * *)g_stringPool) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        (*(void * *)g_stringPool) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), (source)));          \
    old = (StringToken *)(field);                                             \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (int)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = (int)token
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
        if (v_ == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd_), (int)hd_); \
    } \
    arg0->field = s_; }
#define RESERVED(n) virtual void reserved_##n()
#define REL(o) if ((o) != 0) { (o)->_refCount = (int)(o)->_refCount - 1; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy((void *)o); } }
#define REL_O(p) { igObject *q_ = (igObject *)(p); if (q_) { q_->_refCount = q_->_refCount - 1; if (((unsigned long long)(long long)(int)q_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q_); } }
#define ASSIGN_O(o, fld, val) { igObject *n_ = (val); (o) = (igIGBFile *)file.p; if (n_ != 0) n_->_refCount = n_->_refCount + 1; REL_O((o)->fld) (o)->fld = (int)n_; }
#define OFF(p) (((TaggedBlockHeader *)(p))->big == 0 ? 4 : 12)
#define NEXT(p) (*(int *)((char *)(p) + OFF(p) + 4))
#define PREV(p) (*(int *)((char *)(p) + OFF(p)))
#define VCALL(o, off) (*(PF *)(*(char **)(o) + (off)))
#define PAGE_POOL_ALIGNMENT 0x1000
#define TRACER_PAGE_SIZE 0x1000
#define TRACER_BLOCK_SIZE 0x10000
#define NANOSECONDS_PER_SECOND 0x3B9ACA00

extern "C" int __init_cpp(...);
extern "C" int __fini_cpp(...);
struct StringTable;
struct StringChunk;
extern "C" void StringChunk_ReleaseHeader(StringChunk *self, int header);
extern "C" void * StringPool_Allocate(int arg0);
/* 16-byte string intern pool (g_stringPool[0]). */
typedef struct StringPool {
    StringTable *table; /* +0   sorted table of the interned strings */
    StringChunk *chunks; /* +4  head chunk of the storage chain */
    int chunkSize;  /* +8   bytes per new chunk (0x4000) */
    int pool;       /* +12  igMemoryPool the table and chunks come from */
} StringPool;
extern "C" StringPool *StringPool_Construct(StringPool *arg0);
extern "C" void CoreLibrary_MarkRegistered(void);
extern "C" int igVirtualCFuncMetaField_GetVTable(void);
extern "C" void igVirtualCFuncMetaField_EnsureRegistered(void);
extern "C" int igMetaObject_RegisterClass(...);
extern "C" void igVirtualCFuncMetaField_Register(void);
extern "C" void igVirtualCFuncMetaField_GetMetaObjectFunction(void);
extern "C" void igVirtualCFuncMetaField_CreateDefaultDescriptor(void);
extern "C" void **igUnsignedShortMetaField_Create(int arg0);
extern "C" int igUnsignedShortMetaField_Clone(int arg0, int arg1);
extern "C" int igUnsignedShortMetaField_GetVTable(void);
extern "C" void igUnsignedShortMetaField_EnsureRegistered(void);
extern "C" void igUnsignedShortMetaField_Register(void);
extern "C" void igUnsignedShortMetaField_GetMetaObjectFunction(void);
extern "C" void igUnsignedShortMetaField_CreateDefaultDescriptor(void);
extern "C" int igUnsignedShortMetaField_GetDefaultDescriptor(void);
extern "C" void igUnsignedShortArrayMetaField_Create(int arg0);
extern "C" int igUnsignedShortArrayMetaField_GetVTable(void);
extern "C" void igUnsignedShortArrayMetaField_EnsureRegistered(void);
extern "C" void igUnsignedShortArrayMetaField_Register(void);
extern "C" void igUnsignedShortArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igUnsignedShortMetaField_GetPublishedMetaObject(void);
extern "C" void igUnsignedShortArrayMetaField_InitFields(void);
extern "C" void igUnsignedShortArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void **igUnsignedLongMetaField_Create(int arg0);
extern "C" int igUnsignedLongMetaField_Clone(int arg0, int arg1);
extern "C" int igUnsignedLongMetaField_GetVTable(void);
extern "C" void igUnsignedLongMetaField_EnsureRegistered(void);
extern "C" void igUnsignedLongMetaField_Register(void);
extern "C" void igUnsignedLongMetaField_GetMetaObjectFunction(void);
extern "C" void igUnsignedLongMetaField_CreateDefaultDescriptor(void);
extern "C" int igUnsignedLongMetaField_GetDefaultDescriptor(void);
extern "C" int igUnsignedLongArrayMetaField_GetVTable(void);
extern "C" void igUnsignedLongArrayMetaField_EnsureRegistered(void);
extern "C" void igUnsignedLongArrayMetaField_Register(void);
extern "C" void igUnsignedLongArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igUnsignedLongMetaField_GetPublishedMetaObject(void);
extern "C" void igUnsignedLongArrayMetaField_InitFields(void);
extern "C" void igUnsignedLongArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void **igUnsignedIntMetaField_Create(int allocator);
extern "C" int igUnsignedIntMetaField_Clone(int arg0, int arg1);
extern "C" int igUnsignedIntMetaField_GetVTable(void);
extern "C" void igUnsignedIntMetaField_EnsureRegistered(void);
extern "C" void igUnsignedIntMetaField_Register(void);
extern "C" void igUnsignedIntMetaField_GetMetaObjectFunction(void);
extern "C" void igUnsignedIntMetaField_CreateDefaultDescriptor(void);
extern "C" int igUnsignedIntMetaField_GetDefaultDescriptor(void);
extern "C" void igUnsignedIntArrayMetaField_Create(int arg0);
extern "C" int igUnsignedIntArrayMetaField_GetVTable(void);
extern "C" void igUnsignedIntArrayMetaField_EnsureRegistered(void);
extern "C" void igUnsignedIntArrayMetaField_Register(void);
extern "C" void igUnsignedIntArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igUnsignedIntMetaField_GetPublishedMetaObject(void);
extern "C" void igUnsignedIntArrayMetaField_InitFields(void);
extern "C" void igUnsignedIntArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void igUnsignedCharMetaField_Create(int arg0);
extern "C" int igUnsignedCharMetaField_GetVTable(void);
extern "C" void igUnsignedCharMetaField_EnsureRegistered(void);
extern "C" void igUnsignedCharMetaField_Register(void);
extern "C" void igUnsignedCharMetaField_GetMetaObjectFunction(void);
extern "C" void igUnsignedCharMetaField_CreateDefaultDescriptor(void);
extern "C" int igUnsignedCharMetaField_GetDefaultDescriptor(void);
extern "C" int igObjectRefMetaField_GetDefaultDescriptor(void);
extern "C" int igObjectList_GetOrCreateMetaObject(void);
extern "C" int igIntMetaField_GetDefaultDescriptor(void);
extern "C" int igDataList_GetOrCreateMetaObject(void);
extern "C" int igIntList_GetOrCreateMetaObject(void);
extern "C" void igUnsignedCharArrayMetaField_Create(int arg0);
extern "C" int igUnsignedCharArrayMetaField_GetVTable(void);
extern "C" void igUnsignedCharArrayMetaField_EnsureRegistered(void);
extern "C" void igUnsignedCharArrayMetaField_Register(void);
extern "C" void igUnsignedCharArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igUnsignedCharMetaField_GetPublishedMetaObject(void);
extern "C" void igUnsignedCharArrayMetaField_InitFields(void);
extern "C" void igUnsignedCharArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void igTimer_Create(int arg0);
extern "C" igMetaObject *igTimer_GetOrCreateMetaObject(void);
extern "C" void igTimer_EnsureRegistered(void);
extern "C" void igTimer_Register(void);
extern "C" void igTimer_GetMetaObjectFunction(void);
extern "C" void igTimer_SetAbstractProxy(void);
extern "C" void thunk_igLongTimer_GetMetaObject(void);
extern "C" void * igThreadManager_Create(int arg0);
extern "C" void igThreadManager_EnsureRegistered(void);
extern "C" void igThreadManager_Register(void);
extern "C" void igThreadManager_GetMetaObjectFunction(void);
extern "C" void igThreadManager_InitFields(void);
extern "C" void igPsx2ThreadManager_GetMetaObjectFunction(void);
extern "C" void igThreadManager_StaticInitCallback(void);
extern "C" void igThreadManager_ExitCallback(void);
extern "C" int igThread_GetPriorityMetaEnum(void);
extern "C" int igThread_GetStateMetaEnum(void);
extern "C" int igThread_GetScopeMetaEnum(void);
extern "C" int igThread_GetTypeMetaEnum(void);
extern "C" void * igThread_Create(int arg0);
extern "C" igMetaObject *igThread_GetOrCreateMetaObject(void);
extern "C" void igThread_EnsureRegistered(void);
extern "C" void igThread_Register(void);
extern "C" void igThread_GetMetaObjectFunction(void);
extern "C" void igThread_InitFields(void);
extern "C" void igPsx2Thread_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetOrCreateMetaObject(void);
extern "C" int igNonRefCountedThreadList_GetVTable(void);
extern "C" void igNonRefCountedThreadList_EnsureRegistered(void);
extern "C" void igNonRefCountedThreadList_Register(void);
extern "C" void igNonRefCountedThreadList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igThreadList_GetOrCreateMetaObject(void);
extern "C" int igThreadList_GetVTable(void);
extern "C" void igThreadList_EnsureRegistered(void);
extern "C" void igThreadList_Register(void);
extern "C" void igThreadList_GetMetaObjectFunction(void);
extern "C" void * igSymbolTable_Create(int arg0);
extern "C" int igSymbolTable_GetVTable(void);
extern "C" int __dl__FPv(...);
extern "C" void **igSmartPointer_igIntListNoClean_Destruct(void **arg0, short arg1);
extern "C" void igSymbolTable_EnsureRegistered(void);
extern "C" void igSymbolTable_Register(void);
extern "C" void igSymbolTable_GetMetaObjectFunction(void);
extern "C" void igSymbolTable_InitFields(void);
extern "C" void igStructMetaField_Create(int arg0);
extern "C" int igStructMetaField_GetVTable(void);
extern "C" void igStructMetaField_EnsureRegistered(void);
extern "C" void igStructMetaField_Register(void);
extern "C" void igStructMetaField_GetMetaObjectFunction(void);
extern "C" void igStructMetaField_InitFields(void);
extern "C" void igStructMetaField_CreateDefaultDescriptor(void);
extern "C" void igStringTable_Create(int arg0);
extern "C" igMetaObject *igStringTable_GetOrCreateMetaObject(void);
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
extern "C" void igStringTable_EnsureRegistered(void);
extern "C" void igStringTable_Register(void);
extern "C" void igStringTable_GetMetaObjectFunction(void);
extern "C" void igStringTable_InitFields(void);
extern "C" void * igStringRefList_Create(int arg0);
extern "C" igMetaObject *igStringRefList_GetOrCreateMetaObject(void);
extern "C" int igStringRefList_GetVTable(void);
extern "C" void igStringRefList_EnsureRegistered(void);
extern "C" void igStringRefList_Register(void);
extern "C" void igStringRefList_GetMetaObjectFunction(void);
extern "C" void igStringRefList_InitFields(void);
extern "C" void * igStringObjList_Create(int arg0);
extern "C" igMetaObject *igStringObjList_GetOrCreateMetaObject(void);
extern "C" int igStringObjList_GetVTable(void);
extern "C" void igStringObjList_EnsureRegistered(void);
extern "C" void igStringObjList_Register(void);
extern "C" void igStringObjList_GetMetaObjectFunction(void);
extern "C" void * igStringObj_Create(int arg0);
extern "C" igMetaObject *igStringObj_GetOrCreateMetaObject(void);
extern "C" int igStringObj_GetVTable(void);
extern "C" void igStringObj_EnsureRegistered(void);
extern "C" void igStringObj_Register(void);
extern "C" void igStringObj_GetMetaObjectFunction(void);
extern "C" void igStringObj_InitFields(void);
extern "C" void **igStringMetaField_Create(int allocator);
extern "C" void **igObjectRefMetaField_Create(int allocator);
extern "C" void **igIntMetaField_Create(int allocator);
extern "C" void igStringMetaField_InitDefaults(void **self);
extern "C" int igStringMetaField_Clone(int arg0, int arg1);
extern "C" int igStringMetaField_GetVTable(void);
extern "C" void igStringMetaField_EnsureRegistered(void);
extern "C" void igStringMetaField_Register(void);
extern "C" void igStringMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igRefMetaField_GetPublishedMetaObject(void);
extern "C" void igStringMetaField_InitFields(void);
extern "C" void igStringMetaField_CreateDefaultDescriptor(void);
extern "C" int igStringMetaField_GetDefaultDescriptor(void);
extern "C" int igStringArrayMetaField_GetVTable(void);
extern "C" void igStringArrayMetaField_EnsureRegistered(void);
extern "C" void igStringArrayMetaField_Register(void);
extern "C" void igStringArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igStringMetaField_GetPublishedMetaObject(void);
extern "C" void igStringArrayMetaField_InitFields(void);
extern "C" void igStringArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void **igShortMetaField_Create(int arg0);
extern "C" int igShortMetaField_Clone(int arg0, int arg1);
extern "C" int igShortMetaField_GetVTable(void);
extern "C" void igShortMetaField_EnsureRegistered(void);
extern "C" void igShortMetaField_Register(void);
extern "C" void igShortMetaField_GetMetaObjectFunction(void);
extern "C" void igShortMetaField_CreateDefaultDescriptor(void);
extern "C" int igShortMetaField_GetDefaultDescriptor(void);
extern "C" void igShortArrayMetaField_Create(int arg0);
extern "C" int igShortArrayMetaField_GetVTable(void);
extern "C" void igShortArrayMetaField_EnsureRegistered(void);
extern "C" void igShortArrayMetaField_Register(void);
extern "C" void igShortArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igShortMetaField_GetPublishedMetaObject(void);
extern "C" void igShortArrayMetaField_InitFields(void);
extern "C" void igShortArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void * igSemaphore_Create(int arg0);
extern "C" igMetaObject *igSemaphore_GetOrCreateMetaObject(void);
extern "C" void igSemaphore_EnsureRegistered(void);
extern "C" void igSemaphore_Register(void);
extern "C" void igSemaphore_GetMetaObjectFunction(void);
extern "C" void igSemaphore_SetAbstractProxy(void);
extern "C" void igPsx2Semaphore_GetMetaObjectFunction(void);
extern "C" void **igSmartPointer_igLocationTable_Destruct(void **arg0, int arg1);
extern "C" void **igSmartPointer_igCallStackTable_Destruct(void **arg0, short arg1);
extern "C" void igResource_Create(int arg0);
extern "C" igMetaObject *igResource_GetOrCreateMetaObject(void);
extern "C" int FUN_001432d0(...);
extern "C" int FUN_001509f0(...);
extern "C" int FUN_001a0790(...);
extern "C" int FUN_001d36d0(...);
extern "C" int ObjectRef_Destruct_00150eb0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int igResource_GetVTable(void);
extern "C" void **igSmartPointer_igDirectoryList_Destruct(void **arg0, long long arg1);
extern "C" void igResource_EnsureRegistered(void);
extern "C" void igResource_Register(void);
extern "C" void igResource_GetMetaObjectFunction(void);
extern "C" void igResource_InitFields(void);
extern "C" void * igRegistry_Create(int arg0);
extern "C" igMetaObject *igRegistry_GetOrCreateMetaObject(void);
extern "C" int igRegistry_GetVTable(void);
extern "C" void igRegistry_EnsureRegistered(void);
extern "C" void igRegistry_Register(void);
extern "C" void igRegistry_GetMetaObjectFunction(void);
extern "C" void igRegistry_InitFields(void);
extern "C" igMetaObject *igRegistryValueList_GetOrCreateMetaObject(void);
extern "C" int igRegistryValueList_GetVTable(void);
extern "C" void igRegistryValueList_EnsureRegistered(void);
extern "C" void igRegistryValueList_Register(void);
extern "C" void igRegistryValueList_GetMetaObjectFunction(void);
extern "C" void * igRegistryValue_Create(int arg0);
extern "C" int igRegistryValue_GetVTable(void);
extern "C" void igRegistryValue_EnsureRegistered(void);
extern "C" void igRegistryValue_Register(void);
extern "C" void igRegistryValue_GetMetaObjectFunction(void);
extern "C" void igRegistryValue_InitFields(void);
extern "C" void igRefMetaField_EnsureRegistered(void);
extern "C" void igRefMetaField_Register(void);
extern "C" void igRefMetaField_GetMetaObjectFunction(void);
extern "C" void igRefMetaField_InitFields(void);
extern "C" void igRefMetaField_CreateDefaultDescriptor(void);
extern "C" void **igRawRefMetaField_Create(int arg0);
extern "C" int igRawRefMetaField_Clone(int arg0, int arg1);
extern "C" igMetaObject *igRawRefMetaField_GetOrCreateMetaObject(void);
extern "C" int igRawRefMetaField_GetVTable(void);
extern "C" void igRawRefMetaField_EnsureRegistered(void);
extern "C" void igRawRefMetaField_Register(void);
extern "C" void igRawRefMetaField_GetMetaObjectFunction(void);
extern "C" void igRawRefMetaField_CreateDefaultDescriptor(void);
extern "C" int igRawRefMetaField_GetDefaultDescriptor(void);
extern "C" int igRawRefArrayMetaField_GetVTable(void);
extern "C" void igRawRefArrayMetaField_EnsureRegistered(void);
extern "C" void igRawRefArrayMetaField_Register(void);
extern "C" void igRawRefArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igRawRefMetaField_GetPublishedMetaObject(void);
extern "C" void igRawRefArrayMetaField_InitFields(void);
extern "C" void igRawRefArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void * igQueue_Create(int arg0);
extern "C" igMetaObject *igQueue_GetOrCreateMetaObject(void);
extern "C" void igQueue_EnsureRegistered(void);
extern "C" void igQueue_Register(void);
extern "C" void igQueue_GetMetaObjectFunction(void);
extern "C" void igQueue_InitFields(void);
extern "C" void igStandardQueue_GetMetaObjectFunction(void);
extern "C" void igPluginHelper_Create(int arg0);
extern "C" int igPluginHelper_GetVTable(void);
extern "C" void **igSmartPointer_igPluginRepositoryList_Destruct(void **arg0, long long arg1);
extern "C" void **igSmartPointer_igLibraryLoader_Destruct(void **arg0, short arg1);
extern "C" void igPluginHelper_EnsureRegistered(void);
extern "C" void igPluginHelper_Register(void);
extern "C" void igPluginHelper_GetMetaObjectFunction(void);
extern "C" void igPluginHelper_InitFields(void);
extern "C" igMetaObject *igPluginRepositoryList_GetOrCreateMetaObject(void);
extern "C" int igPluginRepositoryList_GetVTable(void);
extern "C" void igPluginRepositoryList_EnsureRegistered(void);
extern "C" void igPluginRepositoryList_Register(void);
extern "C" void igPluginRepositoryList_GetMetaObjectFunction(void);
extern "C" int igPluginRepository_GetLocationTypeMetaEnum(void);
extern "C" int igPluginRepository_Create(int arg0);
extern "C" int igPluginRepository_GetVTable(void);
extern "C" void igPluginRepository_EnsureRegistered(void);
extern "C" void igPluginRepository_Register(void);
extern "C" void igPluginRepository_GetMetaObjectFunction(void);
extern "C" void igPluginRepository_InitFields(void);
extern "C" igMetaObject *igObjectStringMap_GetOrCreateMetaObject(void);
extern "C" int igObjectStringMap_GetVTable(void);
extern "C" void igObjectStringMap_EnsureRegistered(void);
extern "C" void igObjectStringMap_Register(void);
extern "C" void igObjectStringMap_GetMetaObjectFunction(void);
extern "C" void igObjectStringMap_InitFields(void);
extern "C" int igObjectRefMetaField_Clone(int arg0, int arg1);
extern "C" int igObjectRefMetaField_GetVTable(void);
extern "C" void igObjectRefMetaField_EnsureRegistered(void);
extern "C" void igObjectRefMetaField_Register(void);
extern "C" void igObjectRefMetaField_GetMetaObjectFunction(void);
extern "C" void igObjectRefMetaField_InitFields(void);
extern "C" void igObjectRefMetaField_CreateDefaultDescriptor(void);
extern "C" void igObjectRefArrayMetaField_Create(int arg0);
extern "C" int igObjectRefArrayMetaField_GetVTable(void);
extern "C" void igObjectRefArrayMetaField_EnsureRegistered(void);
extern "C" void igObjectRefArrayMetaField_Register(void);
extern "C" void igObjectRefArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igObjectRefMetaField_GetPublishedMetaObject(void);
extern "C" void igObjectRefArrayMetaField_InitFields(void);
extern "C" void igObjectRefArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void * igObjectList_Create(int arg0);
extern "C" int igObjectList_GetVTable(void);
extern "C" void igObjectList_EnsureRegistered(void);
extern "C" void *igObjectList_Register(void);
extern "C" void igObjectList_GetMetaObjectFunction(void);
extern "C" void igObjectList_InitFields(void);
extern "C" int igObjectDirEntry_Create(int arg0);
extern "C" int FUN_0019c840(...);
extern "C" int FUN_0014f4e0(...);
extern "C" int igObjectDirEntry_GetVTable(void);
extern "C" void igObjectDirEntry_EnsureRegistered(void);
extern "C" void igObjectDirEntry_Register(void);
extern "C" void igObjectDirEntry_GetMetaObjectFunction(void);
extern "C" igMetaObject *igDirEntry_GetPublishedMetaObject(void);
extern "C" void igObjectDirEntry_InitFields(void);
extern "C" int igNonRefCountedObjectList_GetVTable(void);
extern "C" void igNonRefCountedObjectList_EnsureRegistered(void);
extern "C" void igNonRefCountedObjectList_Register(void);
extern "C" void igNonRefCountedObjectList_GetMetaObjectFunction(void);
extern "C" void igNonRefCountedObjectList_InitFields(void);
extern "C" int igNamedObjectInfo_GetVTable(void);
extern "C" void igNamedObjectInfo_EnsureRegistered(void);
extern "C" void igNamedObjectInfo_Register(void);
extern "C" void igNamedObjectInfo_GetMetaObjectFunction(void);
extern "C" void igNamedObjectInfo_InitFields(void);
extern "C" igMetaObject *igNamedObjectList_GetOrCreateMetaObject(void);
extern "C" int igNamedObjectList_GetVTable(void);
extern "C" void igNamedObjectList_EnsureRegistered(void);
extern "C" void igNamedObjectList_Register(void);
extern "C" void igNamedObjectList_GetMetaObjectFunction(void);
extern "C" void * igNamedObject_Create(int arg0);
extern "C" igMetaObject *igNamedObject_GetOrCreateMetaObject(void);
extern "C" int igNamedObject_GetVTable(void);
extern "C" void igNamedObject_EnsureRegistered(void);
extern "C" void igNamedObject_Register(void);
extern "C" void igNamedObject_GetMetaObjectFunction(void);
extern "C" void igNamedObject_InitFields(void);
extern "C" void **igMetaObject_Create(int allocator);
extern "C" void *igMetaObject_Clone(int arg0, int arg1);
extern "C" igMetaObject *igMetaObject_GetOrCreateMetaObject(void);
extern "C" int igMetaObject_GetVTable(void);
extern "C" void igMetaObject_EnsureRegistered(void);
extern "C" void igMetaObject_Register(void);
extern "C" void igMetaObject_GetMetaObjectFunction(void);
extern "C" void igMetaObject_InitFields(void);
extern "C" void igMetaFieldInfo_Create(int arg0);
extern "C" int igMetaFieldInfo_GetVTable(void);
extern "C" void igMetaFieldInfo_EnsureRegistered(void);
extern "C" void igMetaFieldInfo_Register(void);
extern "C" void igMetaFieldInfo_GetMetaObjectFunction(void);
extern "C" int igMetaField_GetResetTypeMetaEnum(void);
extern "C" igMetaObject *igMetaField_GetOrCreateMetaObject(void);
extern "C" void igMetaField_EnsureRegistered(void);
extern "C" void igMetaField_Register(void);
extern "C" void igMetaField_GetMetaObjectFunction(void);
extern "C" void igMetaField_InitFields(void);
extern "C" void * igMetaEnum_CreateInstance(int arg0);
extern "C" int igMetaEnum_GetVTable(void);
extern "C" void igMetaEnum_EnsureRegistered(void);
extern "C" void igMetaEnum_Register(void);
extern "C" void igMetaEnum_GetMetaObjectFunction(void);
extern "C" void igMetaEnum_InitFields(void);
extern "C" void **igMemoryRefMetaField_Create(int arg0);
extern "C" int FUN_0014ec50(...);
extern "C" int igMemoryRefMetaField_GetVTable(void);
extern "C" void igMemoryRefMetaField_EnsureRegistered(void);
extern "C" void igMemoryRefMetaField_Register(void);
extern "C" void igMemoryRefMetaField_GetMetaObjectFunction(void);
extern "C" void igMemoryRefMetaField_InitFields(void);
extern "C" void igMemoryRefMetaField_CreateDefaultDescriptor(void);
extern "C" int igMemoryRefMetaField_GetDefaultDescriptor(void);
extern "C" int igMemoryRefArrayMetaField_GetVTable(void);
extern "C" void igMemoryRefArrayMetaField_EnsureRegistered(void);
extern "C" void igMemoryRefArrayMetaField_Register(void);
extern "C" void igMemoryRefArrayMetaField_GetMetaObjectFunction(void);
extern "C" int igMemoryRefMetaField_GetPublishedMetaObject(void);
extern "C" void igMemoryRefArrayMetaField_InitFields(void);
extern "C" void igMemoryRefArrayMetaField_CreateDefaultDescriptor(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetOrCreateMetaObject(void);
extern "C" int igMemoryPoolInfoList_GetVTable(void);
extern "C" void igMemoryPoolInfoList_EnsureRegistered(void);
extern "C" void igMemoryPoolInfoList_Register(void);
extern "C" void igMemoryPoolInfoList_GetMetaObjectFunction(void);
extern "C" void * igMemoryPoolInfo_Create(int arg0);
extern "C" int FUN_00131b20(...);
extern "C" int igMemoryPoolInfo_GetVTable(void);
extern "C" void igMemoryPoolInfo_EnsureRegistered(void);
extern "C" void igMemoryPoolInfo_Register(void);
extern "C" void igMemoryPoolInfo_GetMetaObjectFunction(void);
extern "C" void igMemoryPoolInfo_InitFields(void);
extern "C" void * igMemoryPoolContextInfo_Create(int arg0);
extern "C" int igMemoryPoolContextInfo_GetVTable(void);
extern "C" void igMemoryPoolContextInfo_EnsureRegistered(void);
extern "C" void igMemoryPoolContextInfo_Register(void);
extern "C" void igMemoryPoolContextInfo_GetMetaObjectFunction(void);
extern "C" void igMemoryPoolContextInfo_InitFields(void);
extern "C" igMetaObject *igMemoryPool_GetOrCreateMetaObject(void);
extern "C" void igMemoryPool_EnsureRegistered(void);
extern "C" void igMemoryPool_Register(void);
extern "C" void igMemoryPool_GetMetaObjectFunction(void);
extern "C" void igMemoryPool_InitFields(void);
extern "C" void igArenaMemoryPool_GetMetaObjectFunction(void);
extern "C" void igMemoryFile_Create(int arg0);
extern "C" int igMemoryFile_GetVTable(void);
extern "C" void igMemoryFile_EnsureRegistered(void);
extern "C" void igMemoryFile_Register(void);
extern "C" void igMemoryFile_GetMetaObjectFunction(void);
extern "C" igMetaObject *igFile_GetPublishedMetaObject(void);
extern "C" void igMemoryFile_InitFields(void);
extern "C" void igFile_GetMetaObjectFunction(void);
extern "C" void igMemoryFile_StaticInitCallback(void);
extern "C" void igMemoryFile_ExitCallback(void);
extern "C" int igMemoryFileEntryList_Create(int arg0);
extern "C" int igMemoryFileEntryList_GetVTable(void);
extern "C" void igMemoryFileEntryList_EnsureRegistered(void);
extern "C" void igMemoryFileEntryList_Register(void);
extern "C" void igMemoryFileEntryList_GetMetaObjectFunction(void);
extern "C" void * igMemoryFileEntry_Create(int arg0);
extern "C" int igMemoryFileEntry_GetVTable(void);
extern "C" void igMemoryFileEntry_EnsureRegistered(void);
extern "C" void igMemoryFileEntry_Register(void);
extern "C" void igMemoryFileEntry_GetMetaObjectFunction(void);
extern "C" void igMemoryFileEntry_InitFields(void);
extern "C" int igMemoryDirEntry_Create(int arg0);
extern "C" int igMemoryDirEntry_GetVTable(void);
extern "C" void igMemoryDirEntry_EnsureRegistered(void);
extern "C" void igMemoryDirEntry_Register(void);
extern "C" void igMemoryDirEntry_GetMetaObjectFunction(void);
extern "C" void igMemoryDirEntry_InitFields(void);
extern "C" void * igMemoryDictionary_Create(int arg0);
extern "C" int igMemoryDictionary_GetVTable(void);
extern "C" void igMemoryDictionary_EnsureRegistered(void);
extern "C" void igMemoryDictionary_Register(void);
extern "C" void igMemoryDictionary_GetMetaObjectFunction(void);
extern "C" void igMemoryDictionary_InitFields(void);
extern "C" int igMediaFile_GetVTable(void);
extern "C" void **igSmartPointer_igMedia_Destruct(void **arg0, short arg1);
extern "C" void igMediaFile_EnsureRegistered(void);
extern "C" void igMediaFile_Register(void);
extern "C" void igMediaFile_GetMetaObjectFunction(void);
extern "C" void igMediaFile_InitFields(void);
extern "C" void * igMediaList_Create(int arg0);
extern "C" int igMediaList_GetVTable(void);
extern "C" void igMediaList_EnsureRegistered(void);
extern "C" void igMediaList_Register(void);
extern "C" void igMediaList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMedia_GetOrCreateMetaObject(void);
extern "C" void igMedia_EnsureRegistered(void);
extern "C" void igMedia_Register(void);
extern "C" void igMedia_GetMetaObjectFunction(void);
extern "C" void igMedia_SetAbstractProxy(void);
extern "C" void igPsx2Media_GetMetaObjectFunction(void);
extern "C" void igMedia_StaticInitCallback(void);
extern "C" void igMedia_ExitCallback(void);
extern "C" void igLongTimer_EnsureRegistered(void);
extern "C" void igLongTimer_Register(void);
extern "C" igMetaObject *igTimer_GetPublishedMetaObject(void);
extern "C" void igLongTimer_InitFields(void);
extern "C" void igPsx2LongTimer_GetMetaObjectFunction(void);
extern "C" void igLongMetaField_Create(int arg0);
extern "C" int igLongMetaField_GetVTable(void);
extern "C" void igLongMetaField_EnsureRegistered(void);
extern "C" void igLongMetaField_Register(void);
extern "C" void igLongMetaField_GetMetaObjectFunction(void);
extern "C" void igLongMetaField_CreateDefaultDescriptor(void);
extern "C" int igLongMetaField_GetDefaultDescriptor(void);
extern "C" int igLongArrayMetaField_GetVTable(void);
extern "C" void igLongArrayMetaField_EnsureRegistered(void);
extern "C" void igLongArrayMetaField_Register(void);
extern "C" void igLongArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLongMetaField_GetPublishedMetaObject(void);
extern "C" void igLongArrayMetaField_InitFields(void);
extern "C" void igLongArrayMetaField_CreateDefaultDescriptor(void);
extern "C" igMetaObject *igLocationTable_GetOrCreateMetaObject(void);
extern "C" int igLocationTable_GetVTable(void);
extern "C" void igLocationTable_EnsureRegistered(void);
extern "C" void igLocationTable_Register(void);
extern "C" void igLocationTable_GetMetaObjectFunction(void);
extern "C" void igLocationTable_InitFields(void);
extern "C" igMetaObject *igLibraryLoader_GetOrCreateMetaObject(void);
extern "C" void igLibraryLoader_EnsureRegistered(void);
extern "C" void igLibraryLoader_Register(void);
extern "C" void igLibraryLoader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLibraryList_GetOrCreateMetaObject(void);
extern "C" int igLibraryList_GetVTable(void);
extern "C" void igLibraryList_EnsureRegistered(void);
extern "C" void igLibraryList_Register(void);
extern "C" void igLibraryList_GetMetaObjectFunction(void);
extern "C" void igLibrary_EnsureRegistered(void);
extern "C" void igLibrary_Register(void);
extern "C" void igLibrary_GetMetaObjectFunction(void);
extern "C" void igLibrary_InitFields(void);
extern "C" void **InternalObjectList_Create(int allocator);
extern "C" int __internalObjectList_Clone(int arg0, int arg1);
extern "C" igMetaObject *__internalObjectList_GetOrCreateMetaObject(void);
extern "C" int __internalObjectList_GetVTable(void);
extern "C" void __internalObjectList_EnsureRegistered(void);
extern "C" void __internalObjectList_Register(void);
extern "C" void __internalObjectList_GetMetaObjectFunction(void);
extern "C" igMetaObject *__internalNonRefCountedObjectList_GetPublishedMetaObject(void);
extern "C" void __internalObjectList_InitFields(void);
extern "C" void **__internalNonRefCountedObjectList_Create(int arg0);
extern "C" int __internalNonRefCountedObjectList_Clone(int arg0, int arg1);
extern "C" igMetaObject *__internalNonRefCountedObjectList_GetOrCreateMetaObject(void);
extern "C" int __internalNonRefCountedObjectList_GetVTable(void);
extern "C" void __internalNonRefCountedObjectList_EnsureRegistered(void);
extern "C" void __internalNonRefCountedObjectList_Register(void);
extern "C" void __internalNonRefCountedObjectList_GetMetaObjectFunction(void);
extern "C" void __internalNonRefCountedObjectList_InitFields(void);
extern "C" void *igIntMetaField_Clone(void *self, void *src);
extern "C" igMetaObject *igIntMetaField_GetOrCreateMetaObject(void);
extern "C" int FUN_002ea420(...);
extern "C" int igIntMetaField_GetVTable(void);
extern "C" void igIntMetaField_EnsureRegistered(void);
extern "C" void igIntMetaField_Register(void);
extern "C" void igIntMetaField_GetMetaObjectFunction(void);
extern "C" void igIntMetaField_CreateDefaultDescriptor(void);
extern "C" void igIntArrayMetaField_Create(int arg0);
extern "C" int igIntArrayMetaField_GetVTable(void);
extern "C" void igIntArrayMetaField_EnsureRegistered(void);
extern "C" void igIntArrayMetaField_Register(void);
extern "C" void igIntArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igIntMetaField_GetPublishedMetaObject(void);
extern "C" void igIntArrayMetaField_InitFields(void);
extern "C" void igIntArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void igInfoList_Create(int arg0);
extern "C" igMetaObject *igInfoList_GetOrCreateMetaObject(void);
extern "C" int igInfoList_GetVTable(void);
extern "C" void igInfoList_EnsureRegistered(void);
extern "C" void igInfoList_Register(void);
extern "C" void igInfoList_GetMetaObjectFunction(void);
extern "C" int igInfo_GetVTable(void);
extern "C" void igInfo_EnsureRegistered(void);
extern "C" void igInfo_Register(void);
extern "C" void igInfo_GetMetaObjectFunction(void);
extern "C" void igInfo_InitFields(void);
extern "C" void * igIGBFile_Create(int arg0);
extern "C" int igIGBFile_GetOrCreateMetaObject(void);
extern "C" int FUN_0013a880(...);
extern "C" int FUN_0014aa70(...);
extern "C" int FUN_0014e420(...);
extern "C" int FUN_00150180(...);
extern "C" int FUN_001510d0(...);
extern "C" int FUN_001a4510(...);
extern "C" int FUN_00229270(...);
extern "C" int igIGBFile_GetVTable(void);
extern "C" int *igSmartPointer_igMemoryPool_Construct(int *p);
extern "C" int *igSmartPointer_igMetaField_Construct(int *p);
extern "C" int *igSmartPointer_igMetaFieldList_Construct(int *p);
extern "C" int *igSmartPointer_igFile_Construct(int *p);
extern "C" int *igSmartPointer_igObjectList_Construct(int *p);
extern "C" void igIGBFile_EnsureRegistered(void);
extern "C" void igIGBFile_Register(void);
extern "C" void igIGBFile_GetMetaObjectFunction(void);
extern "C" igMetaObject *igDirectory_GetPublishedMetaObject(void);
extern "C" void igIGBFile_InitFields(void);
extern "C" void igIGBFile_StaticInitCallback(void);
extern "C" void * igFolder_Create(int arg0);
extern "C" int igFolder_GetVTable(void);
extern "C" void igFolder_EnsureRegistered(void);
extern "C" void igFolder_Register(void);
extern "C" void igFolder_GetMetaObjectFunction(void);
extern "C" void igFolder_InitFields(void);
extern "C" void igPsx2Folder_GetMetaObjectFunction(void);
extern "C" void igFloatMetaField_Create(int arg0);
extern "C" int igFloatMetaField_GetVTable(void);
extern "C" void igFloatMetaField_EnsureRegistered(void);
extern "C" void igFloatMetaField_Register(void);
extern "C" void igFloatMetaField_GetMetaObjectFunction(void);
extern "C" void igFloatMetaField_CreateDefaultDescriptor(void);
extern "C" int igFloatMetaField_GetDefaultDescriptor(void);
extern "C" void igFloatArrayMetaField_Create(int arg0);
extern "C" int FUN_002fbfe0(...);
extern "C" int igFloatArrayMetaField_GetVTable(void);
extern "C" void igFloatArrayMetaField_EnsureRegistered(void);
extern "C" void igFloatArrayMetaField_Register(void);
extern "C" void igFloatArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igFloatMetaField_GetPublishedMetaObject(void);
extern "C" void igFloatArrayMetaField_InitFields(void);
extern "C" void igFloatArrayMetaField_CreateDefaultDescriptor(void);
extern "C" int igFile_GetReadModeMetaEnum(void);
extern "C" int igFile_GetOpenModeMetaEnum(void);
extern "C" void * igFile_Create(int arg0);
extern "C" igMetaObject *igFile_GetOrCreateMetaObject(void);
extern "C" void igFile_EnsureRegistered(void);
extern "C" void igFile_Register(void);
extern "C" void igFile_InitFields(void);
extern "C" void igPsx2File_GetMetaObjectFunction(void);
extern "C" void *igExternalInfoEntry_Create(int arg0);
extern "C" int FUN_00130720(...);
extern "C" int igExternalInfoEntry_GetVTable(void);
extern "C" void igExternalInfoEntry_EnsureRegistered(void);
extern "C" void igExternalInfoEntry_Register(void);
extern "C" void igExternalInfoEntry_GetMetaObjectFunction(void);
extern "C" void igExternalInfoEntry_InitFields(void);
extern "C" int igExternalIndexedEntry_GetVTable(void);
extern "C" void igExternalIndexedEntry_EnsureRegistered(void);
extern "C" void igExternalIndexedEntry_Register(void);
extern "C" void igExternalIndexedEntry_GetMetaObjectFunction(void);
extern "C" void igExternalIndexedEntry_InitFields(void);
extern "C" int igExternalDirEntry_GetVTable(void);
extern "C" void igExternalDirEntry_EnsureRegistered(void);
extern "C" void igExternalDirEntry_Register(void);
extern "C" void igExternalDirEntry_GetMetaObjectFunction(void);
extern "C" void igExternalDirEntry_InitFields(void);
extern "C" void * igEventTracker_Create(int arg0);
extern "C" igMetaObject *igEventTracker_GetOrCreateMetaObject(void);
extern "C" int igEventTracker_GetVTable(void);
extern "C" void igEventTracker_EnsureRegistered(void);
extern "C" void igEventTracker_Register(void);
extern "C" void igEventTracker_GetMetaObjectFunction(void);
extern "C" void igEventTracker_InitFields(void);
extern "C" int igErrorHandler_Create(int arg0);
extern "C" int igErrorHandler_GetVTable(void);
extern "C" void igErrorHandler_EnsureRegistered(void);
extern "C" void igErrorHandler_Register(void);
extern "C" void igErrorHandler_GetMetaObjectFunction(void);
extern "C" void igErrorHandler_RegisterExitCallback(void);
extern "C" void igErrorHandler_StaticInitCallback(void);
extern "C" void igErrorHandler_ExitCallback(void);
extern "C" void **igEnumMetaField_Create(int arg0);
extern "C" int igEnumMetaField_Clone(int arg0, int arg1);
extern "C" int igEnumMetaField_GetVTable(void);
extern "C" void igEnumMetaField_EnsureRegistered(void);
extern "C" void igEnumMetaField_Register(void);
extern "C" void igEnumMetaField_GetMetaObjectFunction(void);
extern "C" void igEnumMetaField_InitFields(void);
extern "C" void igEnumMetaField_CreateDefaultDescriptor(void);
extern "C" int igEnumMetaField_GetDefaultDescriptor(void);
extern "C" void igEnumArrayMetaField_Create(int arg0);
extern "C" int igEnumArrayMetaField_GetVTable(void);
extern "C" void igEnumArrayMetaField_EnsureRegistered(void);
extern "C" void igEnumArrayMetaField_Register(void);
extern "C" void igEnumArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEnumMetaField_GetPublishedMetaObject(void);
extern "C" void igEnumArrayMetaField_InitFields(void);
extern "C" void igEnumArrayMetaField_CreateDefaultDescriptor(void);
extern "C" int igDriverDatabase_GetSectionOverrideModeMetaEnum(void);
extern "C" void igDriverDatabase_Create(int arg0);
extern "C" int FUN_001489a0(...);
extern "C" int FUN_0019eeb0(...);
extern "C" int FUN_00227e70(...);
extern "C" int igDriverDatabase_GetVTable(void);
extern "C" void igDriverDatabase_EnsureRegistered(void);
extern "C" void igDriverDatabase_Register(void);
extern "C" void igDriverDatabase_GetMetaObjectFunction(void);
extern "C" void igDriverDatabase_InitFields(void);
extern "C" void igDoubleMetaField_Create(int arg0);
extern "C" int igDoubleMetaField_GetVTable(void);
extern "C" void igDoubleMetaField_EnsureRegistered(void);
extern "C" void igDoubleMetaField_Register(void);
extern "C" void igDoubleMetaField_GetMetaObjectFunction(void);
extern "C" void igDoubleMetaField_CreateDefaultDescriptor(void);
extern "C" int igDoubleMetaField_GetDefaultDescriptor(void);
extern "C" int igDoubleArrayMetaField_GetVTable(void);
extern "C" void igDoubleArrayMetaField_EnsureRegistered(void);
extern "C" void igDoubleArrayMetaField_Register(void);
extern "C" void igDoubleArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igDoubleMetaField_GetPublishedMetaObject(void);
extern "C" void igDoubleArrayMetaField_InitFields(void);
extern "C" void igDoubleArrayMetaField_CreateDefaultDescriptor(void);
extern "C" igMetaObject *igDirectoryList_GetOrCreateMetaObject(void);
extern "C" int igDirectoryList_GetVTable(void);
extern "C" void igDirectoryList_EnsureRegistered(void);
extern "C" void igDirectoryList_Register(void);
extern "C" void igDirectoryList_GetMetaObjectFunction(void);
extern "C" void * igDirectory_Create(int arg0);
extern "C" igMetaObject *igDirectory_GetOrCreateMetaObject(void);
extern "C" int FUN_00135430(...);
extern "C" int FUN_001d35d0(...);
extern "C" int igDirectory_GetVTable(void);
extern "C" void igDirectory_EnsureRegistered(void);
extern "C" void igDirectory_Register(void);
extern "C" void igDirectory_GetMetaObjectFunction(void);
extern "C" void igDirectory_InitFields(void);
extern "C" void igDirectory_StaticInitCallback(void);
extern "C" int igDirEntry_GetRefTypeMetaEnum(void);
extern "C" int igDirEntry_GetResolveMethodMetaEnum(void);
extern "C" void * igDirEntry_Create(int arg0);
extern "C" int igDirEntry_GetVTable(void);
extern "C" void igDirEntry_EnsureRegistered(void);
extern "C" void igDirEntry_Register(void);
extern "C" void igDirEntry_GetMetaObjectFunction(void);
extern "C" void igDirEntry_InitFields(void);
extern "C" int ObjectRef_Destruct_001c6460(...);
extern "C" int FUN_00233590(...);
extern "C" int igDependencyOrderedList_GetVTable(void);
extern "C" void igDependencyOrderedList_EnsureRegistered(void);
extern "C" void igDependencyOrderedList_Register(void);
extern "C" void igDependencyOrderedList_GetMetaObjectFunction(void);
extern "C" void igDependencyOrderedList_InitFields(void);
extern "C" igMetaObject *igDependencyList_GetOrCreateMetaObject(void);
extern "C" int igDependencyList_GetVTable(void);
extern "C" void igDependencyList_EnsureRegistered(void);
extern "C" void igDependencyList_Register(void);
extern "C" void igDependencyList_GetMetaObjectFunction(void);
extern "C" void igDependencyList_InitFields(void);
extern "C" int igDependencyMetaField_GetVTable(void);
extern "C" void igDependencyMetaField_EnsureRegistered(void);
extern "C" void igDependencyMetaField_Register(void);
extern "C" void igDependencyMetaField_GetMetaObjectFunction(void);
extern "C" void igDependencyMetaField_CreateDefaultDescriptor(void);
extern "C" int igDependencyMetaField_GetDefaultDescriptor(void);
extern "C" int igDependencyMetaField_GetSize(void);
extern "C" void igDependencyMetaField_InitDefaults(void *arg0);
extern "C" void igDependencyMetaField_AddSubFields(int arg0);
extern "C" void * igDataList_Create(int arg0);
extern "C" int igDataList_GetVTable(void);
extern "C" void igDataList_EnsureRegistered(void);
extern "C" void *igDataList_Register(void);
extern "C" void igDataList_GetMetaObjectFunction(void);
extern "C" void igDataList_InitFields(void);
extern "C" igMetaObject *igStringRefListList_GetOrCreateMetaObject(void);
extern "C" int igStringRefListList_GetVTable(void);
extern "C" void igStringRefListList_EnsureRegistered(void);
extern "C" void igStringRefListList_Register(void);
extern "C" void igStringRefListList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igObjectListList_GetOrCreateMetaObject(void);
extern "C" int igObjectListList_GetVTable(void);
extern "C" void igObjectListList_EnsureRegistered(void);
extern "C" void igObjectListList_Register(void);
extern "C" void igObjectListList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igIntListList_GetOrCreateMetaObject(void);
extern "C" int igIntListList_GetVTable(void);
extern "C" void igIntListList_EnsureRegistered(void);
extern "C" void igIntListList_Register(void);
extern "C" void igIntListList_GetMetaObjectFunction(void);
extern "C" void * igMetaFieldList_Create(int arg0);
extern "C" igMetaObject *igMetaFieldList_GetOrCreateMetaObject(void);
extern "C" int igMetaFieldList_GetVTable(void);
extern "C" void igMetaFieldList_EnsureRegistered(void);
extern "C" void igMetaFieldList_Register(void);
extern "C" void igMetaFieldList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMetaObjectListList_GetOrCreateMetaObject(void);
extern "C" int igMetaObjectListList_GetVTable(void);
extern "C" void igMetaObjectListList_EnsureRegistered(void);
extern "C" void igMetaObjectListList_Register(void);
extern "C" void igMetaObjectListList_GetMetaObjectFunction(void);
extern "C" void * igMetaObjectList_Create(int arg0);
extern "C" igMetaObject *igMetaObjectList_GetOrCreateMetaObject(void);
extern "C" int igMetaObjectList_GetVTable(void);
extern "C" void igMetaObjectList_EnsureRegistered(void);
extern "C" void igMetaObjectList_Register(void);
extern "C" void igMetaObjectList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igPointerListList_GetOrCreateMetaObject(void);
extern "C" int igPointerListList_GetVTable(void);
extern "C" void igPointerListList_EnsureRegistered(void);
extern "C" void igPointerListList_Register(void);
extern "C" void igPointerListList_GetMetaObjectFunction(void);
extern "C" void * igPointerList_Create(int arg0);
extern "C" igMetaObject *igPointerList_GetOrCreateMetaObject(void);
extern "C" int igPointerList_GetVTable(void);
extern "C" void igPointerList_EnsureRegistered(void);
extern "C" void igPointerList_Register(void);
extern "C" void igPointerList_GetMetaObjectFunction(void);
extern "C" void igPointerList_InitFields(void);
extern "C" igMetaObject *igDoubleList_GetOrCreateMetaObject(void);
extern "C" int igDoubleList_GetVTable(void);
extern "C" void igDoubleList_EnsureRegistered(void);
extern "C" void igDoubleList_Register(void);
extern "C" void igDoubleList_GetMetaObjectFunction(void);
extern "C" void igDoubleList_InitFields(void);
extern "C" igMetaObject *igFloatListList_GetOrCreateMetaObject(void);
extern "C" int igFloatListList_GetVTable(void);
extern "C" void igFloatListList_EnsureRegistered(void);
extern "C" void igFloatListList_Register(void);
extern "C" void igFloatListList_GetMetaObjectFunction(void);
extern "C" void igFloatList_Create(int arg0);
extern "C" igMetaObject *igFloatList_GetOrCreateMetaObject(void);
extern "C" int igFloatList_GetVTable(void);
extern "C" void igFloatList_EnsureRegistered(void);
extern "C" void igFloatList_Register(void);
extern "C" void igFloatList_GetMetaObjectFunction(void);
extern "C" void igFloatList_InitFields(void);
extern "C" void igUnsignedCharList_Create(int arg0);
extern "C" int igUnsignedCharList_GetVTable(void);
extern "C" void igUnsignedCharList_EnsureRegistered(void);
extern "C" void igUnsignedCharList_Register(void);
extern "C" void igUnsignedCharList_GetMetaObjectFunction(void);
extern "C" void igUnsignedCharList_InitFields(void);
extern "C" void igShortListList_Create(int arg0);
extern "C" igMetaObject *igShortListList_GetOrCreateMetaObject(void);
extern "C" int igShortListList_GetVTable(void);
extern "C" void igShortListList_EnsureRegistered(void);
extern "C" void igShortListList_Register(void);
extern "C" void igShortListList_GetMetaObjectFunction(void);
extern "C" void igShortList_Create(int arg0);
extern "C" igMetaObject *igShortList_GetOrCreateMetaObject(void);
extern "C" int igShortList_GetVTable(void);
extern "C" void igShortList_EnsureRegistered(void);
extern "C" void igShortList_Register(void);
extern "C" void igShortList_GetMetaObjectFunction(void);
extern "C" void igShortList_InitFields(void);
extern "C" void igUnsignedShortList_Create(int arg0);
extern "C" igMetaObject *igUnsignedShortList_GetOrCreateMetaObject(void);
extern "C" int igUnsignedShortList_GetVTable(void);
extern "C" void igUnsignedShortList_EnsureRegistered(void);
extern "C" void igUnsignedShortList_Register(void);
extern "C" void igUnsignedShortList_GetMetaObjectFunction(void);
extern "C" void igUnsignedShortList_InitFields(void);
extern "C" void * igUnsignedIntListNoClean_Create(int arg0);
extern "C" igMetaObject *igUnsignedIntListNoClean_GetOrCreateMetaObject(void);
extern "C" int igUnsignedIntListNoClean_GetVTable(void);
extern "C" void igUnsignedIntListNoClean_EnsureRegistered(void);
extern "C" void igUnsignedIntListNoClean_Register(void);
extern "C" void igUnsignedIntListNoClean_GetMetaObjectFunction(void);
extern "C" void igUnsignedIntList_Create(int arg0);
extern "C" igMetaObject *igUnsignedIntList_GetOrCreateMetaObject(void);
extern "C" int igUnsignedIntList_GetVTable(void);
extern "C" void igUnsignedIntList_EnsureRegistered(void);
extern "C" void igUnsignedIntList_Register(void);
extern "C" void igUnsignedIntList_GetMetaObjectFunction(void);
extern "C" void igUnsignedIntList_InitFields(void);
extern "C" igMetaObject *igLongList_GetOrCreateMetaObject(void);
extern "C" int igLongList_GetVTable(void);
extern "C" void igLongList_EnsureRegistered(void);
extern "C" void igLongList_Register(void);
extern "C" void igLongList_GetMetaObjectFunction(void);
extern "C" void igLongList_InitFields(void);
extern "C" void * igIntListNoClean_Create(int arg0);
extern "C" igMetaObject *igIntListNoClean_GetOrCreateMetaObject(void);
extern "C" int igIntListNoClean_GetVTable(void);
extern "C" void igIntListNoClean_EnsureRegistered(void);
extern "C" void igIntListNoClean_Register(void);
extern "C" void igIntListNoClean_GetMetaObjectFunction(void);
extern "C" igMetaObject *igIntList_GetPublishedMetaObject(void);
extern "C" void * igIntList_Create(int arg0);
extern "C" int igIntList_GetVTable(void);
extern "C" void igIntList_EnsureRegistered(void);
extern "C" void *igIntList_Register(void);
extern "C" void igIntList_GetMetaObjectFunction(void);
extern "C" void igIntList_InitFields(void);
extern "C" igMetaObject *igCharListNoClean_GetOrCreateMetaObject(void);
extern "C" int igCharListNoClean_GetVTable(void);
extern "C" void igCharListNoClean_EnsureRegistered(void);
extern "C" void igCharListNoClean_Register(void);
extern "C" void igCharListNoClean_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCharList_GetPublishedMetaObject(void);
extern "C" void igCharList_Create(int arg0);
extern "C" igMetaObject *igCharList_GetOrCreateMetaObject(void);
extern "C" int igCharList_GetVTable(void);
extern "C" void igCharList_EnsureRegistered(void);
extern "C" void igCharList_Register(void);
extern "C" void igCharList_GetMetaObjectFunction(void);
extern "C" void igCharList_InitFields(void);
extern "C" void igBoolList_Create(int arg0);
extern "C" igMetaObject *igBoolList_GetOrCreateMetaObject(void);
extern "C" int igBoolList_GetVTable(void);
extern "C" void igBoolList_EnsureRegistered(void);
extern "C" void igBoolList_Register(void);
extern "C" void igBoolList_GetMetaObjectFunction(void);
extern "C" void igBoolList_InitFields(void);
extern "C" igMetaObject *igContextExtList_GetOrCreateMetaObject(void);
extern "C" int igContextExtList_GetVTable(void);
extern "C" void igContextExtList_EnsureRegistered(void);
extern "C" void igContextExtList_Register(void);
extern "C" void igContextExtList_GetMetaObjectFunction(void);
extern "C" void * igContextExtInfoList_Create(int arg0);
extern "C" igMetaObject *igContextExtInfoList_GetOrCreateMetaObject(void);
extern "C" int igContextExtInfoList_GetVTable(void);
extern "C" void igContextExtInfoList_EnsureRegistered(void);
extern "C" void igContextExtInfoList_Register(void);
extern "C" void igContextExtInfoList_GetMetaObjectFunction(void);
extern "C" void * igContextExtInfo_Create(int arg0);
extern "C" int igContextExtInfo_GetVTable(void);
extern "C" void igContextExtInfo_EnsureRegistered(void);
extern "C" void igContextExtInfo_Register(void);
extern "C" void igContextExtInfo_GetMetaObjectFunction(void);
extern "C" void igContextExtInfo_InitFields(void);
extern "C" void igContextExt_EnsureRegistered(void);
extern "C" void igContextExt_Register(void);
extern "C" void igContextExt_GetMetaObjectFunction(void);
extern "C" void igContextList_Create(int arg0);
extern "C" int igContextList_GetVTable(void);
extern "C" void igContextList_EnsureRegistered(void);
extern "C" void igContextList_Register(void);
extern "C" void igContextList_GetMetaObjectFunction(void);
extern "C" void igContext_EnsureRegistered(void);
extern "C" void igContext_Register(void);
extern "C" void igContext_GetMetaObjectFunction(void);
extern "C" void igContext_InitFields(void);
extern "C" void igCompoundMetaField_EnsureRegistered(void);
extern "C" void igCompoundMetaField_Register(void);
extern "C" void igCompoundMetaField_GetMetaObjectFunction(void);
extern "C" void igCompoundMetaField_InitFields(void);
extern "C" void igCompoundMetaField_CreateDefaultDescriptor(void);
extern "C" int igCompoundMetaField_GetSize(void);
extern "C" void igCompoundMetaField_AddSubFields(int value);
extern "C" void **igCharMetaField_Create(int arg0);
extern "C" void *igCharMetaField_Clone(void *arg0, void *arg1);
extern "C" int igCharMetaField_GetVTable(void);
extern "C" void igCharMetaField_EnsureRegistered(void);
extern "C" void igCharMetaField_Register(void);
extern "C" void igCharMetaField_GetMetaObjectFunction(void);
extern "C" void igCharMetaField_CreateDefaultDescriptor(void);
extern "C" int igCharMetaField_GetDefaultDescriptor(void);
extern "C" void igCharArrayMetaField_Create(int arg0);
extern "C" int igCharArrayMetaField_GetVTable(void);
extern "C" void igCharArrayMetaField_EnsureRegistered(void);
extern "C" void igCharArrayMetaField_Register(void);
extern "C" void igCharArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCharMetaField_GetPublishedMetaObject(void);
extern "C" void igCharArrayMetaField_InitFields(void);
extern "C" void igCharArrayMetaField_CreateDefaultDescriptor(void);
extern "C" igMetaObject *igCallStackTracer_GetOrCreateMetaObject(void);
extern "C" int igCallStackTracer_GetVTable(void);
extern "C" void igCallStackTracer_EnsureRegistered(void);
extern "C" void igCallStackTracer_Register(void);
extern "C" void igCallStackTracer_GetMetaObjectFunction(void);
extern "C" igMetaObject *igUnsignedIntListNoClean_GetPublishedMetaObject(void);
extern "C" void igCallStackTracer_SetAbstractProxy(void);
extern "C" void igPsx2CallStackTracer_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCallStackTable_GetOrCreateMetaObject(void);
extern "C" int igCallStackTable_GetVTable(void);
extern "C" void igCallStackTable_EnsureRegistered(void);
extern "C" void igCallStackTable_Register(void);
extern "C" void igCallStackTable_GetMetaObjectFunction(void);
extern "C" void igCallStackTable_InitFields(void);
extern "C" void **igBoolMetaField_Create(int arg0);
extern "C" int FUN_00300c60(int, int);
extern "C" int FUN_002ff800(int, int);
extern "C" int igBoolMetaField_Clone(int arg0, int arg1);
extern "C" int igBoolMetaField_GetVTable(void);
extern "C" void igBoolMetaField_EnsureRegistered(void);
extern "C" void igBoolMetaField_Register(void);
extern "C" void igBoolMetaField_GetMetaObjectFunction(void);
extern "C" void igBoolMetaField_CreateDefaultDescriptor(void);
extern "C" int igBoolMetaField_GetDefaultDescriptor(void);
extern "C" void igBoolArrayMetaField_Create(int arg0);
extern "C" int igBoolArrayMetaField_GetVTable(void);
extern "C" void igBoolArrayMetaField_EnsureRegistered(void);
extern "C" void igBoolArrayMetaField_Register(void);
extern "C" void igBoolArrayMetaField_GetMetaObjectFunction(void);
extern "C" igMetaObject *igBoolMetaField_GetPublishedMetaObject(void);
extern "C" void igBoolArrayMetaField_InitFields(void);
extern "C" void igBoolArrayMetaField_CreateDefaultDescriptor(void);
extern "C" void *igAliasMemoryPool_Clone(int arg0, int arg1);
extern "C" int FUN_002d1500(...);
extern "C" int igAliasMemoryPool_GetVTable(void);
extern "C" void igAliasMemoryPool_EnsureRegistered(void);
extern "C" void igAliasMemoryPool_Register(void);
extern "C" void igAliasMemoryPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMemoryPool_GetPublishedMetaObject(void);
extern "C" void igAliasMemoryPool_InitFields(void);
extern "C" int igPageMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" int igPageMemoryPool_Clone(int arg0, int arg1);
extern "C" int igPageMemoryPool_GetVTable(void);
extern "C" void igPageMemoryPool_EnsureRegistered(void);
extern "C" void igPageMemoryPool_Register(void);
extern "C" void igPageMemoryPool_GetMetaObjectFunction(void);
extern "C" void igPageMemoryPool_InitFields(void);
extern "C" int igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum(void);
extern "C" int igArenaMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" int igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum(void);
extern "C" void **igArenaMemoryPool_Create(int arg0);
extern "C" int igArenaMemoryPool_Clone(int arg0, int arg1);
extern "C" int igArenaMemoryPool_GetVTable(void);
extern "C" void igArenaMemoryPool_EnsureRegistered(void);
extern "C" void igArenaMemoryPool_Register(void);
extern "C" void igArenaMemoryPool_InitFields(void);
extern "C" void igStackMemoryPool_Create(int arg0);
extern "C" int igStackMemoryPool_GetVTable(void);
extern "C" void igStackMemoryPool_EnsureRegistered(void);
extern "C" void igStackMemoryPool_Register(void);
extern "C" void igStackMemoryPool_GetMetaObjectFunction(void);
extern "C" void igStackMemoryPool_InitFields(void);
extern "C" int igMallocMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" void igMallocMemoryPool_InitDefaults(int extra0);
extern "C" void *igMallocMemoryPool_Clone(void *self, void *src);
extern "C" int igMallocMemoryPool_GetVTable(void);
extern "C" void igMallocMemoryPool_EnsureRegistered(void);
extern "C" void igMallocMemoryPool_Register(void);
extern "C" void igMallocMemoryPool_GetMetaObjectFunction(void);
extern "C" void igMallocMemoryPool_InitFields(void);
extern "C" int igMemoryDescriptorMetaField_GetVTable(void);
extern "C" void igMemoryDescriptorMetaField_EnsureRegistered(void);
extern "C" void igMemoryDescriptorMetaField_Register(void);
extern "C" void igMemoryDescriptorMetaField_GetMetaObjectFunction(void);
extern "C" void igMemoryDescriptorMetaField_CreateDefaultDescriptor(void);
extern "C" int igMemoryDescriptorMetaField_GetSize(void);
extern "C" void igMemoryDescriptorMetaField_InitDefaults(void *arg0);
extern "C" void igMemoryDescriptorMetaField_AddSubFields(int arg0);
extern "C" int igProgramFile_GetVTable(void);
extern "C" void igProgramFile_EnsureRegistered(void);
extern "C" void igProgramFile_Register(void);
extern "C" void igProgramFile_GetMetaObjectFunction(void);
extern "C" void igProgramFile_InitFields(void);
extern "C" void igElfFile_GetMetaObjectFunction(void);
extern "C" void * igElfFile_Create(int arg0);
extern "C" int igElfFile_GetVTable(void);
extern "C" void igElfFile_EnsureRegistered(void);
extern "C" void igElfFile_Register(void);
extern "C" int igProgramFile_GetPublishedMetaObject(void);
extern "C" void igElfFile_InitFields(void);
extern "C" int igStandardQueue_GetVTable(void);
extern "C" void igStandardQueue_EnsureRegistered(void);
extern "C" void igStandardQueue_Register(void);
extern "C" igMetaObject *igQueue_GetPublishedMetaObject(void);
extern "C" void igStandardQueue_InitFields(void);
extern "C" int igPsx2ThreadManager_GetVTable(void);
extern "C" void igPsx2ThreadManager_EnsureRegistered(void);
extern "C" void igPsx2ThreadManager_Register(void);
extern "C" int igThreadManager_GetPublishedMetaObject(void);
extern "C" void igPsx2ThreadManager_SetWriteProxy(void);
extern "C" int igPsx2Thread_GetVTable(void);
extern "C" void igPsx2Thread_EnsureRegistered(void);
extern "C" void igPsx2Thread_Register(void);
extern "C" igMetaObject *igThread_GetPublishedMetaObject(void);
extern "C" void igPsx2Thread_InitFields(void);
extern "C" int igPsx2Semaphore_GetVTable(void);
extern "C" void igPsx2Semaphore_EnsureRegistered(void);
extern "C" void igPsx2Semaphore_Register(void);
extern "C" igMetaObject *igSemaphore_GetPublishedMetaObject(void);
extern "C" void igPsx2Semaphore_InitFields(void);
extern "C" void igPsx2Media_Create(int arg0);
extern "C" int igPsx2Media_GetVTable(void);
extern "C" void igPsx2Media_EnsureRegistered(void);
extern "C" void igPsx2Media_Register(void);
extern "C" igMetaObject *igMedia_GetPublishedMetaObject(void);
extern "C" void igPsx2Media_InitFields(void);
extern "C" int igPsx2LongTimer_GetVTable(void);
extern "C" void igPsx2LongTimer_EnsureRegistered(void);
extern "C" void igPsx2LongTimer_Register(void);
extern "C" int igLongTimer_GetPublishedMetaObject(void);
extern "C" void igPsx2LongTimer_StaticInitCallback(void);
extern "C" void igPsx2IopRpcConnection_Create(int arg0);
extern "C" igMetaObject *igPsx2IopRpcConnection_GetOrCreateMetaObject(void);
extern "C" int igPsx2IopRpcConnection_GetVTable(void);
extern "C" void igPsx2IopRpcConnection_EnsureRegistered(void);
extern "C" void igPsx2IopRpcConnection_Register(void);
extern "C" void igPsx2IopRpcConnection_GetMetaObjectFunction(void);
extern "C" void igPsx2IopRpcConnection_InitFields(void);
extern "C" int igPsx2Folder_GetVTable(void);
extern "C" void igPsx2Folder_EnsureRegistered(void);
extern "C" void igPsx2Folder_Register(void);
extern "C" igMetaObject *igFolder_GetPublishedMetaObject(void);
extern "C" int igPsx2File_Create(int arg0);
extern "C" int igPsx2File_GetVTable(void);
extern "C" void igPsx2File_EnsureRegistered(void);
extern "C" void igPsx2File_Register(void);
extern "C" void igPsx2File_InitFields(void);
extern "C" void igPsx2File_StaticInitCallback(void);
extern "C" int igPsx2CallStackTracer_GetVTable(void);
extern "C" void igPsx2CallStackTracer_EnsureRegistered(void);
extern "C" void igPsx2CallStackTracer_Register(void);
extern "C" igMetaObject *igCallStackTracer_GetPublishedMetaObject(void);
extern "C" void igPsx2CallStackTracer_SetWriteProxy(void);
extern "C" int memset(...);
extern "C" int printf(...);
extern "C" int igAliasMemoryPool_GetAliasedMemoryPool(void *arg0);
extern "C" int igAliasMemoryPool_GetRawMemory(void);
extern "C" void igAliasMemoryPool_SetRawMemory(int *outStatus);
extern "C" int igAliasMemoryPool_IsAlchemyMemory(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_29(void);
extern "C" void igAliasMemoryPool_SetSize(int *statusOut);
extern "C" int igAliasMemoryPool_GetSize(void);
class igResult;
extern "C" igResult igAliasMemoryPool_Configure(igAliasMemoryPool *self, igMemoryPoolInfo *info);
extern "C" int igAliasMemoryPool_CallocateAligned(igAliasMemoryPool *arg0, int arg1, int arg2, unsigned short alignment);
extern "C" int igAliasMemoryPool_OwnsAllocation(igAliasMemoryPool *self, int poolIndex);
extern "C" int __do_global_ctors();
extern "C" int __do_global_dtors();
extern "C" void FUN_002d1660(void);
extern "C" void FUN_002d1690(int extra0);
extern "C" int FUN_002d1e40(...);
extern "C" void igObjectSystem_Acquire(int arg0);
extern "C" int FUN_002d2800(...);
extern "C" void igObjectSystem_Release(void);
extern "C" int igMetaEnum_GetEmpty(void);
extern "C" void igObjectSystem_SetIniText(int arg0);
extern "C" void igObjectSystem_CheckHeaderVersion(void *arg0, int arg1);
extern "C" void *igObjectSystem_Construct(void *arg0);
extern "C" int igObjectSystem_GetRootPath(int *p);
extern "C" int igObjectSystem_GetBasePath(int *p);
extern "C" int *getenv(...);
extern "C" igMetaObject *igMediaFile_GetPublishedMetaObject(void);
extern "C" int igObjectSystem_AppendMetaEnum(int *p, int extra1);
extern "C" int igObjectSystem_AddExitCallback(int *p, int extra1);
extern "C" void igObjectSystem_RunRegistrationCallbacks(int *arg0, int arg1);
extern "C" int strncpy(...);
extern "C" void igObjectSystem_SetEventTrackerFileName(char *arg0, char *arg1);
extern "C" void igObjectSystem_SetSystemPoolEventTrackerFileName(char *a, char *b);
extern "C" void igObjectSystem_SetSymbolsFileName(void *arg0, int arg1);
extern "C" void FUN_002ed5c0(void *);
extern "C" int igObjectSystem_OperatorNew(int extra0);
extern "C" int igObjectSystem_OperatorDelete(int extra0);
extern "C" unsigned short igBoolArrayMetaField_GetSize(void *arg0);
extern "C" int sscanf(...);
extern "C" int strncasecmp(...);
extern "C" int igBoolMetaField_ValueFromString(void *arg0, char *arg1, int arg2);
extern "C" int sprintf(...);
extern "C" void igBoolMetaField_ValueToString(int *arg0, void *arg1, unsigned char *arg2);
extern "C" int **igBoolMetaField_Construct(int **arg0, int extra1);
extern "C" int **igBoolMetaField_Init(int **arg0);
extern "C" int **igBoolMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igBoolMetaField_Destruct(int extra0);
extern "C" int igBoolMetaField_GetSize(void);
extern "C" void igBoolMetaField_SetDefaultValue(void **arg0, char arg1);
extern "C" int igBoolMetaField_GetAlignment(void);
extern "C" void igCallStackTable_SetCapacity(int a0, int a1);
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
    virtual unsigned int vfunc_29(unsigned int *stack);
    virtual int vfunc_30(unsigned int *stack, int offset);
    virtual void vfunc_31(int hashCapacity);
    int _capacity;
    int _hashCapacity;
    igTDataList<unsigned int> *_callStacks;
    igTDataList<int> *_hashIndex;
};
extern "C" void igCallStackTable_SetHashCapacity(igCallStackTableView *table, int hashCapacity);
extern "C" void igCallStackTable_ApplyCapacity(igCallStackTableView *table);
extern "C" void igCallStackTable_RemoveAllCallStacks(igCallStackTableView *table);
extern "C" int igCallStackTable_GetCallStackCount(igCallStackTableView *table);
extern "C" int *igCallStackTracer_CaptureCallStack(int *arg0);
extern "C" int igCallStackTracer_HasSymbols(void);
extern "C" void Gap__Core__igCallStackTracer__vfunc_29(void);
extern "C" void Gap__Core__igCallStackTracer__vfunc_30(void);
extern "C" void igCharArrayMetaField_SetDefaultElement(void *arg0, int arg1, char arg2);
extern "C" int igCharMetaField_ValueFromString(void *arg0, char *arg1, int arg2);
extern "C" void igCharMetaField_ValueToString(int *arg0, int arg1, char *arg2);
extern "C" int **igCharMetaField_Construct(int **arg0, int extra1);
extern "C" int **igCharMetaField_Init(int **arg0);
extern "C" int **igCharMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igCharMetaField_Destruct(int extra0);
extern "C" int igCharMetaField_GetSize(void);
extern "C" void igCharMetaField_SetDefaultValue(void **arg0, char arg1);
extern "C" int igCharMetaField_GetAlignment(void);
extern "C" unsigned short igCompoundMetaField_GetElementSize(void *arg0);
extern "C" void igCompoundMetaField_SetToDefault(void *arg0, int arg1);
extern "C" void igCompoundMetaField_CopyDefaultToValue(void *arg0, int arg1);
extern "C" void igCompoundMetaField_DeepCopy(void *arg0, int arg1, int arg2);
extern "C" void igCompoundMetaField_CopyReference(void *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_GetDescriptor(void);
extern "C" void igCompoundMetaField_SwapValue(void *arg0, int arg1);
extern "C" int igCompoundMetaField_ValueFromString(int *arg0, int arg1, int arg2, int arg3);
extern "C" int strcpy(...);
extern "C" int strlen(...);
extern "C" void FUN_002d6090(void);
extern "C" int FUN_002d60a0(void);
extern "C" int FUN_002d6380(void);
extern "C" int strcmp(...);
extern "C" int igDataList_GetElementSize(void);
extern "C" int memcpy(...);
extern "C" int List_Resize(void *list, int count, int extra2);
extern "C" int memmove(...);
extern "C" int FUN_002d7280(...);
extern "C" void igRendererOrderedList_Clear(char *arg0);
extern "C" int FUN_00301000(...);
extern "C" int FUN_002fb8d0(int);
extern "C" int FUN_002f8920(int);
extern "C" int FUN_002f04f0(int);
extern "C" void igDependencyOrderedList_AddCheckPoint(void *arg0, int arg1);
extern "C" void igDirEntry_RetainSharedRef(void);
extern "C" void igDirEntry_ReleaseSharedRef(void);
extern "C" int igDirEntry_GetSharedEntry(int arg0);
extern "C" int igDirEntry_IsRefMemory(void);
extern "C" void igDirEntry_SetMemoryPoolHandle(void);
extern "C" int igDirEntry_GetMemoryPoolHandle(void);
extern "C" void igDirEntry_WriteMemory(void);
extern "C" void igDirEntry_WriteObject(void);
extern "C" void igDirEntry_PrepareWrite(void);
extern "C" void igDirEntry_ComputeWriteSize(void);
extern "C" void igDirEntry_ReadMemory(void);
extern "C" void igDirEntry_RegisterRef(void);
extern "C" void igDirEntry_PostProcess(void);
extern "C" void igDirEntry_ResolveRefOld(void);
extern "C" void igDirEntry_ResolveRef(void);
extern "C" void igDirEntry_Resolve(void);
extern "C" void igDirEntry_CreateRef(void);
extern "C" void igDirEntry_InitDefaults(int arg0);
extern "C" void igDirEntry_SetRef(void *arg0, int arg1);
extern "C" void igDirEntry_RetainRef(void);
extern "C" void igDirEntry_ReleaseRef(void);
extern "C" void igDirectory_RegisterDependentMetaObjects(void);
extern "C" void *thunk_igDirectory_GetEntry(int *arg0, int arg1);
extern "C" int igDirectory_GetObject(void *arg0, int arg1);
extern "C" void *igDirectory_GetEntry(int *arg0, int arg1);
extern "C" void igDirectory_RemoveInfoByName(void *arg0, int arg1);
extern "C" void igDirectory_AddInfo(void *arg0, void *arg1);
extern "C" void * igDirectory_FindInfoByName(int *arg0, int arg1);
extern "C" int igDirectory_GetInfo(void *arg0, int arg1);
extern "C" int igDirectory_HasEntry(void *dir, unsigned key);
extern "C" int igDirectory_AddObjectRecursive(int arg0, int arg1, int arg2, int extra3);
extern "C" igMetaObject *igDirEntry_GetMeta(void);
extern "C" int igDirectory_GetRefByName(int arg0, int arg1);
extern "C" int igDirectory_GetObjectByName(int arg0, int arg1);
extern "C" void *igDirectory_GetEntryByName(int arg0, int arg1);
extern "C" int igDirectory_GetInfoCount(void *arg0);
struct igDirectoryView;
extern "C" int igDirectory_AddLoadedRef(igDirectoryView *arg0);
extern "C" int igDoubleMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igDoubleMetaField_ValueToString(int *arg0, int arg1, long long *arg2);
extern "C" int igDoubleMetaField_GetSize(void);
extern "C" void igDoubleMetaField_SetDefaultDouble(void **arg0, long long arg1);
extern "C" int igDoubleMetaField_GetAlignment(void);
extern "C" void igDriverDatabase_ReleaseDefaults(int self);
extern "C" void igDriverDatabase_SetCurrentProperty(void *arg0, int arg1, int arg2);
extern "C" int igDriverDatabase_GetCurrentProperty(void *arg0, int arg1);
extern "C" int StringList_CopyRetained(...);
extern "C" int igDriverDatabase_LoadFromFile(void *arg0, int arg1, int arg2);
extern "C" int igDriverDatabase_ClearRawDatabase(int *p);
extern "C" void *igDriverDatabase_ConfigNode_Destruct(void *arg0, long long arg1);
extern "C" int FUN_002daab0(void);
extern "C" void igDriverDatabase_LoadFromString(void *arg0, int arg1);
extern "C" int igDriverDatabase_GetOSName(void *arg0);
extern "C" int igDriverDatabase_GetCpuVendor(void *arg0);
extern "C" int igDriverDatabase_GetCpuType(void *arg0);
extern "C" bool igDriverDatabase_ReadLineFromString(igDriverDatabase *self, char **cursor, char *out, int size);
extern "C" int FUN_0012a78c(void *);
extern "C" void igDriverDatabase_SkipWhitespace(int *arg0);
extern "C" void igDriverDatabase_TrimTrailingWhitespace(int arg0, char *arg1);
extern "C" bool igDriverDatabase_ReadToken(char *arg0, int *arg1);
extern "C" bool igDriverDatabase_ParseOperator(char *arg0, int *arg1);
extern "C" int igDriverDatabase_GetPropertyValueType(int arg0, int arg1);
extern "C" unsigned char igDriverDatabase_CompareTyped(igDriverDatabase *self, int valueType, char *actual, int compareMode, char *expected);
extern "C" int strcasecmp(...);
extern "C" int igDriverDatabase_CompareString(int dummy0, int arg1, int arg2, int arg3);
extern "C" int igDriverDatabase_CompareValues(int dummy0, int arg1, int arg2, int arg3);
extern "C" bool igDriverDatabase_CompareFloat(int unused, int mode, float a, float b);
extern "C" int igDriverDatabase_CompareBool(int p, unsigned char a, int m, unsigned char b);
extern "C" void *igDriverDatabase_Setting_Construct(void *arg0);
extern "C" void *igDriverDatabase_SettingsNode_Construct(void *arg0);
extern "C" void *igDriverDatabase_PropertyNode_Construct(void *arg0, int arg1);
extern "C" void igEnumArrayMetaField_SetDefault(void *arg0, int arg1);
extern "C" int igEnumMetaField_ValueFromString(void *arg0, int *arg1, int arg2);
extern "C" int **igEnumMetaField_Construct(int **arg0, int extra1);
extern "C" int **igEnumMetaField_Init(int **arg0);
extern "C" int **igEnumMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igEnumMetaField_Destruct(int extra0);
extern "C" int igEnumMetaField_GetSize(void);
extern "C" int igEnumMetaField_GetAlignment(void);
extern "C" int thunk_igErrorHandler_GetInstance();
extern "C" void igErrorHandler_ReleaseInstance(void);
extern "C" int igErrorHandler_GetInstance(void);
extern "C" void igEventTracker_CodeReference(void);
extern "C" void igEventTracker_SetCapacity(int a0, int a1);
extern "C" int igEventTracker_GetCount(int *p);
extern "C" void igEventTracker_ReadEventType(int *arg0, char *arg1, char *arg2, int *arg3);
extern "C" void igEventTracker_ReadEventKey(int *arg0, char *arg1, char *arg2, int *arg3);
extern "C" void igEventTracker_ReadEventValue(int *result, igEventTracker *self, char *record, int *value);
extern "C" int igEventTracker_GetNextEventOffset(class igEventTrackerView *self, int offset);
extern "C" int igEventTracker_GetEventFormat(void *arg0, int arg1);
extern "C" int igEventTracker_GetEventTypeName(void *arg0, int arg1);
extern "C" int igEventTracker_GetNotificationCodeName(void *arg0, int arg1);
extern "C" int igEventTracker_InitEvent(int arg0);
extern "C" int igEventTracker_CopyEvent(int arg0, int arg1);
extern "C" void *igEventTracker_InitMemoryEvent(void *arg0, int arg1, void *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18);
extern "C" void *igEventTracker_InitMarkerEvent(void *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8);
extern "C" void *igEventTracker_DestructEvent(void *arg0, long long arg1);
extern "C" void igEventTracker_ClearEvent(int arg0);
extern "C" int igEventTracker_FindFreeEventDataSlot(void *arg0);
extern "C" int igEventTracker_GetEventDataInt(int arg0, int arg1);
extern "C" void igEventTracker_SetEventDataInt(void *arg0, int arg1, int arg2);
extern "C" int igEventTracker_GetEventDataUnsigned(int arg0, int arg1);
extern "C" void igEventTracker_SetEventDataUnsigned(void *arg0, int arg1, int arg2);
extern "C" int igEventTracker_GetEventDataString(int arg0, int arg1);
extern "C" void igEventTracker_SetEventDataString(void *arg0, int arg1, int arg2);
extern "C" void igEventTracker_GetEventDataUnsigned3(int arg0, int arg1, void *arg2);
extern "C" int strcat(...);
extern "C" void igExternalDirEntry_ReleaseDefaults(void **arg0);
extern "C" void ***FUN_002e2fb0(void);
extern "C" void igFile_SetFileName(int *arg0, const char *name);
class igFileView;
extern "C" void igFile_SkipToChar(igFileView *arg0, long long arg1);
extern "C" void igAdxFile_SetOpenMode(int a0, int a1);
extern "C" bool FilePath_IsAbsolute(const char *path);
extern "C" bool FilePath_HasDirectory(const char *path);
extern "C" void igAdxFile_SetBasePath(int arg0);
extern "C" void igFile_ReadAsync(igFileView *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4);
extern "C" void igAdxFile_LoadSearchFilePath(void);
extern "C" int igAdxFile_GetSearchPaths(void);
extern "C" char * strchr(...);
extern "C" int igAdxFile_GetNextSearchPath(char **arg0, char *arg1, int arg2);
extern "C" int igFloatMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" int fptodp(float);
extern "C" void igFloatMetaField_ValueToString(int *arg0, int arg1, float *arg2);
extern "C" int igFloatMetaField_GetSize(void);
extern "C" void igFloatMetaField_SetDefault(void **arg0, float fparg0);
extern "C" int igFloatMetaField_GetAlignment(void);
extern "C" int dpsub(...);
extern "C" int igIGBFile_GetObjectSize(void *arg0, int arg1);
extern "C" void igIGBFile_SetDefaultName(int *arg0);
extern "C" void igIGBFile_RegisterBlindObjectsConfig(void);
class igIGBFileView;
extern "C" int igIGBFile_GetCurrentPosition(igIGBFileView *arg0);
extern "C" void igIGBFile_CloseAfterRead(igIGBFileView *arg0);
extern "C" int igIGBFile_AbortRead(igIGBFileView *arg0);
extern "C" void igIGBFile_EnsureConcrete(int *arg0, void *arg1);
class igInfoView;
struct igDirectoryView;
extern "C" bool FUN_002e2d30(igDirectoryView *directory, igInfoView *info, char *key, igObject *object);
extern "C" int igInfo_FindObjectReference(void **arg0, int arg1, int arg2);
extern "C" int igObject_GetFieldValueByName(void **arg0, int arg1);
extern "C" int igIntArrayMetaField_GetSize(void *arg0);
extern "C" void igIntArrayMetaField_SetDefaultValue(void **arg0, int arg1);
extern "C" int igIntMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igIntMetaField_ValueToString(int *arg0, int arg1, int *arg2);
extern "C" int igIntMetaField_GetSize(void);
extern "C" int **igIntMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igIntMetaField_Destruct(int extra0);
extern "C" void igIntMetaField_SetDefault(void **arg0, int arg1);
extern "C" int igIntMetaField_GetAlignment(void);
extern "C" int ObjectPointerList_FindIndex(char *arg0, int arg1);
extern "C" struct StringPool *StringPool_Destroy(struct StringPool *self, long long delete_flag);
extern "C" void StringPool_OperatorDelete(int arg0);
extern "C" void StringPool_SetBlockSize(int a0, int a1);
extern "C" void igLocationTable_SetHashCapacity(int a0, int a1);
class igLocationTableView;
extern "C" void igLocationTable_Allocate(igLocationTableView *arg0);
extern "C" int igLocationTable_IsInitialized(void *arg0);
extern "C" void igLocationTable_Resize(int *arg0, void *arg1, int arg2);
extern "C" int igLongMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igLongMetaField_ValueToString(int *arg0, int arg1, long long *arg2);
extern "C" int igLongMetaField_GetSize(void);
extern "C" void igLongMetaField_SetDefault(void **arg0, long long arg1);
extern "C" int igLongMetaField_GetAlignment(void);
extern "C" void igMedia_CreateMediaList(void);
extern "C" void igMedia_AddMedia(int arg0);
extern "C" void igMedia_ReleaseMediaList(void);
extern "C" void igMedia_SetDefaultMedia(int arg0);
extern "C" void **igMediaFile_OpenFile(void **arg0, const char *fileName, int arg2);
class igMediaFileView;
extern "C" void igMediaFile_ReadAsync(igMediaFileView *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4);
extern "C" int vsprintf(...);
extern "C" int igMediaFile_UngetChar(igMediaFileView *a, int c);
extern "C" int free(...);
extern "C" void *Memory_AllocateDefaultBuffer(unsigned int size);
extern "C" void *Memory_AllocateAligned(unsigned int size, unsigned short alignment);
extern "C" void *Memory_Callocate(unsigned int size, unsigned int alignment);
extern "C" void *Memory_ReallocateBuffer(void *buffer, unsigned int size);
extern "C" void *Memory_ReallocateAligned(void *buffer, unsigned int size, unsigned short alignment);
extern "C" void *Memory_ReallocateBufferAlias(void *buffer, unsigned int size);
extern "C" void *thunk_Memory_ReallocateAligned(void *buffer, unsigned int size, unsigned short alignment);
extern "C" int Memory_FreeBuffer(void *buffer);
extern "C" int Memory_FreeBufferAliasA(void *buffer);
extern "C" unsigned int Memory_GetBufferSize(void *buffer);
extern "C" void *Memory_DuplicateBuffer(void *source);
extern "C" void Memory_FreeBufferAliasB(void *buffer);
extern "C" void Memory_FreeOwnedBufferUnchecked(void *buffer);
extern "C" void Memory_DumpMemory(unsigned int size, unsigned int perLine, unsigned int digits, unsigned int addr, long long length, const char *name);
extern "C" void *Memory_SystemAllocate(unsigned int size);
extern "C" void Memory_SystemFree(void *block);
extern "C" void igMemoryDirEntry_IsRefMemory(int arg0);
extern "C" int igMemoryDirEntry_GetMeta(void);
extern "C" void igMemoryDirEntry_RegisterRef(void);
extern "C" void igMemoryFile_CreateEntryList(void);
extern "C" void igMemoryFile_ReleaseEntryList(void);
extern "C" void igMemoryFile_AddMemoryFileEntry(int arg0, int arg1, int arg2);
extern "C" void igMemoryFile_LookupMemoryBuffer(int arg0, int *arg1, int *arg2);
class igMemoryFileView;
extern "C" void igMemoryFile_Close(igMemoryFileView *self);
extern "C" int igMemoryFile_Write(void);
extern "C" int igMemoryFile_Scanf(void *arg0, int arg1, ...);
extern "C" int igMemoryFile_Printf(int a, int b, ...);
extern "C" int igMemoryFile_Flush(void);
extern "C" int igMemoryFile_PutChar(void);
extern "C" int igMemoryFile_GetString(void);
extern "C" int igMemoryFile_PutString(void);
extern "C" int igMemoryFile_Seek(igMemoryFileView *self, int offset, int whence);
extern "C" int igMemoryFile_UngetChar(void);
extern "C" int **igMemoryPool_Initialize(int **arg0);
extern "C" int **igMemoryPool_Construct(int **arg0);
extern "C" igMemoryPool *igMemoryPool_CopyConstruct(igMemoryPool *self, igMemoryPool *source);
extern "C" int igMemoryPool_Destruct(int extra0);
extern "C" int malloc(...);
extern "C" void * igObject_OperatorNew(int a0, int a1, int extra2);
extern "C" int igObject_OperatorDelete(int extra0);
extern "C" int (*DAT_00586f50)();
extern "C" int igMemoryPool_HandleOutOfMemory(int arg0, int arg1, int arg2);
extern "C" void igMemoryPool_InitDefaults(void *arg0);
extern "C" void igMemoryPool_ReleaseDefaults(igMemoryPoolView *pool);
extern "C" void Memory_GetDefaultHandleAllocator(void);
extern "C" void * Memory_GetDefaultAllocator(void);
extern "C" int Memory_GetNonTrackedAllocator(void);
extern "C" void igMemoryDictionary_SetCurrent(void *arg0);
extern "C" void igMemoryPool_RegisterPool(void **arg0);
extern "C" void igMemoryPool_UnregisterPool(void **arg0);
extern "C" void *Memory_FindOwningAllocator(int arg0);
extern "C" void igMemoryPool_TransferAllocation(int *arg0);
extern "C" int igMemoryPool_CanTransferTo(void);
extern "C" int igMemoryPool_GetAllocationPoolIndex(void);
extern "C" void igAllocator_EncodeIndexAlias(int extra0);
extern "C" void igMemoryPool_SetPoolIndex(void);
extern "C" igMemoryPoolView *igAllocator_ResolveEncodedIndex(int index);
extern "C" void igMemoryPool_CollectMemoryRegions(void);
extern "C" void igMemoryPool_CollectAllMemoryRegions(int arg0, int extra1);
extern "C" void igMemoryPool_SetPreSize(int *arg0);
extern "C" int igMemoryPool_GetPreSize(void);
extern "C" igResult igMemoryPool_Configure(void **arg1, void *arg2);
extern "C" void igMemoryPool_PrintGlobalStatistics(char *arg0);
extern "C" void igMemoryPool_DisplayOutstandingAllocations(void);
extern "C" int igMemoryPool_Trim(void);
extern "C" bool igMemoryPool_TrimAllPools(int arg0, int arg1);
extern "C" int igMemoryPool_StrDup(void **arg0, int arg1);
extern "C" int igMemoryPool_StrDupAligned(void **arg0, int arg1, unsigned short arg2);
extern "C" int igMemoryPool_GetEventTracker(void);
extern "C" void igMemoryPool_SetScopeFlags(int arg0);
extern "C" void igMemoryPool_TrackEvent(void **arg0, int arg1, int arg2, int arg3);
extern "C" int igMemoryPool_AllocateElementTracked(igMemoryPoolView *pool, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_AllocateTracked(igMemoryPoolView *pool, unsigned int size, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_AllocateAlignedTracked(igMemoryPoolView *pool, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_CallocateTracked(igMemoryPoolView *pool, int count, int size, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_CallocateAlignedTracked(igMemoryPoolView *pool, int count, int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_ReallocateAlignedTracked(igMemoryPoolView *pool, void *block, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_StrDupTracked(igMemoryPoolView *pool, const char *string, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" int igMemoryPool_StrDupAlignedTracked(igMemoryPoolView *pool, const char *string, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void igMemoryPool_GangFreeTracked(void **arg0, unsigned int arg1, int *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
extern "C" int FUN_002f1e30(igMemoryPoolView *pool, int size, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void igMemoryPool_FreeTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void FUN_002f2070(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void Memory_ShutdownAllocatorRegistries(void **rootAllocator);
extern "C" void igMemoryPool_SetDefaults(void *arg0);
extern "C" void igMemoryPool_Shutdown(void);
extern "C" void igMemoryPool_UpdateGlobalStatistics(long long arg0, long long arg1, int arg2);
extern "C" void igMemoryPool_EnableAllocationLock(int *status_out);
extern "C" char * strstr(...);
extern "C" int igMemoryPoolContextInfo_GetPoolInfo(int arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_SetPoolName(int self, int recordIndex, int name);
extern "C" int igMemoryPoolContextInfo_FindPoolIndexByName(int arg0, char *arg1);
extern "C" int strncmp(const char *a, const char *b, unsigned int n);
extern "C" int igMemoryPoolContextInfo_GetPoolIndexByName(int arg0, char *arg1);
extern "C" int igMemoryPoolContextInfo_FindPoolIndex(int arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_SetDirectory(void *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_ResetPools(char *arg0);
extern "C" void igMemoryPoolContextInfo_TrimCapacity(void **arg0);
extern "C" void Gap__Core__igMemoryPoolContextInfo__resetFields(void **arg0, int arg1);
extern "C" void Gap__Core__igMemoryPoolContextInfo__destructFields(void **arg0);
extern "C" void FUN_002f48c0(void);
extern "C" void igMemoryPoolContextInfo_Shutdown(char *arg0);
extern "C" igMetaObject *igMemoryPool_GetMeta(void);
extern "C" void igMemoryPoolContextInfo_ReleaseContextInfo(void *arg0);
extern "C" void FUN_002f5cc0(int *arg0);
extern "C" void MemoryContext_RemoveAllocator(void *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_CompareNames(int arg0, int arg1);
extern "C" void qsort(void *, int, int, int (*)(const void *, const void *));

extern "C" int Memory_GetCurrentContext(void);
extern "C" void * igMemoryPoolContextInfo_Allocate(int arg0);
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *allocation);
extern "C" void Memory_PrintPoolStatistics(int arg0, void *pool);
extern "C" int Memory_GetCurrentContextAlias();
extern "C" void * Memory_GetAllocatorBySelector(int selector);
extern "C" void * Memory_GetAllocatorByName(int name);
extern "C" int Memory_GetPoolNameByIndex(int arg0);
extern "C" void * Memory_GetPoolName(int arg0);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolHandle(int arg0);
extern "C" void * Memory_GetCurrentAllocator(void);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolInfoCount(void *arg0);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolInfo(void *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_AdoptMemoryPoolInfo(void *arg0, void *arg1);
extern "C" int igMemoryPoolContextInfo_AddMemoryPoolInfo(int *p, int extra1);
extern "C" void igMemoryPoolContextInfo_ClearMemoryPoolInfos(void *arg0);
extern "C" void igMemoryPoolInfo_UserRegistryLoad(int *arg0, int *arg1, int arg2, int arg3);
extern "C" void igMemoryPoolInfo_Print(igMemoryPoolInfo *info);
extern "C" void *igMemoryPoolInfoList_Allocate(unsigned int size);
extern "C" void igMemoryPoolInfoList_Delete(void *block);
extern "C" int igMemoryRefArrayMetaField_ReadRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
class igMetaFieldView;
extern "C" int igMemoryRefMetaField_WriteRawFieldMem(igMetaFieldView *self, int *source, void *dest, int directory, int swap);
extern "C" unsigned char GPR_00554c20;
extern "C" unsigned char GPR_00554c24;
extern "C" char text_s_s_s_writeRawFieldMem_0x_x_0_0x[];
extern "C" char text_s_writeRawFieldMem_0x_x_0_0x_x_Not[];
extern "C" int igMemoryRefArrayMetaField_WriteRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4);
extern "C" int igMemoryRefMetaField_GetSize(void);
extern "C" void igMemoryRefMetaField_SetDefaultWord(void **self, int defaultWord);
extern "C" int igMemoryRefMetaField_GetPoolName(int *p);
extern "C" void igMemoryRefMetaField_Destruct(igMemoryRefMetaField *self);
extern "C" void igMetaEnum_GetNameAt(int *arg0, void *arg1, int arg2);
extern "C" int igMetaEnum_GetValueAt(void *arg0, int arg1);
extern "C" __internalObjectList *igMetaField_GetMetaFieldList(void);
extern "C" int igMetaField_GetAlignment(void);
extern "C" int igMetaField_GetSize(void);
extern "C" void igMetaField_IgnoreReset(void);
extern "C" int igMetaField_GetDescriptor(void);
extern "C" int igMetaField_AlignSize(void *p, int size);
class igMetaFieldView;
extern "C" int igMetaField_ReadRawFieldMemAligned(igMetaFieldView *field, void *object, char *data, void *directory, unsigned char swap);
extern "C" unsigned short igMetaField_WriteRawFieldMem(igMetaFieldView *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void igMetaField_ShallowCopy(int a0, int a1, int a2);
extern "C" void igMetaField_DeepCopy(int a0, int a1, int a2);
extern "C" void igMetaField_ConstructCopy(int a0, int a1, int a2);
extern "C" void igMetaField_DeepCopyValue(void *arg0, int arg1, int arg2);
extern "C" void igMetaField_CopyReference(void *arg0, int arg1, int arg2);
extern "C" void igMetaField_IgnoreCopy(void);
extern "C" int igMetaField_GetElementSize(void **arg0);
extern "C" void igMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igMetaField_ValueToString(int *arg0, void *arg1);
extern "C" int igMetaField_IsAlikeByTechnique(void **arg0, int arg1, int arg2, int arg3);
extern "C" int igMetaField_IsAlikeExactly(int a0, int a1, int a2);
extern "C" int igMetaField_IsAlikeDeep(int a0, int a1, int a2);
extern "C" int igMetaField_IsAlikeShallow(int a0, int a1, int a2);
extern "C" int igMetaField_IsAlikeIgnore(void);
extern "C" unsigned char igMetaField_Compare(int a0, int a1, int a2, int a3);
extern "C" void igMetaField_ReleaseElements(void);
extern "C" void igMetaField_ConstructValue(void);
extern "C" void igMetaField_DestructValue(void);
extern "C" void igMetaField_ZeroValue(void);
extern "C" void igMetaField_ClearValue(void);
extern "C" void igMetaField_Print(void *arg0, int arg1, int arg2, const char *arg3);
extern "C" void igMetaField_UserPostRead(int arg0);
extern "C" int igMetaField_IsConstruct(void);
extern "C" void *igMetaObject_CreateInstanceDefault(void *meta);
extern "C" void igMetaObject_FinalizeAndAppendField(void *meta,void *field);
extern "C" int FUN_002fdef0(int a0, int a1);
extern "C" int igObjectSystem_FindMetaByNameDefault(const char *name);
extern "C" void igMetaObject_AddExitCallback(int arg0);
extern "C" void igMetaObject_AddRegistrationCallback(int arg0);
extern "C" void igMetaObject_FinalizeFieldLayoutTree(int arg0);
extern "C" int igMetaObject_GetPersistentFieldCount(int arg0);
extern "C" int igMetaObject_GetPoolName(int *p);
extern "C" int igObject_Destruct(int extra0);
extern "C" void Gap__Core__igObject__constructFields(int extra0, int extra1);
extern "C" void Gap__Core__igObject__destructFields(int extra0);
extern "C" void igObject_UserDeepCopy(void);
extern "C" void Gap__Core__igObject__userConstruct(void);
extern "C" void Gap__Core__igObject__userDestruct(void);
extern "C" void igObject_UserShallowCopy(void);
extern "C" int igObject_UserIsAlikeDeep(void);
extern "C" int igObject_UserIsAlikeShallow(void);
extern "C" void Gap__Core__igObject__resetFields(int extra0, int extra1);
extern "C" void igObject_InitDefaults(int extra0);
extern "C" void igObject_ReleaseDefaults(int extra0);
extern "C" void igObject_UserPreWrite(void);
extern "C" void igObject_UserWriteFilePreProcess(void);
extern "C" void igObject_UserPostLoad(void);
extern "C" void igObject_UserPostRead(void);
extern "C" void igObject_TrimCapacity(int extra0);
extern "C" void igObject_UserApplyWriteProxy(void);
extern "C" void igObject_UserMakeConcrete(void);
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
extern "C" int thunk_Memory_FreeBuffer(int extra0);
extern "C" void igObject_Destroy(void *input);
class igObjectDispatchView;
extern "C" void igObject_ZeroFields(igObjectDispatchView *object);
extern "C" void igObject_ConstructFields(igObjectDispatchView *object);
extern "C" void igObject_ResetFields(igObjectDispatchView *object);
extern "C" void igObject_ResetUnconstructedFields(igObjectDispatchView *object);
extern "C" void igObject_DestructFieldValues(int *arg0);
extern "C" void igObject_ClearFieldValues(int *arg0);
extern "C" void igObject_Print(void **arg0, int arg1, int arg2);
extern "C" void igObject_CopyFields(igObjectDispatchView *self, int source);
extern "C" void igObject_DeepCopy(igObjectDispatchView *self, igObjectDispatchView *source);
extern "C" void igObject_ShallowCopy(igObjectDispatchView *self, int source);
extern "C" int igObject_IsAlikeExactly(void *arg0, void *arg1);
extern "C" void igObject_Copy(int arg0, int arg1, int arg2);
extern "C" int igObject_CloneViaMetadata(void **source, int copyMode);
extern "C" void *igObject_GetAllocationBase(void *self);
extern "C" int igObject_AllocateStorage(int object, int size);
extern "C" int igObject_MallocAligned(int object, int size, unsigned short alignment);
extern "C" int igObject_Callocate(int object, int size, int option);
extern "C" int igObject_Reallocate(int object, int storage, int size);
extern "C" int igObject_ReallocateAligned(int object, int storage, int size, unsigned short alignment);
extern "C" void igObject_FreeStorage(int object, int storage);
extern "C" void igObject_FreeMemory(int object, int storage);
extern "C" int igObject_DuplicateString(int self, int string);
extern "C" int igObjectDirEntry_GetMeta(void);
class igObjectDirEntryView;
extern "C" void igObjectDirEntry_PrepareWrite(igObjectDirEntryView *arg0);
extern "C" int igProperty_FindByPointer(void *arg0, void *arg1, int arg2);
extern "C" int igProperty_FindBySortedKey(void *arg0, void *arg1, int arg2);
extern "C" int igProperty_FindInsertionIndex(void *arg0, void *arg1, unsigned int arg2);
extern "C" int igObjectRefArrayMetaField_ReadRawFieldMem(void *arg0, int arg1, char *arg2, int arg3, int arg4);
extern "C" void igObjectRefArrayMetaField_SetToDefault(void *arg0, int arg1);
extern "C" void igObjectRefArrayMetaField_CopyReference(void *arg0, int arg1, int arg2);
extern "C" void igObjectRefArrayMetaField_ShallowCopy(int *arg0, int arg1, int arg2);
extern "C" int igObjectRefArrayMetaField_GetSize(void *arg0);
extern "C" void igObjectRefMetaField_ReleaseDefaults(int arg0);
extern "C" void igObjectRefMetaField_InitDefaults(void **self);
extern "C" void igObjectRefMetaField_SetValue(int a0, int a1, int a2);
extern "C" void igObjectRefMetaField_SetToDefault(void *arg0, int arg1);
extern "C" void igObjectRefMetaField_CopyDefaultToValue(char *arg0, int arg1);
extern "C" void igObjectRefMetaField_CopyReference(int arg0, int arg1, int arg2);
extern "C" void igObjectRefMetaField_Destruct(igObjectRefMetaField *self);
extern "C" int igObjectStringMap_GetObject(void *arg0, int extra1);
extern "C" int igObjectStringMap_GetCount(void *arg0);
extern "C" int igObjectStringMap_GetObjectAt(void *arg0, int arg1);
extern "C" int *igObjectStringMap_GetNameAt(void *arg0, int arg1);
extern "C" void igReport_Printf(const char *arg0, ...);
extern "C" int vprintf(...);
extern "C" int vsnprintf(...);
extern "C" void igReport_VPrintf(const char *arg0, int arg1);
extern "C" int igReport_ErrorPrintf(int arg0, ...);
extern "C" int fprintf(...);
extern "C" int vfprintf(...);
extern "C" int igReport_VErrorPrintf(int arg0, int arg1);
extern "C" int fflush(...);
extern "C" void igReport_Flush(void);
extern "C" void igReport_FlushError(void);
extern "C" void igFolder_ListFiles(void **arg0);
extern "C" void igPluginHelper_LoadPluginsFromRegistry(void *self);
extern "C" void **igQueue_StartServiceThread(void *arg0, int arg1, unsigned stackSize);
extern "C" int thunk_igStandardQueue_StopServiceThreads(int extra0);
extern "C" int **igRawRefMetaField_Construct(int **arg0, int extra1);
extern "C" int **igRawRefMetaField_Init(int **arg0);
extern "C" int **igRawRefMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igRawRefMetaField_Destruct(igRawRefMetaField *self);
extern "C" int igRefMetaField_ValueFromString(void);
extern "C" void igRefMetaField_ValueToString(int *arg0);
extern "C" int igRefMetaField_GetSize(void);
extern "C" int igRefMetaField_ReadRawFieldMem(void *arg0, int a1, int *arg2, int arg3, int arg4);
extern "C" int igRefMetaField_GetMeta(void);
extern "C" char *igRefMetaField_SkipPastChar(char *s, char ch);
extern "C" void igRefMetaField_Destruct(igRefMetaField *self);
extern "C" int igRefMetaField_GetAlignment(void);
extern "C" int FUN_00305cf0(void);
extern "C" void igRegistry_InitDefaults(void *arg0);
extern "C" int igRegistry_GetNumValuesInSection(int arg0, int arg1);
extern "C" bool igRegistry_GetValueInt(int arg0, int arg1, const char *arg2, int *arg3, int arg4, int arg5);
extern "C" bool igRegistry_GetValueFloat(int arg0, int arg1, const char *arg2, float *arg3, int arg4, float fparg0);
extern "C" int igRegistry_GetValueString(int arg0, int arg1, const char *arg2, int **out, char *def, int create);
extern "C" unsigned char igRegistry_GetValueBool(int arg0, int arg1, const char *arg2, char *arg3, int arg4, int arg5);
extern "C" bool igRegistry_ParseEnumFlags(char *text, int *value, int metaEnum, char *format);
extern "C" int igRegistry_ParseEnumValue(char *text, int *value, igMetaEnum *metaEnum, char *format);
extern "C" int igRegistry_GetValueEnum(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6);
extern "C" int igRegistry_GetValueFlags(int arg0, int arg1, const char *arg2, int arg3, int *arg4, int arg5, int arg6);
extern "C" int igRegistry_GetValueEntry(void *arg0, int arg1);
extern "C" int igRegistry_GetValueCount(void *arg0);
extern "C" int igRegistry_SetValueInt(void *arg0, int arg1, const char *arg2, int arg3);
extern "C" void igStringObj_SetFloat(int string, void *format, float value);
extern "C" int igRegistry_SetValueFloat(int a0, int a1, const char *a2, float x);
extern "C" int igRegistry_SetValueString(void *registry, int section, const char *key, const char *value);
extern "C" int igRegistry_SetValueBool(int arg0, int arg1, const char *arg2, int arg3);
extern "C" int igRegistry_GetSectionName(void *arg0, int arg1);
extern "C" int igReportNotice(const char *arg0, ...);
extern "C" int igReport_Detail(const char *arg0, ...);
extern "C" void igReport_Info(const char *arg0, ...);
extern "C" int igReportError(const char *arg0, ...);
extern "C" int igReport_Warning(const char *arg0, ...);
extern "C" int igReport_DefaultHandler(int arg0, int arg1);
extern "C" int igReport_VReport(int arg0, const char *arg1, int arg2);
extern "C" void igReport_ReadSettings(void);
extern "C" void igReport_RestoreDefaults(void);
extern "C" int igResource_AddDirectory(int *p, int extra1);
extern "C" void igResource_AsyncLoadThreadProc(int *arg0, void *arg1);
extern "C" bool igResource_IsDirectoryLoaded(igResource *self, igDirectoryView *directory);
extern "C" int igResource_GetDefaultResource(void);
extern "C" int igDirectory_GetNthObjectOfType(int directory, int name, int metaName, int wanted);
extern "C" void igResource_WrapRootInSceneInfo(int arg0);
extern "C" int igShortMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igShortMetaField_ValueToString(int *arg0, int arg1, short *arg2);
extern "C" int **igShortMetaField_Construct(int **arg0, int extra1);
extern "C" int **igShortMetaField_Init(int **arg0);
extern "C" int **igShortMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igShortMetaField_Destruct(int extra0);
extern "C" void igShortMetaField_SetDefault(void **arg0, short arg1);
extern "C" int igShortMetaField_GetAlignment(void);
extern "C" int igStringMetaField_ReadRawValue(...);
extern "C" int igStringArrayMetaField_GetSize(void *arg0);
extern "C" void igStringMetaField_ReleaseDefaults(int arg0);
extern "C" void igStringMetaField_ValueFromString(int arg0, int a1, int arg2);
extern "C" int igStringMetaField_AssignRetainedToken(...);
extern "C" void igStringMetaField_ValueToString(void **output, void *field, void **sourceCell);
extern "C" int igStringMetaField_GetTypeSize(void);
extern "C" void igStringMetaField_SwapValue(void);
extern "C" void igStringArrayMetaField_SwapValue(void);
extern "C" void igStringMetaField_ConstructValue(void);
extern "C" void igStringMetaField_SetDefaultText(int *arg0, int arg1);
extern "C" void **FUN_002c3090(...);
extern "C" int igStringMetaField_WriteRawValue(void *self, void *value, void *dst, int a3, int swap);
extern "C" void igStringMetaField_ResetValue(int *arg0, int arg1);
extern "C" void *igStringMetaField_CopyConstruct(void *arg0, void *arg1);
extern "C" void igStringMetaField_Destruct(igStringMetaField *self);
extern "C" void igStringObj_Set(int arg0, int arg1);
extern "C" int strlwr(int);
extern "C" void igStringObj_ToLower(void *arg0);
extern "C" int igStringObj_ToInt(void *arg0, int arg1);
extern "C" int igStringObj_ToFloat(void *arg0, int arg1);
extern "C" void igStringObj_SetInt(int arg0, int arg1, int arg2);
extern "C" void igStringObj_SetBool(int arg0, int arg1, int arg2);
extern "C" int igStringObj_Format(int arg0, int arg1, ...);
extern "C" int igStringObj_VFormat(int arg0, int extra1, int extra2);
extern "C" void igStringObj_StripDirectory(int *arg0);
extern "C" int igStringObj_HasFileExtension(void *arg0, char *arg1);
extern "C" int igStringObj_HasFileExtensionText(char *arg0, char *arg1);
extern "C" int igStrcasecmp(const char *s1, const char *s2);
extern "C" int StringChunk_ReturnBlock(...);
extern "C" StringTable *StringTable_Construct(StringTable *table, StringPool *pool, int capacity);
extern "C" void StringTable_SetSynchronization(int arg0);
extern "C" int StringTable_Find(StringTable *table, int text);
struct StringTokenHeader;
extern "C" StringTokenHeader *StringTable_Register(StringTable *table, StringTokenHeader *header, StringChunk *chunk, int text);
extern "C" void StringTable_RemoveHeader(StringTable *table, int header);
extern "C" int StringTable_DeleteObject(int object);
extern "C" int StringChunk_DeleteObject(int object);
extern "C" void igStringRefList_ReleaseDefaults(void *self0);
extern "C" void igStringTable_SetCapacity(int a0, int a1);
extern "C" void igStringTable_SetHashCapacity(int a0, int a1);
extern "C" void igStringTable_Reserve(void *arg0);
extern "C" void igStringTable_RemoveAll(int arg0);
class igStringTableView;
extern "C" void igStringTable_Truncate(int *result, igStringTableView *table, int count);
extern "C" char *igStringTable_GetString(int *arg0, int arg1);
extern "C" int igStringTable_FindOrAddString(int arg0, int arg1);
extern "C" unsigned short igStructMetaField_GetSize(void *arg0);
extern "C" void igStructMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igStructMetaField_ValueToString(int *arg0, void *arg1);
extern "C" void igSymbolTable_SetCapacity(int a0, int a1);
extern "C" void igSymbolTable_SetHashCapacity(int a0, int a1);
class igSymbolTableView;
extern "C" void igSymbolTable_ReserveStorage(igSymbolTableView *arg0);
extern "C" void igPsx2ThreadManager_CreateGlobal(void);
extern "C" void igPsx2ThreadManager_DestroyGlobal(void);
extern "C" int igUnsignedCharMetaField_ValueFromString(void *arg0, char *arg1, int arg2);
extern "C" void igUnsignedCharMetaField_ValueToString(int *arg0, int arg1, unsigned char *arg2);
extern "C" int igUnsignedCharMetaField_GetSize(void);
extern "C" void igUnsignedCharMetaField_SetDefaultValue(void **arg0, char arg1);
extern "C" int igUnsignedCharMetaField_GetAlignment(void);
extern "C" int igUnsignedIntMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igUnsignedIntMetaField_ValueToString(int *arg0, void *arg1, int *arg2);
extern "C" int igUnsignedIntMetaField_GetSize(void);
extern "C" int **igUnsignedIntMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igUnsignedIntMetaField_Destruct(int extra0);
extern "C" void igUnsignedIntMetaField_SetDefaultValue(void **arg0, int arg1);
extern "C" int igUnsignedIntMetaField_GetAlignment(void);
extern "C" int igUnsignedLongMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igUnsignedLongMetaField_ValueToString(int *arg0, int arg1, long long *arg2);
extern "C" int igUnsignedLongMetaField_GetSize(void);
extern "C" int **igUnsignedLongMetaField_Construct(int **arg0, int extra1);
extern "C" int **igUnsignedLongMetaField_Init(int **arg0);
extern "C" int **igUnsignedLongMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igUnsignedLongMetaField_Destruct(int extra0);
extern "C" void igUnsignedLongMetaField_SetDefaultValue(void **field, unsigned long long value);
extern "C" int igUnsignedShortMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igUnsignedShortMetaField_ValueToString(int *arg0, int arg1, unsigned short *arg2);
extern "C" int igUnsignedShortMetaField_GetSize(void);
extern "C" void igUnsignedShortMetaField_SetDefaultValue(void **arg0, short arg1);
extern "C" int **igUnsignedShortMetaField_Construct(int **arg0, int extra1);
extern "C" int **igUnsignedShortMetaField_Init(int **arg0);
extern "C" int **igUnsignedShortMetaField_CopyConstruct(int **arg0, int extra1);
extern "C" void igUnsignedShortMetaField_Destruct(int extra0);
extern "C" int igVirtualCFuncMetaField_ValueFromString(int arg0, int arg1, int arg2);
extern "C" void igVirtualCFuncMetaField_ValueToString(int *arg0, int arg1, int *arg2);
extern "C" int igVirtualCFuncMetaField_GetSize(void);
extern "C" void igVirtualCFuncMetaField_SetToDefault(void *arg0, int arg1);
extern "C" void igVirtualCFuncMetaField_CopyDefaultToValue(int *arg0, int arg1);
extern "C" int igVirtualCFuncMetaField_GetAlignment(void);
extern "C" void igArenaMemoryPool_CheckInUseBlock(void *arg0, unsigned char *arg1, int extra2);
class igArenaMemoryPoolView;
extern "C" char DAT_004fbf10[];
extern "C" char DAT_004fbf90[];
extern "C" char DAT_004fc010[];
extern "C" char DAT_004fc090[];
extern "C" char DAT_004fc150[];
extern "C" void igArenaMemoryPool_DisplayOutstandingAllocationsBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end);
extern "C" void igArenaMemoryPool_DisplayOutstandingAllocations(void *self0);
extern "C" int strncat(char *, int *, int);
extern "C" char *igMetaEnum_GetNamesByMask(char *arg0, int arg1, int arg2, int arg3);
extern "C" char *igMetaEnum_GetValueName(char *arg0, int arg1, int arg2, int arg3);
extern "C" char *FUN_00312140(char *, int, int, int);
extern "C" char *FUN_00312020(char *, int, int, int);
extern "C" void List_InsertWords(igDataList *list, int index, int count, const void *src);
class igArenaMemoryPoolView;
extern "C" void FUN_00318b40(igArenaMemoryPoolView *self);
extern "C" int FUN_00314510(igArenaMemoryPoolView *self, unsigned int pad, int force);
extern "C" void igArenaMemoryPool_Deactivate(igArenaMemoryPoolView *p);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_29(void);
extern "C" void igArenaMemoryPool_SetSize(int *statusOut);
extern "C" void igArenaMemoryPool_SetMaxSize(int *arg0, char *arg1, unsigned long long arg2);
extern "C" void igArenaMemoryPool_SetPreSize(int *arg0, void *arg1, int arg2);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocatedHigh(void *arg0);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *arg0);
extern "C" int igArenaMemoryPool_GetArenaCount(void *arg0);
extern "C" int igArenaMemoryPool_GetArenaHighCount(void *arg0);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_101(void *arg0);
extern "C" void igArenaMemoryPool_Lock(void *arg0);
extern "C" void igArenaMemoryPool_Unlock(void *arg0);
extern "C" int igArenaMemoryPool_UnlockAndReturn(void *arg0, int arg1);
extern "C" void igArenaMemoryPool_GangAllocAligned(int *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__freeSized(igArenaMemoryPoolView *self, unsigned int size, char **block);
extern "C" void igArenaMemoryPool_Destruct(void **self);
extern "C" int igArenaMemoryPool_OwnsAllocation(void *self, unsigned char *p);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_83(void);
extern "C" int igArenaMemoryPool_GetAllocationSize(int arg0, unsigned char *p);
extern "C" int igArenaMemoryPool_GetEventTracker(void *arg0);
extern "C" void igArenaMemoryPool_Dump(void);
extern "C" int igArenaMemoryPool_GetPoolIndex(void *arg0);
extern "C" void igArenaMemoryPool_SetPoolIndex(void *arg0, int arg1);
extern "C" int igArenaMemoryPool_CanTransferTo(void *arg0, void **arg1);
extern "C" int igArenaMemoryPool_GetAllocationPoolIndex(int arg0, unsigned char *p);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_108(void);
extern "C" int igArenaMemoryPool_GetLowestAddress(void *arg0);
extern "C" int igArenaMemoryPool_GetHighestAddress(void *arg0);
extern "C" void igElfFile_SwapHeader(unsigned char *p);
extern "C" void igElfFile_SwapSectionHeaders(unsigned char *arg0, int arg1);
extern "C" void igElfFile_SwapSymbols(unsigned char *arg0, int arg1);
class ElfFileView;
extern "C" void igElfFile_Close(int *result, ElfFileView *self);
extern "C" int igElfFile_GetSymbol(void *arg0, int arg1);
extern "C" void igElfFile_DemangleName(const char *in, char *out, int size);
extern "C" void igElfFile_Demangle(int *result, void *self, char *mangled, char *out, int size);
extern "C" int *igElfFile_LookupValueName(int arg0, int *arg1);
extern "C" char *igElfFile_FormatFlags(int arg0, int arg1, char *arg2);
extern "C" void igElfFile_PrintSectionHeaders(int *arg0);
extern "C" long long igMallocMemoryPool_GetLocalNetAllocatedHigh(void *arg0);
extern "C" long long igMallocMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *arg0);
extern "C" void igMallocMemoryPool_Lock(void *arg0);
extern "C" void igMallocMemoryPool_Unlock(void *arg0);
extern "C" int igMallocMemoryPool_UnlockAndReturn(void *arg0, int arg1);
extern "C" void igMallocMemoryPool_GangAllocAligned(int *arg0);
extern "C" int igMallocMemoryPool_OwnsAllocation(int arg0, char *arg1);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_83(void);
extern "C" unsigned int igMallocMemoryPool_GetAllocationSize(int arg0, char *arg1);
extern "C" int igMallocMemoryPool_GetEventTracker(void *arg0);
extern "C" void igMallocMemoryPool_Dump(void *self, int a1, int a2, int a3, int t0);
extern "C" int igMallocMemoryPool_GetPoolIndex(void *arg0);
extern "C" void igMallocMemoryPool_SetPoolIndex(void *arg0, int arg1);
extern "C" int igMallocMemoryPool_CanTransferTo(void *arg0, void **arg1);
extern "C" int igMallocMemoryPool_GetAllocationPoolIndex(int arg0, char *arg1);
extern "C" void igPageMemoryPool_Destruct(int extra0);
extern "C" void Gap__Core__igPageMemoryPool__constructFields(int extra0, int extra1);
extern "C" void igPageMemoryPool_Reset(void **arg0);
extern "C" void igPageMemoryPool_SetRawMemory(int *statusOut);
extern "C" void igPageMemoryPool_SetSize(int *statusOut);
extern "C" void igPageMemoryPool_SetAlignment(int *statusOut);
extern "C" void igPageMemoryPool_SetElementSize(int *statusOut);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedHigh(void *arg0);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedWithOverheadHigh(void *arg0);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_101(void *arg0);
extern "C" void igPageMemoryPool_Lock(void *arg0);
extern "C" int igPageMemoryPool_UnlockAndReturn(void *arg0, int arg1);
extern "C" void igPageMemoryPool_GangAlloc(int *arg0);
extern "C" void igPageMemoryPool_GangAllocAligned(int *arg0);
extern "C" void igPageMemoryPool_GangFree(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_83(void);
extern "C" void igPageMemoryPool_SetPoolOptionFlags(void *a0, int a1);
extern "C" int igPageMemoryPool_GetEventTracker(void *arg0);
extern "C" void igPageMemoryPool_Dump(void);
extern "C" int igPageMemoryPool_GetPoolIndex(void *arg0);
extern "C" void igPageMemoryPool_SetPoolIndex(void *arg0, int arg1);
class igPageMemoryPoolView;
extern "C" int igPageMemoryPool_AllocatePages(igPageMemoryPoolView *arg0, int arg1);
extern "C" int igPageMemoryPool_ReallocatePages(igPageMemoryPoolView *arg0, int arg1, int arg2, int arg3);
extern "C" int igPageMemoryPool_AllocatePagesAligned(igPageMemoryPoolView *arg0, int arg1, int arg2);
extern "C" void igPageMemoryPool_PrintStatistics(int extra0, int extra1);
extern "C" void igPageMemoryPool_CollectMemoryRegions(void);
class ProgramFileView;
extern "C" void igProgramFile_Close(int *result, ProgramFileView *self);
extern "C" void igProgramFile_LoadSymbols(int *status_out);
extern "C" void igProgramFile_LoadSymbolTable(int *status_out);
extern "C" void igProgramFile_Demangle(int *status_out);
extern "C" igResult igStackMemoryPool_Configure(igStackMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igStackMemoryPool_SetSize(int *status_out);
extern "C" void igStackMemoryPool_SetRawMemory(int *arg0, void *arg1, int arg2, long long arg3, char arg4);
extern "C" int igStackMemoryPool_Reallocate(void **arg0, int arg1, unsigned int arg2);
extern "C" int igStackMemoryPool_ReallocateAligned(void **arg0, int arg1, unsigned int arg2, unsigned short arg3);
extern "C" int igStackMemoryPool_GetEventTracker(void *arg0);
extern "C" void igStackMemoryPool_Dump(int *a, int a1, int a2, int a3, int a4);
extern "C" int igStackMemoryPool_GetPoolIndex(void *arg0);
extern "C" void igStackMemoryPool_SetPoolIndex(void *arg0, int arg1);
extern "C" void igStackMemoryPool_CollectMemoryRegions(igStackMemoryPool *self, igDataList *list);
class igStandardQueueView;
extern "C" void igStandardQueue_ReleaseDefaults(igStandardQueueView *self);
extern "C" int **SystemAllocatorBase_Construct(int **arg0);
extern "C" int calloc(...);
extern "C" void realloc(int, int);
class SystemAllocator;
extern "C" void SystemAllocatorBase_ReleasePageTables(SystemAllocator *self);
extern "C" int SystemAllocatorBase_Allocate(void *arg0, int arg1);
extern "C" int FUN_00328f20(int arg0, int arg1);
extern "C" void SystemAllocatorBase_Callocate(int unused, int a, int b);
extern "C" void SystemAllocatorBase_Reallocate(int arg0, int arg1, int arg2);
extern "C" int SystemAllocatorBase_DuplicateString(SystemAllocator *self, int *arg1);
extern "C" void SystemAllocatorBase_Free(int a0, int a1);
extern "C" void SystemAllocatorBase_FreeSized(SystemAllocator *self, int arg1, int arg2);
extern "C" int SystemAllocatorBase_ReallocateSized(SystemAllocator *self, int arg1, unsigned int arg2, unsigned int arg3);
extern "C" int SystemAllocatorBase_GetRangeStart(void);
extern "C" int SystemAllocatorBase_GetRawRangeStart(void);
extern "C" int SystemAllocatorBase_GetRangeEnd(void);
extern "C" int SystemAllocatorBase_IsRangeFree(void *self, unsigned int addr, unsigned int len);
extern "C" unsigned int SystemAllocatorBase_FindFreeRange(void *self, int size);
extern "C" int FUN_00329b00(void);
extern "C" int FUN_00329b10(void);
extern "C" void FUN_00329b20(void *arg0, int *arg1, int *arg2, int *arg3);
extern "C" int FUN_00329b40(void *arg0, void *arg1, int *arg2, int *arg3);
extern "C" void SystemAllocatorBase_DumpPageRange(int unused, unsigned int addr, int len);
struct DumpRegion;
extern "C" DumpRegion *DumpRegion_Destruct(DumpRegion *row, short flags);
extern "C" void DumpRegion_SetAnnotation(DumpRegion *row, const char *annotation);
extern "C" void DumpRegion_SetPoolName(DumpRegion *row, const char *poolName);
extern "C" void DumpRegion_Free(void *block);
extern "C" int DumpRegion_CompareStart(DumpRegion **a, DumpRegion **b);
extern "C" void SystemAllocatorBase_CollectHardwareRegions(int extra0);
extern "C" void SystemAllocatorBase_CollectPoolRegions(int a0, int a1);
extern "C" int SystemAllocatorBase_Sbrk(void);
extern "C" void SystemAllocatorBase_ReserveRange(int *arg0, SystemAllocator *self, int arg2, int arg3);
extern "C" void FUN_0032ac60(int *arg0);
extern "C" int PageTable_GetState(int arg0, unsigned int arg1);
extern "C" void PageTable_SetState(int arg0, unsigned int arg1, int arg2);
extern "C" void PageTable_SetStateRange(int arg0, int arg1, int arg2, int arg3);
extern "C" int PageTable_CountRun(int arg0, unsigned int arg1, int arg2, int arg3, int arg4);
extern "C" void PageTable_CountStates(int arg0, void *arg1);
extern "C" void SystemAllocator_EnsureCreated(void);
extern "C" void SystemAllocator_EnsureDestroyed(void);
extern "C" void igPsx2CallStackTracer_HasSymbols(void);
extern "C" int sceClose(...);
class igPsx2FileView;
extern "C" void igPsx2File_CloseHandle(igPsx2FileView *arg0);
extern "C" void **igPsx2File_Open(void **arg0, const char *fileName, int arg2);
extern "C" int sceLseek(...);
extern "C" int sceRead(...);
extern "C" int sceWrite(...);
extern "C" int igPsx2File_Seek(igPsx2FileView *arg0, int arg1, int arg2);
extern "C" void igPsx2File_InitDefaultPrefix(void);
extern "C" char *igPsx2File_MakeCompletePath(char *path);
extern "C" char _toupper(...);
extern "C" int sceDopen(int);
extern "C" int sceDclose(int);
extern "C" int sceDread(...);
extern "C" void StringList_AppendRetained(...);
/* sceOpen flags and sceLseek origins (Sony sifdev.h). */
enum { SCE_RDONLY = 0x1, SCE_WRONLY = 0x2, SCE_RDWR = 0x3, SCE_APPEND = 0x100, SCE_CREAT = 0x200, SCE_TRUNC = 0x400 };
enum { SCE_SEEK_SET = 0, SCE_SEEK_CUR = 1, SCE_SEEK_END = 2 };
extern "C" int sceOpen(const char *path, int flags, ...);
extern "C" char *igPsx2_ResolveModulePath(char *name, int kind);
extern "C" int igPsx2_LoadIopModule(int a, int b, int c, int d, int e);
extern "C" int sceSifLoadModule(...);
extern "C" int igPsx2_LoadIopModuleEx(int *arg0, int arg1, int arg2, int arg3, int arg4, int *arg5);
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
extern "C" void igPsx2_RebootIop(void);
extern "C" void igPsx2_InitializeIop(void);
extern "C" void igPsx2_SetupOutputFiles(void);
extern "C" void igPsx2_SetAtfilePrefix(int *arg0, char *arg1);
extern "C" int sceSifBindRpc(...);
extern "C" int sceSifCallRpc(...);
extern "C" int SyncDCache(...);
extern "C" void igPsx2IopRpcConnection_RpcEndCallback(int sema);
extern "C" int p2ReadNanoseconds(...);
extern "C" long long igPsx2LongTimer_GetCurrentTime(void);
extern "C" int igPsx2LongTimer_GetResolution(void);
extern "C" void p2InitTimer(void);
extern "C" void igPsx2LongTimer_InitTimer(void);
extern "C" void igPsx2LongTimer_StaticInit(void);
extern "C" void iSyncDCache(char *, char *);
extern "C" void Gap__Core__igPsx2Media__userConstruct(int arg0);
extern "C" void DIntr(void);
extern "C" void EIntr(void);
extern "C" void sceSifAddCmdHandler(int, void *, int);
extern "C" void igPsx2Media_SetDevicePrefix(int arg0);
extern "C" int Gap__Core__igPsx2Media__vfunc_32(void);
extern "C" void igPsx2Semaphore_SetInitialCount(int *arg0, void *arg1, int arg2);
extern "C" int ReferSemaStatus(...);
extern "C" void igPsx2Semaphore_Destroy(int *arg0, int *arg1);
extern "C" void igPsx2Semaphore_ISignal(int *arg0, void *arg1);
extern "C" void igPsx2Semaphore_WaitBlocking(int *arg0, void *arg1);
extern "C" int iPollSema(int);
extern "C" void SystemAllocator_Activate(void);
extern "C" void SystemAllocator_Deactivate(void);
extern "C" int FUN_0032f370(void);
extern "C" void SystemAllocator_CollectHardwareRegions(int arg0, int arg1);
extern "C" void SystemAllocator_CollectProgramRegions(int arg0, int arg1);
extern "C" int sbrk(...);
extern "C" int SystemAllocator_Sbrk(int arg0, int arg1);
extern "C" int p2SleepMilliseconds(int);
extern "C" int FUN_0032f7f0(...);
extern "C" long long __udivdi3(int, int);
extern "C" int iSuspendThread(int);
extern "C" int iResumeThread(int);
extern "C" int iChangeThreadPriority(int, int);
extern "C" int TerminateThread(...);
extern "C" int DeleteThread(...);
extern "C" int igPsx2Thread_IsEqual(void *arg0, void *arg1);
class igPsx2ThreadView;
class igSemaphoreView;
class igPsx2ThreadManagerView;
extern "C" void igPsx2Thread_InitDefaults(igPsx2ThreadView *self);
extern "C" void igPsx2Thread_Sleep(int *arg0, int arg1, int arg2);
extern "C" void igPsx2Thread_Exit(void *arg0, int arg1);
extern "C" void igPsx2Thread_WaitForWakeup(int *arg0);
extern "C" void igPsx2Thread_Wakeup(int *arg0, void *arg1);
extern "C" void igPsx2Thread_IWakeup(int *arg0, void *arg1);
extern "C" void igPsx2Thread_EnterStoppingPoint(void *arg0);
extern "C" void igPsx2Thread_LeaveStoppingPoint(void *arg0);
extern "C" int Memory_GetAllocatorOrDefault(int extra0);
extern "C" void Memory_AllocateAligned16(int arg0, int arg1);
extern "C" void Memory_FreeToSelector(int arg0, int arg1);
extern "C" void Memory_ReallocateAligned16(int arg0, int arg1, int arg2);
extern "C" int igPsx2ThreadManager_GetMeta(void);
extern "C" int igPsx2Thread_GetMeta(void);
extern "C" int igPsx2Thread_GetStackAlignment(void);
extern "C" int Gap__Core__igPsx2Thread__vfunc_43(void);
extern "C" void igPsx2Thread_ReleaseDefaults(void *arg0);
extern "C" void Gap__Core__igPsx2Thread__vfunc_52(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_53(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_54(int *result);
extern "C" int igPsx2Semaphore_GetMeta(void);
extern "C" void igPsx2Semaphore_ReleaseDefaults(igSemaphoreView *self);
extern "C" int igPsx2Media_GetMeta(void);
extern "C" igMetaObject *igPsx2LongTimer_GetMeta(void);
extern "C" int __divdi3(...);
extern "C" int __moddi3(...);
extern "C" int __floatdidf(...);
extern "C" int dpadd(...);
extern "C" int dpdiv(...);
extern "C" int litodp(...);
extern "C" int __fixdfdi(...);
extern "C" int dpmul(...);
extern "C" int igPsx2IopRpcConnection_GetMeta(void);
extern "C" igMetaObject *igPsx2Folder_GetMeta(void);
extern "C" int igPsx2File_GetMeta(void);
extern "C" int igPsx2CallStackTracer_GetMeta(void);
extern "C" void igUnsignedIntListNoClean_TrimCapacity(void);
extern "C" int igStandardQueue_GetMeta(void);
extern "C" igMetaObject *igStackMemoryPool_GetMeta(void);
extern "C" unsigned char igStackMemoryPool_IsAlchemyMemory(void *arg0);
extern "C" void igStackMemoryPool_SetMaxSize(int *status_out);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_83(void);
extern "C" int igProgramFile_GetMeta(void);
extern "C" int igElfFile_GetMeta(void);
extern "C" igMetaObject *igVirtualCFuncMetaField_GetMeta(void);
extern "C" int igVirtualCFuncMetaField_GetDescriptor(void);
extern "C" int igUnsignedShortArrayMetaField_GetMeta(void);
extern "C" int igUnsignedShortArrayMetaField_GetDescriptor(void);
extern "C" int igUnsignedLongArrayMetaField_GetMeta(void);
extern "C" int igUnsignedLongArrayMetaField_GetDescriptor(void);
extern "C" int igUnsignedIntArrayMetaField_GetMeta(void);
extern "C" int igUnsignedIntArrayMetaField_GetDescriptor(void);
extern "C" int igUnsignedCharMetaField_GetMeta(void);
extern "C" int igUnsignedCharMetaField_GetDescriptor(void);
extern "C" int igUnsignedCharArrayMetaField_GetMeta(void);
extern "C" int igUnsignedCharArrayMetaField_GetDescriptor(void);
extern "C" int igSymbolTable_GetMeta(void);
extern "C" int igStructMetaField_GetMeta(void);
extern "C" int igStructMetaField_GetDescriptor(void);
extern "C" int igStringTable_GetMeta(void);
extern "C" igMetaObject *igStringRefList_GetMeta(void);
extern "C" igMetaObject *igStringArrayMetaField_GetMeta(void);
extern "C" int igStringArrayMetaField_GetDescriptor(void);
extern "C" int igShortArrayMetaField_GetMeta(void);
extern "C" int igShortArrayMetaField_GetDescriptor(void);
extern "C" int igResource_GetMeta(void);
extern "C" igMetaObject *igRegistry_GetMeta(void);
extern "C" int igRefMetaField_GetDescriptor(void);
extern "C" int igRawRefArrayMetaField_GetMeta(void);
extern "C" int igRawRefArrayMetaField_GetDescriptor(void);
extern "C" igMetaObject *igQueue_GetMeta(void);
extern "C" int igPluginHelper_GetMeta(void);
extern "C" igMetaObject *igObjectRefArrayMetaField_GetMeta(void);
extern "C" int igObjectRefArrayMetaField_GetDescriptor(void);
extern "C" int igNamedObjectInfo_GetMeta(void);
extern "C" igMetaObject *igMetaFieldInfo_GetMeta(void);
extern "C" int igMemoryRefArrayMetaField_GetMeta(void);
extern "C" int igMemoryRefArrayMetaField_GetDescriptor(void);
extern "C" int igMemoryPoolInfo_GetMeta(void);
extern "C" igMetaObject *igMemoryPoolContextInfo_GetMeta(void);
extern "C" int FUN_00331250(void);
extern "C" int igMemoryFile_GetMeta(void);
extern "C" int igMemoryDictionary_GetMeta(void);
extern "C" igMetaObject *igMediaFile_GetMeta(void);
extern "C" int igLongMetaField_GetMeta(void);
extern "C" int igLongMetaField_GetDescriptor(void);
extern "C" int igLongArrayMetaField_GetMeta(void);
extern "C" int igLongArrayMetaField_GetDescriptor(void);
extern "C" int igLocationTable_GetMeta(void);
extern "C" igMetaObject *igIntArrayMetaField_GetMeta(void);
extern "C" int igIntArrayMetaField_GetDescriptor(void);
extern "C" int igIGBFile_GetMeta(void);
extern "C" igMetaObject *igFolder_GetMeta(void);
extern "C" igMetaObject *igFloatMetaField_GetMeta(void);
extern "C" int igFloatMetaField_GetDescriptor(void);
extern "C" int igFloatArrayMetaField_GetMeta(void);
extern "C" int igFloatArrayMetaField_GetDescriptor(void);
extern "C" igMetaObject *igFile_GetMeta(void);
extern "C" int igExternalInfoEntry_GetMeta(void);
extern "C" int igExternalIndexedEntry_GetMeta(void);
extern "C" int igExternalDirEntry_GetMeta(void);
extern "C" int igEventTracker_GetMeta(void);
extern "C" int igEnumArrayMetaField_GetMeta(void);
extern "C" int igEnumArrayMetaField_GetDescriptor(void);
extern "C" int igDriverDatabase_GetMeta(void);
extern "C" igMetaObject *igDoubleMetaField_GetMeta(void);
extern "C" int igDoubleMetaField_GetDescriptor(void);
extern "C" int igDoubleArrayMetaField_GetMeta(void);
extern "C" int igDoubleArrayMetaField_GetDescriptor(void);
extern "C" int igDirectory_GetMeta(void);
extern "C" int igCharArrayMetaField_GetMeta(void);
extern "C" int igCharArrayMetaField_GetDescriptor(void);
extern "C" int igCallStackTracer_GetMeta(void);
extern "C" igMetaObject *igCallStackTable_GetMeta(void);
extern "C" igMetaObject *igBoolArrayMetaField_GetMeta(void);
extern "C" int igBoolArrayMetaField_GetDescriptor(void);
extern "C" int igMemoryDescriptorMetaField_GetMeta(void);
extern "C" int igMemoryDescriptorMetaField_GetDescriptor(void);
extern "C" int igMallocMemoryPool_GetMeta(void);
extern "C" void igMallocMemoryPool_ReleaseDefaults(igMemoryPoolView *self);
extern "C" void igMallocMemoryPool_Reset(void);
extern "C" void igMallocMemoryPool_SetRawMemory(int *statusOut);
extern "C" int igMallocMemoryPool_IsAlchemyMemory(void);
extern "C" int igMallocMemoryPool_GetRawMemory(void);
extern "C" int Gap__Core__igMallocMemoryPool__vfunc_29(void);
extern "C" int igArenaMemoryPool_GetMeta(void);
extern "C" int igPageMemoryPool_GetMeta(void);
extern "C" int igAliasMemoryPool_GetMeta(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_83(void);
extern "C" igMetaObject *igBoolMetaField_GetMeta(void);
extern "C" int igBoolMetaField_GetDescriptor(void);
extern "C" igMetaObject *igCharMetaField_GetMeta(void);
extern "C" int igCharMetaField_GetDescriptor(void);
extern "C" igMetaObject *igCompoundMetaField_GetMeta(void);
extern "C" int igContextList_GetMeta(void);
extern "C" igMetaObject *igContextExtInfo_GetMeta(void);
extern "C" igMetaObject *igContextExtInfoList_GetMeta(void);
extern "C" igMetaObject *igContextExtList_GetMeta(void);
extern "C" igMetaObject *igBoolList_GetMeta(void);
extern "C" igMetaObject *igCharListNoClean_GetMeta(void);
extern "C" void igCharListNoClean_TrimCapacity(void);
extern "C" igMetaObject *igCharList_GetMeta(void);
extern "C" igMetaObject *igIntListNoClean_GetMeta(void);
extern "C" void igIntListNoClean_TrimCapacity(void);
extern "C" int igIntList_GetMetaObject_Virtual(void);
extern "C" igMetaObject *igLongList_GetMeta(void);
extern "C" igMetaObject *igUnsignedIntListNoClean_GetMeta(void);
extern "C" igMetaObject *igUnsignedShortList_GetMeta(void);
extern "C" igMetaObject *igShortList_GetMeta(void);
extern "C" igMetaObject *igShortListList_GetMeta(void);
extern "C" int igUnsignedCharList_GetMeta(void);
extern "C" igMetaObject *igFloatList_GetMeta(void);
extern "C" igMetaObject *igFloatListList_GetMeta(void);
extern "C" igMetaObject *igPointerList_GetMeta(void);
extern "C" igMetaObject *igPointerListList_GetMeta(void);
extern "C" igMetaObject *igMetaObjectList_GetMeta(void);
extern "C" igMetaObject *igMetaObjectListList_GetMeta(void);
extern "C" igMetaObject *igMetaFieldList_GetMeta(void);
extern "C" igMetaObject *igIntListList_GetMeta(void);
extern "C" igMetaObject *igObjectListList_GetMeta(void);
extern "C" igMetaObject *igStringRefListList_GetMeta(void);
extern "C" igMetaObject *igDependencyMetaField_GetMeta(void);
extern "C" int igDependencyMetaField_GetDescriptor(void);
extern "C" int igDependencyList_GetMeta(void);
extern "C" igMetaObject *igDirectoryList_GetMeta(void);
extern "C" int igEnumMetaField_GetMeta(void);
extern "C" int igEnumMetaField_GetDescriptor(void);
extern "C" int igErrorHandler_GetMeta(void);
extern "C" int igInfoList_GetMeta(void);
extern "C" int igIntMetaField_GetMeta(void);
extern "C" int igIntMetaField_GetDescriptor(void);
extern "C" igMetaObject *__internalNonRefCountedObjectList_GetMeta(void);
extern "C" igMetaObject *__internalObjectList_GetMeta(void);
extern "C" int igLibraryList_GetMeta(void);
extern "C" igMetaObject *igMediaList_GetMeta(void);
extern "C" igMetaObject *igMemoryFileEntry_GetMeta(void);
extern "C" igMetaObject *igMemoryFileEntryList_GetMeta(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetMeta(void);
extern "C" int igMemoryRefMetaField_GetMeta(void);
extern "C" int igMemoryRefMetaField_GetDescriptor(void);
extern "C" int igMetaEnum_GetMeta(void);
extern "C" igMetaObject *igNamedObjectList_GetMeta(void);
extern "C" igMetaObject *igObjectRefMetaField_GetMeta(void);
extern "C" int igObjectRefMetaField_GetDescriptor(void);
extern "C" int igObjectStringMap_GetMeta(void);
extern "C" int igPluginRepository_GetMeta(void);
extern "C" igMetaObject *igPluginRepositoryList_GetMeta(void);
extern "C" int igRawRefMetaField_GetMeta(void);
extern "C" int igRawRefMetaField_GetDescriptor(void);
extern "C" int igRegistryValue_GetMeta(void);
extern "C" igMetaObject *igRegistryValueList_GetMeta(void);
extern "C" int igShortMetaField_GetMeta(void);
extern "C" int igShortMetaField_GetDescriptor(void);
extern "C" igMetaObject *igStringMetaField_GetMeta(void);
extern "C" int igStringMetaField_GetDescriptor(void);
extern "C" int igStringObj_GetMeta(void);
extern "C" igMetaObject *igStringObjList_GetMeta(void);
extern "C" igMetaObject *igThreadList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetMeta(void);
extern "C" int igUnsignedIntMetaField_GetMeta(void);
extern "C" int igUnsignedIntMetaField_GetDescriptor(void);
extern "C" igMetaObject *igUnsignedLongMetaField_GetMeta(void);
extern "C" int igUnsignedLongMetaField_GetDescriptor(void);
extern "C" igMetaObject *igUnsignedShortMetaField_GetMeta(void);
extern "C" int igUnsignedShortMetaField_GetDescriptor(void);
extern "C" int igContextList_GetElementMeta(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetElementMeta(void);
extern "C" int igDependencyList_GetElementSize(void);
extern "C" int igPointerList_GetElementSize(void);
extern "C" int igFloatList_GetElementSize(void);
extern "C" int igUnsignedCharList_GetElementSize(void);
extern "C" int igShortList_GetElementSize(void);
extern "C" int igUnsignedShortList_GetElementSize(void);
extern "C" int igIntList_GetElementSize(void);
extern "C" int igCharList_GetElementSize(void);
extern "C" int igBoolList_GetElementSize(void);
extern "C" int igStringRefList_GetElementSize(void);
extern "C" igMetaObject *igContextExtList_GetElementMeta(void);
extern "C" igMetaObject *igContextExtInfoList_GetElementMeta(void);
extern "C" igMetaObject *igMediaList_GetElementMeta(void);
extern "C" igMetaObject *igMemoryFileEntryList_GetElementMeta(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetElementMeta(void);
extern "C" int igInfoList_GetElementMeta(void);
extern "C" int igPluginRepositoryList_GetElementMeta(void);
extern "C" igMetaObject *igRegistryValueList_GetElementMeta(void);
extern "C" igMetaObject *igDirectoryList_GetElementMeta(void);
extern "C" igMetaObject *igDirectory_GetElementMeta(void);
extern "C" igMetaObject *igStringObjList_GetElementMeta(void);
extern "C" igMetaObject *igThreadList_GetElementMeta(void);
extern "C" int beDataObjList_GetElementMeta(void);
extern "C" int igLibraryList_GetElementMeta(void);
extern "C" igMetaObject *igStringRefListList_GetElementMeta(void);
extern "C" igMetaObject *igObjectListList_GetElementMeta(void);
extern "C" igMetaObject *igIntListList_GetElementMeta(void);
extern "C" igMetaObject *igMetaFieldList_GetElementMeta(void);
extern "C" igMetaObject *igMetaObjectListList_GetElementMeta(void);
extern "C" igMetaObject *igMetaObjectList_GetElementMeta(void);
extern "C" igMetaObject *igPointerListList_GetElementMeta(void);
extern "C" igMetaObject *igFloatListList_GetElementMeta(void);
extern "C" igMetaObject *igShortListList_GetElementMeta(void);
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
extern "C" char g_igUnsignedIntArrayMetaField_callbackList[];
extern "C" char igUnsignedIntArrayMetaField_className[];
extern "C" int g_igUnsignedIntArrayMetaField_ctorTable[4];
extern "C" int g_igUnsignedIntArrayMetaField_fieldTable[4];
extern "C" int DAT_004bf328[4];
extern "C" int DAT_004bf330[4];
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
/* igSmartPointer's deleting destructor as retail emitted it out of line, one copy per pointee
 * class (igSmartPointer_igUnsignedIntListNoClean_Destruct, igSmartPointer_igStringTable_Destruct, igSmartPointer_igCallStackTracer_Destruct, igSmartPointer_igLibraryList_Destruct, igSmartPointer_igShortListList_Destruct); the deletion flag
 * is a signed short. */
extern "C" igSmartPointer<igObject> *igSmartPointer_igUnsignedIntListNoClean_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_igStringTable_Destruct(igSmartPointer<igObject> *self,int delete_storage);
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
extern "C" igObject **igSmartPointer_igCharListNoClean_Destruct(igObject **arg0, short arg1);
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
extern "C" igSmartPointer<igObject> *igSmartPointer_igCallStackTracer_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void **igSmartPointer_igSemaphore_Destruct(igObject **self, short flag);
extern "C" igMetaObject *g_igResource_metaObject[4];
extern "C" igMetaObject *igResource_GetMetaObject(void);
extern "C" int DAT_0052eb90[4];
extern "C" igQueue **igSmartPointer_igQueue_Destruct(igQueue **arg0, short arg1);
extern "C" char g_igResource_callbackList[];
extern "C" char igResource_className[];
extern "C" int g_igResource_ctorTable[4];
extern "C" int g_igResource_fieldTable[4];
extern "C" int DAT_004bf7e0[4];
extern "C" int DAT_004bf830[4];
extern "C" igMetaObject *g_igRegistry_metaObject[4];
extern "C" igMetaObject *igRegistry_GetMetaObject(void);
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
extern "C" igSmartPointer<igObject> *igSmartPointer_igLibraryList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
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
extern "C" void *igMemoryRefMetaField_Destroy(igMemoryRefMetaField *arg0, long long arg1);
extern "C" void *igRefMetaField_Destroy(igRefMetaField *arg0, short arg1);
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
extern "C" void *igFile_Destroy(igFile *arg0, short arg1);
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
extern "C" igMetaObject *igLongTimer_GetMetaObject(void);
extern "C" char thunk_igLongTimer_GetMetaObject_002b7b60[];
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
extern "C" igSmartPointer<igObject> *igSmartPointer_igShortListList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" int DAT_00530890[4];

extern "C" igDirectory *igDirectory_Destroy(igDirectory *p, short n);
extern "C" int DAT_00524a20[4];
extern "C" int DAT_005309b0[4];
extern "C" int DAT_00532590[4];
extern "C" void *igDirectory_Construct(igIGBFile *arg0);
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
extern "C" char igIntListNoClean_className[];
extern "C" igMetaObject *g_igIntList_metaObject[4];
extern "C" igMetaObject *igIntList_GetMetaObject(void);
extern "C" int DAT_00531b70[4];
extern "C" char igIntList_className[];
extern "C" int g_igIntList_dataDescriptorCell[4];
extern "C" igMetaObject *g_igCharListNoClean_metaObject[4];
extern "C" igMetaObject *igCharListNoClean_GetMetaObject(void);
extern "C" int DAT_00531a50[4];
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
extern "C" void igCompoundMetaField_InitDefaults(igCompoundMetaField *self);
extern "C" igMetaObject *g_igCharMetaField_metaObject[4];
extern "C" igMetaObject *igCharMetaField_GetMetaObject(void);
extern "C" char g_igCharMetaField_callbackList[];
extern "C" char igCharMetaField_className[];
extern "C" void * DAT_00586938[4];
extern "C" igMetaObject *g_igCharArrayMetaField_metaObject[4];
extern "C" igMetaObject *igCharArrayMetaField_GetMetaObject(void);
extern "C" int DAT_00530a80[4];
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
extern "C" char g_igBoolArrayMetaField_callbackList[];
extern "C" char igBoolArrayMetaField_className[];
extern "C" int g_igBoolArrayMetaField_ctorTable[4];
extern "C" int g_igBoolArrayMetaField_fieldTable[4];
extern "C" int DAT_004c1590[4];
extern "C" int DAT_004c1598[4];
extern "C" igBoolArrayMetaField *DAT_005869a0[4];
/* Class factory of igAliasMemoryPool. Once the object system is running it registers the class and
 * creates the pool through its metaobject on `allocator`. During bootstrap, before the object
 * system exists, it allocates the 184-byte pool by hand, constructs it, and then runs vfunc_09 and
 * userConstruct(0) on it. Those calls are not guarded against a failed allocation. */
class igAliasMemoryPoolView;
extern "C" igAliasMemoryPoolView *igAliasMemoryPool_Create(void *allocator);
extern "C" igMetaObject *g_igAliasMemoryPool_metaObject[4];
extern "C" igMetaObject *igAliasMemoryPool_GetMetaObject(void);
extern "C" int g_igAliasMemoryPool_vtable[4];
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
extern "C" char igElfFile_className[];
extern "C" int g_igElfFile_ctorTable[4];
extern "C" int g_igElfFile_fieldTable[4];
extern "C" int DAT_004c1b90[4];
extern "C" int DAT_004c1bc0[4];
extern "C" igMetaObject *g_igStandardQueue_metaObject[4];
extern "C" igMetaObject *igStandardQueue_GetMetaObject(void);
extern "C" int DAT_0052ddf0[4];
extern "C" int DAT_0052ee50[4];
extern "C" void *igQueue_Destroy(igQueue *arg0, short arg1);
extern "C" char g_igStandardQueue_callbackList[];
extern "C" char igStandardQueue_className[];
extern "C" int g_igStandardQueue_ctorTable[4];
extern "C" int g_igStandardQueue_fieldTable[4];
extern "C" int DAT_004c1c30[4];
extern "C" int DAT_004c1c50[4];
extern "C" igMetaObject *g_igPsx2ThreadManager_metaObject[4];
extern "C" igMetaObject *igPsx2ThreadManager_GetMetaObject(void);
extern "C" int DAT_0052d750[4];
extern "C" char igPsx2ThreadManager_className[];
extern "C" int igPsx2ThreadManager_InitFields_002cf3f0[4];
extern "C" igMetaObject *g_igPsx2Thread_metaObject[4];
extern "C" igMetaObject *igPsx2Thread_GetMetaObject(void);
extern "C" int DAT_0052d7c0[4];
extern "C" char g_igPsx2Thread_callbackList[];
extern "C" char igPsx2Thread_className[];
extern "C" int g_igPsx2Thread_ctorTable[4];
extern "C" int g_igPsx2Thread_fieldTable[4];
extern "C" int DAT_004c1cc0[4];
extern "C" int DAT_004c1ce0[4];
extern "C" igMetaObject *g_igPsx2Semaphore_metaObject[4];
extern "C" igMetaObject *igPsx2Semaphore_GetMetaObject(void);
extern "C" int DAT_0052d970[4];
extern "C" char igPsx2Semaphore_className[];
extern "C" int g_igPsx2Semaphore_ctorTable[4];
extern "C" int g_igPsx2Semaphore_fieldTable[4];
extern "C" int DAT_004c1d18[4];
extern "C" int DAT_004c1d28[4];
extern "C" igMetaObject *g_igPsx2Media_metaObject[4];
extern "C" igMetaObject *igPsx2Media_GetMetaObject(void);
extern "C" int DAT_0052da00[4];
extern "C" char g_igPsx2Media_callbackList[];
extern "C" char igPsx2Media_className[];
extern "C" int g_igPsx2Media_ctorTable[4];
extern "C" int g_igPsx2Media_fieldTable[4];
extern "C" int DAT_004c1d90[4];
extern "C" int DAT_004c1db0[4];
extern "C" igMetaObject *g_igPsx2LongTimer_metaObject[4];
extern "C" igMetaObject *igPsx2LongTimer_GetMetaObject(void);
extern "C" int DAT_0052da90[4];
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
extern "C" char igPsx2CallStackTracer_className[];
extern "C" int igPsx2CallStackTracer_InitFields_002d0530[4];
extern "C" int g_igAliasMemoryPool_vtable[4];
extern "C" char DAT_004f90b0[];
extern "C" int text_null[4];
extern "C" char DAT_004f90c0[];
extern "C" int DAT_004f92b0[4];
extern "C" int DAT_004f92f0[4];
extern "C" void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, igMemoryPoolView *alias);
extern "C" void igAliasMemoryPool_Activate(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_Reset(igAliasMemoryPool *self);
/* igAliasMemoryPool's virtuals: the igMemoryPool table, then the alias pool's own slots 97-101
 * (vfunc_99 to vfunc_103). */
class igAliasMemoryPoolView : public igMemoryPoolView {
public:
    virtual int vfunc_99();                                                      /* slot 97, byte 396: the aliased pool */
    virtual void vfunc_100(igMemoryPool *aliased);                               /* slot 98, byte 400 */
    virtual int vfunc_101();                                                     /* slot 99, byte 404 */
    virtual int vfunc_102();                                                     /* slot 100, byte 408 */
    virtual int ManageAllocation(int block, int size, unsigned short alignment); /* slot 101, byte 412 */
};
extern "C" void igAliasMemoryPool_Deactivate(igAliasMemoryPool *self);
extern "C" unsigned char igAliasMemoryPool_IsActive(igAliasMemoryPool *self);
class igResult;
extern "C" igResult igAliasMemoryPool_EnableAllocationLock(igAliasMemoryPool *pool, int enable);
extern "C" void igAliasMemoryPool_SetMaxSize(int *status, igAliasMemoryPool *self, long long maxSize);
extern "C" long long igAliasMemoryPool_GetMaxSize(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_SetAlignment(int *status, igAliasMemoryPool *self, short alignment);
extern "C" unsigned short igAliasMemoryPool_GetAlignment(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_SetElementSize(int *status_out, igAliasMemoryPool *self, int element_size);
extern "C" int igAliasMemoryPool_GetElementSize(igAliasMemoryPool *self);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_46(igAliasMemoryPool *arg0);
extern "C" long long igAliasMemoryPool_GetLocalNetAllocated(igAliasMemoryPool *self);
extern "C" long long igAliasMemoryPool_GetLocalNetAllocatedWithOverhead(igAliasMemoryPool *self);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_101(igAliasMemoryPool *arg0);
extern "C" long long Gap__Core__igAliasMemoryPool__vfunc_102(igAliasMemoryPool *arg0);
extern "C" long long igAliasMemoryPool_GetFreeSize(igAliasMemoryPool *arg0);
extern "C" void *igAliasMemoryPool_AllocateElement(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_Lock(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_Unlock(igAliasMemoryPool *self);
extern "C" int igAliasMemoryPool_UnlockAndReturn(igAliasMemoryPool *self, int result);
extern "C" void *igAliasMemoryPool_Allocate(igAliasMemoryPool *self,unsigned int size);
extern "C" void *igAliasMemoryPool_AllocateAligned(igAliasMemoryPool *self,unsigned int size,unsigned short alignment);
extern "C" int igAliasMemoryPool_Callocate(igAliasMemoryPool *arg0, int arg1, int arg2);
extern "C" void *igAliasMemoryPool_Reallocate(igAliasMemoryPool *self,void *old,unsigned int size);
extern "C" void *igAliasMemoryPool_ReallocateAligned(igAliasMemoryPool *self,void *old,unsigned int size,unsigned short alignment);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_65(igAliasMemoryPool *arg0, int arg1);
extern "C" igResult igAliasMemoryPool_GangAlloc(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks);
extern "C" igResult igAliasMemoryPool_GangAllocAligned(igAliasMemoryPool *self, int count, unsigned int *sizes, void **blocks, unsigned short *alignments);
extern "C" void igAliasMemoryPool_GangFree(igAliasMemoryPool *self, int count, void **blocks);
extern "C" void *igAliasMemoryPool_Free(igAliasMemoryPool *self,void *old);
extern "C" unsigned int igAliasMemoryPool_GetAllocationSize(igAliasMemoryPool *self,void *old);
/* igReport_Printf is declared variadic, so the first call passes only the format. */
extern "C" void igAliasMemoryPool_PrintStatistics(igAliasMemoryPoolView *self, char *arg1);
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
    virtual void Print(const char *format, ...);                                    /* +124: printf */
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
extern "C" int igAliasMemoryPool_ManageAllocation(igAliasMemoryPool *self, int block, int size, unsigned short alignment);
extern "C" void *igAliasMemoryPool_Initialize(igAliasMemoryPool *self);
extern "C" void *igAliasMemoryPool_Construct(igAliasMemoryPool *self, int extra1);
extern "C" void *igAliasMemoryPool_CopyConstruct(igAliasMemoryPool *self, int extra1);
extern "C" void igAliasMemoryPool_Destruct(igAliasMemoryPool *self);
extern "C" int DAT_00530d80[4];
extern "C" long long DAT_00586dd8[4];
extern "C" int DAT_00586dc0[4];
extern "C" char DAT_004f9300[];
extern "C" unsigned char GPR_00554bf8;
struct ObjectSystemView;
class igEventTrackerView;
extern "C" void igObjectSystem_Startup(ObjectSystemView *self);
extern "C" int IG_ROOT[4];
extern "C" int DAT_004f9468[4];
extern "C" int DAT_004f9470[4];
extern "C" int StringPool_Intern(StringPool *pool, const char *name);
/* Header stored in front of every interned string token. */
struct StringTokenHeader { int owner; int refCount; };
static inline void retainString(const char *string) {
    if (string != 0) {
        StringTokenHeader *header = (StringTokenHeader *)string - 1;
        header->refCount = header->refCount + 1;
    }
}
static inline void releaseString(const char *string) {
    if (string != 0) {
        StringTokenHeader *header = (StringTokenHeader *)string - 1;
        int count = header->refCount - 1;
        header->refCount = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (int)header);
        }
    }
}
/* The shared intern pool g_stringPool[0], created on first use. */
struct InternedStrings {
    static inline StringPool *get() {
        if (g_stringPool[0] == 0) {
            StringPool *pool = (StringPool *)StringPool_Allocate(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = (int)pool;
        }
        return (StringPool *)g_stringPool[0];
    }
};
/* A reference to a string interned in the shared pool. Constructing or assigning from characters
 * interns them; copies share the token and count it. */
struct igStringRef {
    char *p;
    igStringRef() : p(0) {}
    igStringRef(char *chars) {
        char *interned;
        if (chars == 0) {
            interned = 0;
        } else {
            interned = (char *)StringPool_Intern(InternedStrings::get(), chars);
        }
        p = interned;
    }
    igStringRef(const igStringRef &other) : p(other.p) { retainString(p); }
    ~igStringRef() { releaseString(p); }
    igStringRef &operator=(const igStringRef &other) {
        retainString(other.p);
        releaseString(p);
        p = other.p;
        return *this;
    }
    igStringRef &operator=(char *chars) {
        char *interned = (char *)StringPool_Intern(InternedStrings::get(), chars);
        releaseString(p);
        p = interned;
        return *this;
    }
};
extern "C" void igObjectSystem_InitPaths(ObjectSystemView *arg0);
extern "C" int text_exitPre[4];
extern "C" void igObjectSystem_PreExit(ObjectSystemView *arg0);
extern "C" int text_exitIn[4];
extern "C" void igObjectSystem_Exit(ObjectSystemView *arg0);
class MemoryContext;
extern "C" MemoryContext *DAT_00586fd0[4];
extern "C" __internalObjectList *DAT_00587188[4];
extern "C" void igObjectSystem_Shutdown(ObjectSystemView *arg0);
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
    igMemoryPoolView *bootstrapPool; /* the allocator of record 0 (Bootstrap) */
    igMemoryPoolView *systemPool;    /* the allocator of record 4 (System) */
    igRegistry *configRegistry;
    char unknown60[4];
    igResource *resource;         /* the resource manager: named directories and objects */
    char unknown68[12];
    igSymbolTable *symbolTable;   /* loaded from symbolsFileName at memory set-up */
    igEventTrackerView *globalEventTracker; /* useGlobalEventTracker's tracker; receives the "exitPre" and "exitIn" markers */
    igMemoryPoolView *driverDataPool; /* the allocator of record 20 (DriverData) when it is its own pool */
    char unknown92[4];
    igMemoryPoolView *fastPool;       /* the allocator of record 7 (Fast) when it is its own pool */
    char unknown100[12];
    igObject *retainedObject;     /* released at shut-down */
    unsigned char useGlobalEventTracker;
    unsigned char saveEventTrackerOnExit;     /* MemoryContext::vfunc_56 runs at exit */
    unsigned char showLeaksOnExit;
    unsigned char showMemoryStatisticsOnExit;
    unsigned char showObjectStatisticsOnExit;
    char unknown121[3];
    void *eventTrackerInitialCapacity;
    int eventTrackerEventTypeFilter;
    int eventTrackerMarkerTypeFilter;
    int eventTrackerNotificationTypeFilter;
    int eventTrackerNotificationCodeFilter;
    char memoryEventFormat[128];
    char markerEventFormat[128];
    char notificationEventFormat[128];
    char unknown528[388];
    int vtableProbeOffset;        /* zero: the EnsureRegistered probes read the vtable word through it */
    igStringRef rootPath;         /* IG_ROOT from the environment */
    igStringRef basePath;
    /* igMemoryPoolContextInfo_ConfigureEventTracking reads these two through calls: as plain member reads their locals take other saved registers. */
    igMemoryPoolView *getSystemPool() { return systemPool; }
    int getConfigRegistry() { return (int)configRegistry; }
} ObjectSystemView;
extern "C" igMetaField *g_igMetaObjectNameField[4];
extern "C" int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className);
extern "C" void igObjectSystem_AddRegistrationCallback(ObjectSystemView *arg0, int (*arg1)(int));
extern "C" char *DAT_004c1eb8[4];
extern "C" void igObjectSystem_SetMemoryEventFormat(ObjectSystemView *objectSystem, char *format);
extern "C" void * DAT_004c1ec0[4];
extern "C" void igObjectSystem_SetMarkerEventFormat(ObjectSystemView *objectSystem, char *format);
extern "C" void * DAT_004c1ec8[4];
extern "C" void igObjectSystem_SetNotificationEventFormat(ObjectSystemView *objectSystem, char *format);
/* The growable callback array of the class-registration protocol (data pointer, count, capacity).
 * The growth rule is retail's, not a conventional 1.5x: the first capacity is 4 and every later
 * growth multiplies the capacity by (capacity * 3) / 2, so ordinary capacities advance 4 -> 24 ->
 * 864. Do not "fix" it. */
typedef struct {int *data;int count;int capacity;} CallbackArray;
extern "C" CallbackArray *igArray_Construct(CallbackArray *array);
extern "C" CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag);
extern "C" int igArray_Append(CallbackArray *array,int item);
extern "C" void igBoolArrayMetaField_SwapBytes(igBoolArrayMetaField *self, int buffer, int count);
extern "C" void igBoolArrayMetaField_SetDefaultAll(igBoolArrayMetaField *arg0, int arg1);
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
    virtual int vfunc_49(int object);                                           /* +196 */
    virtual int WriteRawFieldMem(int dest, int source, int a3, unsigned char swap); /* +200 */
    virtual int ReadRawFieldMem(int dest, int source, int a3, unsigned char swap); /* +204 */
    virtual int SwapBytes(void *buffer, int count);                               /* +208 */
    virtual void SwapValue(int object);                                         /* +212 */
    RESERVED(52); RESERVED(53);                                                 /* +216, +220 */
    virtual int vfunc_56(int object, int text, int directory);                  /* +224 */
    virtual igStringRef vfunc_57(int object, int directory);                    /* +228 */
    RESERVED(56); RESERVED(57);                                                 /* +232, +236 */
    virtual int IsConstruct();                                                  /* +240 */
    unsigned int _refCount;
    int _offset; int _fieldName; short _typeIndex; short _internalIndex; unsigned short _size; char _pad22[2];
    int _parentMetaObject; int _externalEnumStorage; int _default;
    char _resetMethod; unsigned char _isRunTime; unsigned char _persistent; char _shallowCopyMethod;
    char _deepCopyMethod; char _constructCopyMethod; char _isAlikeExactlyMethod; char _isAlikeDeepMethod;
    char _isAlikeShallowMethod; char _pad45[3];
    int _invarianceFunction;
};
extern "C" void igCallStackTable_Clear(igCallStackTableView *table);
extern "C" void igCallStackTable_TruncateCallStacks(igResult *result, igCallStackTableView *table, int count);
extern "C" unsigned int *igCallStackTable_GetCallStack(igCallStackTableView *table, int offset);
extern "C" void igCallStackTable_InsertCallStack(igCallStackTableView *table, int *stack);
extern "C" unsigned int igCallStackTable_HashCallStack(igCallStackTableView *self, unsigned int *stack);
extern "C" int igCallStackTable_InsertHashEntry(igCallStackTableView *self, unsigned int *stack, int offset);
extern "C" int DAT_004c1e98[];
extern "C" void igCallStackTable_RebuildHashIndex(igCallStackTableView *table, int hashCapacity);
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
extern "C" void igCallStackTracer_FormatAddress(igResult *result, igCallStackTracerView *self, int addr, int format, long long output, long long outputSize);
extern "C" const igResult g_resultSuccess;
extern "C" const igResult g_resultFailure;
extern "C" igResult igThread_SetPriority(igPsx2Thread *self, int priority);
extern "C" igResult igCallStackTracer_LookupAddress(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" void igCharArrayMetaField_SwapBytes(igCharArrayMetaField *self, int buffer, int count);
extern "C" unsigned short igCharArrayMetaField_GetSize(igCharArrayMetaField *self);
extern "C" int DAT_004f95c0[4];
extern "C" int DAT_00531640[4];
extern "C" int igCompoundMetaField_GetAlignment(igCompoundMetaField *arg0);
extern "C" void igCompoundMetaField_ConstructValue(igCompoundMetaField *arg0, int arg1);
extern "C" void igCompoundMetaField_DestructValue(igCompoundMetaField *arg0, int arg1);
extern "C" void igCompoundMetaField_ZeroValue(igCompoundMetaField *a, int x);
extern "C" void igCompoundMetaField_ClearValue(igCompoundMetaField *arg0, int arg1);
extern "C" void igCompoundMetaField_ResetValue(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" void igCompoundMetaField_IgnoreCopy(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" void igCompoundMetaField_Print(igCompoundMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" void igCompoundMetaField_ReleaseElements(igCompoundMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int igCompoundMetaField_Write(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_Compare(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_IsAlikeExactly(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_IsAlikeDeep(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_IsAlikeShallow(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_IsAlikeIgnore(igCompoundMetaField *arg0, int arg1, int arg2);
extern "C" int igCompoundMetaField_WriteRawFieldMem(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, unsigned char arg4);
extern "C" int igCompoundMetaField_ReadRawFieldMem(igCompoundMetaField *arg0, int arg1, int arg2, int arg3, unsigned char arg4);
extern "C" void igCompoundMetaField_SwapBytes(igMetaFieldView *arg0, int arg1, int arg2);
extern "C" int DAT_004f95e8[4];
extern "C" int DAT_004f95f0[4];
extern "C" int DAT_004f95f8[4];
extern "C" int DAT_004f9600[4];
extern "C" int igCompoundMetaField_ValueToString(igStringRef *out, igMetaFieldView *ctx, int a2, int a3);
extern "C" void igContext_BuildExtensionInfoList(igContext *arg0);
extern "C" int igContext_GetExtensionInfoList(igContext *arg0);
extern "C" int igContext_FindExtensionMeta(igContext *arg0, int arg1);
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
extern "C" void *igContext_GetExtension(igVisualContext *arg0, int extra1);
extern "C" int igContext_FindExtensionInstance(igContext *arg0, int arg1);
extern "C" igMetaField *DAT_005867a0[4];
extern "C" void List_Reserve(igDataList *list, int capacity, int elementSize);
extern "C" void List_AppendBytes(igDataList *l, int cnt, int src, int sz);
extern "C" void List_RemoveAt(igDataList *l, int i, int sz);
extern "C" int List_BinarySearch(igDataList *arg0, int arg1, int (*arg2)(int, int), int arg3);
extern "C" int List_AppendWord(igDataList *list, int value);
extern "C" int ObjectList_AppendRetained(igObjectList *list, igObject *object);
extern "C" void List_AppendWords(igDataList *list, int count, const int *words);
extern "C" void List_RemoveWordAt(igDataList *l, int i);
extern "C" int List_BinarySearchWords(igDataList *arg0, int arg1, int (*arg2)(int, int));
typedef int (*Cmp)(int *, void *);
extern "C" int List_LowerBound(igDataList *l, void *key, Cmp cmp);
struct DependencyPair { int a; int b; };
struct igDependencyOrderedListView {
    int _vtable; unsigned int _refCount;
    igTDataList<igObject *> *_objectList;
    igTDataList<DependencyPair> *_dependencies;
    int _order;
    int _checkPoints;
    unsigned char _hasCircularDependencies;
};
extern "C" void igDependencyOrderedList_AddDependency(igDependencyOrderedListView *arg0, int arg1, int arg2);
extern "C" int igRendererOrderedList_Append(igDependencyOrderedListView *, igObject *, int);
extern "C" void igDependencyOrderedList_Rebuild(igDependencyOrderedListView *owner);
extern "C" igResult igObjectList_RemoveRetained(igDependencyOrderedListView *list, igObject *object);
extern "C" void igDependencyOrderedList_RemoveDependency(int *arg0, igDependencyOrderedListView *arg1, int arg2, int arg3);
extern "C" void igDependencyOrderedList_RemoveDependencies(igDependencyOrderedListView *arg0, int arg1);
class igSemaphoreView;
struct igDirectoryView;
class igDirEntryView;
class igInfoView;
struct igDirectoryView : public igVirtualObject {
    int _count; int _capacity; igDirEntryView **_data; int _name;
    igTDataList<igDirectoryView *> *_externalDirectoryList; igTDataList<igInfoView *> *_infoList; igResource *_managingResource;
    unsigned char _sharingState; unsigned char _trackUniqueEntries; char _pad38[2];
    igObjectList *_uniqueEntryList; igTDataList<int> *_refList;
    unsigned char _loadPendingState; unsigned char _validState; unsigned char _compatibleState; char _pad51[1];
    int _loadedRefCount; unsigned char _concreteState; char _pad57[3]; igTDataList<igTDataList<short> *> *_metaFieldPerObjectIndices;
    unsigned char _autoWriteFilePreProcessState; unsigned char _useMemoryPoolAssignmentsState;
    unsigned char _forceWriteMemoryPoolInfoFromMetaState; char _pad67[1];
    igSemaphoreView *_loadingSemaphore;
};
class igIGBFileView;
class igDirEntryView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18();
    virtual igDirEntryView *cloneViaMetadata(int copyMode);                     /* vfunc_21 */
    virtual void d20();
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
    virtual int vfunc_43(int loadFunction);
    int _name; int _index; int _resolveMethod; int _refType; int _ref;
};
class igExternalDirEntryView : public igDirEntryView { public:
    virtual int vfunc_44(int loadFunction);
    int _directoryName; int _entryName; int _entryIndex; int _externalFilePath;
};
/* igDirectory's own virtual slots. ABI view only: never instantiated. */
class igDirectoryDispatchView : public igDirectoryView { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22();
    virtual int resolveExternalEntry(igExternalDirEntryView *entry);            /* vfunc_25 */
};
class igExternalInfoEntryView : public igDirEntryView { public:
    char *_key; int _directoryIndex; char *_infoName;
    void setDirectoryIndex(int index) { _directoryIndex = index; }
    void setKey(char *key) { char *interned = (char *)StringPool_Intern(InternedStrings::get(), key); releaseString(_key); _key = interned; }
    void setInfoName(char *name) { char *interned = (char *)StringPool_Intern(InternedStrings::get(), name); releaseString(_infoName); _infoName = interned; }
};
/* igObject's virtual functions: slot n sits at vtable byte offset 8 + 4 * n (the first two words
 * are the class header). The reflected igObject is the same object seen as data. Named slots carry
 * the igObject symbol names (Gap::Core::igObject::<name>, igObject_CloneViaMetadata); vfunc_NN
 * keeps the symbol's slot number. Slot 17 takes the value the meta-object's write proxy returns.
 * ABI view only: never instantiated. */
class igObjectDispatchView {
public:
    virtual void vfunc_00();
    virtual void constructFields(int flag);
    virtual void destructFields();
    virtual void vfunc_03(igObjectDispatchView *source); virtual void vfunc_04(int source);
    virtual int vfunc_05(igObjectDispatchView *other);
    virtual int vfunc_06(igObjectDispatchView *other);
    virtual void userConstruct(int flag);
    virtual void userDestruct();
    virtual void vfunc_09(); virtual void vfunc_10();
    virtual void resetFields(int flag);
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14();
    virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(int value); virtual void vfunc_18(igMetaObject *meta);
    virtual igObject *cloneViaMetadata(int copyMode);
    virtual igMetaObject *getMeta();
    unsigned int _refCount;
};
/* Removes the object at `index`, releasing it, and clears the vacated last slot. */
static inline void objectListRemoveRetained(igTDataList<igObject *> *list, int index) {
    igObject *o = list->_data[index];
    IG_OBJECT_RELEASE(o);
    List_RemoveWordAt((igDataList *)list, index);
    list->_data[list->_count] = 0;
}
extern "C" int DAT_00586730[4];
extern "C" int g_propertyNameField[4];
extern "C" void igDirectory_ReleaseDefaults(igDirectoryView *arg0);
extern "C" int igDirectory_GetEntryByRef(igDirectoryView *arg0, unsigned key);
extern "C" void igDirectory_SetEntryRef(igDirectoryView *a, int i, int x);
extern "C" int igDirectory_ReplaceReference(igDirectoryView *self, igObjectDispatchView **field, igObjectDispatchView **value);
extern "C" void igDirectory_RemoveInfo(igDirectoryView *h, igObject *object);
extern "C" int igDirectory_FindObjectReferenceInInfos(igDirectoryView *arg0, int arg1, int arg2);
extern "C" int igDirectory_AddObjectCallback(int arg0, igMetaFieldView *arg1, igDirectoryView *arg2);
extern "C" int igDirectory_FindSortedInsertIndex(igDirectoryView *arg0, igMetaField *arg1, unsigned arg2);
/* The pointer word an object list copies in on insert, holding the reference the list takes. It is
 * a class member, not a plain pointer local: igDirectory_InsertObject and igIGBFile_ShareEntries store the word and load
 * it back from its stack slot before the null test (`sw v0,104(sp); lw v1,104(sp); beqz v1`), which
 * MWCC emits for a member read after the constructor's store. A scalar local or parameter is tested
 * from the register and stored in the branch delay slot (712 bytes against retail's 716, and 720
 * against 724). */
template <class T> struct RetainedWord {
    T *p;
    RetainedWord(T *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};
/* An object list's insert: the list takes its own reference, then copies the pointer word in. */
template <class T> static inline void insertObject(igDataList *list, int index, T *object) {
    RetainedWord<T> word(object);
    List_InsertWords(list, index, 1, &word);
}
extern "C" int igDirectory_InsertObject(igDirectoryView *self, igObjectDispatchView *obj, char *name, int resolveMethod);
extern "C" int igDirectory_AddMemoryRef(igDirectoryView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, unsigned char arg7);
extern "C" int igDirectory_AddRawRef(igDirectoryView *list, int key, int name, int val);
extern "C" void igDirectory_MakeConcrete(igDirectoryView *arg0);
extern "C" void igDirectory_SetName(igDirectoryView *arg0, int arg1);
extern "C" int igDirectory_ResolveExternalEntry(igDirectoryView *c, igExternalDirEntryView *o);
extern "C" int igDirectory_UnrefLoaded(igDirectoryView *self);
extern "C" void igDirectory_CreateLoadingSemaphore(igDirectoryView *directory);
extern "C" void igDoubleArrayMetaField_SwapBytes(igDoubleArrayMetaField *arg0, int arg1, int arg2);
extern "C" int igDoubleArrayMetaField_GetSize(igDoubleArrayMetaField *self);
extern "C" int text_lg_n[4];
extern "C" int DAT_004f9610[4];
extern "C" char text_driverDatabaseVerbose[];
extern "C" void igDriverDatabase_InitDefaults(igDriverDatabase *database);
extern "C" int FUN_001cafc0(igObject *, int *, int);
extern "C" int igDriverDatabase_GetSubPropertyValue(igDriverDatabase *arg0, int arg1, int arg2);
/* igVisualContext (an igPsx2VisualContext at run time): slot 25 is vfunc_27, which records the
 * platform names in a driver database. */
class igVisualContextView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void Describe(void *target);
};
extern "C" char *g_stringObjEmptyText[4];
extern "C" void igDriverDatabase_GatherProperties(void *self, igTDataList<igVisualContextView *> *list);
extern "C" int text_drivers_ini[4];
extern "C" int DAT_004f96a8[4];

/* igFolder: a search folder; slot 21 joins _folderName with a file name. */
class igFolderView : public igVirtualObject { public:
    RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6); RESERVED(7);
    RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13); RESERVED(14);
    RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19); RESERVED(20);
    virtual igSmartPointer<igStringObj> vfunc_23(const char *name);             /* +92 */
    igStringRef _folderName;
    void setFolderName(char *name) { _folderName = name; }
};
extern "C" int igDriverDatabase_Load(igDriverDatabase *arg0, const char *arg1, const char *arg2);
/* A node of the parsed driver database (vtable DAT_00530618); section and settings nodes extend it.
 * Slot 0 is the deleting destructor. */
class ConfigNode { public: int kind; virtual void Delete(int flags); };
extern "C" void igDriverDatabase_ProcessConfigNode(igDriverDatabase *self, ConfigNode *node, igRegistry *registry, int section);
extern "C" igTDataList<ConfigNode *> *igDriverDatabase_ParseDatabase(igDriverDatabase *s);
extern "C" void igDriverDatabase_DeleteConfigNodeList(void *self, igTDataList<ConfigNode *> *list);
extern "C" int DAT_00530618[4];
extern "C" int igDriverDatabase_ApplyToRegistry(igDriverDatabase *arg0, int arg1, int arg2, int arg3);
/* The character variable is an int; a char would add a sign extension. */
extern "C" void igDriverDatabase_LoadDatabaseFile(igDriverDatabase *self, igFileView *file);
extern "C" int text_psx2_2[4];
extern "C" int text_mips[4];
extern "C" bool igDriverDatabase_ReadLineFromFile(void *a0, igFileView *s, char *buf, int n);
class ConfigNode;
extern "C" ConfigNode *FUN_002dae40(igDriverDatabase *self);
extern "C" char text_SETTINGS[];
extern "C" char *g_driverDatabaseKeywords[13];
extern "C" int igDriverDatabase_ResolveSettingsSection(igDriverDatabase *self, igStringObj *sectionName, igRegistry *registry, int fallback);
extern "C" char _ctype_[];
extern "C" int text_abcdefghijklmnopqrstuvwxyzABCDEF[4];
extern "C" bool igDriverDatabase_ParseIdentifier(igDriverDatabase *arg0, int *arg1);
extern "C" int DAT_004f9718[4];
extern "C" int DAT_004f9670[4];
extern "C" int DAT_004f9728[4];
extern "C" int igDriverDatabase_ParsePropertyBlock(igDriverDatabase *self, struct ConfigSectionNode *out);
extern "C" int igDriverDatabase_ParseParenthesizedIdentifier(igDriverDatabase *parser, int *out);
extern "C" int DAT_004f9730[4];
extern "C" int DAT_004f9738[4];
extern "C" int DAT_00530608[4];
class ConfigPair { public: igStringObj *key; igStringObj *value; virtual void Delete(int flags); };
extern "C" ConfigPair *igDriverDatabase_Setting_Destruct(ConfigPair *self, int delete_storage);
extern "C" int DAT_005305f8[4];
extern "C" unsigned char g_useOwnerAllocator;
struct ConfigSettingsNode { int kind; int vtable; igTDataList<ConfigPair *> *entries; igStringObj *name; };
extern "C" int igDriverDatabase_ParseSettingsBlock(igDriverDatabase *self, ConfigSettingsNode *out);
extern "C" void igDriverDatabase_ApplySettings(igDriverDatabase *self, igTDataList<ConfigPair *> *entries, igRegistry *registry, int section);
extern "C" void *igDriverDatabase_SettingsNode_Destruct(ConfigSettingsNode *arg0, long long arg1);
extern "C" int DAT_005305e8[4];
struct ConfigSectionNode { int kind; int vtable; int id; igStringObj *name; igTDataList<ConfigNode *> *children; int compareMode; igStringObj *selector; };
extern "C" void *igDriverDatabase_PropertyNode_Destruct(ConfigSectionNode *arg0, long long arg1);
extern "C" void igEnumArrayMetaField_SwapBytes(igEnumArrayMetaField *self, int buffer, int count);
extern "C" int igEnumArrayMetaField_GetSize(igEnumArrayMetaField *self);
extern "C" void igEnumMetaField_SetDefaultValue(igMetaFieldView *self, const int *value);
extern "C" void igEnumMetaField_ValueToString(int result, igEnumArrayMetaField *self, int *value);
extern "C" int DAT_00532430[4];
extern "C" void * DAT_00586df8[4];
extern "C" char GPR_00554bfc;
extern "C" unsigned char DAT_00554bfc;
class igEventTrackerView;
extern "C" void igEventTracker_SetThreadSafe(igEventTrackerView *self, int open);
class igEventTrackerView;
extern "C" void igEventTracker_SetEventTag(igEventTrackerView *tracker, int tag);
struct LocationRecord { int address; int name; int offset; int file; int line; };
/* igLocationTable (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
class igLocationTableView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int vfunc_26(int address);
    virtual igResult vfunc_27(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void d26();
    virtual void vfunc_29(int addr, char *buf, int offset, char *name, int line);
    virtual unsigned int vfunc_30(unsigned int address);
    virtual int vfunc_31(int address, int index);
    virtual void vfunc_32(int capacity);
    int _capacity; int _hashCapacity; igTDataList<unsigned int> *_locations; igTDataList<int> *_hashIndex; int _symbolNames; int _sourceFileNames;
};
/* One igEventTracker event (148 bytes): cleared by igEventTracker_ClearEvent, built by igEventTracker_InitMemoryEvent/igEventTracker_InitMarkerEvent,
 * stored by vfunc_26 and decoded back by vfunc_27. slotStates holds a 2-bit state for each of the
 * 16 words in slots (igEventTracker_FindFreeEventDataSlot..igEventTracker_GetEventDataUnsigned3). */
enum igEventType {
    kEventTypeAny, kMemoryAllocation, kMemoryDetach, kMemoryDeallocation, kMemoryRead, kMemoryWrite, kObjectAllocation,
    kObjectDetach, kObjectDeallocation, kObjectRead, kObjectWrite, kMemberRead, kMemberWrite, kMarker, kNotification, kCustom
};
struct EventRecord { int type; int index; int pad8; int val; int pad16; int markerType; int pad24[6]; char *str; int pad52[4]; int f68; int f72; int *callStack; unsigned int slotStates; int slots[16]; int getType() const { return type; } int getVal() const { return val; } };
/* igEventTracker (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
class igEventTrackerView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_23();                                                    /* slot 21, byte 92 */
    virtual void vfunc_24();                                                    /* slot 22, byte 96: closes what vfunc_23 began */
    virtual void d23();
    virtual void vfunc_26(EventRecord *record, int mode);
    virtual igResult vfunc_27(int offset, EventRecord *record);
    virtual void d26();
    virtual igResult vfunc_29(int offset, int *value);
    virtual void d28(); virtual void d29();
    virtual void vfunc_32(int, int, int *total, int *counts, int *, int *, int *, int *, int *, int *, int *, int, int, int *, int, int); /* slot 30, byte 128: leak summary */
    virtual void vfunc_33(int, int, int name, int *, int *, int *, int *);    /* slot 31, byte 132: per-name sizes */
    virtual int vfunc_34(int offset);
    virtual int vfunc_35();                                                     /* slot 33, byte 140 */
    virtual void d34(); virtual void d35();
    virtual void vfunc_38(EventRecord *record, char *buffer, int size);         /* slot 36, byte 152: formats a record */
    virtual void d37();
    virtual igResult vfunc_40(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void vfunc_41(int offset);
    virtual void d40();
    virtual void vfunc_43();                                                    /* slot 41, byte 172 */
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
extern "C" void igEventTracker_SetEventClassName(igEventTrackerView *tracker, int className);
extern "C" void igEventTracker_Initialize(igEventTrackerView *self);
extern "C" void igEventTracker_Shutdown(igEventTrackerView *self);
extern "C" void igEventTracker_Reset(igEventTrackerView *self);
extern "C" int DAT_004c1ea8[4];
extern "C" void Gap__Core__igEventTracker__vfunc_32(igEventTrackerView *self, int first, int last, int *eventCount, int *typeCounts, int *outstandingCount, unsigned int *allocatedBytes, unsigned int *freedBytes, unsigned int *netBytes, unsigned int *peakNetBytes, unsigned int *largestAllocation, unsigned int *netAtMarkerA, int markerA, int markerAOccurrence, unsigned int *netAtMarkerB, int markerB, int markerBOccurrence);
extern "C" void igEventTracker_GetStatisticsByName(igEventTrackerView *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7);
extern "C" int igEventTracker_FindIndex(igEventTrackerView *self, int value);
extern "C" char text_main[];
extern "C" void igEventTracker_IgnoreEventsInFunction(igEventTrackerView *self, char *wanted);
extern "C" unsigned int igEventTracker_GetHashBucketIndex(igEventTracker *self, unsigned int hash);
extern "C" void igEventTracker_InsertHashIndex(igEventTrackerView *self, int arg1, int arg2);
extern "C" int DAT_004c2120[4];
extern "C" void igEventTracker_RebuildHashIndex(igEventTrackerView *self, int n);
extern "C" int igEventTracker_GetMarkerTypeName(igEventTrackerView *tracker, int type);
extern "C" int igEventTracker_GetNotificationTypeName(igEventTrackerView *tracker, int type);
extern "C" igResult igEventTracker_FormatAddress(igEventTrackerView *self, int addr, int format, long long output, long long outputSize);
extern "C" int DAT_00586e00[4];
extern "C" int DAT_00586e08[4];
extern "C" int DAT_00586e10[4];
/* The result type has a constructor, so the return writes straight through the saved hidden
 * pointer. */
extern "C" igResult igEventTracker_ResolveAddress(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" int Gap__Core__igEventTracker__vfunc_35(igEventTrackerView *self);
extern "C" int Gap__Core__igEventTracker__vfunc_36(igEventTrackerView *self, int *cursor);
extern "C" void Gap__Core__igEventTracker__vfunc_43(igEventTrackerView *self);
extern "C" void igEventTracker_PrintEvent(igEventTrackerView *self, int offset);
extern "C" void igEventTracker_PrintAllEvents(igEventTrackerView *self);
extern "C" int DAT_004c1ed8[4];
extern "C" igResult igEventTracker_WriteFile(igEventTrackerView *self, int arg2);
extern "C" void igEventTracker_ResolveAllCallStackSymbols(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_46(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__vfunc_47(igEventTrackerView *self);
extern "C" int DAT_004c1ee0[32];
extern "C" int DAT_004c1f60[32];
extern "C" int DAT_004c1fe0[16];
extern "C" int DAT_004c2020[64];
extern "C" void Gap__Core__igEventTracker__resetFields(igEventTrackerView *self);
extern "C" int igEventTracker_GetEventDataType(EventRecord *record, int slot);
extern "C" char DAT_004f99f0[];
extern "C" unsigned char GPR_00554c00;
extern "C" void igExternalDirEntry_ReadFile(igExternalDirEntryView *arg0, void *arg1);
extern "C" void igExternalDirEntry_SetDirectoryName(igExternalDirEntry *arg0, int arg1);
extern "C" void igExternalDirEntry_SetRef(igDirEntry *arg0, igObject *arg1);
extern "C" int DAT_004f9a48[4];
extern "C" int text_root[4];
class igIGBFileView : public igDirectoryView { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void setObjectCursor(int at);                                       /* vfunc_26 */
    virtual int objectCursor();                                                 /* vfunc_27 */
    virtual int vfunc_28(int);
    virtual int ReadFile(const char *path);
    virtual igResult vfunc_30();
    virtual igResult vfunc_31();
    virtual igResult vfunc_32();
    virtual igResult vfunc_33();
    virtual int vfunc_34();
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
extern "C" int igExternalDirEntry_LoadExternalFile(igExternalDirEntryView *arg0, int arg1);
extern "C" int igExternalDirEntry_ResolveDirectory(igExternalDirEntryView *self, int loadFunction);
extern "C" void igExternalDirEntry_InitDefaults(igDirEntry *arg0);
extern "C" void igExternalIndexedEntry_Resolve(igExternalIndexedEntry *arg0, void *arg1);
class igInfoView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int vfunc_23(int directory, int object);
    virtual int GetFieldValueByName(int name);
    virtual igResult vfunc_25(igRegistry *ini, char *section);
    virtual igResult vfunc_26(igRegistry *ini, int index);
    virtual void print();                                                       /* vfunc_27 */
    unsigned int _refCount; int _name; int _directory; unsigned char _resolveState;
};
extern "C" void igExternalInfoEntry_Resolve(igExternalInfoEntry *self, igDirectory *directory);
extern "C" int DAT_004c2128[4];
extern "C" void **DAT_00586e18[4];
extern "C" int text_searchFilePath[4];
extern "C" int igFile_SetCompleteFilename(igFileView *arg0, int arg1);
extern "C" int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self);
extern "C" void igFloatArrayMetaField_SwapBytes(igFloatArrayMetaField *arg0, int arg1, int arg2);
extern "C" int DAT_004f9a68[4];
extern "C" int DAT_004f9a70[4];
extern "C" void igFolder_SetFolderName(igFolderView *self, const char *name);
extern "C" int DAT_004f9a78[4];
extern "C" igSmartPointer<igObject> igFolder_GetFullPath(igFolder *folder, int name);
class igLongTimerView;
extern "C" int DAT_004c2130[4];
extern "C" int DAT_004c2138[4];
extern "C" int DAT_004c2140[4];
extern "C" char text_forceWriteMemoryPoolInfoFromMeta[];
extern "C" char text_blindObjects[];
extern "C" int text_readFile_s[4];
extern "C" char DAT_004f9af0[];
extern "C" char text_Total_Time_to_load_s_f_seconds[];
extern "C" igMetaField *DAT_00586280[4];
/* igResource: the resource manager (g_globalContext): loaded directories, the asynchronous loader,
 * and the memory alignment names and values .igb files are matched against. */
class igStandardQueueView;
class igPsx2ThreadView;
struct igResourceView : public igObject {
    unsigned char _useMemoryPoolAssignmentsState; char _pad9[3];
    int _imageDirectory; int _directoryList; int _relativeFilePath; int _absoluteFilePath;
    unsigned char _asyncLoadState; char _pad29[3];
    igSmartPointer<igStandardQueueView> _loadQueue;
    igSmartPointer<igPsx2ThreadView> _loadThread;
    unsigned char _autoCompatibility; char _pad41[3];
    igTDataList<igStringObj *> *_alignmentStrings;
    igTDataList<int> *_alignmentValues;
};
extern "C" igResourceView *g_globalContext;
extern "C" char DAT_00586e20[64];
extern "C" igLongTimerView *DAT_005871d8[4];
extern "C" char GPR_00554c04;
extern "C" unsigned char GPR_00554c08;
extern "C" unsigned char GPR_00554c0c;
extern "C" unsigned char g_useOwnerAllocator;
extern "C" igResult FUN_002e4f60(igIGBFileView *self);
extern "C" igResult FUN_002e63e0(void *);
extern "C" igResult igIGBFile_OpenFile(igIGBFileView *self, const char *fileName, int mode);
extern "C" void igIGBFile_CloseFile(igIGBFileView *self);
extern "C" igResult igIGBFile_OpenForWrite(igIGBFileView *f, const char *fileName);
extern "C" igResult igIGBFile_BuildMetaObjectList(igIGBFileView *arg1);
extern "C" igResult igIGBFile_PrepareEntriesForWrite(igIGBFileView *arg1);
extern "C" igResult igIGBFile_BuildMemoryPoolNameBuffer(igIGBFileView *o);
extern "C" igResult igIGBFile_ComputeBufferSizes(igIGBFile *arg1);
/* One metaobject record of an .igb file's metaobject table. */
struct MetaTableRecord { int nameSize; int majorVersion; int minorVersion; int fieldCount; int parentIndex; int persistCount; };
/* A metaobject's parent reference as a one-word key passed by reference: the key is stored to the
 * stack and reloaded from there. */
struct MetaTableKey { int v; };
extern "C" igResult igIGBFile_BuildMetaObjectBuffer(igIGBFileView *self);
extern "C" igResult igIGBFile_BuildMetaFieldBuffer(igIGBFileView *arg1);
extern "C" igResult igIGBFile_BuildAlignmentBuffer(igIGBFileView *self);
extern "C" igResult igIGBFile_BuildExternalDirectoryBuffer(igIGBFileView *self);
extern "C" igResult igIGBFile_BuildDirectoryBuffer(igIGBFile *file);
extern "C" int FUN_00142bb0(igObjectList *list, void *key);
/* An object list's sorted insert: FUN_00142bb0 finds the position by the pointer's value. */
template <class T> static inline void insertObjectSorted(igObjectList *list, T *object) {
    RetainedWord<T> word(object);
    List_InsertWords((igDataList *)list, FUN_00142bb0(list, &word), 1, &word);
}
extern "C" igResult igIGBFile_ShareEntries(igIGBFileView *self);
extern "C" igResult igIGBFile_WriteEntryBuffer(igIGBFile *file);
extern "C" igResult igIGBFile_AllocateObjectBuffer(igIGBFileView *o);
extern "C" igResult igIGBFile_WriteHeader(igIGBFileView *o);
extern "C" igResult igIGBFile_WriteBuffers(igIGBFileView *arg1);
extern "C" igResult igIGBFile_CloseAfterWrite(igIGBFileView *arg1);
extern "C" igResult igIGBFile_FreeReadBuffers(igIGBFileView *o);
extern "C" igResult igIGBFile_AddInfoListEntry(void *arg1);
extern "C" int igIGBFile_WriteFile(igIGBFileView *arg0, const char *fileName);
extern "C" igResult igIGBFile_BeginRead(igIGBFileView *arg1, const char *fileName);
/* The 48-byte .igb header: the table sizes and counts, the magic cookie, then the version word whose
 * top bits carry the file's flags. */
struct IgbFileHeader {
    int entryBufferSize; int entryCount; int metaObjectBufferSize; int metaObjectCount; int objectBufferSize; int objectCount;
    int memoryRefBufferSize; int memoryRefCount; int metaFieldBufferSize; int metaFieldCount; int magicCookie; int magicVersion;
};
extern "C" igResult igIGBFile_ReadHeader(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadMetaObjectBuffer(igIGBFileView *arg1);
extern "C" igResult igIGBFile_SetupBasePath(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadNextChunk(igIGBFileView *arg1);
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
extern "C" igResult igIGBFile_ReadObjectIndex(igIGBFileView *self);
extern "C" igResult igIGBFile_ReadFinished(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadObjectSectionOld(igIGBFileView *file);
extern "C" void igIGBFile_SetCurrentPosition(igIGBFileView *self, int at);
extern "C" igResult igIGBFile_FreeBasePath(igIGBFileView *arg1);
/* The registered meta-field descriptors igMetaField_GetMetaFieldList returns; each entry's getMeta is its meta object. */
static inline igObjectDispatchView *registeredMetaField(__internalObjectList *fields, int index) {
    return ((igObjectDispatchView **)fields->_data)[index];
}
extern "C" igResult igIGBFile_ReadMetaFieldList(igIGBFileView *self);
extern "C" void Gap__Core__igIGBFile__resetFields(igIGBFileView *arg0);
/* An .igb table section header: its byte size, a version word and the entry count. */
struct IgbSectionHeader { int size; int pad; int count; };
extern "C" igResult igIGBFile_ReadAlignmentTable(igIGBFileView *self);
extern "C" igResult igIGBFile_ReadObjects(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadMemoryRefs(igIGBFileView *arg1);
extern "C" void igIGBFile_CleanUpReadState(igIGBFileView *a);
extern "C" void Gap__Core__igIGBFile__destructFields(igIGBFileView *arg0);
extern "C" igResult igIGBFile_ReadInfoList(igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadExternalDirectories(igIGBFileView *self);
struct NameHeader { int size; int count; };
extern "C" igResult igIGBFile_ReadMemoryPoolNames(igIGBFileView *self);
extern "C" igResult igIGBFile_MakeConcrete(igIGBFileView *arg1);
extern "C" igResult igIGBFile_PostProcessEntries(igIGBFileView *arg1);
/* ReadFile(path): the Alchemy .igb loader driver. Logs "readFile(%s)", notes the clock, then runs
 * the section readers in file order (header, then the version-dependent tables, then the object
 * sections). A reader that fails sends the loader to its error path igIGBFile_AbortRead. After the last
 * reader the load time is reported once through the assert/log hook; an old-format file that still
 * has external references is reported once through the same hook, which prints the file's name.
 * Each reader result is an unnamed temporary with its own stack word. */
extern "C" int igIGBFile_ReadFile(igIGBFileView *self, const char *path);
extern "C" void igIGBFile_ReadFilePostProcess(int *arg0, igIGBFileView *arg1);
extern "C" igResult igIGBFile_ReadFilePostProcessAll(igIGBFileView *self);
extern "C" int igIGBFile_WriteMemoryRefs(igIGBFileView *o);
extern "C" igResult igIGBFile_GetSectionBuffer(igIGBFileView *arg1, int arg2);
extern "C" void igIGBFile_ReadMemoryEntries(int *arg0, igIGBFileView *arg1);
extern "C" void igIntArrayMetaField_SwapBytes(igIntArrayMetaField *self, int passThrough, int perElement);
extern "C" int g_igIntMetaField_vtable[4];
extern "C" void *igIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" void *igIntMetaField_Init(igMetaField *self);
extern "C" int g_ObjectPointerList_vtable[4];
extern "C" void *ObjectPointerList_Construct(__internalNonRefCountedObjectList *self, int extra1);
extern "C" __internalNonRefCountedObjectList *ObjectPointerList_Init(__internalNonRefCountedObjectList *list);
extern "C" __internalNonRefCountedObjectList *ObjectPointerList_CopyConstruct(__internalNonRefCountedObjectList *self, __internalNonRefCountedObjectList *source);
extern "C" void ObjectPointerList_Destruct(__internalNonRefCountedObjectList *self);
extern "C" void ObjectPointerList_EnsureIndex(__internalNonRefCountedObjectList *list, int index);
extern "C" void *ObjectPointerList_FindByStringField(__internalNonRefCountedObjectList *list,igMetaField *selector,const char *name);
extern "C" void ObjectPointerList_ClearUnused(__internalNonRefCountedObjectList *list);
extern "C" void ObjectPointerList_Insert(__internalNonRefCountedObjectList *list,int index,int value);
extern "C" void ObjectPointerList_SetCount(__internalNonRefCountedObjectList *list, int count);
extern "C" int ObjectPointerList_EraseAt(__internalNonRefCountedObjectList *list,int index);
extern "C" int ObjectPointerList_Append(__internalNonRefCountedObjectList *list,int value);
extern "C" void ObjectPointerList_SetAt(__internalNonRefCountedObjectList *list, int index, int value);
extern "C" int g_InternalObjectList_vtable[4];
extern "C" void *InternalObjectList_Construct(__internalObjectList *list, int extra1);
extern "C" void *InternalObjectList_Init(__internalObjectList *list);
extern "C" void *InternalObjectList_CopyConstruct(__internalObjectList *list, __internalObjectList *source);
extern "C" void InternalObjectList_Destruct(__internalObjectList *list);
extern "C" void InternalObjectList_InsertRetained(__internalObjectList *list, int index, igObject *value);
extern "C" void InternalObjectList_SetCount(__internalObjectList *list,int count);
extern "C" int MetaRefList_AppendRetained(__internalObjectList *list, igObject *value);
extern "C" void InternalObjectList_SetAtRetained(__internalObjectList *list, int index, igObject *value);
extern "C" void StringPool_DestroyChunks(StringPool *pool);
extern "C" void * StringPool_Allocate(int arg0);
extern "C" void igLocationTable_Clear(igLocationTableView *table);
extern "C" int igLocationTable_GetCount(igLocationTable *self);
extern "C" void igLocationTable_GetLocationByIndex(int *arg0, igLocationTableView *arg1, int arg2, int *arg3, char *arg4, int arg5, int *arg6, char *arg7, int arg8, int *arg9);
extern "C" int igLocationTable_FindLocationIndex(igLocationTableView *o, int key);
extern "C" void igLocationTable_GetLocation(int *arg0, igLocationTableView *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0);
extern "C" void igLocationTable_AddLocationIfMissing(igLocationTableView *o, int a1, char *a2, int a3, char *a4, int a5);
extern "C" unsigned int igLocationTable_Hash(igLocationTable *self, unsigned int key);
extern "C" int igLocationTable_InsertHash(igLocationTableView *self, int address, int index);
/* The pointer difference is divided by 20 (the division is kept) and the capacity test is spelled
 * `arg1 <= cap`. */

extern "C" int DAT_004c2148;
extern "C" void igLocationTable_Rehash(igLocationTableView *arg0, int arg1);
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
extern "C" igMediaView *igMediaFile_FindDeviceForPath(int arg0);
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
extern "C" void igMediaFile_Close(igMediaFileView *arg0);
extern "C" char DAT_004f9c48[];
extern "C" char DAT_004f9c58[];
extern "C" char DAT_004f9c68[];
extern "C" char DAT_004f9c78[];
extern "C" char DAT_004f9c88[];
extern "C" int DAT_004f9c60[4];
extern "C" int DAT_004f9c70[4];
extern "C" int DAT_004f9c80[4];
extern "C" int DAT_004f9c90[4];
extern "C" void igMediaFile_CloseFile(igMediaFileView *self);
extern "C" void igMediaFile_SetFileSize(igMediaFileView *arg0, int arg1);
extern "C" int igMediaFile_Read(igMediaFileView *arg0, int arg1, int arg2, int arg3);
extern "C" int igMediaFile_Write(igMediaFileView *arg0, int arg1, int arg2, int arg3);
extern "C" int igMediaFile_Flush(igMediaFileView *arg0);
extern "C" int igMediaFile_Printf(igMediaFileView *self, int fmt, ...);
extern "C" int igMediaFile_GetChar(igMediaFileView *arg0);
extern "C" int igMediaFile_PutChar(igMediaFileView *arg0, unsigned char arg1);
extern "C" char *igMediaFile_GetString(igMediaFileView *arg0, char *arg1, int arg2);
extern "C" int igMediaFile_PutString(igMediaFileView *arg0, int arg1);
extern "C" int igMediaFile_Seek(igMediaFileView *arg0, int arg1, int arg2);
extern "C" int igMediaFile_Tell(igMediaFileView *p);
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
    virtual void d35();
    virtual void vfunc_38(igPointerList *regions);                                       /* +152 */
    virtual void CollectProgramRegions(igPointerList *regions);                          /* +156 */
    virtual void CollectHeapRegions(igPointerList *regions);                             /* +160 */
    virtual void vfunc_41(igPointerList *regions);                                       /* +164 */
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
/* The allocator the memory services use; SystemAllocator_Activate installs g_systemAllocator here when it is empty. */
extern "C" SystemAllocator *g_activeSystemAllocator[4];
extern "C" void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateFromPool(int, unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateBufferDirect(unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateAlignedWithAllocator(unsigned int size, unsigned short alignment, igMemoryPoolView *pool);
extern "C" void Memory_FreeBufferWithAllocator(void *block, igMemoryPoolView *pool);
extern "C" igMemoryPoolView *Memory_FindBufferOwner(void *buffer);
extern "C" int Memory_Reallocate(void *block, igMemoryPoolView *pool);
extern "C" int igMemoryDictionary_GetCapacity(igMemoryDictionary *self);
extern "C" void igMemoryDictionary_SetCapacity(igMemoryDictionary *self, int capacity);
/* One slot of igMemoryDictionary's open-addressed table: a key, and its value or -1 for a never-used
 * slot, -2 for a removed one. */
struct MemoryDictionaryEntry { int key; int value; };
/* igMemoryDictionary's entry list (an igUnsignedIntListNoClean); its count is in words, two per entry. */
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
    igTDataList<MemoryDictionaryEntry> *_memoryEntries;
    int _cachedIndex;
};
extern "C" void igMemoryDictionary_InitEntries(igMemoryDictionaryView *self);
extern "C" void igMemoryDictionary_Clear(igMemoryDictionaryView *self);
extern "C" int igMemoryDictionary_IsEnabled(igMemoryDictionary *self);
extern "C" int DAT_004c2150[4];
extern "C" void igMemoryDictionary_ResetEntries(igMemoryDictionaryView *self);
extern "C" int igMemoryDictionary_GetCount(igMemoryDictionary *self);
extern "C" void igMemoryDictionary_GetValue(igResult *result, igMemoryDictionaryView *self, int key, int *value);
extern "C" igResult igMemoryDictionary_Insert(igMemoryDictionaryView *self, int key, int value);
extern "C" igResult igMemoryDictionary_Remove(igMemoryDictionaryView *self, int key);
extern "C" unsigned int igMemoryDictionary_HashKey(igMemoryDictionary *self, unsigned int key);
extern "C" char DAT_004c2158[];
extern "C" int igMemoryDictionary_Resize(igResult *result, igMemoryDictionaryView *self, int capacity);
extern "C" void igMemoryDirEntry_SetMemType(igMemoryDirEntry *arg0, igObjectDispatchView *arg1);
extern "C" void igMemoryDirEntry_AllocateMemory(igMemoryDirEntry *self, igIGBFile *file);
extern "C" void igMemoryDirEntry_WriteMemory(igMemoryDirEntry *arg0, igIGBFile *arg1);
extern "C" void igMemoryDirEntry_AccumulateFileSize(igMemoryDirEntry *self, igIGBFile *file);
/* Stores `object` at `index`, retaining it and releasing the entry it replaces; the store itself is
 * dropped outside the list. */
/* matching construct: hand search — the list is the last parameter, evaluated after the stored object */
static inline void objectListSetRetained(int index, igObject *object, igObjectList *list) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igObject *old = ((igObject **)list->_data)[index];
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((igObject **)list->_data)[index] = object;
    }
}
extern "C" igMemoryDirEntry *igMemoryDirEntry_GetSharedEntry(igMemoryDirEntry *self, igIGBFile *file);
extern "C" void igMemoryDirEntry_ReadMemory(igMemoryDirEntry *arg0, igIGBFile *arg1);
class igMemoryDirEntryView : public igDirEntryView { public:
    int _memSize; int _memTypeSize; int _memType; int _memTypeIndex; int _alignmentTypeIndex; int _memoryPoolHandle;
    unsigned char _refCounted;
};
extern "C" void igMemoryDirEntry_ResolveRefOld(igMemoryDirEntryView *self, igIGBFileView *file);
extern "C" void igMemoryDirEntry_ResolveMemory(igMemoryDirEntryView *self, igIGBFileView *r);
extern "C" void igMemoryDirEntry_SetMemoryPoolHandle(igMemoryDirEntry *self, int memoryPoolHandle);
extern "C" int igMemoryDirEntry_GetMemoryPoolHandle(igMemoryDirEntry *self);
extern "C" int *DAT_00586f48[4];
/* igMemoryFile: an igFile reading a registered memory buffer (_buffer, _iBufferSize bytes) instead of
 * a device; the file name is looked up in the igMemoryFileEntry list on open. */
class igMemoryFileView : public igFileView { public:
    unsigned char _bIsOpen;
    char *_buffer;
    int _iBufferSize;
    int _iSeekPosition;
};
extern "C" void igMemoryFile_Open(int *arg0, igMemoryFileView *self, unsigned int mode);
extern "C" igFileView *igMemoryFile_OpenFile(igFileView *arg0, const char *fileName, int arg2);
extern "C" void igMemoryFile_CloseFile(igMemoryFileView *self);
extern "C" int igMemoryFile_Read(igMemoryFileView *self, void *buffer, int size, int count);
extern "C" char igMemoryFile_GetChar(igMemoryFileView *self);
extern "C" int igMemoryFile_Tell(igMemoryFileView *self);
extern "C" int DAT_0052f620[4];
extern "C" int g_beModelCtrlInfo_metaObject[4];
extern "C" unsigned char GPR_00554994;
extern "C" igResult Memory_LookupAllocation(int arg1, int *arg2);
/* The struct result is returned through the hidden pointer (a0 is the caller's return slot, this
 * is in a1), so the function returns the struct by value. */
extern "C" char text_memoryDictionarySize[];
extern "C" igMemoryDictionaryView *DAT_00586f68[4];
extern "C" igResult Memory_RegisterAllocation(int arg1, igMemoryPoolView *arg2);
extern "C" igResult Memory_UnregisterAllocation(int arg1, igMemoryPoolView *pool);
extern "C" char DAT_00580000[];
/* Allocator registry index lookup and encoded-index publication. An allocator is identified in
 * saved data by "registry index << 1 | which-registry": the primary list gives an even code, the
 * secondary list an odd one. */
/* Growable pointer list of allocators: data, signed count, capacity (same layout as igMemoryPoolInfoList). */
struct AllocatorRegistry {igMemoryPoolView **data;int count;int capacity;};
extern "C" AllocatorRegistry *g_primaryAllocatorList[4];
extern "C" AllocatorRegistry *g_secondaryAllocatorList[4];
extern "C" int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *list,igMemoryPoolView *allocator);
extern "C" int igAllocator_EncodeIndex(igMemoryPoolView *allocator);
extern "C" char DAT_004f9d60[];
extern "C" void igMemoryPool_PrintStatistics(igMemoryPool *arg0, char *arg1);
extern "C" char DAT_004f9fe0[];
extern "C" char * DAT_00586f70[4];
extern "C" int DAT_00586f78[4];
extern "C" int DAT_00586f90[4];
extern "C" int DAT_00586f98[4];
extern "C" int DAT_00586fb0[4];
extern "C" int DAT_00586fb8[4];
extern "C" void *FUN_002f0c80(igMemoryPoolView *self, unsigned int size);
extern "C" void igMemoryPool_SetEventTracker(int dummy0, igObject *arg1);
extern "C" int DAT_004c2160[4];
extern "C" int igMemoryPool_ReallocateTracked(igMemoryPoolView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
extern "C" void igMemoryPool_GangAllocTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10);
extern "C" void igMemoryPool_GangAllocAlignedTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18);
extern "C" void Memory_InitializeAllocatorRegistries(igObject *rootAllocator);
extern "C" void igMemoryPool_UpdateStatistics(igMemoryPool *pool, long long arg1, long long arg2, int arg3);
extern "C" void igMemoryPool_ResetStatistics(igMemoryPool *arg0);
extern "C" void igMemoryPool_UpdateLocalStatistics(igMemoryPool *arg0, int arg1, int arg2, int arg3);
extern "C" long long DAT_00586f80[4];
extern "C" long long DAT_00586f88[4];
extern "C" long long DAT_00586fa0[4];
extern "C" long long DAT_00586fa8[4];
extern "C" long long DAT_00586fc0[4];
extern "C" long long DAT_00586fc8[4];
extern "C" void *DAT_00587000[4];
extern "C" char *g_memoryContextNames[46];
extern "C" char text_InhibitEventTracker[];
extern "C" char text_UseEventTracker[];
struct ContextRecord {
    void *allocator;       /* retained by the slot setter */
    char name[128];        /* 127 characters copied in plus an explicit terminator */
    igMemoryPoolInfo *descriptor;
    unsigned storageFlags, flags;
};
/* igMemoryPoolContextInfo (reflected layout in dw4/reflected.h) with the virtuals its callers use. */
class igMemoryPoolContextInfoView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual igResult vfunc_25(igRegistry *ini, char *section);
    virtual igResult vfunc_26(igRegistry *ini, int index);
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
    virtual int vfunc_30(int handleName);                     /* slot 28: record index for a pool handle name */
    virtual int indexOfAllocator(void *pool);                 /* slot 29: record index holding `pool`, -1 if none */
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual igResult vfunc_35(int, int);
    virtual igResult vfunc_36(int index, igMemoryPoolInfo *info); /* slot 34: fills `info` from record `index` */
    virtual igResult vfunc_37(int index, igMemoryPoolInfo *info, int build); /* slot 35: igMemoryPoolContextInfo_SetPoolInfo */
    virtual void setFlags(unsigned flags);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void vfunc_42();
    virtual void vfunc_43();
    virtual int vfunc_44();
    virtual void InitializeRecordNames();
    virtual void d44();
    virtual int vfunc_47();
    virtual igResult vfunc_48(int config, char *name);         /* slot 46: igMemoryPoolContextInfo_CreateDefaultContextInfo */
    virtual int vfunc_49();
    virtual igResult vfunc_50();                                /* slot 48: FUN_002f5cc0 */
    virtual igResult BuildAllocator(int index, int flag);
    virtual igResult BuildAndAttachEventTracker(int index);
    virtual void RemoveAllocator(int index);
    virtual void vfunc_54();                                    /* slot 52: igMemoryPoolContextInfo_ConfigureEventTracking */
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
extern "C" char g_igMemoryPoolContextInfo_vtable[];
extern "C" MemoryContext *igMemoryPoolContextInfo_Construct(MemoryContext *self);
extern "C" void *igMemoryPoolContextInfo_Destruct(MemoryContext *self, long long deleteFlags);
extern "C" void igMemoryPoolContextInfo_Activate(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_SetEventClassName(MemoryContext *self, int arg1);
extern "C" int DAT_00587010[4];
extern "C" int igMemoryPoolContextInfo_GetAllocatorBySelector(MemoryContext *arg0, int arg1);
extern "C" void *igMemoryPoolContextInfo_GetMemoryPoolByName(MemoryContext *self, const char *name);
extern "C" void igMemoryPoolContextInfo_SetAllocator(MemoryContext *self, int index, igObject *value);
extern "C" int *igMemoryPoolContextInfo_GetPoolName(MemoryContext *arg0, void *pool);
extern "C" int text_kIGMemoryPoolHandle[4];
extern "C" int text_kIGMemoryPool[4];
extern "C" igResult igMemoryPoolContextInfo_ReadConfiguration(MemoryContext *self, int config, int section);
extern "C" igResult igMemoryPoolContextInfo_LoadFromRegistry(MemoryContext *self, int config, int index);
extern "C" igResult igMemoryPoolContextInfo_GetPoolInfos(MemoryContext *self, int file);
extern "C" igResult igMemoryPoolContextInfo_SetPoolInfos(MemoryContext *self, int file, int arg);
typedef void StringToken;
/* a token points at the interned text; its header precedes it */
extern "C" char text_kIGMemoryPoolHandle_s[];
extern "C" void igMemoryPoolContextInfo_FillMemoryPoolInfo(int *result, MemoryContext *context, int index, igMemoryPoolInfo *info);
extern "C" igResult igMemoryPoolContextInfo_SetPoolInfo(MemoryContext *self, int index, igMemoryPoolInfo *desc, int build);
extern "C" void igMemoryPoolContextInfo_DeactivatePools(MemoryContext *arg0);
extern "C" char *DAT_00586de8;
extern "C" int DAT_00586fd8[4];
extern "C" int DAT_00586fe0[4];
extern "C" int DAT_00586fe8[4];
extern "C" int DAT_00586ff0[4];
extern "C" void igMemoryPoolContextInfo_CreateDefaultPools(MemoryContext *self);
extern "C" int D_00587010[4];
extern "C" void igMemoryPoolContextInfo_InitializeRecordNames(MemoryContext *self);
extern "C" char text_bootstrapPoolPreSize[];
extern "C" char text_updatePoolStatistics[];
extern "C" char text_useAliasMemoryPoolRelease[];
extern "C" char text_arenaMemoryPoolOptionFlagsReleas[];
extern "C" char text_arenaMemoryPoolMessageLevelRelea[];
extern "C" char text_arenaMemoryPoolHeapIntegrityChec[];
extern "C" char text_inhibitArenaCountMessage[];
extern "C" char text_nonTrackedPoolPreSize[];
extern "C" igResult igMemoryPoolContextInfo_Initialize(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_RemoveAllAllocators(MemoryContext *arg0);
extern "C" char text_defaultPoolPreSize[];
extern "C" char text_systemPoolPreSize[];
extern "C" char text_scratchPoolSize[];
extern "C" char text_scratchPadPoolSize[];
extern "C" char text_Fixed[];
extern "C" char text_HighSpeed[];
extern "C" char text_OnDemand[];
extern "C" char text_driverPoolSize[];
extern "C" void igMemoryPoolContextInfo_CreateDefaultContextInfo(int *out, MemoryContext *self, int config, char *name);
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
extern "C" void igMemoryPoolContextInfo_ConfigureEventTracking(MemoryContext *self);
extern "C" char DAT_004fa930[];
extern "C" int DAT_004fa988[4];
extern "C" char DAT_004fa990[];
extern "C" char DAT_004fa9b0[];
extern "C" char DAT_004fa9d0[];
enum LeakKind { LeakKindFirst = 0, LeakKindCount = 32 };
extern "C" void igMemoryPoolContextInfo_ShutdownEventTrackers(MemoryContext *self);
extern "C" char text_s_igm[];
extern "C" void igMemoryPoolContextInfo_SaveEventTrackers(MemoryContext *arg0);
extern "C" igResult igMemoryPoolContextInfo_UpdateAllocatorsOfKind(MemoryContext *self, unsigned int kind, int free);
extern "C" void igMemoryPoolContextInfo_SetEventTag(MemoryContext *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_GetEventTag(MemoryContext *self, int arg1, int *out, int n);
extern "C" void igMemoryPoolContextInfo_SetEventTags(MemoryContext *self, int *paths, int n);
extern "C" void igMemoryPoolContextInfo_GetEventClassName(MemoryContext *slots, int arg1, int *out, int n);
extern "C" void igMemoryPoolContextInfo_SetEventClassNames(MemoryContext *arg0, int *arg1, int arg2);
extern "C" void igMemoryPoolContextInfo_SendMarker(MemoryContext *arg0, int arg1, int arg2, int arg3);
extern "C" char text_Pool_statistics[];
extern "C" char DAT_004fab20[];
extern "C" char DAT_004fab30[];
extern "C" void igMemoryPoolContextInfo_PrintPoolStatistics(MemoryContext *arg0, char *arg1, igMemoryPoolView *arg2);
extern "C" char DAT_004f95c8[];
extern "C" int DAT_004fab70[4];
extern "C" int text_Combined_pool_statistics[4];
extern "C" void igMemoryPoolContextInfo_PrintStatistics(MemoryContext *arg0, int *arg1);
extern "C" int DAT_00586ffc[4];
extern "C" igResult igMemoryPoolContextInfo_PushContext(void *arg1);
extern "C" igObject *igMemoryPoolContextInfo_PopContext(void);
extern "C" void igMemoryPoolContextInfo_RemoveMemoryPoolInfo(igMemoryPoolContextInfo *info, igMemoryPoolInfo *poolInfo);
extern "C" int emptyString[4];
extern "C" igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByName(igMemoryPoolContextInfo *arg0, int arg1);
extern "C" char text_Handle[];
extern "C" igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByHandle(igMemoryPoolContextInfo *arg0, char *arg1);
extern "C" char *DAT_004c2228[4];
extern "C" igResult igMemoryPoolContextInfo_ReadFromRegistry(igMemoryPoolContextInfoView *self, igRegistry *ini, char *section);
extern "C" char DAT_004fabc0[];
extern "C" void igMemoryPoolContextInfo_Print(igMemoryPoolContextInfoView *self);
extern "C" igResult igMemoryPoolInfo_LoadFromRegistry(igInfoView *self, igRegistry *ini, char *section);
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
extern "C" void igMemoryPoolInfo_TrimCapacity(igMemoryPoolInfo *arg0);
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
 * for the storage is the object system's bootstrap pool. */
extern "C" AllocatorRegistry *igMemoryPoolInfoList_Init(AllocatorRegistry *list);
extern "C" AllocatorRegistry *igMemoryPoolInfoList_Release(AllocatorRegistry *list,int deleteFlag);
extern "C" void igMemoryPoolInfoList_Append(AllocatorRegistry *list,igMemoryPoolView *entry);
extern "C" void igMemoryRefArrayMetaField_SwapBytes(igMemoryRefArrayMetaField *self, int buffer, int count);
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
 * field's _offset. */
extern "C" void igMetaField_AllocateArray(int *outStatus,igMemoryRefMetaField *field,void *object,int count,igMemoryPoolView *allocator);
extern "C" void igMemoryRefMetaField_SetAlignmentType(igMemoryRefMetaField *self, char *name);
extern "C" int igMemoryRefMetaField_Write(igMemoryRefMetaField *f, int off, int a2);
extern "C" int igMemoryRefMetaField_IsAlikeExactly(igMemoryRefMetaField *arg0, int arg1, int arg2);
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
extern "C" igResult igMetaEnum_GetValueByName(igMetaEnum *meta, const char *name, int *value);
/* The parameter is const so the list pointer is reloaded per iteration, the loop is tested at the
 * bottom via goto, and the locals are declared in the order a4, n, i. */
extern "C" void igMetaEnum_GetNameByValue(int *arg0, const igMetaEnum *arg1, int arg2);
extern "C" int igMetaEnum_GetNameCount(igMetaEnum *self);
typedef struct MetaEnumView { char pad[4]; int _refCount; char *name; igTDataList<char *> *names; igTDataList<int> *values; } MetaEnumView;
extern "C" MetaEnumView *igMetaEnum_Create(char *name, char **names, int *values, int count);
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
extern "C" void igMetaField_EnsureDefaultStorage(igMetaField *field);
extern "C" void igMetaField_SetDefault(igMetaField *self, int defaultValue);
extern "C" void igMetaField_SetFieldName(igMetaField *self, void **newName);
extern "C" void igMetaField_Reset(igMetaField *field,void *object);
extern "C" void igMetaField_SetToDefault(igMetaField *arg0, int arg1);
extern "C" void igMetaField_CopyDefaultToValue(igMetaField *arg0, int arg1);
extern "C" short igMetaField_GetTypeIndex(igMetaFieldView *arg0);
extern "C" void igMetaField_FinalizeDescriptor(igMetaField *field);
extern "C" int igMetaField_WritePersistentValue(igMetaField *field,void *object,void *output,void *context,unsigned char swap);
extern "C" int igMetaField_ReadFieldMem(igMetaFieldView *field, char *object, char *data, igIGBFile *file, unsigned char endianSwap);
extern "C" unsigned short igMetaField_ReadRawFieldMem(igMetaFieldView *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int igMetaField_GetRawFieldMemSize(igMetaField *arg0);
extern "C" void igMetaField_CopyByTechnique(igMetaFieldView *arg0, int arg1, int arg2, int arg3);
extern "C" void igMetaField_ShallowCopyValue(igMetaField *arg0, int arg1, int arg2);
extern "C" void igMetaField_ResetValue(igMetaField *field, void *object);
extern "C" igStringRef igMetaField_ArrayToString(igMetaFieldView *arg1, int arg2, int arg3, int arg4);
extern "C" int igMetaField_ArrayFromString(igMetaFieldView *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int igMetaField_FromString(igMetaFieldView *field, int object, int text, int directory);
extern "C" int igMetaField_Write(igMetaField *arg0);
extern "C" int igMetaField_IsAlikeExactlyValue(igMetaField *arg0, unsigned char *arg1, unsigned char *arg2);
extern "C" int igMetaField_IsAlikeDeepValue(igMetaFieldView *self, const void *left, const void *right);
extern "C" int igMetaField_IsAlikeShallowValue(igMetaFieldView *self, const void *left, const void *right);
extern "C" igStringRef igMetaField_ToString(igMetaFieldView *self, char *object, int directory);
extern "C" void igMetaField_SetValue(igMetaField *arg0, int arg1, int arg2);
extern "C" void igMetaField_SetValueFromField(igMetaFieldView *self, void *object, igMetaFieldView *field, char *source);
extern "C" void igMetaField_SwapBytes(igMetaField *arg0, unsigned char *arg1, int arg2);
extern "C" void igMetaField_SwapValue(igMetaFieldView *self, char *object);
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
extern "C" int igMetaFieldInfo_FindObjectReference(igMetaFieldInfoView *arg0, int arg1, void *arg2);
extern "C" igMetaField *igMetaField_FindByName(int arg0, char *arg1);
struct Instance : public igObject { };

typedef igMetaField *(*FieldFactory)(void *);
struct StaticInitCallbacks { void (**functions)(); int count; };
/* A memory pool's virtuals: slot 31 is igMemoryPool::vfunc_33, IsActive() (returns _isActive);
 * slot 32 is vfunc_34, EnableAllocationLock(enable) (igArenaMemoryPool and igAliasMemoryPool create
 * or drop the pool's _allocationLock semaphore); slot 52 allocates. The callers take IsActive's
 * result at full width: declared unsigned char or bool, the `== 0` test in igMemoryPoolContextInfo_Activate gains the
 * `andi 0xff` of a byte-returning callee (156 bytes against retail's 152). */
extern "C" int g_igMetaObject_vtable[4];
extern "C" igMetaField *g_fieldNameMember[4];
extern "C" int igMetaObject_CreateInstanceDefaultRef(Instance **out, int meta);
extern "C" igSmartPointer<igObject> igMetaObject_CreateInstanceRef(int meta, int pool);
extern "C" void *igMetaObject_Construct(igMetaObject *meta, int extra1);
extern "C" igMetaObject *igMetaObject_Init(igMetaObject *meta);
extern "C" void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source);
extern "C" void igMetaObject_ReleaseLists(igMetaObject *meta);
extern "C" int igMetaObject_CreateInstance(igMetaObject *arg0, igMemoryPoolView *arg1);
extern "C" int igMetaObject_CreateInstanceWithPool(igMetaObject *arg0, igMemoryPoolView *arg1);
extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent);
extern "C" int igMetaObject_CountInstances(igMetaObject *arg0, int arg1);
extern "C" void igMetaObject_SetName(igMetaObject *meta, int name);
extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);
extern "C" void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field);
extern "C" int igMetaObject_GetFieldAt(igMetaObject *self, int index);
extern "C" void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name);
extern "C" void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count);
extern "C" void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start);
extern "C" void igMetaObject_FinalizeFieldLayout(igMetaObject *arg0);
extern "C" int igMetaObject_IsOfType(igMetaObject *arg0, igMetaObject *arg1);
extern "C" int igMetaObject_GetChildCount(igMetaObject *arg0);
extern "C" int igMetaObject_GetChildAt(igMetaObject *self, int index);
extern "C" void *igMetaObject_GetTreeNode(igMetaObject *arg0, int arg1);
extern "C" int igMetaObject_CountTree(igMetaObject *arg0);
extern "C" int igMetaObject_GetFieldCount(igMetaObject *self);
extern "C" void igMetaObject_AddField(igMetaObject *arg0, void *arg1);
extern "C" void igMetaObject_AddFieldAndFinalize(igMetaObject *arg0, void *arg1);
extern "C" int igMetaObject_AddToMetaObjectList(igTDataList<igMetaObject *> *list, igMetaObject *object);
extern "C" void igMetaObject_AssignTypeId(igMetaObject *meta);
extern "C" void igMetaObject_CopyVTable(int *out, igMetaObject *s, igMemoryPoolView *a);
extern "C" void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)());
extern "C" void igNamedObject_SetName(igNamedObject *arg0, int arg1);
/* Name-or-default is a ?: expression, not an if with an empty then-arm. */
extern "C" void igNamedObjectInfo_FindObjectReference(igNamedObjectInfo *self, int file, igNamedObject *object);
extern "C" igNamedObject *igNamedObjectInfo_GetFieldValueByName(igNamedObjectInfo *self, const char *name);
extern "C" int igObjectList_FindByIntField(igTDataList<int> *list, igMetaField *field, int value);
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
extern "C" igObject *igObject_InitHeader(igObject *p);
extern "C" igObject *igObject_CopyConstructHeader(igObject *arg0, igObject *arg1);
/* Stamps the igObject vtable, runs igObject_InitHeader, then fills the header's allocator byte
 * (+7): with the object system active it is the result of the owning allocator's virtual slot 364
 * (the owner-derived encoded allocator index); otherwise zero. */
extern "C" igObject *igObject_ConstructHeader(igObject *self);
extern "C" void igObject_Construct(igObjectDispatchView *arg0, char *arg1);
extern "C" void igObject_ConstructPooled(igObject *arg0, char *arg1);
/* Storage for a new object. Reserves size + prefix_size bytes from the given allocator, falls back
 * to the default allocator (looked up by selector) when none is passed, and to the global heap
 * when there is no allocator at all. It returns the address prefix_size bytes into the block, so a
 * header can precede the object. The allocator method called is vtable offset 216 (vfunc_54), the
 * allocate-bytes slot. */
extern "C" int igObject_GetSerializedSize(igObjectDispatchView *arg0);
extern "C" int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap);
/* An object record in an .igb object section: its meta-object index and byte size, then (old format)
 * the count of persistent fields written. */
struct FieldRecordHead { int kind; int size; int fieldCount; };
extern "C" int igObject_ReadFields(igObjectDispatchView *object, FieldRecordHead *head, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap);
extern "C" int igObject_ReadPersistentFields(igObjectDispatchView *object, FieldRecordHead *head, igDirectoryView *dir, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap);
extern "C" int igObject_IsAlikeDeep(igObjectDispatchView *a, igObjectDispatchView *b);
extern "C" int igObject_IsAlikeShallow(igObjectDispatchView *arg0, igObjectDispatchView *arg1);
typedef int (*Visitor)(void *,void *,void *);
extern "C" void igObject_VisitFields(igObjectDispatchView *object,Visitor callback,void *context);
/* Class-membership test: asks `object` for its metaobject and walks the metaobject's `_parent`
 * chain looking for `kind`. Returns 1 when `kind` is the object's own class or one of its
 * ancestors, else 0. */
extern "C" int igObject_IsKindOf(void *object, igMetaObject *kind);
extern "C" igMemoryPoolView *igObject_GetAllocator(int a0);
extern "C" igSmartPointer<igObject> igObject_Clone(igObjectDispatchView *arg1, int arg2);
extern "C" void igObjectDirEntry_ReleaseDefaults(igObjectDirEntry *self);
/* An igObjectList of igObjectDirEntry, or of such lists (an igIGBFile's _entryPool, one per type meta). */
static inline igObjectDirEntry *objectDirEntryAt(const igObjectList *list, int index) { return ((igObjectDirEntry *const *)list->_data)[index]; }
extern "C" igObjectDirEntry *igObjectDirEntry_GetSharedEntry(igObjectDirEntry *self, igIGBFile *file);
extern "C" void igObjectDirEntry_RetainSharedRef(igObjectDirEntry *self, igObject *object);
extern "C" void igObjectDirEntry_ReleaseSharedRef(igObjectDirEntry *self, igObject *object);
extern "C" void igObjectDirEntry_SetTypeMeta(igObjectDirEntry *arg0, igMetaObject *arg1);
extern "C" void igObjectDirEntry_SetRef(igObjectDirEntry *self, igObject *object);
extern "C" void igObjectDirEntry_WriteObject(igObjectDirEntry *self, igIGBFileView *file);
extern "C" void igObjectDirEntry_RegisterRef(igObjectDirEntry *arg0, int arg1);
/* igObjectDirEntry: a directory entry holding one object (_ref) of meta-object _typeMeta; the IGB
 * file stores the type as _typeMetaIndex into its meta-object list, or by _typeMetaName. */
class igObjectDirEntryView : public igDirEntryView { public:
    igMetaObject *_typeMeta;
    int _typeMetaName;
    int _majorVersion;
    int _minorVersion;
    int _memoryPoolHandle;
    int _typeMetaIndex;
};
extern "C" void igObjectDirEntry_ComputeWriteSize(igObjectDirEntryView *arg0, igIGBFile *arg1);
extern "C" void igObjectDirEntry_PostProcess(igObjectDirEntryView *self);
extern "C" void igObjectDirEntry_ResolveRefOld(igObjectDirEntry *self, igIGBFileView *file);
extern "C" void igObjectDirEntry_ResolveRef(igObjectDirEntry *self, igIGBFileView *file);
extern "C" void igObjectDirEntry_CreateObject(igObjectDirEntryView *self, igIGBFileView *file);
extern "C" void igObjectDirEntry_RetainRef(igObjectDirEntry *self, igObject *object);
extern "C" void igObjectDirEntry_ReleaseRef(igObjectDirEntry *self, igObject *object);
extern "C" void igObjectDirEntry_SetMemoryPoolHandle(igObjectDirEntry *self, int memoryPoolHandle);
extern "C" int igObjectDirEntry_GetMemoryPoolHandle(igObjectDirEntry *self);
extern "C" void ObjectList_FillRetained(igTDataList<igObject *> *arg0, igObject *arg1);
extern "C" void ObjectList_ClearRetainedPreserveCount(igTDataList<igObject *> *arg0, int extra1);
extern "C" void ObjectList_AppendRetainedList(igTDataList<igObject *> *self, igTDataList<igObject *> *source);
extern "C" void ObjectList_ResizeRetained(igTDataList<igObject *> *arg0, int arg1);
extern "C" igResult ObjectList_RemoveFirstRetained(igTDataList<igObject *> *self, igObject *value, int start);
extern "C" int ObjectList_RemoveAllRetained(igTDataList<igObject *> *list, igObject *object, int start);
extern "C" int ObjectList_AppendUniqueRetained(igTDataList<igObject *> *list, igObject *object);
extern "C" int igProperty_FindByName(igObjectList *arg0, igMetaField *arg1, int arg2);
extern "C" void igObjectList_SortByField(igTDataList<igObject *> *self, igMetaField *field);
extern "C" void igObjectRefArrayMetaField_SwapBytes(igObjectRefArrayMetaField *self, int passThrough, int perElement);
extern "C" void igObjectRefArrayMetaField_SetElement(igObjectRefArrayMetaField *arg0, int arg1, int arg2, igObject *arg3);
extern "C" void igObjectRefArrayMetaField_ConstructValue(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void igObjectRefArrayMetaField_DestructValue(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void igObjectRefArrayMetaField_ClearValue(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void igObjectRefArrayMetaField_CopyDefaultToValue(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" void igObjectRefArrayMetaField_DeepCopy(igObjectRefArrayMetaField *s, char *a1, char *a2);
extern "C" void igObjectRefArrayMetaField_ResetValue(igObjectRefArrayMetaField *arg0, int arg1);
extern "C" int igObjectRefArrayMetaField_WriteRawFieldMem(igObjectRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" void igObjectRefArrayMetaField_ReleaseElements(igObjectRefArrayMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int igObjectRefArrayMetaField_IsAlikeExactly(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int igObjectRefArrayMetaField_IsAlikeDeep(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int igObjectRefArrayMetaField_IsAlikeShallow(igObjectRefArrayMetaField *arg0, int arg1, int arg2);
extern "C" int g_igObjectRefMetaField_vtable[4];
extern "C" void igObjectRefMetaField_Assign(igObjectRefMetaField *field,void *object,igObject *value);
extern "C" int igObjectRefMetaField_GetTypeSize(igObjectRefMetaField *);
extern "C" void igObjectRefMetaField_SetDefault(igObjectRefMetaField *arg0, igObject *arg1);
extern "C" int igObjectRefMetaField_ReadRawFieldMem(igObjectRefMetaField *self, igObject **valueSlot, int extra2, int extra3, int extra4);
extern "C" void igObjectRefMetaField_ConstructValue(igObjectRefMetaField *field,void *object);
extern "C" void igObjectRefMetaField_DestructValue(igObjectRefMetaField *field,void *object);
extern "C" void igObjectRefMetaField_ClearValue(igObjectRefMetaField *field,void *object);
extern "C" void igObjectRefMetaField_DeepCopy(igObjectRefMetaField *self, char *dst, char *src);
extern "C" void igObjectRefMetaField_ShallowCopy(igObjectRefMetaField *arg0, int arg1, int arg2);
extern "C" void igObjectRefMetaField_ResetValue(igObjectRefMetaField *self, int instance);
extern "C" void igObjectRefMetaField_Print(igObjectRefMetaField *self, char *object, int depth, const char *indent);
extern "C" void igObjectRefMetaField_ReleaseElements(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3);
extern "C" int igObjectRefMetaField_Compare(igObjectRefMetaField *arg0, int arg1, int arg2);
extern "C" int igObjectRefMetaField_IsAlikeExactly(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" int igObjectRefMetaField_IsAlikeDeep(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" int igObjectRefMetaField_IsAlikeShallow(igObjectRefMetaField *self, int objectA, int objectB);
extern "C" void *igObjectRefMetaField_Construct(igObjectRefMetaField *self, int extra1);
extern "C" void *igObjectRefMetaField_Init(igObjectRefMetaField *self);
extern "C" void *igObjectRefMetaField_CopyConstruct(igObjectRefMetaField *arg0, void *arg1);
extern "C" void igObjectStringMap_Add(igObjectStringMap *self, int name, void *object);
typedef igTDataList<igObject *> FieldList;
extern "C" int igObjectStringMap_GetIndexByName(igObjectStringMap *map, int name);
extern "C" void igObjectStringMap_Clear(igObjectStringMap *o);
extern "C" void igObjectStringMap_RemoveAt(igObjectStringMap *arg0, int arg1);
class igPsx2FileView;
extern "C" igPsx2FileView *DAT_005871b0[4];
extern "C" void igReport_SetOutputFile(igPsx2FileView *arg0);
extern "C" igPsx2FileView *DAT_005871b8[4];
extern "C" void igReport_SetErrorFile(igPsx2FileView *arg0);
extern "C" unsigned char GPR_00554998;
extern "C" unsigned char GPR_0055499c;
extern "C" unsigned char GPR_005549a4;
extern "C" unsigned char GPR_005549a8;
extern "C" void igPluginHelper_AddRepository(igPluginHelper *helper, int name, int location, int locationType);
extern "C" const char *DAT_004c22c8[];
extern "C" const char *DAT_004c22d0[];
extern "C" void igPluginHelper_AddRepositoryFromConfig(igPluginHelper *self, int name, const char *path);
extern "C" char PLUGINS[];
extern "C" bool igRegistry_GetKeyName(int registry, int section, int index, igStringObj **key);
/* igPluginHelper::_libraryLoader; slot 22 (vfunc_24) receives each loaded igLibrary in turn. */
class igLibraryLoaderView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual int vfunc_24(igLibrary **library);
};
extern "C" void Gap__Core__igPluginHelper__userDestruct(igPluginHelper *self);
struct Args { igResult (*fn)(int); igStandardQueueView *queue; };
extern "C" int igPluginHelper_ThreadLoop(Args *args);
extern "C" int igStandardQueue_StopServiceThreads(igStandardQueueView *queue);
extern "C" void igRawRefArrayMetaField_SwapBytes(igRawRefArrayMetaField *self, int item, int count);
extern "C" int igRawRefArrayMetaField_ReadRawFieldMem(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" int igRawRefArrayMetaField_WriteRawFieldMem(igRawRefArrayMetaField *self, int src, void *dst, int a3, int a4);
extern "C" int igRawRefArrayMetaField_GetSize(igRawRefArrayMetaField *self);
extern "C" int igRawRefMetaField_GetSize(igPluginRepositoryList *self);
extern "C" void igRawRefMetaField_Print(igRawRefMetaField *self, char *object, int unusedArg, const char *indent);
extern "C" int igRawRefMetaField_Write(igRawRefArrayMetaField *arg0, int arg1, int arg2);
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
extern "C" int igRefMetaField_ArrayToString(igStringRef *arg0, void *arg1, int *arg2, int arg3, int arg4, char *arg5, int arg6);
extern "C" int igRefMetaField_ArrayFromString(int self, int str, int *out, int n, igDirectory *list);
extern "C" int igRefMetaField_Compare(igRefMetaField *arg0, int arg1, int arg2);
extern "C" int g_igStringMetaField_vtable[4];
extern "C" int g_igUnsignedIntMetaField_vtable[4];
extern "C" void *igRefMetaField_Construct(igRefMetaField *self);
extern "C" void *igRefMetaField_Init(igRefMetaField *self);
extern "C" void *igStringMetaField_Construct(igStringMetaField *self, int extra1);
extern "C" void *igStringMetaField_Init(igStringMetaField *self);
extern "C" void *igUnsignedIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" void *igUnsignedIntMetaField_Init(igMetaField *self);
extern "C" char text_alchemy_ini[];
extern "C" bool igRegistry_Load(igRegistry *self, char *name, char *dir);
extern "C" int igRegistry_Merge(void *self, igRegistry *inc, int overwrite);
extern "C" char *DAT_004fb160[];
extern "C" int igRegistry_GetSectionIndex(igRegistry *self, char *name, int create);
extern "C" int igRegistry_GetValueStringObj(int arg0, int arg1, const char *arg2, igStringObj **arg3, const char *arg4, int arg5);
extern "C" char DAT_004fb190[];
extern "C" int igRegistry_GetValueStringList(void *self, int section, const char *key, igStringRefList *list, int create);
extern "C" char DAT_004d3d11[16];
extern "C" char DAT_004fb198[16];
extern "C" char text_0x_x[16];
extern "C" void igRegistry_Clear(igRegistry *self);
extern "C" char DAT_004fb1a8[];
extern "C" char text_abcdefghijklmnopqrstuvwxyzABCDEF_2[];
extern "C" char DAT_004fb200[];
extern "C" char text_showRegistryQueries[];
extern "C" void igRegistry_ParseFile(igRegistry *self, igFileView *file, int overwrite);
extern "C" bool igRegistry_ReadLine(void *unused, igFileView *s, char *buf, int *lines);
extern "C" igRegistryValue *igRegistry_FindValue(igRegistry *arg0, int arg1, const char *arg2, int arg3);
extern "C" char DAT_004fb280[];
extern "C" int DAT_005871c0;
extern "C" void igRegistry_ProcessInclude(igRegistry *self, igFileView *file, char *line, int lineNo, int overwrite);
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
extern "C" igSmartPointer<igObject> igResource_GetDirectory(void *directory, int name);
extern "C" void igResource_AddAlignment(igResource *self, int name, int value);
extern "C" igDirectory *igResource_GetImageDirectory(igResource *self);
extern "C" int g_resourceLoaderStackSize[4];
/* igResource (reflected.h) with its asynchronous-loading fields: the queue the loader thread
 * serves and the thread. */

extern "C" void igResource_StartAsyncLoading(igResourceView *self);
extern "C" void igResource_StopAsyncLoading(igResourceView *self);
extern "C" void igResource_ReleaseDefaults(igResource *self);
extern "C" void *igResource_GetOrLoadDirectory(igResource *arg0, int arg1);
extern "C" void *igResource_LoadDirectory(igResource *self, int path);
extern "C" igIGBFileView *igResource_ReadFileWithSearchPaths(igResource *self, igIGBFileView *file);
extern "C" void igResource_UnloadDirectory(igResource *self, int name);
extern "C" void igResource_ClearDirectories(igResource *self);
extern "C" void igResource_RemoveIGBFiles(igResource *self);
extern "C" void igDirectory_ConvertObjectsOfType(igDirectory *arg0, int arg1, int arg2);
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
extern "C" void igResource_FinishAsyncLoad(igResource *arg0, int arg1);
extern "C" void igShortArrayMetaField_SwapBytes(igShortArrayMetaField *self, int item, int count);
extern "C" int igShortArrayMetaField_GetSize(igShortArrayMetaField *self);
extern "C" int text_hd_n[4];
extern "C" int DAT_004fb428[4];
extern "C" int DAT_00533080[4];
extern "C" int igShortMetaField_GetSize(igRegistryValueList *self);
extern "C" void igStringArrayMetaField_SwapBytes(igStringArrayMetaField *self, int item, int count);
extern "C" int igStringArrayMetaField_ReadRawFieldMem(igStringArrayMetaField *arg0, void *parg1, void *parg2, int arg3, int arg4);
extern "C" int igStringArrayMetaField_WriteRawFieldMem(igStringArrayMetaField *arg0, void *parg1, void *parg2, int arg3, int arg4);
extern "C" void igStringArrayMetaField_DestructValue(igStringArrayMetaField *arg0, int arg1);
extern "C" void igStringMetaField_AssignText(igStringMetaField *self, int object, int *textCell);
extern "C" int igStringMetaField_Compare(igStringArrayMetaField *self, int objectA, int objectB);
extern "C" void igStringMetaField_DestructValue(igStringMetaField *self, int object);
extern "C" int igStringMetaField_GetRawFieldMemSize(igStringMetaField *arg0, int arg1);
extern "C" void igStringMetaField_CopyValue(igStringMetaField *arg0, int arg1, int arg2);
extern "C" void igStringMetaField_ShallowCopy(igStringArrayMetaField *arg0, int arg1, int arg2);
extern "C" bool igStringMetaField_IsAlikeExactly(igStringMetaField *field,const void *one,const void *two);
extern "C" bool igStringMetaField_IsAlikeDeep(igStringMetaField *field,const void *one,const void *two);
extern "C" bool igStringMetaField_IsAlikeShallow(igStringMetaField *field,const void *one,const void *two);
extern "C" int g_igStringMetaField_vtable[4];
extern "C" void igStringObj_SetN(igStringObj *arg0, int arg1, int arg2);
extern "C" int igStringObj_Clear(igStringObj *arg0);
extern "C" char *FUN_00300d70(igStringObj *, unsigned int);
extern "C" void igStringObj_Insert(igStringObj *self, char *insert, unsigned int at, unsigned int n);
/* An igStringObj's text: its buffer, or the shared empty text when it has none. */
static inline char *igStringObj_Text(igStringObj *s) { return (char *)s->_buffer == 0 ? g_stringObjEmptyText[0] : (char *)s->_buffer; }
extern "C" bool igStringObj_ParseBool(igStringObj *o, char *out);
extern "C" int TRUE[4];
extern "C" int FALSE[4];
extern "C" void igStringObj_KeepExtension(igStringObj *o);
extern "C" void igStringObj_RemovePathFilename(igStringObj *p);
extern "C" int DAT_004C22F0[4];
extern "C" int igStringObj_Erase(igStringObj *self, unsigned int pos, unsigned int len);
extern "C" void igStringObj_Split(igStringObj *src, long long delim, igTDataList<char *> *list);
extern "C" void igStringObj_Trim(igStringObj *self);
extern "C" int igStringObjList_BinarySearch(igStringObjList *self, int key, int (*cmp)(char *, int));
/* The intern pool's sorted string table (24 bytes): `entries` holds the token headers in strcmp
 * order of their text, and the lookup halves `step` (a power of two not above `count`). */
struct StringTable {
    StringPool *pool;            /* +0  owning intern pool */
    unsigned int count;          /* +4  live entries */
    unsigned int step;           /* +8  first binary-search step */
    unsigned int capacity;       /* +12 entry slots allocated */
    StringTokenHeader **entries; /* +16 */
    int emptyChunks;             /* +20 empty chunks seen while only the head chunk exists */
};
typedef char StringTableSize[(sizeof(StringTable) == 24) ? 1 : -1];
/* 36-byte storage chunk of the intern pool. Blocks are carved from the free blocks, which are
 * chained by their end addresses (StringBlockHeader footers). */
struct StringChunk {
    StringTable *table;     /* +0  table of the owning pool */
    StringChunk *next;      /* +4  next chunk in the chain */
    StringChunk *previous;  /* +8  previous chunk in the chain */
    unsigned int capacity;  /* +12 storage size in bytes */
    char *storage;          /* +16 allocator-provided storage base */
    char *storageEnd;       /* +20 end of the storage */
    char *freeHead;         /* +24 end address of the first free block, 0 when full */
    int largestFree;        /* +28 cached largest free size in bytes, -1 = unknown */
    unsigned char isEmpty;  /* +32 no strings live in the chunk */
};
typedef char StringChunkSize[(sizeof(StringChunk) == 36) ? 1 : -1];
typedef struct StringBlockHeader { unsigned short next; unsigned short size; } StringBlockHeader;
extern "C" void *DAT_005871c8[4];
extern "C" void *StringTable_Destroy(StringTable *self, long long delete_flag);
extern "C" void StringTable_NotifyEmptyChunk(StringTable *table, StringChunk *chunk);
extern "C" int StringTable_SearchRetained(StringTable *table, int text, int *found, unsigned int *index);
extern "C" void StringTable_EraseAt(StringTable *self, unsigned index);
extern "C" void StringTable_InsertAt(StringTable *table, int header, int index);
extern "C" void *StringTable_AllocateObject(unsigned int size, igMemoryPoolView *pool);
extern "C" StringChunk *StringChunk_Construct(StringChunk *chunk, StringChunk *previous, StringTable *table, int capacity);
extern "C" StringChunk *StringChunk_Destroy(StringChunk *chunk, long long deleteFlags);
extern "C" int StringChunk_AllocateToken(StringChunk *head, int size, StringChunk **chunkOut, int *headerOut);
extern "C" void StringChunk_InitializeStorage(StringChunk *chunk);
extern "C" int StringChunk_FreeStorage(StringChunk *chunk);
extern "C" char *StringChunk_TakeBlock(StringChunk *self, unsigned int bytes);
extern "C" int StringChunk_MergeBlocks(StringChunk *chunk, unsigned short *previous, unsigned short *left, unsigned short *right);
extern "C" void *StringChunk_AllocateObject(unsigned int size, igMemoryPoolView *pool);
extern "C" void StringList_Resize(igTDataList<char *> *list, int count);
extern "C" int DAT_004c22f8[4];
/* The bounds-checked store of the reflected igIntList: a write outside the list is dropped. */
static inline void igIntList_SetChecked(igIntList *list, int index, int value) {
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((int *)list->_data)[index] = value;
    }
}
/* Slot 21 hashes a string, slot 22 records a string offset in the hash table, slot 23 turns the
 * hash table on or off. */
class igStringTableView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual unsigned int hash(char *s);
    virtual int insert(char *s, int offset);
    virtual void setHashing(int enable);
    unsigned int _refCount;
    int _capacity;
    int _hashCapacity;
    igTDataList<char> *_strings;
    igTDataList<int> *_hashIndex;
};
extern "C" void igStringTable_Clear(igStringTableView *table);
extern "C" int igStringTable_GetCount(igStringTableView *table);
extern "C" int igStringTable_AppendString(igStringTableView *self, char *s);
extern "C" int igStringTable_Find(igStringTableView *arg0, unsigned int arg1);
extern "C" int igStringTable_GetNextStringIndex(igStringTableView *table, int offset);
extern "C" unsigned int igStringTable_Hash(igStringTableView *self, char *s);
extern "C" int igStringTable_InsertHash(igStringTableView *self, char *s, int offset);
extern "C" void igStringTable_SetHashing(igStringTableView *arg0, int arg1);
extern "C" int igStructMetaField_GetAlignment(igStructMetaField *self);
extern "C" void igStructMetaField_ConstructValue(igStructMetaField *self, int instance);
extern "C" void igStructMetaField_DestructValue(igStructMetaField *self, int instance);
extern "C" void igStructMetaField_SetToDefault(igStructMetaField *self, int instance);
extern "C" void igStructMetaField_CopyDefaultToValue(igMetaFieldView *self, void *object);
extern "C" int igStructMetaField_IsConstruct(igStructMetaField *self);
struct SymbolRecord { int name; int address; unsigned int size; int path; };
class igSymbolTableView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int vfunc_23();                                     /* slot 21: the number of symbols */
    virtual void d22();
    virtual igResult vfunc_25(int, int, int, int, int, int, int);
    virtual int vfunc_26(unsigned int address);
    virtual igResult vfunc_27(int addr, char *buf, int size, int *base, int *other, char *name, int nameSize, int *line); /* slot 25: the symbol at addr */
    virtual void d26();
    virtual void vfunc_29(int name, int address, int size, int flags);
    virtual int vfunc_30(int address);
    virtual int vfunc_31(int address, int size, int index);
    virtual void vfunc_32(int capacity);
    unsigned int _refCount; int _capacity; int _hashCapacity; unsigned int _lowAddress; unsigned int _highAddress;
    unsigned int _hashIncrement; igTDataList<int> *_symbols; igTDataList<int> *_hashIndex; int _symbolNames; int _sourceFileNames;
};
extern "C" void igSymbolTable_SetAddressRange(igSymbolTableView *arg0, unsigned arg1, unsigned arg2);
extern "C" int igSymbolTable_GetSymbolCount(igSymbolTable *self);
extern "C" void igSymbolTable_SetSymbolCount(int *arg0, igSymbolTableView *arg1, int arg2);
extern "C" igResult igSymbolTable_GetSymbol(igSymbolTable *self, int idx, char *name, int nameSize, int *a, int *b, char *path, int pathSize);
extern "C" int igSymbolTable_FindSymbolIndex(igSymbolTableView *o, unsigned key);
extern "C" void igSymbolTable_GetSymbolAtAddress(int *out, igSymbolTableView *o, int a, int b, int c, int d, int e, int f, int g, int *h);
extern "C" void igSymbolTable_AddSymbolIfMissing(igSymbolTableView *o, int a, int b, int c, int d);
extern "C" unsigned int igSymbolTable_HashAddress(igSymbolTable *arg0, int arg1);
extern "C" int igSymbolTable_InsertHashEntry(igSymbolTableView *self, int key, int key2, int value);
extern "C" int DAT_004c2300;
extern "C" void igSymbolTable_RebuildHashIndex(igSymbolTableView *self, int n);
extern "C" void igPsx2ThreadManager_InitDefaults(igPsx2ThreadManagerView *self);
extern "C" void igUnsignedCharArrayMetaField_SwapBytes(igUnsignedCharArrayMetaField *arg0, int arg1, int arg2);
extern "C" unsigned short igUnsignedCharArrayMetaField_GetSize(igUnsignedCharArrayMetaField *self);
extern "C" int DAT_004fb440[4];
extern "C" int DAT_004f9948[4];
extern "C" void igUnsignedIntArrayMetaField_SwapBytes(igUnsignedIntArrayMetaField *self, int item, int count);
extern "C" int igUnsignedIntArrayMetaField_GetSize(igUnsignedIntArrayMetaField *self);
extern "C" int DAT_004fb448[4];
extern "C" int g_igUnsignedIntMetaField_vtable[4];
extern "C" void igUnsignedLongArrayMetaField_SwapBytes(igUnsignedLongArrayMetaField *self, int item, int count);
extern "C" int igUnsignedLongArrayMetaField_GetSize(igUnsignedLongArrayMetaField *self);
extern "C" int DAT_00533530[4];
extern "C" int igUnsignedLongMetaField_GetAlignment(igUnsignedLongArrayMetaField *self);
extern "C" void igUnsignedShortArrayMetaField_SwapBytes(igUnsignedShortArrayMetaField *self, int item, int count);
extern "C" int igUnsignedShortArrayMetaField_GetSize(igUnsignedShortArrayMetaField *self);
extern "C" int DAT_00533630[4];
extern "C" int igUnsignedShortMetaField_GetAlignment(igUnsignedShortArrayMetaField *self);
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
extern "C" void FUN_0030f040(igArenaMemoryPool *arg0, int arg1, int arg2, int arg3);
struct TaggedBlockHeader;
struct ArenaState;
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
extern "C" void igArenaMemoryPool_CheckChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
extern "C" char text_E21_This_block_should_be_marked[];
extern "C" char text_E22_Corrupted_free_list[];
extern "C" char text_E23_This_block_should_be_marked[];
extern "C" char text_E24_Block_size_too_small_possibl[];
extern "C" unsigned char g_igArenaMemoryPool_ignoreE21Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE22Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE23Notice;
extern "C" unsigned char g_igArenaMemoryPool_ignoreE24Notice;
extern "C" char DAT_004fb6a0[];
extern "C" char DAT_004fb6e0[];
extern "C" char DAT_004fb700[];
extern "C" char DAT_004fb720[];
extern "C" char DAT_004fb750[];
extern "C" char DAT_004fb790[];
extern "C" char DAT_004fb7d0[];
extern "C" char DAT_004fb810[];
extern "C" char DAT_004fb840[];
extern "C" char DAT_004fb870[];
extern "C" unsigned char GPR_00554c54;
extern "C" unsigned char GPR_00554c58;
extern "C" unsigned char GPR_00554c5c;
extern "C" unsigned char GPR_00554c60;
extern "C" unsigned char GPR_00554c64;
extern "C" unsigned char GPR_00554c68;
extern "C" unsigned char GPR_00554c6c;
extern "C" unsigned char GPR_00554c70;
extern "C" unsigned char GPR_00554c74;
extern "C" unsigned char GPR_00554c78;
extern "C" void igArenaMemoryPool_CheckFreeChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
extern "C" void igArenaMemoryPool_CheckInUseChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
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
extern "C" void igArenaMemoryPool_CheckBlock(igArenaMemoryPoolView *self, TaggedBlockHeader *h, int requested);
extern "C" int text_E37_Corrupted_header[4];
extern "C" unsigned char DAT_00554cb0;
extern "C" char text_igArenaMemoryPool_E67_Block_list[];
extern "C" char text_igArenaMemoryPool_E68_Unable_to[];
extern "C" unsigned char GPR_00554ce4;
extern "C" unsigned char GPR_00554ce8;
extern "C" void igArenaMemoryPool_UpdateBlockList(igArenaMemoryPool *o, unsigned int lo, int len);
extern "C" int DAT_004f9950[];
extern "C" char DAT_004fc1e0[];
extern "C" char text_Pool_d_of_d_tot_0x_06x[];
extern "C" void igArenaMemoryPool_CheckHeapLocked(int *arg0, igArenaMemoryPoolView *arg1);
extern "C" char text_Unable_to_allocate_memory_for_ar[];
extern "C" int DAT_00587200[4];
extern "C" char text_igArenaMemoryPool_checkHeap_E69[];
extern "C" char text_igArenaMemoryPool_checkHeap_E70[];
extern "C" unsigned char GPR_00554cec;
extern "C" unsigned char GPR_00554cf0;
extern "C" igResult igArenaMemoryPool_CheckHeap(igArenaMemoryPoolView *self);
extern "C" void FUN_00310c00(igArenaMemoryPoolView *self);
extern "C" void igArenaMemoryPool_PrintStatistics(igArenaMemoryPoolView *self, char *title);
extern "C" void igArenaMemoryPool_CollectMemoryRegions(igArenaMemoryPoolView *self, igDataList *list);
extern "C" void igArenaMemoryPool_VerifyHeap(int *status, igArenaMemoryPoolView *self);
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
extern "C" igResult FUN_00312790(igArenaMemoryPoolView *self, int index, char *cur, char *end);
extern "C" unsigned char GPR_00554d1c;
extern "C" char text_igArenaMemoryPool_trim_E76_Arena[];
extern "C" igResult igArenaMemoryPool_TrimArenaBlock(igArenaMemoryPoolView *, int, int, int);
extern "C" bool igArenaMemoryPool_Trim(igArenaMemoryPoolView *self, int pad);
/* A free chunk's link pair sits past its header, at +4 or +12 as the header is short or `big`;
 * `big == 0 ? 4 : 12` gives the movn form. */
extern "C" void igArenaMemoryPool_RemoveFreeChunksInRange(int *arg0, igArenaMemoryPool *arg1, unsigned int arg2, unsigned int arg3);
/* igMemoryPoolInfo's string getters, as the pools' configure functions read them: this build takes
 * the release set of the options, checking and messages strings. */
static inline const char *igMemoryPoolInfo_source(const igMemoryPoolInfo *info) { return (const char *)info->_source; }
static inline const char *igMemoryPoolInfo_options(const igMemoryPoolInfo *info) { return (const char *)info->_releaseOptions; }
static inline const char *igMemoryPoolInfo_checking(const igMemoryPoolInfo *info) { return (const char *)info->_releaseChecking; }
static inline const char *igMemoryPoolInfo_messages(const igMemoryPoolInfo *info) { return (const char *)info->_releaseMessages; }
extern "C" char text_Sentinels[];
extern "C" char text_Contiguous[];
extern "C" char text_PreSizeReached[];
extern "C" char text_NoChecking[];
extern "C" char text_LightChecking[];
extern "C" char text_ModerateChecking[];
extern "C" char text_HeavyChecking[];
extern "C" igResult igArenaMemoryPool_Configure(igArenaMemoryPool *pool, igMemoryPoolInfo *info);
/* The arena's 0x814-byte state record, dlmalloc's malloc_state: the fast-bin size limit with two
 * flag bits, the fast bins, the top chunk and the last remainder, 96 bins that are each a chunk
 * header with its two links, the bin map and the tuning values (bit 0 of the flags at 2016 marks
 * the system memory contiguous and makes the chunk checks test the used address range). Then the
 * list of system blocks it has taken (count / 2 peaks in maxBlockPairs, their bytes sum in
 * systemBytes), the raw memory it was given and the address range its system blocks cover. */
struct ArenaState {
    unsigned int maxFast;
    TaggedBlockHeader *fastBins[10];
    char *top;
    TaggedBlockHeader *lastRemainder;
    char bins[96][20];
    unsigned int binMap[4];
    unsigned int trimThreshold;
    int f1992;
    unsigned int mmapThreshold;
    int mmapCount;
    int mmapLimit;
    int mmapPeak;
    unsigned int pageSize;
    int flags;
    int *blocks; int blockCapacity; int blockCount; int maxBlockPairs;
    int rawMemory; char _pad2040[4]; int f2044; int f2048; char _pad2052[4]; int systemBytes;
    unsigned int lowestAddress; unsigned int highestAddress;
};
/* igArenaMemoryPool's own slots (97 on) after the shared igMemoryPool table. */
class igArenaMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97();
    virtual unsigned long long vfunc_100();                                      /* slot 98, byte 400 */
    virtual void d99();
    virtual igResult vfunc_102();                                                /* slot 100, byte 408 */
    virtual igResult vfunc_103();                                                /* slot 101, byte 412 */
    virtual void *MemoryOperation(void *block, int size, unsigned int alignment); /* slot 102, byte 416 */
    virtual unsigned int vfunc_105(int address, int size);                       /* slot 103, byte 420 */
    virtual igResult vfunc_106(char *address, int size);                         /* slot 104, byte 424 */
    virtual void d105(); virtual void d106();
    virtual char *getLowestAddress();                                            /* slot 107, byte 436: vfunc_109 */
    virtual char *getHighestAddress();                                           /* slot 108, byte 440: vfunc_110 */
    virtual void vfunc_111(char *address, int size);                             /* slot 109, byte 444 */
    unsigned int _refCount;
    long long _localAllocated;
    long long _localFreed;
    long long _localNetAllocated;
    long long _localNetAllocatedHigh;
    long long _localAllocatedWithOverhead;
    long long _localFreedWithOverhead;
    long long _localNetAllocatedWithOverhead;
    long long _localNetAllocatedWithOverheadHigh;
    long long _localAllocationCount;
    long long _localFreeCount;
    long long _localNetAllocationCount;
    long long _localNetAllocationCountHigh;
    unsigned char _updateStatistics;
    unsigned char _updateGlobalStatistics;
    char _pad106[6];
    ArenaState *_arenaState;
    unsigned char _isActive;
    char _pad117[3];
    igObject *_allocationLock;
    int _rawMemory;
    unsigned char _isAlchemyMemory;
    char _pad129[7];
    unsigned long long _systemAllocated;
    unsigned int _elementSize;
    char _pad148[4];
    unsigned long long _maxSize;
    unsigned long long _size;
    unsigned int _preSize;
    unsigned short _alignment;
    char _pad174[2];
    igObject *_eventTracker;
    int _poolIndex;
    int _heapIntegrityCheckLevel;
    int _messageLevel;
    int _poolOptionFlags;
    int _poolPreSized;
    unsigned int _smallestChunkSize;
};
extern "C" void igArenaMemoryPool_Activate(igArenaMemoryPoolView *arg0);
extern "C" void igArenaMemoryPool_Reset(igArenaMemoryPool *self);
extern "C" unsigned char igArenaMemoryPool_IsActive(igArenaMemoryPool *self);
extern "C" int igArenaMemoryPool_GetRawMemory(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_SetRawMemory(int *out, igArenaMemoryPoolView *p, int rawMemory, long long size, unsigned char isAlchemyMemory);
extern "C" unsigned char igArenaMemoryPool_IsAlchemyMemory(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_EnableAllocationLock(int *ret, igArenaMemoryPool *p, int flag);
extern "C" long long igArenaMemoryPool_GetSize(igArenaMemoryPool *arg0);
extern "C" long long igArenaMemoryPool_GetMaxSize(igArenaMemoryPool *self);
extern "C" int igArenaMemoryPool_GetPreSize(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_SetAlignment(int *outStatus, igArenaMemoryPool *self, short alignment);
extern "C" unsigned short igArenaMemoryPool_GetAlignment(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_SetElementSize(int *outStatus, igArenaMemoryPool *self, int elementSize);
extern "C" int igArenaMemoryPool_GetElementSize(igArenaMemoryPool *self);
extern "C" long long Gap__Core__igArenaMemoryPool__vfunc_46(igArenaMemoryPool *arg0);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocated(igArenaMemoryPool *self);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocatedWithOverhead(igArenaMemoryPool *self);
extern "C" long long igArenaMemoryPool_GetFreeSize(igArenaMemoryPool *arg0);
extern "C" void *igArenaMemoryPool_AllocateElement(igArenaMemoryPoolView *self);
extern "C" void *igArenaMemoryPool_Allocate(igArenaMemoryPoolView *self, unsigned int size);
extern "C" void *igArenaMemoryPool_AllocateAligned(igArenaMemoryPoolView *self, unsigned int size, unsigned int alignment);
extern "C" void *igArenaMemoryPool_Callocate(igArenaMemoryPoolView *self, int count, int size);
extern "C" int igArenaMemoryPool_CallocateAligned(igArenaMemoryPoolView *t, int n, int m, unsigned int alignment);
extern "C" void *igArenaMemoryPool_Reallocate(igArenaMemoryPoolView *self, void *block, unsigned int size);
extern "C" void *igArenaMemoryPool_ReallocateAligned(igArenaMemoryPoolView *self, void *block, int size, unsigned int alignment);
extern "C" unsigned char GPR_00554d64;
extern "C" unsigned char GPR_00554d68;
static inline void releaseRefObject(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0)
            igObject_Destroy(object);
    }
}
extern "C" void igArenaMemoryPool_SetDefaults(igArenaMemoryPoolView *self);
extern "C" char DAT_004fd670[];
extern "C" char DAT_004fd6d0[];
extern "C" char DAT_004fd730[];
extern "C" unsigned int DAT_00587208[4];
extern "C" unsigned int DAT_00587210[4];
extern "C" unsigned char GPR_00554d6c;
extern "C" unsigned char GPR_00554d70;
extern "C" unsigned char GPR_00554d74;
extern "C" void igArenaMemoryPool_Shutdown(igArenaMemoryPoolView *arg0);
extern "C" void *igArenaMemoryPool_Initialize(igArenaMemoryPool *arg0);
extern "C" void *igArenaMemoryPool_Construct(igArenaMemoryPool *arg0, int extra1);
extern "C" void *igArenaMemoryPool_CopyConstruct(igArenaMemoryPool *arg0, int extra1);
extern "C" void igArenaMemoryPool_Free(igArenaMemoryPoolView *self, void *block);
extern "C" char DAT_004fd7a0[];
extern "C" unsigned char GPR_00554d78;
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(igArenaMemoryPool *p, int f);
extern "C" void igArenaMemoryPool_SetEventTracker(int *arg0, igObject *arg1);
extern "C" void igArenaMemoryPool_TransferAllocation(int *arg0, igArenaMemoryPoolView *arg1, char *arg2, igMemoryPoolView *arg3);
extern "C" unsigned char GPR_00554d7c;
extern "C" void Gap__Core__igArenaMemoryPool__constructFields(igArenaMemoryPoolView *arg0, int arg1);
extern "C" void Gap__Core__igArenaMemoryPool__destructFields(igArenaMemoryPool *self);
extern "C" int g_poolOptionFlagsDefault_004c2370[4];
extern "C" void Gap__Core__igArenaMemoryPool__resetFields(igArenaMemoryPool *self, int extra1);
extern "C" unsigned int igArenaMemoryPool_SystemAllocate(igArenaMemoryPool *arg0, int arg1, int arg2);
extern "C" igResult igArenaMemoryPool_SystemFree(void *arg1, int arg2, long long arg3);
class igArenaMemoryPoolView;
extern "C" void igArenaMemoryPool_GetStackSize(igArenaMemoryPoolView *self);
extern "C" static void igElfFile_Swap16(unsigned char *arg0);
extern "C" static void igElfFile_Swap32(unsigned char *arg0);
extern "C" void igElfFile_Reset(igElfFile *arg0);
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
    virtual igResult LoadSymbols();                            /* slot 25, byte 108 */
    virtual igResult vfunc_28(igSymbolTable *table, int flags);  /* slot 26, byte 112: fills a symbol table */
    virtual igResult Demangle(char *mangled, char *out, int size); /* slot 27, byte 116 */
    virtual void d28();
    virtual void PrintSectionHeaders();                         /* slot 29, byte 124 */
    virtual void PrintSymbols();                                /* slot 30, byte 128 */
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
extern "C" void igElfFile_Open(int *result, ElfFileView *self, const char *path);
extern "C" ElfSection *igElfFile_GetSectionHeader(ElfFileView *self, int index);
extern "C" int igElfFile_FindSectionByType(ElfFileView *self, int type, int nth);
extern "C" char DAT_004fde00[];
extern "C" char DAT_004fde20[];
extern "C" igResult igElfFile_LoadSymbols(ElfFileView *self);
extern "C" char text_No_symbols_in_s[];
extern "C" igResult igElfFile_LoadSymbolTable(ElfFileView *self, igSymbolTableView *table, int functionsOnly);
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
extern "C" void igElfFile_PrintHeader(ElfFileView *o);
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
extern "C" void igElfFile_PrintSectionHeader(ElfFileView *arg0, int arg1, ElfSection *arg2);
extern "C" char DAT_004fe6c0[];
extern "C" void igElfFile_PrintSymbols(ElfFileView *arg0);
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
extern "C" void igElfFile_PrintSymbol(igElfFile *arg0, int arg1, unsigned char *arg2);
extern "C" int text_NoMessages[4];
extern "C" int text_ErrorMessages[4];
extern "C" int text_WarningMessages[4];
extern "C" int text_Notifications[4];
extern "C" igResult igMallocMemoryPool_Configure(igMallocMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igMallocMemoryPool_Activate(igMallocMemoryPool *self);
class igSemaphoreView;
class igMallocMemoryPoolView;
extern "C" igResult igMallocMemoryPool_EnableAllocationLock(igMallocMemoryPoolView *arg1, unsigned char arg2);
extern "C" void igMallocMemoryPool_SetSize(int *outStatus, igMallocMemoryPool *self, long long size);
extern "C" long long igMallocMemoryPool_GetSize(igMallocMemoryPool *self);
extern "C" void igMallocMemoryPool_SetMaxSize(int *status, igMallocMemoryPool *self, long long maxSize);
extern "C" long long igMallocMemoryPool_GetMaxSize(igMallocMemoryPool *self);
extern "C" void igMallocMemoryPool_SetAlignment(int *outStatus, igMallocMemoryPool *self, short alignment);
extern "C" unsigned short igMallocMemoryPool_GetAlignment(igMallocMemoryPool *self);
extern "C" void igMallocMemoryPool_SetElementSize(int *status, igMallocMemoryPool *self, int elementSize);
extern "C" int igMallocMemoryPool_GetElementSize(igMallocMemoryPool *self);
extern "C" long long Gap__Core__igMallocMemoryPool__vfunc_46(igMallocMemoryPool *arg0);
extern "C" long long igMallocMemoryPool_GetLocalNetAllocated(igMallocMemoryPool *self);
extern "C" long long igMallocMemoryPool_GetLocalNetAllocatedWithOverhead(igMallocMemoryPool *self);
extern "C" long long igMallocMemoryPool_GetFreeSize(igMallocMemoryPool *arg0);
/* igMallocMemoryPool appends slot 99 (vfunc_101, byte 404) to the igMemoryPool table: the
 * reallocation core behind allocate, reallocate and free. vfunc_57 calls it with only the block and
 * size (a3 is left as it was), so the trailing alignment is spelled variadic. */
class igMallocMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97(); virtual void d98();
    virtual void *vfunc_101(void *block, unsigned int size, ...);
    unsigned int _refCount;
    long long _localAllocated;
    long long _localFreed;
    long long _localNetAllocated;
    long long _localNetAllocatedHigh;
    long long _localAllocatedWithOverhead;
    long long _localFreedWithOverhead;
    long long _localNetAllocatedWithOverhead;
    long long _localNetAllocatedWithOverheadHigh;
    long long _localAllocationCount;
    long long _localFreeCount;
    long long _localNetAllocationCount;
    long long _localNetAllocationCountHigh;
    unsigned char _updateStatistics;
    unsigned char _updateGlobalStatistics;
    char _pad106[6];
    unsigned char _isActive;
    char _pad113[3];
    igSmartPointer<igSemaphoreView> _allocationLock;
    int _poolIndex;
    unsigned int _elementSize;
    unsigned long long _maxSize;
    unsigned long long _size;
    unsigned short _alignment;
    char _pad146[2];
    igObject *_eventTracker;
    int _messageLevel;
    int _poolOptionFlags;
};
extern "C" void *igMallocMemoryPool_AllocateElement(igMallocMemoryPoolView *self);
extern "C" void *igMallocMemoryPool_Allocate(igMallocMemoryPoolView *self, unsigned int size);
extern "C" void *igMallocMemoryPool_AllocateAligned(igMallocMemoryPoolView *self, unsigned int size, unsigned int alignment);
extern "C" void *igMallocMemoryPool_Callocate(igMallocMemoryPool *self, int count, int size);
extern "C" int igMallocMemoryPool_CallocateAligned(igMallocMemoryPool *arg0, int arg1, int arg2);
extern "C" void *igMallocMemoryPool_Reallocate(igMallocMemoryPoolView *self, void *block, unsigned int size);
extern "C" void *igMallocMemoryPool_ReallocateAligned(igMallocMemoryPoolView *self, void *block, int size, unsigned int alignment);
extern "C" void igMallocMemoryPool_GangFree(igMallocMemoryPoolView *self, unsigned int size, char **block);
extern "C" int g_poolOptionFlagsDefault_004c25f8[4];
extern "C" void Gap__Core__igMallocMemoryPool__resetFields(igMallocMemoryPool *self, int extra1);
extern "C" void igMallocMemoryPool_SetDefaults(igMallocMemoryPool *self);
extern "C" void *igMallocMemoryPool_Initialize(igMallocMemoryPool *arg0);
extern "C" void *igMallocMemoryPool_CopyConstruct(igMallocMemoryPool *arg0, int extra1);
extern "C" void igMallocMemoryPool_Destruct(igMallocMemoryPool *self);
extern "C" void igMallocMemoryPool_Free(igMallocMemoryPoolView *self, void *block);
extern "C" char DAT_004fef30[];
extern "C" void igMallocMemoryPool_PrintStatistics(igMallocMemoryPool *self, char *title);
extern "C" void igMallocMemoryPool_SetEventTracker(igMallocMemoryPool *self, igObject *tracker);
extern "C" int DAT_004ff1b0[4];
extern "C" char DAT_004ff1f0[];
extern "C" void igMallocMemoryPool_TransferAllocation(int *arg0, igMallocMemoryPool *arg1, char *arg2, igMemoryPoolView *arg3);
extern "C" unsigned char igMallocMemoryPool_IsActive(igMallocMemoryPool *self);
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
/* An arena chunk's payload size rounded up to a word; its header words follow in the chunk's bytes. */
static inline unsigned int alignedPayloadSize(TaggedBlockHeader *h) {
    unsigned int size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    return size;
}
/* Chunk size in bytes: the 19-bit size (12 more bits in the third word when `big`), rounded to a word, plus the
 * header words. */
static inline unsigned int chunkBytes(TaggedBlockHeader *h) {
    unsigned int size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    return size + (h->words + 1) * 4;
}
/* A free chunk's list links follow its header: after one word in the short form, after three in the
 * 12-byte form. */
struct ChunkLinks {
    TaggedBlockHeader *forward;
    TaggedBlockHeader *back;
};
static inline ChunkLinks *chunkLinks(TaggedBlockHeader *h) {
    return (ChunkLinks *)((char *)h + (h->big == 0 ? 4 : 12));
}
/* A chunk's payload size as its header gives it. */
static inline unsigned int payloadSize(TaggedBlockHeader *h) {
    if (h->big == 0) {
        return h->size;
    }
    return h->size + (h->sizeHigh << 19);
}
/* The index of the pool that owns a chunk, as igMemoryPool::GetPoolIndex returns it. */
static inline int chunkPoolIndex(TaggedBlockHeader *h) {
    if (h->big == 0) {
        return h->poolLow * 2;
    }
    return (h->poolLow + (h->poolHigh << 5)) * 2;
}
/* Whether a pointer can be one of this arena's chunks: inside the pool's address range, tagged with
 * its pool index, and of a size that ends inside the range. */
#define IS_ARENA_CHUNK(self, p) ((char *)(p) >= (self)->getLowestAddress() && (char *)(p) < (self)->getHighestAddress() && chunkPoolIndex(p) == (self)->_poolIndex && payloadSize(p) < 0x20000000 && (char *)(p) + payloadSize(p) <= (self)->getHighestAddress())
/* dlmalloc's largebin_index: the bin of a chunk of 256 bytes or more. */
static inline unsigned int largeBinIndex(unsigned int size) {
    unsigned int x = size >> 8;
    unsigned int m;
    if (x >= 0x10000) {
        return 95;
    }
    {
        unsigned int n = ((x - 0x100) >> 16) & 8;
        x <<= n;
        m = ((x - 0x1000) >> 16) & 4;
        n += m;
        x <<= m;
        m = ((x - 0x4000) >> 16) & 2;
        n += m;
        x = (x << m) >> 14;
        m = 13 - n + (x & ~(x >> 1));
    }
    return 32 + (m << 2) + ((size >> (m + 6)) & 3);
}
/* Whether the system mapped a chunk on its own (dlmalloc's IS_MMAPPED), which only the 12-byte
 * header can say. */
static inline int chunkIsMapped(TaggedBlockHeader *h) {
    if (h->big == 1) {
        return h->extraUsed;
    }
    return 0;
}
/* The `used` bit of a chunk's header says the chunk before it is in use (dlmalloc's PREV_INUSE). */
static inline int chunkUsedBit(TaggedBlockHeader *h) {
    return h->used;
}
/* The memory a chunk hands out, after its header. */
static inline char *chunkMemory(TaggedBlockHeader *h) {
    return (char *)h + (h->big == 0 ? 4 : 12);
}
/* The header a payload of `size` bytes needs in pool `pool`. */
static inline unsigned int headerBytesFor(unsigned int size, unsigned int pool) {
    if (size >= 0x80000 || pool >= 32) {
        return 12;
    }
    return 4;
}
static inline void setForwardLink(TaggedBlockHeader *h, TaggedBlockHeader *to) {
    chunkLinks(h)->forward = to;
}
/* Records the payload size of a chunk that keeps its `total` bytes, growing a short header's size
 * field into the 12-byte form's when the payload needs it. */
static inline void setChunkPayload(TaggedBlockHeader *h, unsigned int size, unsigned int total) {
    h->size = size;
    if (size >= 0x80000) {
        h->sizeHigh = size >> 19;
        if (h->big == 0) {
            h->big = 1;
            h->extraBig = 1;
            h->extraUsed = 0;
            h->extraMarked = 0;
            h->extraTag = 0;
            h->poolHigh = 0;
        }
    } else if (h->big == 1) {
        h->sizeHigh = 0;
    }
    h->words = ((total - ((size + 3) & ~3)) >> 2) - 1;
}
/* Takes a free chunk out of its bin's list. */
static inline void unlinkChunk(TaggedBlockHeader *p) {
    TaggedBlockHeader *fwd = chunkLinks(p)->forward;
    TaggedBlockHeader *bck = chunkLinks(p)->back;
    chunkLinks(fwd)->back = bck;
    chunkLinks(bck)->forward = fwd;
}
/* Gives an existing chunk a new size of `total` bytes, keeping its pool and flags: a 12-byte header
 * drops its size extension when the size fits 19 bits and nothing else needs the extension word, and
 * a short header grows to the 12-byte form when the size no longer fits. */
static inline void setChunkBytes(TaggedBlockHeader *h, unsigned int total) {
    if (h->big == 1) {
        if (total - 4 < 0x80000 && h->poolHigh == 0 && !h->extraUsed && !h->extraMarked) {
            h->size = total - 4;
            h->words = 0;
            h->extraBig = 0;
        } else {
            h->size = total - 12;
            h->sizeHigh = (total - 12) >> 19;
            h->words = 2;
        }
    } else {
        if (total - 4 >= 0x80000) {
            h->size = total - 12;
            h->sizeHigh = (total - 12) >> 19;
            h->big = 1;
            h->extraBig = 1;
            h->extraUsed = 0;
            h->extraMarked = 0;
            h->extraTag = 0;
            h->poolHigh = 0;
            h->words = 2;
        } else {
            h->size = total - 4;
            if (h->big == 1) {
                h->sizeHigh = 0;
                h->words = 2;
            } else {
                h->words = 0;
            }
        }
    }
}
/* Writes a fresh header for a chunk owned by pool `pool`: the 12-byte form when the payload size
 * needs more than 19 bits, the pool index more than 5, or the chunk is system-mapped, else the
 * short form. A caller that knows the chunk's `total` bytes but not its payload passes a size of
 * -1; one that knows the payload may pass a total of 0 to take the header's own size. */
static inline void initChunkHeader(TaggedBlockHeader *h, unsigned int size, unsigned int total, unsigned int pool, int mapped) {
    h->poolLow = pool;
    h->relocated = 0;
    h->marked = 0;
    h->used = 0;
    if (size == (unsigned int)-1 && total != 0) {
        if (total >= 0x80004 || pool >= 32 || mapped) {
            size = total - 12;
            h->sizeHigh = size >> 19;
            h->poolHigh = pool >> 5;
            h->big = 1;
            h->extraBig = 1;
            h->extraUsed = mapped;
            h->extraMarked = 0;
            h->extraTag = 0;
            h->words = 2;
        } else {
            size = total - 4;
            h->big = 0;
            h->words = 0;
        }
    } else {
        if (size >= 0x80000 || pool >= 32 || mapped) {
            h->sizeHigh = size >> 19;
            h->poolHigh = pool >> 5;
            h->big = 1;
            h->extraBig = 1;
            h->extraUsed = mapped;
            h->extraMarked = 0;
            h->extraTag = 0;
            if (total == 0) {
                total = ((size + 3) & ~3) + 12;
            }
        } else {
            h->big = 0;
            if (total == 0) {
                total = ((size + 3) & ~3) + 4;
            }
        }
        h->words = ((total - ((size + 3) & ~3)) >> 2) - 1;
    }
    h->size = size;
}
extern "C" unsigned char GPR_00554c38;
extern "C" unsigned char GPR_00554c3c;
extern "C" char DAT_004fb4d0[];
extern "C" char DAT_004fb510[];
extern "C" unsigned char GPR_00554cb4, GPR_00554cb8, GPR_00554cbc, GPR_00554cc0, GPR_00554cc4, GPR_00554cc8, GPR_00554ccc, GPR_00554cd0, GPR_00554cd4, GPR_00554cd8, GPR_00554cdc, GPR_00554ce0;
extern "C" char DAT_004fbb00[], DAT_004fbb20[], DAT_004fbb60[], DAT_004fbba0[], DAT_004fbc00[], DAT_004fbc40[], DAT_004fbc60[], DAT_004fbcb0[], DAT_004fbce0[], DAT_004fbd20[], DAT_004fbd70[], DAT_004fbdb0[], DAT_004fbe00[], DAT_004fbe50[];
extern "C" unsigned char GPR_00554d4c;
extern "C" char DAT_004fd2c0[], DAT_004fd2e0[];
extern "C" void *FUN_00315170(igArenaMemoryPoolView *self, unsigned int bytes);
extern "C" void FUN_00318110(igArenaMemoryPoolView *self, char *mem);
extern "C" void *FUN_0031b5d0(igArenaMemoryPoolView *self, unsigned int alignment, unsigned int bytes);
extern "C" void FUN_0030f220(igArenaMemoryPoolView *self);
/* Checks the whole heap when it is made and again when it goes out of scope; the allocator entry
 * points make one at integrity level 3. */
struct ArenaHeapCheck {
    igArenaMemoryPoolView *pool;
    ArenaHeapCheck(igArenaMemoryPoolView *p) : pool(p) { pool->vfunc_103(); }
    ~ArenaHeapCheck() { pool->vfunc_103(); }
};
extern "C" void *igMallocMemoryPool_AllocateBlock(igMallocMemoryPoolView *self, unsigned size);
extern "C" void igMallocMemoryPool_FreeBlock(igMallocMemoryPoolView *self, unsigned char *p);
struct TaggedTailByte { unsigned char low : 7; unsigned char extended : 1; };
extern "C" void *igMallocMemoryPool_ReallocateBlock(igMallocMemoryPoolView *self, char *p, unsigned size);
extern "C" void *igMallocMemoryPool_AllocateAlignedBlock(igMallocMemoryPoolView *self, unsigned alignment, unsigned size);
extern "C" void *igPageMemoryPool_Initialize(igPageMemoryPool *arg0);
extern "C" void *igPageMemoryPool_CopyConstruct(igPageMemoryPool *arg0, int extra1);
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
extern "C" void Gap__Core__igPageMemoryPool__destructFields(igPageMemoryPoolView *self);
extern "C" void Gap__Core__igPageMemoryPool__resetFields(igPageMemoryPool *self, int extra1);
extern "C" igResult igPageMemoryPool_Configure(igPageMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igPageMemoryPool_Activate(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_Deactivate(igPageMemoryPool *self);
extern "C" unsigned char igPageMemoryPool_IsActive(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetRawMemory(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_IsAlchemyMemory(igPageMemoryPool *self);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_29(igPageMemoryPool *self);
extern "C" igResult igPageMemoryPool_EnableAllocationLock(igPageMemoryPoolView *arg1, int arg2);
extern "C" long long igPageMemoryPool_GetSize(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_SetMaxSize(int *status, igPageMemoryPool *self, long long maxSize);
extern "C" long long igPageMemoryPool_GetMaxSize(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetAlignment(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetElementSize(igPageMemoryPool *self);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *arg0);
extern "C" long long igPageMemoryPool_GetLocalNetAllocated(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedWithOverhead(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetFreeSize(igPageMemoryPool *arg0);
extern "C" int igPageMemoryPool_AllocateElement(igPageMemoryPool *self);
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
extern "C" void *igPageMemoryPool_Allocate(igPageMemoryPoolView *self, unsigned int size);
extern "C" void *igPageMemoryPool_AllocateAligned(igPageMemoryPoolView *self, unsigned int size, unsigned int alignment);
extern "C" void *igPageMemoryPool_Callocate(igPageMemoryPool *self, int count, int size);
extern "C" int igPageMemoryPool_CallocateAligned(igPageMemoryPool *self, int n, int sz);
extern "C" void *igPageMemoryPool_Reallocate(igPageMemoryPoolView *self, void *block, unsigned int size);
extern "C" void *igPageMemoryPool_ReallocateAligned(igPageMemoryPoolView *self, void *block, int size, unsigned int alignment);
extern "C" void igPageMemoryPool_Free(igPageMemoryPoolView *self, void *block);
extern "C" unsigned int igPageMemoryPool_OwnsAllocation(igPageMemoryPoolView *self, void *block);
extern "C" unsigned int igPageMemoryPool_GetAllocationSize(igPageMemoryPoolView *self, void *block);
extern "C" void igPageMemoryPool_SetEventTracker(igPageMemoryPool *self, igObject *tracker);
extern "C" void igPageMemoryPool_FreePages(igPageMemoryPoolView *arg0, int arg1, int arg2);
extern "C" int igPageMemoryPool_IsPageAllocated(igPageMemoryPoolView *self, unsigned int arg1);
extern "C" void igPageMemoryPool_MarkPages(igPageMemoryPoolView *self, unsigned int a, int n, int set);
extern "C" unsigned igPageMemoryPool_GetBlockSize(igPageMemoryPoolView *self, void *block);
extern "C" void igPageMemoryPool_DisplayOutstandingAllocations(igPageMemoryPoolView *self);
extern "C" int DAT_004ff4f0[4];
extern "C" char DAT_004ff510[];
extern "C" char DAT_004ff540[];
extern "C" void igProgramFile_Reset(igProgramFile *arg0);
extern "C" igResult igProgramFile_Open(igProgramFile *self, const char *path);
extern "C" void igProgramFile_Load(int *result, ProgramFileView *self, int offset, int size, void **dest);
extern "C" void igProgramFile_PrintHeader(igProgramFile *self);
extern "C" void igProgramFile_PrintSectionHeaders(igProgramFile *self);
extern "C" void igProgramFile_PrintSymbols(igProgramFile *self);
extern "C" char text_Pool_igStackMemoryPool[];
extern "C" void igStackMemoryPool_Activate(igStackMemoryPool *p);
extern "C" void igStackMemoryPool_Reset(igStackMemoryPool *s);
/* Disable step of the stack pool: run virtual slot 124 (vfunc_31, which copies +116 to +132 and
 * recomputes +136 as the 4-byte-aligned end: +132 plus the 64-bit size at +120, less 4), then
 * clear _isActive. The alias pool has the same pair: its slot 128 calls the receiver's slot 124
 * and then clears the active byte. */
extern "C" void igStackMemoryPool_Deactivate(igStackMemoryPool *self);
extern "C" unsigned char igStackMemoryPool_IsActive(igStackMemoryPool *self);
extern "C" long long igStackMemoryPool_GetSize(igStackMemoryPool *self);
extern "C" void igStackMemoryPool_SetAlignment(int *status, igStackMemoryPool *self, short alignment);
extern "C" unsigned short igStackMemoryPool_GetAlignment(igStackMemoryPool *self);
extern "C" void igStackMemoryPool_SetElementSize(int *status, igStackMemoryPool *self, int elementSize);
extern "C" int igStackMemoryPool_GetElementSize(igStackMemoryPool *self);
extern "C" int igStackMemoryPool_GetRawMemory(igStackMemoryPool *self);
extern "C" long long igStackMemoryPool_GetMaxSize(igStackMemoryPool *self);
extern "C" long long Gap__Core__igStackMemoryPool__vfunc_46(igStackMemoryPool *arg0);
/* The stack pool records each block's size in a word pushed down from _nextInt; the top bit marks
 * a freed block. */
struct StackBlockRecord { unsigned size : 31; unsigned freed : 1; };
extern "C" long long igStackMemoryPool_GetLocalNetAllocated(igStackMemoryPool *arg0);
extern "C" long long igStackMemoryPool_GetLocalNetAllocatedWithOverhead(igStackMemoryPool *arg0);
extern "C" long long igStackMemoryPool_GetFreeSize(igStackMemoryPool *arg0);
extern "C" int igStackMemoryPool_AllocateElement(igStackMemoryPool *arg0);
extern "C" int igStackMemoryPool_Allocate(igStackMemoryPool *arg0, int arg1);
extern "C" int igStackMemoryPool_AllocateAligned(igStackMemoryPool *arg0, int size, unsigned short arg2);
extern "C" void *igStackMemoryPool_Callocate(igStackMemoryPool *s, int count, int size);
extern "C" void *igStackMemoryPool_CallocateAligned(igStackMemoryPool *s, int count, int size, unsigned short a);
extern "C" void igStackMemoryPool_GangAlloc(int *result, igStackMemoryPool *pool, unsigned short count, unsigned *sizes, unsigned *out);
extern "C" void igStackMemoryPool_GangAllocAligned(int *result, igStackMemoryPool *pool, unsigned short count, unsigned *sizes, unsigned *out, unsigned short *aligns);
extern "C" int igStackMemoryPool_GetAllocationSize(igStackMemoryPool *arg0, unsigned int arg1);
extern "C" bool igStackMemoryPool_OwnsAllocation(igStackMemoryPool *s, unsigned a);
extern "C" void igStackMemoryPool_GangFree(igStackMemoryPool *self, unsigned count, unsigned *ptrs);
extern "C" void igStackMemoryPool_Free(igStackMemoryPool *self, unsigned block);
extern "C" void igStackMemoryPool_SetEventTracker(igStackMemoryPool *arg0, igObject *arg1);
extern "C" void igStandardQueue_InitDefaults(igStandardQueueView *self);
extern "C" void igStandardQueue_Create(igStandardQueue *self);
extern "C" void igStandardQueue_Destroy(igStandardQueue *self);
extern "C" int igStandardQueue_IsCreated(igStandardQueue *self);
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
/* Holds a semaphore for the enclosing scope; a null semaphore is no lock. */
struct ScopedLock {
    igSemaphoreView *lock;
    ScopedLock(igSemaphoreView *semaphore) : lock(semaphore) {
        if (lock != 0) {
            lock->wait(1);
        }
    }
    ~ScopedLock() {
        if (lock != 0) {
            lock->signal();
        }
    }
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
 * alignment, 42 terminates the thread and 48 sets its priority. */
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
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual igResult setPriority(int priority);
    virtual void d49(); virtual void d50();
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
 * element storage, 24 and 25 insert and remove an element, 26 counts the queued elements and 27
 * tells whether the queue is full. */
class igStandardQueueView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void create();
    virtual void destroy();
    virtual int isCreated();
    virtual igResult insert(int value, int block);
    virtual igResult remove(int *value, int block);
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
extern "C" igResult igStandardQueue_Insert(igStandardQueueView *self, int val, int block);
extern "C" int igStandardQueue_IsFull(igStandardQueueView *self);
extern "C" igResult igStandardQueue_Remove(igStandardQueueView *self, int *out, int block);
extern "C" int igStandardQueue_GetCount(igStandardQueueView *self);
extern "C" void igStandardQueue_Resize(igStandardQueueView *queue, int capacity);
extern "C" igResult igStandardQueue_SetCapacity(igStandardQueueView *self, unsigned n);
extern "C" int igStandardQueue_GetCapacity(igStandardQueue *self);
extern "C" void igStandardQueue_SetMaxCapacity(int *out, igStandardQueueView *self, unsigned a);
extern "C" int igStandardQueue_GetMaxCapacity(igStandardQueue *self);
extern "C" int g_vtable[4];
/* Pages counted by state (the two-bit page-table values the memory map prints as "Heap: Unknown",
 * "Free", "Blocked" and "Allocated"). */
struct PageStateCounts { int unknown; int available; int blocked; int allocated; };
/* One row of the memory map: a region's first address and size, its annotation and its pool name.
 * Rows are allocated from the non-tracked pool (DumpRegion_Allocate), zeroed (DumpRegion_Init) and freed
 * (DumpRegion_Destruct -> DumpRegion_Free). */
struct DumpRegion { unsigned start; unsigned size; char annotation[80]; char poolName[80]; };
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
extern "C" void SystemAllocatorBase_AllocateSized(SystemAllocator *self, unsigned int size);
extern "C" void SystemAllocatorBase_AllocateAligned(SystemAllocator *self, unsigned int size);
extern "C" void SystemAllocatorBase_FreeAligned(SystemAllocator *self, void *block, int size);
extern "C" void SystemAllocatorBase_ReallocateAligned(SystemAllocator *self, void *block, unsigned int size, unsigned int old);
extern "C" void SystemAllocatorBase_AdjustHeap(SystemAllocator *self, int n);
extern "C" unsigned SystemAllocatorBase_AllocateRange(SystemAllocator *self, unsigned a, int n);
extern "C" igResult SystemAllocatorBase_FreeRange(SystemAllocator *self, int arg2, int arg3);
extern "C" int SystemAllocatorBase_GetStackSize(SystemAllocator *self);
extern "C" int SystemAllocatorBase_GetPageSize(igPsx2CallStackTracer *self);
extern "C" igObject *SystemAllocatorBase_Destruct(igObject *self, long long deleteFlags);
extern "C" int SystemAllocatorBase_GetBlockSize(igPsx2CallStackTracer *self);
extern "C" void SystemAllocatorBase_GetStatistics(SystemAllocator *self, int *out);
extern "C" int FUN_003296d0(igPsx2CallStackTracer *self);
extern "C" igResult SystemAllocatorBase_SetPageState(SystemAllocator *self, int state, unsigned int addr, int len);
extern "C" void SystemAllocatorBase_DumpPageTables(SystemAllocator *self);
extern "C" void SystemAllocatorBase_PrintStatistics(SystemAllocator *self);
extern "C" DumpRegion *DumpRegion_Init(DumpRegion *row);
extern "C" DumpRegion *DumpRegion_Allocate(int size);
extern "C" void SystemAllocatorBase_PrintMemoryMap(SystemAllocator *self, char *title, char *path, int a, int b, int c, int d);
extern "C" void SystemAllocatorBase_CollectProgramRegions(SystemAllocator *self, int arg1);
extern "C" void SystemAllocatorBase_CollectHeapRegions(SystemAllocator *self, int arg1);
extern "C" void *SystemAllocatorBase_AllocateTable(SystemAllocator *self, unsigned int size);
extern "C" void SystemAllocatorBase_FreeTable(SystemAllocator *self, void *block);
extern "C" int DAT_004c2618[4];
extern "C" int DAT_004c2620;
extern "C" int igPsx2CallStackTracer_CaptureCallStack(igCallStackTracerView *tracer);
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
extern "C" void igPsx2File_Close(igPsx2FileView *self);
extern "C" void igPsx2File_OpenWithMode(int *result, igPsx2FileView *file, unsigned int mode);
extern "C" void igPsx2File_GrowBuffer(igPsx2FileView *arg0, int arg1);
extern "C" int igPsx2File_Read(igPsx2FileView *arg0, int arg1, int arg2, int arg3);
extern "C" int igPsx2File_Write(igPsx2FileView *arg0, int arg1, int arg2, int arg3);
extern "C" int igPsx2File_Flush(igPsx2FileView *arg0);
extern "C" int igPsx2File_Print(igPsx2FileView *arg0, int arg1, ...);
extern "C" int igPsx2File_GetChar(igPsx2FileView *arg0);
extern "C" int igPsx2File_UngetChar(igPsx2FileView *arg0, int arg1);
extern "C" int igPsx2File_PutChar(igPsx2FileView *arg0, unsigned char arg1);
extern "C" char *igPsx2File_GetString(igPsx2FileView *arg0, char *arg1, int arg2);
extern "C" int igPsx2File_PutString(igPsx2FileView *arg0, char *arg1);
extern "C" int igPsx2File_Tell(igPsx2File *arg0);
extern "C" char text_cdrom0[];
extern "C" int text_host0[4];
extern "C" int DAT_00587338[4];
extern "C" int DAT_00587330[4];
extern "C" int *igPsx2File_MakeCompleteFilename(igPsx2File *self, int arg1);
extern "C" char DAT_004ffbe8[];
extern "C" char DAT_004ffbf0[];
extern "C" igStringRef igPsx2File_JoinPrefix(char *prefix, char *path);
struct FolderFileStat { int mode; char rest[60]; };
extern "C" int sceGetstat(const char *, FolderFileStat *);
extern "C" igSmartPointer<igObject> igPsx2Folder_ListFiles(igPsx2Folder *self);
extern "C" igSmartPointer<igObject> igPsx2Folder_ListDirectories(igPsx2Folder *self);
struct FolderEntryWide { char bytes[328]; };
extern "C" igSmartPointer<igObject> igPsx2Folder_ListEntries(igPsx2Folder *self);
extern "C" void igPsx2Folder_TrimPath(igStringObj *arg0);
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
extern "C" void igPsx2IopRpcConnection_InitDefaults(igPsx2IopRpcConnectionView *self);
extern "C" void igPsx2IopRpcConnection_ReleaseDefaults(igPsx2IopRpcConnectionView *arg0);
extern "C" void igPsx2IopRpcConnection_Bind(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2);
extern "C" int igPsx2IopRpcConnection_Call(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
extern "C" int igPsx2IopRpcConnection_CallWithData(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int *arg4, int arg5);
extern "C" void igPsx2IopRpcConnection_CallNoData(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3);
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
extern "C" void igPsx2Media_RpcCompletionHandler(MediaRpcCompletion *c);
/* One open-file slot of igPsx2Media's handle table. */
struct MediaHandleRow { char *name; unsigned int mode; int fd; };
/* igPsx2Media's handle table: rows[limit] and a stack of free row indices. */
struct MediaHandlePool { unsigned short limit; unsigned short capacity; unsigned short count; short pad; unsigned short *freeList; MediaHandleRow *rows; };
/* An IOP file request in igPsx2Media's command buffer; the IOP writes its result to reply. */
struct MediaIoRequest { int fd; int buffer; int size; int reserved; int kind; int callback; int context; int extra; int reply; };
/* igPsx2Media: the PS2 igMedia device, forwarding file requests to the igFileIO IOP module over RPC. */
class igPsx2MediaView : public igMediaView { public:
    char *_headAndTailBuffer;
    igPsx2IopRpcConnectionView *_connection;
    igSemaphoreView *_sema;
    MediaIoRequest *_commandBuffer;
    char *_writeBuffer;
    MediaHandlePool *_handlePool;
    igStringObj *_conversionString;
    unsigned char _initialized;
};
extern "C" void Gap__Core__igPsx2Media__constructFields(igPsx2MediaView *arg0, int extra1);
extern "C" void Gap__Core__igPsx2Media__destructFields(igPsx2MediaView *arg0);
extern "C" int text_libsd_irx[4];
extern "C" int text_igFileIO_irx[4];
extern "C" int *DAT_00587368;
extern "C" bool GPR_00554de0;
extern "C" void Gap__Core__igPsx2Media__resetFields(igPsx2MediaView *self);
extern "C" int text_cdrom[4];
extern "C" unsigned short igPsx2Media_AllocateHandle(igPsx2MediaView *self);
extern "C" void igPsx2Media_FreeHandle(igPsx2MediaView *media, int handle);
extern "C" char *DAT_004c2650[];
extern "C" void igPsx2Media_MakeDevicePath(igPsx2MediaView *self, int index, char **path);
extern "C" void igPsx2Media_Open(int *arg0, igPsx2MediaView *arg1, int arg2, int **arg3, unsigned int arg4);
extern "C" void igPsx2Media_Close(igPsx2MediaView *self, int arg1);
extern "C" int igPsx2Media_Write(igPsx2Media *arg0, int arg1, int arg2, int arg3);
extern "C" int igPsx2Media_SendIoRequest(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
extern "C" int igPsx2Media_Read(igPsx2MediaView *self, int arg1, int arg2, int arg3);
extern "C" void igPsx2Media_ReadAsync(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int igPsx2Media_Seek(igPsx2Media *arg0, int arg1, int arg2, int arg3);
extern "C" int igPsx2Media_Tell(igPsx2Media *arg0, int arg1);
extern "C" int igPsx2Semaphore_GetInitialCount(igPsx2Semaphore *self);
extern "C" void igPsx2Semaphore_SetMaximumCount(int *arg0, igPsx2Semaphore *self, int arg2);
extern "C" int igPsx2Semaphore_GetMaximumCount(igPsx2Semaphore *self);
extern "C" int igPsx2Semaphore_GetCount(igPsx2Semaphore *arg0);
extern "C" void igPsx2Semaphore_Create(int *arg0, igPsx2Semaphore *self);
extern "C" void igPsx2Semaphore_IPoll(int *arg0, igPsx2Semaphore *self);
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
extern "C" void SystemAllocator_GetStatistics(SystemAllocator *self, ThreadMemoryMap *map);
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
extern "C" void igPsx2Thread_AdoptCurrentThread(igPsx2Thread *self);
extern "C" void igPsx2Thread_Join(int *arg0, void *arg1, igPsx2ThreadView *thread);
extern "C" void igPsx2Thread_Terminate(int *arg0, igPsx2ThreadView *arg1);
extern "C" void igPsx2Thread_Suspend(int *status, igPsx2Thread *self);
extern "C" void igPsx2Thread_Resume(int *status, igPsx2Thread *self);
extern "C" void igPsx2Thread_SetPriority(int *status, igPsx2Thread *self, int priority);
extern "C" igResult igPsx2Thread_ITerminate(igPsx2ThreadView *self);
extern "C" void igPsx2Thread_ISuspend(int *status, igPsx2Thread *thread);
extern "C" void igPsx2Thread_IResume(int *status, igPsx2Thread *self);
extern "C" void igPsx2Thread_ISetPriority(int *status, igPsx2Thread *self, int priority);
extern "C" void igPsx2Thread_Start(int *out, igPsx2ThreadView *thread);
extern "C" unsigned char igPsx2Thread_IsRunning(igPsx2Thread *self);
extern "C" igResult igPsx2Thread_Stop(igPsx2ThreadView *self);
extern "C" igResult igPsx2Thread_GetResult(igPsx2ThreadView *self, int block, int *result);
extern "C" void igPsx2Thread_SetDeferred(int *arg0, igPsx2Thread *self, int arg2);
extern "C" void igPsx2Thread_TestStop(igPsx2ThreadView *self);
extern "C" void igPsx2Thread_Finish(igPsx2ThreadView *thread, int result);
extern "C" int DAT_00586ca8[4];
extern "C" int igPsx2ThreadManager_GetCurrentThread(igPsx2ThreadManager *arg0);
extern "C" void igPsx2ThreadManager_FinishThread(igPsx2ThreadManagerView *manager, igPsx2ThreadView *thread);
extern "C" void igPsx2ThreadManager_AddThread(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread);
extern "C" void igPsx2ThreadManager_RemoveThread(igPsx2ThreadManagerView *self, igPsx2ThreadView *thread);
extern "C" int igPsx2Thread_GetFunction(igPsx2Thread *self);
extern "C" int igPsx2Thread_GetArg(igPsx2Thread *self);
extern "C" igResult igPsx2Thread_SetStack(igPsx2ThreadView *self, int stack, int size);
extern "C" int igPsx2Thread_GetStack(igPsx2Thread *self);
extern "C" int igPsx2Thread_GetStackSize(igPsx2Thread *self);
extern "C" int igPsx2Semaphore_IsCreated(igPsx2Semaphore *self);
extern "C" long long igPsx2LongTimer_GetElapsedTime(igPsx2LongTimer *arg0);
extern "C" void igPsx2LongTimer_ResetAndStop(igPsx2LongTimer *self);
extern "C" void igPsx2LongTimer_SetResetTime(igPsx2LongTimer *self, long long resetTime);
extern "C" long long igPsx2LongTimer_GetResetTime(igPsx2LongTimer *self);
/* The virtuals of the long timer its own methods call, placed at their retail vtable bytes: two
 * header words come first, so vfunc_N sits at byte 4 * N. */
class igLongTimerView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual long long vfunc_24();
    virtual double vfunc_25();                                                  /* +100: elapsed seconds */
    virtual long long vfunc_26();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void setResetTime(long long nanoseconds);
    virtual void d32();
    virtual long long getResetTime();
    virtual void d34();
    virtual long long vfunc_37();
};
extern "C" double igPsx2LongTimer_GetResolutionSeconds(igLongTimerView *self);
extern "C" double igPsx2LongTimer_GetElapsedSeconds(igLongTimerView *self);
extern "C" void igPsx2LongTimer_Start(igPsx2LongTimer *self);
extern "C" void igPsx2LongTimer_Stop(igPsx2LongTimer *self);
extern "C" void igPsx2LongTimer_Reset(igPsx2LongTimer *self);
extern "C" void igPsx2LongTimer_Restart(igPsx2LongTimer *self);
extern "C" void igPsx2LongTimer_SetResetTimeSeconds(igLongTimerView *self, double seconds);
extern "C" double igPsx2LongTimer_GetResetTimeSeconds(igLongTimerView *self);
extern "C" unsigned char igPsx2LongTimer_IsStopped(igPsx2LongTimer *self);
extern "C" void igPsx2File_InitDefaults(igPsx2File *arg0);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_29(igStackMemoryPool *self);
extern "C" void igStringRefList_UserPreWrite(igObjectDispatchView *self);
extern "C" void igStringRefList_TrimCapacity(igStringRefList *l);
extern "C" int g_igMemoryRefArrayMetaField_metaObject_00585de8[4];
extern "C" int g_igMemoryPoolContextInfo_metaObject_00585e98[4];
extern "C" void igMallocMemoryPool_Deactivate(igMallocMemoryPool *self);
extern "C" int FUN_00331a70(igTDataList<unsigned int> *arg0, unsigned int *arg1);
extern "C" int g_beDataObjList_metaObject[4];
extern "C" void igBoolList_TrimCapacity(igDataList *arg0);
extern "C" void igCharList_TrimCapacity(igCharList *arg0);
extern "C" void igIntList_TrimCapacity(igIntList *self);
extern "C" void igUnsignedShortList_TrimCapacity(igDataList *arg0);
extern "C" void igShortList_TrimCapacity(igDataList *arg0);
extern "C" void igUnsignedCharList_TrimCapacity(igDataList *arg0);
extern "C" void igFloatList_TrimCapacity(igDataList *arg0);
extern "C" void igPointerList_TrimCapacity(igDataList *arg0);
extern "C" void igDependencyList_TrimCapacity(igDependencyList *self);

#endif
