igMetaObject *g_beNDMWShopCtrl10_metaObject;
igMetaField *g_beNDMWShopCtrl10_xdataMenuMetaField;
igMetaField *g_beNDMWShopCtrl10_parameterMetaField;

void beNDMWShopCtrl10_Create(int allocator) {
    beNDMWShopCtrl10_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrl10_metaObject, allocator);
}

void *beNDMWShopCtrl10_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrl10_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrl10_EnsureRegistered();
    }
    return g_beNDMWShopCtrl10_metaObject;
}

int beNDMWShopCtrl10_GetVTable(void) {
    beNDMWShopCtrl10 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrl10_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrl10_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrl10_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl10_Register);
}

void *beNDMWShopCtrl10_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl10_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl10_GetMetaObjectFunction,
        "beNDMWShopCtrl10",
        0x5c, /* instance size */
        beNDMWShopCtrl10_GetVTable,
        beNDMWShopCtrl10_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl10_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl10_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl10_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl10_fieldTable[] = {
    "_xdataMenu",
    "_parameter",
};
static igMetaField **g_beNDMWShopCtrl10_fieldHandles[] = {
    &g_beNDMWShopCtrl10_xdataMenuMetaField,
    &g_beNDMWShopCtrl10_parameterMetaField,
};
static int g_beNDMWShopCtrl10_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrl10_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrl10_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrl10_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beNDMWShopCtrl10_fieldTable, g_beNDMWShopCtrl10_fieldHandles, g_beNDMWShopCtrl10_fieldOffsets, base);
}

