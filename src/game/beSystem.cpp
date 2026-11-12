#include "dw4/reflected.h"

extern "C" void FUN_00236be0(int, char *);
extern "C" void FUN_00236c40(int, char *);
extern "C" int FUN_002eb010(int);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(int);
extern "C" void * StringPool_Intern(...);
extern "C" void Gap__Bec__beSystem__vfunc_24(void);
extern "C" int Gap__Bec__beSystem__vfunc_25(void);
extern "C" int Gap__Bec__beSystem__vfunc_20(void);
extern "C" int strcmp(const char *, const char *);
extern "C" float __floatdisf(long long);
extern "C" int igInsightCore_AddInfo(int insight, int info);
extern "C" void Gap__Bec__beSystem__vfunc_21(beSystem *self, int unusedArg);
extern "C" void Gap__Bec__beSystem__vfunc_22(beSystem *self, int unusedArg);
struct GlobalContextRecord { char pad0[8]; char f8; char pad1[47]; igObject *f56; igObject *f60; igObject *f64; };
extern "C" int igObject_Destroy(igObject *);
extern "C" void *igObject_GetAllocator(beSystem *);
extern "C" int DAT_004c22e8[4];
extern "C" int DAT_0050fb10[4];
extern "C" struct GlobalContextRecord *DAT_00586dd0[4];
extern "C" int DAT_00586f20[4];
extern "C" int DAT_00587060[4];
extern "C" int DAT_00587108[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__Bec__beSystem__vfunc_23(beSystem *arg0);
extern "C" int g_beSystem_metaObject[4];
extern "C" void Gap__Bec__beSystem__vfunc_26(beSystem *arg0);
/* Frame clock and staged-directory publication. */


/* The engine-wide context object. Only the members this update touches are named: the two
 * allocator references that are retargeted before a stage directory is requested. */
struct GlobalContextRecord_3a0020 {
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
extern "C" int ndmw_igb[4];
extern "C" struct GlobalContextRecord_3a0020 *g_globalContext[4];
extern "C" int g_stringPool[4];
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" int FUN_00308c80(struct GlobalContextRecord_3a0020 *);
extern "C" igDirectory *FUN_003092f0(struct GlobalContextRecord_3a0020 *, int name);
extern "C" int FUN_00309740(struct GlobalContextRecord_3a0020 *, int directory);
extern "C" int FUN_00309750(struct GlobalContextRecord_3a0020 *, int name);
extern "C" int FUN_00308e00(struct GlobalContextRecord_3a0020 *);
extern "C" void Gap__Bec__beSystem__vfunc_27(beSystem *self);
struct S { char p[44]; bool a; bool b; };
extern "C" int FUN_003a0540(S *s);

/* Hands the object to the insight core's helper FUN_00236be0, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__beSystem__vfunc_21(beSystem *self, int unusedArg)
{
    FUN_00236be0(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

/* Counterpart of slot 21 through FUN_00236c40, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__beSystem__vfunc_22(beSystem *self, int unusedArg)
{
    FUN_00236c40(self->_insight, (char *)self); /* matching construct: char * parameter on FUN_00236*, receiver passed as a byte pointer */
}

void Gap__Bec__beSystem__vfunc_23(beSystem *arg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int *temp_v1;
    int *temp_s0;
    igObject *a;
    void *al;
    struct GlobalContextRecord *r;
    void *al2;
    struct GlobalContextRecord *r2;
    igObject *a2;
    void *al3;
    struct GlobalContextRecord *r3;
    igObject *a3;
    arg0->_isFirstTime = 0;
    arg0->_isActive = 1;
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050fb10[0]);
    temp_v1 = (int *)arg0->_nextStage;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_nextStage = (int)temp_s0;
    a = (igObject *)arg0->_bootDirectory;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    arg0->_bootDirectory = 0;
    DAT_004c22e8[0] = 0x186A0;
    DAT_00586dd0[0]->f8 = 0;
    al = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al = (void *)(int)al;
    } else {
        al = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    r = DAT_00586dd0[0];
    if (al != 0) {
        ((igObject *)al)->_refCount = (int)((igObject *)al)->_refCount + 1;
    }
    a = r->f64;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    r->f64 = (igObject *)al;
    al2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al2 = (void *)(int)al2;
    } else {
        al2 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    r2 = DAT_00586dd0[0];
    if (al2 != 0) {
        ((igObject *)al2)->_refCount = (int)((igObject *)al2)->_refCount + 1;
    }
    a2 = r2->f60;
    if (a2 != 0) {
        a2->_refCount = (int)a2->_refCount - 1;
        if (((unsigned long long)((long long)(int)a2->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a2);
        }
    }
    r2->f60 = (igObject *)al2;
    al2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        al2 = (void *)(int)al2;
    } else {
        al2 = Memory_GetAllocatorBySelector(DAT_00587060[0]);
    }
    r = DAT_00586dd0[0];
    if (al2 != 0) {
        ((igObject *)al2)->_refCount = (int)((igObject *)al2)->_refCount + 1;
    }
    a = r->f56;
    if (a != 0) {
        a->_refCount = (int)a->_refCount - 1;
        if (((unsigned long long)((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(a);
        }
    }
    r->f56 = (igObject *)al2;
}

void Gap__Bec__beSystem__vfunc_24(void)
{
}

int Gap__Bec__beSystem__vfunc_25(void) {
    return 0;
}

void Gap__Bec__beSystem__vfunc_26(beSystem *arg0) {
    arg0->_isFirstTime = 1;
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
    struct GlobalContextRecord_3a0020 *ndmwCtx64;
    struct GlobalContextRecord_3a0020 *ndmwCtx60;
    struct GlobalContextRecord_3a0020 *defaultCtx64;
    struct GlobalContextRecord_3a0020 *defaultCtx60;
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
            if (strcmp((const char *)self->_nextStage, (const char *)&ndmw_igb[0]) == 0) {
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
            emptyToken = ((int *)StringPool_Intern(g_stringPool[0], 0));
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
                emptyToken = ((int *)StringPool_Intern(g_stringPool[0], 0));
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

int FUN_003a0540(S *s) {
    return (s->a & !s->b) != 0;
}

int Gap__Bec__beSystem__vfunc_20(void)
{
    return g_beSystem_metaObject[0];
}
