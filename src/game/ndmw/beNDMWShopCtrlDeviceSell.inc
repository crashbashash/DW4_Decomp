igMetaObject *g_beNDMWShopCtrlDeviceSell_metaObject;
igMetaField *g_beNDMWShopCtrlDeviceSell_decideListMetaField;

void beNDMWShopCtrlDeviceSell_Create(int allocator) {
    beNDMWShopCtrlDeviceSell_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlDeviceSell_metaObject, allocator);
}

void *beNDMWShopCtrlDeviceSell_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlDeviceSell_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlDeviceSell_EnsureRegistered();
    }
    return g_beNDMWShopCtrlDeviceSell_metaObject;
}

int beNDMWShopCtrlDeviceSell_GetVTable(void) {
    beNDMWShopCtrlDeviceSell obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlDeviceSell_vtable[0];
    obj._decideList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlDeviceSell_vtable[0];
    igSmartPointer_igBoolList_Destruct(&obj._decideList, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

void beNDMWShopCtrlDeviceSell_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDeviceSell_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlDeviceSell_callbackList[] = { igBoolList_EnsureRegistered, 0 };

void *beNDMWShopCtrlDeviceSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlDeviceSell_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDeviceSell_GetMetaObjectFunction,
        "beNDMWShopCtrlDeviceSell",
        0x64, /* instance size */
        beNDMWShopCtrlDeviceSell_GetVTable,
        beNDMWShopCtrlDeviceSell_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDeviceSell_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDeviceSell_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlDeviceSell_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlDeviceSell_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlDeviceSell_fieldTable[] = {
    "_decideList",
};
static igMetaField **g_beNDMWShopCtrlDeviceSell_fieldHandles[] = {
    &g_beNDMWShopCtrlDeviceSell_decideListMetaField,
};
static int g_beNDMWShopCtrlDeviceSell_fieldOffsets[] = {
    96,
};

void beNDMWShopCtrlDeviceSell_InitFields(void) {
    int base;
    void *decideList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlDeviceSell_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlDeviceSell_ctorTable, 1);
    decideList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)decideList)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)decideList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlDeviceSell_fieldTable, g_beNDMWShopCtrlDeviceSell_fieldHandles, g_beNDMWShopCtrlDeviceSell_fieldOffsets, base);
}

