void beNDMWLoadIntf2DataSelIntf_Create(int arg0) {
    FUN_003c3680();
    igMetaObject_CreateInstance(*(int *)0x58B890, arg0);
}

igMetaObject *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DataSelIntf_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003c3680();
    return g_beNDMWLoadIntf2DataSelIntf_metaObject[0];
}

int beNDMWLoadIntf2DataSelIntf_GetVTable(void) {
    union U_3c35f0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d0c0[0];
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

void FUN_003c3680(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DataSelIntf_Register);
}

void *beNDMWLoadIntf2DataSelIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DataSelIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DataSelIntf_GetMetaObject,
        beNDMWLoadIntf2DataSelIntf_className,
        0x5c, /* instance size */
        beNDMWLoadIntf2DataSelIntf_GetVTable,
        beNDMWLoadIntf2DataSelIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DataSelIntf_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DataSelIntf_GetMetaObject(void)
{
    beNDMWLoadIntf2DataSelIntf_ResolveMetaObject();
}

void beNDMWLoadIntf2DataSelIntf_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igObjectRefMetaField *temp_s0_5;
    igObjectRefMetaField *temp_s0_6;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(((void * *)g_beNDMWLoadIntf2DataSelIntf_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_beNDMWLoadIntf2DataSelIntf_ctorTable[0], 0x17);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &text_name_2[0]));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DATASELINTF_3[0]);
    temp_v0_2->_externalEnumStorage = (int)(&DAT_0058b898[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) ((int)temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) (int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0->_metaObject = FUN_0034c8e0();
    temp_s0->_refCounted = 0;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_2->_metaObject = (int)FUN_003c6ee0();
    temp_s0_2->_refCounted = 0;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    temp_s0_3->_metaObject = (int)FUN_003c7700();
    temp_s0_3->_refCounted = 0;
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    temp_s0_4->_metaObject = (int)FUN_003c4c20();
    temp_s0_4->_refCounted = 0;
    temp_s0_5 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6));
    temp_s0_5->_metaObject = (int)FUN_003c6b40();
    temp_s0_5->_refCounted = 0;
    temp_s0_6 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    temp_s0_6->_metaObject = (int)FUN_003c3940();
    temp_s0_6->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &g_beNDMWLoadIntf2DataSelIntf_fieldTable[0], &DAT_004cb3c0[0], &DAT_004cb420[0], temp_s2);
}

