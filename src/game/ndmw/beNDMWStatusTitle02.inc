igMetaObject *g_beNDMWStatusTitle02_metaObject;

beNDMWStatusTitle02 *beNDMWStatusTitle02_Create(int allocator) {
    beNDMWStatusTitle02_EnsureRegistered();
    return (beNDMWStatusTitle02 *)igMetaObject_CreateInstance(g_beNDMWStatusTitle02_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusTitle02_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStatusTitle02_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStatusTitle02_EnsureRegistered();
    return g_beNDMWStatusTitle02_metaObject;
}

int beNDMWStatusTitle02_GetVTable(void) {
    beNDMWStatusTitle02 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusTitle02_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWStatusTitle02_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWStatusTitle02_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle02_Register);
}

CallbackArray *beNDMWStatusTitle02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle02_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle02_GetMetaObjectFunction,
        "beNDMWStatusTitle02",
        0x50, /* instance size */
        beNDMWStatusTitle02_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle02_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle02_GetMetaObject();
}

