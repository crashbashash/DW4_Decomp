igMetaObject *g_beNDMWShopCtrlSell_metaObject;

beNDMWShopCtrlSell *beNDMWShopCtrlSell_Create(int allocator) {
    beNDMWShopCtrlSell_EnsureRegistered();
    return (beNDMWShopCtrlSell *)igMetaObject_CreateInstance(g_beNDMWShopCtrlSell_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopCtrlSell_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlSell_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWShopCtrlSell_EnsureRegistered();
    }
    return g_beNDMWShopCtrlSell_metaObject;
}

int beNDMWShopCtrlSell_GetVTable(void) {
    beNDMWShopCtrlSell obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlSell_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlSell_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrlSell_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSell_Register);
}

CallbackArray *beNDMWShopCtrlSell_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlSell_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSell_GetMetaObjectFunction,
        "beNDMWShopCtrlSell",
        0x54, /* instance size */
        beNDMWShopCtrlSell_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlSell_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlSell_GetMetaObject();
}

