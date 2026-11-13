void FUN_002f08d0(igMemoryPool *arg0, char *arg1) {
    long long s4, s3, s2, s1, s0, s6, s7, s8;
    long long sp120, sp110, sp100, spF0;
    __int128 spE0;
    VT_2f08d0 *o = (VT_2f08d0 *)arg0;

    if (arg1 != 0 && *arg1 != 0) {
        FUN_00304430(DAT_004f90b0);
        FUN_00304680();
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
    spE0 = o->v144();
    FUN_00304430(DAT_004f9d60, (int)spF0, (int)sp100, (int)sp110, (int)sp120, (long long)(int)s8, (long long)(int)s7, (long long)(int)s6, (long long)(int)s0, (long long)(int)s1, (long long)(int)s2, (long long)(int)s3, (long long)(int)s4, (long long)spE0, (long long)o->v168());
    FUN_00304680();
}

void FUN_002f0a60(char *arg0) {
    if ((arg0 != 0) && (*arg0 != 0)) {
        FUN_00304430(DAT_004f90b0, arg0);
        FUN_00304680();
    }
    FUN_00304430(DAT_004f9fe0, DAT_00586f70[0], DAT_00586f78[0], ((int *)DAT_00586f80)[0], ((int *)DAT_00586f88)[0], DAT_00586f90[0], DAT_00586f98[0], ((int *)DAT_00586fa0)[0], (long long) ((int *)DAT_00586fa8)[0], (long long) DAT_00586fb0[0], (long long) DAT_00586fb8[0], (long long) ((int *)DAT_00586fc0)[0], (long long) ((int *)DAT_00586fc8)[0]);
    FUN_00304680();
}

void FUN_002f0b30(void) {

}

int FUN_002f0b40(void) {
    return 0;
}

bool FUN_002f0b50(int arg0, int arg1) {
    int s2;
    VM *o;
    int s1;
    VM *q;
    bool s0;
    s0 = false;
    s1 = ((L_2f0b50 * *)g_secondaryAllocatorList)[0]->count - 1;
    while (s1 >= 0) {
        o = (VM *)((L_2f0b50 * *)g_secondaryAllocatorList)[0]->data[s1];
        if (o != 0 && o->v132() != 0 && o->v108(arg1) != 0) {
            s0 = true;
        }
        s1--;
    }
    s2 = ((L_2f0b50 * *)g_primaryAllocatorList)[0]->count - 1;
    while (s2 >= 0) {
        q = (VM *)((L_2f0b50 * *)g_primaryAllocatorList)[0]->data[s2];
        if (q != 0 && q->v132() != 0 && q->v108(arg1) != 0) {
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

int FUN_002f0c90(void **arg0, int arg1) {
    int temp_v0;

    temp_v0 = ((DW4VC_216_1 *)(arg0))->vX((int)(strlen(arg1) + 1));
    strcpy(temp_v0, arg1);
    return temp_v0;
}

int FUN_002f0cf0(void **arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = ((DW4VC_220_2 *)(arg0))->vX((int)(strlen(arg1) + 1), (int)(arg2));
    strcpy(temp_v0, arg1);
    return temp_v0;
}

int FUN_002f0d60(void) {
    return 0;
}

void FUN_002f0d70(int dummy0, S0_2f0d70 *arg1) {
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 - 1));
        if (((unsigned long long) ((long long) arg1->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(arg1);
        }
    }
}

void FUN_002f0db0(int arg0) {
    *(int *)0x4C2160 = arg0;
}

void FUN_002f0dc0(void **arg0, int arg1, int arg2, int arg3) {
    void **temp_v0;

    if ((arg2 == 0) || (arg2 & DAT_004c2160[0])) {
        temp_v0 = (void **)(((DW4VC_356_0 *)(arg0))->vX());
        if (temp_v0 != 0) {
            ((DW4VC_104_2 *)(temp_v0))->vX((int)(arg1), (int)(arg3 + 1));
        }
    }
}

int FUN_002f1410(F_2f1410 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0) {
    char sp170[160];
    char spD0[160];
    int size;
    int flags;
    int flags2;
    Ctx_2f1410 *ctx;
    Ctx_2f1410 *ctx2;

    if (arg1 != 0) {
        size = ((int)Memory_GetBufferSize((void *)arg1));
        FUN_002e2190(sp170, 3, arg1, size, (unsigned short)arg0->v152(), arg4, 0, 0, arg5, arg6, arg7, ((Ctx_2f1410 *)((void *)Memory_GetCurrentContextAlias()))->v108(arg0));
        arg0->v268(sp170, arg3, arg_sp0 + 1);
        FUN_002e2300((int)sp170, -1);
    }
    arg1 = arg0->v232(arg1, arg2);
    if (arg1 != 0) {
        flags2 = arg0->v152() & 0xFFFF;
        ctx2 = (Ctx_2f1410 *)(((void *)Memory_GetCurrentContextAlias()));
        FUN_002e2190(spD0, 1, arg1, arg2, flags2, arg4, 0, 0, arg5, arg6, arg7, ctx2->v108(arg0));
        arg0->v268(spD0, arg3, arg_sp0 + 1);
        FUN_002e2300((int)spD0, -1);
    }
    return arg1;
}

void FUN_002f19f0(R_2f19f0 *arg0, F_2f19f0 *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10) {
    char spB0[156];
    int first;
    int total;
    int flags;
    unsigned int i;
    Ctx_2f19f0 *ctx;

    R_2f19f0 res = arg1->v248();
    if ((arg2 != 0) && (arg3 != 0) && (arg4 != 0) && (res.w == g_resultSuccess.v)) {
        first = *arg4;
        total = 0;
        for (i = 0; i < (unsigned int) (arg2 & 0xFFFF); i++) {
            total += arg3[i];
        }
        flags = arg1->v152() & 0xFFFF;
        ctx = (Ctx_2f19f0 *)(((void *)Memory_GetCurrentContextAlias()));
        FUN_002e2190(spB0, 1, first, total, flags, arg6, 0, 0, arg7, arg_sp0, arg_sp8, ctx->v108(arg1));
        arg1->v268(spB0, arg5, arg_sp10 + 1);
        FUN_002e2300((int)spB0, -1);
    }
    *arg0 = res;
}

void FUN_002f1b70(R_2f1b70 *arg0, F_2f1b70 *arg1, int arg2, int *arg3, int *arg4, int arg5, int arg6, int arg7, int arg_sp0, int arg_sp8, int arg_sp10, int arg_sp18) {
    char spA0[156];
    int first;
    int total;
    unsigned int i;
    Ctx_2f1b70 *ctx;

    R_2f1b70 res = arg1->v252();
    if ((arg2 != 0) && (arg3 != 0) && (arg4 != 0) && (res.w == g_resultSuccess.v)) {
        first = *arg4;
        total = 0;
        for (i = 0; i < (unsigned int) (arg2 & 0xFFFF); i++) {
            total += arg3[i];
        }
        ctx = (Ctx_2f1b70 *)(((void *)Memory_GetCurrentContextAlias()));
        FUN_002e2190(spA0, 1, first, total, 0, arg7, 0, 0, arg_sp0, arg_sp8, arg_sp10, ctx->v108(arg1));
        arg1->v268(spA0, arg6, arg_sp18 + 1);
        FUN_002e2300((int)spA0, -1);
    }
    *arg0 = res;
}

void FUN_002f1cd0(void **arg0, unsigned int arg1, int *arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg_sp0) {
    char spE0[160];
    int first;
    int total;
    unsigned int i;
    void **ctx;

    ((DW4VC_256_0 *)(arg0))->vX();
    if ((arg1 != 0) && (arg2 != 0)) {
        total = 0;
        first = *arg2;
        for (i = 0; i < arg1; i++) {
            if (arg2[i] != 0) {
                total += ((int)Memory_GetBufferSize((void *)arg2[i]));
            }
        }
        ctx = (void **)(((void **)Memory_GetCurrentContextAlias()));
        FUN_002e2190(spE0, 3, first, total, 0, arg4, 0, 0, arg5, arg6, arg7, ((DW4VC_108_1_2f1cd0 *)(ctx))->vX((int)(arg0)));
        ((DW4VC_268_3_2f1cd0 *)(arg0))->vX(spE0, (int)(arg3), (int)(arg_sp0 + 1));
        FUN_002e2300((int)spE0, -1);
    }
}

void Memory_InitializeAllocatorRegistries(igObject *rootAllocator) {
    int secondaryList;
    int primaryList;

    primaryList = ((int)igMemoryPoolInfoList_Allocate(0xC));
    if (primaryList != 0) {
        primaryList = ((int)igMemoryPoolInfoList_Init((RegistryList *)primaryList));
    }
    ((int *)g_primaryAllocatorList)[0] = primaryList;
    igMemoryPoolInfoList_Append((RegistryList *)primaryList, (void *)rootAllocator);
    ((char *)&rootAllocator->_refCount)[3] = 0;
    secondaryList = ((int)igMemoryPoolInfoList_Allocate(0xC));
    if (secondaryList != 0) {
        secondaryList = ((int)igMemoryPoolInfoList_Init((RegistryList *)secondaryList));
    }
    ((int *)g_secondaryAllocatorList)[0] = secondaryList;
}

void Memory_ShutdownAllocatorRegistries(void **rootAllocator) {
    igMemoryPoolInfoList_Release((RegistryList *)(((int *)g_primaryAllocatorList)[0]), 1);
    igMemoryPoolInfoList_Release((RegistryList *)(((int *)g_secondaryAllocatorList)[0]), 1);
    ((int *)g_primaryAllocatorList)[0] = 0;
    ((int *)g_secondaryAllocatorList)[0] = 0;
    ((RootAllocatorVtable *)(rootAllocator))->afterRegistriesCleared();
}

void FUN_002f2260(void *arg0) {
    *(unsigned char *)((char *)arg0 + 104) = (unsigned char) GPR_00554994;
}

void FUN_002f2270(void) {

}

void FUN_002f22f0(igMemoryPool *arg0) {
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

void FUN_002f2340(struct R2340 *arg0, int arg1, int arg2, int arg3) {
    long long a;
    long long b;

    if (arg3 != 0) {
        a = arg1;
        arg0->f8 = arg0->f8 + a;
        arg0->f24 = arg0->f24 + a;
        if (arg0->f32 < arg0->f24) {
            arg0->f32 = arg0->f24;
        }
        b = arg2;
        arg0->f40 = arg0->f40 + b;
        arg0->f56 = arg0->f56 + b;
        if (arg0->f64 < arg0->f56) {
            arg0->f64 = arg0->f56;
        }
        arg0->f72 = arg0->f72 + 1;
        arg0->f88 = arg0->f88 + 1;
        if (arg0->f96 < arg0->f88) {
            arg0->f96 = arg0->f88;
        }
    } else {
        a = arg1;
        b = arg2;
        arg0->f16 = arg0->f16 + a;
        arg0->f24 = arg0->f24 - a;
        arg0->f48 = arg0->f48 + b;
        arg0->f56 = arg0->f56 - b;
        arg0->f80 = arg0->f80 + 1;
        arg0->f88 = arg0->f88 - 1;
    }
}

void FUN_002f2450(long long arg0, long long arg1, int arg2) {
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

void Gap__Core__igMemoryPool__vfunc_34(int *status_out) {
    *status_out = g_resultFailure.v;
}

