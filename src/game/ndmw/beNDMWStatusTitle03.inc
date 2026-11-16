igMetaObject *g_beNDMWStatusTitle03_metaObject;

beNDMWStatusTitle03 *beNDMWStatusTitle03_Create(int allocator) {
    beNDMWStatusTitle03_EnsureRegistered();
    return (beNDMWStatusTitle03 *)igMetaObject_CreateInstance(g_beNDMWStatusTitle03_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWStatusTitle03_GetOrCreateMetaObject(void) {
    if (g_beNDMWStatusTitle03_metaObject == 0) {
        g_beNDMWStatusTitle03_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWStatusTitle03_metaObject;
}

void *beNDMWStatusTitle03_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle03_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusTitle03_EnsureRegistered();
    }
    return g_beNDMWStatusTitle03_metaObject;
}

int beNDMWStatusTitle03_GetVTable(void) {
    beNDMWStatusTitle03 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusTitle03_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusTitle03_vtable[0];
    beNDMWWindowTitle_Destroy((beNDMWWindowTitle *)&obj, 0);
    return vtable;
}

void beNDMWStatusTitle03_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle03_Register);
}

CallbackArray *beNDMWStatusTitle03_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle03_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle03_GetMetaObjectFunction,
        "beNDMWStatusTitle03",
        0x50, /* instance size */
        beNDMWStatusTitle03_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle03_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle03_GetMetaObject();
}

