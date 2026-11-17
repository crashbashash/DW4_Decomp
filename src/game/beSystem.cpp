#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/beSystem.h"
#include "dw4/core/StringPool.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/support/softfloat.h"
#include <string.h>
#include "dw4/core/igResource.h"

/* Header in front of every interned string token: owning chunk, then a full 32-bit reference
 * count. */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

extern "C" {

extern int ndmw_igb[4];

void beSystem_Activate(beSystem *self, int unusedArg);
void beSystem_Deactivate(beSystem *self, int unusedArg);
void beSystem_Start(beSystem *self);
void beSystem_Stop(void);
int beSystem_AddInfo(void);
void beSystem_RemoveAllInfo(beSystem *self);
void beSystem_Update(beSystem *self);
igMetaObject *beSystem_GetMetaObject_Virtual(void);
}

/* Hands the system to the insight scheduler unless it already holds it. */
void beSystem_Activate(beSystem *self, int unusedArg)
{
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

/* Takes the system back out of the insight scheduler when it holds it. */
void beSystem_Deactivate(beSystem *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

/* Activates the system with the ndmw.igb boot scene queued as the next stage, the resource's
 * per-directory memory pool assignments off and the ndmw allocators behind its memory pools. */
void beSystem_Start(beSystem *self)
{
    int newPool;
    int *stageToken;
    int *oldToken;
    StringTokenHeader *tokenHeader;
    int tokenRefCount;
    void *objectPool;
    igResource *objectResource;
    void *pool;
    igResource *dataResource;
    igResource *temporaryResource;

    self->_isFirstTime = 0;
    self->_isActive = 1;
    if (g_stringPool == 0) {
        newPool = (int)StringPool_Allocate(16);
        if (newPool != 0) {
            newPool = (int)(StringPool_Construct((StringPool *)newPool));
        }
        g_stringPool = (StringPool *)newPool;
    }
    stageToken = (int *)(StringPool_Intern(g_stringPool, (const char *)ndmw_igb));
    oldToken = (int *)self->_nextStage;
    if (oldToken != 0) {
        tokenHeader = (StringTokenHeader *)oldToken - 1;
        tokenRefCount = tokenHeader->refCount - 1;
        tokenHeader->refCount = tokenRefCount;
        if (tokenRefCount == 0) {
            StringChunk_ReleaseHeader((StringChunk *)tokenHeader->owner, tokenHeader);
        }
    }
    self->_nextStage = (int)stageToken;
    igRelease((igObject *)self->_bootDirectory);
    self->_bootDirectory = 0;
    g_resourceLoaderStackSize = 100000;
    ((igResource *)g_globalContext)->_useMemoryPoolAssignmentsState = 0;

    objectPool = igObject_GetAllocator(self);
    objectPool = g_useOwnerAllocator != 0 ? objectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    objectResource = (igResource *)g_globalContext;
    if (objectPool != 0) {
        ((igObject *)objectPool)->_refCount = ((igObject *)objectPool)->_refCount + 1;
    }
    igRelease((igObject *)objectResource->_objectMemoryPool);
    objectResource->_objectMemoryPool = (int)objectPool;

    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    dataResource = (igResource *)g_globalContext;
    if (pool != 0) {
        ((igObject *)pool)->_refCount = ((igObject *)pool)->_refCount + 1;
    }
    igRelease((igObject *)dataResource->_dataMemoryPool);
    dataResource->_dataMemoryPool = (int)pool;

    pool = igObject_GetAllocator(self); /* matching construct: manual — the temporary pool reuses the data pool's variable */
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
    temporaryResource = (igResource *)g_globalContext;
    if (pool != 0) {
        ((igObject *)pool)->_refCount = ((igObject *)pool)->_refCount + 1;
    }
    igRelease((igObject *)temporaryResource->_temporaryMemoryPool);
    temporaryResource->_temporaryMemoryPool = (int)pool;
}

void beSystem_Stop(void)
{
}

/* The system takes none of the infos the insight core offers its managers. */
int beSystem_AddInfo(void)
{
    return 0;
}

void beSystem_RemoveAllInfo(beSystem *self)
{
    self->_isFirstTime = 1;
}

/* Once per frame: sample the insight clock into the frame delta, then drive
 * the stage-directory handshake.  A pending _nextStage retargets the
 * resource's allocators (the ndmw.igb boot scene gets its own selector),
 * requests the directory for that name and interns an empty string in its
 * place.  Once the directory has finished loading, each of its infos is
 * offered to the insight core and the directory is released.  Finally the
 * first-frame flag is cleared while the system is active. */
void beSystem_Update(beSystem *self)
{
    long long now;
    void *ndmwObjectPool;
    void *ndmwDataPool;
    void *defaultObjectPool;
    void *defaultDataPool;
    igResource *ndmwObjectResource;
    igResource *ndmwDataResource;
    igResource *defaultObjectResource;
    igResource *defaultDataResource;
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
            if (strcmp((const char *)self->_nextStage, (const char *)ndmw_igb) == 0) {
                ndmwObjectPool = igObject_GetAllocator(self);
                ndmwObjectPool = g_useOwnerAllocator != 0 ? ndmwObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
                ndmwObjectResource = (igResource *)g_globalContext;
                if (ndmwObjectPool != 0) {
                    ((igObject *)ndmwObjectPool)->_refCount = ((igObject *)ndmwObjectPool)->_refCount + 1;
                }
                igRelease((igObject *)ndmwObjectResource->_objectMemoryPool);
                ndmwObjectResource->_objectMemoryPool = (int)ndmwObjectPool;
                ndmwDataPool = igObject_GetAllocator(self);
                ndmwDataPool = g_useOwnerAllocator != 0 ? ndmwDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
                ndmwDataResource = (igResource *)g_globalContext;
                if (ndmwDataPool != 0) {
                    ((igObject *)ndmwDataPool)->_refCount = ((igObject *)ndmwDataPool)->_refCount + 1;
                }
                igRelease((igObject *)ndmwDataResource->_dataMemoryPool);
                ndmwDataResource->_dataMemoryPool = (int)ndmwDataPool;
            } else {
                defaultObjectPool = igObject_GetAllocator(self);
                defaultObjectPool = g_useOwnerAllocator != 0 ? defaultObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                defaultObjectResource = (igResource *)g_globalContext;
                if (defaultObjectPool != 0) {
                    ((igObject *)defaultObjectPool)->_refCount = ((igObject *)defaultObjectPool)->_refCount + 1;
                }
                igRelease((igObject *)defaultObjectResource->_objectMemoryPool);
                defaultObjectResource->_objectMemoryPool = (int)defaultObjectPool;
                defaultDataPool = igObject_GetAllocator(self);
                defaultDataPool = g_useOwnerAllocator != 0 ? defaultDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                defaultDataResource = (igResource *)g_globalContext;
                if (defaultDataPool != 0) {
                    ((igObject *)defaultDataPool)->_refCount = ((igObject *)defaultDataPool)->_refCount + 1;
                }
                igRelease((igObject *)defaultDataResource->_dataMemoryPool);
                defaultDataResource->_dataMemoryPool = (int)defaultDataPool;
            }
            igResource_StartAsyncLoading(g_globalContext);
            directory = igResource_LoadDirectory((igResource *)g_globalContext, (const char *)self->_nextStage);
            if (directory != 0) {
                directory->_refCount = directory->_refCount + 1;
            }
            igRelease((igObject *)self->_bootDirectory);
            self->_bootDirectory = (int)directory;
            if (g_stringPool == 0) {
                newPool = (int)StringPool_Allocate(16);
                if (newPool != 0) {
                    newPool = (int)(StringPool_Construct((StringPool *)newPool));
                }
                g_stringPool = (StringPool *)newPool;
            }
            emptyToken = (int *)StringPool_Intern(g_stringPool, 0);
            oldToken = (int *)self->_nextStage;
            if (oldToken != 0) {
                tokenHeader = (StringTokenHeader *)oldToken - 1;
                tokenRefCount = tokenHeader->refCount - 1;
                tokenHeader->refCount = tokenRefCount;
                if (tokenRefCount == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)tokenHeader->owner, tokenHeader);
                }
            }
            self->_nextStage = (int)emptyToken;
        } else if (self->_bootDirectory != 0) {
            if (igResource_IsDirectoryLoaded((igResource *)g_globalContext, (igDirectory *)self->_bootDirectory)) {
                infos = (igObjectList *)((igDirectory *)self->_bootDirectory)->_infoList;
                index = 0;
                if (0 < infos->_count) {
                    byteOffset = 0;
                    do {
                        igInsightCore_AddInfo((igInsightCore *)self->_insight, (igObject *)(*(int *)(infos->_data + byteOffset)));
                        index += 1;
                        byteOffset += 4;
                    } while (index < infos->_count);
                }
                igResource_UnloadDirectory((igResource *)g_globalContext, (const char *)((igDirectory *)self->_bootDirectory)->_name);
                igRelease((igObject *)self->_bootDirectory);
                self->_bootDirectory = 0;
                igResource_StopAsyncLoading(g_globalContext);
            }
        } else {
            /* Unreachable: entering the handshake needs _nextStage or _bootDirectory set. */
            if (g_stringPool == 0) {
                newPool = (int)StringPool_Allocate(16);
                if (newPool != 0) {
                    newPool = (int)(StringPool_Construct((StringPool *)newPool));
                }
                g_stringPool = (StringPool *)newPool;
            }
            emptyToken = (int *)StringPool_Intern(g_stringPool, 0);
            oldToken = (int *)self->_stageName;
            if (oldToken != 0) {
                tokenHeader = (StringTokenHeader *)oldToken - 1;
                tokenRefCount = tokenHeader->refCount - 1;
                tokenHeader->refCount = tokenRefCount;
                if (tokenRefCount == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)tokenHeader->owner, tokenHeader);
                }
            }
            self->_stageName = (int)emptyToken;
            igRelease((igObject *)self->_bootDirectory);
            self->_bootDirectory = 0;
        }
    }
    if (self->_isActive != 0 && self->_isFirstTime != 0) {
        self->_isFirstTime = 0;
    }
}

/* Active and past its first frame: the gate every manager checks before updating. */
unsigned char beSystem_IsRunning(beSystem *self)
{
    return (self->_isActive & !self->_isFirstTime) != 0;
}

igMetaObject *beSystem_GetMetaObject_Virtual(void)
{
    return g_beSystem_metaObject;
}
