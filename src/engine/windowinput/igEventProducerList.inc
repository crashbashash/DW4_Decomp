igMetaObject *g_igEventProducerList_metaObject;

igMetaObject *igEventProducerList_GetOrCreateMetaObject(void) {
    if (g_igEventProducerList_metaObject == 0) {
        g_igEventProducerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEventProducerList_metaObject;
}

igMetaObject *igEventProducerList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventProducerList_EnsureRegistered();
    return g_igEventProducerList_metaObject;
}

int igEventProducerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igEventProducerList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igEventProducerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventProducerList_Register);
}

static igMetaObjectCallback g_igEventProducerList_callbackList[] = { igEventProducer_EnsureRegistered, 0 };

CallbackArray *igEventProducerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEventProducerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igEventProducerList_GetMetaObjectFunction,
        "igEventProducerList",
        0x14, /* instance size */
        igEventProducerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventProducerList_callbackList /* callback list */
    );
}

void igEventProducerList_GetMetaObjectFunction(void) {
    igEventProducerList_GetMetaObject();
}

