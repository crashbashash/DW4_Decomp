igMetaObject *g_igDataPumpManager_metaObject;
igMetaField *g_igDataPumpManager_dataPumpListMetaField;

igMetaObject *FUN_001e5150(void) {
    if (g_igDataPumpManager_metaObject == 0) {
        g_igDataPumpManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igDataPumpManager_metaObject;
}

igMetaObject *igDataPumpManager_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5280();
    return g_igDataPumpManager_metaObject;
}

int igDataPumpManager_GetVTable(void) {
    Obj_1e51f0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_igDataPumpManager_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igDataPumpManager_vtable[0];
    obj.release();
    return r;
}

void FUN_001e5280(void)
{
    igMetaObject_RunStaticInit(igDataPumpManager_Register);
}

static igMetaObjectCallback g_igDataPumpManager_callbackList[] = { FUN_001e54a0, 0 };

void igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpManager_GetMetaObject,
        "igDataPumpManager",
        0xC, /* instance size */
        igDataPumpManager_GetVTable,
        &igDataPumpManager_InitFields,
        0, /* extra callback item */
        g_igDataPumpManager_callbackList /* callback list */
    );
}

void thunk_igDataPumpManager_GetMetaObject(void) {
    igDataPumpManager_GetMetaObject();
}

static FieldFactory g_igDataPumpManager_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igDataPumpManager_fieldTable[] = {
    "_dataPumpList",
};
static igMetaField **g_igDataPumpManager_fieldHandles[] = {
    &g_igDataPumpManager_dataPumpListMetaField,
};
static int g_igDataPumpManager_fieldOffsets[] = {
    8,
};

void igDataPumpManager_InitFields(void) {
    int firstField;
    void *field;
    igMetaObject *meta;

    meta = g_igDataPumpManager_metaObject;
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igDataPumpManager_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_001e53c0();
    ((igRefMetaField *)field)->_construct = 1;
    ((igMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igDataPumpManager_fieldTable, g_igDataPumpManager_fieldHandles, g_igDataPumpManager_fieldOffsets, firstField);
}

