igMetaObject *g_igGeometryAttrList_metaObject;

igMetaObject *igGeometryAttrList_GetOrCreateMetaObject(void) {
    if (g_igGeometryAttrList_metaObject == 0) {
        g_igGeometryAttrList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGeometryAttrList_metaObject;
}

igMetaObject *igGeometryAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttrList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryAttrList_EnsureRegistered();
    return g_igGeometryAttrList_metaObject;
}

int igGeometryAttrList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igGeometryAttrList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem + 916));
}

void igGeometryAttrList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryAttrList_Register);
}

static igMetaObjectCallback g_igGeometryAttrList_callbackList[] = { FUN_001378f0, 0 };

CallbackArray *igGeometryAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometryAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryAttrList_GetMetaObject,
        "igGeometryAttrList",
        0x14, /* instance size */
        igGeometryAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryAttrList_callbackList /* callback list */
    );
}

void thunk_igGeometryAttrList_GetMetaObject(void) {
    igGeometryAttrList_GetMetaObject();
}

