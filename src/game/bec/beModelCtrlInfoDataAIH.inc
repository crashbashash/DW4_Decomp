void *FUN_00353bf0(void) {
    unsigned char b;
    if (g_beModelCtrlInfoDataAIH_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beModelCtrlInfoDataAIH_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00353cd0();
done:
    return g_beModelCtrlInfoDataAIH_metaObject[0];
}

int beModelCtrlInfoDataAIH_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537a30[0];
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

void FUN_00353cd0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataAIH_Register);
}

void *beModelCtrlInfoDataAIH_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataAIH_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataAIH_GetMetaObject,
        beModelCtrlInfoDataAIH_className,
        0x2c, /* instance size */
        beModelCtrlInfoDataAIH_GetVTable,
        beModelCtrlInfoDataAIH_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlInfoDataAIH_GetMetaObject(void)
{
    FUN_00353bf0();
}

void beModelCtrlInfoDataAIH_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(g_beModelCtrlInfoDataAIH_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beModelCtrlInfoDataAIH_ctorTable[0], 8);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &AIH_2[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_00588c38[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields(temp_s1, &g_beModelCtrlInfoDataAIH_fieldTable[0], &DAT_004c5580[0], &DAT_004c55a0[0], temp_s2);
}

