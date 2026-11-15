igMetaObject *g_beNDMWItemBaseList_metaObject;

void beNDMWItemBaseList_Create(int arg0) {
    FUN_003c9210();
    igMetaObject_CreateInstance(g_beNDMWItemBaseList_metaObject, arg0);
}

igMetaObject *FUN_003c9130(void) {
    if (g_beNDMWItemBaseList_metaObject == 0) {
        g_beNDMWItemBaseList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWItemBaseList_metaObject;
}

void *beNDMWItemBaseList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBaseList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c9210();
    }
    return g_beNDMWItemBaseList_metaObject;
}

int beNDMWItemBaseList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c6e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c9210(void)
{
    igMetaObject_RunStaticInit(beNDMWItemBaseList_Register);
}

static igMetaObjectCallback g_beNDMWItemBaseList_callbackList[] = { FUN_003c9360, 0 };

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

