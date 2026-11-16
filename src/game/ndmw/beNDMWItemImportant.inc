igMetaObject *g_beNDMWItemImportant_metaObject;

beNDMWItemImportant *beNDMWItemImportant_Create(int allocator) {
    beNDMWItemImportant_EnsureRegistered();
    return (beNDMWItemImportant *)igMetaObject_CreateInstance(g_beNDMWItemImportant_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWItemImportant_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemImportant_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWItemImportant_EnsureRegistered();
done:
    return g_beNDMWItemImportant_metaObject;
}

int beNDMWItemImportant_GetVTable(void) {
    beNDMWItemImportant obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemImportant_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void beNDMWItemImportant_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemImportant_Register);
}

CallbackArray *beNDMWItemImportant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemImportant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemImportant_GetMetaObject,
        "beNDMWItemImportant",
        0x14, /* instance size */
        beNDMWItemImportant_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemImportant_GetMetaObject(void)
{
    beNDMWItemImportant_GetReadyMetaObject();
}

