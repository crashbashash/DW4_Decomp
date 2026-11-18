igMetaObject *g_igMatrixObjectList_metaObject;

igMetaObject *igMatrixObjectList_GetOrCreateMetaObject(void) {
    if (g_igMatrixObjectList_metaObject == 0) {
        g_igMatrixObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixObjectList_metaObject;
}

igMetaObject *igMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrixObjectList_EnsureRegistered();
    return g_igMatrixObjectList_metaObject;
}

int igMatrixObjectList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igMatrixObjectList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igMatrixObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectList_Register);
}

static igMetaObjectCallback g_igMatrixObjectList_callbackList[] = { igMatrixObject_EnsureRegistered, 0 };

CallbackArray *igMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMatrixObjectList_GetMetaObjectFunction,
        "igMatrixObjectList",
        0x14, /* instance size */
        igMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectList_callbackList /* callback list */
    );
}

void igMatrixObjectList_GetMetaObjectFunction(void) {
    igMatrixObjectList_GetMetaObject();
}

