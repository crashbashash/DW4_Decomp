igMetaObject *g_beGeneraterItemData_metaObject;
igMetaField *g_beGeneraterItemData_dataListMetaField;

void *beGeneraterItemData_GetMetaObject(void) {
    unsigned char b;
    if (g_beGeneraterItemData_metaObject != 0) {
        b = (g_beGeneraterItemData_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beGeneraterItemData_EnsureRegistered();
done:
    return g_beGeneraterItemData_metaObject;
}

int beGeneraterItemData_GetVTable(void) {
    beGeneraterItemData obj;
    int vtable;
    igObject **dataListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beGeneraterItemData_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beGeneraterItemData_vtable[0];
    igObjectRef_Release(dataListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beGeneraterItemData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemData_Register);
}

static igMetaObjectCallback g_beGeneraterItemData_callbackList[] = { beGeneraterItemDataOneList_EnsureRegistered, 0 };

CallbackArray *beGeneraterItemData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beGeneraterItemData_GetMetaObjectFunction,
        "beGeneraterItemData",
        0x10, /* instance size */
        beGeneraterItemData_GetVTable,
        beGeneraterItemData_InitFields,
        0, /* extra callback item */
        g_beGeneraterItemData_callbackList /* callback list */
    );
}

void beGeneraterItemData_GetMetaObjectFunction(void)
{
    beGeneraterItemData_GetMetaObject();
}

static FieldFactory g_beGeneraterItemData_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beGeneraterItemData_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beGeneraterItemData_fieldHandles[] = {
    &g_beGeneraterItemData_dataListMetaField,
};
static int g_beGeneraterItemData_fieldOffsets[] = {
    12,
};

void beGeneraterItemData_InitFields(void) {
    int base;
    void *dataList;
    igMetaObject *meta;

    meta = g_beGeneraterItemData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGeneraterItemData_ctorTable, 1);
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beGeneraterItemDataOneList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beGeneraterItemData_fieldTable, g_beGeneraterItemData_fieldHandles, g_beGeneraterItemData_fieldOffsets, base);
}

