igMetaObject *FUN_00353240(void) {
    if (g_beModelCtrlInfoDataTrc_metaObject[0] == 0) {
        g_beModelCtrlInfoDataTrc_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beModelCtrlInfoDataTrc_metaObject[0];
}

void *FUN_00353290(void) {
    igMetaObject *g = g_beModelCtrlInfoDataTrc_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003533c0();
    }
    return g_beModelCtrlInfoDataTrc_metaObject[0];
}

int beModelCtrlInfoDataTrc_GetVTable(void) {
    union U_3532e0 u;
    int temp_s1;
    void ** q0;
    S_ref * q1;
    int *temp_a1;
    int temp_v0;
    void *temp_a0;
    void *temp_v1;

    igObject_InitHeader(u.b);
    q0 = (void **)&u.b[8];
    *q0 = 0;
    u.vt = (int)(&DAT_00537b50[0]);
    q1 = (S_ref *)&u.b[16];
    *(int *)q1 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)(&DAT_00537b50[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    u.vt = (int)(&g_igNamedObject_vtable[0]);
    if (q0 != 0) {
        temp_v1 = *q0;
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

void FUN_003533c0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataTrc_Register);
}

void *beModelCtrlInfoDataTrc_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoDataTrc_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataTrc_GetMetaObject,
        beModelCtrlInfoDataTrc_className,
        0x14, /* instance size */
        beModelCtrlInfoDataTrc_GetVTable,
        beModelCtrlInfoDataTrc_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataTrc_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataTrc_GetMetaObject(void)
{
    FUN_00353290();
}

void beModelCtrlInfoDataTrc_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(((void * *)g_beModelCtrlInfoDataTrc_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c54a8[0], 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502218[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00503b38[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_00588bd8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) ((int)temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) (int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_001957c0();
    igMetaObject_NameFields(temp_s1, &DAT_004c54b0[0], &DAT_004c54b8[0], &DAT_004c54c0[0], temp_s2);
}

