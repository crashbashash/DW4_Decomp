igMetaObject *g_igCharMetricsMetaField_metaObject;
void *g_igCharMetricsMetaField_instance;

igMetaObject *igCharMetricsMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igCharMetricsMetaField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharMetricsMetaField_RunStaticInit();
    return g_igCharMetricsMetaField_metaObject;
}

int igCharMetricsMetaField_GetVTable(void) {
    union U_452a10 u;
    int temp_s0;
    S_ref *q0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q1;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igCompoundMetaField_vtable[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&g_igCharMetricsMetaField_vtable[0];
    temp_s0 = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igCompoundMetaField_vtable[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)q0);
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
                StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void igCharMetricsMetaField_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igCharMetricsMetaField_Register);
}

static igMetaObjectCallback g_igCharMetricsMetaField_callbackList[] = { FUN_00452b70, 0 };

CallbackArray *igCharMetricsMetaField_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCharMetricsMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igCharMetricsMetaField_GetMetaObject,
        "igCharMetricsMetaField",
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

    if (g_igCharMetricsMetaField_instance == 0) {
        g_igCharMetricsMetaField_instance = (void *)(igMetaObject_CreateInstance((igMetaObject *)((int)g_igCharMetricsMetaField_metaObject), (igMemoryPoolView *)((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
        temp_s0 = (void *)(g_igCharMetricsMetaField_instance);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(Gap::Core::igMetaField::getMetaFieldTypes(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igCharMetricsMetaField_instance;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            *(short *)((char *)(g_igCharMetricsMetaField_instance) + 18) = (short) (*(int *)((char *)(Gap::Core::igMetaField::getMetaFieldTypes()) + 12) - 1);
            ((Gap::Core::igMetaField *)g_igCharMetricsMetaField_instance)->validate();
        }
    }
}

int FUN_00452c40(void) {
    if (g_igCharMetricsMetaField_instance == 0) {
        igCharMetricsMetaField_RunStaticInit();
    }
    return (int)g_igCharMetricsMetaField_instance;
}

int Gap__Gui__igCharMetricsMetaField__vfunc_25(void) {
    return 0x28;
}

void igCharMetricsMetaField_InitDefaults(igCharMetricsMetaField *self) {
    FUN_00452ca0(self->_fieldList);
}

void FUN_00452ca0(int arg0) {
    void *charNumberName;
    void *stepName;
    void *offsetName;
    void *sizeName;
    void *texCoordMinName;
    void *texCoordMaxName;
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

    temp_s1 = (void *)(igUnsignedShortMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("charNumber" == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_2 = (int)(StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = (int)(StringPool_Construct((StringPool *)var_v0_2));
            }
            g_stringPool = (StringPool *)var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(g_stringPool, "charNumber"));
    }
    charNumberName = (void *)(var_v0);
    ((Gap::Core::igMetaField *)temp_s1)->setFieldName(&charNumberName);
    if (charNumberName != 0) {
        temp_a1 = (int *)((char *)charNumberName - 8);
        temp_v0 = *(int *)((char *)(charNumberName) - 4) - 1;
        *(int *)((char *)(charNumberName) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1), (StringTokenHeader *)temp_a1);
        }
    }
    *(int *)((char *)(temp_s1) + 8) = 0;
    ((Gap::Core::igMetaField *)temp_s1)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1);
    *(int *)((char *)(temp_s1) + 4) = (int)((int) (*(int *)((char *)(temp_s1) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1);
    }
    temp_s1_2 = (void *)(igFloatMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("step" == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_4 = (int)(StringPool_Allocate(0x10));
            if (var_v0_4 != 0) {
                var_v0_4 = (int)(StringPool_Construct((StringPool *)var_v0_4));
            }
            g_stringPool = (StringPool *)var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(g_stringPool, "step"));
    }
    stepName = (void *)(var_v0_3);
    ((Gap::Core::igMetaField *)temp_s1_2)->setFieldName(&stepName);
    if (stepName != 0) {
        temp_a1_2 = (int *)((char *)stepName - 8);
        temp_v0_2 = *(int *)((char *)(stepName) - 4) - 1;
        *(int *)((char *)(stepName) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_2), (StringTokenHeader *)temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s1_2) + 8) = 4;
    ((Gap::Core::igMetaField *)temp_s1_2)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1_2);
    *(int *)((char *)(temp_s1_2) + 4) = (int)((int) (*(int *)((char *)(temp_s1_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1_2);
    }
    temp_s1_3 = (void *)(igVec2fMetaField_CreateInstance(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("offset" == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_6 = (int)(StringPool_Allocate(0x10));
            if (var_v0_6 != 0) {
                var_v0_6 = (int)(StringPool_Construct((StringPool *)var_v0_6));
            }
            g_stringPool = (StringPool *)var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(g_stringPool, "offset"));
    }
    offsetName = (void *)(var_v0_5);
    ((Gap::Core::igMetaField *)temp_s1_3)->setFieldName(&offsetName);
    if (offsetName != 0) {
        temp_a1_3 = (int *)((char *)offsetName - 8);
        temp_v0_3 = *(int *)((char *)(offsetName) - 4) - 1;
        *(int *)((char *)(offsetName) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_3), (StringTokenHeader *)temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s1_3) + 8) = 8;
    ((Gap::Core::igMetaField *)temp_s1_3)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1_3);
    *(int *)((char *)(temp_s1_3) + 4) = (int)((int) (*(int *)((char *)(temp_s1_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1_3);
    }
    temp_s1_4 = (void *)(igVec2fMetaField_CreateInstance(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("size" == 0) {
        var_v0_7 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_8 = (int)(StringPool_Allocate(0x10));
            if (var_v0_8 != 0) {
                var_v0_8 = (int)(StringPool_Construct((StringPool *)var_v0_8));
            }
            g_stringPool = (StringPool *)var_v0_8;
        }
        var_v0_7 = (void *)(StringPool_Intern(g_stringPool, "size"));
    }
    sizeName = (void *)(var_v0_7);
    ((Gap::Core::igMetaField *)temp_s1_4)->setFieldName(&sizeName);
    if (sizeName != 0) {
        temp_a1_4 = (int *)((char *)sizeName - 8);
        temp_v0_4 = *(int *)((char *)(sizeName) - 4) - 1;
        *(int *)((char *)(sizeName) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_4), (StringTokenHeader *)temp_a1_4);
        }
    }
    *(int *)((char *)(temp_s1_4) + 8) = 0x10;
    ((Gap::Core::igMetaField *)temp_s1_4)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1_4);
    *(int *)((char *)(temp_s1_4) + 4) = (int)((int) (*(int *)((char *)(temp_s1_4) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_4) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1_4);
    }
    temp_s1_5 = (void *)(igVec2fMetaField_CreateInstance(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("texCoordMin" == 0) {
        var_v0_9 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_10 = (int)(StringPool_Allocate(0x10));
            if (var_v0_10 != 0) {
                var_v0_10 = (int)(StringPool_Construct((StringPool *)var_v0_10));
            }
            g_stringPool = (StringPool *)var_v0_10;
        }
        var_v0_9 = (void *)(StringPool_Intern(g_stringPool, "texCoordMin"));
    }
    texCoordMinName = (void *)(var_v0_9);
    ((Gap::Core::igMetaField *)temp_s1_5)->setFieldName(&texCoordMinName);
    if (texCoordMinName != 0) {
        temp_a1_5 = (int *)((char *)texCoordMinName - 8);
        temp_v0_5 = *(int *)((char *)(texCoordMinName) - 4) - 1;
        *(int *)((char *)(texCoordMinName) - 4) = temp_v0_5;
        if (temp_v0_5 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_5), (StringTokenHeader *)temp_a1_5);
        }
    }
    *(int *)((char *)(temp_s1_5) + 8) = 0x18;
    ((Gap::Core::igMetaField *)temp_s1_5)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1_5);
    *(int *)((char *)(temp_s1_5) + 4) = (int)((int) (*(int *)((char *)(temp_s1_5) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_5) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1_5);
    }
    temp_s1_6 = (void *)(igVec2fMetaField_CreateInstance(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("texCoordMax" == 0) {
        var_v0_11 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_12 = (int)(StringPool_Allocate(0x10));
            if (var_v0_12 != 0) {
                var_v0_12 = (int)(StringPool_Construct((StringPool *)var_v0_12));
            }
            g_stringPool = (StringPool *)var_v0_12;
        }
        var_v0_11 = (void *)(StringPool_Intern(g_stringPool, "texCoordMax"));
    }
    texCoordMaxName = (void *)(var_v0_11);
    ((Gap::Core::igMetaField *)temp_s1_6)->setFieldName(&texCoordMaxName);
    if (texCoordMaxName != 0) {
        temp_a1_6 = (int *)((char *)texCoordMaxName - 8);
        temp_v0_6 = *(int *)((char *)(texCoordMaxName) - 4) - 1;
        *(int *)((char *)(texCoordMaxName) - 4) = temp_v0_6;
        if (temp_v0_6 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*temp_a1_6), (StringTokenHeader *)temp_a1_6);
        }
    }
    *(int *)((char *)(temp_s1_6) + 8) = 0x20;
    ((Gap::Core::igMetaField *)temp_s1_6)->validate();
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s1_6);
    *(int *)((char *)(temp_s1_6) + 4) = (int)((int) (*(int *)((char *)(temp_s1_6) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s1_6) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s1_6);
    }
}

