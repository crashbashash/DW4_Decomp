void FUN_003c2000(int arg0) {
    FUN_003c2120();
    igMetaObject_CreateInstance(*(int *)0x58B530, arg0);
}

void *beNDMWLogoCtrlData_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWLogoCtrlData_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beNDMWLogoCtrlData_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003c2120();
done:
    return g_beNDMWLogoCtrlData_metaObject[0];
}

int beNDMWLogoCtrlData_GetVTable(void) {
    union U_3c2090 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d310[0];
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

void FUN_003c2120(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoCtrlData_Register);
}

void *beNDMWLogoCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLogoCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLogoCtrlData_GetMetaObject,
        beNDMWLogoCtrlData_className,
        0x20, /* instance size */
        beNDMWLogoCtrlData_GetVTable,
        beNDMWLogoCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLogoCtrlData_GetMetaObject(void)
{
    beNDMWLogoCtrlData_GetReadyMetaObject();
}

void beNDMWLogoCtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(g_beNDMWLogoCtrlData_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWLogoCtrlData_ctorTable[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &CTRL_5[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058b538[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((RT *)temp_v0_2)->references = ((RT *)temp_v0_2)->references - 1;
    if (((unsigned long long)(long long)((RT *)temp_v0_2)->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &g_beNDMWLogoCtrlData_fieldTable[0], &DAT_004cac20[0], &DAT_004cac30[0], temp_s2);
}

int FUN_003c22e0(void) {
    if (DAT_0058b560[0] == 0) {
        DAT_0058b560[0] = igMetaEnum_Create(Message, &DAT_004cac40[0], &DAT_0058b568[0], 1);
    }
    return DAT_0058b560[0];
}

