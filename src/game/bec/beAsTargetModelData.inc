igMetaObject *g_beAsTargetModelData_metaObject;
igMetaField *g_beAsTargetModelData_dataListMetaField;

void *beAsTargetModelData_GetMetaObject(void) {
    igMetaObject *g = g_beAsTargetModelData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAsTargetModelData_EnsureRegistered();
    }
    return g_beAsTargetModelData_metaObject;
}

int beAsTargetModelData_GetVTable(void) {
    beAsTargetModelData obj;
    int vtable;
    igObject **dataListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beAsTargetModelData_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beAsTargetModelData_vtable[0];
    igObjectRef_Release(dataListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAsTargetModelData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAsTargetModelData_Register);
}

static igMetaObjectCallback g_beAsTargetModelData_callbackList[] = { beActionStarterDataList_EnsureRegistered, 0 };

CallbackArray *beAsTargetModelData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAsTargetModelData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAsTargetModelData_GetMetaObjectFunction,
        "beAsTargetModelData",
        0x10, /* instance size */
        beAsTargetModelData_GetVTable,
        beAsTargetModelData_InitFields,
        0, /* extra callback item */
        g_beAsTargetModelData_callbackList /* callback list */
    );
}

void beAsTargetModelData_GetMetaObjectFunction(void)
{
    beAsTargetModelData_GetMetaObject();
}

static FieldFactory g_beAsTargetModelData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beAsTargetModelData_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beAsTargetModelData_fieldHandles[] = {
    &g_beAsTargetModelData_dataListMetaField,
};
static int g_beAsTargetModelData_fieldOffsets[] = {
    12,
};

void beAsTargetModelData_InitFields(void) {
    int base;
    void *dataList;
    igMetaObject *meta;

    meta = g_beAsTargetModelData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beAsTargetModelData_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beActionStarterDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beAsTargetModelData_fieldTable, g_beAsTargetModelData_fieldHandles, g_beAsTargetModelData_fieldOffsets, base);
}

