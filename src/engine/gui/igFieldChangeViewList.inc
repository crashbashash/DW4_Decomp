igMetaObject *g_igFieldChangeViewList_metaObject;

igMetaObject *igFieldChangeViewList_GetOrCreateMetaObject(void) {
    if (g_igFieldChangeViewList_metaObject == 0) {
        g_igFieldChangeViewList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFieldChangeViewList_metaObject;
}

igMetaObject *igFieldChangeViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igFieldChangeViewList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFieldChangeViewList_EnsureRegistered();
    return g_igFieldChangeViewList_metaObject;
}

int igFieldChangeViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFieldChangeViewList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igFieldChangeViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFieldChangeViewList_Register);
}

static igMetaObjectCallback g_igFieldChangeViewList_callbackList[] = { igFieldChangeView_EnsureRegistered, 0 };

CallbackArray *igFieldChangeViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFieldChangeViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igFieldChangeViewList_GetMetaObjectFunction,
        "igFieldChangeViewList",
        0x14, /* instance size */
        igFieldChangeViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFieldChangeViewList_callbackList /* callback list */
    );
}

void igFieldChangeViewList_GetMetaObjectFunction(void) {
    igFieldChangeViewList_GetMetaObject();
}

