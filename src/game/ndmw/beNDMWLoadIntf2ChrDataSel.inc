igMetaObject *beNDMWLoadIntf2ChrDataSel_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2ChrDataSel_metaObject[0] != 0) {
        ready = (g_beNDMWLoadIntf2ChrDataSel_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c2c20();
done:
    return g_beNDMWLoadIntf2ChrDataSel_metaObject[0];
}

int beNDMWLoadIntf2ChrDataSel_GetVTable(void) {
    union U_3c2b90 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00524950[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0053d1e0[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s0;
}

void FUN_003c2c20(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ChrDataSel_Register);
}

void *beNDMWLoadIntf2ChrDataSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        ((igMetaObject_3c2c40 * *)g_beNDMWLoadIntf2ChrDataSel_metaObject),
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ChrDataSel_GetMetaObject,
        beNDMWLoadIntf2ChrDataSel_className,
        0x4c, /* instance size */
        beNDMWLoadIntf2ChrDataSel_GetVTable,
        beNDMWLoadIntf2ChrDataSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ChrDataSel_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2ChrDataSel_GetMetaObject(void)
{
    beNDMWLoadIntf2ChrDataSel_ResolveMetaObject();
}

void beNDMWLoadIntf2ChrDataSel_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(DAT_0058b6b0[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004caf20[0], 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00512878[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b6b8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = FUN_00357910();
    temp_s0->_refCounted = 0;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = FUN_0034c8e0();
    temp_s0_2->_refCounted = 0;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = FUN_003c6ee0();
    temp_s0_3->_refCounted = 0;
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_4->_metaObject = FUN_003c4c20();
    temp_s0_4->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004caf60[0], &DAT_004cafa0[0], &DAT_004cafe0[0], temp_s2);
}

