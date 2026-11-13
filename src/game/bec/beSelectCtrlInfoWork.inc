void beSelectCtrlInfoWork_Create(int arg0) {
    FUN_00345830();
    igMetaObject_CreateInstance(*(int *)0x587F60, arg0);
}

igMetaObject *FUN_003456c0(void) {
    if (g_beSelectCtrlInfoWork_metaObject[0] == 0) {
        g_beSelectCtrlInfoWork_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSelectCtrlInfoWork_metaObject[0];
}

void *FUN_00345710(void) {
    igMetaObject *g = g_beSelectCtrlInfoWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00345830();
    }
    return g_beSelectCtrlInfoWork_metaObject[0];
}

int beSelectCtrlInfoWork_GetVTable(void) {
    union U_345760 u;
    int temp_s1;
    void **q7;
    S_ref *q8;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q7 = &u.p[7];
    q8 = (S_ref *)&u.p[8];
    u.w[0] = (int)(&DAT_00539010[0]);
    *q7 = 0;
    *(int *)q8 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00539010[0]);
    if (q8 != 0) {
        q8 = *(S_ref **)q8;
        if (q8 != 0) {
            q8->f4 = (int)((int) (q8->f4 - 1));
            if (((unsigned long long) ((long long) q8->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q8);
            }
        }
    }
    if (q7 != 0) {
        temp_v1 = *q7;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s1;
}

void FUN_00345830(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoWork_Register);
}

void *beSelectCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSelectCtrlInfoWork_GetMetaObject,
        beSelectCtrlInfoWork_className,
        0x24, /* instance size */
        beSelectCtrlInfoWork_GetVTable,
        beSelectCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beSelectCtrlInfoWork_callbackList /* callback list */
    );
}

void beSelectCtrlInfoWork_GetMetaObject(void)
{
    FUN_00345710();
}

void beSelectCtrlInfoWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSelectCtrlInfoWork_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beSelectCtrlInfoWork_ctorTable[0], 5);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002cb110();
    igMetaObject_NameFields(temp_s0, &g_beSelectCtrlInfoWork_fieldTable[0], &DAT_004c3b00[0], &DAT_004c3b20[0], temp_s2);
}

int beSelectCtrl_GetMessageEnum(void) {
    if (DAT_00587f90[0] == 0) {
        DAT_00587f90[0] = igMetaEnum_Create(&text_MsgAction[0], &DAT_004c3b40[0], &DAT_004c3b60[0], 7);
    }
    return DAT_00587f90[0];
}

