/* Frame clock and staged-directory publication. */
#include "dw4/reflected.h"

/* The engine-wide context object. Only the members this update touches are named: the two
 * allocator references that are retargeted before a stage directory is requested. */
struct GlobalContextRecord {
    char unknown0[60];
    igObject *allocator60;
    igObject *allocator64;
};

/* Header in front of every interned string token: owning chunk, then a full 32-bit reference
 * count. */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

/* C++ with exceptions on; the C-ABI names stay unmangled through this block. */
extern "C" {
int FUN_002eb010(int);
void *Memory_GetAllocatorBySelector(int);
int StringChunk_ReleaseHeader(int, StringTokenHeader *);
int StringPool_Construct(int);
int *StringPool_Intern(int, int);
int igObject_Destroy(igObject *);
void *igObject_GetAllocator(beSystem *);
int igStrCmp(const char *, const char *);
extern int ndmw_igb[4];
extern struct GlobalContextRecord *g_globalContext[4];
extern int g_stringPool[4];
/* Allocator selectors resolved through Memory_GetAllocatorBySelector; 0x587110 is the default
 * selector, 0x587108 is the one this update substitutes for the ndmw.igb boot scene. */
extern int g_ndmwAllocatorSelector[4];
extern int g_defaultAllocatorSelector[4];
/* Byte flag at gp-relative 0x554c14: when nonzero the object allocator is used as returned instead
 * of the selector. */
extern unsigned char GPR_00554c14;
/* File-context calls: FUN_003092f0 requests a directory by name, FUN_00309740 tells whether it has
 * loaded, FUN_00309750 releases the request, FUN_00308e00 closes the context; __floatdisf converts
 * the 64-bit frame delta to float. */
float __floatdisf(long long);
int FUN_00308c80(struct GlobalContextRecord *);
igDirectory *FUN_003092f0(struct GlobalContextRecord *, int name);
int FUN_00309740(struct GlobalContextRecord *, int directory);
int igInsightCore_AddInfo(int insight, int info);
int FUN_00309750(struct GlobalContextRecord *, int name);
int FUN_00308e00(struct GlobalContextRecord *);
void Gap__Bec__beSystem__vfunc_27(beSystem *self);
}

/* Once per frame: sample the insight clock into the frame delta, then drive
 * the stage-directory handshake.  A pending _nextStage retargets the
 * context's allocators (the ndmw.igb boot scene gets its own selector),
 * requests the directory for that name and interns an empty string in its
 * place.  Once the directory has finished loading, each of its infos is
 * offered to the insight core and the directory is released.  Finally the
 * first-frame flag is cleared while the system is active. */
void Gap__Bec__beSystem__vfunc_27(beSystem *self) {
    long long now;
    void *ndmwAlloc64;
    void *ndmwAlloc60;
    void *defaultAlloc64;
    void *defaultAlloc60;
    struct GlobalContextRecord *ndmwCtx64;
    struct GlobalContextRecord *ndmwCtx60;
    struct GlobalContextRecord *defaultCtx64;
    struct GlobalContextRecord *defaultCtx60;
    igObject *oldRef;
    igDirectory *directory;
    igObjectList *infos;
    int index;
    int byteOffset;
    int newPool;
    int tokenRefCount;
    int *emptyToken;
    int *oldToken;
    StringTokenHeader *tokenHeader;
    now = ((igInsightCore *)self->_insight)->_worldTime;
    self->_frameTimeL = now - self->_svWorldTimeL;
    self->_frameTimeF = __floatdisf(self->_frameTimeL) / 1.6666667e7f;
    self->_svWorldTimeL = now;
    if (self->_nextStage != 0 || self->_bootDirectory != 0) {
        if (self->_nextStage != 0) {
            if (igStrCmp((const char *)self->_nextStage, (const char *)&ndmw_igb[0]) == 0) {
                ndmwAlloc64 = igObject_GetAllocator(self);
                if (GPR_00554c14 != 0) {
                    ndmwAlloc64 = (void *)(int)ndmwAlloc64;
                } else {
                    ndmwAlloc64 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
                }
                ndmwCtx64 = g_globalContext[0];
                if (ndmwAlloc64 != 0) {
                    ((igObject *)ndmwAlloc64)->_refCount = (int)((igObject *)ndmwAlloc64)->_refCount + 1;
                }
                oldRef = ndmwCtx64->allocator64;
                if (oldRef != 0) {
                    oldRef->_refCount = (int)oldRef->_refCount - 1;
                    if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(oldRef);
                    }
                }
                ndmwCtx64->allocator64 = (igObject *)ndmwAlloc64;
                ndmwAlloc60 = igObject_GetAllocator(self);
                if (GPR_00554c14 != 0) {
                    ndmwAlloc60 = (void *)(int)ndmwAlloc60;
                } else {
                    ndmwAlloc60 = Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
                }
                ndmwCtx60 = g_globalContext[0];
                if (ndmwAlloc60 != 0) {
                    ((igObject *)ndmwAlloc60)->_refCount = (int)((igObject *)ndmwAlloc60)->_refCount + 1;
                }
                oldRef = ndmwCtx60->allocator60;
                if (oldRef != 0) {
                    oldRef->_refCount = (int)oldRef->_refCount - 1;
                    if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(oldRef);
                    }
                }
                ndmwCtx60->allocator60 = (igObject *)ndmwAlloc60;
            } else {
                defaultAlloc64 = igObject_GetAllocator(self);
                if (GPR_00554c14 != 0) {
                    defaultAlloc64 = (void *)(int)defaultAlloc64;
                } else {
                    defaultAlloc64 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                }
                defaultCtx64 = g_globalContext[0];
                if (defaultAlloc64 != 0) {
                    ((igObject *)defaultAlloc64)->_refCount = (int)((igObject *)defaultAlloc64)->_refCount + 1;
                }
                oldRef = defaultCtx64->allocator64;
                if (oldRef != 0) {
                    oldRef->_refCount = (int)oldRef->_refCount - 1;
                    if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(oldRef);
                    }
                }
                defaultCtx64->allocator64 = (igObject *)defaultAlloc64;
                defaultAlloc60 = igObject_GetAllocator(self);
                if (GPR_00554c14 != 0) {
                    defaultAlloc60 = (void *)(int)defaultAlloc60;
                } else {
                    defaultAlloc60 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
                }
                defaultCtx60 = g_globalContext[0];
                if (defaultAlloc60 != 0) {
                    ((igObject *)defaultAlloc60)->_refCount = (int)((igObject *)defaultAlloc60)->_refCount + 1;
                }
                oldRef = defaultCtx60->allocator60;
                if (oldRef != 0) {
                    oldRef->_refCount = (int)oldRef->_refCount - 1;
                    if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(oldRef);
                    }
                }
                defaultCtx60->allocator60 = (igObject *)defaultAlloc60;
            }
            FUN_00308c80(g_globalContext[0]);
            directory = FUN_003092f0(g_globalContext[0], self->_nextStage);
            if (directory != 0)
                directory->_refCount = (int)directory->_refCount + 1;
            oldRef = (igObject *)self->_bootDirectory;
            if (oldRef != 0) {
                oldRef->_refCount = (int)oldRef->_refCount - 1;
                if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(oldRef);
                }
            }
            self->_bootDirectory = (int)directory;
            if (g_stringPool[0] == 0) {
                newPool = FUN_002eb010(0x10);
                if (newPool != 0)
                    newPool = StringPool_Construct(newPool);
                g_stringPool[0] = newPool;
            }
            emptyToken = StringPool_Intern(g_stringPool[0], 0);
            oldToken = (int *)self->_nextStage;
            if (oldToken != 0) {
                tokenHeader = (StringTokenHeader *)oldToken - 1;
                tokenRefCount = tokenHeader->refCount - 1;
                tokenHeader->refCount = tokenRefCount;
                if (tokenRefCount == 0)
                    StringChunk_ReleaseHeader(tokenHeader->owner, tokenHeader);
            }
            self->_nextStage = (int)emptyToken;
        } else {
            /* nextStage is empty here, so this runs only for a directory still in flight */
            if (self->_bootDirectory != 0) {
                if (FUN_00309740(g_globalContext[0], self->_bootDirectory) != 0) {
                    infos = (igObjectList *)((igDirectory *)self->_bootDirectory)->_infoList;
                    index = 0;
                    if (0 < infos->_count) {
                        byteOffset = 0;
                        do {
                            igInsightCore_AddInfo(self->_insight, *(int *)(infos->_data + byteOffset));
                            index += 1;
                            byteOffset += 4;
                        } while (index < infos->_count);
                    }
                    FUN_00309750(g_globalContext[0], ((igDirectory *)self->_bootDirectory)->_name);
                    oldRef = (igObject *)self->_bootDirectory;
                    if (oldRef != 0) {
                        oldRef->_refCount = (int)oldRef->_refCount - 1;
                        if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) ==
                            0) {
                            igObject_Destroy(oldRef);
                        }
                    }
                    self->_bootDirectory = 0;
                    FUN_00308e00(g_globalContext[0]);
                }
            } else {
                /* Unreachable at run time (the entry test needs one of the two fields set),
                 * but present in the retail bytes: clear the stage name and boot directory. */
                if (g_stringPool[0] == 0) {
                    newPool = FUN_002eb010(0x10);
                    if (newPool != 0)
                        newPool = StringPool_Construct(newPool);
                    g_stringPool[0] = newPool;
                }
                emptyToken = StringPool_Intern(g_stringPool[0], 0);
                oldToken = (int *)self->_stageName;
                if (oldToken != 0) {
                    tokenHeader = (StringTokenHeader *)oldToken - 1;
                    tokenRefCount = tokenHeader->refCount - 1;
                    tokenHeader->refCount = tokenRefCount;
                    if (tokenRefCount == 0)
                        StringChunk_ReleaseHeader(tokenHeader->owner, tokenHeader);
                }
                self->_stageName = (int)emptyToken;
                oldRef = (igObject *)self->_bootDirectory;
                if (oldRef != 0) {
                    oldRef->_refCount = (int)oldRef->_refCount - 1;
                    if (((unsigned long long)((long long)(int)oldRef->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(oldRef);
                    }
                }
                self->_bootDirectory = 0;
            }
        }
    }
    if (self->_isActive != 0 && self->_isFirstTime != 0)
        self->_isFirstTime = 0;
}
