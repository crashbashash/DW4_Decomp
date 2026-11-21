int igMemoryPool_Destruct(int extra0)
{
    return igObject_Destruct(extra0);
}

void * igObject_OperatorNew(int a0, int a1, int extra2) {
    return malloc(a1 + a0);
}

void igObject_OperatorDelete(void *block)
{
    free(block);
}

int (*g_outOfMemoryHandler)();

int igMemoryPool_HandleOutOfMemory(int pool, int size, int attempt) {
    if (g_outOfMemoryHandler != 0) {
        return g_outOfMemoryHandler();
    }
    return attempt == 4;
}

unsigned char g_igMemoryPool_defaultUpdateStatistics = 1;

void igMemoryPool_InitDefaults(void *pool) {
    ((igMemoryPool *)pool)->_updateStatistics = (unsigned char) g_igMemoryPool_defaultUpdateStatistics;
    igMemoryPool_RegisterPool((void **)pool);
}

void igMemoryPool_ReleaseDefaults(igMemoryPoolView *pool) {
    igMemoryPool_UnregisterPool((void **)pool);
}

igMemoryPoolView *Memory_GetDefaultHandleAllocator(void) {
    return Memory_GetAllocatorBySelector(1);
}

void * Memory_GetDefaultAllocator(void) {
    return (void *)(((int)Memory_GetAllocatorBySelector(2)));
}

int Memory_GetNonTrackedAllocator(void) {
    return ((int)Memory_GetAllocatorBySelector(3));
}

igMemoryDictionaryView *g_memoryDictionary;

void igMemoryDictionary_SetCurrent(void *dictionary) {
    void *current;

    current = (void *)((*(void * *)&g_memoryDictionary));
    if (current != dictionary) {
        if (current != 0) {
            (*(void * *)&g_memoryDictionary) = (void *)(0);
            ((igMemoryDictionaryView *)current)->Clear();
            ((igObject *)current)->release();
        }
        (*(void * *)&g_memoryDictionary) = (void *)(dictionary);
    }
}

igResult Memory_LookupAllocation(int address, int *poolOut) {
    int poolIndex;
    igMemoryDictionaryView *o = g_memoryDictionary;
    if (o != 0) {
        int x = o->GetValue(address, &poolIndex).get(); if (x == g_resultSuccess.v) {
            *poolOut = (int)igAllocator_ResolveEncodedIndex(poolIndex);
            if (*poolOut != 0) {
                return igResult(g_resultSuccess.v);
            }
        }
    }
    *poolOut = 0;
    return igResult(g_resultFailure.v);
}

igResult Memory_RegisterAllocation(int address, igMemoryPoolView *pool) {
    int dictionarySize;
    if (g_memoryDictionary == 0) {
        dictionarySize = 0x1000;
        igRegistry_GetValueInt(g_objectSystem->configRegistry, 2,"memoryDictionarySize", &dictionarySize, 0x1000, 0);
        g_memoryDictionary = (igMemoryDictionaryView *)igMemoryDictionary_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked));
        g_memoryDictionary->SetCapacity(dictionarySize);
        g_memoryDictionary->InitEntries();
        igMemoryDictionary_SetCurrent(g_memoryDictionary);
    }
    return g_memoryDictionary->Insert(address, pool->GetPoolIndex());
}

igResult Memory_UnregisterAllocation(int address, igMemoryPoolView *pool) {
    igMemoryDictionaryView *p = g_memoryDictionary;
    if (p != 0) {
        return p->Remove(address);
    }
    return igResult(g_resultFailure.v);
}

void igMemoryPool_RegisterPool(void **pool) {
    AllocatorRegistry *list;
    int idx;
    int flag;

    if (((igMemoryPoolView *)pool)->IsSecondaryAllocator() == 0) {
        list = g_primaryAllocatorList;
        idx = list->count;
        flag = 0;
    } else {
        flag = 1;
        list = g_secondaryAllocatorList;
        idx = list->count;
    }
    if (idx < 0x1F) {
        igMemoryPoolInfoList_Append(list, (igMemoryPoolView *)pool);
    } else {
        idx = igMemoryPoolInfoList_IndexOf(list, (igMemoryPoolView *)0);
        if (idx == -1) {
            idx = list->count;
            igMemoryPoolInfoList_Append(list, (igMemoryPoolView *)pool);
        } else {
            list->data[idx] = (igMemoryPoolView *)pool;
        }
    }
    flag = flag + (idx * 2);
    ((igMemoryPoolView *)pool)->SetPoolIndex(flag);
}

void igMemoryPool_UnregisterPool(void **pool) {
    int index;

    if (((igMemoryPoolView *)pool)->IsSecondaryAllocator() == 0) {
        index = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)((*(int * *)&g_primaryAllocatorList)), (igMemoryPoolView *)pool);
        if (index >= 0) {
            *(int *)(*(*(int * *)&g_primaryAllocatorList) + (index * 4)) = 0;
        }
    } else {
        index = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)((*(int * *)&g_secondaryAllocatorList)), (igMemoryPoolView *)pool);
        if (index >= 0) {
            *(int *)(*(*(int * *)&g_secondaryAllocatorList) + (index * 4)) = 0;
        }
    }
}

void *Memory_FindOwningAllocator(int address) {
    int secondaryIndex;
    igMemoryPoolView *secondary;
    igMemoryPoolView *primary;
    int primaryIndex;

    secondaryIndex = g_secondaryAllocatorList->count - 1;
    while (secondaryIndex >= 0) {
        secondary = (igMemoryPoolView *)g_secondaryAllocatorList->data[secondaryIndex];
        if ((secondary != 0) && (secondary->IsActive() != 0) && (secondary->OwnsAllocation((void *)address) != 0)) {
            return secondary;
        }
        secondaryIndex -= 1;
    }
    primaryIndex = g_primaryAllocatorList->count - 1;
    while (primaryIndex >= 0) {
        primary = (igMemoryPoolView *)g_primaryAllocatorList->data[primaryIndex];
        if ((primary != 0) && (primary->IsActive() != 0) && (primary->OwnsAllocation((void *)address) != 0)) {
            return primary;
        }
        primaryIndex -= 1;
    }
    return 0;
}

void igMemoryPool_TransferAllocation(int *result) {
    *result = g_resultFailure.v;
}

int igMemoryPool_CanTransferTo(void) {
    return 0;
}

int igMemoryPool_GetAllocationPoolIndex(void) {
    return -1;
}

