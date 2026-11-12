void ***FUN_002e2fb0(void) {
    void **a;
    void **al;
    void **cell;
    void **t;
    int name;
    int pool;
    RC *old;
    void *nw;
    int *hdr;
    int c;
    if (DAT_00586e18[0] == 0) {
        al = (void **)FUN_002f8a20();
        if (GPR_00554c14 != 0) {
            a = al;
        } else {
            a = (void **)Memory_GetAllocatorBySelector(DAT_00587060[0]);
        }
        cell = t = (void **)((VC_216 *)a)->vX(4);
        if (t != 0) { *t = 0; }
        DAT_00586e18[0] = cell;
        name = DAT_004c2128[0];
        if (g_stringPool[0] == 0) {
            pool = ((int)FUN_002eb010(16));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((S_2eadf0 *)pool));
            }
            g_stringPool[0] = pool;
        }
        nw = ((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)name));
        old = (RC *)*cell;
        if (old != 0) {
            hdr = (int *)((char *)old - 8);
            c = *(int *)((char *)old - 4) - 1;
            *(int *)((char *)old - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
            }
        }
        *cell = nw;
    }
    return &DAT_00586e18[0];
}

void FUN_002e30b0(int *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    void *temp_a0;
    void *temp_s0;

    if (g_stringPool[0] == 0) {
        var_v0 = ((int)FUN_002eb010(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1)));
    temp_a0 = (void *)arg0[3];
    if (temp_a0 != 0) {
        temp_a1 = (int *)((char *)temp_a0 - 8);
        temp_v1 = *(int *)((char *)(temp_a0) - 4) - 1;
        *(int *)((char *)(temp_a0) - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0[3] = (int)temp_s0;
}

void Gap__igAdxFile__vfunc_38(void **arg0, long long arg1) {
    signed char want = (signed char)arg1;
    signed char c;
    do {
        c = (signed char)((VCa *)arg0)->vX();
    } while (want != c && c != -1);
}

void FUN_002e31b0(int a0, int a1)
{
    *(int *)((char *)a0 + 20) = a1;
}

int FUN_002e31c0(char *arg0) {
    char c;

    if (arg0 == 0) {
        return 0;
    }
    c = *arg0;
    if (c == 0x2F || c == 0x5C) {
        return 1;
    }
    return ((int)strchr(arg0, 0x3A)) != 0;
}

int FUN_002e3220(int arg0) {
    if (arg0 == 0) {
        return 0;
    }
    if ((((int)strchr(arg0, 0x2F)) == 0) && (((int)strchr(arg0, 0x5C)) == 0)) {
        return 0;
    }
    return 1;
}

void FUN_002e3280(int arg0) {
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v1_2;
    int var_v0;
    void **temp_s0;
    void **temp_s1;
    void *temp_a0;
    void *temp_s0_2;
    void *temp_v1;

    if (arg0 == 0) {
        temp_s0 = (void **)(*FUN_002e2fb0());
        if (temp_s0 != 0) {
            if (temp_s0 != 0) {
                temp_v1 = (void *)(*temp_s0);
                if (temp_v1 != 0) {
                    temp_a1 = (int *)((char *)temp_v1 - 8);
                    temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
                    *(int *)((char *)(temp_v1) - 4) = temp_v0;
                    if (temp_v0 == 0) {
                        StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
                    }
                }
            }
            Memory_FreeBuffer(temp_s0);
        }
    } else {
        temp_s1 = (void **)(*FUN_002e2fb0());
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)FUN_002eb010(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        temp_s0_2 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg0)));
        temp_a0 = (void *)(*temp_s1);
        if (temp_a0 != 0) {
            temp_a1_2 = (int *)((char *)temp_a0 - 8);
            temp_v1_2 = *(int *)((char *)(temp_a0) - 4) - 1;
            *(int *)((char *)(temp_a0) - 4) = temp_v1_2;
            if (temp_v1_2 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
            }
        }
        *temp_s1 = temp_s0_2;
    }
}

void Gap__igAdxFile__vfunc_26(void **arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4) {
    arg3(((DW4VC_108_2 *)(arg0))->vX(arg1, 1, arg2), arg4);
}

int FUN_002e34a0(void) {
    return **((int **)FUN_002e2fb0());
}

int FUN_002e34d0(char **arg0, char *arg1, int arg2) {
    char *temp_s1;
    char *temp_v0;
    char temp_v1;
    unsigned int var_s0;

    temp_s1 = *arg0;
    *arg1 = 0;
    if ((temp_s1 == 0) || (*temp_s1 == 0)) {
        return 0;
    }
    temp_v0 = strchr(temp_s1, 0x2C);
    if (temp_v0 == 0) {
        var_s0 = ((unsigned int)strlen(temp_s1));
        if ((unsigned int) (arg2 - 2) <= var_s0) {
            return 0;
        }
        strcpy(arg1, temp_s1);
        *arg0 = 0;
    } else {
        var_s0 = temp_v0 - temp_s1;
        if ((unsigned int) (arg2 - 2) <= var_s0) {
            return 0;
        }
        strncpy(arg1, temp_s1, var_s0);
        arg1[var_s0] = 0;
        *arg0 = temp_v0 + 1;
    }
    if (strcmp(arg1, ((char *)DAT_004f9468)) == 0) {
        *arg1 = 0;
    } else {
        temp_v1 = arg1[var_s0 - 1];
        if (temp_v1 != 0x2F) {
            if (temp_v1 != 0x5C) {
                strcat(arg1, ((char *)DAT_004f9a48));
            }
        }
    }
    return 1;
}

int Gap__igAdxFile__vfunc_39(struct AX *arg0, int arg1) {
    int s0;
    int *a0;
    int *hdr;
    int v;
    int obj;
    if (g_stringPool[0] == 0) {
        obj = ((int)FUN_002eb010(0x10));
        if (obj != 0) {
            obj = ((int)StringPool_Construct((struct S_2eadf0 *)obj));
        }
        g_stringPool[0] = obj;
    }
    s0 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1);
    a0 = (int *)arg0->f40;
    if (a0 != 0) {
        hdr = a0 - 2;
        v = a0[-1] - 1;
        a0[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*hdr), (int)hdr);
        }
    }
    arg0->f40 = s0;
    return arg1;
}

