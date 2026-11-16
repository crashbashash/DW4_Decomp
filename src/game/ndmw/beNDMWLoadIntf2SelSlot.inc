igMetaObject *g_beNDMWLoadIntf2SelSlot_metaObject;
int g_beNDMWLoadIntf2SelSlot_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2SelSlot_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_selMaxMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isOpenMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isSelectMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isReOpenReqMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_selPointMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_modeMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_mcStatMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st0MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st1MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st2MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st3MetaField;

void beNDMWLoadIntf2SelSlot_Create(int arg0) {
    beNDMWLoadIntf2SelSlot_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2SelSlot_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2SelSlot_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2SelSlot_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2SelSlot_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadIntf2SelSlot_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2SelSlot_metaObject;
}

int beNDMWLoadIntf2SelSlot_GetVTable(void) {
    union U_3c2ef0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLoadIntf2SelSlot_vtable[0];
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

void beNDMWLoadIntf2SelSlot_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2SelSlot_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2SelSlot_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, 0 };

void *beNDMWLoadIntf2SelSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2SelSlot_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2SelSlot_GetMetaObject,
        "beNDMWLoadIntf2SelSlot",
        0x5c, /* instance size */
        beNDMWLoadIntf2SelSlot_GetVTable,
        beNDMWLoadIntf2SelSlot_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2SelSlot_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2SelSlot_GetMetaObject(void)
{
    beNDMWLoadIntf2SelSlot_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2SelSlot_ctorTable[] = {
    igObjectRefMetaField_Create,
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
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2SelSlot_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_kindHard",
    "_oldPadData",
    "_selMax",
    "_ramNo",
    "_isOpen",
    "_isSelect",
    "_isCansel",
    "_isReOpenReq",
    "_isEnd",
    "_selPoint",
    "_mcSelPoint",
    "_mode",
    "_mcStat",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2SelSlot_fieldHandles[] = {
    &g_beNDMWLoadIntf2SelSlot_messengerMetaField,
    &g_beNDMWLoadIntf2SelSlot_padManagerMetaField,
    &g_beNDMWLoadIntf2SelSlot_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2SelSlot_textOrderMetaField,
    &g_beNDMWLoadIntf2SelSlot_commonIntfMetaField,
    &g_beNDMWLoadIntf2SelSlot_kindHardMetaField,
    &g_beNDMWLoadIntf2SelSlot_oldPadDataMetaField,
    &g_beNDMWLoadIntf2SelSlot_selMaxMetaField,
    &g_beNDMWLoadIntf2SelSlot_ramNoMetaField,
    &g_beNDMWLoadIntf2SelSlot_isOpenMetaField,
    &g_beNDMWLoadIntf2SelSlot_isSelectMetaField,
    &g_beNDMWLoadIntf2SelSlot_isCanselMetaField,
    &g_beNDMWLoadIntf2SelSlot_isReOpenReqMetaField,
    &g_beNDMWLoadIntf2SelSlot_isEndMetaField,
    &g_beNDMWLoadIntf2SelSlot_selPointMetaField,
    &g_beNDMWLoadIntf2SelSlot_mcSelPointMetaField,
    &g_beNDMWLoadIntf2SelSlot_modeMetaField,
    &g_beNDMWLoadIntf2SelSlot_mcStatMetaField,
    &g_beNDMWLoadIntf2SelSlot_st0MetaField,
    &g_beNDMWLoadIntf2SelSlot_st1MetaField,
    &g_beNDMWLoadIntf2SelSlot_st2MetaField,
    &g_beNDMWLoadIntf2SelSlot_st3MetaField,
};
static int g_beNDMWLoadIntf2SelSlot_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    53,
    54,
    55,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
};

void beNDMWLoadIntf2SelSlot_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s0_5;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadIntf2SelSlot_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2SelSlot_ctorTable, 0x16);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "SELSLOT");
    ((igMetaField *)temp_v0_2)->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2SelSlot_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((igMetaField *)temp_v0_2)->_refCount = (int)((int) ((int)((igMetaField *)temp_v0_2)->_refCount - 1));
    if (((unsigned long long) ((long long) (int)((igMetaField *)temp_v0_2)->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    temp_s0_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    ((igObjectRefMetaField *)temp_s0_5)->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s0_5)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2SelSlot_fieldTable, g_beNDMWLoadIntf2SelSlot_fieldHandles, g_beNDMWLoadIntf2SelSlot_fieldOffsets, temp_s2);
}

