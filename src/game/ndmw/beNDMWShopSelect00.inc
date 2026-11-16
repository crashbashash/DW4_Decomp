igMetaObject *g_beNDMWShopSelect00_metaObject;
igMetaField *g_beNDMWShopSelect00_panelNameMetaField;

void beNDMWShopSelect00_Create(int allocator) {
    beNDMWShopSelect00_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect00_metaObject, allocator);
}

void *beNDMWShopSelect00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect00_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect00_EnsureRegistered();
    }
    return g_beNDMWShopSelect00_metaObject;
}

int beNDMWShopSelect00_GetVTable(void) {
    beNDMWShopSelect00 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    obj._infoName = 0;
    obj._decideList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopSelect00_vtable[0];
    obj._panelName = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelect00_vtable[0];
    igStringRef_Destruct(&obj._panelName, -1);
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect00_Register);
}

void *beNDMWShopSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect00_GetMetaObjectFunction,
        "beNDMWShopSelect00",
        0x74, /* instance size */
        beNDMWShopSelect00_GetVTable,
        beNDMWShopSelect00_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect00_GetMetaObjectFunction(void)
{
    beNDMWShopSelect00_GetMetaObject();
}

static FieldFactory g_beNDMWShopSelect00_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beNDMWShopSelect00_fieldTable[] = {
    "_panelName",
};
static igMetaField **g_beNDMWShopSelect00_fieldHandles[] = {
    &g_beNDMWShopSelect00_panelNameMetaField,
};
static int g_beNDMWShopSelect00_fieldOffsets[] = {
    112,
};

void beNDMWShopSelect00_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWShopSelect00_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopSelect00_ctorTable, 1);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base)), 0);
    igMetaObject_NameFields(meta, g_beNDMWShopSelect00_fieldTable, g_beNDMWShopSelect00_fieldHandles, g_beNDMWShopSelect00_fieldOffsets, base);
}

