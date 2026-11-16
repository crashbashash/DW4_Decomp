igMetaObject *g_igMatrixObjectList_metaObject;

igMetaObject *FUN_001e4ae0(void) {
    if (g_igMatrixObjectList_metaObject == 0) {
        g_igMatrixObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixObjectList_metaObject;
}

igMetaObject *igMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4bc0();
    return g_igMatrixObjectList_metaObject;
}

int igMatrixObjectList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igMatrixObjectList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_001e4bc0(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectList_Register);
}

static igMetaObjectCallback g_igMatrixObjectList_callbackList[] = { FUN_001e4d30, 0 };

CallbackArray *igMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMatrixObjectList_GetMetaObject,
        "igMatrixObjectList",
        0x14, /* instance size */
        igMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igMatrixObjectList_GetMetaObject(void) {
    igMatrixObjectList_GetMetaObject();
}

