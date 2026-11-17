igMetaObject *g_beNDMWLoadCtrl2Info_metaObject;
igMetaField *g_beNDMWLoadCtrl2Info_nameSelListMetaField;

igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2Info_metaObject != 0) {
        ready = (g_beNDMWLoadCtrl2Info_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadCtrl2Info_EnsureRegistered();
done:
    return g_beNDMWLoadCtrl2Info_metaObject;
}

int beNDMWLoadCtrl2Info_GetVTable(void) {
    beNDMWLoadCtrl2Info obj;
    int vtable;
    int *nameSelListRef;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2Info_vtable[0];
    nameSelListRef = &obj._nameSelList;
    *nameSelListRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2Info_vtable[0];
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)nameSelListRef, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, 0);
    return vtable;
}

void beNDMWLoadCtrl2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2Info_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2Info_callbackList[] = { igObjectList_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadCtrl2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadCtrl2Info_GetMetaObject,
        "beNDMWLoadCtrl2Info",
        0x20, /* instance size */
        beNDMWLoadCtrl2Info_GetVTable,
        beNDMWLoadCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2Info_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2Info_GetMetaObject(void)
{
    beNDMWLoadCtrl2Info_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2Info_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2Info_fieldTable[] = {
    "_nameSelList",
};
static igMetaField **g_beNDMWLoadCtrl2Info_fieldHandles[] = {
    &g_beNDMWLoadCtrl2Info_nameSelListMetaField,
};
static int g_beNDMWLoadCtrl2Info_fieldOffsets[] = {
    28,
};

void beNDMWLoadCtrl2Info_InitFields(void) {
    int base;
    void *nameSelList;
    igMetaObject *meta;

    meta = g_beNDMWLoadCtrl2Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadCtrl2Info_ctorTable, 1);
    nameSelList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)nameSelList)->_metaObject = igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWLoadCtrl2Info_fieldTable, g_beNDMWLoadCtrl2Info_fieldHandles, g_beNDMWLoadCtrl2Info_fieldOffsets, base);
}

