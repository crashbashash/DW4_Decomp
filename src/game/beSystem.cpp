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
    Gap::Core::igResource *objectResource;
    void *pool;
    Gap::Core::igResource *dataResource;
    Gap::Core::igResource *temporaryResource;

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
    igObject::release((igObject *)self->_bootDirectory);
    self->_bootDirectory = 0;
    Gap::Core::igResource::_asynchronousLoadingThreadStackSize = 100000;
    g_globalContext->_useMemoryPoolAssignmentsState = 0;

    objectPool = ((Gap::Core::igObject *)self)->getMemoryPool();
    objectPool = g_useOwnerAllocator != 0 ? objectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    objectResource = g_globalContext;
    objectResource->setObjectMemoryPool((igMemoryPool *)objectPool);

    pool = ((Gap::Core::igObject *)self)->getMemoryPool();
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
    dataResource = g_globalContext;
    dataResource->setDataMemoryPool((igMemoryPool *)pool);

    pool = ((Gap::Core::igObject *)self)->getMemoryPool(); /* matching construct: manual — the temporary pool reuses the data pool's variable */
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary);
    temporaryResource = g_globalContext;
    temporaryResource->setTemporaryMemoryPool((igMemoryPool *)pool);
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
    Gap::Core::igResource *ndmwObjectResource;
    Gap::Core::igResource *ndmwDataResource;
    Gap::Core::igResource *defaultObjectResource;
    Gap::Core::igResource *defaultDataResource;
    igObject *oldRef;
    Gap::Core::igDirectory *directory;
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
                ndmwObjectPool = ((Gap::Core::igObject *)self)->getMemoryPool();
                ndmwObjectPool = g_useOwnerAllocator != 0 ? ndmwObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
                ndmwObjectResource = g_globalContext;
                ndmwObjectResource->setObjectMemoryPool((igMemoryPool *)ndmwObjectPool);
                ndmwDataPool = ((Gap::Core::igObject *)self)->getMemoryPool();
                ndmwDataPool = g_useOwnerAllocator != 0 ? ndmwDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0);
                ndmwDataResource = g_globalContext;
                ndmwDataResource->setDataMemoryPool((igMemoryPool *)ndmwDataPool);
            } else {
                defaultObjectPool = ((Gap::Core::igObject *)self)->getMemoryPool();
                defaultObjectPool = g_useOwnerAllocator != 0 ? defaultObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                defaultObjectResource = g_globalContext;
                defaultObjectResource->setObjectMemoryPool((igMemoryPool *)defaultObjectPool);
                defaultDataPool = ((Gap::Core::igObject *)self)->getMemoryPool();
                defaultDataPool = g_useOwnerAllocator != 0 ? defaultDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
                defaultDataResource = g_globalContext;
                defaultDataResource->setDataMemoryPool((igMemoryPool *)defaultDataPool);
            }
            g_globalContext->enableAsynchronousLoading();
            directory = g_globalContext->load((const char *)self->_nextStage);
            Gap::Core::igObject::ref(directory);
            igObject::release((igObject *)self->_bootDirectory);
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
            if (g_globalContext->isLoadFinished((Gap::Core::igDirectory *)self->_bootDirectory)) {
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
                g_globalContext->unload((const char *)((igDirectory *)self->_bootDirectory)->_name);
                igObject::release((igObject *)self->_bootDirectory);
                self->_bootDirectory = 0;
                g_globalContext->disableAsynchronousLoading();
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
            igObject::release((igObject *)self->_bootDirectory);
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
