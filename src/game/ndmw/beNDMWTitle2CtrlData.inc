void FUN_003b2560(int arg0) {
    FUN_003b2680();
    igMetaObject_CreateInstance(*(int *)0x58AAB8, arg0);
}

void *FUN_003b25a0(void) {
    igMetaObject *g = g_beNDMWTitle2CtrlData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b2680();
    }
    return g_beNDMWTitle2CtrlData_metaObject[0];
}

int beNDMWTitle2CtrlData_GetVTable(void) {
    union U_3b25f0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053dc90[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void FUN_003b2680(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2CtrlData_Register);
}

void *beNDMWTitle2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2CtrlData_GetMetaObject,
        beNDMWTitle2CtrlData_className,
        0x30, /* instance size */
        beNDMWTitle2CtrlData_GetVTable,
        beNDMWTitle2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2CtrlData_GetMetaObject(void)
{
    FUN_003b25a0();
}

void beNDMWTitle2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beNDMWTitle2CtrlData_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWTitle2CtrlData_ctorTable[0], 8);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &CTRL_5[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058aac0[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &g_beNDMWTitle2CtrlData_fieldTable[0], &DAT_004c96d0[0], &DAT_004c96f0[0], temp_s2);
}

int FUN_003b2840(void) {
    if (DAT_0058ab08[0] == 0) {
        DAT_0058ab08[0] = igMetaEnum_Create(Message, &DAT_004c9710[0], &DAT_004c9718[0], 2);
    }
    return DAT_0058ab08[0];
}

