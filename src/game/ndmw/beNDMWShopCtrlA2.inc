igMetaObject *g_beNDMWShopCtrlA2_metaObject;

beNDMWShopCtrlA2 *beNDMWShopCtrlA2_Create(int allocator) {
    beNDMWShopCtrlA2_EnsureRegistered();
    return (beNDMWShopCtrlA2 *)igMetaObject_CreateInstance(g_beNDMWShopCtrlA2_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWShopCtrlA2_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlA2_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWShopCtrlA2_EnsureRegistered();
done:
    return g_beNDMWShopCtrlA2_metaObject;
}

int beNDMWShopCtrlA2_GetVTable(void) {
    beNDMWShopCtrlA2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA2_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA2_vtable[0];
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrlA2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA2_Register);
}

CallbackArray *beNDMWShopCtrlA2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlA2_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA2_GetMetaObjectFunction,
        "beNDMWShopCtrlA2",
        0x54, /* instance size */
        beNDMWShopCtrlA2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopCtrlA2_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlA2_GetMetaObject();
}

