igMetaObject *g_beBaseInfoRam_metaObject;
igMetaField *g_beBaseInfoRam_ramNoMetaField;
igMetaField *g_beBaseInfoRam_parentInfoMetaField;
igMetaField *g_beBaseInfoRam_parentManagerMetaField;
igMetaField *g_beBaseInfoRam_isRunMetaField;
igMetaField *g_beBaseInfoRam_st0MetaField;
igMetaField *g_beBaseInfoRam_st1MetaField;
igMetaField *g_beBaseInfoRam_st2MetaField;
igMetaField *g_beBaseInfoRam_st3MetaField;
igMetaField *g_beBaseInfoRam_dataListMetaField;

igMetaObject *beBaseInfoRam_GetOrCreateMetaObject(void) {
    if (g_beBaseInfoRam_metaObject == 0) {
        g_beBaseInfoRam_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBaseInfoRam_metaObject;
}

void *beBaseInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBaseInfoRam_EnsureRegistered();
    }
    return g_beBaseInfoRam_metaObject;
}

int beBaseInfoRam_GetVTable(void) {
    beBaseInfoRam obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    dataListSlot = (igObject **)&obj._dataList;
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beBaseInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoRam_Register);
}

static igMetaObjectCallback g_beBaseInfoRam_callbackList[] = { beBaseInfo_EnsureRegistered, beBaseInfoManager_EnsureRegistered, beBaseInfoDataList_EnsureRegistered, 0 };

CallbackArray *beBaseInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBaseInfoRam_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beBaseInfoRam_GetMetaObjectFunction,
        "beBaseInfoRam",
        0x2c, /* instance size */
        beBaseInfoRam_GetVTable,
        beBaseInfoRam_InitFields,
        0, /* extra callback item */
        g_beBaseInfoRam_callbackList /* callback list */
    );
}

void beBaseInfoRam_GetMetaObjectFunction(void)
{
    beBaseInfoRam_GetMetaObject();
}

static FieldFactory g_beBaseInfoRam_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beBaseInfoRam_fieldTable[] = {
    "_ramNo",
    "_parentInfo",
    "_parentManager",
    "_isRun",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
    "_dataList",
};
static igMetaField **g_beBaseInfoRam_fieldHandles[] = {
    &g_beBaseInfoRam_ramNoMetaField,
    &g_beBaseInfoRam_parentInfoMetaField,
    &g_beBaseInfoRam_parentManagerMetaField,
    &g_beBaseInfoRam_isRunMetaField,
    &g_beBaseInfoRam_st0MetaField,
    &g_beBaseInfoRam_st1MetaField,
    &g_beBaseInfoRam_st2MetaField,
    &g_beBaseInfoRam_st3MetaField,
    &g_beBaseInfoRam_dataListMetaField,
};
static int g_beBaseInfoRam_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beBaseInfoRam_InitFields(void) {
    int base;
    void *dataList;
    void *parentManager;
    void *parentInfo;
    igMetaObject *meta;

    meta = g_beBaseInfoRam_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBaseInfoRam_ctorTable, 9);
    parentInfo = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)parentInfo)->_metaObject = (int)beBaseInfo_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)parentInfo)->_refCounted = 0;
    ((igMetaField *)parentInfo)->_persistent = 0;
    parentManager = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)parentManager)->_metaObject = (int)beBaseInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)parentManager)->_refCounted = 0;
    ((igMetaField *)parentManager)->_persistent = 0;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 3)))->setDefault(1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beBaseInfoDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beBaseInfoRam_fieldTable, g_beBaseInfoRam_fieldHandles, g_beBaseInfoRam_fieldOffsets, base);
}

