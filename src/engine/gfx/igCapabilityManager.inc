igMetaObject *g_igCapabilityManager_metaObject;

igMetaObject *igCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igCapabilityManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCapabilityManager_EnsureRegistered();
    return g_igCapabilityManager_metaObject;
}

void igCapabilityManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCapabilityManager_Register);
}

CallbackArray *igCapabilityManager_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igCapabilityManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igCapabilityManager_GetMetaObjectFunction,
        "igCapabilityManager",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCapabilityManager_GetMetaObjectFunction(void) {
    igCapabilityManager_GetMetaObject();
}

