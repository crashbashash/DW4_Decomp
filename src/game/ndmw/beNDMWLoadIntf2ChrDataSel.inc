igMetaObject *g_beNDMWLoadIntf2ChrDataSel_metaObject;
int g_beNDMWLoadIntf2ChrDataSel_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_selMaxMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_selPointMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st0MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st1MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st2MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st3MetaField;

igMetaObject *beNDMWLoadIntf2ChrDataSel_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2ChrDataSel_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2ChrDataSel_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadIntf2ChrDataSel_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2ChrDataSel_metaObject;
}

int beNDMWLoadIntf2ChrDataSel_GetVTable(void) {
    union U_3c2b90 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_beNDMWLoadIntf2ChrDataSel_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
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

void beNDMWLoadIntf2ChrDataSel_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ChrDataSel_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2ChrDataSel_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, 0 };

void *beNDMWLoadIntf2ChrDataSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2ChrDataSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ChrDataSel_GetMetaObject,
        "beNDMWLoadIntf2ChrDataSel",
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

static FieldFactory g_beNDMWLoadIntf2ChrDataSel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2ChrDataSel_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_commonIntf",
    "_kindHard",
    "_oldPadData",
    "_selMax",
    "_ramNo",
    "_isCansel",
    "_isEnd",
    "_selPoint",
    "_mcSelPoint",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2ChrDataSel_fieldHandles[] = {
    &g_beNDMWLoadIntf2ChrDataSel_messengerMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_padManagerMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_commonIntfMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_kindHardMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_oldPadDataMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_selMaxMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_ramNoMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_isCanselMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_isEndMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_selPointMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_mcSelPointMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st0MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st1MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st2MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st3MetaField,
};
static int g_beNDMWLoadIntf2ChrDataSel_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    49,
    52,
    56,
    60,
    64,
    68,
    72,
};

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

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWLoadIntf2ChrDataSel_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2ChrDataSel_ctorTable, 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "CHRDATASEL");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2ChrDataSel_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = beMessenger_GetOrCreateMetaObject();
    temp_s0->_refCounted = 0;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = bePadManager_GetOrCreateMetaObject();
    temp_s0_2->_refCounted = 0;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    temp_s0_3->_refCounted = 0;
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_4->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    temp_s0_4->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2ChrDataSel_fieldTable, g_beNDMWLoadIntf2ChrDataSel_fieldHandles, g_beNDMWLoadIntf2ChrDataSel_fieldOffsets, temp_s2);
}

