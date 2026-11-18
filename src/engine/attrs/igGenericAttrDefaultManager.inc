igMetaObject *g_igGenericAttrDefaultManager_metaObject;

igGenericAttrDefaultManager *igGenericAttrDefaultManager_Create(igMemoryPoolView *pool) {
    igGenericAttrDefaultManager_EnsureRegistered();
    return (igGenericAttrDefaultManager *)igMetaObject_CreateInstance(g_igGenericAttrDefaultManager_metaObject, pool);
}

igMetaObject *igGenericAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGenericAttrDefaultManager_EnsureRegistered();
    return g_igGenericAttrDefaultManager_metaObject;
}

int igGenericAttrDefaultManager_GetVTable(void) {
    struct O_137b40 o;
    int pad[2];
    igObject_InitHeader((igObject *)&o);
    o.vt = g_igGenericAttrDefaultManager_vtable;
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igGenericAttrDefaultManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGenericAttrDefaultManager_Register);
}

CallbackArray *igGenericAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGenericAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        igGenericAttrDefaultManager_GetMetaObjectFunction,
        "igGenericAttrDefaultManager",
        8, /* instance size */
        igGenericAttrDefaultManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igGenericAttrDefaultManager_GetMetaObjectFunction(void) {
    igGenericAttrDefaultManager_GetMetaObject();
}

