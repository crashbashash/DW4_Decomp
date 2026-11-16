igMetaObject *g_beNDMWItemBaseList_metaObject;

void beNDMWItemBaseList_Create(int allocator) {
    beNDMWItemBaseList_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWItemBaseList_metaObject, allocator);
}

igMetaObject *beNDMWItemBaseList_GetOrCreateMetaObject(void) {
    if (g_beNDMWItemBaseList_metaObject == 0) {
        g_beNDMWItemBaseList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWItemBaseList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWItemBaseList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBaseList_Register);
}

static igMetaObjectCallback g_beNDMWItemBaseList_callbackList[] = { beNDMWItemBase_EnsureRegistered, 0 };

void *beNDMWItemBaseList_Register(void) {
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

