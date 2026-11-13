igMetaObject *igCharMetricsMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsMetaField_RunStaticInit();
    return g_igCharMetricsMetaField_metaObject[0];
}

int igCharMetricsMetaField_GetVTable(void) {
    union U_452a10 u;
    int temp_s0;
    S_ref *q0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q1;

    igMetaField_Init(u.b);
    u.vt = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00541680[0];
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
    u.vt = (int)&g_igMetaField_vtable[0];
    if (&u.b[12] != 0) {
        temp_v1 = *(int **)&u.b[12];
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

void igCharMetricsMetaField_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsMetaField_Register);
}

void igCharMetricsMetaField_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetricsMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igCharMetricsMetaField_GetMetaObject,
        igCharMetricsMetaField_className,
        0x38, /* instance size */
        igCharMetricsMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igCharMetricsMetaField_callbackList /* callback list */
    );
}

void thunk_igCharMetricsMetaField_GetMetaObject(void) {
    igCharMetricsMetaField_GetMetaObject();
}

void FUN_00452b70(void) {
    void *temp_s0;

    if (DAT_0058c650[0] == 0) {
        DAT_0058c650[0] = (void *)(igMetaObject_CreateInstance((int)g_igCharMetricsMetaField_metaObject[0], Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
        temp_s0 = (void *)(DAT_0058c650[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(FUN_002fc250(), temp_s0);
            {
                void *held = (void *)DAT_0058c650[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_0058c650[0]) + 18) = (short) (*(int *)((char *)(FUN_002fc250()) + 12) - 1);
            igMetaField_FinalizeDescriptor(DAT_0058c650[0]);
        }
    }
}

int FUN_00452c40(void) {
    if (DAT_0058c650[0] == 0) {
        igCharMetricsMetaField_RunStaticInit();
    }
    return (int)DAT_0058c650[0];
}

int Gap__Gui__igCharMetricsMetaField__vfunc_25(void) {
    return 0x28;
}

void Gap__Gui__igCharMetricsMetaField__vfunc_11(void *arg0) {
    FUN_00452ca0(*(int *)((char *)arg0 + 52));
}

void FUN_00452ca0(int arg0) {
    void *sp4C;
    void *sp48;
    void *sp44;
    void *sp40;
    void *sp3C;
    void *sp38;
    int *temp_a1;
    int *temp_a1_2;
    int *temp_a1_3;
    int *temp_a1_4;
    int *temp_a1_5;
    int *temp_a1_6;
    int temp_v0;
    int temp_v0_2;
    int temp_v0_3;
    int temp_v0_4;
    int temp_v0_5;
    int temp_v0_6;
    int var_v0_10;
    int var_v0_12;
    int var_v0_2;
    int var_v0_4;
    int var_v0_6;
    int var_v0_8;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s1_3;
    void *temp_s1_4;
    void *temp_s1_5;
    void *temp_s1_6;
    void *var_v0;
    void *var_v0_11;
    void *var_v0_3;
    void *var_v0_5;
    void *var_v0_7;
    void *var_v0_9;

    temp_s1 = (void *)(FUN_002b5fe0(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_charNumber[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = StringPool_Allocate(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = StringPool_Construct(var_v0_2);
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(g_stringPool[0], &text_charNumber[0]));
    }
    sp4C = (void *)(var_v0);
    igMetaField_SetFieldName(temp_s1, &sp4C);
    if (sp4C != 0) {
        temp_a1 = (int *)((char *)sp4C - 8);
        temp_v0 = *(int *)((char *)(sp4C) - 4) - 1;
        *(int *)((char *)(sp4C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    *(int *)((char *)(temp_s1) + 8) = 0;
    igMetaField_FinalizeDescriptor(temp_s1);
    ObjectList_AppendRetained(arg0, temp_s1);
    *(int *)((char *)(temp_s1) + 4) = (int)((int) (*(int *)((char *)(temp_s1) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1);
    }
    temp_s1_2 = (void *)(FUN_002c45f0(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_step[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_4 = StringPool_Allocate(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = StringPool_Construct(var_v0_4);
            }
            g_stringPool[0] = var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(g_stringPool[0], &text_step[0]));
    }
    sp48 = (void *)(var_v0_3);
    igMetaField_SetFieldName(temp_s1_2, &sp48);
    if (sp48 != 0) {
        temp_a1_2 = (int *)((char *)sp48 - 8);
        temp_v0_2 = *(int *)((char *)(sp48) - 4) - 1;
        *(int *)((char *)(sp48) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_2, temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s1_2) + 8) = 4;
    igMetaField_FinalizeDescriptor(temp_s1_2);
    ObjectList_AppendRetained(arg0, temp_s1_2);
    *(int *)((char *)(temp_s1_2) + 4) = (int)((int) (*(int *)((char *)(temp_s1_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_2);
    }
    temp_s1_3 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_offset[0] == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_6 = StringPool_Allocate(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = StringPool_Construct(var_v0_6);
            }
            g_stringPool[0] = var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(g_stringPool[0], &text_offset[0]));
    }
    sp44 = (void *)(var_v0_5);
    igMetaField_SetFieldName(temp_s1_3, &sp44);
    if (sp44 != 0) {
        temp_a1_3 = (int *)((char *)sp44 - 8);
        temp_v0_3 = *(int *)((char *)(sp44) - 4) - 1;
        *(int *)((char *)(sp44) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_3, temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s1_3) + 8) = 8;
    igMetaField_FinalizeDescriptor(temp_s1_3);
    ObjectList_AppendRetained(arg0, temp_s1_3);
    *(int *)((char *)(temp_s1_3) + 4) = (int)((int) (*(int *)((char *)(temp_s1_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_3);
    }
    temp_s1_4 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_size_2[0] == 0) {
        var_v0_7 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_8 = StringPool_Allocate(0x10);
            if (var_v0_8 != 0) {
                var_v0_8 = StringPool_Construct(var_v0_8);
            }
            g_stringPool[0] = var_v0_8;
        }
        var_v0_7 = (void *)(StringPool_Intern(g_stringPool[0], &text_size_2[0]));
    }
    sp40 = (void *)(var_v0_7);
    igMetaField_SetFieldName(temp_s1_4, &sp40);
    if (sp40 != 0) {
        temp_a1_4 = (int *)((char *)sp40 - 8);
        temp_v0_4 = *(int *)((char *)(sp40) - 4) - 1;
        *(int *)((char *)(sp40) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_4, temp_a1_4);
        }
    }
    *(int *)((char *)(temp_s1_4) + 8) = 0x10;
    igMetaField_FinalizeDescriptor(temp_s1_4);
    ObjectList_AppendRetained(arg0, temp_s1_4);
    *(int *)((char *)(temp_s1_4) + 4) = (int)((int) (*(int *)((char *)(temp_s1_4) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_4) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_4);
    }
    temp_s1_5 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_texCoordMin[0] == 0) {
        var_v0_9 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_10 = StringPool_Allocate(0x10);
            if (var_v0_10 != 0) {
                var_v0_10 = StringPool_Construct(var_v0_10);
            }
            g_stringPool[0] = var_v0_10;
        }
        var_v0_9 = (void *)(StringPool_Intern(g_stringPool[0], &text_texCoordMin[0]));
    }
    sp3C = (void *)(var_v0_9);
    igMetaField_SetFieldName(temp_s1_5, &sp3C);
    if (sp3C != 0) {
        temp_a1_5 = (int *)((char *)sp3C - 8);
        temp_v0_5 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0_5;
        if (temp_v0_5 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_5, temp_a1_5);
        }
    }
    *(int *)((char *)(temp_s1_5) + 8) = 0x18;
    igMetaField_FinalizeDescriptor(temp_s1_5);
    ObjectList_AppendRetained(arg0, temp_s1_5);
    *(int *)((char *)(temp_s1_5) + 4) = (int)((int) (*(int *)((char *)(temp_s1_5) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_5) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_5);
    }
    temp_s1_6 = (void *)(FUN_00187b50(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0])));
    if (&text_texCoordMax[0] == 0) {
        var_v0_11 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_12 = StringPool_Allocate(0x10);
            if (var_v0_12 != 0) {
                var_v0_12 = StringPool_Construct(var_v0_12);
            }
            g_stringPool[0] = var_v0_12;
        }
        var_v0_11 = (void *)(StringPool_Intern(g_stringPool[0], &text_texCoordMax[0]));
    }
    sp38 = (void *)(var_v0_11);
    igMetaField_SetFieldName(temp_s1_6, &sp38);
    if (sp38 != 0) {
        temp_a1_6 = (int *)((char *)sp38 - 8);
        temp_v0_6 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_6;
        if (temp_v0_6 == 0) {
            StringChunk_ReleaseHeader(*temp_a1_6, temp_a1_6);
        }
    }
    *(int *)((char *)(temp_s1_6) + 8) = 0x20;
    igMetaField_FinalizeDescriptor(temp_s1_6);
    ObjectList_AppendRetained(arg0, temp_s1_6);
    *(int *)((char *)(temp_s1_6) + 4) = (int)((int) (*(int *)((char *)(temp_s1_6) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_6) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s1_6);
    }
}

