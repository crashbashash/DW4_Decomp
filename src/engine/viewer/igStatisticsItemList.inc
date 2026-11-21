igMetaObject *g_igStatisticsItemList_metaObject;

igMetaObject *igStatisticsItemList_GetOrCreateMetaObject(void) {
    if (g_igStatisticsItemList_metaObject == 0) {
        g_igStatisticsItemList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStatisticsItemList_metaObject;
}

void *igStatisticsItemList_GetMetaObject(void) {
    igMetaObject *g = g_igStatisticsItemList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        igStatisticsItemList_EnsureRegistered();
    }
    return g_igStatisticsItemList_metaObject;
}

int igStatisticsItemList_GetVTable(void) {
    struct Obj_458b80 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igStatisticsItemList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igStatisticsItemList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStatisticsItemList_Register);
}

static igMetaObjectCallback g_igStatisticsItemList_callbackList[] = { igStatisticsItem_EnsureRegistered, 0 };

CallbackArray *igStatisticsItemList_Register(void) {
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igStatisticsItemList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igStatisticsItemList_GetMetaObjectFunction,
        "igStatisticsItemList",
        0x14, /* instance size */
        igStatisticsItemList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStatisticsItemList_callbackList /* callback list */
    );
}

void igStatisticsItemList_GetMetaObjectFunction(void) {
    igStatisticsItemList_GetMetaObject();
}

