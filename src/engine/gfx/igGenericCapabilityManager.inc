igMetaObject *g_igGenericCapabilityManager_metaObject;

void igGenericCapabilityManager_Create(int arg0) {
    igGenericCapabilityManager_EnsureRegistered();
    igMetaObject_CreateInstance(g_igGenericCapabilityManager_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igGenericCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igGenericCapabilityManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGenericCapabilityManager_EnsureRegistered();
    return g_igGenericCapabilityManager_metaObject;
}

int igGenericCapabilityManager_GetVTable(void) {
    struct Obj_14f350 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGenericCapabilityManager_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igGenericCapabilityManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGenericCapabilityManager_Register);
}

CallbackArray *igGenericCapabilityManager_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGenericCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        igGenericCapabilityManager_GetMetaObjectFunction,
        "igGenericCapabilityManager",
        8, /* instance size */
        igGenericCapabilityManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igGenericCapabilityManager_GetMetaObjectFunction(void) {
    igGenericCapabilityManager_GetMetaObject();
}

