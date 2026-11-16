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
    Obj_3b7170 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &g_beNDMWShopCtrlDeviceSell_vtable[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWShopCtrlDeviceSell_vtable[0];
    FUN_00226990(&o.s, -1);
    FUN_003b6770((int **)&o, (long long)0);
    return r;
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

