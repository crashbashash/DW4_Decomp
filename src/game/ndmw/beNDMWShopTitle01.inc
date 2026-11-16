igMetaObject *g_beNDMWShopTitle01_metaObject;

beNDMWShopTitle01 *beNDMWShopTitle01_Create(int allocator) {
    beNDMWShopTitle01_EnsureRegistered();
    return (beNDMWShopTitle01 *)igMetaObject_CreateInstance(g_beNDMWShopTitle01_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopTitle01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopTitle01_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopTitle01_EnsureRegistered();
    }
    return g_beNDMWShopTitle01_metaObject;
}

int beNDMWShopTitle01_GetVTable(void) {
    beNDMWShopTitle01 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopTitle01_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopTitle01_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWShopTitle01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopTitle01_Register);
}

CallbackArray *beNDMWShopTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWShopTitle01_GetMetaObjectFunction,
        "beNDMWShopTitle01",
        0x50, /* instance size */
        beNDMWShopTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopTitle01_GetMetaObjectFunction(void)
{
    beNDMWShopTitle01_GetMetaObject();
}

