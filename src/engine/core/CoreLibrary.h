#ifndef DW4_CORE_LIBRARY_H
#define DW4_CORE_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/core/igTDataList.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igMetaField.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObjectList.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igRegistry.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igPsx2IopRpcConnection.h"
#include "dw4/core/igReport.h"
#include "dw4/core/igPsx2File.h"
#include "dw4/core/igThread.h"
#include "dw4/core/igTimer.h"
#include "dw4/core/igFolder.h"
#include "dw4/core/igDataLists.h"
#include "dw4/core/igStringObj.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igBoolList.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igCharMetaField.h"
#include "dw4/core/igCompoundMetaField.h"
#include "dw4/core/igContext.h"
#include "dw4/core/igDependencyOrderedList.h"
#include "dw4/core/igDirEntry.h"
#include "dw4/core/igDirectory.h"
#include "dw4/core/igDoubleMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIGBFile.h"
#include "dw4/core/igInfo.h"
#include "dw4/core/igInfoList.h"
#include "dw4/core/igIntList.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igMetaObjectList.h"
#include "dw4/core/igMetaObjectListList.h"
#include "dw4/core/igObjectListList.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igShortMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStringRefList.h"
#include "dw4/core/igStringRefListList.h"
#include "dw4/core/igUnsignedCharMetaField.h"
#include "dw4/core/igUnsignedIntList.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igUnsignedLongMetaField.h"
#include "dw4/core/igUnsignedShortMetaField.h"
#include "dw4/maths/igVec2fMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/maths/igVec4ucMetaField.h"
extern "C" {
#include "dw4/support/eekernel.h"
#include "dw4/sony/sif.h"
#define __extension__
#undef __extension__
}
#include "dw4/sony/libkernl.h"
#include "dw4/sony/sifdev.h"
#include "dw4/sony/libdma.h"
#include "dw4/support/softfloat.h"
#include "dw4/p2/p2timer.h"
#include "dw4/game/beFont.h"
#include "dw4/gui/igRendererOrderedList.h"

/* Assigning a smart pointer to an object-reference field: the field takes its own reference on the
 * new object and drops the one it held. */
template <class T, class U> static inline void assignReference(T *&field, const igSmartPointer<U> &value) {
    U *next = value.p;
    T *old;
    U::ref(next);
    old = field;
    T::release(old);
    field = (T *)next;
}

/* Reallocates the list to hold `capacity` elements; a capacity below the count is ignored. */
template <class T> static inline void setCapacity(igTDataList<T> *list, int capacity) {
    if (capacity >= list->_count) {
        ((Gap::Core::igDataList *)list)->setCapacity(capacity, sizeof(T));
    }
}

#include "dw4/core/igobject_release.h"
#include "dw4/core/igCharArrayMetaField.h"
#include "dw4/core/igDoubleList.h"
#include "dw4/core/igDriverDatabase.h"
#include "dw4/core/igFile.h"
#include "dw4/core/igFloatList.h"
#include "dw4/core/igLongList.h"
#include "dw4/core/igMemoryPool.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igNamedObjectList.h"
#include "dw4/core/igObjectDirEntry.h"
#include "dw4/core/igObjectStringMap.h"
#include "dw4/core/igPointerList.h"
#include "dw4/core/igPointerListList.h"
#include "dw4/core/igResource.h"
#include "dw4/core/igStringObjList.h"
#include "dw4/core/igUnsignedCharArrayMetaField.h"
#include "dw4/core/igUnsignedCharList.h"
#include "dw4/core/igUnsignedShortList.h"
#include "dw4/support/list-services.h"
#include "dw4/runtime/init_cpp.h"
#include "dw4/sony/libcdvd_calls.h"
/* Releases a reference field through a copy, so the field is read once. */
#define RELEASE_REF(p) do { ::igObject *t_ = (::igObject *)(p); if (t_ != 0) { t_->_refCount = t_->_refCount - 1; if (((unsigned long long)((long long)(int)t_->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(t_); } } } while (0)
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
        if (file) { file->fprintf(__VA_ARGS__); } \
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
    if (((*(void * *)&g_stringPool)) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        ((*(void * *)&g_stringPool)) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)(((*(void * *)&g_stringPool))), text));          \
    old = (StringToken *)(field);                                             \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = (int)token
#define ASSIGN_TOKEN_DIRECT(field, source)                                           \
    if (((*(void * *)&g_stringPool)) == 0) {                                               \
        poolObj = StringPool_Allocate(16);                                           \
        if (poolObj != 0) {                                                   \
            poolObj = ((void *)StringPool_Construct((StringPool *)poolObj));                          \
        }                                                                     \
        ((*(void * *)&g_stringPool)) = poolObj;                                            \
    }                                                                         \
    token = ((char *)StringPool_Intern((StringPool *)(((*(void * *)&g_stringPool))), (source)));          \
    old = (StringToken *)(field);                                             \
    if (old != 0) {                                                           \
        header = (StringTokenHeader *)old - 1;                                \
        count = header->refCount - 1;                                         \
        header->refCount = count;                                             \
        if (count == 0) {                                                     \
            StringChunk_ReleaseHeader((StringChunk *)header->owner, (StringTokenHeader *)header);                 \
        }                                                                     \
    }                                                                         \
    (field) = (int)token
#define NEW_LARGE_POOL(p) { p = newLargePool(); }
#define NEW_SMALL(p) { p = newSmallPool(); }
#define NEW_POOL(p) { if (g_presetPoolClassName != 0) { if (strcmp(g_presetPoolClassName, "igArenaMemoryPool") == 0) { NEW_LARGE_POOL(p) } else if (strcmp(g_presetPoolClassName, "igMallocMemoryPool") == 0) { NEW_SMALL(p) } else { NEW_LARGE_POOL(p) } } else { NEW_LARGE_POOL(p) } }
#define CONTEXT_NAME_LIMIT 0x7F
#define RC(o) ((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL)
#define RC2(o) ((unsigned long long)(long long)((igObject *)(o))->_refCount & 0x7fffffULL)
#define SETSTR(field) { \
    int v_; int s_; int old_; int *hd_; \
    if (g_stringPool == 0) { \
        v_ = ((int)StringPool_Allocate(0x10)); \
        if (v_ != 0) v_ = ((int)StringPool_Construct((StringPool *)v_)); \
        g_stringPool = (StringPool *)v_; \
    } \
    s_ = (int)StringPool_Intern(g_stringPool, (const char *)0); \
    old_ = info->field; \
    if (old_ != 0) { \
        hd_ = (int *)(old_ - 8); \
        v_ = *(int *)(old_ - 4) - 1; \
        *(int *)(old_ - 4) = v_; \
        if (v_ == 0) StringChunk_ReleaseHeader((StringChunk *)(*hd_), (StringTokenHeader *)hd_); \
    } \
    info->field = s_; }
#define RESERVED(n) virtual void reserved_##n()
#define REL(o) if ((o) != 0) { (o)->_refCount = (int)(o)->_refCount - 1; if (((unsigned long long)((long long)(int)(o)->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy((igObject *)(o)); } }
#define REL_O(p) { ::igObject *q_ = (::igObject *)(p); if (q_) { q_->_refCount = q_->_refCount - 1; if (((unsigned long long)(long long)(int)q_->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q_); } }
#define ASSIGN_O(o, fld, val) { ::igObject *n_ = (val); (o) = (igIGBFile *)file.p; if (n_ != 0) n_->_refCount = n_->_refCount + 1; REL_O((o)->fld) (o)->fld = (int)n_; }
#define OFF(p) (((TaggedBlockHeader *)(p))->big == 0 ? 4 : 12)
#define NEXT(p) (*(int *)((char *)(p) + OFF(p) + 4))
#define PREV(p) (*(int *)((char *)(p) + OFF(p)))
#define VCALL(o, off) (*(PF *)(*(char **)(o) + (off)))
#define PAGE_POOL_ALIGNMENT 0x1000
#define TRACER_PAGE_SIZE 0x1000
#define TRACER_BLOCK_SIZE 0x10000
#define NANOSECONDS_PER_SECOND 0x3B9ACA00

struct StringTable;
struct StringChunk;
/* 16-byte string intern pool (g_stringPool). */
typedef struct StringPool {
    StringTable *table; /* +0   sorted table of the interned strings */
    StringChunk *chunks; /* +4  head chunk of the storage chain */
    int chunkSize;  /* +8   bytes per new chunk (0x4000) */
    int pool;       /* +12  igMemoryPool the table and chunks come from */
} StringPool;
extern "C" void CoreLibrary_MarkRegistered(void);
#include "dw4/core/igBoolArrayMetaField.h"
#include "dw4/core/igEnumArrayMetaField.h"
#include "dw4/core/igFloatArrayMetaField.h"
#include "dw4/core/igIntArrayMetaField.h"
#include "dw4/core/igObjectRefArrayMetaField.h"
#include "dw4/core/igShortArrayMetaField.h"
#include "dw4/core/igStructMetaField.h"
#include "dw4/core/igUnsignedIntArrayMetaField.h"
#include "dw4/core/igUnsignedShortArrayMetaField.h"
#include "dw4/core/igCharList.h"
#include "dw4/core/igContextExt.h"
#include "dw4/core/igNamedObjectInfo.h"
#include "dw4/core/igShortList.h"
#include "dw4/support/emptyString.h"
#include "dw4/core/igSemaphore.h"
#include "dw4/core/igMetaFieldList.h"
#include "dw4/core/igContextList.h"
#include "dw4/core/igPluginHelper.h"
extern "C" void igLongTimer_GetMetaObjectFunction(void);
extern "C" void * igThreadManager_Create(int arg0);
extern "C" void igThreadManager_EnsureRegistered(void);
extern "C" CallbackArray *igThreadManager_Register(void);
extern "C" void igThreadManager_GetMetaObjectFunction(void);
extern "C" void igThreadManager_InitFields(void);
extern "C" void igPsx2ThreadManager_GetMetaObjectFunction(void);
extern "C" void igThreadManager_StaticInitCallback(void);
extern "C" void igThreadManager_ExitCallback(void);
extern "C" int igThread_GetPriorityMetaEnum(void);
extern "C" int igThread_GetStateMetaEnum(void);
extern "C" int igThread_GetScopeMetaEnum(void);
extern "C" int igThread_GetTypeMetaEnum(void);
extern "C" CallbackArray *igThread_Register(void);
extern "C" void igThread_GetMetaObjectFunction(void);
extern "C" void igThread_InitFields(void);
extern "C" void igPsx2Thread_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetOrCreateMetaObject(void);
extern "C" int igNonRefCountedThreadList_GetVTable(void);
extern "C" void igNonRefCountedThreadList_EnsureRegistered(void);
extern "C" CallbackArray *igNonRefCountedThreadList_Register(void);
extern "C" void igNonRefCountedThreadList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igThreadList_GetOrCreateMetaObject(void);
extern "C" int igThreadList_GetVTable(void);
extern "C" void igThreadList_EnsureRegistered(void);
extern "C" CallbackArray *igThreadList_Register(void);
extern "C" void igThreadList_GetMetaObjectFunction(void);
extern "C" void * igSymbolTable_Create(int arg0);
extern "C" int igSymbolTable_GetVTable(void);
extern "C" void **igSmartPointer_igIntListNoClean_Destruct(void **arg0, short arg1);
extern "C" void igSymbolTable_EnsureRegistered(void);
extern "C" CallbackArray *igSymbolTable_Register(void);
extern "C" void igSymbolTable_GetMetaObjectFunction(void);
extern "C" void igSymbolTable_InitFields(void);
extern "C" void *igStringTable_Create(int pool);
extern "C" igMetaObject *igStringTable_GetOrCreateMetaObject(void);
/* The destructor of an object-reference field, inlined through the field's address. */
static inline void ReleaseObjectField(int *slot) {
    if (slot) {
        igObject *object = (igObject *)*slot;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
}
extern "C" int igStringTable_GetVTable(void);
extern "C" void igStringTable_EnsureRegistered(void);
extern "C" CallbackArray *igStringTable_Register(void);
extern "C" void igStringTable_GetMetaObjectFunction(void);
extern "C" void igStringTable_InitFields(void);
extern "C" int igStringRefList_GetVTable(void);
extern "C" CallbackArray *igStringRefList_Register(void);
extern "C" void igStringRefList_GetMetaObjectFunction(void);
extern "C" void igStringRefList_InitFields(void);
extern "C" void * igStringObjList_Create(int arg0);
extern "C" int igStringObjList_GetVTable(void);
extern "C" CallbackArray *igStringObjList_Register(void);
extern "C" void igStringObjList_GetMetaObjectFunction(void);
extern "C" int igStringObj_GetVTable(void);
extern "C" CallbackArray *igStringObj_Register(void);
extern "C" void igStringObj_GetMetaObjectFunction(void);
extern "C" void igStringObj_InitFields(void);
extern "C" void igPsx2Semaphore_GetMetaObjectFunction(void);
extern "C" void **igSmartPointer_igLocationTable_Destruct(void **arg0, int arg1);
extern "C" void **igSmartPointer_igCallStackTable_Destruct(void **arg0, short arg1);
extern "C" void * igQueue_Create(int arg0);
extern "C" igMetaObject *igQueue_GetOrCreateMetaObject(void);
extern "C" void igQueue_EnsureRegistered(void);
extern "C" CallbackArray *igQueue_Register(void);
extern "C" void igQueue_GetMetaObjectFunction(void);
extern "C" void igQueue_InitFields(void);
extern "C" void igStandardQueue_GetMetaObjectFunction(void);
extern "C" void *igPluginHelper_Create(int pool);
extern "C" int igPluginHelper_GetVTable(void);
extern "C" void **igSmartPointer_igPluginRepositoryList_Destruct(void **arg0, long long arg1);
extern "C" void **igSmartPointer_igLibraryLoader_Destruct(void **arg0, short arg1);
extern "C" void igPluginHelper_EnsureRegistered(void);
extern "C" CallbackArray *igPluginHelper_Register(void);
extern "C" void igPluginHelper_GetMetaObjectFunction(void);
extern "C" void igPluginHelper_InitFields(void);
extern "C" igMetaObject *igPluginRepositoryList_GetOrCreateMetaObject(void);
extern "C" int igPluginRepositoryList_GetVTable(void);
extern "C" void igPluginRepositoryList_EnsureRegistered(void);
extern "C" CallbackArray *igPluginRepositoryList_Register(void);
extern "C" void igPluginRepositoryList_GetMetaObjectFunction(void);
extern "C" int igPluginRepository_GetLocationTypeMetaEnum(void);
extern "C" int igPluginRepository_Create(int arg0);
extern "C" int igPluginRepository_GetVTable(void);
extern "C" void igPluginRepository_EnsureRegistered(void);
extern "C" CallbackArray *igPluginRepository_Register(void);
extern "C" void igPluginRepository_GetMetaObjectFunction(void);
extern "C" void igPluginRepository_InitFields(void);
extern "C" int igObjectStringMap_GetVTable(void);
extern "C" CallbackArray *igObjectStringMap_Register(void);
extern "C" void igObjectStringMap_GetMetaObjectFunction(void);
extern "C" void igObjectStringMap_InitFields(void);
extern "C" int igNamedObjectInfo_GetVTable(void);
extern "C" CallbackArray *igNamedObjectInfo_Register(void);
extern "C" void igNamedObjectInfo_GetMetaObjectFunction(void);
extern "C" void igNamedObjectInfo_InitFields(void);
extern "C" int igNamedObjectList_GetVTable(void);
extern "C" CallbackArray *igNamedObjectList_Register(void);
extern "C" void igNamedObjectList_GetMetaObjectFunction(void);
extern "C" void *igMetaObject_Clone(int arg0, int arg1);
extern "C" int igMetaObject_GetVTable(void);
extern "C" CallbackArray *igMetaObject_Register(void);
extern "C" void igMetaObject_GetMetaObjectFunction(void);
extern "C" void igMetaObject_InitFields(void);
extern "C" void *igMetaFieldInfo_Create(int pool);
extern "C" int igMetaFieldInfo_GetVTable(void);
extern "C" void igMetaFieldInfo_EnsureRegistered(void);
extern "C" CallbackArray *igMetaFieldInfo_Register(void);
extern "C" void igMetaFieldInfo_GetMetaObjectFunction(void);
extern "C" int igMetaField_GetResetTypeMetaEnum(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetOrCreateMetaObject(void);
extern "C" int igMemoryPoolInfoList_GetVTable(void);
extern "C" void igMemoryPoolInfoList_EnsureRegistered(void);
extern "C" CallbackArray *igMemoryPoolInfoList_Register(void);
extern "C" void igMemoryPoolInfoList_GetMetaObjectFunction(void);
extern "C" void * igMemoryPoolInfo_Create(int arg0);
extern "C" int igMemoryPoolInfo_GetVTable(void);
extern "C" void igMemoryPoolInfo_EnsureRegistered(void);
extern "C" CallbackArray *igMemoryPoolInfo_Register(void);
extern "C" void igMemoryPoolInfo_GetMetaObjectFunction(void);
extern "C" void igMemoryPoolInfo_InitFields(void);
extern "C" void * igMemoryPoolContextInfo_Create(int arg0);
extern "C" int igMemoryPoolContextInfo_GetVTable(void);
extern "C" void igMemoryPoolContextInfo_EnsureRegistered(void);
extern "C" CallbackArray *igMemoryPoolContextInfo_Register(void);
extern "C" void igMemoryPoolContextInfo_GetMetaObjectFunction(void);
extern "C" void igMemoryPoolContextInfo_InitFields(void);
extern "C" CallbackArray *igMemoryPool_Register(void);
extern "C" void igMemoryPool_GetMetaObjectFunction(void);
extern "C" void igMemoryPool_InitFields(void);
extern "C" void igArenaMemoryPool_GetMetaObjectFunction(void);
extern "C" void * igMemoryDictionary_Create(int arg0);
extern "C" int igMemoryDictionary_GetVTable(void);
extern "C" void igMemoryDictionary_EnsureRegistered(void);
extern "C" CallbackArray *igMemoryDictionary_Register(void);
extern "C" void igMemoryDictionary_GetMetaObjectFunction(void);
extern "C" void igMemoryDictionary_InitFields(void);
extern "C" void igPsx2Media_GetMetaObjectFunction(void);
extern "C" void igLongTimer_EnsureRegistered(void);
extern "C" CallbackArray *igLongTimer_Register(void);
extern "C" void igLongTimer_InitFields(void);
extern "C" void igPsx2LongTimer_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLocationTable_GetOrCreateMetaObject(void);
extern "C" int igLocationTable_GetVTable(void);
extern "C" void igLocationTable_EnsureRegistered(void);
extern "C" CallbackArray *igLocationTable_Register(void);
extern "C" void igLocationTable_GetMetaObjectFunction(void);
extern "C" void igLocationTable_InitFields(void);
extern "C" igMetaObject *igLibraryLoader_GetOrCreateMetaObject(void);
extern "C" void igLibraryLoader_EnsureRegistered(void);
extern "C" CallbackArray *igLibraryLoader_Register(void);
extern "C" void igLibraryLoader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLibraryList_GetOrCreateMetaObject(void);
extern "C" int igLibraryList_GetVTable(void);
extern "C" void igLibraryList_EnsureRegistered(void);
extern "C" CallbackArray *igLibraryList_Register(void);
extern "C" void igLibraryList_GetMetaObjectFunction(void);
extern "C" void igLibrary_EnsureRegistered(void);
extern "C" CallbackArray *igLibrary_Register(void);
extern "C" void igLibrary_GetMetaObjectFunction(void);
extern "C" void igLibrary_InitFields(void);
extern "C" int *igSmartPointer_igMemoryPool_Construct(int *p);
extern "C" int *igSmartPointer_igMetaField_Construct(int *p);
extern "C" int *igSmartPointer_igMetaFieldList_Construct(int *p);
extern "C" int *igSmartPointer_igFile_Construct(int *p);
extern "C" void * igEventTracker_Create(int arg0);
extern "C" igMetaObject *igEventTracker_GetOrCreateMetaObject(void);
extern "C" int igEventTracker_GetVTable(void);
extern "C" void igEventTracker_EnsureRegistered(void);
extern "C" CallbackArray *igEventTracker_Register(void);
extern "C" void igEventTracker_GetMetaObjectFunction(void);
extern "C" void igEventTracker_InitFields(void);
extern "C" int igErrorHandler_Create(int arg0);
extern "C" int igErrorHandler_GetVTable(void);
extern "C" void igErrorHandler_EnsureRegistered(void);
extern "C" CallbackArray *igErrorHandler_Register(void);
extern "C" void igErrorHandler_GetMetaObjectFunction(void);
extern "C" void igErrorHandler_RegisterExitCallback(void);
extern "C" void igErrorHandler_StaticInitCallback(void);
extern "C" void igErrorHandler_ExitCallback(void);
extern "C" int igDriverDatabase_GetSectionOverrideModeMetaEnum(void);
extern "C" int igDriverDatabase_GetVTable(void);
extern "C" void igDriverDatabase_EnsureRegistered(void);
extern "C" CallbackArray *igDriverDatabase_Register(void);
extern "C" void igDriverDatabase_GetMetaObjectFunction(void);
extern "C" void igDriverDatabase_InitFields(void);
extern "C" int igDependencyOrderedList_GetVTable(void);
extern "C" void igDependencyOrderedList_EnsureRegistered(void);
extern "C" void igDependencyOrderedList_GetMetaObjectFunction(void);
extern "C" void igDependencyOrderedList_InitFields(void);
extern "C" int igDependencyMetaField_GetVTable(void);
extern "C" CallbackArray *igDependencyMetaField_Register(void);
extern "C" void igDependencyMetaField_GetMetaObjectFunction(void);
extern "C" void igDependencyMetaField_CreateDefaultDescriptor(void);
extern "C" int igDependencyMetaField_GetDefaultDescriptor(void);
extern "C" int igDependencyMetaField_GetSize(void);
extern "C" void igDependencyMetaField_InitDefaults(void *arg0);
extern "C" void igDependencyMetaField_AddSubFields(int arg0);
extern "C" int igStringRefListList_GetVTable(void);
extern "C" CallbackArray *igStringRefListList_Register(void);
extern "C" void igStringRefListList_GetMetaObjectFunction(void);
extern "C" int igObjectListList_GetVTable(void);
extern "C" CallbackArray *igObjectListList_Register(void);
extern "C" void igObjectListList_GetMetaObjectFunction(void);
extern "C" int igIntListList_GetVTable(void);
extern "C" CallbackArray *igIntListList_Register(void);
extern "C" void igIntListList_GetMetaObjectFunction(void);
extern "C" void * igMetaFieldList_Create(int arg0);
extern "C" int igMetaFieldList_GetVTable(void);
extern "C" CallbackArray *igMetaFieldList_Register(void);
extern "C" void igMetaFieldList_GetMetaObjectFunction(void);
extern "C" int igMetaObjectListList_GetVTable(void);
extern "C" CallbackArray *igMetaObjectListList_Register(void);
extern "C" void igMetaObjectListList_GetMetaObjectFunction(void);
extern "C" int igMetaObjectList_GetVTable(void);
extern "C" CallbackArray *igMetaObjectList_Register(void);
extern "C" void igMetaObjectList_GetMetaObjectFunction(void);
extern "C" int igPointerListList_GetVTable(void);
extern "C" CallbackArray *igPointerListList_Register(void);
extern "C" void igPointerListList_GetMetaObjectFunction(void);
extern "C" int igFloatListList_GetVTable(void);
extern "C" CallbackArray *igFloatListList_Register(void);
extern "C" void igFloatListList_GetMetaObjectFunction(void);
extern "C" igTDataList<igTDataList<short> *> *igShortListList_Create(igMemoryPoolView *pool);
extern "C" igMetaObject *igShortListList_GetOrCreateMetaObject(void);
extern "C" int igShortListList_GetVTable(void);
extern "C" void igShortListList_EnsureRegistered(void);
extern "C" CallbackArray *igShortListList_Register(void);
extern "C" void igShortListList_GetMetaObjectFunction(void);
extern "C" void * igUnsignedIntListNoClean_Create(int arg0);
extern "C" void igUnsignedIntList_Create(int arg0);
extern "C" void * igIntListNoClean_Create(int arg0);
extern "C" igMetaObject *igContextExtList_GetOrCreateMetaObject(void);
extern "C" int igContextExtList_GetVTable(void);
extern "C" void igContextExtList_EnsureRegistered(void);
extern "C" CallbackArray *igContextExtList_Register(void);
extern "C" void igContextExtList_GetMetaObjectFunction(void);
extern "C" void * igContextExtInfoList_Create(int arg0);
extern "C" igMetaObject *igContextExtInfoList_GetOrCreateMetaObject(void);
extern "C" int igContextExtInfoList_GetVTable(void);
extern "C" void igContextExtInfoList_EnsureRegistered(void);
extern "C" CallbackArray *igContextExtInfoList_Register(void);
extern "C" void igContextExtInfoList_GetMetaObjectFunction(void);
extern "C" void * igContextExtInfo_Create(int arg0);
extern "C" int igContextExtInfo_GetVTable(void);
extern "C" void igContextExtInfo_EnsureRegistered(void);
extern "C" CallbackArray *igContextExtInfo_Register(void);
extern "C" void igContextExtInfo_GetMetaObjectFunction(void);
extern "C" void igContextExtInfo_InitFields(void);
extern "C" void igContextExt_EnsureRegistered(void);
extern "C" void igContextExt_GetMetaObjectFunction(void);
extern "C" int igContextList_GetVTable(void);
extern "C" void igContextList_EnsureRegistered(void);
extern "C" CallbackArray *igContextList_Register(void);
extern "C" void igContextList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCallStackTracer_GetOrCreateMetaObject(void);
extern "C" int igCallStackTracer_GetVTable(void);
extern "C" void igCallStackTracer_EnsureRegistered(void);
extern "C" CallbackArray *igCallStackTracer_Register(void);
extern "C" void igCallStackTracer_GetMetaObjectFunction(void);
extern "C" void igCallStackTracer_SetAbstractProxy(void);
extern "C" void igPsx2CallStackTracer_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCallStackTable_GetOrCreateMetaObject(void);
extern "C" int igCallStackTable_GetVTable(void);
extern "C" void igCallStackTable_EnsureRegistered(void);
extern "C" CallbackArray *igCallStackTable_Register(void);
extern "C" void igCallStackTable_GetMetaObjectFunction(void);
extern "C" void igCallStackTable_InitFields(void);
extern "C" void *igAliasMemoryPool_Clone(int arg0, int arg1);
extern "C" int igAliasMemoryPool_GetVTable(void);
extern "C" void igAliasMemoryPool_EnsureRegistered(void);
extern "C" CallbackArray *igAliasMemoryPool_Register(void);
extern "C" void igAliasMemoryPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMemoryPool_GetPublishedMetaObject(void);
extern "C" void igAliasMemoryPool_InitFields(void);
extern "C" int igPageMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" int igPageMemoryPool_Clone(int arg0, int arg1);
extern "C" int igPageMemoryPool_GetVTable(void);
extern "C" void igPageMemoryPool_EnsureRegistered(void);
extern "C" CallbackArray *igPageMemoryPool_Register(void);
extern "C" void igPageMemoryPool_GetMetaObjectFunction(void);
extern "C" void igPageMemoryPool_InitFields(void);
extern "C" int igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum(void);
extern "C" int igArenaMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" int igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum(void);
extern "C" void **igArenaMemoryPool_Create(int arg0);
extern "C" int igArenaMemoryPool_Clone(int arg0, int arg1);
extern "C" int igArenaMemoryPool_GetVTable(void);
extern "C" void igArenaMemoryPool_EnsureRegistered(void);
extern "C" CallbackArray *igArenaMemoryPool_Register(void);
extern "C" void igArenaMemoryPool_InitFields(void);
extern "C" void *igStackMemoryPool_Create(int pool);
extern "C" int igStackMemoryPool_GetVTable(void);
extern "C" void igStackMemoryPool_EnsureRegistered(void);
extern "C" CallbackArray *igStackMemoryPool_Register(void);
extern "C" void igStackMemoryPool_GetMetaObjectFunction(void);
extern "C" void igStackMemoryPool_InitFields(void);
extern "C" int igMallocMemoryPool_GetMessageLevelMetaEnum(void);
extern "C" void igMallocMemoryPool_InitDefaults(int extra0);
extern "C" void *igMallocMemoryPool_Clone(void *self, void *src);
extern "C" int igMallocMemoryPool_GetVTable(void);
extern "C" void igMallocMemoryPool_EnsureRegistered(void);
extern "C" CallbackArray *igMallocMemoryPool_Register(void);
extern "C" void igMallocMemoryPool_GetMetaObjectFunction(void);
extern "C" void igMallocMemoryPool_InitFields(void);
extern "C" int igMemoryDescriptorMetaField_GetVTable(void);
extern "C" CallbackArray *igMemoryDescriptorMetaField_Register(void);
extern "C" void igMemoryDescriptorMetaField_GetMetaObjectFunction(void);
extern "C" void igMemoryDescriptorMetaField_CreateDefaultDescriptor(void);
extern "C" int igMemoryDescriptorMetaField_GetSize(void);
extern "C" void igMemoryDescriptorMetaField_InitDefaults(void *arg0);
extern "C" void igMemoryDescriptorMetaField_AddSubFields(int arg0);
extern "C" int igProgramFile_GetVTable(void);
extern "C" void igProgramFile_EnsureRegistered(void);
extern "C" CallbackArray *igProgramFile_Register(void);
extern "C" void igProgramFile_GetMetaObjectFunction(void);
extern "C" void igProgramFile_InitFields(void);
extern "C" void igElfFile_GetMetaObjectFunction(void);
extern "C" void * igElfFile_Create(int arg0);
extern "C" int igElfFile_GetVTable(void);
extern "C" void igElfFile_EnsureRegistered(void);
extern "C" CallbackArray *igElfFile_Register(void);
extern "C" int igProgramFile_GetPublishedMetaObject(void);
extern "C" void igElfFile_InitFields(void);
extern "C" int igStandardQueue_GetVTable(void);
extern "C" void igStandardQueue_EnsureRegistered(void);
extern "C" CallbackArray *igStandardQueue_Register(void);
extern "C" igMetaObject *igQueue_GetPublishedMetaObject(void);
extern "C" void igStandardQueue_InitFields(void);
extern "C" int igPsx2ThreadManager_GetVTable(void);
extern "C" void igPsx2ThreadManager_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2ThreadManager_Register(void);
extern "C" int igThreadManager_GetPublishedMetaObject(void);
extern "C" void igPsx2ThreadManager_SetWriteProxy(void);
extern "C" int igPsx2Thread_GetVTable(void);
extern "C" void igPsx2Thread_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2Thread_Register(void);
extern "C" igMetaObject *igThread_GetPublishedMetaObject(void);
extern "C" void igPsx2Thread_InitFields(void);
extern "C" int igPsx2Semaphore_GetVTable(void);
extern "C" void igPsx2Semaphore_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2Semaphore_Register(void);
extern "C" void igPsx2Semaphore_InitFields(void);
extern "C" void *igPsx2Media_Create(int pool);
extern "C" int igPsx2Media_GetVTable(void);
extern "C" void igPsx2Media_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2Media_Register(void);
extern "C" void igPsx2Media_InitFields(void);
extern "C" int igPsx2LongTimer_GetVTable(void);
extern "C" void igPsx2LongTimer_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2LongTimer_Register(void);
extern "C" int igLongTimer_GetPublishedMetaObject(void);
extern "C" void igPsx2LongTimer_StaticInitCallback(void);
extern "C" int igPsx2IopRpcConnection_GetVTable(void);
extern "C" CallbackArray *igPsx2IopRpcConnection_Register(void);
extern "C" void igPsx2IopRpcConnection_GetMetaObjectFunction(void);
extern "C" void igPsx2IopRpcConnection_InitFields(void);
extern "C" int igPsx2CallStackTracer_GetVTable(void);
extern "C" void igPsx2CallStackTracer_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2CallStackTracer_Register(void);
extern "C" igMetaObject *igCallStackTracer_GetPublishedMetaObject(void);
extern "C" void igPsx2CallStackTracer_SetWriteProxy(void);
extern "C" int igAliasMemoryPool_GetAliasedMemoryPool(void *arg0);
extern "C" int igAliasMemoryPool_GetRawMemory(void);
extern "C" void igAliasMemoryPool_SetRawMemory(int *outStatus);
extern "C" int igAliasMemoryPool_IsAlchemyMemory(void);
extern "C" int igAliasMemoryPool_IsSecondaryAllocator(void);
extern "C" void igAliasMemoryPool_SetSize(int *statusOut);
extern "C" int igAliasMemoryPool_GetSize(void);
class igResult;
extern "C" igResult igAliasMemoryPool_Configure(igAliasMemoryPool *self, igMemoryPoolInfo *info);
extern "C" int igAliasMemoryPool_CallocateAligned(igAliasMemoryPool *arg0, int arg1, int arg2, unsigned short alignment);
extern "C" int igAliasMemoryPool_OwnsAllocation(igAliasMemoryPool *self, int poolIndex);
extern "C" void __do_global_ctors();
extern "C" void __do_global_dtors();
extern "C" void FUN_002d1660(void);
extern "C" void FUN_002d1690(int extra0);
extern "C" void igObjectSystem_Initialize(struct ObjectSystemView *self);
extern "C" void igObjectSystem_Finalize(struct ObjectSystemView *self);
extern "C" void igObjectSystem_CheckHeaderVersion(void *arg0, int arg1);
extern "C" void *igObjectSystem_Construct(struct ObjectSystemView *self);
extern "C" int igObjectSystem_GetRootPath(int *p);
extern "C" int igObjectSystem_GetBasePath(int *p);
extern "C" int igObjectSystem_AppendMetaEnum(int *p, int extra1);
extern "C" int igObjectSystem_AddExitCallback(int *p, int extra1);
extern "C" void igObjectSystem_RunRegistrationCallbacks(int *arg0, int arg1);
extern "C" void igObjectSystem_SetEventTrackerFileName(char *arg0, char *arg1);
extern "C" void igObjectSystem_SetSystemPoolEventTrackerFileName(char *a, char *b);
extern "C" void igObjectSystem_SetSymbolsFileName(void *arg0, int arg1);
extern "C" void *igObjectSystem_OperatorNew(unsigned int size);
extern "C" void igObjectSystem_OperatorDelete(void *block);
extern "C" int **igBoolMetaField_Construct(int **arg0, int extra1);
extern "C" void igCallStackTable_SetCapacity(int a0, int a1);
class igResult;
/* igCallStackTable (reflected layout in dw4/support/reflected.h) with the virtuals its callers use. Its
 * call stacks are zero-terminated return-address runs packed end to end; the hash index holds
 * their word offsets, -1 for an empty slot. */
class igCallStackTableView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int GetCallStackCount();
    virtual igResult TruncateCallStacks(int count);
    virtual unsigned int *GetCallStack(int offset);
    virtual int AddCallStack(int *stack);
    virtual int InsertCallStack(unsigned int *stack);
    virtual int FindCallStack(unsigned int *stack);
    virtual unsigned int HashCallStack(unsigned int *stack);
    virtual int InsertHashEntry(unsigned int *stack, int offset);
    virtual void RebuildHashIndex(int hashCapacity);
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
extern "C" void igCallStackTracer_PreExit(void);
extern "C" void igCallStackTracer_Exit(void);
extern "C" int **igCharMetaField_Construct(int **arg0, int extra1);
extern "C" void igDependencyOrderedList_TopologicalSort(igDependencyOrderedList *self);
extern "C" void *igDirectory_GetEntryAlias(int *arg0, int arg1);
extern "C" void igDriverDatabase_ReleaseDefaults(int self);
extern "C" int igDriverDatabase_GetCurrentProperty(void *arg0, int arg1);
extern "C" void igDriverDatabase_ClearRawDatabase(int *p);
extern "C" void *igDriverDatabase_ConfigNode_Destruct(void *arg0, long long arg1);
extern "C" void igDriverDatabase_LoadFromString(void *arg0, int arg1);
extern "C" int igDriverDatabase_GetOSName(void *arg0);
extern "C" int igDriverDatabase_GetCpuVendor(void *arg0);
extern "C" int igDriverDatabase_GetCpuType(void *arg0);
extern "C" bool igDriverDatabase_ReadLineFromString(igDriverDatabase *self, char **cursor, char *out, int size);
extern "C" void igDriverDatabase_SkipWhitespace(int *arg0);
extern "C" void igDriverDatabase_TrimTrailingWhitespace(int arg0, char *arg1);
extern "C" bool igDriverDatabase_ReadToken(char *arg0, int *arg1);
extern "C" bool igDriverDatabase_ParseOperator(igDriverDatabase *self, int *out);
extern "C" int igDriverDatabase_GetPropertyValueType(int arg0, int arg1);
extern "C" unsigned char igDriverDatabase_CompareTyped(igDriverDatabase *self, int valueType, char *actual, int compareMode, char *expected);
extern "C" int igDriverDatabase_CompareString(int dummy0, int arg1, int arg2, int arg3);
extern "C" int igDriverDatabase_CompareValues(int dummy0, int arg1, int arg2, int arg3);
extern "C" bool igDriverDatabase_CompareFloat(int unused, int mode, float a, float b);
extern "C" int igDriverDatabase_CompareBool(int p, unsigned char a, int m, unsigned char b);
extern "C" void *igDriverDatabase_Setting_Construct(void *arg0);
extern "C" void *igDriverDatabase_SettingsNode_Construct(void *arg0);
extern "C" void *igDriverDatabase_PropertyNode_Construct(void *arg0, int arg1);
extern "C" int **igEnumMetaField_Construct(int **arg0, int extra1);
extern "C" int igErrorHandler_GetInstanceAlias();
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
struct EventRecord;
extern "C" EventRecord *igEventTracker_CopyEvent(EventRecord *copy, const EventRecord *source);
extern "C" void *igEventTracker_InitMemoryEvent(void *record, int type, void *address, int size, int alignment, int group, int className, int memberName, int annotation, int sourceFile, int line, int poolName);
extern "C" void *igEventTracker_InitMarkerEvent(void *record, int markerType, int markerValue, int markerName, int group, int className, int memberName, int annotation, int sourceFile, int line);
extern "C" void *igEventTracker_DestructEvent(void *arg0, long long arg1);
extern "C" void igEventTracker_ClearEvent(int arg0);
extern "C" int igEventTracker_FindFreeEventDataSlot(void *arg0);
extern "C" int igEventTracker_GetEventDataInt(const EventRecord *record, int slot);
extern "C" void igEventTracker_SetEventDataInt(void *arg0, int arg1, int arg2);
extern "C" unsigned int igEventTracker_GetEventDataUnsigned(const EventRecord *record, int slot);
extern "C" void igEventTracker_SetEventDataUnsigned(void *arg0, int arg1, int arg2);
extern "C" char *igEventTracker_GetEventDataString(const EventRecord *record, int slot);
extern "C" void igEventTracker_SetEventDataString(void *arg0, int arg1, int arg2);
extern "C" void igEventTracker_GetEventDataUnsigned3(const EventRecord *record, int slot, unsigned int *values);
extern "C" void ***igAdxFile_GetSearchPathHolder(void);
class igFileView;
extern "C" int igInfo_FindObjectReference(void **arg0, int arg1, int arg2);
extern "C" struct StringPool *StringPool_Destroy(struct StringPool *self, long long delete_flag);
extern "C" void StringPool_OperatorDelete(int arg0);
extern "C" void StringPool_SetBlockSize(int a0, int a1);
extern "C" void igLocationTable_SetHashCapacity(int a0, int a1);
class igLocationTableView;
extern "C" void igLocationTable_Allocate(igLocationTableView *arg0);
extern "C" int igLocationTable_IsInitialized(void *arg0);
extern "C" void igLocationTable_Resize(int *result, igLocationTable *self, int count);
class igMediaFileView;
extern "C" void *Memory_AllocateAligned(unsigned int size, unsigned short alignment);
extern "C" void *Memory_Callocate(unsigned int size, unsigned int alignment);
extern "C" void *Memory_ReallocateBuffer(void *buffer, unsigned int size);
extern "C" void *Memory_DuplicateBuffer(void *source);
extern "C" void Memory_FreeOwnedBufferUnchecked(void *buffer);
extern "C" void Memory_DumpMemory(unsigned int size, unsigned int perLine, unsigned int digits, unsigned int addr, long long length, const char *name);
extern "C" void Memory_SystemFree(void *block);
class igMemoryFileView;
extern "C" int **igMemoryPool_Initialize(int **arg0);
extern "C" int **igMemoryPool_Construct(int **arg0);
extern "C" igMemoryPool *igMemoryPool_CopyConstruct(igMemoryPool *self, igMemoryPool *source);
extern "C" int igMemoryPool_Destruct(int extra0);
extern "C" void * igObject_OperatorNew(int a0, int a1, int extra2);
extern "C" void igObject_OperatorDelete(void *block);
extern "C" int igMemoryPool_HandleOutOfMemory(int arg0, int arg1, int arg2);
extern "C" void igMemoryPool_InitDefaults(void *arg0);
extern "C" void igMemoryPool_ReleaseDefaults(igMemoryPoolView *pool);
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
extern "C" igResult igMemoryPool_Configure(void **pool, void *object);
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
extern "C" int igMemoryPool_AllocateFromSystemTracked(igMemoryPoolView *pool, int size, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void igMemoryPool_FreeTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void igMemoryPool_FreeFromSystemTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth);
extern "C" void Memory_ShutdownAllocatorRegistries(void **rootAllocator);
extern "C" void igMemoryPool_SetDefaults(void *arg0);
extern "C" void igMemoryPool_Shutdown(void);
extern "C" void igMemoryPool_UpdateGlobalStatistics(long long arg0, long long arg1, int arg2);
extern "C" void igMemoryPool_EnableAllocationLock(int *status_out);
extern "C" int igMemoryPoolContextInfo_GetPoolInfo(int arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_SetPoolName(int self, int recordIndex, int name);
extern "C" int igMemoryPoolContextInfo_FindPoolIndexByName(int arg0, char *arg1);
extern "C" int igMemoryPoolContextInfo_GetPoolIndexByName(int arg0, char *arg1);
extern "C" int igMemoryPoolContextInfo_FindPoolIndex(int arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_SetDirectory(igMemoryPoolContextInfo *self, int directory);
class MemoryContext;
extern "C" void igMemoryPoolContextInfo_ResetPools(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_TrimCapacity(void **arg0);
extern "C" void Gap__Core__igMemoryPoolContextInfo__resetFields(void **arg0, int arg1);
extern "C" void Gap__Core__igMemoryPoolContextInfo__destructFields(void **arg0);
extern "C" void MemoryContext_OnStartupComplete(void);
extern "C" void igMemoryPoolContextInfo_Shutdown(char *arg0);
extern "C" igMetaObject *igMemoryPool_GetMeta(void);
extern "C" void igMemoryPoolContextInfo_ReleaseContextInfo(void *arg0);
extern "C" void FUN_002f5cc0(int *arg0);
extern "C" void MemoryContext_RemoveAllocator(void *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_CompareNames(const char **a, const char **b);

extern "C" int Memory_GetCurrentContext(void);
extern "C" void * igMemoryPoolContextInfo_Allocate(int arg0);
extern "C" void igMemoryPoolContextInfo_DeleteAllocation(void *allocation);
extern "C" void Memory_PrintPoolStatistics(int arg0, void *pool);
extern "C" int Memory_GetPoolNameByIndex(int arg0);
extern "C" void * Memory_GetPoolName(int arg0);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolHandle(int arg0);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolInfoCount(void *arg0);
extern "C" int igMemoryPoolContextInfo_GetMemoryPoolInfo(void *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_AdoptMemoryPoolInfo(void *arg0, void *arg1);
extern "C" void igMemoryPoolContextInfo_AddMemoryPoolInfo(igMemoryPoolContextInfo *self, int poolInfo);
extern "C" void igMemoryPoolContextInfo_ClearMemoryPoolInfos(void *arg0);
extern "C" void igMemoryPoolInfo_UserRegistryLoad(int *arg0, int *arg1, int arg2, int arg3);
extern "C" void igMemoryPoolInfo_Print(igMemoryPoolInfo *info);
extern "C" void *igMemoryPoolInfoList_Allocate(unsigned int size);
extern "C" void igMemoryPoolInfoList_Delete(void *block);
class igMetaFieldView;
class igMetaFieldView;
extern "C" void igMetaField_ConstructCopy(int a0, int a1, int a2);
extern "C" void igMetaObject_FinalizeAndAppendField(void *meta,void *field);
extern "C" int FUN_002fdef0(int a0, int a1);
extern "C" void igMetaObject_FinalizeFieldLayoutTree(int arg0);
extern "C" int igMetaObject_GetPersistentFieldCount(int arg0);
extern "C" int igMetaObject_GetPoolName(int *object);
extern "C" int igObject_Destruct(int extra0);
extern "C" void igObject_TrimCapacity(int extra0);
extern "C" void igObject_RegisterInstance(void **arg0, void *arg1);
class igObjectDispatchView;
extern "C" void igObject_CopyFields(igObjectDispatchView *self, int source);
extern "C" int igObject_CloneViaMetadata(void **source, int copyMode);
extern "C" void igObject_FreeStorage(int object, int storage);
class igObjectDirEntryView;
extern "C" void igReport_VPrintf(const char *arg0, int arg1);
extern "C" int igReport_ErrorPrintf(int arg0, ...);
extern "C" int igReport_VErrorPrintf(int arg0, int arg1);
extern "C" void igReport_FlushError(void);
extern "C" void igPluginHelper_LoadPluginsFromRegistry(void *self);
extern "C" void **igQueue_StartServiceThread(void *arg0, int arg1, unsigned stackSize);
extern "C" int igQueue_ReleaseDefaults(int extra0);
extern "C" int **igRawRefMetaField_Construct(int **arg0, int extra1);
extern "C" char *igRefMetaField_SkipPastChar(char *s, char ch);
extern "C" bool igRegistry_ParseEnumFlags(char *text, int *value, int metaEnum, char *format);
extern "C" int igRegistry_ParseEnumValue(char *text, int *value, igMetaEnum *metaEnum, char *format);
extern "C" int igReport_Detail(const char *arg0, ...);
extern "C" int igReport_DefaultHandler(int arg0, int arg1);
extern "C" int igReport_VReport(int arg0, const char *arg1, int arg2);
extern "C" void igReport_ReadSettings(void);
extern "C" void igReport_RestoreDefaults(void);
extern "C" void igResource_AsyncLoadThreadProc(int *result, Gap::Core::igDirectory *file);
extern "C" void igResource_WrapRootInSceneInfo(int arg0);
extern "C" int **igShortMetaField_Construct(int **arg0, int extra1);
extern "C" int igStringObj_VFormat(int arg0, int extra1, int extra2);
extern "C" void StringChunk_ReturnBlock(StringChunk *self, char *block, unsigned int bytes);
extern "C" StringTable *StringTable_Construct(StringTable *table, StringPool *pool, int capacity);
extern "C" void StringTable_SetSynchronization(int arg0);
extern "C" int StringTable_Find(StringTable *table, int text);
struct StringTokenHeader;
extern "C" StringTokenHeader *StringTable_Register(StringTable *table, StringTokenHeader *header, StringChunk *chunk, int text);
extern "C" void StringTable_RemoveHeader(StringTable *table, int header);
extern "C" int StringTable_DeleteObject(int object);
extern "C" int StringChunk_DeleteObject(int object);
extern "C" void igStringRefList_ReleaseDefaults(void *self0);
extern "C" void igStringTable_SetCapacity(int object, int capacity);
extern "C" void igStringTable_SetHashCapacity(int object, int hashCapacity);
extern "C" void igStringTable_Reserve(void *object);
extern "C" void igStringTable_RemoveAll(int arg0);
class igStringTableView;
extern "C" void igStringTable_Truncate(int *result, igStringTableView *table, int count);
extern "C" char *igStringTable_GetString(int *arg0, int arg1);
extern "C" int igStringTable_FindOrAddString(int arg0, int arg1);
extern "C" void igSymbolTable_SetCapacity(int a0, int a1);
extern "C" void igSymbolTable_SetHashCapacity(int a0, int a1);
class igSymbolTableView;
extern "C" void igSymbolTable_ReserveStorage(igSymbolTableView *arg0);
extern "C" void igPsx2ThreadManager_CreateGlobal(void);
extern "C" void igPsx2ThreadManager_DestroyGlobal(void);
extern "C" int **igUnsignedLongMetaField_Construct(int **arg0, int extra1);
extern "C" int **igUnsignedShortMetaField_Construct(int **arg0, int extra1);
extern "C" void igArenaMemoryPool_CheckInUseBlock(void *arg0, unsigned char *arg1, int extra2);
class igArenaMemoryPoolView;
extern "C" void igArenaMemoryPool_DisplayOutstandingAllocationsBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end);
extern "C" void igArenaMemoryPool_DisplayOutstandingAllocations(void *self0);
extern "C" char *igMetaEnum_GetNamesByMask(char *arg0, int arg1, int arg2, int arg3);
extern "C" char *igMetaEnum_GetValueName(char *arg0, int arg1, int arg2, int arg3);
class igArenaMemoryPoolView;
extern "C" void igArenaMemoryPool_MallocConsolidate(igArenaMemoryPoolView *self);
extern "C" int igArenaMemoryPool_SystemTrim(igArenaMemoryPoolView *self, unsigned int pad, int force);
extern "C" void igArenaMemoryPool_Deactivate(igArenaMemoryPoolView *p);
extern "C" int igArenaMemoryPool_IsSecondaryAllocator(void);
extern "C" void igArenaMemoryPool_SetSize(int *statusOut);
extern "C" void igArenaMemoryPool_SetMaxSize(int *status, igArenaMemoryPool *self, unsigned long long maxSize);
extern "C" void igArenaMemoryPool_SetPreSize(int *status, igArenaMemoryPoolView *self, int preSize);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocatedHigh(igArenaMemoryPool *self);
extern "C" long long igArenaMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igArenaMemoryPool *self);
extern "C" int igArenaMemoryPool_GetArenaCount(igArenaMemoryPoolView *self);
extern "C" int igArenaMemoryPool_GetArenaHighCount(igArenaMemoryPoolView *self);
extern "C" long long igArenaMemoryPool_GetSystemAllocated(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_Lock(igArenaMemoryPoolView *self);
extern "C" void igArenaMemoryPool_Unlock(igArenaMemoryPoolView *self);
extern "C" int igArenaMemoryPool_UnlockAndReturn(igArenaMemoryPoolView *self, int value);
extern "C" void igArenaMemoryPool_GangAllocAligned(int *arg0);
extern "C" void Gap__Core__igArenaMemoryPool__freeSized(igArenaMemoryPoolView *self, unsigned int size, char **block);
extern "C" void igArenaMemoryPool_Destruct(void **self);
extern "C" int igArenaMemoryPool_OwnsAllocation(void *self, unsigned char *p);
extern "C" int Gap__Core__igArenaMemoryPool__vfunc_83(void);
extern "C" int igArenaMemoryPool_GetAllocationSize(int arg0, unsigned char *p);
extern "C" int igArenaMemoryPool_GetEventTracker(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_Dump(void);
extern "C" int igArenaMemoryPool_GetPoolIndex(igArenaMemoryPool *self);
extern "C" void igArenaMemoryPool_SetPoolIndex(igArenaMemoryPool *self, int index);
extern "C" int igArenaMemoryPool_CanTransferTo(igArenaMemoryPool *self, igMemoryPoolView *target);
extern "C" int igArenaMemoryPool_GetAllocationPoolIndex(int arg0, unsigned char *p);
extern "C" void Gap__Core__igArenaMemoryPool__vfunc_108(void);
extern "C" int igArenaMemoryPool_GetLowestAddress(igArenaMemoryPoolView *self);
extern "C" int igArenaMemoryPool_GetHighestAddress(igArenaMemoryPoolView *self);
extern "C" void igElfFile_SwapHeader(unsigned char *p);
extern "C" void igElfFile_SwapSectionHeaders(unsigned char *arg0, int arg1);
extern "C" void igElfFile_SwapSymbols(unsigned char *arg0, int arg1);
class ElfFileView;
extern "C" void igElfFile_Close(int *result, ElfFileView *self);
extern "C" int igElfFile_GetSymbol(void *arg0, int arg1);
extern "C" void igElfFile_DemangleName(const char *in, char *out, int size);
extern "C" void igElfFile_Demangle(int *result, void *self, char *mangled, char *out, int size);
typedef struct ElfValueName { int value; const char *name; } ElfValueName;
extern "C" const char *igElfFile_LookupValueName(int value, const ElfValueName *table);
extern "C" char *igElfFile_FormatFlags(int flags, const ElfValueName *names, char *out);
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
class igPageMemoryPoolView;
extern "C" void igPageMemoryPool_Reset(igPageMemoryPoolView *self);
extern "C" void igPageMemoryPool_SetRawMemory(int *statusOut);
extern "C" void igPageMemoryPool_SetSize(int *statusOut);
extern "C" void igPageMemoryPool_SetAlignment(int *statusOut);
extern "C" void igPageMemoryPool_SetElementSize(int *statusOut);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedHigh(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetSystemAllocated(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_Lock(igPageMemoryPoolView *self);
extern "C" int igPageMemoryPool_UnlockAndReturn(igPageMemoryPoolView *self, int result);
extern "C" void igPageMemoryPool_GangAlloc(int *status);
extern "C" void igPageMemoryPool_GangAllocAligned(int *status);
extern "C" void igPageMemoryPool_GangFree(void);
extern "C" int Gap__Core__igPageMemoryPool__vfunc_83(void);
extern "C" void igPageMemoryPool_SetPoolOptionFlags(igPageMemoryPool *self, int flags);
extern "C" int igPageMemoryPool_GetEventTracker(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_Dump(void);
extern "C" int igPageMemoryPool_GetPoolIndex(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_SetPoolIndex(igPageMemoryPool *self, int index);
extern "C" int igPageMemoryPool_AllocatePages(igPageMemoryPoolView *self, int size);
extern "C" int igPageMemoryPool_ReallocatePages(igPageMemoryPoolView *self, int block, int size, int oldSize);
extern "C" int igPageMemoryPool_AllocatePagesAligned(igPageMemoryPoolView *self, int alignment, int size);
extern "C" void igPageMemoryPool_PrintStatistics(int extra0, int extra1);
extern "C" void igPageMemoryPool_CollectMemoryRegions(void);
class ProgramFileView;
extern "C" void igProgramFile_Close(int *result, ProgramFileView *self);
extern "C" void igProgramFile_LoadSymbols(int *status_out);
extern "C" void igProgramFile_LoadSymbolTable(int *status_out);
extern "C" void igProgramFile_Demangle(int *status_out);
extern "C" igResult igStackMemoryPool_Configure(igStackMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igStackMemoryPool_SetSize(int *status_out);
extern "C" void igStackMemoryPool_SetRawMemory(int *result, igStackMemoryPool *self, int memory, long long size, char isAlchemyMemory);
extern "C" int igStackMemoryPool_Reallocate(void **arg0, int arg1, unsigned int arg2);
extern "C" int igStackMemoryPool_ReallocateAligned(void **arg0, int arg1, unsigned int arg2, unsigned short arg3);
extern "C" int igStackMemoryPool_GetEventTracker(igStackMemoryPool *self);
extern "C" void igStackMemoryPool_Dump(int *a, int a1, int a2, int a3, int a4);
extern "C" int igStackMemoryPool_GetPoolIndex(igStackMemoryPool *self);
extern "C" void igStackMemoryPool_SetPoolIndex(igStackMemoryPool *self, int index);
extern "C" void igStackMemoryPool_CollectMemoryRegions(igStackMemoryPool *self, igDataList *list);
class igStandardQueueView;
extern "C" void igStandardQueue_ReleaseDefaults(igStandardQueueView *self);
extern "C" int **SystemAllocatorBase_Construct(int **arg0);
class SystemAllocator;
extern "C" void SystemAllocatorBase_ReleasePageTables(SystemAllocator *self);
extern "C" int SystemAllocatorBase_Allocate(void *arg0, int arg1);
extern "C" int SystemAllocatorBase_Memalign(int self, int size);
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
extern "C" void SystemAllocatorBase_MarkRange(int *status);
extern "C" int PageTable_GetState(int arg0, unsigned int arg1);
extern "C" void PageTable_SetState(int arg0, unsigned int arg1, int arg2);
extern "C" void PageTable_SetStateRange(int arg0, int arg1, int arg2, int arg3);
extern "C" int PageTable_CountRun(int arg0, unsigned int arg1, int arg2, int arg3, int arg4);
extern "C" void PageTable_CountStates(int arg0, void *arg1);
extern "C" void SystemAllocator_EnsureCreated(void);
extern "C" void SystemAllocator_EnsureDestroyed(void);
extern "C" void igPsx2CallStackTracer_HasSymbols(void);
/* sceOpen flags and sceLseek origins (Sony sifdev.h). */
enum { SCE_RDONLY = 0x1, SCE_WRONLY = 0x2, SCE_RDWR = 0x3, SCE_APPEND = 0x100, SCE_CREAT = 0x200, SCE_TRUNC = 0x400 };
enum { SCE_SEEK_SET = 0, SCE_SEEK_CUR = 1, SCE_SEEK_END = 2 };
extern "C" char *igPsx2_ResolveModulePath(char *name, int kind);
extern "C" igResult igPsx2_LoadIopModuleEx(char *name, int kind, int argLength, const char *args, int *moduleId);
extern "C" void FUN_0032d070(void);
extern "C" void igPsx2_RebootIop(void);
extern "C" void igPsx2_InitializeIop(void);
extern "C" void igPsx2_SetupOutputFiles(void);
extern "C" void igPsx2IopRpcConnection_RpcEndCallback(void *sema);
extern "C" long long igPsx2LongTimer_GetCurrentTime(void);
extern "C" int igPsx2LongTimer_GetResolution(void);
extern "C" void igPsx2LongTimer_InitTimer(void);
extern "C" void igPsx2LongTimer_StaticInit(void);
extern "C" void Gap__Core__igPsx2Media__userConstruct(int arg0);
extern "C" void igPsx2Media_SetDevicePrefix(int arg0);
extern "C" int igPsx2Media_HandlesDevice(void);
extern "C" void igPsx2Semaphore_SetInitialCount(int *arg0, void *arg1, int arg2);
extern "C" void igPsx2Semaphore_Destroy(int *arg0, int *arg1);
extern "C" void igPsx2Semaphore_ISignal(int *arg0, void *arg1);
extern "C" void igPsx2Semaphore_WaitBlocking(int *arg0, void *arg1);
extern "C" int iPollSema(int);
extern "C" void igPsx2Semaphore_Signal(int *result, igPsx2Semaphore *self);
extern "C" void igPsx2Semaphore_Wait(int *result, igPsx2Semaphore *self, int block);
extern "C" void SystemAllocator_Activate(void);
extern "C" void SystemAllocator_Deactivate(void);
extern "C" int FUN_0032f370(void);
extern "C" int SystemAllocator_Sbrk(int arg0, int arg1);
extern "C" void igPsx2Thread_ThreadEntry(void *thread);
extern "C" int iResumeThread(int);
extern "C" int iChangeThreadPriority(int, int);
extern "C" int igPsx2Thread_IsEqual(void *arg0, void *arg1);
class igPsx2ThreadView;
class igPsx2ThreadManagerView;
extern "C" void igPsx2Thread_InitDefaults(igPsx2ThreadView *self);
extern "C" void igPsx2Thread_Sleep(int *result, int self, unsigned long long nanoseconds);
extern "C" void igPsx2Thread_Exit(void *arg0, int arg1);
extern "C" void igPsx2Thread_WaitForWakeup(int *arg0);
extern "C" void igPsx2Thread_Wakeup(int *arg0, void *arg1);
extern "C" void igPsx2Thread_IWakeup(int *arg0, void *arg1);
extern "C" void igPsx2Thread_EnterStoppingPoint(void *arg0);
extern "C" void igPsx2Thread_LeaveStoppingPoint(void *arg0);
extern "C" int Memory_GetAllocatorOrDefault(int extra0);
extern "C" int igPsx2ThreadManager_GetMeta(void);
extern "C" int igPsx2Thread_GetMeta(void);
extern "C" int igPsx2Thread_GetStackAlignment(void);
extern "C" int Gap__Core__igPsx2Thread__vfunc_43(void);
extern "C" void igPsx2Thread_ReleaseDefaults(igPsx2Thread *self);
extern "C" void Gap__Core__igPsx2Thread__vfunc_52(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_53(int *result);
extern "C" void Gap__Core__igPsx2Thread__vfunc_54(int *result);
extern "C" int igPsx2Semaphore_GetMeta(void);
extern "C" void igPsx2Semaphore_ReleaseDefaults(igPsx2Semaphore *self);
extern "C" int igPsx2Media_GetMeta(void);
extern "C" igMetaObject *igPsx2LongTimer_GetMeta(void);
extern "C" int igPsx2IopRpcConnection_GetMeta(void);
extern "C" int igPsx2CallStackTracer_GetMeta(void);
extern "C" int igStandardQueue_GetMeta(void);
extern "C" igMetaObject *igStackMemoryPool_GetMeta(void);
extern "C" unsigned char igStackMemoryPool_IsAlchemyMemory(igStackMemoryPool *self);
extern "C" void igStackMemoryPool_SetMaxSize(int *status_out);
extern "C" int Gap__Core__igStackMemoryPool__vfunc_83(void);
extern "C" int igProgramFile_GetMeta(void);
extern "C" int igElfFile_GetMeta(void);
extern "C" int igSymbolTable_GetMeta(void);
extern "C" int igStringTable_GetMeta(void);
extern "C" igMetaObject *igStringRefList_GetMeta(void);
extern "C" igMetaObject *igQueue_GetMeta(void);
extern "C" int igPluginHelper_GetMeta(void);
extern "C" int igNamedObjectInfo_GetMeta(void);
extern "C" igMetaObject *igMetaFieldInfo_GetMeta(void);
extern "C" int igMemoryPoolInfo_GetMeta(void);
extern "C" igMetaObject *igMemoryPoolContextInfo_GetMeta(void);
extern "C" int MemoryContext_GetMeta(void);
extern "C" int igMemoryDictionary_GetMeta(void);
extern "C" int igLocationTable_GetMeta(void);
extern "C" int igEventTracker_GetMeta(void);
extern "C" int igDriverDatabase_GetMeta(void);
extern "C" int igCallStackTracer_GetMeta(void);
extern "C" igMetaObject *igCallStackTable_GetMeta(void);
extern "C" int igMemoryDescriptorMetaField_GetMeta(void);
extern "C" int igMemoryDescriptorMetaField_GetDescriptor(void);
extern "C" int igMallocMemoryPool_GetMeta(void);
extern "C" void igMallocMemoryPool_ReleaseDefaults(igMemoryPoolView *self);
extern "C" void igMallocMemoryPool_Reset(void);
extern "C" void igMallocMemoryPool_SetRawMemory(int *statusOut);
extern "C" int igMallocMemoryPool_IsAlchemyMemory(void);
extern "C" int igMallocMemoryPool_GetRawMemory(void);
extern "C" int igMallocMemoryPool_IsSecondaryAllocator(void);
extern "C" int igArenaMemoryPool_GetMeta(void);
extern "C" int igPageMemoryPool_GetMeta(void);
extern "C" int igAliasMemoryPool_GetMeta(void);
extern "C" int Gap__Core__igAliasMemoryPool__vfunc_83(void);
extern "C" int igContextList_GetMeta(void);
extern "C" igMetaObject *igContextExtInfo_GetMeta(void);
extern "C" igMetaObject *igContextExtInfoList_GetMeta(void);
extern "C" igMetaObject *igContextExtList_GetMeta(void);
extern "C" igMetaObject *igShortListList_GetMeta(void);
extern "C" igMetaObject *igFloatListList_GetMeta(void);
extern "C" igMetaObject *igPointerListList_GetMeta(void);
extern "C" igMetaObject *igMetaObjectList_GetMeta(void);
extern "C" igMetaObject *igMetaObjectListList_GetMeta(void);
extern "C" igMetaObject *igMetaFieldList_GetMeta(void);
extern "C" igMetaObject *igIntListList_GetMeta(void);
extern "C" igMetaObject *igObjectListList_GetMeta(void);
extern "C" igMetaObject *igStringRefListList_GetMeta(void);
extern "C" igMetaObject *igDependencyMetaField_GetMeta(void);
extern "C" int igDependencyMetaField_GetDescriptor(void);
extern "C" int igErrorHandler_GetMeta(void);
extern "C" int igLibraryList_GetMeta(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetMeta(void);
extern "C" igMetaObject *igNamedObjectList_GetMeta(void);
extern "C" int igObjectStringMap_GetMeta(void);
extern "C" int igPluginRepository_GetMeta(void);
extern "C" igMetaObject *igPluginRepositoryList_GetMeta(void);
extern "C" int igStringObj_GetMeta(void);
extern "C" igMetaObject *igStringObjList_GetMeta(void);
extern "C" igMetaObject *igThreadList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetMeta(void);
extern "C" int igContextList_GetElementMeta(void);
extern "C" igMetaObject *igNonRefCountedThreadList_GetElementMeta(void);
extern "C" int igStringRefList_GetElementSize(void);
extern "C" igMetaObject *igContextExtList_GetElementMeta(void);
extern "C" igMetaObject *igContextExtInfoList_GetElementMeta(void);
extern "C" igMetaObject *igMemoryPoolInfoList_GetElementMeta(void);
extern "C" int igPluginRepositoryList_GetElementMeta(void);
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
extern "C" igMetaObject *g_igThreadManager_metaObject;
extern "C" igMetaObject *igThreadManager_GetMetaObject(void);
extern "C" igMetaObject *g_igThread_metaObject;
extern "C" igMetaObject *igThread_GetMetaObject(void);
extern "C" igMetaObject *g_igNonRefCountedThreadList_metaObject;
extern "C" igMetaObject *igNonRefCountedThreadList_GetMetaObject(void);
extern "C" int g_igNonRefCountedThreadList_vtable[4];
extern "C" igMetaObject *g_igThreadList_metaObject;
extern "C" igMetaObject *igThreadList_GetMetaObject(void);
extern "C" int g_igThreadList_vtable[4];
extern "C" igMetaObject *g_igSymbolTable_metaObject;
extern "C" igMetaObject *igSymbolTable_GetMetaObject(void);
extern "C" int g_igSymbolTable_vtable[4];
/* igSmartPointer's deleting destructor as retail emitted it out of line, one copy per pointee
 * class (igSmartPointer_igUnsignedIntListNoClean_Destruct, igSmartPointer_igStringTable_Destruct, igSmartPointer_igCallStackTracer_Destruct, igSmartPointer_igLibraryList_Destruct, igSmartPointer_igShortListList_Destruct); the deletion flag
 * is a signed short. */
extern "C" igSmartPointer<igObject> *igSmartPointer_igUnsignedIntListNoClean_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_igStringTable_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" int text_size[4];
extern "C" igMetaObject *g_igStringTable_metaObject;
extern "C" igMetaObject *igStringTable_GetMetaObject(void);
extern "C" int g_igStringTable_vtable[4];
extern "C" igObject **igSmartPointer_igCharListNoClean_Destruct(igObject **arg0, short arg1);
extern "C" igMetaObject *g_igStringRefList_metaObject;
extern "C" igMetaObject *igStringRefList_GetMetaObject(void);
extern "C" int g_igStringRefList_vtable[4];
extern "C" igMetaObject *igStringObjList_GetMetaObject(void);
extern "C" int g_igStringObjList_vtable[4];
extern "C" igMetaObject *igStringObj_GetMetaObject(void);
extern "C" int g_igStringObj_vtable[4];
extern "C" int text_shallowCopyMethod[4];
extern "C" int text_destruct[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igCallStackTracer_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void **igSmartPointer_igSemaphore_Destruct(igObject **self, short flag);
extern "C" igMetaObject *g_igQueue_metaObject;
extern "C" igMetaObject *igQueue_GetMetaObject(void);
extern "C" igMetaObject *g_igPluginHelper_metaObject;
extern "C" igMetaObject *igPluginHelper_GetMetaObject(void);
extern "C" int g_igPluginHelper_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_igLibraryList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_igPluginRepositoryList_metaObject;
extern "C" igMetaObject *igPluginRepositoryList_GetMetaObject(void);
extern "C" int g_igPluginRepositoryList_vtable[4];
extern "C" igMetaObject *g_igPluginRepository_metaObject;
extern "C" igMetaObject *igPluginRepository_GetMetaObject(void);
extern "C" int g_igPluginRepository_vtable[4];
extern "C" igMetaObject *g_igPluginRepository_metaObject;
extern "C" igMetaObject *g_igObjectStringMap_metaObject;
extern "C" igMetaObject *igObjectStringMap_GetMetaObject(void);
extern "C" int g_igObjectStringMap_vtable[4];
extern "C" char data[];
extern "C" int text_ref[4];
extern "C" igMetaObject *igNamedObjectInfo_GetMetaObject(void);
extern "C" int g_igNamedObjectInfo_vtable[4];
extern "C" igMetaObject *igNamedObjectList_GetMetaObject(void);
extern "C" int g_igNamedObjectList_vtable[4];
extern "C" igMetaObject *igMetaObject_GetMetaObject(void);
extern "C" int g_igMetaObject_vtable[4];
extern "C" igMetaObject *g_igMetaFieldInfo_metaObject;
extern "C" igMetaObject *igMetaFieldInfo_GetMetaObject(void);
extern "C" int g_igMetaFieldInfo_vtable[4];
extern "C" int text_resetMethod[4];
extern "C" igMetaObject *g_igMemoryPoolInfoList_metaObject;
extern "C" igMetaObject *igMemoryPoolInfoList_GetMetaObject(void);
extern "C" int g_igMemoryPoolInfoList_vtable[4];
extern "C" igMetaObject *g_igMemoryPoolInfo_metaObject;
extern "C" igMetaObject *igMemoryPoolInfo_GetMetaObject(void);
extern "C" int g_igMemoryPoolInfo_vtable[4];
extern "C" igMetaObject *g_igMemoryPoolContextInfo_metaObject;
extern "C" igMetaObject *igMemoryPoolContextInfo_GetMetaObject(void);
extern "C" int g_igMemoryPoolContextInfo_vtable[4];
extern "C" igMetaObject *g_igMemoryPool_metaObject;
extern "C" igMetaObject *igMemoryPool_GetMetaObject(void);
extern "C" igMetaObject *g_igMemoryDictionary_metaObject;
extern "C" igMetaObject *igMemoryDictionary_GetMetaObject(void);
extern "C" int g_igMemoryDictionary_vtable[4];
extern "C" igMetaObject *g_igLongTimer_metaObject;
extern "C" igMetaObject *igLongTimer_GetMetaObject(void);
extern "C" igMetaObject *g_igLocationTable_metaObject;
extern "C" igMetaObject *igLocationTable_GetMetaObject(void);
extern "C" int g_igLocationTable_vtable[4];
extern "C" igMetaObject *g_igLibraryLoader_metaObject;
extern "C" igMetaObject *igLibraryLoader_GetMetaObject(void);
extern "C" igMetaObject *g_igLibraryList_metaObject;
extern "C" igMetaObject *igLibraryList_GetMetaObject(void);
extern "C" int g_igLibraryList_vtable[4];
extern "C" igMetaObject *g_igLibrary_metaObject;
extern "C" igMetaObject *igLibrary_GetMetaObject(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igShortListList_Destruct(igSmartPointer<igObject> *self,int delete_storage);

extern "C" int g_igObjectListBase_vtable[4];
extern "C" int g_igDirectoryBase_vtable[4];
extern "C" int text_capacity[4];
extern "C" int text_count[4];
extern "C" igMetaObject *g_igEventTracker_metaObject;
extern "C" igMetaObject *igEventTracker_GetMetaObject(void);
extern "C" int g_igEventTracker_vtable[4];
extern "C" igMetaObject *g_igErrorHandler_metaObject;
extern "C" igMetaObject *igErrorHandler_GetMetaObject(void);
struct igErrorHandler : public igObject { };
extern "C" int g_igErrorHandler_vtable[4];
extern "C" igMetaObject *g_igDriverDatabase_metaObject;
extern "C" igMetaObject *igDriverDatabase_GetMetaObject(void);
extern "C" int g_igDriverDatabase_vtable[4];
extern "C" igMetaObject *igDependencyOrderedList_GetMetaObject(void);
extern "C" igMetaObject *g_igDependencyMetaField_metaObject;
extern "C" igMetaObject *igDependencyMetaField_GetMetaObject(void);
extern "C" int g_igDependencyMetaField_vtable[4];
extern "C" igMetaObject *g_igStringRefListList_metaObject;
extern "C" igMetaObject *igStringRefListList_GetMetaObject(void);
extern "C" int g_igStringRefListList_vtable[4];
extern "C" igMetaObject *g_igObjectListList_metaObject;
extern "C" igMetaObject *igObjectListList_GetMetaObject(void);
extern "C" int g_igObjectListList_vtable[4];
extern "C" igMetaObject *g_igIntListList_metaObject;
extern "C" igMetaObject *igIntListList_GetMetaObject(void);
extern "C" int g_igIntListList_vtable[4];
extern "C" igMetaObject *g_igMetaFieldList_metaObject;
extern "C" igMetaObject *igMetaFieldList_GetMetaObject(void);
extern "C" int g_igMetaFieldList_vtable[4];
extern "C" igMetaObject *g_igMetaObjectListList_metaObject;
extern "C" igMetaObject *igMetaObjectListList_GetMetaObject(void);
extern "C" int g_igMetaObjectListList_vtable[4];
extern "C" igMetaObject *g_igMetaObjectList_metaObject;
extern "C" igMetaObject *igMetaObjectList_GetMetaObject(void);
extern "C" int g_igMetaObjectList_vtable[4];
extern "C" igMetaObject *g_igPointerListList_metaObject;
extern "C" igMetaObject *igPointerListList_GetMetaObject(void);
extern "C" int g_igPointerListList_vtable[4];
extern "C" igMetaObject *g_igFloatListList_metaObject;
extern "C" igMetaObject *igFloatListList_GetMetaObject(void);
extern "C" int g_igFloatListList_vtable[4];
extern "C" igMetaObject *g_igShortListList_metaObject;
extern "C" igMetaObject *igShortListList_GetMetaObject(void);
extern "C" int g_igShortListList_vtable[4];
extern "C" igMetaObject *g_igContextExtList_metaObject;
extern "C" igMetaObject *igContextExtList_GetMetaObject(void);
extern "C" int g_igContextExtList_vtable[4];
extern "C" igMetaObject *g_igContextExtInfoList_metaObject;
extern "C" igMetaObject *igContextExtInfoList_GetMetaObject(void);
extern "C" int g_igContextExtInfoList_vtable[4];
extern "C" igMetaObject *g_igContextExtInfo_metaObject;
extern "C" igMetaObject *igContextExtInfo_GetMetaObject(void);
extern "C" int g_igContextExtInfo_vtable[4];
extern "C" igMetaObject *igContextExt_GetMetaObject(void);
extern "C" igMetaObject *g_igContextList_metaObject;
extern "C" igMetaObject *igContextList_GetMetaObject(void);
extern "C" int g_igContextList_vtable[4];
extern "C" igMetaObject *g_igCallStackTracer_metaObject;
extern "C" igMetaObject *igCallStackTracer_GetMetaObject(void);
extern "C" int g_igCallStackTracer_vtable[4];
extern "C" igMetaObject *g_igCallStackTable_metaObject;
extern "C" igMetaObject *igCallStackTable_GetMetaObject(void);
extern "C" int g_igCallStackTable_vtable[4];
/* Class factory of igAliasMemoryPool. Once the object system is running it registers the class and
 * creates the pool through its metaobject on `allocator`. During bootstrap, before the object
 * system exists, it allocates the 184-byte pool by hand, constructs it, and then runs InitDefaults and
 * userConstruct(0) on it. Those calls are not guarded against a failed allocation. */
class igAliasMemoryPoolView;
extern "C" igAliasMemoryPoolView *igAliasMemoryPool_Create(void *allocator);
extern "C" igMetaObject *g_igAliasMemoryPool_metaObject;
extern "C" igMetaObject *igAliasMemoryPool_GetMetaObject(void);
extern "C" int g_igAliasMemoryPool_vtable[4];
extern "C" igMetaObject *g_igPageMemoryPool_metaObject;
extern "C" igMetaObject *igPageMemoryPool_GetMetaObject(void);
extern "C" int g_igPageMemoryPool_vtable[4];
extern "C" igMetaObject *g_igArenaMemoryPool_metaObject;
extern "C" igMetaObject *igArenaMemoryPool_GetMetaObject(void);
extern "C" int g_igArenaMemoryPool_vtable[4];
extern "C" igMetaObject *g_igStackMemoryPool_metaObject;
extern "C" igMetaObject *igStackMemoryPool_GetMetaObject(void);
extern "C" int g_igStackMemoryPool_vtable[4];
extern "C" igMetaObject *g_igMallocMemoryPool_metaObject;
extern "C" igMetaObject *igMallocMemoryPool_GetMetaObject(void);
extern "C" int g_igMallocMemoryPool_vtable[4];
extern "C" igMetaObject *g_igMemoryDescriptorMetaField_metaObject;
extern "C" igMetaObject *igMemoryDescriptorMetaField_GetMetaObject(void);
extern "C" int g_igMemoryDescriptorMetaField_vtable[4];
extern "C" igMetaObject *g_igProgramFile_metaObject;
extern "C" igMetaObject *igProgramFile_GetMetaObject(void);
extern "C" int g_igProgramFile_vtable[4];
extern "C" igMetaObject *g_igElfFile_metaObject;
extern "C" igMetaObject *igElfFile_GetMetaObject(void);
extern "C" int g_igElfFile_vtable[4];
extern "C" igMetaObject *g_igStandardQueue_metaObject;
extern "C" igMetaObject *igStandardQueue_GetMetaObject(void);
extern "C" int g_igStandardQueue_vtable[4];
extern "C" int g_igQueue_vtable[4];
extern "C" void *igQueue_Destroy(igQueue *arg0, short arg1);
extern "C" igMetaObject *g_igPsx2ThreadManager_metaObject;
extern "C" igMetaObject *igPsx2ThreadManager_GetMetaObject(void);
extern "C" int g_igPsx2ThreadManager_vtable[4];
extern "C" igMetaObject *g_igPsx2Thread_metaObject;
extern "C" igMetaObject *igPsx2Thread_GetMetaObject(void);
extern "C" int g_igPsx2Thread_vtable[4];
extern "C" igMetaObject *g_igPsx2Semaphore_metaObject;
extern "C" igMetaObject *igPsx2Semaphore_GetMetaObject(void);
extern "C" int g_igPsx2Semaphore_vtable[4];
extern "C" igMetaObject *g_igPsx2Media_metaObject;
extern "C" igMetaObject *igPsx2Media_GetMetaObject(void);
extern "C" int g_igPsx2Media_vtable[4];
extern "C" igMetaObject *g_igPsx2LongTimer_metaObject;
extern "C" igMetaObject *igPsx2LongTimer_GetMetaObject(void);
extern "C" int g_igPsx2LongTimer_vtable[4];
extern "C" igMetaObject *g_igPsx2IopRpcConnection_metaObject;
extern "C" igMetaObject *igPsx2IopRpcConnection_GetMetaObject(void);
extern "C" int g_igPsx2IopRpcConnection_vtable[4];
extern "C" igMetaObject *g_igPsx2CallStackTracer_metaObject;
extern "C" igMetaObject *igPsx2CallStackTracer_GetMetaObject(void);
extern "C" int g_igPsx2CallStackTracer_vtable[4];
extern "C" int g_igAliasMemoryPool_vtable[4];
extern "C" void igAliasMemoryPool_AssignAlias(igAliasMemoryPool *self, igMemoryPoolView *alias);
extern "C" void igAliasMemoryPool_Activate(igAliasMemoryPool *self);
extern "C" void igAliasMemoryPool_Reset(igAliasMemoryPool *self);
/* igAliasMemoryPool's virtuals: the igMemoryPool table, then the alias pool's own slots 97-101
 * (GetAliasedMemoryPool, AssignAlias, GetLocalNetAllocatedHigh, GetLocalNetAllocatedWithOverheadHigh, ManageAllocation). */
class igAliasMemoryPoolView : public igMemoryPoolView {
public:
    virtual int GetAliasedMemoryPool();                                                      /* slot 97, byte 396: the aliased pool */
    virtual void AssignAlias(igMemoryPool *aliased);                               /* slot 98, byte 400 */
    virtual int GetLocalNetAllocatedHigh();                                      /* slot 99, byte 404 */
    virtual int GetLocalNetAllocatedWithOverheadHigh();                          /* slot 100, byte 408 */
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
extern "C" long long igAliasMemoryPool_GetLocalNetAllocatedHigh(igAliasMemoryPool *arg0);
extern "C" long long igAliasMemoryPool_GetLocalNetAllocatedWithOverheadHigh(igAliasMemoryPool *arg0);
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
extern "C" int igAliasMemoryPool_AllocateFromSystem(igAliasMemoryPool *arg0, int arg1);
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
    virtual igResult OpenWithMode(int mode);                                            /* +92: open in a mode number */
    virtual void CloseHandle();                                                        /* +96: close the handle */
    /* Names the file and opens it in a mode string ("r", "wb", ...); nonzero (the file) on success. */
    virtual int Open(const char *name, const char *mode);                           /* +100 */
    virtual void Close();                                                           /* +104 */
    virtual int Read(void *buffer, int size, int count);                            /* +108 */
    virtual void ReadAsync(void *buffer, int count, int (*done)(int, int), int context); /* +112 */
    virtual int Write(const void *buffer, int size, int count);                     /* +116 */
    virtual void vfunc_30();
    virtual void Print(const char *format, ...);                                    /* +124: printf */
    virtual void Flush();                                                        /* +128: flush */
    virtual int GetChar();                                                         /* +132: getc */
    virtual void UngetChar(); virtual void PutChar(); virtual void GetString(); virtual void PutString();
    virtual int Seek(int offset, int whence);                                       /* +152: -1 on failure */
    virtual int Tell();                                                         /* +156: tell */
    virtual void SkipToChar();
    /* Prefixes the device of the file's folder (cdrom0:, host0:) and keeps the result as _completeFilename. */
    virtual char *MakeCompleteFilename(const char *name);                           /* +164 */
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
class igEventTrackerView;
extern "C" void igObjectSystem_Startup(ObjectSystemView *self);
#include "dw4/core/igStringRef.h"
#include "dw4/core/igDirectoryList.h"
#include "dw4/core/igIntListList.h"
#include "dw4/core/igFloatListList.h"
extern "C" void igObjectSystem_InitPaths(ObjectSystemView *arg0);
extern "C" void igObjectSystem_PreExit(ObjectSystemView *arg0);
extern "C" void igObjectSystem_Exit(ObjectSystemView *arg0);
class MemoryContext;
extern "C" void igObjectSystem_Shutdown(ObjectSystemView *arg0);
extern "C" void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta);
/* Looks a registered metaobject up by class name. The object system's metadata registry (the
 * pointer list at +24) is searched on the `_name` field of igMetaObject; an inactive object system
 * (flag byte at +0 clear) finds nothing. */

extern "C" igMetaField *g_igMetaObjectNameField;
extern "C" int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className);
extern "C" void igObjectSystem_AddRegistrationCallback(ObjectSystemView *arg0, int (*arg1)(int));
extern "C" void igObjectSystem_SetMemoryEventFormat(ObjectSystemView *objectSystem, char *format);
extern "C" void igObjectSystem_SetMarkerEventFormat(ObjectSystemView *objectSystem, char *format);
extern "C" void igObjectSystem_SetNotificationEventFormat(ObjectSystemView *objectSystem, char *format);
extern "C" CallbackArray *igArray_Construct(CallbackArray *array);
extern "C" CallbackArray *igArray_Destruct(CallbackArray *array,short deleteFlag);
extern "C" int igArray_Append(CallbackArray *array,int item);
extern "C" int percent_s[4];
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
    virtual igCompoundMetaField *GetDescriptor();                                    /* +92 */
    virtual void SetValue(int object, int value);                               /* +96 */
    virtual int GetSize();                                                      /* +100 */
    virtual unsigned int GetElementSize();                                            /* +104 */
    virtual int GetAlignment();                                                     /* +108 */
    virtual int SetToDefault(int object);                                       /* +112 */
    virtual int IgnoreReset(int object);                                        /* +116 */
    virtual int CopyDefaultToValue(int object);                                 /* +120 */
    virtual int ConstructValue(int object);                                     /* +124 */
    virtual int DestructValue(int object);                                      /* +128 */
    virtual void ZeroValue(int object);                                         /* +132 */
    virtual void ClearValue(int object);                                        /* +136 */
    virtual int SetDefault(const void *value);                                          /* +140 */
    virtual void DeepCopy(int dest, int source);                                /* +144 */
    virtual int CopyReference(int dest, int source);                                 /* +148 */
    virtual void ShallowCopy(int dest, int source);                             /* +152 */
    virtual int ResetValue(int dest, int source);                                 /* +156 */
    virtual void IgnoreCopy(int dest, int source);                                /* +160 */
    virtual void Print(int object, int a2, int a3);                             /* +164 */
    virtual int ReleaseElements(int object, int a2, int a3);                    /* +168 */
    virtual int Write(int object, int file);                                    /* +172 */
    virtual int Compare(int a, int b);                                         /* +176 */
    virtual int IsAlikeExactly(int a, int b);                                         /* +180 */
    virtual int IsAlikeDeep(int a, int b);                                      /* +184 */
    virtual int IsAlikeShallow(int a, int b);                                   /* +188 */
    virtual int IsAlikeIgnore(int a, int b);                                         /* +192 */
    virtual int GetRawFieldMemSize(int object);                                           /* +196 */
    virtual int WriteRawFieldMem(int dest, int source, int a3, unsigned char swap); /* +200 */
    virtual int ReadRawFieldMem(int dest, int source, int a3, unsigned char swap); /* +204 */
    virtual int SwapBytes(void *buffer, int count);                               /* +208 */
    virtual void SwapValue(int object);                                         /* +212 */
    RESERVED(52); RESERVED(53);                                                 /* +216, +220 */
    virtual int ValueFromString(int object, int text, int directory);                  /* +224 */
    virtual igStringRef ValueToString(int object, int directory);                    /* +228 */
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
extern "C" void igCallStackTable_RebuildHashIndex(igCallStackTableView *table, int hashCapacity);
extern "C" int g_callStackRootAddress[4];
/* igCallStackTracer (reflected layout in dw4/support/reflected.h; an igUnsignedIntListNoClean of return
 * addresses) with the virtuals its callers use. */
class igCallStackTracerView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned int *CaptureCallStack(int maxDepth, int skip); virtual int HasSymbols();
    virtual void d24();
    virtual igResult LookupAddress(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual igResult FormatLocation(int addr, char *buf, int offset, char *name, int line, int format, long long output, long long outputSize);
    virtual void PreExit();
    virtual void Exit();
    int _count;
    int _capacity;
    unsigned int *_data;
};
extern "C" void igCallStackTracer_FormatAddress(igResult *result, igCallStackTracerView *self, int addr, int format, long long output, long long outputSize);
extern "C" igResult igThread_SetPriority(igPsx2Thread *self, int priority);
extern "C" igResult igCallStackTracer_LookupAddress(void *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" int percent_d_7[4];
/* igContextExt's own virtual functions past igObject's (slot n at vtable byte offset 4 * n): IsSupported
 * decides whether the extension can serve the context, SetContext binds it. ABI view only: never instantiated. */
class igContextExtView {
public:
    RESERVED(0); RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19); RESERVED(20);
    RESERVED(21); RESERVED(22); RESERVED(23); RESERVED(24); RESERVED(25);
    virtual int IsSupported(igVisualContext *context);                          /* +112 */
    virtual int SetContext(igVisualContext *context);                           /* +116 */
};
extern "C" void List_AppendBytes(igDataList *l, int cnt, int src, int sz);
typedef int (*Cmp)(int *, void *);
struct DependencyPair { void *a; void *b; };
struct igDependencyOrderedListView {
    int _vtable; unsigned int _refCount;
    igTDataList<igObject *> *_objectList;
    igTDataList<DependencyPair> *_dependencies;
    igTDataList<igObject *> *_order;
    int _checkPoints;
    unsigned char _hasCircularDependencies;
};
extern "C" void igDependencyOrderedList_Rebuild(igDependencyOrderedListView *owner);
class igDirEntryView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18();
    virtual igDirEntryView *CloneViaMetadata(int copyMode);                     /* vfunc_21 */
    virtual void d20();
    virtual void SetRef(int ref);
    virtual void RetainRef(int ref);
    virtual void d25();
    virtual igDirEntryView *Resolve(Gap::Core::igIGBFile *file);                /* vfunc_26 */
    virtual void SetReferenceIndex(int index);                                  /* vfunc_27 */
    virtual void ReleaseSharedRef(int ref);
    virtual void SetMemoryPool(int pool);                                       /* vfunc_29 */
    virtual int MemoryPoolIndex();                                              /* vfunc_30 */
    virtual void ReadFinished(Gap::Core::igIGBFile *file);                      /* vfunc_31 */
    virtual void ResolveEntry(Gap::Core::igIGBFile *file);
    virtual void ResolveRefOld(Gap::Core::igIGBFile *file);
    virtual void ResolveRef(Gap::Core::igIGBFile *file);
    virtual void ReadMemory(Gap::Core::igIGBFile *file);
    virtual void RegisterRef(int flag);
    virtual void PostProcess(Gap::Core::igIGBFile *file);
    virtual int PrepareWrite(Gap::Core::igIGBFile *file);
    virtual int ComputeWriteSize(Gap::Core::igIGBFile *file);
    virtual void WriteObject(Gap::Core::igIGBFile *file);
    virtual int WriteMemory(Gap::Core::igIGBFile *file);
    virtual void d42();
    virtual int ResolveDirectory(int loadFunction);
    int _name; int _index; int _resolveMethod; int _refType; int _ref;
};
class igExternalInfoEntryView : public igDirEntryView { public:
    char *_key; int _directoryIndex; char *_infoName;
    void setDirectoryIndex(int index) { _directoryIndex = index; }
    void setKey(char *key) { char *interned = (char *)StringPool_Intern(InternedStrings::get(), key); releaseString(_key); _key = interned; }
    void setInfoName(char *name) { char *interned = (char *)StringPool_Intern(InternedStrings::get(), name); releaseString(_infoName); _infoName = interned; }
};
/* Removes the object at `index`, releasing it, and clears the vacated last slot. */
static inline void objectListRemoveRetained(igTDataList<igObject *> *list, int index) {
    igObject *o = list->_data[index];
    IG_OBJECT_RELEASE(o);
    List_RemoveWordAt((igDataList *)list, index);
    list->_data[list->_count] = 0;
}
extern "C" int igDirectory_ReplaceReference(Gap::Core::igDirectory *self, const igSmartPointer<igVirtualObject> &field, const igSmartPointer<igVirtualObject> &value);
extern "C" int igDirectory_AddObjectCallback(int arg0, igMetaFieldView *arg1, Gap::Core::igDirectory *arg2);
/* An object list's insert: the list takes its own reference, then copies the pointer word in. */
template <class T> static inline void insertObject(igDataList *list, int index, T *object) {
    RetainedWord<T> word(object);
    List_InsertWords(list, index, 1, &word);
}
extern "C" void igDriverDatabase_InitDefaults(igDriverDatabase *database);
extern "C" int igDriverDatabase_GetSubPropertyValue(igDriverDatabase *arg0, int arg1, int arg2);

/* A node of the parsed driver database (vtable g_ConfigNode_vtable); section and settings nodes extend it.
 * Slot 0 is the deleting destructor. */
class ConfigNode { public: int kind; virtual void Delete(int flags); };
/* ConfigNode as data: the kind, then the vtable word its destructor resets. */
struct ConfigNodeData { int kind; int vtable; };
extern "C" void igDriverDatabase_ProcessConfigNode(igDriverDatabase *self, ConfigNode *node, igRegistry *registry, int section);
extern "C" int g_ConfigNode_vtable[4];
/* The character variable is an int; a char would add a sign extension. */
extern "C" void igDriverDatabase_LoadDatabaseFile(igDriverDatabase *self, Gap::Core::igFile *file);
extern "C" bool igDriverDatabase_ReadLineFromFile(void *a0, Gap::Core::igFile *s, char *buf, int n);
class ConfigNode;
extern "C" ConfigNode *igDriverDatabase_ParseNode(igDriverDatabase *self);
extern "C" int igDriverDatabase_ResolveSettingsSection(igDriverDatabase *self, igStringObj *sectionName, igRegistry *registry, int fallback);
extern "C" bool igDriverDatabase_ParseIdentifier(igDriverDatabase *arg0, int *arg1);
extern "C" int igDriverDatabase_ParsePropertyBlock(igDriverDatabase *self, struct ConfigSectionNode *out);
extern "C" int igDriverDatabase_ParseParenthesizedIdentifier(igDriverDatabase *parser, int *out);
extern "C" int g_ConfigPair_vtable[4];
class ConfigPair { public: igStringObj *key; igStringObj *value; virtual void Delete(int flags); };
/* ConfigPair as data: the key and value strings, then the vtable word. */
struct ConfigPairData { igStringObj *key; igStringObj *value; int vtable; };
extern "C" ConfigPair *igDriverDatabase_Setting_Destruct(ConfigPair *self, int delete_storage);
extern "C" int g_ConfigSettingsNode_vtable[4];
struct ConfigSettingsNode { int kind; int vtable; igTDataList<ConfigPair *> *entries; igStringObj *name; };
extern "C" int igDriverDatabase_ParseSettingsBlock(igDriverDatabase *self, ConfigSettingsNode *out);
extern "C" void igDriverDatabase_ApplySettings(igDriverDatabase *self, igTDataList<ConfigPair *> *entries, igRegistry *registry, int section);
extern "C" void *igDriverDatabase_SettingsNode_Destruct(ConfigSettingsNode *arg0, long long arg1);
extern "C" int g_ConfigSectionNode_vtable[4];
struct ConfigSectionNode { int kind; int vtable; int id; igStringObj *name; igTDataList<ConfigNode *> *children; int compareMode; igStringObj *selector; };
extern "C" void *igDriverDatabase_PropertyNode_Destruct(ConfigSectionNode *arg0, long long arg1);
class igEventTrackerView;
extern "C" void igEventTracker_SetThreadSafe(igEventTrackerView *self, int open);
class igEventTrackerView;
extern "C" void igEventTracker_SetEventTag(igEventTrackerView *tracker, int tag);
struct LocationRecord { int address; int name; int offset; int file; int line; };
/* igLocationTable (reflected layout in dw4/support/reflected.h) with the virtuals its callers use. */
class igLocationTableView : public igVirtualObject { public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int FindLocationIndex(int address);
    virtual igResult GetLocation(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void d26();
    virtual void AddLocation(int addr, char *buf, int offset, char *name, int line);
    virtual unsigned int Hash(unsigned int address);
    virtual int InsertHash(int address, int index);
    virtual void Rehash(int capacity);
    int _capacity; int _hashCapacity; igTDataList<unsigned int> *_locations; igTDataList<int> *_hashIndex; int _symbolNames; int _sourceFileNames;
};
/* One igEventTracker event (148 bytes): cleared by igEventTracker_ClearEvent, built by igEventTracker_InitMemoryEvent/igEventTracker_InitMarkerEvent,
 * stored by igEventTrackerView::AddEvent and decoded back by igEventTrackerView::ReadEvent. slotStates holds a 2-bit state for each of the
 * 16 words in slots (igEventTracker_FindFreeEventDataSlot..igEventTracker_GetEventDataUnsigned3). */
enum igEventType {
    kEventTypeAny, kMemoryAllocation, kMemoryDetach, kMemoryDeallocation, kMemoryRead, kMemoryWrite, kObjectAllocation,
    kObjectDetach, kObjectDeallocation, kObjectRead, kObjectWrite, kMemberRead, kMemberWrite, kMarker, kNotification, kCustom
};
struct EventRecord { int type; int index; int address; int val; int alignment; int markerType; int markerValue; char *markerName; int notificationType; int notificationCode; char *notificationText; char *group; char *str; char *memberName; char *annotation; char *eventTag; char *poolName; int sourceFile; int line; int *callStack; unsigned int slotStates; int slots[16]; int getType() const { return type; } int getVal() const { return val; } const char *getSourceFile() const { return (const char *)sourceFile; } int *getCallStack() const { return callStack; } int getAddress() const { return address; } int getIndex() const { return index; } int getAlignment() const { return alignment; } int getLine() const { return line; } int getNotificationCode() const { return notificationCode; } };
/* igEventTracker (reflected layout in dw4/support/reflected.h) with the virtuals its callers use. */
class igEventTrackerView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void Initialize();
    virtual void Shutdown();  /* closes what Initialize began */
    virtual void d23();
    virtual void AddEvent(EventRecord *record, int mode);
    virtual igResult ReadEvent(int offset, EventRecord *record);
    virtual igResult ReadEventType(int offset, int *type);
    virtual igResult ReadEventKey(int offset, int *value);
    virtual igResult ReadEventValue(int offset, int *size);
    virtual int FindIndex(int address);
    virtual void GetStatistics(int, int, int *total, int *counts, int *, int *, int *, int *, int *, int *, int *, int, int, int *, int, int);  /* leak summary */
    virtual void GetStatisticsByName(int, int, int name, int *, int *, int *, int *);  /* per-name sizes */
    virtual int GetNextEventOffset(int offset);
    virtual int GetLeakCount();
    virtual void d34(); virtual void d35();
    virtual void FormatEvent(EventRecord *record, char *buffer, int size);
    virtual igResult FormatAddress(int addr, char *format, char *output, int outputSize);
    virtual igResult ResolveAddress(int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
    virtual void PrintEvent(int offset);
    virtual void d40();
    virtual void PrintLeaks();
    virtual igResult WriteFile(char *name);
    virtual void ResolveAllCallStackSymbols();
    virtual int PreExit();
    virtual int Exit();
    virtual int GetHashBucketIndex(int hash);
    virtual void InsertHashIndex(int value, int offset);
    virtual void RebuildHashIndex(int capacity);
    Gap::Core::igSemaphore *_lock;
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
extern "C" void igEventTracker_GetStatistics(igEventTrackerView *self, int first, int last, int *eventCount, int *typeCounts, int *outstandingCount, unsigned int *allocatedBytes, unsigned int *freedBytes, unsigned int *netBytes, unsigned int *peakNetBytes, unsigned int *largestAllocation, unsigned int *netAtMarkerA, int markerA, int markerAOccurrence, unsigned int *netAtMarkerB, int markerB, int markerBOccurrence);
extern "C" void igEventTracker_GetStatisticsByName(igEventTrackerView *arg0, int arg1, int arg2, int arg3, int *arg4, int *arg5, int *arg6, int *arg7);
extern "C" int igEventTracker_FindIndex(igEventTrackerView *self, int value);
extern "C" char text_main[];
extern "C" void igEventTracker_IgnoreEventsInFunction(igEventTrackerView *self, char *wanted);
extern "C" unsigned int igEventTracker_GetHashBucketIndex(igEventTracker *self, unsigned int hash);
extern "C" void igEventTracker_InsertHashIndex(igEventTrackerView *self, int arg1, int arg2);
extern "C" void igEventTracker_RebuildHashIndex(igEventTrackerView *self, int n);
extern "C" int igEventTracker_GetMarkerTypeName(igEventTrackerView *tracker, int type);
extern "C" int igEventTracker_GetNotificationTypeName(igEventTrackerView *tracker, int type);
extern "C" igResult igEventTracker_FormatAddress(igEventTrackerView *self, int addr, int format, long long output, long long outputSize);
/* The result type has a constructor, so the return writes straight through the saved hidden
 * pointer. */
extern "C" igResult igEventTracker_ResolveAddress(igEventTrackerView *self, int addr, char *buf, int size, int *offset, char *name, int nameSize, int *line);
extern "C" int igEventTracker_GetLeakCount(igEventTrackerView *self);
extern "C" int igEventTracker_FindNextLeak(igEventTrackerView *self, int *cursor);
extern "C" void igEventTracker_PrintLeaks(igEventTrackerView *self);
extern "C" void igEventTracker_PrintEvent(igEventTrackerView *self, int offset);
extern "C" void igEventTracker_PrintAllEvents(igEventTrackerView *self);
extern "C" igResult igEventTracker_WriteFile(igEventTrackerView *self, int arg2);
extern "C" void igEventTracker_ResolveAllCallStackSymbols(igEventTrackerView *self);
extern "C" void igEventTracker_PreExit(igEventTrackerView *self);
extern "C" void igEventTracker_Exit(igEventTrackerView *self);
extern "C" void Gap__Core__igEventTracker__resetFields(igEventTrackerView *self);
extern "C" int igEventTracker_GetEventDataType(EventRecord *record, int slot);
/* igMemoryPoolInfo's own slots, after igInfo's two: 23 ReadFromRegistry, 24 UserRegistryLoad, 25 Print.
 * ABI view only: never instantiated. */
class igMemoryPoolInfoView : public Gap::Core::igInfo { public:
    virtual igResult ReadFromRegistry(igRegistry *ini, char *section);
    virtual igResult UserRegistryLoad(igRegistry *ini, int index);
    virtual void Print();
};
class igLongTimerView;
extern "C" int g_igIGBFile_inheritedFieldCountFill[4];
extern "C" int g_igIGBFile_persistentFieldCountFill[4];
/* One metaobject record of an .igb file's metaobject table. */
struct MetaTableRecord { int nameSize; int majorVersion; int minorVersion; int fieldCount; int parentIndex; int persistCount; };
/* A metaobject's parent reference as a one-word key passed by reference: the key is stored to the
 * stack and reloaded from there. */
struct MetaTableKey { int v; };
#include "dw4/attrs/igObjectList.h"
/* An object list's sorted insert: FUN_00142bb0 finds the position by the pointer's value. */
template <class T> static inline void insertObjectSorted(igObjectList *list, T *object) {
    RetainedWord<T> word(object);
    List_InsertWords((igDataList *)list, FUN_00142bb0(list, (igObject *const *)&word), 1, &word);
}
/* The 48-byte .igb header: the table sizes and counts, the magic cookie, then the version word whose
 * top bits carry the file's flags. */
struct IgbFileHeader {
    int entryBufferSize; int entryCount; int metaObjectBufferSize; int metaObjectCount; int objectBufferSize; int objectCount;
    int memoryRefBufferSize; int memoryRefCount; int metaFieldBufferSize; int metaFieldCount; int magicCookie; int magicVersion;
};
/* The registered meta-field descriptors Gap::Core::igMetaField::getMetaFieldTypes returns; each entry's getMeta is its meta object. */
static inline igObjectDispatchView *registeredMetaField(Gap::Core::__internalObjectList *fields, int index) {
    return (igObjectDispatchView *)fields->get(index);
}
/* An .igb table section header: its byte size, a version word and the entry count. */
struct IgbSectionHeader { int size; int pad; int count; };
struct NameHeader { int size; int count; };
/* ReadFile(path): the Alchemy .igb loader driver. Logs "readFile(%s)", notes the clock, then runs
 * the section readers in file order (header, then the version-dependent tables, then the object
 * sections). A reader that fails sends the loader to its error path igIGBFile_AbortRead. After the last
 * reader the load time is reported once through the assert/log hook; an old-format file that still
 * has external references is reported once through the same hook, which prints the file's name.
 * Each reader result is an unnamed temporary with its own stack word. */
extern "C" void *igIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" void StringPool_DestroyChunks(StringPool *pool);
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

extern "C" void igLocationTable_Rehash(igLocationTableView *arg0, int arg1);
/* igMedia's own virtual functions past igObject's (vfunc_N at vtable byte offset 4 * N); the slot
 * symbols are unnamed (Gap::Core::igPsx2Media::vfunc_NN). ABI view only: never instantiated. */
class igMediaView : public igVirtualObject {
public:
    RESERVED(1); RESERVED(2); RESERVED(3); RESERVED(4); RESERVED(5); RESERVED(6);
    RESERVED(7); RESERVED(8); RESERVED(9); RESERVED(10); RESERVED(11); RESERVED(12); RESERVED(13);
    RESERVED(14); RESERVED(15); RESERVED(16); RESERVED(17); RESERVED(18); RESERVED(19);
    virtual void vfunc_22();
    virtual int AllocateHandle();                                               /* +92 */
    virtual int FreeHandle(int handle);                                         /* +96 */
    virtual igResult Open(int handle, igStringRef path, int mode);              /* +100 */
    virtual int Close(int handle);                                              /* +104 */
    virtual int Write(int handle, const void *buffer, int size);                /* +108 */
    virtual int Read(int handle, void *buffer, int size);                       /* +112 */
    virtual int ReadAsync(int handle, void *buffer, int size, int (*done)(int, int), int context); /* +116 */
    virtual int Seek(int handle, int offset, int whence);                      /* +120 */
    virtual int Tell(int handle);                                               /* +124 */
    virtual int HandlesDevice(const char *path, int prefixLength);              /* +128: nonzero when the path prefix names this device */
};
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
    virtual int ReleasePageTables();                      /* +12 */
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
    virtual int AllocateRange(int address, int size);
    virtual igResult FreeRange(int address, ...); /* size: an int from the page code, a long long from the context dump */
    virtual int GetStackSize();
    virtual void d18();
    virtual int GetPageSize();
    virtual void d20(); virtual void d21(); virtual void d22();
    virtual void GetStatistics(SystemMemoryStatistics *stats);                           /* +100 */
    virtual void d24();
    virtual igResult SetPageState(int state, unsigned int address, int size);                /* +108 */
    virtual int IsRangeFree(unsigned int address, int size);                                /* +112 */
    virtual unsigned int FindFreeRange(int size);                                             /* +116 */
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
    virtual void PrintStatistics();                                                             /* +144 */
    virtual void d35();
    virtual void CollectHardwareRegions(igPointerList *regions);                                       /* +152 */
    virtual void CollectProgramRegions(igPointerList *regions);                          /* +156 */
    virtual void CollectHeapRegions(igPointerList *regions);                             /* +160 */
    virtual void CollectPoolRegions(igPointerList *regions);                                       /* +164 */
    virtual int Sbrk(int delta);                                                     /* +168 */
    virtual igResult ReserveRange(int address, int size);                                    /* +172 */
    virtual void *AllocateTable(unsigned int size);                                           /* +176 */
    virtual void FreeTable(void *block);                                                  /* +180 */
    virtual igResult MarkRange(int address, int size, int set);                          /* +184 */
};
extern "C" SystemAllocator g_systemAllocator;
/* The allocator the memory services use; SystemAllocator_Activate installs g_systemAllocator here when it is empty. */
extern "C" void *Memory_AllocateBufferViaSharedTail(unsigned int size, igMemoryPoolView *pool);
extern "C" void *Memory_AllocateFromPool(int, unsigned int size, igMemoryPoolView *pool);
extern "C" int Memory_Reallocate(void *block, igMemoryPoolView *pool);
extern "C" int igMemoryDictionary_GetCapacity(igMemoryDictionary *self);
extern "C" void igMemoryDictionary_SetCapacity(igMemoryDictionary *self, int capacity);
/* One slot of igMemoryDictionary's open-addressed table: a key, and its value or -1 for a never-used
 * slot, -2 for a removed one. */
struct MemoryDictionaryEntry { int key; int value; };
/* igMemoryDictionary's entry list (an igUnsignedIntListNoClean); its count is in words, two per entry. */
/* igMemoryDictionary (reflected layout in dw4/support/reflected.h) with the virtuals its callers use. */
class igMemoryDictionaryView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int SetCapacity(int); virtual int InitEntries(); virtual int Clear();
    virtual void ResetEntries();
    virtual void d26(); virtual void d27();
    virtual igResult GetValue(int key, int *value);
    virtual igResult Insert(int key, int value);
    virtual igResult Remove(int);
    virtual int HashKey(int key);
    virtual igResult Resize(int capacity);
    int _capacity;
    int _count;
    igTDataList<MemoryDictionaryEntry> *_memoryEntries;
    int _cachedIndex;
};
extern "C" void igMemoryDictionary_InitEntries(igMemoryDictionaryView *self);
extern "C" void igMemoryDictionary_Clear(igMemoryDictionaryView *self);
extern "C" int igMemoryDictionary_IsEnabled(igMemoryDictionary *self);
extern "C" int g_igMemoryDictionary_resetFill[4];
extern "C" void igMemoryDictionary_ResetEntries(igMemoryDictionaryView *self);
extern "C" int igMemoryDictionary_GetCount(igMemoryDictionary *self);
extern "C" void igMemoryDictionary_GetValue(igResult *result, igMemoryDictionaryView *self, int key, int *value);
extern "C" igResult igMemoryDictionary_Insert(igMemoryDictionaryView *self, int key, int value);
extern "C" igResult igMemoryDictionary_Remove(igMemoryDictionaryView *self, int key);
extern "C" unsigned int igMemoryDictionary_HashKey(igMemoryDictionary *self, unsigned int key);
extern "C" char g_igMemoryDictionary_resizeFill[];
extern "C" int igMemoryDictionary_Resize(igResult *result, igMemoryDictionaryView *self, int capacity);
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
class igMemoryDirEntryView : public igDirEntryView { public:
    int _memSize; int _memTypeSize; int _memType; int _memTypeIndex; int _alignmentTypeIndex; int _memoryPoolHandle;
    unsigned char _refCounted;
};
/* igMemoryFile: an igFile reading a registered memory buffer (_buffer, _iBufferSize bytes) instead of
 * a device; the file name is looked up in the igMemoryFileEntry list on open. */
class igMemoryFileView : public igFileView { public:
    unsigned char _bIsOpen;
    char *_buffer;
    int _iBufferSize;
    int _iSeekPosition;
};
extern "C" int g_igMemoryPool_vtable[4];
extern "C" igResult Memory_LookupAllocation(int arg1, int *arg2);
/* The struct result is returned through the hidden pointer (a0 is the caller's return slot, this
 * is in a1), so the function returns the struct by value. */
extern "C" igResult Memory_RegisterAllocation(int arg1, igMemoryPoolView *arg2);
extern "C" igResult Memory_UnregisterAllocation(int arg1, igMemoryPoolView *pool);
extern "C" char DAT_00580000[];
/* Allocator registry index lookup and encoded-index publication. An allocator is identified in
 * saved data by "registry index << 1 | which-registry": the primary list gives an even code, the
 * secondary list an odd one. */
/* Growable pointer list of allocators: data, signed count, capacity (same layout as igMemoryPoolInfoList). */
struct AllocatorRegistry {igMemoryPoolView **data;int count;int capacity;};
extern "C" int igMemoryPoolInfoList_IndexOf(AllocatorRegistry *list,igMemoryPoolView *allocator);
extern "C" int igAllocator_EncodeIndex(igMemoryPoolView *allocator);
extern "C" void igMemoryPool_PrintStatistics(igMemoryPool *arg0, char *arg1);
extern "C" void *igMemoryPool_AllocateFromSystem(igMemoryPoolView *self, unsigned int size);
extern "C" void igMemoryPool_SetEventTracker(int dummy0, igObject *arg1);
extern "C" int igMemoryPool_ReallocateTracked(igMemoryPoolView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0);
extern "C" void igMemoryPool_GangAllocTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10);
extern "C" void igMemoryPool_GangAllocAlignedTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18);
extern "C" void Memory_InitializeAllocatorRegistries(igObject *rootAllocator);
extern "C" void igMemoryPool_UpdateStatistics(igMemoryPool *pool, long long arg1, long long arg2, int arg3);
extern "C" void igMemoryPool_ResetStatistics(igMemoryPool *arg0);
extern "C" void igMemoryPool_UpdateLocalStatistics(igMemoryPool *arg0, int arg1, int arg2, int arg3);
extern "C" char *g_memoryContextNames[46];
struct ContextRecord {
    void *allocator;       /* retained by the slot setter */
    char name[128];        /* 127 characters copied in plus an explicit terminator */
    igMemoryPoolInfo *descriptor;
    unsigned storageFlags, flags;
};
/* igMemoryPoolContextInfo (reflected layout in dw4/support/reflected.h) with the virtuals its callers use. */
class igMemoryPoolContextInfoView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual igResult ReadFromRegistry(igRegistry *ini, char *section);
    virtual igResult ReadFromRegistrySection(igRegistry *ini, int index);
    int _name;
    int _directory;
    unsigned char _resolveState;
    int _memoryPoolInfos;
};
/* The memory context: 46 records, each an allocator slot with its name and descriptor. Its vtable
 * is g_MemoryContext_vtable; the slots past 20 are its own. */
class MemoryContext : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual igMemoryPoolView *GetAllocatorBySelector(int index);
    virtual int GetAllocatorByName(int name);
    virtual void SetAllocator(int index, igObject *allocator);
    virtual int GetPoolInfo(int);
    virtual int GetPoolName(void *pool);
    virtual void d26();
    virtual int FindPoolIndexByName(int);
    virtual int GetPoolIndexByName(int handleName);                     /* record index for a pool handle name */
    virtual int IndexOfAllocator(void *pool);                 /* record index holding `pool`, -1 if none */
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual igResult SetPoolInfos(int, int);
    virtual igResult FillMemoryPoolInfo(int index, igMemoryPoolInfo *info);
    virtual igResult SetPoolInfo(int index, igMemoryPoolInfo *info, int build);
    virtual void SetFlags(unsigned flags);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void CreateDefaultPools();
    virtual void OnStartupComplete();
    virtual int Shutdown();
    virtual void InitializeRecordNames();
    virtual igResult Initialize();
    virtual int RemoveAllAllocators();
    virtual igResult CreateDefaultContextInfo(int config, char *name);
    virtual int ReleaseContextInfo();
    virtual igResult vfunc_50();                                /* slot 48: FUN_002f5cc0 */
    virtual igResult BuildAllocator(int index, int flag);
    virtual igResult BuildAndAttachEventTracker(int index);
    virtual void RemoveAllocator(int index);
    virtual void ConfigureEventTracking();
    virtual int ShutdownEventTrackers();
    virtual void SaveEventTrackers();
    virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60();
    virtual void d61(); virtual void d62();
    virtual void PrintPoolStatistics(int, int);
    virtual void PrintStatistics(int);
    virtual void Destruct(int flags);
    int usedRecords;
    unsigned flags;
    igMemoryPoolContextInfoView *contextInfo;
    ContextRecord records[46];
};
extern "C" char g_MemoryContext_vtable[];
extern "C" MemoryContext *igMemoryPoolContextInfo_Construct(MemoryContext *self);
extern "C" void *igMemoryPoolContextInfo_Destruct(MemoryContext *self, long long deleteFlags);
extern "C" void igMemoryPoolContextInfo_Activate(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_SetEventClassName(MemoryContext *self, int arg1);
extern "C" int igMemoryPoolContextInfo_GetAllocatorBySelector(MemoryContext *arg0, int arg1);
extern "C" void *igMemoryPoolContextInfo_GetMemoryPoolByName(MemoryContext *self, const char *name);
extern "C" void igMemoryPoolContextInfo_SetAllocator(MemoryContext *self, int index, igObject *value);
extern "C" int *igMemoryPoolContextInfo_GetPoolName(MemoryContext *arg0, void *pool);
extern "C" igResult igMemoryPoolContextInfo_ReadConfiguration(MemoryContext *self, int config, int section);
extern "C" igResult igMemoryPoolContextInfo_LoadFromRegistry(MemoryContext *self, int config, int index);
extern "C" igResult igMemoryPoolContextInfo_GetPoolInfos(MemoryContext *self, int file);
extern "C" igResult igMemoryPoolContextInfo_SetPoolInfos(MemoryContext *self, int file, int arg);
typedef void StringToken;
/* a token points at the interned text; its header precedes it */
extern "C" void igMemoryPoolContextInfo_FillMemoryPoolInfo(int *result, MemoryContext *context, int index, igMemoryPoolInfo *info);
extern "C" igResult igMemoryPoolContextInfo_SetPoolInfo(MemoryContext *self, int index, igMemoryPoolInfo *desc, int build);
extern "C" void igMemoryPoolContextInfo_DeactivatePools(MemoryContext *arg0);
extern "C" char *g_presetPoolClassName;
extern "C" void igMemoryPoolContextInfo_CreateDefaultPools(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_InitializeRecordNames(MemoryContext *self);
extern "C" igResult igMemoryPoolContextInfo_Initialize(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_RemoveAllAllocators(MemoryContext *arg0);
extern "C" void igMemoryPoolContextInfo_CreateDefaultContextInfo(int *out, MemoryContext *self, int config, char *name);
extern "C" void MemoryContext_BuildAllocator(int *out, igMemoryPoolContextInfo *arg1, int idx, int flag);
extern "C" void MemoryContext_BuildAndAttachEventTracker(igResult *out, MemoryContext *self, int idx);
typedef igObject Obj6;
extern "C" void igMemoryPoolContextInfo_ConfigureEventTracking(MemoryContext *self);
enum LeakKind { LeakKindFirst = 0, LeakKindCount = 32 };
extern "C" void igMemoryPoolContextInfo_ShutdownEventTrackers(MemoryContext *self);
extern "C" void igMemoryPoolContextInfo_SaveEventTrackers(MemoryContext *arg0);
extern "C" igResult igMemoryPoolContextInfo_UpdateAllocatorsOfKind(MemoryContext *self, unsigned int kind, int free);
extern "C" void igMemoryPoolContextInfo_SetEventTag(MemoryContext *arg0, int arg1);
extern "C" void igMemoryPoolContextInfo_GetEventTag(MemoryContext *self, int arg1, int *out, int n);
extern "C" void igMemoryPoolContextInfo_SetEventTags(MemoryContext *self, int *paths, int n);
extern "C" void igMemoryPoolContextInfo_GetEventClassName(MemoryContext *slots, int arg1, int *out, int n);
extern "C" void igMemoryPoolContextInfo_SetEventClassNames(MemoryContext *arg0, int *arg1, int arg2);
extern "C" void igMemoryPoolContextInfo_SendMarker(MemoryContext *arg0, int arg1, int arg2, int arg3);
extern "C" void igMemoryPoolContextInfo_PrintPoolStatistics(MemoryContext *arg0, char *arg1, igMemoryPoolView *arg2);
extern "C" char newline_2[];
extern "C" void igMemoryPoolContextInfo_PrintStatistics(MemoryContext *arg0, int *arg1);
extern "C" int DAT_00586ffc[4];
extern "C" igResult igMemoryPoolContextInfo_PushContext(void *arg1);
extern "C" igObject *igMemoryPoolContextInfo_PopContext(void);
extern "C" void igMemoryPoolContextInfo_RemoveMemoryPoolInfo(igMemoryPoolContextInfo *info, igMemoryPoolInfo *poolInfo);
extern "C" igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByName(igMemoryPoolContextInfo *arg0, int arg1);
extern "C" igMemoryPoolInfo *igMemoryPoolContextInfo_FindMemoryPoolInfoByHandle(igMemoryPoolContextInfo *arg0, char *arg1);
extern "C" igResult igMemoryPoolContextInfo_ReadFromRegistry(igMemoryPoolContextInfoView *self, igRegistry *ini, char *section);
extern "C" igResult igMemoryPoolContextInfo_ReadFromRegistrySection(igMemoryPoolContextInfo *self, igRegistry *ini, int index);
extern "C" void igMemoryPoolContextInfo_Print(igMemoryPoolContextInfoView *self);
extern "C" igResult igMemoryPoolInfo_LoadFromRegistry(igMemoryPoolInfoView *self, igRegistry *ini, char *section);
extern "C" void igMemoryPoolInfo_TrimCapacity(igMemoryPoolInfo *arg0);
/* The growable pointer list shared by the allocator registries (igMemoryPoolInfoList): data,
 * signed count, capacity. Initial capacity 64 entries, growing four at a time. The allocator used
 * for the storage is the object system's bootstrap pool. */
extern "C" AllocatorRegistry *igMemoryPoolInfoList_Init(AllocatorRegistry *list);
extern "C" AllocatorRegistry *igMemoryPoolInfoList_Release(AllocatorRegistry *list,int deleteFlag);
extern "C" void igMemoryPoolInfoList_Append(AllocatorRegistry *list,igMemoryPoolView *entry);
/* Allocates the backing array of a memory-reference field. The element descriptor (_memType)
 * supplies the element size and alignment through its virtual methods; the allocator is asked for
 * count * size bytes at that alignment and the pointer is published into the owning object at the
 * field's _offset. */
extern "C" igMemoryRefMetaField *igMemoryRefMetaField_Construct(igMemoryRefMetaField *self, int extra1);
/* The parameter is const so the list pointer is reloaded per iteration, the loop is tested at the
 * bottom via goto, and the locals are declared in the order a4, n, i. */
typedef struct MetaEnumView { char pad[4]; int _refCount; char *name; igTDataList<char *> *names; igTDataList<int> *values; } MetaEnumView;
extern "C" void igMetaField_CopyByTechnique(igMetaFieldView *arg0, int arg1, int arg2, int arg3);
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

/* A memory pool's virtuals: slot 31 is igMemoryPool's IsActive() (returns _isActive);
 * slot 32 is EnableAllocationLock(enable) (igArenaMemoryPool and igAliasMemoryPool create
 * or drop the pool's _allocationLock semaphore); slot 52 allocates. The callers take IsActive's
 * result at full width: declared unsigned char or bool, the `== 0` test in igMemoryPoolContextInfo_Activate gains the
 * `andi 0xff` of a byte-returning callee (156 bytes against retail's 152). */
extern "C" int g_igMetaObject_vtable[4];
extern "C" void *igMetaObject_Construct(igMetaObject *meta, int extra1);
extern "C" igMetaObject *igMetaObject_Init(igMetaObject *meta);
extern "C" void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source);
extern "C" void igMetaObject_ReleaseLists(igMetaObject *meta);
extern "C" int igMetaObject_CreateInstanceWithPool(igMetaObject *arg0, igMemoryPoolView *arg1);
extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent);
extern "C" void igMetaObject_SetName(igMetaObject *meta, int name);
extern "C" void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field);
extern "C" void igMetaObject_FinalizeFieldLayout(igMetaObject *arg0);
extern "C" void igMetaObject_AddField(igMetaObject *self, void *object);
extern "C" int igMetaObject_AddToMetaObjectList(igTDataList<igMetaObject *> *list, igMetaObject *object);
extern "C" void igMetaObject_AssignTypeId(igMetaObject *meta);
extern "C" igResult igMetaObject_CopyVTable(igMetaObject *meta, igMemoryPoolView *pool);
/* Name-or-default is a ?: expression, not an if with an empty then-arm. */
extern "C" void igNamedObjectInfo_FindObjectReference(igNamedObjectInfo *self, int file, igNamedObject *object);
extern "C" igNamedObject *igNamedObjectInfo_GetFieldValueByName(igNamedObjectInfo *self, const char *name);
extern "C" int igObjectList_FindByIntField(igTDataList<int> *list, igMetaField *field, int value);
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
extern "C" int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, Gap::Core::igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap);
/* An object record in an .igb object section: its meta-object index and byte size, then (old format)
 * the count of persistent fields written. */
struct FieldRecordHead { int kind; int size; int fieldCount; };
extern "C" int igObject_ReadFields(igObjectDispatchView *object, FieldRecordHead *head, Gap::Core::igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap);
extern "C" int igObject_ReadPersistentFields(igObjectDispatchView *object, FieldRecordHead *head, Gap::Core::igDirectory *dir, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap);
/* An igObjectList of igObjectDirEntry, or of such lists (an igIGBFile's _entryPool, one per type meta). */
static inline igObjectDirEntry *objectDirEntryAt(const igObjectList *list, int index) { return ((igObjectDirEntry *const *)list->_data)[index]; }
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
extern "C" void *igObjectRefMetaField_Construct(igObjectRefMetaField *self, int extra1);
typedef igTDataList<igObject *> FieldList;
extern "C" void igReport_SetOutputFile(Gap::Core::igFile *arg0);
extern "C" void igReport_SetErrorFile(Gap::Core::igFile *arg0);
extern "C" void igPluginHelper_AddRepositoryFromConfig(igPluginHelper *self, int name, const char *path);
/* igPluginHelper::_libraryLoader; the helper's destructor hands it each loaded igLibrary in turn. */
class igLibraryLoaderView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual int UnloadLibrary(igLibrary **library);
};
extern "C" void Gap__Core__igPluginHelper__userDestruct(igPluginHelper *self);
struct Args { igResult (*fn)(int); igStandardQueueView *queue; };
extern "C" int igPluginHelper_ThreadLoop(Args *args);
extern "C" int igStandardQueue_StopServiceThreads(igStandardQueueView *queue);
extern "C" void *igStringMetaField_Construct(igStringMetaField *self, int extra1);
extern "C" void *igUnsignedIntMetaField_Construct(igMetaField *self, int extra1);
extern "C" char DAT_004d3d11[16];
/* igResource (reflected.h) with its asynchronous-loading fields: the queue the loader thread
 * serves and the thread. */

extern "C" void igDirectory_ConvertObjectsOfType(igDirectory *directory, const char *fromName, const char *toName);
static inline igObjectRefMetaField *AsObjectRefMetaField(void *p) {
    if (p != 0 && ((Gap::Core::igObject *)p)->isOfType((igMetaObject *)((void *)Gap::Core::igObjectRefMetaField::getClassMeta())) != 0) { return (igObjectRefMetaField *)p; }
    return 0;
}
static inline void *AsObjectList(void *p) {
    if (p != 0 && ((Gap::Core::igObject *)p)->isOfType((igMetaObject *)((void *)Gap::Core::igObjectList::getClassMeta())) != 0) { return p; }
    return 0;
}
extern "C" void igStringObj_SetN(igStringObj *arg0, int arg1, int arg2);
/* An igStringObj's text: its buffer, or the shared empty text when it has none. */
static inline char *igStringObj_Text(igStringObj *s) { return (char *)s->_buffer == 0 ? g_stringObjEmptyText : (char *)s->_buffer; }
extern "C" bool igStringObj_ParseBool(igStringObj *o, char *out);
extern "C" void igStringObj_RemovePathFilename(igStringObj *p);
extern "C" void igStringObj_Split(igStringObj *src, long long delim, igTDataList<char *> *list);
extern "C" void igStringObj_Trim(igStringObj *self);
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
    virtual unsigned int Hash(char *s);
    virtual int Insert(char *s, int offset);
    virtual void SetHashing(int enable);
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
struct SymbolRecord { int name; int address; unsigned int size; int path; };
class igSymbolTableView { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int GetSymbolCount();                                     /* slot 21: the number of symbols */
    virtual void d22();
    virtual igResult GetSymbol(int, int, int, int, int, int, int);
    virtual int FindSymbolIndex(unsigned int address);
    virtual igResult GetSymbolAtAddress(int addr, char *buf, int size, int *base, int *other, char *name, int nameSize, int *line); /* slot 25: the symbol at addr */
    virtual void d26();
    virtual void AddSymbol(const char *name, void *address, unsigned int size, int flags);
    virtual int HashAddress(int address);
    virtual int InsertHashEntry(int address, int size, int index);
    virtual void RebuildHashIndex(int capacity);
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
extern "C" void igSymbolTable_RebuildHashIndex(igSymbolTableView *self, int n);
extern "C" void igPsx2ThreadManager_InitDefaults(igPsx2ThreadManagerView *self);
extern "C" int percent_u[4];
extern "C" int text_0x_08x[4];
extern "C" int (*g_arenaTriggerHandler[4])(void *, int, int, int, int, int, int);
extern "C" void igArenaMemoryPool_CheckTriggerEvent(igArenaMemoryPool *arg0, int arg1, int arg2, int arg3);
struct TaggedBlockHeader;
struct ArenaState;
extern "C" void igArenaMemoryPool_CheckChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
extern "C" void igArenaMemoryPool_CheckFreeChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
extern "C" void igArenaMemoryPool_CheckInUseChunk(igArenaMemoryPoolView *self, TaggedBlockHeader *h);
extern "C" void igArenaMemoryPool_CheckBlock(igArenaMemoryPoolView *self, TaggedBlockHeader *h, int requested);
extern "C" void igArenaMemoryPool_UpdateBlockList(igArenaMemoryPool *o, unsigned int lo, int len);
extern "C" int text_space[];
extern "C" void igArenaMemoryPool_CheckHeapLocked(int *arg0, igArenaMemoryPoolView *arg1);
extern "C" igResult igArenaMemoryPool_CheckHeap(igArenaMemoryPoolView *self);
extern "C" void igArenaMemoryPool_CheckMallocState(igArenaMemoryPoolView *self);
extern "C" void igArenaMemoryPool_PrintStatistics(igArenaMemoryPoolView *self, char *title);
extern "C" void igArenaMemoryPool_CollectMemoryRegions(igArenaMemoryPoolView *self, igDataList *list);
extern "C" void igArenaMemoryPool_VerifyHeap(int *status, igArenaMemoryPoolView *self);
extern "C" igResult igArenaMemoryPool_CheckHeapBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end);
extern "C" bool igArenaMemoryPool_Trim(igArenaMemoryPoolView *self, int pad);
/* A free chunk's link pair sits past its header, at +4 or +12 as the header is short or `big`;
 * `big == 0 ? 4 : 12` gives the movn form. */
extern "C" void igArenaMemoryPool_RemoveFreeChunksInRange(int *status, igArenaMemoryPoolView *self, unsigned int start, unsigned int end);
/* igMemoryPoolInfo's string getters, as the pools' configure functions read them: this build takes
 * the release set of the options, checking and messages strings. */
static inline const char *igMemoryPoolInfo_source(const igMemoryPoolInfo *info) { return (const char *)info->_source; }
static inline const char *igMemoryPoolInfo_options(const igMemoryPoolInfo *info) { return (const char *)info->_releaseOptions; }
static inline const char *igMemoryPoolInfo_checking(const igMemoryPoolInfo *info) { return (const char *)info->_releaseChecking; }
static inline const char *igMemoryPoolInfo_messages(const igMemoryPoolInfo *info) { return (const char *)info->_releaseMessages; }
extern "C" igResult igArenaMemoryPool_Configure(igArenaMemoryPool *pool, igMemoryPoolInfo *info);
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
/* A bin of the arena: a chunk header that only anchors a free list, with room after it for the two
 * links in either header form. */
struct ArenaBin {
    TaggedBlockHeader header;
    int linkRoom[2];
};
/* The arena's 0x814-byte state record, dlmalloc's malloc_state: the fast-bin size limit with two
 * flag bits, the fast bins, the top chunk and the last remainder, 96 bins that are each a chunk
 * header with its two links, the bin map and the tuning values (bit 0 of the flags at 2016 marks
 * the system memory contiguous and makes the chunk checks test the used address range). Then the
 * list of system blocks it has taken (count / 2 peaks in maxBlockPairs, their bytes sum in
 * systemBytes), the raw memory it was given and the address range its system blocks cover. */
struct ArenaState {
    unsigned int maxFast;
    TaggedBlockHeader *fastBins[10];
    TaggedBlockHeader *top;
    TaggedBlockHeader *lastRemainder;
    ArenaBin bins[96];
    unsigned int binMap[4];
    unsigned int trimThreshold;
    int topPad;
    unsigned int mmapThreshold;
    int mmapCount;
    int mmapLimit;
    int mmapPeak;
    unsigned int pageSize;
    int flags;
    int *blocks; int blockCapacity; int blockCount; int maxBlockPairs;
    int rawMemory; char _pad2040[4]; int sbrkedMem; int maxSbrkedMem; char _pad2052[4]; int systemBytes;
    unsigned int lowestAddress; unsigned int highestAddress;
};
/* igArenaMemoryPool's own slots (97 on) after the shared igMemoryPool table. */
class igArenaMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97();
    virtual unsigned long long GetLocalNetAllocatedWithOverheadHigh();                                      /* slot 98, byte 400 */
    virtual void d99();
    virtual igResult CheckHeapLocked();                                                /* slot 100, byte 408 */
    virtual igResult VerifyHeap();                                                /* slot 101, byte 412 */
    virtual void *MemoryOperation(void *block, int size, unsigned int alignment); /* slot 102, byte 416 */
    virtual unsigned int SystemAllocate(int address, int size);                       /* slot 103, byte 420 */
    virtual igResult SystemFree(char *address, int size);                         /* slot 104, byte 424 */
    virtual void d105(); virtual void d106();
    virtual char *GetLowestAddress();                                            /* slot 107, byte 436: vfunc_109 */
    virtual char *GetHighestAddress();                                           /* slot 108, byte 440: vfunc_110 */
    virtual void UpdateBlockList(char *address, int size);                             /* slot 109, byte 444 */
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
    long long getLocalAllocated() { return _localAllocated; }
    long long getLocalFreed() { return _localFreed; }
    long long getLocalNetAllocated() { return _localNetAllocated; }
    long long getLocalNetAllocatedHigh() { return _localNetAllocatedHigh; }
    long long getLocalAllocatedWithOverhead() { return _localAllocatedWithOverhead; }
    long long getLocalFreedWithOverhead() { return _localFreedWithOverhead; }
    long long getLocalNetAllocatedWithOverhead() { return _localNetAllocatedWithOverhead; }
    long long getLocalNetAllocatedWithOverheadHigh() { return _localNetAllocatedWithOverheadHigh; }
    long long getLocalAllocationCount() { return _localAllocationCount; }
    long long getLocalFreeCount() { return _localFreeCount; }
    long long getLocalNetAllocationCount() { return _localNetAllocationCount; }
    long long getLocalNetAllocationCountHigh() { return _localNetAllocationCountHigh; }
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
static inline void releaseRefObject(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)((long long)(int)object->_refCount << 0x29) >> 0x29) == 0)
            igObject_Destroy(object);
    }
}
extern "C" void igArenaMemoryPool_SetDefaults(igArenaMemoryPoolView *self);
extern "C" void igArenaMemoryPool_Shutdown(igArenaMemoryPoolView *arg0);
extern "C" void *igArenaMemoryPool_Initialize(igArenaMemoryPool *arg0);
extern "C" void *igArenaMemoryPool_Construct(igArenaMemoryPool *arg0, int extra1);
extern "C" void *igArenaMemoryPool_CopyConstruct(igArenaMemoryPool *arg0, int extra1);
extern "C" void igArenaMemoryPool_Free(igArenaMemoryPoolView *self, void *block);
extern "C" void igArenaMemoryPool_SetPoolOptionFlags(igArenaMemoryPool *p, int f);
extern "C" void igArenaMemoryPool_SetEventTracker(igArenaMemoryPool *self, igObject *tracker);
extern "C" void igArenaMemoryPool_TransferAllocation(int *arg0, igArenaMemoryPoolView *arg1, char *arg2, igMemoryPoolView *arg3);
extern "C" void Gap__Core__igArenaMemoryPool__constructFields(igArenaMemoryPoolView *arg0, int arg1);
extern "C" void Gap__Core__igArenaMemoryPool__destructFields(igArenaMemoryPool *self);
extern "C" void Gap__Core__igArenaMemoryPool__resetFields(igArenaMemoryPool *self, int extra1);
extern "C" unsigned int igArenaMemoryPool_SystemAllocate(igArenaMemoryPool *arg0, int arg1, int arg2);
extern "C" void *igArenaMemoryPool_MemoryOperation(igArenaMemoryPoolView *self, char *block, int size, unsigned short alignment);
extern "C" igResult igArenaMemoryPool_SystemFree(void *arg1, int arg2, long long arg3);
class igArenaMemoryPoolView;
extern "C" void igArenaMemoryPool_GetStackSize(igArenaMemoryPoolView *self);
extern "C" {
static void igElfFile_Swap16(unsigned char *arg0);
static void igElfFile_Swap32(unsigned char *arg0);
}
extern "C" void igElfFile_Reset(igElfFile *arg0);
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
    virtual igResult LoadSymbolTable(igSymbolTable *table, int flags);  /* slot 26, byte 112 */
    virtual igResult Demangle(char *mangled, char *out, int size, int flags); /* slot 27, byte 116 */
    virtual void d28();
    virtual void PrintSectionHeaders();                         /* slot 29, byte 124 */
    virtual void PrintSymbols();                                /* slot 30, byte 128 */
    unsigned int refCount; const char *path; Gap::Core::igFile *stream;
};
/* One symbol of the ELF file (Elf32_Sym), with the binding and type values its readers test. */
struct ElfSymbol { int name; unsigned value; int size; unsigned char info; unsigned char other; unsigned short sectionIndex; };
enum { STB_LOCAL = 0, STB_GLOBAL = 1, STB_WEAK = 2, STT_FUNC = 2 };
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
extern "C" igResult igElfFile_LoadSymbols(ElfFileView *self);
extern "C" igResult igElfFile_LoadSymbolTable(ElfFileView *self, igSymbolTableView *table, int functionsOnly);
typedef struct ElfOperatorName { const char *mangled; const char *name; } ElfOperatorName;
extern "C" void igElfFile_PrintHeader(ElfFileView *o);
extern "C" void igElfFile_PrintSectionHeader(ElfFileView *arg0, int arg1, ElfSection *arg2);
extern "C" void igElfFile_PrintSymbols(ElfFileView *arg0);
extern "C" void igElfFile_PrintSymbol(igElfFile *self, int index, ElfSymbol *symbol);
extern "C" igResult igMallocMemoryPool_Configure(igMallocMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igMallocMemoryPool_Activate(igMallocMemoryPool *self);
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
/* igMallocMemoryPool appends slot 99 (MemoryOperation, byte 404) to the igMemoryPool table: the
 * reallocation core behind allocate, reallocate and free. CallocateAligned calls it with only the block and
 * size (a3 is left as it was), so the trailing alignment is spelled variadic. */
class igMallocMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97(); virtual void d98();
    virtual void *MemoryOperation(void *block, unsigned int size, ...);
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
    igSmartPointer<Gap::Core::igSemaphore> _allocationLock;
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
extern "C" void Gap__Core__igMallocMemoryPool__resetFields(igMallocMemoryPool *self, int extra1);
extern "C" void igMallocMemoryPool_SetDefaults(igMallocMemoryPool *self);
extern "C" void *igMallocMemoryPool_Initialize(igMallocMemoryPool *arg0);
extern "C" void *igMallocMemoryPool_CopyConstruct(igMallocMemoryPool *arg0, int extra1);
extern "C" void igMallocMemoryPool_Destruct(igMallocMemoryPool *self);
extern "C" void igMallocMemoryPool_Free(igMallocMemoryPoolView *self, void *block);
extern "C" void igMallocMemoryPool_PrintStatistics(igMallocMemoryPool *self, char *title);
extern "C" void igMallocMemoryPool_SetEventTracker(igMallocMemoryPool *self, igObject *tracker);
extern "C" void igMallocMemoryPool_TransferAllocation(int *arg0, igMallocMemoryPool *arg1, char *arg2, igMemoryPoolView *arg3);
extern "C" unsigned char igMallocMemoryPool_IsActive(igMallocMemoryPool *self);
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
#define IS_ARENA_CHUNK(self, p) ((char *)(p) >= (self)->GetLowestAddress() && (char *)(p) < (self)->GetHighestAddress() && chunkPoolIndex(p) == (self)->_poolIndex && payloadSize(p) < 0x20000000 && (char *)(p) + payloadSize(p) <= (self)->GetHighestAddress())
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
/* Whether a chunk was taken straight from the system allocator instead of the arena, which only the
 * 12-byte header can say. */
static inline int chunkIsExternal(TaggedBlockHeader *h) {
    if (h->big == 1) {
        return h->extraMarked;
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
/* The chunk `offset` bytes from `h` (dlmalloc's chunk_at_offset). */
static inline TaggedBlockHeader *chunkAtOffset(TaggedBlockHeader *h, int offset) {
    return (TaggedBlockHeader *)((char *)h + offset);
}
/* The bin after `bin` (dlmalloc's next_bin). */
static inline TaggedBlockHeader *nextBin(TaggedBlockHeader *bin) {
    return (TaggedBlockHeader *)((char *)bin + sizeof(ArenaBin));
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
/* Writes a fresh header for a chunk of the arena `self`, tagged with the pool's index: the 12-byte
 * form when the payload size needs more than 19 bits, the pool index more than 5, or the chunk is
 * system-mapped, else the short form. A caller that knows the chunk's `total` bytes but not its
 * payload passes a size of -1; one that knows the payload may pass a total of 0 to take the
 * header's own size. */
static inline void initChunkHeader(igArenaMemoryPoolView *self, TaggedBlockHeader *h, unsigned int size, unsigned int total, int mapped) {
    unsigned int pool = (unsigned int)self->_poolIndex >> 1;
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
/* An empty in-use header: the two fenceposts that close off a top chunk the arena can no longer
 * extend are written this way. */
static inline void initFencepost(TaggedBlockHeader *h) {
    h->poolLow = 0;
    h->relocated = 0;
    h->marked = 0;
    h->used = 0;
    h->big = 0;
    h->words = 0;
    h->size = 0;
}
/* Set when the answer to a notice asks not to see it again. */
extern "C" void *igArenaMemoryPool_SystemMalloc(igArenaMemoryPoolView *self, unsigned int nb, unsigned int bytes);
extern "C" void *igArenaMemoryPool_Realloc(igArenaMemoryPoolView *self, char *oldmem, unsigned int bytes);
extern "C" void *igArenaMemoryPool_Malloc(igArenaMemoryPoolView *self, unsigned int bytes);
extern "C" void igArenaMemoryPool_FreeChunk(igArenaMemoryPoolView *self, char *mem);
extern "C" void *igArenaMemoryPool_MallocAligned(igArenaMemoryPoolView *self, unsigned int alignment, unsigned int bytes);
extern "C" void igArenaMemoryPool_InitMallocState(igArenaMemoryPoolView *self);
/* Checks the whole heap when it is made and again when it goes out of scope; the allocator entry
 * points make one at integrity level 3. */
struct ArenaHeapCheck {
    igArenaMemoryPoolView *pool;
    ArenaHeapCheck(igArenaMemoryPoolView *p) : pool(p) { pool->VerifyHeap(); }
    ~ArenaHeapCheck() { pool->VerifyHeap(); }
};
extern "C" void *igMallocMemoryPool_AllocateBlock(igMallocMemoryPoolView *self, unsigned size);
extern "C" void igMallocMemoryPool_FreeBlock(igMallocMemoryPoolView *self, unsigned char *p);
struct TaggedTailByte { unsigned char low : 7; unsigned char extended : 1; };
extern "C" void *igMallocMemoryPool_ReallocateBlock(igMallocMemoryPoolView *self, char *p, unsigned size);
extern "C" void *igMallocMemoryPool_MemoryOperation(igMallocMemoryPoolView *self, char *block, int size, unsigned short alignment);
extern "C" void *igMallocMemoryPool_AllocateAlignedBlock(igMallocMemoryPoolView *self, unsigned alignment, unsigned size);
/* Each member of a gang allocation is preceded by this record: its byte distance from the first
 * member's record, and (first member only) the number of members still allocated. */
struct GangRecord {
    unsigned short offset;
    unsigned short count;
    int reserved;
};
extern "C" igResult igMallocMemoryPool_GangAlloc(igMallocMemoryPoolView *self, int count, unsigned int *sizes, void **blocks);
/* chunkBytes in signed arithmetic, used where the gang allocators find a member's guard word. Retail
 * loads a second -4 there instead of reusing the unsigned mask of the header code, which a signed
 * mask gives. */
static inline int signedChunkBytes(TaggedBlockHeader *h) {
    int size = h->size;
    if (h->big == 1) {
        size += h->sizeHigh << 19;
    }
    size = (size + 3) & ~3;
    return size + (h->words + 1) * 4;
}

/* Rounds a byte count up to 8. The signed parameter keeps the caller's own addition apart from the
 * rounding one (retail adds 12 and then 7). */
static inline int roundUp8(int bytes) { return (bytes + 7) & ~7; }

/* Writes the tagged header of a block a pool hands out whole: owner pool, payload size, and the
 * 12-byte form when the size or the pool index does not fit the short one or the block is `external`
 * (taken straight from the system allocator; the header then carries `extraMarked`). `total` is the
 * block's byte count when the caller knows it, else 0 and the header's own bytes are added to the
 * rounded payload. Gang members are `marked`. */
static inline void initBlockHeader(igMemoryPoolView *self, TaggedBlockHeader *h, unsigned size, unsigned total, bool marked, bool external) {
    int id = self->GetPoolIndex() >> 1;
    h->poolLow = id;
    h->relocated = 0;
    h->marked = marked;
    h->used = 0;
    if (size >= 0x80000 || id >= 32 || external) {
        h->sizeHigh = size >> 19;
        h->poolHigh = id >> 5;
        h->big = 1;
        h->extraBig = 1;
        h->extraUsed = 0;
        h->extraMarked = external;
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
    h->size = size;
}

extern "C" igResult igArenaMemoryPool_GangAlloc(igArenaMemoryPoolView *self, int count, unsigned int *sizes, void **blocks);
/* Whether a pool-option bit is set, as 0 or 1. */
static inline int hasPoolOption(int flags, int mask) { return (flags & mask) != 0; }
extern "C" igResult igArenaMemoryPool_TrimArenaBlock(igArenaMemoryPoolView *self, int index, char *cur, char *end);
extern "C" int igArenaMemoryPool_AllocateFromSystem(igArenaMemoryPoolView *self, int size);
extern "C" void *igPageMemoryPool_Initialize(igPageMemoryPool *arg0);
extern "C" void *igPageMemoryPool_CopyConstruct(igPageMemoryPool *self, int extra1);
extern "C" void Gap__Core__igPageMemoryPool__destructFields(igPageMemoryPoolView *self);
extern "C" void Gap__Core__igPageMemoryPool__resetFields(igPageMemoryPool *self, int extra1);
extern "C" igResult igPageMemoryPool_Configure(igPageMemoryPool *self, igMemoryPoolInfo *info);
extern "C" void igPageMemoryPool_Activate(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_Deactivate(igPageMemoryPool *self);
extern "C" unsigned char igPageMemoryPool_IsActive(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetRawMemory(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_IsAlchemyMemory(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_IsSecondaryAllocator(igPageMemoryPool *self);
extern "C" igResult igPageMemoryPool_EnableAllocationLock(igPageMemoryPoolView *self, int enable);
extern "C" long long igPageMemoryPool_GetSize(igPageMemoryPool *self);
extern "C" void igPageMemoryPool_SetMaxSize(int *status, igPageMemoryPool *self, long long maxSize);
extern "C" long long igPageMemoryPool_GetMaxSize(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetAlignment(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_GetElementSize(igPageMemoryPool *self);
extern "C" long long Gap__Core__igPageMemoryPool__vfunc_46(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetLocalNetAllocated(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetLocalNetAllocatedWithOverhead(igPageMemoryPool *self);
extern "C" long long igPageMemoryPool_GetFreeSize(igPageMemoryPool *self);
extern "C" int igPageMemoryPool_AllocateElement(igPageMemoryPool *self);
/* igPageMemoryPool (reflected.h) with its own slots after the igMemoryPool table (slot 100 is
 * MemoryOperation, 101 and 102 test and set page-table bits, 103 is GetBlockSize)
 * and the page tables in its last 128 bytes spelled out: table t
 * covers addresses t << 27, and each of its 2048 words holds the 2-bit states of 16 4KB pages.
 * CallocateAligned calls slot 100 with only the block and size, so the alignment is spelled variadic. */
class igPageMemoryPoolView : public igMemoryPoolView {
public:
    virtual void d97(); virtual void d98(); virtual void d99();
    virtual void *MemoryOperation(void *block, int size, ...);
    virtual int IsPageAllocated(void *block);
    virtual void MarkPages(unsigned int address, int size, int set);
    virtual unsigned GetBlockSize(void *block);
    unsigned int refCount;
    long long localAllocated, localFreed, localNetAllocated, localNetAllocatedHigh;
    long long localAllocatedWithOverhead, localFreedWithOverhead, localNetAllocatedWithOverhead, localNetAllocatedWithOverheadHigh;
    long long localAllocationCount, localFreeCount, localNetAllocationCount, localNetAllocationCountHigh;
    unsigned char updateStatistics, updateGlobalStatistics; char pad106[6];
    unsigned char isActive; char pad113[3];
    igSmartPointer<Gap::Core::igSemaphore> allocationLock;
    unsigned long long maxSize;
    igObject *eventTracker; int poolIndex;
    int messageLevel; int poolOptionFlags; unsigned *pageTables[32];
};
extern "C" void *igPageMemoryPool_MemoryOperation(igPageMemoryPoolView *self, void *block, int size, unsigned short alignment);
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
extern "C" void igProgramFile_Reset(igProgramFile *arg0);
extern "C" igResult igProgramFile_Open(igProgramFile *self, const char *path);
extern "C" void igProgramFile_Load(int *result, ProgramFileView *self, int offset, int size, void **dest);
extern "C" void igProgramFile_PrintHeader(igProgramFile *self);
extern "C" void igProgramFile_PrintSectionHeaders(igProgramFile *self);
extern "C" void igProgramFile_PrintSymbols(igProgramFile *self);
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
class igPsx2ThreadView;
/* igPsx2Thread with the virtuals its callers use: slot 22 waits for another thread to finish, 23
 * sleeps for a number of nanoseconds, 30 tells whether the thread is running, 40 gives the stack
 * alignment, 42 terminates the thread and 48 sets its priority. */
class igPsx2ThreadView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
    virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual igResult Join(igPsx2ThreadView *thread);
    virtual igResult Sleep(int nanoseconds);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual igResult Start();
    virtual void d29();
    virtual int IsRunning();
    virtual igResult SetFunction(int (*function)(...));
    virtual void d32();
    virtual igResult SetArg(int arg);
    virtual void d34(); virtual void d35(); virtual void d36();
    virtual igResult SetStackSize(unsigned int stackSize);
    virtual void d38();
    virtual void d39();
    virtual int GetStackAlignment();
    virtual void d41();
    virtual igResult Terminate();
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual igResult SetPriority(int priority);
    virtual void d49(); virtual void d50();
    virtual void d51(); virtual void d52();
    virtual void AdoptCurrentThread();
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
    Gap::Core::igSemaphore *_threadDoneSema;
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
    virtual void Create();
    virtual void Destroy();
    virtual int IsCreated();
    virtual igResult Insert(int value, bool block);
    virtual igResult Remove(int *value, bool block);
    virtual unsigned int GetCount();
    virtual int IsFull();
    int _serviceThreads;
    Gap::Core::igSemaphore *_insertLock;
    Gap::Core::igSemaphore *_removeLock;
    Gap::Core::igSemaphore *_queueSema;
    unsigned int _capacity;
    unsigned int _insertElement;
    unsigned int _removeElement;
    int *_data;
    unsigned int _maxCapacity;
};
extern "C" igResult igStandardQueue_Insert(igStandardQueueView *self, int val, bool block);
extern "C" int igStandardQueue_IsFull(igStandardQueueView *self);
extern "C" igResult igStandardQueue_Remove(igStandardQueueView *self, int *out, bool block);
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
extern "C" int g_vtable[4];
extern "C" char text_Size[];
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
extern "C" int g_igPsx2CallStackTracer_terminatorAddress[4];
extern "C" int DAT_004c2620;
extern "C" int igPsx2CallStackTracer_CaptureCallStack(igCallStackTracerView *tracer);
extern "C" unsigned int *Gap__Core__igPsx2CallStackTracer__vfunc_31(igCallStackTracerView *tracer);
/* sceGetstat's sce_stat and sceDread's sce_dirent (Sony sifdev.h). */
struct FolderFileStat { int mode; char rest[60]; };
struct FolderEntry { FolderFileStat stat; char name[256]; void *reserved; };
enum { SCE_STM_FMT = 0xF000, SCE_STM_FDIR = 0x1000 };
struct FolderEntryWide { char bytes[328]; };
struct FolderSearchList;
/* igPsx2IopRpcConnection: a bound SIF RPC client, its transfer memory and the semaphore that
 * serialises calls. */
struct igPsx2IopRpcConnectionView : public igObject { sceSifClientData *_sifData; char *_dataMemory; int _sema; };
extern "C" void igPsx2IopRpcConnection_InitDefaults(igPsx2IopRpcConnectionView *self);
extern "C" void igPsx2IopRpcConnection_ReleaseDefaults(igPsx2IopRpcConnectionView *arg0);
typedef struct MediaRpcShared { char pad[8]; char *buffer; } MediaRpcShared;
typedef struct MediaRpcCompletion {
    char pad[12];
    int kind;
    union {
        struct { int headSize; int tailSize; char *head; char *tail; } read;
        struct { void (*callback)(int, int); int thread; int value; int *slot; } wait;
    } request;
} MediaRpcCompletion;
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
    Gap::Core::igSemaphore *_sema;
    MediaIoRequest *_commandBuffer;
    char *_writeBuffer;
    MediaHandlePool *_handlePool;
    igStringObj *_conversionString;
    unsigned char _initialized;
};
extern "C" void Gap__Core__igPsx2Media__constructFields(igPsx2MediaView *arg0, int extra1);
extern "C" void Gap__Core__igPsx2Media__destructFields(igPsx2MediaView *arg0);
extern "C" void Gap__Core__igPsx2Media__resetFields(igPsx2MediaView *self, int extra1);
extern "C" unsigned short igPsx2Media_AllocateHandle(igPsx2MediaView *self);
extern "C" void igPsx2Media_FreeHandle(igPsx2MediaView *media, int handle);
extern "C" char *g_igPsx2Media_deviceNames[];
extern "C" void igPsx2Media_MakeDevicePath(igPsx2MediaView *self, int index, char **path);
extern "C" void igPsx2Media_Open(int *arg0, igPsx2MediaView *arg1, int arg2, int **arg3, unsigned int arg4);
extern "C" void igPsx2Media_Close(igPsx2MediaView *self, int slot);
extern "C" int igPsx2Media_Write(igPsx2MediaView *self, int slot, char *data, int size);
extern "C" int igPsx2Media_SendIoRequest(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int *arg7);
extern "C" int igPsx2Media_Read(igPsx2MediaView *self, int slot, int buffer, int size);
extern "C" void igPsx2Media_ReadAsync(igPsx2MediaView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int igPsx2Media_Seek(igPsx2MediaView *self, int slot, int offset, int whence);
extern "C" int igPsx2Media_Tell(igPsx2MediaView *self, int slot);
extern "C" int igPsx2Semaphore_GetInitialCount(igPsx2Semaphore *self);
extern "C" void igPsx2Semaphore_SetMaximumCount(int *arg0, igPsx2Semaphore *self, int arg2);
extern "C" int igPsx2Semaphore_GetMaximumCount(igPsx2Semaphore *self);
extern "C" int igPsx2Semaphore_GetCount(igPsx2Semaphore *arg0);
extern "C" void igPsx2Semaphore_Create(int *arg0, igPsx2Semaphore *self);
extern "C" void igPsx2Semaphore_IPoll(int *arg0, igPsx2Semaphore *self);
extern "C" int DAT_0052d8b0[4];
extern "C" char _stack_size[];
extern "C" char __code_start__[];
extern "C" char __data_start__[];
extern "C" char __initialized_data_size__[];
extern "C" char __uninitialized_data_start__[];
extern "C" char __uninitialized_data_size__[];
extern "C" char __fast_memory_start__[];
extern "C" char __fast_memory_size__[];
extern "C" void SystemAllocator_GetStatistics(SystemAllocator *self, SystemMemoryStatistics *stats);
extern "C" void SystemAllocator_CollectHardwareRegions(SystemAllocator *self, igDataList *regions);
extern "C" void SystemAllocator_CollectProgramRegions(SystemAllocator *self, igDataList *regions);
extern "C" char text_Memory_Main[];
extern "C" char text_Platform[];
extern "C" char text_Memory_Fast[];
extern "C" char text_Section_Static_Cons[];
extern "C" char text_Section_VTables[];
extern "C" char text_Section_Small_Data[];
#include "dw4/runtime/exception.h"
extern "C" char __small_data_start__[];
extern "C" char __small_data_size__[];
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
extern "C" igResult igPsx2Thread_GetResult(igPsx2ThreadView *self, bool block, int *result);
extern "C" void igPsx2Thread_SetDeferred(int *arg0, igPsx2Thread *self, int arg2);
extern "C" void igPsx2Thread_TestStop(igPsx2ThreadView *self);
extern "C" void igPsx2Thread_Finish(igPsx2ThreadView *thread, int result);
extern "C" igMetaField *g_igPsx2Thread_threadIDField;
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
    virtual long long GetResolution();
    virtual double GetElapsedSeconds();
    virtual long long GetElapsedTime();
    virtual void Start(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void SetResetTime(long long nanoseconds);
    virtual void d32();
    virtual long long GetResetTime();
    virtual void d34();
    virtual long long GetCurrentTime();
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
extern "C" int igStackMemoryPool_IsSecondaryAllocator(igStackMemoryPool *self);
extern "C" void igStringRefList_UserPreWrite(igObjectDispatchView *self);
extern "C" void igStringRefList_TrimCapacity(igStringRefList *l);
extern "C" void igMallocMemoryPool_Deactivate(igMallocMemoryPool *self);
extern "C" int List_LowerBoundWords(igTDataList<unsigned int> *arg0, unsigned int *arg1);

#endif
