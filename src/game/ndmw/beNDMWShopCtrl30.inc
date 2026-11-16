igMetaObject *g_beNDMWShopCtrl30_metaObject;
igMetaField *g_beNDMWShopCtrl30_bankMenuMetaField;

void beNDMWShopCtrl30_Create(int allocator) {
    beNDMWShopCtrl30_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrl30_metaObject, allocator);
}

void *beNDMWShopCtrl30_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrl30_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrl30_EnsureRegistered();
    }
    return g_beNDMWShopCtrl30_metaObject;
}

int beNDMWShopCtrl30_GetVTable(void) {
    beNDMWShopCtrl30 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrl30_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrl30_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrl30_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl30_Register);
}

void *beNDMWShopCtrl30_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl30_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl30_GetMetaObjectFunction,
        "beNDMWShopCtrl30",
        0x58, /* instance size */
        beNDMWShopCtrl30_GetVTable,
        beNDMWShopCtrl30_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl30_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl30_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl30_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl30_fieldTable[] = {
    "_bankMenu",
};
static igMetaField **g_beNDMWShopCtrl30_fieldHandles[] = {
    &g_beNDMWShopCtrl30_bankMenuMetaField,
};
static int g_beNDMWShopCtrl30_fieldOffsets[] = {
    84,
};

void beNDMWShopCtrl30_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrl30_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrl30_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWShopCtrl30_fieldTable, g_beNDMWShopCtrl30_fieldHandles, g_beNDMWShopCtrl30_fieldOffsets, base);
}

