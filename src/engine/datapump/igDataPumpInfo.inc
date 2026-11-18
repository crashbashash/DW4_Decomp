igMetaObject *g_igDataPumpInfo_metaObject;
igMetaField *g_igDataPumpInfo_dataPumpListMetaField;

void igDataPumpInfo_Create(int arg0) {
    igDataPumpInfo_EnsureRegistered();
    igMetaObject_CreateInstance(g_igDataPumpInfo_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igDataPumpInfo_GetOrCreateMetaObject(void) {
    if (g_igDataPumpInfo_metaObject == 0) {
        g_igDataPumpInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpInfo_metaObject;
}

igMetaObject *igDataPumpInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataPumpInfo_EnsureRegistered();
    return g_igDataPumpInfo_metaObject;
}

int igDataPumpInfo_GetVTable(void) {
    Obj_1e5730 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.r1 = 0;
    obj.vt = &g_igDataPumpInfo_vtable[0];
    obj.r4 = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igDataPumpInfo_vtable[0];
    obj.rel4();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void igDataPumpInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataPumpInfo_Register);
}

static igMetaObjectCallback g_igDataPumpInfo_callbackList[] = { igDataPumpList_EnsureRegistered, 0 };

CallbackArray *igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igDataPumpInfo_GetMetaObjectFunction,
        "igDataPumpInfo",
        0x18, /* instance size */
        igDataPumpInfo_GetVTable,
        &igDataPumpInfo_InitFields,
        0, /* extra callback item */
        g_igDataPumpInfo_callbackList /* callback list */
    );
}

void igDataPumpInfo_GetMetaObjectFunction(void) {
    igDataPumpInfo_GetMetaObject();
}

static FieldFactory g_igDataPumpInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igDataPumpInfo_fieldTable[] = {
    "_dataPumpList",
};
static igMetaField **g_igDataPumpInfo_fieldHandles[] = {
    &g_igDataPumpInfo_dataPumpListMetaField,
};
static int g_igDataPumpInfo_fieldOffsets[] = {
    20,
};

void igDataPumpInfo_InitFields(void) {
    int firstField;
    void *field;
    igMetaObject *meta;

    meta = g_igDataPumpInfo_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDataPumpInfo_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, firstField));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igDataPumpList_GetOrCreateMetaObject();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDataPumpInfo_fieldTable, g_igDataPumpInfo_fieldHandles, g_igDataPumpInfo_fieldOffsets, firstField);
}

