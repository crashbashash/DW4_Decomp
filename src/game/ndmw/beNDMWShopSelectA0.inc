igMetaObject *g_beNDMWShopSelectA0_metaObject;

beNDMWShopSelectA0 *beNDMWShopSelectA0_Create(int allocator) {
    beNDMWShopSelectA0_EnsureRegistered();
    return (beNDMWShopSelectA0 *)igMetaObject_CreateInstance(g_beNDMWShopSelectA0_metaObject, allocator);
}

void *beNDMWShopSelectA0_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopSelectA0_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopSelectA0_EnsureRegistered();
    }
    return g_beNDMWShopSelectA0_metaObject;
}

int beNDMWShopSelectA0_GetVTable(void) {
    beNDMWShopSelectA0 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelectA0_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelectA0_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelectA0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelectA0_Register);
}

void *beNDMWShopSelectA0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelectA0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelectA0_GetMetaObjectFunction,
        "beNDMWShopSelectA0",
        0x70, /* instance size */
        beNDMWShopSelectA0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelectA0_GetMetaObjectFunction(void)
{
    beNDMWShopSelectA0_GetMetaObject();
}

