void FUN_003bc940(int arg0) {
    FUN_003bca60();
    igMetaObject_CreateInstance(*(int *)0x58B0D0, arg0);
}

void *FUN_003bc980(void) {
    bool ok;
    if (DAT_0058b0d0[0] == 0) goto make;
    ok = !!(DAT_0058b0d0[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003bca60();
done:;
    return DAT_0058b0d0[0];
}

int beNDMWSaveIntfCtrlData_GetVTable(void) {
    union U_3bc9d0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_0053d7d0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
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

void FUN_003bca60(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfCtrlData_Register);
}

void *beNDMWSaveIntfCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntfCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfCtrlData_GetMetaObject,
        beNDMWSaveIntfCtrlData_className,
        0x34, /* instance size */
        beNDMWSaveIntfCtrlData_GetVTable,
        beNDMWSaveIntfCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveIntfCtrlData_GetMetaObject(void)
{
    FUN_003bc980();
}

void beNDMWSaveIntfCtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_3bcb10 *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_0058b0d0)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004ca200[0], 0xF);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_3bcb10 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00510d38[0]);
    temp_v0_2->f28 = (int)(&DAT_0058b0d8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &DAT_004ca240[0], &DAT_004ca280[0], &DAT_004ca2c0[0], temp_s2);
}

int FUN_003bcc20(void) {
    if (DAT_0058b158[0] == 0) {
        DAT_0058b158[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004ca300[0], &DAT_004ca320[0], 7);
    }
    return DAT_0058b158[0];
}

