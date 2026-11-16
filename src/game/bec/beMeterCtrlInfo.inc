igMetaObject *g_beMeterCtrlInfo_metaObject;
igMetaField *g_beMeterCtrlInfo_oneDataListMetaField;

void *beMeterCtrlInfo_GetMetaObject(void) {
    bool ok;
    if (g_beMeterCtrlInfo_metaObject == 0) goto make;
    ok = !!(g_beMeterCtrlInfo_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beMeterCtrlInfo_EnsureRegistered();
done:;
    return g_beMeterCtrlInfo_metaObject;
}

int beMeterCtrlInfo_GetVTable(void) {
    beMeterCtrlInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beMeterCtrlInfo_vtable[0];
    obj._oneDataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beMeterCtrlInfo_vtable[0];
    igSmartPointer_igNamedObjectList_Destruct(&obj._oneDataList, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beMeterCtrlInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrlInfo_Register);
}

static igMetaObjectCallback g_beMeterCtrlInfo_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

CallbackArray *beMeterCtrlInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMeterCtrlInfo_GetMetaObjectFunction,
        "beMeterCtrlInfo",
        0x20, /* instance size */
        beMeterCtrlInfo_GetVTable,
        beMeterCtrlInfo_InitFields,
        0, /* extra callback item */
        g_beMeterCtrlInfo_callbackList /* callback list */
    );
}

void beMeterCtrlInfo_GetMetaObjectFunction(void)
{
    beMeterCtrlInfo_GetMetaObject();
}

static FieldFactory g_beMeterCtrlInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beMeterCtrlInfo_fieldTable[] = {
    "_oneDataList",
};
static igMetaField **g_beMeterCtrlInfo_fieldHandles[] = {
    &g_beMeterCtrlInfo_oneDataListMetaField,
};
static int g_beMeterCtrlInfo_fieldOffsets[] = {
    28,
};

void beMeterCtrlInfo_InitFields(void) {
    int base;
    void *oneDataList;
    igMetaObject *meta;

    meta = g_beMeterCtrlInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMeterCtrlInfo_ctorTable, 1);
    oneDataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)oneDataList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)oneDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMeterCtrlInfo_fieldTable, g_beMeterCtrlInfo_fieldHandles, g_beMeterCtrlInfo_fieldOffsets, base);
}

