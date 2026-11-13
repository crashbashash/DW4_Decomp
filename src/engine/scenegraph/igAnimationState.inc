int FUN_001a6a90(void) {
    if (DAT_005620e8[0] == 0) {
        DAT_005620e8[0] = igMetaEnum_Create(&text_Status[0], &DAT_0048cf10[0], &DAT_0048cf20[0], 4);
    }
    return DAT_005620e8[0];
}

int FUN_001a6af0(void) {
    if (DAT_005620f0[0] == 0) {
        DAT_005620f0[0] = igMetaEnum_Create(&text_TransitionMode[0], &DAT_0048cf30[0], &DAT_0048cf50[0], 6);
    }
    return DAT_005620f0[0];
}

int FUN_001a6b50(void) {
    if (DAT_005620f8[0] == 0) {
        DAT_005620f8[0] = igMetaEnum_Create(&text_CombineMode[0], &DAT_0048cf68[0], &DAT_0048cf78[0], 3);
    }
    return DAT_005620f8[0];
}

void FUN_001a6bb0(int arg0) {
    FUN_001a6dc0();
    igMetaObject_CreateInstance(*(int *)0x562100, arg0);
}

igMetaObject *FUN_001a6bf0(void) {
    if (g_igAnimationState_metaObject[0] == 0) {
        g_igAnimationState_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationState_metaObject[0];
}

igMetaObject *igAnimationState_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationState_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6dc0();
    return g_igAnimationState_metaObject[0];
}

int igAnimationState_GetVTable(void) {
    union U_1a6c90 u;
    int temp_s2;
    S_ref *q3;
    S_ref *q2;
    S_ref *q1;
    
    
    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00529550[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    q2 = (S_ref *)&u.b[24];
    *(int *)q2 = 0;
    q3 = (S_ref *)&u.b[120];
    *(int *)q3 = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00529550[0]);
    if (q3 != 0) {
        q3 = *(S_ref **)q3;
        if (q3 != 0) {
            q3->f4 = (int)((int) (q3->f4 - 1));
            if (((unsigned long long) ((long long) q3->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q3);
            }
        }
    }
    if (q2 != 0) {
        q2 = *(S_ref **)q2;
        if (q2 != 0) {
            q2->f4 = (int)((int) (q2->f4 - 1));
            if (((unsigned long long) ((long long) q2->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q2);
            }
        }
    }
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)q1);
            }
        }
    }
    return temp_s2;
}

void FUN_001a6dc0(void)
{
    igMetaObject_RunStaticInit(igAnimationState_Register);
}

void igAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationState_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationState_GetMetaObject,
        igAnimationState_className,
        0xA0, /* instance size */
        igAnimationState_GetVTable,
        &igAnimationState_InitFields,
        0, /* extra callback item */
        g_igAnimationState_callbackList /* callback list */
    );
}

void thunk_igAnimationState_GetMetaObject(void) {
    igAnimationState_GetMetaObject();
}

void igAnimationState_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationState_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationState_ctorTable[0], 0x1A);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001a9130();
    ((igMetaField *)temp_s2)->_resetMethod = 2;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1)));
    FUN_002dc7a0(temp_v0, &DAT_0048d148[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_001a6b50);
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2)));
    FUN_002dc7a0(temp_v0_2, &DAT_0048d150[0]);
    ((igEnumMetaField *)temp_v0_2)->_getMetaEnumFunction = (int)(&FUN_001a6af0);
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3)));
    FUN_002dc7a0(temp_v0_3, &DAT_0048d158[0]);
    ((igEnumMetaField *)temp_v0_3)->_getMetaEnumFunction = (int)(FUN_001a6a90);
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_001a6bf0();
    ((igMetaField *)temp_s2_2)->_resetMethod = 2;
    FUN_002d3890(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5)), 1);
    FUN_002e3810(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9)), 1.0f);
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x10)))->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x11)))->_persistent = 0;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x12)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_001a6bf0();
    ((igMetaField *)temp_s2_3)->_resetMethod = 2;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0x19)))->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igAnimationState_fieldTable[0], &DAT_0048d070[0], &DAT_0048d0e0[0], temp_s1);
}

