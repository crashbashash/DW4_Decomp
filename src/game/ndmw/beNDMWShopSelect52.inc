igMetaObject *g_beNDMWShopSelect52_metaObject;

beNDMWShopSelect52 *beNDMWShopSelect52_Create(int allocator) {
    beNDMWShopSelect52_EnsureRegistered();
    return (beNDMWShopSelect52 *)igMetaObject_CreateInstance(g_beNDMWShopSelect52_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWShopSelect52_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWShopSelect52_metaObject == 0) goto make;
    ok = !!(g_beNDMWShopSelect52_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWShopSelect52_EnsureRegistered();
done:;
    return g_beNDMWShopSelect52_metaObject;
}

int beNDMWShopSelect52_GetVTable(void) {
    beNDMWShopSelect52 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect52_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWShopSelect52_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect52_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect52_Register);
}

CallbackArray *beNDMWShopSelect52_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect52_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect52_GetMetaObjectFunction,
        "beNDMWShopSelect52",
        0x70, /* instance size */
        beNDMWShopSelect52_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect52_GetMetaObjectFunction(void)
{
    beNDMWShopSelect52_GetMetaObject();
}

