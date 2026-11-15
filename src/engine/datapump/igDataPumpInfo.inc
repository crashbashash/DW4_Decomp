igMetaObject *g_igDataPumpInfo_metaObject;
igMetaField *g_igDataPumpInfo_dataPumpListMetaField;

void FUN_001e5650(int arg0) {
    FUN_001e5810();
    igMetaObject_CreateInstance(g_igDataPumpInfo_metaObject, arg0);
}

igMetaObject *FUN_001e5690(void) {
    if (g_igDataPumpInfo_metaObject == 0) {
        g_igDataPumpInfo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igDataPumpInfo_metaObject;
}

igMetaObject *igDataPumpInfo_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5810();
    return g_igDataPumpInfo_metaObject;
}

int igDataPumpInfo_GetVTable(void) {
    Obj_1e5730 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_0052ba10[0];
    obj.r4 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0052ba10[0];
    obj.rel4();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

void FUN_001e5810(void)
{
    igMetaObject_RunStaticInit(igDataPumpInfo_Register);
}

static igMetaObjectCallback g_igDataPumpInfo_callbackList[] = { FUN_001e54a0, 0 };

void igDataPumpInfo_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDataPumpInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igDataPumpInfo_GetMetaObject,
        "igDataPumpInfo",
        0x18, /* instance size */
        igDataPumpInfo_GetVTable,
        &igDataPumpInfo_InitFields,
        0, /* extra callback item */
        g_igDataPumpInfo_callbackList /* callback list */
    );
}

void thunk_igDataPumpInfo_GetMetaObject(void) {
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
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igDataPumpInfo_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, firstField));
    ((igObjectRefMetaField *)field)->_metaObject = (int)FUN_001e53c0();
    ((igRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields(meta, g_igDataPumpInfo_fieldTable, g_igDataPumpInfo_fieldHandles, g_igDataPumpInfo_fieldOffsets, firstField);
}

