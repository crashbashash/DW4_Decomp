igMetaObject *g_igNonRefCountedViewList_metaObject;

igMetaObject *igNonRefCountedViewList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedViewList_metaObject == 0) {
        g_igNonRefCountedViewList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedViewList_metaObject;
}

igMetaObject *igNonRefCountedViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedViewList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedViewList_EnsureRegistered();
    return g_igNonRefCountedViewList_metaObject;
}

int igNonRefCountedViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedViewList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedViewList_Register);
}

static igMetaObjectCallback g_igNonRefCountedViewList_callbackList[] = { igView_EnsureRegistered, 0 };

CallbackArray *igNonRefCountedViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedViewList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igNonRefCountedViewList_GetMetaObjectFunction,
        "igNonRefCountedViewList",
        0x14, /* instance size */
        igNonRefCountedViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedViewList_callbackList /* callback list */
    );
}

void igNonRefCountedViewList_GetMetaObjectFunction(void) {
    igNonRefCountedViewList_GetMetaObject();
}

