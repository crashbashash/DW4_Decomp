igMetaObject *g_beNDMWShopSelect34_metaObject;

void beNDMWShopSelect34_Create(int allocator) {
    beNDMWShopSelect34_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopSelect34_metaObject, allocator);
}

void *beNDMWShopSelect34_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelect34_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelect34_EnsureRegistered();
    }
    return g_beNDMWShopSelect34_metaObject;
}

int beNDMWShopSelect34_GetVTable(void) {
    beNDMWShopSelect34 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect34_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelect34_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect34_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect34_Register);
}

void *beNDMWShopSelect34_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect34_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect34_GetMetaObjectFunction,
        "beNDMWShopSelect34",
        0x70, /* instance size */
        beNDMWShopSelect34_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect34_GetMetaObjectFunction(void)
{
    beNDMWShopSelect34_GetMetaObject();
}

