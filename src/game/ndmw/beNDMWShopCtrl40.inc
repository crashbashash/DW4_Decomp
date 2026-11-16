igMetaObject *g_beNDMWShopCtrl40_metaObject;
igMetaField *g_beNDMWShopCtrl40_selectCursorMetaField;

beNDMWShopCtrl40 *beNDMWShopCtrl40_Create(int allocator) {
    beNDMWShopCtrl40_EnsureRegistered();
    return (beNDMWShopCtrl40 *)igMetaObject_CreateInstance(g_beNDMWShopCtrl40_metaObject, allocator);
}

void *beNDMWShopCtrl40_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWShopCtrl40_metaObject == 0) goto make;
    ok = !!(g_beNDMWShopCtrl40_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWShopCtrl40_EnsureRegistered();
done:;
    return g_beNDMWShopCtrl40_metaObject;
}

int beNDMWShopCtrl40_GetVTable(void) {
    beNDMWShopCtrl40 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrl40_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrl40_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrl40_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl40_Register);
}

void *beNDMWShopCtrl40_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl40_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl40_GetMetaObjectFunction,
        "beNDMWShopCtrl40",
        0x58, /* instance size */
        beNDMWShopCtrl40_GetVTable,
        beNDMWShopCtrl40_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl40_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl40_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl40_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl40_fieldTable[] = {
    "_selectCursor",
};
static igMetaField **g_beNDMWShopCtrl40_fieldHandles[] = {
    &g_beNDMWShopCtrl40_selectCursorMetaField,
};
static int g_beNDMWShopCtrl40_fieldOffsets[] = {
    84,
};

void beNDMWShopCtrl40_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrl40_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrl40_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWShopCtrl40_fieldTable, g_beNDMWShopCtrl40_fieldHandles, g_beNDMWShopCtrl40_fieldOffsets, base);
}

