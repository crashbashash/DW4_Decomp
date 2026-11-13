void *FUN_003538d0(void) {
    igMetaObject *g = g_beModelCtrlInfoDataHit_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00353a00();
    }
    return g_beModelCtrlInfoDataHit_metaObject[0];
}

int beModelCtrlInfoDataHit_GetVTable(void) {
    union U_353920 u;
    int temp_s1;
    void **q2;
    S_ref *q5;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q2 = &u.p[2];
    *q2 = 0;
    u.w[0] = (int)(&DAT_00537a90[0]);
    q5 = (S_ref *)&u.p[5];
    *(int *)q5 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00537a90[0]);
    if (q5 != 0) {
        q5 = *(S_ref **)q5;
        if (q5 != 0) {
            q5->f4 = (int)((int) (q5->f4 - 1));
            if (((unsigned long long) ((long long) q5->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q5);
            }
        }
    }
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    if (q2 != 0) {
        temp_v1 = *q2;
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

void FUN_00353a00(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataHit_Register);
}

void *beModelCtrlInfoDataHit_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataHit_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataHit_GetMetaObject,
        beModelCtrlInfoDataHit_className,
        0x1c, /* instance size */
        beModelCtrlInfoDataHit_GetVTable,
        beModelCtrlInfoDataHit_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataHit_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataHit_GetMetaObject(void)
{
    FUN_003538d0();
}

void beModelCtrlInfoDataHit_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beModelCtrlInfoDataHit_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beModelCtrlInfoDataHit_ctorTable[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00503bf8[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_00588c08[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    *(int *)((char *)(temp_s0) + 56) = FUN_0018a4f0();
    igMetaObject_NameFields(temp_s1, &g_beModelCtrlInfoDataHit_fieldTable[0], &DAT_004c5520[0], &DAT_004c5530[0], temp_s2);
}

