igMetaObject *g_beNDMWStatusSelectE1_metaObject;

void beNDMWStatusSelectE1_Create(int allocator) {
    beNDMWStatusSelectE1_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSelectE1_metaObject, allocator);
}

void *beNDMWStatusSelectE1_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelectE1_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusSelectE1_EnsureRegistered();
    }
    return g_beNDMWStatusSelectE1_metaObject;
}

int beNDMWStatusSelectE1_GetVTable(void) {
    beNDMWStatusSelectE1 obj;
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
    *(int **)&obj._vtable = &g_beNDMWStatusSelectE1_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusSelectE1_vtable[0];
    beNDMWWindowSelect_Destroy((beNDMWWindowSelect *)&obj, 0);
    return vtable;
}

void beNDMWStatusSelectE1_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE1_Register);
}

void *beNDMWStatusSelectE1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelectE1_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE1_GetMetaObjectFunction,
        "beNDMWStatusSelectE1",
        0x70, /* instance size */
        beNDMWStatusSelectE1_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE1_GetMetaObjectFunction(void)
{
    beNDMWStatusSelectE1_GetMetaObject();
}

