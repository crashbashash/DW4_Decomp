igMetaObject *g_beNDMWStatusTitle01_metaObject;

beNDMWStatusTitle01 *beNDMWStatusTitle01_Create(int allocator) {
    beNDMWStatusTitle01_EnsureRegistered();
    return (beNDMWStatusTitle01 *)igMetaObject_CreateInstance(g_beNDMWStatusTitle01_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusTitle01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle01_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStatusTitle01_EnsureRegistered();
    return g_beNDMWStatusTitle01_metaObject;
}

int beNDMWStatusTitle01_GetVTable(void) {
    beNDMWStatusTitle01 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusTitle01_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusTitle01_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWStatusTitle01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle01_Register);
}

CallbackArray *beNDMWStatusTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle01_GetMetaObjectFunction,
        "beNDMWStatusTitle01",
        0x50, /* instance size */
        beNDMWStatusTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle01_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle01_GetMetaObject();
}

