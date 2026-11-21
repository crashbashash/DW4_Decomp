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
        beNDMWPanelObject_EnsureRegistered();
    }
    return g_beNDMWPanelObject_metaObject;
}

void beNDMWPanelObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelObject_Register);
}

static igMetaObjectCallback g_beNDMWPanelObject_callbackList[] = { beBaseInfoManager_EnsureRegistered, beMessenger_EnsureRegistered, beDataObjList_EnsureRegistered, igStringRefList_EnsureRegistered, Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *beNDMWPanelObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWPanelObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
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
    int base;
    void *textColorList;
    void *textSetList;
    void *playerDataList;
    void *messenger;
    void *manager;
    igMetaObject *meta;

    meta = g_beNDMWPanelObject_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWPanelObject_ctorTable, 0x10);
    manager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)manager)->_metaObject = (int)beBaseInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)manager)->_refCounted = 0;
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 6)))->setDefault(2);
    playerDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)playerDataList)->_metaObject = (int)beDataObjList_GetOrCreateMetaObject();
    textSetList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)textSetList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    textColorList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)textColorList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    igMetaObject_NameFields(meta, g_beNDMWPanelObject_fieldTable, g_beNDMWPanelObject_fieldHandles, g_beNDMWPanelObject_fieldOffsets, base);
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

igMetaEnum *beNDMWPanelObject_GetMessageEnum(void) {
    if (g_beNDMWPanelObject_messageMetaEnum == 0) {
        g_beNDMWPanelObject_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beNDMWPanelObject_messageNames, g_beNDMWPanelObject_messageValues, 11);
    }
    return g_beNDMWPanelObject_messageMetaEnum;
}

