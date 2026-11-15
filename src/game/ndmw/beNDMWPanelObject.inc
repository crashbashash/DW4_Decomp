igMetaObject *g_beNDMWPanelObject_metaObject;
igMetaField *g_beNDMWPanelObject_managerMetaField;
igMetaField *g_beNDMWPanelObject_messengerMetaField;
igMetaField *g_beNDMWPanelObject_pageMetaField;
igMetaField *g_beNDMWPanelObject_playerNoMetaField;
igMetaField *g_beNDMWPanelObject_cursorMetaField;
igMetaField *g_beNDMWPanelObject_offsetMetaField;
igMetaField *g_beNDMWPanelObject_lineModeMetaField;
igMetaField *g_beNDMWPanelObject_playerDataListMetaField;
igMetaField *g_beNDMWPanelObject_isNoGateDiskMetaField;
igMetaField *g_beNDMWPanelObject_isNoHealingMetaField;
igMetaField *g_beNDMWPanelObject_isNoParaUpMetaField;
igMetaField *g_beNDMWPanelObject_isNoCurelingMetaField;
igMetaField *g_beNDMWPanelObject_textSetListMetaField;
igMetaField *g_beNDMWPanelObject_textColorListMetaField;
igMetaField *g_beNDMWPanelObject_listKazuMetaField;
igMetaField *g_beNDMWPanelObject_isEmgMetaField;
igMetaEnum *g_beNDMWPanelObject_messageMetaEnum;

igMetaObject *beNDMWPanelObject_ResolveMetaObject(void)
{
    igMetaObject *meta = g_beNDMWPanelObject_metaObject;
    if (!meta || ((meta->_validity & 4) != 0) == false) {
        FUN_003bec70();
    }
    return g_beNDMWPanelObject_metaObject;
}

void FUN_003bec70(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObject_Register);
}

static igMetaObjectCallback g_beNDMWPanelObject_callbackList[] = { FUN_0036a970, FUN_00357d10, FUN_00364170, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWPanelObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWPanelObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWPanelObject_GetMetaObject,
        "beNDMWPanelObject",
        0x3c, /* instance size */
        0,
        beNDMWPanelObject_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelObject_callbackList /* callback list */
    );
}

void beNDMWPanelObject_GetMetaObject(void)
{
    beNDMWPanelObject_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelObject_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWPanelObject_fieldTable[] = {
    "_manager",
    "_messenger",
    "_page",
    "_playerNo",
    "_cursor",
    "_offset",
    "_lineMode",
    "_playerDataList",
    "_isNoGateDisk",
    "_isNoHealing",
    "_isNoParaUp",
    "_isNoCureling",
    "_textSetList",
    "_textColorList",
    "_listKazu",
    "_isEmg",
};
static igMetaField **g_beNDMWPanelObject_fieldHandles[] = {
    &g_beNDMWPanelObject_managerMetaField,
    &g_beNDMWPanelObject_messengerMetaField,
    &g_beNDMWPanelObject_pageMetaField,
    &g_beNDMWPanelObject_playerNoMetaField,
    &g_beNDMWPanelObject_cursorMetaField,
    &g_beNDMWPanelObject_offsetMetaField,
    &g_beNDMWPanelObject_lineModeMetaField,
    &g_beNDMWPanelObject_playerDataListMetaField,
    &g_beNDMWPanelObject_isNoGateDiskMetaField,
    &g_beNDMWPanelObject_isNoHealingMetaField,
    &g_beNDMWPanelObject_isNoParaUpMetaField,
    &g_beNDMWPanelObject_isNoCurelingMetaField,
    &g_beNDMWPanelObject_textSetListMetaField,
    &g_beNDMWPanelObject_textColorListMetaField,
    &g_beNDMWPanelObject_listKazuMetaField,
    &g_beNDMWPanelObject_isEmgMetaField,
};
static int g_beNDMWPanelObject_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    41,
    42,
    43,
    44,
    48,
    52,
    56,
};

void beNDMWPanelObject_InitFields(void) {
    int temp_s2;
    void *temp_s1_5;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWPanelObject_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWPanelObject_ctorTable, 0x10);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0036a8d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 2);
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_00364090();
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    temp_s1_5 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xD));
    ((igObjectRefMetaField *)temp_s1_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWPanelObject_fieldTable, g_beNDMWPanelObject_fieldHandles, g_beNDMWPanelObject_fieldOffsets, temp_s2);
}

static const char *g_beNDMWPanelObject_messageNames[] = {
    "GENERATEITEM",
    "GENERATEWAZA",
    "GENERATESTAT",
    "GENEEMGHEAL",
    "ISCHECK",
    "REMOVE",
    "NOGATEDISK",
    "NOHEALING",
    "NOPARAUP",
    "NOCURELING",
    "ISRUN",
};
static int g_beNDMWPanelObject_messageValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xa,
};

igMetaEnum *FUN_003bee30(void) {
    if (g_beNDMWPanelObject_messageMetaEnum == 0) {
        g_beNDMWPanelObject_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWPanelObject_messageNames, g_beNDMWPanelObject_messageValues, 11);
    }
    return g_beNDMWPanelObject_messageMetaEnum;
}

