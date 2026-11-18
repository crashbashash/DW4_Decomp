igMetaObject *g_igMessageFilterList_metaObject;

igMetaObject *igMessageFilterList_GetOrCreateMetaObject(void) {
    if (g_igMessageFilterList_metaObject == 0) {
        g_igMessageFilterList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageFilterList_metaObject;
}

igMetaObject *igMessageFilterList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageFilterList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessageFilterList_EnsureRegistered();
    return g_igMessageFilterList_metaObject;
}

int igMessageFilterList_GetVTable(void) {
    struct Obj_231a70 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMessageFilterList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMessageFilterList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessageFilterList_Register);
}

static igMetaObjectCallback g_igMessageFilterList_callbackList[] = { igMessageFilter_EnsureRegistered, 0 };

CallbackArray *igMessageFilterList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageFilterList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMessageFilterList_GetMetaObjectFunction,
        "igMessageFilterList",
        0x14, /* instance size */
        igMessageFilterList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageFilterList_callbackList /* callback list */
    );
}

void igMessageFilterList_GetMetaObjectFunction(void) {
    igMessageFilterList_GetMetaObject();
}

