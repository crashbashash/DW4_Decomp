igMetaObject *g_igGeometryList_metaObject;

igMetaObject *igGeometryList_GetOrCreateMetaObject(void) {
    if (g_igGeometryList_metaObject == 0) {
        g_igGeometryList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igGeometryList_vtable[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void igGeometryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryList_Register);
}

static igMetaObjectCallback g_igGeometryList_callbackList[] = { igGeometry_EnsureRegistered, 0 };

void igGeometryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometryList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryList_GetMetaObject,
        "igGeometryList",
        0x14, /* instance size */
        igGeometryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryList_callbackList /* callback list */
    );
}

void thunk_igGeometryList_GetMetaObject(void) {
    igGeometryList_GetMetaObject();
}

