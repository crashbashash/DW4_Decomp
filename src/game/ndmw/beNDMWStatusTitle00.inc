igMetaObject *g_beNDMWStatusTitle00_metaObject;

beNDMWStatusTitle00 *beNDMWStatusTitle00_Create(int allocator) {
    beNDMWStatusTitle00_EnsureRegistered();
    return (beNDMWStatusTitle00 *)igMetaObject_CreateInstance(g_beNDMWStatusTitle00_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusTitle00_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle00_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWStatusTitle00_EnsureRegistered();
done:
    return g_beNDMWStatusTitle00_metaObject;
}

int beNDMWStatusTitle00_GetVTable(void) {
    beNDMWStatusTitle00 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusTitle00_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusTitle00_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWStatusTitle00_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle00_Register);
}

CallbackArray *beNDMWStatusTitle00_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle00_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle00_GetMetaObjectFunction,
        "beNDMWStatusTitle00",
        0x50, /* instance size */
        beNDMWStatusTitle00_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle00_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle00_GetMetaObject();
}

