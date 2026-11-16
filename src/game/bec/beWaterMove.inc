igMetaObject *g_beWaterMove_metaObject;
igMetaField *g_beWaterMove_baseTimeMetaField;
igMetaField *g_beWaterMove_elapseTimeMetaField;
igMetaField *g_beWaterMove_maxTimeMetaField;
igMetaField *g_beWaterMove_targetDataMetaField;
igMetaField *g_beWaterMove_dataListMetaField;

igMetaObject *beWaterMove_GetOrCreateMetaObject(void) {
    if (g_beWaterMove_metaObject == 0) {
        g_beWaterMove_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWaterMove_metaObject;
}

void *beWaterMove_GetMetaObject(void) {
    igMetaObject *g = g_beWaterMove_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWaterMove_EnsureRegistered();
    }
    return g_beWaterMove_metaObject;
}

int beWaterMove_GetVTable(void) {
    beWaterMove obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beWaterMove_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)(((char * *)g_objectSystem)[0] + 916));
    obj._vtable = (int)&g_beWaterMove_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void beWaterMove_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWaterMove_Register);
}

static igMetaObjectCallback g_beWaterMove_callbackList[] = { beWaterMoveDataList_EnsureRegistered, 0 };

void *beWaterMove_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWaterMove_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWaterMove_GetMetaObjectFunction,
        "beWaterMove",
        0x28, /* instance size */
        beWaterMove_GetVTable,
        beWaterMove_InitFields,
        0, /* extra callback item */
        g_beWaterMove_callbackList /* callback list */
    );
}

void beWaterMove_GetMetaObjectFunction(void)
{
    beWaterMove_GetMetaObject();
}

static FieldFactory g_beWaterMove_ctorTable[] = {
    igLongMetaField_Create,
    igLongMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWaterMove_fieldTable[] = {
    "_baseTime",
    "_elapseTime",
    "_maxTime",
    "_targetData",
    "_dataList",
};
static igMetaField **g_beWaterMove_fieldHandles[] = {
    &g_beWaterMove_baseTimeMetaField,
    &g_beWaterMove_elapseTimeMetaField,
    &g_beWaterMove_maxTimeMetaField,
    &g_beWaterMove_targetDataMetaField,
    &g_beWaterMove_dataListMetaField,
};
static int g_beWaterMove_fieldOffsets[] = {
    8,
    16,
    24,
    32,
    36,
};

void beWaterMove_InitFields(void) {
    int base;
    void *dataList;
    void *meta;

    meta = (void *)g_beWaterMove_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWaterMove_ctorTable, 5);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beWaterMoveDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beWaterMove_fieldTable, g_beWaterMove_fieldHandles, g_beWaterMove_fieldOffsets, base);
}

