igMetaObject *igDependencyMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igDependencyMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c8090();
    return g_igDependencyMetaField_metaObject[0];
}

int igDependencyMetaField_GetVTable(void) {
    igDependencyMetaField u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)&u);
    u._vtable = (int)&DAT_00531740[0];
    q0 = (S_ref *)&u._fieldList;
    *(int *)q0 = 0;
    u._vtable = (int)&DAT_00532260[0];
    temp_s0 = *(int *)((char *)&u + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    u._vtable = (int)&DAT_00531740[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = (char *)&u._fieldName;
    u._vtable = (int)&g_igMetaField_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002c8090(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDependencyMetaField_Register);
}

void igDependencyMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igDependencyMetaField_metaObject),
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igDependencyMetaField_GetMetaObject,
        igDependencyMetaField_className,
        0x38, /* instance size */
        igDependencyMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igDependencyMetaField_callbackList /* callback list */
    );
}

void thunk_igDependencyMetaField_GetMetaObject(void) {
    igDependencyMetaField_GetMetaObject();
}

void FUN_002c8120(void) {
    void *temp_s0;

    if (DAT_00586780[0] == 0) {
        DAT_00586780[0] = (void *)(((void *)igMetaObject_CreateInstance((CreateMeta *)g_igDependencyMetaField_metaObject[0], (MemoryPool *)(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
        temp_s0 = (void *)(DAT_00586780[0]);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained((PointerList *)(((void *)FUN_002fc250())), (RefHeader *)temp_s0);
            {
                void *held = (void *)DAT_00586780[0];
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            *(short *)((char *)(DAT_00586780[0]) + 18) = (short) (*(int *)((char *)(((void *)FUN_002fc250())) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)DAT_00586780[0]);
        }
    }
}

int FUN_002c81f0(void) {
    if (((int *)DAT_00586780)[0] == 0) {
        FUN_002c8090();
    }
    return ((int *)DAT_00586780)[0];
}

int Gap__Core__igDependencyMetaField__vfunc_25(void) {
    return 8;
}

void Gap__Core__igDependencyMetaField__vfunc_11(void *arg0) {
    FUN_002c8250(*(int *)((char *)arg0 + 52));
}

void FUN_002c8250(int arg0) {
    void *sp3C;
    void *sp38;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0;
    int temp_v0_2;
    int var_v0_2;
    int var_v0_4;
    void *temp_s0;
    void *temp_s0_2;
    void *var_v0;
    void *var_v0_3;

    temp_s0 = (void *)(((void *)FUN_002bba00(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    if (&text_before[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = ((int)StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = ((int)StringPool_Construct((S_2eadf0 *)var_v0_2));
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_before[0])));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0);
    }
    temp_s0_2 = (void *)(((void *)FUN_002bba00(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    if (&text_after[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_4 = ((int)StringPool_Allocate(0x10));
            if (var_v0_4 != 0) {
                var_v0_4 = ((int)StringPool_Construct((S_2eadf0 *)var_v0_4));
            }
            g_stringPool[0] = var_v0_4;
        }
        var_v0_3 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_after[0])));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName((igMetaField *)temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0_2);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_s0_2);
    }
}

