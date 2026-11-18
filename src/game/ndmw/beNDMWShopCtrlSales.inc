igMetaObject *g_beNDMWShopCtrlSales_metaObject;
igMetaField *g_beNDMWShopCtrlSales_salesItemListMetaField;
igMetaField *g_beNDMWShopCtrlSales_decideListMetaField;

beNDMWShopCtrlSales *beNDMWShopCtrlSales_Create(int allocator) {
    beNDMWShopCtrlSales_EnsureRegistered();
    return (beNDMWShopCtrlSales *)igMetaObject_CreateInstance(g_beNDMWShopCtrlSales_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopCtrlSales_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlSales_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlSales_EnsureRegistered();
    }
    return g_beNDMWShopCtrlSales_metaObject;
}

int beNDMWShopCtrlSales_GetVTable(void) {
    beNDMWShopCtrlSales obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlSales_vtable[0];
    obj._salesItemList = 0;
    obj._decideList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWShopCtrlSales_vtable[0];
    igSmartPointer_igBoolList_Destruct((igSmartPointer<igObject> *)&obj._decideList, -1);
    igSmartPointer_beNDMWItemBaseList_Destruct((igSmartPointer<igObject> *)&obj._salesItemList, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

void beNDMWShopCtrlSales_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSales_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlSales_callbackList[] = { beNDMWItemBaseList_EnsureRegistered, igBoolList_EnsureRegistered, 0 };

CallbackArray *beNDMWShopCtrlSales_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlSales_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSales_GetMetaObjectFunction,
        "beNDMWShopCtrlSales",
        0x68, /* instance size */
        beNDMWShopCtrlSales_GetVTable,
        beNDMWShopCtrlSales_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlSales_callbackList /* callback list */
    );
}

void beNDMWShopCtrlSales_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlSales_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlSales_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlSales_fieldTable[] = {
    "_salesItemList",
    "_decideList",
};
static igMetaField **g_beNDMWShopCtrlSales_fieldHandles[] = {
    &g_beNDMWShopCtrlSales_salesItemListMetaField,
    &g_beNDMWShopCtrlSales_decideListMetaField,
};
static int g_beNDMWShopCtrlSales_fieldOffsets[] = {
    96,
    100,
};

void beNDMWShopCtrlSales_InitFields(void) {
    int base;
    void *decideList;
    void *salesItemList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlSales_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlSales_ctorTable, 2);
    salesItemList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)salesItemList)->_metaObject = (int)beNDMWItemBaseList_GetOrCreateMetaObject();
    decideList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)decideList)->_metaObject = (int)igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)decideList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlSales_fieldTable, g_beNDMWShopCtrlSales_fieldHandles, g_beNDMWShopCtrlSales_fieldOffsets, base);
}

