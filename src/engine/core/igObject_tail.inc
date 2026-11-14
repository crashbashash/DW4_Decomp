int igMemoryPool_Destruct(int extra0)
{
    return igObject_Destruct(extra0);
}

void * igObject_OperatorNew(int a0, int a1, int extra2) {
    return (void *)(malloc((char *)a1 + a0, a1));
}

int igObject_OperatorDelete(int extra0)
{
    return free();
}

int igMemoryPool_HandleOutOfMemory(int arg0, int arg1, int arg2) {
    if (DAT_00586f50 != 0) {
        return DAT_00586f50();
    }
    return arg2 == 4;
}

void igMemoryPool_InitDefaults(void *arg0) {
    *(unsigned char *)((char *)arg0 + 104) = (unsigned char) GPR_00554994;
    igMemoryPool_RegisterPool((void **)arg0);
}

void igMemoryPool_ReleaseDefaults(igMemoryPoolView *pool) {
    igMemoryPool_UnregisterPool((void **)pool);
}

void Memory_GetDefaultHandleAllocator(void) {
    Memory_GetAllocatorBySelector(1);
}

void * Memory_GetDefaultAllocator(void) {
    return (void *)(((int)Memory_GetAllocatorBySelector(2)));
}

int Memory_GetNonTrackedAllocator(void) {
    return ((int)Memory_GetAllocatorBySelector(3));
}

void igMemoryDictionary_SetCurrent(void *arg0) {
    void *temp_s0;

    temp_s0 = (void *)(((void * *)DAT_00586f68)[0]);
    if (temp_s0 != arg0) {
        if (temp_s0 != 0) {
            ((void * *)DAT_00586f68)[0] = (void *)(0);
            ((igMemoryDictionaryView *)temp_s0)->vfunc_26();
            *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_s0);
            }
        }
        ((void * *)DAT_00586f68)[0] = (void *)(arg0);
    }
}

igResult Memory_LookupAllocation(int arg1, int *arg2) {
    int sp3C;
    igMemoryDictionaryView *o = DAT_00586f68[0];
    if (o != 0) {
        int x = o->vfunc_30(arg1, &sp3C).get(); if (x == g_resultSuccess.v) {
            *arg2 = (int)igAllocator_ResolveEncodedIndex(sp3C);
            if (*arg2 != 0) {
                return igResult(g_resultSuccess.v);
            }
        }
    }
    *arg2 = 0;
    return igResult(g_resultFailure.v);
}

igResult Memory_RegisterAllocation(int arg1, igMemoryPoolView *arg2) {
    int dictionarySize;
    if (DAT_00586f68[0] == 0) {
        dictionarySize = 0x1000;
        igRegistry_GetValueInt((int)((ObjectSystemView *)g_objectSystem[0])->configRegistry, 2, text_memoryDictionarySize, &dictionarySize, 0x1000, 0);
        DAT_00586f68[0] = (igMemoryDictionaryView *)igMemoryDictionary_Create((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked));
        DAT_00586f68[0]->vfunc_24(dictionarySize);
        DAT_00586f68[0]->vfunc_25();
        igMemoryDictionary_SetCurrent(DAT_00586f68[0]);
    }
    return DAT_00586f68[0]->vfunc_31(arg1, arg2->GetPoolIndex());
}

igResult Memory_UnregisterAllocation(int arg1, igMemoryPoolView *pool) {
    igMemoryDictionaryView *p = DAT_00586f68[0];
    if (p != 0) {
        return p->vfunc_32(arg1);
    }
    return igResult(g_resultFailure.v);
}

void igMemoryPool_RegisterPool(void **arg0) {
    AllocatorRegistry *list;
    int idx;
    int flag;

    if (((igMemoryPoolView *)arg0)->vfunc_29() == 0) {
        list = g_primaryAllocatorList[0];
        idx = list->count;
        flag = 0;
    } else {
        flag = 1;
        list = g_secondaryAllocatorList[0];
        idx = list->count;
    }
    if (idx < 0x1F) {
        igMemoryPoolInfoList_Append(list, (igMemoryPoolView *)arg0);
    } else {
        idx = igMemoryPoolInfoList_IndexOf(list, (igMemoryPoolView *)0);
        if (idx == -1) {
            idx = list->count;
            igMemoryPoolInfoList_Append(list, (igMemoryPoolView *)arg0);
        } else {
            list->data[idx] = (igMemoryPoolView *)arg0;
        }
    }
    flag = flag + (idx * 2);
    ((igMemoryPoolView *)arg0)->SetPoolIndex(flag);
}

void igMemoryPool_UnregisterPool(void **arg0) {
    int temp_v0;

    if (((igMemoryPoolView *)arg0)->vfunc_29() == 0) {
        temp_v0 = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)(((int * *)g_primaryAllocatorList)[0]), (igMemoryPoolView *)arg0);
        if (temp_v0 >= 0) {
            *(int *)(*((int * *)g_primaryAllocatorList)[0] + (temp_v0 * 4)) = 0;
        }
    } else {
        temp_v0 = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)(((int * *)g_secondaryAllocatorList)[0]), (igMemoryPoolView *)arg0);
        if (temp_v0 >= 0) {
            *(int *)(*((int * *)g_secondaryAllocatorList)[0] + (temp_v0 * 4)) = 0;
        }
    }
}

void *Memory_FindOwningAllocator(int arg0) {
    int var_s2;
    igMemoryPoolView *temp_s1;
    igMemoryPoolView *temp_s2;
    int var_s1;

    var_s2 = g_secondaryAllocatorList[0]->count - 1;
    while (var_s2 >= 0) {
        temp_s1 = (igMemoryPoolView *)g_secondaryAllocatorList[0]->data[var_s2];
        if ((temp_s1 != 0) && (temp_s1->isActive() != 0) && (temp_s1->OwnsAllocation((void *)arg0) != 0)) {
            return temp_s1;
        }
        var_s2 -= 1;
    }
    var_s1 = g_primaryAllocatorList[0]->count - 1;
    while (var_s1 >= 0) {
        temp_s2 = (igMemoryPoolView *)g_primaryAllocatorList[0]->data[var_s1];
        if ((temp_s2 != 0) && (temp_s2->isActive() != 0) && (temp_s2->OwnsAllocation((void *)arg0) != 0)) {
            return temp_s2;
        }
        var_s1 -= 1;
    }
    return 0;
}

void igMemoryPool_TransferAllocation(int *arg0) {
    *arg0 = g_resultFailure.v;
}

int igMemoryPool_CanTransferTo(void) {
    return 0;
}

int igMemoryPool_GetAllocationPoolIndex(void) {
    return -1;
}

