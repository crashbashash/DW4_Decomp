void beNDMWItemBaseList_Create(int arg0) {
    FUN_003c9210();
    igMetaObject_CreateInstance(*(int *)0x58BF88, arg0);
}

igMetaObject *FUN_003c9130(void) {
    if (g_beNDMWItemBaseList_metaObject[0] == 0) {
        g_beNDMWItemBaseList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWItemBaseList_metaObject[0];
}

void *beNDMWItemBaseList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemBaseList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c9210();
    }
    return g_beNDMWItemBaseList_metaObject[0];
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

void *beNDMWItemBaseList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemBaseList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWItemBaseList_GetMetaObject,
        beNDMWItemBaseList_className,
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

