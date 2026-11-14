int **FUN_002effb0(int **arg0) {
    igObject_ConstructHeader((igObject *)arg0);
    *arg0 = &DAT_0052f620[0];
    return arg0;
}

int Gap__Core__igObject__vfunc_00(int extra0)
{
    return Gap__Core__igObject__vfunc_00__002ff0a0(extra0);
}

void * FUN_002f0040(int a0, int a1, int extra2) {
    return (void *)(malloc((char *)a1 + a0, a1));
}

int thunk_free_2(int extra0)
{
    return free();
}

int FUN_002f0060(int arg0, int arg1, int arg2) {
    if (DAT_00586f50 != 0) {
        return DAT_00586f50();
    }
    return arg2 == 4;
}

void FUN_002f00a0(void *arg0) {
    *(unsigned char *)((char *)arg0 + 104) = (unsigned char) GPR_00554994;
    FUN_002f0370((void **)arg0);
}

void FUN_002f00c0(void) {
    Memory_GetAllocatorBySelector(1);
}

void * Memory_GetDefaultAllocator(void) {
    return (void *)(((int)Memory_GetAllocatorBySelector(2)));
}

int FUN_002f00e0(void) {
    return ((int)Memory_GetAllocatorBySelector(3));
}

void FUN_002f00f0(void *arg0) {
    void *temp_s0;

    temp_s0 = (void *)(((void * *)DAT_00586f68)[0]);
    if (temp_s0 != arg0) {
        if (temp_s0 != 0) {
            ((void * *)DAT_00586f68)[0] = (void *)(0);
            ((DW4VC_104_0 *)(((char *)(temp_s0) + 0)))->vX();
            *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
            if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_s0);
            }
        }
        ((void * *)DAT_00586f68)[0] = (void *)(arg0);
    }
}

R_2f0180 FUN_002f0180(int arg1, int *arg2) {
    int sp3C;
    O_2f0180 *o = ((O_2f0180 * *)DAT_00586f68)[0];
    if (o != 0) {
        int x = o->vX(arg1, &sp3C).get(); if (x == g_resultSuccess.v) {
            *arg2 = igAllocator_ResolveEncodedIndex(sp3C);
            if (*arg2 != 0) {
                return R_2f0180(g_resultSuccess.v);
            }
        }
    }
    *arg2 = 0;
    return R_2f0180(g_resultFailure.v);
}

R_2f0220 FUN_002f0220(int arg1, V_2f0220 *arg2) {
    int dictionarySize;
    if (DAT_00586f68[0] == 0) {
        dictionarySize = 0x1000;
        FUN_003065f0(((MemoryContextState *)g_objectSystem[0])->config, 2, text_memoryDictionarySize, &dictionarySize, 0x1000, 0);
        DAT_00586f68[0] = (V_2f0220 *)FUN_002c1070((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleNonTracked));
        DAT_00586f68[0]->vA(dictionarySize);
        DAT_00586f68[0]->vB();
        FUN_002f00f0(DAT_00586f68[0]);
    }
    return DAT_00586f68[0]->vC(arg1, arg2->vD());
}

R_2f0320 FUN_002f0320(int arg1, V_2f0220 *pool) {
    C_2f0320 *p = ((C_2f0320 * *)DAT_00586f68)[0];
    if (p != 0) {
        return p->vX(arg1);
    }
    return R_2f0320(g_resultFailure.v);
}

void FUN_002f0370(void **arg0) {
    PL *list;
    int idx;
    int flag;

    if (((DW4VC_116_0 *)(arg0))->vX() == 0) {
        list = ((PL * *)g_primaryAllocatorList)[0];
        idx = list->n;
        flag = 0;
    } else {
        flag = 1;
        list = ((PL * *)g_secondaryAllocatorList)[0];
        idx = list->n;
    }
    if (idx < 0x1F) {
        igMemoryPoolInfoList_Append((RegistryList *)list, (void *)arg0);
    } else {
        idx = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)list, (AllocatorLookupView *)0);
        if (idx == -1) {
            idx = list->n;
            igMemoryPoolInfoList_Append((RegistryList *)list, (void *)arg0);
        } else {
            list->d[idx] = arg0;
        }
    }
    flag = flag + (idx * 2);
    ((DW4VC_368_1 *)(arg0))->vX((int)flag);
}

void FUN_002f0460(void **arg0) {
    int temp_v0;

    if (((DW4VC_116_0 *)(arg0))->vX() == 0) {
        temp_v0 = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)(((int * *)g_primaryAllocatorList)[0]), (AllocatorLookupView *)arg0);
        if (temp_v0 >= 0) {
            *(int *)(*((int * *)g_primaryAllocatorList)[0] + (temp_v0 * 4)) = 0;
        }
    } else {
        temp_v0 = igMemoryPoolInfoList_IndexOf((AllocatorRegistry *)(((int * *)g_secondaryAllocatorList)[0]), (AllocatorLookupView *)arg0);
        if (temp_v0 >= 0) {
            *(int *)(*((int * *)g_secondaryAllocatorList)[0] + (temp_v0 * 4)) = 0;
        }
    }
}

void *Memory_FindOwningAllocator(int arg0) {
    int var_s2;
    VC_2f04f0 *temp_s1;
    VC_2f04f0 *temp_s2;
    int var_s1;

    var_s2 = g_secondaryAllocatorList[0]->count - 1;
    while (var_s2 >= 0) {
        temp_s1 = (VC_2f04f0 *)g_secondaryAllocatorList[0]->data[var_s2];
        if ((temp_s1 != 0) && (temp_s1->a() != 0) && (temp_s1->b(arg0) != 0)) {
            return temp_s1;
        }
        var_s2 -= 1;
    }
    var_s1 = g_primaryAllocatorList[0]->count - 1;
    while (var_s1 >= 0) {
        temp_s2 = (VC_2f04f0 *)g_primaryAllocatorList[0]->data[var_s1];
        if ((temp_s2 != 0) && (temp_s2->a() != 0) && (temp_s2->b(arg0) != 0)) {
            return temp_s2;
        }
        var_s1 -= 1;
    }
    return 0;
}

void FUN_002f0620(int *arg0) {
    *arg0 = g_resultFailure.v;
}

int FUN_002f0630(void) {
    return 0;
}

int FUN_002f0640(void) {
    return -1;
}

