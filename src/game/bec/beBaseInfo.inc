igMetaObject *g_beBaseInfo_metaObject;
igMetaField *g_beBaseInfo_dataListMetaField;
igMetaField *g_beBaseInfo_ramListMetaField;

igMetaObject *FUN_0036ac80(void) {
    if (g_beBaseInfo_metaObject == 0) {
        g_beBaseInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBaseInfo_metaObject;
}

igMetaObject *FUN_0036acd0(void) {
    if (g_beBaseInfo_metaObject == 0 || !isValid(g_beBaseInfo_metaObject)) FUN_0036ad20();
    return g_beBaseInfo_metaObject;
}

void FUN_0036ad20(void)
{
    igMetaObject_RunStaticInit(beBaseInfo_Register);
}

static igMetaObjectCallback g_beBaseInfo_callbackList[] = { FUN_0036afa0, beBaseInfoRamList_EnsureRegistered, 0 };

void *beBaseInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beBaseInfo_GetMetaObject,
        "beBaseInfo",
        0x1c, /* instance size */
        0,
        beBaseInfo_InitFields,
        0, /* extra callback item */
        g_beBaseInfo_callbackList /* callback list */
    );
}

void beBaseInfo_GetMetaObject(void)
{
    FUN_0036acd0();
}

static FieldFactory g_beBaseInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beBaseInfo_fieldTable[] = {
    "_dataList",
    "_ramList",
};
static igMetaField **g_beBaseInfo_fieldHandles[] = {
    &g_beBaseInfo_dataListMetaField,
    &g_beBaseInfo_ramListMetaField,
};
static int g_beBaseInfo_fieldOffsets[] = {
    20,
    24,
};

void beBaseInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBaseInfo_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036aec0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beBaseInfo_fieldTable, g_beBaseInfo_fieldHandles, g_beBaseInfo_fieldOffsets, temp_s2);
}

