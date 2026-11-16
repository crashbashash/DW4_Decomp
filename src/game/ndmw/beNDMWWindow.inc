igMetaObject *g_beNDMWWindow_metaObject;
igMetaField *g_beNDMWWindow_insightMetaField;
igMetaField *g_beNDMWWindow_messengerMetaField;
igMetaField *g_beNDMWWindow_padManagerMetaField;
igMetaField *g_beNDMWWindow_playerNoMetaField;
igMetaField *g_beNDMWWindow_isRunMetaField;
igMetaField *g_beNDMWWindow_st0MetaField;
igMetaField *g_beNDMWWindow_st1MetaField;
igMetaField *g_beNDMWWindow_st2MetaField;
igMetaField *g_beNDMWWindow_st3MetaField;
igMetaField *g_beNDMWWindow_entCodeMetaField;
igMetaField *g_beNDMWWindow_retCodeMetaField;
igMetaField *g_beNDMWWindow_subWindowMetaField;
igMetaField *g_beNDMWWindow_motherMetaField;
igMetaField *g_beNDMWWindow_textCloseTypeListMetaField;
igMetaField *g_beNDMWWindow_textCloseNameListMetaField;
igMetaField *g_beNDMWWindow_modelCloseInfoNameListMetaField;
igMetaField *g_beNDMWWindow_modelCloseRamNoListMetaField;
igMetaField *g_beNDMWWindow_modelCloseSeqNameListMetaField;

igMetaObject *beNDMWWindow_GetOrCreateMetaObject(void) {
    if (g_beNDMWWindow_metaObject == 0) {
        g_beNDMWWindow_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWWindow_metaObject;
}

void *beNDMWWindow_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWWindow_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWWindow_EnsureRegistered();
    }
    return g_beNDMWWindow_metaObject;
}

void beNDMWWindow_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWWindow_Register);
}

static igMetaObjectCallback g_beNDMWWindow_callbackList[] = { igInsightCore_EnsureRegistered, beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWWindowList_EnsureRegistered, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWWindow_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindow_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWWindow_GetMetaObjectFunction,
        "beNDMWWindow",
        0x50, /* instance size */
        0,
        beNDMWWindow_InitFields,
        0, /* extra callback item */
        g_beNDMWWindow_callbackList /* callback list */
    );
}

void beNDMWWindow_GetMetaObjectFunction(void)
{
    beNDMWWindow_GetMetaObject();
}

static FieldFactory g_beNDMWWindow_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
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
static const char *g_beNDMWWindow_fieldTable[] = {
    "_insight",
    "_messenger",
    "_padManager",
    "_playerNo",
    "_isRun",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
    "_entCode",
    "_retCode",
    "_subWindow",
    "_mother",
    "_textCloseTypeList",
    "_textCloseNameList",
    "_modelCloseInfoNameList",
    "_modelCloseRamNoList",
    "_modelCloseSeqNameList",
};
static igMetaField **g_beNDMWWindow_fieldHandles[] = {
    &g_beNDMWWindow_insightMetaField,
    &g_beNDMWWindow_messengerMetaField,
    &g_beNDMWWindow_padManagerMetaField,
    &g_beNDMWWindow_playerNoMetaField,
    &g_beNDMWWindow_isRunMetaField,
    &g_beNDMWWindow_st0MetaField,
    &g_beNDMWWindow_st1MetaField,
    &g_beNDMWWindow_st2MetaField,
    &g_beNDMWWindow_st3MetaField,
    &g_beNDMWWindow_entCodeMetaField,
    &g_beNDMWWindow_retCodeMetaField,
    &g_beNDMWWindow_subWindowMetaField,
    &g_beNDMWWindow_motherMetaField,
    &g_beNDMWWindow_textCloseTypeListMetaField,
    &g_beNDMWWindow_textCloseNameListMetaField,
    &g_beNDMWWindow_modelCloseInfoNameListMetaField,
    &g_beNDMWWindow_modelCloseRamNoListMetaField,
    &g_beNDMWWindow_modelCloseSeqNameListMetaField,
};
static int g_beNDMWWindow_fieldOffsets[] = {
    8,
    12,
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
    56,
    60,
    64,
    68,
    72,
    76,
};

void beNDMWWindow_InitFields(void) {
    int base;
    void *insight;
    void *modelCloseSeqNameList;
    void *messenger;
    void *padManager;
    void *subWindow;
    void *mother;
    void *textCloseTypeList;
    void *textCloseNameList;
    void *modelCloseInfoNameList;
    void *modelCloseRamNoList;
    igMetaObject *meta;

    meta = g_beNDMWWindow_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWWindow_ctorTable, 0x12);
    insight = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)insight)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 4), 1);
    subWindow = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)subWindow)->_metaObject = (int)beNDMWWindowList_GetOrCreateMetaObject();
    ((igRefMetaField *)subWindow)->_construct = 1;
    mother = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)mother)->_metaObject = (int)beNDMWWindow_GetOrCreateMetaObject();
    textCloseTypeList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)textCloseTypeList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)textCloseTypeList)->_construct = 1;
    textCloseNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xE));
    ((igObjectRefMetaField *)textCloseNameList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)textCloseNameList)->_construct = 1;
    modelCloseInfoNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xF));
    ((igObjectRefMetaField *)modelCloseInfoNameList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)modelCloseInfoNameList)->_construct = 1;
    modelCloseRamNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x10));
    ((igObjectRefMetaField *)modelCloseRamNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)modelCloseRamNoList)->_construct = 1;
    modelCloseSeqNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)modelCloseSeqNameList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)modelCloseSeqNameList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWWindow_fieldTable, g_beNDMWWindow_fieldHandles, g_beNDMWWindow_fieldOffsets, base);
}

