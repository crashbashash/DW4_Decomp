void beNDMWLoadCtrl2CtrlData_Create(int arg0) {
    FUN_003c7b60();
    igMetaObject_CreateInstance(*(int *)0x58BEB0, arg0);
}

void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadCtrl2CtrlData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c7b60();
    }
    return g_beNDMWLoadCtrl2CtrlData_metaObject[0];
}

int beNDMWLoadCtrl2CtrlData_GetVTable(void) {
    union U_3c7ad0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053c750[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void FUN_003c7b60(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CtrlData_Register);
}

void *beNDMWLoadCtrl2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadCtrl2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CtrlData_GetMetaObject,
        beNDMWLoadCtrl2CtrlData_className,
        0x24, /* instance size */
        beNDMWLoadCtrl2CtrlData_GetVTable,
        beNDMWLoadCtrl2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadCtrl2CtrlData_GetMetaObject(void)
{
    beNDMWLoadCtrl2CtrlData_GetReadyMetaObject();
}

void beNDMWLoadCtrl2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beNDMWLoadCtrl2CtrlData_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWLoadCtrl2CtrlData_ctorTable[0], 5);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &CTRL_5[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058beb8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((RT *)temp_v0_2)->references = ((RT *)temp_v0_2)->references - 1;
    if (((unsigned long long)(long long)((RT *)temp_v0_2)->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(temp_s1, temp_s2)), 1);
    igMetaObject_NameFields(temp_s1, &g_beNDMWLoadCtrl2CtrlData_fieldTable[0], &DAT_004cbfe0[0], &DAT_004cc000[0], temp_s2);
}

int LoadCtrl2Message_GetMetaEnum(void) {
    if (DAT_0058bee8[0] == 0) {
        DAT_0058bee8[0] = igMetaEnum_Create(Message, &DAT_004cc020[0], &DAT_004cc030[0], 4);
    }
    return DAT_0058bee8[0];
}

