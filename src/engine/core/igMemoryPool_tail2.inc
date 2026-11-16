void igMemoryPool_PrintStatistics(igMemoryPool *self, char *title) {
    long long netCountHigh, netCount, freeCount, allocationCount, netWithOverheadHigh, netWithOverhead, freedWithOverhead, allocatedWithOverhead;
    long long netAllocatedHigh, netAllocated, freed, allocated;
    __int128 arenaSize;
    igMemoryPoolView *pool = (igMemoryPoolView *)self;

    if (title != 0 && *title != 0) {
        igReport_Printf("%s:\n");
        igReport_Flush();
    }
    netCountHigh = self->_localNetAllocationCountHigh;
    netCount = self->_localNetAllocationCount;
    freeCount = self->_localFreeCount;
    allocationCount = self->_localAllocationCount;
    netWithOverheadHigh = self->_localNetAllocatedWithOverheadHigh;
    netWithOverhead = self->_localNetAllocatedWithOverhead;
    freedWithOverhead = self->_localFreedWithOverhead;
    allocatedWithOverhead = self->_localAllocatedWithOverhead;
    netAllocatedHigh = self->_localNetAllocatedHigh;
    netAllocated = self->_localNetAllocated;
    freed = self->_localFreed;
    allocated = self->_localAllocated;
    arenaSize = (int)pool->GetSize();
    igReport_Printf("    Total allocated:                      %u\n    Total freed:                          %u\n    Net allocated:                        %u\n    Net allocated high:                   %u\n    Total allocated with overhead:        %u\n    Total freed with overhead:            %u\n    Net allocated with overhead:          %u\n    Net allocated high with overhead:     %u\n    Total allocation count:               %u\n    Total free count:                     %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\n    Total pool arena size:                %u\n    Max size limit:                       %u\n", (int)allocated, (int)freed, (int)netAllocated, (int)netAllocatedHigh, (long long)(int)allocatedWithOverhead, (long long)(int)freedWithOverhead, (long long)(int)netWithOverhead, (long long)(int)netWithOverheadHigh, (long long)(int)allocationCount, (long long)(int)freeCount, (long long)(int)netCount, (long long)(int)netCountHigh, (long long)arenaSize, (long long)pool->GetMaxSize());
    igReport_Flush();
}

char *g_globalAllocated;
int g_globalFreed;
long long g_globalNetAllocated;
long long g_globalNetAllocatedHigh;
int g_globalAllocatedWithOverhead;
int g_globalFreedWithOverhead;
long long g_globalNetAllocatedWithOverhead;
long long g_globalNetAllocatedWithOverheadHigh;
int g_globalAllocationCount;
int g_globalFreeCount;
long long g_globalNetAllocationCount;
long long g_globalNetAllocationCountHigh;

void igMemoryPool_PrintGlobalStatistics(char *title) {
    if ((title != 0) && (*title != 0)) {
        igReport_Printf("%s:\n", title);
        igReport_Flush();
    }
    igReport_Printf("    Total allocated:                      %u\n    Total freed:                          %u\n    Net allocated:                        %u\n    Net allocated high:                   %u\n    Total allocated with overhead:        %u\n    Total freed with overhead:            %u\n    Net allocated with overhead:          %u\n    Net allocated high with overhead:     %u\n    Total allocation count:               %u\n    Total free count:                     %u\n    Net allocation count:                 %u\n    Net allocation count high:            %u\n", g_globalAllocated, g_globalFreed, (*(int *)&g_globalNetAllocated), (*(int *)&g_globalNetAllocatedHigh), g_globalAllocatedWithOverhead, g_globalFreedWithOverhead, (*(int *)&g_globalNetAllocatedWithOverhead), (long long) (*(int *)&g_globalNetAllocatedWithOverheadHigh), (long long) g_globalAllocationCount, (long long) g_globalFreeCount, (long long) (*(int *)&g_globalNetAllocationCount), (long long) (*(int *)&g_globalNetAllocationCountHigh));
    igReport_Flush();
}

void igMemoryPool_DisplayOutstandingAllocations(void) {

}

int igMemoryPool_Trim(void) {
    return 0;
}

bool igMemoryPool_TrimAllPools(int unused, int flags) {
    int j;
    igMemoryPoolView *secondary;
    int i;
    igMemoryPoolView *primary;
    bool trimmed;
    trimmed = false;
    i = g_secondaryAllocatorList->count - 1;
    while (i >= 0) {
        secondary = g_secondaryAllocatorList->data[i];
        if (secondary != 0 && secondary->IsActive() != 0 && secondary->Trim(flags) != 0) {
            trimmed = true;
        }
        i--;
    }
    j = g_primaryAllocatorList->count - 1;
    while (j >= 0) {
        primary = g_primaryAllocatorList->data[j];
        if (primary != 0 && primary->IsActive() != 0 && primary->Trim(flags) != 0) {
            trimmed = true;
        }
        j--;
    }
    return trimmed;
}

void *igMemoryPool_AllocateFromSystem(igMemoryPoolView *self, unsigned int size)
{
    return self->Allocate(size);
}

int igMemoryPool_StrDup(void **pool, int string) {
    int copy;

    copy = (int)((igMemoryPoolView *)pool)->Allocate(strlen((const char *)string) + 1);
    strcpy((char *)copy, (const char *)string);
    return copy;
}

int igMemoryPool_StrDupAligned(void **pool, int string, unsigned short alignment) {
    int copy;

    copy = (int)((igMemoryPoolView *)pool)->AllocateAligned(strlen((const char *)string) + 1, alignment);
    strcpy((char *)copy, (const char *)string);
    return copy;
}

int igMemoryPool_GetEventTracker(void) {
    return 0;
}

void igMemoryPool_SetEventTracker(int pool, igObject *tracker) {
    IG_OBJECT_RELEASE(tracker);
}

void igMemoryPool_SetScopeFlags(int flags) {
    *(int *)0x4C2160 = flags;
}

int g_memoryEventScopeFlags = -1;

void igMemoryPool_TrackEvent(void **pool, int record, int scope, int depth) {
    void **tracker;

    if ((scope == 0) || (scope & g_memoryEventScopeFlags)) {
        tracker = (void **)(((igMemoryPoolView *)(pool))->GetEventTracker());
        if (tracker != 0) {
            ((igEventTrackerView *)tracker)->AddEvent((EventRecord *)record, depth + 1);
        }
    }
}

int igMemoryPool_AllocateElementTracked(igMemoryPoolView *pool, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    int size;
    void *block = pool->AllocateElement();
    if (block != 0) {
        size = Memory_GetBufferSize(block);
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->GetAlignment(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_AllocateTracked(igMemoryPoolView *pool, unsigned int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->Allocate(size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->GetAlignment(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_AllocateAlignedTracked(igMemoryPoolView *pool, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->AllocateAligned(size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_CallocateTracked(igMemoryPoolView *pool, int count, int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->Callocate(count, size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, count * size, (unsigned short)pool->GetAlignment(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_CallocateAlignedTracked(igMemoryPoolView *pool, int count, int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = pool->CallocateAligned(count, size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, count * size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_ReallocateTracked(igMemoryPoolView *pool, int block, int newSize, int filter, int tag, int info0, int info1, int info2, int depth) {
    char freeRecord[160];
    char allocRecord[160];
    int oldSize;
    int flags;
    int flags2;
    MemoryContext *ctx;
    MemoryContext *ctx2;

    if (block != 0) {
        oldSize = ((int)Memory_GetBufferSize((void *)block));
        igEventTracker_InitMemoryEvent(freeRecord, 3, (void *)block, oldSize, pool->GetAlignment(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)((void *)Memory_GetCurrentContextAlias()))->GetPoolName(pool));
        pool->TrackEvent(freeRecord, filter, depth + 1);
        igEventTracker_DestructEvent(freeRecord, -1);
    }
    block = (int)pool->Reallocate((void *)block, newSize);
    if (block != 0) {
        flags2 = pool->GetAlignment() & 0xFFFF;
        ctx2 = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(allocRecord, 1, (void *)block, newSize, flags2, tag, 0, 0, info0, info1, info2, ctx2->GetPoolName(pool));
        pool->TrackEvent(allocRecord, filter, depth + 1);
        igEventTracker_DestructEvent(allocRecord, -1);
    }
    return block;
}

int igMemoryPool_ReallocateAlignedTracked(igMemoryPoolView *pool, void *block, unsigned int size, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord freed;
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&freed, 3, block, Memory_GetBufferSize(block), 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&freed, filter, depth + 1);
        igEventTracker_DestructEvent(&freed, -1);
    }
    block = pool->ReallocateAligned(block, size, alignment);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

int igMemoryPool_StrDupTracked(igMemoryPoolView *pool, const char *string, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *copy;
    int size;
    int alignment;
    copy = (void *)pool->StrDup((void *)string);
    if (copy != 0) {
        size = strlen(string) + 1;
        alignment = pool->GetAlignment() & 0xFFFF;
        igEventTracker_InitMemoryEvent(&record, 1, (void *)copy, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)copy;
}

int igMemoryPool_StrDupAlignedTracked(igMemoryPoolView *pool, const char *string, unsigned short alignment, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *copy;
    int size;
    copy = pool->StrDupAligned(string, alignment);
    if (copy != 0) {
        size = strlen(string) + 1;
        igEventTracker_InitMemoryEvent(&record, 1, (void *)copy, size, alignment, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)copy;
}

void igMemoryPool_GangAllocTracked(igResult *result, igMemoryPoolView *pool, int count, int *sizes, int *blocks, int filter, int tag, int info0, int info1, int info2, int depth) {
    char record[156];
    int first;
    int total;
    int flags;
    unsigned int i;
    MemoryContext *ctx;

    igResult res = pool->GangAlloc(count, (unsigned int *)sizes, (void **)blocks);
    if ((count != 0) && (sizes != 0) && (blocks != 0) && (res.v == g_resultSuccess.v)) {
        first = *blocks;
        total = 0;
        for (i = 0; i < (unsigned int) (count & 0xFFFF); i++) {
            total += sizes[i];
        }
        flags = pool->GetAlignment() & 0xFFFF;
        ctx = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(record, 1, (void *)first, total, flags, tag, 0, 0, info0, info1, info2, ctx->GetPoolName(pool));
        pool->TrackEvent(record, filter, depth + 1);
        igEventTracker_DestructEvent(record, -1);
    }
    *result = res;
}

void igMemoryPool_GangAllocAlignedTracked(igResult *result, igMemoryPoolView *pool, int count, int *sizes, int *blocks, int alignments, int filter, int tag, int info0, int info1, int info2, int depth) {
    char record[156];
    int first;
    int total;
    unsigned int i;
    MemoryContext *ctx;

    igResult res = pool->GangAllocAligned(count, (unsigned int *)sizes, (void **)blocks, (unsigned short *)alignments);
    if ((count != 0) && (sizes != 0) && (blocks != 0) && (res.v == g_resultSuccess.v)) {
        first = *blocks;
        total = 0;
        for (i = 0; i < (unsigned int) (count & 0xFFFF); i++) {
            total += sizes[i];
        }
        ctx = (MemoryContext *)(((void *)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(record, 1, (void *)first, total, 0, tag, 0, 0, info0, info1, info2, ctx->GetPoolName(pool));
        pool->TrackEvent(record, filter, depth + 1);
        igEventTracker_DestructEvent(record, -1);
    }
    *result = res;
}

void igMemoryPool_GangFreeTracked(void **pool, unsigned int count, int *blocks, int filter, int tag, int info0, int info1, int info2, int depth) {
    char record[160];
    int first;
    int total;
    unsigned int i;
    void **ctx;

    ((igMemoryPoolView *)pool)->GangFree(count, (void **)blocks);
    if ((count != 0) && (blocks != 0)) {
        total = 0;
        first = *blocks;
        for (i = 0; i < count; i++) {
            if (blocks[i] != 0) {
                total += ((int)Memory_GetBufferSize((void *)blocks[i]));
            }
        }
        ctx = (void **)(((void **)Memory_GetCurrentContextAlias()));
        igEventTracker_InitMemoryEvent(record, 3, (void *)first, total, 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)(ctx))->GetPoolName(pool));
        ((igMemoryPoolView *)(pool))->TrackEvent(record, (int)(filter), (int)(depth + 1));
        igEventTracker_DestructEvent(record, -1);
    }
}

int igMemoryPool_AllocateFromSystemTracked(igMemoryPoolView *pool, int size, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    void *block = (void *)pool->AllocateFromSystem(size);
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 1, (void *)block, size, (unsigned short)pool->GetAlignment(), tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    return (int)block;
}

void igMemoryPool_FreeTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 3, (void *)block, 0, 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
        igEventTracker_DestructEvent(&record, -1);
    }
    pool->Free(block);
}

void igMemoryPool_FreeFromSystemTracked(igMemoryPoolView *pool, void *block, int filter, int tag, int info0, int info1, int info2, int depth) {
    EventRecord record;
    if (block != 0) {
        igEventTracker_InitMemoryEvent(&record, 3, (void *)block, 0, 0, tag, 0, 0, info0, info1, info2, ((MemoryContext *)Memory_GetCurrentContextAlias())->GetPoolName(pool));
        pool->TrackEvent(&record, filter, depth + 1);
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
    (*(int *)&g_primaryAllocatorList) = primaryList;
    igMemoryPoolInfoList_Append((AllocatorRegistry *)primaryList, (igMemoryPoolView *)rootAllocator);
    ((char *)&rootAllocator->_refCount)[3] = 0;
    secondaryList = ((int)igMemoryPoolInfoList_Allocate(0xC));
    if (secondaryList != 0) {
        secondaryList = ((int)igMemoryPoolInfoList_Init((AllocatorRegistry *)secondaryList));
    }
    (*(int *)&g_secondaryAllocatorList) = secondaryList;
}

void Memory_ShutdownAllocatorRegistries(void **rootAllocator) {
    igMemoryPoolInfoList_Release(g_primaryAllocatorList, 1);
    igMemoryPoolInfoList_Release(g_secondaryAllocatorList, 1);
    (*(int *)&g_primaryAllocatorList) = 0;
    (*(int *)&g_secondaryAllocatorList) = 0;
    ((igMemoryPoolView *)(rootAllocator))->Shutdown();
}

void igMemoryPool_SetDefaults(void *pool) {
    ((igMemoryPool *)pool)->_updateStatistics = (unsigned char) g_igMemoryPool_defaultUpdateStatistics;
}

void igMemoryPool_Shutdown(void) {

}

void igMemoryPool_UpdateStatistics(igMemoryPool *pool, long long size, long long sizeWithOverhead, int allocated) {
    ((igMemoryPoolView *)pool)->UpdateLocalStatistics(size, sizeWithOverhead, allocated);
    if (pool->_updateGlobalStatistics != 0) {
        igMemoryPool_UpdateGlobalStatistics(size, sizeWithOverhead, allocated);
    }
}

void igMemoryPool_ResetStatistics(igMemoryPool *self) {
    self->_localAllocated = 0;
    self->_localNetAllocated = 0;
    self->_localNetAllocatedHigh = 0;
    self->_localAllocatedWithOverhead = 0;
    self->_localNetAllocatedWithOverhead = 0;
    self->_localNetAllocatedWithOverheadHigh = 0;
    self->_localAllocationCount = 0;
    self->_localNetAllocationCount = 0;
    self->_localNetAllocationCountHigh = 0;
    self->_localFreed = 0;
    self->_localNetAllocated = 0;
    self->_localFreedWithOverhead = 0;
    self->_localNetAllocatedWithOverhead = 0;
    self->_localFreeCount = 0;
    self->_localNetAllocationCount = 0;
    self->_updateGlobalStatistics = 1;
    self->_updateStatistics = (unsigned char) g_igMemoryPool_defaultUpdateStatistics;
}

void igMemoryPool_UpdateLocalStatistics(igMemoryPool *self, int size, int sizeWithOverhead, int allocated) {
    long long bytes;
    long long bytesWithOverhead;

    if (allocated != 0) {
        bytes = size;
        self->_localAllocated = self->_localAllocated + bytes;
        self->_localNetAllocated = self->_localNetAllocated + bytes;
        if (self->_localNetAllocatedHigh < self->_localNetAllocated) {
            self->_localNetAllocatedHigh = self->_localNetAllocated;
        }
        bytesWithOverhead = sizeWithOverhead;
        self->_localAllocatedWithOverhead = self->_localAllocatedWithOverhead + bytesWithOverhead;
        self->_localNetAllocatedWithOverhead = self->_localNetAllocatedWithOverhead + bytesWithOverhead;
        if (self->_localNetAllocatedWithOverheadHigh < self->_localNetAllocatedWithOverhead) {
            self->_localNetAllocatedWithOverheadHigh = self->_localNetAllocatedWithOverhead;
        }
        self->_localAllocationCount = self->_localAllocationCount + 1;
        self->_localNetAllocationCount = self->_localNetAllocationCount + 1;
        if (self->_localNetAllocationCountHigh < self->_localNetAllocationCount) {
            self->_localNetAllocationCountHigh = self->_localNetAllocationCount;
        }
    } else {
        bytes = size;
        bytesWithOverhead = sizeWithOverhead;
        self->_localFreed = self->_localFreed + bytes;
        self->_localNetAllocated = self->_localNetAllocated - bytes;
        self->_localFreedWithOverhead = self->_localFreedWithOverhead + bytesWithOverhead;
        self->_localNetAllocatedWithOverhead = self->_localNetAllocatedWithOverhead - bytesWithOverhead;
        self->_localFreeCount = self->_localFreeCount + 1;
        self->_localNetAllocationCount = self->_localNetAllocationCount - 1;
    }
}

void igMemoryPool_UpdateGlobalStatistics(long long size, long long sizeWithOverhead, int allocated) {
    long long bytes;
    if (allocated != 0) {
        bytes = (int)size;
        (*(long long *)&g_globalAllocated) += bytes;
        g_globalNetAllocated += bytes;
        if (g_globalNetAllocatedHigh < g_globalNetAllocated) {
            g_globalNetAllocatedHigh = g_globalNetAllocated;
        }
        bytes = (int)sizeWithOverhead;
        (*(long long *)&g_globalAllocatedWithOverhead) += bytes;
        g_globalNetAllocatedWithOverhead += bytes;
        if (g_globalNetAllocatedWithOverheadHigh < g_globalNetAllocatedWithOverhead) {
            g_globalNetAllocatedWithOverheadHigh = g_globalNetAllocatedWithOverhead;
        }
        (*(long long *)&g_globalAllocationCount) += 1;
        g_globalNetAllocationCount += 1;
        if (g_globalNetAllocationCountHigh < g_globalNetAllocationCount) {
            g_globalNetAllocationCountHigh = g_globalNetAllocationCount;
        }
    } else {
        bytes = (int)size;
        (*(long long *)&g_globalFreed) += bytes;
        g_globalNetAllocated -= bytes;
        (*(long long *)&g_globalFreedWithOverhead) += bytes;
        g_globalNetAllocatedWithOverhead -= bytes;
        (*(long long *)&g_globalFreeCount) += 1;
        g_globalNetAllocationCount -= 1;
    }
}

void igMemoryPool_EnableAllocationLock(int *status_out) {
    *status_out = g_resultFailure.v;
}

