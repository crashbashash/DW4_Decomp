igMetaObject *g_beNDMWStatusSelectE0_metaObject;

beNDMWStatusSelectE0 *beNDMWStatusSelectE0_Create(int allocator) {
    beNDMWStatusSelectE0_EnsureRegistered();
    return (beNDMWStatusSelectE0 *)igMetaObject_CreateInstance(g_beNDMWStatusSelectE0_metaObject, allocator);
}

igMetaObject *beNDMWStatusSelectE0_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStatusSelectE0_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStatusSelectE0_EnsureRegistered();
    return g_beNDMWStatusSelectE0_metaObject;
}

int beNDMWStatusSelectE0_GetVTable(void) {
    beNDMWStatusSelectE0 obj;
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
    *(int **)&obj._vtable = &g_beNDMWStatusSelectE0_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusSelectE0_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWStatusSelectE0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE0_Register);
}

void *beNDMWStatusSelectE0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelectE0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE0_GetMetaObjectFunction,
        "beNDMWStatusSelectE0",
        0x70, /* instance size */
        beNDMWStatusSelectE0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE0_GetMetaObjectFunction(void)
{
    beNDMWStatusSelectE0_GetMetaObject();
}

