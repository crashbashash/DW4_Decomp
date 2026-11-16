igMetaObject *g_beNDMWShopSelect03_metaObject;

beNDMWShopSelect03 *beNDMWShopSelect03_Create(int allocator) {
    beNDMWShopSelect03_EnsureRegistered();
    return (beNDMWShopSelect03 *)igMetaObject_CreateInstance(g_beNDMWShopSelect03_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopSelect03_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect03_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect03_EnsureRegistered();
    }
    return g_beNDMWShopSelect03_metaObject;
}

int beNDMWShopSelect03_GetVTable(void) {
    beNDMWShopSelect03 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect03_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelect03_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect03_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect03_Register);
}

CallbackArray *beNDMWShopSelect03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect03_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect03_GetMetaObjectFunction,
        "beNDMWShopSelect03",
        0x70, /* instance size */
        beNDMWShopSelect03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect03_GetMetaObjectFunction(void)
{
    beNDMWShopSelect03_GetMetaObject();
}

