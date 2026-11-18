igMetaObject *g_beNDMWShopSelect01_metaObject;

beNDMWShopSelect01 *beNDMWShopSelect01_Create(int allocator) {
    beNDMWShopSelect01_EnsureRegistered();
    return (beNDMWShopSelect01 *)igMetaObject_CreateInstance(g_beNDMWShopSelect01_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopSelect01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect01_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect01_EnsureRegistered();
    }
    return g_beNDMWShopSelect01_metaObject;
}

int beNDMWShopSelect01_GetVTable(void) {
    beNDMWShopSelect01 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect01_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWShopSelect01_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect01_Register);
}

CallbackArray *beNDMWShopSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect01_GetMetaObjectFunction,
        "beNDMWShopSelect01",
        0x70, /* instance size */
        beNDMWShopSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect01_GetMetaObjectFunction(void)
{
    beNDMWShopSelect01_GetMetaObject();
}

