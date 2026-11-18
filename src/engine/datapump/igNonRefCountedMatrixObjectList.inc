igMetaObject *g_igNonRefCountedMatrixObjectList_metaObject;

igMetaObject *FUN_001e4970(void) {
    if (g_igNonRefCountedMatrixObjectList_metaObject == 0) {
        g_igNonRefCountedMatrixObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedMatrixObjectList_metaObject;
}

igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedMatrixObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4a50();
    return g_igNonRefCountedMatrixObjectList_metaObject;
}

int igNonRefCountedMatrixObjectList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedMatrixObjectList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_001e4a50(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedMatrixObjectList_Register);
}

static igMetaObjectCallback g_igNonRefCountedMatrixObjectList_callbackList[] = { FUN_001e4d30, 0 };

CallbackArray *igNonRefCountedMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedMatrixObjectList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,
        "igNonRefCountedMatrixObjectList",
        0x14, /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedMatrixObjectList_GetMetaObject(void) {
    igNonRefCountedMatrixObjectList_GetMetaObject();
}

