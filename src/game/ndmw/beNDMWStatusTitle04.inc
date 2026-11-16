igMetaObject *g_beNDMWStatusTitle04_metaObject;

void beNDMWStatusTitle04_Create(int allocator) {
    beNDMWStatusTitle04_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusTitle04_metaObject, allocator);
}

void *beNDMWStatusTitle04_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle04_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusTitle04_EnsureRegistered();
    }
    return g_beNDMWStatusTitle04_metaObject;
}

int beNDMWStatusTitle04_GetVTable(void) {
    beNDMWStatusTitle04 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusTitle04_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusTitle04_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWStatusTitle04_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle04_Register);
}

void *beNDMWStatusTitle04_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle04_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle04_GetMetaObjectFunction,
        "beNDMWStatusTitle04",
        0x50, /* instance size */
        beNDMWStatusTitle04_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle04_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle04_GetMetaObject();
}

