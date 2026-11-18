igMetaObject *g_beNDMWShopSelect02_metaObject;
igMetaField *g_beNDMWShopSelect02_playerNoListMetaField;

beNDMWShopSelect02 *beNDMWShopSelect02_Create(int allocator) {
    beNDMWShopSelect02_EnsureRegistered();
    return (beNDMWShopSelect02 *)igMetaObject_CreateInstance(g_beNDMWShopSelect02_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopSelect02_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect02_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect02_EnsureRegistered();
    }
    return g_beNDMWShopSelect02_metaObject;
}

int beNDMWShopSelect02_GetVTable(void) {
    beNDMWShopSelect02 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect02_vtable[0];
    obj._playerNoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWShopSelect02_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._playerNoList, -1);
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect02_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect02_Register);
}

static igMetaObjectCallback g_beNDMWShopSelect02_callbackList[] = { igIntList_EnsureRegistered, 0 };

CallbackArray *beNDMWShopSelect02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect02_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect02_GetMetaObjectFunction,
        "beNDMWShopSelect02",
        0x74, /* instance size */
        beNDMWShopSelect02_GetVTable,
        beNDMWShopSelect02_InitFields,
        0, /* extra callback item */
        g_beNDMWShopSelect02_callbackList /* callback list */
    );
}

void beNDMWShopSelect02_GetMetaObjectFunction(void)
{
    beNDMWShopSelect02_GetMetaObject();
}

static FieldFactory g_beNDMWShopSelect02_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopSelect02_fieldTable[] = {
    "_playerNoList",
};
static igMetaField **g_beNDMWShopSelect02_fieldHandles[] = {
    &g_beNDMWShopSelect02_playerNoListMetaField,
};
static int g_beNDMWShopSelect02_fieldOffsets[] = {
    112,
};

void beNDMWShopSelect02_InitFields(void) {
    int base;
    void *playerNoList;
    igMetaObject *meta;

    meta = g_beNDMWShopSelect02_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopSelect02_ctorTable, 1);
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopSelect02_fieldTable, g_beNDMWShopSelect02_fieldHandles, g_beNDMWShopSelect02_fieldOffsets, base);
}

