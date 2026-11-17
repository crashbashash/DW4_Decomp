igMetaObject *g_beCameraCtrlInfo_metaObject;
igMetaField *g_beCameraCtrlInfo_dataMetaField;

void *beCameraCtrlInfo_GetMetaObject(void) {
    igMetaObject *g = g_beCameraCtrlInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCameraCtrlInfo_EnsureRegistered();
    }
    return g_beCameraCtrlInfo_metaObject;
}

int beCameraCtrlInfo_GetVTable(void) {
    beCameraCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beCameraCtrlInfo_vtable[0];
    obj._data = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beCameraCtrlInfo_vtable[0];
    igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj._data, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beCameraCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraCtrlInfo_Register);
}

static igMetaObjectCallback g_beCameraCtrlInfo_callbackList[] = { igObject_EnsureRegistered, 0 };

CallbackArray *beCameraCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beCameraCtrlInfo_GetMetaObjectFunction,
        "beCameraCtrlInfo",
        0x20, /* instance size */
        beCameraCtrlInfo_GetVTable,
        beCameraCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beCameraCtrlInfo_callbackList /* callback list */
    );
}

void beCameraCtrlInfo_GetMetaObjectFunction(void)
{
    beCameraCtrlInfo_GetMetaObject();
}

static FieldFactory g_beCameraCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beCameraCtrlInfo_fieldTable[] = {
    "_data",
};
static igMetaField **g_beCameraCtrlInfo_fieldHandles[] = {
    &g_beCameraCtrlInfo_dataMetaField,
};
static int g_beCameraCtrlInfo_fieldOffsets[] = {
    28,
};

void beCameraCtrlInfo_InitFields(void) {
    int base;
    void *f;
    igMetaObject *meta;

    meta = g_beCameraCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraCtrlInfo_ctorTable, 1);
    f = igMetaObject_GetFieldAt(meta, base);
    ((igObjectRefMetaField *)f)->_metaObject = (int)g_igObject_metaObject;
    igMetaObject_NameFields(meta, g_beCameraCtrlInfo_fieldTable, g_beCameraCtrlInfo_fieldHandles, g_beCameraCtrlInfo_fieldOffsets, base);
}

