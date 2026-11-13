#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

/* Header in front of every interned string token: owning chunk, then a full 32-bit reference
 * count. */
typedef struct StringTokenHeader {
    int owner;
    int refCount;
} StringTokenHeader;

extern "C" {
void igInsightCore_AddToScheduler(int insight, char *object);
void igInsightCore_RemoveFromScheduler(int insight, char *object);
int StringPool_Allocate(int size);
int StringPool_Construct(int pool);
int *StringPool_Intern(int pool, const void *text);
int StringChunk_ReleaseHeader(int owner, StringTokenHeader *header);
void *Memory_GetAllocatorBySelector(int selector);
void *igObject_GetAllocator(beSystem *object);
int strcmp(const char *, const char *);
float __floatdisf(long long);
int igInsightCore_AddInfo(int insight, int info);
void igResource_StartAsyncLoading(igResource *resource);
void igResource_StopAsyncLoading(igResource *resource);
igDirectory *igResource_LoadDirectory(igResource *resource, int name);
int igResource_IsDirectoryLoaded(igResource *resource, int directory);
int igResource_UnloadDirectory(igResource *resource, int name);

extern igResource *g_globalContext[4];
extern int g_stringPool[4];
extern int g_resourceLoaderStackSize[4];
extern int kIGMemoryPoolHandleUser0[4];
extern int kIGMemoryPoolHandleUser1[4];
extern int kIGMemoryPoolHandleTemporary[4];
extern unsigned char g_useOwnerAllocator;
extern int g_beSystem_metaObject[4];
extern int ndmw_igb[4];

void beSystem_AddToScheduler(beSystem *self, int unusedArg);
void beSystem_RemoveFromScheduler(beSystem *self, int unusedArg);
void beSystem_Start(beSystem *self);
void beSystem_Stop(void);
int beSystem_AcceptInfo(void);
void beSystem_Reset(beSystem *self);
void beSystem_Update(beSystem *self);
int beSystem_IsRunning(beSystem *self);
int beSystem_GetMetaObject_Virtual(void);
}

/* Hands the system to the insight scheduler unless it already holds it. */
void beSystem_AddToScheduler(beSystem *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

/* Takes the system back out of the insight scheduler when it holds it. */
void beSystem_RemoveFromScheduler(beSystem *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
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
    if (g_stringPool[0] == 0) {
        newPool = StringPool_Allocate(16);
        if (newPool != 0) {
            newPool = StringPool_Construct(newPool);
        }
        g_stringPool[0] = newPool;
    }
    stageToken = StringPool_Intern(g_stringPool[0], ndmw_igb);
    oldToken = (int *)self->_nextStage;
    if (oldToken != 0) {
        tokenHeader = (StringTokenHeader *)oldToken - 1;
        tokenRefCount = tokenHeader->refCount - 1;
        tokenHeader->refCount = tokenRefCount;
        if (tokenRefCount == 0) {
            StringChunk_ReleaseHeader(tokenHeader->owner, tokenHeader);
        }
    }
    self->_nextStage = (int)stageToken;
    igRelease((igObject *)self->_bootDirectory);
    self->_bootDirectory = 0;
    g_resourceLoaderStackSize[0] = 100000;
    g_globalContext[0]->_useMemoryPoolAssignmentsState = 0;

    objectPool = igObject_GetAllocator(self);
    objectPool = g_useOwnerAllocator != 0 ? objectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    objectResource = g_globalContext[0];
    if (objectPool != 0) {
        ((igObject *)objectPool)->_refCount = ((igObject *)objectPool)->_refCount + 1;
    }
    igRelease((igObject *)objectResource->_objectMemoryPool);
    objectResource->_objectMemoryPool = (int)objectPool;

    pool = igObject_GetAllocator(self);
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
    dataResource = g_globalContext[0];
    if (pool != 0) {
        ((igObject *)pool)->_refCount = ((igObject *)pool)->_refCount + 1;
    }
    igRelease((igObject *)dataResource->_dataMemoryPool);
    dataResource->_dataMemoryPool = (int)pool;

    pool = igObject_GetAllocator(self); /* matching construct: manual — the temporary pool reuses the data pool's variable */
    pool = g_useOwnerAllocator != 0 ? pool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary[0]);
    temporaryResource = g_globalContext[0];
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
int beSystem_AcceptInfo(void)
{
    return 0;
}

void beSystem_Reset(beSystem *self)
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
                ndmwObjectPool = g_useOwnerAllocator != 0 ? ndmwObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
                ndmwObjectResource = g_globalContext[0];
                if (ndmwObjectPool != 0) {
                    ((igObject *)ndmwObjectPool)->_refCount = ((igObject *)ndmwObjectPool)->_refCount + 1;
                }
                igRelease((igObject *)ndmwObjectResource->_objectMemoryPool);
                ndmwObjectResource->_objectMemoryPool = (int)ndmwObjectPool;
                ndmwDataPool = igObject_GetAllocator(self);
                ndmwDataPool = g_useOwnerAllocator != 0 ? ndmwDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser0[0]);
                ndmwDataResource = g_globalContext[0];
                if (ndmwDataPool != 0) {
                    ((igObject *)ndmwDataPool)->_refCount = ((igObject *)ndmwDataPool)->_refCount + 1;
                }
                igRelease((igObject *)ndmwDataResource->_dataMemoryPool);
                ndmwDataResource->_dataMemoryPool = (int)ndmwDataPool;
            } else {
                defaultObjectPool = igObject_GetAllocator(self);
                defaultObjectPool = g_useOwnerAllocator != 0 ? defaultObjectPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                defaultObjectResource = g_globalContext[0];
                if (defaultObjectPool != 0) {
                    ((igObject *)defaultObjectPool)->_refCount = ((igObject *)defaultObjectPool)->_refCount + 1;
                }
                igRelease((igObject *)defaultObjectResource->_objectMemoryPool);
                defaultObjectResource->_objectMemoryPool = (int)defaultObjectPool;
                defaultDataPool = igObject_GetAllocator(self);
                defaultDataPool = g_useOwnerAllocator != 0 ? defaultDataPool : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                defaultDataResource = g_globalContext[0];
                if (defaultDataPool != 0) {
                    ((igObject *)defaultDataPool)->_refCount = ((igObject *)defaultDataPool)->_refCount + 1;
                }
                igRelease((igObject *)defaultDataResource->_dataMemoryPool);
                defaultDataResource->_dataMemoryPool = (int)defaultDataPool;
            }
            igResource_StartAsyncLoading(g_globalContext[0]);
            directory = igResource_LoadDirectory(g_globalContext[0], self->_nextStage);
            if (directory != 0) {
                directory->_refCount = directory->_refCount + 1;
            }
            igRelease((igObject *)self->_bootDirectory);
            self->_bootDirectory = (int)directory;
            if (g_stringPool[0] == 0) {
                newPool = StringPool_Allocate(16);
                if (newPool != 0) {
                    newPool = StringPool_Construct(newPool);
                }
                g_stringPool[0] = newPool;
            }
            emptyToken = StringPool_Intern(g_stringPool[0], 0);
            oldToken = (int *)self->_nextStage;
            if (oldToken != 0) {
                tokenHeader = (StringTokenHeader *)oldToken - 1;
                tokenRefCount = tokenHeader->refCount - 1;
                tokenHeader->refCount = tokenRefCount;
                if (tokenRefCount == 0) {
                    StringChunk_ReleaseHeader(tokenHeader->owner, tokenHeader);
                }
            }
            self->_nextStage = (int)emptyToken;
        } else if (self->_bootDirectory != 0) {
            if (igResource_IsDirectoryLoaded(g_globalContext[0], self->_bootDirectory) != 0) {
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
                igResource_UnloadDirectory(g_globalContext[0], ((igDirectory *)self->_bootDirectory)->_name);
                igRelease((igObject *)self->_bootDirectory);
                self->_bootDirectory = 0;
                igResource_StopAsyncLoading(g_globalContext[0]);
            }
        } else {
            /* Unreachable: entering the handshake needs _nextStage or _bootDirectory set. */
            if (g_stringPool[0] == 0) {
                newPool = StringPool_Allocate(16);
                if (newPool != 0) {
                    newPool = StringPool_Construct(newPool);
                }
                g_stringPool[0] = newPool;
            }
            emptyToken = StringPool_Intern(g_stringPool[0], 0);
            oldToken = (int *)self->_stageName;
            if (oldToken != 0) {
                tokenHeader = (StringTokenHeader *)oldToken - 1;
                tokenRefCount = tokenHeader->refCount - 1;
                tokenHeader->refCount = tokenRefCount;
                if (tokenRefCount == 0) {
                    StringChunk_ReleaseHeader(tokenHeader->owner, tokenHeader);
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
int beSystem_IsRunning(beSystem *self)
{
    return (self->_isActive & !self->_isFirstTime) != 0;
}

int beSystem_GetMetaObject_Virtual(void)
{
    return g_beSystem_metaObject[0];
}
