igMetaObject *g_beNDMWItemBaseList_metaObject;

beNDMWItemBaseList *beNDMWItemBaseList_Create(int allocator) {
    beNDMWItemBaseList_EnsureRegistered();
    return (beNDMWItemBaseList *)igMetaObject_CreateInstance(g_beNDMWItemBaseList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWItemBaseList_GetOrCreateMetaObject(void) {
    if (g_beNDMWItemBaseList_metaObject == 0) {
        g_beNDMWItemBaseList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWItemBaseList_metaObject;
}

void *beNDMWItemBaseList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBaseList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemBaseList_EnsureRegistered();
    }
    return g_beNDMWItemBaseList_metaObject;
}

int beNDMWItemBaseList_GetVTable(void) {
    beNDMWItemBaseList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemBaseList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWItemBaseList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBaseList_Register);
}

static igMetaObjectCallback g_beNDMWItemBaseList_callbackList[] = { beNDMWItemBase_EnsureRegistered, 0 };

CallbackArray *beNDMWItemBaseList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemBaseList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWItemBaseList_GetMetaObject,
        "beNDMWItemBaseList",
        0x14, /* instance size */
        beNDMWItemBaseList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWItemBaseList_callbackList /* callback list */
    );
}

void beNDMWItemBaseList_GetMetaObject(void)
{
    beNDMWItemBaseList_GetReadyMetaObject();
}

