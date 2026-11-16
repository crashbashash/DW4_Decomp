igMetaObject *g_beNDMWShopSelect11_metaObject;

beNDMWShopSelect11 *beNDMWShopSelect11_Create(int allocator) {
    beNDMWShopSelect11_EnsureRegistered();
    return (beNDMWShopSelect11 *)igMetaObject_CreateInstance(g_beNDMWShopSelect11_metaObject, allocator);
}

void *beNDMWShopSelect11_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWShopSelect11_metaObject != 0) {
        b = (g_beNDMWShopSelect11_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWShopSelect11_EnsureRegistered();
done:
    return g_beNDMWShopSelect11_metaObject;
}

int beNDMWShopSelect11_GetVTable(void) {
    beNDMWShopSelect11 obj;
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
    *(int **)&obj._vtable = &g_beNDMWShopSelect11_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWShopSelect11_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWShopSelect11_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopSelect11_Register);
}

void *beNDMWShopSelect11_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopSelect11_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWShopSelect11_GetMetaObjectFunction,
        "beNDMWShopSelect11",
        0x70, /* instance size */
        beNDMWShopSelect11_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWShopSelect11_GetMetaObjectFunction(void)
{
    beNDMWShopSelect11_GetMetaObject();
}

