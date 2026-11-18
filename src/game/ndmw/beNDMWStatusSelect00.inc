igMetaObject *g_beNDMWStatusSelect00_metaObject;

beNDMWStatusSelect00 *beNDMWStatusSelect00_Create(int allocator) {
    beNDMWStatusSelect00_EnsureRegistered();
    return (beNDMWStatusSelect00 *)igMetaObject_CreateInstance(g_beNDMWStatusSelect00_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusSelect00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelect00_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWStatusSelect00_EnsureRegistered();
done:
    return g_beNDMWStatusSelect00_metaObject;
}

int beNDMWStatusSelect00_GetVTable(void) {
    beNDMWStatusSelect00 obj;
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
    *(int **)&obj._vtable = &g_beNDMWStatusSelect00_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusSelect00_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWStatusSelect00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect00_Register);
}

CallbackArray *beNDMWStatusSelect00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelect00_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect00_GetMetaObjectFunction,
        "beNDMWStatusSelect00",
        0x70, /* instance size */
        beNDMWStatusSelect00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelect00_GetMetaObjectFunction(void)
{
    beNDMWStatusSelect00_GetMetaObject();
}

