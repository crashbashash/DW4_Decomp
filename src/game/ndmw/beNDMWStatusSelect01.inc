igMetaObject *g_beNDMWStatusSelect01_metaObject;

beNDMWStatusSelect01 *beNDMWStatusSelect01_Create(int allocator) {
    beNDMWStatusSelect01_EnsureRegistered();
    return (beNDMWStatusSelect01 *)igMetaObject_CreateInstance(g_beNDMWStatusSelect01_metaObject, allocator);
}

igMetaObject *beNDMWStatusSelect01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelect01_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStatusSelect01_EnsureRegistered();
    return g_beNDMWStatusSelect01_metaObject;
}

int beNDMWStatusSelect01_GetVTable(void) {
    beNDMWStatusSelect01 obj;
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
    *(int **)&obj._vtable = &g_beNDMWStatusSelect01_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusSelect01_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWStatusSelect01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect01_Register);
}

void *beNDMWStatusSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect01_GetMetaObjectFunction,
        "beNDMWStatusSelect01",
        0x70, /* instance size */
        beNDMWStatusSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelect01_GetMetaObjectFunction(void)
{
    beNDMWStatusSelect01_GetMetaObject();
}

