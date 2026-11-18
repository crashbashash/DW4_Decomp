igMetaObject *g_igItemDataBaseField_metaObject;
int g_igItemDataBaseField_defaultDescriptor;

igMetaObject *igItemDataBaseField_GetMetaObject(void)
{
    igMetaObject *g = g_igItemDataBaseField_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228410();
    return g_igItemDataBaseField_metaObject;
}

int igItemDataBaseField_GetVTable(void) {
    union U_5 u;
    int temp_s0;
    S_ref *q0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igMetaField_Init((igMetaField *)u.b);
    u.vt = (int)&g_igCompoundMetaField_vtable[0];
    q0 = (S_ref *)&u.b[52];
    *(int *)q0 = 0;
    u.vt = (int)&g_igItemDataBaseField_vtable[0];
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
    q1 = &u.b[12];
    u.vt = (int)&g_igMetaField_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00228410(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igItemDataBaseField_Register);
}

static igMetaObjectCallback g_igItemDataBaseField_callbackList[] = { FUN_002284a0, 0 };

CallbackArray *igItemDataBaseField_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igItemDataBaseField_metaObject,
        (igMetaObjectRegisterFunction)igCompoundMetaField_Register,
        (igMetaObjectGetFunction)igCompoundMetaField_GetPublishedMetaObject,
        thunk_igItemDataBaseField_GetMetaObject,
        "igItemDataBaseField",
        0x38, /* instance size */
        igItemDataBaseField_GetVTable,
        0,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igItemDataBaseField_callbackList /* callback list */
    );
}

void thunk_igItemDataBaseField_GetMetaObject(void) {
    igItemDataBaseField_GetMetaObject();
}

void FUN_002284a0(void) {
    void *temp_s0;

    if (g_igItemDataBaseField_defaultDescriptor == 0) {
        g_igItemDataBaseField_defaultDescriptor = (int)(igMetaObject_CreateInstance(g_igItemDataBaseField_metaObject, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
        temp_s0 = (void *)(g_igItemDataBaseField_defaultDescriptor);
        if (temp_s0 != 0) {
            MetaRefList_AppendRetained(igMetaField_GetMetaFieldList(), (igObject *)temp_s0);
            {
                void *held = (void *)g_igItemDataBaseField_defaultDescriptor;
                *(int *)((char *)(held) + 4) = *(int *)((char *)(held) + 4) - 1;
                if (((unsigned long long) ((long long) *(int *)((char *)(held) + 4) << 0x29) >> 0x29) == 0) {
                    igObject_Destroy((igObject *)held);
                }
            }
            *(short *)((char *)(g_igItemDataBaseField_defaultDescriptor) + 18) = (short) (*(int *)((char *)(igMetaField_GetMetaFieldList()) + 12) - 1);
            igMetaField_FinalizeDescriptor((igMetaField *)g_igItemDataBaseField_defaultDescriptor);
        }
    }
}

int FUN_00228570(void) {
    if (g_igItemDataBaseField_defaultDescriptor == 0) {
        FUN_00228410();
    }
    return g_igItemDataBaseField_defaultDescriptor;
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

    temp_s0 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("_interfacedMeta" == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_2 = (int)StringPool_Allocate(0x10);
            if (var_v0_2 != 0) {
                var_v0_2 = (int)StringPool_Construct((StringPool *)var_v0_2);
            }
            g_stringPool = (StringPool *)var_v0_2;
        }
        var_v0 = (void *)(StringPool_Intern(g_stringPool, "_interfacedMeta"));
    }
    sp3C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_s0, &sp3C);
    if (sp3C != 0) {
        temp_a1 = (int *)((char *)sp3C - 8);
        temp_v0 = *(int *)((char *)(sp3C) - 4) - 1;
        *(int *)((char *)(sp3C) - 4) = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1, (StringTokenHeader *)temp_a1);
        }
    }
    *(int *)((char *)(temp_s0) + 8) = 0;
    *(int *)((char *)(temp_s0) + 56) = (int)igMetaObject_GetOrCreateMetaObject();
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0);
    *(int *)((char *)(temp_s0) + 4) = (int)((int) (*(int *)((char *)(temp_s0) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0);
    }
    temp_s0_2 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("_itemList" == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_4 = (int)StringPool_Allocate(0x10);
            if (var_v0_4 != 0) {
                var_v0_4 = (int)StringPool_Construct((StringPool *)var_v0_4);
            }
            g_stringPool = (StringPool *)var_v0_4;
        }
        var_v0_3 = (void *)(StringPool_Intern(g_stringPool, "_itemList"));
    }
    sp38 = (void *)(var_v0_3);
    igMetaField_SetFieldName((igMetaField *)temp_s0_2, &sp38);
    if (sp38 != 0) {
        temp_a1_2 = (int *)((char *)sp38 - 8);
        temp_v0_2 = *(int *)((char *)(sp38) - 4) - 1;
        *(int *)((char *)(sp38) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1_2, (StringTokenHeader *)temp_a1_2);
        }
    }
    *(int *)((char *)(temp_s0_2) + 8) = 4;
    *(int *)((char *)(temp_s0_2) + 56) = (int)igMetaObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_2) + 52) = 1;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0_2);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0_2);
    *(int *)((char *)(temp_s0_2) + 4) = (int)((int) (*(int *)((char *)(temp_s0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0_2);
    }
    temp_s0_3 = (void *)(igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    if ("_itemName" == 0) {
        var_v0_5 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            var_v0_6 = (int)StringPool_Allocate(0x10);
            if (var_v0_6 != 0) {
                var_v0_6 = (int)StringPool_Construct((StringPool *)var_v0_6);
            }
            g_stringPool = (StringPool *)var_v0_6;
        }
        var_v0_5 = (void *)(StringPool_Intern(g_stringPool, "_itemName"));
    }
    sp34 = (void *)(var_v0_5);
    igMetaField_SetFieldName((igMetaField *)temp_s0_3, &sp34);
    if (sp34 != 0) {
        temp_a1_3 = (int *)((char *)sp34 - 8);
        temp_v0_3 = *(int *)((char *)(sp34) - 4) - 1;
        *(int *)((char *)(sp34) - 4) = temp_v0_3;
        if (temp_v0_3 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*temp_a1_3, (StringTokenHeader *)temp_a1_3);
        }
    }
    *(int *)((char *)(temp_s0_3) + 8) = 8;
    *(int *)((char *)(temp_s0_3) + 56) = (int)igStringRefList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0_3) + 52) = 1;
    igMetaField_FinalizeDescriptor((igMetaField *)temp_s0_3);
    ObjectList_AppendRetained((igObjectList *)arg0, (igObject *)temp_s0_3);
    *(int *)((char *)(temp_s0_3) + 4) = (int)((int) (*(int *)((char *)(temp_s0_3) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_s0_3) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s0_3);
    }
    igMetaObject_EnsureRegistered();
    igMetaObjectList_EnsureRegistered();
    igStringRefList_EnsureRegistered();
}

