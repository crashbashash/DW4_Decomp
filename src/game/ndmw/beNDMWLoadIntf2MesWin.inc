void FUN_003c6b00(int arg0) {
    FUN_003c6c70();
    igMetaObject_CreateInstance(*(int *)0x58BD98, arg0);
}

int FUN_003c6b40(void) {
    if (((int *)DAT_0058bd98)[0] == 0) {
        ((int *)DAT_0058bd98)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bd98)[0];
}

void *beNDMWLoadIntf2MesWin_GetReadyMetaObject(void) {
    unsigned char b;
    if (DAT_0058bd98[0] != 0) {
        b = (*(int *)((char *)(DAT_0058bd98[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_003c6c70();
done:
    return DAT_0058bd98[0];
}

int beNDMWLoadIntf2MesWin_GetVTable(void) {
    union U_3c6be0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_0053c940[0];
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

void FUN_003c6c70(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MesWin_Register);
}

void *beNDMWLoadIntf2MesWin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2MesWin_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MesWin_GetMetaObject,
        beNDMWLoadIntf2MesWin_className,
        0x40, /* instance size */
        beNDMWLoadIntf2MesWin_GetVTable,
        beNDMWLoadIntf2MesWin_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2MesWin_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2MesWin_GetMetaObject(void)
{
    beNDMWLoadIntf2MesWin_GetReadyMetaObject();
}

void beNDMWLoadIntf2MesWin_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(DAT_0058bd98[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004cbd90[0], 0x12);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00510cd8[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_005130b8[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058bda0[0]);
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
    temp_s0_3->_metaObject = FUN_003c7700();
    temp_s0_3->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004cbde0[0], &DAT_004cbe30[0], &DAT_004cbe80[0], temp_s2);
}

