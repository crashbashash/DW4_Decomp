igMetaObject *g_beNDMWShopCtrlEditBit_metaObject;
igMetaField *g_beNDMWShopCtrlEditBit_editBitMetaField;
igMetaField *g_beNDMWShopCtrlEditBit_editMaxMetaField;

beNDMWShopCtrlEditBit *beNDMWShopCtrlEditBit_Create(int allocator) {
    beNDMWShopCtrlEditBit_EnsureRegistered();
    return (beNDMWShopCtrlEditBit *)igMetaObject_CreateInstance(g_beNDMWShopCtrlEditBit_metaObject, allocator);
}

igMetaObject *beNDMWShopCtrlEditBit_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWShopCtrlEditBit_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWShopCtrlEditBit_EnsureRegistered();
    return g_beNDMWShopCtrlEditBit_metaObject;
}

int beNDMWShopCtrlEditBit_GetVTable(void) {
    beNDMWShopCtrlEditBit obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlEditBit_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlEditBit_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrlEditBit_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlEditBit_Register);
}

void *beNDMWShopCtrlEditBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlEditBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlEditBit_GetMetaObjectFunction,
        "beNDMWShopCtrlEditBit",
        0x5c, /* instance size */
        beNDMWShopCtrlEditBit_GetVTable,
        beNDMWShopCtrlEditBit_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlEditBit_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlEditBit_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrlEditBit_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrlEditBit_fieldTable[] = {
    "_editBit",
    "_editMax",
};
static igMetaField **g_beNDMWShopCtrlEditBit_fieldHandles[] = {
    &g_beNDMWShopCtrlEditBit_editBitMetaField,
    &g_beNDMWShopCtrlEditBit_editMaxMetaField,
};
static int g_beNDMWShopCtrlEditBit_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrlEditBit_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlEditBit_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlEditBit_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlEditBit_fieldTable, g_beNDMWShopCtrlEditBit_fieldHandles, g_beNDMWShopCtrlEditBit_fieldOffsets, base);
}

