igMetaObject *g_igMessageReceiverList_metaObject;

igMetaObject *igMessageReceiverList_GetOrCreateMetaObject(void) {
    if (g_igMessageReceiverList_metaObject == 0) {
        g_igMessageReceiverList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageReceiverList_metaObject;
}

igMetaObject *igMessageReceiverList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiverList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessageReceiverList_EnsureRegistered();
    return g_igMessageReceiverList_metaObject;
}

int igMessageReceiverList_GetVTable(void) {
    struct Obj_231830 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMessageReceiverList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMessageReceiverList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessageReceiverList_Register);
}

static igMetaObjectCallback g_igMessageReceiverList_callbackList[] = { igMessageReceiver_EnsureRegistered, 0 };

CallbackArray *igMessageReceiverList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageReceiverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMessageReceiverList_GetMetaObjectFunction,
        "igMessageReceiverList",
        0x14, /* instance size */
        igMessageReceiverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageReceiverList_callbackList /* callback list */
    );
}

void igMessageReceiverList_GetMetaObjectFunction(void) {
    igMessageReceiverList_GetMetaObject();
}

