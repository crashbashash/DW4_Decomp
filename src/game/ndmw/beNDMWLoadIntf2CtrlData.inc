void FUN_003c43c0(int arg0) {
    FUN_003c44e0();
    igMetaObject_CreateInstance(*(int *)0x58BA30, arg0);
}

void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void) {
    bool ok;
    if (DAT_0058ba30[0] == 0) goto make;
    ok = !!(DAT_0058ba30[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c44e0();
done:;
    return DAT_0058ba30[0];
}

int beNDMWLoadIntf2CtrlData_GetVTable(void) {
    union U_3c4450 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_0053ced0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
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

void FUN_003c44e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2CtrlData_Register);
}

void *beNDMWLoadIntf2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2CtrlData_GetMetaObject,
        beNDMWLoadIntf2CtrlData_className,
        0x34, /* instance size */
        beNDMWLoadIntf2CtrlData_GetVTable,
        beNDMWLoadIntf2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2CtrlData_GetMetaObject(void)
{
    beNDMWLoadIntf2CtrlData_ResolveMetaObject();
}

void beNDMWLoadIntf2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_0058ba30)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cb610[0], 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00510d38[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_0058ba38[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &DAT_004cb650[0], &DAT_004cb690[0], &DAT_004cb6d0[0], temp_s2);
}

int FUN_003c46a0(void) {
    if (DAT_0058bac0[0] == 0) {
        DAT_0058bac0[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004cb710[0], &DAT_004cb730[0], 8);
    }
    return DAT_0058bac0[0];
}

