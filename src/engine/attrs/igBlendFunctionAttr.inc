int FUN_00139e10(void) {
    if (DAT_0055f3a8[0] == 0) {
        DAT_0055f3a8[0] = igMetaEnum_Create(&DAT_004d5b40[0], &DAT_00486a90[0], &DAT_00486aa0[0], 3);
    }
    return DAT_0055f3a8[0];
}

int FUN_00139e70(void) {
    if (DAT_0055f3b0[0] == 0) {
        DAT_0055f3b0[0] = igMetaEnum_Create(&DAT_004d5bc0[0], &DAT_00486ab0[0], &DAT_00486ac0[0], 3);
    }
    return DAT_0055f3b0[0];
}

void FUN_00139ed0(int arg0) {
    FUN_0013a040();
    igMetaObject_CreateInstance(*(int *)0x55F3B8, arg0);
}

int FUN_00139f10(void) {
    if (DAT_0055f3b8[0] == 0) {
        DAT_0055f3b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f3b8[0];
}

igMetaObject *igBlendFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendFunctionAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a040();
    return g_igBlendFunctionAttr_metaObject[0];
}

int igBlendFunctionAttr_GetVTable(void) {
    union U_139fb0 u;
    int temp_s0;
    S_ref *p;

    igObject_InitHeader(u.b);
    p = (S_ref *)&u.b[24];
    u.vt = (int)&DAT_00524210[0];
    *(int *)p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524210[0];
    if (p != 0) {
        p = *(S_ref **)p;
        if (p != 0) {
            p->f4 = (int)((int) (p->f4 - 1));
            if (((unsigned long long) ((long long) p->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    return temp_s0;
}

void FUN_0013a040(void)
{
    igMetaObject_RunStaticInit(igBlendFunctionAttr_Register);
}

void igBlendFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendFunctionAttr_GetMetaObject,
        igBlendFunctionAttr_className,
        0x34, /* instance size */
        igBlendFunctionAttr_GetVTable,
        &igBlendFunctionAttr_InitFields,
        0, /* extra callback item */
        g_igBlendFunctionAttr_callbackList /* callback list */
    );
}

void thunk_igBlendFunctionAttr_GetMetaObject(void) {
    igBlendFunctionAttr_GetMetaObject();
}

void igBlendFunctionAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    struct BlendAttrMetaField *t5;
    struct BlendAttrMetaField *temp_s2;
    struct BlendAttrMetaField *temp_v0;
    struct BlendAttrMetaField *temp_v0_2;
    struct BlendAttrMetaField *temp_v0_3;
    struct BlendAttrMetaField *temp_v0_4;
    struct BlendAttrMetaField *temp_v0_5;
    struct BlendAttrMetaField *temp_v0_6;
    struct BlendAttrMetaField *temp_v0_7;
    struct BlendAttrMetaField *temp_v0_8;

    temp_s0 = (void *)DAT_0055f3b8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486ae0[0], 0xB);
    temp_v0 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1);
    FUN_002dc7a0(temp_v0, &DAT_00486ba0[0]);
    temp_v0->f52 = FUN_00149740;
    temp_v0_2 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    FUN_002dc7a0(temp_v0_2, &DAT_00486ba8[0]);
    temp_v0_2->f52 = FUN_00149740;
    temp_v0_3 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    FUN_002dc7a0(temp_v0_3, &DAT_00486bb0[0]);
    temp_v0_3->f52 = FUN_002d1870;
    temp_s2 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    temp_s2->f56 = FUN_0014fe60();
    temp_s2->f40 = 1;
    temp_s2->f39 = 1;
    temp_s2->f44 = 3;
    FUN_0030e750(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4), 0);
    t5 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 5);
    t5->f48 = (void (*)())FUN_0013c420;
    temp_v0_4 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 6);
    FUN_002e3810(temp_v0_4, 0);
    temp_v0_4->f38 = 0;
    temp_v0_4->f48 = (void (*)())FUN_0013c470;
    temp_v0_5 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 7);
    FUN_002dc7a0(temp_v0_5, &DAT_00486bb8[0]);
    temp_v0_5->f52 = (void (*)())FUN_00139e70;
    temp_v0_6 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 8);
    FUN_002dc7a0(temp_v0_6, &DAT_00486bc0[0]);
    temp_v0_6->f52 = (void (*)())FUN_00139e70;
    temp_v0_7 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 9);
    FUN_002dc7a0(temp_v0_7, &DAT_00486bc8[0]);
    temp_v0_7->f52 = (void (*)())FUN_00139e10;
    temp_v0_8 = (BlendAttrMetaField *)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 0xA);
    FUN_002dc7a0(temp_v0_8, &DAT_00486bd0[0]);
    temp_v0_8->f52 = (void (*)())FUN_00139e70;
    igMetaObject_NameFields(temp_s0, &DAT_00486b10[0], &DAT_00486b40[0], &DAT_00486b70[0], temp_s1);
}

