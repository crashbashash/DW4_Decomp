void FUN_003694a0(int arg0) {
    FUN_00369600();
    igMetaObject_CreateInstance(*(int *)0x589C38, arg0);
}

void *FUN_003694e0(void) {
    unsigned char b;
    if (g_beCameraCtrlInfoRamShake_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beCameraCtrlInfoRamShake_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00369600();
done:
    return g_beCameraCtrlInfoRamShake_metaObject[0];
}

int beCameraCtrlInfoRamShake_GetVTable(void) {
    union U_369530 u;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;

    igObject_InitHeader(u.b);
    p0 = (S_ref *)&u.b[8];
    *(int *)p0 = 0;
    u.vt = (int)&DAT_00534970[0];
    p1 = (S_ref *)&u.b[44];
    *(int *)p1 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00534970[0];
    if (p1 != 0) {
        o = *(char **)p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_00369600(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfoRamShake_Register);
}

void *beCameraCtrlInfoRamShake_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCameraCtrlInfoRamShake_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beCameraCtrlInfoRamShake_GetMetaObject,
        beCameraCtrlInfoRamShake_className,
        0x40, /* instance size */
        beCameraCtrlInfoRamShake_GetVTable,
        beCameraCtrlInfoRamShake_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCameraCtrlInfoRamShake_GetMetaObject(void)
{
    FUN_003694e0();
}

void beCameraCtrlInfoRamShake_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    T_temp_v0_2 *temp_v0_2;

    temp_s1 = (void *)(g_beCameraCtrlInfoRamShake_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c7950[0], 8);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502218[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_temp_v0_2 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00505c20[0]);
    temp_v0_2->f28 = (int)(&DAT_00589c40[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &DAT_004c7970[0], &DAT_004c7990[0], &DAT_004c79b0[0], temp_s2);
}

int FUN_003697c0(void) {
    if (DAT_00589c88[0] == 0) {
        DAT_00589c88[0] = igMetaEnum_Create(&DAT_005016f0[0], &DAT_004c79d0[0], &DAT_004c7a10[0], 0xF);
    }
    return DAT_00589c88[0];
}

