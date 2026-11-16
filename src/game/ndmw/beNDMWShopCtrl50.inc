igMetaObject *g_beNDMWShopCtrl50_metaObject;
igMetaField *g_beNDMWShopCtrl50_cursorMetaField;
igMetaField *g_beNDMWShopCtrl50_conItemNoMetaField;
igMetaField *g_beNDMWShopCtrl50_diskCntMetaField;
igMetaField *g_beNDMWShopCtrl50_kazuMetaField;
igMetaField *g_beNDMWShopCtrl50_tankaMetaField;

beNDMWShopCtrl50 *beNDMWShopCtrl50_Create(int allocator) {
    beNDMWShopCtrl50_EnsureRegistered();
    return (beNDMWShopCtrl50 *)igMetaObject_CreateInstance(g_beNDMWShopCtrl50_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopCtrl50_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrl50_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrl50_EnsureRegistered();
    }
    return g_beNDMWShopCtrl50_metaObject;
}

int beNDMWShopCtrl50_GetVTable(void) {
    beNDMWShopCtrl50 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrl50_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrl50_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrl50_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrl50_Register);
}

CallbackArray *beNDMWShopCtrl50_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrl50_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrl50_GetMetaObjectFunction,
        "beNDMWShopCtrl50",
        0x68, /* instance size */
        beNDMWShopCtrl50_GetVTable,
        beNDMWShopCtrl50_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrl50_GetMetaObjectFunction(void)
{
    beNDMWShopCtrl50_GetMetaObject();
}

static FieldFactory g_beNDMWShopCtrl50_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWShopCtrl50_fieldTable[] = {
    "_cursor",
    "_conItemNo",
    "_diskCnt",
    "_kazu",
    "_tanka",
};
static igMetaField **g_beNDMWShopCtrl50_fieldHandles[] = {
    &g_beNDMWShopCtrl50_cursorMetaField,
    &g_beNDMWShopCtrl50_conItemNoMetaField,
    &g_beNDMWShopCtrl50_diskCntMetaField,
    &g_beNDMWShopCtrl50_kazuMetaField,
    &g_beNDMWShopCtrl50_tankaMetaField,
};
static int g_beNDMWShopCtrl50_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
};

void beNDMWShopCtrl50_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrl50_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrl50_ctorTable, 5);
    igMetaObject_NameFields(meta, g_beNDMWShopCtrl50_fieldTable, g_beNDMWShopCtrl50_fieldHandles, g_beNDMWShopCtrl50_fieldOffsets, base);
}

