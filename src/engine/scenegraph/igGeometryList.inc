igMetaObject *g_igGeometryList_metaObject;

igMetaObject *igGeometryList_GetOrCreateMetaObject(void) {
    if (g_igGeometryList_metaObject == 0) {
        g_igGeometryList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGeometryList_metaObject;
}

igMetaObject *igGeometryList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryList_EnsureRegistered();
    return g_igGeometryList_metaObject;
}

int igGeometryList_GetVTable(void) {
    union U u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igGeometryList_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igGeometryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryList_Register);
}

static igMetaObjectCallback g_igGeometryList_callbackList[] = { igGeometry_EnsureRegistered, 0 };

CallbackArray *igGeometryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometryList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igGeometryList_GetMetaObjectFunction,
        "igGeometryList",
        0x14, /* instance size */
        igGeometryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryList_callbackList /* callback list */
    );
}

void igGeometryList_GetMetaObjectFunction(void) {
    igGeometryList_GetMetaObject();
}

