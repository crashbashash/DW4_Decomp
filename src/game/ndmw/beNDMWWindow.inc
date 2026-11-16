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
        g_beNDMWWindow_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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

void *beNDMWWindow_Register(void) {
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
    int temp_s0;
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    igMetaObject *temp_s1;

    temp_s1 = g_beNDMWWindow_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beNDMWWindow_ctorTable, 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_refCounted = 0;
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_refCounted = 0;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_refCounted = 0;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4), 1);
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)beNDMWWindowList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)beNDMWWindow_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    igMetaObject_NameFields(temp_s1, g_beNDMWWindow_fieldTable, g_beNDMWWindow_fieldHandles, g_beNDMWWindow_fieldOffsets, temp_s0);
}

