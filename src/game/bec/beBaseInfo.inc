igMetaObject *g_beBaseInfo_metaObject;
igMetaField *g_beBaseInfo_dataListMetaField;
igMetaField *g_beBaseInfo_ramListMetaField;

igMetaObject *beBaseInfo_GetOrCreateMetaObject(void) {
    if (g_beBaseInfo_metaObject == 0) {
        g_beBaseInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBaseInfo_metaObject;
}

igMetaObject *beBaseInfo_GetMetaObject(void) {
    if (g_beBaseInfo_metaObject == 0 || !isValid(g_beBaseInfo_metaObject)) beBaseInfo_EnsureRegistered();
    return g_beBaseInfo_metaObject;
}

void beBaseInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfo_Register);
}

static igMetaObjectCallback g_beBaseInfo_callbackList[] = { beBaseInfoDataList_EnsureRegistered, beBaseInfoRamList_EnsureRegistered, 0 };

CallbackArray *beBaseInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beBaseInfo_GetMetaObjectFunction,
        "beBaseInfo",
        0x1c, /* instance size */
        0,
        beBaseInfo_InitFields,
        0, /* extra callback item */
        g_beBaseInfo_callbackList /* callback list */
    );
}

void beBaseInfo_GetMetaObjectFunction(void)
{
    beBaseInfo_GetMetaObject();
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
    int base;
    void *ramList;
    void *dataList;
    igMetaObject *meta;

    meta = g_beBaseInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBaseInfo_ctorTable, 2);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beBaseInfoDataList_GetOrCreateMetaObject();
    ramList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)ramList)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)ramList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beBaseInfo_fieldTable, g_beBaseInfo_fieldHandles, g_beBaseInfo_fieldOffsets, base);
}

