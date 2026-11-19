igMetaObject *g_igDataPumpManager_metaObject;
igMetaField *g_igDataPumpManager_dataPumpListMetaField;

igMetaObject *igDataPumpManager_GetOrCreateMetaObject(void) {
    if (g_igDataPumpManager_metaObject == 0) {
        g_igDataPumpManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpManager_metaObject;
}

igMetaObject *igDataPumpManager_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataPumpManager_EnsureRegistered();
    return g_igDataPumpManager_metaObject;
}

int igDataPumpManager_GetVTable(void) {
    Obj_1e51f0 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDataPumpManager_vtable[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igDataPumpManager_vtable[0];
    obj.release();
    return r;
}

void igDataPumpManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataPumpManager_Register);
}

static igMetaObjectCallback g_igDataPumpManager_callbackList[] = { igDataPumpList_EnsureRegistered, 0 };

CallbackArray *igDataPumpManager_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpManager_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igDataPumpManager_GetMetaObjectFunction,
        "igDataPumpManager",
        0xC, /* instance size */
        igDataPumpManager_GetVTable,
        &igDataPumpManager_InitFields,
        0, /* extra callback item */
        g_igDataPumpManager_callbackList /* callback list */
    );
}

void igDataPumpManager_GetMetaObjectFunction(void) {
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
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDataPumpManager_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igDataPumpList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    ((igMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDataPumpManager_fieldTable, g_igDataPumpManager_fieldHandles, g_igDataPumpManager_fieldOffsets, firstField);
}

