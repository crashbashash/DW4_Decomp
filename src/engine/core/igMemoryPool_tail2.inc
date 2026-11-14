void igMemoryPool_PrintStatistics(igMemoryPool *arg0, char *arg1) {
    long long s4, s3, s2, s1, s0, s6, s7, s8;
    long long sp120, sp110, sp100, spF0;
    __int128 spE0;
    igMemoryPoolView *o = (igMemoryPoolView *)arg0;

    if (arg1 != 0 && *arg1 != 0) {
        igReport_Printf(DAT_004f90b0);
        igReport_Flush();
    }
    s4 = arg0->_localNetAllocationCountHigh;
    s3 = arg0->_localNetAllocationCount;
    s2 = arg0->_localFreeCount;
    s1 = arg0->_localAllocationCount;
    s0 = arg0->_localNetAllocatedWithOverheadHigh;
    s6 = arg0->_localNetAllocatedWithOverhead;
    s7 = arg0->_localFreedWithOverhead;
    s8 = arg0->_localAllocatedWithOverhead;
    sp120 = arg0->_localNetAllocatedHigh;
    sp110 = arg0->_localNetAllocated;
    sp100 = arg0->_localFreed;
    spF0 = arg0->_localAllocated;
    spE0 = (int)o->vfunc_36();
    igReport_Printf(DAT_004f9d60, (int)spF0, (int)sp100, (int)sp110, (int)sp120, (long long)(int)s8, (long long)(int)s7, (long long)(int)s6, (long long)(int)s0, (long long)(int)s1, (long long)(int)s2, (long long)(int)s3, (long long)(int)s4, (long long)spE0, (long long)o->vfunc_42());
    igReport_Flush();
}

void igMemoryPool_PrintGlobalStatistics(char *arg0) {
    if ((arg0 != 0) && (*arg0 != 0)) {
        igReport_Printf(DAT_004f90b0, arg0);
        igReport_Flush();
    }
    igReport_Printf(DAT_004f9fe0, DAT_00586f70[0], DAT_00586f78[0], ((int *)DAT_00586f80)[0], ((int *)DAT_00586f88)[0], DAT_00586f90[0], DAT_00586f98[0], ((int *)DAT_00586fa0)[0], (long long) ((int *)DAT_00586fa8)[0], (long long) DAT_00586fb0[0], (long long) DAT_00586fb8[0], (long long) ((int *)DAT_00586fc0)[0], (long long) ((int *)DAT_00586fc8)[0]);
    igReport_Flush();
}

void igMemoryPool_DisplayOutstandingAllocations(void) {

}

int igMemoryPool_Trim(void) {
    return 0;
}

bool igMemoryPool_TrimAllPools(int arg0, int arg1) {
    int s2;
    igMemoryPoolView *o;
    int s1;
    igMemoryPoolView *q;
    bool s0;
    s0 = false;
    s1 = g_secondaryAllocatorList[0]->count - 1;
    while (s1 >= 0) {
        o = g_secondaryAllocatorList[0]->data[s1];
        if (o != 0 && o->isActive() != 0 && o->Trim(arg1) != 0) {
            s0 = true;
        }
        s1--;
    }
    s2 = g_primaryAllocatorList[0]->count - 1;
    while (s2 >= 0) {
        q = g_primaryAllocatorList[0]->data[s2];
        if (q != 0 && q->isActive() != 0 && q->Trim(arg1) != 0) {
            s0 = true;
        }
        s2--;
    }
    return s0;
}

void *FUN_002f0c80(igMemoryPoolView *self, unsigned int size)
{
    return self->Allocate(size);
}

int igMemoryPool_StrDup(void **arg0, int arg1) {
    int temp_v0;

    temp_v0 = (int)((igMemoryPoolView *)arg0)->Allocate(strlen(arg1) + 1);
    strcpy(temp_v0, arg1);
    return temp_v0;
}

int igMemoryPool_StrDupAligned(void **arg0, int arg1, unsigned short arg2) {
    int temp_v0;

    temp_v0 = (int)((igMemoryPoolView *)arg0)->AllocateAligned(strlen(arg1) + 1, arg2);
    strcpy(temp_v0, arg1);
    return temp_v0;
}

int igMemoryPool_GetEventTracker(void) {
    return 0;
}

void igMemoryPool_SetEventTracker(int dummy0, igObject *arg1) {
    IG_OBJECT_RELEASE(arg1);
}

void igMemoryPool_SetScopeFlags(int arg0) {
    *(int *)0x4C2160 = arg0;
}

void igMemoryPool_TrackEvent(void **arg0, int arg1, int arg2, int arg3) {
    void **temp_v0;

    if ((arg2 == 0) || (arg2 & DAT_004c2160[0])) {
        temp_v0 = (void **)(((igMemoryPoolView *)(arg0))->getEventTracker());
        if (temp_v0 != 0) {
            ((igEventTrackerView *)temp_v0)->vfunc_26((EventRecord *)arg1, arg3 + 1);
        }
    }
}

int igMemoryPool_AllocateElementTracked(igMemoryPoolView *pool, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    int size;
    void *block = pool->vfunc_53();
    if (block != 0) {
        size = Memory_GetBufferSize(block);
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->vfunc_38(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_AllocateTracked(igMemoryPoolView *pool, unsigned int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->Allocate(size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->vfunc_38(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_AllocateAlignedTracked(igMemoryPoolView *pool, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->AllocateAligned(size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_CallocateTracked(igMemoryPoolView *pool, int count, int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->vfunc_56(count, size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, count * size, (unsigned short)pool->vfunc_38(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_CallocateAlignedTracked(igMemoryPoolView *pool, int count, int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->vfunc_57(count, size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, count * size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_ReallocateTracked(igMemoryPoolView *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0) {
    char sp170[160];
    char spD0[160];
    int size;
    int flags;
    int flags2;
    MemoryContext *ctx;
    MemoryContext *ctx2;

    if (arg1 != 0) {
        size = ((int)Memory_GetBufferSize((void *)arg1));
        igEventTracker_InitMemoryEvent(sp170, 3, (void *)arg1, size, arg0->vfunc_38(), arg4, 0, 0, arg5, arg6, arg7, ((MemoryContext *)((void *)Memory_GetCurrentContextAlias()))->vfunc_27(arg0));
        arg0->vfunc_67(sp170, arg3, arg_sp0 + 1);
        igEventTracker_DestructEvent(sp170, -1);
    }
    arg1 = (int)arg0->Reallocate((void *)arg1, arg2);
    if (arg1 != 0) {
        flags2 = arg0->vfunc_38() & 0xFFFF;
        ctx2 = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(spD0, 1, (void *)arg1, arg2, flags2, arg4, 0, 0, arg5, arg6, arg7, ctx2->vfunc_27(arg0));
        arg0->vfunc_67(spD0, arg3, arg_sp0 + 1);
        igEventTracker_DestructEvent(spD0, -1);
    }
    return arg1;
}

int igMemoryPool_ReallocateAlignedTracked(igMemoryPoolView *pool, void *block, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord freed;
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&freed, 3, block, Memory_GetBufferSize(block), 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&freed, filter, depth + 1);
        igEventTracker_DestructEvent(&freed, -1);
    }
    block = pool->ReallocateAligned(block, size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_StrDupTracked(igMemoryPoolView *pool, const char *string, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *copy;
    int size;
    int alignment;
    copy = (void *)pool->vfunc_58((void *)string);
    if (copy != 0) {
        size = strlen(string) + 1;
        alignment = pool->vfunc_38() & 0xFFFF;
        igEventTracker_InitMemoryEvent(&record, 1, (void *)copy, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)copy;
}

int igMemoryPool_StrDupAlignedTracked(igMemoryPoolView *pool, const char *string, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *copy;
    int size;
    copy = pool->vfunc_61(string, alignment);
    if (copy != 0) {
        size = strlen(string) + 1;
        igEventTracker_InitMemoryEvent(&record, 1, (void *)copy, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)copy;
}

void igMemoryPool_GangAllocTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10) {
    char spB0[156];
    int first;
    int total;
    int flags;
    unsigned int i;
    MemoryContext *ctx;

    igResult res = arg1->gangAlloc(arg2, (unsigned int *)arg3, (void **)arg4);
    if ((arg2 != 0) && (arg3 != 0) && (arg4 != 0) && (res.v == g_resultSuccess.v)) {
        first = *arg4;
        total = 0;
        for (i = 0; i < (unsigned int) (arg2 & 0xFFFF); i++) {
            total += arg3[i];
        }
        flags = arg1->vfunc_38() & 0xFFFF;
        ctx = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(spB0, 1, (void *)first, total, flags, arg6, 0, 0, arg7, arg_sp0, arg_sp8, ctx->vfunc_27(arg1));
        arg1->vfunc_67(spB0, arg5, arg_sp10 + 1);
        igEventTracker_DestructEvent(spB0, -1);
    }
    *arg0 = res;
}

void igMemoryPool_GangAllocAlignedTracked(igResult *arg0, igMemoryPoolView *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18) {
    char spA0[156];
    int first;
    int total;
    unsigned int i;
    MemoryContext *ctx;

    igResult res = arg1->gangAllocAligned(arg2, (unsigned int *)arg3, (void **)arg4, (unsigned short *)arg5);
    if ((arg2 != 0) && (arg3 != 0) && (arg4 != 0) && (res.v == g_resultSuccess.v)) {
        first = *arg4;
        total = 0;
        for (i = 0; i < (unsigned int) (arg2 & 0xFFFF); i++) {
            total += arg3[i];
        }
        ctx = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(spA0, 1, (void *)first, total, 0, arg7, 0, 0, arg_sp0, arg_sp8, arg_sp10, ctx->vfunc_27(arg1));
        arg1->vfunc_67(spA0, arg6, arg_sp18 + 1);
        igEventTracker_DestructEvent(spA0, -1);
    }
    *arg0 = res;
}

void igMemoryPool_GangFreeTracked(void **arg0, unsigned int arg1, int *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0) {
    char spE0[160];
    int first;
    int total;
    unsigned int i;
    void **ctx;

    ((igMemoryPoolView *)arg0)->gangFree(arg1, (void **)arg2);
    if ((arg1 != 0) && (arg2 != 0)) {
        total = 0;
        first = *arg2;
        for (i = 0; i < arg1; i++) {
            if (arg2[i] != 0) {
                total += ((int)Memory_GetBufferSize((void *)arg2[i]));
            }
        }
        ctx = (void **)(((void **)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(spE0, 3, (void *)first, total, 0, arg4, 0, 0, arg5, arg6, arg7, ((MemoryContext *)(ctx))->vfunc_27(arg0));
        ((igMemoryPoolView *)(arg0))->vfunc_67(spE0, (int)(arg3), (int)(arg_sp0 + 1));
        igEventTracker_DestructEvent(spE0, -1);
    }
}

int FUN_002f1e30(igMemoryPoolView *pool, int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = (void *)pool->vfunc_65(size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->vfunc_38(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

void igMemoryPool_FreeTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 3, (void *)block, 0, 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    pool->Free(block);
}

void FUN_002f2070(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 3, (void *)block, 0, 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->vfunc_27(pool));
        pool->vfunc_67(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    pool->Free(block);
}

void Memory_InitializeAllocatorRegistries(igObject *rootAllocator) {
    int secondaryList;
    int primaryList;

    primaryList = ((int)igMemoryPoolInfoList_Allocate(0xC));
    if (primaryList != 0) {
        primaryList = ((int)igMemoryPoolInfoList_Init((AllocatorRegistry *)primaryList));
    }
    ((int *)g_primaryAllocatorList)[0] = primaryList;
    igMemoryPoolInfoList_Append((AllocatorRegistry *)primaryList, (igMemoryPoolView *)rootAllocator);
    ((char *)&rootAllocator->_refCount)[3] = 0;
    secondaryList = ((int)igMemoryPoolInfoList_Allocate(0xC));
    if (secondaryList != 0) {
        secondaryList = ((int)igMemoryPoolInfoList_Init((AllocatorRegistry *)secondaryList));
    }
    ((int *)g_secondaryAllocatorList)[0] = secondaryList;
}

void Memory_ShutdownAllocatorRegistries(void **rootAllocator) {
    igMemoryPoolInfoList_Release(g_primaryAllocatorList[0], 1);
    igMemoryPoolInfoList_Release(g_secondaryAllocatorList[0], 1);
    ((int *)g_primaryAllocatorList)[0] = 0;
    ((int *)g_secondaryAllocatorList)[0] = 0;
    ((igMemoryPoolView *)(rootAllocator))->vfunc_98();
}

void igMemoryPool_SetDefaults(void *arg0) {
    *(unsigned char *)((char *)arg0 + 104) = (unsigned char) GPR_00554994;
}

void igMemoryPool_Shutdown(void) {

}

void igMemoryPool_UpdateStatistics(igMemoryPool *pool, long long arg1, long long arg2, int arg3) {
    ((igMemoryPoolView *)pool)->vfunc_52(arg1, arg2, arg3);
    if (pool->_updateGlobalStatistics != 0) {
        igMemoryPool_UpdateGlobalStatistics(arg1, arg2, arg3);
    }
}

void igMemoryPool_ResetStatistics(igMemoryPool *arg0) {
    arg0->_localAllocated = 0;
    arg0->_localNetAllocated = 0;
    arg0->_localNetAllocatedHigh = 0;
    arg0->_localAllocatedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverheadHigh = 0;
    arg0->_localAllocationCount = 0;
    arg0->_localNetAllocationCount = 0;
    arg0->_localNetAllocationCountHigh = 0;
    arg0->_localFreed = 0;
    arg0->_localNetAllocated = 0;
    arg0->_localFreedWithOverhead = 0;
    arg0->_localNetAllocatedWithOverhead = 0;
    arg0->_localFreeCount = 0;
    arg0->_localNetAllocationCount = 0;
    arg0->_updateGlobalStatistics = 1;
    arg0->_updateStatistics = (unsigned char) GPR_00554994;
}

void igMemoryPool_UpdateLocalStatistics(igMemoryPool *arg0, int arg1, int arg2, int arg3) {
    long long a;
    long long b;

    if (arg3 != 0) {
        a = arg1;
        arg0->_localAllocated = arg0->_localAllocated + a;
        arg0->_localNetAllocated = arg0->_localNetAllocated + a;
        if (arg0->_localNetAllocatedHigh < arg0->_localNetAllocated) {
            arg0->_localNetAllocatedHigh = arg0->_localNetAllocated;
        }
        b = arg2;
        arg0->_localAllocatedWithOverhead = arg0->_localAllocatedWithOverhead + b;
        arg0->_localNetAllocatedWithOverhead = arg0->_localNetAllocatedWithOverhead + b;
        if (arg0->_localNetAllocatedWithOverheadHigh < arg0->_localNetAllocatedWithOverhead) {
            arg0->_localNetAllocatedWithOverheadHigh = arg0->_localNetAllocatedWithOverhead;
        }
        arg0->_localAllocationCount = arg0->_localAllocationCount + 1;
        arg0->_localNetAllocationCount = arg0->_localNetAllocationCount + 1;
        if (arg0->_localNetAllocationCountHigh < arg0->_localNetAllocationCount) {
            arg0->_localNetAllocationCountHigh = arg0->_localNetAllocationCount;
        }
    } else {
        a = arg1;
        b = arg2;
        arg0->_localFreed = arg0->_localFreed + a;
        arg0->_localNetAllocated = arg0->_localNetAllocated - a;
        arg0->_localFreedWithOverhead = arg0->_localFreedWithOverhead + b;
        arg0->_localNetAllocatedWithOverhead = arg0->_localNetAllocatedWithOverhead - b;
        arg0->_localFreeCount = arg0->_localFreeCount + 1;
        arg0->_localNetAllocationCount = arg0->_localNetAllocationCount - 1;
    }
}

void igMemoryPool_UpdateGlobalStatistics(long long arg0, long long arg1, int arg2) {
    long long t;
    if (arg2 != 0) {
        t = (int)arg0;
        ((long long *)DAT_00586f70)[0] += t;
        DAT_00586f80[0] += t;
        if (DAT_00586f88[0] < DAT_00586f80[0]) {
            DAT_00586f88[0] = DAT_00586f80[0];
        }
        t = (int)arg1;
        ((long long *)DAT_00586f90)[0] += t;
        DAT_00586fa0[0] += t;
        if (DAT_00586fa8[0] < DAT_00586fa0[0]) {
            DAT_00586fa8[0] = DAT_00586fa0[0];
        }
        ((long long *)DAT_00586fb0)[0] += 1;
        DAT_00586fc0[0] += 1;
        if (DAT_00586fc8[0] < DAT_00586fc0[0]) {
            DAT_00586fc8[0] = DAT_00586fc0[0];
        }
    } else {
        t = (int)arg0;
        ((long long *)DAT_00586f78)[0] += t;
        DAT_00586f80[0] -= t;
        ((long long *)DAT_00586f98)[0] += t;
        DAT_00586fa0[0] -= t;
        ((long long *)DAT_00586fb8)[0] += 1;
        DAT_00586fc0[0] -= 1;
    }
}

void igMemoryPool_EnableAllocationLock(int *status_out) {
    *status_out = g_resultFailure.v;
}

