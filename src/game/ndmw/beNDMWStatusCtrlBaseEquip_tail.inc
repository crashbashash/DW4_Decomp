igMetaObject *g_beNDMWStatusCtrlBaseEquip_metaObject;
igMetaField *g_beNDMWStatusCtrlBaseEquip_kindListPosMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_kindListMaxMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_pocketPosMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_playerListMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_powerSocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_mainSlotMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_subSlotMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_wpuPocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_apuPocketMetaField;
igMetaField *g_beNDMWStatusCtrlBaseEquip_deviceFolderMetaField;

void *FUN_003baaa0(void) {
    bool ok;
    if (g_beNDMWStatusCtrlBaseEquip_metaObject == 0) goto make;
    ok = !!(g_beNDMWStatusCtrlBaseEquip_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003baaf0();
done:;
    return g_beNDMWStatusCtrlBaseEquip_metaObject;
}

void FUN_003baaf0(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlBaseEquip_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlBaseEquip_callbackList[] = { FUN_00364170, FUN_003c9210, 0 };

void *beNDMWStatusCtrlBaseEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWStatusCtrlBaseEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBaseEquip_GetMetaObject,
        "beNDMWStatusCtrlBaseEquip",
        0x7c, /* instance size */
        0,
        beNDMWStatusCtrlBaseEquip_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBaseEquip_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlBaseEquip_GetMetaObject(void)
{
    FUN_003baaa0();
}

static FieldFactory g_beNDMWStatusCtrlBaseEquip_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlBaseEquip_fieldTable[] = {
    "_kindListPos",
    "_kindListMax",
    "_pocketPos",
    "_playerList",
    "_powerSocket",
    "_mainSlot",
    "_subSlot",
    "_wpuPocket",
    "_apuPocket",
    "_deviceFolder",
};
static igMetaField **g_beNDMWStatusCtrlBaseEquip_fieldHandles[] = {
    &g_beNDMWStatusCtrlBaseEquip_kindListPosMetaField,
    &g_beNDMWStatusCtrlBaseEquip_kindListMaxMetaField,
    &g_beNDMWStatusCtrlBaseEquip_pocketPosMetaField,
    &g_beNDMWStatusCtrlBaseEquip_playerListMetaField,
    &g_beNDMWStatusCtrlBaseEquip_powerSocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_mainSlotMetaField,
    &g_beNDMWStatusCtrlBaseEquip_subSlotMetaField,
    &g_beNDMWStatusCtrlBaseEquip_wpuPocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_apuPocketMetaField,
    &g_beNDMWStatusCtrlBaseEquip_deviceFolderMetaField,
};
static int g_beNDMWStatusCtrlBaseEquip_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
    104,
    108,
    112,
    116,
    120,
};

void beNDMWStatusCtrlBaseEquip_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    igMetaObject *temp_s1;

    temp_s1 = g_beNDMWStatusCtrlBaseEquip_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beNDMWStatusCtrlBaseEquip_ctorTable, 0xA);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1), 1);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_00364090();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_003c9130();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_003c9130();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_003c9130();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_003c9130();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_003c9130();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_003c9130();
    igMetaObject_NameFields(temp_s1, g_beNDMWStatusCtrlBaseEquip_fieldTable, g_beNDMWStatusCtrlBaseEquip_fieldHandles, g_beNDMWStatusCtrlBaseEquip_fieldOffsets, temp_s0);
}

