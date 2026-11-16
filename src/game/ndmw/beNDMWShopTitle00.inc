igMetaObject *g_beNDMWShopTitle00_metaObject;

beNDMWShopTitle00 *beNDMWShopTitle00_Create(int allocator) {
    beNDMWShopTitle00_EnsureRegistered();
    return (beNDMWShopTitle00 *)igMetaObject_CreateInstance(g_beNDMWShopTitle00_metaObject, allocator);
}

void *beNDMWShopTitle00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopTitle00_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopTitle00_EnsureRegistered();
    }
    return g_beNDMWShopTitle00_metaObject;
}

int beNDMWShopTitle00_GetVTable(void) {
    beNDMWShopTitle00 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopTitle00_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopTitle00_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWShopTitle00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle00_Register);
}

void *beNDMWShopTitle00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopTitle00_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle00_GetMetaObjectFunction,
        "beNDMWShopTitle00",
        0x50, /* instance size */
        beNDMWShopTitle00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle00_GetMetaObjectFunction(void)
{
    beNDMWShopTitle00_GetMetaObject();
}

