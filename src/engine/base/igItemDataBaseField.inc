igMetaObject *igItemDataBaseField_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228410();
    return g_igItemDataBaseField_metaObject[0];
}

int igItemDataBaseField_GetVTable(void) {
    union U_5 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0052c240[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = &u.b[12];
    u.vt = (int)&g_igMetaField_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00228410(void)
{
    igMetaObject_RunStaticInit(igItemDataBaseField_Register);
}

void igItemDataBaseField_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemDataBaseField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igItemDataBaseField_GetMetaObject,
        igItemDataBaseField_className,
        0x38, /* instance size */
        igItemDataBaseField_GetVTable,
        0,
        0, /* extra callback item */
        g_igItemDataBaseField_callbackList /* callback list */
    );
}

void thunk_igItemDataBaseField_GetMetaObject(void) {
    igItemDataBaseField_GetMetaObject();
}

void FUN_002284a0(void) {
    void *temp_s0;

    if (DAT_0056d9e0[0] == 0) {
        DAT_0056d9e0[0] = (int)(igMetaObject_CreateInstance(g_igItemDataBaseField_metaObject[0], Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
        temp_s0 = (void *)(DAT_0056d9e0[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_0056d9e0[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_0056d9e0[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_0056d9e0[0]);
        }
    }
}

int FUN_00228570(void) {
    if (DAT_0056d9e0[0] == 0) {
        FUN_00228410();
    }
    return DAT_0056d9e0[0];
}

int Gap__igItemDataBaseField__vfunc_25(void) {
    return 0xC;
}

void Gap__igItemDataBaseField__vfunc_11(void *arg0) {
    FUN_002285d0(*(int *)((char *)arg0 + 52));
}

void FUN_002285d0(int arg0) {
    void *sp3C;
    void *sp38;
    void *sp34;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int var_v0_2;
    int var_v0_4;
    int var_v0_6;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *var_v0;
    void *var_v0_3;
    void *var_v0_5;

    temp_s0 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
    if (&text_interfacedMeta[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = StringPool_Allocate(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(g_stringPool[0], &text_interfacedMeta[0]));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    *(int *)((char *)(temp_s0) + 56) = FUN_002be610();
    igMetaField_FinalizeDescriptor(temp_s0);
    ObjectList_AppendRetained(arg0, temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
    temp_s0_2 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
    if (&text_itemList[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_4 = StringPool_Allocate(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            g_stringPool[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(g_stringPool[0], &text_itemList[0]));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    *(int *)((char *)(temp_s0_2) + 56) = FUN_002c8e50();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    igMetaField_FinalizeDescriptor(temp_s0_2);
    ObjectList_AppendRetained(arg0, temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_2);
    }
    temp_s0_3 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0])));
    if (&text_itemName[0] == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_6 = StringPool_Allocate(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = StringPool_Construct(var_v0_6);
            }
            g_stringPool[0] = var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(g_stringPool[0], &text_itemName[0]));
    }
    sp34 = (void *)(var_v0_5);
    igMetaField_SetFieldName(temp_s0_3, &sp34);
    if (sp34 != 0) {
        temp_a1_3 = (int *)((char *)sp34 - 8);
        temp_v0_3 = *(int *)((char *)(sp34) - 4) - 1;
        *(int *)((char *)(sp34) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s0_3) + 8) = 8;
    *(int *)((char *)(temp_s0_3) + 56) = FUN_002b9120();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    igMetaField_FinalizeDescriptor(temp_s0_3);
    ObjectList_AppendRetained(arg0, temp_s0_3);
    *(int *)((char *)(temp_s0_3) + 4) = (int)((int) (*(int *)((char *)(temp_s0_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_3);
    }
    igMetaObject_EnsureRegistered();
    FUN_002c8f30();
    FUN_002b9200();
}

